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
CMAKE_SOURCE_DIR = /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build

# Include any dependencies generated for this target.
include CMakeFiles/bsdiff_offical.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bsdiff_offical.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bsdiff_offical.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bsdiff_offical.dir/flags.make

CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o: CMakeFiles/bsdiff_offical.dir/flags.make
CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o: ../bsdiff_offical.cpp
CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o: CMakeFiles/bsdiff_offical.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o -MF CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o.d -o CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o -c /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/bsdiff_offical.cpp

CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/bsdiff_offical.cpp > CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.i

CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/bsdiff_offical.cpp -o CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.s

# Object files for target bsdiff_offical
bsdiff_offical_OBJECTS = \
"CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o"

# External object files for target bsdiff_offical
bsdiff_offical_EXTERNAL_OBJECTS =

bsdiff_offical: CMakeFiles/bsdiff_offical.dir/bsdiff_offical.cpp.o
bsdiff_offical: CMakeFiles/bsdiff_offical.dir/build.make
bsdiff_offical: ../lib/libbsdiff.so
bsdiff_offical: CMakeFiles/bsdiff_offical.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bsdiff_offical"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bsdiff_offical.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bsdiff_offical.dir/build: bsdiff_offical
.PHONY : CMakeFiles/bsdiff_offical.dir/build

CMakeFiles/bsdiff_offical.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bsdiff_offical.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bsdiff_offical.dir/clean

CMakeFiles/bsdiff_offical.dir/depend:
	cd /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2 /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2 /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build /home/hawrk/Documents/GitHub/hawrk/cpp/bsdiff_v2/build/CMakeFiles/bsdiff_offical.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bsdiff_offical.dir/depend

