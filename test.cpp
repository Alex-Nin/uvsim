#include <cassert>
#include <sstream>
#include <iostream>
#include "uvsim.h"

void TestSetMemory() {
    UVSim simulator;
    simulator.setMemory(0, 1001);

    std::vector<int> memory = simulator.getMemory();
    assert(memory[0] == 1001);

    std::cout << "1. TestSetMemory passed!" << std::endl;
}

void TestLoadProgram() {
    UVSim simulator;
    simulator.loadProgram("testFiles/test1.txt");

    std::vector<int> memory = simulator.getMemory();
    assert(memory[0] == 1007);
    assert(memory[1] == 1008);
    assert(memory[2] == 2007);
    assert(memory[3] == 2008);
    assert(memory[4] == 2109);
    assert(memory[5] == 1109);
    assert(memory[6] == 4300);
    assert(memory[7] == 0000);

    std::cout << "2. TestLoadProgram passed!" << std::endl;
}

void TestLoadProgramFail() {
    UVSim simulator;

    // Redirect cerr to a string stream to capture the error message
    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    // Try to load a non-existent file
    simulator.loadProgram("FAKE_FILE.txt");

    // Restore the original cerr buffer
    std::cerr.rdbuf(old);
    assert(buffer.str() == "Error: Unable to open file.\n");

    std::cout << "3. TestLoadProgramFail passed!" << std::endl;
}

void TestAccumulator() {
    UVSim simulator;
    simulator.setAccumulator(1002);
    assert(simulator.getAccumulator() == 1002);

    std::cout << "4. TestAccumulator passed!" << std::endl;
}

void TestHalt() {
    UVSim simulator;
    simulator.setHalted(true);
    assert(simulator.isHalted() == true);

    std::cout << "5. TestHalt passed!" << std::endl;
}

void TestInstructionPointer() {
    UVSim simulator;
    assert(simulator.getInstructionPointer() == 0);

    std::cout << "6. TestInstructionPointer passed!" << std::endl;
}

void TestInstructionPointerIncrement() {
    UVSim simulator;
    simulator.run();
    assert(simulator.getInstructionPointer() == 1);

    std::cout << "7. TestInstructionPointerIncrement passed!" << std::endl;
}

void TestRead() {
    UVSim simulator;

    std::stringstream input("7\n");
    std::streambuf* cinBuf = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    simulator.setMemory(0, 1010);
    simulator.setMemory(1, 4300);
    simulator.run();

    std::cin.rdbuf(cinBuf);

    std::vector<int> memory = simulator.getMemory();
    assert(memory[10] == 7);

    std::cout << "8. TestRead passed!" << std::endl;
}

void TestReadFail() {
    UVSim simulator;

    std::stringstream input("a\n");
    std::cin.rdbuf(input.rdbuf());

    simulator.setMemory(0, 1010);
    simulator.setMemory(1, 4300);

    std::string errorStr;
    try {
        simulator.run();
    } catch (const std::runtime_error& e) {
        errorStr = e.what();
    }

    assert(errorStr == "Invalid input detected. Halting program.");

    std::cout << "9. TestReadFail passed!" << std::endl;
}

void TestWrite() {
    UVSim simulator;

    std::stringstream output;
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    simulator.setMemory(10, 9);
    simulator.setMemory(0, 1110);
    simulator.setMemory(1, 4300);
    simulator.run();

    std::cout.rdbuf(coutBuf);
    assert(output.str() == "Output of location: 10: 9\n");

    std::cout << "10. TestWrite passed!" << std::endl;
}

int main() {
//    TestSetMemory();
//    TestLoadProgram();
//    TestLoadProgramFail();
//    TestAccumulator();
//    TestHalt();
//    TestInstructionPointer();
//    TestInstructionPointerIncrement();
//    TestRead();
//    TestReadFail();
    TestWrite();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
