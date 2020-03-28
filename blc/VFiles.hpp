#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "stream.hpp"
#include "blc/nonCopyable.hpp"

namespace blc {
	namespace tools {
		class VFiles : private symbole::nonCopyable, public stream{
		public:
			enum seekDir {beg, end, cur};
			//constructeur/destructeur
			~VFiles	(); ///< destructor
			VFiles 	(VFiles&& vFile); ///< move constructor
			VFiles 	(const VFiles&) = delete; ///< copy constructor can't be declared
			VFiles	(const std::string &fileName); ///< clasic constructor
			//Fonction abstraites héritées de stream
			void		close(); ///< disable actions on VFile
			std::string	read() const; ///< read a ligne of VFile
			bool		readable() const; ///< return a boolean to know if we can read VFile
			bool		writable() const; ///< return a boolean to know if we can write on VFile
			bool		isClosed() const; ///< return a boolean to know if we can do some actions on VFile
			std::string	read(const int n) const; ///< read n characters of VFile
			void		write(const std::string &str) const; ///< write on VFile
			//autre
			void	open(); ///< allow actions on VFile
			void	align(); ///< write on file the content of VFile's cache
			void	unload(); ///< write on file the content of VFile's cache and disable actions on VFile
			void	refresh(); ///< filled VFile's cache with content of File
			int		tellg() const; ///< return position of cursor in VFile
			int		gCount() const; ///< return size of VFile's cache
			void	seekg(const int pos); ///< set the cursor at pos
			void	seekg(const int pos, const enum seekDir sd); ///< move cursor of pos square from sd (sd can take three value : beg for begin of VFile, end for end of VFile and cur for current place of cursor in VFile )
		private:
			//attributs
			std::fstream	_file;
			std::string 	_cache;
			int				_cursor;
			std::string 	_fileName;
			bool			_isClosed;
		};
	}
}