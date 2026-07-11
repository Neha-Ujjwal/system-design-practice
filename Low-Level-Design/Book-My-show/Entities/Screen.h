#pragma once
#include <string>
#include <vector>
#include "Seat.h"
class Theatre;

class Screen {
  private:
    int screenId;
    std::string screenName;
    std::vector<Seat*> seats;
    Theatre* theatre = nullptr; 
  public:
    Screen(int id, std::string name, std::vector<Seat*> seats){
      this->screenId = id;
      this->screenName = name;
      this->seats = seats;
    }

    std::vector<Seat*> getSeats(){
      return seats;
    }

    int getScreenId(){
      return screenId;
    }

    std::string getScreenName(){
      return screenName;
    }

    void setTheatre(Theatre* t){
      theatre = t;
    }
       
    Theatre* getTheatre(){ return theatre; }      
};