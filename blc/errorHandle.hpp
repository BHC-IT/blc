/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <string>
#include <exception>
#include <ctime>

#ifndef assertError
	#define assertError(x) std::string(__FILE__) + ": " + __PRETTY_FUNCTION__ + ": " + std::to_string(__LINE__) + ": " + x
	#define traceError(x) blc::error::exception(x, __FILE__, __PRETTY_FUNCTION__, __LINE__, std::time(NULL))
#endif

namespace blc {
	namespace error {
		/// class to throw error.
		class exception : public std::exception {
		public:
			explicit exception(std::string msg);
			exception(std::string msg, std::string file, std::string func = "ND", int line = -1, std::time_t time = -1);
			///< construct the exception with the error message

			~exception() {}
			///< chain throw

			virtual const char		*what() const throw() {return (this->_msg.c_str());}
			///< return the error message

			virtual const std::string	where() const throw() {return (this->_file);}
			///< return the error message

			virtual const std::string	whom() const throw() {return (this->_func);}
			///< return the error message

			virtual const int		line() const throw() {return (this->_line);}
			///< return the error message

			virtual const std::time_t	when() const throw() {return (this->_time);}

		private:
			std::string	_msg;  ///< error message
			std::string	_file;
			std::string	_func;
			int		_line;
			std::time_t	_time;
		};

		inline exception expInfo(std::string str) {
			exception exp(str, __FILE__, __PRETTY_FUNCTION__, __LINE__, std::time(NULL));

			return (exp);
		}

	}  // namespace error

}  // namespace blc
