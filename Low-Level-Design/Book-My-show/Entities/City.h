#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Theatre.h"
#include "Movie.h"

class City {
  private:
    std::string name;
    std::vector<Theatre*> theatres;
  public:
    City(std::string name, std::vector<Theatre*> theatres){
      this->name = name;
      this->theatres = theatres;
    }

    std::string getName(){
      return name;
    }

    std::vector<Theatre*> getTheatres(){
      return theatres;
    }

    void addNewTheatre(Theatre* theatre){
      theatres.push_back(theatre);
    }

    void removeTheatre(Theatre* theatre){
      theatres.erase(std::remove(theatres.begin(), theatres.end(), theatre), theatres.end());
    }

    void showAllAvailableTheatres(Movie* movie){
      for(Theatre* theatre : theatres){
        if(theatre->showAvailableShows(movie)){
          std::cout<<"Theatre: " << theatre->getTheatreName() << " is available for the movie: " << movie->getMovieName() << std::endl;
        }
      }
    }

    void showAllAvailableShows(Theatre* theatre, Movie* movie){
      theatre->showAllAvailableShows(movie);
    }
};