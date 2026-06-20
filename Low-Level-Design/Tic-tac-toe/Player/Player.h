#pragma once
#include <string>
#include "../PlayingPiece/PlayingPiece.h"


class Player {
  private:
    std::string name;
    PlayingPiece* piece;
  public:
    Player(std::string n, PlayingPiece* p){
      name = n;
      piece = p;
    }

    std::string getName() {
      return name;
    }

    PlayingPiece* getPiece() {
      return piece;
    }

    void setName(std::string n){
      name = n;
    }

    void setPiece(PlayingPiece* p){
      piece = p;
    }
};