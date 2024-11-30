#include <iostream>
#include <fstream>

int main() {
    // File paths
    const std::string fileName = "be it an arguments to pass by as an arguments";

    // 1. Write to a file...(.. to the os file)
    std::ofstream outFile(fileName); // Open file in write mode
    if (outFile.is_open()) {
        outFile << "Hello, this is a sample text.\n";
        outFile << "C++ file I/O using fstream is easy!\n";
        outFile.close(); // Close the file
        std::cout << "Data written to file successfully.\n";
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }

    // 2. Read from the file
    std::ifstream inFile(fileName); // Open file in read mode
    if (inFile.is_open()) {
        std::string line;
        std::cout << "\nReading from file:\n";
        while (std::getline(inFile, line)) { // Read line by line
            std::cout << line << std::endl;
        }
        inFile.close(); // Close the file
    } else {
        std::cerr << "Unable to open file for reading.\n";
    }

    return 0;
}
