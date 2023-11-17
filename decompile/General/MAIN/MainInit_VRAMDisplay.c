#include <common.h>

void DECOMP_MainInit_VRAMDisplay()
{
	RECT r;
	DR_MOVE move;
	
	short x[2];
	short y[2];

#ifdef REBUILD_PC
	PsyX_BeginScene();
#endif

	x[0] = 0;
	x[1] = 0x100;
	
	y[0] = 0;
	y[1] = 0x128;

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			r.x = x[i] + 0x200;
			r.y = 0x10c;
			r.w = 0x100;
			r.h = 0xd8;
			
			SetDrawMove(
				&move, &r, 
				x[i], y[j]
			);
			
			move.tag |= 0xffffff;
			
			DrawOTag(&move);
			DrawSync(0);
		}
	}

#ifdef REBUILD_PC
	PsyX_EndScene();
#endif
}