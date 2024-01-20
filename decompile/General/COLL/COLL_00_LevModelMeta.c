#include <common.h>

void* DECOMP_COLL_LevModelMeta(unsigned int id)
{
	// use unsigned so -1 is positive
	if(id >= 0xe2) id = 0;
	
	return &data.MetaDataModels[id];
}