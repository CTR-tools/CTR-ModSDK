#include <common.h>

void DECOMP_BOTS_CollideWithOtherAI(struct Driver* robot_1, struct Driver* robot_2)
{
	struct NavFrame* botNavFrame;

	// first determine which driver bumps forward and which bumps backwards

	// if driver 1 is ahead in the race of driver 2
	if (robot_1->driverRank < robot_2->driverRank)
	{
		// swap driver 1 and driver 2 pointers
		struct Driver* temp = robot_1;
		robot_1 = robot_2;
		robot_2 = temp;
	}

	if ((robot_1->botData.botFlags & 1) == 0)
	{
		// nav path index
		short botPathIndex = robot_1->botData.botPath;

		// pointer to navFrame
		botNavFrame = robot_1->botData.botNavFrame;

		// next navFrame
		botNavFrame++;

		// if you go out of bounds
		if (sdata->NavPath_ptrHeader[botPathIndex]->last <= botNavFrame)
		{
			// loop back to first navFrame
			botNavFrame = sdata->NavPath_ptrNavFrameArray[botPathIndex];
		}
	}
	else
	{
		// pointer to nav frame
		botNavFrame = robot_1->botData.botNavFrame;
	}

	short pos[3];
	// position of one driver
	pos[0] = (short)(robot_1->posCurr.x >> 8);
	pos[1] = (short)(robot_1->posCurr.y >> 8);
	pos[2] = (short)(robot_1->posCurr.z >> 8);

	// two navFrame structs, and position pointer
	int res1 = CAM_MapRange_PosPoints(botNavFrame->pos, robot_1->botData.estimatePos, &pos[0]);

	// position of other driver
	pos[0] = (short)(robot_2->posCurr.x >> 8);
	pos[1] = (short)(robot_2->posCurr.y >> 8);
	pos[2] = (short)(robot_2->posCurr.z >> 8);

	// two navFrame structs, and position pointer
	int res2 = CAM_MapRange_PosPoints(botNavFrame->pos, robot_1->botData.estimatePos, &pos[0]);

	// reduce speed of one AI,
	// the AI that is closer to the previous nav point,
	// who therefore is the driver in the back of the collision

	if (res1 < res2)
	{
		// reduce AI speed
		int speed = *(int*)(&robot_2->botData.unk5bc[0x18]) - 3000;
		speed = ((speed < 0) ? 0 : speed); //clamp to 0
		*(int*)(&robot_1->botData.unk5bc[0x18]) = speed;
	}
	else
	{
		// reduce AI speed
		int speed = *(int*)(&robot_1->botData.unk5bc[0x18]) - 3000;
		speed = ((speed < 0) ? 0 : speed); //clamp to 0
		*(int*)(&robot_2->botData.unk5bc[0x18]) = speed;
	}
}