#ifndef TEST_H
#define TEST_H

#include "shared_ptr.h"
#include <iostream>
#include <string>

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

struct TestObjD 
{
	void operator()(TestObjBase* p) const 
	{
		// std::cout << "Custom deleter for TestObj object." << std::endl;
		delete p;
	}
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

template <class T>
class TestAllocator
{
public:

	typedef T value_type;

	TestAllocator(/*ctor args*/)
	{
		std::cout << "allocator constructor" << std::endl;
	}
	
	template <class U> 
	TestAllocator(const TestAllocator<U>& other)
	{
		std::cout << "allocator constructor" << std::endl;
	}
	
	T* allocate(std::size_t n)
	{
		T *p = new T();
		return p;
	}

	void construct(T* p, std::size_t n)
	{
	}

	void destroy(T* p)
	{
	}
	
	void deallocate(T* p, std::size_t n)
	{
		delete p;
	}

	template <class U>
	struct rebind
	{
		typedef TestAllocator<U> other;
	};
};

template <class T, class U>
bool operator==(const TestAllocator<T>&, const TestAllocator<U>&)
{
}

template <class T, class U>
bool operator!=(const TestAllocator<T>&, const TestAllocator<U>&)
{
}

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

#endif // !TEST_H
