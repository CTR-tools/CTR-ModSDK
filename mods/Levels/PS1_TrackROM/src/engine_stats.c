#include <common.h>

void VehBirth_SetConsts(struct Driver *d)
{
    int stats[4] = {544, 1152, 13900, 15400}; //accel, something, speed, speedometer offset. Divide speed by 256 to know its kph value
    int engineID = data.MetaDataCharacters[data.characterIDs[d->driverID]].engineID;

    for (int i = 0; i < 65; i++)
    {
        int* meta = &data.metaPhys[i];
        int metaOffset = meta[1];
        int metaSize = meta[2];
        int metaValue = meta[3 + engineID];

    	if(i < 13 &&  8 < i)
        {
    		metaValue = stats[i-9];
    	}
        else
        {
        	metaValue = meta[3 + engineID];
        }


        if (metaSize == 2)
        {
            *(short *)((int)d + metaOffset) = (short)(metaValue);
            continue;
        }

        if (metaSize == 1)
        {
            *(char *)((int)d + metaOffset) = (char)(metaValue);
            continue;
        }

        *(int *)((int)d + metaOffset) = (int)(metaValue);
    }
}