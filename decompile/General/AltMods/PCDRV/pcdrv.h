#ifndef PCDRVMACRO_H
#define PCDRVMACRO_H

// for both PS1 and PC
#include <psn00bsdk/include/psxsn.h>

#define CdReadCallback pcCdReadCallback
CdlCB pcCdReadCallback(CdlCB x);

#define CdPosToInt(x) pcCdPosToInt(x)
int pcCdPosToInt(const CdlLOC *p);

#define CdIntToPos pcCdIntToPos
int pcCdIntToPos(int val, const CdlLOC *p);

#define CdSearchFile pcCdSearchFile
CdlFILE *pcCdSearchFile(CdlFILE *loc, const char *filename);

#define CdControl pcCdControl
int pcCdControl(u_char com, u_long *buf, u_char * result);

#define CdRead pcCdRead
int pcCdRead(int sectors, u_long *buf, int mode);

#define CdReadSync pcCdReadSync
int pcCdReadSync(int mode, uint8_t *result);

#endif