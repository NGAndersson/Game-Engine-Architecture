#include "LOSReader.h"
#include <fstream>
#include <iostream>
LOSReader::LOSReader()
{
}

std::istringstream LOSReader::read(std::string filePath, int byteOffset, int size)
{
	std::string line;
	std::ifstream file;
	char* data = new char[size + 1];

	file.open(filePath, std::ios::binary);
	while (line != "HEADER END") //Reading until end of header (offset 0)
	{
		std::getline(file, line);
	}

	file.seekg(byteOffset, file.cur);	//Sets peeker at the correct byte, offseted from end of header
	file.read(data, size);				//reads size amount of characters
	data[size] = '\0';
	std::cout << data;
	return std::istringstream(data);
}
