#include "tests.h"
#include <cstdlib>
#include <vector>

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
	
	//custom_int_allocator();

	system("PAUSE");
}
