#pragma once
#include <stdint.h>

class StackAllocator {
public:
	StackAllocator(void* memory,int sizeOfMemory);
	void* Alloc(int byteSize);
	void ClearStack();
	void Setup(void* memory, int sizeOfMemory);
	StackAllocator();

private:
	void* startPtr;
	void* topPtr;
	uint32_t totalStackSize;
	uint32_t usedMem;
};
