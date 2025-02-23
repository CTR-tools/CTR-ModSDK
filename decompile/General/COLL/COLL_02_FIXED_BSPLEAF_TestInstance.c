#include <common.h>

void DECOMP_COLL_FIXED_BSPLEAF_TestInstance(struct BSP *node, struct ScratchpadStruct *sps)
{
    int arraySize;
    struct BSP *bspArray = node->data.leaf.bspHitboxArray;
    struct BoundingBox *bbox;

    if (bspArray == NULL)
		return;
    
    // check every instance hitbox until
    // end of list (null flag) is found
    for (/**/; bspArray->flag != 0; bspArray++)
    {
		bbox = &bspArray->box;
		
        // 1F8001CC
        arraySize = sps->numInstHitboxesHit - 1;
        for (;arraySize >= 0; arraySize--)
        {
            if (bspArray == sps->bspInstHitboxArr[arraySize])
                goto NextBSP;
        }

        if (
			(
                // if data is invalid (what?)
                (
                    // if collision for instance is disabled
                    ((bspArray->flag & 0x80) == 0) ||
                    // if bspHitbox.InstDef doesn't exist
                    (bspArray->data.hitbox.instDef == NULL)
                ) 
                
                ||

                // if data is valid

                // allows drawing flag is enabled
                ((bspArray->data.hitbox.instDef->ptrInstance->flags & 0xf) != 0)
            ) &&

            // compare bsp boundingbox to scratchpad boundingbox
            (
				(sps->bbox.min[0] <= bbox->max[0]) &&

				(bbox->min[0] <= sps->bbox.max[0]) &&

				(sps->bbox.min[1] <= bbox->max[1]) &&

				(bbox->min[1] <= sps->bbox.max[1]) &&

				(sps->bbox.min[2] <= bbox->max[2]) &&

				(bbox->min[2] <= sps->bbox.max[2])
			)
		  )
        {
            // check with collision for this instance
            COLL_FIXED_INSTANC_TestPoint(sps, bspArray);
        }

		NextBSP:
    }
    
}