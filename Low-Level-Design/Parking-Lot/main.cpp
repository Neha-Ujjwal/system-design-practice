#include <iostream>
#include "ParkingLot.h"
#include "Vehicle/Vehicle.h"
#include "SpotManager/ParkingSpotManager.h"
#include "SpotManager/TwoWheelerSpotManager.h"
#include "SpotManager/FourWheelerSpotManager.h"
#include "LookupStrategy/RandomLookupStrategy.h"
using namespace std;

int main() {
  ParkingSpotLookupStrategy* strategy = new RandomLookupStrategy();

  Vehicle* twoWheeler1 = new Vehicle("TW123", VehicleType::TWO_WHEELER);
  Vehicle* twoWheeler2 = new Vehicle("TW456", VehicleType::TWO_WHEELER);
  Vehicle* twoWheeler3 = new Vehicle("TW789", VehicleType::TWO_WHEELER);

  Vehicle* fourWheeler1 = new Vehicle("FW123", VehicleType::FOUR_WHEELER);

  ParkingSpotManager* twoWheelerManager = new TwoWheelerSpotManager({new ParkingSpot("L1T1"), new ParkingSpot("L1T2")}, strategy);
  ParkingSpotManager* fourWheelerManager = new FourWheelerSpotManager({new ParkingSpot("L1F1"), new ParkingSpot("L1F2")}, strategy);

  ParkingSpotManager* twoWheelerManager2 = new TwoWheelerSpotManager({new ParkingSpot("L2T1"), new ParkingSpot("L2T2")}, strategy);

  unordered_map<VehicleType, ParkingSpotManager*> level1Managers = {
      {VehicleType::TWO_WHEELER, twoWheelerManager},
      {VehicleType::FOUR_WHEELER, fourWheelerManager}
  };

  unordered_map<VehicleType, ParkingSpotManager*> level2Managers = {
      {VehicleType::TWO_WHEELER, twoWheelerManager2}
  };
  ParkingLevel* level1 = new ParkingLevel(1, level1Managers);
  ParkingLevel* level2 = new ParkingLevel(2, level2Managers);

  ParkingBuilding* building = new ParkingBuilding({level1, level2});

  EntranceGate* entranceGate = new EntranceGate(1);
  ExitGate* exitGate = new ExitGate(1, 100);

  ParkingLot* parkingLot = new ParkingLot(entranceGate, exitGate, building);

 cout << "\n=== SIMULATION: VEHICLES ARRIVING ===" << endl;
  Ticket* ticket1 = parkingLot->vehicleArrives(twoWheeler1);
  Ticket* ticket2 = parkingLot->vehicleArrives(twoWheeler2);
  Ticket *ticket3 = parkingLot->vehicleArrives(twoWheeler3);
  Ticket *ticket4 = parkingLot->vehicleArrives(fourWheeler1);

  cout << "\n=== SIMULATION: VEHICLES DEPARTING ===" << endl;
  if (ticket1 != nullptr) parkingLot->vehicleExits(ticket1, exitGate);
  if (ticket2 != nullptr) parkingLot->vehicleExits(ticket2, exitGate);
  if (ticket3 != nullptr) parkingLot->vehicleExits(ticket3, exitGate);
  if (ticket4 != nullptr) parkingLot->vehicleExits(ticket4, exitGate);

  // 7. Clean up Heap Allocations to avoid memory leaks
  delete parkingLot;
  delete entranceGate;
  delete exitGate;
  delete building;
  delete level1;
  delete level2;
  delete twoWheelerManager; delete fourWheelerManager; delete twoWheelerManager2;
  delete twoWheeler1; delete twoWheeler2; delete twoWheeler3; delete fourWheeler1;
  delete strategy;
  if (ticket1) delete ticket1;
  if (ticket2) delete ticket2;
  if (ticket3) delete ticket3;
  if (ticket4) delete ticket4;

  cout << "\n=== SIMULATION TURNED OFF CLEANLY ===" << endl;
  return 0;
};