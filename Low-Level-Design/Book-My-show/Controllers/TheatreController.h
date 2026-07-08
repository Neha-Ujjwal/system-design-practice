#pragma once
#include <vector>
#include "../Entities/City.h"
#include "../Entities/Theatre.h"

class TheatreController {
  private:
   std::vector<Theatre*> theatres;
  public:
    TheatreController(std::vector<Theatre*> theatres){
      this->theatres = theatres;
    }

    std::vector<Theatre*> getTheatres(){
      return theatres;
    }

    void addTheatres(City* city, Theatre* theatre){
      city->addNewTheatre(theatre);
    }

    void removeTheatres(City* city, Theatre* theatre){
      city->removeTheatre(theatre);
    }

    void showAllAvailableTheatres(City* city, Movie* movie){
      city->showAllAvailableTheatres(movie);
    }

    void showAllAvailableMovies(Theatre* theatre){
      theatre->showAllAvailableMovies();
    }

    void showAllAvailableShows(Theatre* theatre, Movie* movie){
      theatre->showAllAvailableShows(movie);
    }
};