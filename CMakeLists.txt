####
# CMakeList
# Author: EnzoLiao95
# CMake Test Version: VERSION 3.7
#

# CMake Minimum Version Required
cmake_minimum_required(VERSION 2.8)
project(CG_exs_demo)

###
# The source files are packed in `src` folder
# Add directory `src` so CMake can call `CMakeLists.txt` in `src`
# The `CMakeLists.txt` in `src` define the dependencies of projects
#
add_subdirectory(src)
