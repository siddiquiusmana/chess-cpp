#include "include/SDL/SDLWindow.h"
#include "include/Logger/LogManager.h"

void displayBanner(std::shared_ptr<spdlog::logger> logger);

int main(int argc, char** argv)
{
    // The log manager that instantiates logging for the whole app
    LogManager lm(argc, argv);

    // The logger for Main
    auto mainLogger = lm.getLogger("Main");

    // Chess Banner
    displayBanner(mainLogger);

    // Create a window
    SDLWindow window("Chess", lm);
    window.createWindow();

    return 0;
}

void displayBanner(std::shared_ptr<spdlog::logger> logger)
{
    logger->info("*************************************************");
    logger->info("**************  Chess Application  **************");
    logger->info("*************************************************");
}