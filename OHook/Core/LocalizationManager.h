#pragma once

#include <string>
#include <unordered_map>
#include <vector>

enum class Language {
    English = 0,
    Spanish = 1,
    Portuguese = 2,
    Chinese = 3
};

class LocalizationManager {
private:
    static Language currentLanguage;
    static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> localizedStrings;
    static bool isInitialized;
    
    static void LoadLanguageFile(Language lang);
    static std::string GetLanguageFileName(Language lang);
    static void LoadDefaultStrings();

public:
    static void Initialize();
    static void SetLanguage(Language lang);
    static Language GetCurrentLanguage();
    static std::string GetText(const std::string& key);
    static std::string GetText(const std::string& key, const std::string& defaultText);
    
    // Helper function to get language display names
    static std::string GetLanguageDisplayName(Language lang);
    static std::vector<Language> GetAvailableLanguages();
    
    // Save/Load language preference
    static void SaveLanguagePreference();
    static void LoadLanguagePreference();
    
    // Deployment helper (following Configuration pattern)
    static void EnsureLanguageFilesDeployed();
};

// Convenience macro for localization
#define LOC(key) LocalizationManager::GetText(key)
#define LOC_DEFAULT(key, defaultText) LocalizationManager::GetText(key, defaultText)