#include <common.h>

int DECOMP_PushBuffer_SetFrustumPlane(short *frustumData, struct FrustumCornerOUT* fc1, short* camPos, struct FrustumCornerOUT* fc2)
{
    int leadingZeroBits;
    int temp;
    u_int normalX = 0;
    int normalY = 0;
    int normalZ = 0;
    int cameraPosX;
    int cameraPosY;
    int cameraPosZ;

#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25;"                         \
    "mfc2   %1, $26;"                         \
    "mfc2   %2, $27;"                         \
    : : "r"(r0), "r"(r1), "r"(r2))

    // cameraPos(x,y,z)
    cameraPosX = (int)camPos[0];
    cameraPosY = (int)camPos[1];
    cameraPosZ = (int)camPos[2];

#define gte_ldR11R12(r0) __asm__ volatile("ctc2 %0, $0" : : "r"(r0))
#define gte_ldR22R23(r0) __asm__ volatile("ctc2 %0, $2" : : "r"(r0))
#define gte_ldR33(r0) __asm__ volatile("ctc2 %0, $4" : : "r"(r0))

    // vector1: corner2 - cameraPos
    gte_ldR11R12(fc2->pos[0] - cameraPosX);
    gte_ldR22R23(fc2->pos[1] - cameraPosY);
    gte_ldR33(fc2->pos[2] - cameraPosZ);

#define gte_ldIR1(r0) __asm__ volatile("mtc2   %0, $9" : : "r"(r0))
#define gte_ldIR2(r0) __asm__ volatile("mtc2   %0, $10" : : "r"(r0))
#define gte_ldIR3(r0) __asm__ volatile("mtc2   %0, $11" : : "r"(r0))

    // vector2: corner1 - cameraPos
    gte_ldIR1(fc1->pos[0] - cameraPosX);
    gte_ldIR2(fc1->pos[1] - cameraPosY);
    gte_ldIR3(fc1->pos[2] - cameraPosZ);

    // OP(sf,lm) - Outer product of 2 vectors
    gte_op0();

    // get normals from GTE registers
    read_mt(normalX, normalY, normalZ);

#define gte_stLZCR() ({                               \
    unsigned int value;                               \
    __asm__ volatile("mfc2   %0, $31" : "=r"(value)); \
    value;                                            \
})

#define gte_ldLZCS(r0) __asm__ volatile("mtc2   %0, $30" : : "r"(r0))

    // absolute
    u_int absNormalX = ((int)normalX < 0) ? -normalX : normalX;
    gte_ldLZCS(absNormalX);
    leadingZeroBits = gte_stLZCR();

    // absolute
    int absNormalY = (normalY < 0) ? -normalY : normalY;
    gte_ldLZCS(absNormalY);
    temp = gte_stLZCR();
    if (temp < leadingZeroBits)
    {
        leadingZeroBits = temp;
    }

    // absolute
    int absNormalZ = (normalZ < 0) ? -normalZ : normalZ;
    gte_ldLZCS(absNormalZ);
    temp = gte_stLZCR();
    if (temp < leadingZeroBits)
    {
        leadingZeroBits = temp;
    }

    // normalized scaled vector
    int vecBitShift;
    if (leadingZeroBits < 0x12)
    {
        vecBitShift = 0x12 - leadingZeroBits;
        normalX = (int)normalX >> (vecBitShift & 0x1f);
        normalY = normalY >> (vecBitShift & 0x1f);
        normalZ = normalZ >> (vecBitShift & 0x1f);
    }

    // length of normal vector
    int length = SquareRoot0_stub(normalX * normalX + normalY * normalY + normalZ * normalZ);

#if 0
    // no div by zero
    if (length == 0) {
      trap(0x1c00);
    }
#endif

    // normalize
    if (length != 0)
    {
        normalX = (normalX << 12) / length;
        normalY = (normalY << 12) / length;
        normalZ = (normalZ << 12) / length;

#if 0
    // overflow checks
    if ((length == -1)
    {
        if (normalX == -0x80000000)
            trap(0x1800);
        if (normalY == -0x80000000)
            trap(0x1800);
        if (normalZ == -0x80000000)
            trap(0x1800);
    }
#endif
    }

    // Calculate plane equation: Ax + By + Cz + D = 0
    // where (A,B,C) is the normal and D is -dot(normal, point)
    int planeD = (int)(normalX * cameraPosX + normalY * cameraPosY + normalZ * cameraPosZ) >> 13;

    // Store the plane equation coefficients
    frustumData[0] = (short)normalX; // A
    frustumData[1] = (short)normalY; // B
    frustumData[2] = (short)normalZ; // C
    frustumData[3] = (short)planeD;  // D

    // Determine plane type based on normal direction
    u_int planeType = normalX >> 31; // Extract sign bit of X

    // Encode plane type based on normal direction
    // Bit 0: X is negative
    // Bit 1: Y is negative
    // Bit 2: Z is negative
    if (normalY < 0)
    {
        planeType |= 2;
    }
    if (normalZ < 0)
    {
        planeType |= 4;
    }
    return planeType;
}