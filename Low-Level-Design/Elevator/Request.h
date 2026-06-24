#pragma once

#include "Enums.h"

class Request {
  private:
    int requestedFloor;
    Direction requestedDirection;
  public:
    Request(int floor, Direction dir){
      requestedFloor = floor;
      requestedDirection = dir;
    }

    //getter and setter methods
    int getRequestedFloor(){
      return requestedFloor;
    }

    Direction getRequestedDirection(){
      return requestedDirection;
    }

    void setRequestedFloor(int floor){
      requestedFloor = floor;
    }

    void setRequestedDirection(Direction dir){
      requestedDirection = dir;
    }
};