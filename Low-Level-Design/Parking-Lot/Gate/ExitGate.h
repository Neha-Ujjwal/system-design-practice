#pragma once
#include "Gate.h"
#include "../Ticket/Ticket.h"
#include "../Vehicle/Vehicle.h"
#include "../Building/ParkingBuilding.h"

class ExitGate: public Gate {
  private:
    int chargeAmount;
  
    double calculateAmount(Ticket* ticket){
      return chargeAmount  ; // Placeholder for actual amount calculation logic based on parking duration and vehicle type
    }
  public:
    ExitGate(int id, int chargeAmount): Gate(id), chargeAmount(chargeAmount) {}

    void exit(Ticket* ticket, ParkingBuilding* building){
      double amount = calculateAmount(ticket);

      std::cout << "Vehicle " << ticket->getVehicle()->getVehicleNumber() << " is exiting. Charge amount: " << amount << std::endl;

      building->release(ticket);

      std::cout << "Vehicle " << ticket->getVehicle()->getVehicleNumber() << " has exited." << std::endl;
    }
};