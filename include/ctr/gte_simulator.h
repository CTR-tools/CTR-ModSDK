#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>

// This structure is an emulation of the GTE register(s) (data & control) and other internal state for the sake
// of fully emulating the GTE for PC.
// 
// see https://psx-spx.consoledev.net/geometrytransformationenginegte/
typedef struct GTE {
	// Registers are R/W unless otherwise specified

	// -=================================================================================================================-
	// GTE Data Register Summary (cop2r0-31)
	// -=================================================================================================================-
	
	//  cop2r0-1   3xS16 VXY0,VZ0              Vector 0 (X,Y,Z)
	union {
		struct {
			struct { s16 lsbs; s16 msbs; } cop2r0;
			s16 cop2r1;
		};
		SVec3 GTE_VECTOR_0;
	};
	//  cop2r2-3   3xS16 VXY1,VZ1              Vector 1 (X,Y,Z)
	union {
		struct {
			struct { s16 lsbs; s16 msbs; } cop2r2;
			s16 cop2r3;
		};
		SVec3 GTE_VECTOR_1;
	};
	//  cop2r4-5   3xS16 VXY2,VZ2              Vector 2 (X,Y,Z)
	union {
		struct {
			struct { s16 lsbs; s16 msbs; } cop2r4;
			s16 cop2r5;
		};
		SVec3 GTE_VECTOR_2;
	};
	//  cop2r6     4xU8  RGBC                  Color/code value
	union {
		struct {
			u8 c;
			u8 b;
			u8 g;
			u8 r;
		} cop2r6;
		u32 ColorC;
	};
    //  cop2r7     1xU16 OTZ                   Average Z value (for Ordering Table)
	union { //Read-only
		u16 cop2r7;
		u16 OTZ;
	};
    //  cop2r8     1xS16 IR0                   16bit Accumulator (Interpolate)
	union {
		s16 cop2r8;
		s16 IR0;
	};
    //  cop2r9-11  3xS16 IR1,IR2,IR3           16bit Accumulator (Vector)
	struct {
		union {
			struct {
				union {
					s16 cop2r9;
					s16 IR1;
				};
				union {
					s16 cop2r10;
					s16 IR2;
				};
				union {
					s16 cop2r11;
					s16 IR3;
				};
			};
			SVec3 GTE_VECTOR_IR;
		};
	};
    //  cop2r12-15 6xS16 SXY0,SXY1,SXY2,SXYP   Screen XY-coordinate FIFO  (3 stages)
	struct {
		struct {
			s16 y;
			s16 x;
		} cop2r12; //older
		struct {
			s16 y;
			s16 x;
		} cop2r13; //old
		struct {
			s16 y;
			s16 x;
		} cop2r14; //new
		struct {
			s16 y;
			s16 x;
		} cop2r15; //mirror of cop2r14 with move-on-write
	};
    //  cop2r16-19 4xU16 SZ0,SZ1,SZ2,SZ3       Screen Z-coordinate FIFO   (4 stages)
	struct {
		struct {
			u16 z;
		} cop2r16; //oldest
		struct {
			u16 z;
		} cop2r17; //older
		struct {
			u16 z;
		} cop2r18; //old
		struct {
			u16 z;
		} cop2r19; //new 
	};
    //  cop2r20-22 12xU8 RGB0,RGB1,RGB2        Color CRGB-code/color FIFO (3 stages)
	struct {
		union {
			struct {
				u8 c;
				u8 b;
				u8 g;
				u8 r;
			} cop2r20;
			u32 Color0;
		};
		union {
			struct {
				u8 c;
				u8 b;
				u8 g;
				u8 r;
			} cop2r21;
			u32 Color1;
		};
		union {
			struct {
				u8 c;
				u8 b;
				u8 g;
				u8 r;
			} cop2r22;
			u32 Color2;
		};
	};
    //  cop2r23    4xU8  (RES1)                Prohibited
	union { //probably unused.
		struct {
			u8 _0;
			u8 _1;
			u8 _2;
			u8 _3;
		} cop2r23;
	};
    //  cop2r24    1xS32 MAC0                  32bit Maths Accumulators (Value)
	union {
		s32 cop2r24;
		s32 MAC0;
	};
    //  cop2r25-27 3xS32 MAC1,MAC2,MAC3        32bit Maths Accumulators (Vector)
	union {
		struct {
			union {
				s32 MAC1;
				s32 cop2r25;
			};
			union {
				s32 MAC2;
				s32 cop2r26;
			};
			union {
				s32 MAC3;
				s32 cop2r27;
			};
		};
		Vec3 GTE_VECTOR_MAC;
	};
    //  cop2r28-29 1xU15 IRGB,ORGB             Convert RGB Color (48bit vs 15bit)
	struct {
		union {
			u16 cop2r28 : 15;
			u16 IRGB : 15;
		};
		union {
			u16 cop2r29 : 15;
			u16 ORGB : 15;
		};
	};
    //  cop2r30-31 2xS32 LZCS,LZCR             Count Leading-Zeroes/Ones (sign bits)
	struct {
		union {
			s32 cop2r30;
			s32 LZCS;
		};
		union { //Read-only
			s32 cop2r31;
			s32 LZCR;
		};
	};

	// -=================================================================================================================-
	// GTE Control Register Summary (cop2r32-63)
	// -=================================================================================================================-
	//  cop2r32-36 9xS16 RT11RT12,..,RT33 Rotation matrix     (3x3)        ;cnt0-4
	union {
		s16 GTE_MATRIX_ROT[3][3];
		struct {
			struct {
				s16 lsbs; //RT11
				s16 msbs; //RT12
			} cop2r32;
			struct {
				s16 lsbs; //RT13
				s16 msbs; //RT21
			} cop2r33;
			struct {
				s16 lsbs; //RT22
				s16 msbs; //RT23
			} cop2r34;
			struct {
				s16 lsbs; //RT31
				s16 msbs; //RT32
			} cop2r35;
			s16 cop2r36; //RT33
		};
	};
    //  cop2r37-39 3x 32 TRX,TRY,TRZ      Translation vector  (X,Y,Z)      ;cnt5-7
	union {
		struct {
			s32 cop2r37;
			s32 cop2r38;
			s32 cop2r39;
		};
		Vec3 GTE_TRANS_TRANSLATION;
	};
    //  cop2r40-44 9xS16 L11L12,..,L33    Light source matrix (3x3)        ;cnt8-12
	union {
		s16 GTE_MATRIX_LIGHT[3][3];
		struct {
			struct {
				s16 lsbs; //L11
				s16 msbs; //L12
			} cop2r40;
			struct {
				s16 lsbs; //L13
				s16 msbs; //L21
			} cop2r41;
			struct {
				s16 lsbs; //L22
				s16 msbs; //L23
			} cop2r42;
			struct {
				s16 lsbs; //L31
				s16 msbs; //L32
			} cop2r43;
			s16 cop2r44; //L33
		};
	};
    //  cop2r45-47 3x 32 RBK,GBK,BBK      Background color    (R,G,B)      ;cnt13-15
	union {
		struct {
			s32 cop2r45; //R
			s32 cop2r46; //G
			s32 cop2r47; //B
		};
		Vec3 GTE_TRANS_BG_COLOR;
	};
    //  cop2r48-52 9xS16 LR1LR2,..,LB3    Light color matrix source (3x3)  ;cnt16-20
	union {
		s16 GTE_MATRIX_COLOR[3][3];
		struct {
			struct {
				s16 lsbs; //LR1
				s16 msbs; //LR2
			} cop2r48;
			struct {
				s16 lsbs; //LR3
				s16 msbs; //LG1
			} cop2r49;
			struct {
				s16 lsbs; //LG2
				s16 msbs; //LG3
			} cop2r50;
			struct {
				s16 lsbs; //LB1
				s16 msbs; //LB2
			} cop2r51;
			s16 cop2r52; //LB3
		};
	};
    //  cop2r53-55 3x 32 RFC,GFC,BFC      Far color           (R,G,B)      ;cnt21-23
	union {
		struct {
			s32 cop2r53; //R
			s32 cop2r54; //G
			s32 cop2r55; //B
		};
		Vec3 GTE_TRANS_FAR_COLOR;
	};
    //  cop2r56-57 2x 32 OFX,OFY          Screen offset       (X,Y)        ;cnt24-25
	union {
		struct {
			s32 cop2r56; //X
			s32 cop2r57; //Y
		};
		Vec2 ScreenOffset;
	};
    //  cop2r58 BuggyU16 H                Projection plane distance.       ;cnt26
	union {
		// BUG: When reading the H register, the hardware does accidently \<sign-expand> the
		// \<unsigned> 16bit value (ie. values +8000h..+FFFFh are returned as FFFF8000h..FFFFFFFFh)
		// (this bug applies only to "mov rd,cop2r58" opcodes; the actual calculations via
		// RTPS/RTPT opcodes are working okay).
		u16 cop2r58;
		s16 cop2r58asSigned;
		u16 ProjectionPlaneDistance;
	};
    //  cop2r59      S16 DQA              Depth queing parameter A (coeff) ;cnt27
	union {
		s16 cop2r59;
		s16 DepthQueingParameterA;
	};
    //  cop2r60       32 DQB              Depth queing parameter B (offset);cnt28
	union {
		s32 cop2r60;
		s32 DepthQueingParameterB;
	};
    //  cop2r61-62 2xS16 ZSF3,ZSF4        Average Z scale factors          ;cnt29-30
	union {
		s16 cop2r61;
		s16 Z3AverageScaleFactor;
	};
	union {
		s16 cop2r62;
		s16 Z4AverageScaleFactor;
	};
    //  cop2r63      U20 FLAG             Returns any calculation errors   ;cnt31
	union {
		u32 cop2r63 : 20;
		u32 CalculationErrors : 20;
	};
} GTE;

