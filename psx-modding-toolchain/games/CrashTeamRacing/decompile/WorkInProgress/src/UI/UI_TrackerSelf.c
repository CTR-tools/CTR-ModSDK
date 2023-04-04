#include <common.h>

void DECOMP_UI_TrackerSelf(struct Driver* d)

{
  short sVar1;
  short sVar2;
  short uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short in_zero;
  short in_at;
  int iVar7;
  char* iVar8;
  short *psVar9;
  u_int rgb0, rgb1, rgb2;
  int beep_rate;
  struct GameTracker *gGT = sdata->gGT;
  u_long *primmemCurr;
  POLY_G3 *p;
  short sVar15;
  u_int uVar16;
  int iVar17;
  short sVar18;
  u_short driverid;
  int warpDist;
  int missileDist;
  struct DB* backDB;
  u_int local_30;
  u_int local_2c;
  int local_28;
  short sStack38;

  // get index of driver in driver array
  driverid = d->driverID;

  if (
		// if there is no missile chasing this player
		(d->thTrackingMe == 0) &&

		// this missile has finished chasing this driver ???
		(*(short *)(*(short*)0x800862e8 + driverid * 2) == 0)
	 )
  {
	// clear type of object tracking the player
    *(short *)(*(short*)0x800862f8 + driverid * 2) = 0;

    return;
  }
  warpDist = 0;

  // If no missile or warpball is chasing this driver
  if (d->thTrackingMe == 0) {
    sVar1 = *(short *)(*(short*)0x800862e8 + driverid * 2);
    iVar8 = &data.unk_between_hudStructPtr_menuRow_arcadeEndRace;
  }

  // if a missile or warpball is chasing this driver
  else {
    sVar1 = *(short *)(*(short*)0x800862e8 + driverid * 2);
    iVar8 = &data.unk_between_hudStructPtr_menuRow_arcadeEndRace;
  }

  sVar2 = *(short *)(iVar8[sVar1]);
  sVar1 = *(short *)(iVar8[sVar1 + 1]);

  // RB_GetThread_ClosestTracker (missile or warpball)
  iVar7 = RB_GetThread_ClosestTracker(d);

  if ((iVar7 == 0) && (psVar9 = (short *)(*(short*)0x800862e8 + driverid * 2), *psVar9 == 0))
  {
	// Get data from missile or warpball
	// driver -> trackerInstFollowingMe -> object -> flags ??
    if ((((struct TrackerWeapon*)d->thTrackingMe->object)->flags & 0x10) != 0)
    goto LAB_8004fe8c;
    sVar18 = 0xc;
  }
  
  else {
    if (
			(
				//if 27th bit of Actions Flag set is on (means ?)
				((d->actionsFlagSet & 0x4000000) != 0) &&

				// driver -> trackerInstFollowingMe
				(iVar7 == d->thTrackingMe)
			) ||
      // missile is not chasing this driver
			(psVar9 = (short *)(*(short*)0x800862e8 + driverid * 2), *psVar9 != 0)
		) goto LAB_8004fe8c;

    //turn on 27th bit of Actions Flag set (means ?)
    d->actionsFlagSet |= 0x4000000;
    sVar18 = 8;
  }
  *psVar9 = sVar18;
LAB_8004fe8c:
  iVar17 = driverid * 2;

  // set pointer of the missile or warpball chasing the player
  d->thTrackingMe = iVar7;

  psVar9 = (short *)(*(short*)0x800862e8 + iVar17);
  if (*psVar9 != 0) {
    *psVar9 = *psVar9 + -1;
  }

						// something with X and Y position
  local_30 = CONCAT22(*(short *)d->instSelf->matrix.t[1],
                      *(short *)d->instSelf->matrix.t[0]);

						// something with Z position
  local_2c = local_2c & 0xffff0000 | (u_int)d->instSelf->matrix.t[2];

  // tileView ViewProj
  MATRIX r0 = (MATRIX *)(gGT->tileView[driverid].matrix_ViewProj.m);
  gte_SetRotMatrix(r0);
  gte_SetTransMatrix(r0);
  
  // ldv0
  // put driver pos on GTE
  setCopReg(2,in_zero,local_30);
  setCopReg(2,in_at,local_2c);

  // RTPS - Perspective Transformation (single)
  copFunction(2,0x180001);

  // stsxy
  // get driver screenspace pos
  uVar3 = getCopReg(2,0xe);
  uVar16 = 0xff;

  // if no missile or warpball is chasing this player
  if (d->thTrackingMe == 0) {
    sVar18 = *(short *)(*(short*)0x800862f0 + iVar17);
  }

  // if a missile or warpball is chasing this player
  else
  {
	// get distance between missile and player

    // uVar8 = sqrt(driver->4a4->30->28 << 0)
    missileDist = sqrt(((struct TrackerWeapon*)d->thTrackingMe->object)->distanceToTarget,0);

    missileDist = missileDist / 0x32;
    sVar18 = (short)missileDist;
    *(short *)(*(short*)0x800862f0 + iVar17) = sVar18;

	// beeping gets faster as missile gets closer
	// iVar10 is beeping rate (higher is less beeps)

	// slowest rate, once every 0x1e frames,
	// if missile is more than 0xc9 units away
    beep_rate = 0x1e;

	if (
			// if missile is closer than 0xc9 units
			(beep_rate < 0xc9) &&

			(
				// apply beep once every 5 frames if
				// missile is less than 100 units away
				beep_rate = 5,

				// if missile is more than 100 units
				// and less than 0xc9 units away
				100 < missileDist
			)
		)
	{
	  // beep once every 10 frames
      beep_rate = 10;
    }

	// if the variable was somehow not set
	if (beep_rate == 0)
	{
	  // kill the game
      trap(0x1c00);
    }

    uVar16 = 0xff;

	// play the beeping on certain frames
    if (gGT->timer % beep_rate == 0) {

	  // If game is not paused
      if ((gGT->gameMode1 & 0xf) == 0)
	  {
		// OtherFX_Play "homing in" sound
        OtherFX_Play(0x56,1);
      }

      uVar16 = 0xffffff;
    }

	// if it's a WarpBall
    if (d->thTrackingMe->inst->model->id == 0x36)
	{
	  	// driver -> threadTracking -> object -> pathNodeStart -> pathNodeIndex?
      warpDist = ((*(int*)((struct TrackerWeapon*)d->thTrackingMe->object) + 0x3c) + 6) -

				// LEV -> path [driver -> pathIndex] -> pathNodeIndex (whaaaat)?
               (u_int)
                      (d->unknown_in_FUN_8005ca24[1] * 0xc +
                       ((gGT + 0x160) + 0x14c) + 6) * 8;

	  // if warpball is further in the lap than the driver,
	  // and warpball needs to go around the track
      if (warpDist < 0)
	  {
		// add to distance between warpball and driver
        warpDist = warpDist + (u_int)(((gGT + 0x160) + 0x14c) + 6) * 8;
      }

	  // type of object following driver is a warpball
      *(short *)(*(short*)0x800862f8 + driverid * 2) = 1;
    }

	// if this is not a warpball
	else
	{
	  // type of object is missile, or nothing?
      *(short *)(*(short*)0x800862f8 + driverid * 2) = 0;
    }
  }
  iVar7 = 0;
  
  // driver screenspace x and y
  sStack38 = (short)((u_int)uVar3 >> 0x10);
  local_28 = (short)uVar3;

  // check distance
  if (warpDist < 16000)
  {
    sVar6 = sVar18 + (sVar2 >> 8);
    sVar5 = (short)((int)sVar1 * 7 >> 0xc);
    for (iVar7 = 0; iVar7 < 2; iVar7++) 
    {
      sVar15 = 1;
      if (iVar7 == 0) {
        sVar15 = -1;
      }

      backDB = gGT->backBuffer;

      primmemCurr = backDB->primMem.curr;

	  p = 0;

	  // if curr < near-end
	  if (primmemCurr <= backDB->primMem.endMin100)
	  {
		// increment curr
        backDB->primMem.curr = primmemCurr + 7;
        p = (POLY_G3*)primmemCurr;
      }
      if (p == 0) {
        return;
      }

	  // if tracking object is warpball
      if (*(short *)(*(short*)0x800862f8 + driverid * 2) == 1) 
	  {
		// tracker border colors (blue)
		rgb0 = 0x309c6900;
        
		rgb2 = 0x30ffff00;
      }

	  // if tracking object is missile
      else 
	  {
      // tracker border colors (orange)
        rgb0 = 0x3000699c;
		
        rgb2 = 0x3000ffff;
      }
      
      *(int*)&p->r0 = rgb0;
      *(int*)&p->r1 = 0x30ffffff;
      *(int*)&p->r2 = rgb2;

      sVar4 = sVar15 * sVar6;
      p->x2 = local_28 + sVar4;
      p->y2 = sStack38 + -0xc;
      p->x1 = local_28 + sVar15 * sVar18;
      p->y1 = sStack38 + -0xc;
      p->x0 = local_28 + sVar4;
      p->y0 = sStack38 - (sVar5 + 0xc);

	  // pointer to OTMem (25c-168=0xf4)
      primmemCurr = gGT->tileView[driverid].ptrOT;

      *(int*)p = *primmemCurr | 0x6000000;
      *primmemCurr = (u_int)p & 0xffffff;

      backDB = gGT->backBuffer;

      primmemCurr = backDB->primMem.curr;

      p = 0;

	  // if curr < near-End
	  if (primmemCurr <= backDB->primMem.endMin100)
	  {
		// increment curr
        backDB->primMem.curr = primmemCurr + 7;
        p = (POLY_G3*)primmemCurr;
      }
      if (p == 0) {
        return;
      }

	  // if tracking object is warpball
      if (*(short *)(*(short*)0x800862f8 + driverid * 2) == 1) {
        *(int*)&rgb1 = 0x305b5b00;
		
        *(int*)&rgb0 = 0x30322b01;
		
        *(int*)&rgb2 = 0x30ffbb00;
      }

	  // if tracking object is missile
      else {
        rgb1 = 0x30005b5b;
		
        rgb0 = 0x30012b32;
		
        rgb2 = 0x3000bbff;
      }
      *(int*)&p->r0 = rgb0;
      *(int*)&p->r1 = rgb1;
      *(int*)&p->r2 = rgb2;

      sVar4 = sVar15 * sVar6;
      p->x2 = local_28 + sVar4;
      p->y2 = sStack38 + sVar5 + -0xc;
      p->x1 = local_28 + sVar15 * sVar18;
      p->y1 = sStack38 + -0xc;
      p->x0 = local_28 + sVar4;
      p->y0 = sStack38 + -0xc;

	  // pointer to OTMem (25c-168=0xf4)
      primmemCurr = gGT->tileView[driverid].ptrOT;

      *(int*)p = *primmemCurr | 0x6000000;
      *primmemCurr = (u_int)p & 0xffffff;
    }
  }

  // UI_TrackerBG
  UI_TrackerBG(

			   // missile lock-on icon
			   (gGT->ptrIcons[0x2d]),

			   (int)local_28 - ((int)sVar2 >> 7),
               (int)sStack38 - ((int)sVar1 * 0xf >> 0xb),

			   // pointer to PrimMem struct
			   &gGT->backBuffer->primMem,

				// pointer to OTMem (25c-168=0xf4)
			   gGT->tileView[driverid].ptrOT,
         1,(int)sVar2,(int)sVar1,uVar16);
  return;
}
 