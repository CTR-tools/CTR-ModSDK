#pragma once

#include <string>
#include <future>

class Updater
{
public:
	Updater();
	bool IsUpdated();
	bool IsBusy();
	bool IsValidBios(const std::string& path);
	bool CheckForUpdates(std::string& status, const std::string& currVersion);
	bool Update(std::string& status, std::string& currVersion, const std::string& gamePath, const std::string& biosPath);

private:
	bool StartRoutine(const std::function<void(void)>& func);

private:
	std::future<void> m_updateRoutine;
	std::function<void(void)> m_routine;
	std::string m_versionAvailable;
	bool m_routineRunning = false;
	bool m_updateAvailable = false;
	bool m_hasDuckstation = false;
	bool m_updated;
};