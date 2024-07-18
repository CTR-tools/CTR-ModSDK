#include "ui.h"
#include "dataManager.h"
#include "IconsFontAwesome6.h"

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
  m_updater.CheckForUpdates(m_status, m_version);
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

  ImGui::BeginDisabled(m_updater.IsBusy() || !m_updater.IsUpdated());
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
  ImGui::BeginDisabled(m_updater.IsBusy() || !updateReady);
  if (ImGui::Button("Update")) { m_updater.Update(m_status, m_version, m_gamePath, m_iniPath); }
  ImGui::EndDisabled();

  if (!m_status.empty()) { ImGui::Text(m_status.c_str()); }

  ImGui::End();
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
