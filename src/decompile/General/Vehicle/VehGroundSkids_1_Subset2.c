#include "common.h"

#define SOME_SCALE 4

// FUN_8005c278
// calculates the next skidmark triangle?
// unk - array of 3 vectors to update
// v1 - some vector1
// v2 - some vector2
// v3 - some vector3
void VehGroundSkids_Subset2(SVECTOR* unk, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3)
{
	//TODO: investigate parent function to give better names

	//unk is SVECTOR[3] at sp 0x0, but for some reason it crashes
	//we can just hardcode the sp address instead
	//cause it's always called with the sp address 0 (check r0)
	SVECTOR* sp = (SVECTOR*)0x1F800000;

	//translation vector on scratchpad
	VECTOR* t = (VECTOR*)0x1F8000B8;

	sp[0].vx = (v1->vx - t->vx) * SOME_SCALE;
	sp[0].vy = (v1->vy - t->vy) * SOME_SCALE;
	sp[0].vz = (v1->vz - t->vz) * SOME_SCALE;

	sp[1].vx = (v2->vx - t->vx) * SOME_SCALE;
	sp[1].vy = (v2->vy - t->vy) * SOME_SCALE;
	sp[1].vz = (v2->vz - t->vz) * SOME_SCALE;

	sp[2].vx = (v3->vx - t->vx) * SOME_SCALE;
	sp[2].vy = (v3->vy - t->vy) * SOME_SCALE;
	sp[2].vz = (v3->vz - t->vz) * SOME_SCALE;
}