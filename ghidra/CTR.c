
// called "CTR" for no good reason,
// come back to this later

// CTR_Box_DrawWirePrims
void FUN_80021500(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                 undefined param_5,undefined param_6,undefined param_7,void *param_8,int param_9)

{
  void *p;
  void *pvVar1;

  pvVar1 = *(void **)(param_9 + 0xc);
  p = (void *)0x0;
  if (pvVar1 <= *(void **)(param_9 + 0x10)) {
    *(int *)(param_9 + 0xc) = (int)pvVar1 + 0x10;
    p = pvVar1;
  }
  if (p != (void *)0x0) {
    
	// psyq macro setLineF2(p)
	*(undefined *)((int)p + 3) = 3;
    *(undefined *)((int)p + 7) = 0x40;
	
	// color R,G
    *(undefined *)((int)p + 4) = param_5;
	*(undefined *)((int)p + 5) = param_6;
	
	// two points (x,y)
    *(undefined2 *)((int)p + 8) = param_1;
    *(undefined2 *)((int)p + 10) = param_2;
    *(undefined2 *)((int)p + 0xc) = param_3;
    *(undefined2 *)((int)p + 0xe) = param_4;
	
	// color B
    *(undefined *)((int)p + 6) = param_7;
    
	AddPrim(param_8,p);
  }
  return;
}


// CTR_Box_DrawWireBox
void FUN_80021594(short *param_1,undefined *param_2,void *param_3,int param_4)

{
  void *pvVar1;
  void *p;

  pvVar1 = *(void **)(param_4 + 0xc);
  p = (void *)0x0;
  if (pvVar1 <= *(void **)(param_4 + 0x10)) {
    *(int *)(param_4 + 0xc) = (int)pvVar1 + 0x18;
    p = pvVar1;
  }
  
  if (p != (void *)0x0) 
  {
	// psyq macro setLineF3(p)
	// set Poly_LineF3 len, code, and padding
    *(undefined *)((int)p + 3) = 5;
    *(undefined *)((int)p + 7) = 0x48;
    *(undefined4 *)((int)p + 0x14) = 0x55555555;
	
	// RGB
    *(undefined *)((int)p + 4) = *param_2;
    *(undefined *)((int)p + 5) = param_2[1];
    *(undefined *)((int)p + 6) = param_2[2];
	
	// three sets of (x,y)
    *(short *)((int)p + 8) = *param_1;
    *(short *)((int)p + 10) = param_1[1];
    *(short *)((int)p + 0xc) = *param_1 + param_1[2];
    *(short *)((int)p + 0xe) = param_1[1];
    *(short *)((int)p + 0x10) = *param_1 + param_1[2];
    *(short *)((int)p + 0x12) = param_1[1] + param_1[3];
    
	AddPrim(param_3,p);
    pvVar1 = *(void **)(param_4 + 0xc);
    
	p = (void *)0x0;
    if (pvVar1 <= *(void **)(param_4 + 0x10)) {
      *(int *)(param_4 + 0xc) = (int)pvVar1 + 0x18;
      p = pvVar1;
    }
    
	if (p != (void *)0x0) 
	{
	  // psyq macro setLineF3(p)
	  // set Poly_LineF3 len, code, and padding
      *(undefined *)((int)p + 3) = 5;
      *(undefined *)((int)p + 7) = 0x48;
      *(undefined4 *)((int)p + 0x14) = 0x55555555;
	  
	  // RGB
      *(undefined *)((int)p + 4) = *param_2;
      *(undefined *)((int)p + 5) = param_2[1];
      *(undefined *)((int)p + 6) = param_2[2];
	  
	  // three sets of (x,y)
      *(short *)((int)p + 8) = *param_1;
      *(short *)((int)p + 10) = param_1[1];
      *(short *)((int)p + 0xc) = *param_1;
      *(short *)((int)p + 0xe) = param_1[1] + param_1[3];
      *(short *)((int)p + 0x10) = *param_1 + param_1[2];
      *(short *)((int)p + 0x12) = param_1[1] + param_1[3];
      
	  AddPrim(param_3,p);
    }
  }
  return;
}


// CTR_Box_DrawClearBox
void FUN_8002177c(short *param_1,undefined *param_2,int param_3,void *param_4,int param_5)

