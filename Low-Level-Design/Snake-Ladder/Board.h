#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include "Cell.h"
#include "Jump.h"

class Board {
  private:
    int size;
    std::vector<std::vector<Cell *>> board;
    int numberOfSnakes;
    int numberOfLadders;
  public:
    Board(int s, int n, int m){
      size = s;
      board.resize(size, std::vector<Cell *>(size, nullptr));
      numberOfSnakes = n;
      numberOfLadders = m;
      initialiseBoard();
      addSnakesAndLadders();
    }

    void initialiseBoard(){
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = new Cell(nullptr);
        }
      }
    }

    void addSnakesAndLadders(){
      std::cout << "Adding Snakes to the board: " << std::endl;

      while(numberOfSnakes){
       int startPoint = (std::rand() % ((size * size) - 2)) + 1;
       int endPoint = (std::rand() % ((size * size) - 2)) + 1;

       if (endPoint >= startPoint){
         continue;
       }

        Jump* j = new Jump(startPoint, endPoint);
        Cell* cell = getCell(startPoint);
        cell->setCell(j);

        numberOfSnakes--;
      }

      std::cout << "Added Snakes to the board" << std::endl;

       std::cout << "Adding Ladders to the board: " << std::endl;

      while(numberOfLadders){
       int startPoint = (std::rand() % ((size * size) - 2)) + 1;
       int endPoint = (std::rand() % ((size * size) - 2)) + 1;

        if(startPoint >= endPoint){
          continue;
        }

        Jump* j = new Jump(startPoint, endPoint);
        Cell* cell = getCell(startPoint);
        cell->setCell(j);

        numberOfLadders--;
      }

       std::cout << "Added Ladders to the board" << std::endl;

    }

    Cell* getCell(int startPoint){
      int row = startPoint / size;
      int col = startPoint % size;
      return board[row][col];
    }

    int getBoardSize(){
      return size;
    }
};