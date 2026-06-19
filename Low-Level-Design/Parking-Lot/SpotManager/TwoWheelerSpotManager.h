#pragma once
#include <vector>
#include "../SpotManager/ParkingSpotManager.h"

class TwoWheelerSpotManager: public ParkingSpotManager {
public:
    TwoWheelerSpotManager(std::vector<ParkingSpot*> spots, ParkingSpotLookupStrategy* strategy)
        : ParkingSpotManager(spots, strategy) {}
};