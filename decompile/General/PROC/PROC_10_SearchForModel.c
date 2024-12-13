#include <common.h>

// search starts with driver thread's child
// searches for turbo model
struct Thread* DECOMP_PROC_SearchForModel(struct Thread* th, short modelID)
{
	while (th != 0)
	{
		// if found, quit
		if (th->modelIndex == modelID) return th;

		// check children recursively, quit if found
		struct Thread* other = DECOMP_PROC_SearchForModel(th->childThread, modelID);
		if (other != 0) return other;

		th = th->siblingThread;
	}

	return th;
}