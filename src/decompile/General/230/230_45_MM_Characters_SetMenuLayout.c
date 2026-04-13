#include <common.h>

#ifdef USE_OXIDE
#include "../AltMods/MM_Oxide_IconArrays.c"
#endif

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

#ifndef USE_OXIDE
  // original game
  #define NUM_ICONS 0xF
#else
  // modded game
  #define NUM_ICONS 0x10
  D230.ptrCsmArr[0] = &OXIDE_icons1p2p[0];
  D230.ptrCsmArr[1] = &OXIDE_icons1p2p[0];
  D230.ptrCsmArr[2] = &OXIDE_icons3p[0];
  D230.ptrCsmArr[3] = &OXIDE_icons4p[0];
  D230.ptrCsmArr[4] = &OXIDE_icons1p2pLimited[0];
  D230.ptrCsmArr[5] = &OXIDE_icons1p2pLimited[0];
  
  
  //struct Model* m = sdata->PLYROBJECTLIST[18];
  struct Model* MM_Characters_GetModelByID(int id);
  struct Model* m = MM_Characters_GetModelByID(0xf);
  
  // modified scale, 5/8 size -- ((orig * 5) >> 3)
  m->headers[0].scale[0] = 0x896;
  m->headers[0].scale[1] = 0x809;
  m->headers[0].scale[2] = 0xADC;
  
  m->headers[0].ptrAnimations[0] = 
  m->headers[0].ptrAnimations[1];
#endif

  // Loop through bottom characters,
  // if any are unlocked, use expanded
  for (i = 0xc; i < NUM_ICONS; i++) 
  {
	#ifdef USE_OXIDE
	
	// modded
	unlocked = D230.ptrCsmArr[0][i].unlockFlags;
	
	#else
	
	// OG game code
    unlocked = D230.csm_1P2P[i].unlockFlags;
	
	#endif
	
	if ((sdata->gameProgress.unlocks[0] >> unlocked & 1) != 0) 
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