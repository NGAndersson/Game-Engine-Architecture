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
#include <list>

#define MEMORY_OS false
#define Scenario 1
#define LightTest 0

struct Particle{
	int x = 1;
	int y = 1;
	int z = 1;
	int TimeToLive = 1;
};

void Threadfunc(int* ToDelete, Particle* Party, PoolAllocator* _PAllocator)
{
	_PAllocator->remove(static_cast<void*>(Party[ToDelete[i]]));
}

int main()
{
	srand(time(NULL));
	int i = 0, j = 64, k = 0;
	std::clock_t c_start, c_end, c_time, c_TotTime;

	MemoryManager* _MManager = new MemoryManager();
	PoolAllocator* _PAllocator = new PoolAllocator();
	//StackAllocator _SAllocator;*/


	if (MEMORY_OS == false && Scenario == 1 && LightTest == 1)
	{
		vector<Particle*> PartSys;
		int PartSize, ObjID;
		Particle* Party[50000];
		_PAllocator->setupPool(sizeof(Particle) * 50000, sizeof(Particle), _MManager->GetMemory(sizeof(Particle) * 50000));
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		while (i < 50000)
		{
			Party[i] = new(_PAllocator->allocate())Particle;
			//PartSys.push_back(new(_PAllocator->allocate())Particle);
			i++;
		}
		i = 1;
		//_PAllocator->remove(static_cast<void*>(Party[2500]));
		for (i = 0; i < 25000; i++)	//Removes all the objects
		{
			_PAllocator->remove(static_cast<void*>(Party[i + 25000]));
			_PAllocator->remove(static_cast<void*>(Party[24999 - i]));
		}

		/*while (i < 10000)
		{
			k = 0;
			while (k < 100)
			{
				PartSize = PartSys.size();
				ObjID = rand() % PartSize;
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
		}*/
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
	else if (MEMORY_OS == true && Scenario == 1 && LightTest == 1)
	{
		vector<Particle*> PartSys;
		Particle* Party[50000];
		int PartSize, ObjID;
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		
		while (i < 50000)
		{
			Party[i] = new Particle;
			//PartSys.push_back( new Particle);
			i++;
		}
		i = 1;
		delete Party[25000];
		for (i = 0; i < 25000; i++)	//Removes all the objects
		{
			delete Party[i + 25000];
			delete Party[24999 - i];
		}
		//while (i < 10000)
		//{
		//	k = 0;
		//	while (k < 100)
		//	{
		//		/*PartSize = PartSys.size();
		//		ObjID = rand() % PartSize;
		//		delete PartSys[ObjID];
		//		PartSys.erase(PartSys.begin() + ObjID);	*/
		//		k++;
		//	}
		//	k = 0;
		//	while (k < 100)
		//	{
		//		PartSys.push_back(new Particle);
		//		k++;
		//	}
		//	i++;
		//}

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
	else if (MEMORY_OS == false && Scenario == 1 && LightTest == 0)
	{
		Particle* Party[50000];
		int Remove[10000];
		int ToDelete[10000];
		list<int> free;
		vector<int> used;
		_PAllocator->setupPool(sizeof(Particle) * 50000, sizeof(Particle), _MManager->GetMemory(sizeof(Particle) * 50000));
		c_time = std::clock();
		auto t_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 50000; i++)	// Add 50000 particle objects
		{
			Party[i] = new(_PAllocator->allocate())Particle;
		}

		//_PAllocator->remove(static_cast<void*>(Party[2500]));
		for (i = 0; i < 25000; i++)	//Removes all the objects
		{
			_PAllocator->remove(static_cast<void*>(Party[i + 25000]));
			_PAllocator->remove(static_cast<void*>(Party[24999 - i]));
		}

		for (i = 0; i < 50000; i++)	// Adds them again
		{
			Party[i] = new(_PAllocator->allocate())Particle;
		}

		auto t_TotTime = std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime = std::clock() - c_time;		//stops time

		for (i = 0; i < 50000; i++)	//pushes used pointer indexes to a vector
		{
			used.push_back(i);
		}

		for (i = 0; i < 10000; i++)	//Randoms the objects that should be removed
		{
			Remove[i] = rand() % used.size();
			ToDelete[i] = used.at(Remove[i]);
			used.erase(used.begin() + Remove[i]);
		}

		c_time = std::clock();		//restarts time
		t_time = std::chrono::high_resolution_clock::now();		//restarts time

		std::thread first(Threadfunc, ToDelete, Party);
		//for (i = 0; i < 10000; i++)	//Removes the objects that should be removed
		//{
		//	_PAllocator->remove(static_cast<void*>(Party[ToDelete[i]]));
		//}

		t_TotTime += std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime += std::clock() - c_time;		//stops time

		for (i = 0; i < 10000; i++)	
		{
			free.push_back(used.at(Remove[i]));
		}

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * c_TotTime / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_TotTime).count()
			<< " ms\n";
	}
	else if (MEMORY_OS == true && Scenario == 1 && LightTest == 0)
	{
		Particle* Party[50000];
		int Remove[10000];
		int ToDelete[10000];
		list<int> free;
		vector<int> used;
		
		c_time = std::clock();
		auto t_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 50000; i++)	// Add 50000 particle objects
		{
			Party[i] = new Particle;
		}

		for (i = 0; i < 25000; i++)	//Removes all the objects
		{
			delete Party[i + 25000];
			delete Party[24999 - i];
		}

		for (i = 0; i < 50000; i++)	// Adds them again
		{
			Party[i] = new Particle;
		}

		auto t_TotTime = std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime = std::clock() - c_time;		//stops time

		for (i = 0; i < 50000; i++)	//pushes used pointer indexes to a vector
		{
			used.push_back(i);
		}

		for (i = 0; i < 10000; i++)	//Randoms the objects that should be removed
		{
			Remove[i] = rand() % used.size();
			ToDelete[i] = used.at(Remove[i]);
			used.erase(used.begin() + Remove[i]);
		}

		c_time = std::clock();		//restarts time
		t_time = std::chrono::high_resolution_clock::now();		//restarts time

		for (i = 0; i < 10000; i++)	//Removes the objects that should be removed
		{
			delete Party[ToDelete[i]];
		}

		t_TotTime += std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime += std::clock() - c_time;		//stops time

		for (i = 0; i < 10000; i++)
		{
			free.push_back(used.at(Remove[i]));
		}


		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * (c_TotTime) / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_TotTime).count()
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