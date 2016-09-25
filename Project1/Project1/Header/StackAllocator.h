#pragma once
#include <stdint.h>

class StackAllocator {
public:
	explicit StackAllocator(void* memory,int sizeOfMemory);
	void* Alloc(int byteSize);
	void ClearStack();

private:
	void* startPtr;
	void* topPtr;
	uint32_t totalStackSize;
	uint32_t usedMem;
};
