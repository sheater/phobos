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
include CMakeFiles/glew.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glew.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glew.dir/flags.make

CMakeFiles/glew.dir/libs/glew/src/glew.c.o: CMakeFiles/glew.dir/flags.make
CMakeFiles/glew.dir/libs/glew/src/glew.c.o: libs/glew/src/glew.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/stepanskovajsa/fi/pv112/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glew.dir/libs/glew/src/glew.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glew.dir/libs/glew/src/glew.c.o   -c /Users/stepanskovajsa/fi/pv112/project/libs/glew/src/glew.c

CMakeFiles/glew.dir/libs/glew/src/glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glew.dir/libs/glew/src/glew.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/stepanskovajsa/fi/pv112/project/libs/glew/src/glew.c > CMakeFiles/glew.dir/libs/glew/src/glew.c.i

CMakeFiles/glew.dir/libs/glew/src/glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glew.dir/libs/glew/src/glew.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/stepanskovajsa/fi/pv112/project/libs/glew/src/glew.c -o CMakeFiles/glew.dir/libs/glew/src/glew.c.s

# Object files for target glew
glew_OBJECTS = \
"CMakeFiles/glew.dir/libs/glew/src/glew.c.o"

# External object files for target glew
glew_EXTERNAL_OBJECTS =

libglew.a: CMakeFiles/glew.dir/libs/glew/src/glew.c.o
libglew.a: CMakeFiles/glew.dir/build.make
libglew.a: CMakeFiles/glew.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/stepanskovajsa/fi/pv112/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglew.a"
	$(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glew.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glew.dir/build: libglew.a

.PHONY : CMakeFiles/glew.dir/build

CMakeFiles/glew.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glew.dir/clean

CMakeFiles/glew.dir/depend:
	cd /Users/stepanskovajsa/fi/pv112/project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project /Users/stepanskovajsa/fi/pv112/project/CMakeFiles/glew.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glew.dir/depend

