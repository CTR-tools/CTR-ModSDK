#include "ui.h"
#include "dataManager.h"
#include "IconsFontAwesome6.h"
#include "requests.h"
#include "patch.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <portable-file-dialogs.h>
#include <filesystem>
#include <cstdlib>

UI::UI()
{
  g_dataManager.BindData(&m_gamePath, DataType::STRING, "GamePath");
  g_dataManager.BindData(&m_duckPath, DataType::STRING, "DuckPath");
  g_dataManager.BindData(&m_version, DataType::STRING, "GameVersion");
  g_dataManager.BindData(&m_iniPath, DataType::STRING, "IniPath");
  g_dataManager.BindData(&m_username, DataType::STRING, "Username");
  g_dataManager.BindData(&m_updated, DataType::BOOL, "Updated");
  m_routineRunning = true;
  m_updateRoutine = std::async(std::launch::async, [&] {
    std::string version;
    Requests::CheckUpdates(version);
    if (m_version != version)
    {
      m_updateAvailable = true;
      m_status = "Update available! v" + version;
    }
  });
}

void UI::Render(int width, int height)
{
  ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)), ImGuiCond_Always);
  ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

  std::string icon = m_username.empty() ? ICON_FA_CIRCLE_XMARK : ICON_FA_CIRCLE_CHECK;
  ImGui::InputText(("Username  " + icon).c_str(), &m_username);
  ImGui::SetItemTooltip("Special characters:\n* = Cross Button\n< = Left Arrow\n@ = Circle\n[ = Square\n^ = Triangle\n& = Space");
  if (m_username.size() > 9) { m_username = m_username.substr(0, 9); }

  bool updateReady = true;
  updateReady &= SelectFile(m_gamePath, "Game Path", {".bin", ".img", ".iso"}, {"Game Files", "*.bin *.img *.iso"}, "Path to the clean NTSC-U version of CTR");
  updateReady &= SelectFile(m_duckPath, "Duck Path ", {".exe"}, {"Executable Files", "*.exe"}, "Path to the duckstation executable");
  updateReady &= SelectFolder(m_iniPath, "Ini Path      ", "Duckstation gamesettings folder.\nUsually in Documents/DuckStation/gamesettings");
  ImGui::Text(("Version: " + m_version).c_str());

  ImGui::BeginDisabled(m_routineRunning || !m_updated);
  if (ImGui::Button("Launch Game"))
  {
    std::string s_clientPath = GetClientPath(m_version);
    std::string s_patchedPath = GetPatchedGamePath(m_version);
    if (!std::filesystem::exists(s_clientPath)) { m_status = "Error: could not find " + s_clientPath; }
    else if (!std::filesystem::exists(s_patchedPath)) { m_status = "Error: could not find " + s_patchedPath; }
    else
    {
      g_dataManager.SaveData();
      std::string clientCommand = "start /b \"\" \"" + std::filesystem::current_path().string() + "/" + GetClientPath(m_version) + "\" " + m_username + " &";
      std::system(clientCommand.c_str());
      const std::string duckCommand = "start /b \"\" \"" + m_duckPath + "\" \"" + s_patchedPath + "\" &";
      std::system(duckCommand.c_str());
    }
  }
  ImGui::EndDisabled();
  ImGui::SameLine();
  ImGui::BeginDisabled(m_routineRunning || !updateReady);
  if (ImGui::Button("Update"))
  {
    m_routineRunning = true;
    m_updateRoutine = std::async(std::launch::async, [&] { Update(); });
  }
  ImGui::EndDisabled();

  if (m_routineRunning && m_updateRoutine.wait_for(std::chrono::nanoseconds(1)) == std::future_status::ready)
  {
    m_routineRunning = false;
  }

  if (!m_status.empty()) { ImGui::Text(m_status.c_str()); }

  ImGui::End();
}

void UI::Update()
{
  std::string version;
  m_status = "Checking for new updates...";
  if (m_updateAvailable || Requests::CheckUpdates(version))
  {
    if (m_updateAvailable || version != m_version)
    {
      std::string path = g_dataFolder + version + "/";
      if (Requests::DownloadUpdates(path, m_status))
      {
        if (Patch::NewVersion(path, m_gamePath, m_status))
        {
          std::string s_ini;
          if (m_iniPath.back() == '/' || m_iniPath.back() == '\\') { s_ini = m_iniPath + g_configString; }
          else { s_ini = m_iniPath + "/" + g_configString; }
          if (std::filesystem::exists(s_ini)) { std::filesystem::remove(s_ini); }
          std::filesystem::copy(path + g_configString, s_ini);
          m_updated = true;
          m_version = version;
          m_status = "Update completed.";
        }
      }
    }
    else { m_status = "Already on the latest patch"; }
  }
  else { m_status = "Error: could not establish connection"; }
}

bool UI::SelectFile(std::string& str, const std::string& label, const std::vector<std::string>& ext, const std::vector<std::string>& filters, const std::string& tip)
{

  bool validPath = false;
  for (const std::string& s : ext)
  {
    if (str.ends_with(s) && std::filesystem::exists(str)) { validPath = true; break; }
  }
  std::string icon = validPath ? ICON_FA_CIRCLE_CHECK : ICON_FA_CIRCLE_XMARK;
  ImGui::InputText((label + " " + icon).c_str(), &str);
  if (!tip.empty()) { ImGui::SetItemTooltip(tip.c_str()); }
  ImGui::SameLine();
  if (ImGui::Button(("...##" + label).c_str()))
  {
    auto selection = pfd::open_file(label, str, filters).result();
    if (selection.empty()) { return false; }
    str = selection.front();
  }
  return validPath;
}

bool UI::SelectFolder(std::string& str, const std::string& label, const std::string& tip)
{
  bool validPath = std::filesystem::is_directory(str);
  std::string icon = validPath ? ICON_FA_CIRCLE_CHECK : ICON_FA_CIRCLE_XMARK;
  ImGui::InputText((label + " " + icon).c_str(), &str);
  if (!tip.empty()) { ImGui::SetItemTooltip(tip.c_str()); }
  ImGui::SameLine();
  if (ImGui::Button(("...##" + label).c_str()))
  {
    auto selection = pfd::select_folder(label).result();
    if (selection.empty()) { return false; }
    str = selection;
  }
  return validPath;
}
