int RefreshCard_BoolGhostForLEV(u_short trackID)
{
  short numGhost = 0;

  // if ghost profiles are present
  if (sdata->numGhostProfilesSaved){
    // loop through ghost profiles
    for (char i = 0; i < sdata->numGhostProfilesSaved - 1; i++)
    {
      // Check trackID of each profile
      if (sdata->ghostProfile_memcard[i].trackID == trackID)
      {
        numGhost++;
      }
    }
  }
  return numGhost;
}