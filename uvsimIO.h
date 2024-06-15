#include "string"

#ifndef UVSIM_IO_H
#define UVSIM_IO_H

class IO {
public:
    /**
     * @brief I/O operation. Read a word from the keyboard into a specific location in memory.
     */
    int read(int operand);

    /**
     * @brief I/O operation. Write a word from a specific location in memory to screen.
     */
    void write(int operand, int value);

    /**
     * @brief Prompts the user for a file name to load.
     * @return The name of the file to load.
     */
    static std::string promptFile();
};

#endif //UVSIM_IO_H
