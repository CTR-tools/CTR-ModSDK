#include <common.h>

void AH_SaveObj_ThTick(struct Thread*);
void AH_SaveObj_ThDestroy(struct Thread*);

void DECOMP_AH_SaveObj_LInB(struct Instance* savInst)
{
    short rot[3];

    struct GameTracker* gGT = sdata->gGT;
    struct Thread* saveTh;
    struct Instance* inst;
    struct SaveObj* save;

    // if this Instance's thread is not valid
    if (savInst->thread == NULL)
    {
        saveTh = THREAD_BirthWithObject(
			SIZE_RELATIVE_POOL_BUCKET(
				sizeof(struct SaveObj),
				NONE,
				SMALL,
				STATIC),
			AH_SaveObj_ThTick, 0, 0);

        savInst->thread = saveTh;

        // if the thread was built properly
        if (saveTh != NULL)
        {
            save = saveTh->object;

            saveTh->inst = savInst;

            saveTh->funcThDestroy = AH_SaveObj_ThDestroy;

            // initialize object
            save->flags = 0;

            save->scanlineFrame = 0;

            // make invisible
            savInst->flags |= 0x80;

            if (gGT->level1->numSpawnType2_PosRot == 0)
            {
                save->inst = NULL;
            }
            // if numSpawn1 is more than zero
            else
            {
            // DAT_800aba80
            // "scan"

            inst = INSTANCE_Birth3D(gGT->modelPtr[0x78], 0, 0);

            inst->matrix.m[0][0] = savInst->matrix.m[0][0];
            inst->matrix.m[0][2] = savInst->matrix.m[0][2];
            inst->matrix.m[1][1] = savInst->matrix.m[1][1];
            inst->matrix.m[2][0] = savInst->matrix.m[2][0];
            inst->matrix.m[2][2] = savInst->matrix.m[2][2];

            inst->matrix.t[0] = savInst->matrix.t[0];
            inst->matrix.t[1] = savInst->matrix.t[1];
            inst->matrix.t[2] = savInst->matrix.t[2];

            rot[0] = gGT->level1->ptrSpawnType2_PosRot->posCoords[3];
            rot[1] = gGT->level1->ptrSpawnType2_PosRot->posCoords[4];
            rot[2] = gGT->level1->ptrSpawnType2_PosRot->posCoords[5];

            ConvertRotToMatrix(&inst->matrix, &rot);

            inst->matrix.t[0] = (int)gGT->level1->ptrSpawnType2_PosRot->posCoords[0];
            inst->matrix.t[1] = (int)gGT->level1->ptrSpawnType2_PosRot->posCoords[1];
            inst->matrix.t[2] = (int)gGT->level1->ptrSpawnType2_PosRot->posCoords[2];

            inst->unk50 = 0xf8;

            save->inst = inst;
            }
        }
    }
    return;
}