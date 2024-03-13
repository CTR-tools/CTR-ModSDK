#include <common.h>

void VehStuckProc_RIP_Init(struct Thread*, struct Driver*);

void DECOMP_RB_Player_KillPlayer(struct Driver* player_1, struct Driver* player_2)
{
  struct GameTracker* gGT = sdata->gGT;
  u_int gameMode;
  char teamsAlive;
  char deadPlayers;
  char boolIsTeamAlive[4];
  char numPlyr;
  char currTeam;
  char cVar3;

  gameMode = gGT->gameMode1;
  numPlyr = numPlyr;
  
  // quit if not in battle mode, or if 
  // either driver is nullptr
  
  if ((gameMode & 0x20) == 0) return;
  if (player_1 == NULL) return;
  if (player_2 == NULL) return;
  
  // If you dont have a Point Limit (battle)
  if ((gameMode & 0x4000) == 0) {
	  
	// If you dont have a Life Limit (battle)
    if ((gameMode & 0x8000) == 0) {
		
	  // Quit the function
      return;
    }
	
	// If you are here, this is LIFE limit
	
	// subtract a life from player
    cVar3 = player_2->BattleHUD.numLives + -1;
	
    deadPlayers = 0;
    
	// if player is alive
	if (cVar3) 
	{
	  // set new number of lives
      player_2->BattleHUD.numLives = cVar3;
	  
	  // leave function
      return;
    }
	
	// if you get here, then player is out of lives
	
    memset(boolIsTeamAlive,0,8);
	
    teamsAlive = 0;
	
    player_2->funcPtrs[0] = VehStuckProc_RIP_Init;
	
	// set lives to zero
    player_2->BattleHUD.numLives = 0;
	
	// the race (or battle) is now over for this driver
    player_2->actionsFlagSet |= 0x2000000;

	// if there are players
    if (numPlyr) 
	{
	  // loop through all players
      for (cVar3 = 0; cVar3 < numPlyr; cVar3++)
	  {
		// If the race is not over for this driver
        if ((gGT->drivers[cVar3]->actionsFlagSet & 0x2000000) == 0) 
		{
          boolIsTeamAlive[gGT->drivers[cVar3]->BattleHUD.teamID] = 1;
        }
		
		// if race is over for this player
        else 
		{
		  // keep count of drivers dead
          deadPlayers += 1;
        }
      } 
    }
	
	// dead driver -> battleHUD.teamID
    currTeam = player_2->BattleHUD.teamID;
	
    if (
			// if driver team exists
			((gGT->battleSetup.teamFlags & 1 << currTeam) != 0) &&
			
			// if no remaining players alive on team
			(boolIsTeamAlive[currTeam] == 0)
		) 
	{
      if ((numPlyr - deadPlayers) < 3) 
	  {
		// increment gGT Standing Points by 1,
		// record how many times players finished in each rank
        gGT->standingsPoints[currTeam * 3 + (numPlyr - deadPlayers)] += 1;
      }
	  
	  // save the rank that each team finished
      gGT->battleSetup.finishedRankOfEachTeam[player_2->BattleHUD.teamID] = numPlyr - deadPlayers;
    }
	
	// count all living teams
	// loop through all teams
    for (currTeam = 0; currTeam < 4; currTeam++)
	{
      if (
			// if team exists
			((gGT->battleSetup.teamFlags & 1 << currTeam) != 0) && 
			
			// if someone is alive on this team
			(boolIsTeamAlive[currTeam] != 0)
		 ) 
	  {
		// count living teams
        teamsAlive += 1;
      }
    }
	
	// if there is not only one team alive
    if (teamsAlive > 1) 
	  // no winner found yet
      return;
	
	// at this point, a winner is found,
	// end the game for all drivers
    
	// if there are players
	if (numPlyr) {
      
	  // loop through all players
	  for (cVar3 = 0; cVar3 < numPlyr; cVar3++)
	  {  
		// The race (or battle) is now over for this driver
		  gGT->drivers[cVar3]->actionsFlagSet |= 0x2000000;
      }
    }
  }
  
  // if Point Limit
  else {
    
	// if driver hit themself
	if (player_2->BattleHUD.teamID == player_1->BattleHUD.teamID) 
	{
	  // subtract a point
      cVar3 = gGT->battleSetup.pointsPerTeam[player_2->BattleHUD.teamID] + -1;

      if (cVar3 < -9) 
	  {
		// can't go lower than -9
        return;
      }
	  
	  // save new score
      gGT->battleSetup.pointsPerTeam[player_2->BattleHUD.teamID] = cVar3;
      return;
    }
	
	// add point to player who got a hit
    cVar3 = gGT->battleSetup.pointsPerTeam[player_1->BattleHUD.teamID] + 1;
	
	// if scores is less than 100
    if (cVar3 < 100) 
	{
	  // increment score
      gGT->battleSetup.pointsPerTeam[player_1->BattleHUD.teamID] = cVar3;
    }
	
	
	// if amount of points earned by this driver is not equal to the winning amount
    if (gGT->battleSetup.pointsPerTeam[player_1->BattleHUD.teamID] != gGT->battleSetup.killLimit) 
      return;
	
	// if this is a time-limit game
    if ((gameMode & 0x10000) != 0) 
      return;
	
	// if this is not a time-limit game,
	// and the last kill has been made,
	// then end the game
	
	// if there are drivers
    if (numPlyr) {
      
	  // loop through all drivers
	  for (cVar3 = 0; cVar3 < numPlyr; cVar3++)
	  {
		// the race (or battle) is now over for this driver
        gGT->drivers[cVar3]->actionsFlagSet |= 0x2000000;
      } 
    }
  }
  
  MainGameEnd_Initialize();
  return;
}
 