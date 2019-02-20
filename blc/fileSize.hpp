#pragma once

#include <string>
#include <istream>
#include <fstream>
#include <iostream>

namespace blc {
	namespace tools {
		long fileSize(std::ifstream &file);
		long fileSize(std::ifstream &file, std::streampos pos, std::ios_base::seekdir way = std::ios_base::beg);
		long fileSize(std::istream &file);
		long fileSize(std::istream &file, std::streampos pos, std::ios_base::seekdir way = std::ios_base::beg);
		long fileSize(const std::string &file);
	}
}
