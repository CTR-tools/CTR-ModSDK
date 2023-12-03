#include <common.h>

void CS_Podium_ThTick(struct Thread *);

void CS_Podium_Stand_Init(short *podiumData)
{
  struct Instance *inst = 
  INSTANCE_BirthWithThread(
      0xa8,
      OVR_233.s_podium,
      SMALL,
      OTHER,
      CS_Podium_ThTick,
      0, 0);

  // if the instance was built
  if (inst == NULL)
    return;

  // set funcThDestroy to remove instance from instance pool
  inst->thread->funcThDestroy = THREAD_DestroyInstance;

  inst->matrix.t[0] = podiumData[0];
  inst->matrix.t[1] = podiumData[1];
  inst->matrix.t[2] = podiumData[2];

  inst->unk51 += 2;
  inst->unk50 += 2;

  // doing these will compile 32 bytes over budget
  // skipping itnto just use podiumData[8] works so far
  // no side effects detected yet.
  
  // podiumData[12] = podiumData[8];
  // podiumData[13] = podiumData[9];
  // podiumData[14] = podiumData[10];
  
  ConvertRotToMatrix(&inst->matrix.m[0][0], &podiumData[8]);
}