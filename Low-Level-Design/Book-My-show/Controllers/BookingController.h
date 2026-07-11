#pragma once
#include "../Entities/Booking.h"
#include "../Entities/User.h"
#include "../Entities/Payment.h"
#include "../Entities/Show.h"
#include "../Entities/Theatre.h"
#include "../Entities/Screen.h"
#include "../Entities/Seat.h"

class BookingController {
  private:
    int bookingId;
  public:
    BookingController(){
      bookingId = 0;
    }

    Booking* addBooking(User* user, std::vector<int> seatNumbers, Theatre* theater, Show* show){
      std::vector<ShowSeat*> seats = show->bookSeats(seatNumbers);
      if(seats.empty()){
        throw std::runtime_error("Seats are not available for booking.");
      }

      Payment* payment = new Payment(bookingId, seats.size() * 100, COMPLETED);
      Booking* booking = new Booking(bookingId, seats, user, payment, show);
      bookingId++;
      return booking;
    }
};