/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "blc/fileSize.hpp"

int64_t blc::tools::fileSize(std::ifstream &file) {
	if (file.is_open() == false)
		return (-1);
	file.seekg(0, file.end);
	int64_t len = file.tellg();
	file.seekg(0, file.beg);

	return (len);
}

int64_t blc::tools::fileSize(std::ifstream &file, std::streampos pos, std::ios_base::seekdir way) {
	if (file.is_open() == false)
		return (-1);
	file.seekg(0, file.end);
	int64_t len = file.tellg();
	file.seekg(pos, way);

	return (len);
}

int64_t blc::tools::fileSize(std::istream &file) {
	file.seekg(0, file.end);
	int64_t len = file.tellg();
	file.seekg(0, file.beg);

	return (len);
}

int64_t blc::tools::fileSize(std::istream &file, std::streampos pos, std::ios_base::seekdir way) {
	file.seekg(0, file.end);
	int64_t len = file.tellg();
	file.seekg(pos, way);

	return (len);
}

int64_t blc::tools::fileSize(const std::string &file) {
	std::ifstream ifile(file, std::ios::in|std::ios::binary|std::ios::ate);

	if (ifile.is_open() == false)
		return (-1);
	ifile.seekg(0, ifile.end);
	int64_t len = ifile.tellg();
	ifile.seekg(0, ifile.beg);

	ifile.close();

	return (len);
}
