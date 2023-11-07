#include "LIBSPU.H"
#include "LIBETC.H"
#include <stdio.h>
#include "Core/EMULATOR.H"
#include "LIBAPI.H"

#include "Core/Audio/EMULATOR_SPU.H"

#if defined(OPENAL)

#elif defined(XAUDIO2)

#include <xaudio2.h>
#include <assert.h>

IXAudio2* pXAudio2 = NULL;
IXAudio2MasteringVoice* pMasterVoice = NULL;
IXAudio2SourceVoice* pSourceVoices[24];

#endif

struct Channel channelList[SPU_MAX_CHANNELS];
short g_spuLeftVol = 0;
short g_spuRightVol = 0;

#include <string.h>

#define SPU_CENTERNOTE (-32768 / 2)

SpuTransferCallbackProc __spu_transferCallback = NULL;

short _spu_voice_centerNote[24] =
{
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE,
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE,
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE
};

unsigned short word_300[] = 
{
  0x8000,0x879c,0x8fac,0x9837,0xa145,0xaadc,0xb504,0xbfc8,0xcb2f,0xd744,0xe411,0xf1a1 
};

unsigned short word_318[] =
{
  0x8000,0x800e,0x801d,0x802c,0x803b,0x804a,0x8058,0x8067,0x8076,0x8085,0x8094,0x80a3
};

unsigned short E40[] =
{
    1799, 1799, 1799, 1799, 1799, 1799, 1799, 1799
};

