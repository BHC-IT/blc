#include <iostream>
#include "blc/serializable.hpp"

static inline char hex(char c)
{
	std::string tab("0123456789ABCDEF");
	if (c >= 16)
		return (tab[c / 16]);
	return (tab[c]);
}

static inline char dehex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return ((c - 'a') + 10);
	else if (c >= 'A' && c <= 'F')
		return ((c - 'A') + 10);
	return (0);
}

std::string blc::tools::serializable::hexToString(const std::string &str)
{
	std::string	ret;
	int		i;

	i = 0;
	while (str[i * 2]){
		ret += ' ';
		ret[i] = dehex(str[i * 2]);
		ret[i] = (ret[i] * 16) + dehex(str[(i * 2) + 1]);
		i++;
	}
	return (ret);
}

std::string blc::tools::serializable::stringToHex(const std::string &str)
{
	std::string	ret;
	int		i;

	i = 0;
	while (str[i]){
		ret += ' ';
		ret += ' ';
		ret[i * 2] = hex(str[i]);
		ret[(i * 2) + 1] = hex(str[i] % 16);
		i++;
	}
	return (ret);
}

std::string blc::tools::serializable::cut(std::string &str, char cut)
{
	int 		i = str.find(cut);
	std::string	ret = str.substr(0, i);

	str = str.substr(i + 1, str.size());
	if (i == -1)
		str = "";

	return (ret);
}

std::string blc::tools::serializable::cut(std::string &&str, char cut)
{
	int 		i = str.find(cut);
	std::string	ret = str.substr(0, i);

	str = str.substr(i + 1, str.size());

	return (ret);
}
