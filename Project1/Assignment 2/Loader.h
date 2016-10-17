#pragma once
#include <unordered_map>
#include <string>
#include <mutex>
#include "Decompressor.h"
#include "LOSReader.h"

class Loader{
public:
	Loader();
	void* Get(std::string guid);
	void Free(std::string guid);


private:
	std::string FindPathZip(std::string guid);
	void FindOffsetCustom(std::string guid, int& offset, int& size);
	std::unordered_map<std::string, char*> registry;
	int maxMemory;
	int usedMemory;
	std::mutex mtxLock;
	Decompressor decompressor;
	LOSReader losReader;
};
