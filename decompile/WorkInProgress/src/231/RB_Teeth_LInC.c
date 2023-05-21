#include <common.h>

void RB_Teeth_ThTick(struct Thread *);

int DECOMP_RB_Teeth_LInC(struct Instance *teethInst, struct Thread *t, struct ScratchpadStruct* sps)
{
    int iVar1;
    struct Thread *teethTh;
    struct Teeth *teeth;
    struct Driver *d;

    // This is the door you can shoot in tiger temple

    // If not in relic race, ignore the function,
    // there are no weapons to activate door anyways
    if ((sdata->gGT->gameMode1 & ARCADE_MODE0) == 0)
        return;
        
    teethTh = teethInst->thread;
    d = t->object;

    if (teethTh == NULL)
    {
        // 0x8 = size
        // 0 = no relation to param4
        // 0x300 = SmallStackPool
        // 0x3 = "static" thread bucket
        teethTh = THREAD_BirthWithObject(0x80303, RB_Teeth_ThTick, s_teeth_800b9de8, 0);

        teethInst->thread = teethTh;

        if (teethTh == NULL)
        {
            return 2;
        }

        teeth = teethTh->object;

        teethTh->inst = teethInst;

        // door not moving
        teeth->direction = 0;

        // timer is zero
        teeth->timeOpen = 0;
    }

    teeth = teethTh->object;

    // if collided object is a player
    if (sps->Input1.modelID == 0x18)
    {
        // if driver is using mask weapon
        if ((d->actionsFlagSet & 0x800000) != 0)
        {
            RB_Teeth_OpenDoor(teethInst);
        }

        return 2;
    }
	
	// If collide with something
	// that is not a player

    // time to close
    if (teeth->timeOpen == 0)
    {
        iVar1 =
            ((int)sps->Input1.pos[0] - teethInst->matrix.t[0]) * (int)teethInst->matrix.m[0][2] +
            ((int)sps->Input1.pos[2] - teethInst->matrix.t[2]) * (int)teethInst->matrix.m[2][2];

        if (iVar1 < 0)
        {
            iVar1 = -iVar1;
        }
        if (iVar1 >> 0xc < 0x81)
        {
            return 1;
        }
        return 2;
    }
    return 2;
}
