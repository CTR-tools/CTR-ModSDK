#include "updater.h"
#include "requests.h"
#include "dataManager.h"
#include "patch.h"
#include "io.h"

#include <fstream>
#include <filesystem>

Updater::Updater()
{
  g_dataManager.BindData(&m_updated, DataType::BOOL, "Updated");
  g_dataManager.BindData(&m_hasDuckstation, DataType::BOOL, "Duck");
}

bool Updater::IsUpdated()
{
  return m_updated;
}

bool Updater::IsBusy()
{
	return m_routineRunning;
}

bool Updater::IsValidBios(const std::string& path)
{
  std::vector<char> v;
  IO::ReadBinaryFile(v, path);
  return v.size() == static_cast<size_t>(0x100000);
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

bool Updater::Update(std::string& status, std::string& currVersion, const std::string& gamePath, const std::string& biosPath)
{
  return StartRoutine([&]
    {
      std::string version;
      bool copyIni = false;
      if (!m_hasDuckstation)
      {
        status = "Downloading Duckstation...";
        std::filesystem::create_directory(g_duckFolder);
        const std::string duckArchive = "duckstation.zip";
        if (!Requests::DownloadFile("github.com", "/stenzek/duckstation/releases/download/latest/duckstation-windows-x64-release.zip", g_duckFolder + duckArchive))
        {
          status = "Error: could not download Duckstation.";
          return false;
        }
        status = "Decompressing Duckstation...";
        if (!IO::DecompressFiles(g_duckFolder, duckArchive))
        {
          status = "Error: could not decompress Duckstation.";
          return false;
        }
        status = "Installing custom settings...";
        const std::string g_biosFolder = g_duckFolder + "bios/";
        std::filesystem::create_directory(g_biosFolder);
        std::string biosName;
        for (int i = static_cast<int>(biosPath.size()) - 1; i >= 0; i--)
        {
          if (biosPath[i] == '/' || biosPath[i] == '\\')
          {
            biosName = biosPath.substr(i + 1);
            break;
          }
        }
        std::filesystem::copy_file(biosPath, g_biosFolder + biosName);
        const std::string duckPortable = g_duckFolder + "portable.txt";
        std::ofstream portableFile(duckPortable.c_str());
        portableFile.close();
        m_hasDuckstation = true;
        copyIni = true;
      }
      status = "Checking for new updates...";
      if (m_updateAvailable || Requests::CheckUpdates(version))
      {
        if (m_updateAvailable || version != currVersion)
        {
          m_versionAvailable = m_updateAvailable ? m_versionAvailable : version;
          std::string path = g_dataFolder + m_versionAvailable + "/";
          if (Requests::DownloadUpdates(path, status) && Patch::NewVersion(path, gamePath, status))
          {
            if (copyIni) { std::filesystem::copy_file(GetIniPath_Version(m_versionAvailable), GetIniPath_Duck()); }
            m_updated = true;
            m_updateAvailable = false;
            currVersion = m_versionAvailable;
            status = "Update completed.";
            return true;
          }
        }
        else { status = "Already on the latest patch"; }
      }
      else { status = "Error: could not establish connection"; }
      return false;
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
