# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nico/Desktop/pratica/s2argv-execs-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nico/Desktop/pratica/s2argv-execs-master/build

# Include any dependencies generated for this target.
include CMakeFiles/execs_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/execs_static.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/execs_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/execs_static.dir/flags.make

CMakeFiles/execs_static.dir/execs.c.o: CMakeFiles/execs_static.dir/flags.make
CMakeFiles/execs_static.dir/execs.c.o: ../execs.c
CMakeFiles/execs_static.dir/execs.c.o: CMakeFiles/execs_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nico/Desktop/pratica/s2argv-execs-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/execs_static.dir/execs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/execs_static.dir/execs.c.o -MF CMakeFiles/execs_static.dir/execs.c.o.d -o CMakeFiles/execs_static.dir/execs.c.o -c /home/nico/Desktop/pratica/s2argv-execs-master/execs.c

CMakeFiles/execs_static.dir/execs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execs_static.dir/execs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nico/Desktop/pratica/s2argv-execs-master/execs.c > CMakeFiles/execs_static.dir/execs.c.i

CMakeFiles/execs_static.dir/execs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execs_static.dir/execs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nico/Desktop/pratica/s2argv-execs-master/execs.c -o CMakeFiles/execs_static.dir/execs.c.s

CMakeFiles/execs_static.dir/noshell.c.o: CMakeFiles/execs_static.dir/flags.make
CMakeFiles/execs_static.dir/noshell.c.o: ../noshell.c
CMakeFiles/execs_static.dir/noshell.c.o: CMakeFiles/execs_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nico/Desktop/pratica/s2argv-execs-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/execs_static.dir/noshell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/execs_static.dir/noshell.c.o -MF CMakeFiles/execs_static.dir/noshell.c.o.d -o CMakeFiles/execs_static.dir/noshell.c.o -c /home/nico/Desktop/pratica/s2argv-execs-master/noshell.c

CMakeFiles/execs_static.dir/noshell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execs_static.dir/noshell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nico/Desktop/pratica/s2argv-execs-master/noshell.c > CMakeFiles/execs_static.dir/noshell.c.i

CMakeFiles/execs_static.dir/noshell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execs_static.dir/noshell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nico/Desktop/pratica/s2argv-execs-master/noshell.c -o CMakeFiles/execs_static.dir/noshell.c.s

# Object files for target execs_static
execs_static_OBJECTS = \
"CMakeFiles/execs_static.dir/execs.c.o" \
"CMakeFiles/execs_static.dir/noshell.c.o"

# External object files for target execs_static
execs_static_EXTERNAL_OBJECTS =

libexecs.a: CMakeFiles/execs_static.dir/execs.c.o
libexecs.a: CMakeFiles/execs_static.dir/noshell.c.o
libexecs.a: CMakeFiles/execs_static.dir/build.make
libexecs.a: CMakeFiles/execs_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nico/Desktop/pratica/s2argv-execs-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libexecs.a"
	$(CMAKE_COMMAND) -P CMakeFiles/execs_static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/execs_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/execs_static.dir/build: libexecs.a
.PHONY : CMakeFiles/execs_static.dir/build

CMakeFiles/execs_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/execs_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/execs_static.dir/clean

CMakeFiles/execs_static.dir/depend:
	cd /home/nico/Desktop/pratica/s2argv-execs-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nico/Desktop/pratica/s2argv-execs-master /home/nico/Desktop/pratica/s2argv-execs-master /home/nico/Desktop/pratica/s2argv-execs-master/build /home/nico/Desktop/pratica/s2argv-execs-master/build /home/nico/Desktop/pratica/s2argv-execs-master/build/CMakeFiles/execs_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/execs_static.dir/depend
