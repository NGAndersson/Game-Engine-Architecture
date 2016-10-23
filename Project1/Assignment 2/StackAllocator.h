#pragma once
#include <stdint.h>

typedef uint32_t Marker;
class StackAllocator {
public:
	StackAllocator(void* memory,int sizeOfMemory);
	StackAllocator();
	~StackAllocator();

	void* Alloc(int byteSize, bool lower);	// bool for lower or upper stack of the doubleedge
	void ClearStack(bool lower);
	void Setup(void* memory, int sizeOfMemory);
	void FreeToMarker(Marker marker, bool lower);
	Marker GetMarker(bool lower);

private:
	void* startPtr;
	void* endPtr;
	void* topOfLowerStack;
	void* topOfUpperStack;
	uint32_t totalStackSize;
	uint32_t usedMemLower;
	uint32_t usedMemUpper;
};
