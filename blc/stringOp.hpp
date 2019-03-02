#pragma once

#include <vector>
#include <algorithm>
#include "blc/serializable.hpp"

namespace blc {
	namespace tools {
		bool 				isNumber(const std::string& s);
		std::vector<std::string>	cut(const std::string &s, char delim = ' ');
		std::vector<std::string>	cut(const std::string &s, std::string delim, bool cut_on = true);
	}
}