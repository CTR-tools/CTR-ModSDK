#include <common.h>

// FUN_80021ac0
void CTR_CycleTex_AllModels(int numModels, struct Model* pModel[], int timer)
{
    int index = 0;

    if ( pModel[index] == NULL || numModels == 0 ) return; 
    
    do
    {
        if ( pModel[index] == NULL ) return;

        for ( int i = 0; i < pModel[index]->numHeaders; i++ )
        {
            struct ModelHeader* pHeader = pModel[index]->headers;

            if (pHeader[i].unk4 != 0 && pHeader[i].flags & 2)
                CTR_CycleTex_Model((struct AnimTex*)pHeader[i].unk4, timer);
        }

        numModels--;
        index++;
    }
    while (numModels != 0);
}