#define CATCH_CONFIG_MAIN
#include "uvsim.cpp"
#include <sstream>
#include <catch2/catch_all.hpp>

using namespace std;

TEST_CASE("TestUVSimMemoryAccessorMethods") {
    UVSim simulator;
    simulator.setMemory(1001);

    auto memory = simulator.getMemory();
    REQUIRE(memory[0] == 1001);
}

TEST_CASE("TestUVSimAccumulatorAccessorMethods") {
    UVSim simulator;
    simulator.setAccumulator(1002);
    REQUIRE(simulator.getAccumulator() == 1002);
}

TEST_CASE("TestUVSimHaltedAccessorMethods") {
    UVSim simulator;
    simulator.setHalted(true);

    REQUIRE(simulator.isHalted() == true);
}

TEST_CASE("TestLoadProgramSuccess") {
    UVSim simulator;

    simulator.loadProgram("test1.txt");

    //Returns memory vector using accessor method and saves it to memory variable
    auto memory = simulator.getMemory();

    REQUIRE(memory[0] == 1007);
    REQUIRE(memory[1] == 1008);
    REQUIRE(memory[2] == 2007);
    REQUIRE(memory[3] == 2008);
    REQUIRE(memory[4] == 2109);
    REQUIRE(memory[5] == 1109);
    REQUIRE(memory[6] == 4300);
    REQUIRE(memory[7] == 0000);
    REQUIRE(memory[8] == 0000);
    REQUIRE(memory[9] == 0000);

}

TEST_CASE("TestLoadProgramFail") {
    UVSim simulator;

    // Redirect cerr to a string stream to capture the error message
    stringstream buffer;
    streambuf* old = cerr.rdbuf(buffer.rdbuf());

    // Try to load a non-existent file
    simulator.loadProgram("FAKE_FILE.txt");

    // Restore the original cerr buffer
    cerr.rdbuf(old);

    REQUIRE(buffer.str() == "Error: Unable to open file.\n");
}

//Needs to be finished
TEST_CASE("TestUVSimFetch") {
    UVSim simulator;

    simulator.loadProgram("test1.txt");

    simulator.run();
    REQUIRE();
}

//Needs to be finished
TEST_CASE("TestUVSimExecute") {
    UVSim simulator;

    simulator.loadProgram("test1.txt");

    simulator.run();
    REQUIRE();
}

TEST_CASE("TestUVSimRun") {
    UVSim simulator;

    simulator.loadProgram("test1.txt");

    simulator.run();
    REQUIRE(simulator.isHalted());
}

TEST_CASE("TestUVSimReadSuccess") {
    UVSim simulator;
    simulator.setMemory(1004);

    stringstream input("123\n");
    streambuf* oldCinBuf = cin.rdbuf(input.rdbuf());

    stringstream errorStream;
    streambuf* oldCerrBuf = cerr.rdbuf(errorStream.rdbuf());

    simulator.run();

    // Reset std::cout back to its original buffer
    cin.rdbuf(oldCinBuf);
    cerr.rdbuf(oldCerrBuf);

    // Verify the contents of the stringstream
    REQUIRE(errorStream.str().empty());
}

TEST_CASE("TestUVSimReadFail") {
    UVSim simulator;
    simulator.setMemory(1004);


    stringstream input("");
    streambuf* oldCinBuf = cin.rdbuf(input.rdbuf());

    stringstream errorStream;
    streambuf* oldCerrBuf = cerr.rdbuf(errorStream.rdbuf());

    simulator.run();

    // Reset cin back to its original buffer
    cin.rdbuf(oldCinBuf);
    cerr.rdbuf(oldCerrBuf);

    REQUIRE(errorStream.str() == "Invalid input detected. Halting program.");
}


TEST_CASE("TestUVSimStore") {
    UVSim simulator;
    simulator.setMemory(2100);

    simulator.run();

    auto memory = simulator.getMemory();

    REQUIRE(memory[0] == 0);
}

TEST_CASE("TestUVSimWrite") {
    UVSim simulator;
    simulator.setMemory(2000);

    stringstream output;
    streambuf* oldCoutBuf = cout.rdbuf(output.rdbuf());

    simulator.run();

    cout.rdbuf(oldCoutBuf);

    REQUIRE(output.str() == "Output of location: 0: 2000\n");
}

TEST_CASE("TestLoad") {
    UVSim simulator;
    simulator.setMemory(2000);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 0);
}

TEST_CASE("TestAdd") {
    UVSim simulator;
    simulator.setMemory(3000);
    simulator.setAccumulator(4000);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 9000);
}

TEST_CASE("TestSubtract") {
    UVSim simulator;
    simulator.setMemory(3100);
    simulator.setAccumulator(2000);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 1000);
}

TEST_CASE("TestDivideSuccess") {
    UVSim simulator;
    simulator.setMemory(3200);
    simulator.setAccumulator(10000);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 3);
}

TEST_CASE("TestDivideFail") {
    UVSim simulator;
    simulator.setMemory(3200);
    simulator.setAccumulator(0);

    stringstream errorStream;
    streambuf* oldCerrBuf = cerr.rdbuf(errorStream.rdbuf());
    simulator.run();
    cerr.rdbuf(oldCerrBuf);

    REQUIRE(errorStream.str() == "Error: Division by zero.\n");
}

TEST_CASE("TestMultiply") {
    UVSim simulator;
    simulator.setMemory(3300);
    simulator.setAccumulator(2);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 6600);

}

TEST_CASE("TestBranch") {
    UVSim simulator;
    simulator.setMemory(4010);
    simulator.run();

    REQUIRE(simulator.getInstructionPointer() == 10);

}

TEST_CASE("TestBranchNeg") {
    UVSim simulator;
    simulator.setMemory(4101);
    simulator.setAccumulator(-1);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 1);

}

TEST_CASE("TestBranchZero") {
    UVSim simulator;
    simulator.setMemory(4205);
    simulator.setAccumulator(0);
    simulator.run();

    REQUIRE(simulator.getAccumulator() == 5);

}

TEST_CASE("TestHalt") {
    UVSim simulator;
    simulator.setMemory(4300);
    simulator.run();

    REQUIRE(simulator.isHalted() == true);

}

TEST_CASE("TestUVSimDump") {
    UVSim simulator;


    REQUIRE();
}
