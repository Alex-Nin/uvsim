# High Functionality
UVSim is a virtual machine simulator that can execute BasicML programs. It consists of the following components:

Memory: UVSim maintains a vector representing its memory, which is used to store program instructions and data.

Registers: UVSim has several registers, including an accumulator, an instruction pointer, and a boolean flag indicating whether the machine has halted.

Instruction Set: UVSim supports a set of basic instructions that manipulate its memory and registers. These instructions include reading from and writing to memory, performing arithmetic operations, and controlling program flow.

Loading Programs: UVSim can load programs from files into its memory, allowing it to execute programs written in BasicML.

Running Programs: UVSim can execute loaded programs by repeatedly fetching and executing instructions until it reaches a halting instruction or encounters an error.

Input and Output: UVSim supports input and output operations, allowing it to interact with users via the terminal. It can read input from the user and display output to the terminal.

Error Handling: UVSim performs basic error checking, such as detecting invalid input and division by zero, and halts execution if an error occurs.
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
**Objective:** Add two numbers and output the correct result  
**Steps:**
1. Load program
2. Load address
3. Load the first number into the accumulator
4. Add the second number into the accumulator

**Use case 2: Subtract numbers**  
**Objective:** Subtract two numbers and output the correct result  
**Steps:**
1. Load program
2. Load address
3. Load the first number into the accumulator
4. Subtract the second number into the accumulator

**Use case 3: Divide numbers**  
**Objective:** Divide two numbers and output the correct result  
**Steps:**
1. Load program
2. Load address
3. Load the first number into the accumulator
4. Divide the second number into the accumulator

**Use case 4: Multiply numbers**  
**Objective:** Multiply two numbers and output the correct result  
**Steps:**
1. Load program
2. Load address
3. Load the first number into the accumulator
4. Multiply the second number into the accumulator

**Use case 5: Read**  
**Objective:** Receives input and saves it to memory  
**Steps:**
1. Load program
2. Read operation code
3. Get input from keyboard
4. Save input to the memory

**Use case 6: Write**  
**Objective:** Print a value from a specific memory location  
**Steps:**
1. Load program
2. Find a word from memory
3. Print the value to screen

**Use case 7: Load**  
**Objective:** Load a word from a specific location into the accumulator  
**Steps:**
1. Load program
2. Find a word from memory
3. Replace current accumulator value with the value of the address

**Use case 8: Store**  
**Objective:** Store a word from the accumulator into a specific location  
**Steps:**
1. Load program
2. Find address
3. Replace current value with the value of the accumulator

**Use case 9: Branch**  
**Objective:** Give Instruction Pointer a new position  
**Steps:**
1. Load program
2. Find address
3. Replace current instruction value with operand

**Use case 10: Halt**  
**Objective:** Stop the virtual machine process  
**Steps:**
1. Load program
2. Find address
3. Halt program process and exits program

