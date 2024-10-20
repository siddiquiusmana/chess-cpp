# Meta info for the project
cmake_minimum_required(VERSION 3.5.0)
project(opengl_chess VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

# GLFW Related - Built the GLFW from source using https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
# and following the instructions on https://www.glfw.org/docs/latest/compile.html
set(GLFW3_INCLUDE_DIR "/usr/local/include")
set(GLFW3_LIBRARY "/usr/local/lib64/libglfw3.a")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

include_directories(${GLFW3_INCLUDE_DIR})

# OpenGL related - Installed through the dnf repo manager
find_package(OpenGL REQUIRED)

# Glad libary - Add the header and the C file with the glad code to a glad library so we can link it
# to the executable easier.
add_library(glad "./third-party/include/glad.h" "./third-party/src/glad.c")

# Executable for this project
add_executable(opengl_chess 
    src/helloworld.cpp
)

# Linking the libraries to the executable
target_link_libraries(opengl_chess 
    glfw3
    glad
    OpenGL::GL
)
