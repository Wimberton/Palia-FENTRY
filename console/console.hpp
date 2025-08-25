#pragma once
#include <cstdio>
#include <cstdarg>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define DISABLE_LOGGING_CONSOLE

#ifndef DISABLE_LOGGING_CONSOLE
#define LOG(...) Console::Log(__VA_ARGS__)
    #define LOG_DEBUG(...) Console::LogDebug(__VA_ARGS__)
    #define LOG_AMMO(...) Console::LogAmmo(__VA_ARGS__)
    #define LOG_FUNCTION(...) Console::LogFunction(__VA_ARGS__)
    #define LOG_RPC(...) Console::LogRPC(__VA_ARGS__)
    #define LOG_EVENT(...) Console::LogEvent(__VA_ARGS__)
#else
#define LOG(...)
    #define LOG_DEBUG(...)
    #define LOG_AMMO(...)
    #define LOG_FUNCTION(...)
#define LOG_RPC(...)
    #define LOG_EVENT(...)
#endif

namespace Console {
    // Log message structure for async logging
    struct LogMessage {
        std::string category;
        std::string message;
        std::chrono::system_clock::time_point timestamp;
        
        LogMessage(const std::string& cat, const std::string& msg) 
            : category(cat), message(msg), timestamp(std::chrono::system_clock::now()) {}
    };
    
    void Alloc();
    void Free();
    void Log(const char* format, ...);
    void LogDebug(const char* format, ...);
    void LogAmmo(const char* format, ...);
    void LogFunction(const char* format, ...);
    void LogRPC(const char* format, ...);
    void LogEvent(const char* format, ...);
    
    // Internal functions
    void EnqueueMessage(const std::string& category, const std::string& message);
    void LoggingThreadWorker();
    void ProcessLogMessage(const LogMessage& msg);
    std::string GetTimestamp(const std::chrono::system_clock::time_point& timePoint);
    std::string FormatMessage(const char* format, va_list args);
}