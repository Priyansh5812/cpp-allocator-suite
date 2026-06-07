#include "StackAlloc.h"
#include <iostream>
using namespace Stack_Allocator;

int main()
{	
	StackAlloc::Initialize(256);

	int* ptr = static_cast<int*>(StackAlloc::Allocate<int>());
	*ptr = 40;

	std::cout << *ptr << std::endl;
	StackAlloc::Release();	
	StackAlloc::DeInitialize();
	return 0;
}
