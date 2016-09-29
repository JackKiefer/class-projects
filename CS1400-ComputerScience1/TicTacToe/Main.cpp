// A simple command-line Tic Tac Toe game

#include "Game.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>

bool askQuestion(std::string);
void instructions();

int main(void)
{
	while (askQuestion("Would you like to start a new game of Tic Tac Toe? (y/n)"))
	{
		Game g;
		instructions();
		g.play();
	}
	return EXIT_SUCCESS;
}

bool askQuestion(std::string q)
{
	
	std::string answer;
	while (true)
	{
		std::cout << q << std::endl;
		std::cin >> answer;
		char a = std::tolower(answer.front());
		if (a == 'y') return true;
		else if (a == 'n') return false;
		else std::cout << "Invalid input" << std::endl;
	}
}

void instructions()
{
	std::cout << std::endl;
	std::cout << "Instructions:" << std::endl << std::endl;
	std::cout << "Player X moves first. Each player chooses their move by" << std::endl;
	std::cout << "entering the number of the cell they'd like to mark." << std::endl;
	std::cout << "The cells are numbered as follows:" << std::endl << std::endl;
	std::cout << "1 | 2 | 3" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "4 | 5 | 6" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "7 | 8 | 9" << std::endl;
	std::cout << std::endl;
	std::cout << "Let the game begin!" << std::endl;
}
