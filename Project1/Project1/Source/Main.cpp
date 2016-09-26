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

struct FirstInt
{
	int Hej = 1;
};

struct SecondInt
{
	int Hej = 2;
};

void* Threadfunc(PoolAllocator* _PAllocator, MemoryManager* _MManager)
{
	return _PAllocator->setupPool(sizeof(FirstInt) * 25000, sizeof(FirstInt), _MManager->GetMemory(sizeof(FirstInt) * 25000));
}

int main()
{
	srand(time(NULL));
	int i = 0, j = 64, k = 0;
	std::clock_t c_start, c_end, c_time, c_TotTime;

	MemoryManager* _MManager = new MemoryManager();
	PoolAllocator* _PAllocator1 = new PoolAllocator();
	PoolAllocator* _PAllocator2 = new PoolAllocator();
	//StackAllocator _SAllocator;*/


	if (MEMORY_OS == false && Scenario == 1 && LightTest == 1)
	{
		vector<Particle*> PartSys;
		int PartSize, ObjID;
		Particle* Party[50000];
		_PAllocator1->setupPool(sizeof(Particle) * 50000, sizeof(Particle), _MManager->GetMemory(sizeof(Particle) * 50000));
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		while (i < 50000)
		{
			Party[i] = new(_PAllocator1->allocate())Particle;
			i++;
		}
		
		for (i = 0; i < 25000; i++)	//Removes all the objects
		{
			_PAllocator1->remove(static_cast<void*>(Party[i + 25000]));
			_PAllocator1->remove(static_cast<void*>(Party[24999 - i]));
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
			i++;
		}
		i = 1;
		delete Party[25000];
		for (i = 0; i < 25000; i++)	//Removes all the objects
		{
			delete Party[i + 25000];
			delete Party[24999 - i];
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
	else if (MEMORY_OS == false && Scenario == 1 && LightTest == 0)
	{
		FirstInt* FirstValue[25000];
		SecondInt* SecondValue[25000];
		int Remove[10000];
		int ToDelete[10000];
		list<int> free;
		vector<int> used;
		std::thread first(Threadfunc, _PAllocator1, _MManager);
		std::thread second(Threadfunc,  _PAllocator2,  _MManager);
		first.join();
		second.join();
		c_time = std::clock();
		auto t_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 25000; i++)	// Add 50000 particle objects
		{
			FirstValue[i] = new(_PAllocator1->allocate())FirstInt;
			SecondValue[i] = new(_PAllocator2->allocate())SecondInt;
		}

		for (i = 0; i < 12500; i++)	//Removes all the objects
		{
			_PAllocator1->remove(static_cast<void*>(FirstValue[i + 12500]));
			_PAllocator1->remove(static_cast<void*>(FirstValue[12499 - i]));
			_PAllocator2->remove(static_cast<void*>(SecondValue[i + 12500]));
			_PAllocator2->remove(static_cast<void*>(SecondValue[12499 - i]));
		}

		for (i = 0; i < 25000; i++)	// Adds them again
		{
			FirstValue[i] = new(_PAllocator1->allocate())FirstInt;
			SecondValue[i] = new(_PAllocator2->allocate())SecondInt;
		}

		auto t_TotTime = std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime = std::clock() - c_time;		//stops time

		for (i = 0; i < 25000; i++)	//pushes used pointer indexes to a vector
		{
			used.push_back(i);
		}

		for (i = 0; i < 10000; i++)	//Randoms the objects that should be removed
		{
			Remove[i] = rand() % used.size();
			ToDelete[i] = used.at(Remove[i]);
			free.push_back(used.at(Remove[i]));
			used.erase(used.begin() + Remove[i]);
		}

		c_time = std::clock();		//restarts time
		t_time = std::chrono::high_resolution_clock::now();		//restarts time

		for (i = 0; i < 10000; i++)	//Removes the objects that should be removed
		{
			_PAllocator1->remove(static_cast<void*>(FirstValue[ToDelete[i]]));
			_PAllocator2->remove(static_cast<void*>(SecondValue[ToDelete[i]]));
		}

		t_TotTime += std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime += std::clock() - c_time;		//stops time

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * c_TotTime / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_TotTime).count()
			<< " ms\n";

		int FirstTot = 0, SecondTot = 0;
		for (i = 0; i < 15000; i++)
		{
			FirstTot += FirstValue[used.at(i)]->Hej;
			SecondTot += SecondValue[used.at(i)]->Hej;
		}
		std::cout << FirstTot << std::endl;
		std::cout << SecondTot << std::endl;
	}
	else if (MEMORY_OS == true && Scenario == 1 && LightTest == 0)
	{
		FirstInt* FirstValue[25000];
		SecondInt* SecondValue[25000];
		int Remove[10000];
		int ToDelete[10000];
		list<int> free;
		vector<int> used;
		
		c_time = std::clock();
		auto t_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 25000; i++)	// Add 50000 particle objects
		{
			FirstValue[i] = new FirstInt;
			SecondValue[i] = new SecondInt;
		}

		for (i = 0; i < 12500; i++)	//Removes all the objects
		{
			delete FirstValue[i + 12500];
			delete FirstValue[12499 - i];
			delete SecondValue[i + 12500];
			delete SecondValue[12499 - i];
		}

		for (i = 0; i < 25000; i++)	// Adds them again
		{
			FirstValue[i] = new FirstInt;
			SecondValue[i] = new SecondInt;
		}

		auto t_TotTime = std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime = std::clock() - c_time;		//stops time

		for (i = 0; i < 25000; i++)	//pushes used pointer indexes to a vector
		{
			used.push_back(i);
		}

		for (i = 0; i < 10000; i++)	//Randoms the objects that should be removed
		{
			Remove[i] = rand() % used.size();
			ToDelete[i] = used.at(Remove[i]);
			free.push_back(used.at(Remove[i]));
			used.erase(used.begin() + Remove[i]);
		}

		c_time = std::clock();		//restarts time
		t_time = std::chrono::high_resolution_clock::now();		//restarts time

		for (i = 0; i < 10000; i++)	//Removes the objects that should be removed
		{
			delete FirstValue[ToDelete[i]];
			delete SecondValue[ToDelete[i]];
		}

		t_TotTime += std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime += std::clock() - c_time;		//stops time


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