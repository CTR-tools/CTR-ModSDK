#include <common.h>

// relocated
struct Thread* DECOMP_THREAD_SearchForModel_InsideBirthWithObject(struct Thread* th, int modelID);

// search starts with driver thread's child
// searches for turbo model
struct Thread* THREAD_SearchForModel(struct Thread* th, int modelID)
{
	// inside THREAD_BirthWithObject.c,
	// required for the byte budget
	DECOMP_THREAD_SearchForModel_InsideBirthWithObject(th, modelID);
}