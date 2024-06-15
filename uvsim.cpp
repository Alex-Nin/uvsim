// Created by Alex, transfered into "uvsim.cpp" by Jess

#include <iostream>
#include <fstream>
#include <iomanip>
#include "uvsim.h"

/**
 * @brief A simple virtual machine simulator for BasicML language.
*/
UVSim::UVSim() :
    memory(100, 0),
    accumulator(0),
    instructionPointer(0),
    halted(false)
    {}

/**
 * @brief Destructor for UVSim class.
 */
UVSim::~UVSim() {
    memory.clear();
    accumulator = 0;
    instructionPointer = 0;
    halted = false;
}

/**
 * @brief Loads a program from a file into the simulator's memory.
 * @param filename The string name of the file containing the program to load.
*/
void UVSim::loadProgram(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    int address = 0;
    while (file >> memory[address]) {
        address++;
    }

    file.close();
}

/**
 * @brief FOR TESTING PURPOSES ONLY, Retrieves the current state of the memory.
* @return A vector containing the values in memory.
*/
std::vector<int> UVSim::getMemory() {
    return memory;
}
/**
 * @brief FOR TESTING PURPOSES ONLY, this method shall not be used anywhere in the code base
 * @param inst Integer element to be added to the memory vector
*/
void UVSim::setMemory(int index, int value) {
    if (index >= 0 && index < memory.size()) {
        memory[index] = value;
    }
}

/**
 * @brief FOR TESTING PURPOSES ONLY, Retrieves the current value in the accumulator.
* @return A vector containing the values in memory.
*/
int UVSim::getAccumulator() {
    return accumulator;
}

/**
 * @brief FOR TESTING PURPOSES ONLY, setter for accumulator variable
 * @param num New value assignment for accumulator
*/
void UVSim::setAccumulator(int num) {
    accumulator = num;
}
/**
 * @brief FOR TESTING PURPOSES ONLY, getter for halted variable
 * @return Boolean value of halted variable
*/
bool UVSim::isHalted() {
    return halted;
}

/**
 * @brief FOR TESTING PURPOSES ONLY, setter for halted variable
 * @param halt New halted boolean value
*/
void UVSim::setHalted(bool halt) {
    halted = halt;
}

/**
 * @brief FOR TESTING PURPOSES ONLY, getter for instructionPointer variable
 * @return Integer value of the instructionPointer variable
*/
int UVSim::getInstructionPointer() {
    return instructionPointer;
}

/**
 * @brief Runs the loaded program using while loop with boolean variable.
*/
void UVSim::run() {
    while (!halted) {
        int instruction = fetch(instructionPointer++);
        execute(instruction);
    }
}

/**
 * @brief Dumps the current state of the simulator to the console.
 */
void UVSim::dump() {
    std::cout << "\n\nREGISTERS:" << std::endl;
    std::cout << "accumulator: " << accumulator << std::endl;
    std::cout << "instructionPointer: " << instructionPointer << std::endl;
    std::cout << "MEMORY:" << std::endl;
    for (unsigned int i = 0; i < memory.size(); i++) {
        // Print the memory location
        std::cout << std::setw(4) << std::setfill(' ') << memory[i] << " ";
        // Print 10 numbers per line
        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl << std::endl << std::endl;
}

/**
 * @brief Prompts the user for a file name to load.
 * @return The name of the file to load.
 */
std::string UVSim::promptFile() {
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

/**
 * @brief
 * @param index Integer representation of the memory location.
 * @return The instruction at the current instruction pointer.
*/
int UVSim::fetch(int index) {
    return memory[index];
}

/**
 * @brief Stores a word (number) in memory at index.
 * @param index The memory location.
 * @param word The word (number) to store in memory.
*/
void UVSim::store(int index, int word) {
    memory[index] = word;
}

/**
 * @brief Read a word from the keyboard into a specific location in memory.
*/
void UVSim::read(int operand) {
    int input;
    std::cout << "Enter an integer: ";

    if (!(std::cin >> input)) {
        throw std::runtime_error("Invalid input detected. Halting program.");
    }

    store(operand, input);
}

/**
 * @brief Write a word from a specific location in memory to screen.
*/
void UVSim::write(int operand) {
    std::cout << "Output of location " << operand << ": " << fetch(operand) << std::endl;
}

/**
 * @brief Truncates a number to 4 digits.
 * @param num The number to truncate.
 * @return The truncated number.
*/
int UVSim::truncate(int num) {
    if (num > 9999) {
        return num % 10000;
    } else if (num < -9999) {
        return -(-num % 10000);
    }
    return num;
}

/**
 * @brief Decodes and executes a fetched instruction.
 * @param instruction The instruction to execute.
*/
void UVSim::execute(int instruction) {
    int opcode = instruction / 100; //YIELDS first two numbers
    int operand = instruction % 100; //YIELDS last two numbers
    switch (opcode) { // (Created by David, mostly)
    case 10: // READ
        read(operand);
        break;
    case 11: // WRITE
        write(operand);
        break;
    case 20: // LOAD
        accumulator = fetch(operand);
        break;
    case 21: // STORE
        store(operand, accumulator);
        break;
    case 30: // ADD
        accumulator = truncate(accumulator + fetch(operand));
        break;
    case 31: // SUBTRACT
        accumulator = truncate(accumulator - fetch(operand));
        break;
    case 32: // DIVIDE
        if (fetch(operand) != 0) {
            accumulator = truncate(accumulator / fetch(operand));
        } else {
            throw std::runtime_error("Error: Division by zero.");
        }
        break;
    case 33: // MULTIPLY
        accumulator = truncate(accumulator * fetch(operand));
        break;
    case 40: // BRANCH
        instructionPointer = operand;
        break;
    case 41: // BRANCHNEG
        if (accumulator < 0) {
                instructionPointer = operand;
        }
        break;
    case 42: // BRANCHZERO
        if (accumulator == 0) {
                instructionPointer = operand;
        }
        break;
    case 43: // HALT
        halted = true;
        break;
    default:
        std::cerr << "Error: Unknown opcode " << opcode << std::endl;
        halted = true;
    }
}