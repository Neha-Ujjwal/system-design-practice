# BookMyShow (Low-Level Design)

A concurrency-safe, object-oriented, and extensible movie-ticket booking system designed in C++. This project centers on the hardest problem in a booking system — **preventing two users from booking the same seat at the same time** — and solves it with per-seat locking, deadlock-free lock ordering, and an all-or-nothing booking transaction. It also models the full domain hierarchy (City → Theatre → Screen → Show → Seat) with a clean separation between physical layout and per-show booking state.

---

## 🏗️ Architecture & Component Hierarchy

The system splits into two conceptual layers — the **physical layer** (what exists) and the **per-show layer** (what's booked) — which is the key to allowing the same physical seat to be booked independently across different shows:

* **`Seat`**: The atomic physical chair — a seat number and a type (silver/gold/platinum). Holds *no* booking status and *no* lock, because a physical seat is shared across every show on its screen.
* **`ShowSeat`**: The per-(seat, show) bookable unit. Wraps a physical `Seat` and owns the `SeatStatus` and the `std::mutex`. This is the object that actually gets locked and booked.
* **`Screen`**: A physical auditorium — a fixed collection of `Seat`s. Reused by many shows. Holds a back-pointer to its owning `Theatre`.
* **`Show`**: A screening — a `Movie` playing on a `Screen` at a time. Owns one `ShowSeat` per physical seat and hosts the atomic `bookSeats()` booking logic.
* **`Theatre`**: A cinema building — holds its `Screen`s (physical rooms) and a schedule of `Show`s (keyed by show id).
* **`City`**: The top of the location hierarchy — holds all its `Theatre`s.
* **`Booking`**: The transaction record — references the `ShowSeat`s reserved, the `User`, the `Payment`, and the `Show`. Derives its theatre through the object graph rather than storing it redundantly.
* **`BookingController`**: Orchestrates the booking workflow — secure seats, take payment, create the record.
* **`TheatreController`**: The browse/admin facade over the location hierarchy.

---

## 🛠️ Design Patterns & Principles Applied

### 1. Single Responsibility Principle (SRP)
Each class has one well-defined job. `Show::bookSeats` is the only place that performs the atomic booking transaction; `ShowSeat` is a passive lockable data holder; `Booking` is an immutable-ish record with no booking logic of its own; the controllers sequence the workflow without leaking concurrency concerns.

### 2. Separation of Physical vs. Per-Show State
Booking status and the lock live on `ShowSeat` (per screening), never on the physical `Seat`. This is what allows seat 7 at 6:00 PM and seat 7 at 9:00 PM — the *same physical chair* — to be booked independently.

### 3. Encapsulation & Derived State
A `Booking` does not store a redundant `Theatre*`. Instead it derives its theatre by walking the object graph (`Booking → Show → Screen → Theatre`), guaranteeing a single source of truth that can never drift out of sync.

### 4. Deadlock-Free Concurrency
The booking transaction acquires all per-seat locks in a **consistent global order** (sorted by seat number), which makes the circular wait that causes deadlock impossible. Duplicate seat requests are de-duplicated first to avoid self-deadlock on a non-recursive mutex.

---

## 🔒 The Booking Transaction (Concurrency Core)

`Show::bookSeats` guarantees a booking is **atomic** (all-or-nothing) and **thread-safe** via five phases:

1. **Resolve & dedupe** — map seat numbers to `ShowSeat*`, dropping duplicates so each mutex appears at most once (prevents self-deadlock).
2. **Sort** — order the seats by seat number so every thread locks in the same order (prevents deadlock).
3. **Lock all** — acquire every seat's mutex, in sorted order, into a RAII lock container.
4. **Check all** — while holding every lock, verify all seats are available; if any is taken, abort (locks auto-release).
5. **Commit all** — mark every seat `BOOKED`, then return; locks release automatically on scope exit.

The check and the commit both happen *while all locks are held*, which is what makes "check-then-act" atomic and closes the double-booking race.

---

## 🚀 End-to-End Execution Simulation

The simulation driver builds a full hierarchy (a city with a theatre, two screens, three shows), then exercises a successful booking, a conflicting booking, per-show seat independence, theatre derivation from a booking, and a 100-thread race for the same seats.

### Compilation & Execution Command

Run this command inside your `Book-My-Show` workspace directory to build and run the simulation. The `-pthread` flag is **required** — the concurrency test uses `std::thread`, and without it the program compiles but crashes at runtime:

```bash
g++ -std=c++17 -pthread main.cpp -o bms && ./bms
```

### Execution Log Output

```text
========== BookMyShow LLD ==========

City Bengaluru -> PVR Forum Mall (2 screens)

[1] Alice books {3,4,5} for Inception 6PM
  Booking #0 | Alice | Inception @ PVR Forum Mall (Audi 1) | 6:00 PM | seats 3 4 5 | Rs.300

[2] Bob tries {5,6} for Inception 6PM (5 is taken)
  rejected: Seats are not available for booking.

[3] Bob books {5} for Inception 9PM (different show, same screen)
  Booking #1 | Bob | Inception @ PVR Forum Mall (Audi 1) | 9:00 PM | seats 5 | Rs.100

[4] Which show, in which theatre did Alice book?
  Show:    6:00 PM Inception
  Theatre: PVR Forum Mall (derived: Booking->Show->Screen->Theatre)

[5] 100 threads race for {7,8} on Inception 6PM
  winners: 1 (expected exactly 1)

========== done ==========
```

The critical line is `[5] winners: 1` — 100 threads raced for the same two seats and exactly one succeeded, proving no double-booking under real contention.

---

## 📂 Directory Structure

```text
Book-My-Show/
├── main.cpp                        # Simulation Entry Point
├── Entities/
│   ├── Seat.h                      # Physical chair (number + type)
│   ├── ShowSeat.h                  # Per-show bookable unit (status + mutex)
│   ├── Screen.h                    # Physical auditorium + Theatre back-pointer
│   ├── Show.h                      # Screening + atomic bookSeats() logic
│   ├── Movie.h                     # Movie model
│   ├── Theatre.h                   # Cinema building (screens + schedule)
│   ├── City.h                      # Location hierarchy root
│   ├── Booking.h                   # Transaction record + derived getTheatre()
│   ├── Payment.h                   # Payment record & status enum
│   └── User.h                      # User model
└── Controllers/
    ├── BookingController.h         # Booking workflow orchestrator
    └── TheatreController.h         # Browse / admin facade
```

---

## 🧭 Known Simplifications (Extension Points)

These are deliberate LLD-scope simplifications rather than defects:

* **No hold-then-confirm flow** — booking goes straight `AVAILABLE → BOOKED`; a real system would use the `RESERVED` state to hold seats during payment and release them on failure/timeout (the enum and setters already support this).
* **Flat pricing** — every seat is Rs. 100 regardless of `SeatType`; tiered pricing (silver/gold/platinum) is a natural next step.
* **Payment always succeeds** — hardcoded `COMPLETED`; the `PENDING → COMPLETED/FAILED` path with seat release on failure is the realistic extension.
* **No cancellation path yet** — `Booking` holds the `ShowSeat`s and `User`, so cancellation can be built on top.
* **Raw pointers** — objects are created with `new` and not deleted; `std::shared_ptr`/`unique_ptr` would manage lifetime in production.