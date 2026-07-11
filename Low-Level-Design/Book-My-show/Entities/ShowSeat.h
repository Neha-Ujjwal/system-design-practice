#pragma once
#include "Seat.h"
#include <mutex>
class Show;

class ShowSeat {
  private:
    Seat* seat;
    Show *show;
    SeatStatus seatStatus;
    std::mutex seatMutex;
  public:
    ShowSeat(Seat* seat, Show* show){
      this->seat = seat;
      this->show = show;
      this->seatStatus = AVAILABLE;
    }
    
    Seat* getSeat(){
      return seat;
    }

    Show* getShow(){
      return show;
    }

    SeatStatus getSeatStatus(){
      return seatStatus;
    }

    void setSeatStatus(SeatStatus seatStatus){
      this->seatStatus = seatStatus;
    }

    std::mutex& getSeatMutex(){
      return seatMutex;
    }

    int getSeatNumber(){
      return seat->getSeatNumber();
    }

    bool isAvailable(){
      return seatStatus == AVAILABLE;
    }

    void bookSeat(){
      seatStatus = BOOKED;
    }
};