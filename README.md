# chess-cpp
 A chess game developed using SDL2. Mainly to learn C++ and its supporting development tools like CMake, Make, and see what game development looks like on C++.

 Need to use X11 with SDL2 on Fedora since wayland requires elevated privileges to create graphical windows. Can do the same by adding the following to the settings.json in VS Code:
 `
 "cmake.configureEnvironment": {
    "SDL_VIDEODRIVER": "x11"
 }
 `