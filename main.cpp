// Created by Alex

#include <iostream>
#include <vector>
#include <iomanip>
#include "uvsim.h"

int main() {
    UVSim simulator;
    std::string inputFile = simulator.promptFile();
    simulator.loadProgram(inputFile);
//    simulator.dump(); // used for debugging
    simulator.run();
//    simulator.dump(); // used for debugging
    return 0;
}
