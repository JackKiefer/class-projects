#ifndef _PERFECT_PLAYER_
#define _PERFECT_PLAYER_

#include "Player.h"
#include <vector>

class PerfectPlayer:public Player
{
public:
  PerfectPlayer(Board::Player);
  virtual Board move(Board board);
  Board getMove(Board);
  int getMove(Board, bool);
  std::vector<Board> getChildren(Board, bool);
  int getScore(Board, bool);
};

#endif
