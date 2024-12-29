#include <common.h>

void DECOMP_GhostTape_WriteBoosts(int addReserve,u_char type,int speedCap)
{
  char *puVar1;

  // quit, if ghost cant be saved
  if (sdata->boolCanSaveGhost == 0) return;
  
  puVar1 = sdata->GhostRecording.ptrCurrOffset;

  if ((type & TURBO_PAD) != 0) 
  {
    if (sdata->GhostRecording.boostCooldown1E != 0) {
      return;
    }
    sdata->GhostRecording.boostCooldown1E = 0x1e;
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
  
  sdata->GhostRecording.ptrCurrOffset += 6;
}