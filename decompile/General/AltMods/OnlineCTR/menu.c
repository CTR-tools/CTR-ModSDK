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
	
	.posX_curr = 0, // X position
	.posY_curr = 0,  // Y position
	
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

void NewPage_ServerCountry()
{
	int i;
	
	menu.posX_curr = 0x198; // X position
	menu.posY_curr = 0x84;  // Y position
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 0x9a+i;
	}
	
	if(octr->PageNumber == 0)
	{
		// override "LAPS" "3/5/7"
		sdata->lngStrings[0x9a] = "EUR -- 6 rooms";
		sdata->lngStrings[0x9b] = "USA -- 6 rooms";
		sdata->lngStrings[0x9c] = "MEX -- 6 rooms";
		sdata->lngStrings[0x9d] = "PRIVATE ROOM";
	}
	
	else
	{
		// override "LAPS" "3/5/7"
		sdata->lngStrings[0x9a] = "BRZ -- 4 rooms";
		sdata->lngStrings[0x9b] = "AUS -- 1 room";
		sdata->lngStrings[0x9c] = "-";
		sdata->lngStrings[0x9d] = "PRIVATE ROOM";
		
		menuRows[2].stringIndex |= 0x8000;
	}
}

void MenuWrites_ServerCountry()
{
	pageMax = 1;
	OnPressX_SetPtr = &octr->serverCountry;
	OnPressX_SetLock = &octr->serverLockIn1;
}

void NewPage_ServerRoom()
{
	int i;
	
	// override "LAPS" "3/5/7"
	sdata->lngStrings[0x9a] = "ROOM 1";
	sdata->lngStrings[0x9b] = "ROOM 2";
	sdata->lngStrings[0x9c] = "ROOM 3";
	sdata->lngStrings[0x9d] = "ROOM 4";
	
	int pn = octr->PageNumber;
	sdata->lngStrings[0x9a][5] = '0' + (4*pn+1);
	sdata->lngStrings[0x9b][5] = '0' + (4*pn+2);
	sdata->lngStrings[0x9c][5] = '0' + (4*pn+3);
	sdata->lngStrings[0x9d][5] = '0' + (4*pn+4);
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 0x809a+i;
	}
	
	int numRooms = 0;
	switch(octr->serverCountry)
	{
		// 6+6+6+1+1=18
		// Player Cap = 160 players
		case 0: numRooms = 6; break; // EUR Looper
		case 1: numRooms = 6; break; // USA Niko
		case 2: numRooms = 6; break; // MEX Claudio
		case 3: numRooms = 1; break; // PRIVATE ROOM
		case 4: numRooms = 4; break; // BZL Pedro
		case 5: numRooms = 1; break; // AUS Matt
		
	}
	
	for(i = 0; i < 4; i++)
	{
		if(4*pn+i < numRooms)
			menuRows[i].stringIndex &= 0x7FFF;
	}
}

void MenuWrites_ServerRoom()
{	
	pageMax = 0;
	if(octr->serverCountry < 3)
		pageMax = 1;
	
	OnPressX_SetPtr = &octr->serverRoom;
	OnPressX_SetLock = &octr->serverLockIn2;
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
	
	// override "LAPS" with "1",
	// reset "3" "5" "7" in case overwritten
	sdata->lngStrings[0x9a] = "1";
	sdata->lngStrings[0x9b] = "3";
	sdata->lngStrings[0x9c] = "5";
	sdata->lngStrings[0x9d] = "7";
	
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
	
	if(pageMax == 0)
		return;
	
	int string = 
		(('1' + octr->PageNumber) << 0) |
		('/' << 8) |
		(('1' + pageMax) << 16);
	
	DECOMP_MainFreeze_ConfigDrawArrows(menu.posX_curr, 0x38, &string);
	
	DecalFont_DrawLine(&string,menu.posX_curr,0x38,FONT_BIG,JUSTIFY_CENTER|WHITE);
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
}

void PrintCharacterStats()
{
	char message[32];
	int slot;
	int i;
	int color;
	
	int numDead = 0;
	for(i = 0; i < octr->NumDrivers; i++)
		if(octr->nameBuffer[i*0xC] == 0)
			numDead++;
	
	sprintf(message, "Players: %d/8", (octr->NumDrivers-numDead));
	DecalFont_DrawLine(message,0x130,0x58,FONT_SMALL,0);

	int h = 0;

	for(i = 0; i < octr->NumDrivers; i++)
	{	
		// convert client index to local index
		if(i == octr->DriverID) slot = 0;
		if(i < octr->DriverID) slot = i+1;
		if(i > octr->DriverID) slot = i;

		char* str = &octr->nameBuffer[slot * 0xc];
		if(str[0] == 0) continue;

		// 0x19 - red
		// 0x1A - green
		int color = 
			octr->boolLockedInCharacters[i] ? 
			PLAYER_GREEN : PLAYER_RED;
		
		int posY = 0x60+h;
		h += 8;
		
		sprintf(message, "%s:", str);
		DecalFont_DrawLine(message,0x130,posY,FONT_SMALL,color);
		
		if(octr->CurrState < LOBBY_CHARACTER_PICK)
			continue;
		
		char* characterName =
			sdata->lngStrings[
				data.MetaDataCharacters[
					data.characterIDs[slot]
				].name_LNG_short];
				
		DecalFont_DrawLine(characterName,0x1AC,posY,FONT_SMALL,color);
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
	
	DecalFont_DrawLine(message,0x8,0x10,FONT_SMALL,PAPU_YELLOW);
	
	onlineLapString[6] = '0' + sdata->gGT->numLaps;
	DecalFont_DrawLine(onlineLapString,0x128,0x10,FONT_SMALL,PAPU_YELLOW);
}