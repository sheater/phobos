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

# Include any dependencies generated for this target.
include libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/depend.make

# Include the progress variables for this target.
include libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/progress.make

# Include the compile flags for this target's objects.
include libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/flags.make

libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.o: libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/flags.make
libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.o: libs/glm/test/gtc/gtc_integer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/stepanskovajsa/fi/pv112/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.o"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.o -c /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc/gtc_integer.cpp

libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.i"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc/gtc_integer.cpp > CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.i

libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.s"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc/gtc_integer.cpp -o CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.s

# Object files for target test-gtc_integer
test__gtc_integer_OBJECTS = \
"CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.o"

# External object files for target test-gtc_integer
test__gtc_integer_EXTERNAL_OBJECTS =

libs/glm/test/gtc/test-gtc_integer: libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/gtc_integer.cpp.o
libs/glm/test/gtc/test-gtc_integer: libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/build.make
libs/glm/test/gtc/test-gtc_integer: libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/stepanskovajsa/fi/pv112/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-gtc_integer"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-gtc_integer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/build: libs/glm/test/gtc/test-gtc_integer

.PHONY : libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/build

libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/clean:
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc && $(CMAKE_COMMAND) -P CMakeFiles/test-gtc_integer.dir/cmake_clean.cmake
.PHONY : libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/clean

libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/depend:
	cd /Users/stepanskovajsa/fi/pv112/project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/glm/test/gtc/CMakeFiles/test-gtc_integer.dir/depend

