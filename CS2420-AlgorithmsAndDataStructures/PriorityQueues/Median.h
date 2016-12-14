#ifndef MEDIAN_H
#define MEDIAN_H

// This class utilizes min/max skew heaps to dynamically find the median of a given data set

#include <iostream>
#include <cstdlib>
#include <string>

#include "SkewHeap.h"

template <typename T>
class Median
{
public:
	Median() :lesserVals("max") {} // lesserVals is a max heap
	void addNum(T);
	void report(bool);
private:
	void updateMedian();
	T curMedian;
	bool firstEntry = false;
	SkewHeap<T> greaterVals; // Default initialized to a min heap
	SkewHeap<T> lesserVals;
};


// Updates the median value following the latest heap insertion
template <typename T>
void Median<T>::updateMedian()
{
	int dif = greaterVals.size() - lesserVals.size();
	if (std::abs(dif) <= 1) return; // Median is fine. Do nothing
	
	T newMedian;

	if (greaterVals.size() > lesserVals.size())
	{
		newMedian = greaterVals.removeMin();
		lesserVals.insert(curMedian);
	}
	else
	{
		newMedian = lesserVals.removeMax();
		greaterVals.insert(curMedian);
	}

	curMedian = newMedian;
}

// Inserts numbers into either heap, or holds on to the first value
template <typename T>
void Median<T>::addNum(T newValue)
{
	if (!firstEntry)
	{
		curMedian = newValue;
		firstEntry = true;
		return;
	}

	if (newValue > curMedian) 
	{
		greaterVals.insert(newValue);
	}

	else if (newValue <= curMedian) // Values equal to the median go into the max heap
	{
		lesserVals.insert(newValue);
	}

	updateMedian();
	
	return;	
}


// Prints a report of data about the heaps
template <typename T>
void Median<T>::report(bool print)
{
	std::cout << "Median: " << curMedian << std::endl
	<< "Total heap size: " << greaterVals.size() + lesserVals.size() << std::endl
	<< "Min heap merges: " << greaterVals.mergeCt() << std::endl
	<< "Max heap merges: " << lesserVals.mergeCt() << std::endl;

	if (print)
	{	
		std::cout << "Min heap:" << std::endl
		<< greaterVals.print() << std::endl

		<< "Max heap:" << std::endl
		<< lesserVals.print() << std::endl;

	}

}

#endif
