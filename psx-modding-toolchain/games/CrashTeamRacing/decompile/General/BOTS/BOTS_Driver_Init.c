#include <common.h>

struct Driver* BOTS_Driver_Init(int driverID)
{
	int pathIndex;
	int numPoints;
	int i;
	struct Thread* t;
	struct Driver* d;
	
	// take default
	pathIndex = sdata->driver_pathIndexIDs[driverID];
	numPoints = sdata->NavPath_ptrHeader[pathIndex]->numPoints;
	
	// if invalid path
	if(numPoints == 0)
	{
		// check all paths
		for(i = 0; i < 3; i++)
		{
			// quit loop when found
			if(sdata->NavPath_ptrHeader[i]->numPoints != 0) 
			{
				// when is one path valid, but another invalid?
				// maybe just left over from early betas?
				while(1) {}
			}
		}
		
		// dont spawn driver
		// will happen on Nitro Court
		return 0;
	}
	
	// path data found
	 
	t = THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Driver), 
				NONE, 
				LARGE, 
				ROBOT
			), 
			
			BOTS_ThTick_Drive,	// behavior
			0,					// debug name
			0					// thread relative
		);
		
	d = t->object;
	memset(d, 0x0, 0x62C);
	Init_NonGhost_Driver(t, driverID);
	sdata->gGT->drivers[driverID] = d;
	t->modelIndex = 0x3f;
	
	// [0x5a4, 0x5b8 not in common.h]
	// [&DAT_8008daf8] unknown use
	
	// [need to finish]
}