#pragma once

#include <vector>
#include <string>

namespace blc {
	/// the main function is used in the static library. if you want to use your hown main, you're inveited to link with the shared library rather than the static one.
	int main(int ac, std::vector<std::string> av, std::vector<std::string> env); ///< main called by blc after a clean start-up
}