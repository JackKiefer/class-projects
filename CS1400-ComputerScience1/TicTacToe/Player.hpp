#ifndef PLAYER_HPP
#define PLAYER_HPP

enum class Player
{
	ONE, TWO, NONE
};

Player next(Player);
char display(Player);

#endif