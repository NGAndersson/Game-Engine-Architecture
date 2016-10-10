#pragma once
#include <string>
#include <sstream>

class LOSReader{
public:
	LOSReader();
	std::istringstream read(std::string filePath, int byteOffset, int byteSize);
private:

};