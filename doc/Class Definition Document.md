# UVSim Class Definition Document

## Overview
This document provides a detailed outline of each class in the UVSim project.

---

## Class Definitions

### Class: `UVSim`
**Purpose**: Serves as the core of UVSim.

#### Methods

- **loadProgram**
    - **Description**: Loads a program from a specified file into the simulator's memory, parsing and storing instructions.
    - **Input**: `filename` - Path to the file containing the program.
    - **Post-conditions**: The program is loaded into memory.

- **getMemory**
    - **Description**: Retrieves the current state of memory, primarily for testing and debugging purposes.
    - **Output**: `std::vector<int>` - A copy of the memory vector.
    - **Post-conditions**: Returns the current state without modifying it.

- **setMemory**
    - **Description**: Sets a memory cell at a specified index to a new value, useful for testing and initialization.
    - **Input**: `index` - Memory index to modify; `value` - New value to set.
    - **Pre-conditions**: Index must be within the range of the memory vector.
    - **Post-conditions**: The memory at the given index is updated.

- **clearMemory**
    - **Description**: Clears the memory of the simulator, setting all cells to zero.
    - **Post-conditions**: All memory cells are set to zero.

- **getAccumulator**
    - **Description**: Accesses the current value of the accumulator.
    - **Output**: `int` - The current value of the accumulator.

- **setAccumulator**
    - **Description**: Sets the accumulator to a specified value, used for testing or initialization.
    - **Input**: `num` - New value for the accumulator.
    - **Post-conditions**: The accumulator is updated to the new value.

- **isHalted**
    - **Description**: Checks if the simulator's execution has been halted.
    - **Output**: `bool` - True if execution is halted, otherwise false.

- **setHalted**
    - **Description**: Sets the halted state of the simulator, controlling the continuation or termination of execution.
    - **Input**: `halt` - Boolean value to set the halted state.
    - **Post-conditions**: The halted state is updated.

- **getInstructionPointer**
    - **Description**: Retrieves the current position of the instruction pointer, which indicates the next instruction to execute.
    - **Output**: `int` - Current value of the instruction pointer.

- **setInstructionPointer**
    - **Description**: Sets the instruction pointer to a specified value, used for testing or initialization.
    - **Input**: `ip` - New value for the instruction pointer.
    - **Post-conditions**: The instruction pointer is updated to the new value.

- **run**
    - **Description**: Initiates the simulation, executing loaded instructions until halted.
    - **Pre-conditions**: A program must be loaded into memory.
    - **Post-conditions**: Executes the program until completion or halt.

- **dump**
    - **Description**: Outputs the current state of the memory and registers for debugging.
    - **Post-conditions**: The state of memory and registers is printed to the output.

- **load**
    - **Description**: Loads the content of a memory location into the accumulator.
    - **Input**: `operand` - Memory location to read from.
    - **Post-conditions**: The accumulator is updated with the value from memory.

- **store**
    - **Description**: Stores a value into a specified memory location.
    - **Input**: `index` - Memory location to write to; `word` - Value to store.
    - **Post-conditions**: Memory at the specified index is updated with the new word.

- **fetch**
    - **Description**: Fetches the instruction from a specific memory location to be executed.
    - **Input**: `index` - Memory location to fetch from.
    - **Output**: `int` - The value of the fetched instruction.
    - **Post-conditions**: Returns the value of the instruction at the specified memory location.

- **execute**
    - **Description**: Decodes and executes the fetched instruction.
    - **Input**: `instruction` - Instruction code to execute.
    - **Pre-conditions**: Instruction must be a valid opcode.
    - **Post-conditions**: Executes the operation specified by the instruction.

### Class: `Arithmetic`
**Purpose**: Manages arithmetic operations within the UVSim, processing calculations and updates to the accumulator based on instruction codes.

#### Methods

- **add**
    - **Description**: Adds a value to the accumulator.
    - **Input**: `acc` - Current value of the accumulator; `value` - Value to add.
    - **Output**: `int` - Updated accumulator value after addition.
    - **Post-conditions**: The accumulator is updated to the sum of `acc` and `value`.

- **subtract**
    - **Description**: Subtracts a value from the accumulator.
    - **Input**: `acc` - Current value of the accumulator; `value` - Value to subtract.
    - **Output**: `int` - Updated accumulator value after subtraction.
    - **Post-conditions**: The accumulator is updated to the difference of `acc` and `value`.

- **multiply**
    - **Description**: Multiplies the accumulator by a given value.
    - **Input**: `acc` - Current value of the accumulator; `value` - Multiplier value.
    - **Output**: `int` - Updated accumulator value after multiplication.
    - **Post-conditions**: The accumulator is updated to the product of `acc` and `value`.

