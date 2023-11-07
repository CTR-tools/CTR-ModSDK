#ifndef LIBSN_H
#define LIBSN_H

#include <stdint.h>
#include <stdio.h>

#if defined(__ANDROID__)
#ifdef __cplusplus
extern "C" {
#endif
#endif


#if defined(_WIN64)
#define PTR_32 __ptr32
#else
#define PTR_32
#endif

extern int PCinit();
extern FILE* PCopen(char* name, int flags, int perms);
extern int PCcreat(char* name, int perms);
extern int PClseek(FILE* fd, int offset, int mode);
extern int PCread(FILE* fd, char* buff, int len);
extern int PCwrite(FILE* fd, char* buff, int len);
extern int PCclose(FILE* fd);

#if defined(__ANDROID__)
#ifdef __cplusplus
}
#endif
#endif

#endif