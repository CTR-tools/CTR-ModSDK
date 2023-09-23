#include <common.h>

void DECOMP_OptionsMenu_TestSound(int newRow, int newBoolPlay)
{
	int oldRow = sdata->OptionSlider_Index;
	int oldBoolPlay = sdata->OptionSlider_BoolPlay;
	
	sdata->OptionSlider_Index = newRow;
	sdata->OptionSlider_BoolPlay = newBoolPlay;
	
	// if row changed
	if(oldRow != newRow)
	{
		// if "was" playing
		if(oldBoolPlay != 0)
		{
			// FX row
			if(oldRow == 0)
			{
				OtherFX_Stop2(0x48);
			}
			
			// Music row
			else if(oldRow == 1)
			{
				// end Aku or Uka song
				// 0=level, 1=aku, 2=uka
				
				if(Music_GetHighestSongPlayIndex() == 1)
				{
					CseqMusic_Stop(2);
				}
				
				else
				{
					CseqMusic_Stop(1);
				}
			}
		
			// Voice row
			else if(oldRow == 2)
			{
				if(sdata->OptionSlider_soundID != 0)
				{
					OtherFX_Stop1(sdata->OptionSlider_soundID);
					sdata->OptionSlider_soundID = 0;
				}
			}
		}
		
		if(newBoolPlay != 0)
		{
			// FX row
			if(newRow == 0)
			{
				OtherFX_Play(0x48, 0);
			}
			
			// Music row
			else if(newRow == 1)
			{
				// end Aku or Uka song
				// 0=level, 1=aku, 2=uka
				
				int val = 1;
				if(Music_GetHighestSongPlayIndex() == 1)
					val = 2;
				
				CseqMusic_Start(val,0,0,0,1);
			}
		}
	}
	
	// Voice row
	if(newRow == 2)
	{
		// OG game does this, instead of gGT->drivers[0]?
		int driverID = sdata->gGT->cameraDC[0].driverToFollow->driverID;
		
		int characterID = data.characterIDs[driverID];
		
		int frameCount = sdata->gGT->frameTimer_MainFrame_ResetDB;
		
		int sampleVoiceID;
		
		// every 25th frame
		if(frameCount == (frameCount/25)*25)
		{
			// every 50th frame (0, 50, 100, 150)
			if(frameCount == (frameCount/50)*50)
			{
				sampleVoiceID = characterID + 0x1c;
			}
			
			// every 50th frame (25, 75, 125, 175)
			else
			{
				sampleVoiceID = characterID + 0x2c;
			}
		
			sdata->OptionSlider_soundID = 
				OtherFX_Play(sampleVoiceID, 0);
		}
	}
}