#ifndef LIBPRESS_H
#define LIBPRESS_H

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void DecDCTReset(int mode);
extern int DecDCTBufSize(u_int* bs);
extern void DecDCTvlc(u_int* bs, u_int*buf);
extern void DecDCTin(u_int* buf, int mode);
extern void DecDCTout(u_int* buf, int size);
extern int DecDCTinSync( int mode) ;
extern int DecDCToutSync( int mode) ;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

	
#endif
