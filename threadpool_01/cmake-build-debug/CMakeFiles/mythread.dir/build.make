# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/sun/clion-2016.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/sun/clion-2016.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sun/Mthreadpool/threadpool_01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sun/Mthreadpool/threadpool_01/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mythread.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mythread.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mythread.dir/flags.make

CMakeFiles/mythread.dir/main.cpp.o: CMakeFiles/mythread.dir/flags.make
CMakeFiles/mythread.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sun/Mthreadpool/threadpool_01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mythread.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mythread.dir/main.cpp.o -c /home/sun/Mthreadpool/threadpool_01/main.cpp

CMakeFiles/mythread.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mythread.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sun/Mthreadpool/threadpool_01/main.cpp > CMakeFiles/mythread.dir/main.cpp.i

CMakeFiles/mythread.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mythread.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sun/Mthreadpool/threadpool_01/main.cpp -o CMakeFiles/mythread.dir/main.cpp.s

CMakeFiles/mythread.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mythread.dir/main.cpp.o.requires

CMakeFiles/mythread.dir/main.cpp.o.provides: CMakeFiles/mythread.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mythread.dir/build.make CMakeFiles/mythread.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mythread.dir/main.cpp.o.provides

CMakeFiles/mythread.dir/main.cpp.o.provides.build: CMakeFiles/mythread.dir/main.cpp.o


# Object files for target mythread
mythread_OBJECTS = \
"CMakeFiles/mythread.dir/main.cpp.o"

# External object files for target mythread
mythread_EXTERNAL_OBJECTS =

libmythread.so: CMakeFiles/mythread.dir/main.cpp.o
libmythread.so: CMakeFiles/mythread.dir/build.make
libmythread.so: CMakeFiles/mythread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sun/Mthreadpool/threadpool_01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libmythread.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mythread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mythread.dir/build: libmythread.so

.PHONY : CMakeFiles/mythread.dir/build

CMakeFiles/mythread.dir/requires: CMakeFiles/mythread.dir/main.cpp.o.requires

.PHONY : CMakeFiles/mythread.dir/requires

CMakeFiles/mythread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mythread.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mythread.dir/clean

CMakeFiles/mythread.dir/depend:
	cd /home/sun/Mthreadpool/threadpool_01/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sun/Mthreadpool/threadpool_01 /home/sun/Mthreadpool/threadpool_01 /home/sun/Mthreadpool/threadpool_01/cmake-build-debug /home/sun/Mthreadpool/threadpool_01/cmake-build-debug /home/sun/Mthreadpool/threadpool_01/cmake-build-debug/CMakeFiles/mythread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mythread.dir/depend

