#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "spawn tested", "[spawn]" ) {
	blc::Process::spawn ls("/bin/ls");

	std::cout << "ls : " << ls.read() << std::endl;

	blc::Process::spawn ll("/bin/ls -l");

	std::cout << "ll : " << ll.read() << std::endl;

	blc::Process::spawn la("/bin/ls", {"-l", "-a"});

	std::cout << "la : " << la.read() << std::endl;
}
