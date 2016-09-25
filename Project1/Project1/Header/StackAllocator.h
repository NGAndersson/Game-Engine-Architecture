#pragma once
#include "Allocator.h"
#include "../Header/MemoryManager.h"
#include <stdint.h>

class StackAllocator {
public:
	typedef uint32_t Marker;
	explicit StackAllocator(uint32_t stackByteSize);
	~StackAllocator();
	void* Alloc(uint32_t byteSize);
	Marker GetMarker();
	void FreeToMarker(Marker marker);
	void ClearStack();

	MemoryManager memManager;

private:
	void* startPtr;
	void* topPtr;
	uint32_t totalStackSize;
	uint32_t usedMem;
};