{
  void *pvVar1;
  void *p;

  pvVar1 = *(void **)(param_5 + 0xc);
  p = (void *)0x0;
  if (pvVar1 <= *(void **)(param_5 + 0x10)) {
    *(int *)(param_5 + 0xc) = (int)pvVar1 + 0x20;
    p = pvVar1;
  }
  if (p != (void *)0x0) {
    *(undefined *)((int)p + 3) = 7;
    *(undefined *)((int)p + 0xf) = 0x2a;
    *(uint *)((int)p + 4) = param_3 << 5 | 0xe1000a00;
    *(undefined4 *)((int)p + 8) = 0;
    *(undefined *)((int)p + 0xc) = *param_2;
    *(undefined *)((int)p + 0xd) = param_2[1];
    *(undefined *)((int)p + 0xe) = param_2[2];
    *(short *)((int)p + 0x10) = *param_1;
    *(short *)((int)p + 0x12) = param_1[1];
    *(short *)((int)p + 0x14) = *param_1 + param_1[2];
    *(short *)((int)p + 0x16) = param_1[1];
    *(short *)((int)p + 0x18) = *param_1;
    *(short *)((int)p + 0x1a) = param_1[1] + param_1[3];
    *(short *)((int)p + 0x1c) = *param_1 + param_1[2];
    *(short *)((int)p + 0x1e) = param_1[1] + param_1[3];
    AddPrim(param_4,p);
  }
  return;
}


// CTR_Box_DrawSolidBox
void FUN_80021894(uint *param_1,uint *param_2,uint *param_3,int param_4)

{
  uint *puVar1;
  uint *puVar2;

  // primMem.curr
  puVar1 = *(uint **)(param_4 + 0xc);
  puVar2 = (uint *)0x0;
  
  // if curr is less or equal than primMem.endMin100
  if (puVar1 <= *(uint **)(param_4 + 0x10)) 
  {
    // set curr six bytes further, that's as much as the primitive will need
    *(uint **)(param_4 + 0xc) = puVar1 + 6;
	
    // set puVar2 to old curr location
    puVar2 = puVar1;
  }
  
  // if puVar2 was set to old curr location (safety check)
  if (puVar2 != (uint *)0x0) 
  {
	// rgb+code: PolyF4 (0x28)
    puVar2[1] = *param_2 & 0xffffff | 0x28000000;
	
	// xy0
    puVar2[2] = *param_1;
	
	// xy1
    puVar2[3] = (int)(short)*(ushort *)param_1 + (int)(short)*(ushort *)(param_1 + 1) & 0xffffU |
                (int)(short)*(ushort *)((int)param_1 + 2) << 0x10;
    
	// xy2
	puVar2[4] = (uint)*(ushort *)param_1 |
                ((int)(short)*(ushort *)((int)param_1 + 2) +
                (int)(short)*(ushort *)((int)param_1 + 6)) * 0x10000;
    
	// xy3
	puVar2[5] = (int)(short)*(ushort *)param_1 + (int)(short)*(ushort *)(param_1 + 1) & 0xffffU |
                ((int)(short)*(ushort *)((int)param_1 + 2) +
                (int)(short)*(ushort *)((int)param_1 + 6)) * 0x10000;
				
    *puVar2 = *param_3 & 0xffffff | 0x5000000;
    *param_3 = (uint)puVar2 & 0xffffff;
  }
  return;
}


// param1 is lev->ptr_tex_array,
// param2 is 1cec (frame timer)

// Animate moving textures:
// turbo pads, waterfalls, lava, etc
void FUN_80021984(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;

  // first texture links to last
  puVar1 = (undefined4 *)*param_1;
  puVar4 = param_1;

  // loop through all
  while (puVar1 != param_1)
  {
	// how many frames until scrolling texture makes full loop
	// (usually ten frames, 1/3 second)
    iVar2 = (int)*(short *)(puVar4 + 1);

    iVar3 = param_2 + *(short *)((int)puVar4 + 6) >> ((int)*(short *)(puVar4 + 2) & 0x1fU);

	// get frame in current scroll
	iVar5 = iVar3 % iVar2;

	// catch error
	if (iVar2 == 0) {
      trap(0x1c00);
    }

	// catch error
	if ((iVar2 == -1) && (iVar3 == -0x80000000)) {
      trap(0x1800);
    }

	// At this point, iVar5 is anywhere [0 to 10],
	// can it be made [0 to 20] and scroll half speed?

	// frame index
    *(undefined2 *)((int)puVar4 + 10) = (short)iVar5;

	// << 10, >> e, multiply by 4, for byte offset in pointer array

	// get pointer from array, one for each texture frame
	*puVar4 = *(undefined4 *)((int)puVar4 + ((iVar5 << 0x10) >> 0xe) + 0xc);

    puVar4 = puVar4 + (int)*(short *)(puVar4 + 1) + 3;

	// go to next
	puVar1 = (undefined4 *)*puVar4;
  }
  return;
}


