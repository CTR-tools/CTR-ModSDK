void CTR_Box_DrawClearBox(RECT *r, u_int *rgb, int param_3, u_long *otMem, struct PrimMem *primMem)
{
	void *pvVar1;
	void *p;
	
	pvVar1 = primMem->curr;
	p = 0;
	if (pvVar1 <= primMem->endMin100)
	{
		primMem->curr = (void *)((int)pvVar1 + 0x20);
		p = pvVar1;
	}
	if (p != 0)
	{
		*(undefined *)((int)p + 3) = 7;
		*(undefined *)((int)p + 0xf) = 0x2a;
		*(uint *)((int)p + 4) = param_3 << 5 | 0xe1000a00;
		*(undefined4 *)((int)p + 8) = 0;
		*(undefined *)((int)p + 0xc) = *(undefined *)rgb;
		*(undefined *)((int)p + 0xd) = *(undefined *)((int)rgb + 1);
		*(undefined *)((int)p + 0xe) = *(undefined *)((int)rgb + 2);
		*(short *)((int)p + 0x10) = r->x;
		*(short *)((int)p + 0x12) = r->y;
		*(short *)((int)p + 0x14) = r->x + r->w;
		*(short *)((int)p + 0x16) = r->y;
		*(short *)((int)p + 0x18) = r->x;
		*(short *)((int)p + 0x1a) = r->y + r->h;
		*(short *)((int)p + 0x1c) = r->x + r->w;
		*(short *)((int)p + 0x1e) = r->y + r->h;
		AddPrim(otMem, p);
	}
	return;
}