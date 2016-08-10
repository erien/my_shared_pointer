#ifndef TEST_H
#define TEST_H

#include "shared_ptr.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

struct TestObjBase
{
	TestObjBase()
	{
		// std::cout << "Test obj BASE constructor call." << std::endl;
	}

	virtual ~TestObjBase()
	{
		// std::cout << "Test obj BASE destructor call." << std::endl;
	}
};

struct TestObj : public TestObjBase
{
	TestObj() : name("test"), id(123)
	{
		// std::cout << "Test obj constructor call." << std::endl;
	}

	~TestObj()
	{
		// std::cout << "Test obj destructor call." << std::endl;
	}

	std::string name;
	int id;
};

template <class T>
struct TestDeleter
{
	void operator()(T* p) const 
	{
		// std::cout << "Custom deleter for int object." << std::endl;
		delete p;
	}
};

void thr(custom::shared_ptr<TestObj> p);

// print out success
void testPassed(std::string testName = "unnamed");

// print out failure
void testFailed(std::string testName = "unnamed");

// epmty pointer test
void empty_constructor();

// empty pointer test
void nullptr_constructor();

// raw pointer constructor test
void raw_pointer_constructor();

// multiple pointers to resource test
void count_references();

// comparison operator test
void comparison_operator();

// assignment test
void assignment_operator();

// dereference test
void dereference_operator();

// swap test
void swap_pointers();

// custom object test
void custom_obj();

// deleter of custom obj test
void custom_obj_deleter();

// deleter of int obj test
void custom_int_deleter();

void custom_empty_int_deleter();

void assign_custom_empty_int_deleter();

void custom_int_allocator();

void multitrhreaded_counter();

void std_multitrhreaded_counter();

#endif // !TEST_H
