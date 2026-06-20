#pragma once
#include <string>

class PlayingPiece{
  private:
    std::string pieceType;
  public:
    PlayingPiece(std::string type){
      pieceType = type; 
    }

    std::string getPieceType() {
      return pieceType;
    }
};