#include "StackAlloc.h"
#include <iostream>
using namespace Stack_Allocator;

class A
{
	public:
		int a;
		A(int v) : a(v)
		{
			std::cout << "Constructed" << std::endl;
		}
		~A()
		{
			a = 0;
		}
};



int main()
{	
	StackAlloc::Initialize(256);
	void* mem = StackAlloc::Allocate<A>();
	A* ptr = new(mem) A(5);
	std::cout << "Value = " << ptr->a << std::endl;
	StackAlloc::Release();
	std::cout << "Value = " << ptr->a << std::endl;
	StackAlloc::DeInitialize();
	return 0;
}
