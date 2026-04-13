#include <common.h>

u_int RefreshCard_GetResult(short searchResult)
{
  // MC_RESULT_FINISHED
  if ((searchResult == 8) && 
      ((sdata->memcardUnk1 & 6) != 0))
  {
    return true;
  }

  u_int boolFound = false;

  if (((sdata->memcardUnk1 & 6) == 0) &&
      // if frame3 == frame4
      (sdata->frame3_memcardAction == sdata->frame4_memcardAction) &&
      (sdata->frame3_memcardSlot == sdata->frame4_memcardSlot))
  {
    // is desired_memcardResult == WhatYouLookFor?
    boolFound = (sdata->desired_memcardResult == searchResult);
  }
  return boolFound;
}