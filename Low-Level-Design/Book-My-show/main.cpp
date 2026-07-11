#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <atomic>
#include "Controllers/BookingController.h"
#include "Controllers/TheatreController.h"

Screen* makeScreen(int id, const std::string& name, int seatCount) {
    std::vector<Seat*> seats;
    for (int i = 1; i <= seatCount; i++) seats.push_back(new Seat(i, SILVER));
    return new Screen(id, name, seats);
}

void printBooking(Booking* b) {
    Show* show = b->getShow();
    std::cout << "  Booking #" << b->getBookingId()
              << " | " << b->getUser()->getName()
              << " | " << show->getMovie()->getMovieName()
              << " @ " << b->getTheatre()->getTheatreName()
              << " (" << show->getScreen()->getScreenName() << ")"
              << " | " << show->getShowTime()
              << " | seats ";
    for (ShowSeat* ss : b->getSeats()) std::cout << ss->getSeatNumber() << " ";
    std::cout << "| Rs." << b->getPayment()->getPaymentAmount() << "\n";
}

int main() {
    std::cout << "========== BookMyShow LLD ==========\n\n";

    // ---------- build the world (bottom-up) ----------
    Movie* inception = new Movie("Inception");
    Movie* interstellar = new Movie("Interstellar");

    Screen* audi1 = makeScreen(1, "Audi 1", 10);
    Screen* audi2 = makeScreen(2, "Audi 2", 10);

    // shows: a movie on a screen at a time
    Show* incept6 = new Show(inception,    "6:00 PM", audi1, "2026-07-11", "2h28m");
    Show* incept9 = new Show(inception,    "9:00 PM", audi1, "2026-07-11", "2h28m");
    Show* inter7  = new Show(interstellar, "7:00 PM", audi2, "2026-07-11", "2h49m");

    // theatre: holds screens + schedule (keyed by show id). Ctor wires screen->theatre.
    std::unordered_map<int, Show*> schedule;
    schedule[101] = incept6;
    schedule[102] = incept9;
    schedule[103] = inter7;
    Theatre* pvr = new Theatre(1, "PVR Forum Mall", {audi1, audi2}, schedule);

    // city + controllers
    City* bengaluru = new City("Bengaluru", {pvr});
    TheatreController theatreController({pvr});
    BookingController bookingController;

    User* alice = new User(1, "Alice");
    User* bob   = new User(2, "Bob");

    std::cout << "City " << bengaluru->getName()
              << " -> " << pvr->getTheatreName()
              << " (" << pvr->getScreens().size() << " screens)\n\n";

    // ---------- 1. successful booking ----------
    std::cout << "[1] Alice books {3,4,5} for Inception 6PM\n";
    Booking* b1 = bookingController.addBooking(alice, {3,4,5}, pvr, incept6);
    printBooking(b1);

    // ---------- 2. conflict: seat 5 already taken on the 6PM show ----------
    std::cout << "\n[2] Bob tries {5,6} for Inception 6PM (5 is taken)\n";
    try {
        bookingController.addBooking(bob, {5,6}, pvr, incept6);
        std::cout << "  booking succeeded (unexpected!)\n";
    } catch (const std::exception& e) {
        std::cout << "  rejected: " << e.what() << "\n";
    }

    // ---------- 3. per-show independence: seat 5 free on the 9PM show ----------
    std::cout << "\n[3] Bob books {5} for Inception 9PM (different show, same screen)\n";
    Booking* b3 = bookingController.addBooking(bob, {5}, pvr, incept9);
    printBooking(b3);

    // ---------- 4. derive theatre from a booking ----------
    std::cout << "\n[4] Which show, in which theatre did Alice book?\n";
    std::cout << "  Show:    " << b1->getShow()->getShowTime()
              << " " << b1->getShow()->getMovie()->getMovieName() << "\n";
    std::cout << "  Theatre: " << b1->getTheatre()->getTheatreName()
              << " (derived: Booking->Show->Screen->Theatre)\n";

    // ---------- 5. concurrency: 100 threads race for the same seats ----------
    std::cout << "\n[5] 100 threads race for {7,8} on Inception 6PM\n";
    std::atomic<int> winners{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; i++)
        threads.emplace_back([&] {
            try { bookingController.addBooking(alice, {8,7}, pvr, incept6); winners++; }
            catch (const std::exception&) {}
        });
    for (auto& t : threads) t.join();
    std::cout << "  winners: " << winners.load() << " (expected exactly 1)\n";

    std::cout << "\n========== done ==========\n";
    return 0;
}