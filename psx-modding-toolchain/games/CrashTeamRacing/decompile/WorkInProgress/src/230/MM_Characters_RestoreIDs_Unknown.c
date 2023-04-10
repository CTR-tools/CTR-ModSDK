#include <common.h>

void DECOMP_MM_Characters_RestoreIDs(void) {
  struct GameTracker *gGT = sdata->gGT;
  short *currID;
  int iVar3;
  int iVar4;
  char i;

  // erase select bits
  sdata->characterSelectFlags = 0;
  OVR_230.transitionFrames = 0xc;
  OVR_230.isMenuTransitioning = 0;

  // This uses 80086e84, which controls character IDs
  // loop 8 times
  // shouldn't it only need to loop a maximum of 4 times?
  for (i = 0; i < 8; i++)
  {
    // set character ID to the last ID you entered
    data.characterIDs[i] = data.characterIDs_backup[i];
  }

  MM_Characters_SetMenuLayout();

  // PTR_DAT_800b5a18 goes to CrashIconX
  // This changes for the three menus
  // 1P + 2P	800B4E80
  // 3P			800B4F34
  // 4P			800B4FE8
  iVar3 = *(int*)0x800b5a18;

  //
  for (i = 0; i < 0xf; i++) {
    // Changes ID of Icon without changing image of icon
    // Changing Crash's ID at 800B50B4 makes it so going to
    // Crash's Icon will teleport the cursor somehwere else

    // Basically sets them to 0, 1, 2, 3, 4... up to 0xE,
    // setting Oxide's manually to 0xF is needed to make his icon appear

    OVR_230.characterIcon[*(short*)0x800b5a20[i]] = i;
  }

  // if number of players is not zero
  if (gGT->numPlyrNextGame) {

    iVar4 = 0

        for (i = 0; i < gGT->numPlyrNextGame; i++) {
      // Determine if this icon is unlocked (and drawing)

      // get character ID
      currID = data.characterIDs[i];

      // get unlock requirement for this character
      uVar1 = *(short *)(((int*)0x800b5a22)[currID]);

      if (
          // If Icon has an unlock requirement
          (uVar1 != -1) &&
          // If Character is Locked
          (sdata->GameProgress.unlocks[currID] >> uVar1 & 1) == 0) {
        // change character to Crash
        *currID = 0;
      }
      iVar4 = i * 0x10000;
    }
  }

  MM_Characters_ClearInactivePlayers();

  // if number of players is not zero
  if (gGT->numPlyrNextGame) {
    for (i = 0; i < gGT->numPlyrNextGame; i++) {

      // set name string ID to the character ID of each player.
      // The string will only draw if both these variables match
      (&DAT_800b59f8)[i] = data.characterIDs[i];
      (&DAT_800b59f0)[i] = data.characterIDs[i];

      // something to do with transitioning between icons
      OVR_230.fill_isMenuTransitioning2[i] = 0;

      // rotation of each driver, 90 degrees difference
      (&DAT_800b5a00)[i] = (i * 0x400) + 400;
    }
  }

  MM_Characters_DrawWindows(0);
  return;
}

