#include "ui.h"
#include "dataManager.h"
#include "IconsFontAwesome6.h"

#include <misc/cpp/imgui_stdlib.h>
#include <portable-file-dialogs.h>
#include <filesystem>
#include <cstdlib>

UI::UI()
{
  g_dataManager.BindData(&m_biosPath, DataType::STRING, "BiosPath");
  g_dataManager.BindData(&m_gamePath, DataType::STRING, "GamePath");
  g_dataManager.BindData(&m_version, DataType::STRING, "GameVersion");
  g_dataManager.BindData(&m_username, DataType::STRING, "Username");
  m_updater.CheckForUpdates(m_status, m_version);
}

static int FilterUsernameChar(ImGuiInputTextCallbackData* data)
{
  if (data->EventChar >= 'a' && data->EventChar <= 'z') { return 0; }
  if (data->EventChar >= 'A' && data->EventChar <= 'Z') { return 0; }
  if (data->EventChar >= '0' && data->EventChar <= '9') { return 0; }
  return 1;
}

void UI::Render(int width, int height)
{
  ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)), ImGuiCond_Always);
  ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

  std::string icon = m_username.empty() ? ICON_FA_CIRCLE_XMARK : ICON_FA_CIRCLE_CHECK;
  ImGui::InputText(("Username  " + icon).c_str(), &m_username, ImGuiInputTextFlags_CallbackCharFilter, FilterUsernameChar);
  if (m_username.size() > 9) { m_username = m_username.substr(0, 9); }

  static bool readBios = true;
  bool updateReady = true;
  updateReady &= SelectFile(m_biosPath, "Bios Path   ", {".bin"}, {"PSX Bios File", "*.bin"}, "Path to a PS1 NTSC-U bios.");
  if (updateReady)
  {
    if (readBios)
    {
      if (m_updater.IsValidBios(m_biosPath)) { readBios = false; }
      else { updateReady = false; }
    }
  }
  else { readBios = true; }
  updateReady &= SelectFile(m_gamePath, "Game Path", {".bin", ".img", ".iso"}, {"Game Files", "*.bin *.img *.iso"}, "Path to the clean NTSC-U version of CTR");
  ImGui::Text(("Version: " + m_version).c_str());

  ImGui::BeginDisabled(m_updater.IsBusy() || !m_updater.IsUpdated());
  if (ImGui::Button("Launch Game"))
  {
    const std::string s_clientPath = GetClientPath(m_version);
    const std::string s_patchedPath = GetPatchedGamePath(m_version);
    if (!std::filesystem::exists(s_clientPath)) { m_status = "Error: could not find " + s_clientPath; }
    else if (!std::filesystem::exists(s_patchedPath)) { m_status = "Error: could not find " + s_patchedPath; }
    else
    {
      g_dataManager.SaveData();
      const std::string clientCommand = "start /b \"\" \"" + std::filesystem::current_path().string() + "/" + GetClientPath(m_version) + "\" " + m_username + " &";
      std::system(clientCommand.c_str());
      const std::string duckCommand = "start /b \"\" \"" + g_duckExecutable + "\" \"" + s_patchedPath + "\" &";
      std::system(duckCommand.c_str());
    }
  }
  ImGui::EndDisabled();
  ImGui::SameLine();
  ImGui::BeginDisabled(m_updater.IsBusy() || !updateReady);
  if (ImGui::Button("Update")) { m_updater.Update(m_status, m_version, m_gamePath, m_biosPath); }
  ImGui::EndDisabled();

  if (!m_status.empty()) { ImGui::Text(m_status.c_str()); }

  ImGui::End();
}

bool UI::SelectFile(std::string& str, const std::string& label, const std::vector<std::string>& ext, const std::vector<std::string>& filters, const std::string& tip)
{

  std::string lowercaseStr;
  for (char c : str)
  {
    if (c <= 'Z' && c >= 'A') { c = c - ('Z' - 'z'); };
    lowercaseStr += c;
  }

  auto checkValidPath = [&]
    {
      if (std::filesystem::exists(str))
      {
        for (const std::string& s : ext)
        {
          if (lowercaseStr.ends_with(s)) { return true; }
        }
      }
    };
  std::string icon = checkValidPath() ? ICON_FA_CIRCLE_CHECK : ICON_FA_CIRCLE_XMARK;
  ImGui::InputText((label + " " + icon).c_str(), &str);
  if (!tip.empty()) { ImGui::SetItemTooltip(tip.c_str()); }
  ImGui::SameLine();
  if (ImGui::Button(("...##" + label).c_str()))
  {
    auto selection = pfd::open_file(label, str, filters).result();
    if (selection.empty()) { return false; }
    str = selection.front();
  }
  return checkValidPath();
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
