#ifndef UVSIM_CONTROL_H
#define UVSIM_CONTROL_H

class Control {
public:
    /**
     * @brief Branch operation. Set the instruction pointer to the operand.
     * @param operand The memory location to branch to.
     */
    int branch(int operand);

    /**
     * @brief Branch operation. Set the instruction pointer to the operand if the accumulator is negative.
     * @param operand The memory location to branch to.
     */
    int branchNeg(int operand, int &instructionPointer, int accumulator);

    /**
     * @brief Branch operation. Set the instruction pointer to the operand if the accumulator is zero.
     * @param operand The memory location to branch to.
     */
    int branchZero(int operand, int &instructionPointer, int accumulator);
};

#endif //UVSIM_CONTROL_H
