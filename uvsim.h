// Created by Jess, adapted from Alex's "main.cpp"

#include <vector>
#include <string>

#ifndef UVSIM_H
#define UVSIM_H

class UVSim {
public:
    /**
     * @brief A simple virtual machine simulator for BasicML language.
     */
    UVSim();

    /**
     * @brief Destructor for UVSim class.
     */
    ~UVSim();

    /**
     * @brief Loads a program from a file into the simulator's memory.
     * @param filename The string name of the file containing the program to load.
     */
    void loadProgram(const std::string &filename);

    /**
     * @brief FOR TESTING PURPOSES ONLY, Retrieves the current state of the memory.
     * @return A vector containing the values in memory.
     */
    std::vector<int> getMemory();

    /**
     * @brief FOR TESTING PURPOSES ONLY, this method shall not be used anywhere in the code base
     * @param index Integer element to be added to the memory vector
     * @param value Integer value to be added to the memory vector
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

    /**
     * @brief FOR TESTING PURPOSES ONLY, dumps the contents of the memory to the screen.
     */
    void dump();

    /**
     * @brief Prompts the user for a file name to load.
     * @return The name of the file to load.
     */
    std::string promptFile();

private:
    // The memory of the UVSim.
    std::vector<int> memory;
    // The accumulator of the UVSim.
    int accumulator;
    // The instruction pointer of the UVSim.
    int instructionPointer;
    // The halted state of the UVSim.
    bool halted;

    /**
     * @brief I/O operation. Read a word from the keyboard into a specific location in memory.
     */
    void read(int operand);

    /**
     * @brief I/O operation. Write a word from a specific location in memory to screen.
     */
    void write(int operand);

    /**
     * @brief Load/store operations. Loads a word (number) from memory into the accumulator.
     * @param operand The memory location to load into the accumulator.
     */
    void load(int operand);

    /**
     * @brief Load/store operations. Stores a word (number) in memory at index.
     * @param index The memory location.
     * @param word The word (number) to store in memory.
     */
    void store(int index, int word);

    /**
     * @brief Arithmetic operation. Add the value at the operand location to the accumulator.
     * @param operand The memory location to add to the accumulator.
     */
    void add(int operand);

    /**
     * @brief Arithmetic operation. Subtract the value at the operand location from the accumulator.
     * @param operand The memory location to subtract from the accumulator.
     */
    void subtract(int operand);

    /**
     * @brief Arithmetic operation. Multiply the value at the operand location with the accumulator.
     * @param operand The memory location to multiply with the accumulator.
     */
    void multiply(int operand);

    /**
     * @brief Arithmetic operation. Divide the value at the operand location from the accumulator.
     * @param operand The memory location to divide the accumulator by.
     */
    void divide(int operand);

    /**
     * @brief Branch operation. Set the instruction pointer to the operand.
     * @param operand The memory location to branch to.
     */
    void branch(int operand);

    /**
     * @brief Branch operation. Set the instruction pointer to the operand if the accumulator is negative.
     * @param operand The memory location to branch to.
     */
    void branchNeg(int operand);

    /**
     * @brief Branch operation. Set the instruction pointer to the operand if the accumulator is zero.
     * @param operand The memory location to branch to.
     */
    void branchZero(int operand);

    /**
     * @brief
     * @param index Integer representation of the memory location.
     * @return The instruction at the current instruction pointer.
     */
    int fetch(int index);

    /**
     * @brief Decodes and executes a fetched instruction.
     * @param instruction The instruction to execute.
     */
    void execute(int instruction);

    /**
     * @brief Truncates a number to 4 digits.
     * @param num The number to truncate.
     * @return The truncated number.
     */
    int truncate(int num);
};

#endif // UVSIM_H