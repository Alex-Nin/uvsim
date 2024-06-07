#include <cassert>
#include <sstream>
#include <iostream>
#include "uvsim.h"

void TestSetMemory() {
    UVSim simulator;
    simulator.setMemory(0, 1001);

    auto memory = simulator.getMemory();
    assert(memory[0] == 1001);
}

void TestLoadProgram() {
    UVSim simulator;
    simulator.loadProgram("testFiles/test1.txt");

    auto memory = simulator.getMemory();
    assert(memory[0] == 1007);
    assert(memory[1] == 1008);
    assert(memory[2] == 2007);
    assert(memory[3] == 2008);
    assert(memory[4] == 2109);
    assert(memory[5] == 1109);
    assert(memory[6] == 4300);
    assert(memory[7] == 0000);
}

int main() {
    TestSetMemory();
    TestLoadProgram();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
