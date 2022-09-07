#include <common.h>

void DECOMP_Driver_SetConsts(struct Driver * driver)
{
	u_int metaPhysSize;
	u_int i;
	struct MetaPhys * metaPhys;
	u_char * d;

	d = (u_char *)driver;

	for(i = 0; i < 65; i++)
	{
		metaPhys = &data.metaPhys[i];

		// Get the size of the variable
		metaPhysSize = metaPhys->size;

		// If variable size == 2 bytes
		if (metaPhysSize == 2)
		{
			*(u_short *)&d[metaPhys->DriverOffset] = metaPhys->value[data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID];
		}

		// if variable size != 2 bytes
		else
		{

			// if variable size < 3 bytes
			if (metaPhysSize < 3)
			{
				// If variable size == 1 byte
				if (metaPhysSize == 1)
				{
					*(u_char *)&d[metaPhys->DriverOffset] = metaPhys->value[data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID];
				}
			}

			// if variable size >= 3 bytes
			else
			{
				if (metaPhysSize == 4)
				{
					*(u_int *)&d[metaPhys->DriverOffset] = metaPhys->value[data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID];
				}
			}
		}
	}

	return;
}