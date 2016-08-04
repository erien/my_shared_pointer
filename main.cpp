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

	std::cout << "eot" << std::endl;
	
	system("PAUSE");
}
