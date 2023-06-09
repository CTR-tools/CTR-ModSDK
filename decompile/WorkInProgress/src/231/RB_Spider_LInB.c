#include <common.h> 

void RB_Spider_ThTick(struct Thread*);

void RB_Spider_ThCollide(int param1, int param_2, int param_3, struct ScratchpadStruct* param_4)
{ 
  // check if modelID is player
  // modelID is 0xc of BSP meta
  
  return (u_int)(param_4->Input1.modelID == 0x18);
}

void DECOMP_RB_Spider_LInB(struct Instance* spiderInst)
{
  struct Thread* spiderTh;
  struct Instance* inst;
  struct Spider* spider;
  short rot[3];
  
  // If this instance has no thread
  if (spiderInst->thread == 0) 
  {
    
	// b95e4
	// "spider"
	// 
	// 0x10 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0xa = "spider" thread bucket
    spiderTh = THREAD_BirthWithObject(0x10030a,RB_Spider_ThTick,0x800b95e4,0);
	
	// give thread to instance
    spiderInst->thread = spiderTh;
	
	// if thread built successfully
    if (spiderTh != NULL) 
	{
	  // get object created with thread
      spider = spiderTh->object;
	  
	  // set funcThCollide, to make player spin out
      spiderTh->funcThCollide = RB_Spider_ThCollide;
	  
	  // give instance to thread
      spiderTh->inst = spiderInst;
	  
	  // set scale (x,y,z)
      spiderInst->scale[0] = 0x1c00;
      spiderInst->scale[1] = 0x1c00;
      spiderInst->scale[2] = 0x1c00;
	  
	  // set animation to 1
      spiderInst->animIndex = 1;
	  
	  // spiderID
      spider->spiderID = (u_short)*(char *)(strlen(spiderInst->name) + (spiderInst + 7)) - 0x30;
	  
	  // spider is near roof
      spider->boolNearRoof = 1;
	  
	  // reset animation loop counter
      spider->animLoopCount = 0;
	  
	  // depending on spiderID, set delay,
	  // three different cycles total
	  
      if (spider->spiderID == 3) {
        spider->delay = 0x5b;
      }
      else {
        if (spider->spiderID == 2) {
          spider->delay = 0x45;
        }
        else {
          spider->delay = 0;
        }
      }
	  
      inst = INSTANCE_Birth3D(sdata->gGT->modelPtr[0x52], s_spidershadow_800b95ec,spiderTh);
	  
	  
	  // copy position and rotation from one instance to another
      inst->matrix.m[0][0] = spiderInst->matrix.m[0][0];
      inst->matrix.m[0][2] = spiderInst->matrix.m[0][2];
      inst->matrix.m[1][1] = spiderInst->matrix.m[1][1];
      inst->matrix.m[2][0] = spiderInst->matrix.m[2][0];
      inst->matrix.m[2][2] = spiderInst->matrix.m[2][2];

      // x, y, z
      inst->matrix.t[0] = spiderInst->matrix.t[0];
      inst->matrix.t[1] = spiderInst->matrix.t[1] - 8;
      inst->matrix.t[2] = spiderInst->matrix.t[2];
	  // Scale (x, y, z)
      inst->scale[0] = 0x2000;
      inst->scale[1] = 0x2000;
      inst->scale[2] = 0x2000;
      
      rot[0] = 0;
      rot[1] = 0;
      rot[2] = 0x200;
	  
	   // convert 3 rotation shorts into rotation matrix
      ConvertRotToMatrix(&inst->matrix,&rot);

      spider->inst = inst;
	  
      spiderInst->matrix.t[2] += 0x4c0;
    }
  }
  return;
}