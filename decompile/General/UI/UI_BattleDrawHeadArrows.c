#include <common.h>

// Draw arrows over the heads of players
void DECOMP_UI_BattleDrawHeadArrows(struct Driver *player)
{
  typedef struct
  {
    u_int tag;
    u_int tpage;
    POLY_G3 g3;
  } G3_SEMITRANS;

  int playerDistance;
  u_short currTeam;
  short sVar1;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  short outXY[2];
  u_int flag;
  u_int color;
  MATRIX *m;
  G3_SEMITRANS *p;
  SVECTOR pos;

  struct GameTracker *gGT = sdata->gGT;

  u_char playerID = player->driverID;

  // pushBuffer ViewProj
  m = &gGT->pushBuffer[playerID].matrix_ViewProj;
  gte_SetRotMatrix(m);
  gte_SetTransMatrix(m);

  u_char numPlyr = gGT->numPlyrCurrGame;

  #ifdef USE_ONLINE
  int OnlineGetNumDrivers();
  numPlyr = OnlineGetNumDrivers();
  #endif

  for (u_char i = 0; i < numPlyr; i++)
  {
    // something related to player structure address
    struct Driver *currDriver = gGT->drivers[i];

	if (
			// skip yourself, skip invisible, skip finished players
			(i == playerID) || 
			(currDriver->invisibleTimer != 0) || 
			((currDriver->actionsFlagSet & 0x2000000) != 0)
		)
	{
      continue;
    }
	
    // If 3 or 4 Players
    sVar1 = 5;

    // If numPlyrCurrGame is less than 3
    if (numPlyr < 3)
    {
      sVar1 = 3;
    }

    struct Instance* currInst = currDriver->instSelf;
    struct Instance* playerInst = player->instSelf;

    // Get X distance and Z distance between two players
    int xDistance = playerInst->matrix.t[0] - currInst->matrix.t[0];
    int zDistance = playerInst->matrix.t[2] - currInst->matrix.t[2];
    int playerDistance = ((xDistance * xDistance) + (zDistance * zDistance));

    // sqrt(0x90000) is 768

    // If currentDriver more than 768 units away from this player,
    // don't draw that driver's arrow
    if (0x90000 > playerDistance)
      continue;

    // load input vector
    pos.vx = currInst->matrix.t[0];
    pos.vy = currInst->matrix.t[1];
    pos.vz = currInst->matrix.t[2];

    gte_ldv0(&pos); // xyz

    // perspective projection
    gte_rtps();

    // get output
    gte_stsxy(&outXY[0]);
    gte_stflg(&flag);

    if ((flag & 0x40000) != 0)
	  continue;
    
    struct PrimMem *primMem = 
		&gGT->backBuffer->primMem;

    p = primMem->curr;
    if (p > primMem->endMin100)
	  return;
	
    primMem->curr = p+1;
	
    p->tpage = 0xe1000a20;
    p->g3.tag = 0;

    p->g3.code = 0x32;

    sVar4 = outXY[0];
    sVar5 = outXY[1] + sVar1;
    iVar6 = (0x1000 - ((playerDistance / 6 + (playerDistance >> 0x1f) >> 0xd) - (playerDistance >> 0x1f)));
    sVar1 = (short)(iVar6 * 3 >> 10);
    sVar3 = (short)(iVar6 * 7 >> 12) + 12;

    p->g3.x0 = sVar4 - sVar1;
    p->g3.y0 = sVar5 - sVar3;
    p->g3.x1 = sVar4;
    p->g3.y1 = sVar5 - 12;
    p->g3.x2 = sVar4 + sVar1;
    p->g3.y2 = sVar5 - sVar3;

    // Battle Team of this driver
    currTeam = currDriver->BattleHUD.teamID;

    // color data
    color = *(u_int *)data.ptrColor[PLAYER_BLUE + currTeam];
	
	#ifdef USE_ONLINE
	int onlineCharID = data.characterIDs[i];
	color = *(u_int *)data.ptrColor[CRASH_BLUE + onlineCharID];
	#endif

    // it's all the same color
    *(int *)&p->g3.r0 = (color & 0xffffff) | 0x30000000;
    *(int *)&p->g3.r1 = color | 0x30000000;
    *(int *)&p->g3.r2 = color | 0x30000000;

    u_long *ot = gGT->pushBuffer[playerID].ptrOT;

    *(int*)p = *ot | 0x8000000;
    *ot = (u_int)p & 0xffffff;
  }
}
