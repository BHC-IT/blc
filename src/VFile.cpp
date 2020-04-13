/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "blc/VFile.hpp"
#include "blc/errorHandle.hpp"

blc::tools::VFile::VFile(const std::string &fileName) : _file(fileName) {
	this->_fileName = fileName;
	this->refresh();
}

blc::tools::VFile::VFile(VFile&& vFile) : _file(vFile._fileName) {
	this->_fileName = vFile._fileName;
	this->refresh();
}

blc::tools::VFile::~VFile() {
	this->_file.close();
}

std::string blc::tools::VFile::getCache() const {
	return (this->_cache);
}

void blc::tools::VFile::setCache(std::string cache) {
	this->_cache = cache;
}

void blc::tools::VFile::write(const std::string &str) const {
	if (!this->_isClosed) {
		if (this->_cursor <= this->_cache.size()) {
			( const_cast <VFile*> (this) )->_cache.insert(this->_cursor, str);
			( const_cast <VFile*> (this) )->_cursor += str.size();
		} else {
			throw blc::error::exception("Cursor exeeds the size of file");
		}
	} else {
		throw blc::error::exception("Attempt to write on a closed virtual file");
	}
}

std::string blc::tools::VFile::read() const {
	if (!this->_isClosed) {
		if (this->_cursor <= this->_cache.size()) {
			std::string tmp = this->_cache.substr(this->_cursor, this->_cache.find_first_of('\n', this->_cursor) - this->_cursor);
			( const_cast <VFile*> (this) )->_cursor += tmp.size() + 1;
			return tmp;
		} else {
			throw blc::error::exception("Cursor exeeds the size of file");
		}
	} else {
		throw blc::error::exception("Attempt to read a closed virtual file");
	}
}

std::string blc::tools::VFile::read(const int n) const {
	if (!this->_isClosed) {
		if (this->_cursor + n <= this->_cache.size()) {
			std::string tmp;
			for (int i = 0 ; i < n ; i++)
				tmp += this->_cache.at(this->_cursor + i);
			( const_cast <VFile*> (this) )->_cursor += n;
			return tmp;
		} else {
			throw blc::error::exception("Cursor exeeds the size of file");
		}
	} else {
		throw blc::error::exception("Attempt to read a closed virtual file");
	}
}

void blc::tools::VFile::close() {
	this->_isClosed = true;
}

void blc::tools::VFile::open() {
	this->_isClosed = false;
	this->_cursor = 0;
}

bool blc::tools::VFile::readable() const {
	if (this->_isClosed == false)
		return (this->_file.is_open()) ? true : false;
	else
		return false;
}

bool blc::tools::VFile::writable() const {
	if (this->_isClosed == false)
		return (this->_file.is_open()) ? true : false;
	else
		return false;
}

bool blc::tools::VFile::isClosed() const {
	return this->_isClosed;
}

void blc::tools::VFile::refresh() {
	if (this->_file) {
		std::string ligne;
		std::string completFile;
		while(getline(this->_file, ligne)) {
			completFile = completFile + ligne + "\n";
		}
		if (completFile.size() > 0)
			completFile.erase(completFile.size()-1);
		this->_cache = completFile;
		this->open();
		this->_cursor = 0;
	} else {
		throw blc::error::exception("Impossible to open file " + this->_fileName);
	}
}

void blc::tools::VFile::unload() {
	this->align();
	this->close();
}

void blc::tools::VFile::align() {
	if (this->_file.is_open()) {
		std::ofstream ofs;
		ofs.open(this->_fileName, std::ofstream::out | std::ofstream::trunc);
		ofs << this->_cache;
		ofs.close();
	}
	else
		throw blc::error::exception("Impossible to open file " + this->_fileName);
}

int blc::tools::VFile::tellg() const {
	return this->_cursor;
}

void blc::tools::VFile::seekg(const int pos) {
	if (pos > this->_cache.size())
		throw blc::error::exception("Impossible to modify cursor (value to hight)");
	else
		this->_cursor = pos;
}

void blc::tools::VFile::seekg(const int pos, const enum blc::tools::seekDir sd) {
	switch(sd) {
	case beg:
		this->seekg(0);
		this->seekg(pos);
		break;
	case end:
		this->seekg(this->gCount());
		if (pos > 0) {
			throw blc::error::exception("Impossible to modify cursor (value to hight)");
		} else if (pos < 0) {
			if (abs(pos) > this->gCount())
				throw blc::error::exception("Impossible to modify cursor (value to low)");
		}
		this->seekg(this->tellg() + pos);
		break;
	case cur:
		if (this->tellg() + pos < 0 || this->tellg() + pos > this->gCount()) {
			this->seekg((this->tellg() + pos < 0)? 0 : this->gCount() );
			throw blc::error::exception("Impossible to modify cursor (value to hight or to low)");
		} else {
			this->seekg(this->tellg() + pos);
		}
		break;
	}
}

int blc::tools::VFile::gCount() const {
	return this->_cache.size();
}
