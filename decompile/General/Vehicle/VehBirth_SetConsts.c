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
	
	int engineID = 
		data.MetaDataCharacters
			[data.characterIDs[driver->driverID]].engineID;

	// Not using this special event
	#if 0
		#ifdef USE_ONLINE
		// Wednesday max stats
		if(octr->special == 2) engineID = 4;
		#endif
	#endif

	for(i = 0; i < 65; i++)
	{
		metaPhys = &data.metaPhys[i];

		metaPhysSize = metaPhys->size;
		
		void* src = &metaPhys->value[engineID];
		void* dst = &d[metaPhys->offset];

		if (metaPhysSize == 1)
		{
			*(char*)dst = *(char*)src;
			continue;
		}
		
		if (metaPhysSize == 2)
		{
			*(short*)dst = *(short*)src;
			continue;
		}
		
		*(int*)dst = *(int*)src;
	}

	return;
}