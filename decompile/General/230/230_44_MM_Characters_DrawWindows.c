#include <common.h>

void DECOMP_MM_Characters_DrawWindows(int boolShowDrivers)
{
  struct GameTracker* gGT;
  short uVar2;
  short uVar3;
  struct Model* uVar4;
  int iVar5;
  unsigned int iVar6;
  u_int uVar7;
  int iVar8;
  short sVar9;
  struct Instance* iVar10;
  short *psVar11;
  struct PushBuffer* pb;
  short *ptrCurr;
  int iVar14;
  struct TransitionMeta* tMeta;
  short rot[3];
  
  gGT = sdata->gGT;

  if (boolShowDrivers != 0) {
    // enable drawing wheels
	gGT->renderFlags |= 0x80;
  }

  for (iVar14 = 0; iVar14 < gGT->numPlyrNextGame; iVar14++)
  {
    psVar11 = &D230.characterSelect_ptrWindowXY[iVar14*2];
    tMeta = &D230.ptrTransitionMeta[iVar14];
  
    pb = &gGT->pushBuffer[iVar14];
    pb->rect.x = psVar11[0] + tMeta[0x10].currX;
    pb->rect.y = psVar11[1] + tMeta[0x10].currY;
    pb->rect.w = D230.characterSelect_sizeX;
    pb->rect.h = D230.characterSelect_sizeY;
  
    // negative StartX
    if ((short)pb->rect.x < 0) {
      pb->rect.w -= pb->rect.x;
      pb->rect.x = 0;
      if ((short)pb->rect.w < 0) {
        pb->rect.w = 0;
      }
    }
  
    // negative StartY
    if ((short)pb->rect.y < 0) {
      pb->rect.h -= pb->rect.y;
      pb->rect.y = 0;
      if ((short)pb->rect.h < 0) {
        pb->rect.h = 0;
      }
    }
  
    // startX + sizeX out of bounds
    if (
            (0x200 < pb->rect.x + pb->rect.w) &&
            (
                pb->rect.w = 0x200 - pb->rect.x,
                pb->rect.w < 0
            )
        )
    {
      pb->rect.x = 0x200;
      pb->rect.w = 0;

#ifdef REBUILD_PC
      // PsyCross can't handle w==0
      pb->rect.w = 1;
#endif
    }
  
    // startY + sizeY out of bounds
    if (
            (0xd8 < pb->rect.y + pb->rect.h) &&
            (
                pb->rect.h = 0xd8 - pb->rect.y,
                pb->rect.h < 0
            )
        ) 
    {
      pb->rect.y = 0xd8;
      pb->rect.h = 0;

#ifdef REBUILD_PC
      // PsyCross can't handle h==0
      pb->rect.h = 1;
#endif
    }
  
    // distanceToScreen
    pb->distanceToScreen_CURR = 0x100;
    pb->distanceToScreen_PREV = 0x100;
  
    // pushBuffer pos and rot to all zero
    pb->pos[0] = 0;
    pb->pos[1] = 0;
    pb->pos[2] = 0;
    pb->rot[0] = 0;
    pb->rot[1] = 0;
    pb->rot[2] = 0;
  
    // player -> instance
    iVar10 = gGT->drivers[iVar14]->instSelf;
  
    // Make Visible
    iVar10->flags &= 0xffffff7f;
  
    // if driver is off-screen
    if (
			// ND bug, this can't happen
			#if 0
			(gGT->numPlyrNextGame <= iVar14) || 
			#endif
			
			(boolShowDrivers == 0)
		) 
    {
      // invisible
      iVar10->flags |= 0x80;
    }
  
	iVar6 = iVar14;

	struct InstDrawPerPlayer* idpp =
		INST_GETIDPP(iVar10);
  
    // clear pushBuffer in every InstDrawPerPlayer
    idpp[0].pushBuffer = 0;
    idpp[1].pushBuffer = 0;
    idpp[2].pushBuffer = 0;
    idpp[3].pushBuffer = 0;
  
    // set pushBuffer in InstDrawPerPlayer,
    // so that each camera can only see one driver
    idpp[iVar6].pushBuffer = pb;

    ptrCurr = &D230.characterSelect_charIDs_curr[iVar6];

    iVar10->animFrame = 0;
    iVar10->vertSplit = 0;

#if 0
    uVar4 = DECOMP_MM_Characters_GetModelByName(data.MetaDataCharacters[(int)*ptrCurr].name_Debug);
#else
	struct Model* MM_Characters_GetModelByID(int id);
	uVar4 = MM_Characters_GetModelByID(*ptrCurr);
#endif

#ifdef USE_OXIDE
	gGT->drivers[iVar14]->wheelSize = 0xccc;
	if(*ptrCurr == 0xf)
		gGT->drivers[iVar14]->wheelSize = 0;
#endif
  
    // set modelPtr in Instance
    iVar10->model = uVar4;
  
    // CameraDC, freecam mode
    gGT->cameraDC[iVar6].cameraMode = 3;
	
    // Set position of player
    iVar10->matrix.t[0] = D230.csm_instPos[0];
    iVar10->matrix.t[1] = D230.csm_instPos[1];
    iVar10->matrix.t[2] = D230.csm_instPos[2];
  
    psVar11 = &D230.timerPerPlayer[iVar6];
    sVar9 = *psVar11 + -1;
  
    // If no transition between players
    if (*psVar11 == 0) {
      // compare to character ID
      if (*ptrCurr != data.characterIDs[iVar6]) {
        *psVar11 = D230.moveModels << 1;
        D230.characterSelect_charIDs_desired[iVar6] = data.characterIDs[iVar6];
      }
    }
  
    // if transition between players
    else {
      // get timer
      *psVar11 = sVar9;
  
      // if timer is before midpoint
      if ((int)sVar9 < (int)D230.moveModels) 
	  {
        // make driver fly off screen
        *ptrCurr = D230.characterSelect_charIDs_desired[iVar6];
        iVar5 = DECOMP_RaceFlag_MoveModels((int)sVar9, (int)D230.moveModels);
  
        // direction moving
        iVar6 = -D230.characterSelect_MoveDir[iVar6];
        iVar8 = iVar5 * D230.unkCharacterWindows >> 0xc;
      }
  
      // if timer is after midpoint
      else {
        // make new driver fly on screen
        iVar5 = DECOMP_RaceFlag_MoveModels((int)sVar9 - (int)D230.moveModels, (int)D230.moveModels);
  
        // direction moving
        iVar8 = D230.characterSelect_MoveDir[iVar6];
        iVar6 = (0x1000 - iVar5) * (int)D230.unkCharacterWindows >> 0xc;
      }

      iVar10->matrix.t[0] += iVar6 * iVar8;
    }
  
    // driver rotation
    rot[0] = D230.csm_instRot[0];
    rot[1] = D230.csm_instRot[1] + D230.characterSelect_angle[iVar14];
    rot[2] = D230.csm_instRot[2];

	// converted to TEST in rebuildPS1
    ConvertRotToMatrix(&iVar10->matrix.m[0][0], &rot[0]);
  }
  return;
}