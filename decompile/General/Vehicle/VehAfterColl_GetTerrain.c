#include <common.h>

struct Terrain* DECOMP_VehAfterColl_GetTerrain(u_char terrainType)
{
	struct Terrain* ter = &data.MetaDataTerrain[0];
	
    if (terrainType < 0x15)
		return &ter[terrainType];
	
	return ter;
}
