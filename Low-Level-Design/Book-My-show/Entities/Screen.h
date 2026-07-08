#pragma once
#include <string>
#include <vector>
#include "Seat.h"

class Screen {
  private:
    int screenId;
    std::string screenName;
    std::vector<Seat*> seats;
  public:
    Screen(int id, std::string name, std::vector<Seat*> seats){
      this->screenId = id;
      this->screenName = name;
      this->seats = seats;
    }

    std::vector<Seat*> getSeats(){
      return seats;
    }

    bool isSeatAvailable(int seatNumber){
      for(Seat* seat : seats){
        if(seat->getSeatNumber() == seatNumber){
          return seat->isAvailable();
        }
      }
      return false;
    }

    int getScreenId(){
      return screenId;
    }

    std::string getScreenName(){
      return screenName;
    }
};