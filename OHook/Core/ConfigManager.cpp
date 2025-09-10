#include "ConfigManager.h"
#include "Logger.h"
#include "LogMacros.h"
#include "console.hpp"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

ConfigManager& ConfigManager::GetInstance() {
    static ConfigManager instance;
    return instance;
}

bool ConfigManager::LoadConfig(const std::string& configPath) {
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        LOG_ERROR("Failed to open config file: %s", configPath.c_str());
        return false;
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errors;
    
    if (!Json::parseFromStream(builder, configFile, &root, &errors)) {
        LOG_ERROR("Failed to parse config file: %s", errors.c_str());
        return false;
    }

    try {
        // Parse clients
        const Json::Value& clients = root["clients"];
        if (!clients.isObject()) {
            LOG_ERROR("Invalid config: 'clients' must be an object");
            return false;
        }

        // Parse standalone client
        if (clients.isMember("standalone")) {
            const Json::Value& standalone = clients["standalone"];
            ClientConfig config;
            config.executable = standalone["executable"].asString();
            
            const Json::Value& offsets = standalone["offsets"];
            for (const auto& member : offsets.getMemberNames()) {
                config.offsets[member] = ParseHexString(offsets[member].asString());
            }
            
            m_clientConfigs[ClientType::STANDALONE] = std::move(config);
            LOG_INFO("Loaded STANDALONE client config");
        }

        // Parse steam client
        if (clients.isMember("steam")) {
            const Json::Value& steam = clients["steam"];
            ClientConfig config;
            config.executable = steam["executable"].asString();
            
            const Json::Value& offsets = steam["offsets"];
            for (const auto& member : offsets.getMemberNames()) {
                config.offsets[member] = ParseHexString(offsets[member].asString());
            }
            
            m_clientConfigs[ClientType::STEAM] = std::move(config);
            LOG_INFO("Loaded STEAM client config");
        }

        // Parse default client
        if (root.isMember("default_client")) {
            std::string defaultStr = root["default_client"].asString();
            std::transform(defaultStr.begin(), defaultStr.end(), defaultStr.begin(), ::tolower);
            
            if (defaultStr == "standalone") {
                m_defaultClient = ClientType::STANDALONE;
            } else if (defaultStr == "steam") {
                m_defaultClient = ClientType::STEAM;
            }
        }

        m_configLoaded = true;
        InitializeLogger();
        LOG_INFO("Config loaded successfully");
        return true;
        
    } catch (const std::exception& e) {
        LOG_ERROR("Error parsing config: %s", e.what());
        return false;
    }
}

ClientConfig* ConfigManager::GetClientConfig(ClientType clientType) {
    if (!m_configLoaded) {
        LOG_ERROR("Config not loaded");
        return nullptr;
    }
    
    auto it = m_clientConfigs.find(clientType);
    if (it != m_clientConfigs.end()) {
        return &it->second;
    }
    
    LOG_ERROR("Client config not found for type: %d", static_cast<int>(clientType));
    return nullptr;
}

ClientType ConfigManager::DetectClientTypeFromConfig(const std::string& processName) {
    if (!m_configLoaded) {
        LOG_WARN("Config not loaded, using default detection");
        return ClientType::UNKNOWN;
    }
    
    // Extract filename from full path
    size_t lastSlash = processName.find_last_of("\\/");
    std::string fileName = processName.substr(lastSlash + 1);
    
    LOG_INFO("Detected process: %s", fileName.c_str());
    
    for (const auto& [clientType, config] : m_clientConfigs) {
        if (fileName == config.executable) {
            const char* typeStr = (clientType == ClientType::STANDALONE) ? "STANDALONE" : 
                                (clientType == ClientType::STEAM) ? "STEAM" : "UNKNOWN";
            LOG_INFO("Client Type: %s", typeStr);
            return clientType;
        }
    }
    
    LOG_WARN("Unknown client type: %s, using default", fileName.c_str());
    return m_defaultClient;
}

uintptr_t ConfigManager::ParseHexString(const std::string& hexStr) {
    uintptr_t result = 0;
    try {
        if (hexStr.length() > 2 && hexStr.substr(0, 2) == "0x") {
            result = std::stoull(hexStr, nullptr, 16);
        } else {
            result = std::stoull(hexStr, nullptr, 10);
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to parse hex string: %s - %s", hexStr.c_str(), e.what());
    }
    return result;
}

void ConfigManager::InitializeLogger() {
    if (!m_configLoaded) {
        return;
    }
    
    try {
        std::ifstream configFile("config/offsets.json");
        if (!configFile.is_open()) {
            return;
        }
        
        Json::Value root;
        Json::CharReaderBuilder builder;
        std::string errors;
        
        if (!Json::parseFromStream(builder, configFile, &root, &errors)) {
            return;
        }
        
        Logger& logger = Logger::GetInstance();
        
        // Parse logging configuration
        if (root.isMember("logging")) {
            const Json::Value& logging = root["logging"];
            
            // Set log level
            if (logging.isMember("level")) {
                std::string levelStr = logging["level"].asString();
                std::transform(levelStr.begin(), levelStr.end(), levelStr.begin(), ::toupper);
                
                if (levelStr == "DEBUG") {
                    logger.SetLogLevel(LogLevel::DEBUG);
                } else if (levelStr == "INFO") {
                    logger.SetLogLevel(LogLevel::INFO);
                } else if (levelStr == "WARN") {
                    logger.SetLogLevel(LogLevel::WARN);
                } else if (levelStr == "ERROR") {
                    logger.SetLogLevel(LogLevel::ERROR);
                } else if (levelStr == "FATAL") {
                    logger.SetLogLevel(LogLevel::FATAL);
                }
            }
            
            // Set console output
            if (logging.isMember("console_output")) {
                logger.EnableConsoleOutput(logging["console_output"].asBool());
            }
            
            // Set file output and log file
            if (logging.isMember("file_output")) {
                bool fileOutput = logging["file_output"].asBool();
                logger.EnableFileOutput(fileOutput);
                
                if (fileOutput && logging.isMember("log_file")) {
                    std::string logFile = logging["log_file"].asString();
                    
                    // Create logs directory if it doesn't exist
                    std::filesystem::path logPath(logFile);
                    if (logPath.has_parent_path()) {
                        std::filesystem::create_directories(logPath.parent_path());
                    }
                    
                    logger.SetLogFile(logFile);
                }
            }
        }
        
    } catch (const std::exception& e) {
        // Fallback to console logging if config parsing fails
        Logger& logger = Logger::GetInstance();
        logger.SetLogLevel(LogLevel::INFO);
        logger.EnableConsoleOutput(true);
        logger.EnableFileOutput(false);
    }
}