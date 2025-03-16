// used for 16x9 (part 1)
// used for oxide
#include <common.h>

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
void FixReservesIncrement(struct Driver * driver, int reserves)
{
	if (driver->reserves > 30000) { driver->uncappedReserves += reserves; }
	else { driver->reserves += reserves; }
}

void Online_CollidePointWithBucket(struct Thread* th, short* vec3_pos)
{
	int rn = octr->serverRoom;
	if (!ROOM_IS_ITEMS(rn)) //itemless rooms have no collision.
		return;
	while (th != 0)
	{
		DECOMP_PROC_CollidePointWithSelf(th, (struct BucketSearchParams*)vec3_pos);
		// next
		th = th->siblingThread;
	}
}
#endif

#ifdef USE_16BY9
void ui16by9_ViewProj(struct PushBuffer* pb)
{
	// Y axis is already scaled 512/216 x 0x360/0x600 -> 4x3
	// X axis correction for 16x9 must be 9/16 x 4/3 -> 0.75
	// 16x9 is 0.75, 20x9 is 0.6, etc

	// 600  / 1000 for 20x9
	// 750  / 1000 for 16x9
	// 1000 / 1000 for 4x3

	pb->matrix_ViewProj.t[0] =
	pb->matrix_ViewProj.t[0] * 750 / 1000;

	pb->matrix_ViewProj.m[0][0] =
	pb->matrix_ViewProj.m[0][0] * 750 / 1000;

	pb->matrix_ViewProj.m[0][1] =
	pb->matrix_ViewProj.m[0][1] * 750 / 1000;

	pb->matrix_ViewProj.m[0][2] =
	pb->matrix_ViewProj.m[0][2] * 750 / 1000;
}
#endif
