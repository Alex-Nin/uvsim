#include <cassert>
#include <sstream>
#include <iostream>
#include <fstream>
#include "uvsim.h"
#include "uvsimArithmetic.h"
#include "uvsimControl.h"
#include "uvsimIO.h"

void TestSetMemory(std::ofstream& ofile) {
    UVSim simulator;
    simulator.setMemory(0, 1001);

    std::vector<int> memory = simulator.getMemory();
    assert(memory[0] == 1001);

    ofile << "Set Memory,TestSetMemory,Test if memory can be set,register 0 = 1001,register 0 = 1001,PASS" << std::endl;
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

    ofile << "Load Program,TestLoadProgram,Test if the file can be loaded successfully,test1.txt,register 0 = 1007 ... register 7 = 0000,PASS" << std::endl;
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

    ofile << "Read File Fail,TestLoadProgramFail,Test if a non-existing file reports an error,FAKE_FILE.txt,error message,PASS" << std::endl;
}

void TestAccumulator(std::ofstream& ofile) {
    UVSim simulator;
    simulator.setAccumulator(1002);
    assert(simulator.getAccumulator() == 1002);

    ofile << "Accumulator,TestAccumulator,Test whether the accumulator can be set to a value,accumulator = 1002, accumulator = 1002,PASS" << std::endl;
}

void TestHalt(std::ofstream& ofile) {
    UVSim simulator;
    simulator.setHalted(true);
    assert(simulator.isHalted() == true);

    ofile << "Halt,TestHalt,Test to see if halt works,N/A,halt program,PASS" << std::endl;
}

void TestInstructionPointer(std::ofstream& ofile) {
    UVSim simulator;
    assert(simulator.getInstructionPointer() == 0);

    ofile << "Instruction Pointer,TestInstructionPointer,Test to see if the instruction pointer's value can be obtained,N/A,instructionPointer = 0,PASS" << std::endl;
}

void TestInstructionPointerIncrement(std::ofstream& ofile) {
    UVSim simulator;
    simulator.run();
    assert(simulator.getInstructionPointer() == 1);

    ofile << "Instruction Pointer Increment,TestInstructionPointerIncrement,Tests whether the value of the instruction pointer can be modified,instructionPointer = 1,instructionPointer = 1,PASS" << std::endl;
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

    ofile << "Read,TestRead,Test that the input values are stored correctly,input = 7,memory 10 = 7,PASS" << std::endl;
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

    ofile << "Read Fail,TestReadFail,Test to see if an error can be thrown if the input value is abnormal,input = a,error message,PASS" << std::endl;
}

void TestWrite(std::ofstream& ofile) {
    UVSim simulator;

    std::stringstream output;
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    simulator.setMemory(10, 9);
    simulator.setMemory(0, 1110);
    simulator.setMemory(1, 4300);
    simulator.run();

    std::cout.rdbuf(coutBuf);
    assert(output.str() == "Output of location 10: 9\n");

    ofile << "Write,TestWrite,Test to see if the value in memory can be read correctly,N/A,memory 10 = 9,PASS" << std::endl;
}

void TestLoad(std::ofstream& ofile) {
    UVSim simulator;

    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(10, 9);
    simulator.setMemory(0, 2010);
    simulator.setMemory(1, 4300);
    simulator.run();
    assert(simulator.getAccumulator() == 9);

    ofile << "Load,TestLoad,Tests if the value can be read and added to the accumulator,N/A,accumulator = 9,PASS" << std::endl;
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

    ofile << "Store,TestStore,Test to see if the value in the accumulator can be saved to memory,N/A,memory 10 = 9,PASS" << std::endl;
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

    ofile << "Branch,TestBranch,Test to see if function can jump to the correct address,N/A,accumulator = 0,PASS" << std::endl;
}

void TestAdd(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 9);
    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(0, 3010);
    simulator.setMemory(2, 4300);
    simulator.run();
    assert(simulator.getAccumulator() == 9);

    ofile << "Add,TestAdd,Test that the addition works and gives the correct answer,memory 10 = 9,accumulator = 9,PASS" << std::endl;
}

void TestSubtract(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 9);
    assert(simulator.getAccumulator() == 0);
    simulator.setMemory(0, 3110);
    simulator.setMemory(2, 4300);
    simulator.run();
    assert(simulator.getAccumulator() == -9);

    ofile << "Subtract,TestSubtract,Test that subtraction works and gives the correct answer,memory 10 = 9,accumulator = -9,PASS" << std::endl;
}

void TestMultiply(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 9);
    simulator.setAccumulator(10);
    simulator.setMemory(0, 3310);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == 90);

    ofile << "Multiply,TestMultiply,Test that the multiplication works and gives the correct answer,memory 10 = 9; accumulator = 10,accumulator = 90,PASS" << std::endl;
}

void TestDivide(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 5);
    simulator.setAccumulator(10);
    simulator.setMemory(0, 3210);
    simulator.setMemory(2, 4300);
    simulator.run();

    assert(simulator.getAccumulator() == 2);

    ofile << "Divide,TestDivide,Test that the division works and gives the correct answer,memory 10 = 5; accumulator = 10,accumulator = 2,PASS" << std::endl;
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

    ofile << "Branch Negative,TestBranchNeg,Tests if the function can be executed when the accumulator is negative,accumulator = -10,accumulator = -10,PASS" << std::endl;
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

    ofile << "Branch Zero,TestBranchZero,Tests if the function can be executed when the accumulator is 0,accumulator = 0,accumulator = 0,PASS" << std::endl;
}

void TestDivideFail(std::ofstream& ofile) {
    UVSim simulator;

    simulator.setMemory(10, 0);
    simulator.setMemory(0, 3210);
    simulator.setMemory(2, 4300);

    std::string errorStr;
    try {
        simulator.run();
    } catch (const std::runtime_error& e) {
        errorStr = e.what();
    }

    assert(errorStr == "Error: Division by zero.");

    ofile << "Divide Fail,TestDivideFail,Tests whether an error can be thrown when calculating division if the value is illegal,memory 10 = 0; accumulator = 0,error message,PASS" << std::endl;
}

int main() {
    std::ofstream outfile("test-output.csv");
    if (!outfile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    outfile << "Test Name,Reference,Description,Inputs,Expected Outputs,PASSed" << std::endl;
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
