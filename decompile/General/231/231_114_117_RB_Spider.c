#include <common.h>

// 872/1424 bytes (not counting webs)

void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh, int damage, int radius, int sound);

void DECOMP_RB_Spider_DrawWebs(struct Thread *t, struct TileView *view)
{
	typedef struct
	{
		u_int tag;
		u_int tpage;
		LINE_F2 f2;
	} multiCmdPacket;

    struct GameTracker *gGT;
    struct PrimMem *primMem;
    MATRIX *m;
    multiCmdPacket *p;

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
	
	int i, j;
	int numPlyr;
    p = primMem->curr;	
	numPlyr = gGT->numPlyrCurrGame;

    if (p + (numSpiders * numPlyr) >= primMem->endMin100)
		return;

    iVar4 = 0x1200;

    iVar11 = 0x1f800000;

    // loop through all players
    for (i = 0; i < numPlyr; i++)
    {
		view = &gGT->tileView[i];
        m = &view->matrix_ViewProj;

        // store on GTE
        gte_SetRotMatrix(m);
        gte_SetTransMatrix(m);

        // loop through spiders
        for(j = 0; j < numSpiders; j++)
        {	
			// printf is required to prevent crashing?
			printf("%d\n", j);
	
			#if 0
            // point0
            gte_ldVXY0(iVar11);
            gte_ldVZ0(iVar11 + 8);

            // point1
            gte_ldVXY1(iVar11 + 4);
            gte_ldVZ1(iVar11 + 8);

            // advance scratchpad
            iVar11 = iVar11 + 0xc;

            // perspective projection
            gte_rtpt();
			
			// this writes two XY0 and XY1 together
            gte_stsxy01c(&p->f2.x0);

            // depth of vertex on screen
            depth = gte_stSZ1();
			
			#else
				
			depth = 10;
			p->f2.x0 = (20 + (10 * j));
			p->f2.x1 = (20 + (10 * j));
			p->f2.y0 = (20 + (10 * 1));
			p->f2.y1 = (20 + (10 * 9));
			
			#endif

            // color (gray)
            lineColor = 0x3f;

            // if line is close enough to the screen
            // to be seen, then generate primitives
            if (depth - 1U < 0x11ff)
            {
				p->tpage = 0xe1000a20;
                p->f2.tag = 0;
				
                if (depth > 0xa00)
                {
                    iVar19 = (iVar4 - depth) * 0x3f;
                    lineColor = iVar19 >> 0xb;
                    if (iVar19 < 0)
                    {
                        lineColor = (iVar19 + 0x7ff) >> 0xb;
                    }
                }

                *(int*)&p->f2.r0 = (lineColor | lineColor << 8 | lineColor << 0x10);
                p->f2.code = 0x42;

                depth = depth >> 6;
                if (depth > 0x3ff)
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
        }
    }

    primMem->curr = p;
}

void DECOMP_RB_Spider_ThTick(struct Thread* t)
{
  short sVar2;
  int iVar3;

  struct Driver* victim;
  struct Instance* spiderInst;
  struct Instance* coll;
  struct Spider* spider;

  spider = t->object;
  spiderInst = t->inst;

  // delay cycle by varying frames
  if (spider->delay != 0)
  {
    spider->delay--;
    return;
  }

#if 0
  spider->unused++;
#endif

  // Sitting Spider
  if (spider->animLoopCount < 4)
  {
	spiderInst->animFrame++;
	iVar3 = INSTANCE_GetNumAnimFrames(spiderInst, 1);
	
	// if Sitting animation is done
	if (iVar3 <= spiderInst->animFrame)
	{
		spiderInst->animFrame = 0;
		spider->animLoopCount++;
	
		// ghidra source code says 5, but it is 
		// now 4, because of reordered logic
		if (spider->animLoopCount == 4)
		{
			spiderInst->animIndex = 0;
	
			if (spider->boolNearRoof == 0)
			{
				// start moving up (end of animation)
				spiderInst->animFrame = 
					INSTANCE_GetNumAnimFrames(spiderInst, 0) - 1;
			}
			
			else
			{
				// start moving down (start of animation)
				spiderInst->animFrame = 0;
				
				PlaySound3D(0x7a, spiderInst);
			}
		}
	}
  }
  
  // Moving Spider
  else
  {  
	// If spider is on ground
	if (spider->boolNearRoof == 0)
	{
		// === Spider Moving Up ===
			
		// Play animation backwards
		spiderInst->animFrame--;
		sVar2 = spiderInst->animFrame;
		
		if (sVar2 == 0)
		{
			// reset loop, near roof, WiggleLegsAndTeeth
			spider->animLoopCount = 0;
			spider->boolNearRoof = 1;
			spiderInst->animIndex = 1;
		}
	
		// last frame of last animation
		else if (sVar2 == 0xc)
		{
			// play sound: spider move up
			PlaySound3D(0x79, spiderInst);
		}
	}
	
	// if spider is near ceiling
	else
	{
		// === Spider Moving Down ===
			
		spiderInst->animFrame++;
		sVar2 = spiderInst->animFrame;
		
		iVar3 = INSTANCE_GetNumAnimFrames(spiderInst, 0);
		if (iVar3 <= spiderInst->animFrame)
		{
			// reset loop, not near roof, WiggleLegsAndTeeth
			spider->animLoopCount = 0;
			spider->boolNearRoof = 0;
			spiderInst->animIndex = 1;
			spiderInst->animFrame = 0;
		}
	
	}
	
	short* arr = 0x800b9da4;
	spiderInst->matrix.t[1] = (int)spiderInst->instDef->pos[1] + arr[sVar2];
	
	// if animation frame is less than 11
	if (sVar2 < 0xb)
	{
		// change spider scaleX and scaleZ based on animation frame
		spider->shadowInst->scale[0] = (short)((sVar2 << 0xc) / 10) + 0x1800;
		spider->shadowInst->scale[2] = (short)((sVar2 << 0xc) / 10) + 0x1800;
	}	  
  }

  Seal_CheckColl(spiderInst, t, 1, 0x9000, 0x7b);
}

void DECOMP_RB_Spider_LInB(struct Instance* inst)
{
  struct Spider* spider;
  short rot[3];

  struct Thread* t = 
	DECOMP_THREAD_BirthWithObject
	(
		SIZE_RELATIVE_POOL_BUCKET
		(
			sizeof(struct Spider),
			NONE,
			SMALL,
			SPIDER
		),
		
		DECOMP_RB_Spider_ThTick,0,0
	);
  
  if (t == NULL) return; 
  inst->thread = t;
  t->inst = inst;
  
  inst->animIndex = 1;
  inst->scale[0] = 0x1c00;
  inst->scale[1] = 0x1c00;
  inst->scale[2] = 0x1c00;
  
  spider = t->object;
  spider->boolNearRoof = 1;
  spider->animLoopCount = 0;
  spider->spiderID = inst->name[7] - '0';
  
  if (spider->spiderID == 3) {
    spider->delay = 91;
  }
  else if (spider->spiderID == 2) {
    spider->delay = 69;
  }
  else {
    spider->delay = 0;
  }
  
  struct Instance* shadowInst = 
	INSTANCE_Birth3D(sdata->gGT->modelPtr[0x53], 0, t);
  
  spider->shadowInst = shadowInst;
  
  *(int*)&shadowInst->matrix.m[0][0] = *(int*)&inst->matrix.m[0][0];
  *(int*)&shadowInst->matrix.m[0][2] = *(int*)&inst->matrix.m[0][2];
  *(int*)&shadowInst->matrix.m[1][1] = *(int*)&inst->matrix.m[1][1];
  *(int*)&shadowInst->matrix.m[2][0] = *(int*)&inst->matrix.m[2][0];
  shadowInst->matrix.m[2][2] = inst->matrix.m[2][2];
  
  shadowInst->matrix.t[0] = inst->matrix.t[0];
  shadowInst->matrix.t[1] = inst->matrix.t[1] - 8;
  shadowInst->matrix.t[2] = inst->matrix.t[2];
  inst->matrix.t[1] += 0x4c0;
  
  shadowInst->scale[0] = 0x2000;
  shadowInst->scale[1] = 0x2000;
  shadowInst->scale[2] = 0x2000;
  
  rot[0] = 0;
  rot[1] = 0x200;
  rot[2] = 0;
  ConvertRotToMatrix(&shadowInst->matrix,&rot);
}