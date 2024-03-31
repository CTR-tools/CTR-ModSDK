#include <common.h>

// Budget: 336/436 bytes

struct Driver* DECOMP_BOTS_Driver_Init(int driverID)
{
	int pathIndex;
	int numPoints;
	int i;
	struct Thread* t;
	struct Driver* d;
	struct GameTracker *gGT = sdata->gGT;
	
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
	 
	t = PROC_BirthWithObject
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
	VehBirth_NonGhost(t, driverID);
	gGT->drivers[driverID] = d;
	t->modelIndex = DYNAMIC_ROBOT_CAR;
	
	d->botPath = i;
	d->botNavFrame = sdata->NavPath_ptrNavFrameArray[i];
	d->actionsFlagSet |= 0x100000;
	LIST_AddFront(&sdata->unk_NavRelated[i], (struct Item*)(&d->unk598));
	
	gGT->numBotsNextGame++;
	BOTS_GotoStartingLine(d);
	return d;
}