#ifdef __WINDOWS__
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
#endif

#include <time.h>

// https://stackoverflow.com/questions/3673226/how-to-print-time-in-format-2009-08-10-181754-811
void PrintTime()
{
	time_t timer;
	char buffer[32];
	struct tm* tm_info;

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf(buffer);
}

int GetWeekDay()
{
	time_t timer;
	char buffer[32];
	struct tm* tm_info;

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%w", tm_info);

	return buffer[0] - '0';
}
