#include <common.h>

void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);

// store in kernel cause whatever
#define string (char*)0x8000FF00
#define frame *(int*)0x8000FFF0
#define ms *(int*)0x8000FFF4


// copy/paste from HelloWorld_Advanced,
// the code is more heavily commented there
void DF_PrintText()
{
  struct GameTracker* gGT;
  u_long* backup;

  #if BUILD == SepReview
  if (sdata->Loading.stage >= 5) return;
  #elif BUILD >= UsaRetail
  if(sdata->Loading.stage == 5) return;
  #endif

  gGT = sdata->gGT;
  backup = gGT->tileView_UI.ptrOT;
  gGT->tileView_UI.ptrOT = gGT->ot_tileView_UI[gGT->swapchainIndex];
  
  if((sdata->gGT->framesInThisLEV-frame) <= 1000)
	  if(sdata->gGT->msInThisLEV-ms != 0)
		sprintf
		(
			string, "Frame: %d     MS: %d     FPS: %d", 
			(sdata->gGT->framesInThisLEV-frame), 
			(sdata->gGT->msInThisLEV-ms),
			1000000/(sdata->gGT->msInThisLEV-ms)
		);
  
  DecalFont_DrawLine(string, 10, 208, FONT_SMALL, ORANGE);
  
  
  gGT->tileView_UI.ptrOT = backup;
}

void DF_DrawOTag(u_long* ot)
{
	int buttonHoldCurr = sdata->gGamepads->
							gamepad[0].buttonsHeldCurrFrame;

	int buttonHoldPrev = sdata->gGamepads->
							gamepad[0].buttonsHeldPrevFrame;
							
	// Enable 60fps (USA Only)
	*(unsigned char*)0x80037930 = 0;
	
	// enable 4P with one controller
	*(unsigned char*)0x800255c4 = 4;

	if(
		// if held this frame, and not previous
		((buttonHoldCurr & BTN_SELECT) == BTN_SELECT) &&
		((buttonHoldPrev & BTN_SELECT) != BTN_SELECT)
	  )
	{
		frame = sdata->gGT->framesInThisLEV;
		ms = sdata->gGT->msInThisLEV;
	}

	DF_PrintText();
	DrawOTag(ot);
}