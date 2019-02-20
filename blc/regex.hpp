#pragma once

#include <string>

namespace blc {
	namespace tools {
		bool regex(const std::string &filter, const std::string &target); ///< test if the target is equivalent to the filter.
	}
}