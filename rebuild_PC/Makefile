.PHONY: all

CFLAGS+=-std=c99 -DUSE_16BY9=1 -O2 \
    -I./PsyCross/include -I../include \
    `${PKG_CONFIG} --cflags sdl2`

# Clang is rigorous
CFLAGS+=-Wno-int-conversion -Wno-incompatible-function-pointer-types -Wno-implicit-function-declaration -Wno-return-type

LDLIBS+=-lpsycross \
    `${PKG_CONFIG} --libs sdl2` \
    `${PKG_CONFIG} --libs openal` \
    -lstdc++ -lm

# Clang always needs "no-pie", some distros might add PIE to GCC too.
LDFLAGS+=-fno-pie -no-pie -Wl,-Ttext,0x00D00000

CrashTeamRacingPC: CrashTeamRacingPC.o

all: CrashTeamRacingPC
