#include "updater.h"
#include "requests.h"
#include "dataManager.h"
#include "patch.h"

#include <filesystem>

Updater::Updater()
{
  g_dataManager.BindData(&m_updated, DataType::BOOL, "Updated");
}

bool Updater::IsUpdated()
{
  return m_updated;
}

bool Updater::IsBusy()
{
	return m_routineRunning;
}

bool Updater::CheckForUpdates(std::string& status, const std::string& currVersion)
{
  return StartRoutine([&]
    {
      std::string version;
      Requests::CheckUpdates(version);
      if (currVersion != version)
      {
        m_updateAvailable = true;
        m_versionAvailable = version;
        status = "Update available! v" + m_versionAvailable;
      }
    }
  );
}

bool Updater::Update(std::string& status, std::string& currVersion, const std::string& gamePath, const std::string& iniPath)
{
  return StartRoutine([&]
    {
      std::string version;
      status = "Checking for new updates...";
      if (m_updateAvailable || Requests::CheckUpdates(version))
      {
        if (m_updateAvailable || version != currVersion)
        {
          m_versionAvailable = m_updateAvailable ? m_versionAvailable : version;
          std::string path = g_dataFolder + m_versionAvailable + "/";
          if (Requests::DownloadUpdates(path, status) && Patch::NewVersion(path, gamePath, status))
          {
            std::string s_ini;
            if (iniPath.back() == '/' || iniPath.back() == '\\') { s_ini = iniPath + g_configString; }
            else { s_ini = iniPath + "/" + g_configString; }
            if (std::filesystem::exists(s_ini)) { std::filesystem::remove(s_ini); }
            std::filesystem::copy(path + g_configString, s_ini);
            m_updated = true;
            m_updateAvailable = false;
            currVersion = m_versionAvailable;
            status = "Update completed.";
          }
        }
        else { status = "Already on the latest patch"; }
      }
      else { status = "Error: could not establish connection"; }
    }
  );
}

bool Updater::StartRoutine(const std::function<void(void)>& func)
{
  if (m_routineRunning) { return false; }

  m_routine = func;
  m_routineRunning = true;
  m_updateRoutine = std::async(std::launch::async, [&] { m_routine(); m_routineRunning = false; });
  return true;
}
