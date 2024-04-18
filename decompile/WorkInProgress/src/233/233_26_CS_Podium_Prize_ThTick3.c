#include <common.h>

extern char prizeHintArr[7];

// Lerp position from center of screen to destination
// Then kill thread
void CS_Podium_Prize_ThTick3(struct Thread *th)
{
    short currScale;
    short sVar2;
    int iVar3;
    int iVar5;
    int iVar8;

    struct GameTracker *gGT;
    int hintID;

    // get instance from thread
    struct Instance *inst = th->inst;

    // get object from thread
	// should replace with struct Prize in 233
    int prize = th->object;

    sVar2 = *(short *)(prize + 0x26) - 1;
    *(short *)(prize + 0x26) = sVar2;

    if (sVar2 != 0)
    {
        iVar3 = *(short *)(prize + 0x28);
        iVar8 = sVar2 * (0x100 - *(short *)(prize + 0x10));
        iVar5 = sVar2 * (0x6c - *(short *)(prize + 0x12));

        iVar8 = (*(short *)(prize + 0x10) + iVar8 / iVar3 - 0x100) * -inst->matrix.t[2];

        if (iVar8 < 0)
        {
            iVar8 += 255;
        }

        inst->matrix.t[0] = iVar8 >> 8;

        iVar5 = (*(short *)(prize + 0x12) + iVar5 / iVar3 - 0x6c) * inst->matrix.t[2];

        if (iVar5 < 0)
        {
            iVar5 += 255;
        }

        inst->matrix.t[1] = iVar5 >> 8;

        // shrink scale
        currScale = inst->scale[0] - 1200;

        // set min scale
        if (currScale < 0x1001)
        {
            currScale = 0x1000;
        }

        // scale y and scale z
        inst->scale[0] = currScale;
        inst->scale[1] = currScale;
        inst->scale[2] = currScale;

        CS_Podium_Prize_Spin(inst, prize);
    }

    // Give hints at the end of each race

    // if you do not go to boss cutscene
    if (CS_Boss_BoolShouldStart() == 0)
    {
		int rewards = sdata->advProgress.rewards[4];
		
		char* arr;
		hintID = 0;
		
		// Give Aku Hint at the first 7 podium
		// rewards, teaching how to play
		for(
				arr = &prizeHintArr[0]; 
				arr < &prizeHintArr[7]; 
				arr++
			)
		{
			int index = (int)*arr;
			
			if((rewards & (1 << (index-10))) == 0)
			{
				hintID = index;
				break;
			}
		}
		
		if(hintID != 0)
			DECOMP_MainFrame_RequestMaskHint(hintID, 0);
    }

LAB_800afa68:

    gGT = sdata->gGT;

    // begin the async 232 load
    gGT->overlayTransition = 2;

    // driver now can move
    gGT->gameMode2 &= ~(0x4);

    // Play "Unlock" Sound
    OtherFX_Play(0x67, 1);

    // This thread is now dead
    th->flags |= 0x800;
}

char prizeHintArr[7] =
{
    // Map Information
    // (part of welcome to adv arena)
    24,

    // Wumpa Fruit Hint
    22,

    // TNT Hint
    23,

    // Hang Time Turbo Hint
    14,

    // Power Sliding Hint
    15,

    // Turbo Boost Hint
    16,

	// Brake Sliding Hint
	17
};