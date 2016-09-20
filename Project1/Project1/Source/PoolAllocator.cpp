#include "../Header/PoolAllocator.h"

void PoolAllocator::setupPool(int size,int blocksize,void* memory)
{
	_memoryBlock = memory;
	_size = size;
	int nrObj = _size / blocksize;

	void* fesk = _memoryBlock;
	_nextBlock = fesk; 
	*((void**)fesk) = static_cast<void*>(static_cast<char*>(fesk) + blocksize);

	for (int i = 0; i < nrObj-1;i++)
	{
		fesk = static_cast<void*>(static_cast<char*>(fesk) + blocksize);//KAKAKAKAKAK fuling
		*((void**)fesk) = static_cast<void*>(static_cast<char*>(fesk) + blocksize);
	}
	fesk = nullptr; //Last pointer points to null

}

void PoolAllocator::remove(void* ptr)
{
	//make the emptyblock point to the next freeblock
	*((void**)ptr) = _nextBlock;

	//Make the nextblock point to the newly freed block
	_nextBlock = ptr;

}

void* PoolAllocator::allocate(void)
{
	if (_nextBlock == nullptr)
		return nullptr;
		// do nothing no more memoryspace
	
	void* retBlock = _nextBlock;

	_nextBlock = *((void**)_nextBlock); // fucking weird ass titts but i understand :)

	return retBlock;
}
