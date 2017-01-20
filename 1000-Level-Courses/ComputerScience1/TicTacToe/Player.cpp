#include "Player.hpp"

Player next(Player p)
{
	if (p == Player::ONE) return Player::TWO;
	else return Player::ONE;
}

char display(Player p)
{
	if (p == Player::ONE) return 'X';
	else if (p == Player::TWO) return 'O';
	else return ' ';
}
