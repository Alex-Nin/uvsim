# High Functionality
UVSim is a virtual machine simulator that can execute BasicML programs. It consists of the following components:

**Memory**: UVSim maintains a vector representing its memory, which is used to store program instructions and data.  
**Registers**: UVSim has several registers, including an accumulator, an instruction pointer, and a boolean flag indicating whether the machine has halted.  
**Instruction Set**: UVSim supports a set of basic instructions that manipulate its memory and registers. These instructions include reading from and writing to memory, performing arithmetic operations, and controlling program flow.  
**Loading Programs**: UVSim can load programs from files into its memory, allowing it to execute programs written in BasicML.  
**Running Programs**: UVSim can execute loaded programs by repeatedly fetching and executing instructions until it reaches a halting instruction or encounters an error.  
**Input and Output**: UVSim supports input and output operations, allowing it to interact with users via the terminal. It can read input from the user and display output to the terminal.  
**Error Handling**: UVSim performs basic error checking, such as detecting invalid input and division by zero, and halts execution if an error occurs.  

---

# User Stories (at least 2)

**User Story 1:**  
As a computer science student,  
I want to input two numbers, perform arithmetic operations (addition, subtraction, multiplication, division), and see the results,  
so that I can understand how basic machine language operations manipulate data and apply these concepts to learn about computer architecture.

**User Story 2:**  
As a computer science student,  
I want to input a number, check if it is positive, negative, or zero, and then direct the flow of the program based on these conditions,  
So that I can understand how conditional branching works in machine language.

---

# Use Cases (10-15)

**Use case 1: Adding numbers**  
**Actor**: UVSim system  
**System**: Arithmetic unit  
**Goal**: To add two numbers and update the accumulator with the result.  
**Steps**:  
1. System identifies the 'add' operation code.
2. System retrieves the number from the specified memory address.
3. System adds the number to the accumulator.
4. Result is stored in the accumulator.

**Use case 2: Subtract numbers**  
**Actor**: UVSim system  
**System**: Arithmetic unit  
**Goal**: To subtract one number from another and update the accumulator with the result.  
Steps:  
1. System identifies the 'subtract' operation code.
2. System retrieves the number from the specified memory address.
3. System subtracts the number from the accumulator.
4. Result is stored in the accumulator.

**Use case 3: Divide numbers**  
**Actor**: UVSim system  
**System**: Arithmetic unit  
**Goal**: To divide one number by another and update the accumulator with the result.  
**Steps**:
1. System identifies the 'divide' operation code.
2. System retrieves the number from the specified memory address.
3. System divides the accumulator by the number.
4. Result is stored in the accumulator.

**Use case 4: Multiply numbers**  
**Actor**: UVSim system  
**System**: Arithmetic unit  
**Goal**: To multiply two numbers and update the accumulator with the result.  
**Steps**:  
1. System identifies the 'multiply' operation code.
2. System retrieves the number from the specified memory address.
3. System multiplies the number by the accumulator.
4. Result is stored in the accumulator.

**Use case 5: Read**  
**Actor**: User  
**System**: Input/Output handler  
**Goa**l: To read input from the user and store it in memory.  
**Steps**:  
1. System prompts the user for input.
2. User enters data.
3. System stores the input in the specified memory location.

**Use case 6: Write**  
**Actor**: UVSim system  
**System**: Input/Output handler  
**Goal**: To display a value from memory to the screen.  
**Steps**:
1. System retrieves a value from a specified memory address.
2. System outputs the value to the screen.

**Use case 7: Load**  
**Actor**: UVSim system  
**System**: Memory management unit  
**Goal**: To load a word from a specific memory location into the accumulator.  
**Steps**:  
1. System identifies the 'load' operation code.
2. System retrieves a word from the specified memory address.
3. System updates the accumulator with the retrieved value.

**Use case 8: Store**  
**Actor**: UVSim system  
**System**: Memory management unit  
**Goal**: To store the value from the accumulator into a specified memory location.  
**Steps**:  
1. System identifies the 'store' operation code.
2. System writes the value of the accumulator to the specified memory address.

**Use Case 9: Branch**
**Actor**: UVSim system  
**System**: Control unit  
**Goal**: To change the instruction pointer based on a specified condition or unconditionally.  
**Steps**:
1. System identifies the 'branch' operation code.
2. The instruction pointer is updated to the specified memory address.
3. The system continues execution from the new instruction pointer location.

**Use case 10: Halt**  
**Actor**: UVSim system  
**System**: Control unit  
**Goal**: To halt the virtual machine process and end program execution.  
**Steps**:
1. Load program
2. Find address
3. Halt program process and exits program
