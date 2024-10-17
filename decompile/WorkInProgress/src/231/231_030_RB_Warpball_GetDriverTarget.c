#include <common.h>

struct Driver* RB_Warpball_GetDriverTarget(struct TrackerWeapon *tw, struct Instance *inst)
{
    u_int distToFinish;
    int currDistance;
    int index;
    int iVar4;
    
    struct Driver* currDriver = NULL;
    struct Driver* hitDriver = NULL;

    // if 10 wumpa fruit were not used
    if ((tw->flags & 1) == 0)
    {
        for (index = 0; index < 8; index++)
        {
            // check next driver until you get the driver
            // farthest in the lead, that has not finished race
            currDriver = sdata->gGT->drivers[index];

            // if driver is valid
            if (((currDriver != NULL) &&

                    // if driver is not the same as driver that fired warpball
                    (currDriver != tw->driverParent)) &&

                // if the race is not over for this driver
                ((currDriver->actionsFlagSet & 0x2000000) == 0))
            {
                return currDriver;
            }
        }
    }

    // if 10 wumpa fruit were used
    else
    {
        // start of lev->path
        struct CheckpointNode* cn = &sdata->gGT->level1->ptr_restart_points[0];

        // node1
        struct CheckpointNode* node1 = &cn[tw->ptrNodeCurr->nextIndex_forward];

        // node2
        struct CheckpointNode* node2 = &cn[node1->nextIndex_forward];

        u_int distToFinish = cn->distToFinish * 8;

        short vec1[4];
        // direction from node1 to node2
        vec1[0] = node1->pos[0] - node2->pos[0];
        vec1[1] = node1->pos[1] - node2->pos[1];
        vec1[2] = node1->pos[2] - node2->pos[2];

        MATH_VectorNormalize(&vec1[0]);

        short vec2[4];
        // direction from orb to node1
        vec2[0] = inst->matrix.t[0] - node1.pos[0];
        vec2[1] = inst->matrix.t[1] - node1.pos[1];
        vec2[2] = inst->matrix.t[2] - node1.pos[2];

        // replace R11R12 and R13R21
	  	gte_ldsvrtrow0(&vec1[0]);

	  	gte_ldv0(&vec2[0]);

        gte_mvmva(0,0,0,3,0);

        // replace stMAC1
        gte_stlvnl0(&iVar4);
        
        u_int maxDistance = 0x7fffffff;

        iVar4 = node1->distanceToFinish * 8 + (iVar4 >> 0xc) + 0x200;
        
        #if 0
        if (uVar1 == 0)
        {
            trap(0x1c00);
        }
        if ((distToFinish == -1) && (iVar4 == -0x80000000))
        {
            trap(0x1800);
        }
        #endif

        for (index = 0; index < 8; index++)
        {
            // pointer to structure of each player
            currDriver = sdata->gGT->drivers[index];

             // if driver is valid
            if (((currDriver != NULL) &&
                    ((tw->driversHit & 1 << (index & 0x1fU)) == 0)) &&
                ((
                    // If the race is not over for this player
                    (currDriver->actionsFlagSet & 0x2000000) == 0 &&

                    // If you are not being mask-grabbed
                    (currDriver->kartState != KS_MASK_GRABBED))))
            {
                currDistance = iVar4 % distToFinish - currDriver->distanceToFinish_curr;
                
                if (currDistance < 0)
                {
                    currDistance += distToFinish;
                }
                if (currDistance < maxDistance)
                {
                    maxDistance = currDistance;
                    hitDriver = currDriver;
                }
            }
        }
    }
    return hitDriver;
}
