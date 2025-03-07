#include <common.h>
#include "utils.h"

struct Model* SearchModel(char *searchName)
{
    struct Model *m;

    int i = 0;
    int j = 0;
    struct Model** models[] = { CHAR_MODEL_PTRS, (struct Model**)sdata->PLYROBJECTLIST, (struct Model**)NULL };
    while (true)
    {
        while (models[j][i] == NULL)
        {
            if (models[++j] == NULL) { return NULL; }
            i = 0;
        }
        if (strncmp(models[j][i]->name, searchName, 16) == 0) { return models[j][i]; }
        i++;
    }
    return NULL;
}