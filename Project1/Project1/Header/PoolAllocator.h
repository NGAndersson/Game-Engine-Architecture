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
	void setupPool(int size,int nrObj,void* memory); //Gets chunk of memory and creates a linked list
	void remove(void* ptr); //Used for removing a block
	void* allocate(void); //Returns block of memory

};


#endif

