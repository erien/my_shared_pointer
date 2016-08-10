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
	custom::shared_ptr<TestObj> csp(new TestObj, TestDeleter<TestObj>());
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
	int *ptr = new int(123);
	std::allocator<int> alloc;
	std::default_delete<int> del;
	custom::shared_ptr<int> csp(ptr, del, alloc);
	if (csp && csp.use_count() == 1)
	{
		testPassed(testName);
	}
	else
	{
		testFailed(testName);
	}
}

void thr(custom::shared_ptr<TestObj> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	// should be thread-safe, even though the shared use_count is incremented:
	custom::shared_ptr<TestObj> lp = p; 
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:" << std::endl;
		std::cout << "lp.get() = " << lp.get() << std::endl;
		std::cout << "lp.use_count() = " << lp.use_count() << std::endl;
	}
}

void multitrhreaded_counter()
{
	std::string testName = "multithreaded use count";
	custom::shared_ptr<TestObj> sp(new TestObj());

	std::cout << "sp: " << std::endl;
	std::cout << "sp.get() = " << sp.get() << std::endl;
	std::cout << "sp.use_count() = " << sp.use_count() << std::endl;

	std::thread t1(thr, sp), t2(thr, sp), t3(thr, sp);
	sp.reset(); // release ownership from main

	std::cout << "Shared ownership between 3 threads and released ownership from main:" << std::endl;
	std::cout << "sp.get() = " << sp.get() << std::endl;
	std::cout << "sp.use_count() = " << sp.use_count() << std::endl;

	t1.join(); t2.join(); t3.join();
	std::cout << "All threads completed, the last one deleted TestObj" << std::endl;
}


void sthr(std::shared_ptr<TestObj> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	// should be thread-safe, even though the shared use_count is incremented:
	std::shared_ptr<TestObj> lp = p;
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:" << std::endl;
		std::cout << "lp.get() = " << lp.get() << std::endl;
		std::cout << "lp.use_count() = " << lp.use_count() << std::endl;
	}
}

void std_multitrhreaded_counter()
{

	std::shared_ptr<TestObj> sp(new TestObj());

	std::cout << "sp: " << std::endl;
	std::cout << "sp.get() = " << sp.get() << std::endl;
	std::cout << "sp.use_count() = " << sp.use_count() << std::endl;

	std::thread t1(sthr, sp), t2(sthr, sp), t3(sthr, sp);
	sp.reset(); // release ownership from main

	std::cout << "Shared ownership between 3 threads and released ownership from main:" << std::endl;
	std::cout << "sp.get() = " << sp.get() << std::endl;
	std::cout << "sp.use_count() = " << sp.use_count() << std::endl;

	t1.join(); t2.join(); t3.join();
	std::cout << "All threads completed, the last one deleted TestObj" << std::endl;
}