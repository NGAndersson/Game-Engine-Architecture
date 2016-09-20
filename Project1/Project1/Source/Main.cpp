#include "../Header/MemoryManager.h"
#include "../Header/PoolAllocator.h"
#include "../Header/StackAllocator.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

#define MEMORY_OS false
#define Scenario 1

struct Particle{
	int x = 1;
	int y = 1;
	int z = 1;
	int TimeToLive = rand() / 1000;
};

int main()
{
	srand(time(NULL));
	int i = 0, j = 64, k = 0;
	std::clock_t c_start, c_end;

	MemoryManager* _MManager = new MemoryManager();
	PoolAllocator* _PAllocator = new PoolAllocator();
	//StackAllocator _SAllocator;*/


	if (MEMORY_OS == false && Scenario == 1)
	{
		_PAllocator->setupPool(sizeof(Particle) * 500, sizeof(Particle), _MManager->GetMemory(sizeof(Particle) * 500));
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		vector<Particle*> PartSys;
		while (i < 500)
		{
			PartSys.push_back(new(_PAllocator->allocate())Particle);
			i++;
		}

		while (i < 10000)
		{
			k = 0;
			while (k < 100)
			{
				int PartSize = PartSys.size();
				int ObjID = rand() % PartSize;
				_PAllocator->remove(static_cast<void*>(PartSys.at(ObjID)));
				PartSys.erase(PartSys.begin() + ObjID);
				k++;
			}
			k = 0;
			while (k < 100)
			{
				PartSys.push_back(new(_PAllocator->allocate())Particle);
				k++;
			}
			i++;
		}
		c_end = std::clock();
		auto t_end = std::chrono::high_resolution_clock::now();

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";
	}
	else if (MEMORY_OS == false && Scenario == 2)
	{
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		while (i < 500)
		{

			i++;
		}
		c_end = std::clock();
		auto t_end = std::chrono::high_resolution_clock::now();

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";
	}
	else if (MEMORY_OS == true && Scenario == 1)
	{
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		vector<Particle*> PartSys;
		
		while (i < 500)
		{
			PartSys.push_back( new Particle);
			i++;
		}
		
		while (i < 10000)
		{
			k = 0;
			while (k < 100)
			{
				int PartSize = PartSys.size();
				int ObjID = rand() % PartSize;
				PartSys.erase(PartSys.begin() + ObjID);	
				k++;
			}
			k = 0;
			while (k < 100)
			{
				PartSys.push_back(new Particle);
				k++;
			}
			i++;
		}

		c_end = std::clock();
		auto t_end = std::chrono::high_resolution_clock::now();

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";
	}
	else if (MEMORY_OS == true && Scenario == 2)
	{
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		while (i < 500)
		{

			i++;
		}
		c_end = std::clock();
		auto t_end = std::chrono::high_resolution_clock::now();

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";
	}

	//TESTCASE FOR POOLALLOCATOR DO NOT REMOVE
	//MemoryManager* test = new MemoryManager();

	//PoolAllocator* mtest = new PoolAllocator();

	//mtest->setupPool(256, 64, test->GetMemory(256));
	//void* testmem[4];
	//string* pt[4];
	//for (int i = 0; i < 4; i++)
	//	testmem[i] = mtest->allocate();

	//for (int i = 0; i < 4; i++)
	//{
	//	pt[i] = new(testmem[i])string("Hello World");
	//}

	//mtest->remove(static_cast<void*>(pt[0]));

	//string* tp = new(mtest->allocate())string("Oscar gillar Man");

	getchar();

	return 0;
}