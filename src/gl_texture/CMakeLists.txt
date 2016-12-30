####
# CMakeLists.txt
# Author: EnzoLiao95
#
# This file is CMakeLists for experiment06 - "OpenGL - Texture".
# The compiler option is NOT supposed to be editted.
#

# Find all source file in current directory
aux_source_directory(. DIR_LIB_SRCS)

# Generate static link library
add_library(GLTextureLib ${DIR_LIB_SRCS})

# Find OpenGL and GLUT packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Find SDL and SDL_image packages
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
include_directories(${SDL_INCLUDE_DIRS} ${SDL_image_INCLUDE_DIRS})

# Could not find the OpenGL and GLUT packages
if (NOT OpenGL_FOUND OR NOT GLUT_FOUND)
    message(FATAL_ERROR "Package OpenGL or GLUT not found!")
endif(NOT OpenGL_FOUND OR NOT GLUT_FOUND)

# Could not find the SDL or SDL_image packages
# Make sure you have installed these libraries
if (NOT SDL_FOUND OR NOT SDL_image_FOUND)
    message(FATAL_ERROR "Package SDL or SDL_image not found!")
endif(NOT SDL_FOUND OR NOT SDL_image_FOUND)