unsigned short _spu_rev_attr[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

short _spu_RQ[10];

SpuCommonAttr dword_424;//Might be wrong struct, need to check
int _spu_isCalled = 0;
int _spu_FiDMA = 0;
int _spu_EVdma = 0;
int _spu_rev_flag = 0;
int _spu_rev_reserve_wa = 0;
int _spu_rev_offsetaddr;
int _spu_rev_startaddr [] = {0xFFFE, 0xFB28, 0xFC18, 0xF6F8, 0xF204, 0xEA44, 0xE128, 0xCFF8, 0xCFF8, 0xF880};
int _spu_AllocBlockNum = 0;
int _spu_AllocLastNum = 0;
int _spu_memList = 0;
int _spu_trans_mode = 0;
int _spu_transMode = 0;
int _spu_addrMode = 0;
int _spu_keystat = 0;
int _spu_RQmask = 0;
int _spu_RQvoice = 0;
int _spu_env = 0;
int _spu_mem_mode = 2;
int _spu_mem_mode_unit = 8;
int _spu_mem_mode_unitM = 7;
char spu[440];//0x1F801C00 is base address
unsigned short* _spu_RXX = (unsigned short*)&spu[0];
int _spu_mem_mode_plus = 3;
void* _spu_transferCallback = NULL;///@TODO initial value check
int _spu_inTransfer = 0;///@TODO initial value check
int _spu_IRQCallback = 0;
int dword_800CED70 = 0;
unsigned short _spu_tsa = 0;
int _spu_keystat_last = 0;
char spuSoundBuffer[524288];

long spuWriteSizes[1024];
int lastWriteIndex = 0;

int _spu_note2pitch(int a0, int a1, int a2, int a3)
{
    a3 += a1;
    a1 = 0x2AAAAAAB;
    int v1 = a3 & 0xFFFF;
    int v0 = v1 >> 7;
    a2 += v0;
    a2 -= a0;
    a2 <<= 16;
    a0 = a2 >> 16;
    int t0 = a0 % a1;
    a3 = v1 & 0x7F;
    a2 >>= 31;
    v0 = t0 >> 1;
    a1 = v0 - a2;
    a2 = a1 - 2;
    v0 = a1 << 1;
    v0 += a1;
    v0 <<= 2;
    a0 -= v0;
    v0 = a0 << 16;
    v1 = a0;
    if (v0 < 0)
    {
        v1 = a0 + 12;
        a2 = a1 - 3;
    }//loc_164

    v0 = a3 & 0xFFFF;

    v1 = word_300[v1];
    v0 = word_300[v0];

    t0 = v1 * v0;
    v0 = a2;
    a1 = t0 >> 16;

    if (v0 >= 0)
    {
        a1 = 0x3FFF;
    }
    else
    {
        a0 = -v0;
        v1 = a0 - 1;
        v0 = 1 << v1;
        a1 += v0;
        a1 = a1 >> a0;
    }

    return a1 & 0xFFFF;
}

int _spu_FsetRXXa(long flag, long addr)
{
    if (_spu_mem_mode != 0)
    {
        if (_spu_mem_mode_unit != 0)
        {
            if (addr % _spu_mem_mode_unit != 0)
            {
                addr += _spu_mem_mode_unit;
                addr &= ~_spu_mem_mode_unitM;
            }
            //loc_BA0
        }
    }
    //loc_BA0
    if (flag == -2)
    {
        return addr;
    }
    else if (flag == -1)
    {
        return (addr >> _spu_mem_mode_plus) & 0xFFFF;
    }
    else
    {
        //loc_BD8
        _spu_RXX[flag] = (short)(addr >> _spu_mem_mode_plus);
    }

    return addr;
}

void SpuGetAllKeysStatus(char* status)
{
	//loc_2EC
	for (int i = 0; i < 24; i++, status++)
	{
		if ((_spu_keystat & (1 << i)))
		{
			if (channelList[i].data != NULL && channelList[i]._adsr.envelopevol > 0) //(unsigned short)_spu_RXX[(i << 3) + 6] != 0)
			{
				*status = SPU_ON;
			}
			else
			{
				*status = SPU_ON_ENV_OFF;
			}
		}
		else
		{
			//loc_330
            if (channelList[i].data == NULL && channelList[i]._adsr.envelopevol > 0)//_spu_RXX[(i << 3) + 6] != 0)
			{
				*status = SPU_OFF_ENV_ON;
			}
			else
			{
				//loc_340
				*status = SPU_OFF;
			}
		}
	}
}

void SpuSetVoiceAttr(SpuVoiceAttr* arg)//
{
#if 0//TRC only ;-(
    _SpuRSetVoiceAttr();
#else

    //s0 = arg
    int a0 = 0;
    int a1 = 0;
    int a2 = 0;
    //s1 = arg->mask
    //s5 = &_spu_voice_centerNote[0];
    //s2 = s1 < 1 ? 1 : 0;

    //loc_238
    for(int i = 0; i < 24; i++)
    {
        //v0 = 1
        //v1 = arg->voice
        //v0 = 1 << i
        //v1 = arg->voice & (1 << i);

        if ((arg->voice & (1 << i)))
        {
            //s3 = i << 3
            if ((arg->mask < 1) || (arg->mask & 0x10))
            {
                //loc_264
                //v0 = i << 4
                //v1 = &_spu_RXX[0];
                //a0 = arg->pitch
                _spu_RXX[(i << 3) + 2] = arg->pitch;
            }
            //loc_27C
            if (arg->mask < 1 || (arg->mask & 0x40))
            {
                _spu_voice_centerNote[i] = arg->sample_note;
            }
            //loc_298
            if (arg->mask < 1 || (arg->mask & 0x20))
            {
                //a1 = _spu_voice_centerNote[i] & 0xFF
                //a3 = arg->note
                //a0 = _spu_voice_centerNote[i] >> 8
                //a2 = arg->note >> 8
                //a3 = arg->note & 0xFF
                //v0 = 
                _spu_RXX[(i << 3) + 2] = _spu_note2pitch((_spu_voice_centerNote[i] >> 8), (_spu_voice_centerNote[i] & 0xFF), (arg->note >> 8), (arg->note & 0xFF));
            }
            //loc_2D8
            if (arg->mask < 1 || (arg->mask & 0x1))
            {
                //v0 = arg->volume.left
                //a0 = 0
                //a1 = arg->volume.left & 0x7FFF
                //v0 = arg->mask & 4

                if (!(arg->mask & 0x4))
                {
                    //v0 = arg->volmode.left
                    switch (arg->volmode.left)
                    {
                    case 1:
                        //loc_33C
                        a0 = 0x8000;
                        break;
                    case 2:
                        //loc_344
                        a0 = 0x9000;
                        break;
                    case 3:
                        //loc_34C
                        a0 = 0xA000;
                        break;
                    case 4:
                        //loc_354
                        a0 = 0xB000;
                        break;
                    case 5:
                        //loc_35C
                        a0 = 0xC000;
                        break;
                    case 6:
                        //loc_364
                        a0 = 0xD000;
                        break;
                    case 7:
                        //loc_36C
                        a0 = 0xE000;
                        break;
                    }
                }
                //def_334
                if (a0 != 0)
                {
                    //v1 = arg->volume.left
                    if (arg->volume.left >= 128)
                    {
                        a1 = 127;
                    }
                    else if (arg->volume.left < 0)
                    {
                        a1 = 0;
                    }
                }
                //loc_3A0
                //v0 = &_spu_RXX[0];
                //v1 = &spu_RXX[i << 3];

                //v0 = a1 | a0
                _spu_RXX[(i << 3)] = a1 | a0;
            }//loc_3B8

            if ((arg->mask < 1) || (arg->mask & 0x2))
            {
                //v0 = arg->volume.right
                //a0 = 0
                //a1 = v0 & 0x7FFF

                if ((arg->mask < 1) || (arg->mask & 0x8))
                {
                    switch (arg->volmode.right)
                    {
                    case 1:
                        //loc_41C
                        a0 = 0x8000;
                        break;
                    case 2:
                        //loc_424
                        a0 = 0x9000;
                        break;
                    case 3:
                        //loc_42C
                        a0 = 0xA000;
                        break;
                    case 4:
                        //loc_434
                        a0 = 0xB000;
                        break;
                    case 5:
                        //loc_43C
                        a0 = 0xC000;
                        break;
                    case 6:
                        //loc_444
                        a0 = 0xD000;
                        break;
                    case 7:
                        //loc_44C
                        a0 = 0xE000;
                        break;
                    }
                }

                //def_414
                if (a0 != 0)
                {
                    if (arg->volume.right >= 128)
                    {
                        a1 = 127;
                    }
                    else if (arg->volume.right < 0)
                    {
                        a1 = 0;
                    }
                }//loc_480

                //v0 = &_spu_RXX[0];
                //v1 = &_spu_RXX[i << 3];
                _spu_RXX[(i << 3) + 1] = a1 | a0;
            }//loc_498

            if ((arg->mask < 1) || (arg->mask & 0x80))
            {
                _spu_FsetRXXa(((i << 3) | 3), arg->addr);
            }
            //loc_4B4
            if ((arg->mask < 1) || (arg->mask & 0x10000))
            {
                _spu_FsetRXXa((i << 3) | 7, arg->loop_addr);
            }//loc_4D4

            if ((arg->mask < 1) || (arg->mask & 0x20000))
            {
                _spu_RXX[i << 3] = arg->adsr1;
            }

            //loc_500
            if ((arg->mask < 1) || (arg->mask & 0x40000))
            {
                _spu_RXX[i << 3] = arg->adsr2;
            }
            //loc_52C

            if ((arg->mask < 1) || (arg->mask & 0x800))
            {
                //a1 = arg->ar
                if (arg->ar >= 128)
                {
                    a1 = 127;
                }

                a2 = 0;

                if ((arg->mask < 1) || (arg->mask & 0x100))
                {
                    //v1 = arg->a_mode
                    //v0 = 5
                    if (arg->a_mode == 5)
                    {
                        a2 = 128;
                    }
                }//loc_57C

                //v0 = &_spu_RXX[0];
                //s3 = &_spu_RXX[i << 3];
                //v0 = _spu_RXX[(i << 3) + 4];
                //v1 = _spu_RXX[(i << 3) + 4] & 0xFF;
                //v0 = ((a1 | a2) << 8)
                _spu_RXX[(i << 3) + 4] = (_spu_RXX[(i << 3) + 4] & 0xFF) | ((a1 | a2) << 8);

            }//loc_5A8

            if ((arg->mask < 1) || arg->mask & 0x1000)
            {
                a1 = arg->dr;
                if (arg->dr >= 16)
                {
                    a1 = 15;
                }//loc_5D0

                _spu_RXX[(i << 3) + 4] = (_spu_RXX[(i << 3) + 4] & 0xFF0F) | (a1 << 4);

            }//loc_5F4

            if ((arg->mask < 1) || (arg->mask & 0x2000))
            {
                a1 = arg->sr;

                if (arg->sr >= 128)
                {
                    a1 = 127;
                }

                a2 = 256;

                if ((arg->mask < 1) || (arg->mask & 0x200))
                {
                    //v1 = arg->s_mode
                    if ((arg->s_mode) == 5)
                    {
                        //loc_674
                        a2 = 512;
                    }
                    else if (arg->s_mode >= 6)
                    {
                        //loc_658
                        if (arg->s_mode == 7)
                        {
                            //loc_67C
                            a2 = 768;
                        }
                    }
                    else if (arg->s_mode == 1)
                    {
                        //loc_66C
                        a2 = 0;
                    }
                }//loc_680
                //v0 = _spu_RXX[(i << 3) + 5];
                //v1 = (_spu_RXX[(i << 3) + 5] & 0x3F) | ((a1 | a2) << 6);
                //v0 = ((a1 | a2) << 6)
                _spu_RXX[(i << 3) + 5] = (_spu_RXX[(i << 3) + 5] & 0x3F) | ((a1 | a2) << 6);
            }//loc_6AC

            if ((arg->mask < 1) || (arg->mask & 0x4000))
            {
                a1 = arg->rr;

                if (arg->rr >= 32)
                {
                    a1 = 31;
                }
                //loc_6D4
                a2 = 0;

                if ((arg->mask < 1) || (arg->mask & 0x400))
                {
                    //v1 = arg->r_mode
                    if (arg->r_mode != 3 && arg->r_mode == 7)
                    {
                        a2 = 32;
                    }//loc_704
                }//loc_704

                //a0 = &_spu_RXX[(i << 3) + 5];
                _spu_RXX[(i << 3) + 5] = (_spu_RXX[(i << 3) + 5] & 0xFFC0) | (a1 | a2);
                //v1 = (a1 | a2)
            }//loc_728

            if ((arg->mask < 1) || arg->mask & 0x8000)
            {
                a1 = arg->sl;
                if ((arg->sl >= 16))
                {
                    a1 = 15;
                }//loc_750

                //v0 = _spu_RXX
                _spu_RXX[(i << 3) + 4] = (_spu_RXX[(i << 3) + 4] & 0xFFF0) | a1;
            }//loc_774
        }//loc_774
    }

    ///@? Not sure what the below is doing yet.
    int scratchPad[256];

    scratchPad[9] = 1;
    scratchPad[10] = 0;

    while (scratchPad[10] < 2)
    {
        //loc_794
        scratchPad[9] <<= 13;
        scratchPad[10]++;
    }
#endif
}

void SpuSetKey(long on_off, unsigned long voice_bit)
{
    voice_bit &= 0xFFFFFF;
    int a2 = voice_bit >> 16;

    if (on_off != 0)
    {
        if (on_off != SPU_ON)
        {
            return;
        }

        if ((_spu_env & 0x1))
        {
            _spu_RQ[0] = (short)voice_bit;
            _spu_RQ[1] = a2;
            _spu_RQmask |= 0x1;
            _spu_RQvoice |= voice_bit;

            if ((_spu_RQ[_spu_RQmask] & voice_bit))
            {
                _spu_RQ[_spu_RQmask] = _spu_RQ[_spu_RQmask] & ~voice_bit;

            }//loc_29C

            if ((_spu_RQ[_spu_RQmask + 1] & voice_bit))
            {
                _spu_RQ[_spu_RQmask + 1] = _spu_RQ[_spu_RQmask + 1] & ~a2;

            }//locret_3B4
        }
        else
        {
            //loc_2C4
            _spu_RXX[196] = (unsigned short)(_spu_keystat | voice_bit);
            _spu_RXX[197] = a2;
            _spu_keystat |= voice_bit;
        }
    }
    else
    {
        //loc_2E4
        if ((_spu_env & 0x1))
        {
            _spu_RQ[_spu_RQmask] = (short)voice_bit;
            _spu_RQ[_spu_RQmask + 1] = a2;
            _spu_RQmask |= 0x1;
            _spu_RQvoice &= (voice_bit ^ -1);

            if ((_spu_RQ[0] & voice_bit))
            {
                _spu_RQ[0] &= voice_bit;
            }
            //loc_360
            if ((_spu_RQ[1] & a2))
            {
                _spu_RQ[1] &= (a2 ^ -1);
            }
            //locret_3B4
        }
        else
        {
            //loc_388
            _spu_RXX[198] = (unsigned short)voice_bit;
            _spu_RXX[199] = a2;
            _spu_keystat &= ~voice_bit;
        }
    }

    if (on_off == 0)
    {
        for (int32_t i = 0; i < SPU_MAX_CHANNELS; i++)
        {
            if (voice_bit & (1 << i) && channelList[i]._adsr.envelopevol == 0)
            {
                channelList[i].data = NULL;
                channelList[i].stop = TRUE;
            }
        }
    }

    _spu_keystat_last |= _spu_keystat;
}

void SpuSetKeyOnWithAttr(SpuVoiceAttr* attr)//(F)
{
	SpuSetVoiceAttr(attr);
	SpuSetKey(SPU_ON, attr->voice);
}

long SpuGetKeyStatus(unsigned long voice_bit)
{
	int a1 = -1;

	//loc_210
	for (int i = 0; i < 24; i++)
	{
		int v0 = 1 << i;

		if ((voice_bit & (1 << i)))
		{
			//loc_240
			if (i != -1)
			{
				//loc_248
				if ((_spu_keystat & (1 << i)) == 0)
				{
					return (0 < _spu_RXX[(i << 3) + 6]) << 1;
				}
				else
				{
					if (_spu_RXX[(i << 3) + 6] == 0)
					{
						return 3;
					}
					else
					{
						return 1;
					}
				}
			}
			else
			{
				return -1;
			}
		}
	}
	if (a1 != -1)
	{
		//loc_248
		if ((_spu_keystat & (1 << a1)) == 0)
		{
			return (0 < _spu_RXX[a1 << 3]) << 1;
		}
		else
		{
			if (_spu_RXX[a1 << 3] == 0)
			{
				return 3;
			}
			else
			{
				return 1;
			}
		}
	}
	else
	{
		return -1;
	}

	return 0;
}


void sub_CB0()
{
    dword_800CED70 &= 0xF0FFFFFF;
    dword_800CED70 |= 0x22000000;
}

void sub_C88()
{
    dword_800CED70 &= 0xF0FFFFFF;
    dword_800CED70 |= 0x20000000;
}

void _spu_Fw(unsigned char* addr, unsigned long size)
{
#if defined(SDL2)
    memcpy(&spuSoundBuffer[_spu_tsa << _spu_mem_mode_plus], addr, size);

    if (__spu_transferCallback != NULL)
    {
        __spu_transferCallback();
    }
#endif
}

unsigned long SpuWrite(unsigned char* addr, unsigned long size)
{
	if (0x7EFF0 < size)
	{
		size = 0x7EFF0;
	}
	
	//loc_228
	_spu_Fw(addr, size);

	if (_spu_transferCallback == NULL)
	{
		_spu_inTransfer = 0;
	}

	return size;
}

long SpuSetTransferMode(long mode)//(F)
{
    int trans_mode = 1;

    if (mode != 0)
    {
        if (mode == 1)
        {
            trans_mode = 1;
        }
        else
        {
            trans_mode = 0;
        }
    }
    else
    {
        //loc_218
        trans_mode = 0;
    }

    _spu_trans_mode = mode;
    _spu_transMode = trans_mode;

	return trans_mode;
}

unsigned long SpuSetTransferStartAddr(unsigned long addr)
{
    if (0x7EFE8 >= addr + 0x1010)
    {
        _spu_tsa = _spu_FsetRXXa(-1, addr);

        return _spu_tsa << _spu_mem_mode_plus;
    }

    return 0;
}

long SpuIsTransferCompleted(long flag)//(F)
{
    long event = 0;

    if (_spu_trans_mode == 1 || _spu_inTransfer == 1)
    {
        return 1;
    }

    event = TestEvent(_spu_EVdma);

    if (flag == 1)
    {
        if (event != 0)
        {
            _spu_inTransfer = 1;
            return 1;
        }
        else
        {
            //loc_260
            do
            {
                event = TestEvent(_spu_EVdma);
            } while (event == 0);

            _spu_inTransfer = 1;
            return 1;
        }
    }
    //loc_280
    if (event == 1)
    {
        _spu_inTransfer = 1;
    }

	return event;
}

void DMACallback(int a0, int callback)
{
    UNIMPLEMENTED();
}

void _SpuDataCallback(int callback)//(F)
{
    DMACallback(4, callback);
}

void SpuStart()//(F)
{
	long event = 0;

	if (_spu_isCalled == 0)
	{
		_spu_isCalled = 1;
		EnterCriticalSection();
		_SpuDataCallback(_spu_FiDMA);
		//event = OpenEvent(HwSPU, EvSpCOMP, EvMdNOINTR, NULL);
		_spu_EVdma = event;
		EnableEvent(event);
		ExitCriticalSection();
	}
	//loc_348
}

void SpuQuit(void)
{
}

void _spu_init(int a0)//(F)
{
	return /*0*/;
}

void _SpuInit(int a0)
{
	ResetCallback();
	_spu_init(a0);

	if (a0 == 0)
	{
		for (int i = 0; i < sizeof(_spu_voice_centerNote) / sizeof(short); i++)
		{
			_spu_voice_centerNote[i] = SPU_CENTERNOTE;
		}
	}
	//loc_240
	SpuStart();

	_spu_rev_flag = 0;
	_spu_rev_reserve_wa = 0;
	dword_424.mask = 0;
	dword_424.mvol.left = 0;
	dword_424.mvol.right = 0;
	dword_424.mvolmode.left = 0;
	dword_424.mvolmode.right = 0;
	dword_424.mvolx.left = 0;
	dword_424.mvolx.right = 0;
	_spu_rev_offsetaddr = _spu_rev_startaddr[0];
	_spu_AllocBlockNum = 0;
	_spu_AllocLastNum = 0;
	_spu_memList = 0;
	_spu_trans_mode = 0;
	_spu_transMode = 0;
	_spu_keystat = 0;
	_spu_RQmask = 0;
	_spu_RQvoice = 0;
	_spu_env = 0;
}

void SpuInit(void)//(F)
{
    _SpuInit(0);

    SPU_Initialise();
}

long SpuSetMute(long on_off)
{
	UNIMPLEMENTED();
	return 0;
}

long SpuSetReverb(long on_off)
{
    return _spu_rev_flag = on_off;;
}

unsigned long _SpuSetAnyVoice(long on_off, unsigned long voice_bit, int a2, int a3)
{
    //UNIMPLEMENTED();
    return 0;
}

unsigned long SpuSetReverbVoice(long on_off, unsigned long voice_bit)
{
    for (int i = 0; i < 32; i++)
    {
        if (voice_bit & (1 << i))
        {
            channelList[i].reverb = TRUE;
        }
    }
    return _SpuSetAnyVoice(on_off, voice_bit, 204, 205);
}

void SpuSetCommonAttr(SpuCommonAttr* attr)
{
	UNIMPLEMENTED();
}

long SpuInitMalloc(long num, char* top)//(F)
{
	if (num > 0)
	{
		//loc_214
		((int*)top)[0] = 0x40001010;
		_spu_memList = (uintptr_t)top;
		_spu_AllocLastNum = 0;
		_spu_AllocBlockNum = num;
		((int*)top)[1] = (0x10000000 << _spu_mem_mode_plus) - 0x1010;
	}

	return num;
}

long SpuMalloc(long size)
{
	return 0/*(long)(uintptr_t)malloc(size)*/;
}

long SpuMallocWithStartAddr(unsigned long addr, long size)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuFree(unsigned long addr)
{
	/*free((void*)(uintptr_t)addr)*/;
}

void SpuSetCommonMasterVolume(short mvol_left, short mvol_right)//(F)
{
    g_spuLeftVol = mvol_left & 0x7FFF;
    g_spuRightVol = mvol_right & 0x7FFF;
}

void SpuGetCommonCDMix(long* cd_mix)
{
    UNIMPLEMENTED();
}

short reverbAttr[6][34] =
{
    {
     0x0000,0x0000,0x007d,0x005b,0x6d80,
     0x54b8,(short)0xbed0,0x0000,0x0000,(short)0xba80,
     0x5800,0x5300,0x04d6,0x0333,0x03f0,
     0x0227,0x0374,0x01ef,0x0334,0x01b5,
     0x0000,0x0000,0x0000,0x0000,0x0000,
     0x0000,0x0000,0x0000,0x01b4,0x0136,
     0x00b8,0x005c,(short)0x8000,(short)0x8000
    },
    {
     0x0000,0x0000,0x0033,0x0025,0x70f0,
     0x4fa8,(short)0xbce0,0x4410,(short)0xc0f0,(short)0x9c00,
     0x5280,0x4ec0,0x03e4,0x031b,0x03a4,
     0x02af,0x0372,0x0266,0x031c,0x025d,
     0x025c,0x018e,0x022f,0x0135,0x01d2,
     0x00b7,0x018f,0x00b5,0x00b4,0x0080,
     0x004c,0x0026,(short)0x8000,(short)0x8000
    },
    {
      0x0000,0x0000,0x00b1,0x007f,0x70f0,
      0x4fa8,(short)0xbce0,0x4510,(short)0xbef0,(short)0xb4c0,
      0x5280,0x4ec0,0x0904,0x076b,0x0824,
      0x065f,0x07a2,0x0616,0x076c,0x05ed,
      0x05ec,0x042e,0x050f,0x0305,0x0462,
      0x02b7,0x042f,0x0265,0x0264,0x01b2,
      0x0100,0x0080,(short)0x8000,(short)0x8000
    },
    {
      0x0000,0x0000,0x00e3,0x00a9,0x6f60,
      0x4fa8,(short)0xbce0,0x4510,(short)0xbef0,(short)0xa680,
      0x5680,0x52c0,0x0dfb,0x0b58,0x0d09,
      0x0a3c,0x0bd9,0x0973,0x0b59,0x08da,
      0x08d9,0x05e9,0x07ec,0x04b0,0x06ef,
      0x03d2,0x05ea,0x031d,0x031c,0x0238,
      0x0154,0x00aa,(short)0x8000,(short)0x8000
    },
    {
      0x0000,0x0000,0x01a5,0x0139,0x6000,
      0x5000,0x4c00,(short)0xb800,(short)0xbc00,(short)0xc000,
      0x6000,0x5c00,0x15ba,0x11bb,0x14c2,
      0x10bd,0x11bc,0x0dc1,0x11c0,0x0dc3,
      0x0dc0,0x09c1,0x0bc4,0x07c1,0x0a00,
      0x06cd,0x09c2,0x05c1,0x05c0,0x041a,
      0x0274,0x013a,(short)0x8000,(short)0x8000
    },
    {
      0x0000,0x0000,0x033d,0x0231,0x7e00,
      0x5000,(short)0xb400,(short)0xb000,0x4c00,(short)0xb000,
      0x6000,0x5400,0x1ed6,0x1a31,0x1d14,
      0x183b,0x1bc2,0x16b2,0x1a32,0x15ef,
      0x15ee,0x1055,0x1334,0x0f2d,0x11f6,
      0x0c5d,0x1056,0x0ae1,0x0ae0,0x07a2,
      0x0464,0x0232,(short)0x8000,(short)0x8000
    }
};

int spu_setReverbAttr(short* revAttr)
{
    int result;

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x1))
    {
        reverb.FB_SRC_A = revAttr[2]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x2))
    {
        reverb.FB_SRC_B = revAttr[3]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x4))
    {
        reverb.IIR_ALPHA = revAttr[4]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x8))
    {
        reverb.ACC_COEF_A = revAttr[5]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x10))
    {
        reverb.ACC_COEF_B = revAttr[6]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x20))
    {
        reverb.ACC_COEF_C = revAttr[7];
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x40))
    {
        reverb.ACC_COEF_D = revAttr[8];
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x80))
    {
        reverb.IIR_COEF = revAttr[9];
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x100))
    {
        reverb.FB_ALPHA = revAttr[10]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x200))
    {
        reverb.FB_X = revAttr[11]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x400))
    {
        reverb.IIR_DEST_A0 = revAttr[12]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x800))
    {
        reverb.IIR_DEST_A1 = revAttr[13]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x1000))
    {
        reverb.ACC_SRC_A0 = revAttr[14]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x1000))
    {
        reverb.ACC_SRC_A1 = revAttr[15]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x4000))
    {
        reverb.ACC_SRC_B0 = revAttr[16]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x8000))
    {
        reverb.ACC_SRC_B1 = revAttr[17]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x10000))
    {
        reverb.IIR_SRC_A0 = revAttr[18]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x20000))
    {
        reverb.IIR_SRC_A1 = revAttr[19]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x40000))
    {
        reverb.IIR_DEST_B0 = revAttr[20]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x80000))
    {
        reverb.IIR_DEST_B1 = revAttr[21]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x100000))
    {
        reverb.ACC_SRC_C0 = revAttr[22]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x200000))
    {
        reverb.ACC_SRC_C1 = revAttr[23]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x400000))
    {
        reverb.ACC_SRC_D0 = revAttr[24]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x800000))
    {
        reverb.ACC_SRC_D1 = revAttr[25]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x1000000))
    {
        reverb.IIR_SRC_B1 = revAttr[26]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x2000000))
    {
        reverb.IIR_SRC_B0 = revAttr[27]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x4000000))
    {
        reverb.MIX_DEST_A0 = revAttr[28]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x8000000))
    {
        reverb.MIX_DEST_A1 = revAttr[29]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x10000000))
    {
        reverb.MIX_DEST_B0 = revAttr[30]; 
    }

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x20000000))
    {
        reverb.MIX_DEST_B1 = revAttr[31]; 
    }
   
    result = ((int*)revAttr)[0] & 0x40000000;

    if (!((int*)revAttr)[0] || (((int*)revAttr)[0] & 0x40000000))
    {
        result = revAttr[32];
        reverb.IN_COEF_L = result; 
    }

    if (!((int*)revAttr)[0] || ((int*)revAttr)[0] < 0)
    {
        result = revAttr[33];
        reverb.IN_COEF_R = result; 
    }

    return result;
}

