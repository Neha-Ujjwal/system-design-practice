#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "Screen.h"
#include "Show.h"
#include "Movie.h"

class Theatre {
  private:
    int theatreId;
    std::string theatreName;
    std::vector<Screen*> screens;
    std::unordered_map<int, Show*> shows;
  public:
    Theatre(int id, std::string name, std::vector<Screen*> screens, std::unordered_map<int, Show*> shows){
      this->theatreId = id;
      this->theatreName = name;
      this->screens = screens;
      this->shows = shows;

      for(Screen* screen : screens){
        screen->setTheatre(this);
      }
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

    bool showAvailableShows(Movie* movie){
      for(auto& entry : shows){
        Show* show = entry.second;
        if(show->getMovie()->getMovieName() == movie->getMovieName()){
          std::cout << show->getShowTime() << " " << show->getShowDate() << " " << show->getShowDuration() << std::endl;
          return true;
        }
      }
      return false;
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

    Theatre* getTheatre(Show* show){
      return show->getScreen()->getTheatre();
    }
};