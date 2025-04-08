#include <common.h>

struct Driver* DECOMP_BOTS_Driver_Init(int driverID)
{
	struct Thread* t;
	struct Driver* d;

	char initialNavPathIndex = sdata->driver_pathIndexIDs[driverID];
	char navPathIndex;
	short navPathPointsCount;// = sdata->NavPath_ptrHeader[navPathIndex]->numPoints;

	navPathIndex = initialNavPathIndex;
	while(1)
	{
		navPathPointsCount = sdata->NavPath_ptrHeader[navPathIndex]->numPoints;
		if (1 < navPathPointsCount) break; //success
		
		navPathIndex--;
		
		// If subtracted below zero,
		// go back to highest index (2)
		if (navPathIndex < 0)
			navPathIndex = 2;
		
		// If all 3 are checked, quit
		if (navPathIndex == initialNavPathIndex)
			return NULL;
	}

	// path data found
	t = DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Driver), //sizeof (struct Driver) == 1584, and yet original code implies size should be 1580?
				NONE, 
				LARGE, 
				ROBOT
			), 
			
			BOTS_ThTick_Drive,	// behavior
			0, //"robotcar",	// debug name
			0					// thread relative
		);
		
	d = t->object;
	memset(d, 0x0, sizeof(struct Driver));
	DECOMP_VehBirth_NonGhost(t, driverID);
	sdata->gGT->drivers[driverID] = d;
	t->modelIndex = DYNAMIC_ROBOT_CAR;
	
	d->botData.botPath = navPathIndex;
	d->botData.botNavFrame = sdata->NavPath_ptrNavFrameArray[navPathIndex];
	d->actionsFlagSet |= 0x100000;
	DECOMP_LIST_AddFront(&sdata->navBotList[navPathIndex], (struct Item*)(&d->botData));
	
	sdata->gGT->numBotsNextGame++;
	BOTS_GotoStartingLine(d);
	return d;
}