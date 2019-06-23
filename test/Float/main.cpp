#include <blc/float.hpp>
#include <iostream>
#include <iomanip>

int main()
{
	blc::math::Float test(2, 0);

	std::cout << std::fixed << std::setprecision(20);
	std::cout << test() << std::endl;
	for (double i = 0; i < 100; i += 1){
		blc::math::Float add(1);
		test = test + add;
		std::cout << "nb = " << test.getNb() << std::endl;
		std::cout << "E = " << test.getE() << std::endl;
		std::cout << "calculated = " << test() << std::endl;
	}
	return (0);
}