struct MenuRow menuRows[5] =
{	
	{
		.stringIndex = 0,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 1,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 2,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 3,
		.rowOnPressRight = 3,
	},
	
	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};

void RECTMENU_OnPressX(struct RectMenu* b);

struct RectMenu menu =
{
	// custom string made myself
	.stringIndexTitle = 0x17d, 
	
	.posX_curr = 0xB0, // X position
	.posY_curr = 0x74,  // Y position
	
	.unk1 = 0,
	
	// 0b11, 2 centers X, 1 centers Y, 0x80 for tiny text
	.state = 3,

	.rows = menuRows,

	.funcPtr = RECTMENU_OnPressX,

	.drawStyle = 0x4,	// 0xF0 looks like load/save
	
	.posX_prev = 0,
	.posY_prev = 0,
	
	.rowSelected = 0,
	.unk1c = 0,
	.unk1e = 0,
	.width = 0,
	.height = 0,
	
	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
};

char* OnPressX_SetPtr;
char* OnPressX_SetLock;
int pageMax;

int MenuFinished()
{
	return *OnPressX_SetLock;
}

void NewPage_Tracks()
{
	int i;
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 
			data.metaDataLEV[4*octr->PageNumber+i].name_LNG;
	}
}

void MenuWrites_Tracks()
{
	pageMax = 7;
	OnPressX_SetPtr = &sdata->gGT->levelID;
	OnPressX_SetLock = &octr->boolLockedInTrack;
}

void NewPage_Laps()
{
	int i;
	
	// override "LAPS" with "1"
	sdata->lngStrings[0x9a] = "1";
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 0x9a+i;
	}
}

void MenuWrites_Laps()
{
	OnPressX_SetPtr = &octr->lapID;
	OnPressX_SetLock = &octr->boolLockedInLap;
}

void NewPage_Characters()
{
	int i;
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 
			data.MetaDataCharacters[4*octr->PageNumber+i].name_LNG_long;
	}
}

void MenuWrites_Characters()
{
	pageMax = 3;
	OnPressX_SetPtr = &data.characterIDs[0];
	OnPressX_SetLock = &octr->boolLockedInCharacters[octr->DriverID];
}

void ResetMenu()
{
	octr->PageNumber = 0;
	menu.rowSelected = 0;
	RECTMENU_Show(&menu);
}

void UpdateMenu()
{
	int buttons = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	// BTN_LEFT = 0x4
	// BTN_RIGHT = 0x8
	// some crazy math to optimize this
	
	if(buttons & 0xC)
	{
		octr->PageNumber += (buttons-6)/2;
	
		if (octr->PageNumber < 0) octr->PageNumber = 0;
		if (octr->PageNumber > pageMax) octr->PageNumber = pageMax;
	}
}

void RECTMENU_OnPressX(struct RectMenu* b)
{
	int i;
	
	RECTMENU_Hide(b);
	sdata->ptrDesiredMenu = 0;
	
	*OnPressX_SetPtr = (4 * octr->PageNumber) + b->rowSelected;
	*OnPressX_SetLock = 1;
	
	RECTMENU_ClearInput();
}

void PrintTimeStamp()
{
	DECOMP_DecalFont_DrawLine(__DATE__, WIDE_PICK(5, 100-40), 206, FONT_SMALL, DARK_RED);
	DECOMP_DecalFont_DrawLine(__TIME__, WIDE_PICK(170, 228-40), 206, FONT_SMALL, DARK_RED);
}

void PrintClientCountStats()
{
	char message[32];
	
	sprintf(message, "ClientID: %d", octr->DriverID);
	DecalFont_DrawLine(message,0x8,0x20,FONT_SMALL,ORANGE);
	
	sprintf(message, "NumTotal: %d", octr->NumDrivers);
	DecalFont_DrawLine(message,0x8,0x28,FONT_SMALL,ORANGE);
}

void PrintCharacterStats()
{
	char message[32];
	int slot;
	int i;
	int color;
	
	sprintf(message, "Players: %d/8", octr->NumDrivers);
	DecalFont_DrawLine(message,0x128,0x40,FONT_SMALL,0);
	
	for(i = 0; i < octr->NumDrivers; i++)
	{	
		// convert client index to local index
		if(i == octr->DriverID) slot = 0;
		if(i < octr->DriverID) slot = i+1;
		if(i > octr->DriverID) slot = i;

		// 0x19 - red
		// 0x1A - green
		int color = 
			octr->boolLockedInCharacters[i] ? 
			PLAYER_GREEN : PLAYER_RED;
		
		sprintf(message, "%s:", &octr->nameBuffer[slot * 0xc]);
		DecalFont_DrawLine(message,0x128,0x48+i*0x8,FONT_SMALL,color);
		
		if(octr->CurrState < LOBBY_CHARACTER_PICK)
			continue;
		
		char* characterName =
			sdata->lngStrings[
				data.MetaDataCharacters[
					data.characterIDs[slot]
				].name_LNG_short];
				
		DecalFont_DrawLine(characterName,0x1A8,0x48+i*0x8,FONT_SMALL,color);
	}
}

char* onlineLapString = "Laps: 0\0";
void PrintRecvTrack()
{
	char message[32];
	
	sprintf(message, "Track: %s", 
				sdata->lngStrings
				[
					data.metaDataLEV[sdata->gGT->levelID].name_LNG
				]
			);
	
	DecalFont_DrawLine(message,0x8,0x10,FONT_SMALL,PLAYER_BLUE);
	
	onlineLapString[6] = '0' + sdata->gGT->numLaps;
	DecalFont_DrawLine(onlineLapString,0x128,0x10,FONT_SMALL,PLAYER_BLUE);
}