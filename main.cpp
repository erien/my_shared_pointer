#include "tests.h"
#include <cstdlib>

int main()
{
	empty_constructor();

	nullptr_constructor();

	raw_pointer_constructor();

	count_references();

	comparison_operator();

	assignment_operator();
	
	dereference_operator();

	swap_pointers();
	
	custom_obj();

	custom_obj_deleter();

	custom_int_deleter();

	custom_empty_int_deleter();

	assign_custom_empty_int_deleter();
	
	custom_int_allocator();

	multitrhreaded_counter();

	//std_multitrhreaded_counter();

	system("PAUSE");
}
