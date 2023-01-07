#include <common.h>

// full disclosure:
// no idea if this function works, can't tell the difference
// between returning a thread, or returning nullptr, and the
// code was changed a lot to make it fit the byte budget

// search starts with driver thread's child
// searches for turbo model
struct Thread* THREAD_SearchForModel(struct Thread* th, int modelID)
{
	struct Thread* other;

	// if found, quit
	if(th->modelIndex == modelID) return th;

	// check children recursively, quit if found
	if(th->childThread == 0) return 0;
	other = THREAD_SearchForModel(th->childThread, modelID);
	if(other != 0) return other;

	if(th->siblingThread == 0) return 0;
	return THREAD_SearchForModel(th->siblingThread, modelID);
}