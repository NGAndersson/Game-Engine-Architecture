#pragma once
#include <unordered_map>
#include <string>

class Loader{
public:
	Loader();
	void* Get(std::string guid);


private:
	std::unordered_map<std::string, void*> registry;
	int maxMemory;
	int usedMemory;
};
