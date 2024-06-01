
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
            int instruction = fetch();
            execute(instruction);
            instructionPointer++;
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
    /// <returns>The instruction at the current instruction pointer.</returns>
    int fetch() {
        return memory[instructionPointer];
    }
    
    /// <summary>
    /// Decodes and executes a fetched instruction.
    /// </summary>
    /// <param name="instruction">The instruction to execute.</param>
    void execute(int instruction) {
        int opcode = instruction / 100; //YIELDS first two numbers
        int operand = instruction % 100; //YIELDS last two numbers

        switch (opcode) {
        case 10: // READ
            break;
        case 11: // WRITE
            break;
        case 20: // LOAD
            break;
        case 21: // STORE
            break;
        case 30: // ADD
            break;
        case 31: // SUBTRACT
            break;
        case 32: // DIVIDE
            break;
        case 33: // MULTIPLY
            break;
        case 40: // BRANCH
            break;
        case 41: // BRANCHNEG
            break;
        case 42: // BRANCHZERO
            break;
        case 43: // HALT
            break;
        default:
            cerr << "Error: Unknown opcode " << opcode << endl;
            halted = true;
        }
    }
};