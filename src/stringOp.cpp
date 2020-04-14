/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "blc/stringOp.hpp"

bool blc::tools::isNumber(const std::string& s) {
	if (s.empty())
		return (false);
	for (auto it : s) {
		if (std::isdigit(it) == false) {
			if (!(it == '-' && s.size() != 1))
				return (false);
		}
	}
	return (true);
}

std::vector<std::string> blc::tools::cut(std::string s, char delim) {
	std::vector<std::string>	v;

	for (auto it = blc::tools::serializable::cut(s, delim); std::get<0>(it) != ""; it = blc::tools::serializable::cut(s, delim)) {
		v.push_back(std::get<0>(it));
		s = std::get<1>(it);
	}
	return (v);
}

std::vector<std::string> blc::tools::cut(const std::string &s, std::string delim, bool cut_on) {
	return (blc::tools::cut(s, delim[0]));
}
