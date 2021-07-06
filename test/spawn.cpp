#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "spawn tested", "[spawn]" ) {
	blc::Process::spawn ls("ls");
	std::string out;

	while((out = ls.read()) != "") std::cout << "ls : " << out << std::endl;

	blc::Process::spawn ll("ls -l");

	while((out = ll.read()) != "") std::cout << "ll : " << out << std::endl;

	blc::Process::spawn la("ls", {"-l", "-a"});

	while((out = la.read()) != "") std::cout << "la : " << out << std::endl;
}
