#include <common.h>

// Not part of original game,
// just for cleaning up repetition
enum MC_EXTRA
{
	MC_EXTRA_NULL = 0,
	MC_EXTRA_CLOSE = 1,
};

int DECOMP_MEMCARD_HandleEvent(void)
{
    int readResult;
    int event;
    int iVar4;
    int *ptrData;
	
	int extra = 0;

    switch (sdata->memcard_stage)
    {

	// after checking info
    case MC_STAGE_GETINFO:
	{
        event = MEMCARD_GetNextSwEvent();
		
        if (event == MC_RETURN_PENDING)
			return MC_RETURN_PENDING;

        else if (event == MC_RETURN_IOE)
        {
            // If this is the first frame of the main game loop,
            // after all initialization is done
            if ((sdata->memcardStatusFlags & 1) != 0)
            {
				// discard any previous events
				// submit a load to test the card
                MEMCARD_SkipEvents();
                while (_card_load(sdata->memcardSlot) != 1);
				
                sdata->memcard_stage = MC_STAGE_NEWCARD;
                return MC_RETURN_PENDING;
            }
            if ((sdata->memcardStatusFlags & 2) == 0)
            {
                sdata->memoryCard_SizeRemaining = 0;
                return MC_RETURN_UNFORMATTED;
            }
			
			sdata->memcard_stage = MC_STAGE_IDLE;
			return MC_RETURN_IOE;
        }

        else if (event == MC_RETURN_NEWCARD)
        {
			// discard any previous events
			// submit a load to test the card
			MEMCARD_SkipEvents();
			while (_card_clear(sdata->memcardSlot) != 1);
			
			event = MEMCARD_WaitForHwEvent();
			if (event == 0)
			{
				// discard any previous events
				// submit a load to test the card
				MEMCARD_SkipEvents();
				while (_card_load(sdata->memcardSlot) != 1);
				
				sdata->memcard_stage = MC_STAGE_NEWCARD;
				return MC_RETURN_PENDING;
			}
			
			return MC_RETURN_NEWCARD;
		}

        else
        {
            sdata->memcard_stage = MC_STAGE_IDLE;
            sdata->memoryCard_SizeRemaining = 0;
            return event;
        }
	}
	// after checking new card
    case MC_STAGE_NEWCARD:

        event = MEMCARD_GetNextSwEvent();

        if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;
		
		sdata->memcard_stage = MC_STAGE_IDLE;

		// if new card passed a "load" test (after format),
		// set stage to idle, record free bytes
        if (event == MC_RETURN_IOE)
        {
            sdata->memcardStatusFlags &= ~(1);
			sdata->memcardStatusFlags |= 2;
            MEMCARD_GetFreeBytes(sdata->memcardSlot);
            return MC_RETURN_NEWCARD;
        }
		
		// if new card was just inserted
        if (event == MC_RETURN_NEWCARD)
        {
            sdata->memcardStatusFlags &= ~(1|2);
            return MC_RETURN_UNFORMATTED;
        }
		
        return event;

	// after the attempt to read header,
	// MC_STAGE_LOAD_PART1_HEADER
    case 3:

        event = MEMCARD_GetNextSwEvent();

        if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;

		// if pass, then move to next stage,
		// setup variables for the load about to happen
        if (event == MC_RETURN_IOE)
        {
            sdata->memcard_stage++;

			// TODO: struct MemcardWORD
			// S, C, iconSize, blockSize

            sdata->memcardIconSize = ((sdata->memcard_ptrStart[2] & 0xf) + 1) * 0x80;

            readResult = MEMCARD_ReadFile(sdata->memcardIconSize, sdata->memcardFileSize);

			// Search for "MEMCARD_SET_SIZE_BYTE3"
            if (
				// if a ghost file (2x) is larger than 1 memcard block file
				// if the number of blocks in this save, is more than 1 block
                // ((sdata->memcardIconSize + sdata->memcardFileSize * 2 + 0x1fff >> 0xd) > 1) &&
				// ((sdata->memcardIconSize + sdata->memcardFileSize * 1 + 0x1fff >> 0xd) < ((int)(unsigned char)sdata->memcard_ptrStart[3]))
				
				// if 2 blocks in the file
				((int)(unsigned char)sdata->memcard_ptrStart[3]) == 2
				)
            {
				// 1-slot file
                sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffb;
                return readResult;
            }
			
			// 2-slot file
            sdata->memcardStatusFlags = sdata->memcardStatusFlags | 4;
            return readResult;
        }

		if (sdata->memcard_remainingAttempts < 1)
		{
			extra = MC_EXTRA_CLOSE;
			break;
		}

        sdata->memcard_remainingAttempts--;
		extra = MC_EXTRA_READ_ICON;
		break;
	
	// LOAD Data
    case 4:
    case 6:

        event = MEMCARD_GetNextSwEvent();

        if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;

        if (event == MC_RETURN_IOE)
        {
            sdata->crc16_checkpoint_byteIndex = 0;
            sdata->crc16_checkpoint_status = 0;
            sdata->memcard_stage++;
			return MC_RETURN_PENDING;
        }
		else
		{
			if (sdata->memcard_remainingAttempts < 1)
			{
				extra = MC_EXTRA_CLOSE;
				break;
			}
			
			sdata->memcard_remainingAttempts--;
			extra = MC_EXTRA_READ_FILE;
			break;
		}

    case 5:
    case 7:
    CASE7_JUMP:

        event = MEMCARD_ChecksumLoad(sdata->memcard_ptrStart, sdata->memcardFileSize);

        if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;

		// This should have no IF,
		// that way it always returns 0 or 1
        if (event == MC_RETURN_IOE)
        {
			extra = MC_EXTRA_CLOSE;
			break;
		}
			
        // at this point, assume checksum failed (return 1),
		// if loading 2-block save, read again, then retry checksum
		
		// THIS WILL NEVER HAPPEN,
		// the |4 flag is never used for LOAD
        if (((sdata->memcardStatusFlags & 4) == 0) && (sdata->memcard_stage < 7))
        {
            sdata->memcard_stage++;
			extra = MC_EXTRA_READ_FILE;
			break;
        }
		
		return event;
    
	// SAVE Data
    case 9:
    case 10:
    case 11:

        event = MEMCARD_GetNextSwEvent();
            
		if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;
			
        if (event == MC_RETURN_IOE)
        {
			if (
					// 1-file write
					(sdata->memcard_stage == 9) || 
					(
						// 2-file write
						((sdata->memcard_stage <= 10)) &&
						((sdata->memcardStatusFlags & 4) != 0)
					)
				)
			{
				sdata->memcard_stage++;	
				extra = MC_EXTRA_WRITE_FILE;
				break;
			}
			
            else
            {
                MEMCARD_CloseFile();
                MEMCARD_GetFreeBytes(sdata->memcardSlot);
                return MC_RETURN_IOE;
            }
        }

        else
        {
			if (sdata->memcard_remainingAttempts < 1)
            {
				extra = MC_EXTRA_CLOSE;
				break;
			}

            sdata->memcard_remainingAttempts--;
            
			if (sdata->memcard_stage == 9)
			{
				extra = MC_EXTRA_WRITE_ICON;
				break;
			}
			
			extra = MC_EXTRA_WRITE_FILE;
			break;
        }				
		
		
    case MC_STAGE_ERASE_FAIL:
        sdata->memcard_stage = MC_STAGE_IDLE;
        return MC_RETURN_TIMEOUT;
		
    case MC_STAGE_ERASE_PASS:
        sdata->memcard_stage = MC_STAGE_IDLE;
        return MC_RETURN_IOE;
		
    default:
        return MC_RETURN_TIMEOUT;
    }
	
	switch(extra)
	{
		case MC_EXTRA_NULL:
			while(1) {
				printf("Did not return?\n");
			}
			
		case MC_EXTRA_CLOSE:
			MEMCARD_CloseFile();
			return event;
			
		case MC_EXTRA_WRITE_ICON:
			return MEMCARD_WriteFile(0, 
				sdata->memcardIcon_PsyqHand, 
				sdata->memcardIconSize);
				
		case MC_EXTRA_WRITE_FILE:
			return MEMCARD_WriteFile(
				sdata->memcardIconSize + (sdata->memcard_stage - 10) * sdata->memcardFileSize,
				sdata->memcard_ptrStart,
				sdata->memcardFileSize);
				
		case MC_EXTRA_READ_ICON:
			return MEMCARD_ReadFile(0, 0x80);
			
		case MC_EXTRA_READ_FILE:
            return MEMCARD_ReadFile(
				sdata->memcardIconSize + (sdata->memcard_stage - 4) * sdata->memcardFileSize, 
				sdata->memcardFileSize);
	};
	

}