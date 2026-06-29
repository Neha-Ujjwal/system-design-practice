#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include "Enums.h"
#include "ElevatorCar.h"

class ElevatorController {
  private:
    ElevatorCar *elevatorCar;
    std::priority_queue<int> downMaxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> upMinHeap;
  public:
    ElevatorController(ElevatorCar* car){
      elevatorCar = car;
    }

    //getter and setter methods
    ElevatorCar* getElevatorCar(){
      return elevatorCar;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> getUpMinHeap(){
      return upMinHeap;
    }

    std::priority_queue<int> getDownMaxHeap(){
      return downMaxHeap;
    }

    void setUpMinHeap(std::priority_queue<int, std::vector<int>, std::greater<int>> q){
      upMinHeap = q;
    }

    void setDownMaxHeap(std::priority_queue<int> q){
      downMaxHeap = q;
    }

    void setElevatorCar(ElevatorCar* car){
      elevatorCar = car;
    }

    void addNewRequest(int floor, Direction dir){
      if(dir == Direction::UP){
        upMinHeap.push(floor);
        std::cout << "Elevator " << elevatorCar->getId() << " queued UP request for Floor " << floor << ".\n";
      }
      else
      {
        downMaxHeap.push(floor);
        std::cout << "Elevator " << elevatorCar->getId() << " queued DOWN request for Floor " << floor << ".\n";
      }
    }

    void controlElevator(){
      // Master loop keeps the elevator processing until BOTH heaps are completely empty
      while(!upMinHeap.empty() || !downMaxHeap.empty()){

        if(elevatorCar->getCurrentDirection() == Direction::UP || !upMinHeap.empty()){
          elevatorCar->setCurrentDirection(Direction::UP);
          elevatorCar->setCurrentState(ElevatorState::MOVING);

          while(!upMinHeap.empty()){
            int nextFloor = upMinHeap.top();
            upMinHeap.pop();

            std::string physicalDir = (nextFloor >= elevatorCar->getCurrentFloor()) ? "UP" : "DOWN";

            std::cout << "Elevator " << elevatorCar->getId() << " moving " << physicalDir 
                      << " from floor " << elevatorCar->getCurrentFloor() << " to floor " << nextFloor << ".\n";
            
            elevatorCar->setCurrentFloor(nextFloor);
            std::cout << "Elevator " << elevatorCar->getId() << " arrived at floor " << nextFloor << ". Doors Open -> Close.\n";
          }
        }

        if(elevatorCar->getCurrentDirection() == Direction::DOWN || !downMaxHeap.empty()){
           elevatorCar->setCurrentDirection(Direction::DOWN);
           elevatorCar->setCurrentState(ElevatorState::MOVING);

           while(!downMaxHeap.empty()){
             int nextFloor = downMaxHeap.top();
             downMaxHeap.pop();

              std::string physicalDir = (nextFloor >= elevatorCar->getCurrentFloor()) ? "UP" : "DOWN";

              std::cout << "Elevator " << elevatorCar->getId() << " moving " << physicalDir 
                        << " from floor " << elevatorCar->getCurrentFloor() << " to floor " << nextFloor << ".\n";
              
              elevatorCar->setCurrentFloor(nextFloor);
              std::cout << "Elevator " << elevatorCar->getId() << " arrived at floor " << nextFloor << ". Doors Open -> Close.\n";
          }
        }
      }

      elevatorCar->setCurrentState(ElevatorState::IDLE);
      elevatorCar->setCurrentDirection(Direction::NONE);
    }

    void addInternalRequest(int targetFloor) {
      int currentFloor = elevatorCar->getCurrentFloor();
      
      if (targetFloor > currentFloor) {
          upMinHeap.push(targetFloor);
          std::cout << "Inside Elevator " << elevatorCar->getId() 
                    << ": Passenger pressed destination Floor " << targetFloor << " (Queued UP).\n";
      } else if (targetFloor < currentFloor) {
          downMaxHeap.push(targetFloor);
          std::cout << "Inside Elevator " << elevatorCar->getId() 
                    << ": Passenger pressed destination Floor " << targetFloor << " (Queued DOWN).\n";
      } else {
          std::cout << "Inside Elevator " << elevatorCar->getId() 
                    << ": Already on Floor " << targetFloor << ". Doors opening.\n";
      }
  }
};