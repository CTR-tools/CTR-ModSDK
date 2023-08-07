#include <common.h>

// param1 - reserves to add
// param2 - add type (increment or set)
// param3 - speed cap
void GhostBuffer_RecordBoosts(int addReserve,char type,int speedCap)
{
  char *puVar1;

  puVar1 = sdata->GhostRecording.ptrCurrOffset;

  // if you can save ghost
  if (sdata->boolCanSaveGhost != 0)
  {
    if ((type & 4) != 0) {
      if (sdata->framesSinceLastGhostWritting1E != 0) {
        return;
      }
      sdata->framesSinceLastGhostWritting1E = 0x1e;
    }

	// 0x82-style chunks are 6 bytes long (including 0x82)

	// Write to recording buffer
    puVar1[0] = 0x82;

	// big endian reserve
    puVar1[1] = (char)((u_int)addReserve >> 8);
    puVar1[2] = (char)addReserve;

	// char, add type (increment or set)
    puVar1[3] = type;

	// big endian speedCcap
    puVar1[4] = (char)((u_int)speedCap >> 8);
    puVar1[5] = (char)speedCap;

	// increment recording offset by 5 bytes
	sdata->GhostRecording.ptrCurrOffset = (int)sdata->GhostRecording.ptrCurrOffset + 6;
  }
  return;
}