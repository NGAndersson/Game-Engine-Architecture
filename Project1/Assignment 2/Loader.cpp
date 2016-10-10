#include "Loader.h"
#include <mutex>
#include <fstream>
#include <iostream>

Loader::Loader()
{
	maxMemory = 1000000;
	usedMemory = 0;
}

void * Loader::Get(std::string guid)
{
	void* retPtr = nullptr;

	mtxLock.lock();
	if (registry.find(guid) != registry.end())	//guid already exists in registry
	{
		if (registry[guid] != nullptr)	//Already being worked on by another thread and will be inserted soon
			return nullptr;
		else
			return registry[guid];		//Asset already exists in registry and has a proper pointer. Return the address
	}
	else	//Guid is not yet in registry
	{	//Find out if there's such a guid in our packages
		std::string filePath;
		if (guid.substr(0, 3) == "los")			//Asset is in our .los custom package
			filePath = FindPathCustom(guid);
		else									//Asset is in a .zip package
			filePath = FindPathZip(guid);
		//Will crash deliberately if FindPath functions can't find the asset

		registry[guid] = nullptr;		//If the asset exists but hasn't been loaded set it as nullptr temporarily so other threads can see that it's being loaded
	}
	mtxLock.unlock();


	//If we've gotten this far, we can begin decompressing and processing the file

	//Send filepath to correct package handler here
	if (guid.substr(0, 3) == "zip")
		//zipper.decompress(filePath);
	//Check file-ending here
	//

	/*
	if(fileEnd == "obj")
	{
		registry[guid] = objLoader.load(file);
		usedMemory += sizeof(*registry[guid]);
	}
	else if(fileEnd == "mp3")
	{
		registry[guid] = soundManager.load(file);
		usedMemory += sizeof(*registry[guid]);
	}
	*/

	return retPtr;
}

std::string Loader::FindPathZip(std::string guid)
{
	bool found = false;
	std::string line;
	std::ifstream fileTable;
	fileTable.open("fileTable.txt");

	while (!fileTable.eof() && fileTable.is_open())
	{
		std::getline(fileTable, line, ' ');		//Look for guid in table
		if (line == guid)						//If found
		{
			std::getline(fileTable, line);		//Get filepath of guid
			fileTable.close();
			found = true;
		}
		else std::getline(fileTable, line);		//go to next line
	}

	if (!found)		//File not found in lookup table
	{
		std::cout << guid << " is not a valid GUID. No such file found in fileTable.txt" << std::endl;
		getchar();
		exit(0);		//Exit program because of stupid
	}
	return line;
}

std::string Loader::FindPathCustom(std::string guid)
{
	bool found = false;
	std::string line;

	if (!found)		//File not found in lookup table
	{
		std::cout << guid << " is not a valid GUID. No such file found in fileTable.txt" << std::endl;
		getchar();
		exit(0);		//Exit program because of stupid
	}

	return line;
}
