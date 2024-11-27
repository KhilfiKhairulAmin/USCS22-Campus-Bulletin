#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

std::string getParagraphInput(int lineLimit) {
    std::vector<std::string> lines; // Store lines as a vector of strings
    std::string currentLine = "";
    char key;

    std::cout << "Start typing your paragraph (Press ESC to submit):\n";

    while (true) {
        key = _getch(); // Read a character

        // Handle ESC key to finish input
        if (key == 27) { // ASCII code for ESC
            if (!currentLine.empty()) {
                lines.push_back(currentLine); // Add the last line
            }
            break;
        }

        // Handle Enter key to start a new line
        if (key == 13) { // ASCII code for Enter
            lines.push_back(currentLine); // Save the current line
            currentLine = ""; // Reset the current line
            std::cout << '\n'; // Move to the next line on screen
        }
        // Handle Backspace key
        else if (key == 8) { // ASCII code for Backspace
            if (!currentLine.empty()) {
                currentLine.pop_back(); // Remove the last character from the current line
                std::cout << "\b \b"; // Erase the character visually
            } else if (!lines.empty()) {
                // Move back to the previous line
                currentLine = lines.back(); // Restore the previous line
                lines.pop_back(); // Remove it from the lines vector

                // Clear the visual newline from the console
                std::cout << "\b \b"; // Remove the empty line visually

                // Clear the characters of the restored line visually
                for (size_t i = 0; i < currentLine.size(); ++i) {
                    std::cout << "\b \b";
                }

                // Redisplay the restored line
                std::cout << currentLine;
            }
        }
        // Allow only printable characters, and limit line length
        else if (isprint(key)) {
            if (currentLine.length() < lineLimit) {
                currentLine += key;
                std::cout << key; // Display the character
            }
        }

        // Automatically move to the next line if line limit is reached
        if (currentLine.length() == lineLimit) {
            lines.push_back(currentLine); // Save the current line
            currentLine = ""; // Reset the current line
            std::cout << '\n'; // Move to the next line on screen
        }
    }

    // Combine all lines with '\n'
    std::string paragraph = "";
    for (const std::string& line : lines) {
        paragraph += line + '\n';
    }

    return paragraph; // Return the compiled paragraph
}

int main() {
    int lineLimit = 20; // Limit each line to 20 characters
    std::string paragraph = getParagraphInput(lineLimit);

    std::cout << "\n\nYour paragraph:\n" << paragraph << std::endl;
    return 0;
}
