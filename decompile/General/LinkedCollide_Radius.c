#include <common.h>

struct Instance* DECOMP_LinkedCollide_Radius(struct Instance* objInst,struct Thread* _objTh,struct Thread* thBucket,unsigned int hitRadius)
{
  int diff_z, diff_y, diff_x;
  unsigned int diff_dist;
  struct Instance* thInst;

  // if thread valid, loop through every thread in the linked list until there are no more threads
  while (thBucket != 0) 
  {
    thInst = thBucket->inst;

    // get difference in X, Y, and Z, from both instances
    diff_x = thInst->matrix.t[0] - objInst->matrix.t[0]; 
    diff_y = thInst->matrix.t[1] - objInst->matrix.t[1]; 
    diff_z = thInst->matrix.t[2] - objInst->matrix.t[2]; 

    diff_dist = diff_x * diff_x + diff_z*diff_z;
    if ((objInst->model->id == 0x21) && ((diff_dist < hitRadius) && (-0x20 < diff_y))) {
      // Minecart has cylindrical collision
        return thInst;
    } else if (diff_dist + diff_y * diff_y < hitRadius) {
        // Spherical collision for everything else
        return thInst; 
    }

    // next thread in the list (thread bucket)
    thBucket = thBucket->siblingThread;
  }
  // no collision
  return 0;
}
