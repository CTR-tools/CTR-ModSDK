#include <common.h>

void DECOMP_DotLights(struct GameTracker* gGT)
{
  int iVar1;
  int d1;
  int iVar5;
  int sortaPosY;
  
  struct Icon* icon;
  int newPosX;
  int sizeX;
  int scale;
  struct PushBuffer* pb;
  int playerIndex;
  int lightIndex;
  int newPosY;
  
  // use as counter
  d1 = 0;

  // time on traffic light counter
  iVar1 = gGT->trafficLightsTimer;
  
  // if timer is negative, skip the whole function
  if (iVar1 < -0x3bf) goto SkipLights;
  
  // default, lights are near center of screen
  sortaPosY = 0x1000;
  
  // green light (1,1,1,1)
  if (iVar1 < 1)
  {
    if (0 < sdata->trafficLightsTimer_prevFrame)
	{
	  // Play "green light" Sound
      DECOMP_OtherFX_Play(0x46,0);
    }

	// (1,1,1,1)
    d1 = 0b1111;

	// use time on traffic light counter to transition
	// lights upward, add full second to treat negative as possitive
	iVar1 = (gGT->trafficLightsTimer + 0x3c0) * 0x1000;
	iVar5 = (int)((long long)((long long)iVar1 * -0x77777777) >> 0x20);
	sortaPosY = (iVar5 + iVar1 >> 9) - (iVar1 >> 0x1f);

	goto DrawLights;
  }
  
  // any of the red lights
  for(lightIndex = 1; lightIndex < 4; lightIndex++)
  {
	  if(iVar1 < (0x3c0*lightIndex)+1)
	  {
		  if(sdata->trafficLightsTimer_prevFrame > (0x3c0*lightIndex))
		  {
			// Play "red light" Sound
			DECOMP_OtherFX_Play(0x45,0);
		  }
		  
		  d1 |= (1<<lightIndex);
		  
	  }
  }
  
  // draw red lights if they are on
  if(d1 != 0) goto DrawLights;

  // default: if no red lights are on,
  // then draw lights coming down
  // d1 is still zero

  // use time on traffic light counter to transition posY downward
  iVar1 = (0xf00 - gGT->trafficLightsTimer) * 0x1000;
  iVar5 = (int)((long long)((long long)iVar1 * -0x77777777) >> 0x20);
  sortaPosY = (iVar5 + iVar1 >> 9) - (iVar1 >> 0x1f);
  
DrawLights:
  
  for(playerIndex = 0; playerIndex < gGT->numPlyrCurrGame; playerIndex++)
  {
      pb = &gGT->pushBuffer[playerIndex];

	  scale = FP(0.5);
	  if(gGT->numPlyrCurrGame == 1) scale = FP(1.0);
	  if(gGT->numPlyrCurrGame == 2) scale = FP(2/3);

	  // pointer to first traffic light icon
      icon = gGT->trafficLightIcon[0];
	  
	  // distance between each light,
	  // adjusted sizeX,
	  // (icon endX - icon startX) * scale / 0x1000
      sizeX = (int)FP_Mult((icon->texLayout.u1 - icon->texLayout.u0), scale);

	  #ifdef USE_16BY9
	  sizeX = WIDE_34(sizeX);
	  #endif

	  // posX of first light
	  // (window sizeX/2) - (light sizeX*2)
	  newPosX = (pb->rect.w + sizeX * -4) / 2;
	  
	  #ifdef USE_16BY9
	  // counter the DrawPolyFT4 midpoint shifting
	  newPosX -= (sizeX * 125) / 1000;
	  #endif

	  // posY
	  newPosY =
				// screen sizeY is used to scale original posY
				(FP_Mult((((int)(pb->rect.h) / 3) * 0x10000 >> 0x10), sortaPosY)) -

			    // adjusted icon sizeY,
				(
					(int)FP_Mult((icon->texLayout.v2 - icon->texLayout.v0), scale)
				);

	  for(lightIndex = 0; lightIndex < 4; lightIndex ++)
	  {

		DECOMP_DecalHUD_DrawPolyFT4(
		
			// icon pointer
			gGT->trafficLightIcon
			[
				// on or off
				((d1 & (1<<(3-lightIndex)))!=0)
				
				+ (2*(lightIndex==3))
				
			],

			// posX
			newPosX + sizeX * lightIndex,

			// posY
			newPosY,

			// pointer to PrimMem struct
			&gGT->backBuffer->primMem,

			// pointer to OT memory
			pb->ptrOT,

			0,scale);
	  }
  }
  
SkipLights:

  // keep record of previous frame's countdown timer
  sdata->trafficLightsTimer_prevFrame = gGT->trafficLightsTimer;
  return;
}