#include <common.h>

void DECOMP_UI_Map_DrawTracking(struct Map* ptrMap,struct Thread* bucket)

{
  unsigned char iconColor;
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
		ptrMap,&inst->matrix.t,
		0x20,0,0,0x1000);
	
	struct TrackerWeapon* tracker = (struct TrackerWeapon*)bucket->object;
	
	// driver target
	d = (struct Driver*)tracker->driverTarget;
	
	// check if target exists
	if(d == NULL) continue;
	
    // == only draw target if target exists ==
	
	// flicker
    iconColor = 4;
    if ((sdata->gGT->timer & 1) != 0)
      iconColor = 3;
      
    DECOMP_UI_Map_DrawRawIcon(
	  ptrMap,&d->instSelf->matrix.t,
	  0x21,iconColor,0,0x1000);
  }
  return;
}