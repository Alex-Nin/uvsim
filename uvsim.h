// Created by Jess, adapted from Alex's "main.cpp"

#include <vector>
#include <string>
#ifndef UVSIM_H
#define UVSIM_H

class UVSim
{
public:
    /**
     * @brief A simple virtual machine simulator for BasicML language.
    */
    UVSim();
    ~UVSim();

    /**
     * @brief Loads a program from a file into the simulator's memory.
     * @param filename The string name of the file containing the program to load.
    */
    void loadProgram(const std::string& filename);

    /**
     * @brief FOR TESTING PURPOSES ONLY, Retrieves the current state of the memory.
    * @return A vector containing the values in memory.
    */
    std::vector<int> getMemory();
    /**
     * @brief FOR TESTING PURPOSES ONLY, this method shall not be used anywhere in the code base
     * @param inst Integer element to be added to the memory vector
    */
    void setMemory(int index, int value);
    /**
     * @brief FOR TESTING PURPOSES ONLY, Retrieves the current value in the accumulator.
    * @return A vector containing the values in memory.
    */
    int getAccumulator();
    /**
     * @brief FOR TESTING PURPOSES ONLY, setter for accumulator variable
     * @param num New value assignment for accumulator
    */
    void setAccumulator(int num);
    /**
     * @brief FOR TESTING PURPOSES ONLY, getter for halted variable
     * @return Boolean value of halted variable
    */
    bool isHalted();

    /**
     * @brief FOR TESTING PURPOSES ONLY, setter for halted variable
     * @param halt New halted boolean value
    */
    void setHalted(bool halt);

    /**
     * @brief FOR TESTING PURPOSES ONLY, getter for instructionPointer variable
     * @return Integer value of the instructionPointer variable
    */
    int getInstructionPointer();

    /**
     * @brief Runs the loaded program using while loop with boolean variable.
    */

    void run();

    void dump();

    std::string promptFile();

private:
    std::vector<int> memory;
    int accumulator;
    int instructionPointer;
    bool halted;

    /**
     * @brief
     * @param index Integer representation of the memory location.
     * @return The instruction at the current instruction pointer.
    */
    int fetch(int index);

    /**
     * @brief Stores a word (number) in memory at index.
     * @param index The memory location.
     * @param word The word (number) to store in memory.
    */
    void store(int index, int word);

    /**
     * @brief Read a word from the keyboard into a specific location in memory.
    */
    void read(int operand);

    /**
     * @brief Write a word from a specific location in memory to screen.
    */
    void write(int operand);

    /**
     * @brief Decodes and executes a fetched instruction.
     * @param instruction The instruction to execute.
    */
    void execute(int instruction);
};

#endif // UVSIM_H