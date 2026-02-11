#pragma once

#include <ctr/macros.h>

#define BACKUP_STACK_BASE_ADDR   ((u32)0x80400000u)
#define BACKUP_STACK_HEAD_PTR    ((volatile u32*)(BACKUP_STACK_BASE_ADDR + 0x0))
#define BACKUP_STACK_DATA_BEGIN  ((u8*)(BACKUP_STACK_BASE_ADDR + 0x8))
#define BACKUP_STACK_DATA_END    ((u8*)(0x80500000u))
#define BACKUP_ALIGN ((u32)4)

void BACKUP_INIT(void);
void* BACKUP_PUSH(const void* src, u32 size);
void* BACKUP_PEEK(u32 depth, u32* out_size);
s32 BACKUP_POP(void); //add variable for "how many times to pop"
s32 BACKUP_POP_MULTIPLE(u32 count);