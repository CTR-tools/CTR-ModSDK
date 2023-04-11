#include <common.h>

void MM_Characters_SetMenuLayout(void)
{
  unsigned short unlocked;
  char expand;
  int iVar3;
  int i;
  int numPlyrNextGame;

  expand = 0;

  // By default, draw "Select character" in 3P menu
  OVR_230.isRosterExpanded = 0;

  numPlyrNextGame = sdata->gGT->numPlyrNextGame;
  
  iVar3 = numPlyrNextGame - 1;

  // Loop through bottom characters,
  // if any are unlocked, use expanded
  for (i = 0xc; i < 0xf; i++) 
  {
    unlocked = OVR_230.csm_1P2P[i].unlockFlags;
    
	if ((sdata->gameProgress.unlocks[unlocked >> 5] >> unlocked & 1) != 0) 
	{
      expand = 1;
	  break;
    }
  }

  if (
      // if 1P2P (0 or 1)
      (iVar3 < 2) &&
	  
      // if very few characters are unlocked
      (!expand)
    ) 
  {
	// layout [4] and [5] for 1P2P without expansion
    iVar3 += 4;
  }


  OVR_230.isRosterExpanded = expand;

  OVR_230.characterSelectIconLayout = iVar3;

  OVR_230.csm_instPos[1] = OVR_230.driverPosY[iVar3];
  OVR_230.csm_instPos[2] = OVR_230.driverPosZ[iVar3];

  OVR_230.characterSelect_sizeX = OVR_230.windowW[iVar3];
  OVR_230.characterSelect_sizeY = OVR_230.windowH[iVar3];

  OVR_230.characterSelect_ptrWindowXY = OVR_230.ptrSelectWindowPos[iVar3];

  OVR_230.csm_Active = OVR_230.ptrCsmArr[iVar3];

  OVR_230.textPos = OVR_230.textPosArr[iVar3];

  OVR_230.ptrTransitionMeta = OVR_230.ptr_transitionMeta_csm[numPlyrNextGame - 1];

  return;
}