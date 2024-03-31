#include <common.h>

struct Thread* DECOMP_PROC_BirthWithObject(
	int flags, void* funcThTick, 
	char* name, struct Thread* relativeTh)
{
	int bucketID;
	struct JitPool* allPools; 
	struct JitPool* myPool;
	int index;
	void* object;
	struct Thread* th;
	struct ThreadBucket* tb;
	struct GameTracker* gGT;

	gGT = sdata->gGT;
	
	// get from self
	bucketID = flags & 0xff;
	
	if(relativeTh != 0)
	{
		// get from relativeTh
		bucketID = relativeTh->flags & 0xff;
	}
	
	// quit if bucket is invalid
	if(bucketID >= NUM_BUCKETS) 
	{
		// Sep3:
		// printf("invalid thread bucket %ld \'%s\'\n",bucketID,name);
		return 0;
	}
	
	// TODO: need an array and enum for this
	allPools = &gGT->JitPools.thread;
	
	// 0x100 - largeStackPool	(0x1970) [4]
	// 0x200 - medStackPool		(0x1948) [3]
	// 0x300 - smallStackPool	(0x1920) [2]
	
	// index is now 1,2,3
	index = (flags>>8)&3;
	
	// index is now 4,3,2
	index = 5 - index;
	
	// small, med, large
	myPool = &allPools[index];
	
	// if can't fit in pool
	if ((flags >> 0x10) > (myPool->itemSize-8))
	{
		// Sep3
		// printf("stack size (%ld) too small for statics (%ld) \'%s\'\n",
		//	myPool->itemSize-8, flags >> 0x10, name);
		
		return 0;
	}
	
	// if no threads remain
	if (allPools[0].free.last == 0)
	{
		// sep 3
		// printf("out of threads \'%s\'\n",name);
		return 0;
	}
	
	if (myPool->free.last == 0)
	{
		// sep 3
		// printf("%ld byte stack allocate failed for thread \'%s\'\n",
		//	myPool->itemSize, name);
		return 0;
	}
	
	// === initialize thread ===

	// thread and object
	th = DECOMP_LIST_RemoveFront(&allPools[0].free);
	object = DECOMP_LIST_RemoveFront(&myPool->free);

	th->inst = 0;
	th->funcThDestroy = 0;
	th->funcThCollide = 0;
	th->cooldownFrameCount = 0;
	
	th->name = name;
	th->flags = flags;
	th->funcThTick = funcThTick;
	th->object = (unsigned int)(((unsigned int)object) + 8);

	// if no relative
	if(relativeTh == 0)
	{
		tb = &sdata->gGT->threadBuckets[bucketID];
		
		th->childThread = 0;
		th->parentThread = 0;
		
		// add to linked list
		th->siblingThread = tb->thread;
		tb->thread = th;
		
		return th;
	}
	
	// == relative exists ==
	
	// if sibling
	if((flags & SELF_SIBLING) != 0)
	{
		// share parent
		th->parentThread = relativeTh->parentThread;
		
		// no child
		th->childThread = 0;
		
		// mix between siblings
		th->siblingThread = relativeTh->siblingThread;
		relativeTh->siblingThread = th;
		
		return th;
	}
	
	// == not sibling ==
	
	// if new thread is relative's child (CHILD_BETWEEN)
	// inject between generations
	if((flags & CHILD_BETWEEN) != 0)
	{
		// this thread is the relative's child
		th->parentThread = relativeTh;
		
		// no siblings
		th->siblingThread = 0;
		
		// mix between generations
		th->childThread = relativeTh->childThread;
		relativeTh->childThread = th;
		
		return th;
	}

	// if new thread is relative's child (CHILD_SIBLING)
	// but NOT injecting between generations
	th->parentThread = relativeTh;
	
	// no child
	th->childThread = 0;
	
	// mix between siblings
	th->siblingThread = relativeTh->childThread;
	relativeTh->childThread = th;
	
	return th;
}

// == This function was relocated due to byte budget ==

// search starts with driver thread's child
// searches for turbo model
struct Thread* DECOMP_PROC_SearchForModel_InsideBirthWithObject(struct Thread* th, int modelID)
{
	struct Thread* other;

	while(th != 0)
	{
		// if found, quit
		if(th->modelIndex == modelID) return th;

		// check children recursively, quit if found
		other = DECOMP_PROC_SearchForModel_InsideBirthWithObject(th->childThread, modelID);
		if(other != 0) return other;

		th = th->siblingThread;
	}
	
	return th;
}