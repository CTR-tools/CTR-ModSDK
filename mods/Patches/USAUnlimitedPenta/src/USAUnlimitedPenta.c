#include <common.h>

// "currently only for UsaRetail, can potentially work in Sep3 too" --Niko

void USAUnlimitedPenta_VehBirth_SetConsts(struct Driver * driver)
{
	u_int metaPhysSize;
	u_int i;
	struct MetaPhys * metaPhys;
	u_char * d;

	d = (u_char *)driver;

	for(i = 0; i < 0x41; i++)
	{
		metaPhys = &data.metaPhys[i];

		// The pre-compiled binary takes out one of the variables in each instance of the MetaPhys struct
		// Because of that we have to reference those starting from unk and ending at size, see the struct on common.h
		// and we also need to treat size as an array, so this is the best we can do
		// oh yeah and the offset (referred to as unk here, because of the above) needs to be subtracted by 4 bytes

		// Get the size of the variable
		metaPhysSize = *(u_int *)&metaPhys->offset;

		switch(metaPhysSize)
		{
			case 1:
				*(u_char *)&d[(int)metaPhys->unusedDebugStr - 4] = *(u_char *)((int)&metaPhys->size + data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID * 4);
				break;
			case 2:
				*(u_short *)&d[(int)metaPhys->unusedDebugStr - 4] = *(u_short *)((int)&metaPhys->size + data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID * 4);
				break;
			case 4:
				*(u_int *)&d[(int)metaPhys->unusedDebugStr - 4] = *(u_int *)((int)&metaPhys->size + data.MetaDataCharacters[data.characterIDs[driver->driverID]].engineID * 4);
				break;
		}
	}

	return;
}