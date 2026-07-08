#pragma once 
#include <string>

class Movie {
  private:
    std::string movieName;
  public:
    Movie(std::string movieName){
      this->movieName = movieName;
    }

    std::string getMovieName(){
      return movieName;
    }

    void setMovieName(std::string movieName){
      this->movieName = movieName;
    }
};