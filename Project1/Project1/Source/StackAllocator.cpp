#include "../Header/StackAllocator.h"

StackAllocator::StackAllocator(uint32_t stackByteSize) {
	startPtr = nullptr;
	endPtr = nullptr;
	totalStackSize = stackByteSize;

	startPtr = ::operator new(stackByteSize);
	endPtr = startPtr;
	currentTop = (Marker)startPtr;
}

StackAllocator::~StackAllocator() {

}

void* StackAllocator::Alloc(uint32_t byteSize) {
	currentTop += byteSize;
};

void StackAllocator::ClearStack() {
	startPtr = nullptr;
	endPtr = nullptr;
	currentTop = (Marker)startPtr;
};

void StackAllocator::FreeToMarker(){

};

StackAllocator::Marker StackAllocator::GetMarker(){
	return currentTop;
};
