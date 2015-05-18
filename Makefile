# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_SOURCE_DIR = /home/stefanomandelli/CCDOPSL/ConsoleSbig

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stefanomandelli/CCDOPSL/ConsoleSbig

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/stefanomandelli/CCDOPSL/ConsoleSbig/CMakeFiles /home/stefanomandelli/CCDOPSL/ConsoleSbig/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/stefanomandelli/CCDOPSL/ConsoleSbig/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ConsoleSbig

# Build rule for target.
ConsoleSbig: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ConsoleSbig
.PHONY : ConsoleSbig

# fast build rule for target.
ConsoleSbig/fast:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/build
.PHONY : ConsoleSbig/fast

src/ConsoleSbig.o: src/ConsoleSbig.cpp.o
.PHONY : src/ConsoleSbig.o

# target to build an object file
src/ConsoleSbig.cpp.o:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/ConsoleSbig.cpp.o
.PHONY : src/ConsoleSbig.cpp.o

src/ConsoleSbig.i: src/ConsoleSbig.cpp.i
.PHONY : src/ConsoleSbig.i

# target to preprocess a source file
src/ConsoleSbig.cpp.i:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/ConsoleSbig.cpp.i
.PHONY : src/ConsoleSbig.cpp.i

src/ConsoleSbig.s: src/ConsoleSbig.cpp.s
.PHONY : src/ConsoleSbig.s

# target to generate assembly for a file
src/ConsoleSbig.cpp.s:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/ConsoleSbig.cpp.s
.PHONY : src/ConsoleSbig.cpp.s

src/csbigcam.o: src/csbigcam.cpp.o
.PHONY : src/csbigcam.o

# target to build an object file
src/csbigcam.cpp.o:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/csbigcam.cpp.o
.PHONY : src/csbigcam.cpp.o

src/csbigcam.i: src/csbigcam.cpp.i
.PHONY : src/csbigcam.i

# target to preprocess a source file
src/csbigcam.cpp.i:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/csbigcam.cpp.i
.PHONY : src/csbigcam.cpp.i

src/csbigcam.s: src/csbigcam.cpp.s
.PHONY : src/csbigcam.s

# target to generate assembly for a file
src/csbigcam.cpp.s:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/csbigcam.cpp.s
.PHONY : src/csbigcam.cpp.s

src/csbigimg.o: src/csbigimg.cpp.o
.PHONY : src/csbigimg.o

# target to build an object file
src/csbigimg.cpp.o:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/csbigimg.cpp.o
.PHONY : src/csbigimg.cpp.o

src/csbigimg.i: src/csbigimg.cpp.i
.PHONY : src/csbigimg.i

# target to preprocess a source file
src/csbigimg.cpp.i:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/csbigimg.cpp.i
.PHONY : src/csbigimg.cpp.i

src/csbigimg.s: src/csbigimg.cpp.s
.PHONY : src/csbigimg.s

# target to generate assembly for a file
src/csbigimg.cpp.s:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/csbigimg.cpp.s
.PHONY : src/csbigimg.cpp.s

src/getImage.o: src/getImage.cpp.o
.PHONY : src/getImage.o

# target to build an object file
src/getImage.cpp.o:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/getImage.cpp.o
.PHONY : src/getImage.cpp.o

src/getImage.i: src/getImage.cpp.i
.PHONY : src/getImage.i

# target to preprocess a source file
src/getImage.cpp.i:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/getImage.cpp.i
.PHONY : src/getImage.cpp.i

src/getImage.s: src/getImage.cpp.s
.PHONY : src/getImage.s

# target to generate assembly for a file
src/getImage.cpp.s:
	$(MAKE) -f CMakeFiles/ConsoleSbig.dir/build.make CMakeFiles/ConsoleSbig.dir/src/getImage.cpp.s
.PHONY : src/getImage.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... ConsoleSbig"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src/ConsoleSbig.o"
	@echo "... src/ConsoleSbig.i"
	@echo "... src/ConsoleSbig.s"
	@echo "... src/csbigcam.o"
	@echo "... src/csbigcam.i"
	@echo "... src/csbigcam.s"
	@echo "... src/csbigimg.o"
	@echo "... src/csbigimg.i"
	@echo "... src/csbigimg.s"
	@echo "... src/getImage.o"
	@echo "... src/getImage.i"
	@echo "... src/getImage.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
