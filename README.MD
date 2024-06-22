# Group Project Milestone 2: UVSim

## Overview
The UVSim is a simple virtual machine, but powerful. The UVSim can only interpret a machine language called BasicML.

## Features
- **Memory Management**: Simulates a 100-word memory.
- **I/O Operations**: Allows reading from and writing to the standard input/output.
- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Control Flow**: Includes operations like branch, branch-if-negative, and branch-if-zero.

## GUI Interface
The UVSim includes a graphical user interface for enhanced usability. The GUI features buttons for loading and executing files, entering input, and clearing the output. Below is a description of the GUI components:

- **Load File**: Button to load a file into the UVSim.
- **Execute File**: Button to execute the loaded file.
- **Type**: Text field to enter input for the UVSim.
- **Enter**: Button to input integers into the UVSim.
- **Clear Output**: Button to clear the output display.
- **Output**: Text area to display the output of the UVSim.
- **Instruments**: Text area to display instructions.

## Prerequisites
- C++ Compiler
- QT6 (currently using latest 6.7.1)

## Installation
To compile and run UVSim, follow these steps:

1. Clone this repository or download the source code.
   ```bash
   git clone https://github.com/DavidADeLeo/CS2450
   cd CS2450
   ```
2. Compile the source code.
   ```bash
    g++ -o uvsim main.cpp uvsim.cpp uvsimArithmetic.cpp uvsimControl.cpp uvsimIO.cpp
    ```
3. Run the executable file.

## Usage
1. Loading a Program
   - **Open the File Menu**: Click on Load File in the top lefthand corner.
   - **Select Load Program**: When prompted, enter the name of the file you wish to load into the UVSim program and hit Enter.

2. Running the Program
   - **Run Button**: Click the Execute File button to run the program.
   - **Instruments Panel**: Reference Instruments righthand panel for program instructions and steps.
   - **Output Window**: Follow the prompts in the Output window.



## Output Example
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

## Unit Tests
To run the unit tests, follow these steps:
```bash
g++ -o test uvsim.cpp uvsimArithmetic.cpp uvsimControl.cpp uvsimIO.cpp test.cpp
./test
```
Check the output and CSV file to see if the tests passed.

## Authors
- Alexander Nin
- David De Leo
- Jess Smith
- Zhihui Chen
