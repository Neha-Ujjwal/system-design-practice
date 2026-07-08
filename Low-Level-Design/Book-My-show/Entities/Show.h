#pragma once
#include "Movie.h"

class Show {
  private:
    Movie* movie;
    std::string showTime;
    std::string showDate;
    std::string showDuration;
  public:
    Show(Movie* movie, std::string showTime, std::string showDate, std::string showDuration){
      this->movie = movie;
      this->showTime = showTime;
      this->showDate = showDate;
      this->showDuration = showDuration;
    }
    
    std::string getShowTime(){
      return showTime;
    }

    std::string getShowDate(){
      return showDate;
    }

    std::string getShowDuration(){
      return showDuration;
    }

    Movie* getMovie (){
      return movie;
    }
};