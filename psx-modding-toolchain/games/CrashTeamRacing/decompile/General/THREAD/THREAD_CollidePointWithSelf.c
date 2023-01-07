#include <common.h>

struct Need_New_Name
{
	// 0x0
	short pos[4];
	
	// 0x8
	struct Thread* th;
	
	// 0xC
	int radius;
	
	// 0x10
	short distComp[4];
};

void THREAD_CollidePointWithSelf(struct Thread* th, struct Need_New_Name* buf)
{
	struct Instance* inst;
	int distComp[3], dist;
	int i;
	
	// if collision disabled, or thread is dead, quit
	if((th->flags & 0x1800) != 0) return;
	
	inst = th->inst;
	dist = 0;
	
	for(i = 0; i < 3; i++)
	{
		distComp[i] = inst->matrix.t[i] - buf->pos[i];
		if((distComp[i]*distComp[i]) > 0x10000000) return;
		dist += distComp[i]*distComp[i];
	}
	
	// if outside hit radius
	if(dist >= buf->radius) return;

	// return distance to center
	buf->radius = dist;
	
	// save the thread collided with
	buf->th = th;
	
	for(i = 0; i < 3; i++)
	{
		buf->distComp[i] = (short)distComp[i];
	}
}