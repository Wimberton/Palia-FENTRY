#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iostream>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4
};

class Logger {
public:
    static Logger& GetInstance();
    
    void SetLogLevel(LogLevel level);
    void SetLogFile(const std::string& filename);
    void EnableConsoleOutput(bool enabled);
    void EnableFileOutput(bool enabled);
    
    void Log(LogLevel level, const char* format, ...);
    void Debug(const char* format, ...);
    void Info(const char* format, ...);
    void Warn(const char* format, ...);
    void Error(const char* format, ...);
    void Fatal(const char* format, ...);
    
    // Convenience methods for existing log types
    void LogAmmo(const char* format, ...);
    void LogFunction(const char* format, ...);
    void LogRPC(const char* format, ...);
    void LogEvent(const char* format, ...);
    
private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    void WriteLog(LogLevel level, const std::string& message);
    std::string GetTimestamp();
    std::string GetLevelString(LogLevel level);
    std::string FormatMessage(const char* format, va_list args);
    
    LogLevel m_currentLevel = LogLevel::INFO;
    bool m_consoleOutput = true;
    bool m_fileOutput = false;
    std::string m_logFileName;
    std::ofstream m_logFile;
    std::mutex m_logMutex;
};