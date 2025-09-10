#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>
#include "Logger.h"

enum class ClientType {
    STANDALONE,
    STEAM,
    UNKNOWN
};

struct ClientConfig {
    std::string executable;
    std::unordered_map<std::string, uintptr_t> offsets;
};

class ConfigManager {
public:
    static ConfigManager& GetInstance();
    
    bool LoadConfig(const std::string& configPath = "config/offsets.json");
    ClientConfig* GetClientConfig(ClientType clientType);
    ClientType DetectClientTypeFromConfig(const std::string& processName);
    void InitializeLogger();
    
private:
    ConfigManager() = default;
    ~ConfigManager() = default;
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    
    std::unordered_map<ClientType, ClientConfig> m_clientConfigs;
    ClientType m_defaultClient = ClientType::STANDALONE;
    bool m_configLoaded = false;
    
    uintptr_t ParseHexString(const std::string& hexStr);
};