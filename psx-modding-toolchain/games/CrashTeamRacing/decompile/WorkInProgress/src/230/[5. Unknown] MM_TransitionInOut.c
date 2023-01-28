#include <common.h>

u_int DECOMP_MM_TransitionInOut(u_short *param_1, int param_2, short numFrames)
{
	u_char bVar1;
	u_short uVar2;
	int iVar3;
	u_short *puVar4;
	int iVar5;
	short sVar6;
	
	bVar1 = 1;
	sVar6 = 0;
	uVar2 = param_1[2];
	if ((short)param_1[2] > -1)
	{
		iVar5 = (int)numFrames;
		puVar4 = param_1 + 2;
		do
		{
			if (((int)((param_2 - (u_int)uVar2) * 0x10000) >> 0x10 == 4) && (sVar6 == 0)) 
			{
				// Play "swoosh" sound for menu transition
				OtherFX_Play(0x65, 0);
			}
			iVar3 = (int)((param_2 - (u_int)uVar2) * 0x10000) >> 0x10;
			if (iVar3 < 1)
			{
				bVar1 = 0;
				puVar4[1] = 0;
				puVar4[2] = 0;
			}
			else
			{
				if (iVar3 < iVar5)
				{
					uVar2 = (u_short)((iVar3 * (short)puVar4[-1]) / iVar5);
					bVar1 = 0;
					puVar4[1] = (u_short)((iVar3 * (short)*param_1) / iVar5);
				}
				else
				{
					uVar2 = puVar4[-1];
					puVar4[1] = *param_1;
				}
				puVar4[2] = uVar2;
			}
			puVar4 = puVar4 + 5;
			param_1 = param_1 + 5;
			uVar2 = *puVar4;
			sVar6 = sVar6 + 1;
		} while (-1 < (short)*puVar4);
	}
	return (u_int)bVar1;
}