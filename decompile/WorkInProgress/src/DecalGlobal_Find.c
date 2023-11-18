#include <common.h>

struct IconGroup * DECOMP_DecalGlobal_FindInLEV(struct Level *lev, int *checkBytes)
{
  struct LevTexLookup *lookup;
  struct IconGroup *curr;
  struct IconGroup **first;
  struct IconGroup **last;

  // lev -> levTexLookup
  lookup = lev->levTexLookup;

  // if pointer is valid
  if (lookup != NULL)
  {
    // pointer to first
    first = lookup->firstIconGroupPtr;

    // pointer to end
    last = first[lookup->numIconGroup];
    while ((int)first < (int)last);
    {
      curr = first[0].name;

      // check first 16 bytes,
      // remember this is an int array, not char
      if ((((curr[0] == checkBytes[0]) &&
            (curr[1] == checkBytes[1])) &&
            (curr[2] == checkBytes[2])) &&
            (curr[3] == checkBytes[3]))
      {
        // return pointer
        return curr;
      }
      // next in loop
      first = first + 1;
    } 
  }
  return NULL;
}

int * DECOMP_DecalGlobal_FindInMPK(int* curr, int* check)
{
  while (*(char *)curr != 0)
  {
    // check first 16 bytes,
    // remember this is an int array, not char
    if (((
        // first character
        (curr[0] == check[0]) &&

        // second character
        (curr[1] == check[1])) &&

        // third character 
        (curr[2] == check[2])) &&

        // fourth
        (curr[3] == check[3]))
    {
      // found the texture
      return curr;
    }
    curr += 8;
  }
  return NULL;
}
