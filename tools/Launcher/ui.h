#pragma once

#include <string>
#include <vector>
#include "updater.h"

class UI
{
public:
	UI();
	void Render(int width, int height);

private:
	bool SelectFile(std::string& str, const std::string& label, const std::vector<std::string>& ext, const std::vector<std::string>& filters, const std::string& tip);
	bool SelectFolder(std::string& str, const std::string& label, const std::string& tip);

private:
	Updater m_updater;
	std::string m_version = "None";
	std::string m_gamePath;
	std::string m_duckPath;
	std::string m_iniPath;
	std::string m_username;
	std::string m_status;
};