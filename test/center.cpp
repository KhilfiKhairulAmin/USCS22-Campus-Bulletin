#include <iostream>
#include <cstdlib>

int main() {
    // Get terminal size using stty command
    int rows, cols;
    if (FILE *fp = popen("stty size", "r")) {
        fscanf(fp, "%d %d", &rows, &cols);
        pclose(fp);
    }

    // Calculate center position
    int centerRow = rows / 2;
    int centerCol = cols / 2;

    // Move the cursor to the center
    std::cout << "\033[" << centerRow << ";" << centerCol << "H";

    // Print your text
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
