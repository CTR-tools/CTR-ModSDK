#include <common.h>

struct Terrain* DECOMP_VehAfterColl_GetTerrain(u_char terrainType)
{
	struct Terrain* ter = &data.MetaDataTerrain[0];
	
	// if terrain is valid
    if (terrainType <= TERRAIN_SLOWDIRT) //20
		return &ter[terrainType];
		
	return ter;
}
