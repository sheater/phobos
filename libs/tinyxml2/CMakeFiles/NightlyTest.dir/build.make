# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/stepanskovajsa/fi/pv112/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/stepanskovajsa/fi/pv112/project

# Utility rule file for NightlyTest.

# Include the progress variables for this target.
include libs/tinyxml2/CMakeFiles/NightlyTest.dir/progress.make

libs/tinyxml2/CMakeFiles/NightlyTest:
	cd /Users/stepanskovajsa/fi/pv112/project/libs/tinyxml2 && /usr/local/Cellar/cmake/3.11.1/bin/ctest -D NightlyTest

NightlyTest: libs/tinyxml2/CMakeFiles/NightlyTest
NightlyTest: libs/tinyxml2/CMakeFiles/NightlyTest.dir/build.make

.PHONY : NightlyTest

# Rule to build all files generated by this target.
libs/tinyxml2/CMakeFiles/NightlyTest.dir/build: NightlyTest

.PHONY : libs/tinyxml2/CMakeFiles/NightlyTest.dir/build

libs/tinyxml2/CMakeFiles/NightlyTest.dir/clean:
	cd /Users/stepanskovajsa/fi/pv112/project/libs/tinyxml2 && $(CMAKE_COMMAND) -P CMakeFiles/NightlyTest.dir/cmake_clean.cmake
.PHONY : libs/tinyxml2/CMakeFiles/NightlyTest.dir/clean

libs/tinyxml2/CMakeFiles/NightlyTest.dir/depend:
	cd /Users/stepanskovajsa/fi/pv112/project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/libs/tinyxml2 /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/libs/tinyxml2 /Users/stepanskovajsa/fi/pv112/project/libs/tinyxml2/CMakeFiles/NightlyTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/tinyxml2/CMakeFiles/NightlyTest.dir/depend

