#include "patch.h"
#include "dataManager.h"
#include "io.h"

#include <xdelta3.h>

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

bool Patch::NewVersion(const std::string& path, const std::string& gamePath, std::string& status)
{
  status = "Decompressing " + g_clientExecutable + "...";
  if (!IO::DecompressFiles(path, g_clientString))
  {
    status = "Error decompressing " + g_clientExecutable;
    return false;
  }
  status = "Applying xdelta patch...";
  if (!DecompressXDelta(path + g_patchString, gamePath, ".bin"))
  {
    status = "Error applying xdelta patch";
    return false;
  }
  return true;
}
