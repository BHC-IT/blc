#include "blc/VFiles.hpp"

blc::tools::VFiles::VFiles(const std::string &fileName) : _file(fileName)
{
	this->_fileName = fileName;
	this->refresh();
}

blc::tools::VFiles::VFiles(VFiles&& vFile) : _file(vFile._fileName)
{
	this->_fileName = vFile._fileName;
	this->refresh();
	delete &vFile;
}

blc::tools::VFiles::~VFiles()
{
	this->_file.close();
}

void blc::tools::VFiles::write(const std::string &str) const
{
	if (!this->_isClosed) {
		if (this->_cursor <= this->_cache.size())
		{
			( const_cast <VFiles*> (this) )->_cache.insert(this->_cursor, str);
			( const_cast <VFiles*> (this) )->_cursor += str.size();
		} else {
			throw blc::error::exception("ERROR : Cursor exeeds the size of file IN FUNCTION 'write(const std::string &str) const;' IN CLASS VFiles");
		}
	} else {
		throw blc::error::exception("ERROR : Attempt to write on a closed virtual file IN FUNCTION 'write(const std::string &str) const;' IN CLASS VFiles");
	}
}

std::string	blc::tools::VFiles::read() const
{
	if (!this->_isClosed)
	{
		if (this->_cursor <= this->_cache.size())
		{
			std::string tmp = this->_cache.substr(this->_cursor, this->_cache.find_first_of('\n', this->_cursor) - this->_cursor);
			( const_cast <VFiles*> (this) )->_cursor += tmp.size() + 1;
			return tmp;
		} else {
			throw blc::error::exception("ERROR : Cursor exeeds the size of file IN FUNCTION 'read() const;' IN CLASS VFiles");
		}
	}
	else
		throw blc::error::exception("ERROR : Attempt to read a closed virtual file IN FUNCTION 'read() const;' IN CLASS VFiles");
}

std::string	blc::tools::VFiles::read(const int n) const
{
	if (!this->_isClosed)
	{
		if (this->_cursor + n <= this->_cache.size())
		{
			std::string tmp;
			for (int i = 0 ; i < n ; i++)
				tmp += this->_cache.at(this->_cursor + i);
			( const_cast <VFiles*> (this) )->_cursor += n;
			return tmp;
		} else {
			throw blc::error::exception("ERROR : Cursor exeeds the size of file IN FUNCTION 'read(const int n) const;' IN CLASS VFiles");
		}
	} else {
		throw blc::error::exception("ERROR : Attempt to read a closed virtual file IN FUNCTION 'read(const int n) const;' IN CLASS VFiles");
	}
}

void blc::tools::VFiles::close()
{
	this->_isClosed = true;
}

void blc::tools::VFiles::open()
{
	this->_isClosed = false;
	this->_cursor = 0;
}

bool blc::tools::VFiles::readable() const
{
	if (!this->isClosed())
		return (this->_file) ? true : false;
	else
		return false;
}

bool blc::tools::VFiles::writable() const
{
	if (!this->isClosed())
		return (this->_file) ? true : false;
	else
		return false;
}

bool blc::tools::VFiles::isClosed() const
{
	return this->_isClosed;
}

void blc::tools::VFiles::refresh()
{
	if(this->_file) //Si l'ouverture s'est bien passée, on peut donc lire
	{
		std::string ligne; //Une variable pour stocker les lignes lues
		std::string completFile; //Une variable pour stocker les lignes lues
		while(getline(this->_file, ligne)) //Tant qu'on n'est pas à la fin, on lit
		{
			completFile = completFile + ligne + "\n";
		}
		if (completFile.size() > 0)
			completFile.erase(completFile.size()-1); //on supprime le dernier retour chariot
		this->_cache = completFile;
		this->open();
		this->_cursor = 0;
	}
	else
		throw blc::error::exception("ERROR: Impossible to open file " + this->_fileName + " IN FUNCTION 'refresh();' IN CLASS VFiles");
}

void blc::tools::VFiles::unload()
{
	this->align();
	this->close();
}

void blc::tools::VFiles::align()
{
	if(this->_file)  //On test si tout est OK
		this->_file << this->_cache;
	else
		throw blc::error::exception("ERROR: Impossible to open file " + this->_fileName + " IN FUNCTION 'align();' IN CLASS VFiles");
}

int blc::tools::VFiles::tellg() const
{
	return this->_cursor;
}

void blc::tools::VFiles::seekg(const int pos)
{
	if (pos > this->_cache.size())
		throw blc::error::exception("ERROR: Impossible to modify cursor (value to hight) IN FUNCTION 'seekg();' IN CLASS VFiles");
	else
		this->_cursor = pos;
}

enum seekDir {beg, end, cur};
void blc::tools::VFiles::seekg(const int pos, const enum seekDir sd)
{
	switch(sd)
	{
	case beg:
		this->seekg(0);
		this->seekg(pos);
		break;
	case end:
		this->seekg(this->gCount());
		if (pos > 0)
			throw blc::error::exception("ERROR: Impossible to modify cursor (value to hight) IN FUNCTION 'seekg();' IN CLASS VFiles");
		else if (pos < 0)
			if (abs(pos) > this->gCount())
				throw blc::error::exception("ERROR: Impossible to modify cursor (value to low) IN FUNCTION 'seekg();' IN CLASS VFiles");
			this->seekg(this->tellg() + pos);
		break;
	case cur:
		if (this->tellg() + pos < 0 || this->tellg() + pos > this->gCount())
		{
			this->seekg((this->tellg() + pos < 0)? 0 : this->gCount() );
			throw blc::error::exception("ERROR: Impossible to modify cursor (value to hight or to low) IN FUNCTION 'seekg();' IN CLASS VFiles");
		} else
			this->seekg(this->tellg() + pos);
		break;
	}
}

int blc::tools::VFiles::gCount() const
{
	return this->_cache.size();
}