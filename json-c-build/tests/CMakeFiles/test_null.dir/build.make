# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_null.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_null.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_null.dir/flags.make

tests/CMakeFiles/test_null.dir/test_null.c.o: tests/CMakeFiles/test_null.dir/flags.make
tests/CMakeFiles/test_null.dir/test_null.c.o: /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c/tests/test_null.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_null.dir/test_null.c.o"
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_null.dir/test_null.c.o -c /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c/tests/test_null.c

tests/CMakeFiles/test_null.dir/test_null.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_null.dir/test_null.c.i"
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c/tests/test_null.c > CMakeFiles/test_null.dir/test_null.c.i

tests/CMakeFiles/test_null.dir/test_null.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_null.dir/test_null.c.s"
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c/tests/test_null.c -o CMakeFiles/test_null.dir/test_null.c.s

# Object files for target test_null
test_null_OBJECTS = \
"CMakeFiles/test_null.dir/test_null.c.o"

# External object files for target test_null
test_null_EXTERNAL_OBJECTS =

tests/test_null: tests/CMakeFiles/test_null.dir/test_null.c.o
tests/test_null: tests/CMakeFiles/test_null.dir/build.make
tests/test_null: libjson-c.5.1.0.dylib
tests/test_null: tests/CMakeFiles/test_null.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_null"
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_null.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_null.dir/build: tests/test_null

.PHONY : tests/CMakeFiles/test_null.dir/build

tests/CMakeFiles/test_null.dir/clean:
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_null.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_null.dir/clean

tests/CMakeFiles/test_null.dir/depend:
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c/tests /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests /Users/joaovictoripirajadealencar/CLionProjects/Cchat/json-c-build/tests/CMakeFiles/test_null.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_null.dir/depend

