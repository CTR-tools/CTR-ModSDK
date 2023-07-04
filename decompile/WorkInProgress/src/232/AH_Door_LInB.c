#include <common.h>

void AH_Door_ThTick(struct Thread *);
void AH_Door_ThDestroy(struct Thread *);

void DECOMP_AH_Door_LInB(struct Instance *inst)
{
  char i;
  char doorID;
  short sVar2;
  char doorIsOpen;
  int levelID;
  int ratio;
  short leftRot[3];
  short rightRot[3];

  struct GameTracker *gGT;
  struct Thread *t;
  struct Instance *otherDoorInst;
  struct Model *m;
  struct ModelHeader *headers;
  struct WoodDoor *door;
  int *piVar6; // Instance? Object?

  gGT = sdata->gGT;
  levelID = gGT->levelID;

  // If this Instance already has a thread
  if (inst->thread != NULL)
    return;

  t = THREAD_BirthWithObject(
      SIZE_RELATIVE_POOL_BUCKET(
          0x38,
          NONE,
          SMALL,
          STATIC),
      AH_Door_ThTick,     // behavior
      (char *)0x800abaa4, // debug name
      0                   // thread relative
  );

  inst->thread = t;

  // if the thread failed to build
  if (t == NULL)
    return;

  door = t->object;

  t->inst = inst;

  t->funcThDestroy = AH_Door_ThDestroy;

  piVar6 = *(short *)((int)door + 0xc);

  // this instance is always the left-hand door,
  // and every left-hand door has one key hole
  inst->flags |= 0x1000;

  for (i = 3; i > -1; i--)
  {
    piVar6[1] = 0;
    piVar6--;
  }

  *(short *)((int)door + 0x24) = 0;
  *(short *)((int)door + 0x1c) = 0;
  *(short *)((int)door + 0x1e) = 0;

  // frame timer
  *(short *)((int)door + 0x26) = 0;

  *(short *)((int)door + 0x32) = 0;
  *(short *)((int)door + 0x14) = 0;
  *(short *)((int)door + 0x16) = 0;
  *(short *)((int)door + 0x18) = 0;
  *(short *)(door + 0xd) = 0;

  // doorID
  doorID = inst->name[5];

  for (i = 5; doorID != NULL; i++)
  {
    sVar2 = *(short *)(door + 0xd);

    // get door ID from string
    *(short *)(door + 0xd) = sVar2 * 10;
    *(short *)(door + 0xd) = sVar2 * 10 + (*(char *)(inst + (short)t + 8) - 0x30);

    doorID = *(char *)(inst + i + 8);
  }

  // Level ID is Glacier Park
  if (levelID == 0x1c)
  {
    // door with two key holes
    m = gGT->modelPtr[0xb5];
  }
  // Level ID is not Glacier Park
  else
  {
    if (
        // Level ID is N Sanity Beach
        (levelID == 0x1a) &&

        // doorID == 5
        (*(short *)(door + 0xd) == 5))
    {
      // door with no key holes
      m = sdata->gGT->modelPtr[0xa7];

#if 0
      // if it does not exist
      if (model == NULL)
      {
        // useless, this will never happen,
        // also then instance would be nullptr,
        // and instance->matrix would dereference
        // nullptr and crash the game

        door->otherDoor = NULL;

        goto LAB_800b08b4;
      }
#endif
    }
    // if not that door
    else
    {
      // STATIC_DOOR
      // door with one key hole
      t = sdata->gGT->modelPtr[0x7a];
    }
  }

  // DAT_800abaa4
  // "door"

  // INSTANCE_Birth3D -- ptrModel, name, thread
  otherDoorInst = INSTANCE_Birth3D(t, (char*)0x800abaa4);

  // spawn instance of right-hand door,
  // which is not in LEV file, only built in thread
  otherDoorInst = door->otherDoor;

LAB_800b08b4:

  // | 0x8000 - reverse culling direction
  otherDoorInst->flags |= 0x9000;

  // copy full matrix (position and rotation)
  // from left-hand door to right-hand door
  otherDoorInst->matrix.m[0][0] = inst->matrix.m[0][0];
  otherDoorInst->matrix.m[0][2] = inst->matrix.m[0][2];
  otherDoorInst->matrix.m[1][1] = inst->matrix.m[1][1];
  otherDoorInst->matrix.m[2][0] = inst->matrix.m[2][0];
  otherDoorInst->matrix.m[2][2] = inst->matrix.m[2][2];
  otherDoorInst->matrix.t[0] = inst->matrix.t[0];
  otherDoorInst->matrix.t[1] = inst->matrix.t[1];
  otherDoorInst->matrix.t[2] = inst->matrix.t[2];

  // set scaleX to -0x1000
  otherDoorInst->scale[0] = 0xf000;

  // reverse culling
  otherDoorInst->flags |= 0x8000;

  ratio = MATH_Cos((int)inst->instDef->rot[1]);

  otherDoorInst->matrix.t[0] += (ratio * 0x600 >> 0xc);

  otherDoorInst->matrix.t[1] = inst->matrix.t[1];

  ratio = MATH_Sin((int)(int)inst->instDef->rot[1]);

  otherDoorInst->matrix.t[2] += (ratio * 0x600 >> 0xc);

  // both doors always face camera
  headers = inst->model->headers;

  headers->flags |= 2;

  headers = otherDoorInst->model->headers;

  headers->flags |= 2;

  if (
      // Level ID is N Sanity Beach, check door to Gemstone Valley
      (levelID == N_SANITY_BEACH && *(short *)(door + 0xd) == 4 && ((sdata->advProgress.rewards[3] & 0x40) != 0)) ||

      // Level ID is N Sanity Beach, check door to Glacier Park
      (levelID == N_SANITY_BEACH && *(short *)(door + 0xd) == 5 && ((sdata->advProgress.rewards[3] & 0x10) != 0)) ||

      // Level ID is Gemstone Valley, check door to Cup room
      (levelID == GEM_STONE_VALLEY && ((sdata->advProgress.rewards[3] & 0x20) != 0)) ||

      // Level ID is Lost Ruins, check door to Glacier Park
      (levelID == THE_LOST_RUINS && ((sdata->advProgress.rewards[3] & 0x80) != 0)) ||

      // Level ID is Glacier Park, check door to Citadel City
      (doorIsOpen = false, levelID == GLACIER_PARK) && ((sdata->advProgress.rewards[3] & 0x100) != 0))
  {
    // door has already been opened
    doorIsOpen = true;
  }

  // if door has already been opened
  if (doorIsOpen)
  {
    // rotation = 90 degrees
    *(short *)((int)door + 0x16) = 0x400;

    leftRot[0] = *(short *)((int)door + 0x14);
    leftRot[1] = inst->instDef->rot[1] + *(short *)((int)door + 0x16);
    leftRot[2] = *(short *)((int)door + 0x18);

    rightRot[0] = *(short *)((int)door + 0x14);
    rightRot[1] = inst->instDef->rot[1] - *(short *)((int)door + 0x16);
    rightRot[2] = *(short *)((int)door + 0x18);

    // make matrices for both doors rotated open

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&inst->matrix, &leftRot);

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&otherDoorInst->matrix, &rightRot);

    // right-hand instance
    door->otherDoor = otherDoorInst;
  }
  return;
}