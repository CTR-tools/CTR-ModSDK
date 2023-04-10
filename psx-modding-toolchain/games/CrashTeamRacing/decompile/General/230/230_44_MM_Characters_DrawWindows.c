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
  short rot[3];
  
  gGT = sdata->gGT;

  if (wheelFlag != 0) {
    // enable drawing wheels
	gGT->renderFlags |= 0x80;
  }

  for (iVar14 = 0; iVar14 < gGT->numPlyrNextGame; iVar14++)
  {
    psVar11 = &OVR_230.characterSelect_ptrWindowXY[iVar14*2];
    iVar6 = &OVR_230.ptrTransitionMeta[iVar14];
  
    // tileView
    tileview = &gGT->tileView[iVar14];
  
    tileview->rect.x = *psVar11 + *(short *)(iVar6 + 0xa6);
  
    // window width
    uVar3 = OVR_230.characterSelect_aspectX;
  
    // window height
    uVar2 = OVR_230.characterSelect_aspectY;
  
    tileview->rect.y = psVar11[1] + *(short *)(iVar6 + 0xa8);
  
    // windowSize (X and Y)
    tileview->aspectX = uVar3;
    tileview->aspectY = uVar2;
  
    // negative StartX
    if ((short)tileview->rect.x < 0) {
      tileview->aspectX -= tileview->rect.x;
      tileview->rect.x = 0;
      if ((short)tileview->aspectX < 0) {
        tileview->aspectX = 0;
      }
    }
  
    // negative StartY
    if ((short)tileview->rect.y < 0) {
      tileview->aspectY -= tileview->rect.y;
      tileview->rect.y = 0;
      if ((short)tileview->aspectY < 0) {
        tileview->aspectY = 0;
      }
    }
  
    // startX + sizeX out of bounds
    if ((0x200 < (int)(short)tileview->rect.x + (int)(short)tileview->aspectX) &&
        (tileview->aspectX = (short)(0x200 - (u_int)(u_short)tileview->rect.x),
         (int)((0x200 - (u_int)(u_short)tileview->rect.x) * 0x10000) < 0)) {
      tileview->rect.x = 0x200;
      tileview->aspectX = 0;
    }
  
    // startY + sizeY out of bounds
    if ((0xd8 < (int)(short)tileview->rect.y + (int)(short)tileview->aspectY) &&
        (tileview->aspectY = (short)(0xd8 - (u_int)(u_short)tileview->rect.y),
         (int)((0xd8 - (u_int)(u_short)tileview->rect.y) * 0x10000) < 0)) {
      tileview->rect.y = 0xd8;
      tileview->aspectY = 0;
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
  
    // clear tileView in every InstDrawPerPlayer
    iVar10->idpp[0].tileView = 0;
    iVar10->idpp[1].tileView = 0;
    iVar10->idpp[2].tileView = 0;
    iVar10->idpp[3].tileView = 0;
  
    // set tileView in InstDrawPerPlayer,
    // so that each camera can only see one driver
    iVar10->idpp[iVar6].tileView = tileview;
  
    ptrCurr = &OVR_230.characterSelect_charIDs_curr[iVar6];
    iVar10->animFrame = 0;
    iVar10->vertSplit = 0;
  
    uVar4 = MM_Characters_GetModelByName(data.MetaDataCharacters[(int)*ptrCurr].name_Debug);
  
    // set modelPtr in Instance
    iVar10->model = uVar4;
  
    // CameraDC, freecam mode
    gGT->cameraDC[iVar6].cameraMode = 3;
	
    // Set position of player
    iVar10->matrix.t[0] = OVR_230.csm_instPos[0];
    iVar10->matrix.t[1] = OVR_230.csm_instPos[1];
    iVar10->matrix.t[2] = OVR_230.csm_instPos[2];
  
    psVar11 = &OVR_230.timerPerPlayer[iVar6];
    sVar9 = *psVar11 + -1;
  
    // If no transition between players
    if (*psVar11 == 0) {
      // compare to character ID
      if (*ptrCurr != data.characterIDs[iVar6]) {
        *psVar11 = OVR_230.moveModels << 1;
        OVR_230.characterSelect_charIDs_desired[iVar6] = data.characterIDs[iVar6];
      }
    }
  
    // if transition between players
    else {
      // get timer
      *psVar11 = sVar9;
  
      // if timer is before midpoint
      if ((int)sVar9 < (int)OVR_230.moveModels) 
	  {
        // make driver fly off screen
        *ptrCurr = OVR_230.characterSelect_charIDs_desired[iVar6];
        iVar5 = TitleFlag_MoveModels((int)sVar9, (int)OVR_230.moveModels);
  
        // direction moving
        iVar6 = -OVR_230.characterSelect_MoveDir[iVar6];
        iVar8 = iVar5 * OVR_230.unkCharacterWindows >> 0xc;
      }
  
      // if timer is after midpoint
      else {
        // make new driver fly on screen
        iVar5 = TitleFlag_MoveModels((int)sVar9 - (int)OVR_230.moveModels, (int)OVR_230.moveModels);
  
        // direction moving
        iVar8 = OVR_230.characterSelect_MoveDir[iVar6];
        iVar6 = (0x1000 - iVar5) * (int)OVR_230.unkCharacterWindows >> 0xc;
      }
  
      iVar10->matrix.t[0] += iVar6 * iVar8;
    }
  
    // driver rotation
    rot[0] = OVR_230.csm_instRot[0];
    rot[1] = OVR_230.csm_instRot[1] + OVR_230.characterSelect_angle[iVar14];
    rot[2] = OVR_230.csm_instRot[2];
  
    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&iVar10->matrix.m[0][0], &rot[0]);
  }
  return;
}