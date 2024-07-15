#pragma once

#include <string>

namespace Requests
{
	bool CheckUpdates(std::string& version);
	bool DownloadUpdates(const std::string& version, std::string& status);
}