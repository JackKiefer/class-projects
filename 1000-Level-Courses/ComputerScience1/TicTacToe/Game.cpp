#include "Game.hpp"
#include "Board.hpp"
#include "Player.hpp"


void Game::play()
{
	board board;
	auto current = Player::ONE;
	while (board.movesLeft())
	{
		board.display();
		auto move = board.askMove(current);
		board.makeMove(move, current);
		board.winnerWinnerVeganDinner(current);
		current = next(current);
	}
}