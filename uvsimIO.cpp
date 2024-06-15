#include "uvsimIO.h"
#include <iostream>
#include <fstream>

using namespace std;

int IO::read(int operand) {
    int input;
    std::cout << "Enter an integer: ";

    if (!(std::cin >> input)) {
        throw std::runtime_error("Invalid input detected. Halting program.");
    }

    return input;
}

void IO::write(int operand, int value) {
    std::cout << "Output of location " << operand << ": " << value << std::endl;
}

std::string IO::promptFile() {
    std::string inputFile;
    while (true) {
        std::cout << "Please enter the name of the file you would like to load: ";
        std::cin >> inputFile;
        std::ifstream file(inputFile);
        if (file.is_open()) {
            break;
        }
        std::cout << "File can not be opened, please enter another file." << std::endl;
    }
    return inputFile;
}