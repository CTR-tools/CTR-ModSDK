#include <common.h>

// relocated
struct Thread* DECOMP_PROC_SearchForModel_InsideBirthWithObject(struct Thread* th, int modelID);

// search starts with driver thread's child
// searches for turbo model
struct Thread* DECOMP_PROC_SearchForModel(struct Thread* th, int modelID)
{
	// inside PROC_BirthWithObject.c,
	// required for the byte budget
	DECOMP_PROC_SearchForModel_InsideBirthWithObject(th, modelID);
}