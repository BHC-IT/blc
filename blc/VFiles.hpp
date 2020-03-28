#include <string>
#include <fstream>
#include <iostream>
#include "stream.hpp"
#include "blc/nonCopyable.hpp"

namespace blc {
	namespace tools {
		class VFiles : private symbole::nonCopyable, public stream{
		private:
			//attributs
			std::fstream	_file;
			std::string 	_cache;
			int				_cursor;
			std::string 	_fileName;
			bool			_isClosed;
		public:
			//constructeur/destructeur
			~VFiles	();
			VFiles 	(VFiles&& vFile);
			VFiles 	(const VFiles&) = delete;
			VFiles	(const std::string &fileName);
			//Fonction abstraites héritées de stream
			void		close();
			std::string	read() const;
			bool		readable() const;
			bool		writable() const;
			bool		isClosed() const;
			std::string	read(const int n) const;
			void		write(const std::string &str) const;
			//autre
			void	open();
			void	align();
			void	unload();
			void	refresh();
			int		getCursor() const;
			void	setCursor(const int pos);
		};
	}
}