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
CMAKE_SOURCE_DIR = /home/hawrk/Documents/GitHub/omni_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hawrk/Documents/GitHub/omni_server/build

# Include any dependencies generated for this target.
include CMakeFiles/test_app_manager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_app_manager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_app_manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_app_manager.dir/flags.make

CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o: ../test/test_app_manager.cpp
CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o -MF CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o.d -o CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/test/test_app_manager.cpp

CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/test/test_app_manager.cpp > CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.i

CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/test/test_app_manager.cpp -o CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.s

CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o: ../common/tc_file.cpp
CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o -MF CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o.d -o CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/common/tc_file.cpp

CMakeFiles/test_app_manager.dir/common/tc_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/common/tc_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/common/tc_file.cpp > CMakeFiles/test_app_manager.dir/common/tc_file.cpp.i

CMakeFiles/test_app_manager.dir/common/tc_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/common/tc_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/common/tc_file.cpp -o CMakeFiles/test_app_manager.dir/common/tc_file.cpp.s

CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o: ../common/curl_lib.cpp
CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o -MF CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o.d -o CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/common/curl_lib.cpp

CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/common/curl_lib.cpp > CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.i

CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/common/curl_lib.cpp -o CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.s

CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o: ../common/crypto_suite.cpp
CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o -MF CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o.d -o CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/common/crypto_suite.cpp

CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/common/crypto_suite.cpp > CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.i

CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/common/crypto_suite.cpp -o CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.s

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o: ../internal/ota/ota_mng_query.cpp
CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o -MF CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o.d -o CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_query.cpp

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_query.cpp > CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.i

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_query.cpp -o CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.s

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o: ../internal/ota/ota_mng_upgrade.cpp
CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o -MF CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o.d -o CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_upgrade.cpp

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_upgrade.cpp > CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.i

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_upgrade.cpp -o CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.s

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o: ../internal/ota/ota_mng_rollback.cpp
CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o -MF CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o.d -o CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_rollback.cpp

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_rollback.cpp > CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.i

CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_mng_rollback.cpp -o CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.s

CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o: CMakeFiles/test_app_manager.dir/flags.make
CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o: ../internal/ota/ota_app_manager.cpp
CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o: CMakeFiles/test_app_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o -MF CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o.d -o CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o -c /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_app_manager.cpp

CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_app_manager.cpp > CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.i

CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawrk/Documents/GitHub/omni_server/internal/ota/ota_app_manager.cpp -o CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.s

# Object files for target test_app_manager
test_app_manager_OBJECTS = \
"CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o" \
"CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o" \
"CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o" \
"CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o" \
"CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o" \
"CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o" \
"CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o" \
"CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o"

# External object files for target test_app_manager
test_app_manager_EXTERNAL_OBJECTS =

test_app_manager: CMakeFiles/test_app_manager.dir/test/test_app_manager.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/common/tc_file.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/common/curl_lib.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/common/crypto_suite.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_query.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_upgrade.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/internal/ota/ota_mng_rollback.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/internal/ota/ota_app_manager.cpp.o
test_app_manager: CMakeFiles/test_app_manager.dir/build.make
test_app_manager: CMakeFiles/test_app_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable test_app_manager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_app_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_app_manager.dir/build: test_app_manager
.PHONY : CMakeFiles/test_app_manager.dir/build

CMakeFiles/test_app_manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_app_manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_app_manager.dir/clean

CMakeFiles/test_app_manager.dir/depend:
	cd /home/hawrk/Documents/GitHub/omni_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hawrk/Documents/GitHub/omni_server /home/hawrk/Documents/GitHub/omni_server /home/hawrk/Documents/GitHub/omni_server/build /home/hawrk/Documents/GitHub/omni_server/build /home/hawrk/Documents/GitHub/omni_server/build/CMakeFiles/test_app_manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_app_manager.dir/depend

