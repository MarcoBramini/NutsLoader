# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/uno_TimerSwitch.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/uno_TimerSwitch.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/uno_TimerSwitch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uno_TimerSwitch.dir/flags.make

CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj: CMakeFiles/uno_TimerSwitch.dir/flags.make
CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj: ../NutsloaderService.cpp
CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj: CMakeFiles/uno_TimerSwitch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj -MF CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj.d -o CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj -c /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/NutsloaderService.cpp

CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.i"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/NutsloaderService.cpp > CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.i

CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.s"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/NutsloaderService.cpp -o CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.s

# Object files for target uno_TimerSwitch
uno_TimerSwitch_OBJECTS = \
"CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj"

# External object files for target uno_TimerSwitch
uno_TimerSwitch_EXTERNAL_OBJECTS =

libuno_TimerSwitch.a: CMakeFiles/uno_TimerSwitch.dir/NutsloaderService.cpp.obj
libuno_TimerSwitch.a: CMakeFiles/uno_TimerSwitch.dir/build.make
libuno_TimerSwitch.a: CMakeFiles/uno_TimerSwitch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libuno_TimerSwitch.a"
	$(CMAKE_COMMAND) -P CMakeFiles/uno_TimerSwitch.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uno_TimerSwitch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uno_TimerSwitch.dir/build: libuno_TimerSwitch.a
.PHONY : CMakeFiles/uno_TimerSwitch.dir/build

CMakeFiles/uno_TimerSwitch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uno_TimerSwitch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uno_TimerSwitch.dir/clean

CMakeFiles/uno_TimerSwitch.dir/depend:
	cd /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug /Users/marcobramini/Documents/Arduino/libraries/NutsloaderService/cmake-build-debug/CMakeFiles/uno_TimerSwitch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uno_TimerSwitch.dir/depend
