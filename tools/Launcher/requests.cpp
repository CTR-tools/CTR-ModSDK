#include "requests.h"
#include "dataManager.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <fstream>

static bool DownloadFile(const std::string& sitePath, const std::string& filePath)
{
  httplib::SSLClient request("www.online-ctr.com");
  httplib::Result response = request.Get("/wp-content/uploads/onlinectr_patches/" + sitePath);
  if (response && response->status == 200) {
    std::ofstream file(filePath.c_str(), std::ios::binary);
    file.write(response->body.c_str(), response->body.size());
    file.close();
    return true;
  }
  return false;
}

bool Requests::CheckUpdates(std::string& version)
{
	httplib::SSLClient request("www.online-ctr.com");
	httplib::Result response = request.Get("/wp-content/uploads/onlinectr_patches/build.txt");
  if (response && response->status == 200) {
    version = response->body;
    return true;
  }
  return false;
}

bool Requests::DownloadUpdates(const std::string& path)
{
  const std::vector<std::string> files = { g_clientString, g_patchString, g_configString };
  if (!std::filesystem::is_directory(path)) { std::filesystem::create_directory(path); }
  for (const std::string& file : files)
  {
    if (!DownloadFile(file, path + file)) { return false; }
  }
  return true;
}
