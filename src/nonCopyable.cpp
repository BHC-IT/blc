#include "blc/nonCopyable.hpp"

blc::tools::nonCopyable::nonCopyable()
{
}

blc::tools::nonCopyable::nonCopyable(const blc::tools::nonCopyable &other)
{
	(void)other;
}

blc::tools::nonCopyable &blc::tools::nonCopyable::operator=(const blc::tools::nonCopyable &other)
{
	(void)other;

	return (*this);
}