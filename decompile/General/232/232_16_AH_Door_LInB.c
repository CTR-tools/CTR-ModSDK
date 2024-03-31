#include <common.h>

void DECOMP_AH_Door_LInB(struct Instance *inst)
{
  char i;
  char doorID;
  short sVar2;
  int levelID;
  int ratio;
  short leftRot[3];
  short rightRot[3];

  struct GameTracker *gGT;
  struct Thread *t;
  struct Instance *otherDoorInst;
  struct Model *m;
  struct ModelHeader *headers;
  struct WoodDoor* woodDoor;
  struct Instance** instPtrArr;

  gGT = sdata->gGT;
  levelID = gGT->levelID;

  // If this Instance already has a thread
  if (inst->thread != NULL)
    return;

  t = 
	DECOMP_PROC_BirthWithObject
	(
      SIZE_RELATIVE_POOL_BUCKET
	  (
          0x38,
          NONE,
          SMALL,
          STATIC
	  ),
      DECOMP_AH_Door_ThTick,   // behavior
      0, 				// debug name
      0                	// thread relative
	);

  inst->thread = t;

  // if the thread failed to build
  if (t == NULL)
    return;

  woodDoor = t->object;

  t->inst = inst;

  t->funcThDestroy = DECOMP_AH_Door_ThDestroy;

  // this instance is always the left-hand door,
  // and every left-hand door has one key hole
  inst->flags |= 0x1000;

  // otherDoor, and 4 keys, all next to each other
  instPtrArr = &woodDoor->otherDoor;
  for (i = 0; i < 5; i++)
  {
      instPtrArr[i] = NULL;
  } 

  woodDoor->doorID = inst->name[5] - '0';
  
  woodDoor->camFlags = 0;
  woodDoor->frameCount_doorOpenAnim = 0;
  woodDoor->keyShrinkFrame = 0;

  woodDoor->doorRot[0] = 0;
  woodDoor->doorRot[1] = 0;
  woodDoor->doorRot[2] = 0;

  // Level ID is Glacier Park
  if (levelID == 0x1c)
  {
    // door with two key holes
    m = gGT->modelPtr[0xb5];
  }
  
  // Level ID is not Glacier Park
  else if (
        // Level ID is N Sanity Beach
        (levelID == 0x1a) &&

        // doorID == 5
        (woodDoor->doorID == 5))
  {
    // door with no key holes
    m = gGT->modelPtr[0xa7];
  }
  
  // if not that door
  else
  {
    // STATIC_DOOR
    // door with one key hole
    m = gGT->modelPtr[0x7a];
  }

  // DAT_800abaa4
  // "door"

  // INSTANCE_Birth3D -- ptrModel, name, thread
  otherDoorInst = DECOMP_INSTANCE_Birth3D(m, 0, 0);

  // spawn instance of right-hand door,
  // which is not in LEV file, only built in thread
  woodDoor->otherDoor = otherDoorInst;

  // | 0x8000 - reverse culling direction
  otherDoorInst->flags |= 0x9000;

  // copy full matrix (position and rotation)
  // from left-hand door to right-hand door
  *(int*)&otherDoorInst->matrix.m[0][0] = *(int*)&inst->matrix.m[0][0];
  *(int*)&otherDoorInst->matrix.m[0][2] = *(int*)&inst->matrix.m[0][2];
  *(int*)&otherDoorInst->matrix.m[1][1] = *(int*)&inst->matrix.m[1][1];
  *(int*)&otherDoorInst->matrix.m[2][0] = *(int*)&inst->matrix.m[2][0];
  otherDoorInst->matrix.m[2][2] = inst->matrix.m[2][2];
  otherDoorInst->matrix.t[0] = inst->matrix.t[0];
  otherDoorInst->matrix.t[1] = inst->matrix.t[1];
  otherDoorInst->matrix.t[2] = inst->matrix.t[2];

  // set scaleX to -0x1000
  otherDoorInst->scale[0] = 0xf000;

  ratio = DECOMP_MATH_Cos((int)inst->instDef->rot[1]);

  otherDoorInst->matrix.t[0] += (ratio * 0x600 >> 0xc);

  otherDoorInst->matrix.t[1] = inst->matrix.t[1];

  ratio = DECOMP_MATH_Sin((int)(int)inst->instDef->rot[1]);

  otherDoorInst->matrix.t[2] += (ratio * 0x600 >> 0xc);

  // both doors always face camera
  headers = inst->model->headers;

  headers->flags |= 2;

  headers = otherDoorInst->model->headers;

  headers->flags |= 2;

  if (
      // Level ID is N Sanity Beach, check door to Gemstone Valley
      (levelID == N_SANITY_BEACH && woodDoor->doorID == 4 && ((sdata->advProgress.rewards[3] & 0x40) != 0)) ||

      // Level ID is N Sanity Beach, check door to Glacier Park
      (levelID == N_SANITY_BEACH && woodDoor->doorID == 5 && ((sdata->advProgress.rewards[3] & 0x10) != 0)) ||

      // Level ID is Gemstone Valley, check door to Cup room
      (levelID == GEM_STONE_VALLEY && ((sdata->advProgress.rewards[3] & 0x20) != 0)) ||

      // Level ID is Lost Ruins, check door to Glacier Park
      (levelID == THE_LOST_RUINS && ((sdata->advProgress.rewards[3] & 0x80) != 0)) ||

      // Level ID is Glacier Park, check door to Citadel City
      (levelID == GLACIER_PARK) && ((sdata->advProgress.rewards[3] & 0x100) != 0))
  {
    // rotation = 90 degrees
    woodDoor->doorRot[1] = 0x400;

    leftRot[0] = woodDoor->doorRot[0];
    leftRot[1] = inst->instDef->rot[1] + woodDoor->doorRot[1];
    leftRot[2] = woodDoor->doorRot[2];

    rightRot[0] = woodDoor->doorRot[0];
    rightRot[1] = inst->instDef->rot[1] - woodDoor->doorRot[1];
    rightRot[2] = woodDoor->doorRot[2];

    // make matrices for both doors rotated open

	// converted to TEST in rebuildPS1
	ConvertRotToMatrix(&inst->matrix, &leftRot);
	ConvertRotToMatrix(&otherDoorInst->matrix, &rightRot);
  }
  return;
}