// PROC_DestroyTracker
void FUN_80041dc0(struct Thread* t)

{
  // If there are any missiles in play
  if (0 < *(int *)(PTR_DAT_8008d2ac + 0x1ec0))
  {
	// decrease number of missiles
    *(int *)(PTR_DAT_8008d2ac + 0x1ec0) = *(int *)(PTR_DAT_8008d2ac + 0x1ec0) + -1;
  }

  // PROC_DestroyInstance
  FUN_80041dfc(t);

  return;
}


// PROC_DestroyInstance
void FUN_80041dfc(int param_1)

{
  // INSTANCE_Death
  FUN_80030aa8(*(undefined4 *)(param_1 + 0x34));
  return;
}


// PROC_DestroyObject
// param_1 thread's object
// param_2 thread flags
void FUN_80041e20(int param_1,uint param_2)

{
  undefined *puVar1;

  if (param_1 != 0) {
    if ((param_2 & 0x300) == 0x100)
	{
	  // Large Stack Pool
      puVar1 = PTR_DAT_8008d2ac + 0x1970;
    }
    else
	{
      if ((param_2 & 0x300) == 0x200)
	  {
		// Medium Stack Pool
        puVar1 = PTR_DAT_8008d2ac + 0x1948;
      }
      else
	  {
		// Small Stack Pool
        puVar1 = PTR_DAT_8008d2ac + 0x1920;
      }
    }

	// LIST_AddFront
	// add to free list
    FUN_80031744(puVar1,param_1 + -8);
  }
  return;
}


// PROC_DestroySelf
// param_1 is a thread
void FUN_80041e9c(int param_1)

{
  // If thread is valid
  if (param_1 != 0) {

	// If thread has an OnDestroy funcPtr
    if (*(code **)(param_1 + 0x24) != (code *)0x0)
	{
	  // execute OnDestroy,
	  // which is usually a pointer to PROC_DestroyInstance
      (**(code **)(param_1 + 0x24))(param_1);
    }

	// Count how many times this thread has been used?

	// x = x + 1
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;

	// PROC_DestroyObject
    FUN_80041e20(*(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x1c));

	// LIST_AddFront
	// add to free list of ThreadPool
	FUN_80031744(PTR_DAT_8008d2ac + 0x18d0,param_1);
  }
  return;
}


// PROC_DestroyBloodline
void FUN_80041f04(int param_1)

{
  // if given thread is valid
  if (param_1 != 0)
  {
    do
	{
	  // recursively find all children
      if (*(int *)(param_1 + 0x14) != 0)
	  {
		// PROC_DestroyBloodline
        FUN_80041f04(param_1 + 0x14);
      }

	  // PROC_DestroySelf
      FUN_80041e9c(param_1);

	  // recursively find all siblings
      param_1 = *(int *)(param_1 + 0x10);

    } while (param_1 != 0);
  }
  return;
}


// PROC_CheckBloodlineForDead
// look for dead threads, and recycle them
void FUN_80041f58(int *param_1,int param_2)

{
  int iVar1;

  if (param_2 != 0)
  {
    do
	{
	  // get sibling
      iVar1 = *(int *)(param_2 + 0x10);

	  // if thread does not need to be deleted
      if ((*(uint *)(param_2 + 0x1c) & 0x800) == 0)
	  {
		// pointer to sibling thread pointer
        param_1 = (int *)(param_2 + 0x10);

		// if there are children
        if (*(int *)(param_2 + 0x14) != 0)
		{
		  // execute recursively for all children and all siblings of
		  // all children, basically all threads "under" this one

		  // PROC_CheckBloodlineForDead
          FUN_80041f58((int*)(param_2 + 0x14), *(int*)(param_2 + 0x14));

		  // pointer sibling thread pointer
          param_1 = (int *)(param_2 + 0x10);
        }
      }

	  // if thread needs to be deleted
      else
	  {
		// if there is a child thread
        if (*(int *)(param_2 + 0x14) != 0)
		{
		  // PROC_DestroyBloodline
          FUN_80041f04(*(int *)(param_2 + 0x14));
        }

		// PROC_DestroySelf
        FUN_80041e9c(param_2);

		// replace thread in thread bucket,
		// with sibling thread
        *param_1 = iVar1;
      }
      param_2 = iVar1;
    } while (iVar1 != 0);
  }
  return;
}


// PROC_CheckAllForDead
void FUN_80041ff4(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  // Loop through all threadBuckets
  // check all threads in the game, check for the flag 0x800,
  // which means those threads need to be deleted

  iVar5 = 0;
  iVar4 = 0x1b2c;
  iVar3 = 0;

  // loop through 0x12 buckets
  do {
    iVar5 = iVar5 + 1;
    puVar2 = PTR_DAT_8008d2ac + iVar4;
    iVar4 = iVar4 + 0x14;
    iVar1 = iVar3 + 0x1b2c;
    iVar3 = iVar3 + 0x14;

	// PROC_CheckBloodlineForDead
    FUN_80041f58(puVar2,*(undefined4 *)(PTR_DAT_8008d2ac + iVar1));

  } while (iVar5 < 0x12);
  return;
}


