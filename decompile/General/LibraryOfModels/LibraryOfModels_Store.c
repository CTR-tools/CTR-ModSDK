#include <common.h>

void DECOMP_LibraryOfModels_Store(struct GameTracker* gGT, unsigned int numModels, struct Model** ptrModelArray)
{
	struct Model* m;
	
	// if numModels is -1, then loop until nullptr,
	// that works by using unsigned int
	while(numModels-- != 0)
	{
		m = *ptrModelArray++;
		if(m == 0) return;
		
		// this is not unsigned,
		// if id == -1, dont put it on list
		if(m->id >= 0)
			gGT->modelPtr[m->id] = m;
	}
}