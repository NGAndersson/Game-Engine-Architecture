#pragma once
#include <mutex>
class MemoryManager {
public:
	static MemoryManager& instance()
	{
		static MemoryManager instance;
		return instance;
	}
	void* GetMemory(int size);
private:
	MemoryManager();
	std::mutex mtx;
	void* freeMemPtr;
	int sizeleft;

};