// CTR_CycleTex_Model
// animates non-lev textures on a single model
// param_1 = animtex, param_2 = timer
void FUN_80021a20(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;

  //active frame texture ptr - first field of the struct
  puVar1 = (undefined4 *)*param_1;

  //store animtex ptr
  puVar4 = param_1;

  //the list ends with the pointer to the first animtex struct, so we loop until its euqal to the passed ptr 
  while (puVar1 != param_1) {
    //num frames
    iVar2 = (int)*(short *)(puVar4 + 1);

    //timer math
    iVar3 = param_2 + *(short *)((int)puVar4 + 6) >> ((int)*(short *)(puVar4 + 2) & 0x1fU);

    //current frame
    iVar5 = iVar3 % iVar2;

    //exceptions
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (iVar3 == -0x80000000)) {
      trap(0x1800);
    }

    //store current frame to the animtex
    *(undefined2 *)((int)puVar4 + 10) = (short)iVar5;

    //copy framearray[curFrame] ptr to active frame texture
    *(undefined4 *)*puVar4 = *(undefined4 *)((int)puVar4 + ((iVar5 << 0x10) >> 0xe) + 0xc);

    //skip to the next struct (12 + 4 * numFrames) 
    puVar4 = puVar4 + (int)*(short *)(puVar4 + 1) + 3;
    
    //get next struct first field value
    puVar1 = (undefined4 *)*puVar4;
  }
  return;
}



// CTR_CycleTex_AllModels (num models, ptr models, timer)
void FUN_80021ac0(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  ushort *puVar3;
  uint uVar4;

    //proceed if model ptr is not null and num models is not 0
    //check against 0 is important here (and in the end of the loop)
    //if -1 if passed as num models, it will keep looping until the NULL ptr
  if ((param_2 != (int *)0x0) && (param_1 != 0)) {
      
    do {

        //NULL check for model
      iVar1 = *param_2;

      if (iVar1 == 0) {
        return;
      }

        //current pModel -> headers
      uVar2 = *(uint *)(iVar1 + 0x14);
      
        //current pModel->headers + current pModel->numHeaders * sizeof (header)
        //end of headers
      uVar4 = uVar2 + (int)*(short *)(iVar1 + 0x12) * 0x40;

        //if have any headers
      if (uVar2 < uVar4) {
          
          //pHeader->flags
        puVar3 = (ushort *)(uVar2 + 0x16);
        
        //loop though all headers
        do {
          if (
            //animtex is not null (0x16+0x26 = 0x3C)
            (*(int *)(puVar3 + 0x13) != 0) && 
            
            //and anim flag is not set?
            ((*puVar3 & 2) == 0)
          )
		  {
			// CTR_CycleTex_Model
            FUN_80021a20(*(int *)(puVar3 + 0x13),param_3);
          }
          
          //next header ptr
          uVar2 = uVar2 + 0x40;
          
          //next header flags
          puVar3 = puVar3 + 0x20;
          
          //if have any headers
        } while (uVar2 < uVar4);
      }

    //decrement num models
      param_1 = param_1 + -1;
      
      //increment ptr model
      param_2 = param_2 + 1;
      
      //loop until loop models is not 0
    } while (param_1 != 0);
    
  }
  return;
}



// CTR_CycleTex_2p3p4pWumpaHUD
void FUN_80021b94(uint *param_1,uint *param_2,int param_3)

{
  *param_2 = *param_1;
  *param_1 = (uint)(param_2 + param_3 + -1) & 0xffffff;
  return;
}


// CTR_ClearRenderLists_1P2P
// param1 - gGT
// param2 - numPlyrCurrGame
void FUN_80021bbc(int param_1,int param_2)

