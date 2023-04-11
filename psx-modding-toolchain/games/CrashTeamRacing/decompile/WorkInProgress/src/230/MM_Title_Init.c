#include <common.h>

int MM_Title_ThTick(struct Thread*);

void DECOMP_MM_Title_Init(void) 
{
  struct GameTracker* gGT = sdata->gGT;
  struct Thread* threadTitle;
  struct Instance* titleInst;
  struct Title* titleObj = *(int*)0x800b59a0;
  int i;
  int *piVar8;
  int *piVar9;
  
  if (
		(
			(
				// if "title" object is nullptr
				(titleObj == NULL) && 
				
				// if you are in main menu
				((gGT->gameMode1 & 0x2000) != 0)
			) &&
			(*(unsigned char*)0x800b5a1c != 2)
		) &&
		(
			(
				// model ptr (Title blue Ring)
				gGT->modelPtr[0x68] != 0 &&
				
				// LEV -> trial_data -> numPointers > 2
				(2 < gGT->level1->ptrSpawnType1->count)
			)
		)
	 ) 
  {
	
	// CameraDC, freecam mode
    gGT->cameraDC->cameraMode = 3;
	
    gGT->tileView[0].distanceToScreen_CURR = 0x1c2;
	
	// pointer to Intro Cam, to view Crash holding Trophy in main menu
    *(unsigned int *)0x800b5a34 = gGT->level1->ptrSpawnType1->pointers;
    
	// 0x24 = size
	// 0 = no relation to param4	
	// 0x200 = MediumStackPool
	// 0xd = "other" thread bucket
	threadTitle = THREAD_BirthWithObject(0x24020d,MM_Title_ThTick,OVR_230.s_title,0);
	
	// Get object of title screen that was just built
    piVar9 = threadTitle->object;
	
	// store object globally
    titleObj = piVar9;
	
	// Memset, 0x24 bytes large
    memset(piVar9,0,0x24);
	
	// store pointer to thread inside object
    *piVar9 = threadTitle;
	
    piVar8 = piVar9;
    
	// create 6 instances
	for (i = 0; i < 6; i++) 
	{
	  // increment to next pointer in object,
	  // which is where instance pointers start
      piVar8 += 1;
	  
      titleInst = INSTANCE_Birth3D(
              (gGT->ptrModel[OVR_230.titleInstances[i].modelID]),OVR_230.s_title,threadTitle);
      
	  // store instance
	  *piVar8 = &titleInst;
      
	  if (OVR_230.titleInstances[i].boolApplyFlag != 0) 
	  { 
        // visible during gameplay
        titleInst->flags |= 0x2000000;
      }
	  
	  // naughty dog typo?
      titleInst->matrix.m[0][0] = 0x1000;
      titleInst->matrix.m[1][0] = 0x1000;
      titleInst->matrix.m[1][1] = 0x5000;
      titleInst->matrix.m[1][0] = 0x5000;
      titleInst->matrix.m[0][0] = 0x5000;
      titleInst->matrix.m[0][2] = 0;
      titleInst->matrix.m[1][2] = 0;
	  
	  // Position
      titleInst->matrix.t[0] = 0;
      titleInst->matrix.t[1] = 0;
      titleInst->matrix.t[2] = 0;
	  
	  // make invisible
      titleInst->flags |=  0x80;
	  
	  // if multiplayer
      if (1 < gGT->numPlyrCurrGame) {
        for (i = 1; i < gGT->numPlyrCurrGame; i++)
        {
          titleInst->idpp[i].tileView->pos[0] = 0;
        } 
      }
    }
	
    MM_Title_CameraMove(piVar9,0);
  }
  return;
} 
 