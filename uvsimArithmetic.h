#ifndef UVSIM_ARITHMETIC_H
#define UVSIM_ARITHMETIC_H

class Arithmetic {
public:
    /**
     * @brief Arithmetic operation. Add the value at the operand location to the accumulator.
     * @param acc The value of the accumulator.
     * @param value The value to add to the accumulator.
     * @return The new value of the accumulator.
     */
    int add(int acc, int value);

    /**
     * @brief Arithmetic operation. Subtract the value at the operand location from the accumulator.
     * @param acc The value of the accumulator.
     * @param value The value to subtract from the accumulator.
     * @return The new value of the accumulator.
     */
    int subtract(int acc, int value);

    /**
     * @brief Arithmetic operation. Multiply the value at the operand location with the accumulator.
     * @param acc The value of the accumulator.
     * @param value The value to multiply with the accumulator.
     * @return The new value of the accumulator.
     */
    int multiply(int acc, int value);

    /**
     * @brief Arithmetic operation. Divide the value at the operand location from the accumulator.
     * @param acc The value of the accumulator.
     * @param value The value to divide the accumulator by.
     * @return The new value of the accumulator.
     */
    int divide(int acc, int value);

private:
    /**
     * @brief Truncates a number to 4 digits.
     * @param num The number to truncate.
     * @return The truncated number.
     */
    int truncate(int num);
};

#endif //UVSIM_ARITHMETIC_H
