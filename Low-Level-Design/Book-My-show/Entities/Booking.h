#pragma once
#include <vector>
#include "User.h"
#include "Payment.h"
#include "Show.h"
#include "ShowSeat.h"

class Booking {
  private:
    int bookingId;
    std::vector<ShowSeat*> seats;
    User* user;
    Payment* payment;
    Show *show;
  public:
    Booking(int bookingId, std::vector<ShowSeat*> seats, User* user, Payment* payment, Show* show){
      this->bookingId = bookingId;
      this->seats = seats;
      this->user = user;
      this->payment = payment;
      this->show = show;
    }
    
    int getBookingId(){
      return bookingId;
    }

    int getNumberOfSeats(){
      return seats.size();
    }

    User* getUser(){
      return user;
    }

    Payment* getPayment(){
      return payment;
    }

    Show* getShow(){
      return show;
    }

    void setBookingId(int bookingId){
      this->bookingId = bookingId;
    }

    void setSeats(std::vector<ShowSeat*> seats){
      this->seats = seats;
    }
    
    void setUser(User* user){
      this->user = user;
    }

    void setPayment(Payment* payment){
      this->payment = payment;
    }
    
    void setShow(Show* show){
      this->show = show;
    }

    std::vector<ShowSeat*> getSeats(){
      return seats;
    }

    Theatre* getTheatre(){
      return getShow()->getScreen()->getTheatre();
    }
};