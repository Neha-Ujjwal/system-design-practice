#pragma once
#include <string>

enum class VehicleType {
  TWO_WHEELER,
  FOUR_WHEELER
};

class Vehicle {
  private:
    std::string vehicleNumber;
    VehicleType vehicleType;
  public:
    Vehicle(std::string number, VehicleType type){
      vehicleNumber = number;
      vehicleType = type;
    }

    std::string getVehicleNumber() {
      return vehicleNumber;
    }

    VehicleType getVehicleType() {
      return vehicleType;
    }

    void setVehicleNumber(std::string number){
      vehicleNumber = number;
    }

    void setVehicleType(VehicleType type){
      vehicleType = type;
    }
};
