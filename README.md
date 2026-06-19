# Multi-Level Parking Lot System (Low-Level Design)

A clean, object-oriented, and thread-safe implementation of a Multi-Level Parking Lot System designed in C++. This project focuses on solid software engineering principles, employing design patterns like the **Strategy Pattern** for spot allocation and managing resources dynamically across multi-tier structures.

---

## 🏗️ Architecture & Component Hierarchy

The system follows a scalable composition layout to distribute responsibilities clearly across components:

* **`Vehicle`**: Represents incoming units tracking a distinct license number and `VehicleType` (`TWO_WHEELER`, `FOUR_WHEELER`).
* **`ParkingSpot`**: The atomic unit tracking availability (`free`/`occupied`) and raw identifiers.
* **`ParkingSpotManager`**: Handles a group of spots thread-safely via `std::mutex` locks and delegates search lookups to a dedicated strategy.
* **`ParkingLevel`**: Houses a mapping (`std::unordered_map`) of vehicle types to their respective managers, allowing a single floor to host mixed parking types seamlessly.
* **`ParkingBuilding`**: Orchestrates levels, loops over floors for dynamic allocations, and issues tracking logs.
* **`ParkingLot`**: The top-level facade interacting with `EntranceGate` and `ExitGate` to issue/process `Ticket` lifecycles.

---

## 🛠️ Design Patterns Applied

### 1. Strategy Pattern

The spot selection mechanism isolates allocation logic from the manager runtime. The interface `ParkingSpotLookupStrategy` exposes a pure virtual function (`= 0`) implemented by concrete algorithms like `RandomLookupStrategy`. This allows developers to add custom algorithms (e.g., Nearest Spot First, VIP Prioritized) without modifying existing class implementations (**Open-Closed Principle**).

### 2. Thread Safety / Concurrency

Every mutable step during runtime parking and unparking allocations is protected using `std::mutex` blocks inside the `ParkingSpotManager`. This prevents critical data race conditions if multiple entrance/exit gates execute transactions simultaneously.

---

## 🚀 End-to-End Execution Simulation

The simulation driver (`main.cpp`) initializes a multi-level building supporting concurrent spot managers, triggers multiple vehicle arrivals (handling overflow situations by dynamically climbing floors), calculates fees at exit parameters, and cleans up heap memory perfectly.

### Compilation & Execution Command

Run this command inside the `Parking-Lot` workspace directory to build and run your application via the C++17 configuration standard:

```bash
clang++ -std=c++17 main.cpp -o parking_simulation && ./parking_simulation

```

### Execution Log Output

```text
=== SIMULATION: VEHICLES ARRIVING ===
Allocated spot L1T1 for vehicle TW123
Allocated spot L1T2 for vehicle TW456
Allocated spot L2T1 for vehicle TW789
Allocated spot L1F1 for vehicle FW123

=== SIMULATION: VEHICLES DEPARTING ===
Vehicle TW123 is exiting. Charge amount: 100
Released spot L1T1 for vehicle TW123
Vehicle TW123 has exited.
Vehicle TW456 is exiting. Charge amount: 100
Released spot L1T2 for vehicle TW456
Vehicle TW456 has exited.
Vehicle TW789 is exiting. Charge amount: 100
Released spot L2T1 for vehicle TW789
Vehicle TW789 has exited.
Vehicle FW123 is exiting. Charge amount: 100
Released spot L1F1 for vehicle FW123
Vehicle FW123 has exited.

=== SIMULATION TURNED OFF CLEANLY ===

```

---

## 📂 Directory Structure

```text
Parking-Lot/
├── main.cpp                     # Simulation Driver Routine
├── ParkingLot.h                 # Orchestration System Facade
├── Building/
│   └── ParkingBuilding.h        # Multi-level Collection Wrapper
├── ParkingLevel/
│   └── ParkingLevel.h           # Multi-Manager Floor Mapping Layer
├── ParkingSpot/
│   └── ParkingSpot.h            # Atomic Spot Entity
├── SpotManager/
│   ├── ParkingSpotManager.h     # Thread-Safe Manager Parent
│   ├── TwoWheelerSpotManager.h  # Concrete Manager Subclass
│   └── FourWheelerSpotManager.h # Concrete Manager Subclass
├── LookupStrategy/
│   ├── ParkingSpotLookupStrategy.h # Strategy Contract Interface
│   └── RandomLookupStrategy.h   # Linear/Random Allocation Logic
├── Gate/
│   ├── EntranceGate.h           # Inbound allocation trigger
│   └── ExitGate.h               # Cost processing & spot release
├── Ticket/
│   └── Ticket.h                 # Transient transactional mapping
└── Vehicle/
    └── Vehicle.h                # Vehicle state and Enums

```