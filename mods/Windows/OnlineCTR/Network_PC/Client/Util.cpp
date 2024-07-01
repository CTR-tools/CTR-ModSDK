#include <windows.h>

#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <thread>

const char* exitReasons[] =
{
	"exit(1) - no duckstation instances running",
	"exit(2) - multiple duckstation instances running",
	"exit(3) - failed to create an enet client host",
	"exit(4) - no available peers for initiating an ENet connection",
	"exit(5) - recv in recvThread failed",
	"exit(6) - readMemorySegment send socket error",
	"exit(7) - readMemorySegment send partial send",
	"exit(8) - readMemorySegment recv socket error",
	"exit(9) - readMemorySegment recv failed",
	"exit(10) - writeMemorySegment 8 byte send socket error",
	"exit(11) - writeMemorySegment 8 byte send partial send",
	"exit(12) - writeMemorySegment 4 byte send socket error",
	"exit(13) - writeMemorySegment 4 byte send partial send",
	"exit(14) - writeMemorySegment 2 byte send socket error",
	"exit(15) - writeMemorySegment 2 byte send partial send",
	"exit(16) - writeMemorySegment 1 byte send socket error",
	"exit(17) - writeMemorySegment 1 byte send partial send",
	"exit(18) - partialRefresh buffer overflow",
	"exit(19) - bad socket (duckstation was closed probably)"
};

extern char* progName;

void exit_execv(int code)
{
	bool codeHasExitReason = code >= sizeof(exitReasons) / sizeof(exitReasons[0]);
	const char* newArgv[] = { progName, codeHasExitReason ? exitReasons[code - 1] : "unknown", nullptr};
	if (_execv(progName, newArgv) == -1)
	{
		if (codeHasExitReason)
			printf("exit(%d) - unknown exit reason\n", code);
		else
			printf("%s\n", exitReasons[code - 1]);
		exit(code);
	}
}