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
include libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/depend.make

# Include the progress variables for this target.
include libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/progress.make

# Include the compile flags for this target's objects.
include libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/flags.make

libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.o: libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/flags.make
libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.o: libs/glm/test/ext/ext_scalar_constants.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/stepanskovajsa/fi/pv112/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.o"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.o -c /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext/ext_scalar_constants.cpp

libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.i"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext/ext_scalar_constants.cpp > CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.i

libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.s"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext/ext_scalar_constants.cpp -o CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.s

# Object files for target test-ext_scalar_constants
test__ext_scalar_constants_OBJECTS = \
"CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.o"

# External object files for target test-ext_scalar_constants
test__ext_scalar_constants_EXTERNAL_OBJECTS =

libs/glm/test/ext/test-ext_scalar_constants: libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/ext_scalar_constants.cpp.o
libs/glm/test/ext/test-ext_scalar_constants: libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/build.make
libs/glm/test/ext/test-ext_scalar_constants: libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/stepanskovajsa/fi/pv112/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-ext_scalar_constants"
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-ext_scalar_constants.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/build: libs/glm/test/ext/test-ext_scalar_constants

.PHONY : libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/build

libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/clean:
	cd /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext && $(CMAKE_COMMAND) -P CMakeFiles/test-ext_scalar_constants.dir/cmake_clean.cmake
.PHONY : libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/clean

libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/depend:
	cd /Users/stepanskovajsa/fi/pv112/project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext /Users/stepanskovajsa/fi/pv112/project/libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/glm/test/ext/CMakeFiles/test-ext_scalar_constants.dir/depend

