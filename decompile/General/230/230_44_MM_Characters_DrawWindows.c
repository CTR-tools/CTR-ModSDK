#include <common.h>

void DECOMP_MM_Characters_DrawWindows(char wheelFlag)
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
  struct TileView* tileview;
  short *ptrCurr;
  int iVar14;
  struct TransitionMeta* tMeta;
  short rot[3];
  
  gGT = sdata->gGT;

  if (wheelFlag != 0) {
    // enable drawing wheels
	gGT->renderFlags |= 0x80;
  }

  for (iVar14 = 0; iVar14 < gGT->numPlyrNextGame; iVar14++)
  {
    psVar11 = &D230.characterSelect_ptrWindowXY[iVar14*2];
    tMeta = &D230.ptrTransitionMeta[iVar14];
  
    // tileView
    tileview = &gGT->tileView[iVar14];
  
    tileview->rect.x = psVar11[0] + tMeta[0x10].currX;
    tileview->rect.y = psVar11[1] + tMeta[0x10].currY;
    tileview->rect.w = D230.characterSelect_sizeX;
    tileview->rect.h = D230.characterSelect_sizeY;
  
    // negative StartX
    if ((short)tileview->rect.x < 0) {
      tileview->rect.w -= tileview->rect.x;
      tileview->rect.x = 0;
      if ((short)tileview->rect.w < 0) {
        tileview->rect.w = 0;
      }
    }
  
    // negative StartY
    if ((short)tileview->rect.y < 0) {
      tileview->rect.h -= tileview->rect.y;
      tileview->rect.y = 0;
      if ((short)tileview->rect.h < 0) {
        tileview->rect.h = 0;
      }
    }
  
    // startX + sizeX out of bounds
    if ((0x200 < (int)(short)tileview->rect.x + (int)(short)tileview->rect.w) &&
        (tileview->rect.w = (short)(0x200 - (u_int)(u_short)tileview->rect.x),
         (int)((0x200 - (u_int)(u_short)tileview->rect.x) * 0x10000) < 0)) {
      tileview->rect.x = 0x200;
      tileview->rect.w = 0;
    }
  
    // startY + sizeY out of bounds
    if ((0xd8 < (int)(short)tileview->rect.y + (int)(short)tileview->rect.h) &&
        (tileview->rect.h = (short)(0xd8 - (u_int)(u_short)tileview->rect.y),
         (int)((0xd8 - (u_int)(u_short)tileview->rect.y) * 0x10000) < 0)) {
      tileview->rect.y = 0xd8;
      tileview->rect.h = 0;
    }
  
    // distanceToScreen
    tileview->distanceToScreen_CURR = 0x100;
    tileview->distanceToScreen_PREV = 0x100;
  
    // tileView pos and rot to all zero
    tileview->pos[0] = 0;
    tileview->pos[1] = 0;
    tileview->pos[2] = 0;
    tileview->rot[0] = 0;
    tileview->rot[1] = 0;
    tileview->rot[2] = 0;
  
    // player -> instance
    iVar10 = gGT->drivers[iVar14]->instSelf;
  
    // Disable "AI flag"
    iVar10->flags &= 0xffffff7f;
  
    // if driver loaded is not human
    if ((gGT->numPlyrNextGame <= iVar14) || (wheelFlag == 0)) 
    {
      // You are an AI (I think)
      iVar10->flags |= 0x80;
    }
  
	iVar6 = iVar14;

	struct InstDrawPerPlayer* idpp =
		INST_GETIDPP(iVar10);
  
    // clear tileView in every InstDrawPerPlayer
    idpp[0].tileView = 0;
    idpp[1].tileView = 0;
    idpp[2].tileView = 0;
    idpp[3].tileView = 0;
  
    // set tileView in InstDrawPerPlayer,
    // so that each camera can only see one driver
    idpp[iVar6].tileView = tileview;

    ptrCurr = &D230.characterSelect_charIDs_curr[iVar6];

    iVar10->animFrame = 0;
    iVar10->vertSplit = 0;

#if 0
    uVar4 = DECOMP_MM_Characters_GetModelByName(data.MetaDataCharacters[(int)*ptrCurr].name_Debug);
#else
	struct Model* MM_Characters_GetModelByID(int id);
	uVar4 = MM_Characters_GetModelByID(*ptrCurr);
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
        iVar5 = DECOMP_TitleFlag_MoveModels((int)sVar9, (int)D230.moveModels);
  
        // direction moving
        iVar6 = -D230.characterSelect_MoveDir[iVar6];
        iVar8 = iVar5 * D230.unkCharacterWindows >> 0xc;
      }
  
      // if timer is after midpoint
      else {
        // make new driver fly on screen
        iVar5 = DECOMP_TitleFlag_MoveModels((int)sVar9 - (int)D230.moveModels, (int)D230.moveModels);
  
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

#if 0 // ANIM_TEST
	rot[1] = D230.csm_instRot[1];
#endif

#ifndef REBUILD_PS1
    ConvertRotToMatrix(&iVar10->matrix.m[0][0], &rot[0]);
#else
    // only a TEST function for REBUILD_PS1 and REBUILD_PC,
    // can not be used stable, with regular PS1 modding
    DECOMP_ConvertRotToMatrix(&iVar10->matrix.m[0][0], &rot[0]);
#endif
  }
  return;
}