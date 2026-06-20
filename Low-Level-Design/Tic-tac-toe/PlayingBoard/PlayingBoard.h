#pragma once
#include <vector>
#include <iostream>
#include "../PlayingPiece/PlayingPiece.h"

class PlayingBoard{
  private:
    int size;
    std::vector<std::vector<PlayingPiece*>> board;

  public:
    PlayingBoard(int s){
        size = s;
        board.resize(size, std::vector<PlayingPiece*>(size, nullptr));
    }
  
    bool addPiece(int row, int col, PlayingPiece* piece){
      if(board[row][col]!=nullptr){
        return false; // Spot already occupied
      }
      board[row][col] = piece;
      return true;
    }

    bool isSpotFree(int row, int col){
      return board[row][col] == nullptr;
    }

    void displayBoard(){
      for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
          if(board[i][j] == nullptr){
            std::cout << "- ";
          } else {
            std::cout << board[i][j]->getPieceType() << " ";
          }
        }
        std::cout << std::endl;
      }
    }

    bool validSpotAvailable(){
      for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
          if(board[i][j] == nullptr){
            return true;
          }
        }
      }
      return false;
    }

    PlayingPiece* getPieceAt(int row, int col) {
      if (row < 0 || row >= size || col < 0 || col >= size) {
        return nullptr;
      }
      return board[row][col];
    }
};