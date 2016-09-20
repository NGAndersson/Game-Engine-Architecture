#include "../Header/Allocator.h"
#include "../Header/MemoryManager.h"
#include "../Header/PoolAllocator.h"
#include "../Header/StackAllocator.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

#define MEMORY_OS true
#define TestCase 1
#define Scenario 1

int main()
{
	int i = 0, j = 64;
	std::clock_t c_start, c_end;
	Allocator _Allocator;
	MemoryManager _MManager;
	PoolAllocator _PAllocator;
	StackAllocator _SAllocator;


	if (MEMORY_OS == false && TestCase == 1 && Scenario == 1)
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
	else if (MEMORY_OS == false && TestCase == 1 && Scenario == 2)
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
	else if (MEMORY_OS == false && TestCase == 2 && Scenario == 1)
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
	else if (MEMORY_OS == false && TestCase == 2 && Scenario == 2)
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
	else if (MEMORY_OS == true && TestCase == 1 && Scenario == 1)
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
	else if (MEMORY_OS == true && TestCase == 1 && Scenario == 2)
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
	else if (MEMORY_OS == true && TestCase == 2 && Scenario == 1)
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
	else if (MEMORY_OS == true && TestCase == 2 && Scenario == 2)
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

	
	getchar();

	return 0;
}