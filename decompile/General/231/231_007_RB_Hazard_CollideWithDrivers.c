#include <common.h>

struct Instance* DECOMP_RB_Hazard_CollideWithDrivers(
	struct Instance* weaponInst, char boolCanSkipParent, 
	int hitRadius, struct Instance* mineDriverInst
)
{
	int i;
	int j;
	struct Driver* driver;
	struct Instance* driverInst;
	
	int dist[3];
	int modelID;
	
	int distCheck;
	
	for(int i = 0; i < 8; i++)
	{
		driver = sdata->gGT->drivers[i];
		
		if(driver == 0) continue;
		if(driver->kartState == KS_MASK_GRABBED) continue;
		driverInst = driver->instSelf;
		
		if (
		
			// if mine can skip parent
			(boolCanSkipParent != 0) &&
			
			// then do not check parent
			(driverInst == mineDriverInst)
			)
		{
			continue;
		}
		
		for(j = 0; j < 3; j++)
		{
			dist[j] = driverInst->matrix.t[j] - weaponInst->matrix.t[j];
			dist[j] *= dist[j];
		}
		
		modelID = weaponInst->model->id;
		
		// 2D collision (barrel, warpball)
		distCheck = dist[0] + dist[2];
		
		// to be more optimal, just do weaponInst->thread->funcThTick == GenericMine_ThTick
		if (
				((unsigned int)modelID - 0x46 < 2) ||	// red or green potion
				(modelID == PU_EXPLOSIVE_CRATE) ||						// Nitro
				(modelID == STATIC_CRATE_TNT) 						// TNT
			)
		{
			// upgrade to 2D collision to 3D sphere
			distCheck += dist[1];
		}
		  
		// 2D collision, or 3D sphere
		if(distCheck < hitRadius)
		{
			// wasted check for 3D sphere,
			// also upgrades 2D collision to 3D cylinder
			if( dist[1] < ( hitRadius << 2 ) )
			{
				return driverInst;
			}
		}
	}
	
	return 0;
}