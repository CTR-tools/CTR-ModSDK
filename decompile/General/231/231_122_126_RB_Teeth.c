#include <common.h>

void DECOMP_RB_Teeth_OpenDoor();

void DECOMP_RB_Teeth_LInB(struct Instance* inst)
{	
  inst->unk50 += 2;
  
  // If in relic race
  if ((sdata->gGT->gameMode1 & RELIC_RACE) != 0) 
  {
	// enable access through a door (disable collision)
    sdata->doorAccessFlags |= 1;
	
	// Make invisible
    inst->flags |= 0x80;
  }
  return;
}

void DECOMP_RB_Teeth_BSP_Callback(struct ScratchpadStruct* sps,struct Thread* weaponThread)
{
  short model;
  struct Thread* teethTh;
  struct Instance* weaponInst;
  struct Instance* teethInst;
  int iVar5;
  
  model = weaponThread->modelIndex;
  
  // if not driver
  if (model != 0x18) 
  {
    if (model < 0x19) 
	{
	  // if not nitro
      if (model != 6) {
        return;
      }
    }
    else 
	{
	  // if not potion or tnt
      if ((model != 0x1d) && (model != 0x27)) {
        return;
      }
    }
  }
  
  teethTh = sps->Union.ThBuckColl.thread;
  
  weaponInst = weaponThread->inst;
  
  teethInst = teethTh->inst;
  
  if ((weaponInst != NULL) && (teethInst != NULL)) {
    iVar5 = ((int)sps->Input1.pos[0] - weaponInst->matrix.t[0]) * (int)teethInst->matrix.m[0][2] +
            ((int)sps->Input1.pos[2] - weaponInst->matrix.t[2]) * (int)teethInst->matrix.m[2][2];

		// catch negative value
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }

    if (0x100 < iVar5 >> 0xc) {
      return;
    }
  }
  
  // door is open
  ((struct Teeth*)teethTh->object)->direction = 1;
  
  return;
}

void DECOMP_RB_Teeth_ThTick(struct Thread* t)
{
  int iVar1;
  u_int flags;
  struct Teeth* teeth;
  struct Instance* inst;
  struct GameTracker* gGT;
  
  gGT = sdata->gGT;
  teeth = t->object;
  inst = t->inst;

  #define SPS \
	((struct ScratchpadStruct*)0x1f800108)
  
  // if door is not moving
  if (teeth->direction == 0) 
  {
	// if timer is zero
    if (teeth->timeOpen == 0) goto LAB_800b9ff8;
    
	// reduce timer by milliseconds
	iVar1 = teeth->timeOpen - gGT->elapsedTimeMS;
    
	// set new timer
	teeth->timeOpen = iVar1;
    
	// if timer is up
	if (iVar1 < 1) 
	{
	  // play sound
	  // teeth closing
      PlaySound3D(0x75,inst);
      
	  // timer is zero
	  teeth->timeOpen = 0;
	  
	  // door is closing
      teeth->direction = -1;
	  
      goto LAB_800b9fe8;
    }
  }
  
  // if door is moving
  else 
  {
	// modify animation index by direction
    inst->animFrame = inst->animFrame + teeth->direction;
	
    iVar1 = VehFrameInst_GetNumAnimFrames(inst,0);
	
	// if animation is not on last frame
    if ((int)inst->animFrame < iVar1) 
	{
	  // if animation when backwards past beginning
      if ((int)inst->animFrame < 0) 
	  {
		// set animation to beginning
        inst->animFrame = 0;
		
		// door is not moving
        teeth->direction = 0;
		
		// timer is zero
        teeth->timeOpen = 0;
		
		// remove access (enable collision)
        sdata->doorAccessFlags &= 0xfffffffe;
      }
    }
	
	// if animation is on last frame (or past)
    else 
	{
	  // set animation to last frame
      inst->animFrame = (short)iVar1 + -1;
	  
	  // door is not moving (fully open)
      teeth->direction = 0;
	  
	  // timer, 2 seconds 
      teeth->timeOpen = 0x780;
    }
LAB_800b9fe8:
    if (teeth->timeOpen == 0) {
LAB_800b9ff8:
      if (-1 < teeth->direction) goto LAB_800ba084;
    }
  }
  
  // Teeth instance position
  SPS->Input1.pos[0] = inst->matrix.t[0];
  SPS->Input1.pos[1] = inst->matrix.t[1];
  SPS->Input1.pos[2] = inst->matrix.t[2];
  
  SPS->Input1.hitRadius = 0x300;
  SPS->Input1.hitRadiusSquared = 0x90000;
  
  SPS->Input1.modelID = 0x70;
  
  SPS->Union.ThBuckColl.thread = t;
  SPS->Union.ThBuckColl.funcCallback = DECOMP_RB_Teeth_BSP_Callback;
  
  // If door wants to close, but Player or Mine
  // is in the way, then do not force the doors to close
  
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER].thread,SPS,0);
  
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[MINE].thread,SPS,0);
  
