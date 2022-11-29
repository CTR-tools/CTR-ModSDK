#include <common.h>

struct Instance* RB_Hazard_CollideWithDrivers(
	struct Instance* weaponInst, 
	bool canHitParent, int hitRadius, struct Instance* mineDriverInst
)
{
	int i;
	int j;
	struct Driver* driver;
	struct Driver* driverInst;
	
	int dist[3];
	int modelID;
	
	int distCheck;
	
	for(int i = 0; i < 8; i++)
	{
		driver = sdata.gGT->drivers[i];
		
		// skip invalid drivers
		if(driver == 0) continue;
		
		// skip invincible drivers
		if(driver->kartState == 5) continue;
		
		driverInst = driver->instSelf;
		
		if (
		
			// if mine can not hit parent
			(canHitParent == 0) &&
			
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
		
		modelID = weaponInst->modelID;
		
		// 2D collision (barrel, warpball)
		distCheck = dist[0] + dist[2];
		
		// to be more optimal, just do weaponInst->thread->funcPerFrame == Mine_Generic_PerFrame
		if (
				((unsigned int)(modelID - 0x46) < 2) ||	// red or green potion
				(modelID == 6) ||						// Nitro
				(modelID == 0x27) 						// TNT
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
			if( distY < ( hitRadius << 2 ) )
			{
				return driverInst;
			}
		}
	}
	
	return 0;
}