# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/source/CppConcurrencyInAction

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/source/CppConcurrencyInAction/build

# Include any dependencies generated for this target.
include CMakeFiles/a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.dir/flags.make

CMakeFiles/a.dir/src/Chap2.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Chap2.o: ../src/Chap2.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a.dir/src/Chap2.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Chap2.o -c /home/source/CppConcurrencyInAction/src/Chap2.cc

CMakeFiles/a.dir/src/Chap2.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Chap2.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/Chap2.cc > CMakeFiles/a.dir/src/Chap2.i

CMakeFiles/a.dir/src/Chap2.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Chap2.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/Chap2.cc -o CMakeFiles/a.dir/src/Chap2.s

CMakeFiles/a.dir/src/Chap3.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Chap3.o: ../src/Chap3.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a.dir/src/Chap3.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Chap3.o -c /home/source/CppConcurrencyInAction/src/Chap3.cc

CMakeFiles/a.dir/src/Chap3.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Chap3.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/Chap3.cc > CMakeFiles/a.dir/src/Chap3.i

CMakeFiles/a.dir/src/Chap3.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Chap3.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/Chap3.cc -o CMakeFiles/a.dir/src/Chap3.s

CMakeFiles/a.dir/src/Chap4.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Chap4.o: ../src/Chap4.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a.dir/src/Chap4.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Chap4.o -c /home/source/CppConcurrencyInAction/src/Chap4.cc

CMakeFiles/a.dir/src/Chap4.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Chap4.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/Chap4.cc > CMakeFiles/a.dir/src/Chap4.i

CMakeFiles/a.dir/src/Chap4.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Chap4.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/Chap4.cc -o CMakeFiles/a.dir/src/Chap4.s

CMakeFiles/a.dir/src/Demo.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Demo.o: ../src/Demo.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/a.dir/src/Demo.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Demo.o -c /home/source/CppConcurrencyInAction/src/Demo.cc

CMakeFiles/a.dir/src/Demo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Demo.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/Demo.cc > CMakeFiles/a.dir/src/Demo.i

CMakeFiles/a.dir/src/Demo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Demo.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/Demo.cc -o CMakeFiles/a.dir/src/Demo.s

CMakeFiles/a.dir/src/Dheader.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Dheader.o: ../src/Dheader.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/a.dir/src/Dheader.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Dheader.o -c /home/source/CppConcurrencyInAction/src/Dheader.cc

CMakeFiles/a.dir/src/Dheader.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Dheader.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/Dheader.cc > CMakeFiles/a.dir/src/Dheader.i

CMakeFiles/a.dir/src/Dheader.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Dheader.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/Dheader.cc -o CMakeFiles/a.dir/src/Dheader.s

CMakeFiles/a.dir/src/PandC.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/PandC.o: ../src/PandC.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/a.dir/src/PandC.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/PandC.o -c /home/source/CppConcurrencyInAction/src/PandC.cc

CMakeFiles/a.dir/src/PandC.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/PandC.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/PandC.cc > CMakeFiles/a.dir/src/PandC.i

CMakeFiles/a.dir/src/PandC.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/PandC.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/PandC.cc -o CMakeFiles/a.dir/src/PandC.s

CMakeFiles/a.dir/src/main.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/main.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/a.dir/src/main.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/main.o -c /home/source/CppConcurrencyInAction/src/main.cc

CMakeFiles/a.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/source/CppConcurrencyInAction/src/main.cc > CMakeFiles/a.dir/src/main.i

CMakeFiles/a.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/source/CppConcurrencyInAction/src/main.cc -o CMakeFiles/a.dir/src/main.s

# Object files for target a
a_OBJECTS = \
"CMakeFiles/a.dir/src/Chap2.o" \
"CMakeFiles/a.dir/src/Chap3.o" \
"CMakeFiles/a.dir/src/Chap4.o" \
"CMakeFiles/a.dir/src/Demo.o" \
"CMakeFiles/a.dir/src/Dheader.o" \
"CMakeFiles/a.dir/src/PandC.o" \
"CMakeFiles/a.dir/src/main.o"

# External object files for target a
a_EXTERNAL_OBJECTS =

a : CMakeFiles/a.dir/src/Chap2.o
a : CMakeFiles/a.dir/src/Chap3.o
a : CMakeFiles/a.dir/src/Chap4.o
a : CMakeFiles/a.dir/src/Demo.o
a : CMakeFiles/a.dir/src/Dheader.o
a : CMakeFiles/a.dir/src/PandC.o
a : CMakeFiles/a.dir/src/main.o
a : CMakeFiles/a.dir/build.make
a : CMakeFiles/a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/source/CppConcurrencyInAction/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.dir/build: a

.PHONY : CMakeFiles/a.dir/build

CMakeFiles/a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.dir/clean

CMakeFiles/a.dir/depend:
	cd /home/source/CppConcurrencyInAction/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/source/CppConcurrencyInAction /home/source/CppConcurrencyInAction /home/source/CppConcurrencyInAction/build /home/source/CppConcurrencyInAction/build /home/source/CppConcurrencyInAction/build/CMakeFiles/a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.dir/depend

