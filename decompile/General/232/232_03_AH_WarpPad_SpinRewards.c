#include <common.h>

void AH_WarpPad_SpinRewards(
	struct Instance* prizeInst,
	struct WarpPad* warppadObj,
	int index,
	int x, int y, int z)
{
	short* specLight;
	unsigned int modelID;
	unsigned int trig;
	unsigned int thirds;
	
	ConvertRotToMatrix(
		&prizeInst->matrix, 
		&warppadObj->spinRot_Prize[0]);
		
	modelID = prizeInst->model->id;
	
	// no specLight on trophy
	if(CheckModelID(modelID, STATIC_TROPHY)) 
		goto SpinReward;
	
	// gem
	else if(CheckModelID(modelID, STATIC_GEM)) 
		specLight = &warppadObj->specLightGem[0];
	
	// relic
	else if(CheckModelID(modelID, STATIC_RELIC)) 
		specLight = &warppadObj->specLightRelic[0];
	
	// token
	else if(CheckModelID(modelID, STATIC_TOKEN)) 
		specLight = &warppadObj->specLightToken[0];
	
	Vector_SpecLightSpin3D(
		prizeInst, 
		&warppadObj->spinRot_Prize[0], 
		specLight);
	
SpinReward:

	// initialized as 0x555*index, but not const
	thirds = warppadObj->thirds[index];

	trig = MATH_Sin(thirds);
	prizeInst->matrix.t[1] = y + ((trig<<6)>>0xc) + 0x100;
	
	// do not use original "thirds",
	// set new value without "+="
	thirds = 0x555*index + warppadObj->spinRot_Rewards[1];
	
	trig = MATH_Sin(thirds);
	prizeInst->matrix.t[0] = x + (trig * 0xA0 >> 0xc);
	
	trig = MATH_Cos(thirds);
	prizeInst->matrix.t[2] = z + (trig * 0xA0 >> 0xc);

}