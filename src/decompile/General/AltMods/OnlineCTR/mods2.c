#include "global.h"
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