#include <common.h>

void DECOMP_AH_Map_HubArrow(
	Vec2* pos, 
	short* arrowPos, char* arrowCol,
	int unk800, int angle)
{
	short local_30 [6];
	short local_20 [6];
	
	struct GameTracker* gGT = sdata->gGT;
	
	int sin = DECOMP_MATH_Sin(angle);
	int cos = DECOMP_MATH_Cos(angle);
	
	for(int i = 0; i < 3; i++)
	{
		local_30[i*2+0] =
			pos->x + 6 +
			(short)((
				(
					((arrowPos[2*i+0] * cos) >> 0xc) +
					((arrowPos[2*i+1] * sin) >> 0xc)
				) * ((unk800 * 8) / 5)
			
			) >> 0xc);
			
		local_30[i*2+1] =
			pos->y + 4 +
			(short)((
				(
					((arrowPos[2*i+1] * cos) >> 0xc) -
					((arrowPos[2*i+0] * sin) >> 0xc)
				) * unk800
			
			) >> 0xc);
	}
	
	short* offset = &D232.primOffsetXY_HubArrow[0];
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			local_20[j*2+0] = 
			local_30[j*2+0] + offset[i*2+0];
			
			local_20[j*2+1] = 
			local_30[j*2+1] + offset[i*2+1];
		}
		
		DECOMP_RECTMENU_DrawRwdTriangle(
			&local_20[0], arrowCol,
			gGT->pushBuffer_UI.ptrOT,
			&gGT->backBuffer->primMem);
		
		arrowCol = (char*)&D232.colorTri[0];
	}
}