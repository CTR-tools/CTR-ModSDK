#include <common.h>

void DECOMP_AH_Map_LoadSave_Full(
	int posX, int posY, 
	short* vertPos, char* vertCol,
	int unk800, int angle)
{
	short local_30 [8];
	short local_20 [8];
	
	struct GameTracker* gGT = sdata->gGT;
	
	int sin = DECOMP_MATH_Sin(angle);
	int cos = DECOMP_MATH_Cos(angle);
	
	for(int i = 0; i < 4; i++)
	{
		local_30[i*2+0] =
			posX + 6 +
			(short)((
				(
					((vertPos[2*i+0] * cos) >> 0xc) +
					((vertPos[2*i+1] * sin) >> 0xc)
				) * ((unk800 * 8) / 5)
			
			) >> 0xc);
			
		local_30[i*2+1] =
			posY + 4 +
			(short)((
				(
					((vertPos[2*i+1] * cos) >> 0xc) -
					((vertPos[2*i+0] * sin) >> 0xc)
				) * unk800
			
			) >> 0xc);
	}
	
	short* offset = &D232.primOffsetXY_LoadSave[0];
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			local_20[j*2+0] = 
			local_30[j*2+0] + offset[i*2+0];
			
			local_20[j*2+1] = 
			local_30[j*2+1] + offset[i*2+1];
		}
		
		DECOMP_AH_Map_LoadSave_Prim(
			&local_20[0], vertCol,
			gGT->pushBuffer_UI.ptrOT,
			&gGT->backBuffer->primMem);
		
		vertCol = &D232.colorQuad[0];
	}
}