#include <cassert>
#include <sstream>
#include <iostream>
#include <fstream>
#include "uvsim.h"

void TestSetMemory(std::ofstream& ofile) {
    // 1
    UVSim simulator;
    simulator.setMemory(0, 1001);

    std::vector<int> memory = simulator.getMemory();
    assert(memory[0] == 1001);

    ofile << "TestSetMemory,PASS" << std::endl;
}

void TestLoadProgram(std::ofstream& ofile) {
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

    ofile << "TestLoadProgram,PASS" << std::endl;
}

void TestLoadProgramFail(std::ofstream& ofile) {
    UVSim simulator;

    // Redirect cerr to a string stream to capture the error message
    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    // Try to load a non-existent file
    simulator.loadProgram("FAKE_FILE.txt");

    // Restore the original cerr buffer
    std::cerr.rdbuf(old);
    assert(buffer.str() == "Error: Unable to open file.\n");

    ofile << "TestLoadProgramFail,PASS" << std::endl;
}

void TestAccumulator(std::ofstream& ofile) {
    UVSim simulator;
    simulator.setAccumulator(1002);
    assert(simulator.getAccumulator() == 1002);

    ofile << "TestAccumulator,PASS" << std::endl;
}

void TestHalt(std::ofstream& ofile) {
    UVSim simulator;
    simulator.setHalted(true);
    assert(simulator.isHalted() == true);

    ofile << "TestHalt,PASS" << std::endl;
}

void TestInstructionPointer(std::ofstream& ofile) {
    UVSim simulator;
    assert(simulator.getInstructionPointer() == 0);

    ofile << "TestInstructionPointer,PASS" << std::endl;
}

void TestInstructionPointerIncrement(std::ofstream& ofile) {
    UVSim simulator;
    simulator.run();
    assert(simulator.getInstructionPointer() == 1);

    ofile << "TestInstructionPointerIncrement,PASS" << std::endl;
}

void TestRead(std::ofstream& ofile) {
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

    ofile << "TestRead,PASS" << std::endl;
}

void TestReadFail(std::ofstream& ofile) {
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

    ofile << "TestReadFail,PASS" << std::endl;
}

void TestWrite(std::ofstream& ofile) {
    UVSim simulator;

    std::stringstream output;
    std::streambuf* coutBuf = ofile.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    simulator.setMemory(10, 9);
    simulator.setMemory(0, 1110);
    simulator.setMemory(1, 4300);
    simulator.run();

    std::cout.rdbuf(coutBuf);
    std::cout << output.str() << std::endl;
    assert(output.str() == "Output of location 10: 9\n");

    ofile << "TestWrite,PASS" << std::endl;
}

void TestLoad(std::ofstream& ofile) {
    UVSim simulator;

    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(10, 9);
    simulator.setMemory(0, 2010);
    simulator.setMemory(1, 4300);
    simulator.run();
    assert(simulator.getAccumulator() == 9);

    ofile << "TestLoad,PASS" << std::endl;
}

void TestStore(std::ofstream& ofile) {
    UVSim simulator;

    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(10, 9);
    simulator.setMemory(0, 2010);
    simulator.setMemory(1, 2110);
    simulator.setMemory(2, 4300);
    simulator.run();

    std::vector<int> memory = simulator.getMemory();
    assert(memory[10] == 9);

    ofile << "TestStore,PASS" << std::endl;
}

void TestBranch(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(0, 4002);
    // Branch to memory location 2
    // ignore the next two instructions
    simulator.setMemory(10, 9);
    simulator.setMemory(1, 2010);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == 0);

    ofile << "TestBranch,PASS" << std::endl;
}

void TestAdd(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 9);
    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(0, 3010);
    simulator.setMemory(2, 4300);
    simulator.run();
    assert(simulator.getAccumulator() == 9);

    ofile << "TestAdd,PASS" << std::endl;
}

void TestSubtract(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 9);
    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(0, 3110);
    simulator.setMemory(2, 4300);
    simulator.run();
    assert(simulator.getAccumulator() == -9);

    ofile << "TestSubtract,PASS" << std::endl;
}

void TestMultiply(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 9);
    simulator.setAccumulator(10);
    simulator.setMemory(0, 3310);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == 90);

    ofile << "TestMultiply,PASS" << std::endl;
}

void TestDivide(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 5);
    simulator.setAccumulator(10);
    simulator.setMemory(0, 3210);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == 2);

    ofile << "TestDivide,PASS" << std::endl;
}

void TestBranchNeg(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setAccumulator(-10);
    simulator.setMemory(0, 4102);
    // Branch to memory location 2
    // ignore the next two instructions
    simulator.setMemory(10, 9);
    simulator.setMemory(1, 2010);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == -10);

    ofile << "TestBranchNeg,PASS" << std::endl;
}

void TestBranchZero(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setAccumulator(0);
    simulator.setMemory(0, 4202);
    // Branch to memory location 2
    // ignore the next two instructions
    simulator.setMemory(10, 9);
    simulator.setMemory(1, 2010);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == 0);

    ofile << "TestBranchZero,PASS" << std::endl;
}

void TestDivideFail(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 0);
    simulator.setMemory(0, 3210);
    simulator.setMemory(2, 4300);

    std::stringstream errorStream;
    std::streambuf* oldCerrBuf = std::cerr.rdbuf(errorStream.rdbuf());
    simulator.run();

    std::cerr.rdbuf(oldCerrBuf);
    std::string errorStr = errorStream.str();
    assert(errorStr == "Error: Division by zero.\n");

    ofile << "TestDivideFail,PASS" << std::endl;
}

int main() {
    std::ofstream outfile("test-output.csv");
    if (!outfile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    outfile << "Test Name,Passed" << std::endl;
    TestSetMemory(outfile);
    TestLoadProgram(outfile);
    TestLoadProgramFail(outfile);
    TestAccumulator(outfile);
    TestHalt(outfile);
    TestInstructionPointer(outfile);
    TestInstructionPointerIncrement(outfile);
    TestRead(outfile);
    TestReadFail(outfile);
    TestWrite(outfile);
    TestLoad(outfile);
    TestStore(outfile);
    TestBranch(outfile);
    TestAdd(outfile);
    TestSubtract(outfile);
    TestMultiply(outfile);
    TestDivide(outfile);
    TestBranchNeg(outfile);
    TestBranchZero(outfile);
    TestDivideFail(outfile);

    outfile.close();
    std::cout << "All tests have passed!" << std::endl;

    return 0;
}
