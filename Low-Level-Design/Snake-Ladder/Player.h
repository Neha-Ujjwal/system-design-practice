#pragma once
#include <string>

class Player {
  private:
    std::string name;
    int currentPosition;

  public:
    Player(std::string n, int position) {
      name = n;
      currentPosition = position;
    }

    std::string getName() {
      return name;
    }

    int getCurrentPosition(){
      return currentPosition;
    }

    void setCurrentPosition(int pos){
      currentPosition = pos;
    }
};