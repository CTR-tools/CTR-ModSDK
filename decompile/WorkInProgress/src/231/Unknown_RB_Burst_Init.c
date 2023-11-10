#include <common.h>

void DECOMP_RB_Burst_Init(struct Instance* inst)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Instance* currInst;
  struct Thread* t;
  struct ModelHeader* currHeaders;
  int *piVar4;
  int * burst;
  unsigned short local_40;
  char *local_3c;
  unsigned short local_38;
  unsigned short local_34;
  code *local_30;
  unsigned short local_2c;
  unsigned short local_28;
  
  burst = inst->thread->object;
  
  // initialize thread for burst
  currInst = INSTANCE_BirthWithThread(0x2b, sdata->s_explosion1, SMALL, BURST, RB_Burst_ThTick, 0xc,0);
  
  // get thread from instance
  t = currInst->thread;
  
  // get object from thread
  piVar4 = t->object;
  
  piVar4[1] = currInst;
  *(char *)(currInst + 0x50) += -2;
  currInst->matrix.t[0] = inst->matrix.t[0];
  currInst->matrix.t[1] = inst->matrix.t[1] + -0x30;
  currInst->matrix.t[2] = inst->matrix.t[2];
  
  // if more than 2 screens
  if (2 < gGT->numPlyrCurrGame) 
  {
	// divide scale by 2
     currInst->scale[0] = currInst->scale[0] >> 1;
    currInst->scale[1] = currInst->scale[1] >> 1;
    currInst->scale[2] = currInst->scale[2] >> 1;
  }
  
  // set rotation to identity matrix
  currInst->matrix.m[0][0] = 0x1000;
  currInst->matrix.m[0][2] = 0;
  currInst->matrix.m[1][1] = 0x1000;
  currInst->matrix.m[2][0] = 0;
  currInst->matrix.m[2][2] = 0x1000;
  
  currHeaders = currInst->model->headers;
  
  // always face camera
  currHeaders->flags |= 2;
  
  currInst = INSTANCE_Birth3D(gGT->modelPtr[0x2b],sdata->s_explosion2,t);
  
  piVar4[2] = currInst;
  
  // instance flags
  currInst->flags |= 0x2000000;
  
  *(char *)(currInst + 0x50) += -2;
  
  // X position
  currInst->matrix.t[0] = inst->matrix.t[0];
  
  // Y position
  currInst->matrix.t[1] = inst->matrix.t[1] + -0x30;
  
  // Z position
  currInst->matrix.t[2] = inst->matrix.t[2];
  
  // if more than 2 screens
  if (2 < gGT->numPlyrCurrGame) 
  {
	// scale (x, y, z)
    currInst->scale[0] = currInst->scale[0] >> 1;
    currInst->scale[1] = currInst->scale[1] >> 1;
    currInst->scale[2] = currInst->scale[2] >> 1;
  }
  
  currInst->matrix.m[0][0] = 0;
  currInst->matrix.m[0][1] = 0xf000;
  currInst->matrix.m[0][2] = 0;
  currInst->matrix.m[1][0] = 0x1000;
  currInst->matrix.m[1][1] = 0;
  currInst->matrix.m[1][2] = 0;
  currInst->matrix.m[2][0] = 0;
  currInst->matrix.m[2][1] = 0;
  currInst->matrix.m[2][2] = 0x1000;
  
  currHeaders = currInst->model->headers;
  
  // always face camera
  currHeaders->flags |= 2;
  
  currInst = INSTANCE_Birth3D(gGT->modelPtr[0x44],sdata->s_shockwave1,t);
  
  piVar4[0] = currInst;
  
  // instance flags
  currInst->flags |= 0x2040000;
  
  *(char *)(currInst + 0x50) += -2;
  
  currInst->matrix.t[0] = inst->matrix.t[0];
  currInst->matrix.t[1] = inst->matrix.t[1] + -0x30;
  currInst->matrix.t[2] = inst->matrix.t[2];
  
  // if more than two screens
  if (2 < gGT->numPlyrCurrGame) 
  {
	// set scale (x, y, z)
    currInst->scale[0] = currInst->scale[0] >> 1;
    currInst->scale[1] = currInst->scale[1] >> 1;
    currInst->scale[2] = currInst->scale[2] >> 1;
  }
  
  // identity matrix
  currInst->matrix.m[0][0] = 0x1000;
  currInst->matrix.m[0][2] = 0;
  currInst->matrix.m[1][1] = 0x1000;
  currInst->matrix.m[2][0] = 0;
  currInst->matrix.m[2][2] = 0x1000;
  
  currHeaders = currInst->model->headers;
  
  // always face camera
  currHeaders->flags |= 2;
  
  currHeaders = currInst->model->headers; // ???

  *(unsigned short *)(currInst + 0x56) |= 2;
  
  DAT_1f800108 = inst->matrix.t[0];
  DAT_1f80010a = inst->matrix.t[1];
  DAT_1f80010c = inst->matrix.t[2];
  
  // missile
  if (inst->model->id == 0x29) 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x80;
    DAT_1f800110 = 0x4000;
  }
  else 
  {
    if ((inst->thread->object + 0x16) & 1 == 0)
	{
	  // hitRadius and hitRadiusSquared
      DAT_1f80010e = 0x140;
      DAT_1f800110 = 0x19000;
    }
    else 
	{
	  // hitRadius and hitRadiusSquared
      DAT_1f80010e = 0x200;
     DAT_1f800110 = 0x40000;
    }
  }
  
  DAT_1f800130 = RB_Burst_CollThBucket;
  
  // instance -> thread
  DAT_1f800120 = inst->thread;
  
  // instance -> model -> modelID
  DAT_1f800114 = inst->model->id;
  
  // check collision with all Player thread
 
  THREAD_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER].thread,&DAT_1f800108,

  // burst->driverParent(?)->instSelf->thread
  *(unsigned short *)(*(int *)(*(int *)(burst + 4) + 0x1c) + 0x6c));

  // check collision with all Robotcar thread
  THREAD_CollideHitboxWithBucket(gGT->threadBuckets[ROBOT].thread,&DAT_1f800108,

  // burst->driverParent(?)->instSelf->thread
  *(unsigned short *)(*(int *)(*(int *)(burst + 4) + 0x1c) + 0x6c));
			   
  // check collision with all Mine thread
  THREAD_CollideHitboxWithBucket(gGT->threadBuckets[MINE].thread,&DAT_1f800108,0);
  
  // check collision with all Tracking thread
  THREAD_CollideHitboxWithBucket(gGT->threadBuckets[TRACKING].thread,&DAT_1f800108,0);
  
  // RB_Burst_CollLevInst (callback for BSP collision)
  DAT_1f800130 = RB_Burst_CollLevInst;
  
  THREAD_StartSearch_Self(&DAT_1f800108);
  return;
}