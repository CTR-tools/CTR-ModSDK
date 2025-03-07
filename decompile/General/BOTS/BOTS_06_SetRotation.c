#include <common.h>

void DECOMP_BOTS_SetRotation(struct Driver* bot, short param_2) //UNTESTED
{
	struct NavFrame* nf = bot->botNavFrame;

	(*(int*)&bot->unk5bc[0x28]) = 0;
	(*(int*)&bot->unk5bc[0x2C]) = 0;
	(*(int*)&bot->unk5bc[0x30]) = 0;

	// ======== Get Driver Position =============

	bot->estimatePos[0] = (short)(((u_int)bot->posCurr.x) >> 8);
	bot->estimatePos[1] = (short)(((u_int)bot->posCurr.y) >> 8);
	bot->estimatePos[2] = (short)(((u_int)bot->posCurr.z) >> 8);

	// ======== Compare to Nav Position =============

	int dx = nf->pos[0] - bot->estimatePos[0];
	int dy = nf->pos[1] - bot->estimatePos[1];
	int dz = nf->pos[2] - bot->estimatePos[2];

	// ======== Calculate Distance =============

	//xz dist from driver to nav
	int xzDist = SquareRoot0_stub(dx * dx + dz * dz);
	bot->distToNextNavXZ = xzDist;
	//xyz distance from driver to nav
	int xyzDist = SquareRoot0_stub(dx * dx + dy * dy + dz * dz);
	bot->distToNextNavXYZ = xyzDist;

	// ======== Calculate Rotation =============

	int rot = ratan2(dy * 0x1000, bot->distToNextNavXZ * 0x1000);
	bot->estimateRotCurrY = rot >> 4;
	bot->unk5a8 = 0;

	// "if BOTS_ThTick_Drive or BOTS_Driver_Convert"
	if (param_2 == 0)
	{
		bot->estimateRotNav[0] = nf->rot[0];
		rot = ratan2(-dx, -dz);
		bot->estimateRotNav[1] = ((rot + 0x800) >> 4);
		bot->estimateRotNav[2] = nf->rot[1];
	}
	else
	{
		bot->estimateRotNav[1] = (char)((sdata->gGT->level1->DriverSpawn[0].rot[1] + 0x400) >> 4);
	}

	short v = bot->estimateRotNav[1] << 4;

	//why does the Driver class have so many ways to store y rotation >:(
	bot->ai_rotY_608 = v;
	bot->angle = v;
	bot->rotCurr.y = v;
	bot->rotPrev.y = v;
	bot->ai_rot4[1] = v;

	bot->botFlags |= 1;
}