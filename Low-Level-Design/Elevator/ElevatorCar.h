#pragma once

#include "Enums.h";

class ElevatorCar {
  private:
    int id;
    int currentFloor;
    Direction currentDirection;
    ElevatorState currentState;
  public:
    // constructor
    ElevatorCar(int id, int floor, Direction dir, ElevatorState state){
      this->id = id;
      currentFloor = floor;
      currentDirection = dir;
      currentState = state;
    }

    //getter methods
    int getId(){
      return id;
    }

    int getCurrentFloor(){
      return currentFloor;
    }

    Direction getCurrentDirection(){
      return currentDirection;
    }

    ElevatorState getCurrentState(){
      return currentState;
    }

    //setter methods
    void setId(int id){
      this->id = id;
    }

    void setCurrentDirection(Direction dir){
      currentDirection = dir;
    }

    void setCurrentFloor(int floor){
      currentFloor = floor;
    }

    void setCurrentState(ElevatorState state){
      currentState = state;
    }
};