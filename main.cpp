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

    void dump() {
        cout << "REGISTERS:" << endl;
        cout << "accumulator: " << accumulator << endl;
        cout << "instructionPointer: " << instructionPointer << endl;
        cout << "MEMORY:" << endl;
        for (int i = 0; i < memory.size(); i++) {
            // Print the memory location
            cout << setw(4) << setfill(' ') << memory[i] << " ";
            // Print 10 numbers per line
            if ((i + 1) % 10 == 0) {
                cout << endl;
            }
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
    /// Read a word from the keyboard into a specific location in memory
    /// </summary>
    void read(int operand) {
        int input;
        cout << "Enter an integer:";

        if (!(cin >> input)) {
            cerr << "Invalid input detected. Halting program." << endl;
            exit(EXIT_FAILURE);
        }

        store(operand, input);
    }

    /// <summary>
    /// Write a word from a specific location in memory to screen.
    /// </summary>
    void write(int operand) {
        cout << "Output of location: " << operand << ": " << fetch(operand) << endl;
    }

    /// <summary>
    /// Decodes and executes a fetched instruction.
    /// </summary>
    /// <param name="instruction">The instruction to execute.</param>
    void execute(int instruction) {
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

int main() {
    UVSim simulator;
    simulator.loadProgram("Test2.txt");
    simulator.run();
    simulator.dump();
    return 0;
}
