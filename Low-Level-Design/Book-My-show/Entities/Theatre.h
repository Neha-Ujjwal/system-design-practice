#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "Screen.h"
#include "Show.h"
#include "Movie.h"
#include "City.h"

class Theatre {
  private:
    int theatreId;
    std::string theatreName;
    std::vector<Screen*> screens;
    std::unordered_map<std::string, Show*> shows;
  public:
    Theatre(int id, std::string name, std::vector<Screen*> screens, std::unordered_map<std::string, Show*> shows){
      this->theatreId = id;
      this->theatreName = name;
      this->screens = screens;
      this->shows = shows;
    }

    int getTheatreId(){
      return theatreId;
    }

    std::string getTheatreName(){
      return theatreName;
    }

    std::vector<Screen*> getScreens(){
      return screens;
    }

    bool isScreenAvailable(int screenId){
      for(Screen* screen : screens){
        if(screen->getScreenId() == screenId){
          return true;
        }
      }
      return false;
    }

    bool isSeatAvailable(int screenId, int seatNumber){
      for(Screen* screen : screens){
        if(screen->getScreenId() == screenId){
          return screen->isSeatAvailable(seatNumber);
        }
      }
      return false;
    }

    bool isShowAvailable(Movie* movie){
      for(auto& entry : shows){
        Show* show = entry.second;
        if(show->getMovie()->getMovieName() == movie->getMovieName()){
          std::cout << show->getShowTime() << " " << show->getShowDate() << " " << show->getShowDuration() << std::endl;
        }
      }
      return true;
    }

    void showAllAvailableMovies(){
      for(auto& entry : shows){
        Show* show = entry.second;
        std::cout << "Movie: " << show->getMovie()->getMovieName() << " is available at " << getTheatreName() << std::endl;
      }
    }

    void showAllAvailableShows(Movie* movie){
      for(auto& entry : shows){
        Show* show = entry.second;
        if(show->getMovie()->getMovieName() == movie->getMovieName()){
          std::cout << "Show: " << show->getShowTime() << " " << show->getShowDate() << " " << show->getShowDuration() << " is available at " << getTheatreName() << std::endl;
        }
      }
    }
};