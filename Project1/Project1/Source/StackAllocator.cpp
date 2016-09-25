#include "../Header/StackAllocator.h"
#include "../Header/MemoryManager.h"

StackAllocator::StackAllocator(uint32_t stackByteSize) {
	startPtr = nullptr;
	topPtr = nullptr;
	totalStackSize = stackByteSize;
	startPtr = memManager.GetMemory(stackByteSize);
	topPtr = startPtr;
}

StackAllocator::~StackAllocator() {
	// memManager remove mem
	startPtr = nullptr;
	topPtr = nullptr;
}

void* StackAllocator::Alloc(uint32_t byteSize) {
	// Check so we dont use more mem then size of stack.
	if (usedMem + byteSize > totalStackSize) {
		return nullptr;
	}
	topPtr = static_cast<void*>(static_cast<char*>(topPtr) + byteSize);
	return topPtr;
};

void StackAllocator::ClearStack() {
	//startPtr = nullptr;
	topPtr = startPtr;
};

void StackAllocator::FreeToMarker(Marker marker){
	topPtr = (void*)marker;
};

StackAllocator::Marker StackAllocator::GetMarker(){
	return (Marker)topPtr;
};
