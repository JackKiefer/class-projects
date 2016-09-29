#include <vector>
#include <algorithm>
#include "PerfectPlayer.h"
#include "Board.h"

PerfectPlayer::PerfectPlayer(Board::Player player):
Player(player)
{
}

int PerfectPlayer::getScore(Board board, bool myTurn)
{
    if (board.winner() == mPlayer) return 10;
    else if (board.winner() == Board::EMPTY) return 0;
    return -10;
}

Board::Player opponent(Board::Player player)
{
    if (player == Board::PLAYER_X) return Board::PLAYER_O;
    return Board::PLAYER_X;
}


std::vector<Board> PerfectPlayer::getChildren(Board board, bool myTurn)
{
  std::vector<Board> children;
  
  Board::Player player;
  if (myTurn) player = mPlayer;
  else player = opponent(mPlayer);

  for(int i=0;i<3;++i)
    for(int j=0;j<3;++j)
    {
      if(board(i,j)==Board::EMPTY)
      { 
        children.push_back(board.move(i,j,player));
      }
    }
    return children;
}


int PerfectPlayer::getMove(Board board, bool myTurn)
{
    if(!board.movesRemain()) return getScore(board, myTurn);

    std::vector<Board> children = getChildren(board, myTurn);
    std::vector<int> scores;

    for(auto&& c : children)
    {
        scores.push_back(getMove(c, !myTurn));
    }

    if (myTurn)
    {
        return *std::max_element(scores.begin(), scores.end()); 
    }
    else
    {
        return *std::min_element(scores.begin(), scores.end()); 
    } 
}

Board PerfectPlayer::getMove(Board board)
{
    std::vector<Board> children = getChildren(board, true);
    int maxScore = -20;
    Board bestBoard;

    for(auto&& c : children)
    {
       auto score = getMove(c, false);
       if( score > maxScore )
       {
           maxScore = score;
           bestBoard = c;
       }
    }
    return bestBoard;
}

Board PerfectPlayer::move(Board board)
{
  return getMove(board);
}


