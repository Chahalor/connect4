# 42 Rush: Connect Four – Terminal Game in C with AI

This project is part of the **42 Rush** series — a coding challenge with a strict 2-day time limit. The goal is to implement the classic **Connect Four** game in pure **C**, playable in the terminal.

A human player competes against a basic **AI** that evaluates the board to make strategic decisions.

---

## 🎯 Goals

- Implement a complete Connect Four game in pure C.
- Create a simple but effective **AI opponent**.
- Maintain a clean, modular structure for code clarity and future extension.
- Ensure the game is lightweight and works in a basic terminal environment.

---

## 🧩 Features

- Text-based interface (no external libraries like `ncurses`).
- Turn-based gameplay between the player and the AI.
- Win detection in all directions (horizontal, vertical, diagonals).
- Simple AI that scores possible moves and blocks or wins when possible.
- Modular design: game logic, AI, and interface are separated.

---

## 🧠 AI Behavior

The AI assigns scores to potential moves by analyzing the grid:
- Prioritizes winning moves.
- Blocks opponent’s winning threats.
- Favors positions that lead to longer alignments (2–3 in a row).
- Uses simple heuristics rather than advanced algorithms (no minimax or machine learning).

---

## 🛠️ Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/Chahalor/connect4
   cd connect4
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the game
   ```bash
   ./connect4 7 6
   ```

## 📁 Project Structure
.
├── src/                # Game logic, AI, and core functions
├── src/main.c          # Entry point
├── global/             # Header for the configuration
├── Makefile            # Build instructions
└── README.md           # Project description

## 🖊️ Authors
 - nduvoid  @Chahalor
 - bcheronn @bcheronn
 - htrap    @MisterDutchi16