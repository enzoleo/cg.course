# Add configuration header file
# CMake will configure the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/cgexs_config.h.in"
    "${PROJECT_BINARY_DIR}/src/cgexs_config.h"
)

####
# Choose The experiments to be constructed
# Default option: ON
# TRY `ccmake` command to change them in GUI
#
option(EXECUTE_MYEXS_01 "Construct experiment01 - Hexagram" ON)
option(EXECUTE_MYEXS_02 "Construct experiment02 - DrawTable" ON)
option(EXECUTE_MYEXS_03 "Construct experiment03 - GLViewer" ON)
option(EXECUTE_MYEXS_04 "Construct experiment04 - GLLists" ON)
option(EXECUTE_MYEXS_05 "Construct experiment05 - GLLights" ON)
option(EXECUTE_MYEXS_06 "Construct experiment06 - GLTexture" ON)

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

# Whether to construct experiment01
if(EXECUTE_MYEXS_01)
    include_directories("${PROJECT_SOURCE_DIR}/src/hexagram")
    add_subdirectory(hexagram)
    set(HexagramLib ${HexagramLib} Hexagram)
    aux_source_directory(./hexagram/ DIR_SRCS_HEX)
    add_executable(HexagramDemo ${DIR_SRCS_HEX})
    target_link_libraries(HexagramDemo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif(EXECUTE_MYEXS_01)

# Whether to construct experiment02
if(EXECUTE_MYEXS_02)
    include_directories("${PROJECT_SOURCE_DIR}/src/draw_table")
    add_subdirectory(draw_table)
    set(DrawTableLib ${DrawTableLib} DrawTable)
    aux_source_directory(./draw_table/ DIR_SRCS_DTABLE)
    add_executable(DrawTableDemo ${DIR_SRCS_DTABLE})
    target_link_libraries(DrawTableDemo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif(EXECUTE_MYEXS_02)

# Whether to construct experiment03
if(EXECUTE_MYEXS_03)
    include_directories("${PROJECT_SOURCE_DIR}/src/gl_viewer")
    add_subdirectory(gl_viewer)
    set(GLViewerLib ${GLViewerLib} GLViewer)
    aux_source_directory(./gl_viewer/ DIR_SRCS_GLVIEW)
    add_executable(GLViewerDemo ${DIR_SRCS_GLVIEW})
    target_link_libraries(GLViewerDemo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif(EXECUTE_MYEXS_03)

# Whether to construct experiment04
if(EXECUTE_MYEXS_04)
    include_directories("${PROJECT_SOURCE_DIR}/src/gl_lists")
    add_subdirectory(gl_lists)
    set(GLListsLib ${GLListsLib} GLLists)
    aux_source_directory(./gl_lists/ DIR_SRCS_GLLISTS)
    add_executable(GLListsDemo ${DIR_SRCS_GLLISTS})
    target_link_libraries(GLListsDemo GLListsLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif(EXECUTE_MYEXS_04)

# Whether to construct experiment05
if(EXECUTE_MYEXS_05)
    include_directories("${PROJECT_SOURCE_DIR}/src/gl_lights")
    add_subdirectory(gl_lights)
    set(GLLightsLib ${GLLightsLib} GLLights)
    aux_source_directory(./gl_lights/ DIR_SRCS_GLLIGHTS)
    add_executable(GLLightsDemo ${DIR_SRCS_GLLIGHTS})
    target_link_libraries(GLLightsDemo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif(EXECUTE_MYEXS_05)

# Whether to construct experiment06
if(EXECUTE_MYEXS_06)
    include_directories("${PROJECT_SOURCE_DIR}/src/gl_texture")
    add_subdirectory(gl_texture)
    set(GLTextureLib ${GLTextureLib} GLTexture)
    aux_source_directory(./gl_texture/ DIR_SRCS_GLTEXTURES)
    add_executable(GLTextureDemo ${DIR_SRCS_GLTEXTURES})
    target_link_libraries(GLTextureDemo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY})
endif(EXECUTE_MYEXS_06)

# GDB Debug supported
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
