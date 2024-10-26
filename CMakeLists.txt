# Meta info for the project
cmake_minimum_required(VERSION 3.5.0)
project(chess VERSION 0.1.0 LANGUAGES C CXX)

# Look for SDL2 and other various 3rd party libraries and fail if not found
find_package(SDL2 REQUIRED)

# Create an executable by adding all the source code
add_executable(chess 
    src/main.cpp
)

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library.
target_link_libraries(chess 
    SDL2::SDL2
    SDL2::SDL2main
)