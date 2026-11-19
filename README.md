# Cellular Systems

**A C++ experiment in emergence, mathematical rules, and evolving patterns.**

Cellular Systems explores how complex visual structures can emerge from simple instructions.

Based on Conway's Game of Life, the program simulates a two-dimensional grid of cells. Each cell is either alive or dead, and its state changes according to the states of its eight neighbours.

## The Rules

Each generation follows four rules:

1. A living cell with fewer than two living neighbours dies.
2. A living cell with two or three living neighbours survives.
3. A living cell with more than three living neighbours dies.
4. A dead cell with exactly three living neighbours becomes alive.

From these rules, patterns can grow, move, stabilize, or disappear.

## Features

- Written in C++17
- Animated terminal visualization
- Adjustable grid dimensions
- Random initial configurations
- Glider pattern demonstration
- Configurable number of generations
- Wraparound grid boundaries

## Running the Simulation

Compile with a C++17-compatible compiler:

```bash
g++ -std=c++17 cellular_systems.cpp -o cellular_systems
```

Run with the default settings:

```bash
./cellular_systems
```

Or customize the simulation:

```bash
./cellular_systems 20 40 100 glider
```

The four optional arguments specify the number of rows, columns, generations, and starting pattern (`random` or `glider`).

On Windows, the compiled program can be run as `.\cellular_systems.exe`.

## Concept

Cellular Systems is an exploration of **emergent behaviour**: the appearance of intricate structures through repeated local interactions.

The project connects computational logic with visual experimentation, using code as a medium for studying pattern, repetition, and change.

## Technology

C++17 · Cellular Automata · Simulation · Algorithmic Art

