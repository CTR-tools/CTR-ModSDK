#include <common.h>

void GetPrimitiveMem(void ** ppPrim, size_t primSize)
{
    struct DB * backBuffer = sdata->gGT->backBuffer;
    if (backBuffer->primMem.curr <= backBuffer->primMem.endMin100)
    {
		*ppPrim = backBuffer->primMem.curr;
		
		backBuffer->primMem.curr = 
		(size_t)backBuffer->primMem.curr + primSize;
		
		((Tag *)*ppPrim)->size = (primSize - sizeof(Tag)) / sizeof(u32);
	}
    else { *ppPrim = nullptr; }
}

void AddPrimitive(void * pPrim, void * pOt)
{
    ((Tag *)pPrim)->addr = ((Tag *)pOt)->addr;
    ((Tag *)pOt)->addr = (u32) pPrim;
}