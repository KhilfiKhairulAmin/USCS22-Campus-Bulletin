#include <iostream>
#include <cstdio>

int main() {
    // Assuming the terminal width is 80 (you can calculate it dynamically if needed)
    int cols = 80;
    int centerCol = cols / 2;

    // Use ANSI escape code to save and restore cursor position
    std::cout << "\033[s"; // Save cursor position
    std::cout << "\033[6n"; // Query the cursor position (outputs to stdin)

    // Read the response to find the current row
    int row, col;
    if (scanf("\033[%d;%dR", &row, &col) == 2) {
        // Move the cursor to the center column, keeping the current row
        std::cout << "\033[" << row << ";" << centerCol << "H";
        std::cout << "Hello, World!" << std::endl;
    }

    std::cout << "\033[u"; // Restore cursor position
    return 0;
}
