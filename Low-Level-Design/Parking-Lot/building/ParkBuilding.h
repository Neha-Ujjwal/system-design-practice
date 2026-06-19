#pragma once
#include <vector>
#include "ParkingLevel.h"

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
};