#pragma once
#include "Movie.h"
#include "Screen.h"
#include "ShowSeat.h"
#include <unordered_map>
#include <mutex>
#include <algorithm>
class Show {
  private:
    Movie* movie;
    Screen* screen;
    std::string showTime;
    std::string showDate;
    std::string showDuration;
    std::unordered_map<int, ShowSeat*> showSeats;
  public:
    Show(Movie* movie, std::string showTime, Screen* screen, std::string showDate, std::string showDuration){
      this->movie = movie;
      this->showTime = showTime;
      this->screen = screen;
      this->showDate = showDate;
      this->showDuration = showDuration;

      for(Seat* seat: screen->getSeats()){
        showSeats[seat->getSeatNumber()] = new ShowSeat(seat, this);
      }
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

    Screen* getScreen(){
      return screen;
    }

    ShowSeat* getShowSeat(int seatNumber){
      auto it = showSeats.find(seatNumber);
      return it == showSeats.end() ? nullptr : it->second;
    }

    std::vector<ShowSeat*> bookSeats(std::vector<int> seatNumbers){
      std::vector<ShowSeat*> targetSeats;
      std::unordered_map<int, bool> isSeen;

      for(int seatNumber : seatNumbers){
        if(isSeen.find(seatNumber) != isSeen.end()){
          continue;
        }
        ShowSeat* showSeat = getShowSeat(seatNumber);
        if(showSeat == nullptr){
          return {};
        }
        isSeen[seatNumber] = true;
        targetSeats.push_back(showSeat);
      }

      sort(targetSeats.begin(), targetSeats.end(), [](ShowSeat* a, ShowSeat* b){
        return a->getSeatNumber() < b->getSeatNumber();
      });

      std::vector<std::unique_lock<std::mutex>> locks;
      for(ShowSeat* showSeat: targetSeats){
        locks.emplace_back(showSeat->getSeatMutex());
      }

      for(ShowSeat* showSeat: targetSeats){
        if(!showSeat->isAvailable()){
          return {};
        }
      }

      for(ShowSeat* showSeat: targetSeats){
        showSeat->bookSeat();
      }

      return targetSeats;   
    }
};