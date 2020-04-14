/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <iostream>

namespace blc {
	/// stream abstraction to construct stream in the blc fashion
	class stream {
	public:
		stream() = default;
		~stream() = default;
		virtual void		write(const std::string &str) const = 0;
		virtual std::string	read() const = 0;
		virtual std::string	read(int n) const = 0;
		virtual void		close() = 0;
		virtual bool		readable() const = 0;
		virtual bool		writable() const = 0;
		virtual bool		isClosed() const = 0;
		stream			&operator<<(const std::string &str);
		stream			&operator<<(const char str[]);
		stream			&operator<<(int nb);
		stream			&operator<<(double nb);
		stream			&operator<<(char c);
		stream			&operator>>(std::string &str);
		stream			&operator>>(char str[]);
		stream			&operator>>(char c);
		stream			&operator>>(int &nb);
		stream			&operator>>(double &nb);

	private:
	};

}  // namespace blc

// std::ostream &operator<<(std::ostream &ostream, blc::stream &socket);
