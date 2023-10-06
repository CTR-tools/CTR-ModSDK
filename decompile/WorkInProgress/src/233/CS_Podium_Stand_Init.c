#include <common.h>

void DECOMP_CS_Podium_Stand_Init(short *podiumData)
{
  struct Instance *inst;

  // create thread for "podium", return instance
  // 0x300 flag = SmallStackPool
  // 0xd = "thread" bucket
  inst = INSTANCE_BirthWithThread(0xa8, s_podium_800abc9c, SMALL, OTHER, 0x800b021c, 0, 0);

  // if the instance was built
  if (inst == NULL)
    return;

  // set funcThDestroy to remove instance from instance pool
  inst->thread->funcThDestroy = THREAD_DestroyInstance;

  inst->matrix[0] = podiumData[0];
  inst->matrix[1] = podiumData[1];
  inst->matrix[2] = podiumData[2];

  inst->unk51 += 2;
  inst->unk50 += 2;

  // rotation
  podiumData[0xc] = podiumData[8];
  podiumData[0xd] = podiumData[9];
  podiumData[0xe] = podiumData[10];

  // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(inst->matrix.m[0][0], podiumData[0xc]);
}