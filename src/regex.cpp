#include "blc/regex.hpp"

#include <iostream>
bool blc::tools::regex(const std::string &filter, const std::string &target)
{
	int i = 0;
	int j = 0;

	if (filter == "*")
		return (true);
	else if (filter.size() == 0 || target.size() == 0)
		return (false);
	while (i != filter.size() && j != target.size()){
		if (filter[i] == '*' && i + 1 == filter.size())
			return (true);
		if (filter[i] != '*' && filter[i] != target[j])
			return (false);
		if (filter[i] == '*' && target[j + 1] == filter[i + 1]){
			i++;
		} else if (filter[i] == target[j]) {
			i++;
		}
		j++;
	}
	if (i == filter.size() && j == target.size())
		return (true);
	return (false);
}