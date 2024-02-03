#include <common.h>

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
    short *scratchpad;
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

    // all threads
    for (numSpiders = 0; t != NULL; numSpiders++)
    {
		struct Instance* inst = t->inst;
		struct InstDef* instDef = inst->instDef;
		
        uVar2 = instDef->pos[0];
        sVar1 = instDef->pos[2];

        scratchpad[0] = uVar2;
        scratchpad[1] = instDef->pos[1] + 0x540;
        scratchpad[2] = (int)sVar1;
		scratchpad[3] = 0;
		
        scratchpad[4] = uVar2;
        scratchpad[5] = t->inst->matrix.t[1] + 0x60;
        scratchpad[6] = (int)sVar1;
		scratchpad[7] = 0;

        scratchpad += 8;

        t = t->siblingThread;
    }
	
	int i, j;
	int numPlyr;
    p = primMem->curr;	
	numPlyr = gGT->numPlyrCurrGame;

    if (p + (numSpiders * numPlyr) >= primMem->endMin100)
		return;

    iVar4 = 0x1200;

    // loop through all players
    for (i = 0; i < numPlyr; i++)
    {
		view = &gGT->tileView[i];
        m = &view->matrix_ViewProj;

        // store on GTE
        gte_SetRotMatrix(m);
        gte_SetTransMatrix(m);
		
		scratchpad = 0x1f800000;

        // loop through spiders
        for(j = 0; j < numSpiders; j++)
        {
			
			// optimal code, but invalid depth,
			// makes the web look darker
#if 0
			// depth of each vertex
			//__asm__ ("swc2 $17, 0( %0 );" : : "r"(ptr)); SZ1
			//__asm__ ("swc2 $18, 0( %0 );" : : "r"(ptr)); SZ2
			//__asm__ ("swc2 $19, 0( %0 );" : : "r"(ptr)); SZ3
			
			// Need this in Level/Model code,
			// rtps is "single", rtpt is "triple"
            gte_ldv01(&scratchpad[0], &scratchpad[4]);
            gte_rtpt();
            gte_stsxy01(&p->f2.x0, &p->f2.x1);
			
			// depth of 2nd vertex
			__asm__ ("swc2 $18, 0( %0 );" : : "r"(&depth));
#else
            gte_ldv0(&scratchpad[0]);
            gte_rtps();
            gte_stsxy(&p->f2.x0);
			
            gte_ldv0(&scratchpad[4]);
            gte_rtps();
            gte_stsxy(&p->f2.x1);
			
			// rtps (single) writes depth to stsz,
			// no need for averaging with avsz3 or stotz
			gte_stsz(&depth);
#endif	
			scratchpad += 8;

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

                p->f2.r0 = lineColor;
                p->f2.g0 = lineColor;
                p->f2.b0 = lineColor;
                p->f2.code = 0x42;

                depth = depth >> 6;
                if (depth > 0x3ff)
                    depth = 0x3ff;

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

  // Sitting Spider
  if (spider->animLoopCount < 4)
  {
	#ifdef USE_60FPS
	if(sdata->gGT->timer & 1)
	#endif
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
		
		#ifdef USE_60FPS
		if(sdata->gGT->timer & 1)
		#endif
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
			
		#ifdef USE_60FPS
		if(sdata->gGT->timer & 1)
		#endif
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
  
  if (spider->spiderID == 3) 
  {
    t->cooldownFrameCount = FPS_DOUBLE(91);
  }
  else if (spider->spiderID == 2) 
  {
    t->cooldownFrameCount = FPS_DOUBLE(69);
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