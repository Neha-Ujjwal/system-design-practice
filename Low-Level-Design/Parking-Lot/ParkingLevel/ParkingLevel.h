#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "../SpotManager/ParkingSpotManager.h"
#include "../Vehicle/Vehicle.h"

class ParkingLevel {
  private:
    int levelNumber;
    std::unordered_map<VehicleType, ParkingSpotManager*> spotManagers;
  public:
    ParkingLevel(int number, std::unordered_map<VehicleType, ParkingSpotManager*> managers){
      levelNumber = number;
      spotManagers = managers;
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