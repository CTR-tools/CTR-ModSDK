#include <common.h>

void Particle_FuncPtr_ExhaustUnderwater(struct Particle *p);

struct Particle *VehEmitter_Exhaust(struct Driver *d, VECTOR *param_2, VECTOR *param_3)
{
    if (((d->instSelf->flags & SPLIT_LINE) != 0) && ((param_2->vy - param_3->vy) + d->posCurr[1] < 256))
    {
        struct Particle* p = Particle_Init(0, sdata->gGT->iconGroup[7], &data.emSet_Exhaust_Water[0]);

        p->funcPtr = Particle_FuncPtr_ExhaustUnderwater;

        if (p == NULL) return p;

        for (char i = 0; i < 3; i++){
            p->axis[i].startVal += (((int*)param_2)[i] - ((int*)param_3)[i]);
            p->axis[i].velocity = ((int*)param_3)[i];
        }

        p->unk18 = d->instSelf->unk50;
        p->driverInst = d->instSelf;
    }
}