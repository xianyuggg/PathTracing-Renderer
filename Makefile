# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xianyu/Desktop/SourceCode/graphicsHW/PathTracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xianyu/Desktop/SourceCode/graphicsHW/PathTracing

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/xianyu/Desktop/SourceCode/graphicsHW/PathTracing/CMakeFiles /Users/xianyu/Desktop/SourceCode/graphicsHW/PathTracing/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/xianyu/Desktop/SourceCode/graphicsHW/PathTracing/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named PathTracing

# Build rule for target.
PathTracing: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PathTracing
.PHONY : PathTracing

# fast build rule for target.
PathTracing/fast:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/build
.PHONY : PathTracing/fast

const/Constant.o: const/Constant.cpp.o

.PHONY : const/Constant.o

# target to build an object file
const/Constant.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/const/Constant.cpp.o
.PHONY : const/Constant.cpp.o

const/Constant.i: const/Constant.cpp.i

.PHONY : const/Constant.i

# target to preprocess a source file
const/Constant.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/const/Constant.cpp.i
.PHONY : const/Constant.cpp.i

const/Constant.s: const/Constant.cpp.s

.PHONY : const/Constant.s

# target to generate assembly for a file
const/Constant.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/const/Constant.cpp.s
.PHONY : const/Constant.cpp.s

const/Vec.o: const/Vec.cpp.o

.PHONY : const/Vec.o

# target to build an object file
const/Vec.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/const/Vec.cpp.o
.PHONY : const/Vec.cpp.o

const/Vec.i: const/Vec.cpp.i

.PHONY : const/Vec.i

# target to preprocess a source file
const/Vec.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/const/Vec.cpp.i
.PHONY : const/Vec.cpp.i

const/Vec.s: const/Vec.cpp.s

.PHONY : const/Vec.s

# target to generate assembly for a file
const/Vec.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/const/Vec.cpp.s
.PHONY : const/Vec.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/main.cpp.s
.PHONY : main.cpp.s

object/AABB.o: object/AABB.cpp.o

.PHONY : object/AABB.o

# target to build an object file
object/AABB.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/AABB.cpp.o
.PHONY : object/AABB.cpp.o

object/AABB.i: object/AABB.cpp.i

.PHONY : object/AABB.i

# target to preprocess a source file
object/AABB.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/AABB.cpp.i
.PHONY : object/AABB.cpp.i

object/AABB.s: object/AABB.cpp.s

.PHONY : object/AABB.s

# target to generate assembly for a file
object/AABB.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/AABB.cpp.s
.PHONY : object/AABB.cpp.s

object/KdTree.o: object/KdTree.cpp.o

.PHONY : object/KdTree.o

# target to build an object file
object/KdTree.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/KdTree.cpp.o
.PHONY : object/KdTree.cpp.o

object/KdTree.i: object/KdTree.cpp.i

.PHONY : object/KdTree.i

# target to preprocess a source file
object/KdTree.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/KdTree.cpp.i
.PHONY : object/KdTree.cpp.i

object/KdTree.s: object/KdTree.cpp.s

.PHONY : object/KdTree.s

# target to generate assembly for a file
object/KdTree.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/KdTree.cpp.s
.PHONY : object/KdTree.cpp.s

object/Obj.o: object/Obj.cpp.o

.PHONY : object/Obj.o

# target to build an object file
object/Obj.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Obj.cpp.o
.PHONY : object/Obj.cpp.o

object/Obj.i: object/Obj.cpp.i

.PHONY : object/Obj.i

# target to preprocess a source file
object/Obj.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Obj.cpp.i
.PHONY : object/Obj.cpp.i

object/Obj.s: object/Obj.cpp.s

.PHONY : object/Obj.s

# target to generate assembly for a file
object/Obj.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Obj.cpp.s
.PHONY : object/Obj.cpp.s

object/Plane.o: object/Plane.cpp.o

.PHONY : object/Plane.o

# target to build an object file
object/Plane.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Plane.cpp.o
.PHONY : object/Plane.cpp.o

object/Plane.i: object/Plane.cpp.i

.PHONY : object/Plane.i

# target to preprocess a source file
object/Plane.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Plane.cpp.i
.PHONY : object/Plane.cpp.i

object/Plane.s: object/Plane.cpp.s

.PHONY : object/Plane.s

# target to generate assembly for a file
object/Plane.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Plane.cpp.s
.PHONY : object/Plane.cpp.s

object/Spheres.o: object/Spheres.cpp.o

.PHONY : object/Spheres.o

# target to build an object file
object/Spheres.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Spheres.cpp.o
.PHONY : object/Spheres.cpp.o

object/Spheres.i: object/Spheres.cpp.i

.PHONY : object/Spheres.i

# target to preprocess a source file
object/Spheres.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Spheres.cpp.i
.PHONY : object/Spheres.cpp.i

object/Spheres.s: object/Spheres.cpp.s

.PHONY : object/Spheres.s

# target to generate assembly for a file
object/Spheres.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Spheres.cpp.s
.PHONY : object/Spheres.cpp.s

object/Texture.o: object/Texture.cpp.o

.PHONY : object/Texture.o

# target to build an object file
object/Texture.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Texture.cpp.o
.PHONY : object/Texture.cpp.o

object/Texture.i: object/Texture.cpp.i

.PHONY : object/Texture.i

# target to preprocess a source file
object/Texture.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Texture.cpp.i
.PHONY : object/Texture.cpp.i

object/Texture.s: object/Texture.cpp.s

.PHONY : object/Texture.s

# target to generate assembly for a file
object/Texture.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make CMakeFiles/PathTracing.dir/object/Texture.cpp.s
.PHONY : object/Texture.cpp.s

world&camera/World.o: world&camera/World.cpp.o

.PHONY : world&camera/World.o

# target to build an object file
world&camera/World.cpp.o:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make "CMakeFiles/PathTracing.dir/world&camera/World.cpp.o"
.PHONY : world&camera/World.cpp.o

world&camera/World.i: world&camera/World.cpp.i

.PHONY : world&camera/World.i

# target to preprocess a source file
world&camera/World.cpp.i:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make "CMakeFiles/PathTracing.dir/world&camera/World.cpp.i"
.PHONY : world&camera/World.cpp.i

world&camera/World.s: world&camera/World.cpp.s

.PHONY : world&camera/World.s

# target to generate assembly for a file
world&camera/World.cpp.s:
	$(MAKE) -f CMakeFiles/PathTracing.dir/build.make "CMakeFiles/PathTracing.dir/world&camera/World.cpp.s"
.PHONY : world&camera/World.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... PathTracing"
	@echo "... const/Constant.o"
	@echo "... const/Constant.i"
	@echo "... const/Constant.s"
	@echo "... const/Vec.o"
	@echo "... const/Vec.i"
	@echo "... const/Vec.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... object/AABB.o"
	@echo "... object/AABB.i"
	@echo "... object/AABB.s"
	@echo "... object/KdTree.o"
	@echo "... object/KdTree.i"
	@echo "... object/KdTree.s"
	@echo "... object/Obj.o"
	@echo "... object/Obj.i"
	@echo "... object/Obj.s"
	@echo "... object/Plane.o"
	@echo "... object/Plane.i"
	@echo "... object/Plane.s"
	@echo "... object/Spheres.o"
	@echo "... object/Spheres.i"
	@echo "... object/Spheres.s"
	@echo "... object/Texture.o"
	@echo "... object/Texture.i"
	@echo "... object/Texture.s"
	@echo "... world&camera/World.o"
	@echo "... world&camera/World.i"
	@echo "... world&camera/World.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

