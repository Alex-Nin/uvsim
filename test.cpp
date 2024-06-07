#include <cassert>
#include <sstream>
#include <iostream>
#include "uvsim.h"

void test1() {
    UVSim simulator;
    simulator.setMemory(0, 1001);

    auto memory = simulator.getMemory();
    assert(memory[0] == 1001);
}

int main() {
    test1();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
