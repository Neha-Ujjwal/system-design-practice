#pragma once
#include "ParkingSpot.h"
#include "ParkingLevel.h"
#include "vehicle/Vehicle.h"

class Ticket{
  private:
    Vehicle* vehicle;
    ParkingSpot* parkingSpot;
    ParkingLevel* parkingLevel;
  public:
    Ticket(Vehicle* v, ParkingSpot* spot, ParkingLevel* level){
      vehicle = v;
      parkingSpot = spot;
      parkingLevel = level;
    }

    Vehicle* getVehicle() {
      return vehicle;
    }

    ParkingSpot* getParkingSpot() {
      return parkingSpot;
    }

    ParkingLevel* getParkingLevel() {
      return parkingLevel;
    }
};