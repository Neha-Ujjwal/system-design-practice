#pragma once
#include <deque>
#include <string>
#include <iostream>
#include "PlayingBoard/PlayingBoard.h"
#include "Player/Player.h"
#include "PlayingPiece/PlayingPieceX.h"
#include "PlayingPiece/PlayingPieceO.h"

class PlayingGame {
  private:
    std::deque<Player*> players;
    PlayingBoard* board;
  public:
    void initializeGame(){
      PlayingPiece* pieceX = new PlayingPieceX();
      PlayingPiece* pieceO = new PlayingPieceO();

      Player* player1 = new Player("Player 1", pieceX);
      Player* player2 = new Player("Player 2", pieceO);

      players.push_back(player1);
      players.push_back(player2);

      board = new PlayingBoard(3);
    }

    std::string startGame(){
      bool winnerFound = false;

      while(!winnerFound){
        Player* currentPlayer = players.front();
        players.pop_front();

        // show current state of board
        board->displayBoard();

        //check if valid spots are available before asking for input
        if(!board->validSpotAvailable()){
          std::cout << "Game is a draw!" << std::endl;
          return "Draw";
        }

        // logic to take input from current player and update board
        std::cout << currentPlayer->getName() <<" " << currentPlayer->getPiece()->getPieceType() << "'s turn: "<< std::endl;
        int row, col;

        std::cout << "Enter row number (0 - 2): ";
        std::cin >> row;
        std::cout << "Enter column number (0 - 2): ";
        std::cin >> col;

        bool isValidMove = board->addPiece(row, col, currentPlayer->getPiece());
        if(!isValidMove){
          std::cout << "Invalid move. Try again." << std::endl;
          players.push_front(currentPlayer);
          continue;
        }

        // logic to check if current player has won after this move
        bool hasWon = checkWinCondition(row, col, currentPlayer->getPiece()->getPieceType());
        if(hasWon){
          winnerFound = true;
          std::cout << currentPlayer->getName() << " wins!" << std::endl;
          return currentPlayer->getName();
        }

        // if no winner, add current player back to the end of the queue
        players.push_back(currentPlayer);
      }

      return "No winner";
    }

    bool checkWinCondition(int row, int col, std::string pieceType){
      bool rowWin = true, colWin = true, diagWin = true, AntiDiagWin = true;

      for (int j = 0; j < 3;j++){
        if(board->getPieceAt(row, j)==nullptr || board->getPieceAt(row, j)->getPieceType() != pieceType){
          rowWin = false;
          break;
        }
      }

      for (int i = 0; i < 3;i++){
        if(board->getPieceAt(i, col)==nullptr || board->getPieceAt(i, col)->getPieceType() != pieceType){
          colWin = false;
          break;
        }
      }

      for (int i = 0; i < 3;i++){
        if(board->getPieceAt(i, i)==nullptr || board->getPieceAt(i, i)->getPieceType() != pieceType){
          diagWin = false;
          break;
        }
      }

      for (int i = 0; i < 3;i++){
        if(board->getPieceAt(i, 2-i)==nullptr || board->getPieceAt(i, 2-i)->getPieceType() != pieceType){
          AntiDiagWin = false;
          break;
        }
      }

      return rowWin || colWin || diagWin || AntiDiagWin;
    }
};