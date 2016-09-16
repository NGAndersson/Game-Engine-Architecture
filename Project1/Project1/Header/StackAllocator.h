#pragma once
#include "Allocator.h"

class StackAllocator {
public:
	typedef unsigned int Marker;
	StackAllocator();
	StackAllocator(unsigned int byteSize);
	~StackAllocator();
	void* Alloc(unsigned int byteSize);
	Marker GetMarker();
	void FreeToMarker();
	void ClearStack();

private:
	void* topPtr;
	void* botPtr;
};
