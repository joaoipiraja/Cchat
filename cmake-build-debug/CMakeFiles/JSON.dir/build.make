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
include CMakeFiles/JSON.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/JSON.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/JSON.dir/flags.make

CMakeFiles/JSON.dir/ChatBrain.c.o: CMakeFiles/JSON.dir/flags.make
CMakeFiles/JSON.dir/ChatBrain.c.o: ../ChatBrain.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/JSON.dir/ChatBrain.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/JSON.dir/ChatBrain.c.o   -c /Users/joaovictoripirajadealencar/CLionProjects/Cchat/ChatBrain.c

CMakeFiles/JSON.dir/ChatBrain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/JSON.dir/ChatBrain.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/joaovictoripirajadealencar/CLionProjects/Cchat/ChatBrain.c > CMakeFiles/JSON.dir/ChatBrain.c.i

CMakeFiles/JSON.dir/ChatBrain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/JSON.dir/ChatBrain.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/joaovictoripirajadealencar/CLionProjects/Cchat/ChatBrain.c -o CMakeFiles/JSON.dir/ChatBrain.c.s

CMakeFiles/JSON.dir/uuid_test.c.o: CMakeFiles/JSON.dir/flags.make
CMakeFiles/JSON.dir/uuid_test.c.o: ../uuid_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/JSON.dir/uuid_test.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/JSON.dir/uuid_test.c.o   -c /Users/joaovictoripirajadealencar/CLionProjects/Cchat/uuid_test.c

CMakeFiles/JSON.dir/uuid_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/JSON.dir/uuid_test.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/joaovictoripirajadealencar/CLionProjects/Cchat/uuid_test.c > CMakeFiles/JSON.dir/uuid_test.c.i

CMakeFiles/JSON.dir/uuid_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/JSON.dir/uuid_test.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/joaovictoripirajadealencar/CLionProjects/Cchat/uuid_test.c -o CMakeFiles/JSON.dir/uuid_test.c.s

# Object files for target JSON
JSON_OBJECTS = \
"CMakeFiles/JSON.dir/ChatBrain.c.o" \
"CMakeFiles/JSON.dir/uuid_test.c.o"

# External object files for target JSON
JSON_EXTERNAL_OBJECTS =

JSON: CMakeFiles/JSON.dir/ChatBrain.c.o
JSON: CMakeFiles/JSON.dir/uuid_test.c.o
JSON: CMakeFiles/JSON.dir/build.make
JSON: CMakeFiles/JSON.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable JSON"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JSON.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/JSON.dir/build: JSON

.PHONY : CMakeFiles/JSON.dir/build

CMakeFiles/JSON.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/JSON.dir/cmake_clean.cmake
.PHONY : CMakeFiles/JSON.dir/clean

CMakeFiles/JSON.dir/depend:
	cd /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joaovictoripirajadealencar/CLionProjects/Cchat /Users/joaovictoripirajadealencar/CLionProjects/Cchat /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug /Users/joaovictoripirajadealencar/CLionProjects/Cchat/cmake-build-debug/CMakeFiles/JSON.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/JSON.dir/depend
