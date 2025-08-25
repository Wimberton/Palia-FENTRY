#include "LocalizationManager.h"
#include "Configuration.h"
#include "console.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <set>
#include <Windows.h>

// Include embedded translation data
#include "en.h"
#include "es.h"
#include "pt.h"
#include "zh.h"

namespace fs = std::filesystem;

// Language files directory - following same pattern as Configuration
static const std::string languageDirectory = "C:\\ProgramData\\OriginPalia\\languages";

// Helper function to ensure directory exists (copied from Configuration pattern)
static void EnsureLanguageDirectoryExists() {
    fs::path dir(languageDirectory);
    if (!fs::exists(dir)) {
        fs::create_directories(dir);
        LOG("Created language directory: %s", languageDirectory.c_str());
    }
}

Language LocalizationManager::currentLanguage = Language::English;
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> LocalizationManager::localizedStrings;
bool LocalizationManager::isInitialized = false;

void LocalizationManager::Initialize() {
    if (isInitialized) return;
    
    LOG("LocalizationManager: Initializing...");
    
    // Ensure language files are deployed to ProgramData (following Configuration pattern)
    EnsureLanguageFilesDeployed();
    
    // Load language preference first
    LoadLanguagePreference();
    
    LOG("LocalizationManager: Current language set to: %d", static_cast<int>(currentLanguage));
    
    // Always load English first as the base/fallback language
    LOG("LocalizationManager: Loading English as base language...");
    LoadLanguageFile(Language::English);
    
    // Then load the selected language (if different) to overlay/override English
    if (currentLanguage != Language::English) {
        LOG("LocalizationManager: Loading selected language overlay...");
        LoadLanguageFile(currentLanguage);
    }
    
    // Verify we have some translations loaded
    std::string enLangKey = GetLanguageFileName(Language::English);
    int englishKeyCount = localizedStrings[enLangKey].size();
    
    if (englishKeyCount == 0) {
        LOG("LocalizationManager: WARNING - No English translations loaded! Translation files may be missing.");
        LOG("LocalizationManager: Please ensure en.txt exists in one of the search paths.");
    } else {
        LOG("LocalizationManager: Successfully loaded %d English translations as base.", englishKeyCount);
    }
    
    isInitialized = true;
    LOG("LocalizationManager: Initialization complete.");
}

void LocalizationManager::SetLanguage(Language lang) {
    if (currentLanguage == lang) return;
    
    currentLanguage = lang;
    Configuration::cfg_SelectedLanguage = static_cast<int>(lang);
    
    LOG("SetLanguage: Switching to language %d", static_cast<int>(lang));
    
    // Always ensure English is loaded as base (don't reload if already current)
    if (lang != Language::English) {
        LoadLanguageFile(Language::English);
    }
    
    // Load the selected language (will overlay English if different)
    LoadLanguageFile(lang);
    
    Configuration::Save();
}

Language LocalizationManager::GetCurrentLanguage() {
    return currentLanguage;
}

std::string LocalizationManager::GetText(const std::string& key) {
    if (!isInitialized) {
        Initialize();
    }
    
    std::string langKey = GetLanguageFileName(currentLanguage);
    
    auto langIt = localizedStrings.find(langKey);
    if (langIt != localizedStrings.end()) {
        auto textIt = langIt->second.find(key);
        if (textIt != langIt->second.end()) {
            return textIt->second;
        }
    }
    
    // Fallback to English if current language doesn't have the key
    if (currentLanguage != Language::English) {
        langKey = GetLanguageFileName(Language::English);
        auto langIt = localizedStrings.find(langKey);
        if (langIt != localizedStrings.end()) {
            auto textIt = langIt->second.find(key);
            if (textIt != langIt->second.end()) {
                return textIt->second;
            }
        }
    }
    
    // Debug output for missing keys (only first few times to avoid spam)
    static std::set<std::string> reportedKeys;
    if (reportedKeys.find(key) == reportedKeys.end() && reportedKeys.size() < 10) {
        LOG("LocalizationManager: Missing translation for key: %s", key.c_str());
        
        std::string langInfo = "LocalizationManager: Available languages: ";
        for (const auto& lang : localizedStrings) {
            langInfo += lang.first + "(" + std::to_string(lang.second.size()) + " keys) ";
        }
        LOG("%s", langInfo.c_str());
        
        reportedKeys.insert(key);
    }
    
    // Return the key itself if no translation found
    return key;
}

std::string LocalizationManager::GetText(const std::string& key, const std::string& defaultText) {
    std::string result = GetText(key);
    return (result == key) ? defaultText : result;
}

std::string LocalizationManager::GetLanguageDisplayName(Language lang) {
    switch (lang) {
        case Language::English: return "English";
        case Language::Spanish: return "Español";
        case Language::Portuguese: return "Português";
        case Language::Chinese: return "中文";
        default: return "Unknown";
    }
}

std::vector<Language> LocalizationManager::GetAvailableLanguages() {
    return { Language::English, Language::Spanish, Language::Portuguese, Language::Chinese };
}

std::string LocalizationManager::GetLanguageFileName(Language lang) {
    switch (lang) {
        case Language::English: return "en";
        case Language::Spanish: return "es";
        case Language::Portuguese: return "pt";
        case Language::Chinese: return "zh";
        default: return "en";
    }
}

