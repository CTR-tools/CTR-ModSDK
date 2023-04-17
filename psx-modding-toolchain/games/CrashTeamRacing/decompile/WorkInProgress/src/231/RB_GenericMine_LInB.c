#include <common.h>

void RB_GenericMine_ThTick(struct Thread *);
void RB_Hazard_ThCollide_Generic(struct Thread *);

void DECOMP_RB_GenericMine_LInB(struct Instance *inst)
{
    struct Thread* t;
    struct GameTracker* gGT = sdata->gGT;
    struct MineWeapon* mw;

    RB_Default_LInB(inst);

    if ((inst->thread) &&
        ((gGT->gameMode1 & 0x8000000) != 0))
    {
        t = THREAD_BirthWithObject(0x2c0304, RB_GenericMine_ThTick, sdata->s_nitro1, 0);

        inst->thread = t;

        if (t)
        {
            t->inst = inst;

            inst->thread->funcThCollide = RB_Hazard_ThCollide_Generic;
            inst->thread->parentThread = gGT->drivers[0]->instSelf->thread;
            inst->thread->modelIndex = inst->model->id;

            mw = inst->thread->object;

            mw->instParent = gGT->drivers[0]->instSelf;

            mw->driverTarget = NULL;
            mw->crateInst = NULL;
            mw->velocity[0] = 0;
            mw->velocity[1] = 0;
            mw->velocity[2] = 0;
            mw->boolDestroyed = 0;
            mw->unk24 = 0;
            mw->extraFlags = 0;

            RB_MinePool_add(mw);

            mw->maxHeight = inst->matrix.t[1];
        }
    }
}