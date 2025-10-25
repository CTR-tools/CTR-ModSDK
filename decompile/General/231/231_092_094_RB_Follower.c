#include <common.h>

void DECOMP_RB_Follower_ProcessBucket(struct Thread* t)
{
	int i;
	int numPlyr;
	int driverID;
	struct Follower* fObj;
	struct Instance* inst;
	struct InstDrawPerPlayer* idpp;
	struct GameTracker* gGT = sdata->gGT;

	numPlyr = gGT->numPlyrNextGame;

	for(/**/; t != 0; t = t->siblingThread)
	{
		// skip dead threads
		if((t->flags & 0x800) != 0) continue;

		fObj = t->object;
		driverID = fObj->driver->driverID;

		inst = t->inst;
		idpp = INST_GETIDPP(inst);

		// make Follower invisible to all other players
		for(i = 0; i < numPlyr; i++)
			if(i != driverID)
				idpp[i].instFlags &= ~(0x40);

		// make Mine invisible to this player
		inst = fObj->mineTh->inst;
		idpp = INST_GETIDPP(inst);
		idpp[driverID].instFlags &= ~(0x40);
	}
}

void DECOMP_RB_Follower_ThTick(struct Thread* t)
{
	int kartState;
	struct Driver* d;
	struct Follower* fObj;
	struct Instance* inst;

	inst = t->inst;
	fObj = t->object;
	d = fObj->driver;
	kartState = d->kartState;

	fObj->frameCount--;

	if(
			(fObj->frameCount > 0) &&
			(
				(kartState == KS_NORMAL) ||
				(kartState == KS_DRIFTING)
			) &&

			// terrible way of checking if mineTh was destroyed
			// before the follower thread was destroyed
			(fObj->mineTh->timesDestroyed == fObj->backupTimesDestroyed) &&

			(d->speedApprox > -1)
		)
	{
		if(inst->scale[0] < 0x800)
		{
			inst->scale[0] = inst->scale[0] << 1;
			inst->scale[1] = inst->scale[1] << 1;
			inst->scale[2] = inst->scale[2] << 1;
		}

		// midpoint between real mine position, and driver position
		inst->matrix.t.x = (fObj->realPos.x + (d->posCurr.x>>8)) >> 1;
		inst->matrix.t.y = (fObj->realPos.y + (d->posCurr.y>>8)) >> 1;
		inst->matrix.t.z = (fObj->realPos.z + (d->posCurr.z>>8)) >> 1;

		return;
	}

	// kill thread
	t->flags |= 0x800;
}

void DECOMP_RB_Follower_Init(struct Driver* d, struct Thread* mineTh)
{
  struct Thread* t;
  struct Instance* followerInst;
  struct Follower* fObj;
  struct Instance* mineInst;

  // disable for slow speed
  if (d->speedApprox <= 0x1e00) return;

  // disable for AI
  if ((d->actionsFlagSet & 0x100000) != 0) return;

  #ifdef USE_ONLINE
  if(d->driverID != NULL) return;
  #endif

  // disable for airborne camera
  if (((sdata->gGT->cameraDC[d->driverID].flags) & 0x10000) != 0) return;

  // create a thread and an Instance
  followerInst = INSTANCE_BirthWithThread(
  	mineTh->modelIndex, 0, SMALL, FOLLOWER,
  	DECOMP_RB_Follower_ThTick, sizeof(struct Follower), 0);

  if (followerInst == NULL) return;

  // followerInst scale
  followerInst->scale[0] = 0x200;
  followerInst->scale[1] = 0x200;
  followerInst->scale[2] = 0x200;

  // mineInst
  mineInst = mineTh->inst;

  // copy position and rotation from one instance to another
  *(int*)&followerInst->matrix.m[0][0] = *(int*)&mineInst->matrix.m[0][0];
  *(int*)&followerInst->matrix.m[0][2] = *(int*)&mineInst->matrix.m[0][2];
  *(int*)&followerInst->matrix.m[1][1] = *(int*)&mineInst->matrix.m[1][1];
  *(int*)&followerInst->matrix.m[2][0] = *(int*)&mineInst->matrix.m[2][0];
  followerInst->matrix.m[2][2] = mineInst->matrix.m[2][2];

  t = followerInst->thread;
  t->funcThDestroy = PROC_DestroyInstance;

  fObj = t->object;
  fObj->frameCount = FPS_DOUBLE(7);
  fObj->driver = d;
  fObj->mineTh = mineTh;
  fObj->backupTimesDestroyed = mineTh->timesDestroyed;

  // backup original position


  	followerInst->matrix.t.x = mineInst->matrix.t.x;
	fObj->realPos.x = mineInst->matrix.t.x;
  	
	followerInst->matrix.t.y = mineInst->matrix.t.y;
	fObj->realPos.y = mineInst->matrix.t.y;
	
	followerInst->matrix.t.z = mineInst->matrix.t.z;
	fObj->realPos.z = mineInst->matrix.t.z;
  
}