#include <common.h>

void DECOMP_UI_TrackerSelf(struct Driver * d)
{
  short y;
  short x;
  short timer;
  short sVar4;
  short sVar5;
  short sVar6;
  short * ptrAnim;
  u_short driverid;
  short screenPosXY[2];
  u_int rgb0, rgb1, rgb2;
  int warpballDist;
  int missileDist;
  int beep_rate;
  u_long * ot;
  POLY_G3 * p;
  SVECTOR pos;
  struct PrimMem * primMem;
  short orientation;
  u_int bgColor;
  short sVar18;
  int screenPosX;
  short screenPosY;
  struct GameTracker * gGT = sdata->gGT;

  // get index of driver in driver array
  driverid = d->driverID;
  
  timer = data.trackerTimer[driverid];

  if (
		// timer loop ended
		(timer == 0) &&
		
		// no more missile chasing player
		(d->thTrackingMe == 0)
	  )
  {
    // clear type of object tracking the player
    data.trackerType[driverid] = NULL;
    return;
  }

  warpballDist = 0;

  // If no missile or warpball is chasing this driver
  if (d->thTrackingMe == 0) {
    ptrAnim = &data.trackerAnim2[0];
  }
  // if a missile or warpball is chasing this driver
  else {
    ptrAnim = &data.trackerAnim1[0];
  }

  x = ptrAnim[timer*2+0];
  y = ptrAnim[timer*2+1];

  struct Thread* trackerTh = 
	DECOMP_RB_GetThread_ClosestTracker(d);

  if (
		// timer loop ended
		(timer == 0) &&
		
		// no missiles chasing player
		(trackerTh == NULL)
	  ) 
  {
	// trackerWeapon hit intended driverTarget
    if ((((struct TrackerWeapon * ) d->thTrackingMe->object)->flags&0x10) != 0)
      goto LAB_8004fe8c;
  
	// reset timer loop
    sVar18 = FPS_DOUBLE(12);
  } 
  
  // missile chasing player,
  // or dead missile + timer loop active
  else 
  {
    if (
			(
				// if 27th bit of Actions Flag set is on (means ?)
				((d->actionsFlagSet&0x4000000) != 0) &&
				
				// tracker chasing driver
				(trackerTh == d->thTrackingMe)
			) ||
      
			// timer loop active
			(timer != 0)
		)
      goto LAB_8004fe8c;

    // turn on 27th bit of Actions Flag set (means ?)
    d->actionsFlagSet |= 0x4000000;
	
	// reset timer loop
    sVar18 = FPS_DOUBLE(8);
  }

  // reset timer loop
  data.trackerTimer[driverid] = sVar18;

  LAB_8004fe8c:

  // set pointer of the missile or warpball chasing the player
  d->thTrackingMe = trackerTh;

  if (timer != 0) {
    data.trackerTimer[driverid]--;
  }

  MATRIX* m = &gGT->pushBuffer[driverid].matrix_ViewProj;
  gte_SetRotMatrix(m);
  gte_SetTransMatrix(m);

  pos.vx = (short) d->instSelf->matrix.t[0];
  pos.vy = (short) d->instSelf->matrix.t[1];
  pos.vz = (short) d->instSelf->matrix.t[2];

  gte_ldv0(&pos);
  gte_rtps();
  gte_stsxy(&screenPosXY);

  // red?
  bgColor = 0xff;

  // if no missile or warpball is chasing this player
  if (d->thTrackingMe == NULL) {
    sVar18 = data.trackerDist[driverid];
  }

  // if a missile or warpball is chasing this player
  else {
	
	struct TrackerWeapon* tw =
		d->thTrackingMe->object;
	
	#ifndef REBUILD_PS1
    missileDist = 
		VehCalc_FastSqrt(
			tw->distanceToTarget, 0);
    #else
	missileDist = 0;
	#endif
	
	missileDist = missileDist / 0x32;
    sVar18 = (short) missileDist;
    data.trackerDist[driverid] = sVar18;

	beep_rate = FPS_DOUBLE(5);
	if(missileDist > 100) beep_rate = FPS_DOUBLE(10);
	if(missileDist > 200) beep_rate = FPS_DOUBLE(30);

    // red
    bgColor = 0xff;

    if ((gGT->timer % beep_rate) == 0) 
	{
      if ((gGT->gameMode1 & PAUSE_ALL) == 0) 
	  {
        // "homing in" sound
        DECOMP_OtherFX_Play(0x56, 1);
	  }

      // white
      bgColor = 0xffffff;
    }
    
	if (d->thTrackingMe->inst->model->id == DYNAMIC_WARPBALL) 
	{
	  struct CheckpointNode* firstNode =
		&gGT->level1->ptr_restart_points[0];
		
      warpballDist = 
	  (
		(
			tw->ptrNodeCurr->distToFinish -
			firstNode[d->unknown_lap_related[1]].distToFinish

        ) * 8
	  );

      // if warpball is further in the lap than the driver,
      // then add a full lap of distance until warpball hits driver
      if (warpballDist < 0) 
	  {
        // add length of track
        warpballDist += (firstNode[0].distToFinish * 8);
      }

      // type of object following driver is a warpball
      data.trackerType[driverid] = 1;
    }
	
    // if this is not a warpball
    else 
	{
      // type of object is missile, or nothing?
      data.trackerType[driverid] = 0;
    }
  }

  // driver screenspace x and y
  screenPosX = (short)screenPosXY[0];
  screenPosY = (short)screenPosXY[1];

  // check distance
  if (warpballDist < 16000) 
  {
    sVar6 = sVar18 + (x >> 8);
    sVar5 = (short)((y * 7) >> 12);

    for (char i = 0; i < 2; i++) 
	{
      // if left side or right side
      orientation = 1;
      if (i == 0) {
        orientation = -1;
      }

	  primMem = &gGT->backBuffer->primMem;
      p = primMem->curr;

      // if curr < near-end
      if (p <= primMem->endMin100) {
        // increment curr
        primMem->curr = p + 1;
      }

      if (p == 0)
        return;

      // if tracking object is warpball
      if (data.trackerType[driverid] == 1) {
        // tracker border colors (blue)
        rgb0 = 0x309c6900;

        rgb2 = 0x30ffff00;
      }

      // if tracking object is missile
      else {
        // tracker border colors (orange)
        rgb0 = 0x3000699c;

        rgb2 = 0x3000ffff;
      }

      *(int * )&p->r0 = rgb0;
      *(int * )&p->r1 = 0x30ffffff;
      *(int * )&p->r2 = rgb2;

      sVar4 = orientation * sVar6;
      p->x2 = screenPosX + sVar4;
      p->y2 = screenPosY - 12;
      p->x1 = screenPosX + orientation * sVar18;
      p->y1 = screenPosY - 12;
      p->x0 = screenPosX + sVar4;
      p->y0 = screenPosY - (sVar5 + 12);

      ot = gGT->pushBuffer[driverid].ptrOT;

      *(int*) p = *ot | 0x6000000;
      *ot = (u_int) p&0xffffff;

      // next Prim

      p = primMem->curr;

      // if curr < near-End
      if (p <= primMem->endMin100) {
        // increment curr
        primMem->curr = p + 1;
      }

      if (p == NULL)
        return;

      // if tracking object is warpball
      if (data.trackerType[driverid] == 1) {
        rgb1 = 0x305b5b00;

        rgb0 = 0x30322b01;

        rgb2 = 0x30ffbb00;
      }

      // if tracking object is missile
      else {
        rgb1 = 0x30005b5b;

        rgb0 = 0x30012b32;

        rgb2 = 0x3000bbff;
      }

      *(int * )&p->r0 = rgb0;
      *(int * )&p->r1 = rgb1;
      *(int * )&p->r2 = rgb2;

      sVar4 = orientation * sVar6;
      p->x2 = screenPosX + sVar4;
      p->y2 = screenPosY + sVar5 - 12;
      p->x1 = screenPosX + orientation * sVar18;
      p->y1 = screenPosY - 12;
      p->x0 = screenPosX + sVar4;
      p->y0 = screenPosY - 12;

      *(int*)p = *ot | 0x6000000;
      *ot = (u_int) p&0xffffff;
    }
  }

  DECOMP_UI_TrackerBG(

    // missile lock-on icon
    gGT->ptrIcons[0x2d],

    screenPosX - (x >> 7),
    screenPosY - ((y * 0xf) >> 0xb),

	&gGT->backBuffer->primMem,
	gGT->pushBuffer[driverid].ptrOT,
	1, x, y, bgColor);
}