/**
* @file IOManager.h
 * @brief The header file for IO management
 *
 * @author Rambolo.
 * @version 0.0.1
 * @date 01.09.2024
 */
#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <json/json.h>

class IOManager {
public:
	// Constructor/destructor
    IOManager() = default;
    virtual ~IOManager() = default;
	
    // Function to load Json from file
    static bool LoadJsonFromFile(const std::string& filePath, Json::Value& outJson);
	
    // Function to save Json to file
    static bool SaveJsonToFile(const std::string& filePath, const Json::Value& jsonData);
	
    // Function to create backup of file
    static bool CreateBackup(const std::string& originalFilePath, const std::string& backupFilePath);

	// Function to restore original file to backup file state
	static bool RestoreBackup(const std::string& backupFilePath, const std::string& originalFilePath);

	// Function to cleanup any unwanted or potentially harmful data
	static void CleanJsonData(Json::Value& jsonData);
	
protected:
	// General Logging
	static void Log(const std::string& message);
    // Error logging
    static void LogError(const std::string& message);
};

#endif