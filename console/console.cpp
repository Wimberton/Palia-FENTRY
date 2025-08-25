#include "console.hpp"
#include <Windows.h>
#include <filesystem>

namespace Console {
#ifndef DISABLE_LOGGING_CONSOLE
    // Thread-safe logging infrastructure
    static std::mutex logMutex;
    static std::condition_variable logCondition;
    static std::queue<LogMessage> logQueue;
    static std::thread loggingThread;
    static std::atomic<bool> shouldStop{false};
    
    // Console and file state
    static std::ofstream logFile;
    static bool consoleAllocated = false;
    static bool fileInitialized = false;
#endif
    
    void Alloc() {
#ifndef DISABLE_LOGGING_CONSOLE
        if (consoleAllocated) return;
        
        // Initialize console
        AllocConsole();
        freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
        freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);
        freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
        
        SetConsoleTitle("Debug Console");
        consoleAllocated = true;
        
        // Initialize log file
        try {
            std::filesystem::create_directories("logs");
            logFile.open("logs/tfd_debug.log", std::ios::app);
            if (logFile.is_open()) {
                fileInitialized = true;
            }
        } catch (...) {
            // If file creation fails, just continue with console logging
        }
        
        // Start the logging thread
        shouldStop = false;
        loggingThread = std::thread(LoggingThreadWorker);
        
        // Log initial message
        EnqueueMessage("SYSTEM", "=== Debug Session Started ===");
#endif
    }
    
    void Free() {
#ifndef DISABLE_LOGGING_CONSOLE
        if (!consoleAllocated) return;
        
        // Log final message
        EnqueueMessage("SYSTEM", "=== Debug Session Ended ===");
        
        // Signal the logging thread to stop
        shouldStop = true;
        logCondition.notify_all();
        
        // Wait for the logging thread to finish
        if (loggingThread.joinable()) {
            loggingThread.join();
        }
        
        // Close log file
        if (fileInitialized && logFile.is_open()) {
            logFile.close();
            fileInitialized = false;
        }
        
        // Free console
        FreeConsole();
        consoleAllocated = false;
#endif
    }

#ifndef DISABLE_LOGGING_CONSOLE
    void LoggingThreadWorker() {
        while (!shouldStop) {
            std::unique_lock<std::mutex> lock(logMutex);
            
            // Wait for messages or shutdown signal
            logCondition.wait(lock, []() { return !logQueue.empty() || shouldStop; });
            
            // Process all available messages
            while (!logQueue.empty()) {
                LogMessage msg = logQueue.front();
                logQueue.pop();
                lock.unlock();
                
                // Process the message outside of the lock
                ProcessLogMessage(msg);
                
                lock.lock();
            }
        }
    }
    
    void ProcessLogMessage(const LogMessage& msg) {
        std::string timestamp = GetTimestamp(msg.timestamp);
        
        // Write to console
        if (consoleAllocated) {
            printf("[%s] [%s] %s\n", timestamp.c_str(), msg.category.c_str(), msg.message.c_str());
        }
        
        // Write to file
        if (fileInitialized && logFile.is_open()) {
            logFile << "[" << timestamp << "] [" << msg.category << "] " << msg.message << std::endl;
            logFile.flush();
        }
    }
    
    std::string GetTimestamp(const std::chrono::system_clock::time_point& timePoint) {
        auto time_t = std::chrono::system_clock::to_time_t(timePoint);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            timePoint.time_since_epoch()) % 1000;
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }
    
    std::string FormatMessage(const char* format, va_list args) {
        char buffer[2048];
        vsnprintf(buffer, sizeof(buffer), format, args);
        return std::string(buffer);
    }
    
    void EnqueueMessage(const std::string& category, const std::string& message) {
        if (!consoleAllocated) return;
        
        std::lock_guard<std::mutex> lock(logMutex);
        logQueue.emplace(category, message);
        logCondition.notify_one();
    }
    
    void Log(const char* format, ...) {
        va_list args;
        va_start(args, format);
        std::string message = FormatMessage(format, args);
        va_end(args);
        
        EnqueueMessage("LOG", message);
    }
    
    void LogDebug(const char* format, ...) {
        va_list args;
        va_start(args, format);
        std::string message = FormatMessage(format, args);
        va_end(args);
        
        EnqueueMessage("DEBUG", message);
    }
    
    void LogAmmo(const char* format, ...) {
        va_list args;
        va_start(args, format);
        std::string message = FormatMessage(format, args);
        va_end(args);
        
        EnqueueMessage("AMMO", message);
    }
    
    void LogFunction(const char* format, ...) {
        va_list args;
        va_start(args, format);
        std::string message = FormatMessage(format, args);
        va_end(args);
        
        EnqueueMessage("FUNCTION", message);
    }
    
    void LogRPC(const char* format, ...) {
        va_list args;
        va_start(args, format);
        std::string message = FormatMessage(format, args);
        va_end(args);
        
        EnqueueMessage("RPC", message);
    }
    
    void LogEvent(const char* format, ...) {
        va_list args;
        va_start(args, format);
        std::string message = FormatMessage(format, args);
        va_end(args);
        
        EnqueueMessage("EVENT", message);
    }
#endif
}