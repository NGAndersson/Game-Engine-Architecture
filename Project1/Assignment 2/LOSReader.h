#pragma once
#include <string>
#include <sstream>

class LOSReader{
public:
	LOSReader();
	char* read(std::string filePath, int byteOffset, int byteSize);
private:

};