extern GTE gte;

//TODO: swap out integer division for GTE division.

/////////////////////////////////////

#define gte_ldsvrtrow0(v_)                                                     \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(v_);                                  \
    gte.cop2r32.lsbs = v_p_[0];                                                \
    gte.cop2r32.msbs = v_p_[1];                                                \
    gte.cop2r33.lsbs = v_p_[2];                                                \
} while (0)

#define gte_ldsvllrow0(v_)                                                     \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(v_);                                  \
    gte.cop2r40.lsbs = v_p_[0];                                                \
    gte.cop2r40.msbs = v_p_[1];                                                \
    gte.cop2r41.lsbs = v_p_[2];                                                \
} while (0)

#define gte_ldsvlcrow0(v_)                                                     \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(v_);                                  \
    gte.cop2r48.lsbs = v_p_[0];                                                \
    gte.cop2r48.msbs = v_p_[1];                                                \
    gte.cop2r49.lsbs = v_p_[2];                                                \
} while (0)

/////////////////////////////////////

#define gte_ldv0(v_)                                                           \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(v_);                                  \
    gte.GTE_VECTOR_0.x = v_p_[0];                                              \
    gte.GTE_VECTOR_0.y = v_p_[1];                                              \
    gte.GTE_VECTOR_0.z = v_p_[2];                                              \
} while (0)

