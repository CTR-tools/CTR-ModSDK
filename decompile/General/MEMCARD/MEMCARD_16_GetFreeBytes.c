#include <common.h>

// === This is bugged ===
// People reported "Out of room" error screens
// even though the memory card was not full

void DECOMP_MEMCARD_GetFreeBytes(int slotIdx)
{
  struct DIRENTRY *firstEntry;
  struct DIRENTRY entry;

  MEMCARD_StringSet(sdata->s_bu00_BASCUS_94426_slots, slotIdx, sdata->s_AnyFile);

  int bytesUsedMemCard = 0;

  // string for directory and file of save that is in use
  firstEntry = firstfile(sdata->s_bu00_BASCUS_94426_slots, &entry);

  for (struct DIRENTRY *nxtEntry = &entry; firstEntry == nxtEntry; nxtEntry = nextfile(&entry))
  {
    bytesUsedMemCard = bytesUsedMemCard + (entry.size + 0x1fffU & 0xffffe000);
  }

  sdata->memoryCard_SizeRemaining = 0x1e000 - bytesUsedMemCard;

  return;
}