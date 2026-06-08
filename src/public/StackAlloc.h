#pragma once
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace Stack_Allocator
{	
	typedef struct Stack_Allocator_Header
	{
		public:
			size_t AllocationSize;
			size_t padding;
			void(*Destructor)(void*);
			
	} AllocationHeader;


	class StackAlloc
	{
	public:
		static void Initialize(size_t bufferSize);
		static void DeInitialize();

		template<typename T>
		static void* Allocate(int count = 1)
		{	
			if (!_self || !_self->buffer)
			{
				std::cout << "Allocator is not initialized" << std::endl;
				return nullptr;
			}	

			size_t alignment = alignof(T);
			size_t bytes = sizeof(T) * count;

			std::byte* curr = static_cast<std::byte*>(_self->buffer) + _self->allocatedBytes;
			uintptr_t currMem = reinterpret_cast<uintptr_t>(curr);
			size_t padding = (alignment - (currMem % alignment)) % alignment;
			
			// Checking with final size (with padding)
			if(_self->allocatedBytes + bytes + sizeof(AllocationHeader) + padding > _self->bufferSize)
			{
				return nullptr;
			}
			
			void* userData = curr + padding;
			AllocationHeader* header = reinterpret_cast<AllocationHeader*>(static_cast<std::byte*>(userData)+bytes);
			header->AllocationSize = bytes;
			header->padding = padding;

			if(!std::is_trivially_destructible<T>())
			{
				header->Destructor = &DestroyObject<T>;
			}
			else
			{
				header->Destructor = nullptr;
			}

			_self->allocatedBytes += (bytes + padding + sizeof(AllocationHeader));
			_self->DebugAllocation(padding, bytes,alignment);
			return userData;
		}
		static void Release();

		template<typename T>
		static void DestroyObject(void* ptr)
		{
			static_cast<T*>(ptr)->~T();
		}

	public:
		StackAlloc(const StackAlloc&) = delete;
	private:
		StackAlloc() = default;
		~StackAlloc() = default;
		AllocationHeader* GetLastHeader();
		void DebugAllocation(size_t padding , size_t allocationSize, size_t alignment);
		void DebugRelease();

	private:
		static StackAlloc* _self;
		void* startPoint;
		void* lastAllocationHeader;
		size_t allocatedBytes = 0;
	public:
		void* buffer;
		size_t bufferSize;

	};
	


}

