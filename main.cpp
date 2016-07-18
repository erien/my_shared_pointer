#include <iostream>
#include <memory>
#include "shared_ptr.h"

int main()
{
	int test = 123;

	std::shared_ptr<int> sp(new int());
	custom::shared_ptr<int> csp();

	std::shared_ptr<int> sp2(new int(123));
	custom::shared_ptr<int> csp2(new int(123));

	std::cout << "std::shared_ptr test: " << *sp2 << std::endl;
	std::cout << "custom::shared_ptr test:" << *csp2<< std::endl;
}
