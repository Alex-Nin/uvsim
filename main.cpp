// Created by Alex

#include "uvsim.h"
#include "uvsimIO.h"

int main() {
    UVSim simulator;
    std::string inputFile = IO::promptFile();
    simulator.loadProgram(inputFile);
    simulator.run();
//    simulator.dump(); // used for debugging
    return 0;
}