#define gte_ldv1(v_)                                                           \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(v_);                                  \
    gte.GTE_VECTOR_1.x = v_p_[0];                                              \
    gte.GTE_VECTOR_1.y = v_p_[1];                                              \
    gte.GTE_VECTOR_1.z = v_p_[2];                                              \
} while (0)

#define gte_ldv2(v_)                                                           \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(v_);                                  \
    gte.GTE_VECTOR_2.x = v_p_[0];                                              \
    gte.GTE_VECTOR_2.y = v_p_[1];                                              \
    gte.GTE_VECTOR_2.z = v_p_[2];                                              \
} while (0)

#define gte_ldsv(v_)                                                           \
do {                                                                           \
    const s16* const v_p_ = (const s16*)(v_);                                  \
    gte.GTE_VECTOR_IR.x = v_p_[0];                                             \
    gte.GTE_VECTOR_IR.y = v_p_[1];                                             \
    gte.GTE_VECTOR_IR.z = v_p_[2];                                             \
} while (0)

/////////////////////////////////////

#define gte_ldlvl(v_)                                                          \
do {                                                                           \
    const s16 *const v_p_ = (const s16*)(const void*)(v_);                     \
    gte.GTE_VECTOR_IR.x = v_p_[0];                                             \
    gte.GTE_VECTOR_IR.y = v_p_[2];                                             \
    gte.GTE_VECTOR_IR.z = v_p_[4];                                             \
} while (0)

