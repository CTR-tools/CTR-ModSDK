#include <common.h>

struct Model* VehBirth_GetModelByName(char *searchName)
{
    struct Model *m;
    struct Model **models;
    int i;

    // array to character models loaded,
    // maximum of 4, used in VS mode
    models = (struct Model **)&data.driverModel_lowLOD[0];

	#ifdef USE_HIGH1P
	#define NUM_CHECK 8 // modding: 8 drivers
	#else
	#define NUM_CHECK 3 // OG game: 3 drivers in VS mode
	#endif

    for (i = 0; i < NUM_CHECK; i++)
    {
        m = models[i];

        // 12/16 bytes is enough
        if (
				(m != NULL) &&
				(*(u_int *)&m->name[0] == *(u_int *)&searchName[0]) &&
				(*(u_int *)&m->name[4] == *(u_int *)&searchName[4]) &&
				(*(u_int *)&m->name[8] == *(u_int *)&searchName[8]) &&
				(*(u_int *)&m->name[12] == *(u_int *)&searchName[12])
			)
        {
            // character found, return pointer
            return m;
        }
    }

	models = sdata->PLYROBJECTLIST;

    if (
			// list is valid, and first element is valid
			(models != NULL) &&
			(models[0] != NULL)
		)
    {
        // loop until all strings are checked (until current is not nullptr)
        for (
				i = 0,	m = models[i]; 
				m != NULL; 
				i++,	m = models[i]
			)
        {
			// 12/16 bytes is enough
            if (
					(*(u_int *)&m->name[0] == *(u_int *)&searchName[0]) &&
					(*(u_int *)&m->name[4] == *(u_int *)&searchName[4]) &&
					(*(u_int *)&m->name[8] == *(u_int *)&searchName[8]) &&
					(*(u_int *)&m->name[12] == *(u_int *)&searchName[12])
				)
            {
                // character found, return pointer
                return m;
            }
        }
    }
    return NULL;
}