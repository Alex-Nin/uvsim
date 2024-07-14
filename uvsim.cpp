// Created by Alex, transfered into "uvsim.cpp" by Jess

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include "uvsim.h"

std::vector<std::string> instructionList = {"10", "11", "20", "21", "30", "31", "32", "33", "40", "41", "42", "43"};

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
    bool isFourDigit = false;
    bool isSixDigit = false;

    std::string line;
    int index = 0;
    while (std::getline(file, line)) {
        std::regex regex("[+-](\\d{4}|\\d{6})");
        if (!std::regex_match(line, regex)) {
            std::cerr << "Error: File contains invalid format." << std::endl;
            return;
        }

        if (line.length() == 5) {
            isFourDigit = true;
            if (isSixDigit) {
                std::cerr << "Error: File contains both 4-digit and 6-digit numbers." << std::endl;
                return;
            }

        if (std::find(instructionList.begin(), instructionList.end(), line.substr(1, 2)) != instructionList.end()) {
                line.insert(1, "0");
                line.insert(4, "0");
            } else {
                line.insert(1, "00");
            }
        } else if (line.length() == 7) {
            isSixDigit = true;
            if (isFourDigit) {
                std::cerr << "Error: File contains both 4-digit and 6-digit numbers." << std::endl;
                return;
            }
        }
        memory[index++] = stoi(line);
    }
    file.close();
}

std::vector<int> UVSim::getMemory() {
    return memory;
}

int UVSim::getMemoryAdd(int index) {
    return memory[index];
}

void UVSim::setMemory(int index, int value) {
    if (index >= 0 && index < memory.size()) {
        memory[index] = value;
    }
}

void UVSim::clearMemory() {
  for (int i = 0; i < memory.size(); i++) {
    memory[i] = 0;
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

void UVSim::setInstructionPointer(int ip) {
    instructionPointer = ip;
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
    std::cout << std::endl;
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
    int opcode = instruction / 1000; //YIELDS first two numbers
    int operand = instruction % 1000; //YIELDS last two numbers

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
