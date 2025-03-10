#include <common.h>

void DECOMP_BOTS_CollideWithOtherAI(struct Driver* robot_1, struct Driver* robot_2)
{
	// first determine which driver bumps forward and which bumps backwards
	if (robot_1->driverRank < robot_2->driverRank)
	{
		struct Driver* temp = robot_2;
		robot_2 = robot_1;
		robot_1 = temp;
	}
	//robot_1 = iVar2
	//robot_2 = param_2

	short* uVar3;
	short* estimatePos = robot_1->botData.estimatePos; //iVar4
	if ((robot_1->botData.botFlags & 1) == 0)
	{
		// nav path index
		short botPathIndex = robot_1->botData.botPath;

		// pointer to navFrame
		estimatePos = &robot_1->botData.botNavFrame->pos[0];
		
		uVar3 = (short*)((&estimatePos[0]) + sizeof(struct NavFrame));

		// if you go out of bounds
		if (sdata->NavPath_ptrHeader[botPathIndex]->last <= (struct NavFrame*)uVar3)
		{
			// loop back to first navFrame
			uVar3 = &sdata->NavPath_ptrNavFrameArray[botPathIndex]->pos[0];
		}
	}
	else
	{
		// pointer to nav frame
		uVar3 = &robot_1->botData.botNavFrame->pos[0];
	}

	short pos[3];
	// position of one driver
	pos[0] = (short)(robot_1->posCurr.x >> 8);
	pos[1] = (short)(robot_1->posCurr.y >> 8);
	pos[2] = (short)(robot_1->posCurr.z >> 8);

	// two navFrame structs, and position pointer
	int res1 = CAM_MapRange_PosPoints(uVar3, estimatePos, &pos[0]);

	// position of other driver
	pos[0] = (short)(robot_2->posCurr.x >> 8);
	pos[1] = (short)(robot_2->posCurr.y >> 8);
	pos[2] = (short)(robot_2->posCurr.z >> 8);

	// two navFrame structs, and position pointer
	int res2 = CAM_MapRange_PosPoints(uVar3, estimatePos, &pos[0]);

	// reduce speed of one AI,
	// the AI that is closer to the previous nav point,
	// who therefore is the driver in the back of the collision

	if (res1 < res2)
	{
		// reduce AI speed
		int speed = robot_1->botData.unk5bc.ai_speedLinear - 3000;
		speed = ((speed < 0) ? 0 : speed); //clamp to 0
		robot_1->botData.unk5bc.ai_speedLinear = speed;
	}
	else
	{
		// reduce AI speed
		int speed = robot_2->botData.unk5bc.ai_speedLinear - 3000;
		speed = ((speed < 0) ? 0 : speed); //clamp to 0
		robot_2->botData.unk5bc.ai_speedLinear = speed;
	}
}