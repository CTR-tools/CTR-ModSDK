#include <common.h>

void DECOMP_PROC_CheckAllForDead()
{
	int i;
	
	struct ThreadBucket* tb = &sdata->gGT->threadBuckets[0];
	
	for(i = 0; i < NUM_BUCKETS; i++)
	{
		DECOMP_PROC_CheckBloodlineForDead(&tb[i].thread, tb[i].thread);
	}
}