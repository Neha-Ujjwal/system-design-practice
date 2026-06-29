#pragma once
#include <vector>
#include "Enums.h"
#include "ElevatorController.h"
#include "./DispatchStrategy/DispatchStrategy.h"

class ElevatorSystem {
  private:
    std::vector<ElevatorController *> controllers;
    DispatchStrategy *strategy;
  public:
    ElevatorSystem(std::vector<ElevatorController *> controllers,  DispatchStrategy *strategy){
      this->controllers = controllers;
      this->strategy = strategy;
    }

    DispatchStrategy* getStrategy(){
      return strategy;
    }

    std::vector<ElevatorController *> getControllers(){
      return controllers;
    }

    void setStrategy(DispatchStrategy* str){
      this->strategy = str;
    }

    void setControllers(std::vector<ElevatorController *> c){
      controllers = c;
    }

    void sendRequest(int floor, Direction dir){
      int selectedElevator = strategy->selectElevator(controllers, floor, dir);

      if(selectedElevator!=-1 && selectedElevator < controllers.size()){
        controllers[selectedElevator]->addNewRequest(floor, dir);
      }else {
        std::cout << "Error: No available elevator found to handle the request at Floor " << floor << ".\n";
      }
    }
};