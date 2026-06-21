#pragma once
#include <deque>
#include <iostream>
#include "Dice.h"
#include "Board.h"
#include "Player.h"

class Game {
  private:
    Board *board;
    std::deque<Player*> dq;
    Dice *dice;
  public:
    Game() {
      initialiseGame();
    }

    void initialiseGame(){
      initialiseBoard();
      initialiseDice();
      addPlayers();
    }

    void initialiseBoard(){
      std::cout << "Enter the size of board: ";
      int boardSize;
      std::cin >> boardSize;

      std::cout << " Enter the number of Snakes you want to add: ";
      int numberOfSnakes;
      std::cin >> numberOfSnakes;

      std::cout << "Enter the number of ladders you want to add: ";
      int numberOfLadders;
      std::cin >> numberOfLadders;

      board = new Board(boardSize, numberOfSnakes, numberOfLadders);
    }

    void initialiseDice(){
      std::cout << "Enter the dice count: ";
      int diceCount;
      std::cin >> diceCount;

      dice = new Dice(diceCount);
    }

    void addPlayers(){
       std::cout << "Creating Players: ";

      Player *p1 = new Player("player1", 0);
      Player *p2 = new Player("player2", 0);

      dq.push_back(p1);
      dq.push_back(p2);
    }

    void startGame(){
      bool isWinnerFound = false;

      while(!isWinnerFound){
        Player *currPlayer = dq.front();
        dq.pop_front();

        std::cout << currPlayer->getName() << "'s turn" << "current position is " << currPlayer->getCurrentPosition() << std::endl;
        int diceScore = dice->rollDice();

        std::cout << "Dice Score " << diceScore << std::endl;
        int prevPos = currPlayer->getCurrentPosition();
        int currPos = prevPos + diceScore;

        if (currPos >= (board->getBoardSize() * board->getBoardSize())) {
            std::cout << "Winner Found!! Winner is " << currPlayer->getName() << std::endl;
            isWinnerFound = true;
            break;
        }

        // move player to correct position
        currPlayer->setCurrentPosition(currPos);

        // check for ladder or snake case
        Cell *currCell = board->getCell(currPos);

        if(currCell!=nullptr){
          //find correspoing jump object
          Jump* j = currCell->getJump();
          if (j != nullptr) {
              std::cout << "Jumped via Snake/Ladder to: " << j->getEndPoint() << std::endl;
              currPos = j->getEndPoint();
              currPlayer->setCurrentPosition(currPos);
          }
        }

        // check for winner case
        if(currPos >= (board ->getBoardSize() * board ->getBoardSize()) - 1){
          std::cout << "Winner Found!! Winner is " << currPlayer->getName() << std::endl;
          isWinnerFound = true;
          break;
        }

        dq.push_back(currPlayer);
      }
    }
};