// param1 = flags
// param2 = funcThTick
// param3 = name of object
// param4 = another thread (parent, sibling, child)

// PROC_BirthWithObject
// Create a thread and object, return thread
int FUN_8004205c(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)
{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;

  // if there is no parent thread
  if (param_4 == 0)
  {
	// get thread bucket index
    uVar5 = param_1 & 0xff;
  }

  // if there is a parent thread
  else
  {
    // get parent thread bucket
    uVar5 = (uint)*(byte *)(param_4 + 0x1c);
  }

  // if large stack pool
  if ((param_1 & 0x300) == 0x100)
  {
	// size of large object
    iVar4 = 0x670;

	// Large Stack Pool
    puVar3 = PTR_DAT_8008d2ac + 0x1970;
  }

  //if not large stack pool
  else
  {
	// size of small object
    iVar4 = 0x48;

	// warpball, shield, etc
    if ((param_1 & 0x300) == 0x200)
	{
	  // size of medium object
      iVar4 = 0x88;

	  // Medium Stack Pool
      puVar3 = PTR_DAT_8008d2ac + 0x1948;
    }

	// beaker, turbo, etc
	else
	{
	  // Small Stack Pool
      puVar3 = PTR_DAT_8008d2ac + 0x1920;
    }
  }


  // LIST_RemoveFront
  // Get first free object in object pool
  iVar1 = FUN_8003186c(puVar3);

  // if threadBucket index is less than 18
  if (uVar5 < 0x12)
  {
	// if size of object passed is small enough to fit in stack
    if (param_1 >> 0x10 < iVar4 - 8U)
	{
	  // if the object allocated,
	  // then create a thread for the object in the thread pool,
	  // and then put a pointer to the object in the thread
      if (iVar1 != 0)
	  {
		// LIST_RemoveFront
		// Get first free thread in ThreadPool
        iVar4 = FUN_8003186c(PTR_DAT_8008d2ac + 0x18d0);

		// if you are out of room
        if (iVar4 == 0)
		{
		  // sep 3
		  // printf("out of threads \'%s\'\n",param_3);

		  // PROC_DestroyObject
          FUN_80041e20(iVar1 + 8,param_1);
          return 0;
        }

		// copy the flags used to create this thread
        *(uint *)(iVar4 + 0x1c) = param_1;

		// erase cooldown
        *(undefined4 *)(iVar4 + 0x18) = 0;

		// funcThDestroy
        *(undefined4 *)(iVar4 + 0x24) = 0;

		// funcThCollide
        *(undefined4 *)(iVar4 + 0x28) = 0;

		// There is no instance attached to thread
        *(undefined4 *)(iVar4 + 0x34) = 0;

		// if no thread was passed
        if (param_4 == 0)
		{
		  // get pointer to thread bucket
          puVar3 = PTR_DAT_8008d2ac + uVar5 * 0x14;

		  // currThread->next = "first thread in list"
          *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(puVar3 + 0x1b2c);

		  // new "first thread in list" = currThread
          *(int *)(puVar3 + 0x1b2c) = iVar4;

		  // parent thread
          *(undefined4 *)(iVar4 + 0xc) = 0;

		  // child thread
          *(undefined4 *)(iVar4 + 0x14) = 0;
        }

		// if a thread was passed as parameter
        else
		{
		  // if param4 is not a sibling
          if ((param_1 & 0x400) == 0)
		  {
			// If the thread passed from param4 is a parent thread
            if ((param_1 & 0x2000) == 0)
			{
			  // the thread you created has no child
              *(undefined4 *)(iVar4 + 0x14) = 0;

			  // thread->next = parent->child
              *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(param_4 + 0x14);

			  // the parent's child is this thread
			  *(int *)(param_4 + 0x14) = iVar4;

			  // this thread's parent is param4
              *(int *)(iVar4 + 0xc) = param_4;
            }

			// inject thread between param4 and it's child
            else
			{
			  // this thread's child equals parent->child
              *(undefined4 *)(iVar4 + 0x14) = *(undefined4 *)(param_4 + 0x14);

			  // parent->child = this thread
              *(int *)(param_4 + 0x14) = iVar4;

			  // this thread's parent is param4
              *(int *)(iVar4 + 0xc) = param_4;

			  // no sibling threads
              *(undefined4 *)(iVar4 + 0x10) = 0;
            }
          }

		  // if param4 is a sibling to new thread
          else
		  {
			// this thread's sibling equals sibling->sibling
            *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(param_4 + 0x10);

			// get the sibling's parent
            uVar2 = *(undefined4 *)(param_4 + 0xc);

			// sibling->sibling = new thread
            *(int *)(param_4 + 0x10) = iVar4;

			// erase this thread's child
            *(undefined4 *)(iVar4 + 0x14) = 0;

			// set this thread's parent
            *(undefined4 *)(iVar4 + 0xc) = uVar2;
          }
        }

		// set ThTick funcPtr
        *(undefined4 *)(iVar4 + 0x2c) = param_2;

		// set string pointer
        *(undefined4 *)(iVar4 + 8) = param_3;

		// assign object to thread
        *(int *)(iVar4 + 0x30) = iVar1 + 8;

		// return thread
        return iVar4;
      }

	  // Sep3
	  // printf("%ld byte stack allocate failed for thread \'%s\'\n",iVar4,param_3);
    }

	// if allocation failed
    else
	{
	  // Sep3
	  // printf("stack size (%ld) too small for statics (%ld) \'%s\'\n",iVar4 - 8U,param_1 >> 0x10,
             //param_3);

      if (iVar1 != 0)
	  {
		// PROC_DestroyObject
        FUN_80041e20(iVar1 + 8,param_1);

        return 0;
      }
    }
  }

  // if you try to access a thread bucket
  // that doesn't exist
  else
  {
	// printf("invalid thread bucket %ld \'%s\'\n",uVar5,param_3);

	// if object is allocated
    if (iVar1 != 0)
	{
	  // PROC_DestroyObject
      FUN_80041e20(iVar1 + 8,param_1);
      return 0;
    }
  }

  return 0;
}