/////////////////////////////////////

#define _Impl_gte_loadVec_GTE_VECTOR_MAC(v_)                                   \
do {                                                                           \
	const s32 *const v_p_ = (const s32*)(const void*)&(v_);                    \
    gte.MAC1 = v_p_[0];                                                        \
    gte.MAC2 = v_p_[1];                                                        \
    gte.MAC3 = v_p_[2];                                                        \
} while (0)

/////////////////////////////////////

#define gte_stopz(out_)                                                        \
do {                                                                           \
    s32* const out_p_ = (s32*)(out_);                                          \
    *out_p_ = gte.MAC0;                                                        \
} while (0)

#define gte_stlvnl0(out_)                                                      \
do {                                                                           \
    s32* const out_p_ = (s32*)(out_);                                          \
    *out_p_ = gte.MAC1;                                                        \
} while (0)

#define gte_stlvnl1(out_)                                                      \
do {                                                                           \
    s32* const out_p_ = (s32*)(out_);                                          \
    *out_p_ = gte.MAC2;                                                        \
} while (0)

#define gte_stlvnl2(out_)                                                      \
do {                                                                           \
    s32* const out_p_ = (s32*)(out_);                                          \
    *out_p_ = gte.MAC3;                                                        \
} while (0)

#define gte_stlvnl(out_)                                                       \
do {                                                                           \
    s32* const out_p_ = (s32*)&(out_);                                         \
    out_p_[0] = gte.MAC1;                                                      \
    out_p_[1] = gte.MAC2;                                                      \
    out_p_[2] = gte.MAC3;                                                      \
} while (0)

/////////////////////////////////////

#define gte_lddp(in_)                       \
do {                                        \
    const s32 in_v_ = (in_);                \
    gte.IR0 = (s16)in_v_;                   \
} while (0)

force_inline void _gte_mvmva(
	u8 doShift,
	const s16(*matrix)[3],        /* s16[3][3] */
	const SVec3* vector,           /* SVec3* (x,y,z are s16) */
	const Vec3* translationVector, /* Vec3*  (x,y,z are s32) */
	u8 doClamp)
{
	const u8  sf = doShift ? 1u : 0u;
	const u8  lm = doClamp ? 1u : 0u;

	const s16 vx = vector->x, vy = vector->y, vz = vector->z;
	const s32 cvx = translationVector->x;
	const s32 cvy = translationVector->y;
	const s32 cvz = translationVector->z;

	const u8 shift = sf ? 12u : 0u;

	/* row 0 */
	{
		s64 acc = (s64)cvx * 0x1000
			+ (s64)matrix[0][0] * vx
			+ (s64)matrix[0][1] * vy
			+ (s64)matrix[0][2] * vz;
		acc >>= shift;                     /* arithmetic on PS1/x86 */
		gte.MAC1 = (s32)acc;

		s32 t = (s32)acc;                  /* IR clamp per 'lm' */
		if (lm) { if (t < 0) t = 0; else if (t > 0x7FFF) t = 0x7FFF; }
		else { if (t < -0x8000) t = -0x8000; else if (t > 0x7FFF) t = 0x7FFF; }
		gte.IR1 = (s16)t;
	}

	/* row 1 */
	{
		s64 acc = (s64)cvy * 0x1000
			+ (s64)matrix[1][0] * vx
			+ (s64)matrix[1][1] * vy
			+ (s64)matrix[1][2] * vz;
		acc >>= shift;
		gte.MAC2 = (s32)acc;

		s32 t = (s32)acc;
		if (lm) { if (t < 0) t = 0; else if (t > 0x7FFF) t = 0x7FFF; }
		else { if (t < -0x8000) t = -0x8000; else if (t > 0x7FFF) t = 0x7FFF; }
		gte.IR2 = (s16)t;
	}

	/* row 2 */
	{
		s64 acc = (s64)cvz * 0x1000
			+ (s64)matrix[2][0] * vx
			+ (s64)matrix[2][1] * vy
			+ (s64)matrix[2][2] * vz;
		acc >>= shift;
		gte.MAC3 = (s32)acc;

		s32 t = (s32)acc;
		if (lm) { if (t < 0) t = 0; else if (t > 0x7FFF) t = 0x7FFF; }
		else { if (t < -0x8000) t = -0x8000; else if (t > 0x7FFF) t = 0x7FFF; }
		gte.IR3 = (s16)t;
	}
}

