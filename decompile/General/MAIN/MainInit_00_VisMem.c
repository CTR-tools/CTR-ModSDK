#include <common.h>

void DECOMP_MainInit_VisMem(struct GameTracker* gGT) {
    
	struct VisMem* visMem = gGT->level1->visMem;
	if(visMem == NULL) return;

	gGT->visMem1 = visMem;
}