{
  undefined *puVar1;
  undefined **ppuVar2;
  int iVar3;

  iVar3 = 0;
  if (0 < param_2) 
  {
	// pointers to rendered quadblocks
    ppuVar2 = &PTR_DAT_80081b20;
	
	// for each player, clear render lists,
	// set default destination for rendered quadblocks
    do 
	{
      puVar1 = *ppuVar2;
      *(undefined4 *)(param_1 + 0x180c) = 0;
      *(undefined **)(param_1 + 0x1808) = puVar1;
      puVar1 = *ppuVar2;
      *(undefined4 *)(param_1 + 0x1814) = 0;
      *(undefined **)(param_1 + 0x1810) = puVar1;
      puVar1 = *ppuVar2;
      *(undefined4 *)(param_1 + 0x181c) = 0;
      *(undefined **)(param_1 + 0x1818) = puVar1;
      puVar1 = *ppuVar2;
      iVar3 = iVar3 + 1;
      *(undefined4 *)(param_1 + 0x1824) = 0;
      *(undefined **)(param_1 + 0x1820) = puVar1;
      puVar1 = *ppuVar2;
      ppuVar2 = ppuVar2 + 1;
      *(undefined4 *)(param_1 + 0x182c) = 0;
      *(undefined4 *)(param_1 + 0x1830) = 0;
      *(undefined4 *)(param_1 + 0x1834) = 0;
      *(undefined **)(param_1 + 0x1828) = puVar1;
	  
	  // next player's render lists
      param_1 = param_1 + 0x30;
	  
    } while (iVar3 < param_2);
  }
  return;
}

// CTR_ClearRenderLists_3P4P
// param1 - gGT
// param2 - numPlyrCurrGame
void FUN_80021c2c(int param_1,int param_2)

{
  undefined *puVar1;
  undefined **ppuVar2;
  int iVar3;

  iVar3 = 0;
  if (0 < param_2) 
  {
	// pointers to rendered quadblocks
    ppuVar2 = &PTR_DAT_80081b30;
	
	// for each player, clear render lists,
	// set default destination for rendered quadblocks
    do 
	{
      puVar1 = *ppuVar2;
      *(undefined4 *)(param_1 + 0x180c) = 0;
      *(undefined **)(param_1 + 0x1808) = puVar1;
      puVar1 = *ppuVar2;
      *(undefined4 *)(param_1 + 0x1814) = 0;
      *(undefined **)(param_1 + 0x1810) = puVar1;
      puVar1 = *ppuVar2;
      iVar3 = iVar3 + 1;
      *(undefined4 *)(param_1 + 0x181c) = 0;
      *(undefined **)(param_1 + 0x1818) = puVar1;
      puVar1 = *ppuVar2;
      ppuVar2 = ppuVar2 + 1;
      *(undefined4 *)(param_1 + 0x1824) = 0;
	  
	  // different from prev function, cause 
	  // the RenderLists are in a different order 
	  // in 1P2P and 3P4P
      *(undefined4 *)(param_1 + 0x1828) = 0;
	  
      *(undefined **)(param_1 + 0x1820) = puVar1;
	  
      param_1 = param_1 + 0x30;
    } while (iVar3 < param_2);
  }
  return;
}


// Intentionally left empty by Naughty Dog
// 8 bytes large, pure empty function
void FUN_80021c8c(void)

{
  return;
}


// CTR_ErrorScreen
// param_1 - red
// param_2 - green
// param_3 - blue
void FUN_80021c94(undefined param_1,undefined param_2,undefined param_3)

{
  int iVar1;
  
  // primitive (TILE in libgpu.h)
  
  // prim tag
  undefined4 local_28;
  
  // RGB + code
  undefined local_24;
  undefined local_23;
  undefined local_22;
  undefined local_21;
  
  // x,y,x,y (rectangle)
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;

  // loop counter
  iVar1 = 0;

  // for iVar1 = 0; iVar1 < 2; iVar1++
  do
  {
    DrawSync(0);
    VSync(0);

	// increment loop counter
    iVar1 = iVar1 + 1;

	// DISPLAY_Swap
    FUN_80023ffc();

	// prim code = 0 (cause bitshifted),
	// with bit-flag parameter '2'
    local_21 = 2;
	
	// len = 03, addr = 0xffffff,
	// this is the first, and last, primitive
    local_28 = 0x3ffffff;

	// gGT->frontBuffer->drawEnv params
    local_1c = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x14) + 4);
    local_1a = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x14) + 6);
    local_20 = **(undefined2 **)(PTR_DAT_8008d2ac + 0x14);
    local_1e = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x14) + 2);

    // set color (red, green, blue)
	local_24 = param_1;
    local_23 = param_2;
    local_22 = param_3;

	// ptr to prim, same as passing an OT
    DrawOTag(&local_28);

  } while (iVar1 < 2);

  DrawSync(0);
  VSync(0);

  // DISPLAY_Swap
  FUN_80023ffc();

  return;
}

