#include <iostream>
#include <memory>
#include "shared_ptr.h"

int main()
{
	{
		int *test = new int(123);
		int *test2 = new int(456);

		// custom::shared_ptr

		// empty pointers
		custom::shared_ptr<int> csp0;
		custom::shared_ptr<int> csp1(nullptr);
		std::cout << "custom::shared_ptr0 use count test: " << (csp0.use_count() == 0) << std::endl;
		std::cout << "custom::shared_ptr1 use count test: " << (csp1.use_count()  == 0) << std::endl;

		// constructed from raw pointers
		custom::shared_ptr<int> csp2(new int(123));
		custom::shared_ptr<int> csp3(new int (456));
		std::cout << "custom::shared_ptr2 use count test: " << (csp2.use_count() == 1) << std::endl;
		std::cout << "custom::shared_ptr3 use count test: " << (csp3.use_count() == 1) << std::endl;

		// comparison
		std::cout << "csp2 == csp3 " << ((csp2 == csp3) == 0)<< std::endl;

		//dereference
		std::cout << "custom::shared_ptr2 deref: " << *csp2 << std::endl;
		std::cout << "custom::shared_ptr3 deref:" << *csp3 << std::endl;

		//swap
		csp2.swap(csp3);
		std::cout << "custom::shared_ptr2 deref after swap: " << *csp2 << std::endl;
		std::cout << "custom::shared_ptr3 deref after swap:" << *csp3 << std::endl;

		// std::shared_ptr
		std::shared_ptr<int> sp0;
		std::shared_ptr<int> sp1(nullptr);
		std::shared_ptr<int> sp2(test2);
		std::shared_ptr<int> sp3(sp2);

		std::cout << "std::shared_ptr0 use count: " << sp0.use_count() << std::endl;
		std::cout << "std::shared_ptr1 use count: " << sp1.use_count() << std::endl;
		std::cout << "std::shared_ptr2 use count: " << sp2.use_count() << std::endl;
		std::cout << "std::shared_ptr3 use count: " << sp3.use_count() << std::endl;
		std::cout << (sp2 == sp3) << std::endl;

		std::cout << "std::shared_ptr deref: " << *sp2 << std::endl;
		std::cout << "std::shared_ptr deref: " << *sp3 << std::endl;
	}
	

	system("PAUSE");
}
