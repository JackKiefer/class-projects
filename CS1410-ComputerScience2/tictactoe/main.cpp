#include <iostream>

#include "Board.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "DefensiveRandomPlayer.h"
#include "PerfectPlayer.h"

using namespace std;

Player* getPlayer(Board::Player player)
{
  char choice;
  cout << "Will player ";
  
  if(player == Board::PLAYER_X)
  {
    cout << "X";
  }
  else 
  {
    cout << "O";
  }

  cout << " be:" << endl;
  cout << "\t(H)uman" << endl;
  cout << "\t(R)andom" << endl;
  cout << "\t(D)efensive" << endl;
  cout << "\t(P)erfect" << endl;
  
  cin >> choice;
  
  switch (choice) {
    case 'H':
    case 'h':
      return new HumanPlayer(player);
    case 'R':
    case 'r':
      return new RandomPlayer(player);
    case 'D':
    case 'd':
      return new DefensiveRandomPlayer(player);
    default:
      return new PerfectPlayer(player);
  }
}

int main()
{
  Player* players[2];
  
  players[0] = getPlayer(Board::PLAYER_X);
  players[1] = getPlayer(Board::PLAYER_O);


int X = 0;
int O = 0;
int C = 0;

for(auto i = 0; i <= 100; ++i)
{
  Board board;
  int current_player = 0;
  
  while(board.movesRemain())
  {
    board = players[current_player]->move(board);
    
    current_player++;
    current_player%=2;
  }

//  board.display();
  switch(board.winner())
  {
    case Board::PLAYER_X:
      std::cout << "X's win!" << std::endl;
      ++X;
      break;
      
    case Board::PLAYER_O:
      std::cout << "O's win!" << std::endl;
      ++O;
      break;
      
    case Board::EMPTY:
      std::cout << "Cat's game!" << std::endl;
      ++C;
      break;
  }
}  
  std::cout << "X wins: " << X << std::endl;
  std::cout << "O wins: " << O << std::endl;
  std::cout << "Cat's:  " << C << std::endl;
  delete players[0];
  delete players[1];
}
