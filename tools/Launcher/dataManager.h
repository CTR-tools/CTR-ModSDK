#pragma once

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <tuple>
#include <string>

extern const std::string g_dataFolder;
extern const std::string g_duckFolder;
extern const std::string g_duckExecutable;
extern const std::string g_clientString;
extern const std::string g_clientExecutable;
extern const std::string g_patchString;
extern const std::string g_configString;

const std::string GetClientPath(const std::string& version);
const std::string GetPatchedGamePath(const std::string& version);
const std::string GetIniPath_Version(const std::string& version);
const std::string GetIniPath_Duck();

using json = nlohmann::json;

enum class DataType
{
	STRING, BOOL,
};

class DataManager
{
public:
	DataManager();
	void BindData(void* data, DataType dataType, const std::string& id);
	void SaveData();

private:
	const std::string m_path = g_dataFolder + "config.json";
	std::unordered_map<std::string, std::tuple<void*, DataType>> m_dataMap;
	json m_json;
};

extern DataManager g_dataManager;