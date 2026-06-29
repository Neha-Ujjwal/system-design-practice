#include <vector>
#include <iostream>
#include "ElevatorCar.h"
#include "ElevatorSystem.h"
#include "./DispatchStrategy/NearestElevatorStrategy.h"

int main() {
    // 1. Setup our system components
    ElevatorCar* car1 = new ElevatorCar(1, 0); // Lift 1 at Floor 0
    ElevatorCar* car2 = new ElevatorCar(2, 4); // Lift 2 at Floor 4
    
    ElevatorController* ctrl1 = new ElevatorController(car1);
    ElevatorController* ctrl2 = new ElevatorController(car2);
    
    std::vector<ElevatorController*> controllers = {ctrl1, ctrl2};
    NearestElevatorStrategy* strategy = new NearestElevatorStrategy();
    
    ElevatorSystem* elevatorSystem = new ElevatorSystem(controllers, strategy);

    // 2. Passengers step up and press buttons (This loads the heaps)
    std::cout << "=== Grouping and Allocating Hall Requests ===\n";
    elevatorSystem->sendRequest(3, Direction::UP);   // Loaded into a controller's heap
    elevatorSystem->sendRequest(7, Direction::UP);   // Loaded into a controller's heap
    elevatorSystem->sendRequest(1, Direction::DOWN); // Loaded into a controller's heap

    // 3. THIS IS HOW THEY MOVE: 
    // We explicitly tell the controllers to turn on their motor loops and process the heaps!
    std::cout << "\n=== Starting Elevator Engine Loops ===\n";
    for (ElevatorController* controller : elevatorSystem->getControllers()) {
        // This invokes your while(!upMinHeap.empty() || !downMaxHeap.empty()) loop
        controller->controlElevator(); 
    }

    // Cleanup memory allocations...
    delete car1; delete car2; delete ctrl1; delete ctrl2; delete strategy; delete elevatorSystem;
    return 0;
}