#include "../Header/StackAllocator.h"

StackAllocator::StackAllocator(void* memory,int sizeOfMemory) {
	startPtr = memory;
	totalStackSize = sizeOfMemory;
	topPtr = startPtr;
}

void* StackAllocator::Alloc(int byteSize) {
	// Check so we dont use more mem then size of stack.
	if (usedMem + byteSize > totalStackSize) {
		return nullptr;
	}

	usedMem += byteSize;
	void* retVal;
	retVal = topPtr;
	topPtr = static_cast<void*>(static_cast<char*>(topPtr) + byteSize);
	return retVal;
}

void StackAllocator::ClearStack() {
	//startPtr = nullptr;
	topPtr = startPtr;
	usedMem = 0;
}

