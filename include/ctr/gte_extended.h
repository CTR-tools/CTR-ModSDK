#pragma once

#define _Impl_gte_loadVec_GTE_VECTOR_MAC(v) __asm__ volatile ( \
	"lwc2	$25, 0( %0 );"	\
	"lwc2	$26, 4( %0 );"	\
	"lwc2	$27, 8( %0 );"	\
	:						\
	: "r"( v ) )
#define _Impl_gte_leadingZeroes(out, in) __asm__ volatile ( \
    "mtc2	%1, $30;" \
    "nop;" \
    "nop;" \
    "swc2	$31, 0( %0 );" \
    : \
    : "r"( out ), "r"( in ) \
    : "memory" \
    )
