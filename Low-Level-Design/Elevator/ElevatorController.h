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

            std::cout << "Elevator " << elevatorCar->getId() << " moving UP from floor " 
                        << elevatorCar->getCurrentFloor() << " to floor " << nextFloor << ".\n";
            
            elevatorCar->setCurrentFloor(nextFloor);
            std::cout << "Elevator " << elevatorCar->getId() << " arrived at floor " << nextFloor << ". Doors Open -> Close.\n";
          }

          // Reset state once the upward sweep finishes
          elevatorCar->setCurrentState(ElevatorState::IDLE);
          elevatorCar->setCurrentDirection(Direction::NONE);
        }

        if(elevatorCar->getCurrentDirection() == Direction::DOWN || !downMaxHeap.empty()){
           elevatorCar->setCurrentDirection(Direction::DOWN);
           elevatorCar->setCurrentState(ElevatorState::MOVING);

           while(!downMaxHeap.empty()){
             int nextFloor = downMaxHeap.top();
             downMaxHeap.pop();

              std::cout << "Elevator " << elevatorCar->getId() << " moving DOWN from floor " 
                        << elevatorCar->getCurrentFloor() << " to floor " << nextFloor << ".\n";
              
              elevatorCar->setCurrentFloor(nextFloor);
              std::cout << "Elevator " << elevatorCar->getId() << " arrived at floor " << nextFloor << ". Doors Open -> Close.\n";
          }

          // Reset state once the downward sweep finishes
          elevatorCar->setCurrentState(ElevatorState::IDLE);
          elevatorCar->setCurrentDirection(Direction::NONE);
        }
      }
    }
};