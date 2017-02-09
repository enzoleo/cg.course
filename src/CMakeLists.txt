# Add configuration header file
# CMake will configure the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/cgexs_config.h.in"
    "${PROJECT_BINARY_DIR}/src/cgexs_config.h"
)

# CMake compiler settings
set(CMAKE_C_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++0x")

# Set cmake module path
# CMake will search Find___.cmake files in this path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Set cmake executable output path
# All executables will be generated in this path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# GDB Debug supported
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# Choose The assignments to be constructed
# Default option: ON
# TRY `ccmake` command to change them in GUI
option(EXECUTE_MYEXS_01 "Construct assignment01 - Hexagram"  ON)
option(EXECUTE_MYEXS_02 "Construct assignment02 - DrawTable" ON)
option(EXECUTE_MYEXS_03 "Construct assignment03 - GLViewer"  ON)
option(EXECUTE_MYEXS_04 "Construct assignment04 - GLLists"   ON)
option(EXECUTE_MYEXS_05 "Construct assignment05 - GLLights"  ON)
option(EXECUTE_MYEXS_06 "Construct assignment06 - GLTexture" ON)
option(EXECUTE_MYEXS_07 "Construct assignment07 - GLPick"    ON)

# Find OpenGL and GLUT packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
if(NOT OPENGL_FOUND OR NOT GLUT_FOUND)
    message(FATAL_ERROR "OpenGL or glut not found!")
endif()
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Find SDL and SDL2_image packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
set(SDL2_LIBRARY_LINKING     ON)
set(SDL2_LIBRARY_NOT_LINKING OFF)

# Could not find the SDL or SDL2_image packages
# Make sure you have installed these libraries. If not, exs06 will not be compiled
if(NOT SDL2_FOUND OR NOT SDL2_IMAGE_FOUND)
    message("Package SDL2 or SDL2_image not found!")
    message("Ignore assignment06 - GLTexture")
    set(EXECUTE_MYEXS_06 OFF)
else()
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
endif()

# Find stanford_bunny header and source
FILE(GLOB_RECURSE EXS04_DEP_CPP "${PROJECT_SOURCE_DIR}/src/gl_lists/stanford_bunny.cpp")
FILE(GLOB_RECURSE EXS04_DEP_H   "${PROJECT_SOURCE_DIR}/src/gl_lists/stanford_bunny.h")
if(NOT EXS04_DEP_CPP OR NOT EXS04_DEP_H)
    message("File missing: stanford_bunny")
    message("Ignore assignment04 - GLLists")
    set(EXECUTE_MYEXS_04 OFF)
endif()

# Find bunny.h with vertex array and normals
FILE(GLOB_RECURSE EXS07_DEP_H "${PROJECT_SOURCE_DIR}/src/gl_pick/bunny.h")
if(NOT EXS07_DEP_H)
    message("File missing: bunny.h")
    message("Ignore assignment07 - GLPick")
    set(EXECUTE_MYEXS_07 OFF)
endif()

# CMake macro: compile specific assignment
macro(add_exec_exs exs_flag dirName demoName SDL2_LIBRARY_LINKING_FLAG)
    if(${exs_flag})
        set(fullDirName "${PROJECT_SOURCE_DIR}/src/${dirName}")
        set(DIR_SRCS "")
        include_directories(${fullDirName})
        aux_source_directory(${fullDirName} DIR_SRCS)
        add_executable(${demoName} ${DIR_SRCS})
        target_link_libraries(${demoName} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
        # If we need to link SDL2 libraries
        if(${SDL2_LIBRARY_LINKING_FLAG})
            target_link_libraries(${demoName} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
        endif()
    endif()
endmacro(add_exec_exs)

# Whether to construct assignments
add_exec_exs(EXECUTE_MYEXS_01 hexagram   HexagramDemo  SDL2_LIBRARY_NOT_LINKING)
add_exec_exs(EXECUTE_MYEXS_02 draw_table DrawTableDemo SDL2_LIBRARY_NOT_LINKING)
add_exec_exs(EXECUTE_MYEXS_03 gl_viewer  GLViewerDemo  SDL2_LIBRARY_NOT_LINKING)
add_exec_exs(EXECUTE_MYEXS_04 gl_lists   GLListsDemo   SDL2_LIBRARY_NOT_LINKING)
add_exec_exs(EXECUTE_MYEXS_05 gl_lights  GLLightsDemo  SDL2_LIBRARY_NOT_LINKING)
add_exec_exs(EXECUTE_MYEXS_06 gl_texture GLTextureDemo SDL2_LIBRARY_LINKING)
add_exec_exs(EXECUTE_MYEXS_07 gl_pick    GLPickDemo    SDL2_LIBRARY_NOT_LINKING)
