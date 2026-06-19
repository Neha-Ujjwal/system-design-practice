#pragma once
#include "Gate.h"
#include "../Ticket/Ticket.h"
#include "../Vehicle/Vehicle.h"
#include "../Building/ParkingBuilding.h"

class EntranceGate: public Gate {
  public:
    EntranceGate(int id): Gate(id) {}

    Ticket* enter(Vehicle* vehicle, ParkingBuilding* building){
      return building->allocate(vehicle);
    }
};