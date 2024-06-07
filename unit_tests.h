#include <cassert>
#include <vector>
#include "uvsim.h"

void test_uvsim_file1_load() {
    UVSim test;
    test.loadProgram("tests/test1.txt");
    std::vector<int> file = test.mem_freeze();
    assert (file.size() != 0);
}