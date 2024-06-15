// Created by Alex

#include "uvsim.h"

int main() {
    UVSim simulator;
    std::string inputFile = simulator.promptFile();
    simulator.loadProgram(inputFile);
    simulator.run();
//    simulator.dump(); // used for debugging
    return 0;
}
