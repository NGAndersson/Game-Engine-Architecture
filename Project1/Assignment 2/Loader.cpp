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

	if (registry.find(guid) != registry.end())	//If the resource does not already exist in the registry, load it
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
		
		mtxLock.lock();
		if (registry.find(guid) != registry.end())	//guid already exists in registry
		{
			if (registry[guid] != nullptr)	//Already being worked on by another thread and will be inserted soon
				return nullptr;
			else
				return registry[guid];		//Asset already exists in registry and has a proper pointer. Return the address.
		}
		else
			registry[guid] = nullptr;		//If the asset hasn't been loaded set it as nullptr temporarily so other threads can see that it's being loaded
		mtxLock.unlock();

		//If we've gotten this far, we can begin decompressing and processing the file

		//Send filepath to zip handler here
		//

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

	}
	return nullptr;
}
