#include <common.h>

void DECOMP_AH_Pause_Draw(int pageID, int posX)
{
	RECT r;
	int levelID = D232.advPausePages[pageID].hubID;
	int lngIndex = D232.advPausePages[pageID].titleLng;
	
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
	if (((sdata->frameCounter >> FPS_RIGHTSHIFT(0)) & 4) == 0)
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
        gGT->tileView_UI.ptrOT,

        ptrColor[0], ptrColor[1], 
		ptrColor[2], ptrColor[3],
		
		0, 0x1000, 0x800);

    // Draw arrow pointing Right
    DECOMP_DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        (posX + half) + 0x112,
        0x16,

        primMem,
		gGT->tileView_UI.ptrOT,

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
    }
	
	int type = D232.advPausePages[pageID].type;
	
	if(type == 0)
	{
		// to-do
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
				
			inst->matrix.t[0] = 
				LoadSave_UI_ConvertX(instPosX, 0x100);
		
			inst->matrix.t[1] = 
				LoadSave_UI_ConvertY(instPosY + 0x41, 0x100);
				
			LoadSave_PrintInteger(
				ptrTokenCount[i],
				instPosX + 0x36,
				instPosY + 0x3a,
				0, 0);
				
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
		struct AdvProgress *adv;
		int bitIndex;
		int count[3];
		
		adv = &sdata->advProgress;
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
				
			inst->matrix.t[0] = 
				LoadSave_UI_ConvertX(instPosX, 0x100);
		
			inst->matrix.t[1] = 
				LoadSave_UI_ConvertY(0x49, 0x100);
				
			LoadSave_PrintInteger(
				count[i],
				instPosX + 0x19,
				0x49,
				0, 0);
				
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
	
	MENUBOX_DrawOuterRect_Edge(
		&r, &sdata->battleSetup_Color_UI_1, 0x20,
		gGT->backBuffer->otMem.startPlusFour);
		
	r.x = 0x100 - half;
	r.y = 10;
	r.w = (short)iVar11;
	r.h = 0x82;

	// Draw 2D Menu rectangle background
	MENUBOX_DrawInnerRect(&r, 4, &gGT->backBuffer->otMem.startPlusFour[3]);
	
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
			
			Vector_SpecLightSpin2D(inst, rotArr, specArr);
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