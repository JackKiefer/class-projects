#include <iostream>
#include <string>
#include "Polish.hpp"

namespace
{
	const auto VERSION = "v1.1"; // because why not
}

void welcomeText()
{
	std::cout << "Welcome to Reverse Polish Calculator " << VERSION << std::endl
		  << "Press enter after each value and operator" << std::endl
		  << "Commands: " << std::endl
		  << "[C]lear the calculator stack" << std::endl
		  << "[D]isplay the stack" << std::endl 
		  << "[E]xit the program" << std::endl
	          << std::endl;
}

int main()
{
	welcomeText();
	runCalculator();
	return EXIT_SUCCESS;
}