#define gte_mvmva(sf_, mx_, v_, cv_, lm_)                                        \
do {                                                                             \
    const u8 sf_v_ = (u8)(sf_);                                                  \
    const u8 lm_v_ = (u8)(lm_);                                                  \
                                                                                  \
    /* matrix pointer */                                                         \
    const s16 (*mx_p_)[3];                                                       \
    static const s16 _gte_zero_mx_[3][3] = {{0,0,0},{0,0,0},{0,0,0}};            \
    switch ((int)(mx_)) {                                                        \
        case GTE_MATRIX_ROT:   mx_p_ = gte.GTE_MATRIX_ROT;   break;              \
        case GTE_MATRIX_LIGHT: mx_p_ = gte.GTE_MATRIX_LIGHT; break;              \
        case GTE_MATRIX_COLOR: mx_p_ = gte.GTE_MATRIX_COLOR; break;              \
        default:               mx_p_ = _gte_zero_mx_;          break;            \
    }                                                                             \
                                                                                  \
    /* vector (SVec3) */                                                         \
    const SVec3* v_p_;                                                           \
    static const SVec3 _gte_zero_svec_ = {0,0,0};                                \
    switch ((int)(v_)) {                                                         \
        case GTE_VECTOR_0:  v_p_ = &gte.GTE_VECTOR_0;  break;                    \
        case GTE_VECTOR_1:  v_p_ = &gte.GTE_VECTOR_1;  break;                    \
        case GTE_VECTOR_2:  v_p_ = &gte.GTE_VECTOR_2;  break;                    \
        case GTE_VECTOR_IR: v_p_ = &gte.GTE_VECTOR_IR; break;                    \
        default:            v_p_ = &_gte_zero_svec_;    break;                   \
    }                                                                             \
                                                                                  \
    /* translation (Vec3) */                                                     \
    const Vec3* cv_p_;                                                           \
    static const Vec3 _gte_zero_vec_ = {0,0,0};                                  \
    switch ((int)(cv_)) {                                                        \
        case GTE_TRANS_TRANSLATION: cv_p_ = &gte.GTE_TRANS_TRANSLATION; break;   \
        case GTE_TRANS_BG_COLOR:   cv_p_ = &gte.GTE_TRANS_BG_COLOR;   break;     \
        case GTE_TRANS_FAR_COLOR:  cv_p_ = &gte.GTE_TRANS_FAR_COLOR;  break;     \
        default:                   cv_p_ = &_gte_zero_vec_;          break;      \
    }                                                                             \
                                                                                  \
    _gte_mvmva(sf_v_, mx_p_, v_p_, cv_p_, lm_v_);                                \
} while (0)

