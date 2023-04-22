#include <common.h>

void THREAD_PerVisData_CheckInstances(struct VisData* visDataLeaf, struct ScratchpadStruct* param_2)
{
  int distX, distY, distZ;
  struct VisData* visDataHitbox;

  visDataHitbox = visDataLeaf->data.leaf.ptrVisDataArray_InstHitboxes;
  if (visDataHitbox == NULL) return; 
    
  // loop through all hitboxes
  for(visDataHitbox; visDataHitbox->flag != 0; visDataHitbox++)
  {
	// must be a hitbox node
    if ((visDataHitbox->flag & 0x80) == 0) continue;
	if  (visDataHitbox.hitbox.instDef == 0) continue;
	
	// These are always InstDef, not converted to Instance
	if ((visDataHitbox.hitbox.instDef->ptrInstance->flags & 0xf) == 0) continue;
	
    distX = (int)param_2->pos[0] - visDataHitbox->hitbox.unkShort[0];
    distY = (int)param_2->pos[1] - visDataHitbox->hitbox.unkShort[1];
    distZ = (int)param_2->pos[2] - visDataHitbox->hitbox.unkShort[2];
	
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
	  param_2->Union.ThBuckColl.funcCallback(param_2,visDataHitbox);
    }
  }
}
