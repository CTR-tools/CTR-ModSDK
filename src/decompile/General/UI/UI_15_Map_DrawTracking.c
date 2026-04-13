#include <common.h>

void DECOMP_UI_Map_DrawTracking(int ptrMap,struct Thread* bucket)

{
  int uVar1;
  struct Instance* inst;
  struct Driver* d;

  for( /* bucket */ ;
		bucket != 0;
		bucket = bucket->siblingThread
	  )
  {
	// thread -> instance
	inst = bucket->inst;
	
	// instance -> model -> modelID != warpball
	if (inst->model->id != DYNAMIC_WARPBALL) continue;
	
	// == only draw warpball ==
	
	// draw warpball
	DECOMP_UI_Map_DrawRawIcon(
		ptrMap,(int*)&inst->matrix.t[0],
		0x20,0,0,0x1000);
	
	// driver target
	d = ((struct TrackerWeapon*)bucket->object)->driverTarget;
	
	// check if target exists
	if(d == 0) continue;
	
    // == only draw target if target exists ==
	
	// flicker
    uVar1 = 4;
    if ((sdata->gGT->timer & 1) != 0)
      uVar1 = 3;
      
    DECOMP_UI_Map_DrawRawIcon(
	  ptrMap,(int*)&d->instSelf->matrix.t[0],
	  0x21,uVar1,0,0x1000);
  }
  return;
}