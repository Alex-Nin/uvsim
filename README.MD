# Group Project Milestone 2: UVSim

## Overview
The UVSim is a simple virtual machine, but powerful. The UVSim can only interpret a machine language called BasicML.

## Features
- **Memory Management**: Simulates a 100-word memory.
- **I/O Operations**: Allows reading from and writing to the standard input/output.
- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Control Flow**: Includes operations like branch, branch-if-negative, and branch-if-zero.

## Prerequisites
- C++ Compiler

## Installation
To compile and run UVSim, follow these steps:

1. Clone this repository or download the source code.
   ```bash
   git clone https://github.com/DavidADeLeo/CS2450
   cd CS2450
   ```
2. Compile the source code.
   ```bash
    g++ -o uvsim main.cpp uvsim.cpp
    ```
3. Run the executable file.
4. Follow the instructions to run the UVSim.

## Example Usage
```bash
Please enter the name of the file you would like to load: testFile/test1.txt
Enter an integer:7
Enter an integer:8
Output of location: 10: 8
REGISTERS:
accumulator: -1
instructionPointer: 9
MEMORY:
1009 1010 2009 3110 4107 1109 4300 1110 4300    7
   8    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0
```

## Authors
- Alexander Nin
- David De Leo
- Jess Smith
- Zhihui Chen
