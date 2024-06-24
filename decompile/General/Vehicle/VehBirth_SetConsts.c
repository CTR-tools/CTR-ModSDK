#include <common.h>

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
#endif

void DECOMP_VehBirth_SetConsts(struct Driver* driver)
{
	u_int metaPhysSize;
	u_int i;
	struct MetaPhys* metaPhys;
	u_char* d;

	d = (u_char*)driver;

	int engineID;

	// Doesn't work this way, kept pulling the wrong engine
	// So far only modifying global MetaData works correctly
	#ifdef USE_ENGINESWAP
		//engineID = octr->engines[driver->driverID]; 
	else
		engineID = data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID;
	#endif
	

	for (i = 0; i < 65; i++)
	{
		metaPhys = &data.metaPhys[i];
		metaPhysSize = metaPhys->size;
		void *src = &metaPhys->value[engineID];
		void *dst = &d[metaPhys->offset];

#ifdef USE_ONLINE
		short override = 0;
		// Moon Mode
		if ((i == 0) && (octr->special == 1))
			override = 450; // Gravity halved
		// Mega Drifts
		if ((i == 8) && (octr->special == 2))
			override = -120; // Negative DriftFriction
		// Reverse Day
		if ((i == 11) && (octr->special == 3))
			override = -0x6400; // Negative Speed

		if (override != 0)
			src = &override; // Point src to override if override is not zero
#endif

		if (metaPhysSize == 1)
		{
			*(char *)dst = *(char *)src;
		}
		else if (metaPhysSize == 2)
		{
			*(short *)dst = *(short *)src;
		}
		else
		{
			*(int *)dst = *(int *)src;
		}
	}

	return;
}