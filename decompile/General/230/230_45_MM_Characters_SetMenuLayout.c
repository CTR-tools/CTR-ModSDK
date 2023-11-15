#include <common.h>

void DECOMP_MM_Characters_SetMenuLayout(void)
{
  unsigned short unlocked;
  char expand;
  int iVar3;
  int i;
  int numPlyrNextGame;

  expand = 0;

  // By default, draw "Select character" in 3P menu
  D230.isRosterExpanded = 0;

  numPlyrNextGame = sdata->gGT->numPlyrNextGame;
  
  iVar3 = numPlyrNextGame - 1;

  // Loop through bottom characters,
  // if any are unlocked, use expanded
  for (i = 0xc; i < 0xf; i++) 
  {
    unlocked = D230.csm_1P2P[i].unlockFlags;
    
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


  D230.isRosterExpanded = expand;

  D230.characterSelectIconLayout = iVar3;

  D230.csm_instPos[1] = D230.driverPosY[iVar3];
  D230.csm_instPos[2] = D230.driverPosZ[iVar3];

  D230.characterSelect_sizeX = D230.windowW[iVar3];
  D230.characterSelect_sizeY = D230.windowH[iVar3];

  D230.characterSelect_ptrWindowXY = D230.ptrSelectWindowPos[iVar3];

  D230.csm_Active = D230.ptrCsmArr[iVar3];

  D230.textPos = D230.textPosArr[iVar3];

  D230.ptrTransitionMeta = D230.ptr_transitionMeta_csm[numPlyrNextGame - 1];

  return;
}