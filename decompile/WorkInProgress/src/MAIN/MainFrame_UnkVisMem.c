#include <common.h>

void MainFrame_UnkVisMem(struct GameTracker *gGT, char screenId)
{
    u_int visSrc; // pointer or not?
    struct PVS *pvs;
    struct QuadBlock *quad;
    struct Driver *d;
    struct mesh_info *mesh;

    d = gGT->drivers[screenId];

    // get quadblock under driver
    quad = d->underDriver;

    mesh = gGT->level1->ptr_mesh_info;

    if (
        // if quadblock exists
        (quad != NULL) &&
        (pvs = quad->pvs,
         pvs != NULL))
    {
        visSrc = pvs->visLeafSrc;

        if (visSrc != NULL)
        {
            if ((visSrc & 1) == 0)
            {
                FUN_80021ea8(

                    gGT->visMem1->visLeafList[screenId],

                    visSrc,

                    // June 1999 calls this "visLeafList"
                    // ptr_mesh_info -> numBSP?
                    (mesh->numBspNodes + 0x1f >> 5) << 2);
            }
            else
            {
                FUN_80021e1c(

                    gGT->visMem1->visLeafList[screenId],

                    visSrc & ~(1 | 2));
            }
        }

        visSrc = pvs->visFaceSrc;

        if (visSrc != NULL)
        {
            if ((visSrc & 1) == NULL)
            {
                FUN_80021ea8(
                    gGT->visMem1->visFaceList[screenId],

                    visSrc,

                    // June 1999 calls this "visFaceList"
                    // ptr_mesh_info -> numQuadBlock?
                    (mesh->numQuadBlock + 0x1f >> 5) << 2);
            }
            else
            {
                FUN_80021e1c(
                    gGT->visMem1->visFaceList[screenId],
                    visSrc & ~(1 | 2));
            }
        }
    }
}