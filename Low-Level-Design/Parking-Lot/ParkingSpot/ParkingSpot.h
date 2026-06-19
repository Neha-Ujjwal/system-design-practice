#pragma once
#include <string>

class ParkingSpot {
  private:
    std::string spotId;
    bool free;
  public:
    ParkingSpot(std::string id){
      spotId = id;
      free = true;
    }

    std::string getSpotId() {
      return spotId;
    }

    void occupySpot() {
      free = false;
    }

    void releaseSpot() {
      free = true;
    }

    bool isSpotFree() {
      return free;
    }
};