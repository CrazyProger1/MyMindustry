# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Programs\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programs\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Programming\MyGames\MyMindustry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Programming\MyGames\MyMindustry\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MyMindustry.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/MyMindustry.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyMindustry.dir/flags.make

CMakeFiles/MyMindustry.dir/main.cpp.obj: CMakeFiles/MyMindustry.dir/flags.make
CMakeFiles/MyMindustry.dir/main.cpp.obj: CMakeFiles/MyMindustry.dir/includes_CXX.rsp
CMakeFiles/MyMindustry.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Programming\MyGames\MyMindustry\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyMindustry.dir/main.cpp.obj"
	D:\Programming\C++\Compilers\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MyMindustry.dir\main.cpp.obj -c D:\Programming\MyGames\MyMindustry\main.cpp

CMakeFiles/MyMindustry.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyMindustry.dir/main.cpp.i"
	D:\Programming\C++\Compilers\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Programming\MyGames\MyMindustry\main.cpp > CMakeFiles\MyMindustry.dir\main.cpp.i

CMakeFiles/MyMindustry.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyMindustry.dir/main.cpp.s"
	D:\Programming\C++\Compilers\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Programming\MyGames\MyMindustry\main.cpp -o CMakeFiles\MyMindustry.dir\main.cpp.s

# Object files for target MyMindustry
MyMindustry_OBJECTS = \
"CMakeFiles/MyMindustry.dir/main.cpp.obj"

# External object files for target MyMindustry
MyMindustry_EXTERNAL_OBJECTS =

MyMindustry.exe: CMakeFiles/MyMindustry.dir/main.cpp.obj
MyMindustry.exe: CMakeFiles/MyMindustry.dir/build.make
MyMindustry.exe: ../externals/SFML-2.5.1/lib/libsfml-graphics-s-d.a
MyMindustry.exe: ../externals/SFML-2.5.1/lib/libsfml-window-s-d.a
MyMindustry.exe: ../externals/SFML-2.5.1/lib/libsfml-system-s-d.a
MyMindustry.exe: ../externals/SFML-2.5.1/lib/libfreetype.a
MyMindustry.exe: CMakeFiles/MyMindustry.dir/linklibs.rsp
MyMindustry.exe: CMakeFiles/MyMindustry.dir/objects1.rsp
MyMindustry.exe: CMakeFiles/MyMindustry.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Programming\MyGames\MyMindustry\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyMindustry.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MyMindustry.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyMindustry.dir/build: MyMindustry.exe
.PHONY : CMakeFiles/MyMindustry.dir/build

CMakeFiles/MyMindustry.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MyMindustry.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MyMindustry.dir/clean

CMakeFiles/MyMindustry.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Programming\MyGames\MyMindustry D:\Programming\MyGames\MyMindustry D:\Programming\MyGames\MyMindustry\cmake-build-debug D:\Programming\MyGames\MyMindustry\cmake-build-debug D:\Programming\MyGames\MyMindustry\cmake-build-debug\CMakeFiles\MyMindustry.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyMindustry.dir/depend

