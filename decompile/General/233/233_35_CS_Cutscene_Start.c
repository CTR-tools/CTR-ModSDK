#include <common.h>

extern unsigned char BoxSceneArr[20];

// for oxide intro and ND box
void DECOMP_CS_Cutscene_Start(void)
{
  // stack allocation
  struct CsThreadInitData initData;

  struct GameTracker *gGT = sdata->gGT;

  // no instance, no initData required,
  // this automatically starts the "introcam" thread
  CS_Thread_Init(0, 0, 0, 0, 0);

  // If this is the Naughty Dog Box Scene
  if (gGT->levelID == NAUGHTY_DOG_CRATE)
  {
	// nullify
	int* ptrIntArr = &initData;
	for(int i = 0; i < sizeof(struct CsThreadInitData)/4; i++)
		ptrIntArr[i] = 0;

    CS_Instance_InitMatrix();

	for(int i = 0; i < 19; i++)
	{
		CS_Thread_Init(BoxSceneArr[i], 0, &initData, 0, 0);
	}
  }

  // if going to credits
  if ((gGT->gameMode2 & CREDITS) != 0)
  {
    OVR_233.isCutsceneOver = 0;

    CS_Credits_Init();

    CS_Instance_InitMatrix();
  }
}

// Should be 19 large
unsigned char BoxSceneArr[20] =
{
	0xb6, // BOX1
	0xb7, // BOX2
	0xb8, // BOX2_BOTTOM
	0xb9, // BOX2_FRONT
	0xba, // BOX2_A
	0xbb, // BOX3
	0xbc, // CODE
	0xbd, // GLOW
	0xbe, // LID
	0xc9, // LIDB
	0xca, // LIDC
	0xcb, // LIDD
	0xbf, // LID2

	193, // KART0
	194, // KART1
	195, // KART2
	196, // KART3

	// --- cut by ND

	199, // KART6
	200, // KART7

	-1, // NULL
};