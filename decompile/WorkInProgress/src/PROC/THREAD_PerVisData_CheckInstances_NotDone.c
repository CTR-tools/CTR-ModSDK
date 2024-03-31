#include <common.h>

void DECOMP_PROC_PerBspLeaf_CheckInstances(struct BSP* bspLeaf, struct ScratchpadStruct* param_2)
{
  int distX, distY, distZ;
  struct BSP* bspHitbox;

  bspHitbox = bspLeaf->data.leaf.bspHitboxArray;
  if (bspHitbox == NULL) return; 
    
  // loop through all hitboxes
  for(bspHitbox; bspHitbox->flag != 0; bspHitbox++)
  {
	// must be a hitbox node
    if ((bspHitbox->flag & 0x80) == 0) continue;
	if  (bspHitbox->hitbox.instDef == 0) continue;
	
	// These are always InstDef, not converted to Instance
	if ((bspHitbox->hitbox.instDef->ptrInstance->flags & 0xf) == 0) continue;
	
    distX = (int)param_2->pos[0] - bspHitbox->hitbox.unkShort[0];
    distY = (int)param_2->pos[1] - bspHitbox->hitbox.unkShort[1];
    distZ = (int)param_2->pos[2] - bspHitbox->hitbox.unkShort[2];
	
    // if all the dist values are small
    if ((distX * distX < 0x10000000) && 
        (distY * distY < 0x10000000) && 
        (distZ * distZ < 0x10000000) && 
        // if abs distance is less than collision radius
        (distX * distX + distY * distY + distX * distX < param_2->Input1.hitRadiusSquared)) 
	{
      param_2->Union.ThBuckColl.distance[0] = distX;
      param_2->Union.ThBuckColl.distance[1] = distY;
      param_2->Union.ThBuckColl.distance[2] = distZ;
	  param_2->Union.ThBuckColl.funcCallback(param_2,bspHitbox);
    }
  }
}
