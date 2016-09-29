#ifndef BOARD_HPP
#define BOARD_HPP

#include "Player.hpp"

class board
{
public:
	board::board() {
		square_1 = Player::NONE;
		square_2 = Player::NONE;
		square_3 = Player::NONE;
		square_4 = Player::NONE;
		square_5 = Player::NONE;
		square_6 = Player::NONE;
		square_7 = Player::NONE;
		square_8 = Player::NONE;
		square_9 = Player::NONE;
		gameWon = false;

	}
	bool movesLeft() const;
	void display() const;
	 int askMove(Player);
	bool isValidMove(int) const;
	void makeMove(int, Player);
	void winnerWinnerVeganDinner(Player);
private:
	bool gameWon;
	Player square_1;
	Player square_2;
	Player square_3;
	Player square_4;
	Player square_5;
	Player square_6;
	Player square_7;
	Player square_8;
	Player square_9;

};

#endif