#include <common.h>

struct Instance* DECOMP_INSTANCE_BirthWithThread(
	int modelID, char* name, int poolType, int bucket,
	void* funcThTick, int objSize, struct Thread* parent)
{
	struct GameTracker* gGT;
	struct Model* m;
	struct Thread* t;
	struct Instance* inst;
	
	gGT = sdata->gGT;
	
	m = gGT->modelPtr[modelID];
	
	if(m == 0)
	{
		// June 1999
		// printf("INSTANCE_BirthWithThread: object type %d not found!\n",param_1);
		
		return 0;
	}
	
	// talkingMask is unaligned
	if((objSize & 3) != 0)
	{
		// align down, then add 4 to align up,
		// no object will exceed 0x670 bytes
		objSize = (objSize & 0xffc) + 4;
	}
	
	t = DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				objSize, 
				
				// relation not given directly
				NONE,
				
				// relation included in one of these
				poolType, 
				bucket
			), 
			
			funcThTick,	// behavior
			name,		// debug name
			parent		// thread relative
		);
		
	/*

	June 1999
    if (iVar2 == 0) {
      printf("%s thread create failed (b)\n",param_2);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }

	*/
	
	t->modelIndex = modelID;
	inst = DECOMP_INSTANCE_Birth3D(m, name, t);
	
	/*

    if (iVar3 == 0) {
      printf("%s instance create failed (b)\n",param_2);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }

	*/
	
	t->inst = inst;
	
	return inst;
}