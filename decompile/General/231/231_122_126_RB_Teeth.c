#include <common.h>

void DECOMP_RB_Teeth_LInB(struct Instance* inst)
{	
  inst->unk50 += 2;
  
  // If in relic race
  if ((sdata->gGT->gameMode1 & RELIC_RACE) != 0) 
  {
	// enable access through a door (disable collision)
    sdata->doorAccessFlags |= 1;
	
	// Make invisible
    inst->flags |= HIDE_MODEL;
  }
  return;
}

void DECOMP_RB_Teeth_BSP_Callback(struct ScratchpadStruct* sps,struct Thread* weaponThread)
{
  short model;
  struct Thread* teethTh;
  struct Instance* weaponInst;
  struct Instance* teethInst;
  int distance;
  
  model = weaponThread->modelIndex;
  
  // if not driver
  if (model != DYNAMIC_PLAYER) 
  {
    if (model < DYNAMIC_SMALL_BOMB) 
	{
	  // if not nitro
      if (model != PU_EXPLOSIVE_CRATE) {
        return;
      }
    }
    else 
	{
	  // if not potion or tnt
      if ((model != DYNAMIC_POISON) && (model != STATIC_CRATE_TNT)) {
        return;
      }
    }
  }
  
  teethTh = sps->Union.ThBuckColl.thread;
  
  weaponInst = weaponThread->inst;
  
  teethInst = teethTh->inst;
  
  if ((weaponInst != NULL) && (teethInst != NULL)) {
    distance = ((int)sps->Input1.pos[0] - weaponInst->matrix.t[0]) * (int)teethInst->matrix.m[0][2] +
            ((int)sps->Input1.pos[2] - weaponInst->matrix.t[2]) * (int)teethInst->matrix.m[2][2];

	// catch negative value
    if (distance < 0) {
      distance = -distance;
    }

    if ((distance >> 0xc) > 0x100) {
      return;
    }
  }
  
  // door is open
  ((struct Teeth*)teethTh->object)->direction = 1;
  
  return;
}

void DECOMP_RB_Teeth_ThTick(struct Thread* t)
{
  int doorTimeCount;
  struct Teeth* teeth;
  struct Instance* doorInst;
  struct GameTracker* gGT;
  
  gGT = sdata->gGT;
  teeth = t->object;
  doorInst = t->inst;
  
  struct ScratchpadStruct* SPS = (struct ScratchpadStruct*)0x1f800108;
  
  // if door is not moving
  if (teeth->direction == 0) 
  {
	// if timer is zero
    if (teeth->timeOpen == 0) goto LAB_800b9ff8;
    
	// reduce timer by milliseconds
	doorTimeCount = teeth->timeOpen - gGT->elapsedTimeMS;
    
	// set new timer
	teeth->timeOpen = doorTimeCount;
    
	// if timer is up
	if (doorTimeCount < 1) 
	{
	  // play sound
	  // teeth closing
      PlaySound3D(0x75,doorInst);
      
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
    doorInst->animFrame += teeth->direction;
	
    doorTimeCount = VehFrameInst_GetNumAnimFrames((struct Driver*)doorInst, 0);
	
	// if animation is not on last frame
    if ((int)doorInst->animFrame < doorTimeCount) 
	{
	  // if animation when backwards past beginning
      if ((int)doorInst->animFrame < 0) 
	  {
		// set animation to beginning
        doorInst->animFrame = 0;
		
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
      doorInst->animFrame = FPS_DOUBLE((short)(doorTimeCount -1));
	  
	  // door is not moving (fully open)
      teeth->direction = 0;
	  
	  // timer
      teeth->timeOpen = SECONDS(2);
    }
LAB_800b9fe8:
    if (teeth->timeOpen == 0) {
LAB_800b9ff8:
      if (teeth->direction > -1) goto LAB_800ba084;
    }
  }
  
  // Teeth instance position
  SPS->Input1.pos[0] = doorInst->matrix.t[0];
  SPS->Input1.pos[1] = doorInst->matrix.t[1];
  SPS->Input1.pos[2] = doorInst->matrix.t[2];
  
  SPS->Input1.hitRadius = 0x300;
  SPS->Input1.hitRadiusSquared = 0x90000;
  
  SPS->Input1.modelID = STATIC_TEETH;
  
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
	doorInst->flags &= ~(HIDE_MODEL);
  }

  // if a timer is active
  // (fully open)
  else 
  {
	// make invisible
    doorInst->flags |= HIDE_MODEL;
  }
  
  return;
}

int DECOMP_RB_Teeth_LInC(struct Instance *teethInst, struct Thread *t, struct ScratchpadStruct* sps)
{
    int distance;
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

        teethTh = PROC_BirthWithObject(
		          SIZE_RELATIVE_POOL_BUCKET(
		              sizeof(struct Teeth),
		              NONE,
		              SMALL,    
		              STATIC),
		          DECOMP_RB_Teeth_ThTick, 0, 0);

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
    if (sps->Input1.modelID == DYNAMIC_PLAYER)
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
        distance =
            ((int)sps->Input1.pos[0] - teethInst->matrix.t[0]) * (int)teethInst->matrix.m[0][2] +
            ((int)sps->Input1.pos[2] - teethInst->matrix.t[2]) * (int)teethInst->matrix.m[2][2];

        if (distance < 0)
        {
            distance = -distance;
        }
        if ((distance >> 0xc) < 0x81)
        {
            return 1;
        }
        return 2;
    }
    return 2;
}

struct InstDef* DECOMP_RB_Teeth_OpenDoor(struct Instance* inst)
{
	struct Thread* teethTh = inst->thread;
	struct Teeth* templeDoor = (struct Teeth*)teethTh->object;
	
	if (teethTh == NULL) {
    
		//ghidra output says third arg to PROC_BirthWithObject is s_teeth_OVR_231__800b9de8, idk the equivalent.
		teethTh = PROC_BirthWithObject(		
		          SIZE_RELATIVE_POOL_BUCKET(
		              sizeof(struct Teeth),
		              NONE,
		              SMALL,
		              STATIC),
		          DECOMP_RB_Teeth_ThTick, NULL, NULL);
		
		inst->thread = teethTh;
		if (teethTh == NULL)
			return NULL;
		
		teethTh->inst = inst;
		
		templeDoor->timeOpen = 0;
	}
	
	PlaySound3D(0x75, inst); // play sound, teeth opening
	templeDoor->direction = 1; // door is open
	sdata->doorAccessFlags |= 1; // enable access through a door (disable collision)
	
	//return (struct Instance*)&DAT_80090000;
	return (struct InstDef*)0x80090000; //todo: make this a reference to named memory
}