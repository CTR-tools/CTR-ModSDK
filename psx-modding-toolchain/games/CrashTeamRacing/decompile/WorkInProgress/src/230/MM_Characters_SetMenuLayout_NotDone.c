#include <common.h>

void MM_Characters_SetMenuLayout(void)
{
  unsigned short unlocked;
  char expand = 0;
  char numPlyr = sdata->gGT->numPlyrNextGame;
  int iVar3;
  int i;

  // By default, draw "Select character" in 3P menu
  OVR_230.isRosterExpanded = 0;

  // By default, array of character IDs is
  // grabbed from array of pointers to arrays of character IDs,
  // it can be index 0,1,2,3
  OVR_230.characterSelectIconLayout = numPlyr - 1;

  // Loop through bottom characters,
  // if any are unlocked, use expanded
  for (i = 0xc; i < 0xf; i++) {
    unlocked = OVR_230.csm_1P2P[i].characterID; // 800B4E8A
    if ((sdata->gameProgress->unlocks[unlocked >> 5] >> unlocked & 1) != 0) {

      // enough characters are unlocked for expanded menu
      // menu is expanded, stop drawing "select character"
      OVR_230.isRosterExpanded = expand;
    }
  }

  if (
      // if there are less than 3 players
      (numPlyr < 3) &&
      // if very few characters are unlocked
      (!expand)
    ) {
    // get new pointer to array of character IDs with less icons
    OVR_230.characterSelectIconLayout = numPlyr + 3;
  }

  // set final index to array of pointers of character IDs
  iVar3 = OVR_230.characterSelectIconLayout;

  // get driver posY from array
  *(int*)0x800b5362 = ((int*)0x800b4db4)[iVar3];

  // get driver posZ from array
  *(int*)0x800b5364 = ((int*)0x800b4da8)[iVar3];

  // get window height from array
  *(int*)0x800b59dc = ((int*)0x800b4d9c)[iVar3];

  // pointer to array of driver window positions,
  // this can be used to dynamically erase any driver window
  // of any player in any menu, for Oxide in menus
  *(int*)0x800b5a0c = OVR_230.ptrSelectWindowPos[iVar3];

  // set pointer to array of driver icons
  // If you ever want to make new driver arrays for oxide,
  // change the pointers at 800b509c to do it
  *(int*)0x800b5a18 = OVR_230.ptr_csm_1P[iVar3];

  // get window width from array
  *(int*)0x800b5a30 = ((int*)0x800b4d90)[iVar3];

  // Get position of text relative to window position
  *(int*)0x800b5a38 = ((int*)0x800b4dc0)[iVar3];

  *(int*)0x800b5a3c = OVR_230.ptr_transitionMeta_csm[numPlyr - 1];
  return;
}