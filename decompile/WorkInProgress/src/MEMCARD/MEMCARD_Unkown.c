#include <common.h>

// TODO: Name function, add symbol
int FUN_8003ddac(void)
{
    int readResult;
    int event;
    int iVar4;
    int *ptrData;

    switch (sdata->unk_card_8008D404)
    {

    case 1:

        event = MEMCARD_GetNextSwEvent();

        if (event == 0)
        {
            // If this is the first frame of the main game loop,
            // after all initialization is done
            if ((sdata->memcardStatusFlags & 1) != 0)
            {
                // allow the "switch" statement to go to stage 2
                sdata->unk_card_8008D404 = 2;

                // do something wtih both memcards if they're present,
                MEMCARD_SkipEvents();

                // ?? spam read until it works?
                while (_card_load(sdata->memcardSlot) != 1)
                    ;

                return 7;
            }
            if ((sdata->memcardStatusFlags & 2) == 0)
            {
                sdata->memoryCard_SizeRemaining = 0;

                event = 5;
            }
        }

        else
        {
            if (event != 3)
            {
                if (event != 7)
                {
                    sdata->unk_card_8008D404 = 0;

                    sdata->memoryCard_SizeRemaining = 0;

                    return event;
                }
                return 7;
            }
            MEMCARD_SkipEvents();
            while (_card_clear(sdata->memcardSlot) != 1)
                ;
            event = MEMCARD_WaitForHwEvent();
            if (event == 0)
            {
                sdata->unk_card_8008D404 = 2;
                MEMCARD_SkipEvents();
                while (_card_load(sdata->memcardSlot) != 1)
                    ;
                return 7;
            }
        }

        goto LAB_8003df38;

    case 2:

        event = MEMCARD_GetNextSwEvent();

        if (event == 0)
        {
            sdata->unk_card_8008D404 = 0;
            sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffe | 2;

            MEMCARD_GetFreeBytes(sdata->memcardSlot);

            return 3;
        }
        if (event == 3)
        {
            sdata->unk_card_8008D404 = 0;
            sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffc;
            return 5;
        }
        if (event == 7)
        {
            return 7;
        }
    LAB_8003df38:
        sdata->unk_card_8008D404 = 0;
        break;

    case 3:

        event = MEMCARD_GetNextSwEvent();

        if (event == 0)
        {
            // allow "switch" statement to go to stage 4
            sdata->unk_card_8008D404 = 4;

            // Bitwise & with 0xf to extract last 4 bits then increment by 1
            sdata->memcardIconSize = ((sdata->memcard_ptrStart[2] & 0xf) + 1) * 0x80;

            readResult = MEMCARD_ReadFile(sdata->memcardIconSize, sdata->memoryCardFileSize_0x1680);

            // count blocks of size 0x200 there are being compared to remaining blocks most likely
            if ((sdata->memcardIconSize + sdata->memoryCardFileSize_0x1680 + 0x1fff >> 0xd < ((int)(unsigned char)sdata->memcard_ptrStart[3])) &&
                (1 < sdata->memcardIconSize + sdata->memoryCardFileSize_0x1680 * 2 + 0x1fff >> 0xd))
            {
                sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffb;
                return readResult;
            }
            sdata->memcardStatusFlags = sdata->memcardStatusFlags | 4;
            return readResult;
        }

        if (event == 7)
        {
            return 7;
        }

        if (sdata->memcard_remainingAttempts > 0)
        {
            iVar4 = 0;
            event = 0x80;

            sdata->memcard_remainingAttempts = sdata->memcard_remainingAttempts - 1;

            goto READCARD_JUMP;
        }

        goto CLOSEFILE_JUMP;

    case 4:
    case 6:

        event = MEMCARD_GetNextSwEvent();

        if (event == 0)
        {
            sdata->crc16_checkpoint_byteIndex = 0;
            sdata->crc16_checkpoint_status = 0;
            sdata->unk_card_8008D404 = sdata->unk_card_8008D404 + 1;
            if ((sdata->memcardStatusFlags & 8) == 0)
            {
                sdata->crc16_checkpoint_byteIndex = 0;
                sdata->crc16_checkpoint_status = 0;
                return 7;
            }
            goto CASE7_JUMP;
        }

        if (event == 7)
        {
            return 7;
        }

        if (sdata->memcard_remainingAttempts > 0)
        {
            iVar4 = sdata->memcardIconSize + (sdata->unk_card_8008D404 - 4) * sdata->memoryCardFileSize_0x1680;
            event = sdata->memoryCardFileSize_0x1680;

            sdata->memcard_remainingAttempts = sdata->memcard_remainingAttempts + -1;

            goto READCARD_JUMP;
        }

        goto CLOSEFILE_JUMP;

    case 5:
    case 7:
    CASE7_JUMP:

        event = MEMCARD_ChecksumLoad(sdata->memcard_ptrStart, sdata->memoryCardFileSize_0x1680);

        if (event != 0)
        {
            // if checksumLoad returned 7, then the checksum
            // is not finished processing, it will continue next frame
            if (event == 7)
            {
                return 7;
            }

            // at this point, assume checksum succeeded (return 1)

            if (((sdata->memcardStatusFlags & 4) == 0) && (iVar4 = sdata->unk_card_8008D404 - 3, sdata->unk_card_8008D404 < 7))
            {
                // Make "switch" statement go to "next" stage
                sdata->unk_card_8008D404 = sdata->unk_card_8008D404 + 1;

                iVar4 = sdata->memcardIconSize + iVar4 * sdata->memoryCardFileSize_0x1680;
                event = sdata->memoryCardFileSize_0x1680;
            READCARD_JUMP:

                return MEMCARD_ReadFile(iVar4, event);
            }
        }
    CLOSEFILE_JUMP:
        MEMCARD_CloseFile();
        break;
    default:
        event = 1;
        break;
    case 9:
    case 10:
    case 11:

        event = MEMCARD_GetNextSwEvent();

        if (event == 0)
        {
            if ((sdata->unk_card_8008D404 != 9) && ((10 < sdata->unk_card_8008D404 || ((sdata->memcardStatusFlags & 4) != 0))))
            {
                MEMCARD_CloseFile();

                MEMCARD_GetFreeBytes(sdata->memcardSlot);

                return 0;
            }
            event = sdata->unk_card_8008D404 - 9;
            sdata->unk_card_8008D404 = sdata->unk_card_8008D404 + 1;
        LAB_8003e1e4:
            iVar4 = sdata->memcardIconSize + event * sdata->memoryCardFileSize_0x1680;

            // pointer to memory card bytes
            ptrData = sdata->memcard_ptrStart;

            // size, 0x1680 bytes
            event = sdata->memoryCardFileSize_0x1680;
        }

        else
        {
            if (event == 7)
            {
                return 7;
            }

            // reduce remaining number of attempts
            iVar4 = sdata->memcard_remainingAttempts - 1;

            // if out of attempts, go to close file
            if (sdata->memcard_remainingAttempts < 1)
                goto CLOSEFILE_JUMP;

            event = sdata->unk_card_8008D404 - 10;
            sdata->memcard_remainingAttempts = iVar4;
            if (sdata->unk_card_8008D404 != 9)
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
    case 13:
        sdata->unk_card_8008D404 = 0;
        event = 1;
        break;
    case 14:
        sdata->unk_card_8008D404 = 0;
        event = 0;
    }
    return event;
}