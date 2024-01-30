#include <common.h>

struct ParticleEmitter Spark_1L[] = {
    [0] =
        {
            .flags = 1,
            .initOffset = 12,
            .InitTypes.FuncInit =
                {
                    .particle_funcPtr = 0x00000000,
                    .particle_colorFlags = 0x58a2,
                    .particle_lifespan = 0x0002,
                    .particle_Type = 0,
                }},
    [1] =
        {
            .flags = 18,
            .initOffset = 0,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 2000,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [2] =
        {
            .flags = 18,
            .initOffset = 2,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [3] =
        {
            .flags = 22,
            .initOffset = 1,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = -200,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [4] =
        {
            .flags = 1,
            .initOffset = 5,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 131072,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [5] =
        {
            .flags = 3,
            .initOffset = 7,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 1,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [6] =
        {
            .flags = 3,
            .initOffset = 8,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -3072,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [7] =
        {
            .flags = 1,
            .initOffset = 9,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -2048,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [8] = {
        .flags = 0,
        .initOffset = 0,
        .InitTypes.AxisInit = {
            .baseValue = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            },
            .rngSeed = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            }}},
};

struct ParticleEmitter Spark_1R[] = {
    [0] =
        {
            .flags = 1,
            .initOffset = 12,
            .InitTypes.FuncInit =
                {
                    .particle_funcPtr = 0x00000000,
                    .particle_colorFlags = 0x58a2,
                    .particle_lifespan = 0x0002,
                    .particle_Type = 0,
                }},
    [1] =
        {
            .flags = 18,
            .initOffset = 0,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [2] =
        {
            .flags = 18,
            .initOffset = 2,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [3] =
        {
            .flags = 22,
            .initOffset = 1,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = -200,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [4] =
        {
            .flags = 1,
            .initOffset = 5,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 131072,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [5] =
        {
            .flags = 3,
            .initOffset = 7,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [6] =
        {
            .flags = 3,
            .initOffset = 8,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -3072,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [7] =
        {
            .flags = 1,
            .initOffset = 9,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -2048,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [8] = {
        .flags = 0,
        .initOffset = 0,
        .InitTypes.AxisInit = {
            .baseValue = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            },
            .rngSeed = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            }}},
};

struct ParticleEmitter Spark_2L[] = {
    [0] =
        {
            .flags = 1,
            .initOffset = 12,
            .InitTypes.FuncInit =
                {
                    .particle_funcPtr = 0x00000000,
                    .particle_colorFlags = 0x58a2,
                    .particle_lifespan = 0x0002,
                    .particle_Type = 0,
                }},
    [1] =
        {
            .flags = 18,
            .initOffset = 0,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 2000,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [2] =
        {
            .flags = 18,
            .initOffset = 2,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [3] =
        {
            .flags = 22,
            .initOffset = 1,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = -200,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [4] =
        {
            .flags = 1,
            .initOffset = 5,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 131072,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [5] =
        {
            .flags = 3,
            .initOffset = 7,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -3072,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [6] =
        {
            .flags = 3,
            .initOffset = 8,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -2048,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [7] =
        {
            .flags = 1,
            .initOffset = 9,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 1,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [8] = {
        .flags = 0,
        .initOffset = 0,
        .InitTypes.AxisInit = {
            .baseValue = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            },
            .rngSeed = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            }}},
};

struct ParticleEmitter Spark_2R[] = {
    [0] =
        {
            .flags = 1,
            .initOffset = 12,
            .InitTypes.FuncInit =
                {
                    .particle_funcPtr = 0x00000000,
                    .particle_colorFlags = 0x58a2,
                    .particle_lifespan = 0x0002,
                    .particle_Type = 0,
                }},
    [1] =
        {
            .flags = 18,
            .initOffset = 0,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [2] =
        {
            .flags = 18,
            .initOffset = 2,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [3] =
        {
            .flags = 22,
            .initOffset = 1,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = -200,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [4] =
        {
            .flags = 1,
            .initOffset = 5,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 131072,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [5] =
        {
            .flags = 3,
            .initOffset = 7,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -3072,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [6] =
        {
            .flags = 3,
            .initOffset = 8,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -2048,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [7] =
        {
            .flags = 1,
            .initOffset = 9,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 1,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [8] = {
        .flags = 0,
        .initOffset = 0,
        .InitTypes.AxisInit = {
            .baseValue = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            },
            .rngSeed = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            }}},
};

struct ParticleEmitter Spark_3L[] = {
    [0] =
        {
            .flags = 1,
            .initOffset = 12,
            .InitTypes.FuncInit =
                {
                    .particle_funcPtr = 0x00000000,
                    .particle_colorFlags = 0x58a2,
                    .particle_lifespan = 0x0002,
                    .particle_Type = 0,
                }},
    [1] =
        {
            .flags = 18,
            .initOffset = 0,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 2000,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [2] =
        {
            .flags = 18,
            .initOffset = 2,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [3] =
        {
            .flags = 22,
            .initOffset = 1,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = -200,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [4] =
        {
            .flags = 1,
            .initOffset = 5,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 131072,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [5] =
        {
            .flags = 3,
            .initOffset = 7,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -2048,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [6] =
        {
            .flags = 3,
            .initOffset = 8,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [7] =
        {
            .flags = 1,
            .initOffset = 9,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -3072,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [8] = {
        .flags = 0,
        .initOffset = 0,
        .InitTypes.AxisInit = {
            .baseValue = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            },
            .rngSeed = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            }}},
};

struct ParticleEmitter Spark_3R[] = {
    [0] =
        {
            .flags = 1,
            .initOffset = 12,
            .InitTypes.FuncInit =
                {
                    .particle_funcPtr = 0x00000000,
                    .particle_colorFlags = 0x58a2,
                    .particle_lifespan = 0x0002,
                    .particle_Type = 0,
                }},
    [1] =
        {
            .flags = 18,
            .initOffset = 0,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [2] =
        {
            .flags = 18,
            .initOffset = 2,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [3] =
        {
            .flags = 22,
            .initOffset = 1,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = -2000,
                            .accel = -200,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 500,
                            .accel = 0,
                        }}},
    [4] =
        {
            .flags = 1,
            .initOffset = 5,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 131072,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [5] =
        {
            .flags = 3,
            .initOffset = 7,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -2048,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [6] =
        {
            .flags = 3,
            .initOffset = 8,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [7] =
        {
            .flags = 1,
            .initOffset = 9,
            .InitTypes.AxisInit =
                {
                    .baseValue =
                        {
                            .startVal = 65280,
                            .velocity = -3072,
                            .accel = 0,
                        },
                    .rngSeed =
                        {
                            .startVal = 0,
                            .velocity = 0,
                            .accel = 0,
                        }}},
    [8] = {
        .flags = 0,
        .initOffset = 0,
        .InitTypes.AxisInit = {
            .baseValue = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            },
            .rngSeed = {
                .startVal = 0,
                .velocity = 0,
                .accel = 0,
            }}},
};

struct ParticleEmitter * SparksL[3] = {&Spark_1L[0],&Spark_2L[0],&Spark_3L[0]};
struct ParticleEmitter * SparksR[3] = {&Spark_1R[0],&Spark_2R[0],&Spark_3R[0]};
