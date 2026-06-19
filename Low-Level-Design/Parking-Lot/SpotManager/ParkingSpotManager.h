#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "../ParkingSpot/ParkingSpot.h"
#include "../LookupStrategy/ParkingSpotLookupStrategy.h"

class ParkingSpotManager {
  private:
    std::vector<ParkingSpot*> parkingSpots;
    ParkingSpotLookupStrategy* lookupStrategy;

    std::mutex lock;
  public: 
    ParkingSpotManager(std::vector<ParkingSpot*> spots, ParkingSpotLookupStrategy* strategy) {
      parkingSpots = spots;
      lookupStrategy = strategy;
    }

    ParkingSpot* park() {
      lock.lock();

      ParkingSpot* spot = lookupStrategy->findSpot(parkingSpots);
      if (spot == nullptr) {
          lock.unlock();
          return nullptr;
      }

      spot->occupySpot();
      lock.unlock();
      return spot;
    }

    void unparkSpot(ParkingSpot* spot){
      lock.lock();
      if(spot!=nullptr){
        spot->releaseSpot();
      }
      lock.unlock();
    }

    bool hasFreeSpot(){
      lock.lock();

      for(int i=0; i<parkingSpots.size(); i++){
        if(parkingSpots[i]->isSpotFree()){
          lock.unlock();
          return true;
        }
      }
      lock.unlock();
      return false;
    }
};