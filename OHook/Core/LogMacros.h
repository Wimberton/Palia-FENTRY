#pragma once

#include "Logger.h"

// New logging macros using Logger class
#define LOG_DEBUG(...) Logger::GetInstance().Debug(__VA_ARGS__)
#define LOG_INFO(...) Logger::GetInstance().Info(__VA_ARGS__)
#define LOG_WARN(...) Logger::GetInstance().Warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::GetInstance().Error(__VA_ARGS__)
#define LOG_FATAL(...) Logger::GetInstance().Fatal(__VA_ARGS__)

// Specialized logging macros
#define LOG_AMMO(...) Logger::GetInstance().LogAmmo(__VA_ARGS__)
#define LOG_FUNCTION(...) Logger::GetInstance().LogFunction(__VA_ARGS__)
#define LOG_RPC(...) Logger::GetInstance().LogRPC(__VA_ARGS__)
#define LOG_EVENT(...) Logger::GetInstance().LogEvent(__VA_ARGS__)

// Backward compatibility - map old LOG to new system
// Error messages should use ERROR level
#define LOG_OLD(...) do { \
    std::string msg(__VA_ARGS__); \
    if (msg.find("[!]") == 0 || msg.find("Error") != std::string::npos || \
        msg.find("Failed") != std::string::npos || msg.find("Unable") != std::string::npos) { \
        Logger::GetInstance().Error(__VA_ARGS__); \
    } else if (msg.find("[+]") == 0 || msg.find("Success") != std::string::npos || \
               msg.find("Setting") != std::string::npos) { \
        Logger::GetInstance().Info(__VA_ARGS__); \
    } else { \
        Logger::GetInstance().Info(__VA_ARGS__); \
    } \
} while(0)