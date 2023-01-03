#include <common.h>

void GAMEPROG_ResetHighScores(struct GameProgress* gameProg)
{
	int i;
	int j;
	int k;
	int characterID;
	struct HighScoreTrack* track;
	struct HighScoreEntry* entry;
	char* name;
	
	// for every track
	for(i = 0; i < 18; i++)
	{
		track = &gameProg->highScoreTracks[i];
		
		// for time trial and relic
		for(j = 0; j < 2; j++)
		{
			// for every entry
			for(k = 0; k < 6; k++)
			{
				characterID = i + j + k;
				characterID = characterID - 0xD * (characterID/0xD);
				
				entry = &track->scoreEntry[j*6+k];
				entry->time = 0x8c640;
				entry->characterID = characterID;
				
				name = sdata->lngStrings[
							data.MetaDataCharacters[
								characterID
							].name_LNG_short
						];
				
				// can't do an int-copy,
				// strings in LNG are unaligned
				strcpy(entry->name, name);
			}
		}
	}
}