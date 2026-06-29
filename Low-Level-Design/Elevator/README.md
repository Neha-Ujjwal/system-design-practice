# Multi-Elevator Control System (Low-Level Design)

A production-grade, object-oriented simulation of a multi-elevator management system written in modern, memory-safe **C++17**. The system leverages advanced scheduling heuristics to optimize passenger wait times across complex building environments.

---

## 🛠️ System Architecture & Design Patterns

The project splits concerns cleanly using the **Single Responsibility Principle (SRP)** and decouples request allocation from the physical execution engines:

* **Strategy Pattern (`DispatchStrategy`)**: Decouples the request-allocation algorithm from the core system. You can hot-swap how elevators are chosen at runtime (e.g., switching from physical proximity calculations to scheduling heuristics) without modifying the central system orchestrator.
* **The LOOK/SCAN Algorithm (`ElevatorController`)**: Avoids naive starvation by maintaining directional sweeps. Upward requests are tracked in a Min-Priority Queue (`std::priority_queue`), and downward requests are tracked in a Max-Priority Queue, maximizing operational throughput.
* **Asynchronous Engine Hand-off**: External calls place requests onto a controller's internal heaps immediately, freeing the central system loop to remain responsive to concurrent passenger requests.

---

## 📂 Project Directory Structure

```text
├── Enums.h                    # Core system type safety definitions (Direction, ElevatorState)
├── ElevatorCar.h              # State model for physical elevator attributes (Floor, ID, State)
├── ElevatorController.h       # LOOK/SCAN scheduling engine utilizing internal min/max heaps
├── DispatchStrategy.h         # Abstract strategy interface for structural elevator selection
├── NearestElevatorStrategy.h  # Heuristic picker based on directional alignment and proximity
├── OddEvenElevatorStrategy.h  # Partitioning strategy handling specific floor/ID parities
├── ElevatorSystem.h           # System Facade orchestrating external hall button dispatches
└── main.cpp                   # Simulation runner initializing and processing workloads

```

---

## 🚀 Compilation & Execution Guide

Ensure you have a modern C++ compiler installed (such as `g++` or `clang`).

### 1. Compile the Project

Build the source modules using the C++17 standard flag to handle standard libraries correctly:

```bash
g++ -std=c++17 main.cpp -o elevator_simulation

```

### 2. Execute the Simulation

Run the generated binary executable directly from your terminal:

```bash
./elevator_simulation

```

---

## 📊 Sample Simulation Output

When executed, the console displays deterministic traces of the routing decisions and movement steps:

```text
=== Grouping and Allocating Hall Requests ===
Elevator 2 queued UP request for Floor 3.
Elevator 2 queued UP request for Floor 7.
Elevator 1 queued DOWN request for Floor 1.

=== Starting Elevator Engine Loops ===
Elevator 1 moving UP from floor 0 to floor 1.
Elevator 1 arrived at floor 1. Doors Open -> Close.
Elevator 2 moving DOWN from floor 4 to floor 3.
Elevator 2 arrived at floor 3. Doors Open -> Close.
Elevator 2 moving UP from floor 3 to floor 7.
Elevator 2 arrived at floor 7. Doors Open -> Close.

```

---

## ✨ Features Handled Perfectly

1. **Directional Alignment Bounds Check**: Elevators moving past a floor are mathematically passed over for trailing options to keep arrival times realistic.
2. **Fallback Resilience**: If no optimal directional elevator can service a call immediately, fallback heuristics cleanly route the request to the nearest available `IDLE` car.
3. **Dual Input Vectors**: Seamlessly manages both **External Hall Calls** (directional buttons outside) and **Internal Car Panel Selections** (destination options inside).

---

This is ready to be dropped straight into a `README.md` file in your repository! What structural topic should we conquer next?