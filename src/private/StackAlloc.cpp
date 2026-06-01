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
	
	delete _self->buffer;
	delete _self;
	_self = nullptr;
	std::cout << "Cleared" << std::endl;
}

void* StackAlloc::Allocate(size_t bytes)
{		
	if(_self->allocatedBytes + bytes + sizeof(AllocationHeader) >= _self->bufferSize)
		return nullptr;
	
	void* res = static_cast<std::byte*>(_self->buffer) + _self->allocatedBytes;
	
	AllocationHeader* header = reinterpret_cast<AllocationHeader*>(static_cast<std::byte*>(res) + bytes);
	header->AllocationSize = bytes;

	_self->allocatedBytes += bytes + sizeof(AllocationHeader);
	return res;
}

void StackAlloc::Release()
{
	AllocationHeader* lastHeader = _self->GetLastHeader();

	if(!lastHeader)
		return;

	size_t bytesToReceed = lastHeader->AllocationSize;
	_self->allocatedBytes -= (sizeof(AllocationHeader) + bytesToReceed);
}


AllocationHeader* StackAlloc::GetLastHeader()
{
	if(_self->allocatedBytes == 0)
		return nullptr;

	AllocationHeader* lastHeader;
	lastHeader = reinterpret_cast<AllocationHeader*>(static_cast<std::byte*>(_self->buffer) + _self->allocatedBytes - sizeof(AllocationHeader));
	return lastHeader;
}