#include "../Header/PoolAllocator.h"

void* PoolAllocator::setupPool(int size,int blocksize,void* memory)
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
	return _nextBlock;
}
