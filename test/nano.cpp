// #include <iostream>
// #include <cstdio> // For popen()

// int main() {
//     FILE* process = popen("C:\\msys64\\usr\\bin\\mintty -e C:\\msys64\\usr\\bin\\nano temp.txt", "r");

//     if (!process) {
//         std::cerr << "Failed to open Nano.\n";
//         return 1;
//     }

//     // Wait for the process to finish
//     pclose(process);

//     std::cout << "Nano editing completed. Back to C++ program.\n";
//     return 0;
// }

#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "Before Nano...\n";

    system("cmd /c start /wait notepad.exe temp.txt");

    std::cout << "After Nano...\n";
    return 0;
}



// #include <iostream>
// #include <fstream>
// #include <cstdlib> // For system()
// #include <string>
// #include <thread>

// void invokeNano(const std::string& filePath) {
//     std::string command = "C:\\msys64\\usr\\bin\\mintty -e C:\\msys64\\usr\\bin\\nano temp.txt" + filePath;
//     // system("clear");
//     int result = system(command.c_str()); // Opens Nano to edit the file
//     if (result == 0) {
//         std::cout << "Nano exited successfully.\n";
//     } else {
//         std::cerr << "Error: Nano failed to open.\n";
//     }
// }

// std::string readFileContent(const std::string& filePath) {
//     std::ifstream file(filePath);
//     std::string content, line;

//     while (std::getline(file, line)) {
//         content += line + '\n';
//     }
//     file.close();

//     return content;
// }

// void writeFileContent(const std::string& filePath, const std::string& content) {
//     std::ofstream file(filePath);
//     file << content;
//     file.close();
// }

// int main() {
//     std::string tempFilePath = "temp_edit.txt";

//     // Write initial content to the temp file
//     std::string initialContent = "This is the initial content.\nYou can edit this using Nano.\n";
//     writeFileContent(tempFilePath, initialContent);

//     // Invoke Nano for editing
//     invokeNano(tempFilePath);

//     // Read the edited content back
//     std::string updatedContent = readFileContent(tempFilePath);
//     std::cout << "\nUpdated Content from Nano:\n";
//     std::cout << updatedContent;

//     // Optionally delete the temp file after use
//     std::remove(tempFilePath.c_str());

//     return 0;
// }
