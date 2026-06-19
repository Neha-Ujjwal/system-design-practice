#pragma once
#include <string>
#include "../ParkingSpot/ParkingSpot.h"
#include <vector>

class ParkingSpotLookupStrategy {
 public:
  virtual ~ParkingSpotLookupStrategy() = default;

  virtual ParkingSpot* findSpot(std::vector<ParkingSpot*> parkingSpots) = 0;
};