//Mx = matrix specified by mx  ;RT/LLM/LCM - Rotation, light or color matrix
//Vx = vector specified by v; V0, V1, V2, or [IR1, IR2, IR3]
//Tx = translation vector specified by cv; TR or BK or Bugged / FC, or None

//MAC1 = (Tx1*1000h + Mx11*Vx1 + Mx12*Vx2 + Mx13*Vx3) SAR (sf*12)
//MAC2 = (Tx2 * 1000h + Mx21 * Vx1 + Mx22 * Vx2 + Mx23 * Vx3) SAR(sf * 12)
//MAC3 = (Tx3 * 1000h + Mx31 * Vx1 + Mx32 * Vx2 + Mx33 * Vx3) SAR(sf * 12)
//[IR1, IR2, IR3] = [MAC1, MAC2, MAC3]
//2nd param is of enum type GTE_MATRIX
//3rd param is of enum type GTE_VECTOR
//#define gte_mvmva(sf_, mx_, v_, cv_, lm_)                                          \
//do {                                                                               \
//    const u8 sf_v_ = (u8)(sf_);                                                    \
//    const u8 lm_v_ = (u8)(lm_);                                                    \
//                                                                                   \
//    /* row 0 */                                                                    \
//    s64 mac1_v_ =  (s64)gte.cv_.x * 0x1000                                         \
//                 + (s64)gte.mx_[0][0] * (s64)gte.v_.x                              \
//                 + (s64)gte.mx_[0][1] * (s64)gte.v_.y                              \
//                 + (s64)gte.mx_[0][2] * (s64)gte.v_.z;                             \
//    mac1_v_ >>= (sf_v_ * 12);                                                      \
//    gte.MAC1 = (s32)mac1_v_;                                                       \
//    { s32 t_v_ = (s32)mac1_v_;                                                     \
//      if (lm_v_) {                                                                 \
//          if (t_v_ < 0) t_v_ = 0;                                                  \
//          else if (t_v_ > 0x7FFF) t_v_ = 0x7FFF;                                   \
//      } else {                                                                     \
//          if (t_v_ < -0x8000) t_v_ = -0x8000;                                      \
//          else if (t_v_ > 0x7FFF) t_v_ = 0x7FFF;                                   \
//      }                                                                            \
//      gte.IR1 = (s16)t_v_; }                                                       \
//                                                                                   \
//    /* row 1 */                                                                    \
//    s64 mac2_v_ =  (s64)gte.cv_.y * 0x1000                                         \
//                 + (s64)gte.mx_[1][0] * (s64)gte.v_.x                              \
//                 + (s64)gte.mx_[1][1] * (s64)gte.v_.y                              \
//                 + (s64)gte.mx_[1][2] * (s64)gte.v_.z;                             \
//    mac2_v_ >>= (sf_v_ * 12);                                                      \
//    gte.MAC2 = (s32)mac2_v_;                                                       \
//    { s32 t_v_ = (s32)mac2_v_;                                                     \
//      if (lm_v_) {                                                                 \
//          if (t_v_ < 0) t_v_ = 0;                                                  \
//          else if (t_v_ > 0x7FFF) t_v_ = 0x7FFF;                                   \
//      } else {                                                                     \
//          if (t_v_ < -0x8000) t_v_ = -0x8000;                                      \
//          else if (t_v_ > 0x7FFF) t_v_ = 0x7FFF;                                   \
//      }                                                                            \
//      gte.IR2 = (s16)t_v_; }                                                       \
//                                                                                   \
//    /* row 2 */                                                                    \
//    s64 mac3_v_ =  (s64)gte.cv_.z * 0x1000                                         \
//                 + (s64)gte.mx_[2][0] * (s64)gte.v_.x                              \
//                 + (s64)gte.mx_[2][1] * (s64)gte.v_.y                              \
//                 + (s64)gte.mx_[2][2] * (s64)gte.v_.z;                             \
//    mac3_v_ >>= (sf_v_ * 12);                                                      \
//    gte.MAC3 = (s32)mac3_v_;                                                       \
//    { s32 t_v_ = (s32)mac3_v_;                                                     \
//      if (lm_v_) {                                                                 \
//          if (t_v_ < 0) t_v_ = 0;                                                  \
//          else if (t_v_ > 0x7FFF) t_v_ = 0x7FFF;                                   \
//      } else {                                                                     \
//          if (t_v_ < -0x8000) t_v_ = -0x8000;                                      \
//          else if (t_v_ > 0x7FFF) t_v_ = 0x7FFF;                                   \
//      }                                                                            \
//      gte.IR3 = (s16)t_v_; }                                                       \
//} while (0)

