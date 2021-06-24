/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <iostream>
#include "blc/serializable.hpp"

static inline char hex(char c) {
	std::string tab("0123456789ABCDEF");
	if (c >= 16)
		return (tab[c / 16]);
	return (tab[c]);
}

static inline char dehex(char c) {
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return ((c - 'a') + 10);
	else if (c >= 'A' && c <= 'F')
		return ((c - 'A') + 10);
	return (0);
}

std::string blc::tools::serializable::hexToString(const std::string &str) {
	std::string	ret;
	int		i;

	i = 0;
	while (str[i * 2]) {
		ret += ' ';
		ret[i] = dehex(str[i * 2]);
		ret[i] = (ret[i] * 16) + dehex(str[(i * 2) + 1]);
		i++;
	}
	return (ret);
}

std::string blc::tools::serializable::stringToHex(const std::string &str) {
	std::string	ret;
	int		i;

	i = 0;
	while (str[i]) {
		ret += ' ';
		ret += ' ';
		ret[i * 2] = hex(str[i]);
		ret[(i * 2) + 1] = hex(str[i] % 16);
		i++;
	}
	return (ret);
}

std::tuple<std::string, std::string> blc::tools::serializable::cut(const std::string &str, char cut) {
	int 		i = str.find(cut);
	std::string	before = str.substr(0, i);
	std::string	after = str.substr(i + 1, str.size());

	if (i == -1)
		return (std::make_tuple(str, ""));
	return (std::make_tuple(before, after));
}
