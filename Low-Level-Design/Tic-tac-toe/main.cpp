#include <iostream>
#include "PlayingGame.h"
using namespace std;

int main() {
  cout << "Initializing Tic-tac-toe game..." << endl;

  PlayingGame game;
  game.initializeGame();
  
  cout << "Starting the game..." << endl;
  string winner = game.startGame();

  cout << "Game Over! Winner: " << winner << endl;

  return 0;
}