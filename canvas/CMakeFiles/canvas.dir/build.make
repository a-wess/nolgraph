# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/awes/projects/rays

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/awes/projects/rays

# Include any dependencies generated for this target.
include canvas/CMakeFiles/canvas.dir/depend.make

# Include the progress variables for this target.
include canvas/CMakeFiles/canvas.dir/progress.make

# Include the compile flags for this target's objects.
include canvas/CMakeFiles/canvas.dir/flags.make

canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o: canvas/CMakeFiles/canvas.dir/flags.make
canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o: canvas/src/canvas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/awes/projects/rays/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o"
	cd /home/awes/projects/rays/canvas && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/canvas.dir/src/canvas.cpp.o -c /home/awes/projects/rays/canvas/src/canvas.cpp

canvas/CMakeFiles/canvas.dir/src/canvas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/canvas.dir/src/canvas.cpp.i"
	cd /home/awes/projects/rays/canvas && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/awes/projects/rays/canvas/src/canvas.cpp > CMakeFiles/canvas.dir/src/canvas.cpp.i

canvas/CMakeFiles/canvas.dir/src/canvas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/canvas.dir/src/canvas.cpp.s"
	cd /home/awes/projects/rays/canvas && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/awes/projects/rays/canvas/src/canvas.cpp -o CMakeFiles/canvas.dir/src/canvas.cpp.s

canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.requires:

.PHONY : canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.requires

canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.provides: canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.requires
	$(MAKE) -f canvas/CMakeFiles/canvas.dir/build.make canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.provides.build
.PHONY : canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.provides

canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.provides.build: canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o


# Object files for target canvas
canvas_OBJECTS = \
"CMakeFiles/canvas.dir/src/canvas.cpp.o"

# External object files for target canvas
canvas_EXTERNAL_OBJECTS =

canvas/libcanvas.a: canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o
canvas/libcanvas.a: canvas/CMakeFiles/canvas.dir/build.make
canvas/libcanvas.a: canvas/CMakeFiles/canvas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/awes/projects/rays/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcanvas.a"
	cd /home/awes/projects/rays/canvas && $(CMAKE_COMMAND) -P CMakeFiles/canvas.dir/cmake_clean_target.cmake
	cd /home/awes/projects/rays/canvas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/canvas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
canvas/CMakeFiles/canvas.dir/build: canvas/libcanvas.a

.PHONY : canvas/CMakeFiles/canvas.dir/build

canvas/CMakeFiles/canvas.dir/requires: canvas/CMakeFiles/canvas.dir/src/canvas.cpp.o.requires

.PHONY : canvas/CMakeFiles/canvas.dir/requires

canvas/CMakeFiles/canvas.dir/clean:
	cd /home/awes/projects/rays/canvas && $(CMAKE_COMMAND) -P CMakeFiles/canvas.dir/cmake_clean.cmake
.PHONY : canvas/CMakeFiles/canvas.dir/clean

canvas/CMakeFiles/canvas.dir/depend:
	cd /home/awes/projects/rays && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/awes/projects/rays /home/awes/projects/rays/canvas /home/awes/projects/rays /home/awes/projects/rays/canvas /home/awes/projects/rays/canvas/CMakeFiles/canvas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : canvas/CMakeFiles/canvas.dir/depend

