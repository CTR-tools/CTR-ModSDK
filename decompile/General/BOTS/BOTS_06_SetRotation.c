#include <common.h>

void BOTS_SetRotation(struct Driver* param_1, short param_2) //UNTESTED
{
	//1st param may be `struct Driver*`
	//2nd param may be `short`
	//TODO
	struct NavFrame* nf = param_1->botNavFrame;

	(*(int*)&param_1->unk5bc[0x28]) = 0;
	(*(int*)&param_1->unk5bc[0x2C]) = 0;
	(*(int*)&param_1->unk5bc[0x30]) = 0;
	param_1->estimatePos[0] = (short)(((u_int)param_1->posCurr.x) >> 8);
	param_1->estimatePos[1] = (short)(((u_int)param_1->posCurr.y) >> 8);
	param_1->estimatePos[2] = (short)(((u_int)param_1->posCurr.z) >> 8);
	int dx = nf->pos[0] - param_1->estimatePos[0];
	int dy = nf->pos[1] - param_1->estimatePos[1];
	int dz = nf->pos[2] - param_1->estimatePos[2];
	int xzDist = SquareRoot0(dx * dx + dz * dz);
	param_1->distToNextNavXZ = xzDist;
	int xyzDist = SquareRoot0(dx * dx + dy * dy + dz * dz);
	param_1->distToNextNavXYZ = xyzDist;

	//there's more to this function, but at this point I realized that there's already an entry
	//in /WIP for this file. Whoops
}