#define gte_gpl0()                                                                \
do {                                                                              \
    /* MACi = MACi + IRi * IR0 (widen to s64 for exact math) */                   \
    s64 mac1_v_ = (s64)gte.MAC1 + (s64)gte.IR1 * (s64)gte.IR0;                    \
    s64 mac2_v_ = (s64)gte.MAC2 + (s64)gte.IR2 * (s64)gte.IR0;                    \
    s64 mac3_v_ = (s64)gte.MAC3 + (s64)gte.IR3 * (s64)gte.IR0;                    \
    gte.MAC1 = (s32)mac1_v_;                                                      \
    gte.MAC2 = (s32)mac2_v_;                                                      \
    gte.MAC3 = (s32)mac3_v_;                                                      \
                                                                                   \
    /* Color FIFO: arithmetic >> 4, then clamp to [0..255] */                     \
    s32 _c0 = gte.MAC1 >> 4;                                                      \
    s32 _c1 = gte.MAC2 >> 4;                                                      \
    s32 _c2 = gte.MAC3 >> 4;                                                      \
    if (_c0 < 0) _c0 = 0; else if (_c0 > 255) _c0 = 255;                           \
    if (_c1 < 0) _c1 = 0; else if (_c1 > 255) _c1 = 255;                           \
    if (_c2 < 0) _c2 = 0; else if (_c2 > 255) _c2 = 255;                           \
    gte.Color0 = (u8)_c0;                                                         \
    gte.Color1 = (u8)_c1;                                                         \
    gte.Color2 = (u8)_c2;                                                         \
                                                                                   \
    /* IR = MAC with signed saturation (no lm parameter for GPL0) */              \
    s32 _t1 = gte.MAC1;                                                           \
    s32 _t2 = gte.MAC2;                                                           \
    s32 _t3 = gte.MAC3;                                                           \
    if (_t1 < -0x8000) _t1 = -0x8000; else if (_t1 > 0x7FFF) _t1 = 0x7FFF;        \
    if (_t2 < -0x8000) _t2 = -0x8000; else if (_t2 > 0x7FFF) _t2 = 0x7FFF;        \
    if (_t3 < -0x8000) _t3 = -0x8000; else if (_t3 > 0x7FFF) _t3 = 0x7FFF;        \
    gte.IR1 = (s16)_t1;                                                           \
    gte.IR2 = (s16)_t2;                                                           \
    gte.IR3 = (s16)_t3;                                                           \
} while (0)

