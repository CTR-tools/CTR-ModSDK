#include <common.h>

void DECOMP_RB_Spider_DrawWebs(struct Thread *t, struct TileView *view)
{
    struct GameTracker *gGT;
    struct PrimMem *primMem;
    MATRIX *m;
    LINE_F2 *p;

    short sVar1;
    u_short uVar2;
    int iVar3;
    int iVar4;
    u_int lineColor;
    u_int *ot;
    int depth;
    u_int *puVar8;
    u_int *piVar9;
    u_int *scratchpad;
    int iVar11;
    int numSpiders;
    int iVar13;
    int iVar16;
    u_int uVar17;
    int iVar19;

    gGT = sdata->gGT;
    primMem = &gGT->backBuffer->primMem;

    // quit if there are no spiders
    if (t == NULL) return;
	
    scratchpad = (u_int *)0x1f800000;
    piVar9 = (int *)0x1f800000;

    // all threads
    for (numSpiders = 0; t != NULL; numSpiders++)
    {
		struct Instance* inst = t->inst;
		struct InstDef* instDef = inst->instDef;
		
        uVar2 = instDef->pos[0];
        iVar3 = instDef->pos[1];
        sVar1 = instDef->pos[2];

        iVar4 = t->inst->matrix.t[1];

        scratchpad[0] = (u_int)uVar2 | (iVar3 + 0x540) * 0x10000;
        scratchpad[1] = (u_int)uVar2 | (iVar4 + 0x60) * 0x10000;
        scratchpad[2] = (int)sVar1;
        scratchpad += 3;

        t = t->siblingThread;
    }
	
	#if 0
	int i;
	int numPlyr;
    p = (LINE_F2 *)primMem->curr;	
	numPlyr = gGT->numPlyrCurrGame;

    if (p + (numSpiders * numPlyr) >= primMem->endMin100)
		return;

    iVar4 = 0x1200;

    uVar17 = 0xe1000a20;

    iVar11 = 0x1f800000;

    // loop through all players
    for (
			i = numPlyr - 1; 
			i > -1; 
			i--
		)
    {
		view = &gGT->tileView[i];
        m = &view->matrix_ViewProj;

        // store on GTE
        gte_SetRotMatrix(m);
        gte_SetTransMatrix(m);

        // primMem offset 0xC
        puVar8 = p + 3;

        // loop through spiders
        for (; numSpiders > -1; numSpiders--)
        {
            // point0
            gte_ldVXY0(iVar11);
            gte_ldVZ0(iVar11 + 8);

            // point1
            gte_ldVXY1(iVar11 + 4);
            gte_ldVZ1(iVar11 + 8);

            // perspective projection
            gte_rtpt();
            gte_stsxy01c((long *)(p + 4));

            // depth of vertex on screen
            depth = gte_stSZ1();

            // color (gray)
            lineColor = 0x3f;

            // if line is close enough to the screen
            // to be seen, then generate primitives
            if (depth - 1U < 0x11ff)
            {
                p->r0 = uVar17;
                p->g0 = 0;
                if (0xa00 < depth)
                {
                    iVar19 = (iVar4 - depth) * 0x3f;
                    lineColor = iVar19 >> 0xb;
                    if (iVar19 < 0)
                    {
                        lineColor = iVar19 + 0x7ff >> 0xb;
                    }
                }

                // prim offset 0x4,
                // R,G,B,code(0x42) LINE_F2
                p->code = 0x42;
                p->b0 = (lineColor | lineColor << 8 | lineColor << 0x10);

                depth = depth >> 6;
                if (0x3ff < depth)
                {
                    depth = 0x3ff;
                }

                // tileView 0xf4, ptrOT
                ot = &view->ptrOT[depth];

                // prim header, OT and prim len
                *(int *)p = *ot | 0x5000000;
                *ot = (u_int)p & 0xffffff;

                p = p + 1;
            }

            // advance scratchpad
            iVar11 = iVar11 + 0xc;
        }
    }

    primMem->curr = p;
	#endif
}

void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh, int damage, int radius, int sound);

