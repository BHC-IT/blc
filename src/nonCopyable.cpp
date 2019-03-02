#include "blc/nonCopyable.hpp"

blc::symbole::nonCopyable::nonCopyable()
{
}

blc::symbole::nonCopyable::nonCopyable(const blc::symbole::nonCopyable &other)
{
	(void)other;
}

blc::symbole::nonCopyable &blc::symbole::nonCopyable::operator=(const blc::symbole::nonCopyable &other)
{
	(void)other;

	return (*this);
}