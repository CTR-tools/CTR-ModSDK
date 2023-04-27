#include <common.h>

void AH_WarpPad_ThTick(struct Thread* t);
void AH_WarpPad_ThDestroy(struct Thread* t);

void AH_WarpPad_LInB(struct Instance* inst)
{
	int i;
	int levelID;
	struct Thread* t;
	struct WarpPad* warppadObj;
	
    t =	
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct WarpPad), 
				NONE, 
				MEDIUM, 
				WARPPAD
			), 
			
			AH_WarpPad_ThTick,	// behavior
			0,					// debug name
			0					// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	t->funcThDestroy = AH_WarpPad_ThDestroy;
	t->modelIndex = 0;
	
	// make invisible
	// this is the red triangle 
	// instance from DCxDemo's LEV Viewer
	inst->flags |= 0x80;
	
	warppadObj = t->object;
	warppadObj->levelID = 0;
	warppadObj->boolEnteredWarppad = 0;
	warppadObj->framesWarping = 0;
	
	// each warppad has a name "warppad#xxx"
	// "warppad#0" is dingo canyon, level ID 0
	// "warppad#16" is slide col, level ID 16
	// "warppad#102" is gem cup 2
	// "warppad#104" is gem cup 4
	// etc
	
	levelID = 0;
	for(i = 8; inst->name[i] != 0; i++)
	{
		levelID = levelID * 10 + inst->name[i] - '0';
	}
		
	warppadObj->levelID = levelID;
	
	// temporary
	for(i = 0; i < WPIS_NUM_INSTANCES; i++)
		warppadObj->inst[i] = 0;
}