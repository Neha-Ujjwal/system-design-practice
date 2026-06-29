#pragma once
#include <vector>
#include "ElevatorController.h"
#include "DispatchStrategy.h"

class OddEvenElevatorStrategy: public DispatchStrategy {
  public:
    OddEvenElevatorStrategy() {};

    int selectElevator(std::vector<ElevatorController *> controllers, int floor, Direction direction) override {
      int selectedElevator = -1;
      int minDistance = INT_MAX;
      bool isFloorOdd = floor % 2 != 0;

      for (int i = 0; i < controllers.size(); i++){
        ElevatorCar *car = controllers[i]->getElevatorCar();
        int currentElevatorId = car->getId();
        bool isElevatorOdd = currentElevatorId % 2 != 0;

        int distance = abs(car->getCurrentFloor() - floor);

        if((isFloorOdd && isElevatorOdd) || (!isFloorOdd && !isElevatorOdd)){
          if(distance < minDistance){
            minDistance = distance;
            selectedElevator = i;
          }
        }
      }

      if(selectedElevator == -1){
        minDistance = INT_MAX;
        for (int i = 0; i < controllers.size(); i++){
          ElevatorCar *car = controllers[i]->getElevatorCar();
          int distance = abs(car->getCurrentFloor() - floor);

          if(distance < minDistance){
            minDistance = distance;
            selectedElevator = i;
          }
        }
      }

      if(selectedElevator==-1){
        return 0;
      }

      return selectedElevator;
    }
};