#include "../blc/blc.hpp"
#include <iostream>

#include "catch.hpp"



TEST_CASE( "VFile tested", "[VFile]" ) {
	blc::tools::VFile file("../test/VFile.test");

	REQUIRE(file.isClosed() == false);
	REQUIRE(file.readable() == true);
	REQUIRE(file.writable() == true);
	REQUIRE(file.read() == "test line 1");
	REQUIRE(file.read() == "test line 2");


	file.close();
	REQUIRE(file.isClosed() == true);
	REQUIRE(file.readable() == false);
	REQUIRE(file.writable() == false);

	try {
		blc::tools::VFile falseFile("../test/VFile.test.test");
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Impossible to open file ../test/VFile.test.test"));
	}

	blc::tools::VFile file2(std::move(file));
	REQUIRE(file2.read() == "test line 1");
	REQUIRE(file2.read() == "test line 2");

	REQUIRE(file2.gCount() == 47);
	REQUIRE(file2.tellg() == 24);

	try {
		file2.seekg(1000);
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Impossible to modify cursor (value to hight)"));
	}

	try {
		file2.seekg(1000, blc::tools::seekDir::beg);
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Impossible to modify cursor (value to hight)"));
	}

	try {
		file2.seekg(1000, blc::tools::seekDir::cur);
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Impossible to modify cursor (value to hight or to low)"));
	}

	try {
		file2.seekg(1, blc::tools::seekDir::end);
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Impossible to modify cursor (value to hight)"));
	}

	file2.seekg(0);
	REQUIRE(file2.tellg() == 0);
	REQUIRE(file2.read(12) == "test line 1\n");

	file2.write("ok\n");

	std::cout << file2.getCache() << std::endl;

	file2.unload();

	blc::tools::VFile file3("../test/VFile.test");
	REQUIRE(file3.read() == "test line 1");
	REQUIRE(file3.read() == "ok");
	REQUIRE(file3.read() == "test line 2");
	REQUIRE(file3.read() == "test line 3");
	REQUIRE(file3.read() == "test line 4");
	try {
		file3.read();
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Cursor exeeds the size of file"));
	}

	file3.setCache("test");
	file3.unload();

	blc::tools::VFile file4("../test/VFile.test");
	REQUIRE(file4.read() == "test");
	try {
		file4.read();
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Cursor exeeds the size of file"));
	}

	try {
		file4.seekg(-50, blc::tools::seekDir::end);
	} catch (blc::error::exception &e) {
		REQUIRE(e.what() == std::string("Error : Impossible to modify cursor (value to low)"));
	}
	file4.seekg(-2, blc::tools::seekDir::end);
	REQUIRE(file4.read() == "st");
}
