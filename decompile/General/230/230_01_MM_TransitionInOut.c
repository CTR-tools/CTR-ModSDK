#include <common.h>

unsigned char DECOMP_MM_TransitionInOut(struct TransitionMeta* meta, int framesPassed, int numFrames)
{
	unsigned char bool_Transitioning;
	short start;
	short framesLeft;
	
	bool_Transitioning = 1;
	start = meta->headStart;
	framesLeft = ((short)framesPassed - start);

    if (framesLeft == FPS_DOUBLE(4))
    {
        // Play "swoosh" sound for menu transition
        DECOMP_OtherFX_Play(0x65, 0);
    }

	// last member of array is null-terminated with 0xFFFF
	for(/**/; start > -1; meta++)
	{
		start = meta->headStart;
		framesLeft = ((short)framesPassed - start);
		
		if (framesLeft < 1)
		{
			bool_Transitioning = 0;
			meta->currX = 0;
			meta->currY = 0;
			continue;
		}

		// else if
		if (framesLeft < (short)numFrames)
		{
			bool_Transitioning = 0;
			meta->currX = framesLeft * meta->distX / (short)numFrames;
			meta->currY = framesLeft * meta->distY / (short)numFrames;
			continue;
		}

		// else
		meta->currX = meta->distX;
		meta->currY = meta->distY;
	}
	return bool_Transitioning;
}