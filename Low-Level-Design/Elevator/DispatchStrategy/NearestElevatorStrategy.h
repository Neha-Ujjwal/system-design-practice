#pragma once
#include <vector>
#include "Enums.h"
#include "ElevatorCar.h"
#include "DispatchStrategy.h"

class NearestElevatorStrategy: public DispatchStrategy {
  public: 
    NearestElevatorStrategy() {}

    int selectElevator(std::vector<ElevatorController*> controllers, int floor, Direction dir) override {
      int selectedControllerIndex = -1;
      int minDistance = INT_MAX;

      for (int i = 0; i < controllers.size();i++){
        ElevatorCar *car = controllers[i]->getElevatorCar();
        int currentFloor = car->getCurrentFloor();

        bool isSameDirection = (car->getCurrentDirection() == dir) && ((dir == Direction::UP && floor >= currentFloor) || (dir == Direction::DOWN && floor <= currentFloor));

        if(isSameDirection){
          int distance = abs(currentFloor - floor);
           if (distance < minDistance) {
            minDistance = distance;
            selectedControllerIndex = i;
          }
        };
      }

      if(selectedControllerIndex == -1){
        for (int i = 0; i < controllers.size(); i++){
          ElevatorCar *car = controllers[i]->getElevatorCar();
          int currentFloor = car->getCurrentFloor();

          int distance = abs(currentFloor - floor);

          if(distance < minDistance){
            minDistance = distance;
            selectedControllerIndex = i;
          }
        }
      }

      if(selectedControllerIndex == -1){
        return 0;
      }

      return selectedControllerIndex;
    }
};