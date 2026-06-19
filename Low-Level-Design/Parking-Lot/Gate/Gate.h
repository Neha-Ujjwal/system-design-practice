#pragma once

class Gate {
  private:
    int gateId;
  public:
    Gate(int id){
      gateId = id;  
    }
    int getGateId() {
      return gateId;
    }
};