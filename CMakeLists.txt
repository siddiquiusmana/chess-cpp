# Meta info for the project
cmake_minimum_required(VERSION 3.5.0)
project(opengl_chess VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

# GLFW Related
set(GLFW3_INCLUDE_DIR "/usr/local/include")
set(GLFW3_LIBRARY "/usr/local/lib64/libglfw3.a")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

include_directories(${GLFW3_INCLUDE_DIR})

# OpenGL related
find_package(OpenGL REQUIRED)

# Glad libary adder
add_library(glad "/home/siddiquiusmana/Projects/opengl-chess/third-party/include/glad.h" "/home/siddiquiusmana/Projects/opengl-chess/third-party/src/glad.c")

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