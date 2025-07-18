#include <common.h>

void DECOMP_AH_WarpPad_SpinRewards(
	struct Instance* prizeInst,
	struct WarpPad* warppadObj,
	int index,
	int x, int y, int z)
{
	short* specLight;
	unsigned int modelID;
	unsigned int trig;
	unsigned int thirds;
	
	// converted to TEST in rebuildPS1
	ConvertRotToMatrix(
		&prizeInst->matrix, 
		&warppadObj->spinRot_Prize[0]);
		
	modelID = prizeInst->model->id;
	
	// OG code had pointers to warppadObj->specLightXXX
	// but that was replaced with pointers to globals,
	// because the arrays didnt actually change per warppad

	//this was re-rewritten because the original rewrite had incorrect behavior
	if (modelID != STATIC_TROPHY) //if not trophy (no specLight on trophy)
	{
		if (modelID == STATIC_GEM) //gem
			specLight = &D232.specLightGem[0];
		else
		{
			if (modelID == STATIC_RELIC) //relic
				specLight = &D232.specLightRelic[0];
			else
			{
				if (modelID == STATIC_TOKEN) //token
					specLight = &D232.specLightToken[0];
				else
					goto SpinReward;
			}
		}
#ifndef REBUILD_PS1
		Vector_SpecLightSpin3D(
			prizeInst,
			&warppadObj->spinRot_Prize[0],
			specLight);
#endif
	}

SpinReward:

	// initialized as 0x555*index, but not const
	thirds = warppadObj->thirds[index];

	trig = DECOMP_MATH_Sin(thirds);
	prizeInst->matrix.t[1] = y + ((trig<<6)>>0xc) + 0x100;
	
	// do not use original "thirds",
	// set new value without "+="
	thirds = 0x555*index + warppadObj->spinRot_Rewards[1];
	
	trig = DECOMP_MATH_Sin(thirds);
	prizeInst->matrix.t[0] = x + (trig * 0xA0 >> 0xc);
	
	trig = DECOMP_MATH_Cos(thirds);
	prizeInst->matrix.t[2] = z + (trig * 0xA0 >> 0xc);
}