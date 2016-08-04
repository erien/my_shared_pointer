#ifndef TEST_H
#define TEST_H

#include "shared_ptr.h"
#include <iostream>
#include <string>

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

#endif // !TEST_H