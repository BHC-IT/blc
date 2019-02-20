#include <iostream>
#include "blc/cinReadable.hpp"

#include <fstream>
bool blc::tools::cinReadable()
{
	return (std::cin.rdbuf()->in_avail() > 0);
}

bool blc::tools::readable(std::istream &stream)
{
	return (stream.rdbuf()->in_avail() > 0);
}