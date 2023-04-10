#include <common.h>

// Search for character model by string,
// specific to main menu lev, altered in oxide mod
struct Model* DECOMP_MM_Characters_SearchModelByString(int *name) {
  struct Model** models;
  struct Model* model;

  // if LEV is valid
  if (sdata->gGT->level1 != NULL)
    return NULL;

  models = sdata->gGT->level1->ptrModelsPtrArray;
  // loop through all models until nullptr is found
  for (model = models[0]; model != NULL; models += 1, model = models[0]) {
    // if model exists, check first 4 bytes for name
    if (*model == *name) {
      // return model pointer
      return model;
    }
  }
  return NULL;
}