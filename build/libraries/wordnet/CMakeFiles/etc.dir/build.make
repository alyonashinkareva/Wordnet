# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build

# Utility rule file for etc.

# Include any custom commands dependencies for this target.
include libraries/wordnet/CMakeFiles/etc.dir/compiler_depend.make

# Include the progress variables for this target.
include libraries/wordnet/CMakeFiles/etc.dir/progress.make

libraries/wordnet/CMakeFiles/etc: /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/libraries/wordnet/etc/hypernyms.txt
libraries/wordnet/CMakeFiles/etc: /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/libraries/wordnet/etc/synsets.txt

libraries/wordnet/etc/hypernyms.txt: /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/libraries/wordnet/etc/hypernyms.txt
libraries/wordnet/etc/hypernyms.txt: /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/libraries/wordnet/etc/synsets.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying test data"
	cd /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E copy_directory /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/libraries/wordnet/etc /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet/tests_sources/etc

libraries/wordnet/etc/synsets.txt: libraries/wordnet/etc/hypernyms.txt
	@$(CMAKE_COMMAND) -E touch_nocreate libraries/wordnet/etc/synsets.txt

etc: libraries/wordnet/CMakeFiles/etc
etc: libraries/wordnet/etc/hypernyms.txt
etc: libraries/wordnet/etc/synsets.txt
etc: libraries/wordnet/CMakeFiles/etc.dir/build.make
.PHONY : etc

# Rule to build all files generated by this target.
libraries/wordnet/CMakeFiles/etc.dir/build: etc
.PHONY : libraries/wordnet/CMakeFiles/etc.dir/build

libraries/wordnet/CMakeFiles/etc.dir/clean:
	cd /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet && $(CMAKE_COMMAND) -P CMakeFiles/etc.dir/cmake_clean.cmake
.PHONY : libraries/wordnet/CMakeFiles/etc.dir/clean

libraries/wordnet/CMakeFiles/etc.dir/depend:
	cd /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/libraries/wordnet /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet /Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet/CMakeFiles/etc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/wordnet/CMakeFiles/etc.dir/depend

