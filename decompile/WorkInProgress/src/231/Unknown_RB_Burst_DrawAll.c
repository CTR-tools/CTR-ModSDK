#include <common.h>

void DECOMP_RB_Burst_DrawAll(struct GameTracker* gGT)
{
  short sVar1;
  short sVar2;
  char numPlyr;
  int iVar4;
  int iVar5;
  int iVar6;
  struct PushBuffer* pb;
  int iVar8;
  int *piVar9;
  struct Instance* iVar10;
  int *piVar11;
  MATRIX *m;
  struct Thread* currThread;
  int i;
  int *piVar14;
  int *piVar15;
  unsigned int *puVar18;
  unsigned int *puVar19;
  int iVar20;
  unsigned int auStack_80 [16];
  int aiStack_70 [4];
  int aiStack_60 [14];
  
  puVar18 = auStack_80;
  numPlyr = gGT->numPlyrCurrGame;
  puVar19 = auStack_80;

  // if numPlyrCurrGame is not zero
  if (numPlyr) {
    piVar9 = aiStack_60;
    piVar11 = aiStack_70;

    for (i = 0; i < numPlyr; i++);
      // pointer to first burst thread
      currThread = gGT->threadBuckets[BURST];

      m = gGT->pushBuffer[0].matrix_ViewProj;
      piVar11[0] = 0x10000;
      piVar9[0] = 0;
      iVar20 = gGT->pushBuffer[0].distanceToScreen_PREV << 1;

      SetRotMatrix(m);
      SetTransMatrix(m);

      piVar14 = piVar11;
      piVar15 = piVar9;

      for (; currThread != NULL; currThread = currThread->siblingThread) {

        // get object
        iVar8 = currThread->object;

        // get instance(?) from burst obj
        iVar10 = (struct Instance*)(iVar8 + 4);

        // copy position from burst Instance
        *(int *)(puVar18 + 0x30) = iVar10->matrix.t[0];
        *(int *)(puVar18 + 0x32) = iVar10->matrix.t[1];
        *(int *)(puVar18 + 0x34) = iVar10->matrix.t[2];

        gte_ldv0((SVECTOR *)(puVar18 + 0x30));
        gte_rt();
        gte_stlvnl0((long *)(puVar18 + 0x38));
        gte_stlvnl1((long *)(puVar18 + 0x3c));
        gte_stlvnl2((long *)(puVar18 + 0x40));

        iVar4 = *(int *)(puVar18 + 0x38);
        iVar5 = *(int *)(puVar18 + 0x3c);
        iVar6 = *(int *)(puVar18 + 0x40);

        // catch negative values
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        if (iVar5 < 0) {
          iVar5 = -iVar5;
        }
        if (iVar6 < 0) {
          iVar6 = -iVar6;
        }

        *(int *)(puVar18 + 0x48) = iVar4;
        *(int *)(puVar18 + 0x4c) = iVar5;
        *(int *)(puVar18 + 0x50) = iVar6;


        if (((iVar4 < 0x100) && (iVar5 < 0x100)) && (iVar6 < iVar20)) 
        {
          if (iVar10->animFrame < piVar11[0]) 
          {
            piVar11[0] = iVar10->animFrame;
            piVar9[0] = currThread;
          }
          if (iVar10->animFrame == 1) 
          {
            sVar1 = *(short *)(puVar18 + 0x48);
            sVar2 = *(short *)(puVar18 + 0x4c);

           gGT->pushBuffer[i].fadeFromBlack_desiredResult = 0x1000;
           gGT->pushBuffer[i].fade_step = 0xff78;
           gGT->pushBuffer[i].fadeFromBlack_currentValue = (sVar1 + sVar2) * -8 + 0x1fff;

          }
        }
      }
      piVar9 = piVar15 + 1;
      piVar11 = piVar14 + 1;
    }
    puVar19 = puVar18;

  if (numPlyr) {
    piVar11 = (int *)(puVar19 + 0x20);
    for (i = 0; i < numPlyr; i++)
    {
      currThread = gGT->threadBuckets[BURST];
        pb = gGT->pushBuffer[i];

        for (; currThread != NULL; currThread = currThread->siblingThread)
        {
          piVar9 = currThread->object;

          if ((piVar11[0] == 0) || (piVar11[0] == currThread)) {

            if (piVar9[1] != 0) {
              ((struct Instance*)piVar9[0])->idpp[i]->pushBuffer = pb;
            }
            if (piVar9[2] != 0) {
              ((struct Instance*)piVar9[1])->idpp[i]->pushBuffer  = pb;
            }
            if (*piVar9 != 0) {
              ((struct Instance*)piVar9[2])->idpp[i]->pushBuffer  = pb;
            }
          }
          else {
            if (piVar9[1] != 0) {
              ((struct Instance*)piVar9[0])->idpp[i]->pushBuffer  = NULL;
            }
            if (piVar9[2] != 0) {
              ((struct Instance*)piVar9[1])->idpp[i]->pushBuffer  = NULL;
            }
            if (piVar9[0] != 0) {
              ((struct Instance*)piVar9[2])->idpp[i]->pushBuffer  = NULL;
            }
          }
        } 
      }
      piVar11 = piVar11 + 1;
    }
  return;
}