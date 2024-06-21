#include "uvsimArithmetic.h"
#include <stdexcept>

int Arithmetic::truncate(int num) {
    if (num > 9999) {
        return num % 10000;
    } else if (num < -9999) {
        return -(-num % 10000);
    }
    return num;
}

int Arithmetic::add(int acc, int value) {
    return truncate(acc + value);
}

int Arithmetic::subtract(int acc, int value) {
    return truncate(acc - value);
}

int Arithmetic::multiply(int acc, int value) {
    return truncate(acc * value);
}

int Arithmetic::divide(int acc, int value) {
    if (value != 0) {
        return truncate(acc / value);
    } else {
        throw std::runtime_error("Error: Division by zero.");
    }
}