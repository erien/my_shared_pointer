#include "tests.h"

void testPassed(std::string testName)
{
	std::cout << "[PASSED] Test " + testName << std::endl;
}

void testFailed(std::string testName)
{
	std::cout << "[FAILED] Test " + testName << std::endl;
}

void empty_constructor()
{
	std::string testName = "empty constructor";
	custom::shared_ptr<int> csp;

	if (!csp && csp.use_count() == 0)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void nullptr_constructor()
{
	std::string testName = "nullptr contructor";
	custom::shared_ptr<int> csp(nullptr);

	if (!csp && csp.use_count() == 0)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void raw_pointer_constructor()
{
	std::string testName = "raw pointer constructor";
	int *raw = new int(123);
	custom::shared_ptr<int> csp1(raw);
	//custom::shared_ptr<int> csp2(raw); // evil - undefined behaviour on destruction!

	if (csp1 && csp1.use_count() == 1)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void count_references()
{
	std::string testName = "count references";
	custom::shared_ptr<int> csp1(new int(123));
	custom::shared_ptr<int> csp2(csp1);

	if (csp1 && csp2 && csp1.use_count() == 2 && csp2.use_count() == 2)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void comparison_operator()
{
	std::string testName = "comparison operator";
	custom::shared_ptr<int> csp1(new int(123));
	custom::shared_ptr<int> csp2(csp1);

	if (csp1 && csp2 && csp1 == csp2)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void assignment_operator()
{
	std::string testName = "assignment operator";
	custom::shared_ptr<int> csp1(new int(123));
	custom::shared_ptr<int> csp2 = csp1;

	if (csp1 && csp2 && csp1 == csp2 && csp1.use_count() == 2 && csp2.use_count() == 2)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void dereference_operator()
{
	std::string testName = "dereference operator";
	custom::shared_ptr<int> csp1(new int(123));
	custom::shared_ptr<int> csp2 = csp1;

	if (csp1 && csp2 && *csp1 == 123 && *csp2 == 123)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void swap_pointers()
{
	std::string testName = "swap";
	custom::shared_ptr<int> csp1(new int(123));
	custom::shared_ptr<int> csp2(new int(456));

	csp2.swap(csp1);

	if (csp1 && csp2 && !(csp1 == csp2) && *csp1 == 456 && *csp2 == 123)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void custom_obj()
{
	std::string testName = "custom object constructor";
	custom::shared_ptr<TestObjBase> csp1(new TestObj);
	custom::shared_ptr<TestObjBase> csp2(csp1);

	if (csp1 && csp2 && csp1 == csp2)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void custom_obj_deleter()
{
	std::string testName = "custom obj constructor with deleter";
	custom::shared_ptr<TestObjBase> csp(new TestObj, TestObjD());
	if (csp && csp.use_count() == 1)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void custom_int_deleter()
{
	std::string testName = "custom int constructor with deleter";
	custom::shared_ptr<int> csp(new int, TestDeleter<int>());
	if (csp && csp.use_count() == 1)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void custom_empty_int_deleter()
{
	std::string testName = "custom empty int constructor with deleter";
	custom::shared_ptr<int> csp(nullptr, TestDeleter<int>());
	custom::shared_ptr<int> csp1(new int, TestDeleter<int>());
	if (!csp && csp.use_count() == 0)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void assign_custom_empty_int_deleter()
{
	std::string testName = "assign to custom empty int constructor with deleter";
	custom::shared_ptr<int> csp(nullptr, TestDeleter<int>());
	custom::shared_ptr<int> csp1(new int, TestDeleter<int>());
	csp = csp1;
	if (csp && csp1 && csp.use_count() == 2 && csp1.use_count() == 2)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void custom_int_allocator()
{
	std::string testName = "custom int constructor with deleter and allocator";
	custom::shared_ptr<TestObjBase> csp(new TestObjBase(), TestDeleter<TestObjBase>(), TestAllocator<TestObjBase>() );
	if (csp && csp.use_count() == 1)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}