LAB_800ba084:

  // if no timer exists
  // (opening, closing, or full closed)
  if (teeth->timeOpen == 0) 
  {
	// make visible
	flags = inst->flags & 0xffffff7f;
  }

  // if a timer is active
  // (fully open)
  else 
  {
	// make invisible
    flags = inst->flags | 0x80;
  }

  inst->flags = flags;
  
  return;
}

int DECOMP_RB_Teeth_LInC(struct Instance *teethInst, struct Thread *t, struct ScratchpadStruct* sps)
{
    int iVar1;
    struct Thread *teethTh;
    struct Teeth *teeth;
    struct Driver *d;

    // This is the door you can shoot in tiger temple

    // If in relic race, ignore the function,
    // there are no weapons to activate door anyways
    if ((sdata->gGT->gameMode1 & RELIC_RACE) != 0)
        return 2;
        
    teethTh = teethInst->thread;
    d = t->object;

    if (teethTh == NULL)
    {
        // 0x8 = size
        // 0 = no relation to param4
        // 0x300 = SmallStackPool
        // 0x3 = "static" thread bucket
        teethTh = PROC_BirthWithObject(0x80303, DECOMP_RB_Teeth_ThTick, 0, 0);

        teethInst->thread = teethTh;

        if (teethTh == NULL)
        {
            return 2;
        }

        teeth = teethTh->object;

        teethTh->inst = teethInst;

        // door not moving
        teeth->direction = 0;

        // timer is zero
        teeth->timeOpen = 0;
    }

    teeth = teethTh->object;

    // if collided object is a player
    if (sps->Input1.modelID == 0x18)
    {
        // if driver is using mask weapon
        if ((d->actionsFlagSet & 0x800000) != 0)
        {
            DECOMP_RB_Teeth_OpenDoor(teethInst);
        }

        return 2;
    }
	
	// If collide with something
	// that is not a player

    // time to close
    if (teeth->timeOpen == 0)
    {
        iVar1 =
            ((int)sps->Input1.pos[0] - teethInst->matrix.t[0]) * (int)teethInst->matrix.m[0][2] +
            ((int)sps->Input1.pos[2] - teethInst->matrix.t[2]) * (int)teethInst->matrix.m[2][2];

        if (iVar1 < 0)
        {
            iVar1 = -iVar1;
        }
        if (iVar1 >> 0xc < 0x81)
        {
            return 1;
        }
        return 2;
    }
    return 2;
}

void DECOMP_RB_Teeth_OpenDoor(struct Instance* inst)
{
  struct Thread* teethTh = inst->thread;
  
  // if there is no thread,
  // just in case it wasn't initialized
  if (teethTh == NULL) 
  {
	
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0x3 = "static" thread bucket
    teethTh = PROC_BirthWithObject(0x80303,DECOMP_RB_Teeth_ThTick,0,0);
	
    inst->thread = teethTh;
	
    if (teethTh == NULL) 
	{
      return;
    }
	
    teethTh->inst = inst;
	
    ((struct Teeth*)teethTh->object)->timeOpen = 0;
  }
  
  // play sound,
  // teeth opening
  PlaySound3D(0x75,inst);
  
  // door is open
  ((struct Teeth*)teethTh->object)->direction = 1;
  
  // enable access through a door (disable collision)
  sdata->doorAccessFlags |= 1;
  
  return;
}