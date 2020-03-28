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
			throw std::string("ERREUR : Le curseur dépasse la taille du fichier DANS LA FONCTION 'write(const std::string &str) const;' DANS LA CLASSE VFiles");
		}
	} else {
		throw std::string("ERREUR : Tentative d'écriture sur un fichier virtuel fermé DANS LA FONCTION 'write(const std::string &str) const;' DANS LA CLASSE VFiles");
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
			throw std::string("ERREUR : Le curseur dépasse la taille du fichier DANS LA FONCTION 'read() const;' DANS LA CLASSE VFiles");
		}
	}
	else
		throw std::string("ERREUR : Tentative de lecture sur un fichier virtuel fermé DANS LA FONCTION 'read() const;' DANS LA CLASSE VFiles");
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
			throw std::string("ERREUR : Le curseur dépasse la taille du fichier DANS LA FONCTION 'read(const int n) const;' DANS LA CLASSE VFiles");
		}
	} else {
		throw std::string("ERREUR : Tentative de lecture sur un fichier virtuel fermé DANS LA FONCTION 'read(const int n) const;' DANS LA CLASSE VFiles");
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
		throw std::string("ERREUR: Impossible d'ouvrir le fichier " + this->_fileName + " en lecture DANS LA FONCTION 'refresh();' DANS LA CLASSE VFiles");
}

void blc::tools::VFiles::unload()
{
	this->align();
	this->close();
}

void blc::tools::VFiles::align()
{
	if(this->_file)  //On teste si tout est OK
		this->_file << this->_cache;
	else
		throw std::string("ERREUR: Impossible d'ouvrir le fichier " + this->_fileName + " en lecture DANS LA FONCTION 'align();' DANS LA CLASSE VFiles");
}

int blc::tools::VFiles::getCursor() const
{
	return this->_cursor;
}

void blc::tools::VFiles::setCursor(const int pos)
{
	if (pos > this->_cache.size())
		throw std::string("ERREUR: Impossible modifier le curseur (valeur trop élevée) DANS LA FONCTION 'setCursor();' DANS LA CLASSE VFiles");
	else
		this->_cursor = pos;
}