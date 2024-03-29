#include <common.h>

struct Instance* DECOMP_LinkedCollide_Hitbox_Desc(struct HitboxDesc* objBoxDesc) {
  struct Instance* thInst;
  int diff_y;
  MATRIX thInstMatrix;
  SVECTOR thInstPos;
  VECTOR outVec;
  long flags[2];

  // Loop over thBucket Linked List
  for (struct Thread* thBucket = objBoxDesc->bucket; thBucket != 0; thBucket = thBucket->siblingThread){
    thInst = thBucket->inst;

    thInstPos.vx = thInst->matrix.t[0];
    thInstPos.vy = thInst->matrix.t[1];
    thInstPos.vz = thInst->matrix.t[2];

    diff_y = thInst->matrix.t[1] - objBoxDesc->inst->matrix.t[1] ;

	#ifndef REBUILD_PS1
    MATH_HitboxMatrix(&thInstMatrix, &objBoxDesc->inst->matrix);
	#endif

    SetRotMatrix(&thInstMatrix);
    SetTransMatrix(&thInstMatrix);

    RotTrans(&thInstPos,&outVec, flags);

    if ( (objBoxDesc->bbox.min[0] < outVec.vx) && (objBoxDesc->bbox.max[0] > outVec.vx) &&
         (objBoxDesc->bbox.min[2] < outVec.vz) && (objBoxDesc->bbox.max[2] > outVec.vz) &&
         (objBoxDesc->bbox.min[1] < diff_y)    && (objBoxDesc->bbox.max[1] > diff_y) ) {
        return thInst; //collision thread instance
      }
    }
  return 0;
}
