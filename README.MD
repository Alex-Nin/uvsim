# Group Project Milestone 4: UVSim

![main_window](screenshots%2Fmain_window.png)

## Overview
The UVSim is a simple virtual machine, but powerful. The UVSim can only interpret a machine language called BasicML.

## Features
- **Memory Management**: Simulates a 100-word memory.
- **I/O Operations**: Allows reading from and writing to the standard input/output.
- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Control Flow**: Includes operations like branch, branch-if-negative, and branch-if-zero.

## GUI Interface
The UVSim includes a graphical user interface for enhanced usability. The GUI features buttons for loading and executing files, entering input, and clearing the output. Below is a description of the GUI components:

- **Set Default Colors**: Button to set the default colors for the GUI.
- **Change Colors**: Button to change the colors of the GUI.
- **Load File**: Button to load a file into the UVSim.
- **Execute File**: Button to execute the loaded file.
- **Save As**: Button to save the instruction to a file.
- **Clear Output**: Button to clear the output display.
- **Console**: Text area to display the console output.
- **Editor**: Text area to add/edit the instruction.
- **Enter data here**: Text field to enter input for the UVSim.
- **Lines**: Text area to display the instruction lines.

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
2. Load CMakeLists.txt in QT Creator.
3. Click on the green play button to compile and run the program.

## Usage
1. Loading a Program
   - **Open the File Menu**: Click on Load File in the top lefthand corner.
   - **Select Load Program**: When prompted, select the file you wish to load into the UVSim program and hit Enter.

2. Running the Program
   - **Run Button**: Click the Execute File button to run the program.
   - **Instruments Panel**: Reference Instruments righthand panel for program instructions and steps.
   - **Output Window**: Follow the prompts in the Output window.

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
