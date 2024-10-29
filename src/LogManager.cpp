#include "include/Logger/LogManager.h"

LogManager::LogManager(int argc, char** argv)
{
    LogManager::initialize(argc, argv);
}

LogManager::~LogManager()
{
    LogManager::shutdown();
}

void LogManager::initialize(int argc, char** argv)
{
    // Store argc and argv for later so every logger can
    // take the logging level if one is defined in the 
    // program arguments
    lm_argc = argc;
    lm_argv = argv;

    // Create the console sink
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // Create the file sink
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);

    // Set the sinks
    lm_sinks = { consoleSink, fileSink };
}

std::shared_ptr<spdlog::logger> LogManager::getLogger(std::string loggerName)
{
    // Check if the logger has already been created and return it
    auto mapIterator = lm_loggerMap.find(loggerName);
    if(mapIterator != lm_loggerMap.end())
    {
        return mapIterator->second;
    }

    // Create a new logger with the given name, set the sinks and register the logger
    auto logger = std::make_shared<spdlog::logger>(loggerName, lm_sinks.begin(), lm_sinks.end());
    spdlog::register_logger(logger);

    // Check if log level has been set in the environment
    spdlog::cfg::load_env_levels();

    // Check if the log level is set in the command line arguments
    // Overwrite the environment variable log level if set
    spdlog::cfg::load_argv_levels(lm_argc, lm_argv);

    // Add the logger to the loggerMap and return the logger
    lm_loggerMap.insert_or_assign(loggerName, logger);
    return logger;
}

void LogManager::shutdown()
{
    // Drop all the loggers
    spdlog::drop_all();

    // Shutdown spdlog
    spdlog::shutdown();
}