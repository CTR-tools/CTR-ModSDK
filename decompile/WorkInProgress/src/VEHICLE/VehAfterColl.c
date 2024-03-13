#include <common.h>

// overbudget by 4 bytes each, how?

void* DECOMP_VehAfterColl_GetSurface(u_int scrubId)
{
    if (6 < scrubId)
    {
        scrubId = 0;
    }
    return &data.MetaDataScrub[scrubId];
}

void* DECOMP_VehAfterColl_GetTerrain(u_char terrainType)
{
    if (20 < terrainType)
    {
        terrainType = 0;
    }
    return &data.MetaDataTerrain[terrainType];
}
