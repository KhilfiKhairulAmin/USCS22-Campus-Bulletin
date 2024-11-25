#include <iostream>
#include <thread>
#include <chrono>

void moveTo(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

int main() {
    // Clear the screen and move to the top left
    std::cout << "\033[2J\033[H";

    // Store specific positions manually
    int progressRow = 5, progressCol = 10;
    int messageRow = 6, messageCol = 10;

    // Move to progress position and print initial message
    moveTo(progressRow, progressCol);
    std::cout << "Progress:";

    // Move to a different position for another message
    moveTo(messageRow, messageCol);
    std::cout << "Starting...";

    // Update progress over time at a specific position
    for (int i = 1; i <= 5; ++i) {
        moveTo(progressRow, progressCol + 10); // Move next to "Progress:"
        std::cout << i << "/5 completed  ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Final message
    moveTo(messageRow, messageCol);
    std::cout << "Done!" << std::endl;

    return 0;
}
