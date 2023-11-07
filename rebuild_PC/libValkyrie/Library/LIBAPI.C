#include "LIBAPI.H"

#if !defined(__ANDROID__)&& !defined(SN_TARGET_PSP2) & !defined(_XBOX) && !defined(__linux__)
#include <thread>
#endif

#include <stdio.h>
#include "Core/EMULATOR.H"

int sp = 0;

int dword_300[] = { 0x20, 0xD,  0x0,  0x0 };
int dword_308[] = { 0x10, 0x20, 0x40, 0x1 };

long SetRCnt(long spec, unsigned short target, long mode)//(F)
{
	int value = 0x48;

	spec &= 0xFFFF;
	if (spec > 2)
	{
		return 0;
	}

	counters[spec].value = 0x1C00;
	counters[spec].target = target;

	if (spec < 2)
	{
		if ((mode & 0x10))
		{
			value = 0x49;
		}
		else if ((mode & 0x1))//loc_148
		{
			value |= 0x100;
		}
	}
	else
	{
		//loc_158
		if (spec == 2 && !(mode & 1))
		{
			value = 0x248;
		}//loc_174
	}
	//loc_174
	if ((mode & 0x1000))
	{
		value |= 0x10;
	}//loc_180

	counters[spec].value |= value;

	return 1;
}

long GetRCnt(long spec)//(F)
{
	spec &= 0xFFFF;

	if (spec > 2)
	{
		return 0;
	}

	return (long)counters[spec].cycle;
}

long ResetRCnt(long spec)//(F)
{
	spec &= 0xFFFF;

	if (spec > 2)
	{
		return 0;
	}

	counters[spec].cycle = 0;

	return 1;
}

long StartRCnt(long spec)//(F)
{
	spec &= 0xFFFF;
	dword_300[1] |= dword_308[spec];

	if (counters[spec].padding00 != NULL)
	{
		counters[spec].timerIndex = spec;
#if defined(UWP_SDL2) || defined(SDL2)
		counters[spec].startTick = (unsigned int)Emulator_GetTicks();

#if defined(UWP) && 0
		unsigned int interval = counters[spec].target >> 5;
#else
		unsigned int interval = counters[spec].target >> 4;
#endif
#if defined(UWP_SDL2) || defined(SDL2) && !defined(USE_THREADS)
		counters[spec].timerId = SDL_AddTimer((1000 / counters[spec].target) + 1, Emulator_CounterWrapper, &counters[spec].timerIndex);
#else
		counters[spec].timerId = std::thread(Emulator_CounterWrapper, spec);
#endif
#endif
	}

	return spec < 3 ? 1 : 0;
}

long StopRCnt(long spec)//TODO
{
#if defined(UWP_SDL2) || defined(SDL2) && !defined(USE_THREADS)
	SDL_RemoveTimer(counters[spec & 0xFFFF].timerId);
#endif
	return 0;
}

static void infiniteFunctionCall(long(*func)())
{
	while (TRUE)
	{
		func();
	}
}

#undef OpenEvent
long OpenEvent(unsigned long event, long unk01, long unk02, long(*func)())
{
	int spec = event &= 0xFFFF;

	if (spec > 2 || func == NULL)
	{
		return 0;
	}

	counters[spec].padding00 = func;

	return 1;
}

long CloseEvent(long event)
{
	UNIMPLEMENTED();
	return 0;
}

long WaitEvent(long event)
{
	UNIMPLEMENTED();
	return 0;
}

long TestEvent(long event)
{
	UNIMPLEMENTED();
	return 1;
}

long EnableEvent(long event)
{
	UNIMPLEMENTED();
	return 0;
}

