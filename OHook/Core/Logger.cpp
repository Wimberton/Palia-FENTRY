#include "Logger.h"
#include <cstdarg>
#include <iomanip>
#include <sstream>
#include <Windows.h>

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

Logger::~Logger() {
    std::lock_guard<std::mutex> lock(m_logMutex);
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void Logger::SetLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_currentLevel = level;
}

void Logger::SetLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
    
    m_logFileName = filename;
    if (m_fileOutput && !filename.empty()) {
        m_logFile.open(filename, std::ios::app);
        if (!m_logFile.is_open()) {
            // Fallback to console if file can't be opened
            std::cerr << "[LOGGER] Failed to open log file: " << filename << std::endl;
        }
    }
}

void Logger::EnableConsoleOutput(bool enabled) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_consoleOutput = enabled;
}

void Logger::EnableFileOutput(bool enabled) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_fileOutput = enabled;
    
    if (enabled && !m_logFileName.empty() && !m_logFile.is_open()) {
        m_logFile.open(m_logFileName, std::ios::app);
        if (!m_logFile.is_open()) {
            std::cerr << "[LOGGER] Failed to open log file: " << m_logFileName << std::endl;
        }
    } else if (!enabled && m_logFile.is_open()) {
        m_logFile.close();
    }
}

void Logger::Log(LogLevel level, const char* format, ...) {
    if (level < m_currentLevel) {
        return;
    }
    
    va_list args;
    va_start(args, format);
    std::string message = FormatMessage(format, args);
    va_end(args);
    
    WriteLog(level, message);
}

void Logger::Debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::DEBUG, message);
}

void Logger::Info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::INFO, message);
}

void Logger::Warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::WARN, message);
}

void Logger::Error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::ERROR, message);
}

void Logger::Fatal(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::FATAL, message);
}

void Logger::LogAmmo(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = "[AMMO] " + FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::DEBUG, message);
}

void Logger::LogFunction(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = "[FUNC] " + FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::DEBUG, message);
}

void Logger::LogRPC(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = "[RPC] " + FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::DEBUG, message);
}

void Logger::LogEvent(const char* format, ...) {
    va_list args;
    va_start(args, format);
    std::string message = "[EVENT] " + FormatMessage(format, args);
    va_end(args);
    WriteLog(LogLevel::INFO, message);
}

void Logger::WriteLog(LogLevel level, const std::string& message) {
    if (level < m_currentLevel) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(m_logMutex);
    
    std::string timestamp = GetTimestamp();
    std::string levelStr = GetLevelString(level);
    std::string fullMessage = timestamp + " [" + levelStr + "] " + message;
    
    // Console output
    if (m_consoleOutput) {
        if (level >= LogLevel::ERROR) {
            std::cerr << fullMessage << std::endl;
        } else {
            std::cout << fullMessage << std::endl;
        }
    }
    
    // File output
    if (m_fileOutput && m_logFile.is_open()) {
        m_logFile << fullMessage << std::endl;
        m_logFile.flush();
    }
}

std::string Logger::GetTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Logger::GetLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO ";
        case LogLevel::WARN:  return "WARN ";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string Logger::FormatMessage(const char* format, va_list args) {
    // Calculate required buffer size
    va_list args_copy;
    va_copy(args_copy, args);
    int size = vsnprintf(nullptr, 0, format, args_copy);
    va_end(args_copy);
    
    if (size <= 0) {
        return "";
    }
    
    // Format the message
    std::string result(size, '\0');
    vsnprintf(&result[0], size + 1, format, args);
    return result;
}