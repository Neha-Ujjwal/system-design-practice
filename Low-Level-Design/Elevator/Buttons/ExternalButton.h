#pragma once
#include "Enums.h"

class ExternalButton {
  private:
    int floor;
    Direction direction;
  public:
    ExternalButton(int floor, Direction dir){
      this->floor = floor;
      direction = dir;
    }

    // getter and setter methods
    Direction getDirection(){
      return direction;
    }

    int getFloor(){
      return floor;
    }

    void setDirection(Direction dir){
      direction = dir;
    }

    void setFloor(int floor){
      this->floor = floor;
    }
};