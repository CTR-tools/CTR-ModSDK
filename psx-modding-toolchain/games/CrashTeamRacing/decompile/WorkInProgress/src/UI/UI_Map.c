#include <common.h>

// void DECOMP_UI_Map_GetIconDemensions(short *param_1,int *param_2,int *param_3)

// {
//   short sVar1;
//   int iVar2;
//   int iVar3;
//   int iVar4;
//   int iVar5;

//   iVar5 = (int)param_1[7] + -0x10;
//   iVar3 = (int)*param_1 - (int)param_1[2];
//   sVar1 = param_1[8];
//   iVar4 = (int)param_1[1] - (int)param_1[3];
//   if (sVar1 == 0) {
//     if (iVar3 == 0) {
//       trap(0x1c00);
//     }
//     if ((iVar3 == -1) && (*param_2 * (int)param_1[4] == -0x80000000)) {
//       trap(0x1800);
//     }
//     iVar2 = *param_3 * (int)param_1[5] * 2;
//     if (iVar4 == 0) {
//       trap(0x1c00);
//     }
//     if ((iVar4 == -1) && (iVar2 == -0x80000000)) {
//       trap(0x1800);
//     }
//     iVar3 = (int)param_1[6] + (*param_2 * (int)param_1[4]) / iVar3;
//     iVar5 = iVar5 + iVar2 / iVar4;
//   }
//   else {
//     if (sVar1 == 1) {
//       iVar2 = *param_2 * (int)param_1[5] * 2;
//       if (iVar3 == 0) {
//         trap(0x1c00);
//       }
//       if ((iVar3 == -1) && (iVar2 == -0x80000000)) {
//         trap(0x1800);
//       }
//       if (iVar4 == 0) {
//         trap(0x1c00);
//       }
//       if ((iVar4 == -1) && (*param_3 * (int)param_1[4] == -0x80000000)) {
//         trap(0x1800);
//       }
//       iVar5 = iVar5 + iVar2 / iVar3;
//       iVar3 = (int)param_1[6] - (*param_3 * (int)param_1[4]) / iVar4;
//     }
//     else {
//       if (sVar1 == 2) {
//         if (iVar3 == 0) {
//           trap(0x1c00);
//         }
//         if ((iVar3 == -1) && (*param_2 * (int)param_1[4] == -0x80000000)) {
//           trap(0x1800);
//         }
//         iVar2 = *param_3 * (int)param_1[5] * 2;
//         if (iVar4 == 0) {
//           trap(0x1c00);
//         }
//         if ((iVar4 == -1) && (iVar2 == -0x80000000)) {
//           trap(0x1800);
//         }
//         iVar3 = (int)param_1[6] - (*param_2 * (int)param_1[4]) / iVar3;
//         iVar5 = iVar5 - iVar2 / iVar4;
//       }
//       else {
//         iVar2 = *param_2 * (int)param_1[5] * 2;
//         if (iVar3 == 0) {
//           trap(0x1c00);
//         }
//         if ((iVar3 == -1) && (iVar2 == -0x80000000)) {
//           trap(0x1800);
//         }
//         if (iVar4 == 0) {
//           trap(0x1c00);
//         }
//         if ((iVar4 == -1) && (*param_3 * (int)param_1[4] == -0x80000000)) {
//           trap(0x1800);
//         }
//         iVar5 = iVar5 - iVar2 / iVar3;
//         iVar3 = (int)param_1[6] + (*param_3 * (int)param_1[4]) / iVar4;
//       }
//     }
//   }

//   // If numPlyrCurrGame is 3
//   if (sdata->gGT->numPlyrCurrGame == 3) {
//     iVar3 = iVar3 + -0x3c;
//     iVar5 = iVar5 + 10;
//   }
//   *param_2 = iVar3;
//   *param_3 = iVar5;
//   return;
// }

// Draw dot for Player on 2D Adv Map
void UI_Map_DrawAdvPlayer(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
                 short param_5,short param_6)

{
  undefined *puVar1;
  undefined4 posX;
  undefined4 posY;

  posX = *param_2;
  posY = param_2[2];

  UI_Map_GetIconDemensions(param_1,&posX,&posY);

  puVar1 = &DAT_80086424;
  if ((sdata->gGT->timer & 2) != 0) {
    puVar1 = &DAT_80086430;
  }

  // AH_Map_HubArrow
  AH_Map_HubArrow((int)(short)posX,(int)(short)posY,&DAT_80086418,puVar1,(int)param_6,
               (int)param_5);
  return;
}

// Draw icon on map
// param_4 color index
// param_6 scale
void UI_Map_DrawRawIcon(undefined4 param_1,undefined4 *param_2,int param_3,int param_4,undefined4 param_5,
                 short scale)

{
  int *piVar1;
  undefined posX;
  undefined posY;

  posX = *param_2;
  posY = param_2[2];

  // Icon dimensions
  UI_Map_GetIconDemensions(param_1,&posX,&posY);

  // color data
  piVar1 = (int *)((int)&PTR_DAT_80081d70 + ((param_4 << 0x10) >> 0xe));

  // DecalHUD_DrawPolyGT4
  DecalHUD_DrawPolyGT4(sdata->gGT->iconGroup[0]->icons[((param_3 << 0x10) >> 0xe) + 0x14],

			   // dimensions
			   posX,
               posY,

			   // pointer to PrimMem struct
			   &sdata->gGT->backBuffer->primMem,

			   // pointer to OT mem
			   sdata->gGT->tileView_UI.ptrOT,

			   // color data
                data.ptrColor[0],
                data.ptrColor[1],
                data.ptrColor[2],
                data.ptrColor[3],

			   0,

			   // scale
			   (int)scale);
  return;
}

