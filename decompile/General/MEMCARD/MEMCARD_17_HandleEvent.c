#include <common.h>

// Not part of original game,
// just for cleaning up repetition
enum MC_EXTRA
{
	MC_EXTRA_NULL,
	MC_EXTRA_CLOSE,
	MC_EXTRA_WRITE_ICON,
	MC_EXTRA_WRITE_FILE,
	MC_EXTRA_READ_FILE
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
			
			// retail feature, this spams every frame,
			// is this for finding unplugged cards?
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
	{
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
	}

	// after requesting to load for first time
	case MC_STAGE_LOAD_PART0_START:

		sdata->memcard_stage++;
		extra = MC_EXTRA_READ_FILE;
		break;
		
	// HEADER code skipped
	
	// LOAD Data
    case MC_STAGE_LOAD_PART2_READ:

        event = MEMCARD_GetNextSwEvent();

        if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;

        if (event == MC_RETURN_IOE)
        {
            sdata->memcard_stage++;
			return MC_RETURN_PENDING;
        }
		else
		{
			extra = MC_EXTRA_READ_FILE;
			break;
		}

    case MC_STAGE_LOAD_PART3_CHECK:

        event = MEMCARD_ChecksumLoad(sdata->memcard_ptrStart, sdata->memcardFileSize);

        if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;

		extra = MC_EXTRA_CLOSE;
		break;
		
	case MC_STAGE_SAVE_PART0_START:
			
		int DECOMP_MEMCARD_ChecksumSave(unsigned char* saveBytes, int len);
		event = DECOMP_MEMCARD_ChecksumSave(sdata->memcard_ptrStart, sdata->memcardFileSize);
		
		if (event == MC_RETURN_PENDING)
			return MC_RETURN_PENDING;
		
		sdata->memcard_stage++;
		extra = MC_EXTRA_WRITE_ICON;
		break;
	
    case MC_STAGE_SAVE_PART1_ICON:
	
        event = MEMCARD_GetNextSwEvent();
            
		if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;
			
        if (event == MC_RETURN_IOE)
        {		
			sdata->memcard_stage++;	
			extra = MC_EXTRA_WRITE_FILE;
			break;
		}
		
		else
		{			
			extra = MC_EXTRA_WRITE_ICON;
			break;
		}
		
		break;
	
    case MC_STAGE_SAVE_PART2_WRITE:

        event = MEMCARD_GetNextSwEvent();
            
		if (event == MC_RETURN_PENDING)
            return MC_RETURN_PENDING;
			
        if (event == MC_RETURN_IOE)
        {
            MEMCARD_CloseFile();
            MEMCARD_GetFreeBytes(sdata->memcardSlot);
            return MC_RETURN_IOE;
        }

        else
        {			
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
		// if HandleEvent was called for a STAGE_DONE
        return MC_RETURN_TIMEOUT;
    }
	
	// Whether pass or fail, deduct one chance anyway
	{
		if (sdata->memcard_remainingAttempts < 1)
		{
			extra = MC_EXTRA_CLOSE;
		}

		sdata->memcard_remainingAttempts--;
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
		
			int* icon = &data.memcardIcon_CrashHead[0];
			if (sdata->memcardFileSize == 0x3E00)
				icon = &data.memcardIcon_Ghost[0];
		
			return MEMCARD_WriteFile(
				0, icon, 
				sdata->memcardIconSize);
				
		case MC_EXTRA_WRITE_FILE:
			return MEMCARD_WriteFile(
				sdata->memcardIconSize,
				sdata->memcard_ptrStart,
				sdata->memcardFileSize);
				
		//case MC_EXTRA_READ_HEADER:
		//	return MEMCARD_ReadFile(0, 0x80);
			
		case MC_EXTRA_READ_FILE:
            return MEMCARD_ReadFile(
				// offset and size,
				// read pointer is assumed
				sdata->memcardIconSize, 
				sdata->memcardFileSize);
	};
}

int MEMCARD_NewFunc_AsyncCRC(unsigned char* saveBytes, int len)
{
	int i;
	int crc;
	int byteIndexEnd;
	int byteIndexStart;
	int boolFinishThisFrame = 1;
	
	// Leave 2 bytes at the end,
	// the checksum is stored there
	len -= 2;
	byteIndexEnd = len;

	// Option 1: Set ZERO for first-frame of multi-frame load
	// Option 2: Set existing checkpoint from previous frame
	crc = sdata->crc16_checkpoint_status;
	byteIndexStart = sdata->crc16_checkpoint_byteIndex;
	
	// if more than 512 bytes remain
	if (byteIndexEnd > (byteIndexStart + 0x200))
	{
		// cap to 512 bytes, and then continue next frame
		byteIndexEnd = (byteIndexStart + 0x200);
		boolFinishThisFrame = 0;
	}
	
	// run checksum
	for (i = byteIndexStart; i < byteIndexEnd; i++)
	{
		crc = MEMCARD_CRC16(crc, saveBytes[i]);
	}

	// save checkpoints for next frame
	sdata->crc16_checkpoint_status = crc;
	sdata->crc16_checkpoint_byteIndex = byteIndexEnd;

	if (boolFinishThisFrame == 0)
	{	
		return MC_RETURN_PENDING;
	}
	
	return MC_RETURN_IOE;
}