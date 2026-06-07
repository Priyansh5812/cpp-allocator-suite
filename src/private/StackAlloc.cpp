#include "StackAlloc.h"

#include <iostream>
using namespace Stack_Allocator;

StackAlloc* StackAlloc:: _self;

void StackAlloc::Initialize(size_t bufferSize)
{	
	if (_self)
	{
		std::cout << "Buffer is already Initialized with "<< _self->bufferSize << " bytes" << std::endl;
		return;
	}


	_self = new StackAlloc();
	_self->buffer = malloc(bufferSize);
	_self->bufferSize = bufferSize;
	std::cout << "Buffer Initialized with " << _self->bufferSize << " bytes" << std::endl;
}

void StackAlloc::DeInitialize()
{
	if (!_self)
	{
		std::cout << "Allocator is not initialized" << std::endl;
		return;
	}
	
	free( _self->buffer);
	delete _self;
	_self = nullptr;
	std::cout << "Cleared" << std::endl;
}



void StackAlloc::Release()
{
	AllocationHeader* lastHeader = _self->GetLastHeader();

	if(!lastHeader)
		return;
	
	size_t bytesToReceed = lastHeader->AllocationSize + lastHeader->padding + sizeof(AllocationHeader);
	_self->allocatedBytes -= bytesToReceed;
	
}


AllocationHeader* StackAlloc::GetLastHeader()
{
	if (!_self || !_self->buffer)
	{
		std::cout << "Allocator is not initialized" << std::endl;
		return nullptr;
	}

	if(_self->allocatedBytes == 0)
		return nullptr;

	AllocationHeader* lastHeader;
	lastHeader = reinterpret_cast<AllocationHeader*>(static_cast<std::byte*>(_self->buffer) + _self->allocatedBytes - sizeof(AllocationHeader));
	return lastHeader;
}

#pragma region DEBUG

void StackAlloc::DebugAllocation(size_t padding , size_t allocationSize, size_t alignment)
{
	std::cout << "-------------Allocation-------------" << std::endl;
	std::cout << "Padding : " << padding << std::endl;
	std::cout << "Alignment : " << alignment << std::endl;
	std::cout << "Allocation Size : " << allocationSize << std::endl;
	std::cout << "Header Size : " << sizeof(AllocationHeader) << std::endl;
	std::cout << "Updated Allocated Bytes : " << _self->allocatedBytes << std::endl;
}

void StackAlloc::DebugRelease()
{
	
}

#pragma endregion