// param_1 is a thread
// param_2 is pointer to vec3 position
// PROC_CollidePointWithSelf
void FUN_8004228c(int param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // if collision is not disabled for this thread
  if ((*(uint *)(param_1 + 0x1c) & 0x1800) == 0)
  {
	// get instance from thread
    iVar1 = *(int *)(param_1 + 0x34);

	// compare posX, posY, posZ
    iVar4 = (int)*param_2 - *(int *)(iVar1 + 0x44);
    iVar2 = (int)param_2[2] - *(int *)(iVar1 + 0x4c);
    iVar1 = (int)param_2[1] - *(int *)(iVar1 + 0x48);

	// This was slightly modified cause
	// Ghidra gave sloppy code, the rewritten
	// if-statment is functionally identical
	// as before, but not the same output

	// if X-distance is small
    if (iVar4 * iVar4 < 0x10000000)
	{
	  // if Y-distance is small
	  if(iVar1 * iVar1 < 0x10000000)
	  {
		// if Z-distance is small
		if(iVar2 * iVar2 < 0x10000000)
		{
		  // distance formula
		  iVar3 = iVar4 * iVar4 + iVar1 * iVar1 + iVar2 * iVar2

		  // if distance is less than radius
		  if (iVar3 < *(int *)(param_2 + 6))
		  {
		  	// store the distance the objects are apart
		  	*(int *)(param_2 + 6) = iVar3;

		  	// store which thread this instance collides with
		  	*(int *)(param_2 + 4) = param_1;

		  	// store the difference in X, Y, and Z
		  	param_2[8] = (short)iVar4;
		  	param_2[9] = (short)iVar1;
		  	param_2[10] = (short)iVar2;
		  }
		}
	  }
    }
  }
  return;
}


// param_1 is a thread
// param_2 is pointer to vec3 position
// PROC_CollidePointWithBucket
void FUN_80042348(int param_1,undefined4 param_2)

{
  // loop through all thread siblings
  if (param_1 != 0)
  {
    do
	{
	  // PROC_CollidePointWithSelf
      FUN_8004228c(param_1,param_2);

	  // thread = thread->next
	  param_1 = *(int *)(param_1 + 0x10);

    } while (param_1 != 0);
  }
  return;
}


// PROC_SearchForModel
int FUN_80042394(int param_1,int param_2)

{
  int iVar1;

  // if thread is valid
  if (param_1 != 0) {
    do
	{
	  // if modelIndex is the same as the parameter
      if ((int)*(short *)(param_1 + 0x44) == param_2)
	  {
		// return this thread
        return param_1;
      }

	  // check all the children for this model index
      iVar1 = FUN_80042394(*(undefined4 *)(param_1 + 0x14),param_2);

	  // if it was found, return it
      if (iVar1 != 0) {
        return iVar1;
      }

	  // thread = thread -> sibling,
	  // check siblings for model index
      param_1 = *(int *)(param_1 + 0x10);

	} while (param_1 != 0);
  }

  // if thread is not valid, return 0
  return param_1;
}