void FUN_80021da0(char *param_1,char *param_2)
{
  char cVar1;
  int iVar2;

  jmp 80021e04;

  do {
    while( true ) {
      if (*param_2 == '\0') {
        return;
      }
      iVar2 = (int)*param_2;
      if (iVar2 < 0) break;
      for (; param_2 = param_2 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
        *param_1 = *param_2;
        param_1 = param_1 + 1;
      }
    }
    iVar2 = 1 - iVar2;
    cVar1 = param_2[1];
    param_2 = param_2 + 2;
  } while (iVar2 == 0);
  do {
    *param_1 = cVar1;
    iVar2 = iVar2 + -1;
    param_1 = param_1 + 1;
  } while (iVar2 != 0);

  jmp 80021e04;

  return;
}

// not a real function, just a goto
void FUN_80021e04(char *param_1,char *param_2)

{

// basically same function as 80021e90
#if 0
		80021e04 00 00 a2 80     lb         v0,0x0(a1)
        80021e08 00 00 a3 90     lbu        v1,0x0(a1)
        80021e0c e6 ff 40 14     bne        v0,zero,LAB_80021da8 // 80021da0+8, after jmp
        80021e10 00 16 03 00     _sll       v0,v1,0x18
        80021e14 08 00 e0 03     jr         ra
        80021e18 00 00 00 00     _nop
#endif
}

void FUN_80021e1c(byte *param_1,byte *param_2)
{
  byte bVar1;
  int iVar2;

  jmp 80021e90;

  do {
    while( true ) {
      if (*param_2 == 0) {
        return;
      }
      iVar2 = (int)(char)*param_2;
      if (iVar2 < 0) break;
      for (; param_2 = param_2 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
        *param_1 = *param_1 | *param_2;
        param_1 = param_1 + 1;
      }
    }
    iVar2 = 1 - iVar2;
    bVar1 = param_2[1];
    param_2 = param_2 + 2;
  } while (iVar2 == 0);
  do {
    iVar2 = iVar2 + -1;
    *param_1 = *param_1 | bVar1;
    param_1 = param_1 + 1;
  } while (iVar2 != 0);

  jmp 80021e90;

  return;
}

// not a real function, just a goto
void FUN_80021e90(byte *param_1,byte *param_2)

{
        80021e90 00 00 a2 80     lb         v0,0x0(a1)
        80021e94 00 00 a3 90     lbu        v1,0x0(a1)
        80021e98 e2 ff 40 14     bne        v0,zero,LAB_80021e24 // 80021e20+8, after jmp
        80021e9c 00 16 03 00     _sll       v0,v1,0x18
        80021ea0 08 00 e0 03     jr         ra
        80021ea4 00 00 00 00     _nop
}



void FUN_80021ea8(uint *param_1,uint *param_2,int param_3)

{
  uint uVar1;

  param_3 = param_3 >> 2;
  while (param_3 != 0) {
    uVar1 = *param_2;
    param_2 = param_2 + 1;
    param_3 = param_3 + -1;
    *param_1 = *param_1 | uVar1;
    param_1 = param_1 + 1;
  }
  return;
}


// CTR_MatrixToRot
// used for matrices generated without rotation,
// which need rotation, like AngleAxis matrices
// param_1 is return vec4
// param_2 is an instance matrix
void FUN_80021edc(short *param_1,int param_2,uint param_3)

