# Group Project Milestone 5: UVSim

![main_window](screenshots%2Fmain_window.png)

## Overview
The UVSim is a simple virtual machine, but powerful. The UVSim can only interpret a machine language called BasicML.

## Features
- **Memory Management**: Simulates a 250-word memory to mimic a basic computer's memory architecture.
- **I/O Operations**: Allows reading from the user and writing to the graphical user interface.
- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Control Flow**: Includes operations like branch, branch-if-negative, and branch-if-zero.

## GUI Interface
The UVSim includes a graphical user interface for enhanced usability.  
The GUI features buttons for loading and executing files, entering input, clearing the output, changing color theme. Below is a description of the GUI components:

- **Set Default Colors**: Sets the current GUI color scheme to default
- **Change Colors**: Allows users to customize the color scheme of the GUI. A color picker dialogue appears to choose both background and text colors. Default colors are white (#FFFFFF) on text and darkgreen (#4C721D) on background.
- **Load File**: Opens a file dialogue to select a .txt file to load into the UVSim's memory.
- **Execute File**: Runs the loaded .txt file. The console outputs each executed instruction and displays any computational results or error messages. If the instructions have been modified, the latest instructions are run, even if they have not been saved
- **Save As**: Saves the current version instructions from the editor into a new file. Changes are persisted in the newly created file.
- **Clear Output**: Clears all text from the output console to reset the view for new operations.
- **Console**: A display area that shows output from executed files or error messages during file execution.
- **Editor**: A text area where users can write or modify instructions. Users can input any valid BasicML instructions here. However, if the user wants to save the changes, then they must save instructions as a file.
- **Enter data here**: An input field for users to provide necessary data when prompted by the program during execution.
- **Lines**: Displays the current set of loaded or edited instructions, aiding in tracking changes and inputs.

## Prerequisites
- C++ Compiler (g++ or clang)
- QT6 (6.7.1 or later)

## Installation
To compile and run UVSim, follow these steps:

1. Clone this repository or download the source code.
   ```bash
   git clone https://github.com/DavidADeLeo/CS2450
   cd CS2450
   ```
2. Load CMakeLists.txt in QT Creator.
3. Click on the green play button to compile and run the program.

## Main Usage
1. Loading a Program
   - **Open the File Menu**: Click on *Load File* in the top left-hand corner.
   - **Select Load Program**: When prompted, select the .txt file you wish to load into the UVSim program and hit Enter.

2. Running the Program
   - **Run Button**: Click the *Execute File* button to run the program.
   - **Instruments Panel**: Reference Instruments righthand panel for program instructions and steps.
   - **Output Window**: Follow the prompts in the Output window.

3. Saving a Program
   - **Save Button**: Click the *Save As* button to save the current program.
   - **Save Program**: When prompted, enter the name of the file you wish to save the program as and hit Enter.

4. Changing Color Scheme
    - **Color Picker**: Click the *Change Colors* button to open the color picker dialogue.
    - **Select Colors**: Choose the desired background and text colors and hit Enter.

5. Modifying Instructions
    - **Editor**: Edit the instructions in the Editor text area (must be valid BasicML instructions).
    - **Save Changes**: Save the changes by clicking the *Save As* button.
    - **Run Modified Program**: Click the *Execute File* button to run the modified program (can run without saving).

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
