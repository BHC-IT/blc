#include "blc/stringOp.hpp"

bool blc::tools::isNumber(const std::string& s)
{
	if (s.empty())
		return (false);
	for (auto it : s){
		if (std::isdigit(it) == false){
			if (!(it == '-' && s.size() != 1))
				return (false);
		}
	}
	return (true);
}

std::vector<std::string> blc::tools::cut(const std::string &s, char delim)
{
	std::vector<std::string>	v;
	std::string 			tmp = s;

	for (auto it = blc::tools::serializable::cut(tmp, delim); it != ""; it = blc::tools::serializable::cut(tmp, delim)){
		v.push_back(it);
	}
	return (v);
}

std::vector<std::string> blc::tools::cut(const std::string &s, std::string delim, bool cut_on)
{
	return (blc::tools::cut(s, delim[0]));
}