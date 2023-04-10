#include <common.h>

// if NOP'd, you can type at 80086e84 while in selection,
// otherwise, 80086e84 will be reset to zero after typing
void DECOMP_MM_Characters_ClearInactivePlayers(void) {
  struct GameTracker *gGT = sdata->gGT;
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  // 8 bytes, backed up character IDs (maybe should've been arrays?)
  int local_8 = OVR_230.characterIDBackup1;
  int local_4 = OVR_230.characterIDBackup2;

  // if number of players is not zero
  if (gGT->numPlyrNextGame) {
    iVar2 = 0;
    for (iVar7 = 0; iVar7 < gGT->numPlyrNextGame; iVar7++) {
      // get character ID
      iVar2 = data.characterIDs[iVar7];
      // if not a secret character
      if (iVar2 < 8) {
        // save -1 (used later in func)
        *(char*)((int)&local_8 + iVar2) = 0xff;
      }
    }
  }

  // if you have more than 1 player
  if (1 < sdata->gGT->numPlyrNextGame) {

    for (iVar7 = 1; iVar7 < gGT->numPlyrNextGame; iVar7++) {

        for (iVar6 = 0; iVar6 < iVar5; iVar6++) {

          if (data.characterIDs[iVar2] == data.characterIDs[iVar6]) {

            iVar2 = 0;

            for (iVar5 = 0; iVar5 < 8; iVar5++) {

              // get value from $sp
              pcVar3 = (char *)((int)&local_8 + iVar2);

              cVar1 = *pcVar3;
              // if not -1,
              // meaning this "was" a secret character

              if (-1 < cVar1) {
                // set character ID to non-secret character
                data.characterIDs[iVar7] = (short)cVar1;
                // set to -1
                *pcVar3 = -1;
                break;
              }

            }
            
          }

        }

      }

    }
  return;
}