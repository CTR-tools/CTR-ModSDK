#include <common.h>

// param1 is thread checked for collision
// param2 is ScratchpadStruct
// param3 is person who used weapon
void DECOMP_PROC_CollideHitboxWithBucket(struct Thread* collThread,struct ScratchpadStruct* param_2,int param_3)
{
  struct Instance* inst;
  int distX, distY, distZ;

  // if thread is valid
  if (collThread != NULL) return;
    do
	{
	  // if child thread exists
      if (collThread->childThread != NULL)
	  {
		// recursively check all children
        PROC_CollideHitboxWithBucket(collThread->childThread,param_2,param_3);
      }

      if (
			// make sure you dont hit your own weapon???
			(collThread->next != param_3) &&

			// if collision is not disabled for this thread,
			// and if this thread is not dead
		    ((collThread->flags & 0x1800) == 0)
		 )
	  {
		// get instance
        inst = collThread->inst;

		// get distance of X, Y, Z
        distX = (int)param_2->Input1.pos[0] - inst->matrix.t[0];
        distY = (int)param_2->Input1.pos[1] - inst->matrix.t[1];
        distZ = (int)param_2->Input1.pos[2] - inst->matrix.t[2];

		// if all the dist values are small
        if ((distX * distX < 0x10000000) &&
			(distY * distY < 0x10000000) &&
			(distZ * distZ < 0x10000000) &&
			// if abs distance is less than collision radius
			(distX * distX + distY * distY + distZ * distZ < param_2->Input1.hitRadiusSquared)
			 )
		  {			
			param_2->Union.ThBuckColl.distance[0] = distX;
			param_2->Union.ThBuckColl.distance[1] = distY;
			param_2->Union.ThBuckColl.distance[2] = distZ;
			param_2->Union.ThBuckColl.funcCallback(param_2,collThread);
          }
        }
	  // thread = thread->sibling;
      collThread = collThread->siblingThread;
    } while (collThread != NULL);
}