//[MAC1,MAC2,MAC3] = [MAC1,MAC2,MAC3] SHL (sf*12)       ;<--- for GPL only
//[MAC1, MAC2, MAC3] = (([IR1, IR2, IR3] * IR0) + [MAC1, MAC2, MAC3]) SAR(sf * 12)
//Color FIFO = [MAC1 / 16, MAC2 / 16, MAC3 / 16, CODE], [IR1, IR2, IR3] = [MAC1, MAC2, MAC3]
#define gte_gpl12()                                                               \
do {                                                                              \
    /* (MAC * 4096) + (IR * IR0), then >> 12  — wide math, no signed << UB */     \
    s64 _m1 = (s64)gte.MAC1 * 4096 + (s64)gte.IR1 * (s64)gte.IR0;                 \
    s64 _m2 = (s64)gte.MAC2 * 4096 + (s64)gte.IR2 * (s64)gte.IR0;                 \
    s64 _m3 = (s64)gte.MAC3 * 4096 + (s64)gte.IR3 * (s64)gte.IR0;                 \
                                                                                  \
    _m1 >>= 12;                                                                   \
    _m2 >>= 12;                                                                   \
    _m3 >>= 12;                                                                   \
                                                                                  \
    gte.MAC1 = (s32)_m1;                                                          \
    gte.MAC2 = (s32)_m2;                                                          \
    gte.MAC3 = (s32)_m3;                                                          \
                                                                                  \
    /* Color outputs: arithmetic >>4 then clamp to [0..255] */                    \
    s32 _c0 = gte.MAC1 >> 4;                                                      \
    s32 _c1 = gte.MAC2 >> 4;                                                      \
    s32 _c2 = gte.MAC3 >> 4;                                                      \
    if (_c0 < 0) _c0 = 0; else if (_c0 > 255) _c0 = 255;                          \
    if (_c1 < 0) _c1 = 0; else if (_c1 > 255) _c1 = 255;                          \
    if (_c2 < 0) _c2 = 0; else if (_c2 > 255) _c2 = 255;                          \
    gte.Color0 = (u8)_c0;                                                         \
    gte.Color1 = (u8)_c1;                                                         \
    gte.Color2 = (u8)_c2;                                                         \
                                                                                  \
    /* [IR] = [MAC] with signed saturation (GPL has no lm parameter) */           \
    s32 _t1 = gte.MAC1, _t2 = gte.MAC2, _t3 = gte.MAC3;                           \
    if (_t1 < -0x8000) _t1 = -0x8000; else if (_t1 > 0x7FFF) _t1 = 0x7FFF;        \
    if (_t2 < -0x8000) _t2 = -0x8000; else if (_t2 > 0x7FFF) _t2 = 0x7FFF;        \
    if (_t3 < -0x8000) _t3 = -0x8000; else if (_t3 > 0x7FFF) _t3 = 0x7FFF;        \
    gte.IR1 = (s16)_t1;                                                           \
    gte.IR2 = (s16)_t2;                                                           \
    gte.IR3 = (s16)_t3;                                                           \
} while (0)

#define _Impl_gte_leadingZeroes(out_, in_)                                       \
do {                                                                             \
    const s32 in_v_  = (in_);                                                    \
    gte.LZCS = in_v_;                                                            \
                                                                                 \
    const u32 v_v_    = (u32)in_v_;                                              \
    const u32 sign_v_ = v_v_ >> 31;   /* 0 for >=0, 1 for <0 */                  \
                                                                                 \
    s32 i_v_ = 0;                                                                \
    while (i_v_ < 32 && (((v_v_ >> (31 - (u32)i_v_)) & 1u) == sign_v_)) {        \
        ++i_v_;                                                                  \
    }                                                                            \
    gte.LZCR = i_v_;                                                             \
    *(s32*)(void*)(out_) = gte.LZCR;                                             \
} while (0)

#define gte_SetRotMatrix(m)                                                     \
do {                                                                            \
    const s16 (*mat)[3] = (const s16 (*)[3])(const void*)(m);                   \
    gte.GTE_MATRIX_ROT[0][0] = mat[0][0];                                       \
    gte.GTE_MATRIX_ROT[0][1] = mat[0][1];                                       \
    gte.GTE_MATRIX_ROT[0][2] = mat[0][2];                                       \
    gte.GTE_MATRIX_ROT[1][0] = mat[1][0];                                       \
    gte.GTE_MATRIX_ROT[1][1] = mat[1][1];                                       \
    gte.GTE_MATRIX_ROT[1][2] = mat[1][2];                                       \
    gte.GTE_MATRIX_ROT[2][0] = mat[2][0];                                       \
    gte.GTE_MATRIX_ROT[2][1] = mat[2][1];                                       \
    gte.GTE_MATRIX_ROT[2][2] = mat[2][2];                                       \
} while (0)
