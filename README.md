# chess-cpp
 A chess game developed using SDL2. Mainly to learn C++ and its supporting development tools like CMake, Make, and see what game development looks like on C++.

## Installation
 Need to install the following:
 - [GCC/GDB](https://code.visualstudio.com/docs/cpp/config-mingw)
 - [CMake](https://cmake.org/download/)
 - [An IDE (Visual Studio Code)](https://code.visualstudio.com/)
 - [SDL2](https://wiki.libsdl.org/SDL2/Installation)
 - [SDL2 Image](https://github.com/libsdl-org/SDL_image/releases)
 - [spdlog](https://github.com/gabime/spdlog)

### Installing libraries
If a project is using cmake, compiling the project is super easy. Find the directory where the CMakeLists.txt file lives (usually in the root) and create a directory named "build" there. Go into that directory and open a terminal. Type ```cmake ..``` to configure the project. 

To compile, just type ```make``` and this will actually try to compile the program. This will require you to have installed all the prerequisites of that program. Once successful, the program will produce an output (in this case, a chess executable). If it's a library that you're trying to install, you can additionally run ```make install``` to install the library to your system's default installation directory.

## Notes
 I'm developing on Fedora 41 so there might be some stuff herethat's different if you're developing on windows.
 
 Need to use X11 with SDL2 on Fedora since wayland requires elevated privileges to create graphical windows. Can do the same by adding the following to the settings.json in VS Code:
 `
 "cmake.configureEnvironment": {
    "SDL_VIDEODRIVER": "x11"
 }
 `