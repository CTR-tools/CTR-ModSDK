#pragma once

#include <vector>
#include <string>

namespace IO
{
	void ReadBinaryFile(std::vector<char>& v, const std::string& path);
	void WriteBinaryFile(const std::vector<char>& v, const std::string& path);
	bool DecompressFiles(const std::string& path, const std::string& filename);
}