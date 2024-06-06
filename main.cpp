// Created by Alex

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class UVSim {

public:

    /**
     * @brief A simple virtual machine simulator for BasicML language.
    */
    UVSim() :
        memory(100, 0),
        accumulator(0),
        instructionPointer(0),
        halted(false)
        {}

    /**
     * @brief Loads a program from a file into the simulator's memory.
     * @param filename The string name of the file containing the program to load.
    */
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

    /**
     * @brief FOR TESTING PURPOSES ONLY, Retrieves the current state of the memory.
    * @return A vector containing the values in memory.
    */
    vector<int> getMemory() {
        return memory;
    }
    /**
     * @brief FOR TESTING PURPOSES ONLY, this method shall not be used anywhere in the code base
     * @param inst Integer element to be added to the memory vector
    */
    void setMemory(int inst) {
        memory.push_back(inst);
    }

    /**
     * @brief FOR TESTING PURPOSES ONLY, Retrieves the current value in the accumulator.
    * @return A vector containing the values in memory.
    */
    int getAccumulator() {
        return accumulator;
    }

    /**
     * @brief FOR TESTING PURPOSES ONLY, setter for accumulator variable
     * @param num New value assignment for accumulator
    */
    void setAccumulator(int num) {
        accumulator = num;
    }
    /**
     * @brief FOR TESTING PURPOSES ONLY, getter for halted variable
     * @return Boolean value of halted variable
    */
    bool isHalted() {
    return halted;
   }
    
    /**
     * @brief FOR TESTING PURPOSES ONLY, setter for halted variable
     * @param halt New halted boolean value
    */
    void setHalted(bool halt) {
        halted = halt;
    }
    
    /**
     * @brief FOR TESTING PURPOSES ONLY, getter for instructionPointer variable
     * @return Integer value of the instructionPointer variable
    */
    int getInstructionPointer() {
        return instructionPointer;
    }
    
    /**
     * @brief Runs the loaded program using while loop with boolean variable.
    */
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

    /**
     * @brief 
     * @param index Integer representation of the memory location.
     * @return The instruction at the current instruction pointer.
    */
    int fetch(int index) {
        return memory[index];
    }

    /**
     * @brief Stores a word (number) in memory at index.
     * @param index The memory location.
     * @param word The word (number) to store in memory.
    */
    void store(int index, int word) {
        memory[index] = word;
    }

    /**
     * @brief Read a word from the keyboard into a specific location in memory.
    */
    void read(int operand) {
        int input;
        cout << "Enter an integer:";

        if (!(cin >> input)) {
            cerr << "Invalid input detected. Halting program." << endl;
            exit(EXIT_FAILURE);
        }

        store(operand, input);
    }

    /**
     * @brief Write a word from a specific location in memory to screen.
    */
    void write(int operand) {
        cout << "Output of location: " << operand << ": " << fetch(operand) << endl;
    }

    /**
     * @brief Decodes and executes a fetched instruction.
     * @param instruction The instruction to execute.
    */
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
            if (fetch(operand) != 0) {
                accumulator /= fetch(operand);
            } else {
                cerr << "Error: Division by zero." << endl;
            }
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
