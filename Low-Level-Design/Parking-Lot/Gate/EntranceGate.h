#pragma once
#include "Gate.h"
#include "../ticket/Ticket.h"
#include "../vehicle/Vehicle.h"
#include "../Building/ParkingBuilding.h"

class EntranceGate: public Gate {
  public:
    EntranceGate(int id): Gate(id) {}

    Ticket* enter(Vehicle* vehicle, ParkingBuilding* building){
      return building->allocate(vehicle);
    }
};