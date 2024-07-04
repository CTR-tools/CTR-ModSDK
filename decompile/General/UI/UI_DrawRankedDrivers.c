#include <common.h>
#include "../AltMods/OnlineCTR/global.h"

// Draw player icons on left side of screen
// in Arcade mode and Boss mode, and draws
// icons in multiplayer on the midY axis (and warpball)

int DriverIndex_GetDamageColor(int iVar14)
{
	struct GameTracker* gGT = sdata->gGT;
	struct Driver* d = gGT->drivers[iVar14];

    int iVar12 = d->damageColorTimer;

	// make icon white
	int local_30 = 0x808080;

	// -30 to -1
    if (iVar12 < 0)
	{
		local_30 = 0;
		int strength = (iVar12 + 30) * 4;
		local_30 += strength;
		local_30 += (0xFF-strength) * 0x100;
		local_30 += strength * 0x10000;

		#ifdef USE_60FPS
		if(gGT->timer & 1)
		#endif

		// one frame closer to zero
		d->damageColorTimer += 1;
    }

    // 30 to 1
    if (iVar12 > 0)
	{
		local_30 = 0;
		int strength = (30 - iVar12) * 4;
		local_30 += (0xFF-strength);
		local_30 += strength * 0x100;
		local_30 += strength * 0x10000;

		#ifdef USE_60FPS
		if(gGT->timer & 1)
		#endif

		// one frame closer to zero
		d->damageColorTimer -= 1;
    }

	return local_30;
}

