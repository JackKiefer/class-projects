#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <functional>
#include "Sort.hpp"

namespace
{
	const auto REPEATS = 10;
}

int getRandom(int n) 
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<> rand(1, 2 * n);
	return rand(engine);
}

std::vector<int> makeVector(int size)
{
	std::vector<int> v;
	for (int i = 0; i < size; ++i)
	{
		v.push_back(getRandom(size));
	}
	return v;
}

long long getTime(std::vector<int>& v, std::function<void(std::vector<int>&)> sort)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	sort(v);
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = endTime - startTime;
	auto micro_secs = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	return micro_secs.count();
}

void menu()
{
	std::cout << "[1 - Bubble sort ] [2 - Insertion sort ] [3 - Selection sort ]" << std::endl;
	std::cout << "[4 -  Merge sort ] [5 -   Quick sort   ] [6 -   std::sort    ]" << std::endl;
	std::cout << "Enter the number of the algorithm to test: " << std::endl;
}

std::function<void(std::vector<int>&)> getAlgorithm()
{
	menu();
	int algo;
	std::cin >> algo;
	switch (algo)
	{
	case 1: 
		std::cout << "Bubble sort:" << std::endl;
		return bubbleSort;
		break;
	case 2: 
		std::cout << "Insertion sort:" << std::endl;
		return insertionSort;
		break;
	case 3: 
		std::cout << "Selection sort:" << std::endl;
		return selectionSort;
		break;
	case 4: 
		std::cout << "Merge sort:" << std::endl;
		return mergeSort;
		break;
	case 5: 
		std::cout << "Quick sort:" << std::endl;
		return quickSort;
		break;
	case 6: 
		std::cout << "std::sort :" << std::endl;
		return stdSort;
		break;
	default: 
		std::cout << "std::sort :" << std::endl;
		return stdSort;
	}
}

std::ofstream fout("data.txt");

void dataOut(std::ofstream& o, int size, long long time)
{
	o << size << " " << time << std::endl;
}

long long getAvg(std::vector<int>& v, std::function<void(std::vector<int>&)> a)
{
	auto sum = 0;
	for (int i = 0; i < REPEATS; ++i)
	{
		auto time = getTime(v, a);
		sum += time;
	}
	auto avg = sum / REPEATS;
	return avg;
}

int main()
{
	std::function<void(std::vector<int>&)> a = getAlgorithm();

	for (int size = 1000; size <= 100000; size += 1000)
	{
		std::vector<int> v = makeVector(size);
		auto avg = getAvg(v, a);
		std::cout << "Vector size = " << size << "\t average sort time: " << avg << " microseconds" << std::endl;
		dataOut(fout, size, avg);
	}
}