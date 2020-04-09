#include "../blc/blc.hpp"
#include <iostream>
#include <unistd.h>

#include "catch.hpp"

class testStream : public blc::stream {
public:
	testStream() = default;
	virtual void		write(const std::string &str) const {}
	virtual std::string	read() const {return "";}
	virtual std::string	read(int n) const {return "";}
	virtual void		close() {}
	virtual bool		readable() const {return true;}
	virtual bool		writable() const {return true;}
	virtual bool		isClosed() const {return true;}
};

TEST_CASE( "stream tested", "[stream]" ) {
	testStream test;

	std::string	recv;
	char		*str;
	char		c;
	int		i;
	double		d;

	test << std::string("ok") << "test" << 0 << 'a' << 1.1;

	test >> recv >> str >> c >> i >> d;
}
