#include <common.h>

void DECOMP_MM_Characters_BackupIDs(void) {
  char i;

  for (i = 0; i < 8; i++) {
    // make a backup of DAT_80086e84 into DAT_8009a980 when you leave character
    // selection, when you return to character selection, DAT_8009a980 is copied
    // back to DAT_80086e84
    data.characterIDs_backup[i] = data.characterIDs[i];
  }
  return;
}