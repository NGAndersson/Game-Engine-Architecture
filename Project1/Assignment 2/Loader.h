#pragma once
#include <unordered_map>
#include <string>
#include <mutex>
#include "Decompressor.h"
#include "LOSReader.h"

struct RegistryEntry
{
	char* data;
	int size = 0;
	int referenceCount = 0;
	bool pinned = false;
};

class Loader{
public:
	static Loader& instance() {
		static Loader *instance = new Loader(); return *instance;
	}
	void* Get(std::string guid);
	void Free(std::string guid);
	void Pin(std::string guid);
	void Unpin(std::string guid);

private:
	Loader();
	void Free();
	std::string FindPathZip(std::string guid);
	void FindOffsetCustom(std::string guid, int& offset, int& size);
	std::unordered_map<std::string, RegistryEntry> registry;
	int maxMemory;
	int usedMemory;
	std::mutex mtxLock;
	Decompressor decompressor;
	LOSReader losReader;
};
