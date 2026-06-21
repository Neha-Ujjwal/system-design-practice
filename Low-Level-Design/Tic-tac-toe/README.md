```text
# Tic-Tac-Toe Game (Low-Level Design)

A clean, object-oriented, and extensible implementation of a classic Tic-Tac-Toe game designed in C++. This project highlights core object-oriented design principles, separating atomic entities like playing pieces and players from the board state and the central game loop orchestrator.

---

## 🏗️ Architecture & Component Hierarchy

The system isolates responsibilities into distinct, decoupled classes to allow for easy extensibility (e.g., modifying board dimensions or adding extra players):

* **`PlayingPiece`**: The base atomic entity representing a mark on the board, extended by concrete subclasses `PlayingPieceX` and `PlayingPieceO`.
* **`Player`**: Represents a participant in the game tracking a name and an assigned `PlayingPiece`.
* **`PlayingBoard`**: Manages the underlying $N \times N$ matrix grid using dynamic vectors, handling piece placement validation and boundary checks.
* **`PlayingGame`**: The central orchestrator that coordinates the main game loop, utilizes a double-ended queue (`std::deque`) for round-robin turn rotation, and validates win or draw conditions.

---

## 🛠️ Design Patterns & Principles Applied

### 1. Single Responsibility Principle (SRP)
Each class has one well-defined job. `PlayingBoard` is only responsible for mutating and inspecting the grid space, while `PlayingGame` manages user interaction, turn lifecycle transitions, and win condition evaluations.

### 2. Encapsulation
The internal state of the board matrix is securely hidden within `PlayingBoard`. The orchestrator interacts with individual cells via a clean public getter method (`getPieceAt`), preventing leaky abstractions.

---

## 🚀 End-to-End Execution Simulation

The simulation driver initializes a $3 \times 3$ board layout, hooks up two players, continuously processes inputs while validating coordinates, checks for invalid or overlapping moves, and catches win or draw scenarios instantly.

### Compilation & Execution Command

Run this command inside your `Tic-tac-toe` workspace directory to build and run the simulation using the C++17 configuration standard:

```bash
clang++ -std=c++17 main.cpp -o tictactoe_simulation && ./tictactoe_simulation

```

### Execution Log Output

```text
Initializing Tic-tac-toe game...
Starting the game...
- - - 
- - - 
- - - 
Player 1 X's turn: 
Enter row number (0 - 2): 1
Enter column number (0 - 2): 1
- - - 
- X - 
- - - 
Player 2 O's turn: 
Enter row number (0 - 2): 2
Enter column number (0 - 2): 2
- - - 
- X - 
- - O 
Player 1 X's turn: 
Enter row number (0 - 2): 0
Enter column number (0 - 2): 0
X - - 
- X - 
- - O 
Player 2 O's turn: 
Enter row number (0 - 2): 0
Enter column number (0 - 2): 1
X O - 
- X - 
- - O 
Player 1 X's turn: 
Enter row number (0 - 2): 1
Enter column number (0 - 2): 2
X O - 
- X X 
- - O 
Player 2 O's turn: 
Enter row number (0 - 2): 1
Enter column number (0 - 2): 0
X O - 
O X X 
- - O 
Player 1 X's turn: 
Enter row number (0 - 2): 2
Enter column number (0 - 2): 1
X O - 
O X X 
- X O 
Player 2 O's turn: 
Enter row number (0 - 2): 2
Enter column number (0 - 2): 0
X O - 
O X X 
O X O 
Player 1 X's turn: 
Enter row number (0 - 2): 0
Enter column number (0 - 2): 2
X O X 
O X X 
O X O 
Game is a draw!
Game Over! Winner: Draw

```

---

## 📂 Directory Structure

```text
Tic-tac-toe/
├── main.cpp                     # Simulation Entry Point
├── PlayingGame.h                # Game Loop Orchestrator
├── PlayingBoard/
│   └── PlayingBoard.h           # Grid Management & State
├── Player/
│   └── Player.h                 # Player Model Structure
└── PlayingPiece/
    ├── PlayingPiece.h           # Base Piece Class & Enums
    ├── PlayingPieceO.h          # Concrete Piece O Subclass
    └── PlayingPieceX.h          # Concrete Piece X Subclass

```

```

```