long DisableEvent(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

void DeliverEvent(unsigned long unk00, unsigned long unk01)
{
	UNIMPLEMENTED();
}

void UnDeliverEvent(unsigned long unk00, unsigned long unk01)
{
	UNIMPLEMENTED();
}

long OpenTh(long(*func)(), unsigned long unk01, unsigned long unk02)
{
	UNIMPLEMENTED();
	return 0;
}

int CloseTh(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

int ChangeTh(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long open(char* unk00, unsigned long unk01)
{
	UNIMPLEMENTED();
	return 0;
}

long close(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long lseek(long unk00, long unk01, long unk02)
{
	UNIMPLEMENTED();
	return 0;
}

long read(long unk00, void* unk01, long unk02)
{
	UNIMPLEMENTED();
	return 0;
}

long write(long unk00, void* unk01, long unk02)
{
	UNIMPLEMENTED();
	return 0;
}

long ioctl(long unk00, long unk01, long unk02)
{
	UNIMPLEMENTED();
	return 0;
}

struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY* unk01)
{
	UNIMPLEMENTED();
	return 0;
}

struct DIRENTRY* nextfile(struct DIRENTRY* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long erase(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long undelete(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long format(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

#if !defined(SN_TARGET_PSP2)
long rename(char* unk00, char* unk01)
{
	UNIMPLEMENTED();
	return 0;
}
#endif

long cd(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

#if !defined(SN_TARGET_PSP2)
long LoadTest(char*  unk00, struct EXEC* unk01)
{
	UNIMPLEMENTED();
	return 0;
}

long Load(char * unk00, struct EXEC* unk01)
{
	UNIMPLEMENTED();
	return 0;
}


long Exec(struct EXEC * unk00, long unk01, char** unk02)
{
	UNIMPLEMENTED();
	return 0;
}

long LoadExec(char * unk00, unsigned long unk01, unsigned long unk02)
{
	UNIMPLEMENTED();
	return 0;
}
#endif

long InitPAD(char * unk00, long unk01, char* unk02, long unk03)
{
	UNIMPLEMENTED();
	return 0;
}

long StartPAD()
{
	UNIMPLEMENTED();
	return 0;
}

void StopPAD()
{
	UNIMPLEMENTED();
}

void EnablePAD()
{
	UNIMPLEMENTED();
}

void DisablePAD()
{
	UNIMPLEMENTED();
}

void FlushCache()
{
	UNIMPLEMENTED();
}

void ReturnFromException()
{
	UNIMPLEMENTED();
}

int EnterCriticalSection()
{
	UNIMPLEMENTED();
	return 0;
}

void ExitCriticalSection()
{
	UNIMPLEMENTED();
}

void Exception()
{
	UNIMPLEMENTED();
}

void SwEnterCriticalSection()
{
	UNIMPLEMENTED();
}
void SwExitCriticalSection()
{
	UNIMPLEMENTED();
}

unsigned long SetSp(unsigned long newsp)//(F)
{
	unsigned long old_sp = sp;
	sp = newsp;
	return old_sp;
}

unsigned long GetSp()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetGp()
{
	//UNIMPLEMENTED();
	return 0;
}

unsigned long GetCr()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetSr()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetSysSp()
{
	UNIMPLEMENTED();
	return 0;
}

long SetConf(unsigned long unk00, unsigned long unk01, unsigned long unk02)
{
	UNIMPLEMENTED();
	return 0;
}

void GetConf(unsigned long* unk00, unsigned long* unk01, unsigned long* unk02)
{
	UNIMPLEMENTED();
}

long _get_errno(void)
{
	UNIMPLEMENTED();
	return 0;
}

long _get_error(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

void SystemError(char unk00, long unk01)
{
	UNIMPLEMENTED();
}

void SetMem(long unk00)
{
	UNIMPLEMENTED();
}

long Krom2RawAdd(unsigned long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long Krom2RawAdd2(unsigned short unk00)
{
	UNIMPLEMENTED();
	return 0;
}

void _96_init(void)
{
	UNIMPLEMENTED();
}

void _96_remove(void)
{
	UNIMPLEMENTED();
}

void _boot(void)
{
	UNIMPLEMENTED();
}

void ChangeClearPAD(long unk00)
{
	UNIMPLEMENTED();
}

void InitCARD(long val)
{
	UNIMPLEMENTED();
}

long StartCARD()
{
	UNIMPLEMENTED();
	return 0;
}

long StopCARD()
{
	UNIMPLEMENTED();
	return 0;
}

void _bu_init()
{
	UNIMPLEMENTED();
}

long _card_info(long chan)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_clear(long chan)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_load(long chan)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_auto(long val)
{
	UNIMPLEMENTED();
	return 0;
}

void _new_card()
{
	UNIMPLEMENTED();
}

long _card_status(long drv)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_wait(long drv)
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long _card_chan(void)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_write(long chan, long block, unsigned char *buf)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_read(long chan, long block, unsigned char *buf)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_format(long chan)
{
	UNIMPLEMENTED();
	return 0;
}
