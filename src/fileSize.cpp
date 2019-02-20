#include "blc/fileSize.hpp"

long blc::tools::fileSize(std::ifstream &file)
{
	if (file.is_open() == false)
		return (-1);
	file.seekg(0, file.end);
	long len = file.tellg();
	file.seekg(0, file.beg);

	return (len);
}

long fileSize(std::ifstream &file, std::streampos pos, std::ios_base::seekdir way)
{
	if (file.is_open() == false)
		return (-1);
	file.seekg(0, file.end);
	long len = file.tellg();
	file.seekg(pos, way);

	return (len);
}

long blc::tools::fileSize(std::istream &file)
{
	file.seekg(0, file.end);
	long len = file.tellg();
	file.seekg(0, file.beg);

	return (len);
}

long fileSize(std::istream &file, std::streampos pos, std::ios_base::seekdir way)
{
	file.seekg(0, file.end);
	long len = file.tellg();
	file.seekg(pos, way);

	return (len);
}

long blc::tools::fileSize(const std::string &file)
{
	std::ifstream ifile(file, std::ios::in|std::ios::binary|std::ios::ate);

	if (ifile.is_open() == false)
		return (-1);
	ifile.seekg(0, ifile.end);
	long len = ifile.tellg();
	ifile.seekg(0, ifile.beg);

	ifile.close();

	return (len);
}
