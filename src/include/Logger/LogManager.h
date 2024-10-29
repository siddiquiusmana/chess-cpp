#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <spdlog/cfg/argv.h>
#include <spdlog/cfg/env.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

/**
 * The class to manage loggers
 */
class LogManager
{
    public:
        // Constructor that initializes the console and
        // file logger with patterns
        LogManager(int argc, char **argv);

        // Simply shutsdowns the loggers
        ~LogManager();

        // Returns a logger that uses the configuration
        // set in the LogManager class.
        std::shared_ptr<spdlog::logger> getLogger(std::string name);

    private:
        // Pattern for console logger
        std::string lm_consolePattern;
        
        // Pattern for file logger
        std::string lm_filePattern;

        // Vector with the console and file sinks
        std::vector<spdlog::sink_ptr> lm_sinks;

        // The loggers
        std::vector<std::shared_ptr<spdlog::logger>> lm_loggers;

        // Map of loggers by name
        std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> lm_loggerMap;

        // Initializes the log manager
        void initialize(int argc, char** argv);

        // Used to shutdown the loggers
        void shutdown();
};