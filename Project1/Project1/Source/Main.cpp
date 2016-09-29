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
#define LightTest 1
#define TestSize 20000
#define RemoveSize 1000

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

void ThreadfuncStack(StackAllocator* _SAllocator, MemoryManager* _MManager)
{
	_SAllocator->Setup(_MManager->GetMemory(sizeof(FirstInt) * 25000), sizeof(FirstInt) * 25000);
}

int main()
{
	srand(time(NULL));
	int i = 0, j = 64, k = 0;
	std::clock_t c_start, c_end, c_time, c_TotTime;

	MemoryManager* _MManager = new MemoryManager();
	PoolAllocator* _PAllocator1 = new PoolAllocator();
	PoolAllocator* _PAllocator2 = new PoolAllocator();
	StackAllocator* _SAllocator1 = new StackAllocator();
	StackAllocator* _SAllocator2 = new StackAllocator();


	if (MEMORY_OS == false && Scenario == 1 && LightTest == 1)
	{
		Particle* Party[TestSize];
		_PAllocator1->setupPool(sizeof(Particle) * TestSize, sizeof(Particle), _MManager->GetMemory(sizeof(Particle) * TestSize));
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		while (i < TestSize)
		{
			Party[i] = new(_PAllocator1->allocate())Particle;
			i++;
		}
		
		for (i = 0; i < (TestSize / 2); i++)	//Removes all the objects
		{
			_PAllocator1->remove(static_cast<void*>(Party[i + (TestSize / 2)]));
			_PAllocator1->remove(static_cast<void*>(Party[(TestSize / 2) - 1 - i]));
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
		FirstInt* FirstValue[TestSize];
		SecondInt *SecondValue[TestSize];
		std::thread first(ThreadfuncStack, _SAllocator1, _MManager);
		std::thread second(ThreadfuncStack, _SAllocator2, _MManager);
		first.join();
		second.join();
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < TestSize; i++)
		{
			FirstValue[i] = new(_SAllocator1->Alloc(sizeof(FirstInt)))FirstInt;
			SecondValue[i] = new(_SAllocator2->Alloc(sizeof(SecondInt)))SecondInt;
		}
		_SAllocator1->ClearStack();
		_SAllocator2->ClearStack();
		c_end = std::clock();
		auto t_end = std::chrono::high_resolution_clock::now();

		std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
			<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
			<< "Wall clock time passed: "
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";

		int FirstTot = 0, SecondTot = 0;
		for (int i = 0; i < TestSize; i++)
		{
			FirstTot += FirstValue[i]->Hej;
			SecondTot += SecondValue[i]->Hej;
		}

		if (FirstTot == TestSize && SecondTot == TestSize * 2)
		{
			std::cout << "All is fine in my dreams :p" << std::endl;
		}
		else
		{
			std::cout << "Error in memory" << std::endl;
		}
	}
	else if (MEMORY_OS == true && Scenario == 1 && LightTest == 1)
	{
		Particle* Party[TestSize];
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		
		while (i < TestSize)
		{
			Party[i] = new Particle;
			i++;
		}

		for (i = 0; i < (TestSize / 2); i++)	//Removes all the objects
		{
			delete Party[i + (TestSize / 2)];
			delete Party[(TestSize / 2) - 1 - i];
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
		FirstInt* FirstValue[TestSize];
		//SecondInt *SecondValue[TestSize];
		c_start = std::clock();
		auto t_start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < TestSize; i++)
		{
			FirstValue[i] = new FirstInt;
			//SecondValue[i] = new SecondInt;
		}
		for (int i = TestSize-1; i > -1; i--)
		{
			delete FirstValue[i];
			//delete SecondValue[i];
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
		FirstInt* FirstValue[TestSize];
		SecondInt* SecondValue[TestSize];
		int Remove[1000];
		int ToDelete[1000];
		list<int> free;
		vector<int> used;
		std::thread first(Threadfunc, _PAllocator1, _MManager);
		std::thread second(Threadfunc,  _PAllocator2,  _MManager);
		first.join();
		second.join();
		c_time = std::clock();
		auto t_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < TestSize; i++)	// Add 50000 particle objects
		{
			FirstValue[i] = new(_PAllocator1->allocate())FirstInt;
			SecondValue[i] = new(_PAllocator2->allocate())SecondInt;
		}

		for (i = 0; i < (TestSize / 2); i++)	//Removes all the objects
		{
			_PAllocator1->remove(static_cast<void*>(FirstValue[i + (TestSize / 2)]));
			_PAllocator1->remove(static_cast<void*>(FirstValue[(TestSize / 2) - 1 - i]));
			_PAllocator2->remove(static_cast<void*>(SecondValue[i + (TestSize / 2)]));
			_PAllocator2->remove(static_cast<void*>(SecondValue[(TestSize / 2) - 1 - i]));
		}

		for (i = 0; i < TestSize; i++)	// Adds them again
		{
			FirstValue[i] = new(_PAllocator1->allocate())FirstInt;
			SecondValue[i] = new(_PAllocator2->allocate())SecondInt;
		}

		auto t_TotTime = std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime = std::clock() - c_time;		//stops time

		for (i = 0; i < TestSize; i++)	//pushes used pointer indexes to a vector
		{
			used.push_back(i);
		}

		for (i = 0; i < RemoveSize; i++)	//Randoms the objects that should be removed
		{
			Remove[i] = rand() % used.size();
			ToDelete[i] = used.at(Remove[i]);
			free.push_back(used.at(Remove[i]));
			used.erase(used.begin() + Remove[i]);
		}

		c_time = std::clock();		//restarts time
		t_time = std::chrono::high_resolution_clock::now();		//restarts time

		for (i = 0; i < RemoveSize; i++)	//Removes the objects that should be removed
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
		for (i = 0; i < TestSize - RemoveSize; i++)
		{
			FirstTot += FirstValue[used.at(i)]->Hej;
			SecondTot += SecondValue[used.at(i)]->Hej;
		}
		if (FirstTot == (TestSize - RemoveSize) && SecondTot == (TestSize - RemoveSize) * 2)
		{
			std::cout << "All is fine in my dreams :p" << std::endl;
		}
		else
		{
			std::cout << "Error in memory" << std::endl;
		}
		
	}
	else if (MEMORY_OS == true && Scenario == 1 && LightTest == 0)
	{
		FirstInt* FirstValue[TestSize];
		SecondInt* SecondValue[TestSize];
		int Remove[1000];
		int ToDelete[1000];
		list<int> free;
		vector<int> used;
		
		c_time = std::clock();
		auto t_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < TestSize; i++)	// Add 50000 particle objects
		{
			FirstValue[i] = new FirstInt;
			SecondValue[i] = new SecondInt;
		}

		for (i = 0; i < (TestSize / 2); i++)	//Removes all the objects
		{
			delete FirstValue[i + (TestSize / 2)];
			delete FirstValue[(TestSize / 2) - 1 - i];
			delete SecondValue[i + (TestSize / 2)];
			delete SecondValue[(TestSize / 2) - 1 - i];
		}

		for (i = 0; i < TestSize; i++)	// Adds them again
		{
			FirstValue[i] = new FirstInt;
			SecondValue[i] = new SecondInt;
		}

		auto t_TotTime = std::chrono::high_resolution_clock::now() - t_time;		//stops time
		c_TotTime = std::clock() - c_time;		//stops time

		for (i = 0; i < TestSize; i++)	//pushes used pointer indexes to a vector
		{
			used.push_back(i);
		}

		for (i = 0; i < RemoveSize; i++)	//Randoms the objects that should be removed
		{
			Remove[i] = rand() % used.size();
			ToDelete[i] = used.at(Remove[i]);
			free.push_back(used.at(Remove[i]));
			used.erase(used.begin() + Remove[i]);
		}

		c_time = std::clock();		//restarts time
		t_time = std::chrono::high_resolution_clock::now();		//restarts time

		for (i = 0; i < RemoveSize; i++)	//Removes the objects that should be removed
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

	getchar();

	return 0;
}