long SpuSetReverbModeType(long mode)
{
    reverb.StartAddr = reverb.CurrAddr = _spu_rev_offsetaddr = _spu_rev_startaddr[mode];
    spu_setReverbAttr(&reverbAttr[mode-1][0]);
    return 0;
}

void SpuSetReverbModeDepth(short depth_left, short depth_right)//(F)
{
    reverb.VolLeft = depth_left;
    reverb.VolRight = depth_right;
}

void SpuGetVoicePitch(int vNum, unsigned short* pitch)
{
    *pitch = channelList[vNum].pitch;
}

void SpuSetVoicePitch(int vNum, unsigned short pitch)
{
    channelList[vNum].pitch = pitch;
}

void SpuSetCommonCDMix(long cd_mix)
{
    UNIMPLEMENTED();
}

SpuTransferCallbackProc SpuSetTransferCallback(SpuTransferCallbackProc func)
{
    SpuTransferCallbackProc prev = __spu_transferCallback;

    if (func != __spu_transferCallback)
    {
        __spu_transferCallback = func;
    }

    return prev;
}

void SpuSetVoiceADSRAttr(int vNum, unsigned short AR, unsigned short DR, unsigned short SR, unsigned short RR, unsigned short SL, long ARmode, long SRmode, long RRmode)
{
    Channel* channel = &channelList[vNum];

    channel->_adsr.attackmodeexp = (ARmode == 5);
    channel->_adsr.attackrate = AR;
    channel->_adsr.decayrate = DR;
    channel->_adsr.sustainlevel = SL;
    channel->_adsr.sustainmodexp = (SRmode == 5);
    channel->_adsr.sustainincrease = (SRmode != 7);
    channel->_adsr.sustainrate = SR;
    channel->_adsr.releasemodeexp = (RRmode == 7);
    channel->_adsr.releaserate = RR;
}

void SpuSetVoiceStartAddr(int vNum, unsigned long startAddr)
{
    SPU_ResetChannel(channelList + vNum, (uint8_t*)spuSoundBuffer + startAddr);
}

void SpuSetVoiceVolume(int vNum, short volL, short volR)
{
    volL &= 0x7FFF;
    volR &= 0x7FFF;

    channelList[vNum].volL = volL;
    channelList[vNum].volR = volR;
}

long SpuClearReverbWorkArea(long mode)
{
    UNIMPLEMENTED();
    return 0;
}

void SpuGetCommonAttr(SpuCommonAttr* attr)
{
    UNIMPLEMENTED();
}

unsigned long SpuRead(unsigned char* addr, unsigned long size)
{
    UNIMPLEMENTED();
    return 0;
}