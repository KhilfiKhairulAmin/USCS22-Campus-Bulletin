#include <iostream>
#include <windows.h>

int main() {
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calculate center position
    int centerRow = rows / 2;
    int centerCol = cols / 2;

    // Set cursor position
    COORD pos = { (SHORT)(centerCol - 6), (SHORT)(centerRow) }; // -6 to align "Hello, World!"
    SetConsoleCursorPosition(hConsole, pos);

    // Print your text
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
