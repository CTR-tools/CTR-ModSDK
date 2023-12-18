#include <common.h>

/// @brief Process "flipbook" texture animation for the provided list of models.
/// @param numModels - number of models to process. negative value means loops until NULL is met
/// @param pModels - pointer to array of model pointers
/// @param timer
void DECOMP_CTR_CycleTex_AllModels(unsigned int numModels, struct Model** pModelArray, int timer)
{
    struct Model * pModel;
    struct ModelHeader * pHeader;

    for(int i = 0; i < numModels; i++)
	{
		pModel = pModelArray[i];
		if(pModel == 0) return;
		
        //iterate over all model headers
        for (int j = 0; j < pModel->numHeaders; j++)
        {
			pHeader = &pModel->headers[j];
			
            if ((pHeader->animtex != NULL) && ((pHeader->flags & 2) == 0) )
            {
                DECOMP_CTR_CycleTex_Model(pHeader->animtex, timer);
            }
        }
    }
}