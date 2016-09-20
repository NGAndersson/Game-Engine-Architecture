//#include "Allocator.h"
#include "../Header/MemoryManager.h"
#include "../Header/PoolAllocator.h"
//#include "StackAllocator.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

#define MEMORY_OS false

int main()
{
	int i = 0, j = 64;
	std::clock_t c_start, c_end;
	/*Allocator _Allocator;
	MemoryManager _MManager;
	PoolAllocator _PAllocator;
	StackAllocator _SAllocator;*/


	if (MEMORY_OS == false)
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
	else if (MEMORY_OS == true)
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

	//	getchar();

	//return 0;
}