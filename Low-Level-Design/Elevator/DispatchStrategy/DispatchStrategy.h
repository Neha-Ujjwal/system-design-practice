#pragma once
#include "ElevatorController.h"

class DispatchStrategy {
  public:
    //Virtual destructor ensures proper memory cleanup for child classes
    virtual ~DispatchStrategy(){}

    virtual int selectElevator(std::vector<ElevatorController *> controllers, int floor, Direction direction) = 0;
};