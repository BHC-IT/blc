#include <blc/blc.hpp>
#include <iostream>
#include <iomanip>
#include <any>
#include <functional>
#include <fstream>
#include <limits>

double round(double n, double pas)
{
	if (n < 0 || pas < 0)
		throw blc::error::exception("negative");
	if (n > std::numeric_limits<int>::max() || pas > std::numeric_limits<int>::max())
		throw blc::error::exception("int overflow");

	double inf = int(n);
	double sup = inf + pas;

	while (n > sup){
		inf = sup;
		sup += pas;
	}
	if (n - inf > sup - n)
		return sup;
	return inf;
}

double round(double n)
{
	if (n < 0)
		throw blc::error::exception("negative");
	if (n > std::numeric_limits<int>::max())
		throw blc::error::exception("int overflow");
	if (n < 3){
		double inf = int(n);
		double sup = inf + 0.5;

		if (n > sup){
			inf = sup;
			sup += 0.5;
		}

		if (n - inf > sup - n)
			return sup;
		return inf;

	} else if (n > 3) {
		int inf = n;
		int sup = inf + 1;

		if (double(n - inf) > double(sup - n))
			return (sup);
		return (inf);
	}
	return n;
}

void test_promise()
{
	blc::tools::promise<int> prom([](resolver<int> resolve, rejecter reject){
		resolve(1);
	});

	prom.then([](int e){
		std::cout << e << std::endl;
	}).catcher([](blc::error::exception e){
		std::cout << e.what() << std::endl;
	});
}

void test_round(double test, double pas, double expected)
{
	double res = 0;

	try {
		res = round(test, pas);
	} catch (blc::error::exception &e) {
		std::cout << "test = " << test << ", round(test) = " << e.what();
		if (expected < 0){
			std::cout << ", expected = " << "error" << std::endl;
			std::cout << "ok" << std::endl << std::endl << std::endl;
		} else {
			std::cout << ", expected = " << expected << std::endl;
			std::cout << "ko" << std::endl << std::endl << std::endl;
		}
		return;
	}
	std::cout << "test = " << test << ", round(test) = " << res << ", expected = " << expected << std::endl;
	std::cout << (res == expected ? "ok" : "ko") << std::endl << std::endl << std::endl;
}

void start_test()
{
	std::ifstream file;

	file.open("../test.txt", std::ifstream::in);

	if (!file.is_open())
		throw blc::error::exception("error opening file");
	double test, pas, expected = 0;

	file >> test >> pas >> expected;

	test_round(test, pas, expected);
	while (file.good()){
		file >> test >> pas >> expected;
		test_round(test, pas, expected);
	}
}

namespace test {
	template <typename T>
	class testConst : public blc::concept::constraint<blc::concept::operable<T>> {
	public:
		testConst() : blc::concept::constraint<blc::concept::operable<T>>(){}
	private:
	};

	template <typename T>
	class testWithout {
	public:
		void add(){
			ok + ok;
		}
	private:
		T ok;
	};

	class dummy {
	public:
	private:
	};
}

int main()
{
	test::testWithout<int> ok;
	for (int i = 0; i < 1000000000; i++){
		ok = test::testWithout<int>();
	}
	// test::testConst<test::dummy> ko;
	// ko.testConstraint();
	// test::testWithout<test::dummy> ko;
	// ko.add();
	// test_round(1, 1);
	// test_round(1.22, 1);
	// test_round(1.66, 1.5);
	// test_round(1.88, 2);
	// test_round(3, 3);
	// test_round(3.1, 3);
	// test_round(3.6, 4);

	return (0);
}