// UI_Map_DrawDrivers
void UI_Map_DrawDrivers(void* levPtrMap,struct Thread* param_2,short *param_3)

{
  int kartColor;
  undefined4 uVar2;
  int d;

  if (param_2 != 0)
  {
	// loop through all drivers
    do
	{
	  // If numPlyrCurrGame is 1, or 3
      if ((sdata->gGT->numPlyrCurrGame == 1) || (sdata->gGT->numPlyrCurrGame == 3))
	  {
		// Player structure
        struct Driver* d = *(int *)(param_2 + 0x30);

		// Player / AI structure + 0x4a shows driver index (0-7)

		// color data index 5 is where color
		// of each kart is stored in the array

		// characterID + 5
        kartColor = data.characterIDs[d->driverID] + 5;

        // if this is human and not AI
        if ((d->actionsFlagSet & 0x100000) == 0) {

		  // If you're in Adventure Arena
          if ((sdata->gGT->gameMode1 & 0x100000) != 0)
		  {
            // If this is an even-numbered frame
            if ((sdata->gGT->timer & 2) == 0) {
              kartColor = 4;
            }

			// If this is an odd numbered frame
            else
			{
			  // cast to short, remove higher bits
              kartColor = kartColor * 0x10000 >> 0x10;
            }

			// Draw dot for Player on 2D Adv Map
            UI_Map_DrawAdvPlayer(levPtrMap,param_2->inst->matrix.m[0][2],0x32,kartColor,
                        (d->rotCurr.y + 0x800U) | 0x1000,0x800);

            goto LAB_8004dea8;
          }

		  // If this is an even numbered frame
          if ((sdata->gGT->timer & 2) == 0) {
            kartColor = 4;
          }

		  // If this is an odd numbered frame
          else {
            kartColor = kartColor * 0x10000 >> 0x10;
          }
          uVar2 = 0x32;
        }
        else {
          uVar2 = 0x31;
          kartColor = kartColor * 0x10000 >> 0x10;
        }

		// Draw icon on map
        UI_Map_DrawRawIcon(levPtrMap,param_2->inst->matrix.m[0][2],uVar2,kartColor,0,0x1000);
      }
LAB_8004dea8:

	  // count how many icons have been drawn,
	  // this was used in prototypes to draw
	  // ascii numbers on maps, wasn't fully removed
      *param_3 = *param_3 + 1;

	  // thread = thread->sibling
      param_2 = param_2->siblingThread;

    } while (param_2 != 0);
  }
  return;
}


void UI_Map_DrawGhosts(void* levPtrMap,struct Thread* ghostThread)
{
  undefined4 uVar1;

  //if (ghost struct pointer?) is not 0 (if you are in Time Trial mode)
  if (ghostThread != 0)
  {
	// loop through all ghosts
    do {
      //if you have beaten Nefarious Tropy
      if (ghostThread->object->unk632 != 0) {
        if (ghostThread->object->ghostID == 0) {
          uVar1 = 6;
          //if the number of elapsed frames since boot is odd
          if ((sdata->gGT->timer & 1) != 0) {
            uVar1 = 5;
          }
        }
        else {
          uVar1 = 0x11;

		  // if timeTrialFlags for this track show [ n tropy beaten ]
          if (((sdata->gameProgress.highScoreTracks[sdata->gGT->levelID].timeTrialFlags & 2) != 0) &&
             (uVar1 = 3, ((sdata->gGT->timer & 1) != 0))) {
            uVar1 = 4;
          }
        }

		// Draw icon on map
        UI_Map_DrawRawIcon(levPtrMap,*(int *)(ghostThread + 0x34) + 0x44,0x31,uVar1,0,0x1000);
      }

	  // Go to next ghost
	  // thread = thread->sibling
      ghostThread = ghostThread->siblingThread;

    } while (ghostThread != 0);
  }
  return;
}


// Draw all "Tracking" warp balls on 2D map
void UI_Map_DrawTracking(void* levPtrMap,struct Thread* warpballThread)

{
  undefined4 uVar1;
  struct Instance* inst;

  if (warpballThread != 0) {
    do {

	  // thread -> instance
      inst = warpballThread->inst;

	  // instance -> model -> modelID == warpball
      if (inst->model->id == 0x36)
	  {
		// Draw icon on map.
        UI_Map_DrawRawIcon(levPtrMap,(inst + 0x44),0x20,0,0,0x1000);

		// get object from thread
        inst = inst->thread->object;

        uVar1 = 4;

		// if object exists
        if (inst != 0) {
          if ((sdata->gGT->timer & 1) != 0) {
            uVar1 = 3;
          }

		  // Draw icon on map
          UI_Map_DrawRawIcon(levPtrMap,inst->instSelf.matrix,0x21,uVar1,0,0x1000);
        }
      }

      warpballThread = warpballThread->siblingThread;
    } while (warpballThread != 0);
  }
  return;
}