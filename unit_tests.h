#include <cassert>
#include <vector>
#include "uvsim.h"

void TestUVSimMemoryAccessorMethods() {
    UVSim simulator;
    simulator.setMemory(1001);

    auto memory = simulator.getMemory();
    assert (memory[0] == 1001);
}

// void TestUVSimAccumulatorAccessorMethods() {
//     UVSim simulator;
//     simulator.setAccumulator(1002);
//     assert (simulator.getAccumulator() == 1002);
// }

// void TestUVSimHaltedAccessorMethods() {
//     UVSim simulator;
//     simulator.setHalted(true);

//     assert (simulator.isHalted() == true);
// }

// void TestLoadProgramSuccess() {
//     UVSim simulator;

//     simulator.loadProgram("test1.txt");

//     //Returns memory vector using accessor method and saves it to memory variable
//     auto memory = simulator.getMemory();

//     assert (memory[0] == 1007);
//     assert (memory[1] == 1008);
//     assert (memory[2] == 2007);
//     assert (memory[3] == 2008);
//     assert (memory[4] == 2109);
//     assert (memory[5] == 1109);
//     assert (memory[6] == 4300);
//     assert (memory[7] == 0000);
//     assert (memory[8] == 0000);
//     assert (memory[9] == 0000);

// }

// void TestLoadProgramFail() {
//     UVSim simulator;
    
//     // Redirect cerr to a string stream to capture the error message
//     stringstream buffer;
//     streambuf* old = cerr.rdbuf(buffer.rdbuf());

//     // Try to load a non-existent file
//     simulator.loadProgram("FAKE_FILE.txt");

//     // Restore the original cerr buffer
//     cerr.rdbuf(old);

//     assert (buffer.str() == "Error: Unable to open file.\n");
// }

// //Needs to be finished
// void TestUVSimFetch() {
//     UVSim simulator;

//     simulator.loadProgram("test1.txt");

//     simulator.run();
//     assert ();
// }

// //Needs to be finished
// void TestUVSimExecute() {
//     UVSim simulator;

//     simulator.loadProgram("test1.txt");

//     simulator.run();
//     assert ();
// }

// void TestUVSimRun() {
//     UVSim simulator;

//     simulator.loadProgram("test1.txt");

//     simulator.run();
//     assert (simulator.isHalted());
// }

// void TestUVSimReadSuccess() {
//     UVSim simulator;
//     simulator.setMemory(1004);

//     stringstream input("123\n");
//     streambuf* oldCinBuf = cin.rdbuf(input.rdbuf());
    
//     stringstream errorStream;
//     streambuf* oldCerrBuf = cerr.rdbuf(errorStream.rdbuf());

//     simulator.run();

//     // Reset std::cout back to its original buffer
//     cin.rdbuf(oldCinBuf);
//     cerr.rdbuf(oldCerrBuf);

//     // Verify the contents of the stringstream
//     assert (errorStream.str().empty());
// }

// void TestUVSimReadFail() {
//     UVSim simulator;
//     simulator.setMemory(1004);
    
 
//     stringstream input("");
//     streambuf* oldCinBuf = cin.rdbuf(input.rdbuf());

//     stringstream errorStream;
//     streambuf* oldCerrBuf = cerr.rdbuf(errorStream.rdbuf());

//     simulator.run();

//     // Reset cin back to its original buffer
//     cin.rdbuf(oldCinBuf);
//     cerr.rdbuf(oldCerrBuf);

//     assert (errorStream.str() == "Invalid input detected. Halting program.");
// }


// void TestUVSimStore() {
//     UVSim simulator;
//     simulator.setMemory(2100);

//     simulator.run();

//     auto memory = simulator.getMemory();

//     assert (memory[0] == 0);
// }

// void TestUVSimWrite() {
//     UVSim simulator;
//     simulator.setMemory(2000);

//     stringstream output;
//     streambuf* oldCoutBuf = cout.rdbuf(output.rdbuf());

//     simulator.run();

//     cout.rdbuf(oldCoutBuf);
    
//     assert (output.str() == "Output of location: 0: 2000\n");
// }

// void TestLoad() {
//     UVSim simulator;
//     simulator.setMemory(2000);
//     simulator.run();

//     assert (simulator.getAccumulator() == 0);
// }

// void TestAdd() {
//     UVSim simulator;
//     simulator.setMemory(3000);
//     simulator.setAccumulator(4000);
//     simulator.run();

//     assert (simulator.getAccumulator() == 9000);
// }

// void TestSubtract() {
//     UVSim simulator;
//     simulator.setMemory(3100);
//     simulator.setAccumulator(2000);
//     simulator.run();

//     assert (simulator.getAccumulator() == 1000);
// }

// void TestDivideSuccess() {
//     UVSim simulator;
//     simulator.setMemory(3200);
//     simulator.setAccumulator(10000);
//     simulator.run();
    
//     assert (simulator.getAccumulator() == 3);
// }

// void TestDivideFail() {
//     UVSim simulator;
//     simulator.setMemory(3200);
//     simulator.setAccumulator(0);

//     stringstream errorStream;
//     streambuf* oldCerrBuf = cerr.rdbuf(errorStream.rdbuf());
//     simulator.run();
//     cerr.rdbuf(oldCerrBuf);

//     assert (errorStream.str() == "Error: Division by zero.\n");
// }

// void TestMultiply() {
//     UVSim simulator;
//     simulator.setMemory(3300);
//     simulator.setAccumulator(2);
//     simulator.run();

//     assert (simulator.getAccumulator() == 6600);

// }

// void TestBranch() {
//     UVSim simulator;
//     simulator.setMemory(4010);
//     simulator.run();

//     assert (simulator.getInstructionPointer() == 10);
    
// }

// void TestBranchNeg() {
//     UVSim simulator;
//     simulator.setMemory(4101);
//     simulator.setAccumulator(-1);
//     simulator.run();

//     assert (simulator.getAccumulator() == 1);
    
// }

// void TestBranchZero() {
//     UVSim simulator;
//     simulator.setMemory(4205);
//     simulator.setAccumulator(0);
//     simulator.run();

//     assert (simulator.getAccumulator() == 5);

// }

// void TestHalt() {
//     UVSim simulator;
//     simulator.setMemory(4300);
//     simulator.run();

//     assert (simulator.isHalted() == true);
    
// }

// void TestUVSimDump() {
//     UVSim simulator;


//     assert ()
// }
