#include <windows.h>

#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <thread>

const char* exitReasons[] =
{
	"[unused exit reason]",			                        //1
	"[unused exit reason]",			                        //2
	"failed to create an enet client host",					//3 g
	"no available peers for initiating an ENet connection",	//4 g
	"recv in pineRecv failed",							    //5 g
	"pineSend socket error",                    			//6 g
	"pineSend partial send",                    			//7 g
	"[unused exit reason]",			                        //8
	"[unused exit reason]",			                        //9
	"send_readMemorySegment attempt to send 0 bytes",       //10 g
	"send_writeMemorySegment attempt to send 0 bytes",      //11 g
	"attempt to ps1ptr.waitWrite() when not writing",       //12 g
	"attempt to ps1ptr.waitRead() when not reading",        //13 g
	"attempt to ps1ptr.get() when PINE busy",				//14 g
};

extern char* progName;

void exit_execv(int code)
{
	bool codeHasExitReason = code >= sizeof(exitReasons) / sizeof(exitReasons[0]);
	const char* newArgv[] = { progName, codeHasExitReason ? exitReasons[code - 1] : "unknown exit reason", nullptr};
	if (_execv(progName, newArgv) == -1)
	{
		if (codeHasExitReason)
			printf("exit(%d) - unknown exit reason\n", code);
		else
			printf("exit(%d) - %s\n", code, exitReasons[code - 1]);
		exit(code);
	}
}