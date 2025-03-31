
#if 0
typedef struct {
	CdlLOC	pos;		/* file location */
	u_int	size;		/* file size */
	char	name[16];	/* file name (body) */
} CdlFILE;
#endif

int fileCount = 0;
int fileFD[8] = {0};
int currFD = 0;
CdlCB fpReadCallback = 0;

CdlCB pcCdReadCallback(CdlCB x)
{
	fpReadCallback = x;
}

int pcCdPosToInt(const CdlLOC *p)
{
	return *(int*)p;
}

int pcCdIntToPos(int val, const CdlLOC *p)
{
	*(int*)p = val;
}

CdlFILE *pcCdSearchFile(CdlFILE *loc, const char *filename)
{
	#ifdef REBUILD_PC
	int v1;
	#else
	// because this API is STRANGE
	register int v1 asm("v1");
	#endif
	
	// Turn "\\BIGFILE.BIG;1" into "BIGFILE.BIG"

#ifdef REBUILD_PC
	// stupid access violation
	char* str2 = malloc(strlen(filename + 1));
	strcpy(str2, filename);
	filename = str2;
#endif

	char* str = filename;
	while(*str != 0)
	{
		if (*str == ';')
			*str = '\0';
		
		str++;
	}
	
	v1 = PCopen(&filename[1], PCDRV_MODE_READ);
	
	// if Error: return 0;
	
	fileFD[fileCount] = v1;
	
	// max of 256 files
	// CTR has 40 files,
	// top 1 byte is fd
	// bottom 3 bytes is sectorIndex
	*(int*)&loc->pos = fileCount << 24;
	
	fileCount++;
	
	return loc;
}

int pcCdControl(u_char com, u_long *buf, u_char * result)
{
	#ifdef REBUILD_PC
	int v1;
	#else
	// because this API is STRANGE
	register int v1 asm("v1");
	#endif
	
	// for now, assume com = CdlSetloc
	{
		currFD = *(int*)buf >> 24;
		int sector = *(int*)buf & 0xffffff;
	
		v1 = PClseek(fileFD[currFD], sector*0x800, PCDRV_SEEK_SET);
	}
	
	// TODO: handle v1 failures
	return 1;
}

int pcCdRead(int sectors, u_long *buf, int mode)
{
	#ifdef REBUILD_PC
	int v1;
	#else
	// because this API is STRANGE
	register int v1 asm("v1");
	#endif
	
	v1 = PCread(fileFD[currFD], buf, sectors*0x800);
	
// Specific to CTR, do NOT do this,
// see LOAD_NextQueuedFile, need to wait
// for curr->ptrDestination to write, cause
// that variable is used in the read callback
#if 0
	if(fpReadCallback != 0)
	{
		// TODO: Error handling of v1
		fpReadCallback(CdlComplete, 0);
	}
#endif
	
	return 1;
}

int pcCdReadSync(int mode, uint8_t *result)
{
	// do nothing, pcCdRead() already finished
	
	// zero sectors remain
	return 0;
}

// PS1
#ifndef REBUILD_PC

// Copied from here:
// https://github.com/Lameguy64/PSn00bSDK/blob/master/libpsn00b/psxapi/_syscalls.s
asm(
"## PCDRV (host file access) API                                   \n"
".section .text.PCinit, \"ax\", @progbits                          \n"
".global PCinit                                                    \n"
".type PCinit, @function                                           \n"
"                                                                  \n"
"PCinit:                                                           \n"
"	break 0, 0x101 # () -> error                                   \n"
"                                                                  \n"
"	jr    $ra                                                      \n"
"	nop                                                            \n"
"                                                                  \n"
".section .text.PCcreat, \"ax\", @progbits                         \n"
".global PCcreat                                                   \n"
".type PCcreat, @function                                          \n"
"                                                                  \n"
"PCcreat:                                                          \n"
"	li    $a2, 0                                                   \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x102 # (path, path, 0) -> error, fd                  \n"
"                                                                  \n"
"	bgez  $v0, .Lcreate_ok # if (error < 0) fd = error             \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lcreate_ok:                                                      \n"
"	jr    $ra # return fd                                          \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PCopen, \"ax\", @progbits                          \n"
".global PCopen                                                    \n"
".type PCopen, @function                                           \n"
"                                                                  \n"
"PCopen:                                                           \n"
"	move  $a2, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x103 # (path, path, mode) -> error, fd               \n"
"                                                                  \n"
"	bgez  $v0, .Lopen_ok # if (error < 0) fd = error               \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lopen_ok:                                                        \n"
"	jr    $ra # return fd                                          \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PCclose, \"ax\", @progbits                         \n"
".global PCclose                                                   \n"
".type PCclose, @function                                          \n"
"                                                                  \n"
"PCclose:                                                          \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x104 # (fd, fd) -> error                             \n"
"                                                                  \n"
"	jr    $ra                                                      \n"
"	nop                                                            \n"
"                                                                  \n"
".section .text.PCread, \"ax\", @progbits                          \n"
".global PCread                                                    \n"
".type PCread, @function                                           \n"
"                                                                  \n"
"PCread:                                                           \n"
"	move  $a3, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x105 # (fd, fd, length, data) -> error, length       \n"
"                                                                  \n"
"	bgez  $v0, .Lread_ok # if (error < 0) length = error           \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lread_ok:                                                        \n"
"	jr    $ra # return length                                      \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PCwrite, \"ax\", @progbits                         \n"
".global PCwrite                                                   \n"
".type PCwrite, @function                                          \n"
"                                                                  \n"
"PCwrite:                                                          \n"
"	move  $a3, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x106 # (fd, fd, length, data) -> error, length       \n"
"                                                                  \n"
"	bgez  $v0, .Lwrite_ok # if (error < 0) length = error          \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lwrite_ok:                                                       \n"
"	jr    $ra # return length                                      \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PClseek, \"ax\", @progbits                         \n"
".global PClseek                                                   \n"
".type PClseek, @function                                          \n"
"                                                                  \n"
"PClseek:                                                          \n"
"	move  $a3, $a2                                                 \n"
"	move  $a2, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x107 # (fd, fd, offset, mode) -> error, offset       \n"
"                                                                  \n"
"	bgez  $v0, .Lseek_ok # if (error < 0) offset = error           \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lseek_ok:                                                        \n"
"	jr    $ra # return offset                                      \n"
"	move  $v0, $v1                                                 \n"
);
#endif