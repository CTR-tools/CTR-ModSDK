#include <common.h>

void DECOMP_MainInit_VisMem(struct GameTracker* gGT) {
    
	struct VisMem* visMem = gGT->level1->visMem;
	if(visMem == NULL) return;

	gGT->visMem1 = visMem;
    for (int i = 0; i < gGT->numPlyrCurrGame; i++) 
	{
        visMem->visLeafSrc[i] = 0;
        visMem->visFaceSrc[i] = 0;
        visMem->visOVertSrc[i] = 0;
        visMem->visSCVertSrc[i] = 0;
    }
}