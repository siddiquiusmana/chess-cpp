#include "include/Chess.h"

/**
 * Main function
 */
int main(int argc, char** argv)
{
    // The log manager that instantiates logging for the whole app
    auto lm_ptr = std::make_shared<LogManager>(argc, argv);
    
    // The chess game
    Chess chess(lm_ptr);
    chess.run();

    return 0;
}

