#pragma once

enum SeatType {
  SILVER,
  GOLD,
  PLATINUM
};

enum SeatStatus {
  AVAILABLE,
  BOOKED,
  RESERVED
};

class Seat {
  private:
    int seatNumber;
    SeatType seatType;
    SeatStatus seatStatus;
  public:
    Seat(int n, SeatType t){
      seatNumber = n;
      seatType = t;
    }

    int getSeatNumber(){
      return seatNumber;
    }

    SeatType getSeatType(){
      return seatType;
    }

    bool isAvailable(){
      return isAvailable;
    }
};