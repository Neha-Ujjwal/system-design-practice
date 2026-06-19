#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "ParkingSpotManager.h"
#include "../vehicle/Vehicle.h"

class ParkingLevel {
  private:
    int levelNumber;
    std::unordered_map<VehicleType, ParkingSpotManager*> spotManagers;
  public:
    ParkingLevel(int number, VehicleType type, std::vector<ParkingSpotManager*> managers){
      levelNumber = number;
      spotManagers[type] = managers[0];
    }

    bool hasAvailability(VehicleType type){
      if(spotManagers.find(type) == spotManagers.end()){
        throw std::runtime_error("No spot manager found for vehicle type");
      }
      return spotManagers[type]->hasFreeSpot();
    }

    ParkingSpot* parkVehicle(VehicleType type){
      if(spotManagers.find(type) == spotManagers.end()){
        throw std::runtime_error("No spot manager found for vehicle type");
      }
      return spotManagers[type]->park();
    }

    void unparkVehicle(VehicleType type, ParkingSpot* spot){
      if(spotManagers.find(type) == spotManagers.end()){
        throw std::runtime_error("No spot manager found for vehicle type");
      }
      spotManagers[type]->unparkSpot(spot);
    }
};