void DECOMP_RB_Spider_ThTick(struct Thread* spiderTh)
{
  short sVar2;
  int iVar3;

  struct Driver* victim;
  struct Instance* spiderInst;
  struct Instance* coll;
  struct Spider* spider;

  spider = spiderTh->object;

  spiderInst = spiderTh->inst;

  // delay cycle by varying frames
  if (spider->delay != 0)
  {
    spider->delay--;
    return;
  }

#if 0
  spider->unused++;
#endif

  // If spider is on ground
  if (spider->boolNearRoof == 0)
  {
    // if animation finished more than 4 times
    if (4 < spider->animLoopCount)
    {
      // Play animation backwards
      sVar2 = spiderInst->animFrame + -1;

      // if animation is at beginning
      if (spiderInst->animFrame + -1 < 1)
      {
        spiderInst->animFrame = 0;
        spider->animLoopCount = 0;
        spider->boolNearRoof = 1;

        // set animation to WiggleLegsAndTeeth
        goto LAB_800b9a14;
      }

      // set new animation frame
      spiderInst->animFrame = sVar2;

      // last frame of last animation
      if (sVar2 == 0xc)
      {
        // play sound: spider move up
        PlaySound3D(0x79, spiderInst);
      }

      goto LAB_800b9a1c;
    }

    sVar2 = spiderInst->animFrame;

    iVar3 = INSTANCE_GetNumAnimFrames(spiderInst);

    // if animation is done
    if (iVar3 <= (int)sVar2 + 1)
    {
      spiderInst->animFrame = 0;
      spider->animLoopCount++;

      // if animation finishes 5 times
      if (spider->animLoopCount == 5)
      {
        // set animation to zero
        spiderInst->animIndex = 0;

        sVar2 = INSTANCE_GetNumAnimFrames(spiderInst, 0);

        // set animation frame to last frame
        spiderInst->animFrame = sVar2 + -1;
      }
      goto LAB_800b9aa8;
    }
  }

  // if spider is near ceiling
  else
  {
    if (spider->animLoopCount > 4)
    {
      sVar2 = spiderInst->animFrame;

      iVar3 = INSTANCE_GetNumAnimFrames(spiderInst, 0);

      // if animation is not done
      if ((int)sVar2 < iVar3 - 1)
      {
        spiderInst->animFrame += 1;
      }

      // if animation finished
      else
      {
        // reset animation counter
        spider->animLoopCount = 0;

        // move spider to ground
        spider->boolNearRoof = 0;
      LAB_800b9a14:

        // set animation to WiggleLegsAndTeeth
        spiderInst->animIndex = 1;
      }
    LAB_800b9a1c:

      spiderInst->matrix.t[1] = (int)spiderInst->instDef->pos[1] + (int)((short *)0x800b9da4)[spiderInst->animFrame];

      // if animation frame is less than 11
      if ((int)spiderInst->animFrame < 0xb)
      {
        // change spider scaleX and scaleZ based on animation frame

        spider->shadowInst->scale[0] = (short)(((int)spiderInst->animFrame << 0xc) / 10) + 0x1800;
        spider->shadowInst->scale[2] = (short)(((int)spiderInst->animFrame << 0xc) / 10) + 0x1800;
      }
      goto LAB_800b9aa8;
    }

    sVar2 = spiderInst->animFrame;

    iVar3 = INSTANCE_GetNumAnimFrames(spiderInst);

    // if animation is finished
    if (iVar3 - 1 <= (int)sVar2)
    {
      // restart animation to frame zero
      spiderInst->animFrame = 0;

      // increment number of times animation finishes
      sVar2 = spider->animLoopCount;
      spider->animLoopCount = sVar2 + 1;

      // if animation finishes 5 times
      if ((short)(sVar2 + 1) == 5)
      {
        // set animation to ChangePosition
        spiderInst->animIndex = 0;

        // set animation frame to zero
        spiderInst->animFrame = 0;

        // play sound: spider move down
        PlaySound3D(0x7a, spiderInst);
      }
      goto LAB_800b9aa8;
    }
  }

  // increment animation frame
  spiderInst->animFrame += 1;

LAB_800b9aa8:

  Seal_CheckColl(spiderInst, spiderTh, 1, 0x9000, 0x7b);
}

void DECOMP_RB_Spider_LInB(struct Instance* spiderInst)
{
  struct Thread* spiderTh;
  struct Instance* inst;
  struct Spider* spider;
  short rot[3];
  
  if (spiderInst->thread != 0) return;

  // 0x10 = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0xa = "spider" thread bucket
  spiderTh = THREAD_BirthWithObject(0x10030a,DECOMP_RB_Spider_ThTick,0,0);
  
  if (spiderTh == NULL) return; 
  spiderInst->thread = spiderTh;
  spiderTh->inst = spiderInst;
  
  spiderInst->animIndex = 1;
  spiderInst->scale[0] = 0x1c00;
  spiderInst->scale[1] = 0x1c00;
  spiderInst->scale[2] = 0x1c00;
  
  spider = spiderTh->object;
  spider->boolNearRoof = 1;
  spider->animLoopCount = 0;
  spider->spiderID = spiderInst->name[7] - '0';
  
  if (spider->spiderID == 3) {
    spider->delay = 0x5b;
  }
  else if (spider->spiderID == 2) {
    spider->delay = 0x45;
  }
  else {
    spider->delay = 0;
  }
  
  inst = INSTANCE_Birth3D(sdata->gGT->modelPtr[0x53], 0, spiderTh);
  spider->shadowInst = inst;
  
  *(int*)&inst->matrix.m[0][0] = *(int*)&spiderInst->matrix.m[0][0];
  *(int*)&inst->matrix.m[0][2] = *(int*)&spiderInst->matrix.m[0][2];
  *(int*)&inst->matrix.m[1][1] = *(int*)&spiderInst->matrix.m[1][1];
  *(int*)&inst->matrix.m[2][0] = *(int*)&spiderInst->matrix.m[2][0];
  inst->matrix.m[2][2] = spiderInst->matrix.m[2][2];
  
  inst->matrix.t[0] = spiderInst->matrix.t[0];
  inst->matrix.t[1] = spiderInst->matrix.t[1] - 8;
  inst->matrix.t[2] = spiderInst->matrix.t[2];
  spiderInst->matrix.t[1] += 0x4c0;
  
  inst->scale[0] = 0x2000;
  inst->scale[1] = 0x2000;
  inst->scale[2] = 0x2000;
  
  rot[0] = 0;
  rot[1] = 0x200;
  rot[2] = 0;
  ConvertRotToMatrix(&inst->matrix,&rot);
}