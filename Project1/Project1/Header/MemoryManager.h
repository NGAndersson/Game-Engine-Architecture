#pragma once
#include <mutex>
class MemoryManager {
public:
	MemoryManager();
	~MemoryManager();
	void* GetMemory(int size);
private:
	std::mutex mtx;
	void* freeMemPtr;
	int sizeleft;

};