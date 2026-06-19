#pragma once
#include <vector>
#include "ParkingSpotManager.h"

class FourWheelerSpotManager: public ParkingSpotManager {
public:
    FourWheelerSpotManager(std::vector<ParkingSpot*> spots, ParkingSpotLookupStrategy* strategy)
        : ParkingSpotManager(spots, strategy) {}
};