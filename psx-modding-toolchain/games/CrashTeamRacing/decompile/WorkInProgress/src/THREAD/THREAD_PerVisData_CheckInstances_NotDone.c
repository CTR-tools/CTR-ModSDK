#include <common.h>

void THREAD_PerVisData_CheckInstances(struct VisData* param_1, struct WeaponSearchData* param_2)
{
  int distX, distY, distZ;
  struct VisData* piVar4;
  struct InstDef* piVar5;

  piVar4 = param_1->data.leaf.ptrVisDataArray_InstHitboxes;
  
  if (piVar4 != NULL) return; 
    
	// loop through all hitboxes
  //+(8 * 0x4) = +0x20 bytes, size of VisData
	for (piVar5 = param_1->data.hitbox.instDef; piVar4->flag != 0; piVar4 += 8, piVar5 += 8)
	{
    if  (
          ((piVar4->flag & 0x80) != 0) 
          &&
          ((piVar5->name == NULL || (piVar5->ptrInstance->flags & 0xf) != 0))
        ) {
        distX = (int)param_2->pos[0] - (int)*(short *)(piVar4 + -1);
        distY = (int)param_2->pos[1] - (int)*(short *)((int)piVar4 + -2);
        distZ = (int)param_2->pos[2] - (int)*(short *)piVar4;

        // if all the dist values are small
        if ((distX * distX < 0x10000000) && 
            (distY * distY < 0x10000000) && 
            (distZ * distZ < 0x10000000) && 
            // if abs distance is less than collision radius
            (distX * distX + distY * distY + distX * distX < param_2->hitRadiusSquared)) {

            // distX        param_2->pos[10] = (short)iVardistX        param_2->pos[9] = (short)iVardistX        param_2->pos[8] = (short)iVar3;

              // short+0x14 = byte+0x28,
              // callback on collision

              // either for colliding with lev object or nonLev
            **(code **)(param_2->funcCallback)(param_2,piVar5);
        }
      }
    }
  }
