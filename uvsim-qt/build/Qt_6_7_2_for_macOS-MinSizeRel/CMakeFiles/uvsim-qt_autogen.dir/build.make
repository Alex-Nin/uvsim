# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/zhihuichen/Qt/Tools/CMake/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Users/zhihuichen/Qt/Tools/CMake/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhihuichen/Downloads/CS2450/uvsim-qt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel

# Utility rule file for uvsim-qt_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/uvsim-qt_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/uvsim-qt_autogen.dir/progress.make

CMakeFiles/uvsim-qt_autogen: uvsim-qt_autogen/timestamp

uvsim-qt_autogen/timestamp: /Users/zhihuichen/Qt/6.7.2/macos/./libexec/moc
uvsim-qt_autogen/timestamp: /Users/zhihuichen/Qt/6.7.2/macos/./libexec/uic
uvsim-qt_autogen/timestamp: CMakeFiles/uvsim-qt_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target uvsim-qt"
	/Users/zhihuichen/Qt/Tools/CMake/CMake.app/Contents/bin/cmake -E cmake_autogen /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel/CMakeFiles/uvsim-qt_autogen.dir/AutogenInfo.json MinSizeRel
	/Users/zhihuichen/Qt/Tools/CMake/CMake.app/Contents/bin/cmake -E touch /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel/uvsim-qt_autogen/timestamp

uvsim-qt_autogen: CMakeFiles/uvsim-qt_autogen
uvsim-qt_autogen: uvsim-qt_autogen/timestamp
uvsim-qt_autogen: CMakeFiles/uvsim-qt_autogen.dir/build.make
.PHONY : uvsim-qt_autogen

# Rule to build all files generated by this target.
CMakeFiles/uvsim-qt_autogen.dir/build: uvsim-qt_autogen
.PHONY : CMakeFiles/uvsim-qt_autogen.dir/build

CMakeFiles/uvsim-qt_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uvsim-qt_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uvsim-qt_autogen.dir/clean

CMakeFiles/uvsim-qt_autogen.dir/depend:
	cd /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhihuichen/Downloads/CS2450/uvsim-qt /Users/zhihuichen/Downloads/CS2450/uvsim-qt /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel /Users/zhihuichen/Downloads/CS2450/uvsim-qt/build/Qt_6_7_2_for_macOS-MinSizeRel/CMakeFiles/uvsim-qt_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/uvsim-qt_autogen.dir/depend
