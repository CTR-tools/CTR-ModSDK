#include <common.h>

struct CheckpointNode* DECOMP_RB_Warpball_NewPathNode(struct CheckpointNode *cn, struct Driver *d)
{
    u_char currPoint;
    u_int currIndex;
    u_char boolPointExists = false;

    struct GameTracker *gGT = sdata->gGT;

    // if no driver is chased
    if (d == NULL)
    {
    RETURN_NEXT_INDEX:
        return &gGT->level1->ptr_restart_points[cn->nextIndex_forward];
    }

    // pathPoint -> left index
    currIndex = cn->nextIndex_left;

    // if driver is not near that point
    if (d->unknown_lap_related[0] != currIndex)
    {
        // if left point is valid
        if (cn->nextIndex_left != 0xff)
        {
            struct CheckpointNode *currNode = cn;
            for (int i = 0; i < 3; i++)
            {
                // path index
                if (currNode->nextIndex_left == -1)
                {
                    currPoint = currNode->nextIndex_forward;
                }

                // path index
                else
                {
                    currPoint = currNode->nextIndex_left;
                }

                // path node
                currNode = gGT->level1->ptr_restart_points[currPoint];

                // compare path index
                if (d->unknown_lap_related[0] == currNode->nextIndex_forward)
                {
                    boolPointExists = true;
                    break;
                }
            }
        }
        if (!boolPointExists)
            goto RETURN_NEXT_INDEX;
        currIndex = cn->nextIndex_left;
    }

    // new path node
    return &gGT->level1->ptr_restart_points[currIndex];
}