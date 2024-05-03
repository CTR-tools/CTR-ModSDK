#include <common.h>

void CS_Podium_Stand_Init(u_short *);
void CS_Podium_Prize_Init(u_int, char*, short *);
int CS_Thread_Init(u_int, char*, short *, short, u_int);
void CS_Podium_Camera_ThTick(int param_1);

void DECOMP_CS_Podium_FullScene_Init()
{
	struct Instance *driverInstSelf;
	struct Thread *victoryCamThread;
	u_int podiumMusic;
	
	struct
	{
		// podium position
		// X Y Z and ?
		short podiumPos[4];
		
		// character position
		// X Y Z and ?
		short characterPos[4];
		
		// rotation (for both)
		// X Y Z and ?
		short rot[4];
		
		// matrix
		u_int local_30;
		u_int local_2c;
		u_int local_28;
		u_int local_24;
		u_int local_20;
	} InitData;
	
	struct PosRot
	{
		short pos[3];
		short rot[3];
	};
	
	struct PosRot* posRot;
	
	struct GameTracker* gGT = sdata->gGT;

	// assume cutscene did not manipulate audio
	OVR_233.CutsceneManipulatesAudio = 0;
	
	// Make a backup of FX volume, clamp to 0x100
	OVR_233.FXVolumeBackup = howl_VolumeGet(0);
	OVR_233.FXVolumeBackup &= 0xff;
	
	// Make a backup of Music volume, clamp to 0x100
	OVR_233.MusicVolumeBackup = howl_VolumeGet(1);
	OVR_233.MusicVolumeBackup &= 0xff;
	
	// Make a backup of Voice volume, clamp to 0x100
	OVR_233.VoiceVolumeBackup = howl_VolumeGet(2);
	OVR_233.VoiceVolumeBackup &= 0xff;
	
	// Cutscene is now starting
	OVR_233.isCutsceneOver = 0;
	OVR_233.cutsceneState = 0;

	OVR_233.PodiumInitUnk3 = 0;
	
	driverInstSelf = gGT->drivers[0]->instSelf;
	
	OVR_233.PodiumInitUnk2 = 0;
	
	// Make kart model invisible
	driverInstSelf->flags |= 0x80;
	
	DECOMP_VehPhysProc_FreezeEndEvent_Init(driverInstSelf->thread, gGT->drivers[0]);
	
	// Number of Winners = 1
	// this means Draw Confetti on one window
	gGT->numWinners = 1;
	
	// Set winnerIndex[0] to 0, to draw 
	// confetti on the first pushBuffer
	gGT->winnerIndex[0] = 0;
	
	gGT->confetti.numParticles_max = 200;
	gGT->confetti.unk2 = 200;
	gGT->hudFlags &= 0xfe;
	
	// Draw Confetti
	gGT->renderFlags |= 4;
	
	gGT->gameMode2 |= VEH_FREEZE_PODIUM;
	
	// position and rotation of podium scene
	// Y coordinate (podiumPos[1]) has added height
	posRot = gGT->level1->ptrSpawnType2_PosRot[1].posCoords;
	InitData.podiumPos[0] = posRot->pos[0];
	InitData.podiumPos[1] = posRot->pos[1] + 0x80;
	InitData.podiumPos[2] = posRot->pos[2];
	InitData.rot[0] =  posRot->rot[0];
	InitData.rot[1] =  posRot->rot[1];
	InitData.rot[2] =  posRot->rot[2];

	// convert 3 rotation shorts into rotation matrix
	ConvertRotToMatrix(&InitData.local_30, &InitData.rot[0]);
	// Move position of trophy girl
	gte_SetLightMatrix(&InitData.local_30);
	
	// CameraDC, this makes the camera stop following you as it does while racing, it must be zero to follow you
	gGT->cameraDC[0].cameraMode = 3;
	
	// if someone placed third
	if (gGT->podium_modelIndex_Third != '\0')
	{
		InitData.characterPos[0] = 299;
		InitData.characterPos[1] = 0xffab;
		InitData.characterPos[2] = 0;
	
		// create thread for "third"
		CS_Thread_Init(gGT->podium_modelIndex_Third, &OVR_233.s_third[0], (void*)&InitData, 0x600, 0);
	}
	
	// if someone placed second
	if (gGT->podium_modelIndex_Second != '\0')
	{
		InitData.characterPos[0] = 0xfed5;
		InitData.characterPos[1] = 0xffd6;
		InitData.characterPos[2] = 0;
	
		// create thread for "second"
		CS_Thread_Init(gGT->podium_modelIndex_Second, &OVR_233.s_second[0], (void*)&InitData, 0x200, 0);
	}
	
	InitData.characterPos[0] = 0;
	InitData.characterPos[1] = 0;
	InitData.characterPos[2] = 0;
	
	// create thread for "first"
	CS_Thread_Init(gGT->podium_modelIndex_First, &OVR_233.s_first[0], (void*)&InitData, 0, 0);
	
	InitData.characterPos[0] = 0x1a8;
	InitData.characterPos[1] = 0xff80;
	InitData.characterPos[2] = 0x140;
	
	// create thread for trophy girl (internally called "tawna")
	CS_Thread_Init(gGT->podium_modelIndex_tawna, &OVR_233.s_tawna[0], (void*)&InitData, -0x2aa, 0);
	
	CS_Podium_Prize_Init(gGT->podiumRewardID, &OVR_233.s_prize[0], (void*)&InitData);
	
	CS_Podium_Stand_Init((void*)&InitData);
	
	// PROC_BirthWithObject
	// 0x4 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0xf = camera thread bucket
	victoryCamThread = (struct Thread *)PROC_BirthWithObject(0x4030f, (u_int)CS_Podium_Camera_ThTick, 0, 0);
	
	// if it allocated correctly
	if (victoryCamThread != 0) 
	{
		// initialize first "short" of the object to zero
		*(short*)victoryCamThread->object = 0;
	}

	// change victory music based on who is first in the podium
	switch(gGT->podium_modelIndex_First-0x7e)
	{
		// Crash, Coco, Fake Crash
		case 0:
		case 3:
		case 0xE:
			// Crash's music
			podiumMusic = 10;
			break;
		
		// Cortex, NGin, NTrophy
		case 1:
		case 4:
		case 0xC:
			// Cortex's music
			podiumMusic = 8;
			break;
		
		// Polar Pura
		case 6:
		case 7:
			// Polar and Pura's music
			podiumMusic = 7;
			break;
		
		// pinstripe kjoe
		case 8:
		case 0xb:
			// Pinstripe's music
			podiumMusic = 0xb;
			break;
		
		// papu, roo, penta
		case 9:
		case 10:
		case 0xD:
			// Ripper Roo's music
			podiumMusic = 9;
			break;
		
		// Tiny, Dingo, Oxide
		default:
			// Default music is Tiny Tiger's
			podiumMusic = 0xc;
			break;
	}

	DECOMP_CDSYS_XAPlay(0, podiumMusic);
  
	return;
}
