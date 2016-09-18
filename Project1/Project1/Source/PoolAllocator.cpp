#include "../Header/PoolAllocator.h"


void PoolAllocator::setupPool(int size,int nrObj,void* memory)
{
	_memoryBlock = memory;
	_size = size;

	void** fesk =(void**) _memoryBlock;
	_nextBlock = fesk; 
	for (int i = 0; i < nrObj-1;i++)
	{
		*fesk = reinterpret_cast<void*>(reinterpret_cast<int>(fesk) + size);//KAKAKAKAKAK fuling
		fesk = (void**) *fesk;
	}

	*fesk = nullptr; //Last pointer points to null

}

void PoolAllocator::remove(void* ptr)
{
	//make the emptyblock point to the next freeblock
	*((void**)ptr) = _nextBlock;

	//Make the nextblock point to the newly freed block
	_nextBlock = (void**)ptr;

}

void* PoolAllocator::allocate(void)
{
	if (_nextBlock == nullptr)
		return nullptr;
		// do nothing no more memoryspace
	
	void* retBlock = _nextBlock;

	_nextBlock = (void**)*_nextBlock; // fucking weird ass titts but i understand :)

	return retBlock;
}
