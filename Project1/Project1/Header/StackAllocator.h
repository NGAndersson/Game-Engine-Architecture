#pragma once
#include "Allocator.h"

struct Marker {

};

class StackAllocator {
public:
	StackAllocator();
	~StackAllocator();
	// GetMemory will be implemented on parent.
	
	Marker GetMarker();
	void FreeToMarker();
	void ClearStack();

private:
	void* topPtr;
	void* botPtr;
};