{
  short sVar1;
  int y;
  long x;
  short *psVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  short *psVar11;
  short local_res8;

  // boolInvert
  uVar4 = param_3 >> 2 & 1;
  
  uVar6 = (uint)(byte)(&DAT_8008d004)[param_3 >> 3 & 3];
  uVar7 = (uint)(byte)(&DAT_8008d00c)[uVar6 + uVar4];
  uVar8 = (uint)(byte)(&DAT_8008d00c)[uVar6 - (uVar4 - 1)];
  if ((param_3 >> 1 & 1) == 1) {
    iVar5 = uVar6 * 6 + param_2;
    psVar2 = (short *)(uVar7 * 2 + iVar5);
    y = (int)*psVar2;
    psVar11 = (short *)(uVar8 * 2 + iVar5);
    iVar5 = (int)*psVar11;

	// fast sqrt, bit shifted up 0x18/2, down 0xc
    y = FUN_8003d214(y * y + iVar5 * iVar5,0x18);
    y = y >> 0xc;

	if (y < 0x11) {
      x = ratan2(-(int)*(short *)(uVar8 * 2 + uVar7 * 6 + param_2),
                 (int)*(short *)(uVar7 * 8 + param_2));
      *param_1 = (short)x;
      x = (long)*(short *)(uVar6 * 8 + param_2);
LAB_80022194:
      x = ratan2(y,x);
      param_1[1] = (short)x;
      param_1[2] = 0;
      goto LAB_800221a4;
    }
    x = ratan2((int)*psVar2,(int)*psVar11);
    *param_1 = (short)x;
    x = ratan2(y,(int)*(short *)(uVar6 * 8 + param_2));
    param_1[1] = (short)x;
    sVar1 = *(short *)(uVar6 * 2 + uVar7 * 6 + param_2);
    y = -(int)*(short *)(uVar6 * 2 + uVar8 * 6 + param_2);
  }
  else {
    psVar2 = (short *)(uVar6 * 8 + param_2);
    y = (int)*psVar2;
    iVar10 = uVar6 * 2;
    iVar9 = uVar7 * 6 + param_2;
    psVar11 = (short *)(iVar10 + iVar9);
    iVar5 = (int)*psVar11;

	// fast sqrt, bit shifted up 0x18/2, down 0xc
    y = FUN_8003d214(y * y + iVar5 * iVar5,0x18);
    x = y >> 0xc;

	if (x < 0x11) {
      lVar3 = ratan2(-(int)*(short *)(uVar8 * 2 + iVar9),(int)*(short *)(uVar7 * 8 + param_2));
      *param_1 = (short)lVar3;
      y = -(int)*(short *)(iVar10 + uVar8 * 6 + param_2);
      goto LAB_80022194;
    }
    y = uVar8 * 6 + param_2;
    lVar3 = ratan2((int)*(short *)(uVar7 * 2 + y),(int)*(short *)(uVar8 * 8 + param_2));
    *param_1 = (short)lVar3;
    x = ratan2(-(int)*(short *)(iVar10 + y),x);
    param_1[1] = (short)x;
    sVar1 = *psVar11;
    y = (int)*psVar2;
  }
  x = ratan2((int)sVar1,y);
  param_1[2] = (short)x;
LAB_800221a4:
  
  // boolInvert
  if (uVar4 == 1) {
    *param_1 = -*param_1;
    param_1[2] = -param_1[2];
    param_1[1] = -param_1[1];
  }
  
  // boolRotate
  if ((param_3 & 1) == 1) 
  {
	// swap X and Z
    sVar1 = param_1[0];
    param_1[0] = param_1[2];
    param_1[2] = sVar1;
  }
  
  // store backup of parameter, in result
  local_res8 = (short)param_3;
  param_1[3] = local_res8;
  
  return;
}


// CTR_ScrambleGhostString
void FUN_80022234(undefined *param_1,byte *param_2)

{
  byte bVar1;
  ushort uVar2;
  ushort *puVar3;
  uint uVar4;

  // first byte of input string
  bVar1 = *param_2;

  do {

	// if input string is empty
	if (bVar1 == 0)
	{
	  // output string is empty
      *param_1 = 0;
      return;
    }

    uVar4 = 0;
	
	// if this is a symbol,
	// not a character
    if (bVar1 < 4) 
	{
	  // get the next character
      bVar1 = *param_2;
      param_2 = param_2 + 1;
	  
	  // character << 8
      uVar4 = (uint)bVar1 << 8;
    }
	
	// next character
    bVar1 = *param_2;
    param_2 = param_2 + 1;

	// string scrambler data
    puVar3 = &DAT_80081dfc;
    uVar2 = DAT_80081dfe;

	// loop until the end of scrambler data
    while (uVar2 != 0xffff)
	{
      if (
			// if set of two characters == last two characters
			((uint)uVar2 == (uVar4 | bVar1)) &&
			(
				// get two characters from scramble data
				uVar2 = *puVar3,
				(uVar2 & 0xff00) != 0
			)
		  )
	  {
		// write from scramble data, to output string
        *param_1 = (char)(uVar2 >> 8);
        param_1[1] = (char)uVar2;
        param_1 = param_1 + 2;
		
		// quit loop,
		// continue with string
        break;
      }
      uVar2 = puVar3[3];
      puVar3 = puVar3 + 2;
    }
	
	// next character in string
    bVar1 = *param_2;
	
  } while( true );
}