std::string GetDLLDirectory() {
    char dllPath[MAX_PATH] = {0}; // Initialize to zero
    HMODULE hModule = NULL;
    
    // Get handle to current DLL
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
                         GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                         (LPCSTR)&GetDLLDirectory, &hModule) && hModule) {
        
        DWORD pathLen = GetModuleFileNameA(hModule, dllPath, MAX_PATH - 1);
        if (pathLen > 0 && pathLen < MAX_PATH) {
            dllPath[pathLen] = '\0'; // Ensure null termination
            
            // Get directory of DLL
            std::string dllDir(dllPath);
            size_t lastSlash = dllDir.find_last_of("\\/");
            if (lastSlash != std::string::npos) {
                dllDir = dllDir.substr(0, lastSlash + 1);
            }
            
            LOG("GetDLLDirectory: Found DLL directory: %s", dllDir.c_str());
            return dllDir;
        }
    }
    
    LOG("GetDLLDirectory: Failed to get DLL directory");
    return "";
}

void LocalizationManager::LoadLanguageFile(Language lang) {
    std::string langKey = GetLanguageFileName(lang);
    
    // Language files are always in ProgramData (created from embedded content)
    std::string programDataPath = languageDirectory + "\\" + langKey + ".txt";
    
    std::ifstream file(programDataPath);
    if (!file.is_open()) {
        LOG("Could not open language file: %s", programDataPath.c_str());
        LOG("This should not happen as embedded content creates this file during deployment");
        return;
    }
    
    std::string fileName = programDataPath;
    
    LOG("Loading language file: %s", fileName.c_str());
    
    // Clear existing strings for this language to start fresh
    localizedStrings[langKey].clear();
    
    std::string line;
    int lineNumber = 0;
    int loadedKeys = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;
        
        // Find the separator
        size_t separatorPos = line.find('=');
        if (separatorPos == std::string::npos) {
            if (!line.empty()) {
                LOG("LoadLanguageFile: Skipping line %d (no separator): %s", lineNumber, line.c_str());
            }
            continue;
        }
        
        std::string key = line.substr(0, separatorPos);
        std::string value = line.substr(separatorPos + 1);
        
        // Trim whitespace
        key.erase(0, key.find_first_not_of(" \t\r\n"));
        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);
        
        if (!key.empty()) {
            localizedStrings[langKey][key] = value;
            loadedKeys++;
            
            // Debug output for first few keys
            if (loadedKeys <= 5) {
                LOG("LoadLanguageFile: Loaded key %d: '%s' = '%s'", loadedKeys, key.c_str(), value.c_str());
            }
        }
    }
    
    LOG("LoadLanguageFile: Successfully loaded %d keys from %s", loadedKeys, fileName.c_str());
    file.close();
}

void LocalizationManager::LoadDefaultStrings() {
    // No hardcoded defaults - all translations must come from external files
    LOG("LoadDefaultStrings: No hardcoded defaults - relying on external language files");
}

void LocalizationManager::SaveLanguagePreference() {
    // Integrated with the existing Configuration system
    // This is called from SetLanguage, and Configuration::Save() is called automatically
    // when configuration changes
}

void LocalizationManager::LoadLanguagePreference() {
    // Load from the existing Configuration system
    // Ensure the value is valid (0 = English, 1 = Spanish, 2 = Portuguese, 3 = Chinese)
    int langValue = Configuration::cfg_SelectedLanguage;
    if (langValue < 0 || langValue >= 4) {
        langValue = 0; // Default to English if invalid
        Configuration::cfg_SelectedLanguage = 0;
        LOG("LoadLanguagePreference: Invalid language value %d, defaulting to English", langValue);
    }
    currentLanguage = static_cast<Language>(langValue);
    
    std::string languageName = GetLanguageDisplayName(currentLanguage);
    LOG("LoadLanguagePreference: Loaded language preference: %d (%s)", 
        langValue, languageName.c_str());
}



void LocalizationManager::EnsureLanguageFilesDeployed() {
    // Ensure ProgramData directory exists (following Configuration pattern)
    EnsureLanguageDirectoryExists();
    
    // Create language files in ProgramData if they don't exist (like Configuration creates JSON)
    std::vector<std::pair<Language, const char*>> languageData = {
        { Language::English, EmbeddedTranslations::ENGLISH_CONTENT },
        { Language::Spanish, EmbeddedTranslations::SPANISH_CONTENT },
        { Language::Portuguese, EmbeddedTranslations::PORTUGUESE_CONTENT },
        { Language::Chinese, EmbeddedTranslations::CHINESE_CONTENT }
    };
    
    for (const auto& [lang, content] : languageData) {
        std::string langKey = GetLanguageFileName(lang);
        std::string programDataPath = languageDirectory + "\\" + langKey + ".txt";
        
        // Always create/replace the file with latest embedded content (ensuring users get updates)
        std::ofstream file(programDataPath);
        if (file.is_open()) {
            file << content;
            file.close();
            if (fs::exists(programDataPath)) {
                LOG("EnsureLanguageFilesDeployed: Updated %s in ProgramData with latest embedded content", langKey.c_str());
            } else {
                LOG("EnsureLanguageFilesDeployed: Created %s in ProgramData with embedded content", langKey.c_str());
            }
        } else {
            LOG("EnsureLanguageFilesDeployed: Failed to write %s to ProgramData", langKey.c_str());
        }
    }
}