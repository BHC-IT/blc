#include <blc/blc.hpp>
#include <iostream>
#include <iomanip>
#include <functional>


int main()
{
	blc::tools::promise<int> prom([](auto resolve, auto reject){
		// std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(5));
		resolve(1);
	});

	prom.then([](int e){
		std::cout << e << std::endl;
	}).catcher([](blc::error::exception e){
		std::cout << e.what() << std::endl;
	});
	std::cout << "ok" << std::endl;
	return (0);
}