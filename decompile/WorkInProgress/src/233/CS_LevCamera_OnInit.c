#include <common.h>

// for oxide intro and ND box
void CS_LevCamera_OnInit(void)
{
  short local_48;
  short local_46;
  short local_44;
  short local_40;
  short local_3e;
  short local_3c;
  short local_38;
  short local_36;
  short local_34;
  struct GameTracker* gGT = sdata->gGT;

  // create thread for "introcam"
  CS_Thread_Init(0, s_introcam_800abd24, 0, 0, 0);

  // if not going to credits
  if ((gGT->gameMode2 & CREDITS) == 0) 
  {
    // If this is the Naughty Dog Box Scene
    if (gGT->levelID == 0x29)
    {
      CS_Instance_InitMatrix();
      local_48 = 0;
      local_46 = 0;
      local_44 = 0;
      local_38 = 0;
      local_36 = 0;
      local_34 = 0;
      local_40 = 0;
      local_3e = 0;
      local_3c = 0;

      // Create 19 threads for the Naughty Dog Box Scene
      CS_Thread_Init(0xb6, s_BOX_01_800abd30, &local_48, 0, 0);
      CS_Thread_Init(0xb7, s_BOX_02_800abd38, &local_48, 0, 0);
      CS_Thread_Init(0xb8, s_BOX_02_BOTTOM_800abd40, &local_48, 0, 0);
      CS_Thread_Init(0xb9, s_BOX_02_FRONT_800abd50, &local_48, 0, 0);
      CS_Thread_Init(0xba, s_BOX_02A_800abd60, &local_48, 0, 0);
      CS_Thread_Init(0xbb, s_BOX_03_800abd68, &local_48, 0, 0);

      // 800abd70 = "CODE"
      CS_Thread_Init(0xbc, &DAT_800abd70, &local_48, 0, 0);

      // 800abd78 = "GLOW"
      CS_Thread_Init(0xbd, &DAT_800abd78, &local_48, 0, 0);

      // 800abd80 = "LID"
      CS_Thread_Init(0xbe, &DAT_800abd80, &local_48, 0, 0);

      // 800abd84 = "LIDB"
      CS_Thread_Init(0xc9, &DAT_800abd84, &local_48, 0, 0);

      // 800abd84 = "LIDC"
      CS_Thread_Init(0xca, &DAT_800abd8c, &local_48, 0, 0);

      // 800abd84 = "LIDD"
      CS_Thread_Init(0xcb, &DAT_800abd94, &local_48, 0, 0);

      // 800abd84 = "LID2"
      CS_Thread_Init(0xbf, &DAT_800abd9c, &local_48, 0, 0);

      // There are 5 cars that appear in the cutscene,
      // but the pointers and strings suggest there
      // could have been 8
      CS_Thread_Init(0xc1, s_KART0_800abda4, &local_48, 0, 0);
      CS_Thread_Init(0xc2, s_KART1_800abdac, &local_48, 0, 0);
      CS_Thread_Init(0xc3, s_KART2_800abdb4, &local_48, 0, 0);
      CS_Thread_Init(0xc4, s_KART3_800abdbc, &local_48, 0, 0);
      CS_Thread_Init(199, s_KART6_800abdc4, &local_48, 0, 0);
      CS_Thread_Init(200, s_KART7_800abdcc, &local_48, 0, 0);
    }
  }
  // if going to credits
  else 
  {
    OVR_233.isCutsceneOver = 0;

    CS_Credits_Init();

    CS_Instance_InitMatrix();
  }
}