#include "List.hpp"
#include <iostream>

template <typename T>
LinkedList<T> makeList(LinkedList<T> list)
{
	LinkedList<T> newList;
	newList = list;
	return newList;
}

int main()
{
	
	LinkedList<int> intList;

	std::cout << "Linked list of integers:" << std::endl;

	intList.push(42);
	intList.push(18);
	intList.push(2);
	intList.push(10);
	intList.push(20);
	intList.push(17);
	intList.push(42);

	intList.forEach(print<int>);

	std::cout << std::endl
		 << "Size: " << intList.size() << std::endl << std::endl;

	std::cout << "intList.remove(42):" << std::endl;
	intList.remove(42);
	
	intList.forEach(print<int>);

	std::cout << std::endl
		<< "Size: " << intList.size() << std::endl << std::endl;


	std::cout << "testList initialized through a function call:" << std::endl; 

	LinkedList<int> testList = makeList(intList);
	testList.forEach(print<int>);
	std::cout << std::endl;

	std::cout << "testList_2 initialized through assigning it the values of testList:" << std::endl;

	LinkedList<int> testList_2 = testList;
	testList_2.forEach(print<int>);
}