#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

#define MAX_WIDTH 25

void setConsoleCursorPosition(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    int xPos = 0;
    int yPos = 6;  // Starting position for input
    string input;  // Store the input, +1 for null-terminator
    int index = 0;

    std::cout << "Enter input (max width per line " << MAX_WIDTH << " characters):" << std::endl;

    while (true) {
        char ch = _getch();  // Windows-specific function to get a single character
        if (ch == '\r')
        {
          input += "\n";  // Null-terminate the string
          std::cout << "\n";    // Move to next line
          yPos++;              // Move cursor down one line
          xPos = 0;            // Reset cursor to the beginning of the new line
          index = 0;           // Reset index for next line input
        }
        if (ch == '$') {  // Enter key pressed
            break;
        } else if (ch == '\b') {  // Backspace key pressed
            if (index > 0) {
                --index;
                xPos--;
                setConsoleCursorPosition(xPos, yPos);
                std::cout << " " << std::flush;  // Erase last character
                setConsoleCursorPosition(xPos, yPos);
                input = input.substr(0, input.size()-1);
            }
        } else {
            if (index < MAX_WIDTH) {
                input += ch;
                index++;
                std::cout << ch;  // Echo the character
                xPos++;
            }
        }
    }

    std::cout << "\nYour input: " << input << std::endl;

    return 0;
}
