#include "LOSReader.h"
#include <fstream>

LOSReader::LOSReader()
{
}

std::istringstream LOSReader::read(std::string filePath, int byteOffset, int size)
{
	std::string line;
	std::ifstream file;
	char* data;

	file.open(filePath);
	while (line != "HEADER END") //Reading until end of header (offset 0)
	{
		std::getline(file, line);
	}

	file.seekg(byteOffset, file.cur);	//Sets peeker at the correct byte, offseted from end of header
	file.get(data, size);				//reads size amount of characters

	return std::istringstream(data);
}
