#include "dataManager.h"

#include <fstream>
#include <filesystem>

const std::string g_dataFolder = "data/";
const std::string g_duckFolder = g_dataFolder + "duckstation/";
const std::string g_duckExecutable = g_duckFolder + "duckstation-qt-x64-ReleaseLTCG.exe";
const std::string g_clientString = "client.zip";
const std::string g_clientExecutable = "Client.exe";
const std::string g_patchString = "ctr-u_Online30.xdelta";
const std::string g_configString = "SCUS-94426.ini";

const std::string GetClientPath(const std::string& version)
{
	return g_dataFolder + version + "/" + g_clientExecutable;
}

const std::string GetPatchedGamePath(const std::string& version)
{
	std::string s_patch = g_dataFolder + version + "/" + g_patchString;
	return s_patch.substr(0, s_patch.find(".")) + ".bin";
}

const std::string GetIniPath_Version(const std::string& version)
{
	return g_dataFolder + version + "/" + g_configString;
}

const std::string GetIniPath_Duck()
{
	return g_duckFolder + "settings.ini";
}

DataManager g_dataManager;

DataManager::DataManager()
{
	if (!std::filesystem::is_directory(g_dataFolder)) { std::filesystem::create_directory(g_dataFolder); }
	if (std::filesystem::exists(m_path)) { m_json = json::parse(std::ifstream(m_path)); }
}

void DataManager::BindData(void* data, DataType dataType, const std::string& id)
{
	if (m_json.contains(id))
	{
		switch (dataType)
		{
		case DataType::STRING:
			*static_cast<std::string*>(data) = m_json[id];
			break;
		case DataType::BOOL:
			*static_cast<bool*>(data) = m_json[id];
			break;
		}
	}
	m_dataMap[id] = {data, dataType};
}

void DataManager::SaveData()
{
	for (const auto&[key, value] : m_dataMap)
	{
		void* pData = std::get<void*>(value);
		switch (std::get<DataType>(value))
		{
		case DataType::STRING:
			m_json[key] = *(static_cast<std::string*>(pData));
			break;
		case DataType::BOOL:
			m_json[key] = *(static_cast<bool*>(pData));
			break;
		}
	}
	std::ofstream file(m_path);
	file << std::setw(4) << m_json << std::endl;
}
