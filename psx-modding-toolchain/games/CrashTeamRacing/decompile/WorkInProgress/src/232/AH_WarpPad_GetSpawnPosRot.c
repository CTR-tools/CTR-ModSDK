#include <common.h>

int* DECOMP_AH_WarpPad_GetSpawnPosRot(short *param_1)
{
  struct Thread* bucket;
  struct Instance* inst;
  int ratio;
  
  // loop through all warppad threads in thread bucket
  bucket = &sdata->gGT->threadBuckets[5];
  
  while(true) 
  {
	// if next thread is not found
    if (bucket->next == 0) 
	{
	  // quit
      return 0;
    }
	
    inst = bucket->inst;
	
	// If a warppad is found that belongs to the previous level
    if (bucket->inst->thread == sdata->gGT->prevLEV)
	{
		// then run the second half of the function
		break;
	}

	// go to next warppad
    bucket = bucket->siblingThread;
  }
  
  // cosine (instance -> instDef -> rotY)
  ratio = MATH_Cos(inst->instDef->rot[1]);
  param_1[0] = inst->matrix.t[0] + (short)((ratio << 10) >> 0xc);
  param_1[1] = inst->matrix.t[1];
  
  // sine (instance -> instDef -> rotY)
  ratio = MATH_Sin(inst->instDef->rot[1]);
  param_1[2] = inst->matrix.t[2] + (short)(ratio * -0x400 >> 0xc);
  
  return &inst->instDef->rot[0];
}