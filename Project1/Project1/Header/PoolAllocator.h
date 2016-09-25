#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H
#include <stdio.h>
#include <string.h>

using namespace std; 

class PoolAllocator
{
//Attributes
private:
	void* _memoryBlock;
	int _size;
	void* _nextBlock;

public:


//Methods
private:


public:
	PoolAllocator()
	{

	}
	void* setupPool(int size,int nrObj,void* memory); //Gets chunk of memory and creates a linked list
	inline void remove(void* ptr) {
		//make the emptyblock point to the next freeblock
		*((void**)ptr) = _nextBlock;

		//Make the nextblock point to the newly freed block
		_nextBlock = ptr;

	}; //Used for removing a block
	inline void* allocate(void) {
		if (_nextBlock == nullptr)
			return nullptr;
		// do nothing no more memoryspace

		void* retBlock = _nextBlock;

		_nextBlock = *((void**)_nextBlock); // fucking weird ass titts but i understand :)

		return retBlock;
	}; //Returns block of memory

};


#endif

