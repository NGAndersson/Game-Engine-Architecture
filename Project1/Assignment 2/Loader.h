#pragma once
#include <unordered_map>
#include <string>
#include <mutex>

class Loader{
public:
	Loader();
	void* Get(std::string guid);


private:
	std::string FindPathZip(std::string guid);
	std::string FindPathCustom(std::string guid);
	std::unordered_map<std::string, void*> registry;
	int maxMemory;
	int usedMemory;
	std::mutex mtxLock;
};
