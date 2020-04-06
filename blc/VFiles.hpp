/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

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
			~VFiles();
			///< destructor

			VFiles(VFiles&& vFile);
			///< move constructor

			VFiles 	(const VFiles&) = delete;
			///< copy constructor can't be declared

			explicit VFiles(const std::string &fileName);
			///< clasic constructor

			void		close();
			///< disable actions on VFile

			std::string	read() const;
			///< read a ligne of VFile

			bool		readable() const;
			///< return a boolean to know if we can read VFile

			bool		writable() const;
			///< return a boolean to know if we can write on VFile

			bool		isClosed() const;
			///< return a boolean to know if we can do some actions on VFile

			std::string	read(const int n) const;
			///< read n characters of VFile

			void		write(const std::string &str) const;
			///< write on VFile

			void		open();
			///< allow actions on VFile

			void		align();
			///< write on file the content of VFile's cache

			void		unload();
			///< write on file the content of VFile's cache and disable actions on VFile

			void		refresh();
			///< filled VFile's cache with content of File

			int		tellg() const;
			///< return position of cursor in VFile

			int		gCount() const;
			///< return size of VFile's cache

			void		seekg(const int pos);
			///< set the cursor at pos

			void		seekg(const int pos, const enum seekDir sd);
			///< move cursor of pos square from sd (sd can take three value : beg for begin of VFile, end for end of VFile and cur for current place of cursor in VFile )


		private:
			std::fstream	_file;
			std::string	_cache;
			int		_cursor;
			std::string	_fileName;
			bool		_isClosed;
		};

	}  // namespace tools

}  // namespace blc
