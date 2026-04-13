#include <common.h>

void DECOMP_AH_Map_LoadSave_Prim(
	short* vertPos, char* vertCol, 
	void* ot, struct PrimMem* primMem)
{
	POLY_G4* p = primMem->curr;
	primMem->curr = p+1;
	
	*(int*)&p->r0 = *(int*)&vertCol[0x0];
	*(int*)&p->r1 = *(int*)&vertCol[0x4];
	*(int*)&p->r2 = *(int*)&vertCol[0x8];
	*(int*)&p->r3 = *(int*)&vertCol[0xC];
	
	*(int*)&p->x0 = *(int*)&vertPos[0x0];
	*(int*)&p->x1 = *(int*)&vertPos[0x2];
	*(int*)&p->x2 = *(int*)&vertPos[0x4];
	*(int*)&p->x3 = *(int*)&vertPos[0x6];
	
	setPolyG4(p);
	AddPrim(ot, p);
}