#pragma once

class MemoryManager {
public:
	MemoryManager();
	~MemoryManager();
	void* GetMemory(int size);
private:
	void* freeMemPtr;
	int sizeleft;

};