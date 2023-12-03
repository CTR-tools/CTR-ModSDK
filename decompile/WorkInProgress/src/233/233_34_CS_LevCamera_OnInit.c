#include <common.h>

// for oxide intro and ND box
void CS_LevCamera_OnInit(void)
{
  MATRIX matrice;
  struct GameTracker *gGT = sdata->gGT;

  // create thread for "introcam"
  CS_Thread_Init(0, &OVR_233.s_introcam, 0, 0, 0);

  // if not going to credits
  if ((gGT->gameMode2 & CREDITS) == 0)
  {
    // If this is the Naughty Dog Box Scene
    if (gGT->levelID == NAUGHTY_DOG_CRATE)
    {
      CS_Instance_InitMatrix();
      matrice.m[0][0] = 0;
      matrice.m[0][1] = 0;
      matrice.m[0][2] = 0;
      matrice.m[1][0] = 0;
      matrice.m[1][1] = 0;
      matrice.m[1][2] = 0;
      matrice.m[2][0] = 0;
      matrice.m[2][1] = 0;
      matrice.m[2][2] = 0;

      // Create 19 threads for the Naughty Dog Box Scene
      CS_Thread_Init(0xb6, &OVR_233.s_box1, &matrice, 0, 0);
      CS_Thread_Init(0xb7, &OVR_233.s_box2, &matrice, 0, 0);
      CS_Thread_Init(0xb8, &OVR_233.s_box2_bottom, &matrice, 0, 0);
      CS_Thread_Init(0xb9, &OVR_233.s_box2_front, &matrice, 0, 0);
      CS_Thread_Init(0xba, &OVR_233.s_box2_A, &matrice, 0, 0);
      CS_Thread_Init(0xbb, &OVR_233.s_box3, &matrice, 0, 0);

      // 800abd70 = "CODE"
      CS_Thread_Init(0xbc, &OVR_233.s_code, &matrice, 0, 0);

      // 800abd78 = "GLOW"
      CS_Thread_Init(0xbd, &OVR_233.s_glow, &matrice, 0, 0);

      // 800abd80 = "LID"
      CS_Thread_Init(0xbe, &OVR_233.s_lid, &matrice, 0, 0);

      // 800abd84 = "LIDB"
      CS_Thread_Init(0xc9, &OVR_233.s_lidb, &matrice, 0, 0);

      // 800abd84 = "LIDC"
      CS_Thread_Init(0xca, &OVR_233.s_lidc, &matrice, 0, 0);

      // 800abd84 = "LIDD"
      CS_Thread_Init(0xcb, &OVR_233.s_lidd, &matrice, 0, 0);

      // 800abd84 = "LID2"
      CS_Thread_Init(0xbf, &OVR_233.s_lid2, &matrice, 0, 0);

      // There are 5 cars that appear in the cutscene,
      // but the pointers and strings suggest there
      // could have been 8
      CS_Thread_Init(193, &OVR_233.s_kart0, &matrice, 0, 0);
      CS_Thread_Init(194, &OVR_233.s_kart1, &matrice, 0, 0);
      CS_Thread_Init(195, &OVR_233.s_kart2, &matrice, 0, 0);
      CS_Thread_Init(196, &OVR_233.s_kart3, &matrice, 0, 0);
      CS_Thread_Init(199, &OVR_233.s_kart6, &matrice, 0, 0);
      CS_Thread_Init(200, &OVR_233.s_kart7, &matrice, 0, 0);
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