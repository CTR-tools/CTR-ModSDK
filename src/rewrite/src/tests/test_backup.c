#include <ctr/test_backup.h>
#include <ctr/nd.h>

//this type isn't part of the public API
typedef struct FrameHeader {
	u32 prev;
	u32 size;
} FrameHeader;

force_inline u32 align_up(u32 n, u32 a)
{
	u32 r = n % a;
	return r ? (n + (a - r)) : n;
}

force_inline u8* top_next_free_ptr(void)
{
	u32 head = *BACKUP_STACK_HEAD_PTR;
	if (!head) { return BACKUP_STACK_DATA_BEGIN; }

	FrameHeader* h = (FrameHeader*)((u8*)0 + head);
	u8* after = (u8*)(h + 1) + h->size;
	u32 aligned = align_up((u32)(after - (u8*)0), BACKUP_ALIGN);
	return (u8*)((u8*)0 + aligned);
}

void BACKUP_INIT(void)
{
	*BACKUP_STACK_HEAD_PTR = 0;
}

/* PUSH:
   - If src == NULL: reserves 'size' bytes; returns writable payload pointer.
   - If src != NULL: copies 'size' bytes from src into payload; returns payload pointer.
   Returns NULL on OOM. */
void* BACKUP_PUSH(const void* src, u32 size)
{
	u8* where = top_next_free_ptr();
	u32 need = align_up((u32)sizeof(FrameHeader) + size, BACKUP_ALIGN);

	if (where + need > BACKUP_STACK_DATA_END) { return 0; }

	FrameHeader* h = (FrameHeader*)where;
	h->prev = *BACKUP_STACK_HEAD_PTR;
	h->size = size;

	void* payload = (void*)(h + 1);
	if (src && size) { memcpy(payload, src, (s32)size); }

	*BACKUP_STACK_HEAD_PTR = (u32)(where - (u8*)0);
	return payload;
}

/* PEEK depth n (0 = top). Returns payload pointer or NULL if out-of-range.
   Optionally writes size to *out_size. */
void* BACKUP_PEEK(u32 depth, u32* out_size)
{
	u32 addr = *BACKUP_STACK_HEAD_PTR;
	FrameHeader* h = (FrameHeader*)((u8*)0 + addr);

	while (h && depth--) {
		h = (FrameHeader*)((u8*)0 + h->prev);
	}
	if (!h) { return 0; }

	if (out_size) { *out_size = h->size; }
	return (void*)(h + 1);
}

/* POP top frame. Returns 0 on success, nonzero if empty. */
s32 BACKUP_POP(void)
{
	u32 head = *BACKUP_STACK_HEAD_PTR;
	if (!head) { return -1; }

	FrameHeader* h = (FrameHeader*)((u8*)0 + head);
	*BACKUP_STACK_HEAD_PTR = h->prev;
	return 0;
}

s32 BACKUP_POP_MULTIPLE(u32 count)
{
	for (u32 i = 0; i < count; i++) {
		if (BACKUP_POP() != 0) { return -1; }
	}
}