#include <common.h>

void DECOMP_MM_Characters_DrawWindows(char wheelFlag)
{
  struct GameTracker* gGT = sdata->gGT;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  short *psVar11;
  struct TileView* tileview;
  short *psVar13;
  int iVar14;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;

  if (wheelFlag != 0) {
    // enable drawing wheels
    *(unsigned int *)(gGT + 0x256c) |= 0x80;
  }

  // if number of players is not zero
  if (gGT->numPlyrNextGame) {

    for (iVar14 = 0; iVar14 < gGT->numPlyrNextGame; iVar14++)
    {
      psVar11 = ((short *)0x800b5a0c)[iVar14]
      iVar6 = (short *)0x800b5a3c[iVar14]

      // tileView
      tileview = gGT->tileView[iVar14];

      tileview->rect.x = *psVar11 + *(short *)(iVar6 + 0xa6);

      // window width
      uVar3 = *(unsigned int*)0x800b5a30;

      // window height
      uVar2 = *(unsigned int*)0x800b59dc;

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
          (tileview->aspectX = (short)(0x200 - (uint)(ushort)tileview->rect.x),
           (int)((0x200 - (uint)(ushort)tileview->rect.x) * 0x10000) < 0)) {
        tileview->rect.x = 0x200;
        tileview->aspectX = 0;
      }

      // startY + sizeY out of bounds
      if ((0xd8 < (int)(short)tileview->rect.y + (int)(short)tileview->aspectY) &&
          (tileview->aspectY = (short)(0xd8 - (uint)(ushort)tileview->rect.y),
           (int)((0xd8 - (uint)(ushort)tileview->rect.y) * 0x10000) < 0)) {
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
      iVar10 = gGT->drivers[iVar14].instSelf;

      // Disable "AI flag"
      iVar10->flags &= 0xffffff7f;

      // if driver loaded is not human
      if ((gGT->numPlyrNextGame <= iVar14) || (wheelFlag == 0)) 
      {
        // You are an AI (I think)
        iVar10->flags |= 0x80;
      }

      // clear tileView in every InstDrawPerPlayer
      iVar10->idpp[0].tileView = 0;
      iVar10->idpp[1].tileView = 0;
      iVar10->idpp[2].tileView = 0;
      iVar10->idpp[3].tileView = 0;

      // set tileView in InstDrawPerPlayer,
      // so that each camera can only see one driver
      iVar10->idpp[iVar14].tileView = puVar12;

      psVar13 = &DAT_800b59f8[iVar14];
      iVar10->animFrame = 0;
      iVar10->vertSplit = 0;

      uVar4 = MM_Characters_GetModelByName(data.MetaDataCharacters[(int)*psVar13].name_Debug);

      // set modelPtr in Instance
      iVar10->modelPtr = uVar4;

      // CameraDC, freecam mode
      gGT->CameraDC[iVar6] = 3;

      // Set position of player
      iVar10->matrix.t[0] = *(int*)0x800b5360;
      iVar10->matrix.t[1] = *(int*)0x800b5362;
      iVar10->matrix.t[2] = *(int*)0x800b5364;

      psVar11 = &DAT_800b5a24 + iVar6;
      sVar9 = *psVar11 + -1;

      // If no transition between players
      if (*psVar11 == 0) {
        // compare to character ID
        if (*psVar13 != data.characterIDs[iVar6]) {
          *psVar11 = (short)(*(int*)0x800b536e << 1);
          &DAT_800b59f0[iVar6] = data.characterIDs[iVar6];
        }
      }

      // if transition between players
      else {
        // get timer
        *psVar11 = sVar9;

        // if timer is before midpoint
        if ((int)sVar9 < (int)DAT_800b536e) {
          // make driver fly off screen
          *psVar13 = (&DAT_800b59f0)[iVar6];
          iVar5 = TitleFlag_MoveModels();

          // direction moving
          iVar6 = -(int)(short)(&DAT_800b59e8)[iVar6];
          iVar8 = iVar5 * DAT_800b5370 >> 0xc;
        }

        // if timer is after midpoint
        else {
          // make new driver fly on screen
          iVar5 = TitleFlag_MoveModels((int)sVar9 - (int)DAT_800b536e);

          // direction moving
          iVar8 = (int)(short)(&DAT_800b59e8)[iVar6];
          iVar6 = (0x1000 - iVar5) * (int)DAT_800b5370 >> 0xc;
        }

        iVar10->matrix.t[0] += iVar6 * iVar8;
      }

      // driver rotation
      local_2c = DAT_800b536c;
      local_30 = DAT_800b5368;
      local_2e = DAT_800b536a + *(short *)((int)&DAT_800b5a00 + ((iVar14 << 0x10) >> 0xf));

      // convert 3 rotation shorts into rotation matrix
      ConvertRotToMatrix(&iVar10->matrix.m[0][0], &local_30);

      iVar10 = iVar14 * 0x10000;
    } 
  }
  return;
}