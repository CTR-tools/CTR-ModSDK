#include <common.h>

void DECOMP_AH_Pause_Draw(int pageID, int posX)
{
	RECT r;
	int levelID = D232.advPausePages[pageID].hubID;
	int lngIndex = D232.advPausePages[pageID].titleLng;

	int bitIndex;
	struct AdvProgress *adv;
	adv = &sdata->advProgress;

	if(lngIndex < 0)
		lngIndex = data.metaDataLEV[levelID].name_LNG;

	char* str = sdata->lngStrings[lngIndex];

	DECOMP_DecalFont_DrawLine(
		str,
		posX + 0x100, 0xf, FONT_BIG,
		0xffff8000);

	int len =
		DECOMP_DecalFont_GetLineWidth(str, FONT_BIG);

	int half = len >> 1;

	// orange/red
	int colorIndex = 0;
	if ((sdata->frameCounter & FPS_DOUBLE(4)) == 0)
		colorIndex = 3;

	int* ptrColor = data.ptrColor[colorIndex];

    struct GameTracker *gGT = sdata->gGT;
	struct PrimMem* primMem = &gGT->backBuffer->primMem;

	struct Icon** iconPtrArray =
		ICONGROUP_GETICONS(gGT->iconGroup[4]);

    // Draw arrow pointing Left
    DECOMP_DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        (posX - half) + 0xec,
        0x16,

        primMem,
        gGT->pushBuffer_UI.ptrOT,

        ptrColor[0], ptrColor[1],
		ptrColor[2], ptrColor[3],

		0, 0x1000, 0x800);

    // Draw arrow pointing Right
    DECOMP_DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        (posX + half) + 0x112,
        0x16,

        primMem,
		gGT->pushBuffer_UI.ptrOT,

        ptrColor[0], ptrColor[1],
		ptrColor[2], ptrColor[3],

		0, 0x1000, 0);

	struct PauseObject* ptrPauseObject =
		D232.ptrPauseObject;

    // loop through 14 instances
    for (int i = 0; i < 0xe; i++)
    {
		// assume no awards won
        ptrPauseObject->PauseMember[i].unlockFlag &= ~(1);

		// dont draw instance
		ptrPauseObject->PauseMember[i].indexAdvPauseInst = -1;
    }

	int type = D232.advPausePages[pageID].type;

	if(type == 0)
	{
		int hubID = levelID-0x19;

		// gemstone
		if(hubID == 0)
		{
			// 2 relics
			for(int i = 0; i < 2; i++)
			{
				// 0x10 + i:
				// 0x10 - SlideCol
				// 0x11 - TurboTrack

				struct MetaDataLEV* mdLev =
					&data.metaDataLEV[0x10+i];

				DECOMP_DecalFont_DrawLine(
					sdata->lngStrings[mdLev->name_LNG],
					posX + 0x6e, i*0x10 + 4 + 0x26,
					FONT_BIG, 0);

				struct Instance* inst =
					ptrPauseObject->PauseMember[i].inst;

				// Remove SelectProfile with regular UI variant
				inst->matrix.t[0] =
					DECOMP_UI_ConvertX_2(posX + 0x16d + 1*0x1e, 0x100);

				inst->matrix.t[1] =
					DECOMP_UI_ConvertY_2(i*0x10 + 4 + 0x2f, 0x100);

				// 6, 7, 8,
				// sapphire, gold, platinum

				// set sapphire by default
				ptrPauseObject->PauseMember[i].indexAdvPauseInst = 6;

				// unlock if sapphire is visible
				ptrPauseObject->PauseMember[i].unlockFlag |=
					CHECK_ADV_BIT(adv->rewards, (0x10+i+0x16));

				// increment to gold
				ptrPauseObject->PauseMember[i].indexAdvPauseInst +=
					CHECK_ADV_BIT(adv->rewards, (0x10+i+0x28));

				// increment to platinum
				ptrPauseObject->PauseMember[i].indexAdvPauseInst +=
					CHECK_ADV_BIT(adv->rewards, (0x10+i+0x3a));
			}

			char bossID = 0xf;

			DECOMP_DecalFont_DrawLine(
				sdata->lngStrings[
					data.MetaDataCharacters[
						bossID
					].name_LNG_long
				],
				posX + 0x6e, 2*0x10 + 4 + 0x26,
				FONT_BIG, 4);

			// === Draw Star ===

			// black
			int color = 0x15;

			// set to grey (if beaten oxide at least once)
			if(CHECK_ADV_BIT(adv->rewards, 0x62) != 0)
				color = 1;

			u_int *starColor;
            starColor = data.ptrColor[color];

			struct Icon** iconPtrArray =
				ICONGROUP_GETICONS(gGT->iconGroup[5]);

			DECOMP_DecalHUD_DrawPolyGT4
			(
				iconPtrArray[0x37],

				posX + 0x16d + 0x18,
				2*0x10 + 4 + 0x2a,

				&gGT->backBuffer->primMem,
				gGT->pushBuffer_UI.ptrOT,

				starColor[0], starColor[1],
				starColor[2], starColor[3],

				0, 0x1000
			);

			// 5 gems
			for(int i = 0; i < 5; i++)
			{
				struct Instance* inst =
					ptrPauseObject->PauseMember[2+i].inst;

				// Remove SelectProfile with regular UI variant
				inst->matrix.t[0] =
					DECOMP_UI_ConvertX_2(posX + 0x100 + (i-2)*60, 0x100);

				inst->matrix.t[1] =
					DECOMP_UI_ConvertY_2(((i&1)<<4)|0x6a, 0x100);

				// gem color
				ptrPauseObject->PauseMember[2+i].indexAdvPauseInst = i;

				// unlock gem
				ptrPauseObject->PauseMember[2+i].unlockFlag |=
					CHECK_ADV_BIT(adv->rewards, (i+0x6a));
			}
		}

		// any other hub
		else
		{
			short* check = &data.advHubTrackIDs[(hubID-1)*4];

			// 4 tracks
			for(int i = 0; i < 4; i++)
			{
				struct MetaDataLEV* mdLev =
					&data.metaDataLEV[check[i]];

				DECOMP_DecalFont_DrawLine(
					sdata->lngStrings[mdLev->name_LNG],
					posX + 0x50, i*0x10 + 0 + 0x26,
					FONT_BIG, 0);

				// 3 instances per track
				for(int j = 0; j < 3; j++)
				{
					struct Instance* inst =
						ptrPauseObject->PauseMember[3*i+j].inst;

					// Remove SelectProfile with regular UI variant
					inst->matrix.t[0] =
						DECOMP_UI_ConvertX_2(posX + 0x15e + j*0x1e, 0x100);

					inst->matrix.t[1] =
						DECOMP_UI_ConvertY_2(i*0x10 + 0 + 0x2f, 0x100);
				}

				// trophy
				ptrPauseObject->PauseMember[i*3+0].indexAdvPauseInst = 14;
				ptrPauseObject->PauseMember[i*3+0].unlockFlag |=
					CHECK_ADV_BIT(adv->rewards, (check[i]+6));

				// 6, 7, 8,
				// sapphire, gold, platinum

				// set sapphire by default
				ptrPauseObject->PauseMember[i*3+1].indexAdvPauseInst = 6;

				// unlock if sapphire is visible
				ptrPauseObject->PauseMember[i*3+1].unlockFlag |=
					CHECK_ADV_BIT(adv->rewards, (check[i]+0x16));

				// increment to gold
				ptrPauseObject->PauseMember[i*3+1].indexAdvPauseInst +=
					CHECK_ADV_BIT(adv->rewards, (check[i]+0x28));

				// increment to platinum
				ptrPauseObject->PauseMember[i*3+1].indexAdvPauseInst +=
					CHECK_ADV_BIT(adv->rewards, (check[i]+0x3a));

				// CTR Tokens
				ptrPauseObject->PauseMember[i*3+2].indexAdvPauseInst = 9+mdLev->ctrTokenGroupID;
				ptrPauseObject->PauseMember[i*3+2].unlockFlag |=
					CHECK_ADV_BIT(adv->rewards, (check[i]+0x4c));
			}

			// roo, papu, joe, pinstripe
			// 10, 9, 11, 8
			int bossArr = 0x080b090a;
			char bossID = bossArr >> (8*(hubID-1));

			DECOMP_DecalFont_DrawLine(
				sdata->lngStrings[
					data.MetaDataCharacters[
						bossID
					].name_LNG_long
				],
				posX + 0x50, 4*0x10 + 0 + 0x26,
				FONT_BIG, 4);

			struct Instance* inst =
				ptrPauseObject->PauseMember[12].inst;

			// Remove SelectProfile with regular UI variant
			inst->matrix.t[0] =
				DECOMP_UI_ConvertX_2(posX + 0x15e + 1*0x1e, 0x100);

			inst->matrix.t[1] =
				DECOMP_UI_ConvertY_2(4*0x10 + 0 + 0x2f, 0x100);

			ptrPauseObject->PauseMember[12].indexAdvPauseInst = 5;
			ptrPauseObject->PauseMember[12].unlockFlag |=
				CHECK_ADV_BIT(adv->rewards, ((hubID-1)+0x5e));

			// skull rock, rampage ruins,
			// rocky road, nitro court
			// 10, 9, 11, 8
			int crystalArr = 0x12171315;
			char crystalID = crystalArr >> (8*(hubID-1));

			DECOMP_DecalFont_DrawLine(
				sdata->lngStrings[
					data.metaDataLEV[
						crystalID
					].name_LNG
				],
				posX + 0x50, 5*0x10 + 0 + 0x26,
				FONT_BIG, 1);

			inst =
				ptrPauseObject->PauseMember[13].inst;

			// Remove SelectProfile with regular UI variant
			inst->matrix.t[0] =
				DECOMP_UI_ConvertX_2(posX + 0x15e + 1*0x1e, 0x100);

			inst->matrix.t[1] =
				DECOMP_UI_ConvertY_2(5*0x10 + 0 + 0x2f, 0x100);

			ptrPauseObject->PauseMember[13].indexAdvPauseInst = 13;
			ptrPauseObject->PauseMember[13].unlockFlag |=
				CHECK_ADV_BIT(adv->rewards, ((hubID-1)+0x6f));
		}
	}

	else if(type == 1)
	{
		int* ptrTokenCount =
			&sdata->gGT->currAdvProfile.numCtrTokens.red;

		for(int i = 0; i < 5; i++)
		{
			short instPosX = posX + 0xf0 + ((i-2)*60);
			short instPosY = (i&1) * 0x28;

			ptrPauseObject->PauseMember[i].indexAdvPauseInst = i+9;
			ptrPauseObject->PauseMember[i].unlockFlag |= 1;

			struct Instance* inst =
				ptrPauseObject->PauseMember[i].inst;

			// Remove SelectProfile with regular UI variant
			inst->matrix.t[0] =
				DECOMP_UI_ConvertX_2(instPosX, 0x100);

			inst->matrix.t[1] =
				DECOMP_UI_ConvertY_2(instPosY + 0x41, 0x100);

			#ifndef REBUILD_PS1
			SelectProfile_PrintInteger(
				ptrTokenCount[i],
				instPosX + 0x36,
				instPosY + 0x3a,
				0, 0);
			#endif

			int strX = 'X';
			DECOMP_DecalFont_DrawLine(
				&strX,
				instPosX + 0x24,
				instPosY + 0x3e,
				FONT_SMALL, 0);
		}
	}

	else
	{
		int count[3];
		count[0] = 0;
		count[1] = 0;
		count[2] = 0;

		for(int i = 0; i < 0x12; i++)
		{
			// platinum
			if(CHECK_ADV_BIT(adv->rewards, (i+0x3a)) != 0)
				count[2]++;

			// gold
			else if(CHECK_ADV_BIT(adv->rewards, (i+0x28)) != 0)
				count[1]++;

			// sapphire
			else if(CHECK_ADV_BIT(adv->rewards, (i+0x16)) != 0)
				count[0]++;
		}

		for(int i = 0; i < 3; i++)
		{
			short instPosX = posX + 0xf6 + ((i-1)*90);

			ptrPauseObject->PauseMember[i].indexAdvPauseInst = i+6;
			ptrPauseObject->PauseMember[i].unlockFlag |= 1;

			struct Instance* inst =
				ptrPauseObject->PauseMember[i].inst;

			// Remove SelectProfile with regular UI variant
			inst->matrix.t[0] =
				DECOMP_UI_ConvertX_2(instPosX, 0x100);

			inst->matrix.t[1] =
				DECOMP_UI_ConvertY_2(0x49, 0x100);

			#ifndef REBUILD_PS1
			SelectProfile_PrintInteger(
				count[i],
				instPosX + 0x19,
				0x49,
				0, 0);
			#endif

			int strX = 'X';
			DECOMP_DecalFont_DrawLine(
				&strX,
				instPosX + 10,
				0x4e,
				FONT_SMALL, 0);
		}

		// variable reuse
		bitIndex = count[0] + count[1] + count[2];

		// be careful, might overflow in languages
		// other than english, where "TOTAL" is longer
		sprintf(&count[0], "%s %d", sdata->lngStrings[0xc4], bitIndex);

		DECOMP_DecalFont_DrawLine(
			count,
			posX + 0x100, 0x6e,
			FONT_BIG,
			0xffff8000);
	}

	int iVar7 = len;

	int iVar11 = iVar7 + 0x14;
	if ((short)iVar7 < 0x20b) {
		iVar11 = 0x21e;
	}

	half = iVar11 >> 1;

	r.x = 0x10a - half;
	r.y = 0x20;
	r.w = (short)iVar11 + -0x14;
	r.h = 2;

	Color color;
	color.self = sdata->battleSetup_Color_UI_1;
	DECOMP_RECTMENU_DrawOuterRect_Edge(&r, color, 0x20, gGT->backBuffer->otMem.startPlusFour);

	r.x = 0x100 - half;
	r.y = 10;
	r.w = (short)iVar11;
	r.h = 0x82;

	// Draw 2D Menu rectangle background
	DECOMP_RECTMENU_DrawInnerRect(
		&r, 4, &gGT->backBuffer->otMem.startPlusFour[3]);

	for(int i = 0; i < 0xe; i++)
	{
		int index =
			ptrPauseObject->PauseMember[i].indexAdvPauseInst;

		struct Instance* inst =
			ptrPauseObject->PauseMember[i].inst;

		if(index < 0)
		{
			// make invisible
			inst->flags |= 0x80;
			continue;
		}

		inst->flags &= 0xfff8ff7f;
		inst->flags |= D232.advPauseInst[index].instFlags;

		if(ptrPauseObject->PauseMember[i].unlockFlag == 0)
		{
			inst->flags &= 0xfff8ff7f;
			inst->colorRGBA = 0;
			inst->alphaScale = 0x1000;
		}

		else
		{
			unsigned char* ptrColor =
				&D232.advPauseInst[index].color;

			inst->alphaScale = 0;
			inst->colorRGBA =
				(ptrColor[0] << 0x14) |
				(ptrColor[1] << 0xc) |
				(ptrColor[2] << 0x4);
		}

		int scale =
			D232.advPauseInst[index].scale;

		// can we just replace the table values instead?
		if(type == 1) scale = 0x1000;
		if(type == 2) scale = scale << 2;

		inst->scale[0] = scale;
		inst->scale[1] = scale;
		inst->scale[2] = scale;

		int modelID =
			D232.advPauseInst[index].modelID;

		inst->model = gGT->modelPtr[modelID];

		short* rotArr =
			&ptrPauseObject->PauseMember[i].rot[0];

		ConvertRotToMatrix(&inst->matrix, rotArr);

		// if using specular light
		if((inst->flags & 0x70000) == 0x20000)
		{
			short* specArr =
				&D232.advPauseInst[index].specLight[0];

			#ifndef REBUILD_PS1
			Vector_SpecLightSpin2D(inst, rotArr, specArr);
			#endif
		}

		else
		{
			inst->colorRGBA = 0;
		}

		rotArr[1] =
			inst->matrix.t[0] * 0x10 +
			inst->matrix.t[1] * 0x20 +
			sdata->frameCounter * FPS_HALF(0x40);

		rotArr[1] &= 0xfff;
	}
}