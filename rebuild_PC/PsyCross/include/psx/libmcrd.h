#ifndef LIBMCRD_H
#define LIBMCRD_H

#include "kernel.h"

typedef void (*MemCB)( int cmds, int rslt );

#define McFuncExist		(1)
#define McFuncAccept		(2)
#define McFuncReadFile		(3)
#define McFuncWriteFile		(4)
#define McFuncReadData		(5)
#define McFuncWriteData		(6)

#define	McErrNone		(0)
#define	McErrCardNotExist	(1)
#define	McErrCardInvalid	(2)
#define	McErrNewCard		(3)
#define	McErrNotFormat		(4)
#define	McErrFileNotExist	(5)
#define	McErrAlreadyExist	(6)
#define	McErrBlockFull		(7)
#define	McErrExtend		(0x8000)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void MemCardInit(int val );
extern void MemCardEnd( void );
extern void MemCardStart(void);
extern void MemCardStop(void);
extern int MemCardExist(int chan );
extern int MemCardAccept(int chan );
extern int MemCardOpen(int chan, char* file, int flag );
extern void MemCardClose(void);
extern int MemCardReadData( unsigned int* adrs, int ofs, int bytes );
extern int MemCardReadFile(int chan, char* file, unsigned int* adrs, int ofs, int bytes );
extern int MemCardWriteData( unsigned int* adrs, int ofs, int bytes );
extern int MemCardWriteFile(int chan, char* file, unsigned int* adrs, int ofs , int bytes );
extern int MemCardCreateFile(int chan, char* file, int blocks );
extern int MemCardDeleteFile(int chan, char* file );
extern int MemCardFormat(int chan );
extern int MemCardUnformat(int chan);
extern int MemCardSync(int mode, int* cmds, int* rslt );
extern MemCB MemCardCallback( MemCB func );
extern int MemCardGetDirentry(int chan, char* name, struct DIRENTRY* dir, int* files, int ofs, int max );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
