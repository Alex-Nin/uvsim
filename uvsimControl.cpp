#include "uvsimControl.h"

int Control::branch(int operand) {
    return operand;
}

int Control::branchNeg(int operand, int &instructionPointer, int accumulator) {
    if (accumulator < 0) {
        return branch(operand);
    }
    return instructionPointer;
}

int Control::branchZero(int operand, int &instructionPointer, int accumulator) {
    if (accumulator == 0) {
        return branch(operand);
    }
    return instructionPointer;
}