// PROC_PerBspLeaf_CheckInstances
// param_1 is bspLeaf
void FUN_800423fc(int param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;

  // bspHitboxArray
  piVar5 = *(int **)(param_1 + 0x14);
  
  if ((piVar5 != (int *)0x0) && (*piVar5 != 0)) 
  {
	// bspLeaf[0x14] (bspHitbox)
    piVar4 = piVar5 + 5;
    
	// loop through all hitboxes
	do 
	{
      if (((*(byte *)piVar5 & 0x80) != 0) &&
         ((piVar4[2] == 0 || ((*(uint *)(*(int *)(piVar4[2] + 0x2c) + 0x28) & 0xf) != 0)))) {
        
		// 0x14 - 4
		iVar3 = (int)*param_2 - (int)*(short *)(piVar4 + -1);
        
		// 0x14 - 0
		iVar1 = (int)param_2[2] - (int)*(short *)piVar4;
		
		// 0x14 - 2
        iVar2 = (int)param_2[1] - (int)*(short *)((int)piVar4 + -2);
		
        if (iVar3 * iVar3 < 0x10000000) {
          if (((iVar2 * iVar2 < 0x10000000) && (iVar1 * iVar1 < 0x10000000)) &&
             (iVar3 * iVar3 + iVar2 * iVar2 + iVar1 * iVar1 < *(int *)(param_2 + 4))) {
            param_2[10] = (short)iVar1;
            param_2[9] = (short)iVar2;
            param_2[8] = (short)iVar3;

			// short+0x14 = byte+0x28,
			// callback on collision

			// either for colliding with lev object or nonLev
            (**(code **)(param_2 + 0x14))(param_2,piVar5);
          }
        }
      }
      piVar5 = piVar5 + 8;
      piVar4 = piVar4 + 8;
    } while (*piVar5 != 0);
  }
  return;
}


// PROC_StartSearch_Self
void FUN_80042544(short *param_1)

{
  short sVar1;
  undefined *puVar2;

  // box half-length
  sVar1 = param_1[3];

  // position of object hitting
  // tiger temple teeth

  // param[0] = posX,
  // param[1] = posY,
  // param[2] = posZ,

  // Make hitbox, min and max x,y,z
  param_1[0xe] = *param_1 - sVar1;
  param_1[0xf] = param_1[1] - sVar1;
  param_1[0x10] = param_1[2] - sVar1;
  param_1[0x11] = *param_1 + sVar1;
  param_1[0x12] = param_1[1] + sVar1;
  puVar2 = PTR_DAT_8008d2ac;
  param_1[0x13] = param_1[2] + sVar1;

  // COLL_SearchTree_FindX, callback is PROC_PerBspLeaf_CheckInstances
  FUN_8001ebec(*(undefined4 *)(**(int **)(puVar2 + 0x160) + 0x18),param_1 + 0xe,FUN_800423fc);
  return;
}


// PROC_CollideHitboxWithBucket
// param1 is thread checked for collision
// param2 is ScratchpadStruct
// param3 is person who used weapon
void FUN_800425d4(int param_1,short *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;

  // if thread is valid
  if (param_1 != 0) {
    do
	{
	  // if child thread exists
      if (*(int *)(param_1 + 0x14) != 0)
	  {
		// recursively check all children
        FUN_800425d4(*(int *)(param_1 + 0x14),param_2,param_3);
      }

      if (
			// make sure you dont hit your own weapon???
			(param_1 != param_3) &&

			// if collision is not disabled for this thread,
			// and if this thread is not dead
		    ((*(uint *)(param_1 + 0x1c) & 0x1800) == 0)
		 )
	  {
		// get instance
        iVar1 = *(int *)(param_1 + 0x34);

		// get distance of X, Y, Z
        iVar3 = (int)*param_2 - *(int *)(iVar1 + 0x44);
        iVar2 = (int)param_2[1] - *(int *)(iVar1 + 0x48);
        iVar1 = (int)param_2[2] - *(int *)(iVar1 + 0x4c);

		// if X dist is small
        if (iVar3 * iVar3 < 0x10000000)
		{
          if (
				(
					// if Y dist and Z dist are small
					(iVar2 * iVar2 < 0x10000000) &&
					(iVar1 * iVar1 < 0x10000000)
				) &&

				// if distance is less than collision radius
				(iVar3 * iVar3 + iVar2 * iVar2 + iVar1 * iVar1 < *(int *)(param_2 + 4))
			 )
		  {
			// save distances
            param_2[8] = (short)iVar3;
            param_2[9] = (short)iVar2;
            param_2[10] = (short)iVar1;

			// some collision funcPtr???
            (**(code **)(param_2 + 0x14))(param_2,param_1);
          }
        }
      }

	  // thread = thread->sibling;
      param_1 = *(int *)(param_1 + 0x10);

    } while (param_1 != 0);
  }
  return;
}
