#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "../ParkingLevel/ParkingLevel.h"
#include "../Ticket/Ticket.h"

class ParkingBuilding {
  private:
    std::vector<ParkingLevel*> parkingLevels;
  public:
    ParkingBuilding(std::vector<ParkingLevel*> levels){
      parkingLevels = levels;
    }

    std::vector<ParkingLevel*> getParkingLevels() {
      return parkingLevels;
    }

    Ticket* allocate(Vehicle* vehicle){
      VehicleType type = vehicle->getVehicleType();

      for (int i = 0; i < parkingLevels.size();i++){
        if(parkingLevels[i]->hasAvailability(type)){
          ParkingSpot* spot = parkingLevels[i]->parkVehicle(type);
          if(spot != nullptr){
            Ticket* ticket = new Ticket(vehicle, spot, parkingLevels[i]);
            std::cout << "Allocated spot " << spot->getSpotId() << " for vehicle " << vehicle->getVehicleNumber() << std::endl;
            return ticket;
          }
        }
      }
      throw std::runtime_error("No available parking spot for vehicle type");
    }

    void release(Ticket* ticket){
      ParkingLevel* level = ticket->getParkingLevel();
      ParkingSpot* spot = ticket->getParkingSpot();
      VehicleType type = ticket->getVehicle()->getVehicleType();

      level->unparkVehicle(type, spot);
      std::cout << "Released spot " << spot->getSpotId() << " for vehicle " << ticket->getVehicle()->getVehicleNumber() << std::endl;
    }
};