#include <blc/blc.hpp>
#include <iostream>
#include <iomanip>

int main()
{
	blc::tools::promise<int> prom([](blc::tools::promise<int>::resolve resolve, blc::tools::promise<int>::reject reject){
	});

	return (1);
}