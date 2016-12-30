####
# CMakeLists.txt
# Author: EnzoLiao95
#
# This file is CMakeLists for experiment05 - "OpenGL - Lights".
# The compiler option is NOT supposed to be editted.
#

# Find all source file in current directory
aux_source_directory(. DIR_LIB_SRCS)

# Generate static link library
add_library(GLLightsLib ${DIR_LIB_SRCS})

# Find OpenGL and GLUT packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Could not find the OpenGL and GLUT packages
if (NOT OpenGL_FOUND OR NOT GLUT_FOUND)
    message(FATAL_ERROR "Package OpenGL or GLUT not found!")
endif(NOT OpenGL_FOUND OR NOT GLUT_FOUND)

