# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/iVan/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/iVan/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/9.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/9.dir/flags.make

CMakeFiles/9.dir/main.c.o: CMakeFiles/9.dir/flags.make
CMakeFiles/9.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/9.dir/main.c.o"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/9.dir/main.c.o   -c /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/main.c

CMakeFiles/9.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/9.dir/main.c.i"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/main.c > CMakeFiles/9.dir/main.c.i

CMakeFiles/9.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/9.dir/main.c.s"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/main.c -o CMakeFiles/9.dir/main.c.s

CMakeFiles/9.dir/BracketTree.c.o: CMakeFiles/9.dir/flags.make
CMakeFiles/9.dir/BracketTree.c.o: ../BracketTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/9.dir/BracketTree.c.o"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/9.dir/BracketTree.c.o   -c /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/BracketTree.c

CMakeFiles/9.dir/BracketTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/9.dir/BracketTree.c.i"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/BracketTree.c > CMakeFiles/9.dir/BracketTree.c.i

CMakeFiles/9.dir/BracketTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/9.dir/BracketTree.c.s"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/BracketTree.c -o CMakeFiles/9.dir/BracketTree.c.s

# Object files for target 9
9_OBJECTS = \
"CMakeFiles/9.dir/main.c.o" \
"CMakeFiles/9.dir/BracketTree.c.o"

# External object files for target 9
9_EXTERNAL_OBJECTS =

9.exe: CMakeFiles/9.dir/main.c.o
9.exe: CMakeFiles/9.dir/BracketTree.c.o
9.exe: CMakeFiles/9.dir/build.make
9.exe: CMakeFiles/9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable 9.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/9.dir/build: 9.exe

.PHONY : CMakeFiles/9.dir/build

CMakeFiles/9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/9.dir/clean

CMakeFiles/9.dir/depend:
	cd /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9 /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9 /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug /cygdrive/c/Users/iVan/Documents/GitHub/F_AlG/FUND-ALG/4/9/cmake-build-debug/CMakeFiles/9.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/9.dir/depend

