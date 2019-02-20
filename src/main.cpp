#include <iostream>
#include <cstdlib>
#include <ctime>
#include "blc/blcmain.hpp"
#include "blc/errorHandle.hpp"

#ifdef _WIN32
	#include <winsock2.h>
#endif

int main(int ac, char **av, char **env)
{
	int ret;
	std::vector<std::string> newAv;
	std::vector<std::string> newEnv;

	std::srand(std::time(nullptr));
	#ifdef _WIN32
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2,0), &WSAData);
	#endif
	#ifdef __GNUC__
		std::cin.sync_with_stdio(false);
	#endif
	for (int i = 0; av[i]; i++){
		newAv.push_back(std::string(av[i]));
	}
	for (int i = 0; env[i]; i++){
		newEnv.push_back(std::string(env[i]));
	}
	std::cout << std::boolalpha;
	try {
		ret = blc::main(ac, newAv, newEnv);
	} catch (blc::error::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	#ifdef _WIN32
		WSACleanup();
	#endif
	return (ret);
}