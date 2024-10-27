#include "include/SDLWindow.h"
#include <spdlog/cfg/env.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main(void)
{
    spdlog::cfg::load_env_levels();

    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("This is a debug message");

    // Create a window
    SDLWindow window("Chess");
    window.createWindow();

    return 0;
}