- **divide**
    - **Description**: Divides the accumulator by a given value.
    - **Input**: `acc` - Current value of the accumulator; `value` - Divisor value.
    - **Output**: `int` - Updated accumulator value after division.
    - **Pre-conditions**: `value` should not be zero to avoid division by zero error.
    - **Post-conditions**: The accumulator is updated to the quotient of `acc` divided by `value`.

- **truncate**
    - **Description**: Truncates a number to 4 digits, used for keeping accumulator values within limits.
    - **Input**: `num` - Number to truncate.
    - **Output**: `int` - Truncated number.
    - **Post-conditions**: Returns a four-digit truncated version of `num`.

### Class: `Control`
**Purpose**: Handles control flow operations such as branching based on the state of the accumulator and the instruction pointer.

#### Methods

- **branch**
    - **Description**: Directly sets the instruction pointer to a specified location.
    - **Input**: `operand` - Memory location to branch to.
    - **Post-conditions**: The instruction pointer is updated to `operand`.

- **branchNeg**
    - **Description**: Branches to the specified location if the accumulator is negative.
    - **Input**: `operand` - Memory location to branch to; `instructionPointer` - Reference to the current instruction pointer; `accumulator` - Current value of the accumulator.
    - **Post-conditions**: If `accumulator` is negative, `instructionPointer` is updated to `operand`.

- **branchZero**
    - **Description**: Branches to the specified location if the accumulator is zero.
    - **Input**: `operand` - Memory location to branch to; `instructionPointer` - Reference to the current instruction pointer; `accumulator` - Current value of the accumulator.
    - **Post-conditions**: If `accumulator` is zero, `instructionPointer` is updated to `operand`.

### Class: `IO`
**Purpose**: Manages all input and output operations for the UVSim.

#### Methods

- **read**
    - **Description**: Reads an integer from the keyboard and stores it at a specified memory location.
    - **Input**: `operand` - Memory location where the read value will be stored.
    - **Output**: `int` - The integer read from the keyboard.
    - **Post-conditions**: The memory at `operand` is updated with the user input.

- **write**
    - **Description**: Outputs a word from a specified memory location to the screen.
    - **Input**: `operand` - Memory location of the word; `value` - The value at the memory location.
    - **Post-conditions**: The value is written to the screen.

- **promptFile**
    - **Description**: Prompts the user to enter a file name for loading a program.
    - **Output**: `std::string` - Name of the file input by the user.
    - **Post-conditions**: Returns the name of the file entered by the user, to be used for loading a program.

### Class: `MainWindow`
**Purpose**: Provides a GUI for the UVSim, allowing users to interact with the simulator.

#### Methods

- **onButton1Clicked**
    - **Description**: Event handler for the "Load File" button, loading a file into the simulator.
    - **Post-conditions**: The file is loaded into the simulator.

- **onButton2Clicked**
    - **Description**: Event handler for the "Execute File" button, executing the loaded file.
    - **Pre-conditions**: A file must be loaded into memory.
    - **Post-conditions**: The program is executed.

- **onButton3Clicked**
    - **Description**: Event handler for the "Save As" button, saving the current instructions to a file.
    - **Post-conditions**: The instructions are saved to a file.

- **onButton4Clicked**
    - **Description**: Event handler for the "Clear Output" button, clearing the output area.
    - **Post-conditions**: The output area is cleared.

- **setDefaultColors**
    - **Description**: Sets the default colors for the GUI components.
    - **Post-conditions**: The colors of the GUI components are set to default values.

- **changeColors**
    - **Description**: Changes the colors of the GUI components based on user choice.
    - **Post-conditions**: The colors of the GUI components are updated.

- **onTextViewerTextChanged**
    - **Description**: Event handler for the text viewer, limiting the number of lines that can be entered.
    - **Post-conditions**: The number of lines is limited.

- **loadTextFile**
    - **Description**: Loads the content of a text file into the text viewer.
    - **Input**: `filename` - Path to the file to load.
    - **Post-conditions**: The content of the file is loaded into the text viewer.

- **saveTextFile**
    - **Description**: Saves the content of the text viewer to a file.
    - **Input**: `filename` - Path to the file to save.
    - **Post-conditions**: The content of the text viewer is saved to the file.

- **setTextFileTitle**
    - **Description**: Sets the title of the program.
    - **Post-conditions**: The title of the program is set.

- **run**
    - **Description**: Initiates the simulation, executing loaded instructions until halted.
    - **Pre-conditions**: A program must be loaded into memory.
    - **Post-conditions**: Executes the program until completion or halt.

- **getUserInput**
    - **Description**: Retrieves user input from the input field.
    - **Post-conditions**: Returns the user input from the text viewer.
