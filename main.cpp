// Created by Alex

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class UVSim {
public:
    /// <summary>
    /// A simple virtual machine simulator for BasicML language.
    /// </summary>
    UVSim() :
        memory(100, 0),
        accumulator(0),
        instructionPointer(0),
        halted(false)
        {}

    /// <summary>
    /// Loads a program from a file into the simulator's memory.
    /// </summary>
    /// <param name="filename">The name of the file containing the program to load.</param>
    void loadProgram(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        int address = 0;
        while (file >> memory[address]) {
            address++;
        }

        file.close();
    }

    /// <summary>
    /// Runs the loaded program using while loop with boolean variable.
    /// </summary>
    void run() {
        while (!halted) {
            int instruction = fetch(instructionPointer++);
            execute(instruction);
        }
    }

private:
    vector<int> memory;
    int accumulator;
    int instructionPointer;
    bool halted;

    /// <summary>
    /// Fetches the current instruction from memory.
    /// </summary>
    /// <param name="index">The memory location.</param>
    /// <returns>The instruction at the current instruction pointer.</returns>
    int fetch(int index) {
        return memory[index];
    }

    /// <summary> (created by David)
    /// Stores a word (number) in memory at index.
    /// </summary>
    /// <param name="index">The memory location.</param>
    /// <param name="word">The word (number) to store in memory.</param>
    void store(int index, int word) {
        memory[index] = word;
    }

    /// <summary>
    /// Decodes and executes a fetched instruction.
    /// </summary>
    /// <param name="instruction">The instruction to execute.</param>
    void execute(int instruction) {
        int opcode = instruction / 100; //YIELDS first two numbers
        int operand = instruction % 100; //YIELDS last two numbers
        int myNum = 0;

        switch (opcode) { // (Created by David, mostly)
        case 10: // READ
            break; // Chen TODO
        case 11: // WRITE
            break; // Chen TODO
        case 20: // LOAD
            accumulator = fetch(operand);
            break;
        case 21: // STORE
            store(operand, accumulator);
            break;
        case 30: // ADD
            accumulator += fetch(operand);
            break;
        case 31: // SUBTRACT
            accumulator -= fetch(operand);
            break;
        case 32: // DIVIDE
            accumulator /= fetch(operand);
            break;
        case 33: // MULTIPLY
            accumulator *= fetch(operand);
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
            cerr << "Error: Unknown opcode " << opcode << endl;
            halted = true;
        }
    }
};
