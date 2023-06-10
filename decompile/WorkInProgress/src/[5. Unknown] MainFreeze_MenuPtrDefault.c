#include <common.h>

void DECOMP_MainFreeze_MenuPtrDefault(struct MenuBox* mb)
{
	u_short uVar1;
	struct GameTracker *psVar2;
	u_int uVar3;
	u_int uVar4;
	u_short uVar5;
	short levelID;
	u_int uVar6;
	
	psVar2 = sdata->gGT;
	if (sdata->gGT->cooldownfromPauseUntilUnpause != 0)
	{
		return;
	}
	if (mb->unk1e != 0)
	{
		uVar5 = mb->drawStyle & 0xfeff;
		mb->drawStyle = uVar5;
		if (2 < (byte)psVar2->numPlyrCurrGame)
		{
			mb->drawStyle = uVar5 | 0x100;
		}
		if ((sdata->gGT->gameMode1 & 0x100000) == 0)
		{
			return;
		}
		if ((mb->state & 0x1000) != 0)
		{
			return;
		}
		uVar3 = LOAD_IsOpen_AdvHub();
		if (uVar3 == 0)
		{
			return;
		}
		AH_Pause_Update();
		return;
	}
	if (mb->rowSelected < 0)
	{
		return;
	}
	uVar1 = mb->rows[mb->rowSelected].stringIndex;
	uVar6 = (u_int)mb->rows[mb->rowSelected].stringIndex;
	if (uVar1 == 0xe)
	{
		sdata->numIconsEOR = &sdata->menuBox_optionsMenu_racingWheel;
		sdata->menuBox_optionsMenu_racingWheel.rowSelected = 8;
		return;
	}
	if ((uVar6 - 0xb & 0xffff) < 2)
	{
		sdata->numIconsEOR = (struct MenuBox *)&DAT_800b518c;
		return;
	}
	if (uVar1 == 3)
	{
		sdata->numIconsEOR = &sdata->menuRow_quit;
		sdata->menuRow_quit.rowSelected = 1;
		return;
	}
	sdata->gGT->cooldownFromUnpauseUntilPause = 5;
	MENUBOX_Hide(mb);
	MainFreeze_SafeAdvDestroy();
	psVar2 = sdata->gGT;
	uVar3 = sdata->Loading.OnComplete.RemBitsConfig0;
	switch((int)((uVar6 - 1) * 0x10000) >> 0x10)
	{
		case 0:
		case 3:
			sdata->gGT->gameMode1 &= ~PAUSE_1;
			uVar3 = TitleFlag_IsFullyOffScreen();
			if (uVar3 == 1)
			{
				TitleFlag_BeginTransition(1);
			}
			if (sdata->boolPlayGhost == 0)
			{
				sdata->Loading.stage = -5;
				return;
			}
			if (ptrGhostTapePlaying == 0)
			{
				sdata->Loading.stage = -5;
				return;
			}
			sdata->characterIDs[1] = *(short *)(ptrGhostTapePlaying + 6);
			sdata->Loading.stage = -5;
			return;
		case 1:
			ElimBG_Deactivate((int)sdata->gGT);
			sdata->gGT->gameMode1 &= ~PAUSE_1;
			MainFrame_TogglePauseAudio(0);
			OtherFX_Play(1, 1);
			return;
		default:
			goto switchD_80039bcc_caseD_2;
		case 4:
			GhostBuffer_Destroy();
			levelID = 0x27;
			sdata->mainMenuState = 1;
			sdata->Loading.OnComplete.AddBitsConfig0 |= 0x2000;
			sdata->gGT->gameMode1 &= ~PAUSE_1;
			break;
		case 5:
			GhostBuffer_Destroy();
			levelID = 0x27;
			sdata->mainMenuState = 2;
			sdata->Loading.OnComplete.AddBitsConfig0 |= 0x2000;
			sdata->gGT->gameMode1 &= ~PAUSE_1;
			break;
		case 9:
			levelID = 0x27;
			sdata->mainMenuState = 3;
			sdata->Loading.OnComplete.AddBitsConfig0 |= 0x2000;
			sdata->gGT->gameMode1 &= ~PAUSE_1;
			break;
		case 0xc:
			sdata->Loading.OnComplete.AddBitsConfig0 |= 0x100000;
			sdata->Loading.OnComplete.RemBitsConfig0 |= 0xc000000;
			sdata->Loading.OnComplete.RemBitsConfig8 |= 8;
			uVar6 = sdata->gGT->gameMode1;
			uVar4 = uVar6 & ~PAUSE_1;
			sdata->gGT->gameMode1 = uVar4;
			if ((uVar6 & 0x10000000) == 0)
			{
				if ((int)uVar4 < 0)
				{
					sdata->Loading.OnComplete.RemBitsConfig0 = uVar3 | 0x8c000000;
					sdata->Loading.OnComplete.AddBitsConfig8 = sdata->Loading.OnComplete.AddBitsConfig8 | 1;
				}
				levelID = *(short *)&psVar2->prevLEV;
			}
			else
			{
				levelID = 0x19;
				sdata->Loading.OnComplete.RemBitsConfig0 = uVar3 | 0x1c000000;
				psVar2->levelID = (psVar2->cup).cupID + 100;
			}
	}
	MainRaceTrack_RequestLoad(levelID);
switchD_80039bcc_caseD_2:
										// WARNING: Read-only address (ram, 0x8008d958) is written
										// WARNING: Read-only address (ram, 0x8009d2ac) is written
	return;
}