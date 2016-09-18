#pragma once
#include "Allocator.h"
#include <stdint.h>

class StackAllocator {
public:
	typedef uint32_t Marker;
	explicit StackAllocator(uint32_t stackByteSize);
	~StackAllocator();
	void* Alloc(uint32_t byteSize);
	Marker GetMarker();
	void FreeToMarker();
	void ClearStack();

private:
	void* startPtr;
	void* endPtr;
	Marker currentTop;
	uint32_t totalStackSize;
};
