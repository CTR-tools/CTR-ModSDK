#include <ovr_233.h>

int THREAD_BirthWithObject(u_int, u_int, char*, int);
void CS_Podium_Stand_Init(u_short *);
void CS_Podium_Prize_Init(u_int, char*, short *);
short howl_VolumeGet(int volumeType);
void Player_Freeze_Init(struct Thread* t, struct Driver* d);
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
	
	driverInstSelf = sdata->gGT->drivers[0]->instSelf;
	
	OVR_233.PodiumInitUnk2 = 0;
	
	// Make kart model invisible
	driverInstSelf->flags |= 0x80;
	
	Player_Freeze_Init(driverInstSelf->thread, sdata->gGT->drivers[0]);
	
	// Number of Winners = 1
	// this means Draw Confetti on one window
	sdata->gGT->numWinners = 1;
	
	// Set winnerIndex[0] to 0, to draw 
	// confetti on the first tileView
	sdata->gGT->winnerIndex[0] = 0;
	
	sdata->gGT->confetti.numParticles_max = 200;
	sdata->gGT->confetti.unk2 = 200;
	sdata->gGT->hudFlags &= 0xfe;
	
	// Draw Confetti
	sdata->gGT->renderFlags |= 4;
	
	sdata->gGT->gameMode2 |= 4;
	
	struct PosRot
	{
		short pos[3];
		short rot[3];
	};
	
	// position and rotation of podium scene
	// Y coordinate (podiumPos[1]) has added height
	InitData.podiumPos[0] = ((struct PosRot*)(*(int*)((int)sdata->gGT->level1->ptr_spawn_arrays + 0xC)))->pos[0];
	InitData.podiumPos[1] = ((struct PosRot*)(*(int*)((int)sdata->gGT->level1->ptr_spawn_arrays + 0xC)))->pos[1] + 0x80;
	InitData.podiumPos[2] = ((struct PosRot*)(*(int*)((int)sdata->gGT->level1->ptr_spawn_arrays + 0xC)))->pos[2];
	InitData.rot[0] =  ((struct PosRot*)(*(int*)((int)sdata->gGT->level1->ptr_spawn_arrays + 0xC)))->rot[0];
	InitData.rot[1] =  ((struct PosRot*)(*(int*)((int)sdata->gGT->level1->ptr_spawn_arrays + 0xC)))->rot[1];
	InitData.rot[2] =  ((struct PosRot*)(*(int*)((int)sdata->gGT->level1->ptr_spawn_arrays + 0xC)))->rot[2];

	// convert 3 rotation shorts into rotation matrix
	ConvertRotToMatrix(&InitData.local_30, &InitData.rot[0]);
	// Move position of trophy girl
	gte_SetLightMatrix(&InitData.local_30);
	
	// CameraDC, this makes the camera stop following you as it does while racing, it must be zero to follow you
	sdata->gGT->cameraDC[0].cameraMode = 3;
	
	// if someone placed third
	if (sdata->gGT->podium_modelIndex_Third != '\0')
	{
		InitData.characterPos[0] = 299;
		InitData.characterPos[1] = 0xffab;
		InitData.characterPos[2] = 0;
	
		// create thread for "third"
		CS_Thread_Init(sdata->gGT->podium_modelIndex_Third, &OVR_233.s_third[0], (void*)&InitData, 0x600, 0);
	}
	
	// if someone placed second
	if (sdata->gGT->podium_modelIndex_Second != '\0')
	{
		InitData.characterPos[0] = 0xfed5;
		InitData.characterPos[1] = 0xffd6;
		InitData.characterPos[2] = 0;
	
		// create thread for "second"
		CS_Thread_Init(sdata->gGT->podium_modelIndex_Second, &OVR_233.s_second[0], (void*)&InitData, 0x200, 0);
	}
	
	InitData.characterPos[0] = 0;
	InitData.characterPos[1] = 0;
	InitData.characterPos[2] = 0;
	
	// create thread for "first"
	CS_Thread_Init(sdata->gGT->podium_modelIndex_First, &OVR_233.s_first[0], (void*)&InitData, 0, 0);
	
	InitData.characterPos[0] = 0x1a8;
	InitData.characterPos[1] = 0xff80;
	InitData.characterPos[2] = 0x140;
	
	// create thread for trophy girl (internally called "tawna")
	CS_Thread_Init(sdata->gGT->podium_modelIndex_tawna, &OVR_233.s_tawna[0], (void*)&InitData, -0x2aa, 0);
	
	CS_Podium_Prize_Init(sdata->gGT->podiumRewardID, &OVR_233.s_prize[0], (void*)&InitData);
	
	CS_Podium_Stand_Init((void*)&InitData);
	
	// THREAD_BirthWithObject
	// 0x4 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0xf = camera thread bucket
	victoryCamThread = (struct Thread *)THREAD_BirthWithObject(0x4030f, (u_int)CS_Podium_Camera_ThTick, &OVR_233.s_victorycam[0], 0);
	
	// if it allocated correctly
	if (victoryCamThread != 0) 
	{
		// initialize first "short" of the object to zero
		victoryCamThread->object = 0;
	}

	// change victory music based on who is first in the podium
	switch(sdata->gGT->podium_modelIndex_First)
	{
		case 0x7e:
		case 0x81:
		case 0x8c:
			// Crash's music
			podiumMusic = 10;
			break;
		case 0x7f:
		case 0x82:
		case 0x8a:
			// Cortex's music
			podiumMusic = 8;
			break;
		default:
			// Default music is Tiny Tiger's
			podiumMusic = 0xc;
			break;
		case 0x84:
		case 0x85:
			// Polar and Pura's music
			podiumMusic = 7;
			break;
		case 0x86:
		case 0x89:
			// Pinstripe's music
			podiumMusic = 0xb;
			break;
		case 0x87:
		case 0x88:
		case 0x8b:
			// Ripper Roo's music
			podiumMusic = 9;
	}

	CDSYS_XAPlay(0, podiumMusic);
  
	return;
}