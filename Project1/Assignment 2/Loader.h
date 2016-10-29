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
		static Loader instance;
		return instance;
	}

	Loader(Loader const&) = delete;
	void operator= (Loader const&) = delete;

	void* Get(std::string guid);
	void Free(std::string guid);
	void Pin(std::string guid);
	void Unpin(std::string guid);
	int GetSize(std::string guid);

private:
	Loader();
	void Free();
	std::string FindPathZip(std::string guid);
	void FindOffsetCustom(std::string guid, int& offset, int& size);
	std::unordered_map<std::string, RegistryEntry> registry;
	std::unordered_map<std::string, int> sizeRegistry;
	int maxMemory;
	int usedMemory;
	std::mutex loadLock;
	std::mutex freeLock;
	Decompressor decompressor;
	LOSReader losReader;
};
