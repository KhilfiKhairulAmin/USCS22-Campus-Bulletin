#include <iostream>
#include <conio.h>   // For _getch() on Windows
#include <string>

void displayOptions(int selected) {
    // Clear the line before displaying options
    std::cout << "\033[2K\r"; 

    // Display "Yes" in highlighted text if selected
    if (selected == 0) {
        std::cout << "\033[7m Yes \033[0m  No";
    } else {
        std::cout << " Yes  \033[7m No \033[0m";
    }

    std::cout.flush();  // Ensure the output is displayed immediately
}

int main() {
    int selected = 0;  // 0 for "Yes", 1 for "No"
    
    std::cout << "Use the Left and Right arrows to select Yes or No, and press Enter to confirm.\n";
    displayOptions(selected);

    while (true) {
        int key = _getch(); // Get a single character input

        // Detect arrow keys: in Windows, arrow keys start with a 224 or 0 followed by the specific keycode
        if (key == 224 || key == 0) {
            key = _getch();  // Get the actual key code after 224/0

            if (key == 75) {  // Left arrow key
                selected = 0;
                displayOptions(selected);
            } else if (key == 77) {  // Right arrow key
                selected = 1;
                displayOptions(selected);
            }
        } else if (key == 13) {  // Enter key to confirm selection
            break;
        }
    }

    // Clear the line and show final selection
    std::cout << "\033[2K\r";  
    std::cout << "You selected: " << (selected == 0 ? "Yes" : "No") << std::endl;

    return 0;
}
