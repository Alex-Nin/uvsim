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

int UVSim::fetch(int index) {
    return memory[index];
}

void UVSim::load(int operand) {
    accumulator = fetch(operand);
}

void UVSim::store(int index, int word) {
    memory[index] = word;
}

void UVSim::execute(int instruction) {
    int opcode = instruction / 100; //YIELDS first two numbers
    int operand = instruction % 100; //YIELDS last two numbers

    switch (opcode) { // (Created by David, mostly)
        case 10: // READ
            memory[operand] = io.read(operand);
            break;
        case 11: // WRITE
            io.write(operand, memory[operand]);
            break;
        case 20: // LOAD
            load(operand);
            break;
        case 21: // STORE
            store(operand, accumulator);
            break;
        case 30: // ADD
            accumulator = arithmetic.add(accumulator, fetch(operand));
            break;
        case 31: // SUBTRACT
            accumulator = arithmetic.subtract(accumulator, fetch(operand));
            break;
        case 32: // DIVIDE
            accumulator = arithmetic.divide(accumulator, fetch(operand));
            break;
        case 33: // MULTIPLY
            accumulator = arithmetic.multiply(accumulator, fetch(operand));
            break;
        case 40: // BRANCH
            instructionPointer = control.branch(operand);
            break;
        case 41: // BRANCHNEG
            instructionPointer = control.branchNeg(operand, instructionPointer, accumulator);
            break;
        case 42: // BRANCHZERO
            instructionPointer = control.branchZero(operand, instructionPointer, accumulator);
            break;
        case 43: // HALT
            halted = true;
            break;
        default:
            std::cerr << "Error: Unknown opcode " << opcode << std::endl;
            halted = true;
    }
}