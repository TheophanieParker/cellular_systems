
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

using Grid = std::vector<std::vector<bool>>;

// Count the living cells surrounding a position.
int countNeighbors(const Grid& grid, int row, int col) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());
    int count = 0;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int r = (row + dr + rows) % rows;
            int c = (col + dc + cols) % cols;

            if (grid[r][c]) ++count;
        }
    }

    return count;
}

// Calculate the next generation.
Grid nextGeneration(const Grid& grid) {
    Grid next = grid;

    for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
        for (int c = 0; c < static_cast<int>(grid[r].size()); ++c) {
            int neighbors = countNeighbors(grid, r, c);

            if (grid[r][c]) {
                next[r][c] = (neighbors == 2 || neighbors == 3);
            } else {
                next[r][c] = (neighbors == 3);
            }
        }
    }

    return next;
}

// Draw the grid in the terminal.
void display(const Grid& grid, int generation) {
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "CELLULAR SYSTEMS\n";
    std::cout << "Conway's Game of Life | Generation "
              << generation << "\n\n";

    for (const auto& row : grid) {
        for (bool alive : row) {
            std::cout << (alive ? "##" : "  ");
        }
        std::cout << '\n';
    }

    std::cout << "\nPress Ctrl+C to stop.\n";
}

// Create a random starting pattern.
Grid randomGrid(int rows, int cols) {
    Grid grid(rows, std::vector<bool>(cols, false));

    std::random_device device;
    std::mt19937 generator(device());
    std::bernoulli_distribution alive(0.30);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = alive(generator);
        }
    }

    return grid;
}

// Add a moving glider pattern.
void addGlider(Grid& grid, int row, int col) {
    const int pattern[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            grid[(row + r) % rows][(col + c) % cols] =
                pattern[r][c] == 1;
        }
    }
}

int main(int argc, char* argv[]) {
    int rows = 20;
    int cols = 40;
    int generations = 100;
    int delayMs = 150;
    std::string mode = "random";

    try {
        if (argc > 1) rows = std::stoi(argv[1]);
        if (argc > 2) cols = std::stoi(argv[2]);
        if (argc > 3) generations = std::stoi(argv[3]);
        if (argc > 4) mode = argv[4];
    } catch (const std::exception&) {
        std::cerr << "Invalid arguments.\n";
        return 1;
    }

    if (rows < 3 || cols < 3 || generations < 1 ||
        rows > 100 || cols > 100 ||
        (mode != "random" && mode != "glider")) {
        std::cerr << "Usage: cellular_systems "
                  << "[rows 3-100] [cols 3-100] "
                  << "[generations] [random|glider]\n";
        return 1;
    }

    Grid grid(rows, std::vector<bool>(cols, false));

    if (mode == "random") {
        grid = randomGrid(rows, cols);
    } else {
        addGlider(grid, rows / 2, cols / 2);
    }

    for (int generation = 0;
         generation < generations; ++generation) {
        display(grid, generation);
        grid = nextGeneration(grid);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(delayMs)
        );
    }

    std::cout << "\nSimulation complete.\n";
    return 0;
}
