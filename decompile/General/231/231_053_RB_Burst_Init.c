#include <common.h>

void RB_Burst_ThTick();
void RB_Burst_CollLevInst();
void RB_Burst_CollThBucket();

void DECOMP_RB_Burst_Init(struct Instance* weaponInst)
{
  struct GameTracker* gGT = sdata->gGT;
  struct ModelHeader* headers;
  struct Instance* currInst;
  struct Thread* t;
  int* burst;
  
  // initialize thread for burst
  currInst = 
	INSTANCE_BirthWithThread(
		0x2b, 0, SMALL, BURST, 
		RB_Burst_ThTick, 0xc,0);
  
  // get thread from instance
  t = currInst->thread;
  
  // get object from thread
  burst = t->object;
  
  // ====== First Instance =========
  
  burst[1] = currInst;
  currInst->unk50 += -2;
  
  // set rotation to identity matrix
  *(int*)&currInst->matrix.m[0][0] = 0x1000;
  *(int*)&currInst->matrix.m[0][2] = 0;
  *(int*)&currInst->matrix.m[1][1] = 0x1000;
  *(int*)&currInst->matrix.m[2][0] = 0;
  currInst->matrix.m[2][2] = 0x1000;
  
  // set flag to always point to camera
  headers = currInst->model->headers;
  headers[0].flags |= 2;
  
  // ======== Next one ===========
  
  currInst = INSTANCE_Birth3D(gGT->modelPtr[0x2b],0,t);
  
  burst[2] = currInst;
  currInst->unk50 += -2;
  
  // instance flags
  currInst->flags |= 0x2000000;
  
  // rotate 90 degrees
  currInst->matrix.m[0][0] = 0;
  currInst->matrix.m[0][1] = 0xf000;
  currInst->matrix.m[0][2] = 0;
  currInst->matrix.m[1][0] = 0x1000;
  *(int*)&currInst->matrix.m[1][1] = 0;
  *(int*)&currInst->matrix.m[2][0] = 0;
  currInst->matrix.m[2][2] = 0x1000;
  
  // set flag to always point to camera
  headers = currInst->model->headers;
  headers[0].flags |= 2;
  
  // ======= Next One ===========
  
  currInst = INSTANCE_Birth3D(gGT->modelPtr[0x44],0,t);
  
  burst[0] = currInst;
  currInst->unk50 += -2;
  
  // instance flags
  currInst->flags |= 0x2040000;
      
  // set flag to always point to camera
  headers = currInst->model->headers;
  headers[0].flags |= 2;
  headers[1].flags |= 2;
  
  // ======= End of Instance =========
  
  for(int i = 0; /*i < 3*/; i++)
  {
	currInst = burst[i];

	currInst->matrix.t[0] = weaponInst->matrix.t[0];
	currInst->matrix.t[1] = weaponInst->matrix.t[1] + -0x30;
	currInst->matrix.t[2] = weaponInst->matrix.t[2];
	
	// if more than two screens
	if (2 < gGT->numPlyrCurrGame) 
	{
		// set scale (x, y, z)
		currInst->scale[0] = currInst->scale[0] >> 1;
		currInst->scale[1] = currInst->scale[1] >> 1;
		currInst->scale[2] = currInst->scale[2] >> 1;
	}

	// identity matrix (z)
	*(int*)&currInst->matrix.m[2][0] = 0;
	currInst->matrix.m[2][2] = 0x1000;

	if(i == 2)
		break;

	// identity matrix (x, y)
	*(int*)&currInst->matrix.m[0][0] = 0x1000;
	*(int*)&currInst->matrix.m[0][2] = 0;
	*(int*)&currInst->matrix.m[1][1] = 0x1000;
  }
  
  // currInst is burst[2]
  
  // rotate 90 degrees (X -> -Y)
  currInst->matrix.m[0][0] = 0;
  currInst->matrix.m[0][1] = 0xf000;
  currInst->matrix.m[0][2] = 0;
  
  // rotate 90 degrees (Y -> X)
  currInst->matrix.m[1][0] = 0x1000;
  *(int*)&currInst->matrix.m[1][1] = 0;
  
  // ========= Collisions ===========
  
  struct ScratchpadStruct* sps = 0x1f800108;

  // put weapon position on scratchpad
  sps->Input1.pos[0] = weaponInst->matrix.t[0];
  sps->Input1.pos[1] = weaponInst->matrix.t[1];
  sps->Input1.pos[2] = weaponInst->matrix.t[2];
  
  struct TrackerWeapon* tw = 
	weaponInst->thread->object;
  
  int modelID = weaponInst->model->id;
  
  // missile
  if (modelID == 0x29) 
  {
	// hitRadius and hitRadiusSquared
    sps->Input1.hitRadius = 0x80;
    sps->Input1.hitRadiusSquared = 0x4000;
  }
  else 
  {
    if ((tw->flags & 1) == 0)
	{
	  // hitRadius and hitRadiusSquared
      sps->Input1.hitRadius = 0x140;
      sps->Input1.hitRadiusSquared = 0x19000;
    }
    else 
	{
	  // hitRadius and hitRadiusSquared
      sps->Input1.hitRadius = 0x200;
	  sps->Input1.hitRadiusSquared = 0x40000;
    }
  }
    
  sps->Input1.modelID = modelID;
  
  sps->Union.ThBuckColl.thread = weaponInst->thread;
  sps->Union.ThBuckColl.funcCallback = RB_Burst_CollThBucket;
  
  struct Thread* driverTh =
	tw->instParent->thread;
  
  // check collision with all Player thread
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER].thread,sps,driverTh);
  
  // check collision with all Robotcar thread
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[ROBOT].thread,sps,driverTh);
			   
  // check collision with all Mine thread
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[MINE].thread,sps,0);
  
  // check collision with all Tracking thread
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[TRACKING].thread,sps,0);
  
  sps->Union.ThBuckColl.funcCallback = RB_Burst_CollLevInst;
  
  PROC_StartSearch_Self(sps);
  return;
}