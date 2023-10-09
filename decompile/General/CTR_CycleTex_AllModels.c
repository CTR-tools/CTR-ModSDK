#include <common.h>

/// @brief Process "flipbook" texture animation for the provided list of models.
/// @param numModels - number of models to process. negative value means loops until NULL is met
/// @param pModels - pointer to array of model pointers
/// @param timer
void CTR_CycleTex_AllModels(int numModels, struct Model** pModelArray, int timer)
{
    struct Model * pModel;
    struct ModelHeader * pHeader;

    // validate params
    if (pModelArray == NULL || numModels == 0) return;

    do {

        // get model pointer and validate
        if (pModel = *pModelArray, pModel == NULL) return;

        //iterate over all model headers
        for (pHeader = pModel->headers; pHeader < pModel->headers + pModel->numHeaders; pHeader++)
        {
            // if anim tex data is present and some flag is not set
            // TODO: update unk4 name in ModelHeader
            // TODO: replace value 2 with a flag name
            if (pHeader->unk4 != NULL && (pHeader->flags & 2) == 0 )
            {
                CTR_CycleTex_Model(pHeader->unk4, timer);
            }
        }

        numModels--;
        pModelArray++;

    } while (numModels != 0);
}