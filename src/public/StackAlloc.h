#pragma once
namespace Stack_Allocator
{	

	typedef struct Stack_Allocator_Header AllocationHeader;


	class StackAlloc
	{

	public:
		static void Initialize(size_t bufferSize);
		static void DeInitialize();
		static void* Allocate(size_t bytes);
		static void Release();
	public:
		StackAlloc(const StackAlloc&) = delete;
	private:
		StackAlloc() = default;
		~StackAlloc() = default;
		AllocationHeader* GetLastHeader();

	private:
		static StackAlloc* _self;
		void* startPoint;
		void* lastAllocationHeader;
		size_t allocatedBytes;
	public:
		void* buffer;
		size_t bufferSize;

	};

	typedef struct Stack_Allocator_Header
	{
		public:
			size_t AllocationSize;

	} AllocationHeader;

}