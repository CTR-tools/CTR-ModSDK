#include <common.h>

void DECOMP_PROC_CollidePointWithSelf(struct Thread* th, struct Need_New_Name* buf)
{
	struct Instance* inst;
	int distX;
	int distY;
	int distZ;
	int dist;
	
	// if collision disabled, or thread is dead, quit
	if((th->flags & 0x1800) != 0) return;
	
	inst = th->inst;
	
	// Do not try to optimize this with loops,
	// it will not compile to less assembly,
	// 180 bytes is as low as this will go
	
	distX = (int)buf->pos[0]-(int)inst->matrix.t[0];
	distY = (int)buf->pos[1]-(int)inst->matrix.t[1];
	distZ = (int)buf->pos[2]-(int)inst->matrix.t[2];
	
	if(distX*distX >= 0x10000000) return;
	if(distY*distY >= 0x10000000) return;
	if(distZ*distZ >= 0x10000000) return;
	
	dist = distX*distX + distY*distY + distZ*distZ;
	
	// if outside hit radius
	if(dist >= buf->radius) return;

	// return distance to center
	buf->radius = dist;
	
	// save the thread collided with
	buf->th = th;
	
	buf->distX = (short)distX;
	buf->distY = (short)distY;
	buf->distZ = (short)distZ;
}