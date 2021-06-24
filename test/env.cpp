#include <ctime> // time

#include "catch.hpp"
#include "blc/env.hpp"

TEST_CASE( "env tested", "[env]" ) {

	blc::Process::env<std::string, int> e;

	REQUIRE(e.size() == 0);

	e += std::make_pair("test", "test");
	e += std::make_pair("lol", 1);

	REQUIRE(std::get<std::string>(e["test"]) == "test");
	REQUIRE(std::get<int>(e["lol"]) == 1);

	e -= "test";
	e -= "lol";
	REQUIRE(e.size() == 0);

	e.emplace("test", "test");
	REQUIRE(std::get<std::string>(e["test"]) == "test");
	REQUIRE(e.size() == 1);

	e._pushRegister_unsafe();

	blc::Process::env<std::string, int> r = blc::Process::env<std::string, int>::getFromRegister_unsafe();

	REQUIRE(std::get<std::string>(r["test"]) == "test");
	REQUIRE(r.size() == 1);

	r["truc"] = "hello";
	REQUIRE(std::get<std::string>(r["truc"]) == "hello");
	REQUIRE(r.size() == 2);

	r._pushRegister_unsafe();

	e.pullRegister();
	REQUIRE(std::get<std::string>(e["truc"]) == "hello");
	REQUIRE(e.size() == 2);

	blc::Process::env<std::string, int> c(std::vector<std::string>{"TEST=test", "TRUC=truc"});
	REQUIRE(std::get<std::string>(c["TRUC"]) == "truc");
	REQUIRE(c.size() == 2);
}