void DECOMP_UI_DrawRankedDrivers(void)
{
    u_short uVar1;
    char bVar2;
    int iVar3;
    int iVar4;
    struct GameTracker *gGT;
    short txtColor;
    u_int uVar7;
    int absPosRank;
    int iVar8;
    short *puVar9;
    short numRacersFinished;
    u_short uVar11;
    int iVar12;
    short *psVar13;
    int iVar14;
    struct Thread* warpballThread;
    struct Instance* warpballInst;
    int iVar15;
    u_short *puVar16;
    short *psVar17;
    u_short uVar18;
    Point pos;
    short local_44;
    short local_40;
    short local_3e;
    short local_3c;
    short local_38;
    short local_34;
    u_int local_30;
    u_int local_2c;

    gGT = sdata->gGT;

	int numPlyr = gGT->numPlyrCurrGame;

    if (numPlyr == 1)
	{
      // Number of racers that have finished race
      numRacersFinished = 0;

      // incremented when looping through player structures

      for (iVar14 = 0; iVar14 < 8; iVar14++)
	  {
        if (data.rankIconsTransitionTimer[iVar14] == 0)
		{
          // player structure + 0x482 is your rank in the race
          // 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
          data.rankIconsDesired[iVar14] = gGT->drivers[iVar14]->driverRank;
        }

        // if player structure pointer is not nullptr
        if ((gGT->drivers[iVar14] != 0) &&

          //if racer finished the race
          ((gGT->drivers[iVar14]->actionsFlagSet&0x2000000) != 0))
		{
          // count how many racers have finished
          numRacersFinished++;
        }
      }

      // Default for Arcade: Show 4 racers
      iVar14 = 4;

      // If you're in a Boss Race
      if (gGT->gameMode1 < 0)
	  {
        // Show 2 racers
        iVar14 = 2;
      }

	  #ifdef USE_ONLINE
	  int OnlineGetNumDrivers();
	  int oNumDrivers = OnlineGetNumDrivers();
	  if(oNumDrivers < 9) { iVar14 = oNumDrivers; }
	  #endif

      // start drawing the icons
      iVar15 = 0;

	  // height to draw rank (this bitshifts later)
	  iVar12 = 0x380000;

	  #ifndef USE_ONLINE
	  for (iVar15 = 0; iVar15 < iVar14; iVar15++)
	  {
		// make the text white by default
		txtColor = 4;

		// if racer has finished the race
		if (iVar15 < numRacersFinished) {
			// make the text red
			txtColor = 3;
		}

		// draw rank number: '1', '2', '3', '4'
		sdata->s_spacebar[0] = (char) iVar15 + '1';
		DECOMP_DecalFont_DrawLine(&sdata->s_spacebar[0], 0x34, iVar12 >> 0x10, 2, txtColor);

		// add to Y, which mekes it lower on screen
		iVar12 = iVar12 + 0x1b0000;
	  }
	  #endif

      for (iVar14 = 0; iVar14 < 8; iVar14++)
	  {
		#ifdef USE_ONLINE
		if (!octr->nameBuffer[iVar14][0]) { continue; }
		#endif

        short* curr = &data.rankIconsCurr[iVar14];
	    short* des = &data.rankIconsDesired[iVar14];

        if (
          // if player structure pointer is not nullptr
          (gGT->drivers[iVar14] != 0) &&

          // if you haven't gotten to the last driver
          ((*des + 1) < 9)
        )
		{
		  local_30 = DriverIndex_GetDamageColor(iVar14);

          psVar13 = &data.rankIconsTransitionTimer[iVar14];

		  // placeholder
		  pos.x = -100;

		  // icon not transitioning
          if (*psVar13 == 0)
		  {
            // get absolute pos-rank of driver
            iVar12 = *des;

            // if current == desired
            if (iVar12 == *curr)
			{
              // if top positions

			  #ifdef USE_ONLINE
			  pos.x = 10;
			  pos.y = 53 + iVar12 * 20;
			  #else
			  if (iVar12 < 4)
			  {
				pos.x = 0x14;
				pos.y = iVar12 * 0x1b + 0x39;
              }
			  else { continue; }
			  #endif
            }
          }

		  #ifdef USE_ONLINE
		  short iconScale = FP(0.75);
		  txtColor = 4;
		  if (checkpointTracker[iVar15].raceFinished) { txtColor = 3; }
		  sdata->s_spacebar[0] = (char) *curr + '1';
		  DECOMP_DecalFont_DrawLine(&sdata->s_spacebar[0], 29, 53 + *curr * 20, 2, txtColor);
		  #else
          short iconScale = FP(1);
		  #endif

		  // === Icon Transitioning ===
		  if(pos.x == -100)
		  {
			DECOMP_UI_Lerp2D_Angular(
				(short *)&pos,
				*curr,
				*des,
				*psVar13
			);

            psVar13[0]++;

		    if (*psVar13 >= FPS_DOUBLE(5))
		    {
              *psVar13 = 0;
              *curr = *des;
            }
		  }

		  Color color;
		  color.self = local_30;
		  DECOMP_UI_DrawDriverIcon(

            gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[iVar14]].iconID],

            pos,

            gGT->pushBuffer_UI.ptrOT,

            1, iconScale, color);

		  #ifdef USE_ONLINE
		  if (checkpointTracker[iVar14].timer > 0)
		  {
			DECOMP_DecalFont_DrawLineStrlen(
				checkpointTracker[iVar14].displayTime,
				10,
				pos.x + 30,
				pos.y + 9,
				FONT_SMALL, checkpointTracker[iVar14].drawFlags);
			checkpointTracker[iVar14].timer -= sdata->gGT->elapsedTimeMS;
			DECOMP_DecalFont_DrawLineStrlen(
				octr->nameBuffer[iVar14],
				3,
				pos.x + 45,
				pos.y + 1,
				FONT_SMALL, iVar14 == 0 ? JUSTIFY_CENTER | BLUE : JUSTIFY_CENTER | ORANGE);
		  }
		  else
		  {
			DECOMP_DecalFont_DrawLineStrlen(
				octr->nameBuffer[iVar14],
				3,
				pos.x + 45,
				pos.y + 7,
				FONT_SMALL, iVar14 == 0 ? JUSTIFY_CENTER | BLUE : JUSTIFY_CENTER | ORANGE);
		  }
		  #endif
        }
      }
    }

	// if this is multiplayer
    else
	{
      puVar16 = &data.rankIconsTransitionTimer[0];
      iVar15 = 0;

	  int totalNumDrivers;
      totalNumDrivers = numPlyr + gGT->numBotsNextGame;

      for (iVar14 = 0; iVar14 < totalNumDrivers; iVar14++)
	  {
        // puVar5 increases by 4 for each iteration

        local_30 = DriverIndex_GetDamageColor(iVar14);

        uVar1 = *puVar16;

        if (
				//if racer is in first lap and
				(gGT->drivers[iVar14]->lapIndex == 0) &&

				//racer crossed the startline backwards
				//this is when race starts and you're behind the finish line
				((gGT->drivers[iVar14]->actionsFlagSet&0x1000000) != 0)
        )
		{
          LAB_80052b00:
            // icon posX is zero,
            // dont go to end of lap on the graph
            uVar18 = 0;
        }
        else {
          // length of track
          iVar3 = gGT->level1->ptr_restart_points[0].distToFinish * 8;
          iVar4 = iVar3 - gGT->drivers[iVar14]->distanceToFinish_curr;
          iVar3 = iVar3 / 0x1d1;

          // divide distanceToFinish by screen width
          uVar18 = iVar4 / iVar3;
          uVar18 = (u_short) uVar18;

#if 0
          if (iVar3 == 0) trap(0x1c00);
          if ((iVar3 == -1) && (iVar4 == -0x80000000)) trap(0x1800);
          if (uVar18 << 0x10 < 0) goto LAB_80052b00;
#endif
        }

        // posX
        iVar4 = uVar18;
        iVar3 = iVar4 - (short) uVar1;

        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        uVar7 = iVar3 / 0xe;
        if ((uVar7 & 0xffff) == 0) {
          uVar7 = 1;
        }
        iVar3 = uVar1 + uVar7;
        uVar11 = (u_short) iVar3;
        if ((short) uVar1 < iVar4) {
          bVar2 = iVar4 < (short) iVar3;
        } else {
          iVar3 = uVar1 - uVar7;
          uVar11 = (u_short) iVar3;
          bVar2 = (short) iVar3 < iVar4;
        }
        if (bVar2) {
          uVar11 = uVar18;
        }
        iVar3 = uVar18 - uVar11;
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }

        // 400 = 0x191
        if (400 < iVar3) {
          uVar11 = uVar18;
        }

		int posX = uVar11 + 5;
		int posY = 0x66;

		#ifdef USE_NEW2P
		if(numPlyr == 2)
		{
			posX = 0xF4;
			posY = ((uVar11 + 5) * 0xd8) / 0x200;
		}
		#endif

        DECOMP_DecalHUD_DrawPolyGT4(
          gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[iVar14]].iconID],
		  posX, posY,

          // pointer to PrimMem struct
          &gGT->backBuffer->primMem,

          // pointer to OT memory
          gGT->pushBuffer_UI.ptrOT,

          // color data
          local_30, local_30, local_30, local_30,

          TRANS_50_DECAL, 0x9d8); // 0x9d8 = 8/13

        *puVar16 = uVar11;
        puVar16 = puVar16 + 1;
      }

	  for (
	  	warpballThread = gGT->threadBuckets[TRACKING].thread;
	  	warpballThread != 0;
	  	warpballThread = warpballThread->siblingThread
	  )
	  {
	  	// Get Instance from Thread
	  	warpballInst = warpballThread->inst;

	  	// if not warpball, skip
	  	if (warpballInst->model->id != 0x36)
	  		continue;

	  	// pointer to path data
	  	struct CheckpointNode* cn = gGT->level1->ptr_restart_points;

	  	struct TrackerWeapon* tw = warpballInst->thread->object;

	  	iVar4 = tw->nodeCurrIndex;
	  	iVar12 = 0;

	  	if (gGT->level1->cnt_restart_points < 1) continue;
	  	if (iVar4 < 0) continue;

	  	int pos[4];
	  	pos[0] = warpballInst->matrix.t[0];
	  	pos[1] = warpballInst->matrix.t[1];
	  	pos[2] = warpballInst->matrix.t[2];

	  	struct CheckpointNode* cn1 = &cn[tw->ptrNodeCurr->nextIndex_forward];
	  	struct CheckpointNode* cn2 = &cn[cn1->nextIndex_forward];

#ifndef REBUILD_PC
	  	short vec1[4];
	  	vec1[0] = cn1->pos[0] - cn2->pos[0];
	  	vec1[1] = cn1->pos[1] - cn2->pos[1];
	  	vec1[2] = cn1->pos[2] - cn2->pos[2];
	  	MATH_VectorNormalize(&vec1[0]);

	  	short vec2[4];
	  	vec2[0] = pos[0] - cn1->pos[0];
	  	vec2[1] = pos[1] - cn1->pos[1];
	  	vec2[2] = pos[2] - cn1->pos[2];

	  	// replace R11R12 and R13R21
	  	gte_ldsvrtrow0(&vec1[0]);

	  	// required short
	  	gte_ldv0(&vec2[0]);

	  	gte_mvmva(0,0,0,3,0);

	  	// replace stMAC1
	  	gte_stlvnl0(&iVar15);
#endif

	  	iVar3 = cn1->distToFinish * 8 + (iVar15 >> 0xc);
	  	iVar15 = gGT->level1->ptr_restart_points[0].distToFinish * 8;
	  	iVar12 = iVar3 % iVar15;

	  	#if 0
	  	if (uVar1 == 0) trap(0x1c00);
	  	if ((iVar15 == -1) && (iVar3 == -0x80000000)) trap(0x1800);
	  	#endif

	  	iVar15 = gGT->level1->ptr_restart_points[0].distToFinish * 8;
	  	iVar12 = iVar15 - iVar12;
	  	iVar15 = iVar15 / 0x1d1;

	  	#if 0
	  	if (iVar15 == 0) trap(0x1c00);
	  	if ((iVar15 == -1) && (iVar12 == -0x80000000)) trap(0x1800);
	  	#endif

		int posX = (iVar12 / iVar15) + 5;
		int posY = 0x66;

		#ifdef USE_NEW2P
		if(numPlyr == 2)
		{
			posX = 0xF4;
			posY = (((iVar12 / iVar15) + 5) * 0xd8) / 0x200;
		}
		#endif

	  	DECOMP_DecalHUD_DrawWeapon(
	  	// warpball icon
	  	gGT->ptrIcons[0xe],
	  	posX, posY,

	  	// pointer to PrimMem struct
	  	&gGT->backBuffer->primMem,

	  	// pointer to OT memory
	  	gGT->pushBuffer_UI.ptrOT,

	  	TRANS_50_DECAL, FP(2/3) - FP(1/8), 1);
	  }
	}
}