# Meta info for the project
cmake_minimum_required(VERSION 3.5.0)
project(chess VERSION 0.1.0 LANGUAGES C CXX)

# Look for SDL2 and other various 3rd party libraries and fail if not found
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

# Create an executable by adding all the source code
add_executable(chess 
    src/main.cpp
    src/SDL/SDLWindow.cpp
    src/LogManager/LogManager.cpp
    src/Chess/Bishop.cpp
    src/Chess/Chess.cpp
    src/Chess/ChessPiece.cpp
    src/Chess/ChessUtils.cpp
    src/Chess/King.cpp
    src/Chess/Knight.cpp
    src/Chess/Pawn.cpp
    src/Chess/Queen.cpp
    src/Chess/Rook.cpp
    src/theme/ThemeManager.cpp
)

# The include directory with the header files
target_include_directories(chess
    PUBLIC src/include
)

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library.
target_link_libraries(chess 
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    spdlog::spdlog
)