#include <common.h>

void VehLap_UpdateProgress(struct Driver *driver)
{
    u_short maxDist;
    u_int uVar5;
    struct QuadBlock *qb;
    struct CheckpointNode *nodes;
    struct CheckpointNode *node1;
    struct CheckpointNode *node2;
    struct CheckpointNode *quadnode;
    int progress;
    int iVarX;
    int iVarY;
    short index;
    SVec3 vec2;
    SVec3 vec1;
    struct GameTracker *gGT = sdata->gGT;
    // uint local_1c;

    // if player structure is not nullptr
    if (driver != NULL)
    {
        index = -1;

        // If this is human and not an AI
        if ((driver->actionsFlagSet & 0x100000) == 0)
        {
            // quadblock (last valid)
            qb = driver->lastValid;

            if (
                // if quadblock exists
                (qb != NULL) &&

                // quadBlock -> checkpointIndex is valid
                (qb->checkpointIndex != -1))
            {
                index = qb->checkpointIndex;
            }
        }

        // If this is an AI
        else
        {
            // duplicate of quadblock checkpointIndex (AI-exclusive)
            index = driver->ai_quadblock_checkpointIndex;
        }

        // if level has respawn points
        if ((gGT->level1->cnt_restart_points - 1U < 0xff) &&

            // checkpointIndex is valid
            (-1 < index))
        {
            // array of respawn points
            nodes = gGT->level1->ptr_restart_points;

            // byte offset of respawn point from last-valid quadblock
            quadnode = &nodes[index];

            // pointer to desired respawn point
            node1 = &nodes[quadnode->nextIndex_forward];

            node2 = &nodes[node1->nextIndex_forward];
            vec1.x = node1->pos[0] - node2->pos[0];
            vec1.y = node1->pos[1] - node2->pos[1];
            vec1.z = node1->pos[2] - node2->pos[2];

            // local_1c = local_1c & 0xffff0000 | (node1[2] - node2[2]);

            MATH_VectorNormalize(&vec1);

            // Player X, Y, and Z
            vec2.x = FP8_INT(driver->posCurr.x) - node1->pos[0]; 
            vec2.y = FP8_INT(driver->posCurr.y) - node1->pos[1];
            vec2.z = FP8_INT(driver->posCurr.z) - node1->pos[2];

            #define gte_ldR11R12(r0) __asm__ volatile("ctc2 %0, $0" : : "r"(r0))
            #define gte_ldR13R21(r0) __asm__ volatile("ctc2 %0, $1" : : "r"(r0))
            #define gte_ldR22R23(r0) __asm__ volatile("ctc2 %0, $2" : : "r"(r0))
            
            gte_ldR11R12(*(int*)&vec2.x);
            gte_ldR13R21((vec2.z) | (driver->matrixMovingDir.m[0][2] >> 5));
            gte_ldR22R23((driver->matrixMovingDir.m[1][2] >> 5) | (driver->matrixMovingDir.m[2][2] >> 5));
            gte_ldv0(&vec1);
            gte_mvmva(0, 0, 0, 3, 0);

            gte_stlvnl0(&iVarX);
            gte_stlvnl1(&iVarY);
            progress = node1->distToFinish * 8 + FP_INT(iVarX);

            maxDist = gGT->level1->ptr_restart_points->distToFinish << 3;

#if 0
      if (uVar1 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
        trap(0x1800);
      }
#endif

            // set new progress
            driver->distanceToFinish_curr = progress % maxDist;

            if (iVarY < 0x5a801)
            {
                // uVar5 = Actions Flag set with 9th bit off
                uVar5 = driver->actionsFlagSet & ~(0x100);
            }
            else
            {
                // uVar5 = Actions Flag set with 9th bit on
                uVar5 = driver->actionsFlagSet | 0x100;
            }

            // manage 9th bit of Actions Flag set
            driver->actionsFlagSet = uVar5;

            // if 28th bit of Actions Flag set is on (means ?) and
            if (((driver->actionsFlagSet & 0x8000000) != 0) &&
                (driver->unknown_lap_related[1] != index))
            {
                // save respawn index
                driver->unknown_lap_related[0] = (char)index;

                // turn off 28th bit of Actions Flag set (means ?)
                driver->actionsFlagSet &= ~(0x8000000);
            }
            if (*(char *)(quadnode + 9) != -1)
            {
                // turn on 28th bit of Actions Flag set (means ?)
                driver->actionsFlagSet |= 0x8000000;
            }

            // checkpointIndex
            driver->unknown_lap_related[1] = (char)index;
        }
    }
    return;
}
