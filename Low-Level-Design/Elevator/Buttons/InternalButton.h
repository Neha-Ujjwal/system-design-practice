#pragma once

class InternalButton {
  private:
    int floor;
  public:
    InternalButton(int f){
      floor = f;
    }

    //getter and setter methods
    void setFloor(int floor){
      this->floor = floor;
    }

    int getFloor(){
      return floor;
    }
};