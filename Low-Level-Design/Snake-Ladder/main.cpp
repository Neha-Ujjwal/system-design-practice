#include <iostream>
#include "Game.h"
using namespace std;

int main() {
  cout << "=== SNAKE AND LADDER SIMULATION CRADLE ===" << endl;

  // 1. Instantiating the object calls the constructor, which calls initialiseGame() once
  Game* g = new Game();

  cout << "\nStarting the gameplay loop..." << endl;
  
  // 2. Kick off the actual game loop!
  g->startGame();

  // 3. Clean up heap memory
  delete g; 
  return 0;
}