#include <common.h>

void DECOMP_AH_Map_HubArrowOutter(
	struct Map* hubPtrs, int arrowIndex,
	Vec2* pos,
	int inputAngle, int type)
{
	struct GameTracker* gGT;
	gGT = sdata->gGT;

	pos->x += D232.hubArrowXY_Inner[2*type+0];
	pos->y += D232.hubArrowXY_Inner[2*type+1];

	int timer = gGT->timer >> FPS_RIGHTSHIFT(0);

	int colorR;
	int colorG;
	int var8;

	colorG = 0x40;
	if((timer & 1) != 0)
		colorG = 0xe0;

	if(type == 0)
	{
		colorR = colorG;
		var8 = 0x200;
	}

	else if(type == 1)
	{
		colorR = 0xff;
		var8 = 0x555;

		pos->x += D232.hubArrowXY_Outter[2*(((inputAngle>>0x8)&0xc)>>2)+0];
		pos->y += D232.hubArrowXY_Outter[2*(((inputAngle>>0x8)&0xc)>>2)+1];
	}

	else
	{
		colorR = colorG;
		var8 = 0x199;

		// needed?
		// param_5._0_2_ = (ushort)param_5 ^ 0x800;
	}

	for(int iVar10 = 0; iVar10 < 3; iVar10++)
	{
		unsigned int var5 =
			(~(timer + (int)arrowIndex * 0xc) & 0x3f) +
			(2 - (int)(short)iVar10) * -6;

		if (var5 >= 0xc)
			continue;

		int iVar16 =
			((var5 * 0x2aa + 0x1000) * 0x10000) >> 0x1a;
        
		#if 0
		int bVar1 = 1;
		#endif


        int iVar6 = 0;
        int iVar9 = 0;

		for(int iVar13 = 0; iVar13 < var8+0xfff; iVar13 += var8)
		{
			if(type != 2)
				var5 = 0;

			int angle = iVar13 + inputAngle;

			int sin = DECOMP_MATH_Sin(angle);
			int cos = DECOMP_MATH_Cos(angle);

			int iVar4 = (var5 & 1) + 0xc;

			sin = pos->x + ((((iVar16 << 3) / 5) * sin) >> iVar4);
			cos = pos->y - ((((iVar16     )    ) * cos) >> iVar4);
            
			#if 0 //unused ?
			if(!bVar1)
			{
				DECOMP_CTR_Box_DrawWirePrims(
					(Point){iVar9, iVar6}, (Point){sin, cos},
					MakeColor(colorR, colorG, 0xff),
					(void*)gGT->pushBuffer_UI.ptrOT);
			}
			
            
			bVar1 = 0;
			#endif
			
			iVar9 = sin;
			iVar6 = cos;
			var5++;
		}
	}
}