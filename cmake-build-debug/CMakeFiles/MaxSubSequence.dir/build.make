# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joaovictoripirajadealencar/CLionProjects/Cchat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MaxSubSequence.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MaxSubSequence.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MaxSubSequence.dir/flags.make

CMakeFiles/MaxSubSequence.dir/client.c.o: CMakeFiles/MaxSubSequence.dir/flags.make
CMakeFiles/MaxSubSequence.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MaxSubSequence.dir/client.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MaxSubSequence.dir/client.c.o   -c /Users/joaovictoripirajadealencar/CLionProjects/Cchat/client.c

CMakeFiles/MaxSubSequence.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MaxSubSequence.dir/client.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/joaovictoripirajadealencar/CLionProjects/Cchat/client.c > CMakeFiles/MaxSubSequence.dir/client.c.i

CMakeFiles/MaxSubSequence.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MaxSubSequence.dir/client.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/joaovictoripirajadealencar/CLionProjects/Cchat/client.c -o CMakeFiles/MaxSubSequence.dir/client.c.s

# Object files for target MaxSubSequence
MaxSubSequence_OBJECTS = \
"CMakeFiles/MaxSubSequence.dir/client.c.o"

# External object files for target MaxSubSequence
MaxSubSequence_EXTERNAL_OBJECTS =

MaxSubSequence: CMakeFiles/MaxSubSequence.dir/client.c.o
MaxSubSequence: CMakeFiles/MaxSubSequence.dir/build.make
MaxSubSequence: CMakeFiles/MaxSubSequence.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MaxSubSequence"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MaxSubSequence.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MaxSubSequence.dir/build: MaxSubSequence

.PHONY : CMakeFiles/MaxSubSequence.dir/build

CMakeFiles/MaxSubSequence.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MaxSubSequence.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MaxSubSequence.dir/clean

CMakeFiles/MaxSubSequence.dir/depend:
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joaovictoripirajadealencar/CLionProjects/Cchat /Users/joaovictoripirajadealencar/CLionProjects/Cchat /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles/MaxSubSequence.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MaxSubSequence.dir/depend

