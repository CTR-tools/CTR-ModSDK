#include <common.h>

void DECOMP_UI_CupStandings_UpdateCupRanks(void)
{
  struct GameTracker *gGT;
  int totalNumCharacters;
  u_int checked;
  short rank;
  u_int currIndex;
  short highestPts;

  gGT = sdata->gGT;
  totalNumCharacters = gGT->numBotsNextGame + gGT->numPlyrCurrGame;
  checked = 0;

  // set highest numPoints value to zero
  highestPts = 0;
  // set driver index of highest score to zero
  currIndex = 0xffffffff;

  if (totalNumCharacters != 0) {
    for(int i = 0; i < totalNumCharacters; i++)
	{
        highestPts = 0;
        currIndex = 0xffffffff;
        rank = -1;
        for (int j = totalNumCharacters - 1; j > -1; j--) {
          if (
				// if number of points held by this player
				// is more than the biggest number found yet
				(highestPts <= gGT->cup.points[j]) &&
                !(checked & (1 << j)))
		  {
			// set new highest score found
            highestPts = gGT->cup.points[j];

            if (currIndex != 0xffffffff)
			{
              checked &= ~(1 << currIndex);
            }
            checked |= 1 << j;

			// set ID of driver with highest score
            currIndex = j;
          }
          // set rank by the current order
          rank = currIndex;
        } 
	  // Update cup rank of each player
      data.cupPositionPerPlayer[i] = rank;
    }
  return;
  }
}