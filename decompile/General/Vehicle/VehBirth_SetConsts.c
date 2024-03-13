#include <common.h>

void DECOMP_VehBirth_SetConsts(struct Driver* driver)
{
	u_int metaPhysSize;
	u_int i;
	struct MetaPhys * metaPhys;
	u_char * d;

	d = (u_char *)driver;

	for(i = 0; i < 65; i++)
	{
		metaPhys = &data.metaPhys[i];

		metaPhysSize = metaPhys->size;
		
		void* src = &metaPhys->value[data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID];
		void* dst = &d[metaPhys->DriverOffset];

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