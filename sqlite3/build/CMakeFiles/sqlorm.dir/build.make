# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/hawrk/github/hawrk/cpp/sqlite3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hawrk/github/hawrk/cpp/sqlite3/build

# Include any dependencies generated for this target.
include CMakeFiles/sqlorm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sqlorm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sqlorm.dir/flags.make

CMakeFiles/sqlorm.dir/sqliteOrm.cpp.o: CMakeFiles/sqlorm.dir/flags.make
CMakeFiles/sqlorm.dir/sqliteOrm.cpp.o: ../sqliteOrm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/github/hawrk/cpp/sqlite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sqlorm.dir/sqliteOrm.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sqlorm.dir/sqliteOrm.cpp.o -c /home/hawrk/github/hawrk/cpp/sqlite3/sqliteOrm.cpp

CMakeFiles/sqlorm.dir/sqliteOrm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sqlorm.dir/sqliteOrm.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/github/hawrk/cpp/sqlite3/sqliteOrm.cpp > CMakeFiles/sqlorm.dir/sqliteOrm.cpp.i

CMakeFiles/sqlorm.dir/sqliteOrm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sqlorm.dir/sqliteOrm.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/github/hawrk/cpp/sqlite3/sqliteOrm.cpp -o CMakeFiles/sqlorm.dir/sqliteOrm.cpp.s

# Object files for target sqlorm
sqlorm_OBJECTS = \
"CMakeFiles/sqlorm.dir/sqliteOrm.cpp.o"

# External object files for target sqlorm
sqlorm_EXTERNAL_OBJECTS =

sqlorm: CMakeFiles/sqlorm.dir/sqliteOrm.cpp.o
sqlorm: CMakeFiles/sqlorm.dir/build.make
sqlorm: CMakeFiles/sqlorm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hawrk/github/hawrk/cpp/sqlite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sqlorm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sqlorm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sqlorm.dir/build: sqlorm

.PHONY : CMakeFiles/sqlorm.dir/build

CMakeFiles/sqlorm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sqlorm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sqlorm.dir/clean

CMakeFiles/sqlorm.dir/depend:
	cd /home/hawrk/github/hawrk/cpp/sqlite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hawrk/github/hawrk/cpp/sqlite3 /home/hawrk/github/hawrk/cpp/sqlite3 /home/hawrk/github/hawrk/cpp/sqlite3/build /home/hawrk/github/hawrk/cpp/sqlite3/build /home/hawrk/github/hawrk/cpp/sqlite3/build/CMakeFiles/sqlorm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sqlorm.dir/depend

