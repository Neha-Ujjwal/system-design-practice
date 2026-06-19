#pragma once
#include "ParkingSpotLookupStrategy.h"

class RandomLookupStrategy: public ParkingSpotLookupStrategy {
  public:
    ParkingSpot* findSpot(std::vector<ParkingSpot*> parkingSpots) override {
      for (int i = 0; i < parkingSpots.size();i++){
        if(parkingSpots[i]->isSpotFree()){
          return parkingSpots[i];
        }
      }
      return nullptr;
    }
};