// LinkedCollide_Radius
// param_1 instance
// param_2 thread of param_1's instance (unused)
// param_3 thread (thread bucket)
// param_4 collision radius
int FUN_800314e0(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // only continue if thread is valid
  if (param_3 != 0)
  {
	// loop through every thread
	// in the linked list
    do
	{
	  // get instance from thread
      iVar4 = *(int *)(param_3 + 0x34);

	  // get difference in X, Y, and Z, from both instances
      iVar3 = *(int *)(iVar4 + 0x44) - *(int *)(param_1 + 0x44);
      iVar2 = *(int *)(iVar4 + 0x48) - *(int *)(param_1 + 0x48);
      iVar1 = *(int *)(iVar4 + 0x4c) - *(int *)(param_1 + 0x4c);

	  // if Minecart
      if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x21) 
	  {
		// Cylinder collision
        if (((uint)(iVar3 * iVar3 + iVar1 * iVar1) < param_4) && (-0x20 < iVar2)) {
          return iVar4;
        }
      }

	  // all other models to spherical collision
      else
	  {
		// if distance is less than collision radius
        if ((uint)(iVar3 * iVar3 + iVar1 * iVar1 + iVar2 * iVar2) < param_4)
		{
		  // return the instance it collided with
          return iVar4;
        }
      }

	  // go to the next thread in the list
      param_3 = *(int *)(param_3 + 0x10);

	// until there are no more threads
    } while (param_3 != 0);
  }

  // no collision
  return 0;
}


// LinkedCollide_Hitbox_Desc
void FUN_800315ac(undefined4 *param_1)

{
  FUN_80031608(*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5]);
  return;
}


// param_1 instance
// param_2 thread of param_1's instance
// param_3 thread (thread bucket)
// param_4 hitbox_X
// param_5 hitbox_Y
// param_6 hitbox_Z
// LinkedCollide_Hitbox
int FUN_80031608(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6)

{
  int iVar1;
  int iVar2;
  short local_resc;
  short sStackX14;
  MATRIX MStack88;
  SVECTOR local_38;
  VECTOR local_30;
  long alStack32 [2];

  if (param_3 != 0) {
    do
	{
	  // thread->instance
      iVar1 = *(int *)(param_3 + 0x34);

	  // instance position
      local_38.vx = *(short *)(iVar1 + 0x44);
      local_38.vy = *(short *)(iVar1 + 0x48);
      local_38.vz = *(short *)(iVar1 + 0x4c);

	  iVar2 = *(int *)(iVar1 + 0x48) - *(int *)(param_1 + 0x48);

	  // output: ???
	  // input: instance matrix
	  // MATH_HitboxMatrix
	  FUN_8003d264(&MStack88,param_1 + 0x30);

      SetRotMatrix(&MStack88);
      SetTransMatrix(&MStack88);

	  // local_38 - input
	  // local_30 - output
	  // alStack32 - flag
      RotTrans(&local_38,&local_30,alStack32);

      if (
			(
				(
					(local_30.vx < param_5._2_2_) &&
					(
						local_resc = (short)param_4,
						local_resc < local_30.vx
					)
				) &&
				(local_30.vz < param_6._2_2_)
			) &&
			(
				(
					(
						(short)param_5 < local_30.vz &&
						(
							sStackX14 = (short)((uint)param_4 >> 0x10),
							sStackX14 <= iVar2
						)
					) &&
					(iVar2 < (short)param_6)
				)
			)
		  )
	  {
		// return instance that collided with thread
        return iVar1;
      }

	  // thread -> sibling
      param_3 = *(int *)(param_3 + 0x10);

    } while (param_3 != 0);
  }
  return 0;
}
