#pragma once
#include "Building/ParkingBuilding.h"
#include "Gate/EntranceGate.h"
#include "Gate/ExitGate.h"

class ParkingLot {
  private:
    EntranceGate* entranceGate;
    ExitGate* exitGate;
    ParkingBuilding* parkingBuilding;
  public:
    ParkingLot(EntranceGate* gate, ExitGate* exitGate, ParkingBuilding* building){
      entranceGate = gate;
      exitGate = exitGate;
      parkingBuilding = building; 
    }

    Ticket* vehicleArrives(Vehicle* vehicle){
      return entranceGate->enter(vehicle, parkingBuilding);
    }

    void vehicleExits(Ticket* ticket, ExitGate* exitGate){
      exitGate->exit(ticket, parkingBuilding);
    }
};