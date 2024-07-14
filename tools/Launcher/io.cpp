#include "io.h"

#include <fstream>

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
