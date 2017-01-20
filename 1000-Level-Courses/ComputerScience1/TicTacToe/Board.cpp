#include "Board.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>

bool board::movesLeft() const
{
	return (
		   (square_1 == Player::NONE ||
			square_2 == Player::NONE ||
			square_3 == Player::NONE ||
			square_4 == Player::NONE ||
			square_5 == Player::NONE ||
			square_6 == Player::NONE ||
			square_7 == Player::NONE ||
			square_8 == Player::NONE ||
			square_9 == Player::NONE) &&
			gameWon == false
		);
}


bool board::isValidMove(int move) const
{
	switch (move)
	{
		case 1: return (square_1 == Player::NONE);
		case 2: return (square_2 == Player::NONE);
		case 3: return (square_3 == Player::NONE);
		case 4: return (square_4 == Player::NONE);
		case 5: return (square_5 == Player::NONE);
		case 6: return (square_6 == Player::NONE);
		case 7: return (square_7 == Player::NONE);
		case 8: return (square_8 == Player::NONE);
		case 9: return (square_9 == Player::NONE);
		default: return false;
	}
}

void board::display() const
{
	std::string v = " | ";
	std::string h = "---------";
	std::cout << std::endl;
	std::cout << ::display(square_1) << v << ::display(square_2) << v << ::display(square_3) << std::endl;
	std::cout << h << std::endl;
	std::cout << ::display(square_4) << v << ::display(square_5) << v << ::display(square_6) << std::endl;
	std::cout << h << std::endl;
	std::cout << ::display(square_7) << v << ::display(square_8) << v << ::display(square_9) << std::endl << std::endl;
}

int board::askMove(Player p)
{
	std::cout << "Player " << ::display(p) << ", enter your move." << std::endl;
	while (true)
	{
		std::string input;
		std::cin >> input;
		char tempChar = input.front();
		int move = tempChar - '0';
		if (isValidMove(move)) return move;
		else
		{
			std::cout << "Invalid move" << std::endl;
		}
	}
}

void board::makeMove(int move, Player p)
{
	switch (move)
	{
	case 1: square_1 = p; 
		break;
	case 2: square_2 = p;
		break;		   
	case 3: square_3 = p;
		break;		   
	case 4: square_4 = p;
		break;		   
	case 5: square_5 = p;
		break;		   
	case 6: square_6 = p;
		break;		   
	case 7: square_7 = p;
		break;		   
	case 8: square_8 = p;
		break;		   
	case 9: square_9 = p;
		break;
	}
}

// 1 | 2 | 3
// ---------
// 4 | 5 | 6
// ---------
// 7 | 8 | 9


void board::winnerWinnerVeganDinner(Player p)
{
	if (
		(square_1 == square_2 && square_2 == square_3 && square_2 != Player::NONE) || // 1 2 3
		(square_4 == square_5 && square_5 == square_6 && square_5 != Player::NONE) || // 4 5 6
		(square_7 == square_8 && square_8 == square_9 && square_8 != Player::NONE) || // 7 8 9
		(square_1 == square_4 && square_4 == square_7 && square_4 != Player::NONE) || // 1 4 7
		(square_2 == square_5 && square_5 == square_8 && square_5 != Player::NONE) || // 2 5 8
		(square_3 == square_6 && square_6 == square_9 && square_6 != Player::NONE) || // 3 6 9
		(square_1 == square_5 && square_5 == square_9 && square_5 != Player::NONE) || // 1 5 9
		(square_3 == square_5 && square_5 == square_7 && square_5 != Player::NONE)    // 3 5 7
		)
	{
		display();
		std::cout << "Player " << ::display(p) << " wins!" << std::endl;
		gameWon = true;
	}
	else if (movesLeft() == false)
	{
		display();
		std::cout << "The game is a draw!" << std::endl;
		gameWon = true;
	}
}
