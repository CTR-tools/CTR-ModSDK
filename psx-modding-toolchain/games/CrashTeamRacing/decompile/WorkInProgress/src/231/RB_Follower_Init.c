#include <common.h>

void RB_Follower_ThTick(struct Thread*);

void DECOMP_RB_Follower_Init(struct Driver* d, struct Thread* t)
{
  struct Instance* iVar1;
  struct Thread* tVar2;
  void* obj;
  struct Instance* iVar3;
  
  if (
		(
			(0x1e00 < d->speedApprox) && 
			
			// if driver is not an AI
			((d->actionsFlagSet & 0x100000) == 0)
		 &&
		((sdata->gGT->cameraDC[d->driverID].flags) & 0x10000) == 0)
	) 
  {	 
	// create a thread and an Instance
    iVar1 = INSTANCE_BirthWithThread(t->modelIndex,s_data->s_follower, SMALL, FOLLOWER, RB_Follower_ThTick,0x18,0);
    
	// if that worked successfully
	if (iVar1 != NULL) 
	{
	  // set the scale
      iVar1->scale[0] = 0x200;
      iVar1->scale[1] = 0x200;
      iVar1->scale[2] = 0x200;
	  
	  // get instance from thread
      iVar3 = t->inst;
	  
	  // copy position and rotation from one instance to another 
      iVar1->matrix.m[0][0] = iVar3->matrix.m[0][0];
      iVar1->matrix.m[0][2] = iVar3->matrix.m[0][2];
      iVar1->matrix.m[1][1] = iVar3->matrix.m[1][1];
      iVar1->matrix.m[2][0] = iVar3->matrix.m[2][0];
      iVar1->matrix.m[2][2] = iVar3->matrix.m[2][2];
      
      iVar1->matrix.t[0] = iVar3->matrix.t[0];
      iVar1->matrix.t[1] = iVar3->matrix.t[1];
      iVar1->matrix.t[2] = iVar3->matrix.t[2];
	  
	  // Get the thread
      tVar2 = iVar1->thread;
	  
	  // set funcThDestroy to remove instance from instance pool
      tVar2->funcThDestroy = THREAD_DestroyInstance;
      
	  // get the object attached to the thread
	  obj = tVar2->object;
	  
	  // thread lasts 7 frames
      obj[0] = 7;
	  
	  // driver
      obj[1] = d;
	  
	  // thread
      obj[2] = t;
	  
	  // thread -> timesDestroyed (it's used???)
      obj[3] = *(undefined4 *)(t + 0x20);
	  
	  // save position of driver
      *(int *)((int)obj + 0x10) = iVar3->matrix.t[0];
      *(int *)((int)obj + 0x12) = iVar3->matrix.t[1];
      *(int *)((int)obj + 0x14) = iVar3->matrix.t[2];
    }
  }
  return;
}