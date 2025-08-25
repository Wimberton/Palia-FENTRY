/**
 * @file IOManager.cpp
 * @brief IO manager class
 *
 * @author Rambolo.
 * @version 0.0.1
 * @date 01.09.2024
 */

#include "IOManager.h"
#include <filesystem>

// Loading json from file
bool IOManager::LoadJsonFromFile(const std::string& filePath, Json::Value& outJson) {
	std::ifstream fileStream(filePath, std::ifstream::binary);
	if (!fileStream.is_open()) {
		LogError("Failed to open file: " + filePath);
		return false;
	}

	// Check if file is empty
	fileStream.seekg(0, std::ios::end);
	if (fileStream.tellg() == 0) {
		fileStream.close();
		outJson = Json::Value(); // insert empty Json object.
		return true; // An empty file is not considered corrupt
	}
	// Reset the stream to the beginning
	fileStream.seekg(0, std::ios::beg);
	
	try {
		fileStream >> outJson;
		
		// Check if data is valid
		if (fileStream.fail() || outJson.isNull() || outJson.toStyledString().find_first_not_of(" \n\t") == std::string::npos) {
			throw std::runtime_error("JSON data is invalid, empty, or could not be parsed.");
		}
	} catch (const std::exception& e) {
		LogError("Error reading file: '" + filePath + "'. " + std::string(e.what()));
		return false;
	}

	Log("Successfully loaded file: " + std::string(filePath));
	
	return true;
}

// Save json to file
bool IOManager::SaveJsonToFile(const std::string& filePath, const Json::Value& jsonData) {
	// Clean data before saving.
	Json::Value cleanedJsonData = jsonData;
	CleanJsonData(cleanedJsonData);
	
	// Write to temp file first.
	std::string tempFilePath = filePath + ".tmp";
	std::ofstream tempFile(tempFilePath);
	if (!tempFile.is_open()) {
		LogError("Failed to open temporary file for writing: " + tempFilePath);
		return false;
	}

	try {
		tempFile << cleanedJsonData.toStyledString();
	} catch (const std::exception& e) {
		LogError("Error writing JSON to temp file: " + std::string(e.what()));
	}
	tempFile.close();
	
	// Create a backup before replacing the original file
	if (!CreateBackup(filePath, filePath + ".backup")) {
		LogError("Failed to create a backup for file: " + filePath);
		return false;
	}
	
	// Replace original file with temp file
	std::filesystem::rename(tempFilePath, filePath);
	//Log("Successfully saved to file: " + filePath);
	return true;
}

// Function to create backup of a file
bool IOManager::CreateBackup(const std::string& originalFilePath, const std::string& backupFilePath) {
	try {
		if (std::filesystem::exists(originalFilePath)) {
			std::filesystem::copy(originalFilePath, backupFilePath, std::filesystem::copy_options::overwrite_existing);
			//Log("Successfully created backup file: " + backupFilePath);
			return true;
		}
	} catch (const std::exception& e) {
		LogError("Error creating backup: " + std::string(e.what()));
	}
	return false;
}

// Function to restore backup file
bool IOManager::RestoreBackup(const std::string& backupFilePath, const std::string& originalFilePath) {
	if (!std::filesystem::exists(backupFilePath)) {
		LogError("Backup file not present: " + backupFilePath);
		return false;
	}
	
	try {
		std::filesystem::rename(backupFilePath, originalFilePath);
		Log("Original file successfully restored from backup.");
	} catch (const std::exception& e) {
		LogError("Error replacing backup file: " + std::string(e.what()));
		return false;
	}
	return true;
}

// Function to clean json data
void IOManager::CleanJsonData(Json::Value& jsonData) {
	if (jsonData.isObject()) {
		for (const auto& key : jsonData.getMemberNames()) {
			if (jsonData[key].isNull() || key == "Unknown" || jsonData[key].empty()) {
				jsonData.removeMember(key);
			} else {
				// Recursively clean nested objects or arrays.
				CleanJsonData(jsonData[key]);
			}
		}
	} else if (jsonData.isArray()) {
		for (Json::ArrayIndex i = 0; i < jsonData.size(); i++) {
			if (jsonData[i].isNull() || jsonData[i].empty()) {
				jsonData.removeIndex(i, nullptr);
			} else {
				CleanJsonData(jsonData[i]);
			}
		}
	}
}


// Utility functions
void IOManager::Log(const std::string& message) {
	std::cout << message << '\n';
}

void IOManager::LogError(const std::string& message) {
	std::cerr << message << '\n';
}