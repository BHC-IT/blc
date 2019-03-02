#include "blc/stream.hpp"

blc::stream &blc::stream::operator<<(const std::string &str)
{

	return (*this);
}

blc::stream &blc::stream::operator<<(char str[])
{

	return (*this);
}

blc::stream &blc::stream::operator<<(int nb)
{

	return (*this);
}

blc::stream &blc::stream::operator<<(double nb)
{

	return (*this);
}

blc::stream &blc::stream::operator<<(char c)
{

	return (*this);
}


blc::stream &blc::stream::operator>>(std::string &str)
{

	return (*this);
}

blc::stream &blc::stream::operator>>(int &nb)
{

	return (*this);
}

blc::stream &blc::stream::operator>>(double &nb)
{

	return (*this);
}
