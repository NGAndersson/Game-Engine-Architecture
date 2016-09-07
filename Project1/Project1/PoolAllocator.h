#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H
#include <stdio.h>
#include <string.h>
#include "Allocator.h"

using namespace std; 

class PoolAllocator : public Allocator
{
//Attributes
private:
	void* _memoryBlock;


public:


//Methods
private:


public:
	void setupPool(int size); //Gets chunk of memory and creates a linked list
	void remove(void* ptr); //Used for removing a block
	void* getSome(void); //Returns block of memory

};


#endif

