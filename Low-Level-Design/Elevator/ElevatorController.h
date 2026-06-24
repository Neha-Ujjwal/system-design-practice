#pragma once
#include <vector>
#include "ElevatorCar.h"

class ElevatorController {
  private:
    ElevatorCar *elevatorCar;
    std::vector<int> pendingFloors;
  public:
    ElevatorController(ElevatorCar* car, std::vector<int> floors){
      elevatorCar = car;
      pendingFloors = floors;
    }

    //getter and setter methods
    ElevatorCar* getElevatorCar(){
      return elevatorCar;
    }

    std::vector<int> getPendingFloors(){
      return pendingFloors;
    }

    void setElevatorCar(ElevatorCar* car){
      elevatorCar = car;
    }

    void setPendingFloors(std::vector<int> floors){
      pendingFloors = floors;
    }
};