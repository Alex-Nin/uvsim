// Created by Alex, transfered into "uvsim.cpp" by Jess

#include <iostream>
#include <fstream>
#include <iomanip>
#include "uvsim.h"

UVSim::UVSim() :
        memory(100, 0),
        accumulator(0),
        instructionPointer(0),
        halted(false) {}

UVSim::~UVSim() {
    memory.clear();
    accumulator = 0;
    instructionPointer = 0;
    halted = false;
}

void UVSim::loadProgram(const std::string &filename) {
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

std::vector<int> UVSim::getMemory() {
    return memory;
}

void UVSim::setMemory(int index, int value) {
    if (index >= 0 && index < memory.size()) {
        memory[index] = value;
    }
}

int UVSim::getAccumulator() {
    return accumulator;
}

void UVSim::setAccumulator(int num) {
    accumulator = num;
}

bool UVSim::isHalted() {
    return halted;
}

void UVSim::setHalted(bool halt) {
    halted = halt;
}

int UVSim::getInstructionPointer() {
    return instructionPointer;
}

void UVSim::run() {
    while (!halted) {
        int instruction = fetch(instructionPointer++);
        execute(instruction);
    }
}

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

int UVSim::fetch(int index) {
    return memory[index];
}

void UVSim::load(int operand) {
    accumulator = fetch(operand);
}

void UVSim::store(int index, int word) {
    memory[index] = word;
}

void UVSim::read(int operand) {
    int input;
    std::cout << "Enter an integer: ";

    if (!(std::cin >> input)) {
        throw std::runtime_error("Invalid input detected. Halting program.");
    }

    store(operand, input);
}

void UVSim::write(int operand) {
    std::cout << "Output of location " << operand << ": " << fetch(operand) << std::endl;
}

void UVSim::add(int operand) {
    accumulator = truncate(accumulator + fetch(operand));
}

void UVSim::subtract(int operand) {
    accumulator = truncate(accumulator - fetch(operand));
}

void UVSim::multiply(int operand) {
    accumulator = truncate(accumulator * fetch(operand));
}

void UVSim::divide(int operand) {
    if (fetch(operand) != 0) {
        accumulator = truncate(accumulator / fetch(operand));
    } else {
        throw std::runtime_error("Error: Division by zero.");
    }
}

void UVSim::branch(int operand) {
    instructionPointer = operand;
}

void UVSim::branchNeg(int operand) {
    if (accumulator < 0) {
        branch(operand);
    }
}

void UVSim::branchZero(int operand) {
    if (accumulator == 0) {
        branch(operand);
    }
}

int UVSim::truncate(int num) {
    if (num > 9999) {
        return num % 10000;
    } else if (num < -9999) {
        return -(-num % 10000);
    }
    return num;
}

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
            load(operand);
            break;
        case 21: // STORE
            store(operand, accumulator);
            break;
        case 30: // ADD
            add(operand);
            break;
        case 31: // SUBTRACT
            subtract(operand);
            break;
        case 32: // DIVIDE
            divide(operand);
            break;
        case 33: // MULTIPLY
            multiply(operand);
            break;
        case 40: // BRANCH
            branch(operand);
            break;
        case 41: // BRANCHNEG
            branchNeg(operand);
            break;
        case 42: // BRANCHZERO
            branchZero(operand);
            break;
        case 43: // HALT
            halted = true;
            break;
        default:
            std::cerr << "Error: Unknown opcode " << opcode << std::endl;
            halted = true;
    }
}