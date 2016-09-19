#include "../Header/MemoryManager.h"

MemoryManager::MemoryManager()
{
	freeMemPtr = ::operator new(1000000);
}

MemoryManager::~MemoryManager()
{
}

void * MemoryManager::GetMemory(int size)
{
	if (size < sizeleft) {					//If the requested memory is bigger than available memory
		void* returnptr = freeMemPtr;		//set the current freememory-pointer as the return pointer
		freeMemPtr = static_cast<void*>(static_cast<char*>(freeMemPtr) + size);			//increment the freememory-pointer by the requested memory size so the requester can use all the memory without us giving it away again
		sizeleft -= size;
		return returnptr;					
	}
	else return nullptr;
}
