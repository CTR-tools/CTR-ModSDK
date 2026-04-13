#include <common.h>

// temporary
extern struct Ovr233_Credits_BSS* creditsBSS;

// should have parameter, but it's not used
void CS_Credits_ThTick()
{
	int i;
	struct Instance* danceInv;
	struct CreditsObj* creditsObj;
	
	creditsObj = &creditsBSS->creditsObj;
	
	danceInv = creditsBSS->dancerInst_invisible;

	// waste?
	creditsObj->creditDanceInst = danceInv;
	
	if(danceInv != 0)
	{
		// make invisible
		danceInv->flags |= 0x80;
		
		danceInv->matrix.t[0] = creditsBSS->creditGhost_Pos[0];
		danceInv->matrix.t[1] = creditsBSS->creditGhost_Pos[1];
		danceInv->matrix.t[2] = creditsBSS->creditGhost_Pos[2];
		
		// once every 4 frames
		if((sdata->gGT->timer & 3) == 0)
		{
			for(i = 4; i > 0; i--)
			{
				CS_Credits_AnimateCreditGhost(
					creditsObj->creditGhostInst[i], 
					creditsObj->creditGhostInst[i-1], i
				);
				
				creditsObj->creditGhostInst[i] =
				creditsObj->creditGhostInst[i-1];
			}
			
			CS_Credits_AnimateCreditGhost(
				creditsObj->creditGhostInst[0],
				danceInv, i);
				
			creditsObj->creditGhostModel[0] = danceInv->model;
		}
		
		// 3 of 4 frames
		else
		{
			CS_Credits_AnimateCreditGhost(
				creditsObj->creditGhostInst[0],
				danceInv, 0);
			
			for(i = 1; i < 5; i++)
			{
				// this is not danceInv, I'm saving regsiters
				danceInv = creditsObj->creditGhostInst[i];
				
				danceInv->scale[0] += 0x4B;
				danceInv->scale[0] += 0x4B;
				danceInv->scale[0] += 0x4B;
				danceInv->alphaScale += 0x9d;
			}
		}
	}
	
	if (creditsObj->countdown > 0)
		creditsObj->countdown--;
	
	CS_Credits_DrawNames(creditsObj);
	CS_Credits_DrawEpilogue(creditsObj);
}
