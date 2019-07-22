#include <blc/blc.hpp>
#include <iostream>
#include <iomanip>
#include <functional>


int main()
{
	blc::tools::promise<int> prom([](resolver<int> resolve, rejecter reject){
		resolve(1);
	});

	prom.then([](int e){
		std::cout << e << std::endl;
	}).catcher([](blc::error::exception e){
		std::cout << e.what() << std::endl;
	});
	return (0);
}