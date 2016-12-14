#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "DisjointSet.h"

namespace
{
	const std::size_t MEMBERS = 99;
	const auto MAX_WIDTH = 20;
}

// Gets a random integer between 0 and the size of the array
int getRand() 
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<> range(0, MEMBERS - 1);
	return range(engine);
}

int main()
{
	DisjointSet<int, MEMBERS> network;
	
	auto days = 0;

	// -- Introduction -- //

	if ( MEMBERS <= MAX_WIDTH )
	{
		std::cout <<	"Welcome to E'ERBODY GON' BE FRIENDS. We're using an array of size " << MEMBERS << ": "
			<< std::endl << std::endl;
		
		std::cout << network.toString() << std::endl << std::endl;

		std::cout << "The array will be printed after each union. Press enter to step through." << std::endl;
	}
	else
	{
		std::cout << "Welcome to WOW ***E'ERBODY*** GON' BE FRIENDS!!!" << std::endl;
		std::cout << "The specified array of size " << MEMBERS << " is too large to be printed."
		<< std::endl << "The results are as follows: ";
	}

	// -- Social Network Algorithm -- //

	while (!network.connected())
	{
		if ( MEMBERS <= MAX_WIDTH )
			std::cin.ignore();	

		++days;

		auto randomA = getRand();
		auto randomB = getRand();

		if ( MEMBERS <= MAX_WIDTH )
			std::cout << "Union( " << randomA << ", " << randomB << " ):" << std::endl;

		network.unionize(randomA, randomB);

		if ( MEMBERS <= MAX_WIDTH )
			std::cout << network.toString() << std::endl; 
	}
	
	// -- Results -- //

	std::cout << std::endl << std::endl;

	std::cout << "E'eryone be friends, mon!" << std::endl
		<< "Time taken: " << days << " days" << std::endl 
		<< "Total successful unions: " << network.getUnionCt() << std::endl
		<< "Total finds: " << network.getFindCt() << std::endl;	
}
