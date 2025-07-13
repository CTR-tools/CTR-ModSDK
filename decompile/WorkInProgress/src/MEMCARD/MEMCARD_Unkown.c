#include <common.h>

// TODO: Name function, add symbol (MEMCARD_GetStageResult)
int FUN_8003ddac(void)
{
    int readResult;
    int event;
    int iVar4;
    int *ptrData;

    switch (sdata->memcard_stage)
    {

	// after checking info
    case MC_STAGE_GETINFO:

        event = MEMCARD_GetNextSwEvent();
		
        if (event == MC_RETURN_PENDING)
			return 0;

        else if (event == MC_RETURN_IOE)
        {
            // If this is the first frame of the main game loop,
            // after all initialization is done
            if ((sdata->memcardStatusFlags & 1) != 0)
            {
				// discard any previous events
				// submit a load to make sure format worked,
				// check the result of a NEW CARD
                MEMCARD_SkipEvents();
                while (_card_load(sdata->memcardSlot) != 1);
                sdata->memcard_stage = MC_STAGE_NEWCARD;
                return 7;
            }
            if ((sdata->memcardStatusFlags & 2) == 0)
            {
                sdata->memoryCard_SizeRemaining = 0;
                event = 5;
            }
        }

        else if (event == MC_RETURN_NEWCARD)
        {
			MEMCARD_SkipEvents();
			while (_card_clear(sdata->memcardSlot) != 1);
			
			event = MEMCARD_WaitForHwEvent();
			if (event == 0)
			{
				// discard any previous events
				// submit a load to make sure format worked,
				// check the result of a NEW CARD
				MEMCARD_SkipEvents();
				while (_card_load(sdata->memcardSlot) != 1);
				sdata->memcard_stage = MC_STAGE_NEWCARD;
				return 7;
			}
		}

        else
        {
            sdata->memcard_stage = MC_STAGE_IDLE;
            sdata->memoryCard_SizeRemaining = 0;
            return event;
        }

        sdata->memcard_stage = MC_STAGE_IDLE;
        break;

	// after checking new card
    case MC_STAGE_NEWCARD:

        event = MEMCARD_GetNextSwEvent();

		// if nothing happened yet, try again next frame
        if (event == MC_RETURN_PENDING)
            return 0;
		
		sdata->memcard_stage = MC_STAGE_IDLE;

		// if new card passed a "load" test (after format),
		// set stage to idle, record free bytes
        if (event == MC_RETURN_IOE)
        {
            sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffe | 2;
            MEMCARD_GetFreeBytes(sdata->memcardSlot);
            return 3;
        }
		
		// if new card was just inserted
        if (event == MC_RETURN_NEWCARD)
        {
            sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffc;
            return 5;
        }
		
        break;

	// after the attempt to read icon,
	// MC_STAGE_LOAD_PART1_ICON
    case 3:

        event = MEMCARD_GetNextSwEvent();

		// if nothing happened yet, try again next frame
        if (event == MC_RETURN_PENDING)
        {
            return 7;
        }

		// if pass, then move to next stage,
		// setup variables for the load about to happen
        if (event == MC_RETURN_IOE)
        {
            sdata->memcard_stage++;

            sdata->memcardIconSize = ((sdata->memcard_ptrStart[2] & 0xf) + 1) * 0x80;

            readResult = MEMCARD_ReadFile(sdata->memcardIconSize, sdata->memcardFileSize);

			// Search for "MEMCARD_SET_SIZE_BYTE3"
            if (
                // ((sdata->memcardIconSize + sdata->memcardFileSize * 2 + 0x1fff >> 0xd) > 1) &&
				   ((sdata->memcardIconSize + sdata->memcardFileSize * 1 + 0x1fff >> 0xd) < ((int)(unsigned char)sdata->memcard_ptrStart[3]))
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

		// if failed, restart attempting icon
        if (sdata->memcard_remainingAttempts > 0)
        {
			// replicate MEMCARD_ReadFile(0, 0x80) from MEMCARD_LOAD
            iVar4 = 0;
            event = 0x80;

            sdata->memcard_remainingAttempts = sdata->memcard_remainingAttempts - 1;

            goto READCARD_JUMP;
        }

        goto CLOSEFILE_JUMP;

    case 4:
    case 6:

        event = MEMCARD_GetNextSwEvent();

        if (event == MC_RETURN_PENDING)
        {
            return 7;
        }

        if (event == MC_RETURN_IOE)
        {
            sdata->crc16_checkpoint_byteIndex = 0;
            sdata->crc16_checkpoint_status = 0;
            sdata->memcard_stage = sdata->memcard_stage + 1;
            if ((sdata->memcardStatusFlags & 8) == 0)
            {
                sdata->crc16_checkpoint_byteIndex = 0;
                sdata->crc16_checkpoint_status = 0;
                return 7;
            }
            goto CASE7_JUMP;
        }

        if (sdata->memcard_remainingAttempts > 0)
        {
            iVar4 = sdata->memcardIconSize + (sdata->memcard_stage - 4) * sdata->memcardFileSize;
            event = sdata->memcardFileSize;

            sdata->memcard_remainingAttempts = sdata->memcard_remainingAttempts + -1;

            goto READCARD_JUMP;
        }

        goto CLOSEFILE_JUMP;

    case 5:
    case 7:
    CASE7_JUMP:

        event = MEMCARD_ChecksumLoad(sdata->memcard_ptrStart, sdata->memcardFileSize);

        if (event == MC_RETURN_PENDING)
        {
            return 7;
        }

        if (event == MC_RETURN_IOE)
        {
		CLOSEFILE_JUMP:
			MEMCARD_CloseFile();
			break;
		}
			
        // at this point, assume checksum succeeded (return 1)

        if (((sdata->memcardStatusFlags & 4) == 0) && (sdata->memcard_stage < 7))
        {
            // Make "switch" statement go to "next" stage
            sdata->memcard_stage = sdata->memcard_stage + 1;

            iVar4 = sdata->memcardIconSize + (sdata->memcard_stage - 4) * sdata->memcardFileSize;
            event = sdata->memcardFileSize;
        
		READCARD_JUMP:
            return MEMCARD_ReadFile(iVar4, event);
        }
		
		break;
        
    default:
        event = 1;
        break;
    case 9:
    case 10:
    case 11:

        event = MEMCARD_GetNextSwEvent();
            
		if (event == MC_RETURN_PENDING)
        {
            return 7;
        }
			
        if (event == MC_RETURN_IOE)
        {
            if ((sdata->memcard_stage != 9) && ((10 < sdata->memcard_stage || ((sdata->memcardStatusFlags & 4) != 0))))
            {
                MEMCARD_CloseFile();

                MEMCARD_GetFreeBytes(sdata->memcardSlot);

                return 0;
            }
            
			sdata->memcard_stage = sdata->memcard_stage + 1;
			
        LAB_8003e1e4:
            event = sdata->memcard_stage - 10;
            iVar4 = sdata->memcardIconSize + event * sdata->memcardFileSize;

            // pointer to memory card bytes
            ptrData = sdata->memcard_ptrStart;

            // size, 0x1680 bytes
            event = sdata->memcardFileSize;
        }

        else
        {
            // reduce remaining number of attempts
            iVar4 = sdata->memcard_remainingAttempts - 1;

            // if out of attempts, go to close file
            if (sdata->memcard_remainingAttempts < 1)
                goto CLOSEFILE_JUMP;

            sdata->memcard_remainingAttempts = iVar4;
            if (sdata->memcard_stage != 9)
                goto LAB_8003e1e4;
			
            iVar4 = 0;

            // pointer to memory card icon
            // psyq hand
            ptrData = Data->memcardIcon_PsyqHand;

            // 256 bytes, 0x100
            event = sdata->memcardIconSize;
        }

        event = MEMCARD_WriteFile(iVar4, ptrData, event);
        break;
		
    case MC_STAGE_ERASE_FAIL: // 13
        sdata->memcard_stage = MC_STAGE_IDLE;
        event = MC_RETURN_TIMEOUT; // 1
        break;
		
    case MC_STAGE_ERASE_PASS: // 14
        sdata->memcard_stage = MC_STAGE_IDLE;
        event = MC_RETURN_IOE; // 0
    }
    return event;
}