/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <string>
#include <sstream>
#include "blc/errorHandle.hpp"

blc::error::exception::exception(std::string msg) : _msg(msg), _file("ND"), _func("ND"), _line(-1), _time(-1) {
	std::ostringstream oss;

	oss << "Error : " << msg;
	this->_msg = oss.str();
}

blc::error::exception::exception(std::string msg, std::string file, std::string func, int line, std::time_t time) :	_msg(msg),
															_file(file),
															_func(func),
															_line(line),
															_time(time) {
	std::ostringstream oss;

	oss << msg;
	this->_msg = oss.str();
}
