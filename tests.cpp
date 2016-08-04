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
