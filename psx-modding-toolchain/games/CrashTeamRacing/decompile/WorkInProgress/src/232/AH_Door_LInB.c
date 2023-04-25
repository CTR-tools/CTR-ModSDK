#include <common.h>

void AH_Door_ThTick(struct Thread*);
void AH_Door_ThDestroy(struct Thread*);

void DECOMP_AH_Door_LInB(struct Instance* doorInst)
{
  char i;
  char doorID;
  short sVar2;
  char doorIsOpen;
  int lev;
  int ratio;
  short leftRot[3];
  short rightRot[3];

  struct GameTracker* gGT = sdata->gGT;
  struct Thread* doorTh;
  struct Instance* otherDoorInst;
  struct Model* model;
  struct ModelHeader* headers;
  struct WoodDoor* door;
  int *piVar6; // Instance? Object?

  lev = gGT->levelID;

  // If this Instance already has a thread
  if (doorInst->thread)
    return;

  // 0x38 = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0x3 = static thread bucket
  doorTh = THREAD_BirthWithObject(0x380303, AH_Door_ThTick, &DAT_800abaa4, 0);

  doorInst->thread = doorTh;

  // if the thread failed to build
  if (doorTh == NULL)
    return;

  door = doorTh->object;

  doorTh->inst = doorInst;

  doorTh->funcThDestroy = AH_Door_ThDestroy;

  piVar6 = *(short *)((int)door + 0xc);

  // this instance is always the left-hand door,
  // and every left-hand door has one key hole
  doorInst->flags |= 0x1000;

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
  doorID = doorInst->name[5];

  for (i = 5; doorID != NULL; i++)
  {
    sVar2 = *(short *)(door + 0xd);

    // get door ID from string
    *(short *)(door + 0xd) = sVar2 * 10;
    *(short *)(door + 0xd) = sVar2 * 10 + (*(char *)(doorInst + (short)doorTh + 8) - 0x30);

    doorID = *(char *)(doorInst + i + 8);
  }

  // Level ID is Glacier Park
  if (lev == 0x1c)
  {
    // door with two key holes
    model = gGT->modelPtr[0xb5];
  }
  // Level ID is not Glacier Park
  else
  {
    if (
        // Level ID is N Sanity Beach
        (lev == 0x1a) &&

        // doorID == 5
        (*(short *)(door + 0xd) == 5))
    {
      // door with no key holes
      model = sdata->gGT->modelPtr[0xa7];

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
      doorTh = sdata->gGT->modelPtr[0x7a];
    }
  }

  // DAT_800abaa4
  // "door"

  // INSTANCE_Birth3D -- ptrModel, name, thread
  otherDoorInst = INSTANCE_Birth3D(doorTh, &DAT_800abaa4);

  // spawn instance of right-hand door,
  // which is not in LEV file, only built in thread
  otherDoorInst = door->otherDoor;

LAB_800b08b4:

  // | 0x8000 - reverse culling direction
  otherDoorInst->flags |= 0x9000;

  // copy full matrix (position and rotation)
  // from left-hand door to right-hand door
  otherDoorInst->matrix.m[0][0] = doorInst->matrix.m[0][0];
  otherDoorInst->matrix.m[0][2] = doorInst->matrix.m[0][2];
  otherDoorInst->matrix.m[1][1] = doorInst->matrix.m[1][1];
  otherDoorInst->matrix.m[2][0] = doorInst->matrix.m[2][0];
  otherDoorInst->matrix.m[2][2] = doorInst->matrix.m[2][2];
  otherDoorInst->matrix.t[0] = doorInst->matrix.t[0];
  otherDoorInst->matrix.t[1] = doorInst->matrix.t[1];
  otherDoorInst->matrix.t[2] = doorInst->matrix.t[2];

  // set scaleX to -0x1000
  otherDoorInst->scale[0] = 0xf000;

  // reverse culling
  otherDoorInst->flags |= 0x8000;

  ratio = MATH_Cos((int)doorInst->instDef->rot[1]);

  otherDoorInst->matrix.t[0] += (ratio * 0x600 >> 0xc);

  otherDoorInst->matrix.t[1] = doorInst->matrix.t[1];

  ratio = MATH_Sin((int)(int)doorInst->instDef->rot[1]);

  otherDoorInst->matrix.t[2] += (ratio * 0x600 >> 0xc);

  // both doors always face camera
  headers = doorInst->model->headers;

  headers->flags |= 2;

  headers = otherDoorInst->model->headers;

  headers->flags |= 2;

  if (
      // Level ID is N Sanity Beach, check door to Gemstone Valley
      (lev == 0x1a && *(short *)(door + 0xd) == 4 && ((sdata->advProgress.rewards[3] & 0x40) != 0)) ||

      // Level ID is N Sanity Beach, check door to Glacier Park
      (lev == 0x1a && *(short *)(door + 0xd) == 5 && ((sdata->advProgress.rewards[3] & 0x10) != 0)) ||

      // Level ID is Gemstone Valley, check door to Cup room
      (lev == 0x19 && ((sdata->advProgress.rewards[3] & 0x20) != 0)) ||

      // Level ID is Lost Ruins, check door to Glacier Park
      (lev == 0x1b && ((sdata->advProgress.rewards[3] & 0x80) != 0)) ||

      // Level ID is Glacier Park, check door to Citadel City
      (doorIsOpen = false, lev == 0x1c) && ((sdata->advProgress.rewards[3] & 0x100) != 0))
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
    leftRot[1] = doorInst->instDef->rot[1] + *(short *)((int)door + 0x16);
    leftRot[2] = *(short *)((int)door + 0x18);

    rightRot[0] = *(short *)((int)door + 0x14);
    rightRot[1] = doorInst->instDef->rot[1] - *(short *)((int)door + 0x16);
    rightRot[2] = *(short *)((int)door + 0x18);

    // make matrices for both doors rotated open

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&doorInst->matrix, &leftRot);

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&otherDoorInst->matrix, &rightRot);

    // right-hand instance
    door->otherDoor = otherDoorInst;
  }
  return;
}