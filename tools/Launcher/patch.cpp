#include "patch.h"
#include "dataManager.h"
#include "io.h"

#include <xdelta3.h>
#include <zip.h>

static bool DecompressFile(const std::string& path, const std::string& filename, const std::string& ext)
{
  int err;
  zip_t* zipArchive = zip_open(path.c_str(), 0, &err);
  if (!zipArchive) { return false; }

  zip_stat_t zipStat;
  zip_stat_init(&zipStat);
  zip_stat(zipArchive, filename.c_str(), 0, &zipStat);
  std::vector<char> decompressedFile;
  decompressedFile.resize(zipStat.size);
  zip_file* file = zip_fopen(zipArchive, filename.c_str(), 0);
  zip_fread(file, decompressedFile.data(), zipStat.size);
  zip_fclose(file);
  zip_close(zipArchive);

  std::string newFilePath = path.substr(0, path.find(".")) + ext;
  IO::WriteBinaryFile(decompressedFile, newFilePath);
}

static bool DecompressXDelta(const std::string& xdeltaPath, const std::string& inputPath, const std::string& ext)
{
  std::vector<char> xdelta;
  std::vector<char> game;
  IO::ReadBinaryFile(xdelta, xdeltaPath);
  IO::ReadBinaryFile(game, inputPath);
  std::vector<char> patchedGame;
  patchedGame.resize(2 * game.size());
  usize_t patchedGameSize;
  int result = xd3_decode_memory(reinterpret_cast<uint8_t*>(xdelta.data()), xdelta.size(), reinterpret_cast<uint8_t*>(game.data()), game.size(), reinterpret_cast<uint8_t*>(patchedGame.data()), &patchedGameSize, patchedGame.size(), 1 << 11);
  if (result != 0) { return false; }

  patchedGame.resize(patchedGameSize);
  std::string filename = xdeltaPath.substr(0, xdeltaPath.find(".")) + ext;
  IO::WriteBinaryFile(patchedGame, filename);
  return true;
}

bool Patch::NewVersion(const std::string& path, const std::string& gamePath)
{
  return DecompressFile(path + g_clientString, g_clientExecutable, ".exe") && DecompressXDelta(path + g_patchString, gamePath, ".bin");
}
