#include <common.h>

unsigned char DECOMP_MM_TransitionInOut(unsigned short* meta, int framesPassed, int numFrames)
{
	unsigned char bool_Transitioning;
	unsigned short start;
	unsigned short framesLeft;
	unsigned short *puVar4;
	unsigned short loop;
	
	bool_Transitioning = 1;
	loop = 0;
	start = meta[2];
	if (start > -1)
	{
		puVar4 = meta + 2;
		do
		{
            framesLeft = ((short)framesPassed - start);
			if (framesLeft < 1)
			{
				bool_Transitioning = 0;
				puVar4[1] = 0;
				puVar4[2] = 0;
			}
			else
			{
                if ((framesLeft == 4) && (loop == 0)) 
                {
                    // Play "swoosh" sound for menu transition
                    OtherFX_Play(0x65, 0);
                }
				if (framesLeft < (short)numFrames)
				{
					bool_Transitioning = 0;
					start = framesLeft * puVar4[-1] / (short)numFrames;
					puVar4[1] = framesLeft * meta[0] / (short)numFrames;
				}
				else
				{
					start = puVar4[-1];
					puVar4[1] = meta[0];
				}
				puVar4[2] = start;
			}
			puVar4 += 5;
			meta += 5;
			start = *puVar4;
			loop++;
		} while (-1 < *puVar4);
	}
	return bool_Transitioning;
}