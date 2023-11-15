#include <common.h>

void DECOMP_THREAD_CheckAllForDead()
{
	int i;
	
	struct ThreadBucket* tb = &sdata->gGT->threadBuckets[0];
	
	for(i = 0; i < NUM_BUCKETS; i++)
	{
		DECOMP_THREAD_CheckBloodlineForDead(&tb[i].thread, tb[i].thread);
	}
}