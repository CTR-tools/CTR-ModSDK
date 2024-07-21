#include "io.h"

#include <filesystem>
#include <fstream>
#include <zip.h>

void IO::ReadBinaryFile(std::vector<char>& v, const std::string& path)
{
  std::ifstream file(path.c_str(), std::ios::binary);
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  v.resize(size);
  file.seekg(0, std::ios::beg);
  file.read(v.data(), size);
  file.close();
}

void IO::WriteBinaryFile(const std::vector<char>& v, const std::string& path)
{
  std::ofstream output(path.c_str(), std::ios::binary);
  output.write(v.data(), v.size());
  output.close();
}

bool IO::DecompressFiles(const std::string& path, const std::string& filename)
{
  int err;
  zip_t* zipArchive = zip_open((path + filename).c_str(), 0, &err);
  if (!zipArchive) { return false; }

  zip_stat_t zipStat;
  for (int i = 0; i < zip_get_num_entries(zipArchive, 0); i++)
  {
    if (zip_stat_index(zipArchive, i, 0, &zipStat) == 0)
    {
      std::string archiveName(zipStat.name);
      if (archiveName.back() == '/' || archiveName.back() == '\\')
      {
        std::filesystem::create_directory(path + archiveName);
      }
      else
      {
        std::vector<char> decompressedFile;
        decompressedFile.resize(zipStat.size);
        zip_file* file = zip_fopen_index(zipArchive, i, 0);
        if (!file) { return false; }
        zip_fread(file, decompressedFile.data(), zipStat.size);
        zip_fclose(file);
        IO::WriteBinaryFile(decompressedFile, path + archiveName);
      }
    }
  }
  zip_close(zipArchive);
  return true;
}
