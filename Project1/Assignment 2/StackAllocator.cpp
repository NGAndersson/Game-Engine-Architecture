#include "StackAllocator.h"

StackAllocator::StackAllocator(void* memory,int sizeOfMemory) {
	startPtr = memory;
	totalStackSize = sizeOfMemory;
	topOfLowerStack = startPtr;
	endPtr = static_cast<void*>(static_cast<char*>(startPtr) + sizeOfMemory);
	topOfUpperStack = endPtr;
}

StackAllocator::StackAllocator() {};
StackAllocator::~StackAllocator() {
	startPtr = nullptr;
	endPtr = nullptr;
	topOfLowerStack = nullptr;
	topOfUpperStack = nullptr;
};

void StackAllocator::Setup(void* memory, int sizeOfMemory) {
	totalStackSize = sizeOfMemory;
	startPtr = memory;
	topOfLowerStack = startPtr;
	endPtr = static_cast<void*>(static_cast<char*>(startPtr) + sizeOfMemory);
	topOfUpperStack = endPtr;
}

void* StackAllocator::Alloc(int byteSize, bool lower) {
	// Check so we dont use more mem then size of stack.
	if (usedMemLower + usedMemUpper + byteSize > totalStackSize) {
		return nullptr;
	}

	if (lower) {
		usedMemLower += byteSize;
		void* retVal;
		retVal = topOfLowerStack;
		topOfLowerStack = static_cast<void*>(static_cast<char*>(topOfLowerStack) + byteSize);
		return retVal;
	}
	if (!lower) {
		usedMemUpper += byteSize;
		void* retVal;
		retVal = topOfUpperStack;
		topOfUpperStack = static_cast<void*>(static_cast<char*>(topOfUpperStack) - byteSize);
		return retVal;
	}

	return nullptr;
}

void StackAllocator::ClearStack(bool lower) {
	if (lower) {
		topOfLowerStack = startPtr;
		usedMemLower = 0;
	}
	if (!lower) {
		topOfUpperStack = endPtr;
		usedMemUpper = 0;
	}
}

void StackAllocator::FreeToMarker(Marker marker, bool lower) {
	if (lower) {
		topOfLowerStack = (void*)marker;
	}
	if (!lower) {
		topOfUpperStack = (void*)marker;
	}
};

Marker StackAllocator::GetMarker(bool lower) {
	if (lower) {
		return (Marker)topOfLowerStack;
	}
	if (!lower) {
		return (Marker)topOfUpperStack;
	}
	Marker marker = 0;
	return marker;
}
