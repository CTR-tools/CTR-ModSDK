                             //
                             // OVR_229 
                             // OVR_229::800a0cb8-OVR_229::800a930b
                             //
     
	 // Overlay Tag
	 9::800a0cb8 0e              ??         0Eh
     9::800a0cb9 00              ??         00h
     9::800a0cba 00              ??         00h
     9::800a0cbb 00              ??         00h
	 
// FUN_800a0cbc, called by exe as entry to this monsterous algorithm, for rendering LEV.
// param1 (a0) - offset 0x1808 of gameTracker, one struct per player
// param2 (a1) - pushBuffer
// param3 (a2) - LEV->ptr_mesh_info, pointer is stored at first four bytes of LEV
// param4 (a3) - primMem
// param5 (sp+0x10) - Vismem 0x10-0x1F
// param6 (sp+0x14) - Vismem 0x10-0x1F
// param7 (sp+0x18) - Vismem 0x10-0x1F
// param8 (sp+0x1c) - Vismem 0x10-0x1F
// param9 (sp+0x20) - lev->0x44
	 
	 // allocate stack memory
     9::800a0cbc c4 ff bd 27     addiu      sp,sp,-0x3c
	 
	 // backup registers on stack, including $gp which is edited in the algorithm
     9::800a0cc0 10 00 b0 af     sw         s0,0x10(sp)
     9::800a0cc4 14 00 b1 af     sw         s1,0x14(sp)
     9::800a0cc8 18 00 b2 af     sw         s2,0x18(sp)
     9::800a0ccc 1c 00 b3 af     sw         s3,0x1c(sp)
     9::800a0cd0 20 00 b4 af     sw         s4,0x20(sp)
     9::800a0cd4 24 00 b5 af     sw         s5,0x24(sp)
     9::800a0cd8 28 00 b6 af     sw         s6,0x28(sp)
     9::800a0cdc 2c 00 b7 af     sw         s7,0x2c(sp)
     9::800a0ce0 30 00 bc af     sw         gp,0x30(sp)
	 9::800a0ce4 34 00 be af     sw         s8,0x34(sp)
     9::800a0ce8 38 00 bf af     sw         ra,0x38(sp)
     
	 // $at = 1f800000
	 9::800a0cec 80 1f 01 3c     lui        at,0x1f80
	 
	 // 0x1f800038 = $sp (backup)
     9::800a0cf0 38 00 3d ac     sw         sp,offset DAT_1f800038(at)      

	 // remember $sp was subtracted by 0x3C,
	 // so this was originally offsets 0x10 and 0x14
	 
	 // param_5, P1 VisMem 0x10-0x1F (visFaceList)
	 // param_6, P2 VisMem 0x10-0x1F (visFaceList)
	 // param_7, P3 VisMem 0x10-0x1F (visFaceList)
	 // param_8, P4 VisMem 0x10-0x1F (visFaceList)
     9::800a0cf4 4c 00 a3 8f     lw         v1,0x4c(sp)
     9::800a0cf8 50 00 a8 8f     lw         t0,0x50(sp)
     9::800a0cfc 54 00 a9 8f     lw         t1,0x54(sp)
     9::800a0d00 58 00 aa 8f     lw         t2,0x58(sp)
	 
	 // if any of the four visFaceLists are invalid, jump to 800a102c,
	 // where the function rsetores the backed-up registers, and returns to the EXE
	 // ------------------------------
	 // 1f8000cc = P1 visFaceList
	 // 1f8000d0 = P2 visFaceList
	 // 1f8000d4 = P3 visFaceList
	 // 1f8000d8 = P4 visFaceList
     9::800a0d04 c9 00 60 10     beq        v1,zero,LAB_OVR_229__800a102c
     9::800a0d08 cc 00 23 ac     _sw        v1,offset DAT_1f8000cc(at)                       = ??
     9::800a0d0c c7 00 00 11     beq        t0,zero,LAB_OVR_229__800a102c
     9::800a0d10 d0 00 28 ac     _sw        t0,offset DAT_1f8000d0(at)                       = ??
     9::800a0d14 c5 00 20 11     beq        t1,zero,LAB_OVR_229__800a102c
     9::800a0d18 d4 00 29 ac     _sw        t1,offset DAT_1f8000d4(at)                       = ??
     9::800a0d1c c3 00 40 11     beq        t2,zero,LAB_OVR_229__800a102c
     9::800a0d20 d8 00 2a ac     _sw        t2,offset DAT_1f8000d8(at)                       = ??
	 
	 // param_9, lev->0x44 (restart_main?)
     9::800a0d24 5c 00 aa 8f     lw         t2,0x5c(sp)
	 
	 // primMem->curr
     9::800a0d28 0c 00 e2 8c     lw         v0,0xc(a3)
	 
	 // 1f800088 = param_6 lev->0x44 (restart_main)
     9::800a0d2c 88 00 2a ac     sw         t2,offset DAT_1f800088(at)                       = ??
     
	 // v1 = mesh_info -> ptrQuadBlockArray
	 9::800a0d30 0c 00 c3 8c     lw         v1,0xc(a2)
	 
	 // primMem->end
     9::800a0d34 08 00 e8 8c     lw         t0,0x8(a3)
	 
	 // primMem->unk(0x14?)
     9::800a0d38 14 00 fd 8c     lw         sp,0x14(a3)
	 
	 // if ptrQuadBlockArray == 0 (invalid), then end rendering, return to exe
     9::800a0d3c bb 00 60 10     beq        v1,zero,LAB_OVR_229__800a102c
	 
	 // 1f800030 = primMem->end
     9::800a0d40 30 00 28 ac     _sw        t0,offset DAT_1f800030(at)                       = ??
	 
	 // 1f8000dc = P1 pushBuffer
	 // 1f8000e0 = P2 pushBuffer
	 // 1f8000e4 = P3 pushBuffer
	 // 1f8000e8 = P4 pushBuffer
     9::800a0d44 dc 00 25 ac     sw         a1,offset DAT_1f8000dc(at)                       = ??
     9::800a0d48 10 01 a5 24     addiu      a1,a1,0x110
     9::800a0d4c e0 00 25 ac     sw         a1,offset DAT_1f8000e0(at)                       = ??
     9::800a0d50 10 01 a5 24     addiu      a1,a1,0x110
     9::800a0d54 e4 00 25 ac     sw         a1,offset DAT_1f8000e4(at)                       = ??
     9::800a0d58 10 01 a5 24     addiu      a1,a1,0x110
     9::800a0d5c e8 00 25 ac     sw         a1,offset DAT_1f8000e8(at)                       = ??
     
	 // t2 = 80084228
     // address of ptrClipBuffer array
	 9::800a0d60 08 80 0a 3c     lui        t2,0x8008
     9::800a0d64 28 42 4a 25     addiu      t2,t2,0x4228
     
	 // v1 = P1 clipBuffer
	 // t0 = P2 clipBuffer
	 // t1 = P3 clipBuffer
	 // t2 = P4 clipBuffer
	 9::800a0d68 00 00 43 8d     lw         v1,0x0(t2)=>DAT_80084228
     9::800a0d6c 04 00 48 8d     lw         t0,0x4(t2)=>DAT_8008422c
     9::800a0d70 08 00 49 8d     lw         t1,0x8(t2)=>DAT_80084230
     9::800a0d74 0c 00 4a 8d     lw         t2,0xc(t2)=>DAT_80084234
	 
	 // 1f800000 = P1 clipBuffer
	 // 1f800004 = P2 clipBuffer
	 // 1f800008 = P3 clipBuffer
	 // 1f80000c = P4 clipBuffer
     9::800a0d78 00 00 23 ac     sw         v1,0x0(at)=>DAT_1f800000                         = ??
     9::800a0d7c 04 00 28 ac     sw         t0,offset DAT_1f800004(at)                       = ??
     9::800a0d80 08 00 29 ac     sw         t1,offset DAT_1f800008(at)                       = ??
     9::800a0d84 0c 00 2a ac     sw         t2,offset DAT_1f80000c(at)                       = ??
	 
	 // t5 = 0x224 (loop)
     9::800a0d88 24 02 0d 24     li         t5,0x224
	 
	 // t3 = 0x1f8001b4 (ptr to start clearing)
     9::800a0d8c b4 01 2b 24     addiu      t3,at,0x1b4
	 
	 // loop, set 0x1f8001b4-0x1F8003D8
                             LAB_OVR_229__800a0d90                           XREF[1]:     OVR_229::800a0d98(j)  
     9::800a0d90 00 00 60 ad     sw         zero,0x0(t3)=>DAT_1f8001b4                       = ??
     9::800a0d94 04 00 6b 25     addiu      t3,t3,0x4
     9::800a0d98 fd ff a0 1d     bgtz       t5,LAB_OVR_229__800a0d90
     9::800a0d9c fc ff ad 25     _addiu     t5,t5,-0x4
	 
	 // t5 = 0x17 (loop)
     9::800a0da0 17 00 0d 24     li         t5,0x17
	 
	 // t3 = 0x800ab464
     9::800a0da4 0b 80 0b 3c     lui        t3,0x800b
     9::800a0da8 2c 8f 6b 25     addiu      t3,t3,-0x70d4
	 
	 // t4 = 0x1f8000ec
     9::800a0dac ec 00 2c 24     addiu      t4,at,0xec
	 
	 // 0x1f8000ec-0x1F800148
	 // some kind of render flags for quadblocks, not sure how they work
	 
	 // copy 0x17*4 bytes from 0x800ab464 to 0x1f8000ec
	 // this is 0x1f8000ec-0x1F800148
                             LAB_OVR_229__800a0db0                           XREF[1]:     OVR_229::800a0dc0(j)  
     9::800a0db0 00 00 6e 8d     lw         t6,0x0(t3)=>DAT_OVR_229__800a8f2c                = 80900818h
                                                                                             = 18100800h
     9::800a0db4 04 00 6b 25     addiu      t3,t3,0x4
     9::800a0db8 00 00 8e ad     sw         t6,0x0(t4)=>DAT_1f8000ec                         = ??
     9::800a0dbc 04 00 8c 25     addiu      t4,t4,0x4
     9::800a0dc0 fb ff a0 15     bne        t5,zero,LAB_OVR_229__800a0db0
     9::800a0dc4 ff ff ad 25     _addiu     t5,t5,-0x1
	 
	 // s7 = mesh_info -> ptrVertexArray
     9::800a0dc8 10 00 d7 8c     lw         s7,0x10(a2)
	 
	 // 1f800060 = gGT + 0x1808 (renderlists)
     9::800a0dcc 60 00 24 ac     sw         a0,offset DAT_1f800060(at)                       = ??
	 
	 // v1 = 0x1C (loop)
     9::800a0dd0 1c 00 03 24     li         v1,0x1c
	 
	 // loop through 7 functions (0x1c/4)
	 
                             LAB_OVR_229__800a0dd4                           XREF[1]:     OVR_229::800a0fc0(j)  
							 
	 // if loop is over, jump to end
     9::800a0dd4 7c 00 60 04     bltz       v1,LAB_OVR_229__800a0fc8
	 
	 // loop runs
	 
	 // t0 = renderLists+loopIndex
	 // first bsp (bsp node) in the linked list of this particular render list
     9::800a0dd8 21 40 64 00     _addu      t0,v1,a0
	 
	 // a0 = t0 + 0x0 (P1's renderlists)
     9::800a0ddc 00 00 04 8d     lw         a0,0x0(t0)
	 
	 // 1f800034 = v1 (backup loop counter)
     9::800a0de0 34 00 23 ac     sw         v1,offset DAT_1f800034(at)                       = ??
	 
	 // if P1's renderlist is empty, jump to Player2_AsFirstDraw
     9::800a0de4 11 00 80 10     beq        a0,zero,LAB_OVR_229__800a0e2c
     9::800a0de8 00 00 00 00     _nop
	 
	 // Get JR, and Run CopyMeta loops
	 // Decide which JR will execute (write 1f800074)
     9::800a0dec 1b 84 02 0c     jal        FUN_OVR_229__800a106c                            undefined FUN_OVR_229__800a106c()
     9::800a0df0 00 00 00 00     _nop
     
	 // t2 = 1f8000cc (P1 visFaceList)
	 9::800a0df4 cc 00 2a 8c     lw         t2,offset DAT_1f8000cc(at)                       = ??
	 
	 // t1 = 1f800000 (P1 clipBuffer)
     9::800a0df8 00 00 29 8c     lw         t1,0x0(at)=>DAT_1f800000                         = ??
	 
	 // t0 = 80096404 (P1 quadblock list destination)
     9::800a0dfc 09 80 08 3c     lui        t0,0x8009
     9::800a0e00 04 64 08 25     addiu      t0,t0,0x6404
	 
	 // call PrepareDraw (set camera matrix, window dimensions, etc)
	 // delay slot: a1 = 1f8000dc (P1 pushBuffer)
     9::800a0e04 32 84 02 0c     jal        FUN_OVR_229__800a10c8                            undefined FUN_OVR_229__800a10c8()
     9::800a0e08 dc 00 25 8c     _lw        a1,offset DAT_1f8000dc(at)                       = ??
     
	 // get JR
	 9::800a0e0c 74 00 28 8c     lw         t0,offset DAT_1f800074(at)                       = ??
	 
	 // t1 = 0x800a0e20, return address after JR, to return to right
	 // after the JR, literally four instructions from here
     9::800a0e10 0a 80 09 3c     lui        t1,0x800a
     9::800a0e14 20 0e 29 25     addiu      t1,t1,0xe20
	 
	 // use JR,
	 // store fake-RA at 1f800054
     9::800a0e18 08 00 00 01     jr         t0
     9::800a0e1c 54 00 29 ac     _sw        t1=>LAB_OVR_229__800a0e20,offset DAT_1f800054(   = ??
	 
                             LAB_OVR_229__800a0e20                           XREF[1]:     OVR_229::800a0e1c(*)  
     
	 // ???
	 9::800a0e20 10 00 29 8c     lw         t1,0x10(at)
	 
	 // jump to Player2_AsNextDraw
     9::800a0e24 0c 00 01 04     bgez       zero,LAB_OVR_229__800a0e58
	 
	 // store t1 at 1f800000 (P1 clip buffer)
     9::800a0e28 00 00 29 ac     _sw        t1,0x0(at)
                             
	 // Player2_AsFirstDraw
							 LAB_OVR_229__800a0e2c                           XREF[1]:     OVR_229::800a0de4(j)  
							 
	 // a0 = 1f800060 (renderlists)
     9::800a0e2c 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
	 
	 // v1 = loop index
     9::800a0e30 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
	 
	 // t1 = 80096404
     9::800a0e34 09 80 09 3c     lui        t1,0x8009
     9::800a0e38 04 64 29 25     addiu      t1,t1,0x6404
	 
	 // t0 = renderLists+loopIndex
	 // first bsp (bsp node) in the linked list of this particular render list
     9::800a0e3c 21 40 64 00     addu       t0,v1,a0
	 
	 // a0 = t0 + 0x30 (P2's renderlists)
     9::800a0e40 30 00 04 8d     lw         a0,0x30(t0)
	 
     9::800a0e44 00 00 20 ad     sw         zero,0x0(t1)=>DAT_80096404                       = ??
	 
	 // if P2's renderlist is empty, jump to Player3_AsFirstDraw
     9::800a0e48 18 00 80 10     beq        a0,zero,LAB_OVR_229__800a0eac
	 
	 // Get JR, and Run CopyMeta loops
	 // Decide which JR will execute (write 1f800074),
	 // $ra = 800a0e74 (Player2_DrawHere)
     9::800a0e4c 0a 80 1f 3c     _lui       ra,0x800a
     9::800a0e50 86 00 01 04     bgez       zero,FUN_OVR_229__800a106c
     9::800a0e54 74 0e ff 37     _ori       ra,ra,0xe74
                             
	 // Player2_AsNextDraw 
							 LAB_OVR_229__800a0e58                           XREF[1]:     OVR_229::800a0e24(j)  
							 
	 // a0 = 1f800060 (renderlists)
     9::800a0e58 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
	 
	 // v1 = loop index
     9::800a0e5c 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
     9::800a0e60 00 00 00 00     nop
	 
	 // t0 = renderLists+loopIndex
	 // first bsp (bsp node) in the linked list of this particular render list
     9::800a0e64 21 40 64 00     addu       t0,v1,a0
	 
	 // add 0x30 (go to P2 render lists, 0x30 away from P1)
     9::800a0e68 30 00 04 8d     lw         a0,0x30(t0)
     9::800a0e6c 00 00 00 00     nop
	 
	 // if render list is invalid, jump to Player3_AsFirstDraw
     9::800a0e70 0e 00 80 10     beq        a0,zero,LAB_OVR_229__800a0eac
     
	 // Player2_DrawHere
	 
	 // t2 = 1f8000d0 (P2 visFaceList)
	 9::800a0e74 d0 00 2a 8c     _lw        t2,offset DAT_1f8000d0(at)                       = ??
     
	 // t1 = 1f800004 (P2 clipBuffer)
	 9::800a0e78 04 00 29 8c     lw         t1,offset DAT_1f800004(at)                       = ??
     
	 // t0 = 80096504 (P2 quadblock list destination)
	 9::800a0e7c 09 80 08 3c     lui        t0,0x8009
     9::800a0e80 04 65 08 25     addiu      t0,t0,0x6504
     	 
	 // call PrepareDraw (set camera matrix, window dimensions, etc)
	 // delay slot: a1 = 1f8000e0 (P2 pushBuffer)
	 9::800a0e84 32 84 02 0c     jal        FUN_OVR_229__800a10c8                            undefined FUN_OVR_229__800a10c8()
     9::800a0e88 e0 00 25 8c     _lw        a1,offset DAT_1f8000e0(at)                       = ??
	 
	 // get JR
     9::800a0e8c 74 00 28 8c     lw         t0,offset DAT_1f800074(at)                       = ??
     
	 // t1 = 0x800a0e20, return address after JR, to return to right
	 // after the JR, literally four instructions from here
	 9::800a0e90 0a 80 09 3c     lui        t1,0x800a
     9::800a0e94 a0 0e 29 25     addiu      t1,t1,0xea0
     
	 // use JR
	 // store fake-RA at 1f800054
	 9::800a0e98 08 00 00 01     jr         t0
     9::800a0e9c 54 00 29 ac     _sw        t1=>LAB_OVR_229__800a0ea0,offset DAT_1f800054(   = ??
     
                        LAB_OVR_229__800a0ea0                           XREF[1]:     OVR_229::800a0e9c(*)  
     
	 // ???
	 9::800a0ea0 10 00 29 8c     lw         t1,0x10(at)
	 
	 // jump to Player3_AsNextDraw
     9::800a0ea4 0c 00 01 04     bgez       zero,LAB_OVR_229__800a0ed8
	 
	 // store t1 at 1f800004 (P2 clip buffer)
     9::800a0ea8 04 00 29 ac     _sw        t1,0x4(at)
                             
	 // Player3_AsFirstDraw
							 LAB_OVR_229__800a0eac                           XREF[2]:     OVR_229::800a0e48(j), 
                                                                                          OVR_229::800a0e70(j)  
     9::800a0eac 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
     9::800a0eb0 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
     9::800a0eb4 09 80 09 3c     lui        t1,0x8009
     9::800a0eb8 04 65 29 25     addiu      t1,t1,0x6504
     9::800a0ebc 21 40 64 00     addu       t0,v1,a0
     9::800a0ec0 60 00 04 8d     lw         a0,0x60(t0)
     9::800a0ec4 00 00 20 ad     sw         zero,0x0(t1)=>DAT_80096504                       = ??
     9::800a0ec8 18 00 80 10     beq        a0,zero,LAB_OVR_229__800a0f2c
     9::800a0ecc 0a 80 1f 3c     _lui       ra,0x800a
     9::800a0ed0 66 00 01 04     bgez       zero,FUN_OVR_229__800a106c
     9::800a0ed4 f4 0e ff 37     _ori       ra,ra,0xef4
                             
	 // Player3_AsNextDraw
							 LAB_OVR_229__800a0ed8                           XREF[1]:     OVR_229::800a0ea4(j)  
     9::800a0ed8 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
     9::800a0edc 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
     9::800a0ee0 00 00 00 00     nop
     9::800a0ee4 21 40 64 00     addu       t0,v1,a0
     9::800a0ee8 60 00 04 8d     lw         a0,0x60(t0)
     9::800a0eec 00 00 00 00     nop
     9::800a0ef0 0e 00 80 10     beq        a0,zero,LAB_OVR_229__800a0f2c
     
	 // Player3_DrawHere
	 
	 9::800a0ef4 d4 00 2a 8c     _lw        t2,offset DAT_1f8000d4(at)                       = ??
     9::800a0ef8 08 00 29 8c     lw         t1,offset DAT_1f800008(at)                       = ??
     9::800a0efc 09 80 08 3c     lui        t0,0x8009
     9::800a0f00 04 66 08 25     addiu      t0,t0,0x6604
	 
	 // call PrepareDraw (set camera matrix, window dimensions, etc)
	 // delay slot: a1 = 1f8000e4 (P3 pushBuffer)
     9::800a0f04 32 84 02 0c     jal        FUN_OVR_229__800a10c8                            undefined FUN_OVR_229__800a10c8()
     9::800a0f08 e4 00 25 8c     _lw        a1,offset DAT_1f8000e4(at)                       = ??
	 
     9::800a0f0c 74 00 28 8c     lw         t0,offset DAT_1f800074(at)                       = ??
     9::800a0f10 0a 80 09 3c     lui        t1,0x800a
     9::800a0f14 20 0f 29 25     addiu      t1,t1,0xf20
     9::800a0f18 08 00 00 01     jr         t0
     9::800a0f1c 54 00 29 ac     _sw        t1=>LAB_OVR_229__800a0f20,offset DAT_1f800054(   = ??
                             LAB_OVR_229__800a0f20                           XREF[1]:     OVR_229::800a0f1c(*)  
     9::800a0f20 10 00 29 8c     lw         t1,0x10(at)
     9::800a0f24 0c 00 01 04     bgez       zero,LAB_OVR_229__800a0f58
     9::800a0f28 08 00 29 ac     _sw        t1,0x8(at)
                             
	 // Player4_DrawAsFirst
							 LAB_OVR_229__800a0f2c                           XREF[2]:     OVR_229::800a0ec8(j), 
                                                                                          OVR_229::800a0ef0(j)  
     9::800a0f2c 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
     9::800a0f30 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
     9::800a0f34 09 80 09 3c     lui        t1,0x8009
     9::800a0f38 04 66 29 25     addiu      t1,t1,0x6604
     9::800a0f3c 21 40 64 00     addu       t0,v1,a0
     9::800a0f40 90 00 04 8d     lw         a0,0x90(t0)
     9::800a0f44 00 00 20 ad     sw         zero,0x0(t1)=>DAT_80096604                       = ??
     9::800a0f48 18 00 80 10     beq        a0,zero,LAB_OVR_229__800a0fac
     9::800a0f4c 0a 80 1f 3c     _lui       ra,0x800a
     9::800a0f50 46 00 01 04     bgez       zero,FUN_OVR_229__800a106c
     9::800a0f54 74 0f ff 37     _ori       ra,ra,0xf74
	 
	 // Player4_DrawAsNext
                             LAB_OVR_229__800a0f58                           XREF[1]:     OVR_229::800a0f24(j)  
     9::800a0f58 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
     9::800a0f5c 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
     9::800a0f60 00 00 00 00     nop
     9::800a0f64 21 40 64 00     addu       t0,v1,a0
     9::800a0f68 90 00 04 8d     lw         a0,0x90(t0)
     9::800a0f6c 00 00 00 00     nop
     9::800a0f70 0e 00 80 10     beq        a0,zero,LAB_OVR_229__800a0fac
	 
	 // Player4_DrawHere
	 
     9::800a0f74 d8 00 2a 8c     _lw        t2,offset DAT_1f8000d8(at)                       = ??
     9::800a0f78 0c 00 29 8c     lw         t1,offset DAT_1f80000c(at)                       = ??
     9::800a0f7c 09 80 08 3c     lui        t0,0x8009
     9::800a0f80 04 67 08 25     addiu      t0,t0,0x6704
	 
	 // call PrepareDraw (set camera matrix, window dimensions, etc)
	 // delay slot: a1 = 1f8000e8 (P4 pushBuffer)
     9::800a0f84 32 84 02 0c     jal        FUN_OVR_229__800a10c8                            undefined FUN_OVR_229__800a10c8()
     9::800a0f88 e8 00 25 8c     _lw        a1,offset DAT_1f8000e8(at)                       = ??
	 
     9::800a0f8c 74 00 28 8c     lw         t0,offset DAT_1f800074(at)                       = ??
     9::800a0f90 0a 80 09 3c     lui        t1,0x800a
     9::800a0f94 a0 0f 29 25     addiu      t1,t1,0xfa0
     9::800a0f98 08 00 00 01     jr         t0
     9::800a0f9c 54 00 29 ac     _sw        t1=>LAB_OVR_229__800a0fa0,offset DAT_1f800054(   = ??
                             LAB_OVR_229__800a0fa0                           XREF[1]:     OVR_229::800a0f9c(*)  
     9::800a0fa0 10 00 29 8c     lw         t1,0x10(at)
     9::800a0fa4 04 00 01 04     bgez       zero,LAB_OVR_229__800a0fb8
     9::800a0fa8 0c 00 29 ac     _sw        t1,0xc(at)
                             
	 // after all players call their JRs
							 LAB_OVR_229__800a0fac                           XREF[2]:     OVR_229::800a0f48(j), 
                                                                                          OVR_229::800a0f70(j)  
     9::800a0fac 09 80 09 3c     lui        t1,0x8009
     9::800a0fb0 04 67 29 25     addiu      t1,t1,0x6704
     9::800a0fb4 00 00 20 ad     sw         zero,0x0(t1)=>DAT_80096704                       = ??
                             LAB_OVR_229__800a0fb8                           XREF[1]:     OVR_229::800a0fa4(j)  
     9::800a0fb8 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
     9::800a0fbc 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
     9::800a0fc0 84 ff 01 04     bgez       zero,LAB_OVR_229__800a0dd4
     9::800a0fc4 fc ff 63 24     _addiu     v1,v1,-0x4
                             LAB_OVR_229__800a0fc8                           XREF[1]:     OVR_229::800a0dd4(j)  
     9::800a0fc8 af a3 02 0c     jal        FUN_OVR_229__800a8ebc                            undefined FUN_OVR_229__800a8ebc()
     9::800a0fcc dc 00 25 8c     _lw        a1,offset DAT_1f8000dc(at)                       = ??
     9::800a0fd0 08 80 0a 3c     lui        t2,0x8008
     9::800a0fd4 28 42 4a 25     addiu      t2,t2,0x4228
     9::800a0fd8 00 00 57 8d     lw         s7,0x0(t2)=>DAT_80084228
     9::800a0fdc 9c a0 02 0c     jal        FUN_OVR_229__800a8270                            undefined FUN_OVR_229__800a8270()
     9::800a0fe0 00 00 38 8c     _lw        t8,0x0(at)=>DAT_1f800000                         = ??
     9::800a0fe4 e0 00 25 8c     lw         a1,offset DAT_1f8000e0(at)                       = ??
     9::800a0fe8 08 80 0a 3c     lui        t2,0x8008
     9::800a0fec 28 42 4a 25     addiu      t2,t2,0x4228
     9::800a0ff0 04 00 57 8d     lw         s7,0x4(t2)=>DAT_8008422c
     9::800a0ff4 9c a0 02 0c     jal        FUN_OVR_229__800a8270                            undefined FUN_OVR_229__800a8270()
     9::800a0ff8 04 00 38 8c     _lw        t8,offset DAT_1f800004(at)                       = ??
     9::800a0ffc e4 00 25 8c     lw         a1,offset DAT_1f8000e4(at)                       = ??
     9::800a1000 08 80 0a 3c     lui        t2,0x8008
     9::800a1004 28 42 4a 25     addiu      t2,t2,0x4228
     9::800a1008 08 00 57 8d     lw         s7,0x8(t2)=>DAT_80084230
     9::800a100c 9c a0 02 0c     jal        FUN_OVR_229__800a8270                            undefined FUN_OVR_229__800a8270()
     9::800a1010 08 00 38 8c     _lw        t8,offset DAT_1f800008(at)                       = ??
     9::800a1014 e8 00 25 8c     lw         a1,offset DAT_1f8000e8(at)                       = ??
     9::800a1018 08 80 0a 3c     lui        t2,0x8008
     9::800a101c 28 42 4a 25     addiu      t2,t2,0x4228
     9::800a1020 0c 00 57 8d     lw         s7,0xc(t2)=>DAT_80084234
     9::800a1024 9c a0 02 0c     jal        FUN_OVR_229__800a8270                            undefined FUN_OVR_229__800a8270()
     9::800a1028 0c 00 38 8c     _lw        t8,offset DAT_1f80000c(at)                       = ??
                             
	 // end of main render function,
	 // restore all backed up registers, return to exe
							 LAB_OVR_229__800a102c                           XREF[14]:    OVR_229::800a0d04(j), 
                                                                                          OVR_229::800a0d0c(j), 
                                                                                          OVR_229::800a0d14(j), 
                                                                                          OVR_229::800a0d1c(j), 
                                                                                          OVR_229::800a0d3c(j), 
                                                                                          OVR_229::800a11e4(j), 
                                                                                          OVR_229::800a1c4c(j), 
                                                                                          FUN_OVR_229__800a2f54:800a2a28(j
                                                                                          OVR_229::800a387c(j), 
                                                                                          FUN_OVR_229__800a4d94:800a4868(j
                                                                                          OVR_229::800a56bc(j), 
                                                                                          OVR_229::800a66a8(j), 
                                                                                          OVR_229::800a72c0(j), 
                                                                                          OVR_229::800a8338(j)  
     
	 // end of main render function,
	 // restore all backed up registers, return to exe
	 9::800a102c 14 00 fd ac     sw         sp,0x14(a3)
     9::800a1030 38 00 3d 8c     lw         sp,offset DAT_1f800038(at)                       = ??
     9::800a1034 0c 00 e2 ac     sw         v0,0xc(a3)
     9::800a1038 38 00 bf 8f     lw         ra,0x38(sp)
     9::800a103c 34 00 be 8f     lw         s8,0x34(sp)
     9::800a1040 30 00 bc 8f     lw         gp,0x30(sp)
     9::800a1044 2c 00 b7 8f     lw         s7,0x2c(sp)
     9::800a1048 28 00 b6 8f     lw         s6,0x28(sp)
     9::800a104c 24 00 b5 8f     lw         s5,0x24(sp)
     9::800a1050 20 00 b4 8f     lw         s4,0x20(sp)
     9::800a1054 1c 00 b3 8f     lw         s3,0x1c(sp)
     9::800a1058 18 00 b2 8f     lw         s2,0x18(sp)
     9::800a105c 14 00 b1 8f     lw         s1,0x14(sp)
     9::800a1060 10 00 b0 8f     lw         s0,0x10(sp)
     9::800a1064 08 00 e0 03     jr         ra
     9::800a1068 3c 00 bd 27     _addiu     sp,sp,0x3c
                            

							**************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             
	// FUN_800a106c: Get JR, and Run CopyMeta loops
							 undefined FUN_OVR_229__800a106c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a106c                           XREF[4]:     OVR_229::800a0dec(c), 
                                                                                          OVR_229::800a0e50(j), 
                                                                                          OVR_229::800a0ed0(j), 
                                                                                          OVR_229::800a0f50(j)  
     // FUN_800a106c: Get JR, and Run CopyMeta loops
	 
	 // t0 = 800A8EEC
	 9::800a106c 0b 80 08 3c     lui        t0,0x800b
     9::800a1070 ec 8e 08 25     addiu      t0,t0,-0x7114
	 
	 // t0 += loopIndex (v1)
     9::800a1074 21 40 03 01     addu       t0,t0,v1
	 
	 // t2 = derefrence t0, CopyMeta
     9::800a1078 00 00 0a 8d     lw         t2,0x0(t0)=>DAT_OVR_229__800a8eec                = 80h
     
     // t0 = 800A8F0C
     9::800a107c 0b 80 08 3c     lui        t0,0x800b
     9::800a1080 0c 8f 08 25     addiu      t0,t0,-0x70f4
	 
	 // t0 += loopIndex (v1)
     9::800a1084 21 40 03 01     addu       t0,t0,v1
	 
	 // t0 = dereference, get function pointer
     9::800a1088 00 00 08 8d     lw         t0,0x0(t0)=>DAT_OVR_229__800a8f0c                = ACh
                                                                                             = OVR_229::800a665c

	 // run a loop, CopyMeta sends stuff from RAM to scratchpad,
	 // depending on which function in this 0x1c (0x7) loop is running                             
							 LAB_OVR_229__800a108c                           XREF[1]:     OVR_229::800a10b8(j)  
     
	 // CopyMeta size
	 9::800a108c 00 00 4d 8d     lw         t5,0x0(t2)=>DAT_OVR_229__800a91e4                = 0000000Eh
                                                                                             = 00000002h
     
	 // CopyMeta source (RAM addr)
	 9::800a1090 04 00 4b 8d     lw         t3,0x4(t2)=>PTR_PTR_LAB_OVR_229__800a6a0c_OVR_   = OVR_229::800a9200
                                                                                             = OVR_229::800a923c
     
	 // CopyMeta destination (scratchpad offset)
	 9::800a1094 08 00 4c 8d     lw         t4,0x8(t2)=>DAT_OVR_229__800a91ec                = 0000014Ch
                                                                                             = 00000188h
     
	 // if size == 0, skip the copy
	 9::800a1098 09 00 a0 11     beq        t5,zero,LAB_OVR_229__800a10c0
     
	 // t4 = scratchpad+t4
	 9::800a109c 21 60 81 01     _addu      t4,t4,at
                             
	 // loop through and copy until size runs out
							 LAB_OVR_229__800a10a0                           XREF[1]:     OVR_229::800a10b0(j)  
     
	 // get int from source
	 9::800a10a0 00 00 6e 8d     lw         t6,0x0(t3)
     9::800a10a4 04 00 6b 25     addiu      t3,t3,0x4
	 
	 // store int in destination
     9::800a10a8 00 00 8e ad     sw         t6=>LAB_OVR_229__800a6a0c,0x0(t4)=>DAT_1f80014c  = ??
     9::800a10ac 04 00 8c 25     addiu      t4,t4,0x4
	 
	 // end copy when size runs out
     9::800a10b0 fb ff a0 15     bne        t5,zero,LAB_OVR_229__800a10a0
     9::800a10b4 ff ff ad 25     _addiu     t5,t5,-0x1
	 
	 // loop infinitely until an invalid CopyMeta is found with null size
     9::800a10b8 f4 ff 01 04     bgez       zero,LAB_OVR_229__800a108c
	 
	 // next CopyMeta
     9::800a10bc 0c 00 4a 21     _addi      t2,t2,0xc
     
	 // JR RA,
	 // t0 = 800a665c[loopIndex], (JR to be used in rendering)
                        LAB_OVR_229__800a10c0                           XREF[1]:     OVR_229::800a1098(j)  
     9::800a10c0 08 00 e0 03     jr         ra
     9::800a10c4 74 00 28 ac     _sw        t0=>LAB_OVR_229__800a665c,offset DAT_1f800074(   = ??
                             
							 
							 **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a10c8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a10c8                           XREF[4]:     OVR_229::800a0e04(c), 
                                                                                          OVR_229::800a0e84(c), 
                                                                                          OVR_229::800a0f04(c), 
                                                                                          OVR_229::800a0f84(c)  
     
	 // FUN_OVR_229__800a10c8: PrepareDraw (set camera matrix, window dimensions, etc)
	 9::800a10c8 64 00 28 ac     sw         t0,0x64(at)
     9::800a10cc 10 00 29 ac     sw         t1,0x10(at)
     9::800a10d0 c8 00 2a ac     sw         t2,0xc8(at)
	 
	 // pushBuffer offset 0x28, store entire matrix on GTE
     9::800a10d4 28 00 ab 8c     lw         t3,0x28(a1)
     9::800a10d8 2c 00 ac 8c     lw         t4,0x2c(a1)
     9::800a10dc 30 00 ad 8c     lw         t5,0x30(a1)
     9::800a10e0 34 00 ae 8c     lw         t6,0x34(a1)
     9::800a10e4 38 00 af 8c     lw         t7,0x38(a1)
     9::800a10e8 3c 00 b0 8c     lw         s0,0x3c(a1)
     9::800a10ec 40 00 b1 8c     lw         s1,0x40(a1)
     9::800a10f0 44 00 b2 8c     lw         s2,0x44(a1)
     9::800a10f4 00 00 cb 48     gte_ldR1   t3
     9::800a10f8 00 08 cc 48     gte_ldR1   t4
     9::800a10fc 00 10 cd 48     gte_ldR2   t5
     9::800a1100 00 18 ce 48     gte_ldR3   t6
     9::800a1104 00 20 cf 48     gte_ldR33  t7
     9::800a1108 00 28 d0        ldtr       s0,s1,s2
                 48 00 30 
                 d1 48 00 
				 
	 // pushBuffer 0xC - 0x12, frustum data
     9::800a1114 0c 00 b0 84     lh         s0,0xc(a1)
     9::800a1118 0e 00 b1 84     lh         s1,0xe(a1)
     9::800a111c 10 00 b2 84     lh         s2,0x10(a1)
     9::800a1120 98 01 30 a4     sh         s0,0x198(at)
     9::800a1124 9a 01 31 a4     sh         s1,0x19a(at)
     9::800a1128 9c 01 32 a4     sh         s2,0x19c(at)
	 
	 // screen dimensions, and distance to screen
     9::800a112c 20 00 a3 84     lh         v1,0x20(a1)
     9::800a1130 22 00 a8 84     lh         t0,0x22(a1)
     9::800a1134 18 00 a9 8c     lw         t1,0x18(a1)
     9::800a1138 c0 1b 03 00     sll        v1,v1,0xf
     9::800a113c c0 43 08 00     sll        t0,t0,0xf
     9::800a1140 00 c0 c3 48     gte_ldOFX  v1
     9::800a1144 00 c8 c8 48     gte_ldOFY  t0
     9::800a1148 00 d0 c9 48     gte_ldH    t1
	 
	 // halfway point
     9::800a114c 43 48 09 00     sra        t1,t1,0x1
     9::800a1150 01 00 29 25     addiu      t1,t1,0x1
	 
	 // 0x1f80005c = halfway distance
     9::800a1154 5c 00 29 ac     sw         t1,0x5c(at)
     
	 9::800a1158 20 00 a3 8c     lw         v1,0x20(a1)
     9::800a115c f4 00 a5 8c     lw         a1,0xf4(a1)
     9::800a1160 08 00 e0 03     jr         ra
     9::800a1164 6c 00 23 ac     _sw        v1,0x6c(at)
	 
                             LAB_OVR_229__800a1168                           XREF[8]:     OVR_229::800a1560(j), 
                                                                                          OVR_229::800a1c54(j), 
                                                                                          OVR_229::800a2eb8(j), 
                                                                                          OVR_229::800a3884(j), 
                                                                                          FUN_OVR_229__800a4d94:800a4cf8(j
                                                                                          OVR_229::800a56c4(j), 
                                                                                          OVR_229::800a695c(j), 
                                                                                          OVR_229::800a72c8(j)  
     9::800a1168 54 00 3f 8c     lw         ra,0x54(at)
     9::800a116c 00 00 00 00     nop
     9::800a1170 08 00 e0 03     jr         ra
     9::800a1174 00 00 00 00     _nop
     9::800a1178 88 00 23 8c     lw         v1,0x88(at)
     9::800a117c 00 a8 c0        ldfcdir    zero,zero,zero
                 48 00 b0 
                 c0 48 00 
     9::800a1188 00 00 68 8c     lw         t0,0x0(v1)
     9::800a118c 04 00 69 8c     lw         t1,0x4(v1)
     9::800a1190 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a1194 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a1198 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_229__800a119c                           XREF[1]:     OVR_229::800a1554(j)  
     9::800a119c ef 00 80 10     beq        a0,zero,LAB_OVR_229__800a155c
     9::800a11a0 00 00 00 00     _nop
     9::800a11a4 1c 00 78 8c     lw         t8,0x1c(v1)
     9::800a11a8 18 00 79 8c     lw         t9,0x18(v1)
     9::800a11ac c8 00 2a 8c     lw         t2,0xc8(at)
     9::800a11b0 3c 00 08 97     lhu        t0,0x3c(t8)
     9::800a11b4 68 00 39 ac     sw         t9,0x68(at)
     9::800a11b8 c2 48 08 00     srl        t1,t0,0x3
     9::800a11bc fc 01 29 31     andi       t1,t1,0x1fc
     9::800a11c0 21 48 2a 01     addu       t1,t1,t2
     9::800a11c4 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a11c8 00 00 29 8d     lw         t1,0x0(t1)
     9::800a11cc 1f 00 08 31     andi       t0,t0,0x1f
     9::800a11d0 bc 00 28 ac     sw         t0,0xbc(at)
     9::800a11d4 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_229__800a11d8                           XREF[1]:     OVR_229::800a1548(j)  
     9::800a11d8 30 00 23 8c     lw         v1,0x30(at)
     9::800a11dc 40 37 48 24     addiu      t0,v0,0x3740
     9::800a11e0 23 18 68 00     subu       v1,v1,t0
     9::800a11e4 91 ff 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a11e8 bc 00 23 8c     _lw        v1,0xbc(at)
     9::800a11ec c4 00 28 8c     lw         t0,0xc4(at)
     9::800a11f0 06 00 61 04     bgez       v1,LAB_OVR_229__800a120c
     9::800a11f4 c0 00 29 8c     _lw        t1,0xc0(at)
     9::800a11f8 1f 00 03 24     li         v1,0x1f
     9::800a11fc 04 00 28 8d     lw         t0,0x4(t1)
     9::800a1200 04 00 29 25     addiu      t1,t1,0x4
     9::800a1204 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a1208 c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_229__800a120c                           XREF[1]:     OVR_229::800a11f0(j)  
     9::800a120c 04 40 68 00     sllv       t0,t0,v1
     9::800a1210 ff ff 63 24     addiu      v1,v1,-0x1
     9::800a1214 c9 00 01 05     bgez       t0,LAB_OVR_229__800a153c
     9::800a1218 bc 00 23 ac     _sw        v1,0xbc(at)
     9::800a121c b4 01 3e 24     addiu      s8,at,0x1b4
     9::800a1220 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a1224 00 00 14 8f     lw         s4,0x0(t8)
     9::800a1228 04 00 16 8f     lw         s6,0x4(t8)
     9::800a122c ff ff 93 32     andi       s3,s4,0xffff
     9::800a1230 00 99 13 00     sll        s3,s3,0x4
     9::800a1234 21 98 77 02     addu       s3,s3,s7
     9::800a1238 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a1240 02 a4 14 00     srl        s4,s4,0x10
     9::800a1244 00 a1 14 00     sll        s4,s4,0x4
     9::800a1248 21 a0 97 02     addu       s4,s4,s7
     9::800a124c 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a1254 ff ff d5 32     andi       s5,s6,0xffff
     9::800a1258 00 a9 15 00     sll        s5,s5,0x4
     9::800a125c 21 a8 b7 02     addu       s5,s5,s7
     9::800a1260 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a1268 02 b4 16 00     srl        s6,s6,0x10
     9::800a126c 00 b1 16 00     sll        s6,s6,0x4
     9::800a1270 30 00 28 4a     RTPT
     9::800a1274 21 b0 d7 02     addu       s6,s6,s7
     9::800a1278 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a127c 08 00 90 8e     lw         s0,0x8(s4)
     9::800a1280 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a1284 08 00 cf af     sw         t7,0x8(s8)
     9::800a1288 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a128c 30 00 d1 af     sw         s1,0x30(s8)
     9::800a1290 0c 00 6f 86     lh         t7,0xc(s3)
     9::800a1294 0c 00 90 86     lh         s0,0xc(s4)
     9::800a1298 0c 00 b1 86     lh         s1,0xc(s5)
     9::800a129c 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a12a0 00 f8 43 48     gte_stFLAG v1
     9::800a12a4 10 00 d1 eb     gte_stSZ1  0x10(s8)
     9::800a12a8 80 1b 03 00     sll        v1,v1,0xe
     9::800a12ac c2 1f 03 00     srl        v1,v1,0x1f
     9::800a12b0 9d 00 60 14     bne        v1,zero,LAB_OVR_229__800a1528
     9::800a12b4 08 00 14 8f     _lw        s4,0x8(t8)
     9::800a12b8 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a12bc 24 00 d2 eb     gte_stSZ2  0x24(s8)
     9::800a12c0 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a12c4 38 00 d3 eb     gte_stSZ3  0x38(s8)
     9::800a12c8 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a12cc 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a12d0 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a12d4 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a12d8 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a12dc 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a12e0 06 00 cf a7     sh         t7,0x6(s8)
     9::800a12e4 1a 00 d0 a7     sh         s0,0x1a(s8)
     9::800a12e8 2e 00 d1 a7     sh         s1,0x2e(s8)
     9::800a12ec 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a12f4 ff ff 93 32     andi       s3,s4,0xffff
     9::800a12f8 00 99 13 00     sll        s3,s3,0x4
     9::800a12fc 21 98 77 02     addu       s3,s3,s7
     9::800a1300 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a1308 02 a4 14 00     srl        s4,s4,0x10
     9::800a130c 00 a1 14 00     sll        s4,s4,0x4
     9::800a1310 21 a0 97 02     addu       s4,s4,s7
     9::800a1314 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a131c 21 c8 20 00     move       t9,at
     9::800a1320 00 00 00 00     nop
     9::800a1324 30 00 28 4a     RTPT
     9::800a1328 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a132c 08 00 70 8e     lw         s0,0x8(s3)
     9::800a1330 08 00 91 8e     lw         s1,0x8(s4)
     9::800a1334 44 00 cf af     sw         t7,0x44(s8)
     9::800a1338 58 00 d0 af     sw         s0,0x58(s8)
     9::800a133c 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a1340 0c 00 cf 86     lh         t7,0xc(s6)
     9::800a1344 0c 00 70 86     lh         s0,0xc(s3)
     9::800a1348 0c 00 91 86     lh         s1,0xc(s4)
     9::800a134c 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a1350 00 f8 43 48     gte_stFLAG v1
     9::800a1354 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     9::800a1358 80 1b 03 00     sll        v1,v1,0xe
     9::800a135c c2 1f 03 00     srl        v1,v1,0x1f
     9::800a1360 71 00 60 14     bne        v1,zero,LAB_OVR_229__800a1528
     9::800a1364 0c 00 14 8f     _lw        s4,0xc(t8)
     9::800a1368 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     9::800a136c 60 00 d2 eb     gte_stSZ2  0x60(s8)
     9::800a1370 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a1374 74 00 d3 eb     gte_stSZ3  0x74(s8)
     9::800a1378 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a137c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a1380 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a1384 10 00 15 97     lhu        s5,0x10(t8)
     9::800a1388 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a138c 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a1390 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a1394 42 00 cf a7     sh         t7,0x42(s8)
     9::800a1398 56 00 d0 a7     sh         s0,0x56(s8)
     9::800a139c 6a 00 d1 a7     sh         s1,0x6a(s8)
     9::800a13a0 ff ff 93 32     andi       s3,s4,0xffff
     9::800a13a4 00 99 13 00     sll        s3,s3,0x4
     9::800a13a8 21 98 77 02     addu       s3,s3,s7
     9::800a13ac 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a13b4 02 a4 14 00     srl        s4,s4,0x10
     9::800a13b8 00 a1 14 00     sll        s4,s4,0x4
     9::800a13bc 21 a0 97 02     addu       s4,s4,s7
     9::800a13c0 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a13c8 14 00 09 8f     lw         t1,0x14(t8)
     9::800a13cc 00 a9 15 00     sll        s5,s5,0x4
     9::800a13d0 21 a8 b7 02     addu       s5,s5,s7
     9::800a13d4 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a13dc 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a13e0 08 00 08 24     li         t0,0x8
     9::800a13e4 30 00 28 4a     RTPT
     9::800a13e8 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a13ec 08 00 90 8e     lw         s0,0x8(s4)
     9::800a13f0 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a13f4 80 00 cf af     sw         t7,0x80(s8)
     9::800a13f8 94 00 d0 af     sw         s0,0x94(s8)
     9::800a13fc a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a1400 0c 00 6f 86     lh         t7,0xc(s3)
     9::800a1404 0c 00 90 86     lh         s0,0xc(s4)
     9::800a1408 0c 00 b1 86     lh         s1,0xc(s5)
     9::800a140c 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a1410 00 f8 43 48     gte_stFLAG v1
     9::800a1414 88 00 d1 eb     gte_stSZ1  0x88(s8)
     9::800a1418 80 1b 03 00     sll        v1,v1,0xe
     9::800a141c c2 1f 03 00     srl        v1,v1,0x1f
     9::800a1420 41 00 60 14     bne        v1,zero,LAB_OVR_229__800a1528
     9::800a1424 98 00 cd eb     _gte_stS   0x98(s8)
     9::800a1428 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     9::800a142c ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a1430 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     9::800a1434 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a1438 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a143c 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a1440 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a1444 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a1448 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a144c 7e 00 cf a7     sh         t7,0x7e(s8)
     9::800a1450 92 00 d0 a7     sh         s0,0x92(s8)
     9::800a1454 a6 00 d1 a7     sh         s1,0xa6(s8)
     9::800a1458 98 01 2d 84     lh         t5,0x198(at)
     9::800a145c 9c 01 2e 84     lh         t6,0x19c(at)
     9::800a1460 00 00 cb 87     lh         t3,0x0(s8)
     9::800a1464 04 00 cc 87     lh         t4,0x4(s8)
     9::800a1468 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a146c 08 00 cf 8f     _lw        t7,0x8(s8)
     9::800a1470 14 00 cb 87     lh         t3,0x14(s8)
     9::800a1474 18 00 cc 87     lh         t4,0x18(s8)
     9::800a1478 08 00 cf af     sw         t7,0x8(s8)
     9::800a147c 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a1480 1c 00 cf 8f     _lw        t7,0x1c(s8)
     9::800a1484 28 00 cb 87     lh         t3,0x28(s8)
     9::800a1488 2c 00 cc 87     lh         t4,0x2c(s8)
     9::800a148c 1c 00 cf af     sw         t7,0x1c(s8)
     9::800a1490 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a1494 30 00 cf 8f     _lw        t7,0x30(s8)
     9::800a1498 3c 00 cb 87     lh         t3,0x3c(s8)
     9::800a149c 40 00 cc 87     lh         t4,0x40(s8)
     9::800a14a0 30 00 cf af     sw         t7,0x30(s8)
     9::800a14a4 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a14a8 44 00 cf 8f     _lw        t7,0x44(s8)
     9::800a14ac 50 00 cb 87     lh         t3,0x50(s8)
     9::800a14b0 54 00 cc 87     lh         t4,0x54(s8)
     9::800a14b4 44 00 cf af     sw         t7,0x44(s8)
     9::800a14b8 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a14bc 58 00 cf 8f     _lw        t7,0x58(s8)
     9::800a14c0 64 00 cb 87     lh         t3,0x64(s8)
     9::800a14c4 68 00 cc 87     lh         t4,0x68(s8)
     9::800a14c8 58 00 cf af     sw         t7,0x58(s8)
     9::800a14cc 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a14d0 6c 00 cf 8f     _lw        t7,0x6c(s8)
     9::800a14d4 78 00 cb 87     lh         t3,0x78(s8)
     9::800a14d8 7c 00 cc 87     lh         t4,0x7c(s8)
     9::800a14dc 6c 00 cf af     sw         t7,0x6c(s8)
     9::800a14e0 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a14e4 80 00 cf 8f     _lw        t7,0x80(s8)
     9::800a14e8 8c 00 cb 87     lh         t3,0x8c(s8)
     9::800a14ec 90 00 cc 87     lh         t4,0x90(s8)
     9::800a14f0 80 00 cf af     sw         t7,0x80(s8)
     9::800a14f4 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a14f8 94 00 cf 8f     _lw        t7,0x94(s8)
     9::800a14fc a0 00 cb 87     lh         t3,0xa0(s8)
     9::800a1500 a4 00 cc 87     lh         t4,0xa4(s8)
     9::800a1504 94 00 cf af     sw         t7,0x94(s8)
     9::800a1508 5c 85 02 0c     jal        FUN_OVR_229__800a1570                            undefined FUN_OVR_229__800a1570()
     9::800a150c a8 00 cf 8f     _lw        t7,0xa8(s8)
     9::800a1510 0a 80 03 3c     lui        v1,0x800a
     9::800a1514 3c 15 63 24     addiu      v1,v1,0x153c
     9::800a1518 a8 00 cf af     sw         t7,0xa8(s8)
     9::800a151c 3c 00 23 af     sw         v1=>LAB_OVR_229__800a153c,0x3c(t9)
     9::800a1520 af 00 01 04     bgez       zero,LAB_OVR_229__800a17e0
     9::800a1524 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a1528                           XREF[3]:     OVR_229::800a12b0(j), 
                                                                                          OVR_229::800a1360(j), 
                                                                                          OVR_229::800a1420(j)  
     9::800a1528 64 00 28 8c     lw         t0,0x64(at)
     9::800a152c 00 00 00 00     nop
     9::800a1530 00 00 18 ad     sw         t8,0x0(t0)
     9::800a1534 04 00 08 25     addiu      t0,t0,0x4
     9::800a1538 64 00 28 ac     sw         t0,0x64(at)
                             LAB_OVR_229__800a153c                           XREF[2]:     OVR_229::800a1214(j), 
                                                                                          OVR_229::800a151c(*)  
     9::800a153c 68 00 39 8c     lw         t9,0x68(at)
     9::800a1540 5c 00 18 27     addiu      t8,t8,0x5c
     9::800a1544 ff ff 39 27     addiu      t9,t9,-0x1
     9::800a1548 23 ff 20 1f     bgtz       t9,LAB_OVR_229__800a11d8
     9::800a154c 68 00 39 ac     _sw        t9,0x68(at)
     9::800a1550 00 00 84 8c     lw         a0,0x0(a0)
     9::800a1554 11 ff 01 04     bgez       zero,LAB_OVR_229__800a119c
     9::800a1558 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_229__800a155c                           XREF[1]:     OVR_229::800a119c(j)  
     9::800a155c 64 00 28 8c     lw         t0,0x64(at)
     9::800a1560 01 ff 01 04     bgez       zero,LAB_OVR_229__800a1168
     9::800a1564 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_229__800a1568                           XREF[3]:     OVR_229::800a194c(j), 
                                                                                          OVR_229::800a1954(j), 
                                                                                          OVR_229::800a1994(j)  
     9::800a1568 08 00 e0 03     jr         ra
     9::800a156c 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a1570()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a1570                           XREF[9]:     OVR_229::800a1468(c), 
                                                                                          OVR_229::800a147c(c), 
                                                                                          OVR_229::800a1490(c), 
                                                                                          OVR_229::800a14a4(c), 
                                                                                          OVR_229::800a14b8(c), 
                                                                                          OVR_229::800a14cc(c), 
                                                                                          OVR_229::800a14e0(c), 
                                                                                          OVR_229::800a14f4(c), 
                                                                                          OVR_229::800a1508(c)  
     9::800a1570 23 58 6d 01     subu       t3,t3,t5
     9::800a1574 02 00 61 05     bgez       t3,LAB_OVR_229__800a1580
     9::800a1578 23 60 8e 01     _subu      t4,t4,t6
     9::800a157c 22 58 0b 00     sub        t3,zero,t3
                             LAB_OVR_229__800a1580                           XREF[1]:     OVR_229::800a1574(j)  
     9::800a1580 02 00 81 05     bgez       t4,LAB_OVR_229__800a158c
     9::800a1584 00 00 00 00     _nop
     9::800a1588 22 60 0c 00     sub        t4,zero,t4
                             LAB_OVR_229__800a158c                           XREF[1]:     OVR_229::800a1580(j)  
     9::800a158c 23 40 6c 01     subu       t0,t3,t4
     9::800a1590 03 00 01 05     bgez       t0,LAB_OVR_229__800a15a0
     9::800a1594 83 40 0c 00     _sra       t0,t4,0x2
     9::800a1598 83 40 0b 00     sra        t0,t3,0x2
     9::800a159c 21 58 80 01     move       t3,t4
                             LAB_OVR_229__800a15a0                           XREF[1]:     OVR_229::800a1590(j)  
     9::800a15a0 21 58 68 01     addu       t3,t3,t0
     9::800a15a4 00 f4 6b 25     addiu      t3,t3,-0xc00
     9::800a15a8 0b 00 61 05     bgez       t3,LAB_OVR_229__800a15d8
     9::800a15ac c0 40 0b 00     _sll       t0,t3,0x3
     9::800a15b0 00 10 08 25     addiu      t0,t0,0x1000
     9::800a15b4 06 00 00 05     bltz       t0,LAB_OVR_229__800a15d0
     9::800a15b8 00 30 8f 48     _gte_ldRGB t7
     9::800a15bc 00 40 88 48     gte_ldIR0  t0
     9::800a15c0 00 00 00        nDPCS
                 00 00 00 
                 00 00 10 
     9::800a15cc 00 b0 0f 48     gte_stRGB2 t7
                             LAB_OVR_229__800a15d0                           XREF[1]:     OVR_229::800a15b4(j)  
     9::800a15d0 08 00 e0 03     jr         ra
     9::800a15d4 00 00 00 00     _nop
                             LAB_OVR_229__800a15d8                           XREF[1]:     OVR_229::800a15a8(j)  
     9::800a15d8 08 00 e0 03     jr         ra
     9::800a15dc 00 00 0f 24     _li        t7,0x0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a15e0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a15e0                           XREF[4]:     FUN_OVR_229__800a166c:800a16b8(j
                                                                                          FUN_OVR_229__800a166c:800a1750(c
                                                                                          FUN_OVR_229__800a166c:800a1778(c
                                                                                          FUN_OVR_229__800a166c:800a17e4(c
     9::800a15e0 00 00 d3 27     addiu      s3,s8,0x0
     9::800a15e4 50 00 d4 27     addiu      s4,s8,0x50
     9::800a15e8 64 00 d5 27     addiu      s5,s8,0x64
     9::800a15ec c7 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a15f0 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a15f4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a15f4                           XREF[6]:     FUN_OVR_229__800a166c:800a16c0(c
                                                                                          FUN_OVR_229__800a166c:800a1760(j
                                                                                          FUN_OVR_229__800a166c:800a1770(c
                                                                                          FUN_OVR_229__800a166c:800a17a0(c
                                                                                          FUN_OVR_229__800a166c:800a17c0(c
                                                                                          FUN_OVR_229__800a166c:800a17f4(c
     9::800a15f4 50 00 d3 27     addiu      s3,s8,0x50
     9::800a15f8 14 00 d4 27     addiu      s4,s8,0x14
     9::800a15fc 78 00 d5 27     addiu      s5,s8,0x78
     9::800a1600 c2 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a1604 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a1608()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a1608                           XREF[6]:     FUN_OVR_229__800a166c:800a16e8(c
                                                                                          FUN_OVR_229__800a166c:800a1748(c
                                                                                          FUN_OVR_229__800a166c:800a1788(j
                                                                                          FUN_OVR_229__800a166c:800a1798(c
                                                                                          FUN_OVR_229__800a166c:800a17c8(c
                                                                                          FUN_OVR_229__800a166c:800a1804(c
     9::800a1608 64 00 d3 27     addiu      s3,s8,0x64
     9::800a160c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a1610 28 00 d5 27     addiu      s5,s8,0x28
     9::800a1614 bd 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a1618 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a161c                           XREF[4]:     OVR_229::800a1738(j), 
                                                                                          OVR_229::800a17b0(j), 
                                                                                          OVR_229::800a17d8(j), 
                                                                                          OVR_229::800a181c(j)  
     9::800a161c 78 00 d3 27     addiu      s3,s8,0x78
     9::800a1620 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a1624 a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a1628 b8 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a162c 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a1630()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a1630                           XREF[2]:     FUN_OVR_229__800a166c:800a16e0(c
                                                                                          FUN_OVR_229__800a166c:800a17b8(c
     9::800a1630 64 00 d3 27     addiu      s3,s8,0x64
     9::800a1634 00 00 d4 27     addiu      s4,s8,0x0
     9::800a1638 78 00 d5 27     addiu      s5,s8,0x78
     9::800a163c b3 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a1640 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a1644()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a1644                           XREF[2]:     FUN_OVR_229__800a166c:800a16f8(j
                                                                                          FUN_OVR_229__800a166c:800a1768(c
     9::800a1644 14 00 d3 27     addiu      s3,s8,0x14
     9::800a1648 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a164c 78 00 d5 27     addiu      s5,s8,0x78
     9::800a1650 ae 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a1654 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a1658()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a1658                           XREF[2]:     FUN_OVR_229__800a166c:800a16c8(c
                                                                                          FUN_OVR_229__800a166c:800a1790(c
     9::800a1658 28 00 d3 27     addiu      s3,s8,0x28
     9::800a165c 00 00 d4 27     addiu      s4,s8,0x0
     9::800a1660 78 00 d5 27     addiu      s5,s8,0x78
     9::800a1664 a9 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a1668 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a166c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a166c                           XREF[2]:     OVR_229::800a16d8(j), 
                                                                                          OVR_229::800a1740(c)  
     9::800a166c 28 00 d3 27     addiu      s3,s8,0x28
     9::800a1670 78 00 d4 27     addiu      s4,s8,0x78
     9::800a1674 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a1678 a4 00 01 04     bgez       zero,FUN_OVR_229__800a190c
     9::800a167c 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a1680 50 00 d3 27     addiu      s3,s8,0x50
     9::800a1684 14 00 d4 27     addiu      s4,s8,0x14
     9::800a1688 78 00 d5 27     addiu      s5,s8,0x78
     9::800a168c 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a1690 43 86 02 0c     jal        FUN_OVR_229__800a190c                            undefined FUN_OVR_229__800a190c()
     9::800a1694 0c 00 0a 24     _li        t2,0xc
     9::800a1698 64 00 d3 27     addiu      s3,s8,0x64
     9::800a169c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a16a0 28 00 d5 27     addiu      s5,s8,0x28
     9::800a16a4 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a16a8 43 86 02 0c     jal        FUN_OVR_229__800a190c                            undefined FUN_OVR_229__800a190c()
     9::800a16ac 0c 00 0a 24     _li        t2,0xc
     9::800a16b0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a16b4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a16b8 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a15e0
     9::800a16bc 0c 00 0a 24     _li        t2,0xc
     9::800a16c0 7d 85 02 0c     jal        FUN_OVR_229__800a15f4                            undefined FUN_OVR_229__800a15f4()
     9::800a16c4 0c 00 0a 24     _li        t2,0xc
     9::800a16c8 96 85 02 0c     jal        FUN_OVR_229__800a1658                            undefined FUN_OVR_229__800a1658()
     9::800a16cc 0c 00 0a 24     _li        t2,0xc
     9::800a16d0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a16d4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a16d8 e4 ff 01 04     bgez       zero,FUN_OVR_229__800a166c
     9::800a16dc 0c 00 0a 24     _li        t2,0xc
     9::800a16e0 8c 85 02 0c     jal        FUN_OVR_229__800a1630                            undefined FUN_OVR_229__800a1630()
     9::800a16e4 0c 00 0a 24     _li        t2,0xc
     9::800a16e8 82 85 02 0c     jal        FUN_OVR_229__800a1608                            undefined FUN_OVR_229__800a1608()
     9::800a16ec 0c 00 0a 24     _li        t2,0xc
     9::800a16f0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a16f4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a16f8 d2 ff 01 04     bgez       zero,FUN_OVR_229__800a1644
     9::800a16fc 0c 00 0a 24     _li        t2,0xc
     9::800a1700 00 00 d3 27     addiu      s3,s8,0x0
     9::800a1704 14 00 d4 27     addiu      s4,s8,0x14
     9::800a1708 78 00 d5 27     addiu      s5,s8,0x78
     9::800a170c 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a1710 43 86 02 0c     jal        FUN_OVR_229__800a190c                            undefined FUN_OVR_229__800a190c()
     9::800a1714 0c 00 0a 24     _li        t2,0xc
     9::800a1718 00 00 d3 27     addiu      s3,s8,0x0
     9::800a171c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a1720 28 00 d5 27     addiu      s5,s8,0x28
     9::800a1724 a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a1728 43 86 02 0c     jal        FUN_OVR_229__800a190c                            undefined FUN_OVR_229__800a190c()
     9::800a172c 0c 00 0a 24     _li        t2,0xc
     9::800a1730 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a1734 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a1738 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a161c
     9::800a173c 0c 00 0a 24     _li        t2,0xc
     9::800a1740 9b 85 02 0c     jal        FUN_OVR_229__800a166c                            undefined FUN_OVR_229__800a166c()
     9::800a1744 0c 00 0a 24     _li        t2,0xc
     9::800a1748 82 85 02 0c     jal        FUN_OVR_229__800a1608                            undefined FUN_OVR_229__800a1608()
     9::800a174c 04 00 0a 24     _li        t2,0x4
     9::800a1750 78 85 02 0c     jal        FUN_OVR_229__800a15e0                            undefined FUN_OVR_229__800a15e0()
     9::800a1754 0c 00 0a 24     _li        t2,0xc
     9::800a1758 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a175c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a1760 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a15f4
     9::800a1764 0c 00 0a 24     _li        t2,0xc
     9::800a1768 91 85 02 0c     jal        FUN_OVR_229__800a1644                            undefined FUN_OVR_229__800a1644()
     9::800a176c 0c 00 0a 24     _li        t2,0xc
     9::800a1770 7d 85 02 0c     jal        FUN_OVR_229__800a15f4                            undefined FUN_OVR_229__800a15f4()
     9::800a1774 04 00 0a 24     _li        t2,0x4
     9::800a1778 78 85 02 0c     jal        FUN_OVR_229__800a15e0                            undefined FUN_OVR_229__800a15e0()
     9::800a177c 0c 00 0a 24     _li        t2,0xc
     9::800a1780 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a1784 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a1788 9f ff 01 04     bgez       zero,FUN_OVR_229__800a1608
     9::800a178c 0c 00 0a 24     _li        t2,0xc
     9::800a1790 96 85 02 0c     jal        FUN_OVR_229__800a1658                            undefined FUN_OVR_229__800a1658()
     9::800a1794 0c 00 0a 24     _li        t2,0xc
     9::800a1798 82 85 02 0c     jal        FUN_OVR_229__800a1608                            undefined FUN_OVR_229__800a1608()
     9::800a179c 08 00 0a 24     _li        t2,0x8
     9::800a17a0 7d 85 02 0c     jal        FUN_OVR_229__800a15f4                            undefined FUN_OVR_229__800a15f4()
     9::800a17a4 0c 00 0a 24     _li        t2,0xc
     9::800a17a8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a17ac fc ff 39 27     addiu      t9,t9,-0x4
     9::800a17b0 9a ff 01 04     bgez       zero,LAB_OVR_229__800a161c
     9::800a17b4 0c 00 0a 24     _li        t2,0xc
     9::800a17b8 8c 85 02 0c     jal        FUN_OVR_229__800a1630                            undefined FUN_OVR_229__800a1630()
     9::800a17bc 0c 00 0a 24     _li        t2,0xc
     9::800a17c0 7d 85 02 0c     jal        FUN_OVR_229__800a15f4                            undefined FUN_OVR_229__800a15f4()
     9::800a17c4 08 00 0a 24     _li        t2,0x8
     9::800a17c8 82 85 02 0c     jal        FUN_OVR_229__800a1608                            undefined FUN_OVR_229__800a1608()
     9::800a17cc 0c 00 0a 24     _li        t2,0xc
     9::800a17d0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a17d4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a17d8 90 ff 01 04     bgez       zero,LAB_OVR_229__800a161c
     9::800a17dc 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_229__800a17e0                           XREF[1]:     OVR_229::800a1520(j)  
     9::800a17e0 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a17e4 78 85 02 0c     jal        FUN_OVR_229__800a15e0                            undefined FUN_OVR_229__800a15e0()
     9::800a17e8 0c 00 0a 24     _li        t2,0xc
     9::800a17ec 04 00 03 24     li         v1,0x4
     9::800a17f0 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a17f4 7d 85 02 0c     jal        FUN_OVR_229__800a15f4                            undefined FUN_OVR_229__800a15f4()
     9::800a17f8 0c 00 0a 24     _li        t2,0xc
     9::800a17fc 08 00 03 24     li         v1,0x8
     9::800a1800 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a1804 82 85 02 0c     jal        FUN_OVR_229__800a1608                            undefined FUN_OVR_229__800a1608()
     9::800a1808 0c 00 0a 24     _li        t2,0xc
     9::800a180c 0c 00 03 24     li         v1,0xc
     9::800a1810 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a1814 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a1818 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a181c 7f ff 01 04     bgez       zero,LAB_OVR_229__800a161c
     9::800a1820 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a1824()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a1824                           XREF[5]:     FUN_OVR_229__800a190c:800a1a6c(c
                                                                                          FUN_OVR_229__800a190c:800a1a80(c
                                                                                          FUN_OVR_229__800a190c:800a1a94(c
                                                                                          FUN_OVR_229__800a190c:800a1aa8(c
                                                                                          FUN_OVR_229__800a190c:800a1abc(c
     9::800a1824 00 00 ab 85     lh         t3,0x0(t5)
     9::800a1828 00 00 cc 85     lh         t4,0x0(t6)
     9::800a182c 00 00 eb a5     sh         t3,0x0(t7)
     9::800a1830 21 18 6c 01     addu       v1,t3,t4
     9::800a1834 43 18 03 00     sra        v1,v1,0x1
     9::800a1838 00 00 03 a6     sh         v1,0x0(s0)
     9::800a183c 02 00 ab 85     lh         t3,0x2(t5)
     9::800a1840 02 00 cc 85     lh         t4,0x2(t6)
     9::800a1844 02 00 eb a5     sh         t3,0x2(t7)
     9::800a1848 21 18 6c 01     addu       v1,t3,t4
     9::800a184c 43 18 03 00     sra        v1,v1,0x1
     9::800a1850 02 00 03 a6     sh         v1,0x2(s0)
     9::800a1854 04 00 ab 85     lh         t3,0x4(t5)
     9::800a1858 04 00 cc 85     lh         t4,0x4(t6)
     9::800a185c 04 00 eb a5     sh         t3,0x4(t7)
     9::800a1860 21 18 6c 01     addu       v1,t3,t4
     9::800a1864 43 18 03 00     sra        v1,v1,0x1
     9::800a1868 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a186c 00 08 83 48     gte_ldVZ0  v1
     9::800a1870 04 00 03 a6     sh         v1,0x4(s0)
     9::800a1874 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a1878 01 00 18 4a     RTPS
     9::800a187c 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a1880 08 00 eb a1     sb         t3,0x8(t7)
     9::800a1884 21 18 6c 01     addu       v1,t3,t4
     9::800a1888 43 18 03 00     sra        v1,v1,0x1
     9::800a188c 08 00 03 a2     sb         v1,0x8(s0)
     9::800a1890 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a1894 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a1898 09 00 eb a1     sb         t3,0x9(t7)
     9::800a189c 21 18 6c 01     addu       v1,t3,t4
     9::800a18a0 43 18 03 00     sra        v1,v1,0x1
     9::800a18a4 09 00 03 a2     sb         v1,0x9(s0)
     9::800a18a8 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a18ac 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a18b0 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a18b4 21 18 6c 01     addu       v1,t3,t4
     9::800a18b8 43 18 03 00     sra        v1,v1,0x1
     9::800a18bc 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a18c0 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a18c4 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a18c8 06 00 eb a1     sb         t3,0x6(t7)
     9::800a18cc 21 18 6c 01     addu       v1,t3,t4
     9::800a18d0 43 18 03 00     sra        v1,v1,0x1
     9::800a18d4 06 00 03 a2     sb         v1,0x6(s0)
     9::800a18d8 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a18dc 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a18e0 07 00 eb a1     sb         t3,0x7(t7)
     9::800a18e4 21 18 6c 01     addu       v1,t3,t4
     9::800a18e8 43 18 03 00     sra        v1,v1,0x1
     9::800a18ec 07 00 03 a2     sb         v1,0x7(s0)
     9::800a18f0 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a18f4 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a18f8 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a18fc 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a1900 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a1904 08 00 e0 03     jr         ra
     9::800a1908 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a190c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a190c                           XREF[12]:    FUN_OVR_229__800a15e0:800a15ec(j
                                                                                          FUN_OVR_229__800a15f4:800a1600(j
                                                                                          FUN_OVR_229__800a1608:800a1614(j
                                                                                          FUN_OVR_229__800a166c:800a1628(j
                                                                                          FUN_OVR_229__800a1630:800a163c(j
                                                                                          FUN_OVR_229__800a1644:800a1650(j
                                                                                          FUN_OVR_229__800a1658:800a1664(j
                                                                                          FUN_OVR_229__800a166c:800a1678(j
                                                                                          FUN_OVR_229__800a166c:800a1690(c
                                                                                          FUN_OVR_229__800a166c:800a16a8(c
                                                                                          FUN_OVR_229__800a166c:800a1710(c
                                                                                          FUN_OVR_229__800a166c:800a1728(c
     9::800a190c 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a1910 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a1914 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a1918 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a191c 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a1920 23 78 68 01     subu       t7,t3,t0
     9::800a1924 23 80 88 01     subu       s0,t4,t0
     9::800a1928 23 88 a8 01     subu       s1,t5,t0
     9::800a192c 23 90 c8 01     subu       s2,t6,t0
     9::800a1930 24 40 6c 01     and        t0,t3,t4
     9::800a1934 24 40 0d 01     and        t0,t0,t5
     9::800a1938 24 40 0e 01     and        t0,t0,t6
     9::800a193c 25 78 f0 01     or         t7,t7,s0
     9::800a1940 25 78 f1 01     or         t7,t7,s1
     9::800a1944 27 78 f2 01     nor        t7,t7,s2
     9::800a1948 25 78 e8 01     or         t7,t7,t0
     9::800a194c 06 ff e0 05     bltz       t7,LAB_OVR_229__800a1568
     9::800a1950 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a1954 04 ff e0 05     bltz       t7,LAB_OVR_229__800a1568
     9::800a1958 08 00 6f 8e     _lw        t7,0x8(s3)
     9::800a195c 08 00 90 8e     lw         s0,0x8(s4)
     9::800a1960 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a1964 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a1968 25 40 f0 01     or         t0,t7,s0
     9::800a196c 25 40 11 01     or         t0,t0,s1
     9::800a1970 02 00 00 15     bne        t0,zero,LAB_OVR_229__800a197c
     9::800a1974 04 00 03 24     _li        v1,0x4
     9::800a1978 00 00 03 24     li         v1,0x0
                             LAB_OVR_229__800a197c                           XREF[1]:     OVR_229::800a1970(j)  
     9::800a197c 25 40 11 02     or         t0,s0,s1
     9::800a1980 25 40 12 01     or         t0,t0,s2
     9::800a1984 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a1990
     9::800a1988 00 00 00 00     _nop
     9::800a198c 08 00 63 34     ori        v1,v1,0x8
                             LAB_OVR_229__800a1990                           XREF[1]:     OVR_229::800a1984(j)  
     9::800a1990 24 50 43 01     and        t2,t2,v1
     9::800a1994 f4 fe 40 11     beq        t2,zero,LAB_OVR_229__800a1568
     9::800a1998 70 00 2a ac     _sw        t2,0x70(at)
     9::800a199c 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a19a0 24 03 28 24     addiu      t0,at,0x324
     9::800a19a4 52 00 1e 11     beq        t0,s8,LAB_OVR_229__800a1af0
     9::800a19a8 04 00 39 27     _addiu     t9,t9,0x4
     9::800a19ac 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a19b0 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a19b4 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a19b8 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a19bc b4 01 23 24     addiu      v1,at,0x1b4
     9::800a19c0 16 00 7e 14     bne        v1,s8,LAB_OVR_229__800a1a1c
     9::800a19c4 40 01 03 24     _li        v1,0x140
     9::800a19c8 b4 00 c9 8f     lw         t1,0xb4(s8)
     9::800a19cc 23 18 6c 01     subu       v1,t3,t4
     9::800a19d0 82 48 09 00     srl        t1,t1,0x2
     9::800a19d4 21 48 38 01     addu       t1,t1,t8
     9::800a19d8 18 00 29 81     lb         t1,0x18(t1)
     9::800a19dc 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a19e8
     9::800a19e0 21 e0 60 01     _move      gp,t3
     9::800a19e4 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a19e8                           XREF[1]:     OVR_229::800a19dc(j)  
     9::800a19e8 23 18 8d 03     subu       v1,gp,t5
     9::800a19ec 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a19f8
     9::800a19f0 23 18 8e 03     _subu      v1,gp,t6
     9::800a19f4 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a19f8                           XREF[1]:     OVR_229::800a19ec(j)  
     9::800a19f8 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a1a04
     9::800a19fc 00 00 00 00     _nop
     9::800a1a00 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a1a04                           XREF[1]:     OVR_229::800a19f8(j)  
     9::800a1a04 21 18 80 03     move       v1,gp
     9::800a1a08 82 e1 1c 00     srl        gp,gp,0x6
     9::800a1a0c 21 e0 89 03     addu       gp,gp,t1
     9::800a1a10 80 e0 1c 00     sll        gp,gp,0x2
     9::800a1a14 21 e0 85 03     addu       gp,gp,a1
     9::800a1a18 80 02 03 24     li         v1,0x280
                             LAB_OVR_229__800a1a1c                           XREF[1]:     OVR_229::800a19c0(j)  
     9::800a1a1c 23 88 63 01     subu       s1,t3,v1
     9::800a1a20 23 90 83 01     subu       s2,t4,v1
     9::800a1a24 23 78 a3 01     subu       t7,t5,v1
     9::800a1a28 23 80 c3 01     subu       s0,t6,v1
     9::800a1a2c 42 8f 11 00     srl        s1,s1,0x1d
     9::800a1a30 04 00 31 32     andi       s1,s1,0x4
     9::800a1a34 02 97 12 00     srl        s2,s2,0x1c
     9::800a1a38 08 00 52 32     andi       s2,s2,0x8
     9::800a1a3c 25 88 32 02     or         s1,s1,s2
     9::800a1a40 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a1a44 10 00 ef 31     andi       t7,t7,0x10
     9::800a1a48 25 88 2f 02     or         s1,s1,t7
     9::800a1a4c 82 86 10 00     srl        s0,s0,0x1a
     9::800a1a50 20 00 10 32     andi       s0,s0,0x20
     9::800a1a54 25 88 30 02     or         s1,s1,s0
     9::800a1a58 25 00 20 12     beq        s1,zero,LAB_OVR_229__800a1af0
     9::800a1a5c 21 68 60 02     _move      t5,s3
     9::800a1a60 21 70 80 02     move       t6,s4
     9::800a1a64 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a1a68 00 00 cf 27     addiu      t7,s8,0x0
     9::800a1a6c 09 86 02 0c     jal        FUN_OVR_229__800a1824                            undefined FUN_OVR_229__800a1824()
     9::800a1a70 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a1a74 21 68 80 02     move       t5,s4
     9::800a1a78 21 70 c0 02     move       t6,s6
     9::800a1a7c 14 00 cf 27     addiu      t7,s8,0x14
     9::800a1a80 09 86 02 0c     jal        FUN_OVR_229__800a1824                            undefined FUN_OVR_229__800a1824()
     9::800a1a84 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a1a88 21 68 a0 02     move       t5,s5
     9::800a1a8c 21 70 60 02     move       t6,s3
     9::800a1a90 28 00 cf 27     addiu      t7,s8,0x28
     9::800a1a94 09 86 02 0c     jal        FUN_OVR_229__800a1824                            undefined FUN_OVR_229__800a1824()
     9::800a1a98 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a1a9c 21 68 c0 02     move       t5,s6
     9::800a1aa0 21 70 a0 02     move       t6,s5
     9::800a1aa4 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a1aa8 09 86 02 0c     jal        FUN_OVR_229__800a1824                            undefined FUN_OVR_229__800a1824()
     9::800a1aac a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a1ab0 21 68 80 02     move       t5,s4
     9::800a1ab4 21 70 a0 02     move       t6,s5
     9::800a1ab8 14 00 cf 27     addiu      t7,s8,0x14
     9::800a1abc 09 86 02 0c     jal        FUN_OVR_229__800a1824                            undefined FUN_OVR_229__800a1824()
     9::800a1ac0 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a1ac4 21 18 21 02     addu       v1,s1,at
     9::800a1ac8 48 01 63 8c     lw         v1,0x148(v1)
     9::800a1acc 0a 80 08 3c     lui        t0,0x800a
     9::800a1ad0 e0 1a 08 25     addiu      t0,t0,0x1ae0
     9::800a1ad4 3c 00 28 af     sw         t0=>LAB_OVR_229__800a1ae0,0x3c(t9)
     9::800a1ad8 08 00 60 00     jr         v1
     9::800a1adc 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a1ae0                           XREF[1]:     FUN_OVR_229__800a190c:800a1ad4(*
     9::800a1ae0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a1ae4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a1ae8 08 00 e0 03     jr         ra
     9::800a1aec 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a1af0                           XREF[2]:     OVR_229::800a19a4(j), 
                                                                                          OVR_229::800a1a58(j)  
     9::800a1af0 70 00 23 8c     lw         v1,0x70(at)
     9::800a1af4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a1af8 21 18 61 00     addu       v1,v1,at
     9::800a1afc 84 01 63 8c     lw         v1,0x184(v1)
     9::800a1b00 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a1b04 08 00 60 00     jr         v1
     9::800a1b08 00 00 00 00     _nop
     9::800a1b0c 21 98 80 02     move       s3,s4
     9::800a1b10 21 a0 c0 02     move       s4,s6
     9::800a1b14 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a1b18 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a1b1c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a1b20 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a1b24 08 00 90 8e     lw         s0,0x8(s4)
     9::800a1b28 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a1b2c 06 00 73 86     lh         s3,0x6(s3)
     9::800a1b30 06 00 94 86     lh         s4,0x6(s4)
     9::800a1b34 06 00 b5 86     lh         s5,0x6(s5)
     9::800a1b38 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a1b3c a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a1b40 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a1b44 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a1b48 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a1b4c a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a1b50 00 36 03 3c     lui        v1,0x3600
     9::800a1b54 25 18 6f 00     or         v1,v1,t7
     9::800a1b58 04 00 43 ac     sw         v1,0x4(v0)
     9::800a1b5c 08 00 4b ac     sw         t3,0x8(v0)
     9::800a1b60 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a1b64 10 00 50 ac     sw         s0,0x10(v0)
     9::800a1b68 14 00 4c ac     sw         t4,0x14(v0)
     9::800a1b6c 18 00 54 ac     sw         s4,0x18(v0)
     9::800a1b70 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a1b74 20 00 4d ac     sw         t5,0x20(v0)
     9::800a1b78 24 00 55 ac     sw         s5,0x24(v0)
     9::800a1b7c 28 00 09 24     li         t1,0x28
     9::800a1b80 25 00 01 04     bgez       zero,LAB_OVR_229__800a1c18
     9::800a1b84 00 09 0a 3c     _lui       t2,0x900
     9::800a1b88 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a1b8c 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a1b90 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a1b94 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a1b98 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a1b9c 08 00 90 8e     lw         s0,0x8(s4)
     9::800a1ba0 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a1ba4 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a1ba8 06 00 73 86     lh         s3,0x6(s3)
     9::800a1bac 06 00 94 86     lh         s4,0x6(s4)
     9::800a1bb0 06 00 b5 86     lh         s5,0x6(s5)
     9::800a1bb4 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a1bb8 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a1bbc 06 00 d4 86     lh         s4,0x6(s6)
     9::800a1bc0 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a1bc4 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a1bc8 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a1bcc a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a1bd0 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a1bd4 00 3e 03 3c     lui        v1,0x3e00
     9::800a1bd8 25 18 6f 00     or         v1,v1,t7
     9::800a1bdc 04 00 43 ac     sw         v1,0x4(v0)
     9::800a1be0 08 00 4b ac     sw         t3,0x8(v0)
     9::800a1be4 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a1be8 10 00 50 ac     sw         s0,0x10(v0)
     9::800a1bec 14 00 4c ac     sw         t4,0x14(v0)
     9::800a1bf0 18 00 54 ac     sw         s4,0x18(v0)
     9::800a1bf4 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a1bf8 20 00 4d ac     sw         t5,0x20(v0)
     9::800a1bfc 24 00 55 ac     sw         s5,0x24(v0)
     9::800a1c00 28 00 52 ac     sw         s2,0x28(v0)
     9::800a1c04 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a1c08 02 1c 15 00     srl        v1,s5,0x10
     9::800a1c0c 30 00 43 ac     sw         v1,0x30(v0)
     9::800a1c10 34 00 09 24     li         t1,0x34
     9::800a1c14 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a1c18                           XREF[1]:     OVR_229::800a1b80(j)  
     9::800a1c18 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a1c1c 00 42 02 00     sll        t0,v0,0x8
     9::800a1c20 02 42 08 00     srl        t0,t0,0x8
     9::800a1c24 25 18 6a 00     or         v1,v1,t2
     9::800a1c28 00 00 43 ac     sw         v1,0x0(v0)
     9::800a1c2c 21 10 49 00     addu       v0,v0,t1
     9::800a1c30 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a1c34 08 00 e0 03     jr         ra
     9::800a1c38 01 00 bd 23     _addi      sp,sp,0x1
     9::800a1c3c 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_229__800a1c40                           XREF[1]:     OVR_229::800a2058(j)  
     9::800a1c40 30 00 23 8c     lw         v1,0x30(at)
     9::800a1c44 40 37 48 24     addiu      t0,v0,0x3740
     9::800a1c48 23 18 68 00     subu       v1,v1,t0
     9::800a1c4c f7 fc 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a1c50 b4 01 3e 24     _addiu     s8,at,0x1b4
     9::800a1c54 44 fd 00 13     beq        t8,zero,LAB_OVR_229__800a1168
     9::800a1c58 b4 00 c0 af     _sw        zero,0xb4(s8)
     9::800a1c5c 00 00 14 8f     lw         s4,0x0(t8)
     9::800a1c60 04 00 16 8f     lw         s6,0x4(t8)
     9::800a1c64 ff ff 93 32     andi       s3,s4,0xffff
     9::800a1c68 00 99 13 00     sll        s3,s3,0x4
     9::800a1c6c 21 98 77 02     addu       s3,s3,s7
     9::800a1c70 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a1c78 02 a4 14 00     srl        s4,s4,0x10
     9::800a1c7c 00 a1 14 00     sll        s4,s4,0x4
     9::800a1c80 21 a0 97 02     addu       s4,s4,s7
     9::800a1c84 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a1c8c ff ff d5 32     andi       s5,s6,0xffff
     9::800a1c90 00 a9 15 00     sll        s5,s5,0x4
     9::800a1c94 21 a8 b7 02     addu       s5,s5,s7
     9::800a1c98 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a1ca0 02 b4 16 00     srl        s6,s6,0x10
     9::800a1ca4 00 b1 16 00     sll        s6,s6,0x4
     9::800a1ca8 30 00 28 4a     RTPT
     9::800a1cac 21 b0 d7 02     addu       s6,s6,s7
     9::800a1cb0 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a1cb4 08 00 90 8e     lw         s0,0x8(s4)
     9::800a1cb8 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a1cbc 08 00 cf af     sw         t7,0x8(s8)
     9::800a1cc0 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a1cc4 30 00 d1 af     sw         s1,0x30(s8)
     9::800a1cc8 0c 00 6f 86     lh         t7,0xc(s3)
     9::800a1ccc 0c 00 90 86     lh         s0,0xc(s4)
     9::800a1cd0 0c 00 b1 86     lh         s1,0xc(s5)
     9::800a1cd4 08 00 14 8f     lw         s4,0x8(t8)
     9::800a1cd8 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a1cdc 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a1ce0 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a1ce4 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a1ce8 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a1cec 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a1cf0 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a1cf4 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a1cf8 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a1cfc 06 00 cf a7     sh         t7,0x6(s8)
     9::800a1d00 1a 00 d0 a7     sh         s0,0x1a(s8)
     9::800a1d04 2e 00 d1 a7     sh         s1,0x2e(s8)
     9::800a1d08 5c 00 2a 8c     lw         t2,0x5c(at)
     9::800a1d0c 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a1d18 10 00 c3 a7     sh         v1,0x10(s8)
     9::800a1d1c 24 00 c8 a7     sh         t0,0x24(s8)
     9::800a1d20 38 00 c9 a7     sh         t1,0x38(s8)
     9::800a1d24 23 58 6a 00     subu       t3,v1,t2
     9::800a1d28 23 60 0a 01     subu       t4,t0,t2
     9::800a1d2c 23 68 2a 01     subu       t5,t1,t2
     9::800a1d30 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a1d34 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a1d38 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a1d3c 12 00 cb a3     sb         t3,0x12(s8)
     9::800a1d40 26 00 cc a3     sb         t4,0x26(s8)
     9::800a1d44 3a 00 cd a3     sb         t5,0x3a(s8)
     9::800a1d48 40 18 03 00     sll        v1,v1,0x1
     9::800a1d4c 40 40 08 00     sll        t0,t0,0x1
     9::800a1d50 40 48 09 00     sll        t1,t1,0x1
     9::800a1d54 23 58 6a 00     subu       t3,v1,t2
     9::800a1d58 23 60 0a 01     subu       t4,t0,t2
     9::800a1d5c 23 68 2a 01     subu       t5,t1,t2
     9::800a1d60 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a1d64 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a1d68 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a1d6c 13 00 cb a3     sb         t3,0x13(s8)
     9::800a1d70 27 00 cc a3     sb         t4,0x27(s8)
     9::800a1d74 3b 00 cd a3     sb         t5,0x3b(s8)
     9::800a1d78 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a1d80 ff ff 93 32     andi       s3,s4,0xffff
     9::800a1d84 00 99 13 00     sll        s3,s3,0x4
     9::800a1d88 21 98 77 02     addu       s3,s3,s7
     9::800a1d8c 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a1d94 02 a4 14 00     srl        s4,s4,0x10
     9::800a1d98 00 a1 14 00     sll        s4,s4,0x4
     9::800a1d9c 21 a0 97 02     addu       s4,s4,s7
     9::800a1da0 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a1da8 21 c8 20 00     move       t9,at
     9::800a1dac 00 00 00 00     nop
     9::800a1db0 30 00 28 4a     RTPT
     9::800a1db4 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a1db8 08 00 70 8e     lw         s0,0x8(s3)
     9::800a1dbc 08 00 91 8e     lw         s1,0x8(s4)
     9::800a1dc0 44 00 cf af     sw         t7,0x44(s8)
     9::800a1dc4 58 00 d0 af     sw         s0,0x58(s8)
     9::800a1dc8 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a1dcc 0c 00 cf 86     lh         t7,0xc(s6)
     9::800a1dd0 0c 00 70 86     lh         s0,0xc(s3)
     9::800a1dd4 0c 00 91 86     lh         s1,0xc(s4)
     9::800a1dd8 0c 00 14 8f     lw         s4,0xc(t8)
     9::800a1ddc 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a1de0 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     9::800a1de4 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a1de8 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a1dec 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a1df0 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a1df4 10 00 15 97     lhu        s5,0x10(t8)
     9::800a1df8 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a1dfc 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a1e00 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a1e04 42 00 cf a7     sh         t7,0x42(s8)
     9::800a1e08 56 00 d0 a7     sh         s0,0x56(s8)
     9::800a1e0c 6a 00 d1 a7     sh         s1,0x6a(s8)
     9::800a1e10 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a1e1c 4c 00 c3 a7     sh         v1,0x4c(s8)
     9::800a1e20 60 00 c8 a7     sh         t0,0x60(s8)
     9::800a1e24 74 00 c9 a7     sh         t1,0x74(s8)
     9::800a1e28 23 58 6a 00     subu       t3,v1,t2
     9::800a1e2c 23 60 0a 01     subu       t4,t0,t2
     9::800a1e30 23 68 2a 01     subu       t5,t1,t2
     9::800a1e34 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a1e38 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a1e3c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a1e40 4e 00 cb a3     sb         t3,0x4e(s8)
     9::800a1e44 62 00 cc a3     sb         t4,0x62(s8)
     9::800a1e48 76 00 cd a3     sb         t5,0x76(s8)
     9::800a1e4c 40 18 03 00     sll        v1,v1,0x1
     9::800a1e50 40 40 08 00     sll        t0,t0,0x1
     9::800a1e54 40 48 09 00     sll        t1,t1,0x1
     9::800a1e58 23 58 6a 00     subu       t3,v1,t2
     9::800a1e5c 23 60 0a 01     subu       t4,t0,t2
     9::800a1e60 23 68 2a 01     subu       t5,t1,t2
     9::800a1e64 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a1e68 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a1e6c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a1e70 4f 00 cb a3     sb         t3,0x4f(s8)
     9::800a1e74 63 00 cc a3     sb         t4,0x63(s8)
     9::800a1e78 77 00 cd a3     sb         t5,0x77(s8)
     9::800a1e7c ff ff 93 32     andi       s3,s4,0xffff
     9::800a1e80 00 99 13 00     sll        s3,s3,0x4
     9::800a1e84 21 98 77 02     addu       s3,s3,s7
     9::800a1e88 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a1e90 02 a4 14 00     srl        s4,s4,0x10
     9::800a1e94 00 a1 14 00     sll        s4,s4,0x4
     9::800a1e98 21 a0 97 02     addu       s4,s4,s7
     9::800a1e9c 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a1ea4 14 00 09 8f     lw         t1,0x14(t8)
     9::800a1ea8 00 a9 15 00     sll        s5,s5,0x4
     9::800a1eac 21 a8 b7 02     addu       s5,s5,s7
     9::800a1eb0 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a1eb8 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a1ebc 00 00 00 00     nop
     9::800a1ec0 30 00 28 4a     RTPT
     9::800a1ec4 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a1ec8 08 00 90 8e     lw         s0,0x8(s4)
     9::800a1ecc 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a1ed0 80 00 cf af     sw         t7,0x80(s8)
     9::800a1ed4 94 00 d0 af     sw         s0,0x94(s8)
     9::800a1ed8 a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a1edc 0c 00 6f 86     lh         t7,0xc(s3)
     9::800a1ee0 0c 00 90 86     lh         s0,0xc(s4)
     9::800a1ee4 0c 00 b1 86     lh         s1,0xc(s5)
     9::800a1ee8 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a1eec 98 00 cd eb     gte_stSXY1 0x98(s8)
     9::800a1ef0 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a1ef4 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a1ef8 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a1efc 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a1f00 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a1f04 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a1f08 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a1f0c 7e 00 cf a7     sh         t7,0x7e(s8)
     9::800a1f10 92 00 d0 a7     sh         s0,0x92(s8)
     9::800a1f14 a6 00 d1 a7     sh         s1,0xa6(s8)
     9::800a1f18 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a1f24 88 00 c3 a7     sh         v1,0x88(s8)
     9::800a1f28 9c 00 c8 a7     sh         t0,0x9c(s8)
     9::800a1f2c b0 00 c9 a7     sh         t1,0xb0(s8)
     9::800a1f30 23 58 6a 00     subu       t3,v1,t2
     9::800a1f34 23 60 0a 01     subu       t4,t0,t2
     9::800a1f38 23 68 2a 01     subu       t5,t1,t2
     9::800a1f3c c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a1f40 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a1f44 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a1f48 8a 00 cb a3     sb         t3,0x8a(s8)
     9::800a1f4c 9e 00 cc a3     sb         t4,0x9e(s8)
     9::800a1f50 b2 00 cd a3     sb         t5,0xb2(s8)
     9::800a1f54 40 18 03 00     sll        v1,v1,0x1
     9::800a1f58 40 40 08 00     sll        t0,t0,0x1
     9::800a1f5c 40 48 09 00     sll        t1,t1,0x1
     9::800a1f60 23 58 6a 00     subu       t3,v1,t2
     9::800a1f64 23 60 0a 01     subu       t4,t0,t2
     9::800a1f68 23 68 2a 01     subu       t5,t1,t2
     9::800a1f6c c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a1f70 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a1f74 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a1f78 8b 00 cb a3     sb         t3,0x8b(s8)
     9::800a1f7c 9f 00 cc a3     sb         t4,0x9f(s8)
     9::800a1f80 b3 00 cd a3     sb         t5,0xb3(s8)
     9::800a1f84 98 01 2d 84     lh         t5,0x198(at)
     9::800a1f88 9c 01 2e 84     lh         t6,0x19c(at)
     9::800a1f8c 00 00 cb 87     lh         t3,0x0(s8)
     9::800a1f90 04 00 cc 87     lh         t4,0x4(s8)
     9::800a1f94 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a1f98 08 00 cf 8f     _lw        t7,0x8(s8)
     9::800a1f9c 14 00 cb 87     lh         t3,0x14(s8)
     9::800a1fa0 18 00 cc 87     lh         t4,0x18(s8)
     9::800a1fa4 08 00 cf af     sw         t7,0x8(s8)
     9::800a1fa8 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a1fac 1c 00 cf 8f     _lw        t7,0x1c(s8)
     9::800a1fb0 28 00 cb 87     lh         t3,0x28(s8)
     9::800a1fb4 2c 00 cc 87     lh         t4,0x2c(s8)
     9::800a1fb8 1c 00 cf af     sw         t7,0x1c(s8)
     9::800a1fbc 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a1fc0 30 00 cf 8f     _lw        t7,0x30(s8)
     9::800a1fc4 3c 00 cb 87     lh         t3,0x3c(s8)
     9::800a1fc8 40 00 cc 87     lh         t4,0x40(s8)
     9::800a1fcc 30 00 cf af     sw         t7,0x30(s8)
     9::800a1fd0 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a1fd4 44 00 cf 8f     _lw        t7,0x44(s8)
     9::800a1fd8 50 00 cb 87     lh         t3,0x50(s8)
     9::800a1fdc 54 00 cc 87     lh         t4,0x54(s8)
     9::800a1fe0 44 00 cf af     sw         t7,0x44(s8)
     9::800a1fe4 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a1fe8 58 00 cf 8f     _lw        t7,0x58(s8)
     9::800a1fec 64 00 cb 87     lh         t3,0x64(s8)
     9::800a1ff0 68 00 cc 87     lh         t4,0x68(s8)
     9::800a1ff4 58 00 cf af     sw         t7,0x58(s8)
     9::800a1ff8 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a1ffc 6c 00 cf 8f     _lw        t7,0x6c(s8)
     9::800a2000 78 00 cb 87     lh         t3,0x78(s8)
     9::800a2004 7c 00 cc 87     lh         t4,0x7c(s8)
     9::800a2008 6c 00 cf af     sw         t7,0x6c(s8)
     9::800a200c 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a2010 80 00 cf 8f     _lw        t7,0x80(s8)
     9::800a2014 8c 00 cb 87     lh         t3,0x8c(s8)
     9::800a2018 90 00 cc 87     lh         t4,0x90(s8)
     9::800a201c 80 00 cf af     sw         t7,0x80(s8)
     9::800a2020 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a2024 94 00 cf 8f     _lw        t7,0x94(s8)
     9::800a2028 a0 00 cb 87     lh         t3,0xa0(s8)
     9::800a202c a4 00 cc 87     lh         t4,0xa4(s8)
     9::800a2030 94 00 cf af     sw         t7,0x94(s8)
     9::800a2034 1a 88 02 0c     jal        FUN_OVR_229__800a2068                            undefined FUN_OVR_229__800a2068()
     9::800a2038 a8 00 cf 8f     _lw        t7,0xa8(s8)
     9::800a203c 0a 80 03 3c     lui        v1,0x800a
     9::800a2040 54 20 63 24     addiu      v1,v1,0x2054
     9::800a2044 a8 00 cf af     sw         t7,0xa8(s8)
     9::800a2048 3c 00 23 af     sw         v1=>LAB_OVR_229__800a2054,0x3c(t9)
     9::800a204c a2 00 01 04     bgez       zero,LAB_OVR_229__800a22d8
     9::800a2050 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a2054                           XREF[1]:     OVR_229::800a2048(*)  
     9::800a2054 04 00 98 8c     lw         t8,0x4(a0)
     9::800a2058 f9 fe 01 04     bgez       zero,LAB_OVR_229__800a1c40
     9::800a205c 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_229__800a2060                           XREF[8]:     OVR_229::800a2444(j), 
                                                                                          OVR_229::800a24a8(j), 
                                                                                          OVR_229::800a24b0(j), 
                                                                                          OVR_229::800a24f0(j), 
                                                                                          OVR_229::800a2684(j), 
                                                                                          OVR_229::800a2730(j), 
                                                                                          OVR_229::800a2854(j), 
                                                                                          OVR_229::800a290c(j)  
     9::800a2060 08 00 e0 03     jr         ra
     9::800a2064 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2068()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2068                           XREF[9]:     OVR_229::800a1f94(c), 
                                                                                          OVR_229::800a1fa8(c), 
                                                                                          OVR_229::800a1fbc(c), 
                                                                                          OVR_229::800a1fd0(c), 
                                                                                          OVR_229::800a1fe4(c), 
                                                                                          OVR_229::800a1ff8(c), 
                                                                                          OVR_229::800a200c(c), 
                                                                                          OVR_229::800a2020(c), 
                                                                                          OVR_229::800a2034(c)  
     9::800a2068 23 58 6d 01     subu       t3,t3,t5
     9::800a206c 02 00 61 05     bgez       t3,LAB_OVR_229__800a2078
     9::800a2070 23 60 8e 01     _subu      t4,t4,t6
     9::800a2074 22 58 0b 00     sub        t3,zero,t3
                             LAB_OVR_229__800a2078                           XREF[1]:     OVR_229::800a206c(j)  
     9::800a2078 02 00 81 05     bgez       t4,LAB_OVR_229__800a2084
     9::800a207c 00 00 00 00     _nop
     9::800a2080 22 60 0c 00     sub        t4,zero,t4
                             LAB_OVR_229__800a2084                           XREF[1]:     OVR_229::800a2078(j)  
     9::800a2084 23 40 6c 01     subu       t0,t3,t4
     9::800a2088 03 00 01 05     bgez       t0,LAB_OVR_229__800a2098
     9::800a208c 83 40 0c 00     _sra       t0,t4,0x2
     9::800a2090 83 40 0b 00     sra        t0,t3,0x2
     9::800a2094 21 58 80 01     move       t3,t4
                             LAB_OVR_229__800a2098                           XREF[1]:     OVR_229::800a2088(j)  
     9::800a2098 21 58 68 01     addu       t3,t3,t0
     9::800a209c 00 f4 6b 25     addiu      t3,t3,-0xc00
     9::800a20a0 0b 00 61 05     bgez       t3,LAB_OVR_229__800a20d0
     9::800a20a4 c0 40 0b 00     _sll       t0,t3,0x3
     9::800a20a8 00 10 08 25     addiu      t0,t0,0x1000
     9::800a20ac 06 00 00 05     bltz       t0,LAB_OVR_229__800a20c8
     9::800a20b0 00 30 8f 48     _gte_ldRGB t7
     9::800a20b4 00 40 88 48     gte_ldIR0  t0
     9::800a20b8 00 00 00        nDPCS
                 00 00 00 
                 00 00 10 
     9::800a20c4 00 b0 0f 48     gte_stRGB2 t7
                             LAB_OVR_229__800a20c8                           XREF[1]:     OVR_229::800a20ac(j)  
     9::800a20c8 08 00 e0 03     jr         ra
     9::800a20cc 00 00 00 00     _nop
                             LAB_OVR_229__800a20d0                           XREF[1]:     OVR_229::800a20a0(j)  
     9::800a20d0 08 00 e0 03     jr         ra
     9::800a20d4 00 00 0f 24     _li        t7,0x0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a20d8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a20d8                           XREF[4]:     FUN_OVR_229__800a2164:800a21b0(j
                                                                                          FUN_OVR_229__800a2164:800a2248(c
                                                                                          FUN_OVR_229__800a2164:800a2270(c
                                                                                          FUN_OVR_229__800a2164:800a22dc(c
     9::800a20d8 00 00 d3 27     addiu      s3,s8,0x0
     9::800a20dc 50 00 d4 27     addiu      s4,s8,0x50
     9::800a20e0 64 00 d5 27     addiu      s5,s8,0x64
     9::800a20e4 d0 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a20e8 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a20ec()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a20ec                           XREF[6]:     FUN_OVR_229__800a2164:800a21b8(c
                                                                                          FUN_OVR_229__800a2164:800a2258(j
                                                                                          FUN_OVR_229__800a2164:800a2268(c
                                                                                          FUN_OVR_229__800a2164:800a2298(c
                                                                                          FUN_OVR_229__800a2164:800a22b8(c
                                                                                          FUN_OVR_229__800a2164:800a22ec(c
     9::800a20ec 50 00 d3 27     addiu      s3,s8,0x50
     9::800a20f0 14 00 d4 27     addiu      s4,s8,0x14
     9::800a20f4 78 00 d5 27     addiu      s5,s8,0x78
     9::800a20f8 cb 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a20fc 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2100()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2100                           XREF[6]:     FUN_OVR_229__800a2164:800a21e0(c
                                                                                          FUN_OVR_229__800a2164:800a2240(c
                                                                                          FUN_OVR_229__800a2164:800a2280(j
                                                                                          FUN_OVR_229__800a2164:800a2290(c
                                                                                          FUN_OVR_229__800a2164:800a22c0(c
                                                                                          FUN_OVR_229__800a2164:800a22fc(c
     9::800a2100 64 00 d3 27     addiu      s3,s8,0x64
     9::800a2104 78 00 d4 27     addiu      s4,s8,0x78
     9::800a2108 28 00 d5 27     addiu      s5,s8,0x28
     9::800a210c c6 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a2110 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a2114                           XREF[4]:     OVR_229::800a2230(j), 
                                                                                          OVR_229::800a22a8(j), 
                                                                                          OVR_229::800a22d0(j), 
                                                                                          OVR_229::800a2314(j)  
     9::800a2114 78 00 d3 27     addiu      s3,s8,0x78
     9::800a2118 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a211c a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a2120 c1 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a2124 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2128()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2128                           XREF[2]:     FUN_OVR_229__800a2164:800a21d8(c
                                                                                          FUN_OVR_229__800a2164:800a22b0(c
     9::800a2128 64 00 d3 27     addiu      s3,s8,0x64
     9::800a212c 00 00 d4 27     addiu      s4,s8,0x0
     9::800a2130 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2134 bc 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a2138 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a213c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a213c                           XREF[2]:     FUN_OVR_229__800a2164:800a21f0(j
                                                                                          FUN_OVR_229__800a2164:800a2260(c
     9::800a213c 14 00 d3 27     addiu      s3,s8,0x14
     9::800a2140 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a2144 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2148 b7 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a214c a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2150()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2150                           XREF[2]:     FUN_OVR_229__800a2164:800a21c0(c
                                                                                          FUN_OVR_229__800a2164:800a2288(c
     9::800a2150 28 00 d3 27     addiu      s3,s8,0x28
     9::800a2154 00 00 d4 27     addiu      s4,s8,0x0
     9::800a2158 78 00 d5 27     addiu      s5,s8,0x78
     9::800a215c b2 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a2160 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2164()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2164                           XREF[2]:     OVR_229::800a21d0(j), 
                                                                                          OVR_229::800a2238(c)  
     9::800a2164 28 00 d3 27     addiu      s3,s8,0x28
     9::800a2168 78 00 d4 27     addiu      s4,s8,0x78
     9::800a216c 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a2170 ad 00 01 04     bgez       zero,FUN_OVR_229__800a2428
     9::800a2174 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a2178 50 00 d3 27     addiu      s3,s8,0x50
     9::800a217c 14 00 d4 27     addiu      s4,s8,0x14
     9::800a2180 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2184 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a2188 0a 89 02 0c     jal        FUN_OVR_229__800a2428                            undefined FUN_OVR_229__800a2428()
     9::800a218c 0c 00 0a 24     _li        t2,0xc
     9::800a2190 64 00 d3 27     addiu      s3,s8,0x64
     9::800a2194 78 00 d4 27     addiu      s4,s8,0x78
     9::800a2198 28 00 d5 27     addiu      s5,s8,0x28
     9::800a219c 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a21a0 0a 89 02 0c     jal        FUN_OVR_229__800a2428                            undefined FUN_OVR_229__800a2428()
     9::800a21a4 0c 00 0a 24     _li        t2,0xc
     9::800a21a8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a21ac fc ff 39 27     addiu      t9,t9,-0x4
     9::800a21b0 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a20d8
     9::800a21b4 0c 00 0a 24     _li        t2,0xc
     9::800a21b8 3b 88 02 0c     jal        FUN_OVR_229__800a20ec                            undefined FUN_OVR_229__800a20ec()
     9::800a21bc 0c 00 0a 24     _li        t2,0xc
     9::800a21c0 54 88 02 0c     jal        FUN_OVR_229__800a2150                            undefined FUN_OVR_229__800a2150()
     9::800a21c4 0c 00 0a 24     _li        t2,0xc
     9::800a21c8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a21cc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a21d0 e4 ff 01 04     bgez       zero,FUN_OVR_229__800a2164
     9::800a21d4 0c 00 0a 24     _li        t2,0xc
     9::800a21d8 4a 88 02 0c     jal        FUN_OVR_229__800a2128                            undefined FUN_OVR_229__800a2128()
     9::800a21dc 0c 00 0a 24     _li        t2,0xc
     9::800a21e0 40 88 02 0c     jal        FUN_OVR_229__800a2100                            undefined FUN_OVR_229__800a2100()
     9::800a21e4 0c 00 0a 24     _li        t2,0xc
     9::800a21e8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a21ec fc ff 39 27     addiu      t9,t9,-0x4
     9::800a21f0 d2 ff 01 04     bgez       zero,FUN_OVR_229__800a213c
     9::800a21f4 0c 00 0a 24     _li        t2,0xc
     9::800a21f8 00 00 d3 27     addiu      s3,s8,0x0
     9::800a21fc 14 00 d4 27     addiu      s4,s8,0x14
     9::800a2200 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2204 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a2208 0a 89 02 0c     jal        FUN_OVR_229__800a2428                            undefined FUN_OVR_229__800a2428()
     9::800a220c 0c 00 0a 24     _li        t2,0xc
     9::800a2210 00 00 d3 27     addiu      s3,s8,0x0
     9::800a2214 78 00 d4 27     addiu      s4,s8,0x78
     9::800a2218 28 00 d5 27     addiu      s5,s8,0x28
     9::800a221c a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a2220 0a 89 02 0c     jal        FUN_OVR_229__800a2428                            undefined FUN_OVR_229__800a2428()
     9::800a2224 0c 00 0a 24     _li        t2,0xc
     9::800a2228 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a222c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2230 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a2114
     9::800a2234 0c 00 0a 24     _li        t2,0xc
     9::800a2238 59 88 02 0c     jal        FUN_OVR_229__800a2164                            undefined FUN_OVR_229__800a2164()
     9::800a223c 0c 00 0a 24     _li        t2,0xc
     9::800a2240 40 88 02 0c     jal        FUN_OVR_229__800a2100                            undefined FUN_OVR_229__800a2100()
     9::800a2244 04 00 0a 24     _li        t2,0x4
     9::800a2248 36 88 02 0c     jal        FUN_OVR_229__800a20d8                            undefined FUN_OVR_229__800a20d8()
     9::800a224c 0c 00 0a 24     _li        t2,0xc
     9::800a2250 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a2254 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2258 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a20ec
     9::800a225c 0c 00 0a 24     _li        t2,0xc
     9::800a2260 4f 88 02 0c     jal        FUN_OVR_229__800a213c                            undefined FUN_OVR_229__800a213c()
     9::800a2264 0c 00 0a 24     _li        t2,0xc
     9::800a2268 3b 88 02 0c     jal        FUN_OVR_229__800a20ec                            undefined FUN_OVR_229__800a20ec()
     9::800a226c 04 00 0a 24     _li        t2,0x4
     9::800a2270 36 88 02 0c     jal        FUN_OVR_229__800a20d8                            undefined FUN_OVR_229__800a20d8()
     9::800a2274 0c 00 0a 24     _li        t2,0xc
     9::800a2278 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a227c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2280 9f ff 01 04     bgez       zero,FUN_OVR_229__800a2100
     9::800a2284 0c 00 0a 24     _li        t2,0xc
     9::800a2288 54 88 02 0c     jal        FUN_OVR_229__800a2150                            undefined FUN_OVR_229__800a2150()
     9::800a228c 0c 00 0a 24     _li        t2,0xc
     9::800a2290 40 88 02 0c     jal        FUN_OVR_229__800a2100                            undefined FUN_OVR_229__800a2100()
     9::800a2294 08 00 0a 24     _li        t2,0x8
     9::800a2298 3b 88 02 0c     jal        FUN_OVR_229__800a20ec                            undefined FUN_OVR_229__800a20ec()
     9::800a229c 0c 00 0a 24     _li        t2,0xc
     9::800a22a0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a22a4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a22a8 9a ff 01 04     bgez       zero,LAB_OVR_229__800a2114
     9::800a22ac 0c 00 0a 24     _li        t2,0xc
     9::800a22b0 4a 88 02 0c     jal        FUN_OVR_229__800a2128                            undefined FUN_OVR_229__800a2128()
     9::800a22b4 0c 00 0a 24     _li        t2,0xc
     9::800a22b8 3b 88 02 0c     jal        FUN_OVR_229__800a20ec                            undefined FUN_OVR_229__800a20ec()
     9::800a22bc 08 00 0a 24     _li        t2,0x8
     9::800a22c0 40 88 02 0c     jal        FUN_OVR_229__800a2100                            undefined FUN_OVR_229__800a2100()
     9::800a22c4 0c 00 0a 24     _li        t2,0xc
     9::800a22c8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a22cc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a22d0 90 ff 01 04     bgez       zero,LAB_OVR_229__800a2114
     9::800a22d4 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_229__800a22d8                           XREF[1]:     OVR_229::800a204c(j)  
     9::800a22d8 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a22dc 36 88 02 0c     jal        FUN_OVR_229__800a20d8                            undefined FUN_OVR_229__800a20d8()
     9::800a22e0 0c 00 0a 24     _li        t2,0xc
     9::800a22e4 04 00 03 24     li         v1,0x4
     9::800a22e8 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a22ec 3b 88 02 0c     jal        FUN_OVR_229__800a20ec                            undefined FUN_OVR_229__800a20ec()
     9::800a22f0 0c 00 0a 24     _li        t2,0xc
     9::800a22f4 08 00 03 24     li         v1,0x8
     9::800a22f8 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a22fc 40 88 02 0c     jal        FUN_OVR_229__800a2100                            undefined FUN_OVR_229__800a2100()
     9::800a2300 0c 00 0a 24     _li        t2,0xc
     9::800a2304 0c 00 03 24     li         v1,0xc
     9::800a2308 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a230c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a2310 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2314 7f ff 01 04     bgez       zero,LAB_OVR_229__800a2114
     9::800a2318 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a231c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a231c                           XREF[5]:     FUN_OVR_229__800a2428:800a25c8(c
                                                                                          FUN_OVR_229__800a2428:800a25dc(c
                                                                                          FUN_OVR_229__800a2428:800a25f0(c
                                                                                          FUN_OVR_229__800a2428:800a2604(c
                                                                                          FUN_OVR_229__800a2428:800a2618(c
     9::800a231c 00 00 ab 85     lh         t3,0x0(t5)
     9::800a2320 00 00 cc 85     lh         t4,0x0(t6)
     9::800a2324 00 00 eb a5     sh         t3,0x0(t7)
     9::800a2328 21 18 6c 01     addu       v1,t3,t4
     9::800a232c 43 18 03 00     sra        v1,v1,0x1
     9::800a2330 00 00 03 a6     sh         v1,0x0(s0)
     9::800a2334 02 00 ab 85     lh         t3,0x2(t5)
     9::800a2338 02 00 cc 85     lh         t4,0x2(t6)
     9::800a233c 02 00 eb a5     sh         t3,0x2(t7)
     9::800a2340 21 18 6c 01     addu       v1,t3,t4
     9::800a2344 43 18 03 00     sra        v1,v1,0x1
     9::800a2348 02 00 03 a6     sh         v1,0x2(s0)
     9::800a234c 04 00 ab 85     lh         t3,0x4(t5)
     9::800a2350 04 00 cc 85     lh         t4,0x4(t6)
     9::800a2354 04 00 eb a5     sh         t3,0x4(t7)
     9::800a2358 21 18 6c 01     addu       v1,t3,t4
     9::800a235c 43 18 03 00     sra        v1,v1,0x1
     9::800a2360 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a2364 00 08 83 48     gte_ldVZ0  v1
     9::800a2368 04 00 03 a6     sh         v1,0x4(s0)
     9::800a236c 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a2370 01 00 18 4a     RTPS
     9::800a2374 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a2378 08 00 eb a1     sb         t3,0x8(t7)
     9::800a237c 21 18 6c 01     addu       v1,t3,t4
     9::800a2380 43 18 03 00     sra        v1,v1,0x1
     9::800a2384 08 00 03 a2     sb         v1,0x8(s0)
     9::800a2388 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a238c 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a2390 09 00 eb a1     sb         t3,0x9(t7)
     9::800a2394 21 18 6c 01     addu       v1,t3,t4
     9::800a2398 43 18 03 00     sra        v1,v1,0x1
     9::800a239c 09 00 03 a2     sb         v1,0x9(s0)
     9::800a23a0 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a23a4 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a23a8 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a23ac 21 18 6c 01     addu       v1,t3,t4
     9::800a23b0 43 18 03 00     sra        v1,v1,0x1
     9::800a23b4 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a23b8 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a23bc 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a23c0 06 00 eb a1     sb         t3,0x6(t7)
     9::800a23c4 21 18 6c 01     addu       v1,t3,t4
     9::800a23c8 43 18 03 00     sra        v1,v1,0x1
     9::800a23cc 06 00 03 a2     sb         v1,0x6(s0)
     9::800a23d0 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a23d4 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a23d8 07 00 eb a1     sb         t3,0x7(t7)
     9::800a23dc 21 18 6c 01     addu       v1,t3,t4
     9::800a23e0 43 18 03 00     sra        v1,v1,0x1
     9::800a23e4 07 00 03 a2     sb         v1,0x7(s0)
     9::800a23e8 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a23ec 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a23f0 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a23f4 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a23f8 5c 00 2b 8c     lw         t3,0x5c(at)
     9::800a23fc 00 98 03 48     gte_stSZ3  v1
     9::800a2400 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a2404 10 00 03 ae     sw         v1,0x10(s0)
     9::800a2408 23 40 6b 00     subu       t0,v1,t3
     9::800a240c c2 47 08 00     srl        t0,t0,0x1f
     9::800a2410 12 00 08 a2     sb         t0,0x12(s0)
     9::800a2414 40 18 03 00     sll        v1,v1,0x1
     9::800a2418 23 40 6b 00     subu       t0,v1,t3
     9::800a241c c2 47 08 00     srl        t0,t0,0x1f
     9::800a2420 08 00 e0 03     jr         ra
     9::800a2424 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2428()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2428                           XREF[12]:    FUN_OVR_229__800a20d8:800a20e4(j
                                                                                          FUN_OVR_229__800a20ec:800a20f8(j
                                                                                          FUN_OVR_229__800a2100:800a210c(j
                                                                                          FUN_OVR_229__800a2164:800a2120(j
                                                                                          FUN_OVR_229__800a2128:800a2134(j
                                                                                          FUN_OVR_229__800a213c:800a2148(j
                                                                                          FUN_OVR_229__800a2150:800a215c(j
                                                                                          FUN_OVR_229__800a2164:800a2170(j
                                                                                          FUN_OVR_229__800a2164:800a2188(c
                                                                                          FUN_OVR_229__800a2164:800a21a0(c
                                                                                          FUN_OVR_229__800a2164:800a2208(c
                                                                                          FUN_OVR_229__800a2164:800a2220(c
     9::800a2428 13 00 6f 82     lb         t7,0x13(s3)
     9::800a242c 13 00 90 82     lb         s0,0x13(s4)
     9::800a2430 13 00 b1 82     lb         s1,0x13(s5)
     9::800a2434 13 00 d2 82     lb         s2,0x13(s6)
     9::800a2438 24 18 f0 01     and        v1,t7,s0
     9::800a243c 24 18 71 00     and        v1,v1,s1
     9::800a2440 24 18 72 00     and        v1,v1,s2
     9::800a2444 06 ff 60 14     bne        v1,zero,LAB_OVR_229__800a2060
     9::800a2448 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a244c 12 00 90 82     lb         s0,0x12(s4)
     9::800a2450 12 00 b1 82     lb         s1,0x12(s5)
     9::800a2454 12 00 d2 82     lb         s2,0x12(s6)
     9::800a2458 25 78 f0 01     or         t7,t7,s0
     9::800a245c 25 78 f1 01     or         t7,t7,s1
     9::800a2460 25 78 f2 01     or         t7,t7,s2
     9::800a2464 23 00 e0 15     bne        t7,zero,LAB_OVR_229__800a24f4
     9::800a2468 6c 00 28 8c     _lw        t0,0x6c(at)
     9::800a246c 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a2470 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a2474 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a2478 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a247c 23 78 68 01     subu       t7,t3,t0
     9::800a2480 23 80 88 01     subu       s0,t4,t0
     9::800a2484 23 88 a8 01     subu       s1,t5,t0
     9::800a2488 23 90 c8 01     subu       s2,t6,t0
     9::800a248c 24 40 6c 01     and        t0,t3,t4
     9::800a2490 24 40 0d 01     and        t0,t0,t5
     9::800a2494 24 40 0e 01     and        t0,t0,t6
     9::800a2498 25 78 f0 01     or         t7,t7,s0
     9::800a249c 25 78 f1 01     or         t7,t7,s1
     9::800a24a0 27 78 f2 01     nor        t7,t7,s2
     9::800a24a4 25 78 e8 01     or         t7,t7,t0
     9::800a24a8 ed fe e0 05     bltz       t7,LAB_OVR_229__800a2060
     9::800a24ac 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a24b0 eb fe e0 05     bltz       t7,LAB_OVR_229__800a2060
     9::800a24b4 08 00 6f 8e     _lw        t7,0x8(s3)
     9::800a24b8 08 00 90 8e     lw         s0,0x8(s4)
     9::800a24bc 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a24c0 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a24c4 25 40 f0 01     or         t0,t7,s0
     9::800a24c8 25 40 11 01     or         t0,t0,s1
     9::800a24cc 02 00 00 15     bne        t0,zero,LAB_OVR_229__800a24d8
     9::800a24d0 04 00 03 24     _li        v1,0x4
     9::800a24d4 00 00 03 24     li         v1,0x0
                             LAB_OVR_229__800a24d8                           XREF[1]:     OVR_229::800a24cc(j)  
     9::800a24d8 25 40 11 02     or         t0,s0,s1
     9::800a24dc 25 40 12 01     or         t0,t0,s2
     9::800a24e0 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a24ec
     9::800a24e4 00 00 00 00     _nop
     9::800a24e8 08 00 63 34     ori        v1,v1,0x8
                             LAB_OVR_229__800a24ec                           XREF[1]:     OVR_229::800a24e0(j)  
     9::800a24ec 24 50 43 01     and        t2,t2,v1
     9::800a24f0 db fe 40 11     beq        t2,zero,LAB_OVR_229__800a2060
                             LAB_OVR_229__800a24f4                           XREF[1]:     OVR_229::800a2464(j)  
     9::800a24f4 70 00 2a ac     _sw        t2,0x70(at)
     9::800a24f8 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a24fc 24 03 28 24     addiu      t0,at,0x324
     9::800a2500 52 00 1e 11     beq        t0,s8,LAB_OVR_229__800a264c
     9::800a2504 04 00 39 27     _addiu     t9,t9,0x4
     9::800a2508 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a250c 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a2510 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a2514 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a2518 b4 01 23 24     addiu      v1,at,0x1b4
     9::800a251c 16 00 7e 14     bne        v1,s8,LAB_OVR_229__800a2578
     9::800a2520 40 01 03 24     _li        v1,0x140
     9::800a2524 b4 00 c9 8f     lw         t1,0xb4(s8)
     9::800a2528 23 18 6c 01     subu       v1,t3,t4
     9::800a252c 82 48 09 00     srl        t1,t1,0x2
     9::800a2530 21 48 38 01     addu       t1,t1,t8
     9::800a2534 18 00 29 81     lb         t1,0x18(t1)
     9::800a2538 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a2544
     9::800a253c 21 e0 60 01     _move      gp,t3
     9::800a2540 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a2544                           XREF[1]:     OVR_229::800a2538(j)  
     9::800a2544 23 18 8d 03     subu       v1,gp,t5
     9::800a2548 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a2554
     9::800a254c 23 18 8e 03     _subu      v1,gp,t6
     9::800a2550 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a2554                           XREF[1]:     OVR_229::800a2548(j)  
     9::800a2554 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a2560
     9::800a2558 00 00 00 00     _nop
     9::800a255c 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a2560                           XREF[1]:     OVR_229::800a2554(j)  
     9::800a2560 21 18 80 03     move       v1,gp
     9::800a2564 82 e1 1c 00     srl        gp,gp,0x6
     9::800a2568 21 e0 89 03     addu       gp,gp,t1
     9::800a256c 80 e0 1c 00     sll        gp,gp,0x2
     9::800a2570 21 e0 85 03     addu       gp,gp,a1
     9::800a2574 80 02 03 24     li         v1,0x280
                             LAB_OVR_229__800a2578                           XREF[1]:     OVR_229::800a251c(j)  
     9::800a2578 23 88 63 01     subu       s1,t3,v1
     9::800a257c 23 90 83 01     subu       s2,t4,v1
     9::800a2580 23 78 a3 01     subu       t7,t5,v1
     9::800a2584 23 80 c3 01     subu       s0,t6,v1
     9::800a2588 42 8f 11 00     srl        s1,s1,0x1d
     9::800a258c 04 00 31 32     andi       s1,s1,0x4
     9::800a2590 02 97 12 00     srl        s2,s2,0x1c
     9::800a2594 08 00 52 32     andi       s2,s2,0x8
     9::800a2598 25 88 32 02     or         s1,s1,s2
     9::800a259c c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a25a0 10 00 ef 31     andi       t7,t7,0x10
     9::800a25a4 25 88 2f 02     or         s1,s1,t7
     9::800a25a8 82 86 10 00     srl        s0,s0,0x1a
     9::800a25ac 20 00 10 32     andi       s0,s0,0x20
     9::800a25b0 25 88 30 02     or         s1,s1,s0
     9::800a25b4 25 00 20 12     beq        s1,zero,LAB_OVR_229__800a264c
     9::800a25b8 21 68 60 02     _move      t5,s3
     9::800a25bc 21 70 80 02     move       t6,s4
     9::800a25c0 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a25c4 00 00 cf 27     addiu      t7,s8,0x0
     9::800a25c8 c7 88 02 0c     jal        FUN_OVR_229__800a231c                            undefined FUN_OVR_229__800a231c()
     9::800a25cc 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a25d0 21 68 80 02     move       t5,s4
     9::800a25d4 21 70 c0 02     move       t6,s6
     9::800a25d8 14 00 cf 27     addiu      t7,s8,0x14
     9::800a25dc c7 88 02 0c     jal        FUN_OVR_229__800a231c                            undefined FUN_OVR_229__800a231c()
     9::800a25e0 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a25e4 21 68 a0 02     move       t5,s5
     9::800a25e8 21 70 60 02     move       t6,s3
     9::800a25ec 28 00 cf 27     addiu      t7,s8,0x28
     9::800a25f0 c7 88 02 0c     jal        FUN_OVR_229__800a231c                            undefined FUN_OVR_229__800a231c()
     9::800a25f4 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a25f8 21 68 c0 02     move       t5,s6
     9::800a25fc 21 70 a0 02     move       t6,s5
     9::800a2600 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a2604 c7 88 02 0c     jal        FUN_OVR_229__800a231c                            undefined FUN_OVR_229__800a231c()
     9::800a2608 a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a260c 21 68 80 02     move       t5,s4
     9::800a2610 21 70 a0 02     move       t6,s5
     9::800a2614 14 00 cf 27     addiu      t7,s8,0x14
     9::800a2618 c7 88 02 0c     jal        FUN_OVR_229__800a231c                            undefined FUN_OVR_229__800a231c()
     9::800a261c 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a2620 21 18 21 02     addu       v1,s1,at
     9::800a2624 48 01 63 8c     lw         v1,0x148(v1)
     9::800a2628 0a 80 08 3c     lui        t0,0x800a
     9::800a262c 3c 26 08 25     addiu      t0,t0,0x263c
     9::800a2630 3c 00 28 af     sw         t0=>LAB_OVR_229__800a263c,0x3c(t9)
     9::800a2634 08 00 60 00     jr         v1
     9::800a2638 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a263c                           XREF[1]:     FUN_OVR_229__800a2428:800a2630(*
     9::800a263c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a2640 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2644 08 00 e0 03     jr         ra
     9::800a2648 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a264c                           XREF[2]:     OVR_229::800a2500(j), 
                                                                                          OVR_229::800a25b4(j)  
     9::800a264c 70 00 23 8c     lw         v1,0x70(at)
     9::800a2650 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2654 21 18 61 00     addu       v1,v1,at
     9::800a2658 84 01 63 8c     lw         v1,0x184(v1)
     9::800a265c 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a2660 08 00 60 00     jr         v1
     9::800a2664 00 00 00 00     _nop
     9::800a2668 21 98 80 02     move       s3,s4
     9::800a266c 21 a0 c0 02     move       s4,s6
     9::800a2670 13 00 6f 82     lb         t7,0x13(s3)
     9::800a2674 13 00 90 82     lb         s0,0x13(s4)
     9::800a2678 13 00 b1 82     lb         s1,0x13(s5)
     9::800a267c 24 18 f0 01     and        v1,t7,s0
     9::800a2680 24 18 71 00     and        v1,v1,s1
     9::800a2684 76 fe 60 04     bltz       v1,LAB_OVR_229__800a2060
     9::800a2688 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a268c 12 00 90 82     lb         s0,0x12(s4)
     9::800a2690 12 00 b1 82     lb         s1,0x12(s5)
     9::800a2694 25 78 f0 01     or         t7,t7,s0
     9::800a2698 25 78 f1 01     or         t7,t7,s1
     9::800a269c 5a 00 e0 05     bltz       t7,LAB_OVR_229__800a2808
     9::800a26a0 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a26a4 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a26a8 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a26ac 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a26b0 08 00 90 8e     lw         s0,0x8(s4)
     9::800a26b4 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a26b8 06 00 73 86     lh         s3,0x6(s3)
     9::800a26bc 06 00 94 86     lh         s4,0x6(s4)
     9::800a26c0 06 00 b5 86     lh         s5,0x6(s5)
     9::800a26c4 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a26c8 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a26cc a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a26d0 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a26d4 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a26d8 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a26dc 00 36 03 3c     lui        v1,0x3600
     9::800a26e0 25 18 6f 00     or         v1,v1,t7
     9::800a26e4 04 00 43 ac     sw         v1,0x4(v0)
     9::800a26e8 08 00 4b ac     sw         t3,0x8(v0)
     9::800a26ec 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a26f0 10 00 50 ac     sw         s0,0x10(v0)
     9::800a26f4 14 00 4c ac     sw         t4,0x14(v0)
     9::800a26f8 18 00 54 ac     sw         s4,0x18(v0)
     9::800a26fc 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a2700 20 00 4d ac     sw         t5,0x20(v0)
     9::800a2704 24 00 55 ac     sw         s5,0x24(v0)
     9::800a2708 28 00 09 24     li         t1,0x28
     9::800a270c 35 00 01 04     bgez       zero,LAB_OVR_229__800a27e4
     9::800a2710 00 09 0a 3c     _lui       t2,0x900
     9::800a2714 13 00 6f 82     lb         t7,0x13(s3)
     9::800a2718 13 00 90 82     lb         s0,0x13(s4)
     9::800a271c 13 00 b1 82     lb         s1,0x13(s5)
     9::800a2720 13 00 d2 82     lb         s2,0x13(s6)
     9::800a2724 24 18 f0 01     and        v1,t7,s0
     9::800a2728 24 18 71 00     and        v1,v1,s1
     9::800a272c 24 18 72 00     and        v1,v1,s2
     9::800a2730 4b fe 60 14     bne        v1,zero,LAB_OVR_229__800a2060
     9::800a2734 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a2738 12 00 90 82     lb         s0,0x12(s4)
     9::800a273c 12 00 b1 82     lb         s1,0x12(s5)
     9::800a2740 12 00 d2 82     lb         s2,0x12(s6)
     9::800a2744 25 78 f0 01     or         t7,t7,s0
     9::800a2748 25 78 f1 01     or         t7,t7,s1
     9::800a274c 25 78 f2 01     or         t7,t7,s2
     9::800a2750 56 00 e0 15     bne        t7,zero,LAB_OVR_229__800a28ac
     9::800a2754 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a2758 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a275c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a2760 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a2764 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a2768 08 00 90 8e     lw         s0,0x8(s4)
     9::800a276c 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a2770 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a2774 06 00 73 86     lh         s3,0x6(s3)
     9::800a2778 06 00 94 86     lh         s4,0x6(s4)
     9::800a277c 06 00 b5 86     lh         s5,0x6(s5)
     9::800a2780 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a2784 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a2788 06 00 d4 86     lh         s4,0x6(s6)
     9::800a278c a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a2790 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a2794 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a2798 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a279c a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a27a0 00 3e 03 3c     lui        v1,0x3e00
     9::800a27a4 25 18 6f 00     or         v1,v1,t7
     9::800a27a8 04 00 43 ac     sw         v1,0x4(v0)
     9::800a27ac 08 00 4b ac     sw         t3,0x8(v0)
     9::800a27b0 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a27b4 10 00 50 ac     sw         s0,0x10(v0)
     9::800a27b8 14 00 4c ac     sw         t4,0x14(v0)
     9::800a27bc 18 00 54 ac     sw         s4,0x18(v0)
     9::800a27c0 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a27c4 20 00 4d ac     sw         t5,0x20(v0)
     9::800a27c8 24 00 55 ac     sw         s5,0x24(v0)
     9::800a27cc 28 00 52 ac     sw         s2,0x28(v0)
     9::800a27d0 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a27d4 02 1c 15 00     srl        v1,s5,0x10
     9::800a27d8 30 00 43 ac     sw         v1,0x30(v0)
     9::800a27dc 34 00 09 24     li         t1,0x34
     9::800a27e0 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a27e4                           XREF[1]:     OVR_229::800a270c(j)  
     9::800a27e4 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a27e8 00 42 02 00     sll        t0,v0,0x8
     9::800a27ec 02 42 08 00     srl        t0,t0,0x8
     9::800a27f0 25 18 6a 00     or         v1,v1,t2
     9::800a27f4 00 00 43 ac     sw         v1,0x0(v0)
     9::800a27f8 21 10 49 00     addu       v0,v0,t1
     9::800a27fc 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a2800 08 00 e0 03     jr         ra
     9::800a2804 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_229__800a2808                           XREF[1]:     OVR_229::800a269c(j)  
     9::800a2808 58 00 3f ac     sw         ra,0x58(at)
     9::800a280c 98 01 2f 84     lh         t7,0x198(at)
     9::800a2810 9a 01 30 84     lh         s0,0x19a(at)
     9::800a2814 9c 01 31 84     lh         s1,0x19c(at)
     9::800a2818 00 00 63 86     lh         v1,0x0(s3)
     9::800a281c 02 00 68 86     lh         t0,0x2(s3)
     9::800a2820 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a2824 04 00 69 86     _lh        t1,0x4(s3)
     9::800a2828 0b 00 40 05     bltz       t2,LAB_OVR_229__800a2858
     9::800a282c 00 00 83 86     _lh        v1,0x0(s4)
     9::800a2830 02 00 88 86     lh         t0,0x2(s4)
     9::800a2834 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a2838 04 00 89 86     _lh        t1,0x4(s4)
     9::800a283c 06 00 40 05     bltz       t2,LAB_OVR_229__800a2858
     9::800a2840 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a2844 02 00 a8 86     lh         t0,0x2(s5)
     9::800a2848 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a284c 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a2850 58 00 3f 8c     lw         ra,0x58(at)
     9::800a2854 02 fe 41 05     bgez       t2,LAB_OVR_229__800a2060
                             LAB_OVR_229__800a2858                           XREF[2]:     OVR_229::800a2828(j), 
                                                                                          OVR_229::800a283c(j)  
     9::800a2858 10 00 2f 8c     lw         t7,0x10(at)
     9::800a285c 00 80 03 3c     lui        v1,0x8000
     9::800a2860 a6 01 28 84     lh         t0,0x1a6(at)
     9::800a2864 a2 01 29 84     lh         t1,0x1a2(at)
     9::800a2868 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a286c 00 00 e3 ad     sw         v1=>DAT_80000000,0x0(t7)                         = ??
     9::800a2870 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a2874 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a2878 21 68 60 02     move       t5,s3
     9::800a287c 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a2880 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a2884 21 68 80 02     move       t5,s4
     9::800a2888 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a288c 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a2890 21 68 a0 02     move       t5,s5
     9::800a2894 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a2898 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a289c 58 00 3f 8c     lw         ra,0x58(at)
     9::800a28a0 30 00 ef 25     addiu      t7,t7,0x30
     9::800a28a4 08 00 e0 03     jr         ra
     9::800a28a8 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_229__800a28ac                           XREF[1]:     OVR_229::800a2750(j)  
     9::800a28ac 58 00 3f ac     sw         ra,0x58(at)
     9::800a28b0 98 01 2f 84     lh         t7,0x198(at)
     9::800a28b4 9a 01 30 84     lh         s0,0x19a(at)
     9::800a28b8 9c 01 31 84     lh         s1,0x19c(at)
     9::800a28bc 00 00 63 86     lh         v1,0x0(s3)
     9::800a28c0 02 00 68 86     lh         t0,0x2(s3)
     9::800a28c4 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a28c8 04 00 69 86     _lh        t1,0x4(s3)
     9::800a28cc 10 00 40 05     bltz       t2,LAB_OVR_229__800a2910
     9::800a28d0 00 00 83 86     _lh        v1,0x0(s4)
     9::800a28d4 02 00 88 86     lh         t0,0x2(s4)
     9::800a28d8 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a28dc 04 00 89 86     _lh        t1,0x4(s4)
     9::800a28e0 0b 00 40 05     bltz       t2,LAB_OVR_229__800a2910
     9::800a28e4 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a28e8 02 00 a8 86     lh         t0,0x2(s5)
     9::800a28ec 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a28f0 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a28f4 06 00 40 05     bltz       t2,LAB_OVR_229__800a2910
     9::800a28f8 00 00 c3 86     _lh        v1,0x0(s6)
     9::800a28fc 02 00 c8 86     lh         t0,0x2(s6)
     9::800a2900 5d 8a 02 0c     jal        FUN_OVR_229__800a2974                            undefined FUN_OVR_229__800a2974()
     9::800a2904 04 00 c9 86     _lh        t1,0x4(s6)
     9::800a2908 58 00 3f 8c     lw         ra,0x58(at)
     9::800a290c d4 fd 41 05     bgez       t2,LAB_OVR_229__800a2060
                             LAB_OVR_229__800a2910                           XREF[3]:     OVR_229::800a28cc(j), 
                                                                                          OVR_229::800a28e0(j), 
                                                                                          OVR_229::800a28f4(j)  
     9::800a2910 10 00 2f 8c     lw         t7,0x10(at)
     9::800a2914 00 80 03 3c     lui        v1,0x8000
     9::800a2918 01 00 63 34     ori        v1,v1,0x1
     9::800a291c a6 01 28 84     lh         t0,0x1a6(at)
     9::800a2920 a2 01 29 84     lh         t1,0x1a2(at)
     9::800a2924 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a2928 00 00 e3 ad     sw         v1=>DAT_80000000+1,0x0(t7)
     9::800a292c 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a2930 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a2934 21 68 60 02     move       t5,s3
     9::800a2938 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a293c 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a2940 21 68 80 02     move       t5,s4
     9::800a2944 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a2948 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a294c 21 68 a0 02     move       t5,s5
     9::800a2950 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a2954 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a2958 21 68 c0 02     move       t5,s6
     9::800a295c 6d 8a 02 0c     jal        FUN_OVR_229__800a29b4                            undefined FUN_OVR_229__800a29b4()
     9::800a2960 30 00 f0 25     _addiu     s0,t7,0x30
     9::800a2964 58 00 3f 8c     lw         ra,0x58(at)
     9::800a2968 3c 00 ef 25     addiu      t7,t7,0x3c
     9::800a296c 08 00 e0 03     jr         ra
     9::800a2970 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2974()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2974                           XREF[7]:     OVR_229::800a2820(c), 
                                                                                          OVR_229::800a2834(c), 
                                                                                          OVR_229::800a2848(c), 
                                                                                          OVR_229::800a28c4(c), 
                                                                                          OVR_229::800a28d8(c), 
                                                                                          OVR_229::800a28ec(c), 
                                                                                          OVR_229::800a2900(c)  
     9::800a2974 23 18 6f 00     subu       v1,v1,t7
     9::800a2978 02 00 61 04     bgez       v1,LAB_OVR_229__800a2984
     9::800a297c 23 40 10 01     _subu      t0,t0,s0
     9::800a2980 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_229__800a2984                           XREF[1]:     OVR_229::800a2978(j)  
     9::800a2984 00 ff 6b 24     addiu      t3,v1,-0x100
     9::800a2988 02 00 01 05     bgez       t0,LAB_OVR_229__800a2994
     9::800a298c 23 48 31 01     _subu      t1,t1,s1
     9::800a2990 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_229__800a2994                           XREF[1]:     OVR_229::800a2988(j)  
     9::800a2994 80 fe 0c 25     addiu      t4,t0,-0x180
     9::800a2998 02 00 21 05     bgez       t1,LAB_OVR_229__800a29a4
     9::800a299c 00 00 00 00     _nop
     9::800a29a0 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_229__800a29a4                           XREF[1]:     OVR_229::800a2998(j)  
     9::800a29a4 00 ff 2d 25     addiu      t5,t1,-0x100
     9::800a29a8 24 58 6c 01     and        t3,t3,t4
     9::800a29ac 08 00 e0 03     jr         ra
     9::800a29b0 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a29b4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a29b4                           XREF[7]:     OVR_229::800a287c(c), 
                                                                                          OVR_229::800a2888(c), 
                                                                                          OVR_229::800a2894(c), 
                                                                                          OVR_229::800a2938(c), 
                                                                                          OVR_229::800a2944(c), 
                                                                                          OVR_229::800a2950(c), 
                                                                                          OVR_229::800a295c(c)  
     9::800a29b4 13 00 a3 81     lb         v1,0x13(t5)
     9::800a29b8 00 00 a8 8d     lw         t0,0x0(t5)
     9::800a29bc 04 00 a9 8d     lw         t1,0x4(t5)
     9::800a29c0 08 00 aa 8d     lw         t2,0x8(t5)
     9::800a29c4 00 1e 03 00     sll        v1,v1,0x18
     9::800a29c8 25 50 43 01     or         t2,t2,v1
     9::800a29cc 00 00 08 ae     sw         t0,0x0(s0)
     9::800a29d0 04 00 09 ae     sw         t1,0x4(s0)
     9::800a29d4 08 00 e0 03     jr         ra
     9::800a29d8 08 00 0a ae     _sw        t2,0x8(s0)
     9::800a29dc 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_229__800a29e0                           XREF[1]:     OVR_229::800a2e94(j)  
     9::800a29e0 34 01 80 10     beq        a0,zero,LAB_OVR_229__800a2eb4
     9::800a29e4 00 00 00 00     _nop
     9::800a29e8 1c 00 78 8c     lw         t8,0x1c(v1)
     9::800a29ec 18 00 79 8c     lw         t9,0x18(v1)
     9::800a29f0 c8 00 2a 8c     lw         t2,0xc8(at)
     9::800a29f4 3c 00 08 97     lhu        t0,0x3c(t8)
     9::800a29f8 68 00 39 ac     sw         t9,0x68(at)
     9::800a29fc c2 48 08 00     srl        t1,t0,0x3
     9::800a2a00 fc 01 29 31     andi       t1,t1,0x1fc
     9::800a2a04 21 48 2a 01     addu       t1,t1,t2
     9::800a2a08 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a2a0c 00 00 29 8d     lw         t1,0x0(t1)
     9::800a2a10 1f 00 08 31     andi       t0,t0,0x1f
     9::800a2a14 bc 00 28 ac     sw         t0,0xbc(at)
     9::800a2a18 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_229__800a2a1c                           XREF[1]:     OVR_229::800a2e88(j)  
     9::800a2a1c 30 00 23 8c     lw         v1,0x30(at)
     9::800a2a20 40 37 48 24     addiu      t0,v0,0x3740
     9::800a2a24 23 18 68 00     subu       v1,v1,t0
     9::800a2a28 80 f9 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a2a2c bc 00 23 8c     _lw        v1,0xbc(at)
     9::800a2a30 c4 00 28 8c     lw         t0,0xc4(at)
     9::800a2a34 06 00 61 04     bgez       v1,LAB_OVR_229__800a2a50
     9::800a2a38 c0 00 29 8c     _lw        t1,0xc0(at)
     9::800a2a3c 1f 00 03 24     li         v1,0x1f
     9::800a2a40 04 00 28 8d     lw         t0,0x4(t1)
     9::800a2a44 04 00 29 25     addiu      t1,t1,0x4
     9::800a2a48 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a2a4c c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_229__800a2a50                           XREF[1]:     OVR_229::800a2a34(j)  
     9::800a2a50 04 40 68 00     sllv       t0,t0,v1
     9::800a2a54 ff ff 63 24     addiu      v1,v1,-0x1
     9::800a2a58 08 01 01 05     bgez       t0,LAB_OVR_229__800a2e7c
     9::800a2a5c bc 00 23 ac     _sw        v1,0xbc(at)
     9::800a2a60 b4 01 3e 24     addiu      s8,at,0x1b4
     9::800a2a64 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a2a68 00 00 14 8f     lw         s4,0x0(t8)
     9::800a2a6c 04 00 16 8f     lw         s6,0x4(t8)
     9::800a2a70 ff ff 93 32     andi       s3,s4,0xffff
     9::800a2a74 00 99 13 00     sll        s3,s3,0x4
     9::800a2a78 21 98 77 02     addu       s3,s3,s7
     9::800a2a7c 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a2a84 02 a4 14 00     srl        s4,s4,0x10
     9::800a2a88 00 a1 14 00     sll        s4,s4,0x4
     9::800a2a8c 21 a0 97 02     addu       s4,s4,s7
     9::800a2a90 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a2a98 ff ff d5 32     andi       s5,s6,0xffff
     9::800a2a9c 00 a9 15 00     sll        s5,s5,0x4
     9::800a2aa0 21 a8 b7 02     addu       s5,s5,s7
     9::800a2aa4 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a2aac 02 b4 16 00     srl        s6,s6,0x10
     9::800a2ab0 00 b1 16 00     sll        s6,s6,0x4
     9::800a2ab4 30 00 28 4a     RTPT
     9::800a2ab8 21 b0 d7 02     addu       s6,s6,s7
     9::800a2abc 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a2ac0 08 00 90 8e     lw         s0,0x8(s4)
     9::800a2ac4 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a2ac8 08 00 cf af     sw         t7,0x8(s8)
     9::800a2acc 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a2ad0 30 00 d1 af     sw         s1,0x30(s8)
     9::800a2ad4 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a2ad8 00 f8 43 48     gte_stFLAG v1
     9::800a2adc 10 00 d1 eb     gte_stSZ1  0x10(s8)
     9::800a2ae0 80 1b 03 00     sll        v1,v1,0xe
     9::800a2ae4 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a2ae8 ec 00 60 14     bne        v1,zero,LAB_OVR_229__800a2e9c
     9::800a2aec 08 00 14 8f     _lw        s4,0x8(t8)
     9::800a2af0 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a2af4 24 00 d2 eb     gte_stSZ2  0x24(s8)
     9::800a2af8 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a2afc 38 00 d3 eb     gte_stSZ3  0x38(s8)
     9::800a2b00 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a2b04 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a2b08 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a2b0c 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a2b10 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a2b14 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a2b18 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a2b20 14 00 09 8f     lw         t1,0x14(t8)
     9::800a2b24 ff ff 93 32     andi       s3,s4,0xffff
     9::800a2b28 00 99 13 00     sll        s3,s3,0x4
     9::800a2b2c 21 98 77 02     addu       s3,s3,s7
     9::800a2b30 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a2b38 02 a4 14 00     srl        s4,s4,0x10
     9::800a2b3c 00 a1 14 00     sll        s4,s4,0x4
     9::800a2b40 21 a0 97 02     addu       s4,s4,s7
     9::800a2b44 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a2b4c 21 c8 20 00     move       t9,at
     9::800a2b50 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a2b54 30 00 28 4a     RTPT
     9::800a2b58 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a2b5c 08 00 70 8e     lw         s0,0x8(s3)
     9::800a2b60 08 00 91 8e     lw         s1,0x8(s4)
     9::800a2b64 44 00 cf af     sw         t7,0x44(s8)
     9::800a2b68 58 00 d0 af     sw         s0,0x58(s8)
     9::800a2b6c 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a2b70 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a2b74 00 f8 43 48     gte_stFLAG v1
     9::800a2b78 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     9::800a2b7c 80 1b 03 00     sll        v1,v1,0xe
     9::800a2b80 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a2b84 c5 00 60 14     bne        v1,zero,LAB_OVR_229__800a2e9c
     9::800a2b88 5c 00 cd eb     _gte_stS   0x5c(s8)
     9::800a2b8c 60 00 d2 eb     gte_stSZ2  0x60(s8)
     9::800a2b90 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a2b94 74 00 d3 eb     gte_stSZ3  0x74(s8)
     9::800a2b98 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a2b9c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a2ba0 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a2ba4 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a2ba8 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a2bac 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a2bb0 40 00 03 8f     lw         v1,0x40(t8)
     9::800a2bb4 00 00 d3 27     addiu      s3,s8,0x0
     9::800a2bb8 14 00 d4 27     addiu      s4,s8,0x14
     9::800a2bbc 28 00 d5 27     addiu      s5,s8,0x28
     9::800a2bc0 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a2bc4 00 00 68 8c     lw         t0,0x0(v1)
     9::800a2bc8 04 00 69 8c     lw         t1,0x4(v1)
     9::800a2bcc 08 00 6a 8c     lw         t2,0x8(v1)
     9::800a2bd0 94 01 20 ac     sw         zero,0x194(at)
     9::800a2bd4 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a2bd8 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a2bdc a8 01 2a ac     sw         t2,0x1a8(at)
     9::800a2be0 06 00 68 a6     sh         t0,0x6(s3)
     9::800a2be4 06 00 89 a6     sh         t1,0x6(s4)
     9::800a2be8 06 00 aa a6     sh         t2,0x6(s5)
     9::800a2bec 02 54 0a 00     srl        t2,t2,0x10
     9::800a2bf0 06 00 ca a6     sh         t2,0x6(s6)
     9::800a2bf4 10 00 cb 8f     lw         t3,0x10(s8)
     9::800a2bf8 24 00 cc 8f     lw         t4,0x24(s8)
     9::800a2bfc 38 00 cd 8f     lw         t5,0x38(s8)
     9::800a2c00 4c 00 ce 8f     lw         t6,0x4c(s8)
     9::800a2c04 23 18 6c 01     subu       v1,t3,t4
     9::800a2c08 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a2c14
     9::800a2c0c 21 e0 60 01     _move      gp,t3
     9::800a2c10 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a2c14                           XREF[1]:     OVR_229::800a2c08(j)  
     9::800a2c14 23 18 8d 03     subu       v1,gp,t5
     9::800a2c18 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a2c24
     9::800a2c1c 7c 00 29 80     _lb        t1,0x7c(at)
     9::800a2c20 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a2c24                           XREF[1]:     OVR_229::800a2c18(j)  
     9::800a2c24 23 18 8e 03     subu       v1,gp,t6
     9::800a2c28 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a2c34
     9::800a2c2c 82 e1 1c 00     _srl       gp,gp,0x6
     9::800a2c30 82 e1 0e 00     srl        gp,t6,0x6
                             LAB_OVR_229__800a2c34                           XREF[1]:     OVR_229::800a2c28(j)  
     9::800a2c34 21 e0 89 03     addu       gp,gp,t1
     9::800a2c38 80 e0 1c 00     sll        gp,gp,0x2
     9::800a2c3c 21 e0 85 03     addu       gp,gp,a1
     9::800a2c40 80 f8 71 25     addiu      s1,t3,-0x780
     9::800a2c44 80 f8 92 25     addiu      s2,t4,-0x780
     9::800a2c48 80 f8 af 25     addiu      t7,t5,-0x780
     9::800a2c4c 80 f8 d0 25     addiu      s0,t6,-0x780
     9::800a2c50 42 8f 11 00     srl        s1,s1,0x1d
     9::800a2c54 04 00 31 32     andi       s1,s1,0x4
     9::800a2c58 02 97 12 00     srl        s2,s2,0x1c
     9::800a2c5c 08 00 52 32     andi       s2,s2,0x8
     9::800a2c60 25 88 32 02     or         s1,s1,s2
     9::800a2c64 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a2c68 10 00 ef 31     andi       t7,t7,0x10
     9::800a2c6c 25 88 2f 02     or         s1,s1,t7
     9::800a2c70 82 86 10 00     srl        s0,s0,0x1a
     9::800a2c74 20 00 10 32     andi       s0,s0,0x20
     9::800a2c78 25 88 30 02     or         s1,s1,s0
     9::800a2c7c 55 00 20 12     beq        s1,zero,LAB_OVR_229__800a2dd4
     9::800a2c80 21 c8 20 00     _move      t9,at
     9::800a2c84 21 58 21 02     addu       t3,s1,at
     9::800a2c88 48 01 6b 8d     lw         t3,0x148(t3)
     9::800a2c8c 0c 00 14 8f     lw         s4,0xc(t8)
     9::800a2c90 10 00 15 97     lhu        s5,0x10(t8)
     9::800a2c94 ff ff 93 32     andi       s3,s4,0xffff
     9::800a2c98 00 99 13 00     sll        s3,s3,0x4
     9::800a2c9c 21 98 77 02     addu       s3,s3,s7
     9::800a2ca0 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a2ca8 02 a4 14 00     srl        s4,s4,0x10
     9::800a2cac 00 a1 14 00     sll        s4,s4,0x4
     9::800a2cb0 21 a0 97 02     addu       s4,s4,s7
     9::800a2cb4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a2cbc 00 a9 15 00     sll        s5,s5,0x4
     9::800a2cc0 21 a8 b7 02     addu       s5,s5,s7
     9::800a2cc4 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a2ccc 0a 80 03 3c     lui        v1,0x800a
     9::800a2cd0 7c 2e 63 24     addiu      v1,v1,0x2e7c
     9::800a2cd4 30 00 28 4a     RTPT
     9::800a2cd8 3c 00 23 af     sw         v1=>LAB_OVR_229__800a2e7c,0x3c(t9)
     9::800a2cdc 04 00 39 27     addiu      t9,t9,0x4
     9::800a2ce0 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a2ce4 08 00 90 8e     lw         s0,0x8(s4)
     9::800a2ce8 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a2cec 80 00 cf af     sw         t7,0x80(s8)
     9::800a2cf0 94 00 d0 af     sw         s0,0x94(s8)
     9::800a2cf4 a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a2cf8 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a2cfc 00 f8 43 48     gte_stFLAG v1
     9::800a2d00 88 00 d1 eb     gte_stSZ1  0x88(s8)
     9::800a2d04 80 1b 03 00     sll        v1,v1,0xe
     9::800a2d08 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a2d0c 63 00 60 14     bne        v1,zero,LAB_OVR_229__800a2e9c
     9::800a2d10 98 00 cd eb     _gte_stS   0x98(s8)
     9::800a2d14 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     9::800a2d18 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a2d1c b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     9::800a2d20 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a2d24 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a2d28 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a2d2c 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a2d30 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a2d34 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a2d38 06 00 c3 93     lbu        v1,0x6(s8)
     9::800a2d3c 1a 00 c8 93     lbu        t0,0x1a(s8)
     9::800a2d40 2e 00 c9 93     lbu        t1,0x2e(s8)
     9::800a2d44 42 00 ca 93     lbu        t2,0x42(s8)
     9::800a2d48 21 78 68 00     addu       t7,v1,t0
     9::800a2d4c 21 80 69 00     addu       s0,v1,t1
     9::800a2d50 21 88 09 01     addu       s1,t0,t1
     9::800a2d54 21 90 0a 01     addu       s2,t0,t2
     9::800a2d58 21 18 2a 01     addu       v1,t1,t2
     9::800a2d5c 43 78 0f 00     sra        t7,t7,0x1
     9::800a2d60 43 80 10 00     sra        s0,s0,0x1
     9::800a2d64 43 88 11 00     sra        s1,s1,0x1
     9::800a2d68 43 90 12 00     sra        s2,s2,0x1
     9::800a2d6c 43 18 03 00     sra        v1,v1,0x1
     9::800a2d70 56 00 cf a3     sb         t7,0x56(s8)
     9::800a2d74 6a 00 d0 a3     sb         s0,0x6a(s8)
     9::800a2d78 7e 00 d1 a3     sb         s1,0x7e(s8)
     9::800a2d7c 92 00 d2 a3     sb         s2,0x92(s8)
     9::800a2d80 a6 00 c3 a3     sb         v1,0xa6(s8)
     9::800a2d84 07 00 c3 93     lbu        v1,0x7(s8)
     9::800a2d88 1b 00 c8 93     lbu        t0,0x1b(s8)
     9::800a2d8c 2f 00 c9 93     lbu        t1,0x2f(s8)
     9::800a2d90 43 00 ca 93     lbu        t2,0x43(s8)
     9::800a2d94 21 78 68 00     addu       t7,v1,t0
     9::800a2d98 21 80 69 00     addu       s0,v1,t1
     9::800a2d9c 21 88 09 01     addu       s1,t0,t1
     9::800a2da0 21 90 0a 01     addu       s2,t0,t2
     9::800a2da4 21 18 2a 01     addu       v1,t1,t2
     9::800a2da8 43 78 0f 00     sra        t7,t7,0x1
     9::800a2dac 43 80 10 00     sra        s0,s0,0x1
     9::800a2db0 43 88 11 00     sra        s1,s1,0x1
     9::800a2db4 43 90 12 00     sra        s2,s2,0x1
     9::800a2db8 43 18 03 00     sra        v1,v1,0x1
     9::800a2dbc 57 00 cf a3     sb         t7,0x57(s8)
     9::800a2dc0 6b 00 d0 a3     sb         s0,0x6b(s8)
     9::800a2dc4 7f 00 d1 a3     sb         s1,0x7f(s8)
     9::800a2dc8 93 00 d2 a3     sb         s2,0x93(s8)
     9::800a2dcc 08 00 60 01     jr         t3
     9::800a2dd0 a7 00 c3 a3     _sb        v1,0xa7(s8)
                             LAB_OVR_229__800a2dd4                           XREF[1]:     OVR_229::800a2c7c(j)  
     9::800a2dd4 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a2dd8 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a2ddc 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a2de0 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a2de4 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a2de8 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a2dec 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a2df0 06 00 40 4b     NCLIP
     9::800a2df4 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a2df8 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a2dfc 23 78 68 01     subu       t7,t3,t0
     9::800a2e00 23 80 88 01     subu       s0,t4,t0
     9::800a2e04 23 88 a8 01     subu       s1,t5,t0
     9::800a2e08 23 90 c8 01     subu       s2,t6,t0
     9::800a2e0c 00 c0 08 48     gte_stMAC0 t0
     9::800a2e10 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a2e14 22 40 08 00     sub        t0,zero,t0
     9::800a2e18 25 40 09 01     or         t0,t0,t1
     9::800a2e1c 06 00 40 4b     NCLIP
     9::800a2e20 24 18 6c 01     and        v1,t3,t4
     9::800a2e24 24 18 6d 00     and        v1,v1,t5
     9::800a2e28 24 18 6e 00     and        v1,v1,t6
     9::800a2e2c 25 78 f0 01     or         t7,t7,s0
     9::800a2e30 25 78 f1 01     or         t7,t7,s1
     9::800a2e34 27 78 f2 01     nor        t7,t7,s2
     9::800a2e38 25 78 e3 01     or         t7,t7,v1
     9::800a2e3c 0f 00 e0 05     bltz       t7,LAB_OVR_229__800a2e7c
     9::800a2e40 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a2e44 0d 00 e0 05     bltz       t7,LAB_OVR_229__800a2e7c
     9::800a2e48 00 c0 03 48     _gte_stM   v1
     9::800a2e4c c2 47 08 00     srl        t0,t0,0x1f
     9::800a2e50 80 40 08 00     sll        t0,t0,0x2
     9::800a2e54 25 18 69 00     or         v1,v1,t1
     9::800a2e58 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a2e5c c0 18 03 00     sll        v1,v1,0x3
     9::800a2e60 25 18 68 00     or         v1,v1,t0
     9::800a2e64 05 00 60 10     beq        v1,zero,LAB_OVR_229__800a2e7c
     9::800a2e68 21 18 61 00     _addu      v1,v1,at
     9::800a2e6c 84 01 63 8c     lw         v1,0x184(v1)
     9::800a2e70 00 00 00 00     nop
     9::800a2e74 09 f8 60 00     jalr       v1
     9::800a2e78 00 00 00 00     _nop
                             LAB_OVR_229__800a2e7c                           XREF[7]:     OVR_229::800a2a58(j), 
                                                                                          OVR_229::800a2cd8(*), 
                                                                                          OVR_229::800a2e3c(j), 
                                                                                          OVR_229::800a2e44(j), 
                                                                                          OVR_229::800a2e64(j), 
                                                                                          OVR_229::800a2eac(j), 
                                                                                          OVR_229::800a3120(j)  
     9::800a2e7c 68 00 39 8c     lw         t9,0x68(at)
     9::800a2e80 5c 00 18 27     addiu      t8,t8,0x5c
     9::800a2e84 ff ff 39 27     addiu      t9,t9,-0x1
     9::800a2e88 e4 fe 20 1f     bgtz       t9,LAB_OVR_229__800a2a1c
     9::800a2e8c 68 00 39 ac     _sw        t9,0x68(at)
     9::800a2e90 00 00 84 8c     lw         a0,0x0(a0)
     9::800a2e94 d2 fe 01 04     bgez       zero,LAB_OVR_229__800a29e0
     9::800a2e98 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_229__800a2e9c                           XREF[3]:     OVR_229::800a2ae8(j), 
                                                                                          OVR_229::800a2b84(j), 
                                                                                          OVR_229::800a2d0c(j)  
     9::800a2e9c 64 00 28 8c     lw         t0,0x64(at)
     9::800a2ea0 00 00 00 00     nop
     9::800a2ea4 00 00 18 ad     sw         t8,0x0(t0)
     9::800a2ea8 04 00 08 25     addiu      t0,t0,0x4
     9::800a2eac f3 ff 01 04     bgez       zero,LAB_OVR_229__800a2e7c
     9::800a2eb0 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_229__800a2eb4                           XREF[1]:     OVR_229::800a29e0(j)  
     9::800a2eb4 64 00 28 8c     lw         t0,0x64(at)
     9::800a2eb8 ab f8 01 04     bgez       zero,LAB_OVR_229__800a1168
     9::800a2ebc 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_229__800a2ec0                           XREF[6]:     FUN_OVR_229__800a3254:800a32c8(j
                                                                                          FUN_OVR_229__800a3254:800a32d0(j
                                                                                          FUN_OVR_229__800a3254:800a3304(j
                                                                                          OVR_229::800a3414(j), 
                                                                                          OVR_229::800a341c(j), 
                                                                                          OVR_229::800a3448(j)  
     9::800a2ec0 08 00 e0 03     jr         ra
     9::800a2ec4 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2ec8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2ec8                           XREF[4]:     FUN_OVR_229__800a2f54:800a2fa0(j
                                                                                          FUN_OVR_229__800a2f54:800a3038(c
                                                                                          FUN_OVR_229__800a2f54:800a3060(c
                                                                                          FUN_OVR_229__800a2f54:800a312c(c
     9::800a2ec8 00 00 d3 27     addiu      s3,s8,0x0
     9::800a2ecc 50 00 d4 27     addiu      s4,s8,0x50
     9::800a2ed0 64 00 d5 27     addiu      s5,s8,0x64
     9::800a2ed4 df 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2ed8 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2edc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2edc                           XREF[6]:     FUN_OVR_229__800a2f54:800a2fa8(c
                                                                                          FUN_OVR_229__800a2f54:800a3048(j
                                                                                          FUN_OVR_229__800a2f54:800a3058(c
                                                                                          FUN_OVR_229__800a2f54:800a3088(c
                                                                                          FUN_OVR_229__800a2f54:800a30a8(c
                                                                                          FUN_OVR_229__800a2f54:800a313c(c
     9::800a2edc 50 00 d3 27     addiu      s3,s8,0x50
     9::800a2ee0 14 00 d4 27     addiu      s4,s8,0x14
     9::800a2ee4 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2ee8 da 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2eec 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2ef0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2ef0                           XREF[6]:     FUN_OVR_229__800a2f54:800a2fd0(c
                                                                                          FUN_OVR_229__800a2f54:800a3030(c
                                                                                          FUN_OVR_229__800a2f54:800a3070(j
                                                                                          FUN_OVR_229__800a2f54:800a3080(c
                                                                                          FUN_OVR_229__800a2f54:800a30b0(c
                                                                                          FUN_OVR_229__800a2f54:800a314c(c
     9::800a2ef0 64 00 d3 27     addiu      s3,s8,0x64
     9::800a2ef4 78 00 d4 27     addiu      s4,s8,0x78
     9::800a2ef8 28 00 d5 27     addiu      s5,s8,0x28
     9::800a2efc d5 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2f00 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a2f04                           XREF[4]:     OVR_229::800a3020(j), 
                                                                                          OVR_229::800a3098(j), 
                                                                                          OVR_229::800a30c0(j), 
                                                                                          OVR_229::800a3164(j)  
     9::800a2f04 78 00 d3 27     addiu      s3,s8,0x78
     9::800a2f08 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a2f0c a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a2f10 d0 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2f14 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2f18()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2f18                           XREF[2]:     FUN_OVR_229__800a2f54:800a2fc8(c
                                                                                          FUN_OVR_229__800a2f54:800a30a0(c
     9::800a2f18 64 00 d3 27     addiu      s3,s8,0x64
     9::800a2f1c 00 00 d4 27     addiu      s4,s8,0x0
     9::800a2f20 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2f24 cb 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2f28 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2f2c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2f2c                           XREF[2]:     FUN_OVR_229__800a2f54:800a2fe0(j
                                                                                          FUN_OVR_229__800a2f54:800a3050(c
     9::800a2f2c 14 00 d3 27     addiu      s3,s8,0x14
     9::800a2f30 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a2f34 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2f38 c6 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2f3c a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2f40()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2f40                           XREF[2]:     FUN_OVR_229__800a2f54:800a2fb0(c
                                                                                          FUN_OVR_229__800a2f54:800a3078(c
     9::800a2f40 28 00 d3 27     addiu      s3,s8,0x28
     9::800a2f44 00 00 d4 27     addiu      s4,s8,0x0
     9::800a2f48 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2f4c c1 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2f50 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a2f54()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a2f54                           XREF[2]:     OVR_229::800a2fc0(j), 
                                                                                          OVR_229::800a3028(c)  
     9::800a2f54 28 00 d3 27     addiu      s3,s8,0x28
     9::800a2f58 78 00 d4 27     addiu      s4,s8,0x78
     9::800a2f5c 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a2f60 bc 00 01 04     bgez       zero,FUN_OVR_229__800a3254
     9::800a2f64 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a2f68 50 00 d3 27     addiu      s3,s8,0x50
     9::800a2f6c 14 00 d4 27     addiu      s4,s8,0x14
     9::800a2f70 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2f74 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a2f78 95 8c 02 0c     jal        FUN_OVR_229__800a3254                            undefined FUN_OVR_229__800a3254()
     9::800a2f7c 0c 00 0a 24     _li        t2,0xc
     9::800a2f80 64 00 d3 27     addiu      s3,s8,0x64
     9::800a2f84 78 00 d4 27     addiu      s4,s8,0x78
     9::800a2f88 28 00 d5 27     addiu      s5,s8,0x28
     9::800a2f8c 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a2f90 95 8c 02 0c     jal        FUN_OVR_229__800a3254                            undefined FUN_OVR_229__800a3254()
     9::800a2f94 0c 00 0a 24     _li        t2,0xc
     9::800a2f98 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a2f9c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2fa0 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a2ec8
     9::800a2fa4 0c 00 0a 24     _li        t2,0xc
     9::800a2fa8 b7 8b 02 0c     jal        FUN_OVR_229__800a2edc                            undefined FUN_OVR_229__800a2edc()
     9::800a2fac 0c 00 0a 24     _li        t2,0xc
     9::800a2fb0 d0 8b 02 0c     jal        FUN_OVR_229__800a2f40                            undefined FUN_OVR_229__800a2f40()
     9::800a2fb4 0c 00 0a 24     _li        t2,0xc
     9::800a2fb8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a2fbc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2fc0 e4 ff 01 04     bgez       zero,FUN_OVR_229__800a2f54
     9::800a2fc4 0c 00 0a 24     _li        t2,0xc
     9::800a2fc8 c6 8b 02 0c     jal        FUN_OVR_229__800a2f18                            undefined FUN_OVR_229__800a2f18()
     9::800a2fcc 0c 00 0a 24     _li        t2,0xc
     9::800a2fd0 bc 8b 02 0c     jal        FUN_OVR_229__800a2ef0                            undefined FUN_OVR_229__800a2ef0()
     9::800a2fd4 0c 00 0a 24     _li        t2,0xc
     9::800a2fd8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a2fdc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a2fe0 d2 ff 01 04     bgez       zero,FUN_OVR_229__800a2f2c
     9::800a2fe4 0c 00 0a 24     _li        t2,0xc
     9::800a2fe8 00 00 d3 27     addiu      s3,s8,0x0
     9::800a2fec 14 00 d4 27     addiu      s4,s8,0x14
     9::800a2ff0 78 00 d5 27     addiu      s5,s8,0x78
     9::800a2ff4 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a2ff8 95 8c 02 0c     jal        FUN_OVR_229__800a3254                            undefined FUN_OVR_229__800a3254()
     9::800a2ffc 0c 00 0a 24     _li        t2,0xc
     9::800a3000 00 00 d3 27     addiu      s3,s8,0x0
     9::800a3004 78 00 d4 27     addiu      s4,s8,0x78
     9::800a3008 28 00 d5 27     addiu      s5,s8,0x28
     9::800a300c a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a3010 95 8c 02 0c     jal        FUN_OVR_229__800a3254                            undefined FUN_OVR_229__800a3254()
     9::800a3014 0c 00 0a 24     _li        t2,0xc
     9::800a3018 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a301c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3020 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a2f04
     9::800a3024 0c 00 0a 24     _li        t2,0xc
     9::800a3028 d5 8b 02 0c     jal        FUN_OVR_229__800a2f54                            undefined FUN_OVR_229__800a2f54()
     9::800a302c 0c 00 0a 24     _li        t2,0xc
     9::800a3030 bc 8b 02 0c     jal        FUN_OVR_229__800a2ef0                            undefined FUN_OVR_229__800a2ef0()
     9::800a3034 04 00 0a 24     _li        t2,0x4
     9::800a3038 b2 8b 02 0c     jal        FUN_OVR_229__800a2ec8                            undefined FUN_OVR_229__800a2ec8()
     9::800a303c 0c 00 0a 24     _li        t2,0xc
     9::800a3040 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3044 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3048 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a2edc
     9::800a304c 0c 00 0a 24     _li        t2,0xc
     9::800a3050 cb 8b 02 0c     jal        FUN_OVR_229__800a2f2c                            undefined FUN_OVR_229__800a2f2c()
     9::800a3054 0c 00 0a 24     _li        t2,0xc
     9::800a3058 b7 8b 02 0c     jal        FUN_OVR_229__800a2edc                            undefined FUN_OVR_229__800a2edc()
     9::800a305c 04 00 0a 24     _li        t2,0x4
     9::800a3060 b2 8b 02 0c     jal        FUN_OVR_229__800a2ec8                            undefined FUN_OVR_229__800a2ec8()
     9::800a3064 0c 00 0a 24     _li        t2,0xc
     9::800a3068 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a306c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3070 9f ff 01 04     bgez       zero,FUN_OVR_229__800a2ef0
     9::800a3074 0c 00 0a 24     _li        t2,0xc
     9::800a3078 d0 8b 02 0c     jal        FUN_OVR_229__800a2f40                            undefined FUN_OVR_229__800a2f40()
     9::800a307c 0c 00 0a 24     _li        t2,0xc
     9::800a3080 bc 8b 02 0c     jal        FUN_OVR_229__800a2ef0                            undefined FUN_OVR_229__800a2ef0()
     9::800a3084 08 00 0a 24     _li        t2,0x8
     9::800a3088 b7 8b 02 0c     jal        FUN_OVR_229__800a2edc                            undefined FUN_OVR_229__800a2edc()
     9::800a308c 0c 00 0a 24     _li        t2,0xc
     9::800a3090 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3094 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3098 9a ff 01 04     bgez       zero,LAB_OVR_229__800a2f04
     9::800a309c 0c 00 0a 24     _li        t2,0xc
     9::800a30a0 c6 8b 02 0c     jal        FUN_OVR_229__800a2f18                            undefined FUN_OVR_229__800a2f18()
     9::800a30a4 0c 00 0a 24     _li        t2,0xc
     9::800a30a8 b7 8b 02 0c     jal        FUN_OVR_229__800a2edc                            undefined FUN_OVR_229__800a2edc()
     9::800a30ac 08 00 0a 24     _li        t2,0x8
     9::800a30b0 bc 8b 02 0c     jal        FUN_OVR_229__800a2ef0                            undefined FUN_OVR_229__800a2ef0()
     9::800a30b4 0c 00 0a 24     _li        t2,0xc
     9::800a30b8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a30bc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a30c0 90 ff 01 04     bgez       zero,LAB_OVR_229__800a2f04
     9::800a30c4 0c 00 0a 24     _li        t2,0xc
     9::800a30c8 b4 01 23 24     addiu      v1,at,0x1b4
     9::800a30cc 16 00 7e 14     bne        v1,s8,LAB_OVR_229__800a3128
     9::800a30d0 50 00 03 3c     _lui       v1,0x50
     9::800a30d4 78 64 63 34     ori        v1,v1,0x6478
     9::800a30d8 08 00 08 24     li         t0,0x8
     9::800a30dc d0 8c 02 0c     jal        FUN_OVR_229__800a3340                            undefined FUN_OVR_229__800a3340()
     9::800a30e0 00 00 0a 24     _li        t2,0x0
     9::800a30e4 14 50 03 3c     lui        v1,0x5014
     9::800a30e8 8c 78 63 34     ori        v1,v1,0x788c
     9::800a30ec 0d 00 08 24     li         t0,0xd
     9::800a30f0 d0 8c 02 0c     jal        FUN_OVR_229__800a3340                            undefined FUN_OVR_229__800a3340()
     9::800a30f4 04 00 0a 24     _li        t2,0x4
     9::800a30f8 78 64 03 3c     lui        v1,0x6478
     9::800a30fc a0 28 63 34     ori        v1,v1,0x28a0
     9::800a3100 12 00 08 24     li         t0,0x12
     9::800a3104 d0 8c 02 0c     jal        FUN_OVR_229__800a3340                            undefined FUN_OVR_229__800a3340()
     9::800a3108 08 00 0a 24     _li        t2,0x8
     9::800a310c 8c 78 03 3c     lui        v1,0x788c
     9::800a3110 3c a0 63 34     ori        v1,v1,0xa03c
     9::800a3114 17 00 08 24     li         t0,0x17
     9::800a3118 d0 8c 02 0c     jal        FUN_OVR_229__800a3340                            undefined FUN_OVR_229__800a3340()
     9::800a311c 0c 00 0a 24     _li        t2,0xc
     9::800a3120 56 ff 01 04     bgez       zero,LAB_OVR_229__800a2e7c
     9::800a3124 00 00 00 00     _nop
                             LAB_OVR_229__800a3128                           XREF[1]:     OVR_229::800a30cc(j)  
     9::800a3128 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a312c b2 8b 02 0c     jal        FUN_OVR_229__800a2ec8                            undefined FUN_OVR_229__800a2ec8()
     9::800a3130 0c 00 0a 24     _li        t2,0xc
     9::800a3134 04 00 03 24     li         v1,0x4
     9::800a3138 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a313c b7 8b 02 0c     jal        FUN_OVR_229__800a2edc                            undefined FUN_OVR_229__800a2edc()
     9::800a3140 0c 00 0a 24     _li        t2,0xc
     9::800a3144 08 00 03 24     li         v1,0x8
     9::800a3148 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a314c bc 8b 02 0c     jal        FUN_OVR_229__800a2ef0                            undefined FUN_OVR_229__800a2ef0()
     9::800a3150 0c 00 0a 24     _li        t2,0xc
     9::800a3154 0c 00 03 24     li         v1,0xc
     9::800a3158 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a315c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3160 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3164 67 ff 01 04     bgez       zero,LAB_OVR_229__800a2f04
     9::800a3168 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a316c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a316c                           XREF[5]:     FUN_OVR_229__800a3340:800a35c0(c
                                                                                          FUN_OVR_229__800a3340:800a35d4(c
                                                                                          FUN_OVR_229__800a3340:800a35e8(c
                                                                                          FUN_OVR_229__800a3340:800a35fc(c
                                                                                          FUN_OVR_229__800a3340:800a3610(c
     9::800a316c 00 00 ab 85     lh         t3,0x0(t5)
     9::800a3170 00 00 cc 85     lh         t4,0x0(t6)
     9::800a3174 00 00 eb a5     sh         t3,0x0(t7)
     9::800a3178 21 18 6c 01     addu       v1,t3,t4
     9::800a317c 43 18 03 00     sra        v1,v1,0x1
     9::800a3180 00 00 03 a6     sh         v1,0x0(s0)
     9::800a3184 02 00 ab 85     lh         t3,0x2(t5)
     9::800a3188 02 00 cc 85     lh         t4,0x2(t6)
     9::800a318c 02 00 eb a5     sh         t3,0x2(t7)
     9::800a3190 21 18 6c 01     addu       v1,t3,t4
     9::800a3194 43 18 03 00     sra        v1,v1,0x1
     9::800a3198 02 00 03 a6     sh         v1,0x2(s0)
     9::800a319c 04 00 ab 85     lh         t3,0x4(t5)
     9::800a31a0 04 00 cc 85     lh         t4,0x4(t6)
     9::800a31a4 04 00 eb a5     sh         t3,0x4(t7)
     9::800a31a8 21 18 6c 01     addu       v1,t3,t4
     9::800a31ac 43 18 03 00     sra        v1,v1,0x1
     9::800a31b0 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a31b4 00 08 83 48     gte_ldVZ0  v1
     9::800a31b8 04 00 03 a6     sh         v1,0x4(s0)
     9::800a31bc 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a31c0 01 00 18 4a     RTPS
     9::800a31c4 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a31c8 08 00 eb a1     sb         t3,0x8(t7)
     9::800a31cc 21 18 6c 01     addu       v1,t3,t4
     9::800a31d0 43 18 03 00     sra        v1,v1,0x1
     9::800a31d4 08 00 03 a2     sb         v1,0x8(s0)
     9::800a31d8 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a31dc 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a31e0 09 00 eb a1     sb         t3,0x9(t7)
     9::800a31e4 21 18 6c 01     addu       v1,t3,t4
     9::800a31e8 43 18 03 00     sra        v1,v1,0x1
     9::800a31ec 09 00 03 a2     sb         v1,0x9(s0)
     9::800a31f0 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a31f4 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a31f8 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a31fc 21 18 6c 01     addu       v1,t3,t4
     9::800a3200 43 18 03 00     sra        v1,v1,0x1
     9::800a3204 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a3208 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a320c 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a3210 06 00 eb a1     sb         t3,0x6(t7)
     9::800a3214 21 18 6c 01     addu       v1,t3,t4
     9::800a3218 43 18 03 00     sra        v1,v1,0x1
     9::800a321c 06 00 03 a2     sb         v1,0x6(s0)
     9::800a3220 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a3224 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a3228 07 00 eb a1     sb         t3,0x7(t7)
     9::800a322c 21 18 6c 01     addu       v1,t3,t4
     9::800a3230 43 18 03 00     sra        v1,v1,0x1
     9::800a3234 07 00 03 a2     sb         v1,0x7(s0)
     9::800a3238 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a323c 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a3240 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a3244 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a3248 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a324c 08 00 e0 03     jr         ra
     9::800a3250 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3254()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3254                           XREF[12]:    FUN_OVR_229__800a2ec8:800a2ed4(j
                                                                                          FUN_OVR_229__800a2edc:800a2ee8(j
                                                                                          FUN_OVR_229__800a2ef0:800a2efc(j
                                                                                          FUN_OVR_229__800a2f54:800a2f10(j
                                                                                          FUN_OVR_229__800a2f18:800a2f24(j
                                                                                          FUN_OVR_229__800a2f2c:800a2f38(j
                                                                                          FUN_OVR_229__800a2f40:800a2f4c(j
                                                                                          FUN_OVR_229__800a2f54:800a2f60(j
                                                                                          FUN_OVR_229__800a2f54:800a2f78(c
                                                                                          FUN_OVR_229__800a2f54:800a2f90(c
                                                                                          FUN_OVR_229__800a2f54:800a2ff8(c
                                                                                          FUN_OVR_229__800a2f54:800a3010(c
     9::800a3254 70 00 2a ac     sw         t2,0x70(at)
     9::800a3258 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a325c 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a3260 94 01 2a 8c     lw         t2,0x194(at)
     9::800a3264 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a3268 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a326c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a3270 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a3274 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a3278 06 00 40 4b     NCLIP
     9::800a327c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a3280 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a3284 23 78 68 01     subu       t7,t3,t0
     9::800a3288 23 80 88 01     subu       s0,t4,t0
     9::800a328c 23 88 a8 01     subu       s1,t5,t0
     9::800a3290 23 90 c8 01     subu       s2,t6,t0
     9::800a3294 00 c0 08 48     gte_stMAC0 t0
     9::800a3298 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a329c 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a32a8
     9::800a32a0 22 40 08 00     _sub       t0,zero,t0
     9::800a32a4 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a32a8                           XREF[1]:     OVR_229::800a329c(j)  
     9::800a32a8 06 00 40 4b     NCLIP
     9::800a32ac 24 18 6c 01     and        v1,t3,t4
     9::800a32b0 24 18 6d 00     and        v1,v1,t5
     9::800a32b4 24 18 6e 00     and        v1,v1,t6
     9::800a32b8 25 78 f0 01     or         t7,t7,s0
     9::800a32bc 25 78 f1 01     or         t7,t7,s1
     9::800a32c0 27 78 f2 01     nor        t7,t7,s2
     9::800a32c4 25 78 e3 01     or         t7,t7,v1
     9::800a32c8 fd fe e0 05     bltz       t7,LAB_OVR_229__800a2ec0
     9::800a32cc 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a32d0 fb fe e0 05     bltz       t7,LAB_OVR_229__800a2ec0
     9::800a32d4 00 c0 03 48     _gte_stM   v1
     9::800a32d8 25 40 09 01     or         t0,t0,t1
     9::800a32dc 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a32e8
     9::800a32e0 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a32e4 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a32e8                           XREF[1]:     OVR_229::800a32dc(j)  
     9::800a32e8 80 40 08 00     sll        t0,t0,0x2
     9::800a32ec 25 18 69 00     or         v1,v1,t1
     9::800a32f0 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a32f4 c0 18 03 00     sll        v1,v1,0x3
     9::800a32f8 70 00 2a 8c     lw         t2,0x70(at)
     9::800a32fc 25 18 68 00     or         v1,v1,t0
     9::800a3300 24 18 6a 00     and        v1,v1,t2
     9::800a3304 ee fe 60 10     beq        v1,zero,LAB_OVR_229__800a2ec0
     9::800a3308 70 00 23 ac     _sw        v1,0x70(at)
     9::800a330c 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a3310 24 03 28 24     addiu      t0,at,0x324
     9::800a3314 d3 00 1e 11     beq        t0,s8,LAB_OVR_229__800a3664
     9::800a3318 04 00 39 27     _addiu     t9,t9,0x4
     9::800a331c 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a3320 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a3324 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a3328 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a332c c0 fe 71 25     addiu      s1,t3,-0x140
     9::800a3330 c0 fe 92 25     addiu      s2,t4,-0x140
     9::800a3334 c0 fe af 25     addiu      t7,t5,-0x140
     9::800a3338 91 00 01 04     bgez       zero,LAB_OVR_229__800a3580
     9::800a333c c0 fe d0 25     _addiu     s0,t6,-0x140
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3340()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3340                           XREF[4]:     FUN_OVR_229__800a2f54:800a30dc(c
                                                                                          FUN_OVR_229__800a2f54:800a30f0(c
                                                                                          FUN_OVR_229__800a2f54:800a3104(c
                                                                                          FUN_OVR_229__800a2f54:800a3118(c
     9::800a3340 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a3344 b4 00 ca af     sw         t2,0xb4(s8)
     9::800a3348 06 50 09 01     srlv       t2,t1,t0
     9::800a334c 1f 00 4a 31     andi       t2,t2,0x1f
     9::800a3350 80 50 0a 00     sll        t2,t2,0x2
     9::800a3354 21 50 41 01     addu       t2,t2,at
     9::800a3358 ec 00 4a 8d     lw         t2,0xec(t2)
     9::800a335c 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a3360 94 01 2a ac     sw         t2,0x194(at)
     9::800a3364 02 9e 0a 00     srl        s3,t2,0x18
     9::800a3368 1f 00 73 32     andi       s3,s3,0x1f
     9::800a336c 06 98 63 02     srlv       s3,v1,s3
     9::800a3370 ff 00 73 32     andi       s3,s3,0xff
     9::800a3374 21 98 7e 02     addu       s3,s3,s8
     9::800a3378 02 a4 0a 00     srl        s4,t2,0x10
     9::800a337c 1f 00 94 32     andi       s4,s4,0x1f
     9::800a3380 06 a0 83 02     srlv       s4,v1,s4
     9::800a3384 ff 00 94 32     andi       s4,s4,0xff
     9::800a3388 21 a0 9e 02     addu       s4,s4,s8
     9::800a338c 02 aa 0a 00     srl        s5,t2,0x8
     9::800a3390 1f 00 b5 32     andi       s5,s5,0x1f
     9::800a3394 06 a8 a3 02     srlv       s5,v1,s5
     9::800a3398 ff 00 b5 32     andi       s5,s5,0xff
     9::800a339c 21 a8 be 02     addu       s5,s5,s8
     9::800a33a0 1f 00 56 31     andi       s6,t2,0x1f
     9::800a33a4 06 b0 c3 02     srlv       s6,v1,s6
     9::800a33a8 ff 00 d6 32     andi       s6,s6,0xff
     9::800a33ac 21 b0 de 02     addu       s6,s6,s8
     9::800a33b0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a33b4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a33b8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a33bc 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a33c0 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a33c4 06 00 40 4b     NCLIP
     9::800a33c8 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a33cc 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a33d0 23 78 68 01     subu       t7,t3,t0
     9::800a33d4 23 80 88 01     subu       s0,t4,t0
     9::800a33d8 23 88 a8 01     subu       s1,t5,t0
     9::800a33dc 23 90 c8 01     subu       s2,t6,t0
     9::800a33e0 00 c0 08 48     gte_stMAC0 t0
     9::800a33e4 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a33e8 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a33f4
     9::800a33ec 22 40 08 00     _sub       t0,zero,t0
     9::800a33f0 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a33f4                           XREF[1]:     OVR_229::800a33e8(j)  
     9::800a33f4 06 00 40 4b     NCLIP
     9::800a33f8 24 18 6c 01     and        v1,t3,t4
     9::800a33fc 24 18 6d 00     and        v1,v1,t5
     9::800a3400 24 18 6e 00     and        v1,v1,t6
     9::800a3404 25 78 f0 01     or         t7,t7,s0
     9::800a3408 25 78 f1 01     or         t7,t7,s1
     9::800a340c 27 78 f2 01     nor        t7,t7,s2
     9::800a3410 25 78 e3 01     or         t7,t7,v1
     9::800a3414 aa fe e0 05     bltz       t7,LAB_OVR_229__800a2ec0
     9::800a3418 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a341c a8 fe e0 05     bltz       t7,LAB_OVR_229__800a2ec0
     9::800a3420 00 c0 03 48     _gte_stM   v1
     9::800a3424 25 40 09 01     or         t0,t0,t1
     9::800a3428 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a3434
     9::800a342c c2 47 08 00     _srl       t0,t0,0x1f
     9::800a3430 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a3434                           XREF[1]:     OVR_229::800a3428(j)  
     9::800a3434 80 40 08 00     sll        t0,t0,0x2
     9::800a3438 25 18 69 00     or         v1,v1,t1
     9::800a343c c2 1f 03 00     srl        v1,v1,0x1f
     9::800a3440 c0 18 03 00     sll        v1,v1,0x3
     9::800a3444 25 18 68 00     or         v1,v1,t0
     9::800a3448 9d fe 60 10     beq        v1,zero,LAB_OVR_229__800a2ec0
     9::800a344c 70 00 23 ac     _sw        v1,0x70(at)
     9::800a3450 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a3454 04 00 39 27     addiu      t9,t9,0x4
     9::800a3458 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a345c 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a3460 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a3464 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a3468 b4 00 c3 8f     lw         v1,0xb4(s8)
     9::800a346c 23 50 6c 01     subu       t2,t3,t4
     9::800a3470 82 48 03 00     srl        t1,v1,0x2
     9::800a3474 21 48 38 01     addu       t1,t1,t8
     9::800a3478 18 00 29 81     lb         t1,0x18(t1)
     9::800a347c 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a3488
     9::800a3480 21 e0 60 01     _move      gp,t3
     9::800a3484 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a3488                           XREF[1]:     OVR_229::800a347c(j)  
     9::800a3488 23 50 8d 03     subu       t2,gp,t5
     9::800a348c 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a3498
     9::800a3490 21 18 78 00     _addu      v1,v1,t8
     9::800a3494 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a3498                           XREF[1]:     OVR_229::800a348c(j)  
     9::800a3498 23 50 8e 03     subu       t2,gp,t6
     9::800a349c 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a34a8
     9::800a34a0 1c 00 63 8c     _lw        v1,0x1c(v1)
     9::800a34a4 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a34a8                           XREF[1]:     OVR_229::800a349c(j)  
     9::800a34a8 21 50 80 03     move       t2,gp
     9::800a34ac 82 e1 1c 00     srl        gp,gp,0x6
     9::800a34b0 21 e0 89 03     addu       gp,gp,t1
     9::800a34b4 01 00 69 30     andi       t1,v1,0x1
     9::800a34b8 02 00 20 11     beq        t1,zero,LAB_OVR_229__800a34c4
     9::800a34bc 80 e0 1c 00     _sll       gp,gp,0x2
     9::800a34c0 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_229__800a34c4                           XREF[1]:     OVR_229::800a34b8(j)  
     9::800a34c4 02 00 81 07     bgez       gp,LAB_OVR_229__800a34d0
     9::800a34c8 21 e0 85 03     _addu      gp,gp,a1
     9::800a34cc 21 e0 a0 00     move       gp,a1
                             LAB_OVR_229__800a34d0                           XREF[1]:     OVR_229::800a34c4(j)  
     9::800a34d0 24 00 69 8c     lw         t1,0x24(v1)
     9::800a34d4 c0 f9 48 25     addiu      t0,t2,-0x640
     9::800a34d8 84 00 29 ac     sw         t1,0x84(at)
     9::800a34dc 0a 00 01 05     bgez       t0,LAB_OVR_229__800a3508
     9::800a34e0 00 fb 48 25     _addiu     t0,t2,-0x500
     9::800a34e4 0c 00 63 24     addiu      v1,v1,0xc
     9::800a34e8 07 00 01 05     bgez       t0,LAB_OVR_229__800a3508
     9::800a34ec 80 fd 48 25     _addiu     t0,t2,-0x280
     9::800a34f0 0c 00 63 24     addiu      v1,v1,0xc
     9::800a34f4 04 00 01 05     bgez       t0,LAB_OVR_229__800a3508
     9::800a34f8 00 00 00 00     _nop
     9::800a34fc 02 00 20 05     bltz       t1,LAB_OVR_229__800a3508
     9::800a3500 00 00 00 00     _nop
     9::800a3504 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_229__800a3508                           XREF[4]:     OVR_229::800a34dc(j), 
                                                                                          OVR_229::800a34e8(j), 
                                                                                          OVR_229::800a34f4(j), 
                                                                                          OVR_229::800a34fc(j)  
     9::800a3508 94 01 2a 8c     lw         t2,0x194(at)
     9::800a350c 00 00 68 8c     lw         t0,0x0(v1)
     9::800a3510 04 00 69 8c     lw         t1,0x4(v1)
     9::800a3514 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a3518 ac 01 28 ac     sw         t0,0x1ac(at)
     9::800a351c a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a3520 00 52 0a 00     sll        t2,t2,0x8
     9::800a3524 0a 00 40 05     bltz       t2,LAB_OVR_229__800a3550
     9::800a3528 b0 01 29 ac     _sw        t1,0x1b0(at)
     9::800a352c 06 00 68 a6     sh         t0,0x6(s3)
     9::800a3530 08 00 68 8c     lw         t0,0x8(v1)
     9::800a3534 06 00 89 a6     sh         t1,0x6(s4)
     9::800a3538 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a353c 00 54 0a 00     sll        t2,t2,0x10
     9::800a3540 0b 00 40 05     bltz       t2,LAB_OVR_229__800a3570
     9::800a3544 02 4c 08 00     _srl       t1,t0,0x10
     9::800a3548 09 00 01 04     bgez       zero,LAB_OVR_229__800a3570
     9::800a354c 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_229__800a3550                           XREF[1]:     OVR_229::800a3524(j)  
     9::800a3550 06 00 69 a6     sh         t1,0x6(s3)
     9::800a3554 08 00 69 8c     lw         t1,0x8(v1)
     9::800a3558 00 54 0a 00     sll        t2,t2,0x10
     9::800a355c 06 00 88 a6     sh         t0,0x6(s4)
     9::800a3560 02 44 09 00     srl        t0,t1,0x10
     9::800a3564 02 00 40 05     bltz       t2,LAB_OVR_229__800a3570
     9::800a3568 06 00 a8 a6     _sh        t0,0x6(s5)
     9::800a356c 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a3570                           XREF[3]:     OVR_229::800a3540(j), 
                                                                                          OVR_229::800a3548(j), 
                                                                                          OVR_229::800a3564(j)  
     9::800a3570 80 fd 71 25     addiu      s1,t3,-0x280
     9::800a3574 80 fd 92 25     addiu      s2,t4,-0x280
     9::800a3578 80 fd af 25     addiu      t7,t5,-0x280
     9::800a357c 80 fd d0 25     addiu      s0,t6,-0x280
                             LAB_OVR_229__800a3580                           XREF[1]:     FUN_OVR_229__800a3254:800a3338(j
     9::800a3580 42 8f 11 00     srl        s1,s1,0x1d
     9::800a3584 04 00 31 32     andi       s1,s1,0x4
     9::800a3588 02 97 12 00     srl        s2,s2,0x1c
     9::800a358c 08 00 52 32     andi       s2,s2,0x8
     9::800a3590 25 88 32 02     or         s1,s1,s2
     9::800a3594 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a3598 10 00 ef 31     andi       t7,t7,0x10
     9::800a359c 25 88 2f 02     or         s1,s1,t7
     9::800a35a0 82 86 10 00     srl        s0,s0,0x1a
     9::800a35a4 20 00 10 32     andi       s0,s0,0x20
     9::800a35a8 25 88 30 02     or         s1,s1,s0
     9::800a35ac 26 00 20 12     beq        s1,zero,LAB_OVR_229__800a3648
     9::800a35b0 21 68 60 02     _move      t5,s3
     9::800a35b4 21 70 80 02     move       t6,s4
     9::800a35b8 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a35bc 00 00 cf 27     addiu      t7,s8,0x0
     9::800a35c0 5b 8c 02 0c     jal        FUN_OVR_229__800a316c                            undefined FUN_OVR_229__800a316c()
     9::800a35c4 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a35c8 21 68 80 02     move       t5,s4
     9::800a35cc 21 70 c0 02     move       t6,s6
     9::800a35d0 14 00 cf 27     addiu      t7,s8,0x14
     9::800a35d4 5b 8c 02 0c     jal        FUN_OVR_229__800a316c                            undefined FUN_OVR_229__800a316c()
     9::800a35d8 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a35dc 21 68 a0 02     move       t5,s5
     9::800a35e0 21 70 60 02     move       t6,s3
     9::800a35e4 28 00 cf 27     addiu      t7,s8,0x28
     9::800a35e8 5b 8c 02 0c     jal        FUN_OVR_229__800a316c                            undefined FUN_OVR_229__800a316c()
     9::800a35ec 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a35f0 21 68 c0 02     move       t5,s6
     9::800a35f4 21 70 a0 02     move       t6,s5
     9::800a35f8 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a35fc 5b 8c 02 0c     jal        FUN_OVR_229__800a316c                            undefined FUN_OVR_229__800a316c()
     9::800a3600 a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a3604 21 68 80 02     move       t5,s4
     9::800a3608 21 70 a0 02     move       t6,s5
     9::800a360c 14 00 cf 27     addiu      t7,s8,0x14
     9::800a3610 5b 8c 02 0c     jal        FUN_OVR_229__800a316c                            undefined FUN_OVR_229__800a316c()
     9::800a3614 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a3618 21 18 21 02     addu       v1,s1,at
     9::800a361c 48 01 63 8c     lw         v1,0x148(v1)
     9::800a3620 0a 80 08 3c     lui        t0,0x800a
     9::800a3624 38 36 08 25     addiu      t0,t0,0x3638
     9::800a3628 9c 00 23 ac     sw         v1,0x9c(at)
     9::800a362c 3c 00 28 af     sw         t0=>LAB_OVR_229__800a3638,0x3c(t9)
     9::800a3630 08 00 60 00     jr         v1
     9::800a3634 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a3638                           XREF[1]:     FUN_OVR_229__800a3340:800a362c(*
     9::800a3638 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a363c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3640 08 00 e0 03     jr         ra
     9::800a3644 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a3648                           XREF[1]:     OVR_229::800a35ac(j)  
     9::800a3648 70 00 23 8c     lw         v1,0x70(at)
     9::800a364c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3650 21 18 61 00     addu       v1,v1,at
     9::800a3654 84 01 63 8c     lw         v1,0x184(v1)
     9::800a3658 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a365c 08 00 60 00     jr         v1
     9::800a3660 00 00 00 00     _nop
                             LAB_OVR_229__800a3664                           XREF[1]:     OVR_229::800a3314(j)  
     9::800a3664 84 00 23 8c     lw         v1,0x84(at)
     9::800a3668 24 03 2a 24     addiu      t2,at,0x324
     9::800a366c 26 00 60 1c     bgtz       v1,LAB_OVR_229__800a3708
     9::800a3670 20 03 28 8c     _lw        t0,0x320(at)
     9::800a3674 d8 03 29 8c     lw         t1,0x3d8(at)
     9::800a3678 16 00 5e 15     bne        t2,s8,LAB_OVR_229__800a36d4
     9::800a367c 9c 00 23 8c     _lw        v1,0x9c(at)
     9::800a3680 0a 80 0a 3c     lui        t2,0x800a
     9::800a3684 c8 30 4a 25     addiu      t2,t2,0x30c8
     9::800a3688 1f 00 6a 14     bne        v1,t2,LAB_OVR_229__800a3708
     9::800a368c 94 01 23 8c     _lw        v1,0x194(at)
     9::800a3690 40 40 08 00     sll        t0,t0,0x1
     9::800a3694 00 1a 03 00     sll        v1,v1,0x8
     9::800a3698 02 00 61 04     bgez       v1,LAB_OVR_229__800a36a4
     9::800a369c 84 00 2a 8c     _lw        t2,0x84(at)
     9::800a36a0 c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_229__800a36a4                           XREF[1]:     OVR_229::800a3698(j)  
     9::800a36a4 21 40 09 01     addu       t0,t0,t1
     9::800a36a8 21 50 48 01     addu       t2,t2,t0
     9::800a36ac 00 00 48 8d     lw         t0,0x0(t2)
     9::800a36b0 04 00 49 8d     lw         t1,0x4(t2)
     9::800a36b4 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a36b8 06 00 68 a6     sh         t0,0x6(s3)
     9::800a36bc 08 00 48 85     lh         t0,0x8(t2)
     9::800a36c0 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a36c4 06 00 89 a6     sh         t1,0x6(s4)
     9::800a36c8 0a 00 49 85     lh         t1,0xa(t2)
     9::800a36cc 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a36d0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a36d4                           XREF[2]:     OVR_229::800a3678(j), 
                                                                                          OVR_229::800a3714(j)  
     9::800a36d4 70 00 23 8c     lw         v1,0x70(at)
     9::800a36d8 00 00 00 00     nop
     9::800a36dc 21 18 61 00     addu       v1,v1,at
     9::800a36e0 84 01 63 8c     lw         v1,0x184(v1)
     9::800a36e4 00 00 00 00     nop
     9::800a36e8 09 f8 60 00     jalr       v1
     9::800a36ec fc ff 39 27     _addiu     t9,t9,-0x4
     9::800a36f0 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a36f4 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a36f8 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a36fc a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a3700 08 00 e0 03     jr         ra
     9::800a3704 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_229__800a3708                           XREF[2]:     OVR_229::800a366c(j), 
                                                                                          OVR_229::800a3688(j)  
     9::800a3708 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a370c b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a3710 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a3714 ef ff 01 04     bgez       zero,LAB_OVR_229__800a36d4
     9::800a3718 a4 01 29 ac     _sw        t1,0x1a4(at)
     9::800a371c 21 98 80 02     move       s3,s4
     9::800a3720 21 a0 c0 02     move       s4,s6
     9::800a3724 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a3728 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a372c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a3730 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a3734 08 00 90 8e     lw         s0,0x8(s4)
     9::800a3738 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a373c 06 00 73 86     lh         s3,0x6(s3)
     9::800a3740 06 00 94 86     lh         s4,0x6(s4)
     9::800a3744 06 00 b5 86     lh         s5,0x6(s5)
     9::800a3748 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a374c a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a3750 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a3754 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a3758 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a375c a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a3760 60 00 03 3c     lui        v1,0x60
     9::800a3764 24 48 83 02     and        t1,s4,v1
     9::800a3768 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a3774
     9::800a376c 00 36 03 3c     _lui       v1,0x3600
     9::800a3770 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a3774                           XREF[1]:     OVR_229::800a3768(j)  
     9::800a3774 25 18 6f 00     or         v1,v1,t7
     9::800a3778 04 00 43 ac     sw         v1,0x4(v0)
     9::800a377c 08 00 4b ac     sw         t3,0x8(v0)
     9::800a3780 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a3784 10 00 50 ac     sw         s0,0x10(v0)
     9::800a3788 14 00 4c ac     sw         t4,0x14(v0)
     9::800a378c 18 00 54 ac     sw         s4,0x18(v0)
     9::800a3790 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a3794 20 00 4d ac     sw         t5,0x20(v0)
     9::800a3798 24 00 55 ac     sw         s5,0x24(v0)
     9::800a379c 28 00 09 24     li         t1,0x28
     9::800a37a0 29 00 01 04     bgez       zero,LAB_OVR_229__800a3848
     9::800a37a4 00 09 0a 3c     _lui       t2,0x900
     9::800a37a8 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a37ac 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a37b0 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a37b4 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a37b8 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a37bc 08 00 90 8e     lw         s0,0x8(s4)
     9::800a37c0 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a37c4 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a37c8 06 00 73 86     lh         s3,0x6(s3)
     9::800a37cc 06 00 94 86     lh         s4,0x6(s4)
     9::800a37d0 06 00 b5 86     lh         s5,0x6(s5)
     9::800a37d4 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a37d8 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a37dc 06 00 d4 86     lh         s4,0x6(s6)
     9::800a37e0 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a37e4 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a37e8 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a37ec a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a37f0 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a37f4 60 00 03 3c     lui        v1,0x60
     9::800a37f8 24 48 83 02     and        t1,s4,v1
     9::800a37fc 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a3808
     9::800a3800 00 3e 03 3c     _lui       v1,0x3e00
     9::800a3804 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a3808                           XREF[1]:     OVR_229::800a37fc(j)  
     9::800a3808 25 18 6f 00     or         v1,v1,t7
     9::800a380c 04 00 43 ac     sw         v1,0x4(v0)
     9::800a3810 08 00 4b ac     sw         t3,0x8(v0)
     9::800a3814 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a3818 10 00 50 ac     sw         s0,0x10(v0)
     9::800a381c 14 00 4c ac     sw         t4,0x14(v0)
     9::800a3820 18 00 54 ac     sw         s4,0x18(v0)
     9::800a3824 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a3828 20 00 4d ac     sw         t5,0x20(v0)
     9::800a382c 24 00 55 ac     sw         s5,0x24(v0)
     9::800a3830 28 00 52 ac     sw         s2,0x28(v0)
     9::800a3834 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a3838 02 1c 15 00     srl        v1,s5,0x10
     9::800a383c 30 00 43 ac     sw         v1,0x30(v0)
     9::800a3840 34 00 09 24     li         t1,0x34
     9::800a3844 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a3848                           XREF[1]:     OVR_229::800a37a0(j)  
     9::800a3848 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a384c 00 42 02 00     sll        t0,v0,0x8
     9::800a3850 02 42 08 00     srl        t0,t0,0x8
     9::800a3854 25 18 6a 00     or         v1,v1,t2
     9::800a3858 00 00 43 ac     sw         v1,0x0(v0)
     9::800a385c 21 10 49 00     addu       v0,v0,t1
     9::800a3860 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a3864 08 00 e0 03     jr         ra
     9::800a3868 01 00 bd 23     _addi      sp,sp,0x1
     9::800a386c 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_229__800a3870                           XREF[1]:     OVR_229::800a3bc0(j)  
     9::800a3870 30 00 23 8c     lw         v1,0x30(at)
     9::800a3874 40 37 48 24     addiu      t0,v0,0x3740
     9::800a3878 23 18 68 00     subu       v1,v1,t0
     9::800a387c eb f5 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a3880 b4 01 3e 24     _addiu     s8,at,0x1b4
     9::800a3884 38 f6 00 13     beq        t8,zero,LAB_OVR_229__800a1168
     9::800a3888 b4 00 c0 af     _sw        zero,0xb4(s8)
     9::800a388c 00 00 14 8f     lw         s4,0x0(t8)
     9::800a3890 04 00 16 8f     lw         s6,0x4(t8)
     9::800a3894 ff ff 93 32     andi       s3,s4,0xffff
     9::800a3898 00 99 13 00     sll        s3,s3,0x4
     9::800a389c 21 98 77 02     addu       s3,s3,s7
     9::800a38a0 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a38a8 02 a4 14 00     srl        s4,s4,0x10
     9::800a38ac 00 a1 14 00     sll        s4,s4,0x4
     9::800a38b0 21 a0 97 02     addu       s4,s4,s7
     9::800a38b4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a38bc ff ff d5 32     andi       s5,s6,0xffff
     9::800a38c0 00 a9 15 00     sll        s5,s5,0x4
     9::800a38c4 21 a8 b7 02     addu       s5,s5,s7
     9::800a38c8 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a38d0 02 b4 16 00     srl        s6,s6,0x10
     9::800a38d4 00 b1 16 00     sll        s6,s6,0x4
     9::800a38d8 30 00 28 4a     RTPT
     9::800a38dc 21 b0 d7 02     addu       s6,s6,s7
     9::800a38e0 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a38e4 08 00 90 8e     lw         s0,0x8(s4)
     9::800a38e8 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a38ec 08 00 cf af     sw         t7,0x8(s8)
     9::800a38f0 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a38f4 30 00 d1 af     sw         s1,0x30(s8)
     9::800a38f8 08 00 14 8f     lw         s4,0x8(t8)
     9::800a38fc 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a3900 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a3904 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a3908 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a390c 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a3910 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a3914 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a3918 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a391c 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a3920 5c 00 2a 8c     lw         t2,0x5c(at)
     9::800a3924 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a3930 10 00 c3 a7     sh         v1,0x10(s8)
     9::800a3934 24 00 c8 a7     sh         t0,0x24(s8)
     9::800a3938 38 00 c9 a7     sh         t1,0x38(s8)
     9::800a393c 23 58 6a 00     subu       t3,v1,t2
     9::800a3940 23 60 0a 01     subu       t4,t0,t2
     9::800a3944 23 68 2a 01     subu       t5,t1,t2
     9::800a3948 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a394c c2 67 0c 00     srl        t4,t4,0x1f
     9::800a3950 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a3954 12 00 cb a3     sb         t3,0x12(s8)
     9::800a3958 26 00 cc a3     sb         t4,0x26(s8)
     9::800a395c 3a 00 cd a3     sb         t5,0x3a(s8)
     9::800a3960 40 18 03 00     sll        v1,v1,0x1
     9::800a3964 40 40 08 00     sll        t0,t0,0x1
     9::800a3968 40 48 09 00     sll        t1,t1,0x1
     9::800a396c 23 58 6a 00     subu       t3,v1,t2
     9::800a3970 23 60 0a 01     subu       t4,t0,t2
     9::800a3974 23 68 2a 01     subu       t5,t1,t2
     9::800a3978 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a397c c2 67 0c 00     srl        t4,t4,0x1f
     9::800a3980 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a3984 13 00 cb a3     sb         t3,0x13(s8)
     9::800a3988 27 00 cc a3     sb         t4,0x27(s8)
     9::800a398c 3b 00 cd a3     sb         t5,0x3b(s8)
     9::800a3990 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a3998 ff ff 93 32     andi       s3,s4,0xffff
     9::800a399c 00 99 13 00     sll        s3,s3,0x4
     9::800a39a0 21 98 77 02     addu       s3,s3,s7
     9::800a39a4 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a39ac 02 a4 14 00     srl        s4,s4,0x10
     9::800a39b0 00 a1 14 00     sll        s4,s4,0x4
     9::800a39b4 21 a0 97 02     addu       s4,s4,s7
     9::800a39b8 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a39c0 21 c8 20 00     move       t9,at
     9::800a39c4 00 00 00 00     nop
     9::800a39c8 30 00 28 4a     RTPT
     9::800a39cc 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a39d0 08 00 70 8e     lw         s0,0x8(s3)
     9::800a39d4 08 00 91 8e     lw         s1,0x8(s4)
     9::800a39d8 44 00 cf af     sw         t7,0x44(s8)
     9::800a39dc 58 00 d0 af     sw         s0,0x58(s8)
     9::800a39e0 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a39e4 0c 00 14 8f     lw         s4,0xc(t8)
     9::800a39e8 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a39ec 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     9::800a39f0 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a39f4 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a39f8 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a39fc 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a3a00 10 00 15 97     lhu        s5,0x10(t8)
     9::800a3a04 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a3a08 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a3a0c 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a3a10 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a3a1c 4c 00 c3 a7     sh         v1,0x4c(s8)
     9::800a3a20 60 00 c8 a7     sh         t0,0x60(s8)
     9::800a3a24 74 00 c9 a7     sh         t1,0x74(s8)
     9::800a3a28 23 58 6a 00     subu       t3,v1,t2
     9::800a3a2c 23 60 0a 01     subu       t4,t0,t2
     9::800a3a30 23 68 2a 01     subu       t5,t1,t2
     9::800a3a34 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a3a38 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a3a3c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a3a40 4e 00 cb a3     sb         t3,0x4e(s8)
     9::800a3a44 62 00 cc a3     sb         t4,0x62(s8)
     9::800a3a48 76 00 cd a3     sb         t5,0x76(s8)
     9::800a3a4c 40 18 03 00     sll        v1,v1,0x1
     9::800a3a50 40 40 08 00     sll        t0,t0,0x1
     9::800a3a54 40 48 09 00     sll        t1,t1,0x1
     9::800a3a58 23 58 6a 00     subu       t3,v1,t2
     9::800a3a5c 23 60 0a 01     subu       t4,t0,t2
     9::800a3a60 23 68 2a 01     subu       t5,t1,t2
     9::800a3a64 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a3a68 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a3a6c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a3a70 4f 00 cb a3     sb         t3,0x4f(s8)
     9::800a3a74 63 00 cc a3     sb         t4,0x63(s8)
     9::800a3a78 77 00 cd a3     sb         t5,0x77(s8)
     9::800a3a7c ff ff 93 32     andi       s3,s4,0xffff
     9::800a3a80 00 99 13 00     sll        s3,s3,0x4
     9::800a3a84 21 98 77 02     addu       s3,s3,s7
     9::800a3a88 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a3a90 02 a4 14 00     srl        s4,s4,0x10
     9::800a3a94 00 a1 14 00     sll        s4,s4,0x4
     9::800a3a98 21 a0 97 02     addu       s4,s4,s7
     9::800a3a9c 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a3aa4 14 00 09 8f     lw         t1,0x14(t8)
     9::800a3aa8 00 a9 15 00     sll        s5,s5,0x4
     9::800a3aac 21 a8 b7 02     addu       s5,s5,s7
     9::800a3ab0 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a3ab8 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a3abc 00 00 00 00     nop
     9::800a3ac0 30 00 28 4a     RTPT
     9::800a3ac4 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a3ac8 08 00 90 8e     lw         s0,0x8(s4)
     9::800a3acc 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a3ad0 80 00 cf af     sw         t7,0x80(s8)
     9::800a3ad4 94 00 d0 af     sw         s0,0x94(s8)
     9::800a3ad8 a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a3adc 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a3ae0 98 00 cd eb     gte_stSXY1 0x98(s8)
     9::800a3ae4 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a3ae8 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a3aec 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a3af0 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a3af4 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a3af8 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a3afc a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a3b00 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a3b0c 88 00 c3 a7     sh         v1,0x88(s8)
     9::800a3b10 9c 00 c8 a7     sh         t0,0x9c(s8)
     9::800a3b14 b0 00 c9 a7     sh         t1,0xb0(s8)
     9::800a3b18 23 58 6a 00     subu       t3,v1,t2
     9::800a3b1c 23 60 0a 01     subu       t4,t0,t2
     9::800a3b20 23 68 2a 01     subu       t5,t1,t2
     9::800a3b24 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a3b28 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a3b2c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a3b30 8a 00 cb a3     sb         t3,0x8a(s8)
     9::800a3b34 9e 00 cc a3     sb         t4,0x9e(s8)
     9::800a3b38 b2 00 cd a3     sb         t5,0xb2(s8)
     9::800a3b3c 40 18 03 00     sll        v1,v1,0x1
     9::800a3b40 40 40 08 00     sll        t0,t0,0x1
     9::800a3b44 40 48 09 00     sll        t1,t1,0x1
     9::800a3b48 23 58 6a 00     subu       t3,v1,t2
     9::800a3b4c 23 60 0a 01     subu       t4,t0,t2
     9::800a3b50 23 68 2a 01     subu       t5,t1,t2
     9::800a3b54 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a3b58 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a3b5c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a3b60 8b 00 cb a3     sb         t3,0x8b(s8)
     9::800a3b64 9f 00 cc a3     sb         t4,0x9f(s8)
     9::800a3b68 b3 00 cd a3     sb         t5,0xb3(s8)
     9::800a3b6c 50 00 03 3c     lui        v1,0x50
     9::800a3b70 78 64 63 34     ori        v1,v1,0x6478
     9::800a3b74 08 00 08 24     li         t0,0x8
     9::800a3b78 14 90 02 0c     jal        FUN_OVR_229__800a4050                            undefined FUN_OVR_229__800a4050()
     9::800a3b7c 00 00 0a 24     _li        t2,0x0
     9::800a3b80 14 50 03 3c     lui        v1,0x5014
     9::800a3b84 8c 78 63 34     ori        v1,v1,0x788c
     9::800a3b88 0d 00 08 24     li         t0,0xd
     9::800a3b8c 14 90 02 0c     jal        FUN_OVR_229__800a4050                            undefined FUN_OVR_229__800a4050()
     9::800a3b90 04 00 0a 24     _li        t2,0x4
     9::800a3b94 78 64 03 3c     lui        v1,0x6478
     9::800a3b98 a0 28 63 34     ori        v1,v1,0x28a0
     9::800a3b9c 12 00 08 24     li         t0,0x12
     9::800a3ba0 14 90 02 0c     jal        FUN_OVR_229__800a4050                            undefined FUN_OVR_229__800a4050()
     9::800a3ba4 08 00 0a 24     _li        t2,0x8
     9::800a3ba8 8c 78 03 3c     lui        v1,0x788c
     9::800a3bac 3c a0 63 34     ori        v1,v1,0xa03c
     9::800a3bb0 17 00 08 24     li         t0,0x17
     9::800a3bb4 14 90 02 0c     jal        FUN_OVR_229__800a4050                            undefined FUN_OVR_229__800a4050()
     9::800a3bb8 0c 00 0a 24     _li        t2,0xc
     9::800a3bbc 04 00 98 8c     lw         t8,0x4(a0)
     9::800a3bc0 2b ff 01 04     bgez       zero,LAB_OVR_229__800a3870
     9::800a3bc4 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_229__800a3bc8                           XREF[12]:    FUN_OVR_229__800a3f20:800a3f3c(j
                                                                                          FUN_OVR_229__800a3f20:800a3fd8(j
                                                                                          FUN_OVR_229__800a3f20:800a3fe0(j
                                                                                          FUN_OVR_229__800a3f20:800a4014(j
                                                                                          OVR_229::800a40dc(j), 
                                                                                          OVR_229::800a4168(j), 
                                                                                          OVR_229::800a4170(j), 
                                                                                          OVR_229::800a419c(j), 
                                                                                          FUN_OVR_229__800a3f20:800a44a4(j
                                                                                          FUN_OVR_229__800a3f20:800a4560(j
                                                                                          FUN_OVR_229__800a3f20:800a4694(j
                                                                                          FUN_OVR_229__800a3f20:800a474c(j
     9::800a3bc8 08 00 e0 03     jr         ra
     9::800a3bcc 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3bd0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3bd0                           XREF[4]:     FUN_OVR_229__800a3c20:800a3ca8(j
                                                                                          FUN_OVR_229__800a3c20:800a3d40(c
                                                                                          FUN_OVR_229__800a3c20:800a3d68(c
                                                                                          FUN_OVR_229__800a3c20:800a3dd4(c
     9::800a3bd0 00 00 d3 27     addiu      s3,s8,0x0
     9::800a3bd4 50 00 d4 27     addiu      s4,s8,0x50
     9::800a3bd8 64 00 d5 27     addiu      s5,s8,0x64
     9::800a3bdc d0 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3be0 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3be4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3be4                           XREF[6]:     FUN_OVR_229__800a3c20:800a3cb0(c
                                                                                          FUN_OVR_229__800a3c20:800a3d50(j
                                                                                          FUN_OVR_229__800a3c20:800a3d60(c
                                                                                          FUN_OVR_229__800a3c20:800a3d90(c
                                                                                          FUN_OVR_229__800a3c20:800a3db0(c
                                                                                          FUN_OVR_229__800a3c20:800a3de4(c
     9::800a3be4 50 00 d3 27     addiu      s3,s8,0x50
     9::800a3be8 14 00 d4 27     addiu      s4,s8,0x14
     9::800a3bec 78 00 d5 27     addiu      s5,s8,0x78
     9::800a3bf0 cb 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3bf4 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3bf8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3bf8                           XREF[6]:     FUN_OVR_229__800a3c20:800a3cd8(c
                                                                                          FUN_OVR_229__800a3c20:800a3d38(c
                                                                                          FUN_OVR_229__800a3c20:800a3d78(j
                                                                                          FUN_OVR_229__800a3c20:800a3d88(c
                                                                                          FUN_OVR_229__800a3c20:800a3db8(c
                                                                                          FUN_OVR_229__800a3c20:800a3df4(c
     9::800a3bf8 64 00 d3 27     addiu      s3,s8,0x64
     9::800a3bfc 78 00 d4 27     addiu      s4,s8,0x78
     9::800a3c00 28 00 d5 27     addiu      s5,s8,0x28
     9::800a3c04 c6 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3c08 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a3c0c                           XREF[4]:     OVR_229::800a3d28(j), 
                                                                                          OVR_229::800a3da0(j), 
                                                                                          OVR_229::800a3dc8(j), 
                                                                                          OVR_229::800a3e0c(j)  
     9::800a3c0c 78 00 d3 27     addiu      s3,s8,0x78
     9::800a3c10 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a3c14 a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a3c18 c1 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3c1c 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3c20()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3c20                           XREF[2]:     OVR_229::800a3cd0(c), 
                                                                                          OVR_229::800a3da8(c)  
     9::800a3c20 64 00 d3 27     addiu      s3,s8,0x64
     9::800a3c24 00 00 d4 27     addiu      s4,s8,0x0
     9::800a3c28 78 00 d5 27     addiu      s5,s8,0x78
     9::800a3c2c bc 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3c30 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a3c34                           XREF[2]:     OVR_229::800a3ce8(j), 
                                                                                          OVR_229::800a3d58(c)  
     9::800a3c34 14 00 d3 27     addiu      s3,s8,0x14
     9::800a3c38 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a3c3c 78 00 d5 27     addiu      s5,s8,0x78
     9::800a3c40 b7 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3c44 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a3c48                           XREF[2]:     OVR_229::800a3cb8(c), 
                                                                                          OVR_229::800a3d80(c)  
     9::800a3c48 28 00 d3 27     addiu      s3,s8,0x28
     9::800a3c4c 00 00 d4 27     addiu      s4,s8,0x0
     9::800a3c50 78 00 d5 27     addiu      s5,s8,0x78
     9::800a3c54 b2 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3c58 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a3c5c                           XREF[2]:     OVR_229::800a3cc8(j), 
                                                                                          OVR_229::800a3d30(c)  
     9::800a3c5c 28 00 d3 27     addiu      s3,s8,0x28
     9::800a3c60 78 00 d4 27     addiu      s4,s8,0x78
     9::800a3c64 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a3c68 ad 00 01 04     bgez       zero,FUN_OVR_229__800a3f20
     9::800a3c6c 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a3c70 50 00 d3 27     addiu      s3,s8,0x50
     9::800a3c74 14 00 d4 27     addiu      s4,s8,0x14
     9::800a3c78 78 00 d5 27     addiu      s5,s8,0x78
     9::800a3c7c 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a3c80 c8 8f 02 0c     jal        FUN_OVR_229__800a3f20                            undefined FUN_OVR_229__800a3f20()
     9::800a3c84 0c 00 0a 24     _li        t2,0xc
     9::800a3c88 64 00 d3 27     addiu      s3,s8,0x64
     9::800a3c8c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a3c90 28 00 d5 27     addiu      s5,s8,0x28
     9::800a3c94 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a3c98 c8 8f 02 0c     jal        FUN_OVR_229__800a3f20                            undefined FUN_OVR_229__800a3f20()
     9::800a3c9c 0c 00 0a 24     _li        t2,0xc
     9::800a3ca0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3ca4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3ca8 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a3bd0
     9::800a3cac 0c 00 0a 24     _li        t2,0xc
     9::800a3cb0 f9 8e 02 0c     jal        FUN_OVR_229__800a3be4                            undefined FUN_OVR_229__800a3be4()
     9::800a3cb4 0c 00 0a 24     _li        t2,0xc
     9::800a3cb8 12 8f 02 0c     jal        SUB_OVR_229__800a3c48
     9::800a3cbc 0c 00 0a 24     _li        t2,0xc
     9::800a3cc0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3cc4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3cc8 e4 ff 01 04     bgez       zero,SUB_OVR_229__800a3c5c
     9::800a3ccc 0c 00 0a 24     _li        t2,0xc
     9::800a3cd0 08 8f 02 0c     jal        FUN_OVR_229__800a3c20                            undefined FUN_OVR_229__800a3c20()
     9::800a3cd4 0c 00 0a 24     _li        t2,0xc
     9::800a3cd8 fe 8e 02 0c     jal        FUN_OVR_229__800a3bf8                            undefined FUN_OVR_229__800a3bf8()
     9::800a3cdc 0c 00 0a 24     _li        t2,0xc
     9::800a3ce0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3ce4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3ce8 d2 ff 01 04     bgez       zero,SUB_OVR_229__800a3c34
     9::800a3cec 0c 00 0a 24     _li        t2,0xc
     9::800a3cf0 00 00 d3 27     addiu      s3,s8,0x0
     9::800a3cf4 14 00 d4 27     addiu      s4,s8,0x14
     9::800a3cf8 78 00 d5 27     addiu      s5,s8,0x78
     9::800a3cfc 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a3d00 c8 8f 02 0c     jal        FUN_OVR_229__800a3f20                            undefined FUN_OVR_229__800a3f20()
     9::800a3d04 0c 00 0a 24     _li        t2,0xc
     9::800a3d08 00 00 d3 27     addiu      s3,s8,0x0
     9::800a3d0c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a3d10 28 00 d5 27     addiu      s5,s8,0x28
     9::800a3d14 a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a3d18 c8 8f 02 0c     jal        FUN_OVR_229__800a3f20                            undefined FUN_OVR_229__800a3f20()
     9::800a3d1c 0c 00 0a 24     _li        t2,0xc
     9::800a3d20 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3d24 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3d28 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a3c0c
     9::800a3d2c 0c 00 0a 24     _li        t2,0xc
     9::800a3d30 17 8f 02 0c     jal        SUB_OVR_229__800a3c5c
     9::800a3d34 0c 00 0a 24     _li        t2,0xc
     9::800a3d38 fe 8e 02 0c     jal        FUN_OVR_229__800a3bf8                            undefined FUN_OVR_229__800a3bf8()
     9::800a3d3c 04 00 0a 24     _li        t2,0x4
     9::800a3d40 f4 8e 02 0c     jal        FUN_OVR_229__800a3bd0                            undefined FUN_OVR_229__800a3bd0()
     9::800a3d44 0c 00 0a 24     _li        t2,0xc
     9::800a3d48 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3d4c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3d50 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a3be4
     9::800a3d54 0c 00 0a 24     _li        t2,0xc
     9::800a3d58 0d 8f 02 0c     jal        SUB_OVR_229__800a3c34
     9::800a3d5c 0c 00 0a 24     _li        t2,0xc
     9::800a3d60 f9 8e 02 0c     jal        FUN_OVR_229__800a3be4                            undefined FUN_OVR_229__800a3be4()
     9::800a3d64 04 00 0a 24     _li        t2,0x4
     9::800a3d68 f4 8e 02 0c     jal        FUN_OVR_229__800a3bd0                            undefined FUN_OVR_229__800a3bd0()
     9::800a3d6c 0c 00 0a 24     _li        t2,0xc
     9::800a3d70 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3d74 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3d78 9f ff 01 04     bgez       zero,FUN_OVR_229__800a3bf8
     9::800a3d7c 0c 00 0a 24     _li        t2,0xc
     9::800a3d80 12 8f 02 0c     jal        SUB_OVR_229__800a3c48
     9::800a3d84 0c 00 0a 24     _li        t2,0xc
     9::800a3d88 fe 8e 02 0c     jal        FUN_OVR_229__800a3bf8                            undefined FUN_OVR_229__800a3bf8()
     9::800a3d8c 08 00 0a 24     _li        t2,0x8
     9::800a3d90 f9 8e 02 0c     jal        FUN_OVR_229__800a3be4                            undefined FUN_OVR_229__800a3be4()
     9::800a3d94 0c 00 0a 24     _li        t2,0xc
     9::800a3d98 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3d9c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3da0 9a ff 01 04     bgez       zero,LAB_OVR_229__800a3c0c
     9::800a3da4 0c 00 0a 24     _li        t2,0xc
     9::800a3da8 08 8f 02 0c     jal        FUN_OVR_229__800a3c20                            undefined FUN_OVR_229__800a3c20()
     9::800a3dac 0c 00 0a 24     _li        t2,0xc
     9::800a3db0 f9 8e 02 0c     jal        FUN_OVR_229__800a3be4                            undefined FUN_OVR_229__800a3be4()
     9::800a3db4 08 00 0a 24     _li        t2,0x8
     9::800a3db8 fe 8e 02 0c     jal        FUN_OVR_229__800a3bf8                            undefined FUN_OVR_229__800a3bf8()
     9::800a3dbc 0c 00 0a 24     _li        t2,0xc
     9::800a3dc0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3dc4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3dc8 90 ff 01 04     bgez       zero,LAB_OVR_229__800a3c0c
     9::800a3dcc 0c 00 0a 24     _li        t2,0xc
     9::800a3dd0 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a3dd4 f4 8e 02 0c     jal        FUN_OVR_229__800a3bd0                            undefined FUN_OVR_229__800a3bd0()
     9::800a3dd8 0c 00 0a 24     _li        t2,0xc
     9::800a3ddc 0c 00 03 24     li         v1,0xc
     9::800a3de0 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a3de4 f9 8e 02 0c     jal        FUN_OVR_229__800a3be4                            undefined FUN_OVR_229__800a3be4()
     9::800a3de8 0c 00 0a 24     _li        t2,0xc
     9::800a3dec 30 00 03 24     li         v1,0x30
     9::800a3df0 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a3df4 fe 8e 02 0c     jal        FUN_OVR_229__800a3bf8                            undefined FUN_OVR_229__800a3bf8()
     9::800a3df8 0c 00 0a 24     _li        t2,0xc
     9::800a3dfc 3c 00 03 24     li         v1,0x3c
     9::800a3e00 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a3e04 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a3e08 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a3e0c 7f ff 01 04     bgez       zero,LAB_OVR_229__800a3c0c
     9::800a3e10 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3e14()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3e14                           XREF[5]:     FUN_OVR_229__800a4050:800a432c(c
                                                                                          FUN_OVR_229__800a4050:800a4340(c
                                                                                          FUN_OVR_229__800a4050:800a4354(c
                                                                                          FUN_OVR_229__800a4050:800a4368(c
                                                                                          FUN_OVR_229__800a4050:800a437c(c
     9::800a3e14 00 00 ab 85     lh         t3,0x0(t5)
     9::800a3e18 00 00 cc 85     lh         t4,0x0(t6)
     9::800a3e1c 00 00 eb a5     sh         t3,0x0(t7)
     9::800a3e20 21 18 6c 01     addu       v1,t3,t4
     9::800a3e24 43 18 03 00     sra        v1,v1,0x1
     9::800a3e28 00 00 03 a6     sh         v1,0x0(s0)
     9::800a3e2c 02 00 ab 85     lh         t3,0x2(t5)
     9::800a3e30 02 00 cc 85     lh         t4,0x2(t6)
     9::800a3e34 02 00 eb a5     sh         t3,0x2(t7)
     9::800a3e38 21 18 6c 01     addu       v1,t3,t4
     9::800a3e3c 43 18 03 00     sra        v1,v1,0x1
     9::800a3e40 02 00 03 a6     sh         v1,0x2(s0)
     9::800a3e44 04 00 ab 85     lh         t3,0x4(t5)
     9::800a3e48 04 00 cc 85     lh         t4,0x4(t6)
     9::800a3e4c 04 00 eb a5     sh         t3,0x4(t7)
     9::800a3e50 21 18 6c 01     addu       v1,t3,t4
     9::800a3e54 43 18 03 00     sra        v1,v1,0x1
     9::800a3e58 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a3e5c 00 08 83 48     gte_ldVZ0  v1
     9::800a3e60 04 00 03 a6     sh         v1,0x4(s0)
     9::800a3e64 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a3e68 01 00 18 4a     RTPS
     9::800a3e6c 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a3e70 08 00 eb a1     sb         t3,0x8(t7)
     9::800a3e74 21 18 6c 01     addu       v1,t3,t4
     9::800a3e78 43 18 03 00     sra        v1,v1,0x1
     9::800a3e7c 08 00 03 a2     sb         v1,0x8(s0)
     9::800a3e80 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a3e84 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a3e88 09 00 eb a1     sb         t3,0x9(t7)
     9::800a3e8c 21 18 6c 01     addu       v1,t3,t4
     9::800a3e90 43 18 03 00     sra        v1,v1,0x1
     9::800a3e94 09 00 03 a2     sb         v1,0x9(s0)
     9::800a3e98 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a3e9c 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a3ea0 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a3ea4 21 18 6c 01     addu       v1,t3,t4
     9::800a3ea8 43 18 03 00     sra        v1,v1,0x1
     9::800a3eac 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a3eb0 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a3eb4 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a3eb8 06 00 eb a1     sb         t3,0x6(t7)
     9::800a3ebc 21 18 6c 01     addu       v1,t3,t4
     9::800a3ec0 43 18 03 00     sra        v1,v1,0x1
     9::800a3ec4 06 00 03 a2     sb         v1,0x6(s0)
     9::800a3ec8 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a3ecc 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a3ed0 07 00 eb a1     sb         t3,0x7(t7)
     9::800a3ed4 21 18 6c 01     addu       v1,t3,t4
     9::800a3ed8 43 18 03 00     sra        v1,v1,0x1
     9::800a3edc 07 00 03 a2     sb         v1,0x7(s0)
     9::800a3ee0 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a3ee4 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a3ee8 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a3eec 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a3ef0 5c 00 2b 8c     lw         t3,0x5c(at)
     9::800a3ef4 00 98 03 48     gte_stSZ3  v1
     9::800a3ef8 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a3efc 10 00 03 ae     sw         v1,0x10(s0)
     9::800a3f00 23 40 6b 00     subu       t0,v1,t3
     9::800a3f04 c2 47 08 00     srl        t0,t0,0x1f
     9::800a3f08 12 00 08 a2     sb         t0,0x12(s0)
     9::800a3f0c 40 18 03 00     sll        v1,v1,0x1
     9::800a3f10 23 40 6b 00     subu       t0,v1,t3
     9::800a3f14 c2 47 08 00     srl        t0,t0,0x1f
     9::800a3f18 08 00 e0 03     jr         ra
     9::800a3f1c 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a3f20()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a3f20                           XREF[12]:    FUN_OVR_229__800a3bd0:800a3bdc(j
                                                                                          FUN_OVR_229__800a3be4:800a3bf0(j
                                                                                          FUN_OVR_229__800a3bf8:800a3c04(j
                                                                                          FUN_OVR_229__800a3c20:800a3c18(j
                                                                                          FUN_OVR_229__800a3c20:800a3c2c(j
                                                                                          FUN_OVR_229__800a3c20:800a3c40(j
                                                                                          FUN_OVR_229__800a3c20:800a3c54(j
                                                                                          FUN_OVR_229__800a3c20:800a3c68(j
                                                                                          FUN_OVR_229__800a3c20:800a3c80(c
                                                                                          FUN_OVR_229__800a3c20:800a3c98(c
                                                                                          FUN_OVR_229__800a3c20:800a3d00(c
                                                                                          FUN_OVR_229__800a3c20:800a3d18(c
     9::800a3f20 13 00 6f 82     lb         t7,0x13(s3)
     9::800a3f24 13 00 90 82     lb         s0,0x13(s4)
     9::800a3f28 13 00 b1 82     lb         s1,0x13(s5)
     9::800a3f2c 13 00 d2 82     lb         s2,0x13(s6)
     9::800a3f30 24 18 f0 01     and        v1,t7,s0
     9::800a3f34 24 18 71 00     and        v1,v1,s1
     9::800a3f38 24 18 72 00     and        v1,v1,s2
     9::800a3f3c 22 ff 60 14     bne        v1,zero,LAB_OVR_229__800a3bc8
     9::800a3f40 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a3f44 12 00 90 82     lb         s0,0x12(s4)
     9::800a3f48 12 00 b1 82     lb         s1,0x12(s5)
     9::800a3f4c 12 00 d2 82     lb         s2,0x12(s6)
     9::800a3f50 25 78 f0 01     or         t7,t7,s0
     9::800a3f54 25 78 f1 01     or         t7,t7,s1
     9::800a3f58 25 78 f2 01     or         t7,t7,s2
     9::800a3f5c 2e 00 e0 15     bne        t7,zero,LAB_OVR_229__800a4018
     9::800a3f60 0c 00 03 24     _li        v1,0xc
     9::800a3f64 70 00 2a ac     sw         t2,0x70(at)
     9::800a3f68 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a3f6c 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a3f70 94 01 2a 8c     lw         t2,0x194(at)
     9::800a3f74 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a3f78 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a3f7c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a3f80 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a3f84 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a3f88 06 00 40 4b     NCLIP
     9::800a3f8c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a3f90 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a3f94 23 78 68 01     subu       t7,t3,t0
     9::800a3f98 23 80 88 01     subu       s0,t4,t0
     9::800a3f9c 23 88 a8 01     subu       s1,t5,t0
     9::800a3fa0 23 90 c8 01     subu       s2,t6,t0
     9::800a3fa4 00 c0 08 48     gte_stMAC0 t0
     9::800a3fa8 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a3fac 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a3fb8
     9::800a3fb0 22 40 08 00     _sub       t0,zero,t0
     9::800a3fb4 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a3fb8                           XREF[1]:     OVR_229::800a3fac(j)  
     9::800a3fb8 06 00 40 4b     NCLIP
     9::800a3fbc 24 18 6c 01     and        v1,t3,t4
     9::800a3fc0 24 18 6d 00     and        v1,v1,t5
     9::800a3fc4 24 18 6e 00     and        v1,v1,t6
     9::800a3fc8 25 78 f0 01     or         t7,t7,s0
     9::800a3fcc 25 78 f1 01     or         t7,t7,s1
     9::800a3fd0 27 78 f2 01     nor        t7,t7,s2
     9::800a3fd4 25 78 e3 01     or         t7,t7,v1
     9::800a3fd8 fb fe e0 05     bltz       t7,LAB_OVR_229__800a3bc8
     9::800a3fdc 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a3fe0 f9 fe e0 05     bltz       t7,LAB_OVR_229__800a3bc8
     9::800a3fe4 00 c0 03 48     _gte_stM   v1
     9::800a3fe8 25 40 09 01     or         t0,t0,t1
     9::800a3fec 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a3ff8
     9::800a3ff0 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a3ff4 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a3ff8                           XREF[1]:     OVR_229::800a3fec(j)  
     9::800a3ff8 80 40 08 00     sll        t0,t0,0x2
     9::800a3ffc 25 18 69 00     or         v1,v1,t1
     9::800a4000 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a4004 c0 18 03 00     sll        v1,v1,0x3
     9::800a4008 70 00 2a 8c     lw         t2,0x70(at)
     9::800a400c 25 18 68 00     or         v1,v1,t0
     9::800a4010 24 18 6a 00     and        v1,v1,t2
     9::800a4014 ec fe 60 10     beq        v1,zero,LAB_OVR_229__800a3bc8
                             LAB_OVR_229__800a4018                           XREF[1]:     OVR_229::800a3f5c(j)  
     9::800a4018 70 00 23 ac     _sw        v1,0x70(at)
     9::800a401c 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a4020 24 03 28 24     addiu      t0,at,0x324
     9::800a4024 ea 00 1e 11     beq        t0,s8,LAB_OVR_229__800a43d0
     9::800a4028 04 00 39 27     _addiu     t9,t9,0x4
     9::800a402c 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a4030 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a4034 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a4038 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a403c c0 fe 71 25     addiu      s1,t3,-0x140
     9::800a4040 c0 fe 92 25     addiu      s2,t4,-0x140
     9::800a4044 c0 fe af 25     addiu      t7,t5,-0x140
     9::800a4048 a8 00 01 04     bgez       zero,LAB_OVR_229__800a42ec
     9::800a404c c0 fe d0 25     _addiu     s0,t6,-0x140
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4050()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4050                           XREF[4]:     OVR_229::800a3b78(c), 
                                                                                          OVR_229::800a3b8c(c), 
                                                                                          OVR_229::800a3ba0(c), 
                                                                                          OVR_229::800a3bb4(c)  
     9::800a4050 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a4054 b4 00 ca af     sw         t2,0xb4(s8)
     9::800a4058 06 50 09 01     srlv       t2,t1,t0
     9::800a405c 1f 00 4a 31     andi       t2,t2,0x1f
     9::800a4060 80 50 0a 00     sll        t2,t2,0x2
     9::800a4064 21 50 41 01     addu       t2,t2,at
     9::800a4068 ec 00 4a 8d     lw         t2,0xec(t2)
     9::800a406c 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a4070 94 01 2a ac     sw         t2,0x194(at)
     9::800a4074 02 9e 0a 00     srl        s3,t2,0x18
     9::800a4078 1f 00 73 32     andi       s3,s3,0x1f
     9::800a407c 06 98 63 02     srlv       s3,v1,s3
     9::800a4080 ff 00 73 32     andi       s3,s3,0xff
     9::800a4084 21 98 7e 02     addu       s3,s3,s8
     9::800a4088 02 a4 0a 00     srl        s4,t2,0x10
     9::800a408c 1f 00 94 32     andi       s4,s4,0x1f
     9::800a4090 06 a0 83 02     srlv       s4,v1,s4
     9::800a4094 ff 00 94 32     andi       s4,s4,0xff
     9::800a4098 21 a0 9e 02     addu       s4,s4,s8
     9::800a409c 02 aa 0a 00     srl        s5,t2,0x8
     9::800a40a0 1f 00 b5 32     andi       s5,s5,0x1f
     9::800a40a4 06 a8 a3 02     srlv       s5,v1,s5
     9::800a40a8 ff 00 b5 32     andi       s5,s5,0xff
     9::800a40ac 21 a8 be 02     addu       s5,s5,s8
     9::800a40b0 1f 00 56 31     andi       s6,t2,0x1f
     9::800a40b4 06 b0 c3 02     srlv       s6,v1,s6
     9::800a40b8 ff 00 d6 32     andi       s6,s6,0xff
     9::800a40bc 21 b0 de 02     addu       s6,s6,s8
     9::800a40c0 13 00 6f 82     lb         t7,0x13(s3)
     9::800a40c4 13 00 90 82     lb         s0,0x13(s4)
     9::800a40c8 13 00 b1 82     lb         s1,0x13(s5)
     9::800a40cc 13 00 d2 82     lb         s2,0x13(s6)
     9::800a40d0 24 18 f0 01     and        v1,t7,s0
     9::800a40d4 24 18 71 00     and        v1,v1,s1
     9::800a40d8 24 18 72 00     and        v1,v1,s2
     9::800a40dc ba fe 60 14     bne        v1,zero,LAB_OVR_229__800a3bc8
     9::800a40e0 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a40e4 12 00 90 82     lb         s0,0x12(s4)
     9::800a40e8 12 00 b1 82     lb         s1,0x12(s5)
     9::800a40ec 12 00 d2 82     lb         s2,0x12(s6)
     9::800a40f0 25 78 f0 01     or         t7,t7,s0
     9::800a40f4 25 78 f1 01     or         t7,t7,s1
     9::800a40f8 25 78 f2 01     or         t7,t7,s2
     9::800a40fc 28 00 e0 15     bne        t7,zero,LAB_OVR_229__800a41a0
     9::800a4100 0c 00 03 24     _li        v1,0xc
     9::800a4104 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a4108 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a410c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a4110 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a4114 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a4118 06 00 40 4b     NCLIP
     9::800a411c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a4120 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a4124 23 78 68 01     subu       t7,t3,t0
     9::800a4128 23 80 88 01     subu       s0,t4,t0
     9::800a412c 23 88 a8 01     subu       s1,t5,t0
     9::800a4130 23 90 c8 01     subu       s2,t6,t0
     9::800a4134 00 c0 08 48     gte_stMAC0 t0
     9::800a4138 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a413c 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a4148
     9::800a4140 22 40 08 00     _sub       t0,zero,t0
     9::800a4144 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a4148                           XREF[1]:     OVR_229::800a413c(j)  
     9::800a4148 06 00 40 4b     NCLIP
     9::800a414c 24 18 6c 01     and        v1,t3,t4
     9::800a4150 24 18 6d 00     and        v1,v1,t5
     9::800a4154 24 18 6e 00     and        v1,v1,t6
     9::800a4158 25 78 f0 01     or         t7,t7,s0
     9::800a415c 25 78 f1 01     or         t7,t7,s1
     9::800a4160 27 78 f2 01     nor        t7,t7,s2
     9::800a4164 25 78 e3 01     or         t7,t7,v1
     9::800a4168 97 fe e0 05     bltz       t7,LAB_OVR_229__800a3bc8
     9::800a416c 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a4170 95 fe e0 05     bltz       t7,LAB_OVR_229__800a3bc8
     9::800a4174 00 c0 03 48     _gte_stM   v1
     9::800a4178 25 40 09 01     or         t0,t0,t1
     9::800a417c 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a4188
     9::800a4180 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a4184 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a4188                           XREF[1]:     OVR_229::800a417c(j)  
     9::800a4188 80 40 08 00     sll        t0,t0,0x2
     9::800a418c 25 18 69 00     or         v1,v1,t1
     9::800a4190 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a4194 c0 18 03 00     sll        v1,v1,0x3
     9::800a4198 25 18 68 00     or         v1,v1,t0
     9::800a419c 8a fe 60 10     beq        v1,zero,LAB_OVR_229__800a3bc8
                             LAB_OVR_229__800a41a0                           XREF[1]:     OVR_229::800a40fc(j)  
     9::800a41a0 70 00 23 ac     _sw        v1,0x70(at)
     9::800a41a4 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a41a8 04 00 39 27     addiu      t9,t9,0x4
     9::800a41ac c2 4f 09 00     srl        t1,t1,0x1f
     9::800a41b0 c0 4f 09 00     sll        t1,t1,0x1f
     9::800a41b4 c2 57 0a 00     srl        t2,t2,0x1f
     9::800a41b8 80 57 0a 00     sll        t2,t2,0x1e
     9::800a41bc 25 50 49 01     or         t2,t2,t1
     9::800a41c0 80 00 2a ac     sw         t2,0x80(at)
     9::800a41c4 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a41c8 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a41cc 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a41d0 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a41d4 b4 00 c3 8f     lw         v1,0xb4(s8)
     9::800a41d8 23 50 6c 01     subu       t2,t3,t4
     9::800a41dc 82 48 03 00     srl        t1,v1,0x2
     9::800a41e0 21 48 38 01     addu       t1,t1,t8
     9::800a41e4 18 00 29 81     lb         t1,0x18(t1)
     9::800a41e8 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a41f4
     9::800a41ec 21 e0 60 01     _move      gp,t3
     9::800a41f0 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a41f4                           XREF[1]:     OVR_229::800a41e8(j)  
     9::800a41f4 23 50 8d 03     subu       t2,gp,t5
     9::800a41f8 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a4204
     9::800a41fc 21 18 78 00     _addu      v1,v1,t8
     9::800a4200 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a4204                           XREF[1]:     OVR_229::800a41f8(j)  
     9::800a4204 23 50 8e 03     subu       t2,gp,t6
     9::800a4208 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a4214
     9::800a420c 1c 00 63 8c     _lw        v1,0x1c(v1)
     9::800a4210 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a4214                           XREF[1]:     OVR_229::800a4208(j)  
     9::800a4214 21 50 80 03     move       t2,gp
     9::800a4218 82 e1 1c 00     srl        gp,gp,0x6
     9::800a421c 21 e0 89 03     addu       gp,gp,t1
     9::800a4220 01 00 69 30     andi       t1,v1,0x1
     9::800a4224 02 00 20 11     beq        t1,zero,LAB_OVR_229__800a4230
     9::800a4228 80 e0 1c 00     _sll       gp,gp,0x2
     9::800a422c ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_229__800a4230                           XREF[1]:     OVR_229::800a4224(j)  
     9::800a4230 02 00 81 07     bgez       gp,LAB_OVR_229__800a423c
     9::800a4234 21 e0 85 03     _addu      gp,gp,a1
     9::800a4238 21 e0 a0 00     move       gp,a1
                             LAB_OVR_229__800a423c                           XREF[1]:     OVR_229::800a4230(j)  
     9::800a423c 24 00 69 8c     lw         t1,0x24(v1)
     9::800a4240 c0 f9 48 25     addiu      t0,t2,-0x640
     9::800a4244 84 00 29 ac     sw         t1,0x84(at)
     9::800a4248 0a 00 01 05     bgez       t0,LAB_OVR_229__800a4274
     9::800a424c 00 fb 48 25     _addiu     t0,t2,-0x500
     9::800a4250 0c 00 63 24     addiu      v1,v1,0xc
     9::800a4254 07 00 01 05     bgez       t0,LAB_OVR_229__800a4274
     9::800a4258 80 fd 48 25     _addiu     t0,t2,-0x280
     9::800a425c 0c 00 63 24     addiu      v1,v1,0xc
     9::800a4260 04 00 01 05     bgez       t0,LAB_OVR_229__800a4274
     9::800a4264 00 00 00 00     _nop
     9::800a4268 02 00 20 05     bltz       t1,LAB_OVR_229__800a4274
     9::800a426c 00 00 00 00     _nop
     9::800a4270 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_229__800a4274                           XREF[4]:     OVR_229::800a4248(j), 
                                                                                          OVR_229::800a4254(j), 
                                                                                          OVR_229::800a4260(j), 
                                                                                          OVR_229::800a4268(j)  
     9::800a4274 94 01 2a 8c     lw         t2,0x194(at)
     9::800a4278 00 00 68 8c     lw         t0,0x0(v1)
     9::800a427c 04 00 69 8c     lw         t1,0x4(v1)
     9::800a4280 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a4284 ac 01 28 ac     sw         t0,0x1ac(at)
     9::800a4288 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a428c 00 52 0a 00     sll        t2,t2,0x8
     9::800a4290 0a 00 40 05     bltz       t2,LAB_OVR_229__800a42bc
     9::800a4294 b0 01 29 ac     _sw        t1,0x1b0(at)
     9::800a4298 06 00 68 a6     sh         t0,0x6(s3)
     9::800a429c 08 00 68 8c     lw         t0,0x8(v1)
     9::800a42a0 06 00 89 a6     sh         t1,0x6(s4)
     9::800a42a4 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a42a8 00 54 0a 00     sll        t2,t2,0x10
     9::800a42ac 0b 00 40 05     bltz       t2,LAB_OVR_229__800a42dc
     9::800a42b0 02 4c 08 00     _srl       t1,t0,0x10
     9::800a42b4 09 00 01 04     bgez       zero,LAB_OVR_229__800a42dc
     9::800a42b8 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_229__800a42bc                           XREF[1]:     OVR_229::800a4290(j)  
     9::800a42bc 06 00 69 a6     sh         t1,0x6(s3)
     9::800a42c0 08 00 69 8c     lw         t1,0x8(v1)
     9::800a42c4 00 54 0a 00     sll        t2,t2,0x10
     9::800a42c8 06 00 88 a6     sh         t0,0x6(s4)
     9::800a42cc 02 44 09 00     srl        t0,t1,0x10
     9::800a42d0 02 00 40 05     bltz       t2,LAB_OVR_229__800a42dc
     9::800a42d4 06 00 a8 a6     _sh        t0,0x6(s5)
     9::800a42d8 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a42dc                           XREF[3]:     OVR_229::800a42ac(j), 
                                                                                          OVR_229::800a42b4(j), 
                                                                                          OVR_229::800a42d0(j)  
     9::800a42dc 80 fd 71 25     addiu      s1,t3,-0x280
     9::800a42e0 80 fd 92 25     addiu      s2,t4,-0x280
     9::800a42e4 80 fd af 25     addiu      t7,t5,-0x280
     9::800a42e8 80 fd d0 25     addiu      s0,t6,-0x280
                             LAB_OVR_229__800a42ec                           XREF[1]:     FUN_OVR_229__800a3f20:800a4048(j
     9::800a42ec 42 8f 11 00     srl        s1,s1,0x1d
     9::800a42f0 04 00 31 32     andi       s1,s1,0x4
     9::800a42f4 02 97 12 00     srl        s2,s2,0x1c
     9::800a42f8 08 00 52 32     andi       s2,s2,0x8
     9::800a42fc 25 88 32 02     or         s1,s1,s2
     9::800a4300 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a4304 10 00 ef 31     andi       t7,t7,0x10
     9::800a4308 25 88 2f 02     or         s1,s1,t7
     9::800a430c 82 86 10 00     srl        s0,s0,0x1a
     9::800a4310 20 00 10 32     andi       s0,s0,0x20
     9::800a4314 25 88 30 02     or         s1,s1,s0
     9::800a4318 26 00 20 12     beq        s1,zero,LAB_OVR_229__800a43b4
     9::800a431c 21 68 60 02     _move      t5,s3
     9::800a4320 21 70 80 02     move       t6,s4
     9::800a4324 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a4328 00 00 cf 27     addiu      t7,s8,0x0
     9::800a432c 85 8f 02 0c     jal        FUN_OVR_229__800a3e14                            undefined FUN_OVR_229__800a3e14()
     9::800a4330 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a4334 21 68 80 02     move       t5,s4
     9::800a4338 21 70 c0 02     move       t6,s6
     9::800a433c 14 00 cf 27     addiu      t7,s8,0x14
     9::800a4340 85 8f 02 0c     jal        FUN_OVR_229__800a3e14                            undefined FUN_OVR_229__800a3e14()
     9::800a4344 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a4348 21 68 a0 02     move       t5,s5
     9::800a434c 21 70 60 02     move       t6,s3
     9::800a4350 28 00 cf 27     addiu      t7,s8,0x28
     9::800a4354 85 8f 02 0c     jal        FUN_OVR_229__800a3e14                            undefined FUN_OVR_229__800a3e14()
     9::800a4358 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a435c 21 68 c0 02     move       t5,s6
     9::800a4360 21 70 a0 02     move       t6,s5
     9::800a4364 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a4368 85 8f 02 0c     jal        FUN_OVR_229__800a3e14                            undefined FUN_OVR_229__800a3e14()
     9::800a436c a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a4370 21 68 80 02     move       t5,s4
     9::800a4374 21 70 a0 02     move       t6,s5
     9::800a4378 14 00 cf 27     addiu      t7,s8,0x14
     9::800a437c 85 8f 02 0c     jal        FUN_OVR_229__800a3e14                            undefined FUN_OVR_229__800a3e14()
     9::800a4380 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a4384 21 18 21 02     addu       v1,s1,at
     9::800a4388 48 01 63 8c     lw         v1,0x148(v1)
     9::800a438c 0a 80 08 3c     lui        t0,0x800a
     9::800a4390 a4 43 08 25     addiu      t0,t0,0x43a4
     9::800a4394 9c 00 23 ac     sw         v1,0x9c(at)
     9::800a4398 3c 00 28 af     sw         t0=>LAB_OVR_229__800a43a4,0x3c(t9)
     9::800a439c 08 00 60 00     jr         v1
     9::800a43a0 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a43a4                           XREF[1]:     FUN_OVR_229__800a4050:800a4398(*
     9::800a43a4 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a43a8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a43ac 08 00 e0 03     jr         ra
     9::800a43b0 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a43b4                           XREF[1]:     OVR_229::800a4318(j)  
     9::800a43b4 70 00 23 8c     lw         v1,0x70(at)
     9::800a43b8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a43bc 21 18 61 00     addu       v1,v1,at
     9::800a43c0 84 01 63 8c     lw         v1,0x184(v1)
     9::800a43c4 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a43c8 08 00 60 00     jr         v1
     9::800a43cc 00 00 00 00     _nop
                             LAB_OVR_229__800a43d0                           XREF[1]:     OVR_229::800a4024(j)  
     9::800a43d0 84 00 23 8c     lw         v1,0x84(at)
     9::800a43d4 24 03 2a 24     addiu      t2,at,0x324
     9::800a43d8 26 00 60 1c     bgtz       v1,LAB_OVR_229__800a4474
     9::800a43dc 20 03 28 8c     _lw        t0,0x320(at)
     9::800a43e0 d8 03 29 8c     lw         t1,0x3d8(at)
     9::800a43e4 16 00 5e 15     bne        t2,s8,LAB_OVR_229__800a4440
     9::800a43e8 9c 00 23 8c     _lw        v1,0x9c(at)
     9::800a43ec 0a 80 0a 3c     lui        t2,0x800a
     9::800a43f0 d0 3d 4a 25     addiu      t2,t2,0x3dd0
     9::800a43f4 1f 00 6a 14     bne        v1,t2,LAB_OVR_229__800a4474
     9::800a43f8 94 01 23 8c     _lw        v1,0x194(at)
     9::800a43fc 40 40 08 00     sll        t0,t0,0x1
     9::800a4400 00 1a 03 00     sll        v1,v1,0x8
     9::800a4404 02 00 61 04     bgez       v1,LAB_OVR_229__800a4410
     9::800a4408 84 00 2a 8c     _lw        t2,0x84(at)
     9::800a440c c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_229__800a4410                           XREF[1]:     OVR_229::800a4404(j)  
     9::800a4410 21 40 09 01     addu       t0,t0,t1
     9::800a4414 21 50 48 01     addu       t2,t2,t0
     9::800a4418 00 00 48 8d     lw         t0,0x0(t2)
     9::800a441c 04 00 49 8d     lw         t1,0x4(t2)
     9::800a4420 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a4424 06 00 68 a6     sh         t0,0x6(s3)
     9::800a4428 08 00 48 85     lh         t0,0x8(t2)
     9::800a442c a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a4430 06 00 89 a6     sh         t1,0x6(s4)
     9::800a4434 0a 00 49 85     lh         t1,0xa(t2)
     9::800a4438 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a443c 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a4440                           XREF[2]:     OVR_229::800a43e4(j), 
                                                                                          OVR_229::800a4480(j)  
     9::800a4440 70 00 23 8c     lw         v1,0x70(at)
     9::800a4444 00 00 00 00     nop
     9::800a4448 21 18 61 00     addu       v1,v1,at
     9::800a444c 84 01 63 8c     lw         v1,0x184(v1)
     9::800a4450 00 00 00 00     nop
     9::800a4454 09 f8 60 00     jalr       v1
     9::800a4458 fc ff 39 27     _addiu     t9,t9,-0x4
     9::800a445c 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a4460 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a4464 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a4468 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a446c 08 00 e0 03     jr         ra
     9::800a4470 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_229__800a4474                           XREF[2]:     OVR_229::800a43d8(j), 
                                                                                          OVR_229::800a43f4(j)  
     9::800a4474 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a4478 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a447c a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a4480 ef ff 01 04     bgez       zero,LAB_OVR_229__800a4440
     9::800a4484 a4 01 29 ac     _sw        t1,0x1a4(at)
     9::800a4488 21 98 80 02     move       s3,s4
     9::800a448c 21 a0 c0 02     move       s4,s6
     9::800a4490 13 00 6f 82     lb         t7,0x13(s3)
     9::800a4494 13 00 90 82     lb         s0,0x13(s4)
     9::800a4498 13 00 b1 82     lb         s1,0x13(s5)
     9::800a449c 24 18 f0 01     and        v1,t7,s0
     9::800a44a0 24 18 71 00     and        v1,v1,s1
     9::800a44a4 c8 fd 60 04     bltz       v1,LAB_OVR_229__800a3bc8
     9::800a44a8 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a44ac 12 00 90 82     lb         s0,0x12(s4)
     9::800a44b0 12 00 b1 82     lb         s1,0x12(s5)
     9::800a44b4 25 78 f0 01     or         t7,t7,s0
     9::800a44b8 25 78 f1 01     or         t7,t7,s1
     9::800a44bc 62 00 e0 05     bltz       t7,LAB_OVR_229__800a4648
     9::800a44c0 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a44c4 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a44c8 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a44cc 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a44d0 08 00 90 8e     lw         s0,0x8(s4)
     9::800a44d4 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a44d8 06 00 73 86     lh         s3,0x6(s3)
     9::800a44dc 06 00 94 86     lh         s4,0x6(s4)
     9::800a44e0 06 00 b5 86     lh         s5,0x6(s5)
     9::800a44e4 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a44e8 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a44ec a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a44f0 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a44f4 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a44f8 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a44fc 60 00 03 3c     lui        v1,0x60
     9::800a4500 24 48 83 02     and        t1,s4,v1
     9::800a4504 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a4510
     9::800a4508 00 36 03 3c     _lui       v1,0x3600
     9::800a450c 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a4510                           XREF[1]:     OVR_229::800a4504(j)  
     9::800a4510 25 18 6f 00     or         v1,v1,t7
     9::800a4514 04 00 43 ac     sw         v1,0x4(v0)
     9::800a4518 08 00 4b ac     sw         t3,0x8(v0)
     9::800a451c 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a4520 10 00 50 ac     sw         s0,0x10(v0)
     9::800a4524 14 00 4c ac     sw         t4,0x14(v0)
     9::800a4528 18 00 54 ac     sw         s4,0x18(v0)
     9::800a452c 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a4530 20 00 4d ac     sw         t5,0x20(v0)
     9::800a4534 24 00 55 ac     sw         s5,0x24(v0)
     9::800a4538 28 00 09 24     li         t1,0x28
     9::800a453c 39 00 01 04     bgez       zero,LAB_OVR_229__800a4624
     9::800a4540 00 09 0a 3c     _lui       t2,0x900
     9::800a4544 13 00 6f 82     lb         t7,0x13(s3)
     9::800a4548 13 00 90 82     lb         s0,0x13(s4)
     9::800a454c 13 00 b1 82     lb         s1,0x13(s5)
     9::800a4550 13 00 d2 82     lb         s2,0x13(s6)
     9::800a4554 24 18 f0 01     and        v1,t7,s0
     9::800a4558 24 18 71 00     and        v1,v1,s1
     9::800a455c 24 18 72 00     and        v1,v1,s2
     9::800a4560 99 fd 60 14     bne        v1,zero,LAB_OVR_229__800a3bc8
     9::800a4564 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a4568 12 00 90 82     lb         s0,0x12(s4)
     9::800a456c 12 00 b1 82     lb         s1,0x12(s5)
     9::800a4570 12 00 d2 82     lb         s2,0x12(s6)
     9::800a4574 25 78 f0 01     or         t7,t7,s0
     9::800a4578 25 78 f1 01     or         t7,t7,s1
     9::800a457c 25 78 f2 01     or         t7,t7,s2
     9::800a4580 5a 00 e0 15     bne        t7,zero,LAB_OVR_229__800a46ec
     9::800a4584 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a4588 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a458c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a4590 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a4594 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a4598 08 00 90 8e     lw         s0,0x8(s4)
     9::800a459c 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a45a0 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a45a4 06 00 73 86     lh         s3,0x6(s3)
     9::800a45a8 06 00 94 86     lh         s4,0x6(s4)
     9::800a45ac 06 00 b5 86     lh         s5,0x6(s5)
     9::800a45b0 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a45b4 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a45b8 06 00 d4 86     lh         s4,0x6(s6)
     9::800a45bc a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a45c0 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a45c4 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a45c8 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a45cc a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a45d0 60 00 03 3c     lui        v1,0x60
     9::800a45d4 24 48 83 02     and        t1,s4,v1
     9::800a45d8 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a45e4
     9::800a45dc 00 3e 03 3c     _lui       v1,0x3e00
     9::800a45e0 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a45e4                           XREF[1]:     OVR_229::800a45d8(j)  
     9::800a45e4 25 18 6f 00     or         v1,v1,t7
     9::800a45e8 04 00 43 ac     sw         v1,0x4(v0)
     9::800a45ec 08 00 4b ac     sw         t3,0x8(v0)
     9::800a45f0 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a45f4 10 00 50 ac     sw         s0,0x10(v0)
     9::800a45f8 14 00 4c ac     sw         t4,0x14(v0)
     9::800a45fc 18 00 54 ac     sw         s4,0x18(v0)
     9::800a4600 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a4604 20 00 4d ac     sw         t5,0x20(v0)
     9::800a4608 24 00 55 ac     sw         s5,0x24(v0)
     9::800a460c 28 00 52 ac     sw         s2,0x28(v0)
     9::800a4610 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a4614 02 1c 15 00     srl        v1,s5,0x10
     9::800a4618 30 00 43 ac     sw         v1,0x30(v0)
     9::800a461c 34 00 09 24     li         t1,0x34
     9::800a4620 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a4624                           XREF[1]:     OVR_229::800a453c(j)  
     9::800a4624 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a4628 00 42 02 00     sll        t0,v0,0x8
     9::800a462c 02 42 08 00     srl        t0,t0,0x8
     9::800a4630 25 18 6a 00     or         v1,v1,t2
     9::800a4634 00 00 43 ac     sw         v1,0x0(v0)
     9::800a4638 21 10 49 00     addu       v0,v0,t1
     9::800a463c 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a4640 08 00 e0 03     jr         ra
     9::800a4644 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_229__800a4648                           XREF[1]:     OVR_229::800a44bc(j)  
     9::800a4648 58 00 3f ac     sw         ra,0x58(at)
     9::800a464c 98 01 2f 84     lh         t7,0x198(at)
     9::800a4650 9a 01 30 84     lh         s0,0x19a(at)
     9::800a4654 9c 01 31 84     lh         s1,0x19c(at)
     9::800a4658 00 00 63 86     lh         v1,0x0(s3)
     9::800a465c 02 00 68 86     lh         t0,0x2(s3)
     9::800a4660 ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a4664 04 00 69 86     _lh        t1,0x4(s3)
     9::800a4668 0b 00 40 05     bltz       t2,LAB_OVR_229__800a4698
     9::800a466c 00 00 83 86     _lh        v1,0x0(s4)
     9::800a4670 02 00 88 86     lh         t0,0x2(s4)
     9::800a4674 ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a4678 04 00 89 86     _lh        t1,0x4(s4)
     9::800a467c 06 00 40 05     bltz       t2,LAB_OVR_229__800a4698
     9::800a4680 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a4684 02 00 a8 86     lh         t0,0x2(s5)
     9::800a4688 ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a468c 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a4690 58 00 3f 8c     lw         ra,0x58(at)
     9::800a4694 4c fd 41 05     bgez       t2,LAB_OVR_229__800a3bc8
                             LAB_OVR_229__800a4698                           XREF[2]:     OVR_229::800a4668(j), 
                                                                                          OVR_229::800a467c(j)  
     9::800a4698 10 00 2f 8c     lw         t7,0x10(at)
     9::800a469c 80 00 23 8c     lw         v1,0x80(at)
     9::800a46a0 a6 01 28 84     lh         t0,0x1a6(at)
     9::800a46a4 a2 01 29 84     lh         t1,0x1a2(at)
     9::800a46a8 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a46ac 00 00 e3 ad     sw         v1,0x0(t7)
     9::800a46b0 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a46b4 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a46b8 21 68 60 02     move       t5,s3
     9::800a46bc fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a46c0 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a46c4 21 68 80 02     move       t5,s4
     9::800a46c8 fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a46cc 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a46d0 21 68 a0 02     move       t5,s5
     9::800a46d4 fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a46d8 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a46dc 58 00 3f 8c     lw         ra,0x58(at)
     9::800a46e0 30 00 ef 25     addiu      t7,t7,0x30
     9::800a46e4 08 00 e0 03     jr         ra
     9::800a46e8 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_229__800a46ec                           XREF[1]:     OVR_229::800a4580(j)  
     9::800a46ec 58 00 3f ac     sw         ra,0x58(at)
     9::800a46f0 98 01 2f 84     lh         t7,0x198(at)
     9::800a46f4 9a 01 30 84     lh         s0,0x19a(at)
     9::800a46f8 9c 01 31 84     lh         s1,0x19c(at)
     9::800a46fc 00 00 63 86     lh         v1,0x0(s3)
     9::800a4700 02 00 68 86     lh         t0,0x2(s3)
     9::800a4704 ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a4708 04 00 69 86     _lh        t1,0x4(s3)
     9::800a470c 10 00 40 05     bltz       t2,LAB_OVR_229__800a4750
     9::800a4710 00 00 83 86     _lh        v1,0x0(s4)
     9::800a4714 02 00 88 86     lh         t0,0x2(s4)
     9::800a4718 ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a471c 04 00 89 86     _lh        t1,0x4(s4)
     9::800a4720 0b 00 40 05     bltz       t2,LAB_OVR_229__800a4750
     9::800a4724 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a4728 02 00 a8 86     lh         t0,0x2(s5)
     9::800a472c ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a4730 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a4734 06 00 40 05     bltz       t2,LAB_OVR_229__800a4750
     9::800a4738 00 00 c3 86     _lh        v1,0x0(s6)
     9::800a473c 02 00 c8 86     lh         t0,0x2(s6)
     9::800a4740 ed 91 02 0c     jal        FUN_OVR_229__800a47b4                            undefined FUN_OVR_229__800a47b4()
     9::800a4744 04 00 c9 86     _lh        t1,0x4(s6)
     9::800a4748 58 00 3f 8c     lw         ra,0x58(at)
     9::800a474c 1e fd 41 05     bgez       t2,LAB_OVR_229__800a3bc8
                             LAB_OVR_229__800a4750                           XREF[3]:     OVR_229::800a470c(j), 
                                                                                          OVR_229::800a4720(j), 
                                                                                          OVR_229::800a4734(j)  
     9::800a4750 10 00 2f 8c     lw         t7,0x10(at)
     9::800a4754 80 00 23 8c     lw         v1,0x80(at)
     9::800a4758 a6 01 28 84     lh         t0,0x1a6(at)
     9::800a475c a2 01 29 84     lh         t1,0x1a2(at)
     9::800a4760 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a4764 01 00 63 34     ori        v1,v1,0x1
     9::800a4768 00 00 e3 ad     sw         v1,0x0(t7)
     9::800a476c 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a4770 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a4774 21 68 60 02     move       t5,s3
     9::800a4778 fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a477c 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a4780 21 68 80 02     move       t5,s4
     9::800a4784 fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a4788 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a478c 21 68 a0 02     move       t5,s5
     9::800a4790 fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a4794 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a4798 21 68 c0 02     move       t5,s6
     9::800a479c fd 91 02 0c     jal        FUN_OVR_229__800a47f4                            undefined FUN_OVR_229__800a47f4()
     9::800a47a0 30 00 f0 25     _addiu     s0,t7,0x30
     9::800a47a4 58 00 3f 8c     lw         ra,0x58(at)
     9::800a47a8 3c 00 ef 25     addiu      t7,t7,0x3c
     9::800a47ac 08 00 e0 03     jr         ra
     9::800a47b0 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a47b4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a47b4                           XREF[7]:     FUN_OVR_229__800a3f20:800a4660(c
                                                                                          FUN_OVR_229__800a3f20:800a4674(c
                                                                                          FUN_OVR_229__800a3f20:800a4688(c
                                                                                          FUN_OVR_229__800a3f20:800a4704(c
                                                                                          FUN_OVR_229__800a3f20:800a4718(c
                                                                                          FUN_OVR_229__800a3f20:800a472c(c
                                                                                          FUN_OVR_229__800a3f20:800a4740(c
     9::800a47b4 23 18 6f 00     subu       v1,v1,t7
     9::800a47b8 02 00 61 04     bgez       v1,LAB_OVR_229__800a47c4
     9::800a47bc 23 40 10 01     _subu      t0,t0,s0
     9::800a47c0 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_229__800a47c4                           XREF[1]:     OVR_229::800a47b8(j)  
     9::800a47c4 00 ff 6b 24     addiu      t3,v1,-0x100
     9::800a47c8 02 00 01 05     bgez       t0,LAB_OVR_229__800a47d4
     9::800a47cc 23 48 31 01     _subu      t1,t1,s1
     9::800a47d0 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_229__800a47d4                           XREF[1]:     OVR_229::800a47c8(j)  
     9::800a47d4 80 fe 0c 25     addiu      t4,t0,-0x180
     9::800a47d8 02 00 21 05     bgez       t1,LAB_OVR_229__800a47e4
     9::800a47dc 00 00 00 00     _nop
     9::800a47e0 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_229__800a47e4                           XREF[1]:     OVR_229::800a47d8(j)  
     9::800a47e4 00 ff 2d 25     addiu      t5,t1,-0x100
     9::800a47e8 24 58 6c 01     and        t3,t3,t4
     9::800a47ec 08 00 e0 03     jr         ra
     9::800a47f0 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a47f4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a47f4                           XREF[7]:     FUN_OVR_229__800a3f20:800a46bc(c
                                                                                          FUN_OVR_229__800a3f20:800a46c8(c
                                                                                          FUN_OVR_229__800a3f20:800a46d4(c
                                                                                          FUN_OVR_229__800a3f20:800a4778(c
                                                                                          FUN_OVR_229__800a3f20:800a4784(c
                                                                                          FUN_OVR_229__800a3f20:800a4790(c
                                                                                          FUN_OVR_229__800a3f20:800a479c(c
     9::800a47f4 13 00 a3 81     lb         v1,0x13(t5)
     9::800a47f8 00 00 a8 8d     lw         t0,0x0(t5)
     9::800a47fc 04 00 a9 8d     lw         t1,0x4(t5)
     9::800a4800 08 00 aa 8d     lw         t2,0x8(t5)
     9::800a4804 00 1e 03 00     sll        v1,v1,0x18
     9::800a4808 25 50 43 01     or         t2,t2,v1
     9::800a480c 00 00 08 ae     sw         t0,0x0(s0)
     9::800a4810 04 00 09 ae     sw         t1,0x4(s0)
     9::800a4814 08 00 e0 03     jr         ra
     9::800a4818 08 00 0a ae     _sw        t2,0x8(s0)
     9::800a481c 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_229__800a4820                           XREF[1]:     OVR_229::800a4cd4(j)  
     9::800a4820 34 01 80 10     beq        a0,zero,LAB_OVR_229__800a4cf4
     9::800a4824 00 00 00 00     _nop
     9::800a4828 1c 00 78 8c     lw         t8,0x1c(v1)
     9::800a482c 18 00 79 8c     lw         t9,0x18(v1)
     9::800a4830 c8 00 2a 8c     lw         t2,0xc8(at)
     9::800a4834 3c 00 08 97     lhu        t0,0x3c(t8)
     9::800a4838 68 00 39 ac     sw         t9,0x68(at)
     9::800a483c c2 48 08 00     srl        t1,t0,0x3
     9::800a4840 fc 01 29 31     andi       t1,t1,0x1fc
     9::800a4844 21 48 2a 01     addu       t1,t1,t2
     9::800a4848 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a484c 00 00 29 8d     lw         t1,0x0(t1)
     9::800a4850 1f 00 08 31     andi       t0,t0,0x1f
     9::800a4854 bc 00 28 ac     sw         t0,0xbc(at)
     9::800a4858 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_229__800a485c                           XREF[1]:     OVR_229::800a4cc8(j)  
     9::800a485c 30 00 23 8c     lw         v1,0x30(at)
     9::800a4860 40 37 48 24     addiu      t0,v0,0x3740
     9::800a4864 23 18 68 00     subu       v1,v1,t0
     9::800a4868 f0 f1 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a486c bc 00 23 8c     _lw        v1,0xbc(at)
     9::800a4870 c4 00 28 8c     lw         t0,0xc4(at)
     9::800a4874 06 00 61 04     bgez       v1,LAB_OVR_229__800a4890
     9::800a4878 c0 00 29 8c     _lw        t1,0xc0(at)
     9::800a487c 1f 00 03 24     li         v1,0x1f
     9::800a4880 04 00 28 8d     lw         t0,0x4(t1)
     9::800a4884 04 00 29 25     addiu      t1,t1,0x4
     9::800a4888 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a488c c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_229__800a4890                           XREF[1]:     OVR_229::800a4874(j)  
     9::800a4890 04 40 68 00     sllv       t0,t0,v1
     9::800a4894 ff ff 63 24     addiu      v1,v1,-0x1
     9::800a4898 08 01 01 05     bgez       t0,LAB_OVR_229__800a4cbc
     9::800a489c bc 00 23 ac     _sw        v1,0xbc(at)
     9::800a48a0 b4 01 3e 24     addiu      s8,at,0x1b4
     9::800a48a4 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a48a8 00 00 14 8f     lw         s4,0x0(t8)
     9::800a48ac 04 00 16 8f     lw         s6,0x4(t8)
     9::800a48b0 ff ff 93 32     andi       s3,s4,0xffff
     9::800a48b4 00 99 13 00     sll        s3,s3,0x4
     9::800a48b8 21 98 77 02     addu       s3,s3,s7
     9::800a48bc 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a48c4 02 a4 14 00     srl        s4,s4,0x10
     9::800a48c8 00 a1 14 00     sll        s4,s4,0x4
     9::800a48cc 21 a0 97 02     addu       s4,s4,s7
     9::800a48d0 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a48d8 ff ff d5 32     andi       s5,s6,0xffff
     9::800a48dc 00 a9 15 00     sll        s5,s5,0x4
     9::800a48e0 21 a8 b7 02     addu       s5,s5,s7
     9::800a48e4 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a48ec 02 b4 16 00     srl        s6,s6,0x10
     9::800a48f0 00 b1 16 00     sll        s6,s6,0x4
     9::800a48f4 30 00 28 4a     RTPT
     9::800a48f8 21 b0 d7 02     addu       s6,s6,s7
     9::800a48fc 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a4900 08 00 90 8e     lw         s0,0x8(s4)
     9::800a4904 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a4908 08 00 cf af     sw         t7,0x8(s8)
     9::800a490c 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a4910 30 00 d1 af     sw         s1,0x30(s8)
     9::800a4914 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a4918 00 f8 43 48     gte_stFLAG v1
     9::800a491c 10 00 d1 eb     gte_stSZ1  0x10(s8)
     9::800a4920 80 1b 03 00     sll        v1,v1,0xe
     9::800a4924 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a4928 ec 00 60 14     bne        v1,zero,LAB_OVR_229__800a4cdc
     9::800a492c 08 00 14 8f     _lw        s4,0x8(t8)
     9::800a4930 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a4934 24 00 d2 eb     gte_stSZ2  0x24(s8)
     9::800a4938 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a493c 38 00 d3 eb     gte_stSZ3  0x38(s8)
     9::800a4940 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a4944 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a4948 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a494c 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a4950 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a4954 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a4958 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a4960 14 00 09 8f     lw         t1,0x14(t8)
     9::800a4964 ff ff 93 32     andi       s3,s4,0xffff
     9::800a4968 00 99 13 00     sll        s3,s3,0x4
     9::800a496c 21 98 77 02     addu       s3,s3,s7
     9::800a4970 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a4978 02 a4 14 00     srl        s4,s4,0x10
     9::800a497c 00 a1 14 00     sll        s4,s4,0x4
     9::800a4980 21 a0 97 02     addu       s4,s4,s7
     9::800a4984 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a498c 21 c8 20 00     move       t9,at
     9::800a4990 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a4994 30 00 28 4a     RTPT
     9::800a4998 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a499c 08 00 70 8e     lw         s0,0x8(s3)
     9::800a49a0 08 00 91 8e     lw         s1,0x8(s4)
     9::800a49a4 44 00 cf af     sw         t7,0x44(s8)
     9::800a49a8 58 00 d0 af     sw         s0,0x58(s8)
     9::800a49ac 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a49b0 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a49b4 00 f8 43 48     gte_stFLAG v1
     9::800a49b8 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     9::800a49bc 80 1b 03 00     sll        v1,v1,0xe
     9::800a49c0 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a49c4 c5 00 60 14     bne        v1,zero,LAB_OVR_229__800a4cdc
     9::800a49c8 5c 00 cd eb     _gte_stS   0x5c(s8)
     9::800a49cc 60 00 d2 eb     gte_stSZ2  0x60(s8)
     9::800a49d0 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a49d4 74 00 d3 eb     gte_stSZ3  0x74(s8)
     9::800a49d8 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a49dc 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a49e0 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a49e4 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a49e8 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a49ec 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a49f0 40 00 03 8f     lw         v1,0x40(t8)
     9::800a49f4 00 00 d3 27     addiu      s3,s8,0x0
     9::800a49f8 14 00 d4 27     addiu      s4,s8,0x14
     9::800a49fc 28 00 d5 27     addiu      s5,s8,0x28
     9::800a4a00 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a4a04 00 00 68 8c     lw         t0,0x0(v1)
     9::800a4a08 04 00 69 8c     lw         t1,0x4(v1)
     9::800a4a0c 08 00 6a 8c     lw         t2,0x8(v1)
     9::800a4a10 94 01 20 ac     sw         zero,0x194(at)
     9::800a4a14 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a4a18 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a4a1c a8 01 2a ac     sw         t2,0x1a8(at)
     9::800a4a20 06 00 68 a6     sh         t0,0x6(s3)
     9::800a4a24 06 00 89 a6     sh         t1,0x6(s4)
     9::800a4a28 06 00 aa a6     sh         t2,0x6(s5)
     9::800a4a2c 02 54 0a 00     srl        t2,t2,0x10
     9::800a4a30 06 00 ca a6     sh         t2,0x6(s6)
     9::800a4a34 10 00 cb 8f     lw         t3,0x10(s8)
     9::800a4a38 24 00 cc 8f     lw         t4,0x24(s8)
     9::800a4a3c 38 00 cd 8f     lw         t5,0x38(s8)
     9::800a4a40 4c 00 ce 8f     lw         t6,0x4c(s8)
     9::800a4a44 23 18 6c 01     subu       v1,t3,t4
     9::800a4a48 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a4a54
     9::800a4a4c 21 e0 60 01     _move      gp,t3
     9::800a4a50 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a4a54                           XREF[1]:     OVR_229::800a4a48(j)  
     9::800a4a54 23 18 8d 03     subu       v1,gp,t5
     9::800a4a58 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a4a64
     9::800a4a5c 7c 00 29 80     _lb        t1,0x7c(at)
     9::800a4a60 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a4a64                           XREF[1]:     OVR_229::800a4a58(j)  
     9::800a4a64 23 18 8e 03     subu       v1,gp,t6
     9::800a4a68 02 00 60 1c     bgtz       v1,LAB_OVR_229__800a4a74
     9::800a4a6c 82 e1 1c 00     _srl       gp,gp,0x6
     9::800a4a70 82 e1 0e 00     srl        gp,t6,0x6
                             LAB_OVR_229__800a4a74                           XREF[1]:     OVR_229::800a4a68(j)  
     9::800a4a74 21 e0 89 03     addu       gp,gp,t1
     9::800a4a78 80 e0 1c 00     sll        gp,gp,0x2
     9::800a4a7c 21 e0 85 03     addu       gp,gp,a1
     9::800a4a80 80 f8 71 25     addiu      s1,t3,-0x780
     9::800a4a84 80 f8 92 25     addiu      s2,t4,-0x780
     9::800a4a88 80 f8 af 25     addiu      t7,t5,-0x780
     9::800a4a8c 80 f8 d0 25     addiu      s0,t6,-0x780
     9::800a4a90 42 8f 11 00     srl        s1,s1,0x1d
     9::800a4a94 04 00 31 32     andi       s1,s1,0x4
     9::800a4a98 02 97 12 00     srl        s2,s2,0x1c
     9::800a4a9c 08 00 52 32     andi       s2,s2,0x8
     9::800a4aa0 25 88 32 02     or         s1,s1,s2
     9::800a4aa4 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a4aa8 10 00 ef 31     andi       t7,t7,0x10
     9::800a4aac 25 88 2f 02     or         s1,s1,t7
     9::800a4ab0 82 86 10 00     srl        s0,s0,0x1a
     9::800a4ab4 20 00 10 32     andi       s0,s0,0x20
     9::800a4ab8 25 88 30 02     or         s1,s1,s0
     9::800a4abc 55 00 20 12     beq        s1,zero,LAB_OVR_229__800a4c14
     9::800a4ac0 21 c8 20 00     _move      t9,at
     9::800a4ac4 21 58 21 02     addu       t3,s1,at
     9::800a4ac8 48 01 6b 8d     lw         t3,0x148(t3)
     9::800a4acc 0c 00 14 8f     lw         s4,0xc(t8)
     9::800a4ad0 10 00 15 97     lhu        s5,0x10(t8)
     9::800a4ad4 ff ff 93 32     andi       s3,s4,0xffff
     9::800a4ad8 00 99 13 00     sll        s3,s3,0x4
     9::800a4adc 21 98 77 02     addu       s3,s3,s7
     9::800a4ae0 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a4ae8 02 a4 14 00     srl        s4,s4,0x10
     9::800a4aec 00 a1 14 00     sll        s4,s4,0x4
     9::800a4af0 21 a0 97 02     addu       s4,s4,s7
     9::800a4af4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a4afc 00 a9 15 00     sll        s5,s5,0x4
     9::800a4b00 21 a8 b7 02     addu       s5,s5,s7
     9::800a4b04 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a4b0c 0a 80 03 3c     lui        v1,0x800a
     9::800a4b10 bc 4c 63 24     addiu      v1,v1,0x4cbc
     9::800a4b14 30 00 28 4a     RTPT
     9::800a4b18 3c 00 23 af     sw         v1=>LAB_OVR_229__800a4cbc,0x3c(t9)
     9::800a4b1c 04 00 39 27     addiu      t9,t9,0x4
     9::800a4b20 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a4b24 08 00 90 8e     lw         s0,0x8(s4)
     9::800a4b28 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a4b2c 80 00 cf af     sw         t7,0x80(s8)
     9::800a4b30 94 00 d0 af     sw         s0,0x94(s8)
     9::800a4b34 a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a4b38 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a4b3c 00 f8 43 48     gte_stFLAG v1
     9::800a4b40 88 00 d1 eb     gte_stSZ1  0x88(s8)
     9::800a4b44 80 1b 03 00     sll        v1,v1,0xe
     9::800a4b48 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a4b4c 63 00 60 14     bne        v1,zero,LAB_OVR_229__800a4cdc
     9::800a4b50 98 00 cd eb     _gte_stS   0x98(s8)
     9::800a4b54 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     9::800a4b58 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a4b5c b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     9::800a4b60 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a4b64 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a4b68 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a4b6c 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a4b70 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a4b74 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a4b78 06 00 c3 93     lbu        v1,0x6(s8)
     9::800a4b7c 1a 00 c8 93     lbu        t0,0x1a(s8)
     9::800a4b80 2e 00 c9 93     lbu        t1,0x2e(s8)
     9::800a4b84 42 00 ca 93     lbu        t2,0x42(s8)
     9::800a4b88 21 78 68 00     addu       t7,v1,t0
     9::800a4b8c 21 80 69 00     addu       s0,v1,t1
     9::800a4b90 21 88 09 01     addu       s1,t0,t1
     9::800a4b94 21 90 0a 01     addu       s2,t0,t2
     9::800a4b98 21 18 2a 01     addu       v1,t1,t2
     9::800a4b9c 43 78 0f 00     sra        t7,t7,0x1
     9::800a4ba0 43 80 10 00     sra        s0,s0,0x1
     9::800a4ba4 43 88 11 00     sra        s1,s1,0x1
     9::800a4ba8 43 90 12 00     sra        s2,s2,0x1
     9::800a4bac 43 18 03 00     sra        v1,v1,0x1
     9::800a4bb0 56 00 cf a3     sb         t7,0x56(s8)
     9::800a4bb4 6a 00 d0 a3     sb         s0,0x6a(s8)
     9::800a4bb8 7e 00 d1 a3     sb         s1,0x7e(s8)
     9::800a4bbc 92 00 d2 a3     sb         s2,0x92(s8)
     9::800a4bc0 a6 00 c3 a3     sb         v1,0xa6(s8)
     9::800a4bc4 07 00 c3 93     lbu        v1,0x7(s8)
     9::800a4bc8 1b 00 c8 93     lbu        t0,0x1b(s8)
     9::800a4bcc 2f 00 c9 93     lbu        t1,0x2f(s8)
     9::800a4bd0 43 00 ca 93     lbu        t2,0x43(s8)
     9::800a4bd4 21 78 68 00     addu       t7,v1,t0
     9::800a4bd8 21 80 69 00     addu       s0,v1,t1
     9::800a4bdc 21 88 09 01     addu       s1,t0,t1
     9::800a4be0 21 90 0a 01     addu       s2,t0,t2
     9::800a4be4 21 18 2a 01     addu       v1,t1,t2
     9::800a4be8 43 78 0f 00     sra        t7,t7,0x1
     9::800a4bec 43 80 10 00     sra        s0,s0,0x1
     9::800a4bf0 43 88 11 00     sra        s1,s1,0x1
     9::800a4bf4 43 90 12 00     sra        s2,s2,0x1
     9::800a4bf8 43 18 03 00     sra        v1,v1,0x1
     9::800a4bfc 57 00 cf a3     sb         t7,0x57(s8)
     9::800a4c00 6b 00 d0 a3     sb         s0,0x6b(s8)
     9::800a4c04 7f 00 d1 a3     sb         s1,0x7f(s8)
     9::800a4c08 93 00 d2 a3     sb         s2,0x93(s8)
     9::800a4c0c 08 00 60 01     jr         t3
     9::800a4c10 a7 00 c3 a3     _sb        v1,0xa7(s8)
                             LAB_OVR_229__800a4c14                           XREF[1]:     OVR_229::800a4abc(j)  
     9::800a4c14 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a4c18 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a4c1c 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a4c20 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a4c24 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a4c28 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a4c2c 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a4c30 06 00 40 4b     NCLIP
     9::800a4c34 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a4c38 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a4c3c 23 78 68 01     subu       t7,t3,t0
     9::800a4c40 23 80 88 01     subu       s0,t4,t0
     9::800a4c44 23 88 a8 01     subu       s1,t5,t0
     9::800a4c48 23 90 c8 01     subu       s2,t6,t0
     9::800a4c4c 00 c0 08 48     gte_stMAC0 t0
     9::800a4c50 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a4c54 22 40 08 00     sub        t0,zero,t0
     9::800a4c58 25 40 09 01     or         t0,t0,t1
     9::800a4c5c 06 00 40 4b     NCLIP
     9::800a4c60 24 18 6c 01     and        v1,t3,t4
     9::800a4c64 24 18 6d 00     and        v1,v1,t5
     9::800a4c68 24 18 6e 00     and        v1,v1,t6
     9::800a4c6c 25 78 f0 01     or         t7,t7,s0
     9::800a4c70 25 78 f1 01     or         t7,t7,s1
     9::800a4c74 27 78 f2 01     nor        t7,t7,s2
     9::800a4c78 25 78 e3 01     or         t7,t7,v1
     9::800a4c7c 0f 00 e0 05     bltz       t7,LAB_OVR_229__800a4cbc
     9::800a4c80 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a4c84 0d 00 e0 05     bltz       t7,LAB_OVR_229__800a4cbc
     9::800a4c88 00 c0 03 48     _gte_stM   v1
     9::800a4c8c c2 47 08 00     srl        t0,t0,0x1f
     9::800a4c90 80 40 08 00     sll        t0,t0,0x2
     9::800a4c94 25 18 69 00     or         v1,v1,t1
     9::800a4c98 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a4c9c c0 18 03 00     sll        v1,v1,0x3
     9::800a4ca0 25 18 68 00     or         v1,v1,t0
     9::800a4ca4 05 00 60 10     beq        v1,zero,LAB_OVR_229__800a4cbc
     9::800a4ca8 21 18 61 00     _addu      v1,v1,at
     9::800a4cac 84 01 63 8c     lw         v1,0x184(v1)
     9::800a4cb0 00 00 00 00     nop
     9::800a4cb4 09 f8 60 00     jalr       v1
     9::800a4cb8 00 00 00 00     _nop
                             LAB_OVR_229__800a4cbc                           XREF[7]:     OVR_229::800a4898(j), 
                                                                                          OVR_229::800a4b18(*), 
                                                                                          OVR_229::800a4c7c(j), 
                                                                                          OVR_229::800a4c84(j), 
                                                                                          OVR_229::800a4ca4(j), 
                                                                                          OVR_229::800a4cec(j), 
                                                                                          OVR_229::800a4f60(j)  
     9::800a4cbc 68 00 39 8c     lw         t9,0x68(at)
     9::800a4cc0 5c 00 18 27     addiu      t8,t8,0x5c
     9::800a4cc4 ff ff 39 27     addiu      t9,t9,-0x1
     9::800a4cc8 e4 fe 20 1f     bgtz       t9,LAB_OVR_229__800a485c
     9::800a4ccc 68 00 39 ac     _sw        t9,0x68(at)
     9::800a4cd0 00 00 84 8c     lw         a0,0x0(a0)
     9::800a4cd4 d2 fe 01 04     bgez       zero,LAB_OVR_229__800a4820
     9::800a4cd8 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_229__800a4cdc                           XREF[3]:     OVR_229::800a4928(j), 
                                                                                          OVR_229::800a49c4(j), 
                                                                                          OVR_229::800a4b4c(j)  
     9::800a4cdc 64 00 28 8c     lw         t0,0x64(at)
     9::800a4ce0 00 00 00 00     nop
     9::800a4ce4 00 00 18 ad     sw         t8,0x0(t0)
     9::800a4ce8 04 00 08 25     addiu      t0,t0,0x4
     9::800a4cec f3 ff 01 04     bgez       zero,LAB_OVR_229__800a4cbc
     9::800a4cf0 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_229__800a4cf4                           XREF[1]:     OVR_229::800a4820(j)  
     9::800a4cf4 64 00 28 8c     lw         t0,0x64(at)
     9::800a4cf8 1b f1 01 04     bgez       zero,LAB_OVR_229__800a1168
     9::800a4cfc 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_229__800a4d00                           XREF[6]:     FUN_OVR_229__800a5094:800a5108(j
                                                                                          FUN_OVR_229__800a5094:800a5110(j
                                                                                          FUN_OVR_229__800a5094:800a5144(j
                                                                                          OVR_229::800a5254(j), 
                                                                                          OVR_229::800a525c(j), 
                                                                                          OVR_229::800a5288(j)  
     9::800a4d00 08 00 e0 03     jr         ra
     9::800a4d04 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d08()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d08                           XREF[4]:     FUN_OVR_229__800a4d94:800a4de0(j
                                                                                          FUN_OVR_229__800a4d94:800a4e78(c
                                                                                          FUN_OVR_229__800a4d94:800a4ea0(c
                                                                                          FUN_OVR_229__800a4d94:800a4f6c(c
     9::800a4d08 00 00 d3 27     addiu      s3,s8,0x0
     9::800a4d0c 50 00 d4 27     addiu      s4,s8,0x50
     9::800a4d10 64 00 d5 27     addiu      s5,s8,0x64
     9::800a4d14 df 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d18 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d1c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d1c                           XREF[6]:     FUN_OVR_229__800a4d94:800a4de8(c
                                                                                          FUN_OVR_229__800a4d94:800a4e88(j
                                                                                          FUN_OVR_229__800a4d94:800a4e98(c
                                                                                          FUN_OVR_229__800a4d94:800a4ec8(c
                                                                                          FUN_OVR_229__800a4d94:800a4ee8(c
                                                                                          FUN_OVR_229__800a4d94:800a4f7c(c
     9::800a4d1c 50 00 d3 27     addiu      s3,s8,0x50
     9::800a4d20 14 00 d4 27     addiu      s4,s8,0x14
     9::800a4d24 78 00 d5 27     addiu      s5,s8,0x78
     9::800a4d28 da 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d2c 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d30()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d30                           XREF[6]:     FUN_OVR_229__800a4d94:800a4e10(c
                                                                                          FUN_OVR_229__800a4d94:800a4e70(c
                                                                                          FUN_OVR_229__800a4d94:800a4eb0(j
                                                                                          FUN_OVR_229__800a4d94:800a4ec0(c
                                                                                          FUN_OVR_229__800a4d94:800a4ef0(c
                                                                                          FUN_OVR_229__800a4d94:800a4f8c(c
     9::800a4d30 64 00 d3 27     addiu      s3,s8,0x64
     9::800a4d34 78 00 d4 27     addiu      s4,s8,0x78
     9::800a4d38 28 00 d5 27     addiu      s5,s8,0x28
     9::800a4d3c d5 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d40 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a4d44                           XREF[4]:     OVR_229::800a4e60(j), 
                                                                                          OVR_229::800a4ed8(j), 
                                                                                          OVR_229::800a4f00(j), 
                                                                                          OVR_229::800a4fa4(j)  
     9::800a4d44 78 00 d3 27     addiu      s3,s8,0x78
     9::800a4d48 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a4d4c a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a4d50 d0 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d54 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d58()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d58                           XREF[2]:     FUN_OVR_229__800a4d94:800a4e08(c
                                                                                          FUN_OVR_229__800a4d94:800a4ee0(c
     9::800a4d58 64 00 d3 27     addiu      s3,s8,0x64
     9::800a4d5c 00 00 d4 27     addiu      s4,s8,0x0
     9::800a4d60 78 00 d5 27     addiu      s5,s8,0x78
     9::800a4d64 cb 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d68 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d6c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d6c                           XREF[2]:     FUN_OVR_229__800a4d94:800a4e20(j
                                                                                          FUN_OVR_229__800a4d94:800a4e90(c
     9::800a4d6c 14 00 d3 27     addiu      s3,s8,0x14
     9::800a4d70 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a4d74 78 00 d5 27     addiu      s5,s8,0x78
     9::800a4d78 c6 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d7c a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d80()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d80                           XREF[2]:     FUN_OVR_229__800a4d94:800a4df0(c
                                                                                          FUN_OVR_229__800a4d94:800a4eb8(c
     9::800a4d80 28 00 d3 27     addiu      s3,s8,0x28
     9::800a4d84 00 00 d4 27     addiu      s4,s8,0x0
     9::800a4d88 78 00 d5 27     addiu      s5,s8,0x78
     9::800a4d8c c1 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4d90 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4d94()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4d94                           XREF[2]:     OVR_229::800a4e00(j), 
                                                                                          OVR_229::800a4e68(c)  
     9::800a4d94 28 00 d3 27     addiu      s3,s8,0x28
     9::800a4d98 78 00 d4 27     addiu      s4,s8,0x78
     9::800a4d9c 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a4da0 bc 00 01 04     bgez       zero,FUN_OVR_229__800a5094
     9::800a4da4 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a4da8 50 00 d3 27     addiu      s3,s8,0x50
     9::800a4dac 14 00 d4 27     addiu      s4,s8,0x14
     9::800a4db0 78 00 d5 27     addiu      s5,s8,0x78
     9::800a4db4 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a4db8 25 94 02 0c     jal        FUN_OVR_229__800a5094                            undefined FUN_OVR_229__800a5094()
     9::800a4dbc 0c 00 0a 24     _li        t2,0xc
     9::800a4dc0 64 00 d3 27     addiu      s3,s8,0x64
     9::800a4dc4 78 00 d4 27     addiu      s4,s8,0x78
     9::800a4dc8 28 00 d5 27     addiu      s5,s8,0x28
     9::800a4dcc 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a4dd0 25 94 02 0c     jal        FUN_OVR_229__800a5094                            undefined FUN_OVR_229__800a5094()
     9::800a4dd4 0c 00 0a 24     _li        t2,0xc
     9::800a4dd8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4ddc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4de0 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a4d08
     9::800a4de4 0c 00 0a 24     _li        t2,0xc
     9::800a4de8 47 93 02 0c     jal        FUN_OVR_229__800a4d1c                            undefined FUN_OVR_229__800a4d1c()
     9::800a4dec 0c 00 0a 24     _li        t2,0xc
     9::800a4df0 60 93 02 0c     jal        FUN_OVR_229__800a4d80                            undefined FUN_OVR_229__800a4d80()
     9::800a4df4 0c 00 0a 24     _li        t2,0xc
     9::800a4df8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4dfc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4e00 e4 ff 01 04     bgez       zero,FUN_OVR_229__800a4d94
     9::800a4e04 0c 00 0a 24     _li        t2,0xc
     9::800a4e08 56 93 02 0c     jal        FUN_OVR_229__800a4d58                            undefined FUN_OVR_229__800a4d58()
     9::800a4e0c 0c 00 0a 24     _li        t2,0xc
     9::800a4e10 4c 93 02 0c     jal        FUN_OVR_229__800a4d30                            undefined FUN_OVR_229__800a4d30()
     9::800a4e14 0c 00 0a 24     _li        t2,0xc
     9::800a4e18 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4e1c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4e20 d2 ff 01 04     bgez       zero,FUN_OVR_229__800a4d6c
     9::800a4e24 0c 00 0a 24     _li        t2,0xc
     9::800a4e28 00 00 d3 27     addiu      s3,s8,0x0
     9::800a4e2c 14 00 d4 27     addiu      s4,s8,0x14
     9::800a4e30 78 00 d5 27     addiu      s5,s8,0x78
     9::800a4e34 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a4e38 25 94 02 0c     jal        FUN_OVR_229__800a5094                            undefined FUN_OVR_229__800a5094()
     9::800a4e3c 0c 00 0a 24     _li        t2,0xc
     9::800a4e40 00 00 d3 27     addiu      s3,s8,0x0
     9::800a4e44 78 00 d4 27     addiu      s4,s8,0x78
     9::800a4e48 28 00 d5 27     addiu      s5,s8,0x28
     9::800a4e4c a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a4e50 25 94 02 0c     jal        FUN_OVR_229__800a5094                            undefined FUN_OVR_229__800a5094()
     9::800a4e54 0c 00 0a 24     _li        t2,0xc
     9::800a4e58 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4e5c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4e60 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a4d44
     9::800a4e64 0c 00 0a 24     _li        t2,0xc
     9::800a4e68 65 93 02 0c     jal        FUN_OVR_229__800a4d94                            undefined FUN_OVR_229__800a4d94()
     9::800a4e6c 0c 00 0a 24     _li        t2,0xc
     9::800a4e70 4c 93 02 0c     jal        FUN_OVR_229__800a4d30                            undefined FUN_OVR_229__800a4d30()
     9::800a4e74 04 00 0a 24     _li        t2,0x4
     9::800a4e78 42 93 02 0c     jal        FUN_OVR_229__800a4d08                            undefined FUN_OVR_229__800a4d08()
     9::800a4e7c 0c 00 0a 24     _li        t2,0xc
     9::800a4e80 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4e84 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4e88 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a4d1c
     9::800a4e8c 0c 00 0a 24     _li        t2,0xc
     9::800a4e90 5b 93 02 0c     jal        FUN_OVR_229__800a4d6c                            undefined FUN_OVR_229__800a4d6c()
     9::800a4e94 0c 00 0a 24     _li        t2,0xc
     9::800a4e98 47 93 02 0c     jal        FUN_OVR_229__800a4d1c                            undefined FUN_OVR_229__800a4d1c()
     9::800a4e9c 04 00 0a 24     _li        t2,0x4
     9::800a4ea0 42 93 02 0c     jal        FUN_OVR_229__800a4d08                            undefined FUN_OVR_229__800a4d08()
     9::800a4ea4 0c 00 0a 24     _li        t2,0xc
     9::800a4ea8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4eac fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4eb0 9f ff 01 04     bgez       zero,FUN_OVR_229__800a4d30
     9::800a4eb4 0c 00 0a 24     _li        t2,0xc
     9::800a4eb8 60 93 02 0c     jal        FUN_OVR_229__800a4d80                            undefined FUN_OVR_229__800a4d80()
     9::800a4ebc 0c 00 0a 24     _li        t2,0xc
     9::800a4ec0 4c 93 02 0c     jal        FUN_OVR_229__800a4d30                            undefined FUN_OVR_229__800a4d30()
     9::800a4ec4 08 00 0a 24     _li        t2,0x8
     9::800a4ec8 47 93 02 0c     jal        FUN_OVR_229__800a4d1c                            undefined FUN_OVR_229__800a4d1c()
     9::800a4ecc 0c 00 0a 24     _li        t2,0xc
     9::800a4ed0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4ed4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4ed8 9a ff 01 04     bgez       zero,LAB_OVR_229__800a4d44
     9::800a4edc 0c 00 0a 24     _li        t2,0xc
     9::800a4ee0 56 93 02 0c     jal        FUN_OVR_229__800a4d58                            undefined FUN_OVR_229__800a4d58()
     9::800a4ee4 0c 00 0a 24     _li        t2,0xc
     9::800a4ee8 47 93 02 0c     jal        FUN_OVR_229__800a4d1c                            undefined FUN_OVR_229__800a4d1c()
     9::800a4eec 08 00 0a 24     _li        t2,0x8
     9::800a4ef0 4c 93 02 0c     jal        FUN_OVR_229__800a4d30                            undefined FUN_OVR_229__800a4d30()
     9::800a4ef4 0c 00 0a 24     _li        t2,0xc
     9::800a4ef8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4efc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4f00 90 ff 01 04     bgez       zero,LAB_OVR_229__800a4d44
     9::800a4f04 0c 00 0a 24     _li        t2,0xc
     9::800a4f08 b4 01 23 24     addiu      v1,at,0x1b4
     9::800a4f0c 16 00 7e 14     bne        v1,s8,LAB_OVR_229__800a4f68
     9::800a4f10 50 00 03 3c     _lui       v1,0x50
     9::800a4f14 78 64 63 34     ori        v1,v1,0x6478
     9::800a4f18 08 00 08 24     li         t0,0x8
     9::800a4f1c 60 94 02 0c     jal        FUN_OVR_229__800a5180                            undefined FUN_OVR_229__800a5180()
     9::800a4f20 00 00 0a 24     _li        t2,0x0
     9::800a4f24 14 50 03 3c     lui        v1,0x5014
     9::800a4f28 8c 78 63 34     ori        v1,v1,0x788c
     9::800a4f2c 0d 00 08 24     li         t0,0xd
     9::800a4f30 60 94 02 0c     jal        FUN_OVR_229__800a5180                            undefined FUN_OVR_229__800a5180()
     9::800a4f34 04 00 0a 24     _li        t2,0x4
     9::800a4f38 78 64 03 3c     lui        v1,0x6478
     9::800a4f3c a0 28 63 34     ori        v1,v1,0x28a0
     9::800a4f40 12 00 08 24     li         t0,0x12
     9::800a4f44 60 94 02 0c     jal        FUN_OVR_229__800a5180                            undefined FUN_OVR_229__800a5180()
     9::800a4f48 08 00 0a 24     _li        t2,0x8
     9::800a4f4c 8c 78 03 3c     lui        v1,0x788c
     9::800a4f50 3c a0 63 34     ori        v1,v1,0xa03c
     9::800a4f54 17 00 08 24     li         t0,0x17
     9::800a4f58 60 94 02 0c     jal        FUN_OVR_229__800a5180                            undefined FUN_OVR_229__800a5180()
     9::800a4f5c 0c 00 0a 24     _li        t2,0xc
     9::800a4f60 56 ff 01 04     bgez       zero,LAB_OVR_229__800a4cbc
     9::800a4f64 00 00 00 00     _nop
                             LAB_OVR_229__800a4f68                           XREF[1]:     OVR_229::800a4f0c(j)  
     9::800a4f68 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a4f6c 42 93 02 0c     jal        FUN_OVR_229__800a4d08                            undefined FUN_OVR_229__800a4d08()
     9::800a4f70 0c 00 0a 24     _li        t2,0xc
     9::800a4f74 04 00 03 24     li         v1,0x4
     9::800a4f78 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a4f7c 47 93 02 0c     jal        FUN_OVR_229__800a4d1c                            undefined FUN_OVR_229__800a4d1c()
     9::800a4f80 0c 00 0a 24     _li        t2,0xc
     9::800a4f84 08 00 03 24     li         v1,0x8
     9::800a4f88 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a4f8c 4c 93 02 0c     jal        FUN_OVR_229__800a4d30                            undefined FUN_OVR_229__800a4d30()
     9::800a4f90 0c 00 0a 24     _li        t2,0xc
     9::800a4f94 0c 00 03 24     li         v1,0xc
     9::800a4f98 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a4f9c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a4fa0 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a4fa4 67 ff 01 04     bgez       zero,LAB_OVR_229__800a4d44
     9::800a4fa8 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a4fac()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a4fac                           XREF[5]:     FUN_OVR_229__800a5180:800a5400(c
                                                                                          FUN_OVR_229__800a5180:800a5414(c
                                                                                          FUN_OVR_229__800a5180:800a5428(c
                                                                                          FUN_OVR_229__800a5180:800a543c(c
                                                                                          FUN_OVR_229__800a5180:800a5450(c
     9::800a4fac 00 00 ab 85     lh         t3,0x0(t5)
     9::800a4fb0 00 00 cc 85     lh         t4,0x0(t6)
     9::800a4fb4 00 00 eb a5     sh         t3,0x0(t7)
     9::800a4fb8 21 18 6c 01     addu       v1,t3,t4
     9::800a4fbc 43 18 03 00     sra        v1,v1,0x1
     9::800a4fc0 00 00 03 a6     sh         v1,0x0(s0)
     9::800a4fc4 02 00 ab 85     lh         t3,0x2(t5)
     9::800a4fc8 02 00 cc 85     lh         t4,0x2(t6)
     9::800a4fcc 02 00 eb a5     sh         t3,0x2(t7)
     9::800a4fd0 21 18 6c 01     addu       v1,t3,t4
     9::800a4fd4 43 18 03 00     sra        v1,v1,0x1
     9::800a4fd8 02 00 03 a6     sh         v1,0x2(s0)
     9::800a4fdc 04 00 ab 85     lh         t3,0x4(t5)
     9::800a4fe0 04 00 cc 85     lh         t4,0x4(t6)
     9::800a4fe4 04 00 eb a5     sh         t3,0x4(t7)
     9::800a4fe8 21 18 6c 01     addu       v1,t3,t4
     9::800a4fec 43 18 03 00     sra        v1,v1,0x1
     9::800a4ff0 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a4ff4 00 08 83 48     gte_ldVZ0  v1
     9::800a4ff8 04 00 03 a6     sh         v1,0x4(s0)
     9::800a4ffc 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a5000 01 00 18 4a     RTPS
     9::800a5004 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a5008 08 00 eb a1     sb         t3,0x8(t7)
     9::800a500c 21 18 6c 01     addu       v1,t3,t4
     9::800a5010 43 18 03 00     sra        v1,v1,0x1
     9::800a5014 08 00 03 a2     sb         v1,0x8(s0)
     9::800a5018 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a501c 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a5020 09 00 eb a1     sb         t3,0x9(t7)
     9::800a5024 21 18 6c 01     addu       v1,t3,t4
     9::800a5028 43 18 03 00     sra        v1,v1,0x1
     9::800a502c 09 00 03 a2     sb         v1,0x9(s0)
     9::800a5030 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a5034 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a5038 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a503c 21 18 6c 01     addu       v1,t3,t4
     9::800a5040 43 18 03 00     sra        v1,v1,0x1
     9::800a5044 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a5048 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a504c 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a5050 06 00 eb a1     sb         t3,0x6(t7)
     9::800a5054 21 18 6c 01     addu       v1,t3,t4
     9::800a5058 43 18 03 00     sra        v1,v1,0x1
     9::800a505c 06 00 03 a2     sb         v1,0x6(s0)
     9::800a5060 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a5064 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a5068 07 00 eb a1     sb         t3,0x7(t7)
     9::800a506c 21 18 6c 01     addu       v1,t3,t4
     9::800a5070 43 18 03 00     sra        v1,v1,0x1
     9::800a5074 07 00 03 a2     sb         v1,0x7(s0)
     9::800a5078 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a507c 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a5080 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a5084 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a5088 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a508c 08 00 e0 03     jr         ra
     9::800a5090 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5094()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5094                           XREF[12]:    FUN_OVR_229__800a4d08:800a4d14(j
                                                                                          FUN_OVR_229__800a4d1c:800a4d28(j
                                                                                          FUN_OVR_229__800a4d30:800a4d3c(j
                                                                                          FUN_OVR_229__800a4d94:800a4d50(j
                                                                                          FUN_OVR_229__800a4d58:800a4d64(j
                                                                                          FUN_OVR_229__800a4d6c:800a4d78(j
                                                                                          FUN_OVR_229__800a4d80:800a4d8c(j
                                                                                          FUN_OVR_229__800a4d94:800a4da0(j
                                                                                          FUN_OVR_229__800a4d94:800a4db8(c
                                                                                          FUN_OVR_229__800a4d94:800a4dd0(c
                                                                                          FUN_OVR_229__800a4d94:800a4e38(c
                                                                                          FUN_OVR_229__800a4d94:800a4e50(c
     9::800a5094 70 00 2a ac     sw         t2,0x70(at)
     9::800a5098 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a509c 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a50a0 94 01 2a 8c     lw         t2,0x194(at)
     9::800a50a4 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a50a8 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a50ac 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a50b0 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a50b4 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a50b8 06 00 40 4b     NCLIP
     9::800a50bc 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a50c0 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a50c4 23 78 68 01     subu       t7,t3,t0
     9::800a50c8 23 80 88 01     subu       s0,t4,t0
     9::800a50cc 23 88 a8 01     subu       s1,t5,t0
     9::800a50d0 23 90 c8 01     subu       s2,t6,t0
     9::800a50d4 00 c0 08 48     gte_stMAC0 t0
     9::800a50d8 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a50dc 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a50e8
     9::800a50e0 22 40 08 00     _sub       t0,zero,t0
     9::800a50e4 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a50e8                           XREF[1]:     OVR_229::800a50dc(j)  
     9::800a50e8 06 00 40 4b     NCLIP
     9::800a50ec 24 18 6c 01     and        v1,t3,t4
     9::800a50f0 24 18 6d 00     and        v1,v1,t5
     9::800a50f4 24 18 6e 00     and        v1,v1,t6
     9::800a50f8 25 78 f0 01     or         t7,t7,s0
     9::800a50fc 25 78 f1 01     or         t7,t7,s1
     9::800a5100 27 78 f2 01     nor        t7,t7,s2
     9::800a5104 25 78 e3 01     or         t7,t7,v1
     9::800a5108 fd fe e0 05     bltz       t7,LAB_OVR_229__800a4d00
     9::800a510c 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a5110 fb fe e0 05     bltz       t7,LAB_OVR_229__800a4d00
     9::800a5114 00 c0 03 48     _gte_stM   v1
     9::800a5118 25 40 09 01     or         t0,t0,t1
     9::800a511c 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a5128
     9::800a5120 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a5124 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a5128                           XREF[1]:     OVR_229::800a511c(j)  
     9::800a5128 80 40 08 00     sll        t0,t0,0x2
     9::800a512c 25 18 69 00     or         v1,v1,t1
     9::800a5130 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a5134 c0 18 03 00     sll        v1,v1,0x3
     9::800a5138 70 00 2a 8c     lw         t2,0x70(at)
     9::800a513c 25 18 68 00     or         v1,v1,t0
     9::800a5140 24 18 6a 00     and        v1,v1,t2
     9::800a5144 ee fe 60 10     beq        v1,zero,LAB_OVR_229__800a4d00
     9::800a5148 70 00 23 ac     _sw        v1,0x70(at)
     9::800a514c 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a5150 24 03 28 24     addiu      t0,at,0x324
     9::800a5154 d3 00 1e 11     beq        t0,s8,LAB_OVR_229__800a54a4
     9::800a5158 04 00 39 27     _addiu     t9,t9,0x4
     9::800a515c 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a5160 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a5164 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a5168 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a516c c0 fe 71 25     addiu      s1,t3,-0x140
     9::800a5170 c0 fe 92 25     addiu      s2,t4,-0x140
     9::800a5174 c0 fe af 25     addiu      t7,t5,-0x140
     9::800a5178 91 00 01 04     bgez       zero,LAB_OVR_229__800a53c0
     9::800a517c c0 fe d0 25     _addiu     s0,t6,-0x140
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5180()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5180                           XREF[4]:     FUN_OVR_229__800a4d94:800a4f1c(c
                                                                                          FUN_OVR_229__800a4d94:800a4f30(c
                                                                                          FUN_OVR_229__800a4d94:800a4f44(c
                                                                                          FUN_OVR_229__800a4d94:800a4f58(c
     9::800a5180 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a5184 b4 00 ca af     sw         t2,0xb4(s8)
     9::800a5188 06 50 09 01     srlv       t2,t1,t0
     9::800a518c 1f 00 4a 31     andi       t2,t2,0x1f
     9::800a5190 80 50 0a 00     sll        t2,t2,0x2
     9::800a5194 21 50 41 01     addu       t2,t2,at
     9::800a5198 ec 00 4a 8d     lw         t2,0xec(t2)
     9::800a519c 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a51a0 94 01 2a ac     sw         t2,0x194(at)
     9::800a51a4 02 9e 0a 00     srl        s3,t2,0x18
     9::800a51a8 1f 00 73 32     andi       s3,s3,0x1f
     9::800a51ac 06 98 63 02     srlv       s3,v1,s3
     9::800a51b0 ff 00 73 32     andi       s3,s3,0xff
     9::800a51b4 21 98 7e 02     addu       s3,s3,s8
     9::800a51b8 02 a4 0a 00     srl        s4,t2,0x10
     9::800a51bc 1f 00 94 32     andi       s4,s4,0x1f
     9::800a51c0 06 a0 83 02     srlv       s4,v1,s4
     9::800a51c4 ff 00 94 32     andi       s4,s4,0xff
     9::800a51c8 21 a0 9e 02     addu       s4,s4,s8
     9::800a51cc 02 aa 0a 00     srl        s5,t2,0x8
     9::800a51d0 1f 00 b5 32     andi       s5,s5,0x1f
     9::800a51d4 06 a8 a3 02     srlv       s5,v1,s5
     9::800a51d8 ff 00 b5 32     andi       s5,s5,0xff
     9::800a51dc 21 a8 be 02     addu       s5,s5,s8
     9::800a51e0 1f 00 56 31     andi       s6,t2,0x1f
     9::800a51e4 06 b0 c3 02     srlv       s6,v1,s6
     9::800a51e8 ff 00 d6 32     andi       s6,s6,0xff
     9::800a51ec 21 b0 de 02     addu       s6,s6,s8
     9::800a51f0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a51f4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a51f8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a51fc 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a5200 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a5204 06 00 40 4b     NCLIP
     9::800a5208 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a520c 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a5210 23 78 68 01     subu       t7,t3,t0
     9::800a5214 23 80 88 01     subu       s0,t4,t0
     9::800a5218 23 88 a8 01     subu       s1,t5,t0
     9::800a521c 23 90 c8 01     subu       s2,t6,t0
     9::800a5220 00 c0 08 48     gte_stMAC0 t0
     9::800a5224 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a5228 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a5234
     9::800a522c 22 40 08 00     _sub       t0,zero,t0
     9::800a5230 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a5234                           XREF[1]:     OVR_229::800a5228(j)  
     9::800a5234 06 00 40 4b     NCLIP
     9::800a5238 24 18 6c 01     and        v1,t3,t4
     9::800a523c 24 18 6d 00     and        v1,v1,t5
     9::800a5240 24 18 6e 00     and        v1,v1,t6
     9::800a5244 25 78 f0 01     or         t7,t7,s0
     9::800a5248 25 78 f1 01     or         t7,t7,s1
     9::800a524c 27 78 f2 01     nor        t7,t7,s2
     9::800a5250 25 78 e3 01     or         t7,t7,v1
     9::800a5254 aa fe e0 05     bltz       t7,LAB_OVR_229__800a4d00
     9::800a5258 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a525c a8 fe e0 05     bltz       t7,LAB_OVR_229__800a4d00
     9::800a5260 00 c0 03 48     _gte_stM   v1
     9::800a5264 25 40 09 01     or         t0,t0,t1
     9::800a5268 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a5274
     9::800a526c c2 47 08 00     _srl       t0,t0,0x1f
     9::800a5270 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a5274                           XREF[1]:     OVR_229::800a5268(j)  
     9::800a5274 80 40 08 00     sll        t0,t0,0x2
     9::800a5278 25 18 69 00     or         v1,v1,t1
     9::800a527c c2 1f 03 00     srl        v1,v1,0x1f
     9::800a5280 c0 18 03 00     sll        v1,v1,0x3
     9::800a5284 25 18 68 00     or         v1,v1,t0
     9::800a5288 9d fe 60 10     beq        v1,zero,LAB_OVR_229__800a4d00
     9::800a528c 70 00 23 ac     _sw        v1,0x70(at)
     9::800a5290 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a5294 04 00 39 27     addiu      t9,t9,0x4
     9::800a5298 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a529c 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a52a0 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a52a4 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a52a8 b4 00 c3 8f     lw         v1,0xb4(s8)
     9::800a52ac 23 50 6c 01     subu       t2,t3,t4
     9::800a52b0 82 48 03 00     srl        t1,v1,0x2
     9::800a52b4 21 48 38 01     addu       t1,t1,t8
     9::800a52b8 18 00 29 81     lb         t1,0x18(t1)
     9::800a52bc 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a52c8
     9::800a52c0 21 e0 60 01     _move      gp,t3
     9::800a52c4 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a52c8                           XREF[1]:     OVR_229::800a52bc(j)  
     9::800a52c8 23 50 8d 03     subu       t2,gp,t5
     9::800a52cc 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a52d8
     9::800a52d0 21 18 78 00     _addu      v1,v1,t8
     9::800a52d4 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a52d8                           XREF[1]:     OVR_229::800a52cc(j)  
     9::800a52d8 23 50 8e 03     subu       t2,gp,t6
     9::800a52dc 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a52e8
     9::800a52e0 1c 00 63 8c     _lw        v1,0x1c(v1)
     9::800a52e4 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a52e8                           XREF[1]:     OVR_229::800a52dc(j)  
     9::800a52e8 21 50 80 03     move       t2,gp
     9::800a52ec 82 e1 1c 00     srl        gp,gp,0x6
     9::800a52f0 21 e0 89 03     addu       gp,gp,t1
     9::800a52f4 01 00 69 30     andi       t1,v1,0x1
     9::800a52f8 02 00 20 11     beq        t1,zero,LAB_OVR_229__800a5304
     9::800a52fc 80 e0 1c 00     _sll       gp,gp,0x2
     9::800a5300 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_229__800a5304                           XREF[1]:     OVR_229::800a52f8(j)  
     9::800a5304 02 00 81 07     bgez       gp,LAB_OVR_229__800a5310
     9::800a5308 21 e0 85 03     _addu      gp,gp,a1
     9::800a530c 21 e0 a0 00     move       gp,a1
                             LAB_OVR_229__800a5310                           XREF[1]:     OVR_229::800a5304(j)  
     9::800a5310 24 00 69 8c     lw         t1,0x24(v1)
     9::800a5314 c0 f9 48 25     addiu      t0,t2,-0x640
     9::800a5318 84 00 29 ac     sw         t1,0x84(at)
     9::800a531c 0a 00 01 05     bgez       t0,LAB_OVR_229__800a5348
     9::800a5320 00 fb 48 25     _addiu     t0,t2,-0x500
     9::800a5324 0c 00 63 24     addiu      v1,v1,0xc
     9::800a5328 07 00 01 05     bgez       t0,LAB_OVR_229__800a5348
     9::800a532c 80 fd 48 25     _addiu     t0,t2,-0x280
     9::800a5330 0c 00 63 24     addiu      v1,v1,0xc
     9::800a5334 04 00 01 05     bgez       t0,LAB_OVR_229__800a5348
     9::800a5338 00 00 00 00     _nop
     9::800a533c 02 00 20 05     bltz       t1,LAB_OVR_229__800a5348
     9::800a5340 00 00 00 00     _nop
     9::800a5344 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_229__800a5348                           XREF[4]:     OVR_229::800a531c(j), 
                                                                                          OVR_229::800a5328(j), 
                                                                                          OVR_229::800a5334(j), 
                                                                                          OVR_229::800a533c(j)  
     9::800a5348 94 01 2a 8c     lw         t2,0x194(at)
     9::800a534c 00 00 68 8c     lw         t0,0x0(v1)
     9::800a5350 04 00 69 8c     lw         t1,0x4(v1)
     9::800a5354 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a5358 ac 01 28 ac     sw         t0,0x1ac(at)
     9::800a535c a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a5360 00 52 0a 00     sll        t2,t2,0x8
     9::800a5364 0a 00 40 05     bltz       t2,LAB_OVR_229__800a5390
     9::800a5368 b0 01 29 ac     _sw        t1,0x1b0(at)
     9::800a536c 06 00 68 a6     sh         t0,0x6(s3)
     9::800a5370 08 00 68 8c     lw         t0,0x8(v1)
     9::800a5374 06 00 89 a6     sh         t1,0x6(s4)
     9::800a5378 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a537c 00 54 0a 00     sll        t2,t2,0x10
     9::800a5380 0b 00 40 05     bltz       t2,LAB_OVR_229__800a53b0
     9::800a5384 02 4c 08 00     _srl       t1,t0,0x10
     9::800a5388 09 00 01 04     bgez       zero,LAB_OVR_229__800a53b0
     9::800a538c 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_229__800a5390                           XREF[1]:     OVR_229::800a5364(j)  
     9::800a5390 06 00 69 a6     sh         t1,0x6(s3)
     9::800a5394 08 00 69 8c     lw         t1,0x8(v1)
     9::800a5398 00 54 0a 00     sll        t2,t2,0x10
     9::800a539c 06 00 88 a6     sh         t0,0x6(s4)
     9::800a53a0 02 44 09 00     srl        t0,t1,0x10
     9::800a53a4 02 00 40 05     bltz       t2,LAB_OVR_229__800a53b0
     9::800a53a8 06 00 a8 a6     _sh        t0,0x6(s5)
     9::800a53ac 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a53b0                           XREF[3]:     OVR_229::800a5380(j), 
                                                                                          OVR_229::800a5388(j), 
                                                                                          OVR_229::800a53a4(j)  
     9::800a53b0 80 fd 71 25     addiu      s1,t3,-0x280
     9::800a53b4 80 fd 92 25     addiu      s2,t4,-0x280
     9::800a53b8 80 fd af 25     addiu      t7,t5,-0x280
     9::800a53bc 80 fd d0 25     addiu      s0,t6,-0x280
                             LAB_OVR_229__800a53c0                           XREF[1]:     FUN_OVR_229__800a5094:800a5178(j
     9::800a53c0 42 8f 11 00     srl        s1,s1,0x1d
     9::800a53c4 04 00 31 32     andi       s1,s1,0x4
     9::800a53c8 02 97 12 00     srl        s2,s2,0x1c
     9::800a53cc 08 00 52 32     andi       s2,s2,0x8
     9::800a53d0 25 88 32 02     or         s1,s1,s2
     9::800a53d4 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a53d8 10 00 ef 31     andi       t7,t7,0x10
     9::800a53dc 25 88 2f 02     or         s1,s1,t7
     9::800a53e0 82 86 10 00     srl        s0,s0,0x1a
     9::800a53e4 20 00 10 32     andi       s0,s0,0x20
     9::800a53e8 25 88 30 02     or         s1,s1,s0
     9::800a53ec 26 00 20 12     beq        s1,zero,LAB_OVR_229__800a5488
     9::800a53f0 21 68 60 02     _move      t5,s3
     9::800a53f4 21 70 80 02     move       t6,s4
     9::800a53f8 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a53fc 00 00 cf 27     addiu      t7,s8,0x0
     9::800a5400 eb 93 02 0c     jal        FUN_OVR_229__800a4fac                            undefined FUN_OVR_229__800a4fac()
     9::800a5404 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a5408 21 68 80 02     move       t5,s4
     9::800a540c 21 70 c0 02     move       t6,s6
     9::800a5410 14 00 cf 27     addiu      t7,s8,0x14
     9::800a5414 eb 93 02 0c     jal        FUN_OVR_229__800a4fac                            undefined FUN_OVR_229__800a4fac()
     9::800a5418 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a541c 21 68 a0 02     move       t5,s5
     9::800a5420 21 70 60 02     move       t6,s3
     9::800a5424 28 00 cf 27     addiu      t7,s8,0x28
     9::800a5428 eb 93 02 0c     jal        FUN_OVR_229__800a4fac                            undefined FUN_OVR_229__800a4fac()
     9::800a542c 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a5430 21 68 c0 02     move       t5,s6
     9::800a5434 21 70 a0 02     move       t6,s5
     9::800a5438 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a543c eb 93 02 0c     jal        FUN_OVR_229__800a4fac                            undefined FUN_OVR_229__800a4fac()
     9::800a5440 a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a5444 50 00 cd 27     addiu      t5,s8,0x50
     9::800a5448 a0 00 ce 27     addiu      t6,s8,0xa0
     9::800a544c 50 00 cf 27     addiu      t7,s8,0x50
     9::800a5450 eb 93 02 0c     jal        FUN_OVR_229__800a4fac                            undefined FUN_OVR_229__800a4fac()
     9::800a5454 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a5458 21 18 21 02     addu       v1,s1,at
     9::800a545c 48 01 63 8c     lw         v1,0x148(v1)
     9::800a5460 0a 80 08 3c     lui        t0,0x800a
     9::800a5464 78 54 08 25     addiu      t0,t0,0x5478
     9::800a5468 9c 00 23 ac     sw         v1,0x9c(at)
     9::800a546c 3c 00 28 af     sw         t0=>LAB_OVR_229__800a5478,0x3c(t9)
     9::800a5470 08 00 60 00     jr         v1
     9::800a5474 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a5478                           XREF[1]:     FUN_OVR_229__800a5180:800a546c(*
     9::800a5478 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a547c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5480 08 00 e0 03     jr         ra
     9::800a5484 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a5488                           XREF[1]:     OVR_229::800a53ec(j)  
     9::800a5488 70 00 23 8c     lw         v1,0x70(at)
     9::800a548c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5490 21 18 61 00     addu       v1,v1,at
     9::800a5494 84 01 63 8c     lw         v1,0x184(v1)
     9::800a5498 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a549c 08 00 60 00     jr         v1
     9::800a54a0 00 00 00 00     _nop
                             LAB_OVR_229__800a54a4                           XREF[1]:     OVR_229::800a5154(j)  
     9::800a54a4 84 00 23 8c     lw         v1,0x84(at)
     9::800a54a8 24 03 2a 24     addiu      t2,at,0x324
     9::800a54ac 26 00 60 1c     bgtz       v1,LAB_OVR_229__800a5548
     9::800a54b0 20 03 28 8c     _lw        t0,0x320(at)
     9::800a54b4 d8 03 29 8c     lw         t1,0x3d8(at)
     9::800a54b8 16 00 5e 15     bne        t2,s8,LAB_OVR_229__800a5514
     9::800a54bc 9c 00 23 8c     _lw        v1,0x9c(at)
     9::800a54c0 0a 80 0a 3c     lui        t2,0x800a
     9::800a54c4 08 4f 4a 25     addiu      t2,t2,0x4f08
     9::800a54c8 1f 00 6a 14     bne        v1,t2,LAB_OVR_229__800a5548
     9::800a54cc 94 01 23 8c     _lw        v1,0x194(at)
     9::800a54d0 40 40 08 00     sll        t0,t0,0x1
     9::800a54d4 00 1a 03 00     sll        v1,v1,0x8
     9::800a54d8 02 00 61 04     bgez       v1,LAB_OVR_229__800a54e4
     9::800a54dc 84 00 2a 8c     _lw        t2,0x84(at)
     9::800a54e0 c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_229__800a54e4                           XREF[1]:     OVR_229::800a54d8(j)  
     9::800a54e4 21 40 09 01     addu       t0,t0,t1
     9::800a54e8 21 50 48 01     addu       t2,t2,t0
     9::800a54ec 00 00 48 8d     lw         t0,0x0(t2)
     9::800a54f0 04 00 49 8d     lw         t1,0x4(t2)
     9::800a54f4 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a54f8 06 00 68 a6     sh         t0,0x6(s3)
     9::800a54fc 08 00 48 85     lh         t0,0x8(t2)
     9::800a5500 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a5504 06 00 89 a6     sh         t1,0x6(s4)
     9::800a5508 0a 00 49 85     lh         t1,0xa(t2)
     9::800a550c 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a5510 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a5514                           XREF[2]:     OVR_229::800a54b8(j), 
                                                                                          OVR_229::800a5554(j)  
     9::800a5514 70 00 23 8c     lw         v1,0x70(at)
     9::800a5518 00 00 00 00     nop
     9::800a551c 21 18 61 00     addu       v1,v1,at
     9::800a5520 84 01 63 8c     lw         v1,0x184(v1)
     9::800a5524 00 00 00 00     nop
     9::800a5528 09 f8 60 00     jalr       v1
     9::800a552c fc ff 39 27     _addiu     t9,t9,-0x4
     9::800a5530 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a5534 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a5538 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a553c a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a5540 08 00 e0 03     jr         ra
     9::800a5544 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_229__800a5548                           XREF[2]:     OVR_229::800a54ac(j), 
                                                                                          OVR_229::800a54c8(j)  
     9::800a5548 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a554c b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a5550 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a5554 ef ff 01 04     bgez       zero,LAB_OVR_229__800a5514
     9::800a5558 a4 01 29 ac     _sw        t1,0x1a4(at)
     9::800a555c 21 98 80 02     move       s3,s4
     9::800a5560 21 a0 c0 02     move       s4,s6
     9::800a5564 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a5568 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a556c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a5570 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a5574 08 00 90 8e     lw         s0,0x8(s4)
     9::800a5578 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a557c 06 00 73 86     lh         s3,0x6(s3)
     9::800a5580 06 00 94 86     lh         s4,0x6(s4)
     9::800a5584 06 00 b5 86     lh         s5,0x6(s5)
     9::800a5588 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a558c a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a5590 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a5594 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a5598 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a559c a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a55a0 60 00 03 3c     lui        v1,0x60
     9::800a55a4 24 48 83 02     and        t1,s4,v1
     9::800a55a8 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a55b4
     9::800a55ac 00 36 03 3c     _lui       v1,0x3600
     9::800a55b0 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a55b4                           XREF[1]:     OVR_229::800a55a8(j)  
     9::800a55b4 25 18 6f 00     or         v1,v1,t7
     9::800a55b8 04 00 43 ac     sw         v1,0x4(v0)
     9::800a55bc 08 00 4b ac     sw         t3,0x8(v0)
     9::800a55c0 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a55c4 10 00 50 ac     sw         s0,0x10(v0)
     9::800a55c8 14 00 4c ac     sw         t4,0x14(v0)
     9::800a55cc 18 00 54 ac     sw         s4,0x18(v0)
     9::800a55d0 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a55d4 20 00 4d ac     sw         t5,0x20(v0)
     9::800a55d8 24 00 55 ac     sw         s5,0x24(v0)
     9::800a55dc 28 00 09 24     li         t1,0x28
     9::800a55e0 29 00 01 04     bgez       zero,LAB_OVR_229__800a5688
     9::800a55e4 00 09 0a 3c     _lui       t2,0x900
     9::800a55e8 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a55ec 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a55f0 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a55f4 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a55f8 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a55fc 08 00 90 8e     lw         s0,0x8(s4)
     9::800a5600 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a5604 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a5608 06 00 73 86     lh         s3,0x6(s3)
     9::800a560c 06 00 94 86     lh         s4,0x6(s4)
     9::800a5610 06 00 b5 86     lh         s5,0x6(s5)
     9::800a5614 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a5618 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a561c 06 00 d4 86     lh         s4,0x6(s6)
     9::800a5620 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a5624 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a5628 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a562c a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a5630 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a5634 60 00 03 3c     lui        v1,0x60
     9::800a5638 24 48 83 02     and        t1,s4,v1
     9::800a563c 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a5648
     9::800a5640 00 3e 03 3c     _lui       v1,0x3e00
     9::800a5644 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a5648                           XREF[1]:     OVR_229::800a563c(j)  
     9::800a5648 25 18 6f 00     or         v1,v1,t7
     9::800a564c 04 00 43 ac     sw         v1,0x4(v0)
     9::800a5650 08 00 4b ac     sw         t3,0x8(v0)
     9::800a5654 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a5658 10 00 50 ac     sw         s0,0x10(v0)
     9::800a565c 14 00 4c ac     sw         t4,0x14(v0)
     9::800a5660 18 00 54 ac     sw         s4,0x18(v0)
     9::800a5664 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a5668 20 00 4d ac     sw         t5,0x20(v0)
     9::800a566c 24 00 55 ac     sw         s5,0x24(v0)
     9::800a5670 28 00 52 ac     sw         s2,0x28(v0)
     9::800a5674 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a5678 02 1c 15 00     srl        v1,s5,0x10
     9::800a567c 30 00 43 ac     sw         v1,0x30(v0)
     9::800a5680 34 00 09 24     li         t1,0x34
     9::800a5684 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a5688                           XREF[1]:     OVR_229::800a55e0(j)  
     9::800a5688 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a568c 00 42 02 00     sll        t0,v0,0x8
     9::800a5690 02 42 08 00     srl        t0,t0,0x8
     9::800a5694 25 18 6a 00     or         v1,v1,t2
     9::800a5698 00 00 43 ac     sw         v1,0x0(v0)
     9::800a569c 21 10 49 00     addu       v0,v0,t1
     9::800a56a0 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a56a4 08 00 e0 03     jr         ra
     9::800a56a8 01 00 bd 23     _addi      sp,sp,0x1
     9::800a56ac 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_229__800a56b0                           XREF[1]:     OVR_229::800a5a00(j)  
     9::800a56b0 30 00 23 8c     lw         v1,0x30(at)
     9::800a56b4 40 37 48 24     addiu      t0,v0,0x3740
     9::800a56b8 23 18 68 00     subu       v1,v1,t0
     9::800a56bc 5b ee 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a56c0 b4 01 3e 24     _addiu     s8,at,0x1b4
     9::800a56c4 a8 ee 00 13     beq        t8,zero,LAB_OVR_229__800a1168
     9::800a56c8 b4 00 c0 af     _sw        zero,0xb4(s8)
     9::800a56cc 00 00 14 8f     lw         s4,0x0(t8)
     9::800a56d0 04 00 16 8f     lw         s6,0x4(t8)
     9::800a56d4 ff ff 93 32     andi       s3,s4,0xffff
     9::800a56d8 00 99 13 00     sll        s3,s3,0x4
     9::800a56dc 21 98 77 02     addu       s3,s3,s7
     9::800a56e0 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a56e8 02 a4 14 00     srl        s4,s4,0x10
     9::800a56ec 00 a1 14 00     sll        s4,s4,0x4
     9::800a56f0 21 a0 97 02     addu       s4,s4,s7
     9::800a56f4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a56fc ff ff d5 32     andi       s5,s6,0xffff
     9::800a5700 00 a9 15 00     sll        s5,s5,0x4
     9::800a5704 21 a8 b7 02     addu       s5,s5,s7
     9::800a5708 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a5710 02 b4 16 00     srl        s6,s6,0x10
     9::800a5714 00 b1 16 00     sll        s6,s6,0x4
     9::800a5718 30 00 28 4a     RTPT
     9::800a571c 21 b0 d7 02     addu       s6,s6,s7
     9::800a5720 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a5724 08 00 90 8e     lw         s0,0x8(s4)
     9::800a5728 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a572c 08 00 cf af     sw         t7,0x8(s8)
     9::800a5730 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a5734 30 00 d1 af     sw         s1,0x30(s8)
     9::800a5738 08 00 14 8f     lw         s4,0x8(t8)
     9::800a573c 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a5740 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a5744 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a5748 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a574c 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a5750 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a5754 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a5758 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a575c 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a5760 5c 00 2a 8c     lw         t2,0x5c(at)
     9::800a5764 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a5770 10 00 c3 a7     sh         v1,0x10(s8)
     9::800a5774 24 00 c8 a7     sh         t0,0x24(s8)
     9::800a5778 38 00 c9 a7     sh         t1,0x38(s8)
     9::800a577c 23 58 6a 00     subu       t3,v1,t2
     9::800a5780 23 60 0a 01     subu       t4,t0,t2
     9::800a5784 23 68 2a 01     subu       t5,t1,t2
     9::800a5788 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a578c c2 67 0c 00     srl        t4,t4,0x1f
     9::800a5790 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a5794 12 00 cb a3     sb         t3,0x12(s8)
     9::800a5798 26 00 cc a3     sb         t4,0x26(s8)
     9::800a579c 3a 00 cd a3     sb         t5,0x3a(s8)
     9::800a57a0 40 18 03 00     sll        v1,v1,0x1
     9::800a57a4 40 40 08 00     sll        t0,t0,0x1
     9::800a57a8 40 48 09 00     sll        t1,t1,0x1
     9::800a57ac 23 58 6a 00     subu       t3,v1,t2
     9::800a57b0 23 60 0a 01     subu       t4,t0,t2
     9::800a57b4 23 68 2a 01     subu       t5,t1,t2
     9::800a57b8 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a57bc c2 67 0c 00     srl        t4,t4,0x1f
     9::800a57c0 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a57c4 13 00 cb a3     sb         t3,0x13(s8)
     9::800a57c8 27 00 cc a3     sb         t4,0x27(s8)
     9::800a57cc 3b 00 cd a3     sb         t5,0x3b(s8)
     9::800a57d0 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a57d8 ff ff 93 32     andi       s3,s4,0xffff
     9::800a57dc 00 99 13 00     sll        s3,s3,0x4
     9::800a57e0 21 98 77 02     addu       s3,s3,s7
     9::800a57e4 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a57ec 02 a4 14 00     srl        s4,s4,0x10
     9::800a57f0 00 a1 14 00     sll        s4,s4,0x4
     9::800a57f4 21 a0 97 02     addu       s4,s4,s7
     9::800a57f8 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a5800 21 c8 20 00     move       t9,at
     9::800a5804 00 00 00 00     nop
     9::800a5808 30 00 28 4a     RTPT
     9::800a580c 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a5810 08 00 70 8e     lw         s0,0x8(s3)
     9::800a5814 08 00 91 8e     lw         s1,0x8(s4)
     9::800a5818 44 00 cf af     sw         t7,0x44(s8)
     9::800a581c 58 00 d0 af     sw         s0,0x58(s8)
     9::800a5820 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a5824 0c 00 14 8f     lw         s4,0xc(t8)
     9::800a5828 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a582c 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     9::800a5830 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a5834 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a5838 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a583c 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a5840 10 00 15 97     lhu        s5,0x10(t8)
     9::800a5844 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a5848 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a584c 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a5850 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a585c 4c 00 c3 a7     sh         v1,0x4c(s8)
     9::800a5860 60 00 c8 a7     sh         t0,0x60(s8)
     9::800a5864 74 00 c9 a7     sh         t1,0x74(s8)
     9::800a5868 23 58 6a 00     subu       t3,v1,t2
     9::800a586c 23 60 0a 01     subu       t4,t0,t2
     9::800a5870 23 68 2a 01     subu       t5,t1,t2
     9::800a5874 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a5878 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a587c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a5880 4e 00 cb a3     sb         t3,0x4e(s8)
     9::800a5884 62 00 cc a3     sb         t4,0x62(s8)
     9::800a5888 76 00 cd a3     sb         t5,0x76(s8)
     9::800a588c 40 18 03 00     sll        v1,v1,0x1
     9::800a5890 40 40 08 00     sll        t0,t0,0x1
     9::800a5894 40 48 09 00     sll        t1,t1,0x1
     9::800a5898 23 58 6a 00     subu       t3,v1,t2
     9::800a589c 23 60 0a 01     subu       t4,t0,t2
     9::800a58a0 23 68 2a 01     subu       t5,t1,t2
     9::800a58a4 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a58a8 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a58ac c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a58b0 4f 00 cb a3     sb         t3,0x4f(s8)
     9::800a58b4 63 00 cc a3     sb         t4,0x63(s8)
     9::800a58b8 77 00 cd a3     sb         t5,0x77(s8)
     9::800a58bc ff ff 93 32     andi       s3,s4,0xffff
     9::800a58c0 00 99 13 00     sll        s3,s3,0x4
     9::800a58c4 21 98 77 02     addu       s3,s3,s7
     9::800a58c8 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a58d0 02 a4 14 00     srl        s4,s4,0x10
     9::800a58d4 00 a1 14 00     sll        s4,s4,0x4
     9::800a58d8 21 a0 97 02     addu       s4,s4,s7
     9::800a58dc 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a58e4 14 00 09 8f     lw         t1,0x14(t8)
     9::800a58e8 00 a9 15 00     sll        s5,s5,0x4
     9::800a58ec 21 a8 b7 02     addu       s5,s5,s7
     9::800a58f0 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a58f8 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a58fc 00 00 00 00     nop
     9::800a5900 30 00 28 4a     RTPT
     9::800a5904 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a5908 08 00 90 8e     lw         s0,0x8(s4)
     9::800a590c 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a5910 80 00 cf af     sw         t7,0x80(s8)
     9::800a5914 94 00 d0 af     sw         s0,0x94(s8)
     9::800a5918 a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a591c 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a5920 98 00 cd eb     gte_stSXY1 0x98(s8)
     9::800a5924 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a5928 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a592c 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a5930 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a5934 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a5938 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a593c a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a5940 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a594c 88 00 c3 a7     sh         v1,0x88(s8)
     9::800a5950 9c 00 c8 a7     sh         t0,0x9c(s8)
     9::800a5954 b0 00 c9 a7     sh         t1,0xb0(s8)
     9::800a5958 23 58 6a 00     subu       t3,v1,t2
     9::800a595c 23 60 0a 01     subu       t4,t0,t2
     9::800a5960 23 68 2a 01     subu       t5,t1,t2
     9::800a5964 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a5968 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a596c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a5970 8a 00 cb a3     sb         t3,0x8a(s8)
     9::800a5974 9e 00 cc a3     sb         t4,0x9e(s8)
     9::800a5978 b2 00 cd a3     sb         t5,0xb2(s8)
     9::800a597c 40 18 03 00     sll        v1,v1,0x1
     9::800a5980 40 40 08 00     sll        t0,t0,0x1
     9::800a5984 40 48 09 00     sll        t1,t1,0x1
     9::800a5988 23 58 6a 00     subu       t3,v1,t2
     9::800a598c 23 60 0a 01     subu       t4,t0,t2
     9::800a5990 23 68 2a 01     subu       t5,t1,t2
     9::800a5994 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a5998 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a599c c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a59a0 8b 00 cb a3     sb         t3,0x8b(s8)
     9::800a59a4 9f 00 cc a3     sb         t4,0x9f(s8)
     9::800a59a8 b3 00 cd a3     sb         t5,0xb3(s8)
     9::800a59ac 50 00 03 3c     lui        v1,0x50
     9::800a59b0 78 64 63 34     ori        v1,v1,0x6478
     9::800a59b4 08 00 08 24     li         t0,0x8
     9::800a59b8 a4 97 02 0c     jal        FUN_OVR_229__800a5e90                            undefined FUN_OVR_229__800a5e90()
     9::800a59bc 00 00 0a 24     _li        t2,0x0
     9::800a59c0 14 50 03 3c     lui        v1,0x5014
     9::800a59c4 8c 78 63 34     ori        v1,v1,0x788c
     9::800a59c8 0d 00 08 24     li         t0,0xd
     9::800a59cc a4 97 02 0c     jal        FUN_OVR_229__800a5e90                            undefined FUN_OVR_229__800a5e90()
     9::800a59d0 04 00 0a 24     _li        t2,0x4
     9::800a59d4 78 64 03 3c     lui        v1,0x6478
     9::800a59d8 a0 28 63 34     ori        v1,v1,0x28a0
     9::800a59dc 12 00 08 24     li         t0,0x12
     9::800a59e0 a4 97 02 0c     jal        FUN_OVR_229__800a5e90                            undefined FUN_OVR_229__800a5e90()
     9::800a59e4 08 00 0a 24     _li        t2,0x8
     9::800a59e8 8c 78 03 3c     lui        v1,0x788c
     9::800a59ec 3c a0 63 34     ori        v1,v1,0xa03c
     9::800a59f0 17 00 08 24     li         t0,0x17
     9::800a59f4 a4 97 02 0c     jal        FUN_OVR_229__800a5e90                            undefined FUN_OVR_229__800a5e90()
     9::800a59f8 0c 00 0a 24     _li        t2,0xc
     9::800a59fc 04 00 98 8c     lw         t8,0x4(a0)
     9::800a5a00 2b ff 01 04     bgez       zero,LAB_OVR_229__800a56b0
     9::800a5a04 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_229__800a5a08                           XREF[12]:    FUN_OVR_229__800a5d60:800a5d7c(j
                                                                                          FUN_OVR_229__800a5d60:800a5e18(j
                                                                                          FUN_OVR_229__800a5d60:800a5e20(j
                                                                                          FUN_OVR_229__800a5d60:800a5e54(j
                                                                                          OVR_229::800a5f1c(j), 
                                                                                          OVR_229::800a5fa8(j), 
                                                                                          OVR_229::800a5fb0(j), 
                                                                                          OVR_229::800a5fdc(j), 
                                                                                          FUN_OVR_229__800a5d60:800a62e4(j
                                                                                          FUN_OVR_229__800a5d60:800a63a0(j
                                                                                          FUN_OVR_229__800a5d60:800a64d4(j
                                                                                          FUN_OVR_229__800a5d60:800a658c(j
     9::800a5a08 08 00 e0 03     jr         ra
     9::800a5a0c 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5a10()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5a10                           XREF[4]:     FUN_OVR_229__800a5a60:800a5ae8(j
                                                                                          FUN_OVR_229__800a5a60:800a5b80(c
                                                                                          FUN_OVR_229__800a5a60:800a5ba8(c
                                                                                          FUN_OVR_229__800a5a60:800a5c14(c
     9::800a5a10 00 00 d3 27     addiu      s3,s8,0x0
     9::800a5a14 50 00 d4 27     addiu      s4,s8,0x50
     9::800a5a18 64 00 d5 27     addiu      s5,s8,0x64
     9::800a5a1c d0 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a20 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5a24()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5a24                           XREF[6]:     FUN_OVR_229__800a5a60:800a5af0(c
                                                                                          FUN_OVR_229__800a5a60:800a5b90(j
                                                                                          FUN_OVR_229__800a5a60:800a5ba0(c
                                                                                          FUN_OVR_229__800a5a60:800a5bd0(c
                                                                                          FUN_OVR_229__800a5a60:800a5bf0(c
                                                                                          FUN_OVR_229__800a5a60:800a5c24(c
     9::800a5a24 50 00 d3 27     addiu      s3,s8,0x50
     9::800a5a28 14 00 d4 27     addiu      s4,s8,0x14
     9::800a5a2c 78 00 d5 27     addiu      s5,s8,0x78
     9::800a5a30 cb 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a34 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5a38()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5a38                           XREF[6]:     FUN_OVR_229__800a5a60:800a5b18(c
                                                                                          FUN_OVR_229__800a5a60:800a5b78(c
                                                                                          FUN_OVR_229__800a5a60:800a5bb8(j
                                                                                          FUN_OVR_229__800a5a60:800a5bc8(c
                                                                                          FUN_OVR_229__800a5a60:800a5bf8(c
                                                                                          FUN_OVR_229__800a5a60:800a5c34(c
     9::800a5a38 64 00 d3 27     addiu      s3,s8,0x64
     9::800a5a3c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a5a40 28 00 d5 27     addiu      s5,s8,0x28
     9::800a5a44 c6 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a48 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a5a4c                           XREF[4]:     OVR_229::800a5b68(j), 
                                                                                          OVR_229::800a5be0(j), 
                                                                                          OVR_229::800a5c08(j), 
                                                                                          OVR_229::800a5c4c(j)  
     9::800a5a4c 78 00 d3 27     addiu      s3,s8,0x78
     9::800a5a50 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a5a54 a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a5a58 c1 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a5c 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5a60()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5a60                           XREF[2]:     OVR_229::800a5b10(c), 
                                                                                          OVR_229::800a5be8(c)  
     9::800a5a60 64 00 d3 27     addiu      s3,s8,0x64
     9::800a5a64 00 00 d4 27     addiu      s4,s8,0x0
     9::800a5a68 78 00 d5 27     addiu      s5,s8,0x78
     9::800a5a6c bc 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a70 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a5a74                           XREF[2]:     OVR_229::800a5b28(j), 
                                                                                          OVR_229::800a5b98(c)  
     9::800a5a74 14 00 d3 27     addiu      s3,s8,0x14
     9::800a5a78 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a5a7c 78 00 d5 27     addiu      s5,s8,0x78
     9::800a5a80 b7 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a84 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a5a88                           XREF[2]:     OVR_229::800a5af8(c), 
                                                                                          OVR_229::800a5bc0(c)  
     9::800a5a88 28 00 d3 27     addiu      s3,s8,0x28
     9::800a5a8c 00 00 d4 27     addiu      s4,s8,0x0
     9::800a5a90 78 00 d5 27     addiu      s5,s8,0x78
     9::800a5a94 b2 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5a98 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a5a9c                           XREF[2]:     OVR_229::800a5b08(j), 
                                                                                          OVR_229::800a5b70(c)  
     9::800a5a9c 28 00 d3 27     addiu      s3,s8,0x28
     9::800a5aa0 78 00 d4 27     addiu      s4,s8,0x78
     9::800a5aa4 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a5aa8 ad 00 01 04     bgez       zero,FUN_OVR_229__800a5d60
     9::800a5aac 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a5ab0 50 00 d3 27     addiu      s3,s8,0x50
     9::800a5ab4 14 00 d4 27     addiu      s4,s8,0x14
     9::800a5ab8 78 00 d5 27     addiu      s5,s8,0x78
     9::800a5abc 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a5ac0 58 97 02 0c     jal        FUN_OVR_229__800a5d60                            undefined FUN_OVR_229__800a5d60()
     9::800a5ac4 0c 00 0a 24     _li        t2,0xc
     9::800a5ac8 64 00 d3 27     addiu      s3,s8,0x64
     9::800a5acc 78 00 d4 27     addiu      s4,s8,0x78
     9::800a5ad0 28 00 d5 27     addiu      s5,s8,0x28
     9::800a5ad4 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a5ad8 58 97 02 0c     jal        FUN_OVR_229__800a5d60                            undefined FUN_OVR_229__800a5d60()
     9::800a5adc 0c 00 0a 24     _li        t2,0xc
     9::800a5ae0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5ae4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5ae8 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a5a10
     9::800a5aec 0c 00 0a 24     _li        t2,0xc
     9::800a5af0 89 96 02 0c     jal        FUN_OVR_229__800a5a24                            undefined FUN_OVR_229__800a5a24()
     9::800a5af4 0c 00 0a 24     _li        t2,0xc
     9::800a5af8 a2 96 02 0c     jal        SUB_OVR_229__800a5a88
     9::800a5afc 0c 00 0a 24     _li        t2,0xc
     9::800a5b00 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5b04 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5b08 e4 ff 01 04     bgez       zero,SUB_OVR_229__800a5a9c
     9::800a5b0c 0c 00 0a 24     _li        t2,0xc
     9::800a5b10 98 96 02 0c     jal        FUN_OVR_229__800a5a60                            undefined FUN_OVR_229__800a5a60()
     9::800a5b14 0c 00 0a 24     _li        t2,0xc
     9::800a5b18 8e 96 02 0c     jal        FUN_OVR_229__800a5a38                            undefined FUN_OVR_229__800a5a38()
     9::800a5b1c 0c 00 0a 24     _li        t2,0xc
     9::800a5b20 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5b24 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5b28 d2 ff 01 04     bgez       zero,SUB_OVR_229__800a5a74
     9::800a5b2c 0c 00 0a 24     _li        t2,0xc
     9::800a5b30 00 00 d3 27     addiu      s3,s8,0x0
     9::800a5b34 14 00 d4 27     addiu      s4,s8,0x14
     9::800a5b38 78 00 d5 27     addiu      s5,s8,0x78
     9::800a5b3c 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a5b40 58 97 02 0c     jal        FUN_OVR_229__800a5d60                            undefined FUN_OVR_229__800a5d60()
     9::800a5b44 0c 00 0a 24     _li        t2,0xc
     9::800a5b48 00 00 d3 27     addiu      s3,s8,0x0
     9::800a5b4c 78 00 d4 27     addiu      s4,s8,0x78
     9::800a5b50 28 00 d5 27     addiu      s5,s8,0x28
     9::800a5b54 a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a5b58 58 97 02 0c     jal        FUN_OVR_229__800a5d60                            undefined FUN_OVR_229__800a5d60()
     9::800a5b5c 0c 00 0a 24     _li        t2,0xc
     9::800a5b60 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5b64 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5b68 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a5a4c
     9::800a5b6c 0c 00 0a 24     _li        t2,0xc
     9::800a5b70 a7 96 02 0c     jal        SUB_OVR_229__800a5a9c
     9::800a5b74 0c 00 0a 24     _li        t2,0xc
     9::800a5b78 8e 96 02 0c     jal        FUN_OVR_229__800a5a38                            undefined FUN_OVR_229__800a5a38()
     9::800a5b7c 04 00 0a 24     _li        t2,0x4
     9::800a5b80 84 96 02 0c     jal        FUN_OVR_229__800a5a10                            undefined FUN_OVR_229__800a5a10()
     9::800a5b84 0c 00 0a 24     _li        t2,0xc
     9::800a5b88 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5b8c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5b90 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a5a24
     9::800a5b94 0c 00 0a 24     _li        t2,0xc
     9::800a5b98 9d 96 02 0c     jal        SUB_OVR_229__800a5a74
     9::800a5b9c 0c 00 0a 24     _li        t2,0xc
     9::800a5ba0 89 96 02 0c     jal        FUN_OVR_229__800a5a24                            undefined FUN_OVR_229__800a5a24()
     9::800a5ba4 04 00 0a 24     _li        t2,0x4
     9::800a5ba8 84 96 02 0c     jal        FUN_OVR_229__800a5a10                            undefined FUN_OVR_229__800a5a10()
     9::800a5bac 0c 00 0a 24     _li        t2,0xc
     9::800a5bb0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5bb4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5bb8 9f ff 01 04     bgez       zero,FUN_OVR_229__800a5a38
     9::800a5bbc 0c 00 0a 24     _li        t2,0xc
     9::800a5bc0 a2 96 02 0c     jal        SUB_OVR_229__800a5a88
     9::800a5bc4 0c 00 0a 24     _li        t2,0xc
     9::800a5bc8 8e 96 02 0c     jal        FUN_OVR_229__800a5a38                            undefined FUN_OVR_229__800a5a38()
     9::800a5bcc 08 00 0a 24     _li        t2,0x8
     9::800a5bd0 89 96 02 0c     jal        FUN_OVR_229__800a5a24                            undefined FUN_OVR_229__800a5a24()
     9::800a5bd4 0c 00 0a 24     _li        t2,0xc
     9::800a5bd8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5bdc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5be0 9a ff 01 04     bgez       zero,LAB_OVR_229__800a5a4c
     9::800a5be4 0c 00 0a 24     _li        t2,0xc
     9::800a5be8 98 96 02 0c     jal        FUN_OVR_229__800a5a60                            undefined FUN_OVR_229__800a5a60()
     9::800a5bec 0c 00 0a 24     _li        t2,0xc
     9::800a5bf0 89 96 02 0c     jal        FUN_OVR_229__800a5a24                            undefined FUN_OVR_229__800a5a24()
     9::800a5bf4 08 00 0a 24     _li        t2,0x8
     9::800a5bf8 8e 96 02 0c     jal        FUN_OVR_229__800a5a38                            undefined FUN_OVR_229__800a5a38()
     9::800a5bfc 0c 00 0a 24     _li        t2,0xc
     9::800a5c00 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5c04 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5c08 90 ff 01 04     bgez       zero,LAB_OVR_229__800a5a4c
     9::800a5c0c 0c 00 0a 24     _li        t2,0xc
     9::800a5c10 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a5c14 84 96 02 0c     jal        FUN_OVR_229__800a5a10                            undefined FUN_OVR_229__800a5a10()
     9::800a5c18 0c 00 0a 24     _li        t2,0xc
     9::800a5c1c 0c 00 03 24     li         v1,0xc
     9::800a5c20 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a5c24 89 96 02 0c     jal        FUN_OVR_229__800a5a24                            undefined FUN_OVR_229__800a5a24()
     9::800a5c28 0c 00 0a 24     _li        t2,0xc
     9::800a5c2c 30 00 03 24     li         v1,0x30
     9::800a5c30 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a5c34 8e 96 02 0c     jal        FUN_OVR_229__800a5a38                            undefined FUN_OVR_229__800a5a38()
     9::800a5c38 0c 00 0a 24     _li        t2,0xc
     9::800a5c3c 3c 00 03 24     li         v1,0x3c
     9::800a5c40 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a5c44 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a5c48 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a5c4c 7f ff 01 04     bgez       zero,LAB_OVR_229__800a5a4c
     9::800a5c50 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5c54()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5c54                           XREF[5]:     FUN_OVR_229__800a5e90:800a616c(c
                                                                                          FUN_OVR_229__800a5e90:800a6180(c
                                                                                          FUN_OVR_229__800a5e90:800a6194(c
                                                                                          FUN_OVR_229__800a5e90:800a61a8(c
                                                                                          FUN_OVR_229__800a5e90:800a61bc(c
     9::800a5c54 00 00 ab 85     lh         t3,0x0(t5)
     9::800a5c58 00 00 cc 85     lh         t4,0x0(t6)
     9::800a5c5c 00 00 eb a5     sh         t3,0x0(t7)
     9::800a5c60 21 18 6c 01     addu       v1,t3,t4
     9::800a5c64 43 18 03 00     sra        v1,v1,0x1
     9::800a5c68 00 00 03 a6     sh         v1,0x0(s0)
     9::800a5c6c 02 00 ab 85     lh         t3,0x2(t5)
     9::800a5c70 02 00 cc 85     lh         t4,0x2(t6)
     9::800a5c74 02 00 eb a5     sh         t3,0x2(t7)
     9::800a5c78 21 18 6c 01     addu       v1,t3,t4
     9::800a5c7c 43 18 03 00     sra        v1,v1,0x1
     9::800a5c80 02 00 03 a6     sh         v1,0x2(s0)
     9::800a5c84 04 00 ab 85     lh         t3,0x4(t5)
     9::800a5c88 04 00 cc 85     lh         t4,0x4(t6)
     9::800a5c8c 04 00 eb a5     sh         t3,0x4(t7)
     9::800a5c90 21 18 6c 01     addu       v1,t3,t4
     9::800a5c94 43 18 03 00     sra        v1,v1,0x1
     9::800a5c98 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a5c9c 00 08 83 48     gte_ldVZ0  v1
     9::800a5ca0 04 00 03 a6     sh         v1,0x4(s0)
     9::800a5ca4 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a5ca8 01 00 18 4a     RTPS
     9::800a5cac 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a5cb0 08 00 eb a1     sb         t3,0x8(t7)
     9::800a5cb4 21 18 6c 01     addu       v1,t3,t4
     9::800a5cb8 43 18 03 00     sra        v1,v1,0x1
     9::800a5cbc 08 00 03 a2     sb         v1,0x8(s0)
     9::800a5cc0 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a5cc4 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a5cc8 09 00 eb a1     sb         t3,0x9(t7)
     9::800a5ccc 21 18 6c 01     addu       v1,t3,t4
     9::800a5cd0 43 18 03 00     sra        v1,v1,0x1
     9::800a5cd4 09 00 03 a2     sb         v1,0x9(s0)
     9::800a5cd8 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a5cdc 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a5ce0 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a5ce4 21 18 6c 01     addu       v1,t3,t4
     9::800a5ce8 43 18 03 00     sra        v1,v1,0x1
     9::800a5cec 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a5cf0 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a5cf4 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a5cf8 06 00 eb a1     sb         t3,0x6(t7)
     9::800a5cfc 21 18 6c 01     addu       v1,t3,t4
     9::800a5d00 43 18 03 00     sra        v1,v1,0x1
     9::800a5d04 06 00 03 a2     sb         v1,0x6(s0)
     9::800a5d08 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a5d0c 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a5d10 07 00 eb a1     sb         t3,0x7(t7)
     9::800a5d14 21 18 6c 01     addu       v1,t3,t4
     9::800a5d18 43 18 03 00     sra        v1,v1,0x1
     9::800a5d1c 07 00 03 a2     sb         v1,0x7(s0)
     9::800a5d20 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a5d24 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a5d28 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a5d2c 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a5d30 5c 00 2b 8c     lw         t3,0x5c(at)
     9::800a5d34 00 98 03 48     gte_stSZ3  v1
     9::800a5d38 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a5d3c 10 00 03 ae     sw         v1,0x10(s0)
     9::800a5d40 23 40 6b 00     subu       t0,v1,t3
     9::800a5d44 c2 47 08 00     srl        t0,t0,0x1f
     9::800a5d48 12 00 08 a2     sb         t0,0x12(s0)
     9::800a5d4c 40 18 03 00     sll        v1,v1,0x1
     9::800a5d50 23 40 6b 00     subu       t0,v1,t3
     9::800a5d54 c2 47 08 00     srl        t0,t0,0x1f
     9::800a5d58 08 00 e0 03     jr         ra
     9::800a5d5c 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5d60()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5d60                           XREF[12]:    FUN_OVR_229__800a5a10:800a5a1c(j
                                                                                          FUN_OVR_229__800a5a24:800a5a30(j
                                                                                          FUN_OVR_229__800a5a38:800a5a44(j
                                                                                          FUN_OVR_229__800a5a60:800a5a58(j
                                                                                          FUN_OVR_229__800a5a60:800a5a6c(j
                                                                                          FUN_OVR_229__800a5a60:800a5a80(j
                                                                                          FUN_OVR_229__800a5a60:800a5a94(j
                                                                                          FUN_OVR_229__800a5a60:800a5aa8(j
                                                                                          FUN_OVR_229__800a5a60:800a5ac0(c
                                                                                          FUN_OVR_229__800a5a60:800a5ad8(c
                                                                                          FUN_OVR_229__800a5a60:800a5b40(c
                                                                                          FUN_OVR_229__800a5a60:800a5b58(c
     9::800a5d60 13 00 6f 82     lb         t7,0x13(s3)
     9::800a5d64 13 00 90 82     lb         s0,0x13(s4)
     9::800a5d68 13 00 b1 82     lb         s1,0x13(s5)
     9::800a5d6c 13 00 d2 82     lb         s2,0x13(s6)
     9::800a5d70 24 18 f0 01     and        v1,t7,s0
     9::800a5d74 24 18 71 00     and        v1,v1,s1
     9::800a5d78 24 18 72 00     and        v1,v1,s2
     9::800a5d7c 22 ff 60 14     bne        v1,zero,LAB_OVR_229__800a5a08
     9::800a5d80 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a5d84 12 00 90 82     lb         s0,0x12(s4)
     9::800a5d88 12 00 b1 82     lb         s1,0x12(s5)
     9::800a5d8c 12 00 d2 82     lb         s2,0x12(s6)
     9::800a5d90 25 78 f0 01     or         t7,t7,s0
     9::800a5d94 25 78 f1 01     or         t7,t7,s1
     9::800a5d98 25 78 f2 01     or         t7,t7,s2
     9::800a5d9c 2e 00 e0 15     bne        t7,zero,LAB_OVR_229__800a5e58
     9::800a5da0 0c 00 03 24     _li        v1,0xc
     9::800a5da4 70 00 2a ac     sw         t2,0x70(at)
     9::800a5da8 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a5dac 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a5db0 94 01 2a 8c     lw         t2,0x194(at)
     9::800a5db4 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a5db8 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a5dbc 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a5dc0 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a5dc4 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a5dc8 06 00 40 4b     NCLIP
     9::800a5dcc 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a5dd0 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a5dd4 23 78 68 01     subu       t7,t3,t0
     9::800a5dd8 23 80 88 01     subu       s0,t4,t0
     9::800a5ddc 23 88 a8 01     subu       s1,t5,t0
     9::800a5de0 23 90 c8 01     subu       s2,t6,t0
     9::800a5de4 00 c0 08 48     gte_stMAC0 t0
     9::800a5de8 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a5dec 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a5df8
     9::800a5df0 22 40 08 00     _sub       t0,zero,t0
     9::800a5df4 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a5df8                           XREF[1]:     OVR_229::800a5dec(j)  
     9::800a5df8 06 00 40 4b     NCLIP
     9::800a5dfc 24 18 6c 01     and        v1,t3,t4
     9::800a5e00 24 18 6d 00     and        v1,v1,t5
     9::800a5e04 24 18 6e 00     and        v1,v1,t6
     9::800a5e08 25 78 f0 01     or         t7,t7,s0
     9::800a5e0c 25 78 f1 01     or         t7,t7,s1
     9::800a5e10 27 78 f2 01     nor        t7,t7,s2
     9::800a5e14 25 78 e3 01     or         t7,t7,v1
     9::800a5e18 fb fe e0 05     bltz       t7,LAB_OVR_229__800a5a08
     9::800a5e1c 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a5e20 f9 fe e0 05     bltz       t7,LAB_OVR_229__800a5a08
     9::800a5e24 00 c0 03 48     _gte_stM   v1
     9::800a5e28 25 40 09 01     or         t0,t0,t1
     9::800a5e2c 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a5e38
     9::800a5e30 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a5e34 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a5e38                           XREF[1]:     OVR_229::800a5e2c(j)  
     9::800a5e38 80 40 08 00     sll        t0,t0,0x2
     9::800a5e3c 25 18 69 00     or         v1,v1,t1
     9::800a5e40 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a5e44 c0 18 03 00     sll        v1,v1,0x3
     9::800a5e48 70 00 2a 8c     lw         t2,0x70(at)
     9::800a5e4c 25 18 68 00     or         v1,v1,t0
     9::800a5e50 24 18 6a 00     and        v1,v1,t2
     9::800a5e54 ec fe 60 10     beq        v1,zero,LAB_OVR_229__800a5a08
                             LAB_OVR_229__800a5e58                           XREF[1]:     OVR_229::800a5d9c(j)  
     9::800a5e58 70 00 23 ac     _sw        v1,0x70(at)
     9::800a5e5c 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a5e60 24 03 28 24     addiu      t0,at,0x324
     9::800a5e64 ea 00 1e 11     beq        t0,s8,LAB_OVR_229__800a6210
     9::800a5e68 04 00 39 27     _addiu     t9,t9,0x4
     9::800a5e6c 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a5e70 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a5e74 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a5e78 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a5e7c c0 fe 71 25     addiu      s1,t3,-0x140
     9::800a5e80 c0 fe 92 25     addiu      s2,t4,-0x140
     9::800a5e84 c0 fe af 25     addiu      t7,t5,-0x140
     9::800a5e88 a8 00 01 04     bgez       zero,LAB_OVR_229__800a612c
     9::800a5e8c c0 fe d0 25     _addiu     s0,t6,-0x140
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a5e90()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a5e90                           XREF[4]:     OVR_229::800a59b8(c), 
                                                                                          OVR_229::800a59cc(c), 
                                                                                          OVR_229::800a59e0(c), 
                                                                                          OVR_229::800a59f4(c)  
     9::800a5e90 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a5e94 b4 00 ca af     sw         t2,0xb4(s8)
     9::800a5e98 06 50 09 01     srlv       t2,t1,t0
     9::800a5e9c 1f 00 4a 31     andi       t2,t2,0x1f
     9::800a5ea0 80 50 0a 00     sll        t2,t2,0x2
     9::800a5ea4 21 50 41 01     addu       t2,t2,at
     9::800a5ea8 ec 00 4a 8d     lw         t2,0xec(t2)
     9::800a5eac 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a5eb0 94 01 2a ac     sw         t2,0x194(at)
     9::800a5eb4 02 9e 0a 00     srl        s3,t2,0x18
     9::800a5eb8 1f 00 73 32     andi       s3,s3,0x1f
     9::800a5ebc 06 98 63 02     srlv       s3,v1,s3
     9::800a5ec0 ff 00 73 32     andi       s3,s3,0xff
     9::800a5ec4 21 98 7e 02     addu       s3,s3,s8
     9::800a5ec8 02 a4 0a 00     srl        s4,t2,0x10
     9::800a5ecc 1f 00 94 32     andi       s4,s4,0x1f
     9::800a5ed0 06 a0 83 02     srlv       s4,v1,s4
     9::800a5ed4 ff 00 94 32     andi       s4,s4,0xff
     9::800a5ed8 21 a0 9e 02     addu       s4,s4,s8
     9::800a5edc 02 aa 0a 00     srl        s5,t2,0x8
     9::800a5ee0 1f 00 b5 32     andi       s5,s5,0x1f
     9::800a5ee4 06 a8 a3 02     srlv       s5,v1,s5
     9::800a5ee8 ff 00 b5 32     andi       s5,s5,0xff
     9::800a5eec 21 a8 be 02     addu       s5,s5,s8
     9::800a5ef0 1f 00 56 31     andi       s6,t2,0x1f
     9::800a5ef4 06 b0 c3 02     srlv       s6,v1,s6
     9::800a5ef8 ff 00 d6 32     andi       s6,s6,0xff
     9::800a5efc 21 b0 de 02     addu       s6,s6,s8
     9::800a5f00 13 00 6f 82     lb         t7,0x13(s3)
     9::800a5f04 13 00 90 82     lb         s0,0x13(s4)
     9::800a5f08 13 00 b1 82     lb         s1,0x13(s5)
     9::800a5f0c 13 00 d2 82     lb         s2,0x13(s6)
     9::800a5f10 24 18 f0 01     and        v1,t7,s0
     9::800a5f14 24 18 71 00     and        v1,v1,s1
     9::800a5f18 24 18 72 00     and        v1,v1,s2
     9::800a5f1c ba fe 60 14     bne        v1,zero,LAB_OVR_229__800a5a08
     9::800a5f20 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a5f24 12 00 90 82     lb         s0,0x12(s4)
     9::800a5f28 12 00 b1 82     lb         s1,0x12(s5)
     9::800a5f2c 12 00 d2 82     lb         s2,0x12(s6)
     9::800a5f30 25 78 f0 01     or         t7,t7,s0
     9::800a5f34 25 78 f1 01     or         t7,t7,s1
     9::800a5f38 25 78 f2 01     or         t7,t7,s2
     9::800a5f3c 28 00 e0 15     bne        t7,zero,LAB_OVR_229__800a5fe0
     9::800a5f40 0c 00 03 24     _li        v1,0xc
     9::800a5f44 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a5f48 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a5f4c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a5f50 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a5f54 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a5f58 06 00 40 4b     NCLIP
     9::800a5f5c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a5f60 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a5f64 23 78 68 01     subu       t7,t3,t0
     9::800a5f68 23 80 88 01     subu       s0,t4,t0
     9::800a5f6c 23 88 a8 01     subu       s1,t5,t0
     9::800a5f70 23 90 c8 01     subu       s2,t6,t0
     9::800a5f74 00 c0 08 48     gte_stMAC0 t0
     9::800a5f78 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a5f7c 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a5f88
     9::800a5f80 22 40 08 00     _sub       t0,zero,t0
     9::800a5f84 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a5f88                           XREF[1]:     OVR_229::800a5f7c(j)  
     9::800a5f88 06 00 40 4b     NCLIP
     9::800a5f8c 24 18 6c 01     and        v1,t3,t4
     9::800a5f90 24 18 6d 00     and        v1,v1,t5
     9::800a5f94 24 18 6e 00     and        v1,v1,t6
     9::800a5f98 25 78 f0 01     or         t7,t7,s0
     9::800a5f9c 25 78 f1 01     or         t7,t7,s1
     9::800a5fa0 27 78 f2 01     nor        t7,t7,s2
     9::800a5fa4 25 78 e3 01     or         t7,t7,v1
     9::800a5fa8 97 fe e0 05     bltz       t7,LAB_OVR_229__800a5a08
     9::800a5fac 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a5fb0 95 fe e0 05     bltz       t7,LAB_OVR_229__800a5a08
     9::800a5fb4 00 c0 03 48     _gte_stM   v1
     9::800a5fb8 25 40 09 01     or         t0,t0,t1
     9::800a5fbc 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a5fc8
     9::800a5fc0 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a5fc4 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a5fc8                           XREF[1]:     OVR_229::800a5fbc(j)  
     9::800a5fc8 80 40 08 00     sll        t0,t0,0x2
     9::800a5fcc 25 18 69 00     or         v1,v1,t1
     9::800a5fd0 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a5fd4 c0 18 03 00     sll        v1,v1,0x3
     9::800a5fd8 25 18 68 00     or         v1,v1,t0
     9::800a5fdc 8a fe 60 10     beq        v1,zero,LAB_OVR_229__800a5a08
                             LAB_OVR_229__800a5fe0                           XREF[1]:     OVR_229::800a5f3c(j)  
     9::800a5fe0 70 00 23 ac     _sw        v1,0x70(at)
     9::800a5fe4 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a5fe8 04 00 39 27     addiu      t9,t9,0x4
     9::800a5fec c2 4f 09 00     srl        t1,t1,0x1f
     9::800a5ff0 c0 4f 09 00     sll        t1,t1,0x1f
     9::800a5ff4 c2 57 0a 00     srl        t2,t2,0x1f
     9::800a5ff8 80 57 0a 00     sll        t2,t2,0x1e
     9::800a5ffc 25 50 49 01     or         t2,t2,t1
     9::800a6000 80 00 2a ac     sw         t2,0x80(at)
     9::800a6004 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a6008 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a600c 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a6010 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a6014 b4 00 c3 8f     lw         v1,0xb4(s8)
     9::800a6018 23 50 6c 01     subu       t2,t3,t4
     9::800a601c 82 48 03 00     srl        t1,v1,0x2
     9::800a6020 21 48 38 01     addu       t1,t1,t8
     9::800a6024 18 00 29 81     lb         t1,0x18(t1)
     9::800a6028 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a6034
     9::800a602c 21 e0 60 01     _move      gp,t3
     9::800a6030 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a6034                           XREF[1]:     OVR_229::800a6028(j)  
     9::800a6034 23 50 8d 03     subu       t2,gp,t5
     9::800a6038 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a6044
     9::800a603c 21 18 78 00     _addu      v1,v1,t8
     9::800a6040 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a6044                           XREF[1]:     OVR_229::800a6038(j)  
     9::800a6044 23 50 8e 03     subu       t2,gp,t6
     9::800a6048 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a6054
     9::800a604c 1c 00 63 8c     _lw        v1,0x1c(v1)
     9::800a6050 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a6054                           XREF[1]:     OVR_229::800a6048(j)  
     9::800a6054 21 50 80 03     move       t2,gp
     9::800a6058 82 e1 1c 00     srl        gp,gp,0x6
     9::800a605c 21 e0 89 03     addu       gp,gp,t1
     9::800a6060 01 00 69 30     andi       t1,v1,0x1
     9::800a6064 02 00 20 11     beq        t1,zero,LAB_OVR_229__800a6070
     9::800a6068 80 e0 1c 00     _sll       gp,gp,0x2
     9::800a606c ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_229__800a6070                           XREF[1]:     OVR_229::800a6064(j)  
     9::800a6070 02 00 81 07     bgez       gp,LAB_OVR_229__800a607c
     9::800a6074 21 e0 85 03     _addu      gp,gp,a1
     9::800a6078 21 e0 a0 00     move       gp,a1
                             LAB_OVR_229__800a607c                           XREF[1]:     OVR_229::800a6070(j)  
     9::800a607c 24 00 69 8c     lw         t1,0x24(v1)
     9::800a6080 c0 f9 48 25     addiu      t0,t2,-0x640
     9::800a6084 84 00 29 ac     sw         t1,0x84(at)
     9::800a6088 0a 00 01 05     bgez       t0,LAB_OVR_229__800a60b4
     9::800a608c 00 fb 48 25     _addiu     t0,t2,-0x500
     9::800a6090 0c 00 63 24     addiu      v1,v1,0xc
     9::800a6094 07 00 01 05     bgez       t0,LAB_OVR_229__800a60b4
     9::800a6098 80 fd 48 25     _addiu     t0,t2,-0x280
     9::800a609c 0c 00 63 24     addiu      v1,v1,0xc
     9::800a60a0 04 00 01 05     bgez       t0,LAB_OVR_229__800a60b4
     9::800a60a4 00 00 00 00     _nop
     9::800a60a8 02 00 20 05     bltz       t1,LAB_OVR_229__800a60b4
     9::800a60ac 00 00 00 00     _nop
     9::800a60b0 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_229__800a60b4                           XREF[4]:     OVR_229::800a6088(j), 
                                                                                          OVR_229::800a6094(j), 
                                                                                          OVR_229::800a60a0(j), 
                                                                                          OVR_229::800a60a8(j)  
     9::800a60b4 94 01 2a 8c     lw         t2,0x194(at)
     9::800a60b8 00 00 68 8c     lw         t0,0x0(v1)
     9::800a60bc 04 00 69 8c     lw         t1,0x4(v1)
     9::800a60c0 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a60c4 ac 01 28 ac     sw         t0,0x1ac(at)
     9::800a60c8 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a60cc 00 52 0a 00     sll        t2,t2,0x8
     9::800a60d0 0a 00 40 05     bltz       t2,LAB_OVR_229__800a60fc
     9::800a60d4 b0 01 29 ac     _sw        t1,0x1b0(at)
     9::800a60d8 06 00 68 a6     sh         t0,0x6(s3)
     9::800a60dc 08 00 68 8c     lw         t0,0x8(v1)
     9::800a60e0 06 00 89 a6     sh         t1,0x6(s4)
     9::800a60e4 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a60e8 00 54 0a 00     sll        t2,t2,0x10
     9::800a60ec 0b 00 40 05     bltz       t2,LAB_OVR_229__800a611c
     9::800a60f0 02 4c 08 00     _srl       t1,t0,0x10
     9::800a60f4 09 00 01 04     bgez       zero,LAB_OVR_229__800a611c
     9::800a60f8 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_229__800a60fc                           XREF[1]:     OVR_229::800a60d0(j)  
     9::800a60fc 06 00 69 a6     sh         t1,0x6(s3)
     9::800a6100 08 00 69 8c     lw         t1,0x8(v1)
     9::800a6104 00 54 0a 00     sll        t2,t2,0x10
     9::800a6108 06 00 88 a6     sh         t0,0x6(s4)
     9::800a610c 02 44 09 00     srl        t0,t1,0x10
     9::800a6110 02 00 40 05     bltz       t2,LAB_OVR_229__800a611c
     9::800a6114 06 00 a8 a6     _sh        t0,0x6(s5)
     9::800a6118 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a611c                           XREF[3]:     OVR_229::800a60ec(j), 
                                                                                          OVR_229::800a60f4(j), 
                                                                                          OVR_229::800a6110(j)  
     9::800a611c 80 fd 71 25     addiu      s1,t3,-0x280
     9::800a6120 80 fd 92 25     addiu      s2,t4,-0x280
     9::800a6124 80 fd af 25     addiu      t7,t5,-0x280
     9::800a6128 80 fd d0 25     addiu      s0,t6,-0x280
                             LAB_OVR_229__800a612c                           XREF[1]:     FUN_OVR_229__800a5d60:800a5e88(j
     9::800a612c 42 8f 11 00     srl        s1,s1,0x1d
     9::800a6130 04 00 31 32     andi       s1,s1,0x4
     9::800a6134 02 97 12 00     srl        s2,s2,0x1c
     9::800a6138 08 00 52 32     andi       s2,s2,0x8
     9::800a613c 25 88 32 02     or         s1,s1,s2
     9::800a6140 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a6144 10 00 ef 31     andi       t7,t7,0x10
     9::800a6148 25 88 2f 02     or         s1,s1,t7
     9::800a614c 82 86 10 00     srl        s0,s0,0x1a
     9::800a6150 20 00 10 32     andi       s0,s0,0x20
     9::800a6154 25 88 30 02     or         s1,s1,s0
     9::800a6158 26 00 20 12     beq        s1,zero,LAB_OVR_229__800a61f4
     9::800a615c 21 68 60 02     _move      t5,s3
     9::800a6160 21 70 80 02     move       t6,s4
     9::800a6164 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a6168 00 00 cf 27     addiu      t7,s8,0x0
     9::800a616c 15 97 02 0c     jal        FUN_OVR_229__800a5c54                            undefined FUN_OVR_229__800a5c54()
     9::800a6170 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a6174 21 68 80 02     move       t5,s4
     9::800a6178 21 70 c0 02     move       t6,s6
     9::800a617c 14 00 cf 27     addiu      t7,s8,0x14
     9::800a6180 15 97 02 0c     jal        FUN_OVR_229__800a5c54                            undefined FUN_OVR_229__800a5c54()
     9::800a6184 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a6188 21 68 a0 02     move       t5,s5
     9::800a618c 21 70 60 02     move       t6,s3
     9::800a6190 28 00 cf 27     addiu      t7,s8,0x28
     9::800a6194 15 97 02 0c     jal        FUN_OVR_229__800a5c54                            undefined FUN_OVR_229__800a5c54()
     9::800a6198 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a619c 21 68 c0 02     move       t5,s6
     9::800a61a0 21 70 a0 02     move       t6,s5
     9::800a61a4 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a61a8 15 97 02 0c     jal        FUN_OVR_229__800a5c54                            undefined FUN_OVR_229__800a5c54()
     9::800a61ac a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a61b0 50 00 cd 27     addiu      t5,s8,0x50
     9::800a61b4 a0 00 ce 27     addiu      t6,s8,0xa0
     9::800a61b8 50 00 cf 27     addiu      t7,s8,0x50
     9::800a61bc 15 97 02 0c     jal        FUN_OVR_229__800a5c54                            undefined FUN_OVR_229__800a5c54()
     9::800a61c0 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a61c4 21 18 21 02     addu       v1,s1,at
     9::800a61c8 48 01 63 8c     lw         v1,0x148(v1)
     9::800a61cc 0a 80 08 3c     lui        t0,0x800a
     9::800a61d0 e4 61 08 25     addiu      t0,t0,0x61e4
     9::800a61d4 9c 00 23 ac     sw         v1,0x9c(at)
     9::800a61d8 3c 00 28 af     sw         t0=>LAB_OVR_229__800a61e4,0x3c(t9)
     9::800a61dc 08 00 60 00     jr         v1
     9::800a61e0 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a61e4                           XREF[1]:     FUN_OVR_229__800a5e90:800a61d8(*
     9::800a61e4 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a61e8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a61ec 08 00 e0 03     jr         ra
     9::800a61f0 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a61f4                           XREF[1]:     OVR_229::800a6158(j)  
     9::800a61f4 70 00 23 8c     lw         v1,0x70(at)
     9::800a61f8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a61fc 21 18 61 00     addu       v1,v1,at
     9::800a6200 84 01 63 8c     lw         v1,0x184(v1)
     9::800a6204 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a6208 08 00 60 00     jr         v1
     9::800a620c 00 00 00 00     _nop
                             LAB_OVR_229__800a6210                           XREF[1]:     OVR_229::800a5e64(j)  
     9::800a6210 84 00 23 8c     lw         v1,0x84(at)
     9::800a6214 24 03 2a 24     addiu      t2,at,0x324
     9::800a6218 26 00 60 1c     bgtz       v1,LAB_OVR_229__800a62b4
     9::800a621c 20 03 28 8c     _lw        t0,0x320(at)
     9::800a6220 d8 03 29 8c     lw         t1,0x3d8(at)
     9::800a6224 16 00 5e 15     bne        t2,s8,LAB_OVR_229__800a6280
     9::800a6228 9c 00 23 8c     _lw        v1,0x9c(at)
     9::800a622c 0a 80 0a 3c     lui        t2,0x800a
     9::800a6230 10 5c 4a 25     addiu      t2,t2,0x5c10
     9::800a6234 1f 00 6a 14     bne        v1,t2,LAB_OVR_229__800a62b4
     9::800a6238 94 01 23 8c     _lw        v1,0x194(at)
     9::800a623c 40 40 08 00     sll        t0,t0,0x1
     9::800a6240 00 1a 03 00     sll        v1,v1,0x8
     9::800a6244 02 00 61 04     bgez       v1,LAB_OVR_229__800a6250
     9::800a6248 84 00 2a 8c     _lw        t2,0x84(at)
     9::800a624c c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_229__800a6250                           XREF[1]:     OVR_229::800a6244(j)  
     9::800a6250 21 40 09 01     addu       t0,t0,t1
     9::800a6254 21 50 48 01     addu       t2,t2,t0
     9::800a6258 00 00 48 8d     lw         t0,0x0(t2)
     9::800a625c 04 00 49 8d     lw         t1,0x4(t2)
     9::800a6260 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a6264 06 00 68 a6     sh         t0,0x6(s3)
     9::800a6268 08 00 48 85     lh         t0,0x8(t2)
     9::800a626c a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a6270 06 00 89 a6     sh         t1,0x6(s4)
     9::800a6274 0a 00 49 85     lh         t1,0xa(t2)
     9::800a6278 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a627c 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a6280                           XREF[2]:     OVR_229::800a6224(j), 
                                                                                          OVR_229::800a62c0(j)  
     9::800a6280 70 00 23 8c     lw         v1,0x70(at)
     9::800a6284 00 00 00 00     nop
     9::800a6288 21 18 61 00     addu       v1,v1,at
     9::800a628c 84 01 63 8c     lw         v1,0x184(v1)
     9::800a6290 00 00 00 00     nop
     9::800a6294 09 f8 60 00     jalr       v1
     9::800a6298 fc ff 39 27     _addiu     t9,t9,-0x4
     9::800a629c 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a62a0 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a62a4 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a62a8 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a62ac 08 00 e0 03     jr         ra
     9::800a62b0 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_229__800a62b4                           XREF[2]:     OVR_229::800a6218(j), 
                                                                                          OVR_229::800a6234(j)  
     9::800a62b4 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a62b8 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a62bc a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a62c0 ef ff 01 04     bgez       zero,LAB_OVR_229__800a6280
     9::800a62c4 a4 01 29 ac     _sw        t1,0x1a4(at)
     9::800a62c8 21 98 80 02     move       s3,s4
     9::800a62cc 21 a0 c0 02     move       s4,s6
     9::800a62d0 13 00 6f 82     lb         t7,0x13(s3)
     9::800a62d4 13 00 90 82     lb         s0,0x13(s4)
     9::800a62d8 13 00 b1 82     lb         s1,0x13(s5)
     9::800a62dc 24 18 f0 01     and        v1,t7,s0
     9::800a62e0 24 18 71 00     and        v1,v1,s1
     9::800a62e4 c8 fd 60 04     bltz       v1,LAB_OVR_229__800a5a08
     9::800a62e8 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a62ec 12 00 90 82     lb         s0,0x12(s4)
     9::800a62f0 12 00 b1 82     lb         s1,0x12(s5)
     9::800a62f4 25 78 f0 01     or         t7,t7,s0
     9::800a62f8 25 78 f1 01     or         t7,t7,s1
     9::800a62fc 62 00 e0 05     bltz       t7,LAB_OVR_229__800a6488
     9::800a6300 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a6304 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a6308 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a630c 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a6310 08 00 90 8e     lw         s0,0x8(s4)
     9::800a6314 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a6318 06 00 73 86     lh         s3,0x6(s3)
     9::800a631c 06 00 94 86     lh         s4,0x6(s4)
     9::800a6320 06 00 b5 86     lh         s5,0x6(s5)
     9::800a6324 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a6328 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a632c a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a6330 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a6334 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a6338 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a633c 60 00 03 3c     lui        v1,0x60
     9::800a6340 24 48 83 02     and        t1,s4,v1
     9::800a6344 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a6350
     9::800a6348 00 36 03 3c     _lui       v1,0x3600
     9::800a634c 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a6350                           XREF[1]:     OVR_229::800a6344(j)  
     9::800a6350 25 18 6f 00     or         v1,v1,t7
     9::800a6354 04 00 43 ac     sw         v1,0x4(v0)
     9::800a6358 08 00 4b ac     sw         t3,0x8(v0)
     9::800a635c 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a6360 10 00 50 ac     sw         s0,0x10(v0)
     9::800a6364 14 00 4c ac     sw         t4,0x14(v0)
     9::800a6368 18 00 54 ac     sw         s4,0x18(v0)
     9::800a636c 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a6370 20 00 4d ac     sw         t5,0x20(v0)
     9::800a6374 24 00 55 ac     sw         s5,0x24(v0)
     9::800a6378 28 00 09 24     li         t1,0x28
     9::800a637c 39 00 01 04     bgez       zero,LAB_OVR_229__800a6464
     9::800a6380 00 09 0a 3c     _lui       t2,0x900
     9::800a6384 13 00 6f 82     lb         t7,0x13(s3)
     9::800a6388 13 00 90 82     lb         s0,0x13(s4)
     9::800a638c 13 00 b1 82     lb         s1,0x13(s5)
     9::800a6390 13 00 d2 82     lb         s2,0x13(s6)
     9::800a6394 24 18 f0 01     and        v1,t7,s0
     9::800a6398 24 18 71 00     and        v1,v1,s1
     9::800a639c 24 18 72 00     and        v1,v1,s2
     9::800a63a0 99 fd 60 14     bne        v1,zero,LAB_OVR_229__800a5a08
     9::800a63a4 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a63a8 12 00 90 82     lb         s0,0x12(s4)
     9::800a63ac 12 00 b1 82     lb         s1,0x12(s5)
     9::800a63b0 12 00 d2 82     lb         s2,0x12(s6)
     9::800a63b4 25 78 f0 01     or         t7,t7,s0
     9::800a63b8 25 78 f1 01     or         t7,t7,s1
     9::800a63bc 25 78 f2 01     or         t7,t7,s2
     9::800a63c0 5a 00 e0 15     bne        t7,zero,LAB_OVR_229__800a652c
     9::800a63c4 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a63c8 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a63cc 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a63d0 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a63d4 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a63d8 08 00 90 8e     lw         s0,0x8(s4)
     9::800a63dc 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a63e0 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a63e4 06 00 73 86     lh         s3,0x6(s3)
     9::800a63e8 06 00 94 86     lh         s4,0x6(s4)
     9::800a63ec 06 00 b5 86     lh         s5,0x6(s5)
     9::800a63f0 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a63f4 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a63f8 06 00 d4 86     lh         s4,0x6(s6)
     9::800a63fc a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a6400 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a6404 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a6408 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a640c a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a6410 60 00 03 3c     lui        v1,0x60
     9::800a6414 24 48 83 02     and        t1,s4,v1
     9::800a6418 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a6424
     9::800a641c 00 3e 03 3c     _lui       v1,0x3e00
     9::800a6420 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a6424                           XREF[1]:     OVR_229::800a6418(j)  
     9::800a6424 25 18 6f 00     or         v1,v1,t7
     9::800a6428 04 00 43 ac     sw         v1,0x4(v0)
     9::800a642c 08 00 4b ac     sw         t3,0x8(v0)
     9::800a6430 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a6434 10 00 50 ac     sw         s0,0x10(v0)
     9::800a6438 14 00 4c ac     sw         t4,0x14(v0)
     9::800a643c 18 00 54 ac     sw         s4,0x18(v0)
     9::800a6440 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a6444 20 00 4d ac     sw         t5,0x20(v0)
     9::800a6448 24 00 55 ac     sw         s5,0x24(v0)
     9::800a644c 28 00 52 ac     sw         s2,0x28(v0)
     9::800a6450 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a6454 02 1c 15 00     srl        v1,s5,0x10
     9::800a6458 30 00 43 ac     sw         v1,0x30(v0)
     9::800a645c 34 00 09 24     li         t1,0x34
     9::800a6460 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a6464                           XREF[1]:     OVR_229::800a637c(j)  
     9::800a6464 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a6468 00 42 02 00     sll        t0,v0,0x8
     9::800a646c 02 42 08 00     srl        t0,t0,0x8
     9::800a6470 25 18 6a 00     or         v1,v1,t2
     9::800a6474 00 00 43 ac     sw         v1,0x0(v0)
     9::800a6478 21 10 49 00     addu       v0,v0,t1
     9::800a647c 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a6480 08 00 e0 03     jr         ra
     9::800a6484 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_229__800a6488                           XREF[1]:     OVR_229::800a62fc(j)  
     9::800a6488 58 00 3f ac     sw         ra,0x58(at)
     9::800a648c 98 01 2f 84     lh         t7,0x198(at)
     9::800a6490 9a 01 30 84     lh         s0,0x19a(at)
     9::800a6494 9c 01 31 84     lh         s1,0x19c(at)
     9::800a6498 00 00 63 86     lh         v1,0x0(s3)
     9::800a649c 02 00 68 86     lh         t0,0x2(s3)
     9::800a64a0 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a64a4 04 00 69 86     _lh        t1,0x4(s3)
     9::800a64a8 0b 00 40 05     bltz       t2,LAB_OVR_229__800a64d8
     9::800a64ac 00 00 83 86     _lh        v1,0x0(s4)
     9::800a64b0 02 00 88 86     lh         t0,0x2(s4)
     9::800a64b4 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a64b8 04 00 89 86     _lh        t1,0x4(s4)
     9::800a64bc 06 00 40 05     bltz       t2,LAB_OVR_229__800a64d8
     9::800a64c0 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a64c4 02 00 a8 86     lh         t0,0x2(s5)
     9::800a64c8 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a64cc 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a64d0 58 00 3f 8c     lw         ra,0x58(at)
     9::800a64d4 4c fd 41 05     bgez       t2,LAB_OVR_229__800a5a08
                             LAB_OVR_229__800a64d8                           XREF[2]:     OVR_229::800a64a8(j), 
                                                                                          OVR_229::800a64bc(j)  
     9::800a64d8 10 00 2f 8c     lw         t7,0x10(at)
     9::800a64dc 80 00 23 8c     lw         v1,0x80(at)
     9::800a64e0 a6 01 28 84     lh         t0,0x1a6(at)
     9::800a64e4 a2 01 29 84     lh         t1,0x1a2(at)
     9::800a64e8 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a64ec 00 00 e3 ad     sw         v1,0x0(t7)
     9::800a64f0 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a64f4 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a64f8 21 68 60 02     move       t5,s3
     9::800a64fc 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a6500 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a6504 21 68 80 02     move       t5,s4
     9::800a6508 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a650c 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a6510 21 68 a0 02     move       t5,s5
     9::800a6514 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a6518 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a651c 58 00 3f 8c     lw         ra,0x58(at)
     9::800a6520 30 00 ef 25     addiu      t7,t7,0x30
     9::800a6524 08 00 e0 03     jr         ra
     9::800a6528 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_229__800a652c                           XREF[1]:     OVR_229::800a63c0(j)  
     9::800a652c 58 00 3f ac     sw         ra,0x58(at)
     9::800a6530 98 01 2f 84     lh         t7,0x198(at)
     9::800a6534 9a 01 30 84     lh         s0,0x19a(at)
     9::800a6538 9c 01 31 84     lh         s1,0x19c(at)
     9::800a653c 00 00 63 86     lh         v1,0x0(s3)
     9::800a6540 02 00 68 86     lh         t0,0x2(s3)
     9::800a6544 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a6548 04 00 69 86     _lh        t1,0x4(s3)
     9::800a654c 10 00 40 05     bltz       t2,LAB_OVR_229__800a6590
     9::800a6550 00 00 83 86     _lh        v1,0x0(s4)
     9::800a6554 02 00 88 86     lh         t0,0x2(s4)
     9::800a6558 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a655c 04 00 89 86     _lh        t1,0x4(s4)
     9::800a6560 0b 00 40 05     bltz       t2,LAB_OVR_229__800a6590
     9::800a6564 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a6568 02 00 a8 86     lh         t0,0x2(s5)
     9::800a656c 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a6570 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a6574 06 00 40 05     bltz       t2,LAB_OVR_229__800a6590
     9::800a6578 00 00 c3 86     _lh        v1,0x0(s6)
     9::800a657c 02 00 c8 86     lh         t0,0x2(s6)
     9::800a6580 7d 99 02 0c     jal        FUN_OVR_229__800a65f4                            undefined FUN_OVR_229__800a65f4()
     9::800a6584 04 00 c9 86     _lh        t1,0x4(s6)
     9::800a6588 58 00 3f 8c     lw         ra,0x58(at)
     9::800a658c 1e fd 41 05     bgez       t2,LAB_OVR_229__800a5a08
                             LAB_OVR_229__800a6590                           XREF[3]:     OVR_229::800a654c(j), 
                                                                                          OVR_229::800a6560(j), 
                                                                                          OVR_229::800a6574(j)  
     9::800a6590 10 00 2f 8c     lw         t7,0x10(at)
     9::800a6594 80 00 23 8c     lw         v1,0x80(at)
     9::800a6598 a6 01 28 84     lh         t0,0x1a6(at)
     9::800a659c a2 01 29 84     lh         t1,0x1a2(at)
     9::800a65a0 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a65a4 01 00 63 34     ori        v1,v1,0x1
     9::800a65a8 00 00 e3 ad     sw         v1,0x0(t7)
     9::800a65ac 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a65b0 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a65b4 21 68 60 02     move       t5,s3
     9::800a65b8 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a65bc 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a65c0 21 68 80 02     move       t5,s4
     9::800a65c4 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a65c8 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a65cc 21 68 a0 02     move       t5,s5
     9::800a65d0 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a65d4 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a65d8 21 68 c0 02     move       t5,s6
     9::800a65dc 8d 99 02 0c     jal        FUN_OVR_229__800a6634                            undefined FUN_OVR_229__800a6634()
     9::800a65e0 30 00 f0 25     _addiu     s0,t7,0x30
     9::800a65e4 58 00 3f 8c     lw         ra,0x58(at)
     9::800a65e8 3c 00 ef 25     addiu      t7,t7,0x3c
     9::800a65ec 08 00 e0 03     jr         ra
     9::800a65f0 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a65f4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a65f4                           XREF[7]:     FUN_OVR_229__800a5d60:800a64a0(c
                                                                                          FUN_OVR_229__800a5d60:800a64b4(c
                                                                                          FUN_OVR_229__800a5d60:800a64c8(c
                                                                                          FUN_OVR_229__800a5d60:800a6544(c
                                                                                          FUN_OVR_229__800a5d60:800a6558(c
                                                                                          FUN_OVR_229__800a5d60:800a656c(c
                                                                                          FUN_OVR_229__800a5d60:800a6580(c
     9::800a65f4 23 18 6f 00     subu       v1,v1,t7
     9::800a65f8 02 00 61 04     bgez       v1,LAB_OVR_229__800a6604
     9::800a65fc 23 40 10 01     _subu      t0,t0,s0
     9::800a6600 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_229__800a6604                           XREF[1]:     OVR_229::800a65f8(j)  
     9::800a6604 00 ff 6b 24     addiu      t3,v1,-0x100
     9::800a6608 02 00 01 05     bgez       t0,LAB_OVR_229__800a6614
     9::800a660c 23 48 31 01     _subu      t1,t1,s1
     9::800a6610 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_229__800a6614                           XREF[1]:     OVR_229::800a6608(j)  
     9::800a6614 80 fe 0c 25     addiu      t4,t0,-0x180
     9::800a6618 02 00 21 05     bgez       t1,LAB_OVR_229__800a6624
     9::800a661c 00 00 00 00     _nop
     9::800a6620 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_229__800a6624                           XREF[1]:     OVR_229::800a6618(j)  
     9::800a6624 00 ff 2d 25     addiu      t5,t1,-0x100
     9::800a6628 24 58 6c 01     and        t3,t3,t4
     9::800a662c 08 00 e0 03     jr         ra
     9::800a6630 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a6634()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a6634                           XREF[7]:     FUN_OVR_229__800a5d60:800a64fc(c
                                                                                          FUN_OVR_229__800a5d60:800a6508(c
                                                                                          FUN_OVR_229__800a5d60:800a6514(c
                                                                                          FUN_OVR_229__800a5d60:800a65b8(c
                                                                                          FUN_OVR_229__800a5d60:800a65c4(c
                                                                                          FUN_OVR_229__800a5d60:800a65d0(c
                                                                                          FUN_OVR_229__800a5d60:800a65dc(c
     9::800a6634 13 00 a3 81     lb         v1,0x13(t5)
     9::800a6638 00 00 a8 8d     lw         t0,0x0(t5)
     9::800a663c 04 00 a9 8d     lw         t1,0x4(t5)
     9::800a6640 08 00 aa 8d     lw         t2,0x8(t5)
     9::800a6644 00 1e 03 00     sll        v1,v1,0x18
     9::800a6648 25 50 43 01     or         t2,t2,v1
     9::800a664c 00 00 08 ae     sw         t0,0x0(s0)
     9::800a6650 04 00 09 ae     sw         t1,0x4(s0)
     9::800a6654 08 00 e0 03     jr         ra
     9::800a6658 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_229__800a665c                           XREF[2]:     FUN_OVR_229__800a106c:800a10c4(*
                                                                                          OVR_229::800a8f28(*)  
     9::800a665c 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_229__800a6660                           XREF[1]:     OVR_229::800a6938(j)  
     9::800a6660 bd 00 80 10     beq        a0,zero,LAB_OVR_229__800a6958
     9::800a6664 00 00 00 00     _nop
     9::800a6668 1c 00 78 8c     lw         t8,0x1c(v1)
     9::800a666c 18 00 79 8c     lw         t9,0x18(v1)
     9::800a6670 c8 00 2a 8c     lw         t2,0xc8(at)
     9::800a6674 3c 00 08 97     lhu        t0,0x3c(t8)
     9::800a6678 68 00 39 ac     sw         t9,0x68(at)
     9::800a667c c2 48 08 00     srl        t1,t0,0x3
     9::800a6680 fc 01 29 31     andi       t1,t1,0x1fc
     9::800a6684 21 48 2a 01     addu       t1,t1,t2
     9::800a6688 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a668c 00 00 29 8d     lw         t1,0x0(t1)
     9::800a6690 1f 00 08 31     andi       t0,t0,0x1f
     9::800a6694 bc 00 28 ac     sw         t0,0xbc(at)
     9::800a6698 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_229__800a669c                           XREF[1]:     OVR_229::800a692c(j)  
     9::800a669c 30 00 23 8c     lw         v1,0x30(at)
     9::800a66a0 40 37 48 24     addiu      t0,v0,0x3740
     9::800a66a4 23 18 68 00     subu       v1,v1,t0
     9::800a66a8 60 ea 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a66ac bc 00 23 8c     _lw        v1,0xbc(at)
     9::800a66b0 c4 00 28 8c     lw         t0,0xc4(at)
     9::800a66b4 06 00 61 04     bgez       v1,LAB_OVR_229__800a66d0
     9::800a66b8 c0 00 29 8c     _lw        t1,0xc0(at)
     9::800a66bc 1f 00 03 24     li         v1,0x1f
     9::800a66c0 04 00 28 8d     lw         t0,0x4(t1)
     9::800a66c4 04 00 29 25     addiu      t1,t1,0x4
     9::800a66c8 c0 00 29 ac     sw         t1,0xc0(at)
     9::800a66cc c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_229__800a66d0                           XREF[1]:     OVR_229::800a66b4(j)  
     9::800a66d0 04 40 68 00     sllv       t0,t0,v1
     9::800a66d4 ff ff 63 24     addiu      v1,v1,-0x1
     9::800a66d8 91 00 01 05     bgez       t0,LAB_OVR_229__800a6920
     9::800a66dc bc 00 23 ac     _sw        v1,0xbc(at)
     9::800a66e0 b4 01 3e 24     addiu      s8,at,0x1b4
     9::800a66e4 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a66e8 00 00 14 8f     lw         s4,0x0(t8)
     9::800a66ec 04 00 16 8f     lw         s6,0x4(t8)
     9::800a66f0 ff ff 93 32     andi       s3,s4,0xffff
     9::800a66f4 00 99 13 00     sll        s3,s3,0x4
     9::800a66f8 21 98 77 02     addu       s3,s3,s7
     9::800a66fc 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a6704 02 a4 14 00     srl        s4,s4,0x10
     9::800a6708 00 a1 14 00     sll        s4,s4,0x4
     9::800a670c 21 a0 97 02     addu       s4,s4,s7
     9::800a6710 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a6718 ff ff d5 32     andi       s5,s6,0xffff
     9::800a671c 00 a9 15 00     sll        s5,s5,0x4
     9::800a6720 21 a8 b7 02     addu       s5,s5,s7
     9::800a6724 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a672c 02 b4 16 00     srl        s6,s6,0x10
     9::800a6730 00 b1 16 00     sll        s6,s6,0x4
     9::800a6734 30 00 28 4a     RTPT
     9::800a6738 21 b0 d7 02     addu       s6,s6,s7
     9::800a673c 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a6740 08 00 90 8e     lw         s0,0x8(s4)
     9::800a6744 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a6748 08 00 cf af     sw         t7,0x8(s8)
     9::800a674c 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a6750 30 00 d1 af     sw         s1,0x30(s8)
     9::800a6754 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a6758 00 f8 43 48     gte_stFLAG v1
     9::800a675c 10 00 d1 eb     gte_stSZ1  0x10(s8)
     9::800a6760 80 1b 03 00     sll        v1,v1,0xe
     9::800a6764 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a6768 75 00 60 14     bne        v1,zero,LAB_OVR_229__800a6940
     9::800a676c 08 00 14 8f     _lw        s4,0x8(t8)
     9::800a6770 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a6774 24 00 d2 eb     gte_stSZ2  0x24(s8)
     9::800a6778 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a677c 38 00 d3 eb     gte_stSZ3  0x38(s8)
     9::800a6780 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a6784 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a6788 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a678c 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a6790 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a6794 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a6798 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a67a0 ff ff 93 32     andi       s3,s4,0xffff
     9::800a67a4 00 99 13 00     sll        s3,s3,0x4
     9::800a67a8 21 98 77 02     addu       s3,s3,s7
     9::800a67ac 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a67b4 02 a4 14 00     srl        s4,s4,0x10
     9::800a67b8 00 a1 14 00     sll        s4,s4,0x4
     9::800a67bc 21 a0 97 02     addu       s4,s4,s7
     9::800a67c0 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a67c8 21 c8 20 00     move       t9,at
     9::800a67cc 00 00 00 00     nop
     9::800a67d0 30 00 28 4a     RTPT
     9::800a67d4 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a67d8 08 00 70 8e     lw         s0,0x8(s3)
     9::800a67dc 08 00 91 8e     lw         s1,0x8(s4)
     9::800a67e0 44 00 cf af     sw         t7,0x44(s8)
     9::800a67e4 58 00 d0 af     sw         s0,0x58(s8)
     9::800a67e8 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a67ec 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a67f0 00 f8 43 48     gte_stFLAG v1
     9::800a67f4 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     9::800a67f8 80 1b 03 00     sll        v1,v1,0xe
     9::800a67fc c2 1f 03 00     srl        v1,v1,0x1f
     9::800a6800 4f 00 60 14     bne        v1,zero,LAB_OVR_229__800a6940
     9::800a6804 0c 00 14 8f     _lw        s4,0xc(t8)
     9::800a6808 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     9::800a680c 60 00 d2 eb     gte_stSZ2  0x60(s8)
     9::800a6810 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a6814 74 00 d3 eb     gte_stSZ3  0x74(s8)
     9::800a6818 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a681c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a6820 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a6824 10 00 15 97     lhu        s5,0x10(t8)
     9::800a6828 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a682c 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a6830 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a6834 ff ff 93 32     andi       s3,s4,0xffff
     9::800a6838 00 99 13 00     sll        s3,s3,0x4
     9::800a683c 21 98 77 02     addu       s3,s3,s7
     9::800a6840 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a6848 02 a4 14 00     srl        s4,s4,0x10
     9::800a684c 00 a1 14 00     sll        s4,s4,0x4
     9::800a6850 21 a0 97 02     addu       s4,s4,s7
     9::800a6854 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a685c 14 00 09 8f     lw         t1,0x14(t8)
     9::800a6860 00 a9 15 00     sll        s5,s5,0x4
     9::800a6864 21 a8 b7 02     addu       s5,s5,s7
     9::800a6868 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a6870 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a6874 08 00 08 24     li         t0,0x8
     9::800a6878 30 00 28 4a     RTPT
     9::800a687c 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a6880 08 00 90 8e     lw         s0,0x8(s4)
     9::800a6884 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a6888 80 00 cf af     sw         t7,0x80(s8)
     9::800a688c 94 00 d0 af     sw         s0,0x94(s8)
     9::800a6890 a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a6894 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a6898 00 f8 43 48     gte_stFLAG v1
     9::800a689c 88 00 d1 eb     gte_stSZ1  0x88(s8)
     9::800a68a0 80 1b 03 00     sll        v1,v1,0xe
     9::800a68a4 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a68a8 25 00 60 14     bne        v1,zero,LAB_OVR_229__800a6940
     9::800a68ac 98 00 cd eb     _gte_stS   0x98(s8)
     9::800a68b0 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     9::800a68b4 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a68b8 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     9::800a68bc 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a68c0 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a68c4 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a68c8 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a68cc a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a68d0 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a68d4 50 00 03 3c     lui        v1,0x50
     9::800a68d8 78 64 63 34     ori        v1,v1,0x6478
     9::800a68dc 61 9b 02 0c     jal        FUN_OVR_229__800a6d84                            undefined FUN_OVR_229__800a6d84()
     9::800a68e0 00 00 0a 24     _li        t2,0x0
     9::800a68e4 14 50 03 3c     lui        v1,0x5014
     9::800a68e8 8c 78 63 34     ori        v1,v1,0x788c
     9::800a68ec 0d 00 08 24     li         t0,0xd
     9::800a68f0 61 9b 02 0c     jal        FUN_OVR_229__800a6d84                            undefined FUN_OVR_229__800a6d84()
     9::800a68f4 04 00 0a 24     _li        t2,0x4
     9::800a68f8 78 64 03 3c     lui        v1,0x6478
     9::800a68fc a0 28 63 34     ori        v1,v1,0x28a0
     9::800a6900 12 00 08 24     li         t0,0x12
     9::800a6904 61 9b 02 0c     jal        FUN_OVR_229__800a6d84                            undefined FUN_OVR_229__800a6d84()
     9::800a6908 08 00 0a 24     _li        t2,0x8
     9::800a690c 8c 78 03 3c     lui        v1,0x788c
     9::800a6910 3c a0 63 34     ori        v1,v1,0xa03c
     9::800a6914 17 00 08 24     li         t0,0x17
     9::800a6918 61 9b 02 0c     jal        FUN_OVR_229__800a6d84                            undefined FUN_OVR_229__800a6d84()
     9::800a691c 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_229__800a6920                           XREF[2]:     OVR_229::800a66d8(j), 
                                                                                          OVR_229::800a6950(j)  
     9::800a6920 68 00 39 8c     lw         t9,0x68(at)
     9::800a6924 5c 00 18 27     addiu      t8,t8,0x5c
     9::800a6928 ff ff 39 27     addiu      t9,t9,-0x1
     9::800a692c 5b ff 20 1f     bgtz       t9,LAB_OVR_229__800a669c
     9::800a6930 68 00 39 ac     _sw        t9,0x68(at)
     9::800a6934 00 00 84 8c     lw         a0,0x0(a0)
     9::800a6938 49 ff 01 04     bgez       zero,LAB_OVR_229__800a6660
     9::800a693c 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_229__800a6940                           XREF[3]:     OVR_229::800a6768(j), 
                                                                                          OVR_229::800a6800(j), 
                                                                                          OVR_229::800a68a8(j)  
     9::800a6940 64 00 28 8c     lw         t0,0x64(at)
     9::800a6944 00 00 00 00     nop
     9::800a6948 00 00 18 ad     sw         t8,0x0(t0)
     9::800a694c 04 00 08 25     addiu      t0,t0,0x4
     9::800a6950 f3 ff 01 04     bgez       zero,LAB_OVR_229__800a6920
     9::800a6954 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_229__800a6958                           XREF[1]:     OVR_229::800a6660(j)  
     9::800a6958 64 00 28 8c     lw         t0,0x64(at)
     9::800a695c 02 ea 01 04     bgez       zero,LAB_OVR_229__800a1168
     9::800a6960 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_229__800a6964                           XREF[6]:     FUN_OVR_229__800a6c98:800a6d0c(j
                                                                                          FUN_OVR_229__800a6c98:800a6d14(j
                                                                                          FUN_OVR_229__800a6c98:800a6d48(j
                                                                                          OVR_229::800a6e58(j), 
                                                                                          OVR_229::800a6e60(j), 
                                                                                          OVR_229::800a6e8c(j)  
     9::800a6964 08 00 e0 03     jr         ra
     9::800a6968 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a696c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a696c                           XREF[4]:     FUN_OVR_229__800a69f8:800a6a44(j
                                                                                          FUN_OVR_229__800a69f8:800a6adc(c
                                                                                          FUN_OVR_229__800a69f8:800a6b04(c
                                                                                          FUN_OVR_229__800a69f8:800a6b70(c
     9::800a696c 00 00 d3 27     addiu      s3,s8,0x0
     9::800a6970 50 00 d4 27     addiu      s4,s8,0x50
     9::800a6974 64 00 d5 27     addiu      s5,s8,0x64
     9::800a6978 c7 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a697c 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a6980()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a6980                           XREF[6]:     FUN_OVR_229__800a69f8:800a6a4c(c
                                                                                          FUN_OVR_229__800a69f8:800a6aec(j
                                                                                          FUN_OVR_229__800a69f8:800a6afc(c
                                                                                          FUN_OVR_229__800a69f8:800a6b2c(c
                                                                                          FUN_OVR_229__800a69f8:800a6b4c(c
                                                                                          FUN_OVR_229__800a69f8:800a6b80(c
     9::800a6980 50 00 d3 27     addiu      s3,s8,0x50
     9::800a6984 14 00 d4 27     addiu      s4,s8,0x14
     9::800a6988 78 00 d5 27     addiu      s5,s8,0x78
     9::800a698c c2 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a6990 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a6994()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a6994                           XREF[6]:     FUN_OVR_229__800a69f8:800a6a74(c
                                                                                          FUN_OVR_229__800a69f8:800a6ad4(c
                                                                                          FUN_OVR_229__800a69f8:800a6b14(j
                                                                                          FUN_OVR_229__800a69f8:800a6b24(c
                                                                                          FUN_OVR_229__800a69f8:800a6b54(c
                                                                                          FUN_OVR_229__800a69f8:800a6b90(c
     9::800a6994 64 00 d3 27     addiu      s3,s8,0x64
     9::800a6998 78 00 d4 27     addiu      s4,s8,0x78
     9::800a699c 28 00 d5 27     addiu      s5,s8,0x28
     9::800a69a0 bd 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a69a4 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a69a8                           XREF[4]:     OVR_229::800a6ac4(j), 
                                                                                          OVR_229::800a6b3c(j), 
                                                                                          OVR_229::800a6b64(j), 
                                                                                          OVR_229::800a6ba8(j)  
     9::800a69a8 78 00 d3 27     addiu      s3,s8,0x78
     9::800a69ac 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a69b0 a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a69b4 b8 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a69b8 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a69bc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a69bc                           XREF[2]:     FUN_OVR_229__800a69f8:800a6a6c(c
                                                                                          FUN_OVR_229__800a69f8:800a6b44(c
     9::800a69bc 64 00 d3 27     addiu      s3,s8,0x64
     9::800a69c0 00 00 d4 27     addiu      s4,s8,0x0
     9::800a69c4 78 00 d5 27     addiu      s5,s8,0x78
     9::800a69c8 b3 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a69cc 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a69d0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a69d0                           XREF[2]:     FUN_OVR_229__800a69f8:800a6a84(j
                                                                                          FUN_OVR_229__800a69f8:800a6af4(c
     9::800a69d0 14 00 d3 27     addiu      s3,s8,0x14
     9::800a69d4 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a69d8 78 00 d5 27     addiu      s5,s8,0x78
     9::800a69dc ae 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a69e0 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a69e4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a69e4                           XREF[2]:     FUN_OVR_229__800a69f8:800a6a54(c
                                                                                          FUN_OVR_229__800a69f8:800a6b1c(c
     9::800a69e4 28 00 d3 27     addiu      s3,s8,0x28
     9::800a69e8 00 00 d4 27     addiu      s4,s8,0x0
     9::800a69ec 78 00 d5 27     addiu      s5,s8,0x78
     9::800a69f0 a9 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a69f4 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a69f8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a69f8                           XREF[2]:     OVR_229::800a6a64(j), 
                                                                                          OVR_229::800a6acc(c)  
     9::800a69f8 28 00 d3 27     addiu      s3,s8,0x28
     9::800a69fc 78 00 d4 27     addiu      s4,s8,0x78
     9::800a6a00 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a6a04 a4 00 01 04     bgez       zero,FUN_OVR_229__800a6c98
     9::800a6a08 8c 00 d6 27     _addiu     s6,s8,0x8c
                             LAB_OVR_229__800a6a0c                           XREF[2]:     FUN_OVR_229__800a106c:800a10a8(*
                                                                                          OVR_229::800a9200(*)  
     9::800a6a0c 50 00 d3 27     addiu      s3,s8,0x50
     9::800a6a10 14 00 d4 27     addiu      s4,s8,0x14
     9::800a6a14 78 00 d5 27     addiu      s5,s8,0x78
     9::800a6a18 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a6a1c 26 9b 02 0c     jal        FUN_OVR_229__800a6c98                            undefined FUN_OVR_229__800a6c98()
     9::800a6a20 0c 00 0a 24     _li        t2,0xc
     9::800a6a24 64 00 d3 27     addiu      s3,s8,0x64
     9::800a6a28 78 00 d4 27     addiu      s4,s8,0x78
     9::800a6a2c 28 00 d5 27     addiu      s5,s8,0x28
     9::800a6a30 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a6a34 26 9b 02 0c     jal        FUN_OVR_229__800a6c98                            undefined FUN_OVR_229__800a6c98()
     9::800a6a38 0c 00 0a 24     _li        t2,0xc
     9::800a6a3c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6a40 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6a44 c9 ff 01 04     bgez       zero,FUN_OVR_229__800a696c
     9::800a6a48 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_229__800a6a4c                           XREF[2]:     FUN_OVR_229__800a106c:800a10a8(*
                                                                                          OVR_229::800a9204(*)  
     9::800a6a4c 60 9a 02 0c     jal        FUN_OVR_229__800a6980                            undefined FUN_OVR_229__800a6980()
     9::800a6a50 0c 00 0a 24     _li        t2,0xc
     9::800a6a54 79 9a 02 0c     jal        FUN_OVR_229__800a69e4                            undefined FUN_OVR_229__800a69e4()
     9::800a6a58 0c 00 0a 24     _li        t2,0xc
     9::800a6a5c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6a60 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6a64 e4 ff 01 04     bgez       zero,FUN_OVR_229__800a69f8
     9::800a6a68 0c 00 0a 24     _li        t2,0xc
     9::800a6a6c 6f 9a 02 0c     jal        FUN_OVR_229__800a69bc                            undefined FUN_OVR_229__800a69bc()
     9::800a6a70 0c 00 0a 24     _li        t2,0xc
     9::800a6a74 65 9a 02 0c     jal        FUN_OVR_229__800a6994                            undefined FUN_OVR_229__800a6994()
     9::800a6a78 0c 00 0a 24     _li        t2,0xc
     9::800a6a7c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6a80 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6a84 d2 ff 01 04     bgez       zero,FUN_OVR_229__800a69d0
     9::800a6a88 0c 00 0a 24     _li        t2,0xc
     9::800a6a8c 00 00 d3 27     addiu      s3,s8,0x0
     9::800a6a90 14 00 d4 27     addiu      s4,s8,0x14
     9::800a6a94 78 00 d5 27     addiu      s5,s8,0x78
     9::800a6a98 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a6a9c 26 9b 02 0c     jal        FUN_OVR_229__800a6c98                            undefined FUN_OVR_229__800a6c98()
     9::800a6aa0 0c 00 0a 24     _li        t2,0xc
     9::800a6aa4 00 00 d3 27     addiu      s3,s8,0x0
     9::800a6aa8 78 00 d4 27     addiu      s4,s8,0x78
     9::800a6aac 28 00 d5 27     addiu      s5,s8,0x28
     9::800a6ab0 a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a6ab4 26 9b 02 0c     jal        FUN_OVR_229__800a6c98                            undefined FUN_OVR_229__800a6c98()
     9::800a6ab8 0c 00 0a 24     _li        t2,0xc
     9::800a6abc 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6ac0 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6ac4 b8 ff 01 04     bgez       zero,LAB_OVR_229__800a69a8
     9::800a6ac8 0c 00 0a 24     _li        t2,0xc
     9::800a6acc 7e 9a 02 0c     jal        FUN_OVR_229__800a69f8                            undefined FUN_OVR_229__800a69f8()
     9::800a6ad0 0c 00 0a 24     _li        t2,0xc
     9::800a6ad4 65 9a 02 0c     jal        FUN_OVR_229__800a6994                            undefined FUN_OVR_229__800a6994()
     9::800a6ad8 04 00 0a 24     _li        t2,0x4
     9::800a6adc 5b 9a 02 0c     jal        FUN_OVR_229__800a696c                            undefined FUN_OVR_229__800a696c()
     9::800a6ae0 0c 00 0a 24     _li        t2,0xc
     9::800a6ae4 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6ae8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6aec a4 ff 01 04     bgez       zero,FUN_OVR_229__800a6980
     9::800a6af0 0c 00 0a 24     _li        t2,0xc
     9::800a6af4 74 9a 02 0c     jal        FUN_OVR_229__800a69d0                            undefined FUN_OVR_229__800a69d0()
     9::800a6af8 0c 00 0a 24     _li        t2,0xc
     9::800a6afc 60 9a 02 0c     jal        FUN_OVR_229__800a6980                            undefined FUN_OVR_229__800a6980()
     9::800a6b00 04 00 0a 24     _li        t2,0x4
     9::800a6b04 5b 9a 02 0c     jal        FUN_OVR_229__800a696c                            undefined FUN_OVR_229__800a696c()
     9::800a6b08 0c 00 0a 24     _li        t2,0xc
     9::800a6b0c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6b10 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6b14 9f ff 01 04     bgez       zero,FUN_OVR_229__800a6994
     9::800a6b18 0c 00 0a 24     _li        t2,0xc
     9::800a6b1c 79 9a 02 0c     jal        FUN_OVR_229__800a69e4                            undefined FUN_OVR_229__800a69e4()
     9::800a6b20 0c 00 0a 24     _li        t2,0xc
     9::800a6b24 65 9a 02 0c     jal        FUN_OVR_229__800a6994                            undefined FUN_OVR_229__800a6994()
     9::800a6b28 08 00 0a 24     _li        t2,0x8
     9::800a6b2c 60 9a 02 0c     jal        FUN_OVR_229__800a6980                            undefined FUN_OVR_229__800a6980()
     9::800a6b30 0c 00 0a 24     _li        t2,0xc
     9::800a6b34 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6b38 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6b3c 9a ff 01 04     bgez       zero,LAB_OVR_229__800a69a8
     9::800a6b40 0c 00 0a 24     _li        t2,0xc
     9::800a6b44 6f 9a 02 0c     jal        FUN_OVR_229__800a69bc                            undefined FUN_OVR_229__800a69bc()
     9::800a6b48 0c 00 0a 24     _li        t2,0xc
     9::800a6b4c 60 9a 02 0c     jal        FUN_OVR_229__800a6980                            undefined FUN_OVR_229__800a6980()
     9::800a6b50 08 00 0a 24     _li        t2,0x8
     9::800a6b54 65 9a 02 0c     jal        FUN_OVR_229__800a6994                            undefined FUN_OVR_229__800a6994()
     9::800a6b58 0c 00 0a 24     _li        t2,0xc
     9::800a6b5c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6b60 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6b64 90 ff 01 04     bgez       zero,LAB_OVR_229__800a69a8
     9::800a6b68 0c 00 0a 24     _li        t2,0xc
     9::800a6b6c b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a6b70 5b 9a 02 0c     jal        FUN_OVR_229__800a696c                            undefined FUN_OVR_229__800a696c()
     9::800a6b74 0c 00 0a 24     _li        t2,0xc
     9::800a6b78 0c 00 03 24     li         v1,0xc
     9::800a6b7c b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a6b80 60 9a 02 0c     jal        FUN_OVR_229__800a6980                            undefined FUN_OVR_229__800a6980()
     9::800a6b84 0c 00 0a 24     _li        t2,0xc
     9::800a6b88 30 00 03 24     li         v1,0x30
     9::800a6b8c b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a6b90 65 9a 02 0c     jal        FUN_OVR_229__800a6994                            undefined FUN_OVR_229__800a6994()
     9::800a6b94 0c 00 0a 24     _li        t2,0xc
     9::800a6b98 3c 00 03 24     li         v1,0x3c
     9::800a6b9c b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a6ba0 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a6ba4 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a6ba8 7f ff 01 04     bgez       zero,LAB_OVR_229__800a69a8
     9::800a6bac 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a6bb0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a6bb0                           XREF[5]:     FUN_OVR_229__800a6d84:800a7004(c
                                                                                          FUN_OVR_229__800a6d84:800a7018(c
                                                                                          FUN_OVR_229__800a6d84:800a702c(c
                                                                                          FUN_OVR_229__800a6d84:800a7040(c
                                                                                          FUN_OVR_229__800a6d84:800a7054(c
     9::800a6bb0 00 00 ab 85     lh         t3,0x0(t5)
     9::800a6bb4 00 00 cc 85     lh         t4,0x0(t6)
     9::800a6bb8 00 00 eb a5     sh         t3,0x0(t7)
     9::800a6bbc 21 18 6c 01     addu       v1,t3,t4
     9::800a6bc0 43 18 03 00     sra        v1,v1,0x1
     9::800a6bc4 00 00 03 a6     sh         v1,0x0(s0)
     9::800a6bc8 02 00 ab 85     lh         t3,0x2(t5)
     9::800a6bcc 02 00 cc 85     lh         t4,0x2(t6)
     9::800a6bd0 02 00 eb a5     sh         t3,0x2(t7)
     9::800a6bd4 21 18 6c 01     addu       v1,t3,t4
     9::800a6bd8 43 18 03 00     sra        v1,v1,0x1
     9::800a6bdc 02 00 03 a6     sh         v1,0x2(s0)
     9::800a6be0 04 00 ab 85     lh         t3,0x4(t5)
     9::800a6be4 04 00 cc 85     lh         t4,0x4(t6)
     9::800a6be8 04 00 eb a5     sh         t3,0x4(t7)
     9::800a6bec 21 18 6c 01     addu       v1,t3,t4
     9::800a6bf0 43 18 03 00     sra        v1,v1,0x1
     9::800a6bf4 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a6bf8 00 08 83 48     gte_ldVZ0  v1
     9::800a6bfc 04 00 03 a6     sh         v1,0x4(s0)
     9::800a6c00 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a6c04 01 00 18 4a     RTPS
     9::800a6c08 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a6c0c 08 00 eb a1     sb         t3,0x8(t7)
     9::800a6c10 21 18 6c 01     addu       v1,t3,t4
     9::800a6c14 43 18 03 00     sra        v1,v1,0x1
     9::800a6c18 08 00 03 a2     sb         v1,0x8(s0)
     9::800a6c1c 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a6c20 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a6c24 09 00 eb a1     sb         t3,0x9(t7)
     9::800a6c28 21 18 6c 01     addu       v1,t3,t4
     9::800a6c2c 43 18 03 00     sra        v1,v1,0x1
     9::800a6c30 09 00 03 a2     sb         v1,0x9(s0)
     9::800a6c34 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a6c38 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a6c3c 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a6c40 21 18 6c 01     addu       v1,t3,t4
     9::800a6c44 43 18 03 00     sra        v1,v1,0x1
     9::800a6c48 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a6c4c 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a6c50 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a6c54 06 00 eb a1     sb         t3,0x6(t7)
     9::800a6c58 21 18 6c 01     addu       v1,t3,t4
     9::800a6c5c 43 18 03 00     sra        v1,v1,0x1
     9::800a6c60 06 00 03 a2     sb         v1,0x6(s0)
     9::800a6c64 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a6c68 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a6c6c 07 00 eb a1     sb         t3,0x7(t7)
     9::800a6c70 21 18 6c 01     addu       v1,t3,t4
     9::800a6c74 43 18 03 00     sra        v1,v1,0x1
     9::800a6c78 07 00 03 a2     sb         v1,0x7(s0)
     9::800a6c7c 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a6c80 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a6c84 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a6c88 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a6c8c 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a6c90 08 00 e0 03     jr         ra
     9::800a6c94 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a6c98()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a6c98                           XREF[12]:    FUN_OVR_229__800a696c:800a6978(j
                                                                                          FUN_OVR_229__800a6980:800a698c(j
                                                                                          FUN_OVR_229__800a6994:800a69a0(j
                                                                                          FUN_OVR_229__800a69f8:800a69b4(j
                                                                                          FUN_OVR_229__800a69bc:800a69c8(j
                                                                                          FUN_OVR_229__800a69d0:800a69dc(j
                                                                                          FUN_OVR_229__800a69e4:800a69f0(j
                                                                                          FUN_OVR_229__800a69f8:800a6a04(j
                                                                                          FUN_OVR_229__800a69f8:800a6a1c(c
                                                                                          FUN_OVR_229__800a69f8:800a6a34(c
                                                                                          FUN_OVR_229__800a69f8:800a6a9c(c
                                                                                          FUN_OVR_229__800a69f8:800a6ab4(c
     9::800a6c98 70 00 2a ac     sw         t2,0x70(at)
     9::800a6c9c 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a6ca0 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a6ca4 94 01 2a 8c     lw         t2,0x194(at)
     9::800a6ca8 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a6cac 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a6cb0 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a6cb4 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a6cb8 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a6cbc 06 00 40 4b     NCLIP
     9::800a6cc0 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a6cc4 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a6cc8 23 78 68 01     subu       t7,t3,t0
     9::800a6ccc 23 80 88 01     subu       s0,t4,t0
     9::800a6cd0 23 88 a8 01     subu       s1,t5,t0
     9::800a6cd4 23 90 c8 01     subu       s2,t6,t0
     9::800a6cd8 00 c0 08 48     gte_stMAC0 t0
     9::800a6cdc 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a6ce0 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a6cec
     9::800a6ce4 22 40 08 00     _sub       t0,zero,t0
     9::800a6ce8 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a6cec                           XREF[1]:     OVR_229::800a6ce0(j)  
     9::800a6cec 06 00 40 4b     NCLIP
     9::800a6cf0 24 18 6c 01     and        v1,t3,t4
     9::800a6cf4 24 18 6d 00     and        v1,v1,t5
     9::800a6cf8 24 18 6e 00     and        v1,v1,t6
     9::800a6cfc 25 78 f0 01     or         t7,t7,s0
     9::800a6d00 25 78 f1 01     or         t7,t7,s1
     9::800a6d04 27 78 f2 01     nor        t7,t7,s2
     9::800a6d08 25 78 e3 01     or         t7,t7,v1
     9::800a6d0c 15 ff e0 05     bltz       t7,LAB_OVR_229__800a6964
     9::800a6d10 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a6d14 13 ff e0 05     bltz       t7,LAB_OVR_229__800a6964
     9::800a6d18 00 c0 03 48     _gte_stM   v1
     9::800a6d1c 25 40 09 01     or         t0,t0,t1
     9::800a6d20 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a6d2c
     9::800a6d24 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a6d28 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a6d2c                           XREF[1]:     OVR_229::800a6d20(j)  
     9::800a6d2c 80 40 08 00     sll        t0,t0,0x2
     9::800a6d30 25 18 69 00     or         v1,v1,t1
     9::800a6d34 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a6d38 c0 18 03 00     sll        v1,v1,0x3
     9::800a6d3c 70 00 2a 8c     lw         t2,0x70(at)
     9::800a6d40 25 18 68 00     or         v1,v1,t0
     9::800a6d44 24 18 6a 00     and        v1,v1,t2
     9::800a6d48 06 ff 60 10     beq        v1,zero,LAB_OVR_229__800a6964
     9::800a6d4c 70 00 23 ac     _sw        v1,0x70(at)
     9::800a6d50 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a6d54 24 03 28 24     addiu      t0,at,0x324
     9::800a6d58 d3 00 1e 11     beq        t0,s8,LAB_OVR_229__800a70a8
     9::800a6d5c 04 00 39 27     _addiu     t9,t9,0x4
     9::800a6d60 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a6d64 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a6d68 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a6d6c 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a6d70 c0 fe 71 25     addiu      s1,t3,-0x140
     9::800a6d74 c0 fe 92 25     addiu      s2,t4,-0x140
     9::800a6d78 c0 fe af 25     addiu      t7,t5,-0x140
     9::800a6d7c 91 00 01 04     bgez       zero,LAB_OVR_229__800a6fc4
     9::800a6d80 c0 fe d0 25     _addiu     s0,t6,-0x140
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a6d84()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a6d84                           XREF[4]:     OVR_229::800a68dc(c), 
                                                                                          OVR_229::800a68f0(c), 
                                                                                          OVR_229::800a6904(c), 
                                                                                          OVR_229::800a6918(c)  
     9::800a6d84 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a6d88 b4 00 ca af     sw         t2,0xb4(s8)
     9::800a6d8c 06 50 09 01     srlv       t2,t1,t0
     9::800a6d90 1f 00 4a 31     andi       t2,t2,0x1f
     9::800a6d94 80 50 0a 00     sll        t2,t2,0x2
     9::800a6d98 21 50 41 01     addu       t2,t2,at
     9::800a6d9c ec 00 4a 8d     lw         t2,0xec(t2)
     9::800a6da0 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a6da4 94 01 2a ac     sw         t2,0x194(at)
     9::800a6da8 02 9e 0a 00     srl        s3,t2,0x18
     9::800a6dac 1f 00 73 32     andi       s3,s3,0x1f
     9::800a6db0 06 98 63 02     srlv       s3,v1,s3
     9::800a6db4 ff 00 73 32     andi       s3,s3,0xff
     9::800a6db8 21 98 7e 02     addu       s3,s3,s8
     9::800a6dbc 02 a4 0a 00     srl        s4,t2,0x10
     9::800a6dc0 1f 00 94 32     andi       s4,s4,0x1f
     9::800a6dc4 06 a0 83 02     srlv       s4,v1,s4
     9::800a6dc8 ff 00 94 32     andi       s4,s4,0xff
     9::800a6dcc 21 a0 9e 02     addu       s4,s4,s8
     9::800a6dd0 02 aa 0a 00     srl        s5,t2,0x8
     9::800a6dd4 1f 00 b5 32     andi       s5,s5,0x1f
     9::800a6dd8 06 a8 a3 02     srlv       s5,v1,s5
     9::800a6ddc ff 00 b5 32     andi       s5,s5,0xff
     9::800a6de0 21 a8 be 02     addu       s5,s5,s8
     9::800a6de4 1f 00 56 31     andi       s6,t2,0x1f
     9::800a6de8 06 b0 c3 02     srlv       s6,v1,s6
     9::800a6dec ff 00 d6 32     andi       s6,s6,0xff
     9::800a6df0 21 b0 de 02     addu       s6,s6,s8
     9::800a6df4 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a6df8 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a6dfc 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a6e00 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a6e04 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a6e08 06 00 40 4b     NCLIP
     9::800a6e0c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a6e10 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a6e14 23 78 68 01     subu       t7,t3,t0
     9::800a6e18 23 80 88 01     subu       s0,t4,t0
     9::800a6e1c 23 88 a8 01     subu       s1,t5,t0
     9::800a6e20 23 90 c8 01     subu       s2,t6,t0
     9::800a6e24 00 c0 08 48     gte_stMAC0 t0
     9::800a6e28 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a6e2c 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a6e38
     9::800a6e30 22 40 08 00     _sub       t0,zero,t0
     9::800a6e34 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a6e38                           XREF[1]:     OVR_229::800a6e2c(j)  
     9::800a6e38 06 00 40 4b     NCLIP
     9::800a6e3c 24 18 6c 01     and        v1,t3,t4
     9::800a6e40 24 18 6d 00     and        v1,v1,t5
     9::800a6e44 24 18 6e 00     and        v1,v1,t6
     9::800a6e48 25 78 f0 01     or         t7,t7,s0
     9::800a6e4c 25 78 f1 01     or         t7,t7,s1
     9::800a6e50 27 78 f2 01     nor        t7,t7,s2
     9::800a6e54 25 78 e3 01     or         t7,t7,v1
     9::800a6e58 c2 fe e0 05     bltz       t7,LAB_OVR_229__800a6964
     9::800a6e5c 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a6e60 c0 fe e0 05     bltz       t7,LAB_OVR_229__800a6964
     9::800a6e64 00 c0 03 48     _gte_stM   v1
     9::800a6e68 25 40 09 01     or         t0,t0,t1
     9::800a6e6c 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a6e78
     9::800a6e70 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a6e74 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a6e78                           XREF[1]:     OVR_229::800a6e6c(j)  
     9::800a6e78 80 40 08 00     sll        t0,t0,0x2
     9::800a6e7c 25 18 69 00     or         v1,v1,t1
     9::800a6e80 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a6e84 c0 18 03 00     sll        v1,v1,0x3
     9::800a6e88 25 18 68 00     or         v1,v1,t0
     9::800a6e8c b5 fe 60 10     beq        v1,zero,LAB_OVR_229__800a6964
     9::800a6e90 70 00 23 ac     _sw        v1,0x70(at)
     9::800a6e94 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a6e98 04 00 39 27     addiu      t9,t9,0x4
     9::800a6e9c 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a6ea0 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a6ea4 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a6ea8 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a6eac b4 00 c3 8f     lw         v1,0xb4(s8)
     9::800a6eb0 23 50 6c 01     subu       t2,t3,t4
     9::800a6eb4 82 48 03 00     srl        t1,v1,0x2
     9::800a6eb8 21 48 38 01     addu       t1,t1,t8
     9::800a6ebc 18 00 29 81     lb         t1,0x18(t1)
     9::800a6ec0 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a6ecc
     9::800a6ec4 21 e0 60 01     _move      gp,t3
     9::800a6ec8 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a6ecc                           XREF[1]:     OVR_229::800a6ec0(j)  
     9::800a6ecc 23 50 8d 03     subu       t2,gp,t5
     9::800a6ed0 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a6edc
     9::800a6ed4 21 18 78 00     _addu      v1,v1,t8
     9::800a6ed8 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a6edc                           XREF[1]:     OVR_229::800a6ed0(j)  
     9::800a6edc 23 50 8e 03     subu       t2,gp,t6
     9::800a6ee0 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a6eec
     9::800a6ee4 1c 00 63 8c     _lw        v1,0x1c(v1)
     9::800a6ee8 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a6eec                           XREF[1]:     OVR_229::800a6ee0(j)  
     9::800a6eec 21 50 80 03     move       t2,gp
     9::800a6ef0 82 e1 1c 00     srl        gp,gp,0x6
     9::800a6ef4 21 e0 89 03     addu       gp,gp,t1
     9::800a6ef8 01 00 69 30     andi       t1,v1,0x1
     9::800a6efc 02 00 20 11     beq        t1,zero,LAB_OVR_229__800a6f08
     9::800a6f00 80 e0 1c 00     _sll       gp,gp,0x2
     9::800a6f04 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_229__800a6f08                           XREF[1]:     OVR_229::800a6efc(j)  
     9::800a6f08 02 00 81 07     bgez       gp,LAB_OVR_229__800a6f14
     9::800a6f0c 21 e0 85 03     _addu      gp,gp,a1
     9::800a6f10 21 e0 a0 00     move       gp,a1
                             LAB_OVR_229__800a6f14                           XREF[1]:     OVR_229::800a6f08(j)  
     9::800a6f14 24 00 69 8c     lw         t1,0x24(v1)
     9::800a6f18 c0 f9 48 25     addiu      t0,t2,-0x640
     9::800a6f1c 84 00 29 ac     sw         t1,0x84(at)
     9::800a6f20 0a 00 01 05     bgez       t0,LAB_OVR_229__800a6f4c
     9::800a6f24 00 fb 48 25     _addiu     t0,t2,-0x500
     9::800a6f28 0c 00 63 24     addiu      v1,v1,0xc
     9::800a6f2c 07 00 01 05     bgez       t0,LAB_OVR_229__800a6f4c
     9::800a6f30 80 fd 48 25     _addiu     t0,t2,-0x280
     9::800a6f34 0c 00 63 24     addiu      v1,v1,0xc
     9::800a6f38 04 00 01 05     bgez       t0,LAB_OVR_229__800a6f4c
     9::800a6f3c 00 00 00 00     _nop
     9::800a6f40 02 00 20 05     bltz       t1,LAB_OVR_229__800a6f4c
     9::800a6f44 00 00 00 00     _nop
     9::800a6f48 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_229__800a6f4c                           XREF[4]:     OVR_229::800a6f20(j), 
                                                                                          OVR_229::800a6f2c(j), 
                                                                                          OVR_229::800a6f38(j), 
                                                                                          OVR_229::800a6f40(j)  
     9::800a6f4c 94 01 2a 8c     lw         t2,0x194(at)
     9::800a6f50 00 00 68 8c     lw         t0,0x0(v1)
     9::800a6f54 04 00 69 8c     lw         t1,0x4(v1)
     9::800a6f58 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a6f5c ac 01 28 ac     sw         t0,0x1ac(at)
     9::800a6f60 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a6f64 00 52 0a 00     sll        t2,t2,0x8
     9::800a6f68 0a 00 40 05     bltz       t2,LAB_OVR_229__800a6f94
     9::800a6f6c b0 01 29 ac     _sw        t1,0x1b0(at)
     9::800a6f70 06 00 68 a6     sh         t0,0x6(s3)
     9::800a6f74 08 00 68 8c     lw         t0,0x8(v1)
     9::800a6f78 06 00 89 a6     sh         t1,0x6(s4)
     9::800a6f7c 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a6f80 00 54 0a 00     sll        t2,t2,0x10
     9::800a6f84 0b 00 40 05     bltz       t2,LAB_OVR_229__800a6fb4
     9::800a6f88 02 4c 08 00     _srl       t1,t0,0x10
     9::800a6f8c 09 00 01 04     bgez       zero,LAB_OVR_229__800a6fb4
     9::800a6f90 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_229__800a6f94                           XREF[1]:     OVR_229::800a6f68(j)  
     9::800a6f94 06 00 69 a6     sh         t1,0x6(s3)
     9::800a6f98 08 00 69 8c     lw         t1,0x8(v1)
     9::800a6f9c 00 54 0a 00     sll        t2,t2,0x10
     9::800a6fa0 06 00 88 a6     sh         t0,0x6(s4)
     9::800a6fa4 02 44 09 00     srl        t0,t1,0x10
     9::800a6fa8 02 00 40 05     bltz       t2,LAB_OVR_229__800a6fb4
     9::800a6fac 06 00 a8 a6     _sh        t0,0x6(s5)
     9::800a6fb0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a6fb4                           XREF[3]:     OVR_229::800a6f84(j), 
                                                                                          OVR_229::800a6f8c(j), 
                                                                                          OVR_229::800a6fa8(j)  
     9::800a6fb4 80 fd 71 25     addiu      s1,t3,-0x280
     9::800a6fb8 80 fd 92 25     addiu      s2,t4,-0x280
     9::800a6fbc 80 fd af 25     addiu      t7,t5,-0x280
     9::800a6fc0 80 fd d0 25     addiu      s0,t6,-0x280
                             LAB_OVR_229__800a6fc4                           XREF[1]:     FUN_OVR_229__800a6c98:800a6d7c(j
     9::800a6fc4 42 8f 11 00     srl        s1,s1,0x1d
     9::800a6fc8 04 00 31 32     andi       s1,s1,0x4
     9::800a6fcc 02 97 12 00     srl        s2,s2,0x1c
     9::800a6fd0 08 00 52 32     andi       s2,s2,0x8
     9::800a6fd4 25 88 32 02     or         s1,s1,s2
     9::800a6fd8 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a6fdc 10 00 ef 31     andi       t7,t7,0x10
     9::800a6fe0 25 88 2f 02     or         s1,s1,t7
     9::800a6fe4 82 86 10 00     srl        s0,s0,0x1a
     9::800a6fe8 20 00 10 32     andi       s0,s0,0x20
     9::800a6fec 25 88 30 02     or         s1,s1,s0
     9::800a6ff0 26 00 20 12     beq        s1,zero,LAB_OVR_229__800a708c
     9::800a6ff4 21 68 60 02     _move      t5,s3
     9::800a6ff8 21 70 80 02     move       t6,s4
     9::800a6ffc b8 00 de 27     addiu      s8,s8,0xb8
     9::800a7000 00 00 cf 27     addiu      t7,s8,0x0
     9::800a7004 ec 9a 02 0c     jal        FUN_OVR_229__800a6bb0                            undefined FUN_OVR_229__800a6bb0()
     9::800a7008 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a700c 21 68 80 02     move       t5,s4
     9::800a7010 21 70 c0 02     move       t6,s6
     9::800a7014 14 00 cf 27     addiu      t7,s8,0x14
     9::800a7018 ec 9a 02 0c     jal        FUN_OVR_229__800a6bb0                            undefined FUN_OVR_229__800a6bb0()
     9::800a701c 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a7020 21 68 a0 02     move       t5,s5
     9::800a7024 21 70 60 02     move       t6,s3
     9::800a7028 28 00 cf 27     addiu      t7,s8,0x28
     9::800a702c ec 9a 02 0c     jal        FUN_OVR_229__800a6bb0                            undefined FUN_OVR_229__800a6bb0()
     9::800a7030 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a7034 21 68 c0 02     move       t5,s6
     9::800a7038 21 70 a0 02     move       t6,s5
     9::800a703c 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a7040 ec 9a 02 0c     jal        FUN_OVR_229__800a6bb0                            undefined FUN_OVR_229__800a6bb0()
     9::800a7044 a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a7048 21 68 80 02     move       t5,s4
     9::800a704c 21 70 a0 02     move       t6,s5
     9::800a7050 14 00 cf 27     addiu      t7,s8,0x14
     9::800a7054 ec 9a 02 0c     jal        FUN_OVR_229__800a6bb0                            undefined FUN_OVR_229__800a6bb0()
     9::800a7058 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a705c 21 18 21 02     addu       v1,s1,at
     9::800a7060 48 01 63 8c     lw         v1,0x148(v1)
     9::800a7064 0a 80 08 3c     lui        t0,0x800a
     9::800a7068 7c 70 08 25     addiu      t0,t0,0x707c
     9::800a706c 9c 00 23 ac     sw         v1,0x9c(at)
     9::800a7070 3c 00 28 af     sw         t0=>LAB_OVR_229__800a707c,0x3c(t9)
     9::800a7074 08 00 60 00     jr         v1
     9::800a7078 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a707c                           XREF[1]:     FUN_OVR_229__800a6d84:800a7070(*
     9::800a707c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7080 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a7084 08 00 e0 03     jr         ra
     9::800a7088 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a708c                           XREF[1]:     OVR_229::800a6ff0(j)  
     9::800a708c 70 00 23 8c     lw         v1,0x70(at)
     9::800a7090 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a7094 21 18 61 00     addu       v1,v1,at
     9::800a7098 84 01 63 8c     lw         v1,0x184(v1)
     9::800a709c 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a70a0 08 00 60 00     jr         v1
     9::800a70a4 00 00 00 00     _nop
                             LAB_OVR_229__800a70a8                           XREF[1]:     OVR_229::800a6d58(j)  
     9::800a70a8 84 00 23 8c     lw         v1,0x84(at)
     9::800a70ac 24 03 2a 24     addiu      t2,at,0x324
     9::800a70b0 26 00 60 1c     bgtz       v1,LAB_OVR_229__800a714c
     9::800a70b4 20 03 28 8c     _lw        t0,0x320(at)
     9::800a70b8 d8 03 29 8c     lw         t1,0x3d8(at)
     9::800a70bc 16 00 5e 15     bne        t2,s8,LAB_OVR_229__800a7118
     9::800a70c0 9c 00 23 8c     _lw        v1,0x9c(at)
     9::800a70c4 0a 80 0a 3c     lui        t2,0x800a
     9::800a70c8 6c 6b 4a 25     addiu      t2,t2,0x6b6c
     9::800a70cc 1f 00 6a 14     bne        v1,t2,LAB_OVR_229__800a714c
     9::800a70d0 94 01 23 8c     _lw        v1,0x194(at)
     9::800a70d4 40 40 08 00     sll        t0,t0,0x1
     9::800a70d8 00 1a 03 00     sll        v1,v1,0x8
     9::800a70dc 02 00 61 04     bgez       v1,LAB_OVR_229__800a70e8
     9::800a70e0 84 00 2a 8c     _lw        t2,0x84(at)
     9::800a70e4 c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_229__800a70e8                           XREF[1]:     OVR_229::800a70dc(j)  
     9::800a70e8 21 40 09 01     addu       t0,t0,t1
     9::800a70ec 21 50 48 01     addu       t2,t2,t0
     9::800a70f0 00 00 48 8d     lw         t0,0x0(t2)
     9::800a70f4 04 00 49 8d     lw         t1,0x4(t2)
     9::800a70f8 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a70fc 06 00 68 a6     sh         t0,0x6(s3)
     9::800a7100 08 00 48 85     lh         t0,0x8(t2)
     9::800a7104 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a7108 06 00 89 a6     sh         t1,0x6(s4)
     9::800a710c 0a 00 49 85     lh         t1,0xa(t2)
     9::800a7110 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a7114 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a7118                           XREF[2]:     OVR_229::800a70bc(j), 
                                                                                          OVR_229::800a7158(j)  
     9::800a7118 70 00 23 8c     lw         v1,0x70(at)
     9::800a711c 00 00 00 00     nop
     9::800a7120 21 18 61 00     addu       v1,v1,at
     9::800a7124 84 01 63 8c     lw         v1,0x184(v1)
     9::800a7128 00 00 00 00     nop
     9::800a712c 09 f8 60 00     jalr       v1
     9::800a7130 fc ff 39 27     _addiu     t9,t9,-0x4
     9::800a7134 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a7138 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a713c b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a7140 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a7144 08 00 e0 03     jr         ra
     9::800a7148 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_229__800a714c                           XREF[2]:     OVR_229::800a70b0(j), 
                                                                                          OVR_229::800a70cc(j)  
     9::800a714c ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a7150 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a7154 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a7158 ef ff 01 04     bgez       zero,LAB_OVR_229__800a7118
     9::800a715c a4 01 29 ac     _sw        t1,0x1a4(at)
     9::800a7160 21 98 80 02     move       s3,s4
     9::800a7164 21 a0 c0 02     move       s4,s6
                             LAB_OVR_229__800a7168                           XREF[1]:     OVR_229::800a923c(*)  
     9::800a7168 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a716c 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a7170 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a7174 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a7178 08 00 90 8e     lw         s0,0x8(s4)
     9::800a717c 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a7180 06 00 73 86     lh         s3,0x6(s3)
     9::800a7184 06 00 94 86     lh         s4,0x6(s4)
     9::800a7188 06 00 b5 86     lh         s5,0x6(s5)
     9::800a718c a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a7190 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a7194 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a7198 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a719c a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a71a0 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a71a4 60 00 03 3c     lui        v1,0x60
     9::800a71a8 24 48 83 02     and        t1,s4,v1
     9::800a71ac 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a71b8
     9::800a71b0 00 36 03 3c     _lui       v1,0x3600
     9::800a71b4 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a71b8                           XREF[1]:     OVR_229::800a71ac(j)  
     9::800a71b8 25 18 6f 00     or         v1,v1,t7
     9::800a71bc 04 00 43 ac     sw         v1,0x4(v0)
     9::800a71c0 08 00 4b ac     sw         t3,0x8(v0)
     9::800a71c4 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a71c8 10 00 50 ac     sw         s0,0x10(v0)
     9::800a71cc 14 00 4c ac     sw         t4,0x14(v0)
     9::800a71d0 18 00 54 ac     sw         s4,0x18(v0)
     9::800a71d4 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a71d8 20 00 4d ac     sw         t5,0x20(v0)
     9::800a71dc 24 00 55 ac     sw         s5,0x24(v0)
     9::800a71e0 28 00 09 24     li         t1,0x28
     9::800a71e4 29 00 01 04     bgez       zero,LAB_OVR_229__800a728c
     9::800a71e8 00 09 0a 3c     _lui       t2,0x900
     9::800a71ec 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a71f0 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a71f4 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a71f8 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a71fc 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a7200 08 00 90 8e     lw         s0,0x8(s4)
     9::800a7204 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a7208 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a720c 06 00 73 86     lh         s3,0x6(s3)
     9::800a7210 06 00 94 86     lh         s4,0x6(s4)
     9::800a7214 06 00 b5 86     lh         s5,0x6(s5)
     9::800a7218 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a721c a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a7220 06 00 d4 86     lh         s4,0x6(s6)
     9::800a7224 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a7228 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a722c a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a7230 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a7234 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a7238 60 00 03 3c     lui        v1,0x60
     9::800a723c 24 48 83 02     and        t1,s4,v1
     9::800a7240 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a724c
     9::800a7244 00 3e 03 3c     _lui       v1,0x3e00
     9::800a7248 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a724c                           XREF[1]:     OVR_229::800a7240(j)  
     9::800a724c 25 18 6f 00     or         v1,v1,t7
     9::800a7250 04 00 43 ac     sw         v1,0x4(v0)
     9::800a7254 08 00 4b ac     sw         t3,0x8(v0)
     9::800a7258 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a725c 10 00 50 ac     sw         s0,0x10(v0)
     9::800a7260 14 00 4c ac     sw         t4,0x14(v0)
     9::800a7264 18 00 54 ac     sw         s4,0x18(v0)
     9::800a7268 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a726c 20 00 4d ac     sw         t5,0x20(v0)
     9::800a7270 24 00 55 ac     sw         s5,0x24(v0)
     9::800a7274 28 00 52 ac     sw         s2,0x28(v0)
     9::800a7278 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a727c 02 1c 15 00     srl        v1,s5,0x10
     9::800a7280 30 00 43 ac     sw         v1,0x30(v0)
     9::800a7284 34 00 09 24     li         t1,0x34
     9::800a7288 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a728c                           XREF[1]:     OVR_229::800a71e4(j)  
     9::800a728c 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a7290 00 42 02 00     sll        t0,v0,0x8
     9::800a7294 02 42 08 00     srl        t0,t0,0x8
     9::800a7298 25 18 6a 00     or         v1,v1,t2
     9::800a729c 00 00 43 ac     sw         v1,0x0(v0)
     9::800a72a0 21 10 49 00     addu       v0,v0,t1
     9::800a72a4 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a72a8 08 00 e0 03     jr         ra
     9::800a72ac 01 00 bd 23     _addi      sp,sp,0x1
     9::800a72b0 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_229__800a72b4                           XREF[1]:     OVR_229::800a7604(j)  
     9::800a72b4 30 00 23 8c     lw         v1,0x30(at)
     9::800a72b8 40 37 48 24     addiu      t0,v0,0x3740
     9::800a72bc 23 18 68 00     subu       v1,v1,t0
     9::800a72c0 5a e7 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a72c4 b4 01 3e 24     _addiu     s8,at,0x1b4
     9::800a72c8 a7 e7 00 13     beq        t8,zero,LAB_OVR_229__800a1168
     9::800a72cc b4 00 c0 af     _sw        zero,0xb4(s8)
     9::800a72d0 00 00 14 8f     lw         s4,0x0(t8)
     9::800a72d4 04 00 16 8f     lw         s6,0x4(t8)
     9::800a72d8 ff ff 93 32     andi       s3,s4,0xffff
     9::800a72dc 00 99 13 00     sll        s3,s3,0x4
     9::800a72e0 21 98 77 02     addu       s3,s3,s7
     9::800a72e4 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a72ec 02 a4 14 00     srl        s4,s4,0x10
     9::800a72f0 00 a1 14 00     sll        s4,s4,0x4
     9::800a72f4 21 a0 97 02     addu       s4,s4,s7
     9::800a72f8 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a7300 ff ff d5 32     andi       s5,s6,0xffff
     9::800a7304 00 a9 15 00     sll        s5,s5,0x4
     9::800a7308 21 a8 b7 02     addu       s5,s5,s7
     9::800a730c 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a7314 02 b4 16 00     srl        s6,s6,0x10
     9::800a7318 00 b1 16 00     sll        s6,s6,0x4
     9::800a731c 30 00 28 4a     RTPT
     9::800a7320 21 b0 d7 02     addu       s6,s6,s7
     9::800a7324 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a7328 08 00 90 8e     lw         s0,0x8(s4)
     9::800a732c 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a7330 08 00 cf af     sw         t7,0x8(s8)
     9::800a7334 1c 00 d0 af     sw         s0,0x1c(s8)
     9::800a7338 30 00 d1 af     sw         s1,0x30(s8)
     9::800a733c 08 00 14 8f     lw         s4,0x8(t8)
     9::800a7340 0c 00 cc eb     gte_stSXY0 0xc(s8)
     9::800a7344 20 00 cd eb     gte_stSXY1 0x20(s8)
     9::800a7348 34 00 ce eb     gte_stSXY2 0x34(s8)
     9::800a734c 00 00 c0 eb     sVXY0      0x0(s8)
     9::800a7350 04 00 c1 eb     gte_stVZ0  0x4(s8)
     9::800a7354 14 00 c2 eb     gte_stVXY1 0x14(s8)
     9::800a7358 18 00 c3 eb     gte_stVZ1  0x18(s8)
     9::800a735c 28 00 c4 eb     gte_stVXY2 0x28(s8)
     9::800a7360 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     9::800a7364 5c 00 2a 8c     lw         t2,0x5c(at)
     9::800a7368 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a7374 10 00 c3 a7     sh         v1,0x10(s8)
     9::800a7378 24 00 c8 a7     sh         t0,0x24(s8)
     9::800a737c 38 00 c9 a7     sh         t1,0x38(s8)
     9::800a7380 23 58 6a 00     subu       t3,v1,t2
     9::800a7384 23 60 0a 01     subu       t4,t0,t2
     9::800a7388 23 68 2a 01     subu       t5,t1,t2
     9::800a738c c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a7390 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a7394 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a7398 12 00 cb a3     sb         t3,0x12(s8)
     9::800a739c 26 00 cc a3     sb         t4,0x26(s8)
     9::800a73a0 3a 00 cd a3     sb         t5,0x3a(s8)
     9::800a73a4 40 18 03 00     sll        v1,v1,0x1
     9::800a73a8 40 40 08 00     sll        t0,t0,0x1
     9::800a73ac 40 48 09 00     sll        t1,t1,0x1
     9::800a73b0 23 58 6a 00     subu       t3,v1,t2
     9::800a73b4 23 60 0a 01     subu       t4,t0,t2
     9::800a73b8 23 68 2a 01     subu       t5,t1,t2
     9::800a73bc c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a73c0 c2 67 0c 00     srl        t4,t4,0x1f
     9::800a73c4 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a73c8 13 00 cb a3     sb         t3,0x13(s8)
     9::800a73cc 27 00 cc a3     sb         t4,0x27(s8)
     9::800a73d0 3b 00 cd a3     sb         t5,0x3b(s8)
     9::800a73d4 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     9::800a73dc ff ff 93 32     andi       s3,s4,0xffff
     9::800a73e0 00 99 13 00     sll        s3,s3,0x4
     9::800a73e4 21 98 77 02     addu       s3,s3,s7
     9::800a73e8 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     9::800a73f0 02 a4 14 00     srl        s4,s4,0x10
     9::800a73f4 00 a1 14 00     sll        s4,s4,0x4
     9::800a73f8 21 a0 97 02     addu       s4,s4,s7
     9::800a73fc 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     9::800a7404 21 c8 20 00     move       t9,at
     9::800a7408 00 00 00 00     nop
     9::800a740c 30 00 28 4a     RTPT
     9::800a7410 08 00 cf 8e     lw         t7,0x8(s6)
     9::800a7414 08 00 70 8e     lw         s0,0x8(s3)
     9::800a7418 08 00 91 8e     lw         s1,0x8(s4)
     9::800a741c 44 00 cf af     sw         t7,0x44(s8)
     9::800a7420 58 00 d0 af     sw         s0,0x58(s8)
     9::800a7424 6c 00 d1 af     sw         s1,0x6c(s8)
     9::800a7428 0c 00 14 8f     lw         s4,0xc(t8)
     9::800a742c 48 00 cc eb     gte_stSXY0 0x48(s8)
     9::800a7430 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     9::800a7434 70 00 ce eb     gte_stSXY2 0x70(s8)
     9::800a7438 3c 00 c0 eb     sVXY0      0x3c(s8)
     9::800a743c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     9::800a7440 50 00 c2 eb     gte_stVXY1 0x50(s8)
     9::800a7444 10 00 15 97     lhu        s5,0x10(t8)
     9::800a7448 54 00 c3 eb     gte_stVZ1  0x54(s8)
     9::800a744c 64 00 c4 eb     gte_stVXY2 0x64(s8)
     9::800a7450 68 00 c5 eb     gte_stVZ2  0x68(s8)
     9::800a7454 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a7460 4c 00 c3 a7     sh         v1,0x4c(s8)
     9::800a7464 60 00 c8 a7     sh         t0,0x60(s8)
     9::800a7468 74 00 c9 a7     sh         t1,0x74(s8)
     9::800a746c 23 58 6a 00     subu       t3,v1,t2
     9::800a7470 23 60 0a 01     subu       t4,t0,t2
     9::800a7474 23 68 2a 01     subu       t5,t1,t2
     9::800a7478 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a747c c2 67 0c 00     srl        t4,t4,0x1f
     9::800a7480 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a7484 4e 00 cb a3     sb         t3,0x4e(s8)
     9::800a7488 62 00 cc a3     sb         t4,0x62(s8)
     9::800a748c 76 00 cd a3     sb         t5,0x76(s8)
     9::800a7490 40 18 03 00     sll        v1,v1,0x1
     9::800a7494 40 40 08 00     sll        t0,t0,0x1
     9::800a7498 40 48 09 00     sll        t1,t1,0x1
     9::800a749c 23 58 6a 00     subu       t3,v1,t2
     9::800a74a0 23 60 0a 01     subu       t4,t0,t2
     9::800a74a4 23 68 2a 01     subu       t5,t1,t2
     9::800a74a8 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a74ac c2 67 0c 00     srl        t4,t4,0x1f
     9::800a74b0 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a74b4 4f 00 cb a3     sb         t3,0x4f(s8)
     9::800a74b8 63 00 cc a3     sb         t4,0x63(s8)
     9::800a74bc 77 00 cd a3     sb         t5,0x77(s8)
     9::800a74c0 ff ff 93 32     andi       s3,s4,0xffff
     9::800a74c4 00 99 13 00     sll        s3,s3,0x4
     9::800a74c8 21 98 77 02     addu       s3,s3,s7
     9::800a74cc 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     9::800a74d4 02 a4 14 00     srl        s4,s4,0x10
     9::800a74d8 00 a1 14 00     sll        s4,s4,0x4
     9::800a74dc 21 a0 97 02     addu       s4,s4,s7
     9::800a74e0 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     9::800a74e8 14 00 09 8f     lw         t1,0x14(t8)
     9::800a74ec 00 a9 15 00     sll        s5,s5,0x4
     9::800a74f0 21 a8 b7 02     addu       s5,s5,s7
     9::800a74f4 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     9::800a74fc 7c 00 29 ac     sw         t1,0x7c(at)
     9::800a7500 00 00 00 00     nop
     9::800a7504 30 00 28 4a     RTPT
     9::800a7508 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a750c 08 00 90 8e     lw         s0,0x8(s4)
     9::800a7510 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a7514 80 00 cf af     sw         t7,0x80(s8)
     9::800a7518 94 00 d0 af     sw         s0,0x94(s8)
     9::800a751c a8 00 d1 af     sw         s1,0xa8(s8)
     9::800a7520 84 00 cc eb     gte_stSXY0 0x84(s8)
     9::800a7524 98 00 cd eb     gte_stSXY1 0x98(s8)
     9::800a7528 ac 00 ce eb     gte_stSXY2 0xac(s8)
     9::800a752c 78 00 c0 eb     sVXY0      0x78(s8)
     9::800a7530 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     9::800a7534 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     9::800a7538 90 00 c3 eb     gte_stVZ1  0x90(s8)
     9::800a753c a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     9::800a7540 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     9::800a7544 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     9::800a7550 88 00 c3 a7     sh         v1,0x88(s8)
     9::800a7554 9c 00 c8 a7     sh         t0,0x9c(s8)
     9::800a7558 b0 00 c9 a7     sh         t1,0xb0(s8)
     9::800a755c 23 58 6a 00     subu       t3,v1,t2
     9::800a7560 23 60 0a 01     subu       t4,t0,t2
     9::800a7564 23 68 2a 01     subu       t5,t1,t2
     9::800a7568 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a756c c2 67 0c 00     srl        t4,t4,0x1f
     9::800a7570 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a7574 8a 00 cb a3     sb         t3,0x8a(s8)
     9::800a7578 9e 00 cc a3     sb         t4,0x9e(s8)
     9::800a757c b2 00 cd a3     sb         t5,0xb2(s8)
     9::800a7580 40 18 03 00     sll        v1,v1,0x1
     9::800a7584 40 40 08 00     sll        t0,t0,0x1
     9::800a7588 40 48 09 00     sll        t1,t1,0x1
     9::800a758c 23 58 6a 00     subu       t3,v1,t2
     9::800a7590 23 60 0a 01     subu       t4,t0,t2
     9::800a7594 23 68 2a 01     subu       t5,t1,t2
     9::800a7598 c2 5f 0b 00     srl        t3,t3,0x1f
     9::800a759c c2 67 0c 00     srl        t4,t4,0x1f
     9::800a75a0 c2 6f 0d 00     srl        t5,t5,0x1f
     9::800a75a4 8b 00 cb a3     sb         t3,0x8b(s8)
     9::800a75a8 9f 00 cc a3     sb         t4,0x9f(s8)
     9::800a75ac b3 00 cd a3     sb         t5,0xb3(s8)
     9::800a75b0 50 00 03 3c     lui        v1,0x50
     9::800a75b4 78 64 63 34     ori        v1,v1,0x6478
     9::800a75b8 08 00 08 24     li         t0,0x8
     9::800a75bc a5 9e 02 0c     jal        FUN_OVR_229__800a7a94                            undefined FUN_OVR_229__800a7a94()
     9::800a75c0 00 00 0a 24     _li        t2,0x0
     9::800a75c4 14 50 03 3c     lui        v1,0x5014
     9::800a75c8 8c 78 63 34     ori        v1,v1,0x788c
     9::800a75cc 0d 00 08 24     li         t0,0xd
     9::800a75d0 a5 9e 02 0c     jal        FUN_OVR_229__800a7a94                            undefined FUN_OVR_229__800a7a94()
     9::800a75d4 04 00 0a 24     _li        t2,0x4
     9::800a75d8 78 64 03 3c     lui        v1,0x6478
     9::800a75dc a0 28 63 34     ori        v1,v1,0x28a0
     9::800a75e0 12 00 08 24     li         t0,0x12
     9::800a75e4 a5 9e 02 0c     jal        FUN_OVR_229__800a7a94                            undefined FUN_OVR_229__800a7a94()
     9::800a75e8 08 00 0a 24     _li        t2,0x8
     9::800a75ec 8c 78 03 3c     lui        v1,0x788c
     9::800a75f0 3c a0 63 34     ori        v1,v1,0xa03c
     9::800a75f4 17 00 08 24     li         t0,0x17
     9::800a75f8 a5 9e 02 0c     jal        FUN_OVR_229__800a7a94                            undefined FUN_OVR_229__800a7a94()
     9::800a75fc 0c 00 0a 24     _li        t2,0xc
     9::800a7600 04 00 98 8c     lw         t8,0x4(a0)
     9::800a7604 2b ff 01 04     bgez       zero,LAB_OVR_229__800a72b4
     9::800a7608 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_229__800a760c                           XREF[12]:    FUN_OVR_229__800a7964:800a7980(j
                                                                                          FUN_OVR_229__800a7964:800a7a1c(j
                                                                                          FUN_OVR_229__800a7964:800a7a24(j
                                                                                          FUN_OVR_229__800a7964:800a7a58(j
                                                                                          OVR_229::800a7b20(j), 
                                                                                          OVR_229::800a7bac(j), 
                                                                                          OVR_229::800a7bb4(j), 
                                                                                          OVR_229::800a7be0(j), 
                                                                                          FUN_OVR_229__800a7964:800a7ee8(j
                                                                                          FUN_OVR_229__800a7964:800a7fa4(j
                                                                                          FUN_OVR_229__800a7964:800a80d8(j
                                                                                          FUN_OVR_229__800a7964:800a8190(j
     9::800a760c 08 00 e0 03     jr         ra
     9::800a7610 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a7614()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a7614                           XREF[4]:     FUN_OVR_229__800a7664:800a76ec(j
                                                                                          FUN_OVR_229__800a7664:800a7784(c
                                                                                          FUN_OVR_229__800a7664:800a77ac(c
                                                                                          FUN_OVR_229__800a7664:800a7818(c
     9::800a7614 00 00 d3 27     addiu      s3,s8,0x0
     9::800a7618 50 00 d4 27     addiu      s4,s8,0x50
     9::800a761c 64 00 d5 27     addiu      s5,s8,0x64
     9::800a7620 d0 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a7624 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a7628()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a7628                           XREF[6]:     FUN_OVR_229__800a7664:800a76f4(c
                                                                                          FUN_OVR_229__800a7664:800a7794(j
                                                                                          FUN_OVR_229__800a7664:800a77a4(c
                                                                                          FUN_OVR_229__800a7664:800a77d4(c
                                                                                          FUN_OVR_229__800a7664:800a77f4(c
                                                                                          FUN_OVR_229__800a7664:800a7828(c
     9::800a7628 50 00 d3 27     addiu      s3,s8,0x50
     9::800a762c 14 00 d4 27     addiu      s4,s8,0x14
     9::800a7630 78 00 d5 27     addiu      s5,s8,0x78
     9::800a7634 cb 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a7638 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a763c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a763c                           XREF[6]:     FUN_OVR_229__800a7664:800a771c(c
                                                                                          FUN_OVR_229__800a7664:800a777c(c
                                                                                          FUN_OVR_229__800a7664:800a77bc(j
                                                                                          FUN_OVR_229__800a7664:800a77cc(c
                                                                                          FUN_OVR_229__800a7664:800a77fc(c
                                                                                          FUN_OVR_229__800a7664:800a7838(c
     9::800a763c 64 00 d3 27     addiu      s3,s8,0x64
     9::800a7640 78 00 d4 27     addiu      s4,s8,0x78
     9::800a7644 28 00 d5 27     addiu      s5,s8,0x28
     9::800a7648 c6 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a764c a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_229__800a7650                           XREF[4]:     OVR_229::800a776c(j), 
                                                                                          OVR_229::800a77e4(j), 
                                                                                          OVR_229::800a780c(j), 
                                                                                          OVR_229::800a7850(j)  
     9::800a7650 78 00 d3 27     addiu      s3,s8,0x78
     9::800a7654 8c 00 d4 27     addiu      s4,s8,0x8c
     9::800a7658 a0 00 d5 27     addiu      s5,s8,0xa0
     9::800a765c c1 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a7660 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a7664()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a7664                           XREF[2]:     OVR_229::800a7714(c), 
                                                                                          OVR_229::800a77ec(c)  
     9::800a7664 64 00 d3 27     addiu      s3,s8,0x64
     9::800a7668 00 00 d4 27     addiu      s4,s8,0x0
     9::800a766c 78 00 d5 27     addiu      s5,s8,0x78
     9::800a7670 bc 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a7674 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a7678                           XREF[2]:     OVR_229::800a772c(j), 
                                                                                          OVR_229::800a779c(c)  
     9::800a7678 14 00 d3 27     addiu      s3,s8,0x14
     9::800a767c 3c 00 d4 27     addiu      s4,s8,0x3c
     9::800a7680 78 00 d5 27     addiu      s5,s8,0x78
     9::800a7684 b7 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a7688 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a768c                           XREF[2]:     OVR_229::800a76fc(c), 
                                                                                          OVR_229::800a77c4(c)  
     9::800a768c 28 00 d3 27     addiu      s3,s8,0x28
     9::800a7690 00 00 d4 27     addiu      s4,s8,0x0
     9::800a7694 78 00 d5 27     addiu      s5,s8,0x78
     9::800a7698 b2 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a769c 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_229__800a76a0                           XREF[2]:     OVR_229::800a770c(j), 
                                                                                          OVR_229::800a7774(c)  
     9::800a76a0 28 00 d3 27     addiu      s3,s8,0x28
     9::800a76a4 78 00 d4 27     addiu      s4,s8,0x78
     9::800a76a8 3c 00 d5 27     addiu      s5,s8,0x3c
     9::800a76ac ad 00 01 04     bgez       zero,FUN_OVR_229__800a7964
     9::800a76b0 8c 00 d6 27     _addiu     s6,s8,0x8c
     9::800a76b4 50 00 d3 27     addiu      s3,s8,0x50
     9::800a76b8 14 00 d4 27     addiu      s4,s8,0x14
     9::800a76bc 78 00 d5 27     addiu      s5,s8,0x78
     9::800a76c0 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a76c4 59 9e 02 0c     jal        FUN_OVR_229__800a7964                            undefined FUN_OVR_229__800a7964()
     9::800a76c8 0c 00 0a 24     _li        t2,0xc
     9::800a76cc 64 00 d3 27     addiu      s3,s8,0x64
     9::800a76d0 78 00 d4 27     addiu      s4,s8,0x78
     9::800a76d4 28 00 d5 27     addiu      s5,s8,0x28
     9::800a76d8 3c 00 d6 27     addiu      s6,s8,0x3c
     9::800a76dc 59 9e 02 0c     jal        FUN_OVR_229__800a7964                            undefined FUN_OVR_229__800a7964()
     9::800a76e0 0c 00 0a 24     _li        t2,0xc
     9::800a76e4 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a76e8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a76ec c9 ff 01 04     bgez       zero,FUN_OVR_229__800a7614
     9::800a76f0 0c 00 0a 24     _li        t2,0xc
     9::800a76f4 8a 9d 02 0c     jal        FUN_OVR_229__800a7628                            undefined FUN_OVR_229__800a7628()
     9::800a76f8 0c 00 0a 24     _li        t2,0xc
     9::800a76fc a3 9d 02 0c     jal        SUB_OVR_229__800a768c
     9::800a7700 0c 00 0a 24     _li        t2,0xc
     9::800a7704 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7708 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a770c e4 ff 01 04     bgez       zero,SUB_OVR_229__800a76a0
     9::800a7710 0c 00 0a 24     _li        t2,0xc
     9::800a7714 99 9d 02 0c     jal        FUN_OVR_229__800a7664                            undefined FUN_OVR_229__800a7664()
     9::800a7718 0c 00 0a 24     _li        t2,0xc
     9::800a771c 8f 9d 02 0c     jal        FUN_OVR_229__800a763c                            undefined FUN_OVR_229__800a763c()
     9::800a7720 0c 00 0a 24     _li        t2,0xc
     9::800a7724 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7728 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a772c d2 ff 01 04     bgez       zero,SUB_OVR_229__800a7678
     9::800a7730 0c 00 0a 24     _li        t2,0xc
     9::800a7734 00 00 d3 27     addiu      s3,s8,0x0
     9::800a7738 14 00 d4 27     addiu      s4,s8,0x14
     9::800a773c 78 00 d5 27     addiu      s5,s8,0x78
     9::800a7740 8c 00 d6 27     addiu      s6,s8,0x8c
     9::800a7744 59 9e 02 0c     jal        FUN_OVR_229__800a7964                            undefined FUN_OVR_229__800a7964()
     9::800a7748 0c 00 0a 24     _li        t2,0xc
     9::800a774c 00 00 d3 27     addiu      s3,s8,0x0
     9::800a7750 78 00 d4 27     addiu      s4,s8,0x78
     9::800a7754 28 00 d5 27     addiu      s5,s8,0x28
     9::800a7758 a0 00 d6 27     addiu      s6,s8,0xa0
     9::800a775c 59 9e 02 0c     jal        FUN_OVR_229__800a7964                            undefined FUN_OVR_229__800a7964()
     9::800a7760 0c 00 0a 24     _li        t2,0xc
     9::800a7764 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7768 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a776c b8 ff 01 04     bgez       zero,LAB_OVR_229__800a7650
     9::800a7770 0c 00 0a 24     _li        t2,0xc
     9::800a7774 a8 9d 02 0c     jal        SUB_OVR_229__800a76a0
     9::800a7778 0c 00 0a 24     _li        t2,0xc
     9::800a777c 8f 9d 02 0c     jal        FUN_OVR_229__800a763c                            undefined FUN_OVR_229__800a763c()
     9::800a7780 04 00 0a 24     _li        t2,0x4
     9::800a7784 85 9d 02 0c     jal        FUN_OVR_229__800a7614                            undefined FUN_OVR_229__800a7614()
     9::800a7788 0c 00 0a 24     _li        t2,0xc
     9::800a778c 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7790 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a7794 a4 ff 01 04     bgez       zero,FUN_OVR_229__800a7628
     9::800a7798 0c 00 0a 24     _li        t2,0xc
     9::800a779c 9e 9d 02 0c     jal        SUB_OVR_229__800a7678
     9::800a77a0 0c 00 0a 24     _li        t2,0xc
     9::800a77a4 8a 9d 02 0c     jal        FUN_OVR_229__800a7628                            undefined FUN_OVR_229__800a7628()
     9::800a77a8 04 00 0a 24     _li        t2,0x4
     9::800a77ac 85 9d 02 0c     jal        FUN_OVR_229__800a7614                            undefined FUN_OVR_229__800a7614()
     9::800a77b0 0c 00 0a 24     _li        t2,0xc
     9::800a77b4 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a77b8 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a77bc 9f ff 01 04     bgez       zero,FUN_OVR_229__800a763c
     9::800a77c0 0c 00 0a 24     _li        t2,0xc
     9::800a77c4 a3 9d 02 0c     jal        SUB_OVR_229__800a768c
     9::800a77c8 0c 00 0a 24     _li        t2,0xc
     9::800a77cc 8f 9d 02 0c     jal        FUN_OVR_229__800a763c                            undefined FUN_OVR_229__800a763c()
     9::800a77d0 08 00 0a 24     _li        t2,0x8
     9::800a77d4 8a 9d 02 0c     jal        FUN_OVR_229__800a7628                            undefined FUN_OVR_229__800a7628()
     9::800a77d8 0c 00 0a 24     _li        t2,0xc
     9::800a77dc 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a77e0 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a77e4 9a ff 01 04     bgez       zero,LAB_OVR_229__800a7650
     9::800a77e8 0c 00 0a 24     _li        t2,0xc
     9::800a77ec 99 9d 02 0c     jal        FUN_OVR_229__800a7664                            undefined FUN_OVR_229__800a7664()
     9::800a77f0 0c 00 0a 24     _li        t2,0xc
     9::800a77f4 8a 9d 02 0c     jal        FUN_OVR_229__800a7628                            undefined FUN_OVR_229__800a7628()
     9::800a77f8 08 00 0a 24     _li        t2,0x8
     9::800a77fc 8f 9d 02 0c     jal        FUN_OVR_229__800a763c                            undefined FUN_OVR_229__800a763c()
     9::800a7800 0c 00 0a 24     _li        t2,0xc
     9::800a7804 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7808 fc ff 39 27     addiu      t9,t9,-0x4
     9::800a780c 90 ff 01 04     bgez       zero,LAB_OVR_229__800a7650
     9::800a7810 0c 00 0a 24     _li        t2,0xc
     9::800a7814 b4 00 c0 af     sw         zero,0xb4(s8)
     9::800a7818 85 9d 02 0c     jal        FUN_OVR_229__800a7614                            undefined FUN_OVR_229__800a7614()
     9::800a781c 0c 00 0a 24     _li        t2,0xc
     9::800a7820 0c 00 03 24     li         v1,0xc
     9::800a7824 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a7828 8a 9d 02 0c     jal        FUN_OVR_229__800a7628                            undefined FUN_OVR_229__800a7628()
     9::800a782c 0c 00 0a 24     _li        t2,0xc
     9::800a7830 30 00 03 24     li         v1,0x30
     9::800a7834 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a7838 8f 9d 02 0c     jal        FUN_OVR_229__800a763c                            undefined FUN_OVR_229__800a763c()
     9::800a783c 0c 00 0a 24     _li        t2,0xc
     9::800a7840 3c 00 03 24     li         v1,0x3c
     9::800a7844 b4 00 c3 af     sw         v1,0xb4(s8)
     9::800a7848 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a784c fc ff 39 27     addiu      t9,t9,-0x4
     9::800a7850 7f ff 01 04     bgez       zero,LAB_OVR_229__800a7650
     9::800a7854 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a7858()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a7858                           XREF[5]:     FUN_OVR_229__800a7a94:800a7d70(c
                                                                                          FUN_OVR_229__800a7a94:800a7d84(c
                                                                                          FUN_OVR_229__800a7a94:800a7d98(c
                                                                                          FUN_OVR_229__800a7a94:800a7dac(c
                                                                                          FUN_OVR_229__800a7a94:800a7dc0(c
     9::800a7858 00 00 ab 85     lh         t3,0x0(t5)
     9::800a785c 00 00 cc 85     lh         t4,0x0(t6)
     9::800a7860 00 00 eb a5     sh         t3,0x0(t7)
     9::800a7864 21 18 6c 01     addu       v1,t3,t4
     9::800a7868 43 18 03 00     sra        v1,v1,0x1
     9::800a786c 00 00 03 a6     sh         v1,0x0(s0)
     9::800a7870 02 00 ab 85     lh         t3,0x2(t5)
     9::800a7874 02 00 cc 85     lh         t4,0x2(t6)
     9::800a7878 02 00 eb a5     sh         t3,0x2(t7)
     9::800a787c 21 18 6c 01     addu       v1,t3,t4
     9::800a7880 43 18 03 00     sra        v1,v1,0x1
     9::800a7884 02 00 03 a6     sh         v1,0x2(s0)
     9::800a7888 04 00 ab 85     lh         t3,0x4(t5)
     9::800a788c 04 00 cc 85     lh         t4,0x4(t6)
     9::800a7890 04 00 eb a5     sh         t3,0x4(t7)
     9::800a7894 21 18 6c 01     addu       v1,t3,t4
     9::800a7898 43 18 03 00     sra        v1,v1,0x1
     9::800a789c 00 00 00 ca     gte_ldVXY0 0x0(s0)
     9::800a78a0 00 08 83 48     gte_ldVZ0  v1
     9::800a78a4 04 00 03 a6     sh         v1,0x4(s0)
     9::800a78a8 08 00 ab 91     lbu        t3,0x8(t5)
     9::800a78ac 01 00 18 4a     RTPS
     9::800a78b0 08 00 cc 91     lbu        t4,0x8(t6)
     9::800a78b4 08 00 eb a1     sb         t3,0x8(t7)
     9::800a78b8 21 18 6c 01     addu       v1,t3,t4
     9::800a78bc 43 18 03 00     sra        v1,v1,0x1
     9::800a78c0 08 00 03 a2     sb         v1,0x8(s0)
     9::800a78c4 09 00 ab 91     lbu        t3,0x9(t5)
     9::800a78c8 09 00 cc 91     lbu        t4,0x9(t6)
     9::800a78cc 09 00 eb a1     sb         t3,0x9(t7)
     9::800a78d0 21 18 6c 01     addu       v1,t3,t4
     9::800a78d4 43 18 03 00     sra        v1,v1,0x1
     9::800a78d8 09 00 03 a2     sb         v1,0x9(s0)
     9::800a78dc 0a 00 ab 91     lbu        t3,0xa(t5)
     9::800a78e0 0a 00 cc 91     lbu        t4,0xa(t6)
     9::800a78e4 0a 00 eb a1     sb         t3,0xa(t7)
     9::800a78e8 21 18 6c 01     addu       v1,t3,t4
     9::800a78ec 43 18 03 00     sra        v1,v1,0x1
     9::800a78f0 0a 00 03 a2     sb         v1,0xa(s0)
     9::800a78f4 06 00 ab 91     lbu        t3,0x6(t5)
     9::800a78f8 06 00 cc 91     lbu        t4,0x6(t6)
     9::800a78fc 06 00 eb a1     sb         t3,0x6(t7)
     9::800a7900 21 18 6c 01     addu       v1,t3,t4
     9::800a7904 43 18 03 00     sra        v1,v1,0x1
     9::800a7908 06 00 03 a2     sb         v1,0x6(s0)
     9::800a790c 07 00 ab 91     lbu        t3,0x7(t5)
     9::800a7910 07 00 cc 91     lbu        t4,0x7(t6)
     9::800a7914 07 00 eb a1     sb         t3,0x7(t7)
     9::800a7918 21 18 6c 01     addu       v1,t3,t4
     9::800a791c 43 18 03 00     sra        v1,v1,0x1
     9::800a7920 07 00 03 a2     sb         v1,0x7(s0)
     9::800a7924 0c 00 a3 8d     lw         v1,0xc(t5)
     9::800a7928 10 00 a8 8d     lw         t0,0x10(t5)
     9::800a792c 0c 00 e3 ad     sw         v1,0xc(t7)
     9::800a7930 10 00 e8 ad     sw         t0,0x10(t7)
     9::800a7934 5c 00 2b 8c     lw         t3,0x5c(at)
     9::800a7938 00 98 03 48     gte_stSZ3  v1
     9::800a793c 0c 00 0e ea     gte_stSXY2 0xc(s0)
     9::800a7940 10 00 03 ae     sw         v1,0x10(s0)
     9::800a7944 23 40 6b 00     subu       t0,v1,t3
     9::800a7948 c2 47 08 00     srl        t0,t0,0x1f
     9::800a794c 12 00 08 a2     sb         t0,0x12(s0)
     9::800a7950 40 18 03 00     sll        v1,v1,0x1
     9::800a7954 23 40 6b 00     subu       t0,v1,t3
     9::800a7958 c2 47 08 00     srl        t0,t0,0x1f
     9::800a795c 08 00 e0 03     jr         ra
     9::800a7960 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a7964()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a7964                           XREF[12]:    FUN_OVR_229__800a7614:800a7620(j
                                                                                          FUN_OVR_229__800a7628:800a7634(j
                                                                                          FUN_OVR_229__800a763c:800a7648(j
                                                                                          FUN_OVR_229__800a7664:800a765c(j
                                                                                          FUN_OVR_229__800a7664:800a7670(j
                                                                                          FUN_OVR_229__800a7664:800a7684(j
                                                                                          FUN_OVR_229__800a7664:800a7698(j
                                                                                          FUN_OVR_229__800a7664:800a76ac(j
                                                                                          FUN_OVR_229__800a7664:800a76c4(c
                                                                                          FUN_OVR_229__800a7664:800a76dc(c
                                                                                          FUN_OVR_229__800a7664:800a7744(c
                                                                                          FUN_OVR_229__800a7664:800a775c(c
     9::800a7964 13 00 6f 82     lb         t7,0x13(s3)
     9::800a7968 13 00 90 82     lb         s0,0x13(s4)
     9::800a796c 13 00 b1 82     lb         s1,0x13(s5)
     9::800a7970 13 00 d2 82     lb         s2,0x13(s6)
     9::800a7974 24 18 f0 01     and        v1,t7,s0
     9::800a7978 24 18 71 00     and        v1,v1,s1
     9::800a797c 24 18 72 00     and        v1,v1,s2
     9::800a7980 22 ff 60 14     bne        v1,zero,LAB_OVR_229__800a760c
     9::800a7984 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a7988 12 00 90 82     lb         s0,0x12(s4)
     9::800a798c 12 00 b1 82     lb         s1,0x12(s5)
     9::800a7990 12 00 d2 82     lb         s2,0x12(s6)
     9::800a7994 25 78 f0 01     or         t7,t7,s0
     9::800a7998 25 78 f1 01     or         t7,t7,s1
     9::800a799c 25 78 f2 01     or         t7,t7,s2
     9::800a79a0 2e 00 e0 15     bne        t7,zero,LAB_OVR_229__800a7a5c
     9::800a79a4 0c 00 03 24     _li        v1,0xc
     9::800a79a8 70 00 2a ac     sw         t2,0x70(at)
     9::800a79ac 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a79b0 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a79b4 94 01 2a 8c     lw         t2,0x194(at)
     9::800a79b8 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a79bc 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a79c0 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a79c4 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a79c8 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a79cc 06 00 40 4b     NCLIP
     9::800a79d0 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a79d4 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a79d8 23 78 68 01     subu       t7,t3,t0
     9::800a79dc 23 80 88 01     subu       s0,t4,t0
     9::800a79e0 23 88 a8 01     subu       s1,t5,t0
     9::800a79e4 23 90 c8 01     subu       s2,t6,t0
     9::800a79e8 00 c0 08 48     gte_stMAC0 t0
     9::800a79ec 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a79f0 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a79fc
     9::800a79f4 22 40 08 00     _sub       t0,zero,t0
     9::800a79f8 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a79fc                           XREF[1]:     OVR_229::800a79f0(j)  
     9::800a79fc 06 00 40 4b     NCLIP
     9::800a7a00 24 18 6c 01     and        v1,t3,t4
     9::800a7a04 24 18 6d 00     and        v1,v1,t5
     9::800a7a08 24 18 6e 00     and        v1,v1,t6
     9::800a7a0c 25 78 f0 01     or         t7,t7,s0
     9::800a7a10 25 78 f1 01     or         t7,t7,s1
     9::800a7a14 27 78 f2 01     nor        t7,t7,s2
     9::800a7a18 25 78 e3 01     or         t7,t7,v1
     9::800a7a1c fb fe e0 05     bltz       t7,LAB_OVR_229__800a760c
     9::800a7a20 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a7a24 f9 fe e0 05     bltz       t7,LAB_OVR_229__800a760c
     9::800a7a28 00 c0 03 48     _gte_stM   v1
     9::800a7a2c 25 40 09 01     or         t0,t0,t1
     9::800a7a30 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a7a3c
     9::800a7a34 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a7a38 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a7a3c                           XREF[1]:     OVR_229::800a7a30(j)  
     9::800a7a3c 80 40 08 00     sll        t0,t0,0x2
     9::800a7a40 25 18 69 00     or         v1,v1,t1
     9::800a7a44 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a7a48 c0 18 03 00     sll        v1,v1,0x3
     9::800a7a4c 70 00 2a 8c     lw         t2,0x70(at)
     9::800a7a50 25 18 68 00     or         v1,v1,t0
     9::800a7a54 24 18 6a 00     and        v1,v1,t2
     9::800a7a58 ec fe 60 10     beq        v1,zero,LAB_OVR_229__800a760c
                             LAB_OVR_229__800a7a5c                           XREF[1]:     OVR_229::800a79a0(j)  
     9::800a7a5c 70 00 23 ac     _sw        v1,0x70(at)
     9::800a7a60 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a7a64 24 03 28 24     addiu      t0,at,0x324
     9::800a7a68 ea 00 1e 11     beq        t0,s8,LAB_OVR_229__800a7e14
     9::800a7a6c 04 00 39 27     _addiu     t9,t9,0x4
     9::800a7a70 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a7a74 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a7a78 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a7a7c 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a7a80 c0 fe 71 25     addiu      s1,t3,-0x140
     9::800a7a84 c0 fe 92 25     addiu      s2,t4,-0x140
     9::800a7a88 c0 fe af 25     addiu      t7,t5,-0x140
     9::800a7a8c a8 00 01 04     bgez       zero,LAB_OVR_229__800a7d30
     9::800a7a90 c0 fe d0 25     _addiu     s0,t6,-0x140
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a7a94()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a7a94                           XREF[4]:     OVR_229::800a75bc(c), 
                                                                                          OVR_229::800a75d0(c), 
                                                                                          OVR_229::800a75e4(c), 
                                                                                          OVR_229::800a75f8(c)  
     9::800a7a94 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a7a98 b4 00 ca af     sw         t2,0xb4(s8)
     9::800a7a9c 06 50 09 01     srlv       t2,t1,t0
     9::800a7aa0 1f 00 4a 31     andi       t2,t2,0x1f
     9::800a7aa4 80 50 0a 00     sll        t2,t2,0x2
     9::800a7aa8 21 50 41 01     addu       t2,t2,at
     9::800a7aac ec 00 4a 8d     lw         t2,0xec(t2)
     9::800a7ab0 6c 00 28 8c     lw         t0,0x6c(at)
     9::800a7ab4 94 01 2a ac     sw         t2,0x194(at)
     9::800a7ab8 02 9e 0a 00     srl        s3,t2,0x18
     9::800a7abc 1f 00 73 32     andi       s3,s3,0x1f
     9::800a7ac0 06 98 63 02     srlv       s3,v1,s3
     9::800a7ac4 ff 00 73 32     andi       s3,s3,0xff
     9::800a7ac8 21 98 7e 02     addu       s3,s3,s8
     9::800a7acc 02 a4 0a 00     srl        s4,t2,0x10
     9::800a7ad0 1f 00 94 32     andi       s4,s4,0x1f
     9::800a7ad4 06 a0 83 02     srlv       s4,v1,s4
     9::800a7ad8 ff 00 94 32     andi       s4,s4,0xff
     9::800a7adc 21 a0 9e 02     addu       s4,s4,s8
     9::800a7ae0 02 aa 0a 00     srl        s5,t2,0x8
     9::800a7ae4 1f 00 b5 32     andi       s5,s5,0x1f
     9::800a7ae8 06 a8 a3 02     srlv       s5,v1,s5
     9::800a7aec ff 00 b5 32     andi       s5,s5,0xff
     9::800a7af0 21 a8 be 02     addu       s5,s5,s8
     9::800a7af4 1f 00 56 31     andi       s6,t2,0x1f
     9::800a7af8 06 b0 c3 02     srlv       s6,v1,s6
     9::800a7afc ff 00 d6 32     andi       s6,s6,0xff
     9::800a7b00 21 b0 de 02     addu       s6,s6,s8
     9::800a7b04 13 00 6f 82     lb         t7,0x13(s3)
     9::800a7b08 13 00 90 82     lb         s0,0x13(s4)
     9::800a7b0c 13 00 b1 82     lb         s1,0x13(s5)
     9::800a7b10 13 00 d2 82     lb         s2,0x13(s6)
     9::800a7b14 24 18 f0 01     and        v1,t7,s0
     9::800a7b18 24 18 71 00     and        v1,v1,s1
     9::800a7b1c 24 18 72 00     and        v1,v1,s2
     9::800a7b20 ba fe 60 14     bne        v1,zero,LAB_OVR_229__800a760c
     9::800a7b24 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a7b28 12 00 90 82     lb         s0,0x12(s4)
     9::800a7b2c 12 00 b1 82     lb         s1,0x12(s5)
     9::800a7b30 12 00 d2 82     lb         s2,0x12(s6)
     9::800a7b34 25 78 f0 01     or         t7,t7,s0
     9::800a7b38 25 78 f1 01     or         t7,t7,s1
     9::800a7b3c 25 78 f2 01     or         t7,t7,s2
     9::800a7b40 28 00 e0 15     bne        t7,zero,LAB_OVR_229__800a7be4
     9::800a7b44 0c 00 03 24     _li        v1,0xc
     9::800a7b48 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     9::800a7b4c 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     9::800a7b50 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     9::800a7b54 0c 00 6b 8e     lw         t3,0xc(s3)
     9::800a7b58 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a7b5c 06 00 40 4b     NCLIP
     9::800a7b60 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a7b64 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a7b68 23 78 68 01     subu       t7,t3,t0
     9::800a7b6c 23 80 88 01     subu       s0,t4,t0
     9::800a7b70 23 88 a8 01     subu       s1,t5,t0
     9::800a7b74 23 90 c8 01     subu       s2,t6,t0
     9::800a7b78 00 c0 08 48     gte_stMAC0 t0
     9::800a7b7c 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     9::800a7b80 02 00 00 11     beq        t0,zero,LAB_OVR_229__800a7b8c
     9::800a7b84 22 40 08 00     _sub       t0,zero,t0
     9::800a7b88 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_229__800a7b8c                           XREF[1]:     OVR_229::800a7b80(j)  
     9::800a7b8c 06 00 40 4b     NCLIP
     9::800a7b90 24 18 6c 01     and        v1,t3,t4
     9::800a7b94 24 18 6d 00     and        v1,v1,t5
     9::800a7b98 24 18 6e 00     and        v1,v1,t6
     9::800a7b9c 25 78 f0 01     or         t7,t7,s0
     9::800a7ba0 25 78 f1 01     or         t7,t7,s1
     9::800a7ba4 27 78 f2 01     nor        t7,t7,s2
     9::800a7ba8 25 78 e3 01     or         t7,t7,v1
     9::800a7bac 97 fe e0 05     bltz       t7,LAB_OVR_229__800a760c
     9::800a7bb0 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a7bb4 95 fe e0 05     bltz       t7,LAB_OVR_229__800a760c
     9::800a7bb8 00 c0 03 48     _gte_stM   v1
     9::800a7bbc 25 40 09 01     or         t0,t0,t1
     9::800a7bc0 02 00 60 10     beq        v1,zero,LAB_OVR_229__800a7bcc
     9::800a7bc4 c2 47 08 00     _srl       t0,t0,0x1f
     9::800a7bc8 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_229__800a7bcc                           XREF[1]:     OVR_229::800a7bc0(j)  
     9::800a7bcc 80 40 08 00     sll        t0,t0,0x2
     9::800a7bd0 25 18 69 00     or         v1,v1,t1
     9::800a7bd4 c2 1f 03 00     srl        v1,v1,0x1f
     9::800a7bd8 c0 18 03 00     sll        v1,v1,0x3
     9::800a7bdc 25 18 68 00     or         v1,v1,t0
     9::800a7be0 8a fe 60 10     beq        v1,zero,LAB_OVR_229__800a760c
                             LAB_OVR_229__800a7be4                           XREF[1]:     OVR_229::800a7b40(j)  
     9::800a7be4 70 00 23 ac     _sw        v1,0x70(at)
     9::800a7be8 3c 00 3f af     sw         ra,0x3c(t9)
     9::800a7bec 04 00 39 27     addiu      t9,t9,0x4
     9::800a7bf0 c2 4f 09 00     srl        t1,t1,0x1f
     9::800a7bf4 c0 4f 09 00     sll        t1,t1,0x1f
     9::800a7bf8 c2 57 0a 00     srl        t2,t2,0x1f
     9::800a7bfc 80 57 0a 00     sll        t2,t2,0x1e
     9::800a7c00 25 50 49 01     or         t2,t2,t1
     9::800a7c04 80 00 2a ac     sw         t2,0x80(at)
     9::800a7c08 10 00 6b 96     lhu        t3,0x10(s3)
     9::800a7c0c 10 00 8c 96     lhu        t4,0x10(s4)
     9::800a7c10 10 00 ad 96     lhu        t5,0x10(s5)
     9::800a7c14 10 00 ce 96     lhu        t6,0x10(s6)
     9::800a7c18 b4 00 c3 8f     lw         v1,0xb4(s8)
     9::800a7c1c 23 50 6c 01     subu       t2,t3,t4
     9::800a7c20 82 48 03 00     srl        t1,v1,0x2
     9::800a7c24 21 48 38 01     addu       t1,t1,t8
     9::800a7c28 18 00 29 81     lb         t1,0x18(t1)
     9::800a7c2c 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a7c38
     9::800a7c30 21 e0 60 01     _move      gp,t3
     9::800a7c34 21 e0 80 01     move       gp,t4
                             LAB_OVR_229__800a7c38                           XREF[1]:     OVR_229::800a7c2c(j)  
     9::800a7c38 23 50 8d 03     subu       t2,gp,t5
     9::800a7c3c 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a7c48
     9::800a7c40 21 18 78 00     _addu      v1,v1,t8
     9::800a7c44 21 e0 a0 01     move       gp,t5
                             LAB_OVR_229__800a7c48                           XREF[1]:     OVR_229::800a7c3c(j)  
     9::800a7c48 23 50 8e 03     subu       t2,gp,t6
     9::800a7c4c 02 00 40 1d     bgtz       t2,LAB_OVR_229__800a7c58
     9::800a7c50 1c 00 63 8c     _lw        v1,0x1c(v1)
     9::800a7c54 21 e0 c0 01     move       gp,t6
                             LAB_OVR_229__800a7c58                           XREF[1]:     OVR_229::800a7c4c(j)  
     9::800a7c58 21 50 80 03     move       t2,gp
     9::800a7c5c 82 e1 1c 00     srl        gp,gp,0x6
     9::800a7c60 21 e0 89 03     addu       gp,gp,t1
     9::800a7c64 01 00 69 30     andi       t1,v1,0x1
     9::800a7c68 02 00 20 11     beq        t1,zero,LAB_OVR_229__800a7c74
     9::800a7c6c 80 e0 1c 00     _sll       gp,gp,0x2
     9::800a7c70 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_229__800a7c74                           XREF[1]:     OVR_229::800a7c68(j)  
     9::800a7c74 02 00 81 07     bgez       gp,LAB_OVR_229__800a7c80
     9::800a7c78 21 e0 85 03     _addu      gp,gp,a1
     9::800a7c7c 21 e0 a0 00     move       gp,a1
                             LAB_OVR_229__800a7c80                           XREF[1]:     OVR_229::800a7c74(j)  
     9::800a7c80 24 00 69 8c     lw         t1,0x24(v1)
     9::800a7c84 c0 f9 48 25     addiu      t0,t2,-0x640
     9::800a7c88 84 00 29 ac     sw         t1,0x84(at)
     9::800a7c8c 0a 00 01 05     bgez       t0,LAB_OVR_229__800a7cb8
     9::800a7c90 00 fb 48 25     _addiu     t0,t2,-0x500
     9::800a7c94 0c 00 63 24     addiu      v1,v1,0xc
     9::800a7c98 07 00 01 05     bgez       t0,LAB_OVR_229__800a7cb8
     9::800a7c9c 80 fd 48 25     _addiu     t0,t2,-0x280
     9::800a7ca0 0c 00 63 24     addiu      v1,v1,0xc
     9::800a7ca4 04 00 01 05     bgez       t0,LAB_OVR_229__800a7cb8
     9::800a7ca8 00 00 00 00     _nop
     9::800a7cac 02 00 20 05     bltz       t1,LAB_OVR_229__800a7cb8
     9::800a7cb0 00 00 00 00     _nop
     9::800a7cb4 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_229__800a7cb8                           XREF[4]:     OVR_229::800a7c8c(j), 
                                                                                          OVR_229::800a7c98(j), 
                                                                                          OVR_229::800a7ca4(j), 
                                                                                          OVR_229::800a7cac(j)  
     9::800a7cb8 94 01 2a 8c     lw         t2,0x194(at)
     9::800a7cbc 00 00 68 8c     lw         t0,0x0(v1)
     9::800a7cc0 04 00 69 8c     lw         t1,0x4(v1)
     9::800a7cc4 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a7cc8 ac 01 28 ac     sw         t0,0x1ac(at)
     9::800a7ccc a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a7cd0 00 52 0a 00     sll        t2,t2,0x8
     9::800a7cd4 0a 00 40 05     bltz       t2,LAB_OVR_229__800a7d00
     9::800a7cd8 b0 01 29 ac     _sw        t1,0x1b0(at)
     9::800a7cdc 06 00 68 a6     sh         t0,0x6(s3)
     9::800a7ce0 08 00 68 8c     lw         t0,0x8(v1)
     9::800a7ce4 06 00 89 a6     sh         t1,0x6(s4)
     9::800a7ce8 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a7cec 00 54 0a 00     sll        t2,t2,0x10
     9::800a7cf0 0b 00 40 05     bltz       t2,LAB_OVR_229__800a7d20
     9::800a7cf4 02 4c 08 00     _srl       t1,t0,0x10
     9::800a7cf8 09 00 01 04     bgez       zero,LAB_OVR_229__800a7d20
     9::800a7cfc 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_229__800a7d00                           XREF[1]:     OVR_229::800a7cd4(j)  
     9::800a7d00 06 00 69 a6     sh         t1,0x6(s3)
     9::800a7d04 08 00 69 8c     lw         t1,0x8(v1)
     9::800a7d08 00 54 0a 00     sll        t2,t2,0x10
     9::800a7d0c 06 00 88 a6     sh         t0,0x6(s4)
     9::800a7d10 02 44 09 00     srl        t0,t1,0x10
     9::800a7d14 02 00 40 05     bltz       t2,LAB_OVR_229__800a7d20
     9::800a7d18 06 00 a8 a6     _sh        t0,0x6(s5)
     9::800a7d1c 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a7d20                           XREF[3]:     OVR_229::800a7cf0(j), 
                                                                                          OVR_229::800a7cf8(j), 
                                                                                          OVR_229::800a7d14(j)  
     9::800a7d20 80 fd 71 25     addiu      s1,t3,-0x280
     9::800a7d24 80 fd 92 25     addiu      s2,t4,-0x280
     9::800a7d28 80 fd af 25     addiu      t7,t5,-0x280
     9::800a7d2c 80 fd d0 25     addiu      s0,t6,-0x280
                             LAB_OVR_229__800a7d30                           XREF[1]:     FUN_OVR_229__800a7964:800a7a8c(j
     9::800a7d30 42 8f 11 00     srl        s1,s1,0x1d
     9::800a7d34 04 00 31 32     andi       s1,s1,0x4
     9::800a7d38 02 97 12 00     srl        s2,s2,0x1c
     9::800a7d3c 08 00 52 32     andi       s2,s2,0x8
     9::800a7d40 25 88 32 02     or         s1,s1,s2
     9::800a7d44 c2 7e 0f 00     srl        t7,t7,0x1b
     9::800a7d48 10 00 ef 31     andi       t7,t7,0x10
     9::800a7d4c 25 88 2f 02     or         s1,s1,t7
     9::800a7d50 82 86 10 00     srl        s0,s0,0x1a
     9::800a7d54 20 00 10 32     andi       s0,s0,0x20
     9::800a7d58 25 88 30 02     or         s1,s1,s0
     9::800a7d5c 26 00 20 12     beq        s1,zero,LAB_OVR_229__800a7df8
     9::800a7d60 21 68 60 02     _move      t5,s3
     9::800a7d64 21 70 80 02     move       t6,s4
     9::800a7d68 b8 00 de 27     addiu      s8,s8,0xb8
     9::800a7d6c 00 00 cf 27     addiu      t7,s8,0x0
     9::800a7d70 16 9e 02 0c     jal        FUN_OVR_229__800a7858                            undefined FUN_OVR_229__800a7858()
     9::800a7d74 50 00 d0 27     _addiu     s0,s8,0x50
     9::800a7d78 21 68 80 02     move       t5,s4
     9::800a7d7c 21 70 c0 02     move       t6,s6
     9::800a7d80 14 00 cf 27     addiu      t7,s8,0x14
     9::800a7d84 16 9e 02 0c     jal        FUN_OVR_229__800a7858                            undefined FUN_OVR_229__800a7858()
     9::800a7d88 8c 00 d0 27     _addiu     s0,s8,0x8c
     9::800a7d8c 21 68 a0 02     move       t5,s5
     9::800a7d90 21 70 60 02     move       t6,s3
     9::800a7d94 28 00 cf 27     addiu      t7,s8,0x28
     9::800a7d98 16 9e 02 0c     jal        FUN_OVR_229__800a7858                            undefined FUN_OVR_229__800a7858()
     9::800a7d9c 64 00 d0 27     _addiu     s0,s8,0x64
     9::800a7da0 21 68 c0 02     move       t5,s6
     9::800a7da4 21 70 a0 02     move       t6,s5
     9::800a7da8 3c 00 cf 27     addiu      t7,s8,0x3c
     9::800a7dac 16 9e 02 0c     jal        FUN_OVR_229__800a7858                            undefined FUN_OVR_229__800a7858()
     9::800a7db0 a0 00 d0 27     _addiu     s0,s8,0xa0
     9::800a7db4 21 68 80 02     move       t5,s4
     9::800a7db8 21 70 a0 02     move       t6,s5
     9::800a7dbc 14 00 cf 27     addiu      t7,s8,0x14
     9::800a7dc0 16 9e 02 0c     jal        FUN_OVR_229__800a7858                            undefined FUN_OVR_229__800a7858()
     9::800a7dc4 78 00 d0 27     _addiu     s0,s8,0x78
     9::800a7dc8 21 18 21 02     addu       v1,s1,at
     9::800a7dcc 48 01 63 8c     lw         v1,0x148(v1)
     9::800a7dd0 0a 80 08 3c     lui        t0,0x800a
     9::800a7dd4 e8 7d 08 25     addiu      t0,t0,0x7de8
     9::800a7dd8 9c 00 23 ac     sw         v1,0x9c(at)
     9::800a7ddc 3c 00 28 af     sw         t0=>LAB_OVR_229__800a7de8,0x3c(t9)
     9::800a7de0 08 00 60 00     jr         v1
     9::800a7de4 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_229__800a7de8                           XREF[1]:     FUN_OVR_229__800a7a94:800a7ddc(*
     9::800a7de8 38 00 3f 8f     lw         ra,0x38(t9)
     9::800a7dec fc ff 39 27     addiu      t9,t9,-0x4
     9::800a7df0 08 00 e0 03     jr         ra
     9::800a7df4 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_229__800a7df8                           XREF[1]:     OVR_229::800a7d5c(j)  
     9::800a7df8 70 00 23 8c     lw         v1,0x70(at)
     9::800a7dfc fc ff 39 27     addiu      t9,t9,-0x4
     9::800a7e00 21 18 61 00     addu       v1,v1,at
     9::800a7e04 84 01 63 8c     lw         v1,0x184(v1)
     9::800a7e08 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a7e0c 08 00 60 00     jr         v1
     9::800a7e10 00 00 00 00     _nop
                             LAB_OVR_229__800a7e14                           XREF[1]:     OVR_229::800a7a68(j)  
     9::800a7e14 84 00 23 8c     lw         v1,0x84(at)
     9::800a7e18 24 03 2a 24     addiu      t2,at,0x324
     9::800a7e1c 26 00 60 1c     bgtz       v1,LAB_OVR_229__800a7eb8
     9::800a7e20 20 03 28 8c     _lw        t0,0x320(at)
     9::800a7e24 d8 03 29 8c     lw         t1,0x3d8(at)
     9::800a7e28 16 00 5e 15     bne        t2,s8,LAB_OVR_229__800a7e84
     9::800a7e2c 9c 00 23 8c     _lw        v1,0x9c(at)
     9::800a7e30 0a 80 0a 3c     lui        t2,0x800a
     9::800a7e34 14 78 4a 25     addiu      t2,t2,0x7814
     9::800a7e38 1f 00 6a 14     bne        v1,t2,LAB_OVR_229__800a7eb8
     9::800a7e3c 94 01 23 8c     _lw        v1,0x194(at)
     9::800a7e40 40 40 08 00     sll        t0,t0,0x1
     9::800a7e44 00 1a 03 00     sll        v1,v1,0x8
     9::800a7e48 02 00 61 04     bgez       v1,LAB_OVR_229__800a7e54
     9::800a7e4c 84 00 2a 8c     _lw        t2,0x84(at)
     9::800a7e50 c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_229__800a7e54                           XREF[1]:     OVR_229::800a7e48(j)  
     9::800a7e54 21 40 09 01     addu       t0,t0,t1
     9::800a7e58 21 50 48 01     addu       t2,t2,t0
     9::800a7e5c 00 00 48 8d     lw         t0,0x0(t2)
     9::800a7e60 04 00 49 8d     lw         t1,0x4(t2)
     9::800a7e64 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a7e68 06 00 68 a6     sh         t0,0x6(s3)
     9::800a7e6c 08 00 48 85     lh         t0,0x8(t2)
     9::800a7e70 a4 01 29 ac     sw         t1,0x1a4(at)
     9::800a7e74 06 00 89 a6     sh         t1,0x6(s4)
     9::800a7e78 0a 00 49 85     lh         t1,0xa(t2)
     9::800a7e7c 06 00 a8 a6     sh         t0,0x6(s5)
     9::800a7e80 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_229__800a7e84                           XREF[2]:     OVR_229::800a7e28(j), 
                                                                                          OVR_229::800a7ec4(j)  
     9::800a7e84 70 00 23 8c     lw         v1,0x70(at)
     9::800a7e88 00 00 00 00     nop
     9::800a7e8c 21 18 61 00     addu       v1,v1,at
     9::800a7e90 84 01 63 8c     lw         v1,0x184(v1)
     9::800a7e94 00 00 00 00     nop
     9::800a7e98 09 f8 60 00     jalr       v1
     9::800a7e9c fc ff 39 27     _addiu     t9,t9,-0x4
     9::800a7ea0 3c 00 3f 8f     lw         ra,0x3c(t9)
     9::800a7ea4 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a7ea8 b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a7eac a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a7eb0 08 00 e0 03     jr         ra
     9::800a7eb4 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_229__800a7eb8                           XREF[2]:     OVR_229::800a7e1c(j), 
                                                                                          OVR_229::800a7e38(j)  
     9::800a7eb8 ac 01 28 8c     lw         t0,0x1ac(at)
     9::800a7ebc b0 01 29 8c     lw         t1,0x1b0(at)
     9::800a7ec0 a0 01 28 ac     sw         t0,0x1a0(at)
     9::800a7ec4 ef ff 01 04     bgez       zero,LAB_OVR_229__800a7e84
     9::800a7ec8 a4 01 29 ac     _sw        t1,0x1a4(at)
     9::800a7ecc 21 98 80 02     move       s3,s4
     9::800a7ed0 21 a0 c0 02     move       s4,s6
     9::800a7ed4 13 00 6f 82     lb         t7,0x13(s3)
     9::800a7ed8 13 00 90 82     lb         s0,0x13(s4)
     9::800a7edc 13 00 b1 82     lb         s1,0x13(s5)
     9::800a7ee0 24 18 f0 01     and        v1,t7,s0
     9::800a7ee4 24 18 71 00     and        v1,v1,s1
     9::800a7ee8 c8 fd 60 04     bltz       v1,LAB_OVR_229__800a760c
     9::800a7eec 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a7ef0 12 00 90 82     lb         s0,0x12(s4)
     9::800a7ef4 12 00 b1 82     lb         s1,0x12(s5)
     9::800a7ef8 25 78 f0 01     or         t7,t7,s0
     9::800a7efc 25 78 f1 01     or         t7,t7,s1
     9::800a7f00 62 00 e0 05     bltz       t7,LAB_OVR_229__800a808c
     9::800a7f04 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a7f08 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a7f0c 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a7f10 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a7f14 08 00 90 8e     lw         s0,0x8(s4)
     9::800a7f18 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a7f1c 06 00 73 86     lh         s3,0x6(s3)
     9::800a7f20 06 00 94 86     lh         s4,0x6(s4)
     9::800a7f24 06 00 b5 86     lh         s5,0x6(s5)
     9::800a7f28 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a7f2c a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a7f30 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a7f34 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a7f38 a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a7f3c a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a7f40 60 00 03 3c     lui        v1,0x60
     9::800a7f44 24 48 83 02     and        t1,s4,v1
     9::800a7f48 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a7f54
     9::800a7f4c 00 36 03 3c     _lui       v1,0x3600
     9::800a7f50 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a7f54                           XREF[1]:     OVR_229::800a7f48(j)  
     9::800a7f54 25 18 6f 00     or         v1,v1,t7
     9::800a7f58 04 00 43 ac     sw         v1,0x4(v0)
     9::800a7f5c 08 00 4b ac     sw         t3,0x8(v0)
     9::800a7f60 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a7f64 10 00 50 ac     sw         s0,0x10(v0)
     9::800a7f68 14 00 4c ac     sw         t4,0x14(v0)
     9::800a7f6c 18 00 54 ac     sw         s4,0x18(v0)
     9::800a7f70 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a7f74 20 00 4d ac     sw         t5,0x20(v0)
     9::800a7f78 24 00 55 ac     sw         s5,0x24(v0)
     9::800a7f7c 28 00 09 24     li         t1,0x28
     9::800a7f80 39 00 01 04     bgez       zero,LAB_OVR_229__800a8068
     9::800a7f84 00 09 0a 3c     _lui       t2,0x900
     9::800a7f88 13 00 6f 82     lb         t7,0x13(s3)
     9::800a7f8c 13 00 90 82     lb         s0,0x13(s4)
     9::800a7f90 13 00 b1 82     lb         s1,0x13(s5)
     9::800a7f94 13 00 d2 82     lb         s2,0x13(s6)
     9::800a7f98 24 18 f0 01     and        v1,t7,s0
     9::800a7f9c 24 18 71 00     and        v1,v1,s1
     9::800a7fa0 24 18 72 00     and        v1,v1,s2
     9::800a7fa4 99 fd 60 14     bne        v1,zero,LAB_OVR_229__800a760c
     9::800a7fa8 12 00 6f 82     _lb        t7,0x12(s3)
     9::800a7fac 12 00 90 82     lb         s0,0x12(s4)
     9::800a7fb0 12 00 b1 82     lb         s1,0x12(s5)
     9::800a7fb4 12 00 d2 82     lb         s2,0x12(s6)
     9::800a7fb8 25 78 f0 01     or         t7,t7,s0
     9::800a7fbc 25 78 f1 01     or         t7,t7,s1
     9::800a7fc0 25 78 f2 01     or         t7,t7,s2
     9::800a7fc4 5a 00 e0 15     bne        t7,zero,LAB_OVR_229__800a8130
     9::800a7fc8 0c 00 6b 8e     _lw        t3,0xc(s3)
     9::800a7fcc 0c 00 8c 8e     lw         t4,0xc(s4)
     9::800a7fd0 0c 00 ad 8e     lw         t5,0xc(s5)
     9::800a7fd4 0c 00 ce 8e     lw         t6,0xc(s6)
     9::800a7fd8 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a7fdc 08 00 90 8e     lw         s0,0x8(s4)
     9::800a7fe0 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a7fe4 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a7fe8 06 00 73 86     lh         s3,0x6(s3)
     9::800a7fec 06 00 94 86     lh         s4,0x6(s4)
     9::800a7ff0 06 00 b5 86     lh         s5,0x6(s5)
     9::800a7ff4 a0 01 33 a4     sh         s3,0x1a0(at)
     9::800a7ff8 a4 01 34 a4     sh         s4,0x1a4(at)
     9::800a7ffc 06 00 d4 86     lh         s4,0x6(s6)
     9::800a8000 a8 01 35 a4     sh         s5,0x1a8(at)
     9::800a8004 aa 01 34 a4     sh         s4,0x1aa(at)
     9::800a8008 a0 01 33 8c     lw         s3,0x1a0(at)
     9::800a800c a4 01 34 8c     lw         s4,0x1a4(at)
     9::800a8010 a8 01 35 8c     lw         s5,0x1a8(at)
     9::800a8014 60 00 03 3c     lui        v1,0x60
     9::800a8018 24 48 83 02     and        t1,s4,v1
     9::800a801c 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a8028
     9::800a8020 00 3e 03 3c     _lui       v1,0x3e00
     9::800a8024 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a8028                           XREF[1]:     OVR_229::800a801c(j)  
     9::800a8028 25 18 6f 00     or         v1,v1,t7
     9::800a802c 04 00 43 ac     sw         v1,0x4(v0)
     9::800a8030 08 00 4b ac     sw         t3,0x8(v0)
     9::800a8034 0c 00 53 ac     sw         s3,0xc(v0)
     9::800a8038 10 00 50 ac     sw         s0,0x10(v0)
     9::800a803c 14 00 4c ac     sw         t4,0x14(v0)
     9::800a8040 18 00 54 ac     sw         s4,0x18(v0)
     9::800a8044 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a8048 20 00 4d ac     sw         t5,0x20(v0)
     9::800a804c 24 00 55 ac     sw         s5,0x24(v0)
     9::800a8050 28 00 52 ac     sw         s2,0x28(v0)
     9::800a8054 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a8058 02 1c 15 00     srl        v1,s5,0x10
     9::800a805c 30 00 43 ac     sw         v1,0x30(v0)
     9::800a8060 34 00 09 24     li         t1,0x34
     9::800a8064 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_229__800a8068                           XREF[1]:     OVR_229::800a7f80(j)  
     9::800a8068 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a806c 00 42 02 00     sll        t0,v0,0x8
     9::800a8070 02 42 08 00     srl        t0,t0,0x8
     9::800a8074 25 18 6a 00     or         v1,v1,t2
     9::800a8078 00 00 43 ac     sw         v1,0x0(v0)
     9::800a807c 21 10 49 00     addu       v0,v0,t1
     9::800a8080 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a8084 08 00 e0 03     jr         ra
     9::800a8088 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_229__800a808c                           XREF[1]:     OVR_229::800a7f00(j)  
     9::800a808c 58 00 3f ac     sw         ra,0x58(at)
     9::800a8090 98 01 2f 84     lh         t7,0x198(at)
     9::800a8094 9a 01 30 84     lh         s0,0x19a(at)
     9::800a8098 9c 01 31 84     lh         s1,0x19c(at)
     9::800a809c 00 00 63 86     lh         v1,0x0(s3)
     9::800a80a0 02 00 68 86     lh         t0,0x2(s3)
     9::800a80a4 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a80a8 04 00 69 86     _lh        t1,0x4(s3)
     9::800a80ac 0b 00 40 05     bltz       t2,LAB_OVR_229__800a80dc
     9::800a80b0 00 00 83 86     _lh        v1,0x0(s4)
     9::800a80b4 02 00 88 86     lh         t0,0x2(s4)
     9::800a80b8 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a80bc 04 00 89 86     _lh        t1,0x4(s4)
     9::800a80c0 06 00 40 05     bltz       t2,LAB_OVR_229__800a80dc
     9::800a80c4 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a80c8 02 00 a8 86     lh         t0,0x2(s5)
     9::800a80cc 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a80d0 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a80d4 58 00 3f 8c     lw         ra,0x58(at)
     9::800a80d8 4c fd 41 05     bgez       t2,LAB_OVR_229__800a760c
                             LAB_OVR_229__800a80dc                           XREF[2]:     OVR_229::800a80ac(j), 
                                                                                          OVR_229::800a80c0(j)  
     9::800a80dc 10 00 2f 8c     lw         t7,0x10(at)
     9::800a80e0 80 00 23 8c     lw         v1,0x80(at)
     9::800a80e4 a6 01 28 84     lh         t0,0x1a6(at)
     9::800a80e8 a2 01 29 84     lh         t1,0x1a2(at)
     9::800a80ec 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a80f0 00 00 e3 ad     sw         v1,0x0(t7)
     9::800a80f4 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a80f8 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a80fc 21 68 60 02     move       t5,s3
     9::800a8100 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a8104 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a8108 21 68 80 02     move       t5,s4
     9::800a810c 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a8110 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a8114 21 68 a0 02     move       t5,s5
     9::800a8118 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a811c 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a8120 58 00 3f 8c     lw         ra,0x58(at)
     9::800a8124 30 00 ef 25     addiu      t7,t7,0x30
     9::800a8128 08 00 e0 03     jr         ra
     9::800a812c 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_229__800a8130                           XREF[1]:     OVR_229::800a7fc4(j)  
     9::800a8130 58 00 3f ac     sw         ra,0x58(at)
     9::800a8134 98 01 2f 84     lh         t7,0x198(at)
     9::800a8138 9a 01 30 84     lh         s0,0x19a(at)
     9::800a813c 9c 01 31 84     lh         s1,0x19c(at)
     9::800a8140 00 00 63 86     lh         v1,0x0(s3)
     9::800a8144 02 00 68 86     lh         t0,0x2(s3)
     9::800a8148 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a814c 04 00 69 86     _lh        t1,0x4(s3)
     9::800a8150 10 00 40 05     bltz       t2,LAB_OVR_229__800a8194
     9::800a8154 00 00 83 86     _lh        v1,0x0(s4)
     9::800a8158 02 00 88 86     lh         t0,0x2(s4)
     9::800a815c 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a8160 04 00 89 86     _lh        t1,0x4(s4)
     9::800a8164 0b 00 40 05     bltz       t2,LAB_OVR_229__800a8194
     9::800a8168 00 00 a3 86     _lh        v1,0x0(s5)
     9::800a816c 02 00 a8 86     lh         t0,0x2(s5)
     9::800a8170 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a8174 04 00 a9 86     _lh        t1,0x4(s5)
     9::800a8178 06 00 40 05     bltz       t2,LAB_OVR_229__800a8194
     9::800a817c 00 00 c3 86     _lh        v1,0x0(s6)
     9::800a8180 02 00 c8 86     lh         t0,0x2(s6)
     9::800a8184 7e a0 02 0c     jal        FUN_OVR_229__800a81f8                            undefined FUN_OVR_229__800a81f8()
     9::800a8188 04 00 c9 86     _lh        t1,0x4(s6)
     9::800a818c 58 00 3f 8c     lw         ra,0x58(at)
     9::800a8190 1e fd 41 05     bgez       t2,LAB_OVR_229__800a760c
                             LAB_OVR_229__800a8194                           XREF[3]:     OVR_229::800a8150(j), 
                                                                                          OVR_229::800a8164(j), 
                                                                                          OVR_229::800a8178(j)  
     9::800a8194 10 00 2f 8c     lw         t7,0x10(at)
     9::800a8198 80 00 23 8c     lw         v1,0x80(at)
     9::800a819c a6 01 28 84     lh         t0,0x1a6(at)
     9::800a81a0 a2 01 29 84     lh         t1,0x1a2(at)
     9::800a81a4 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     9::800a81a8 01 00 63 34     ori        v1,v1,0x1
     9::800a81ac 00 00 e3 ad     sw         v1,0x0(t7)
     9::800a81b0 08 00 e8 a5     sh         t0,0x8(t7)
     9::800a81b4 0a 00 e9 a5     sh         t1,0xa(t7)
     9::800a81b8 21 68 60 02     move       t5,s3
     9::800a81bc 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a81c0 0c 00 f0 25     _addiu     s0,t7,0xc
     9::800a81c4 21 68 80 02     move       t5,s4
     9::800a81c8 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a81cc 18 00 f0 25     _addiu     s0,t7,0x18
     9::800a81d0 21 68 a0 02     move       t5,s5
     9::800a81d4 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a81d8 24 00 f0 25     _addiu     s0,t7,0x24
     9::800a81dc 21 68 c0 02     move       t5,s6
     9::800a81e0 8e a0 02 0c     jal        FUN_OVR_229__800a8238                            undefined FUN_OVR_229__800a8238()
     9::800a81e4 30 00 f0 25     _addiu     s0,t7,0x30
     9::800a81e8 58 00 3f 8c     lw         ra,0x58(at)
     9::800a81ec 3c 00 ef 25     addiu      t7,t7,0x3c
     9::800a81f0 08 00 e0 03     jr         ra
     9::800a81f4 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a81f8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a81f8                           XREF[7]:     FUN_OVR_229__800a7964:800a80a4(c
                                                                                          FUN_OVR_229__800a7964:800a80b8(c
                                                                                          FUN_OVR_229__800a7964:800a80cc(c
                                                                                          FUN_OVR_229__800a7964:800a8148(c
                                                                                          FUN_OVR_229__800a7964:800a815c(c
                                                                                          FUN_OVR_229__800a7964:800a8170(c
                                                                                          FUN_OVR_229__800a7964:800a8184(c
     9::800a81f8 23 18 6f 00     subu       v1,v1,t7
     9::800a81fc 02 00 61 04     bgez       v1,LAB_OVR_229__800a8208
     9::800a8200 23 40 10 01     _subu      t0,t0,s0
     9::800a8204 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_229__800a8208                           XREF[1]:     OVR_229::800a81fc(j)  
     9::800a8208 00 ff 6b 24     addiu      t3,v1,-0x100
     9::800a820c 02 00 01 05     bgez       t0,LAB_OVR_229__800a8218
     9::800a8210 23 48 31 01     _subu      t1,t1,s1
     9::800a8214 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_229__800a8218                           XREF[1]:     OVR_229::800a820c(j)  
     9::800a8218 80 fe 0c 25     addiu      t4,t0,-0x180
     9::800a821c 02 00 21 05     bgez       t1,LAB_OVR_229__800a8228
     9::800a8220 00 00 00 00     _nop
     9::800a8224 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_229__800a8228                           XREF[1]:     OVR_229::800a821c(j)  
     9::800a8228 00 ff 2d 25     addiu      t5,t1,-0x100
     9::800a822c 24 58 6c 01     and        t3,t3,t4
     9::800a8230 08 00 e0 03     jr         ra
     9::800a8234 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a8238()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a8238                           XREF[7]:     FUN_OVR_229__800a7964:800a8100(c
                                                                                          FUN_OVR_229__800a7964:800a810c(c
                                                                                          FUN_OVR_229__800a7964:800a8118(c
                                                                                          FUN_OVR_229__800a7964:800a81bc(c
                                                                                          FUN_OVR_229__800a7964:800a81c8(c
                                                                                          FUN_OVR_229__800a7964:800a81d4(c
                                                                                          FUN_OVR_229__800a7964:800a81e0(c
     9::800a8238 13 00 a3 81     lb         v1,0x13(t5)
     9::800a823c 00 00 a8 8d     lw         t0,0x0(t5)
     9::800a8240 04 00 a9 8d     lw         t1,0x4(t5)
     9::800a8244 08 00 aa 8d     lw         t2,0x8(t5)
     9::800a8248 00 1e 03 00     sll        v1,v1,0x18
     9::800a824c 25 50 43 01     or         t2,t2,v1
     9::800a8250 00 00 08 ae     sw         t0,0x0(s0)
     9::800a8254 04 00 09 ae     sw         t1,0x4(s0)
     9::800a8258 08 00 e0 03     jr         ra
     9::800a825c 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_229__800a8260                           XREF[1]:     OVR_229::800a8328(j)  
     9::800a8260 a0 02 3f 8c     lw         ra,0x2a0(at)
     9::800a8264 00 00 00 00     nop
                             LAB_OVR_229__800a8268                           XREF[1]:     OVR_229::800a8274(j)  
     9::800a8268 08 00 e0 03     jr         ra
     9::800a826c 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a8270()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a8270                           XREF[4]:     OVR_229::800a0fdc(c), 
                                                                                          OVR_229::800a0ff4(c), 
                                                                                          OVR_229::800a100c(c), 
                                                                                          OVR_229::800a1024(c)  
     
	 // pushBuffer matrix offset 0x28, upload to GTE
	 9::800a8270 a0 02 3f ac     sw         ra,0x2a0(at)
     9::800a8274 fc ff f8 12     beq        s7,t8,LAB_OVR_229__800a8268
     9::800a8278 28 00 ab 8c     _lw        t3,0x28(a1)
     9::800a827c 2c 00 ac 8c     lw         t4,0x2c(a1)
     9::800a8280 30 00 ad 8c     lw         t5,0x30(a1)
     9::800a8284 34 00 ae 8c     lw         t6,0x34(a1)
     9::800a8288 38 00 af 8c     lw         t7,0x38(a1)
     9::800a828c 3c 00 b0 8c     lw         s0,0x3c(a1)
     9::800a8290 40 00 b1 8c     lw         s1,0x40(a1)
     9::800a8294 44 00 b2 8c     lw         s2,0x44(a1)
     9::800a8298 00 40 cb 48     gte_ldL1   t3
     9::800a829c 00 48 cc 48     gte_ldL1   t4
     9::800a82a0 00 50 cd 48     gte_ldL2   t5
     9::800a82a4 00 58 ce 48     gte_ldL3   t6
     9::800a82a8 00 60 cf 48     gte_ldL33  t7
     9::800a82ac 00 68 d0        ldbkdir    s0,s1,s2
                 48 00 70 
                 d1 48 00 
				 
	 // distance to screen, and window dimensions, give to GTE
     9::800a82b8 20 00 a3 84     lh         v1,0x20(a1)
     9::800a82bc 22 00 a8 84     lh         t0,0x22(a1)
     9::800a82c0 18 00 be 8c     lw         s8,0x18(a1)
     9::800a82c4 c0 1b 03 00     sll        v1,v1,0xf
     9::800a82c8 c0 43 08 00     sll        t0,t0,0xf
     9::800a82cc 00 c0 c3 48     gte_ldOFX  v1
     9::800a82d0 00 c8 c8 48     gte_ldOFY  t0
     9::800a82d4 00 d0 de 48     gte_ldH    s8
	 
     9::800a82d8 42 f0 1e 00     srl        s8,s8,0x1
     9::800a82dc 01 00 de 27     addiu      s8,s8,0x1
     9::800a82e0 08 02 3e a4     sh         s8,0x208(at)
     9::800a82e4 1c 02 3e a4     sh         s8,0x21c(at)
     9::800a82e8 30 02 3e a4     sh         s8,0x230(at)
     9::800a82ec 16 02 20 a4     sh         zero,0x216(at)
     9::800a82f0 2a 02 20 a4     sh         zero,0x22a(at)
     9::800a82f4 3e 02 20 a4     sh         zero,0x23e(at)
     9::800a82f8 20 00 a3 8c     lw         v1,0x20(a1)
     9::800a82fc f4 00 a5 8c     lw         a1,0xf4(a1)
     9::800a8300 6c 00 23 ac     sw         v1,0x6c(at)
     9::800a8304 00 10 0b 24     li         t3,0x1000
     9::800a8308 00 00 cb 48     gte_ldR1   t3
     9::800a830c 00 08 c0 48     gte_ldR1   zero
     9::800a8310 00 10 cb 48     gte_ldR2   t3
     9::800a8314 00 18 c0 48     gte_ldR3   zero
     9::800a8318 00 20 cb 48     gte_ldR33  t3
     9::800a831c 00 28 c0        ldtr       zero,zero,zero
                 48 00 30 
                 c0 48 00 
                             LAB_OVR_229__800a8328                           XREF[24]:    OVR_229::800a845c(j), 
                                                                                          OVR_229::800a8494(j), 
                                                                                          OVR_229::800a84cc(j), 
                                                                                          OVR_229::800a8500(j), 
                                                                                          OVR_229::800a8538(j), 
                                                                                          OVR_229::800a856c(j), 
                                                                                          OVR_229::800a85a0(j), 
                                                                                          OVR_229::800a85a8(j), 
                                                                                          OVR_229::800a8a64(j), 
                                                                                          OVR_229::800a8aac(j), 
                                                                                          OVR_229::800a8b04(j), 
                                                                                          OVR_229::800a8b58(j), 
                                                                                          OVR_229::800a8bb0(j), 
                                                                                          OVR_229::800a8c04(j), 
                                                                                          OVR_229::800a8c64(j), 
                                                                                          OVR_229::800a8c98(j), 
                                                                                          OVR_229::800a8ce0(j), 
                                                                                          OVR_229::800a8d48(j), 
                                                                                          OVR_229::800a8d9c(j), 
                                                                                          OVR_229::800a8de0(j), [more]
     9::800a8328 cd ff f8 12     beq        s7,t8,LAB_OVR_229__800a8260
     9::800a832c 30 00 23 8c     _lw        v1,0x30(at)
     9::800a8330 68 34 48 24     addiu      t0,v0,0x3468
     9::800a8334 23 18 68 00     subu       v1,v1,t0
     9::800a8338 3c e3 60 04     bltz       v1,LAB_OVR_229__800a102c
     9::800a833c 0c 00 e0 ca     _gte_ldV   0xc(s7)
     9::800a8340 10 00 e1 ca     gte_ldVZ0  0x10(s7)
     9::800a8344 08 00 e8 86     lh         t0,0x8(s7)
     9::800a8348 0a 00 e9 86     lh         t1,0xa(s7)
     9::800a834c 12 20 4a 4a     LLV0BK
     9::800a8350 a6 01 28 a4     sh         t0,0x1a6(at)
     9::800a8354 a2 01 29 a4     sh         t1,0x1a2(at)
     9::800a8358 12 00 e3 86     lh         v1,0x12(s7)
     9::800a835c 14 00 e8 8e     lw         t0,0x14(s7)
     9::800a8360 ba 01 23 a4     sh         v1,0x1ba(at)
     9::800a8364 bc 01 28 ac     sw         t0,0x1bc(at)
     9::800a8368 00 48 0b 48     gte_stIR1  t3
     9::800a836c 00 50 0c 48     gte_stIR2  t4
     9::800a8370 00 58 0d 48     gte_stIR3  t5
     9::800a8374 b4 01 2b a4     sh         t3,0x1b4(at)
     9::800a8378 b6 01 2c a4     sh         t4,0x1b6(at)
     9::800a837c b8 01 2d a4     sh         t5,0x1b8(at)
     9::800a8380 18 00 e0 ca     gte_ldVXY0 0x18(s7)
     9::800a8384 1c 00 e1 ca     gte_ldVZ0  0x1c(s7)
     9::800a8388 1e 00 e3 86     lh         v1,0x1e(s7)
     9::800a838c 20 00 e8 8e     lw         t0,0x20(s7)
     9::800a8390 12 20 4a 4a     LLV0BK
     9::800a8394 ce 01 23 a4     sh         v1,0x1ce(at)
     9::800a8398 d0 01 28 ac     sw         t0,0x1d0(at)
     9::800a839c 04 00 fc 8e     lw         gp,0x4(s7)
     9::800a83a0 00 48 0b 48     gte_stIR1  t3
     9::800a83a4 00 50 0c 48     gte_stIR2  t4
     9::800a83a8 00 58 0d 48     gte_stIR3  t5
     9::800a83ac c8 01 2b a4     sh         t3,0x1c8(at)
     9::800a83b0 ca 01 2c a4     sh         t4,0x1ca(at)
     9::800a83b4 cc 01 2d a4     sh         t5,0x1cc(at)
     9::800a83b8 24 00 e0 ca     gte_ldVXY0 0x24(s7)
     9::800a83bc 28 00 e1 ca     gte_ldVZ0  0x28(s7)
     9::800a83c0 00 00 e9 8e     lw         t1,0x0(s7)
     9::800a83c4 2a 00 e3 86     lh         v1,0x2a(s7)
     9::800a83c8 12 20 4a 4a     LLV0BK
     9::800a83cc 2c 00 e8 8e     lw         t0,0x2c(s7)
     9::800a83d0 e2 01 23 a4     sh         v1,0x1e2(at)
     9::800a83d4 e4 01 28 ac     sw         t0,0x1e4(at)
     9::800a83d8 00 48 0b 48     gte_stIR1  t3
     9::800a83dc 00 50 0c 48     gte_stIR2  t4
     9::800a83e0 00 58 0d 48     gte_stIR3  t5
     9::800a83e4 dc 01 2b a4     sh         t3,0x1dc(at)
     9::800a83e8 de 01 2c a4     sh         t4,0x1de(at)
     9::800a83ec e0 01 2d a4     sh         t5,0x1e0(at)
     9::800a83f0 01 00 23 31     andi       v1,t1,0x1
     9::800a83f4 6f 01 60 14     bne        v1,zero,LAB_OVR_229__800a89b4
     9::800a83f8 7c 00 29 ac     _sw        t1,0x7c(at)
     9::800a83fc 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a8400 b4 01 2d 24     _addiu     t5,at,0x1b4
     9::800a8404 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a8408 c8 01 2d 24     _addiu     t5,at,0x1c8
     9::800a840c 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a8410 dc 01 2d 24     _addiu     t5,at,0x1dc
     9::800a8414 bf 01 23 80     lb         v1,0x1bf(at)
     9::800a8418 d3 01 28 80     lb         t0,0x1d3(at)
     9::800a841c e7 01 29 80     lb         t1,0x1e7(at)
     9::800a8420 80 18 03 00     sll        v1,v1,0x2
     9::800a8424 c0 40 08 00     sll        t0,t0,0x3
     9::800a8428 00 49 09 00     sll        t1,t1,0x4
     9::800a842c 25 18 68 00     or         v1,v1,t0
     9::800a8430 25 18 69 00     or         v1,v1,t1
     9::800a8434 21 18 61 00     addu       v1,v1,at
     9::800a8438 40 02 63 8c     lw         v1,0x240(v1)
     9::800a843c bf 01 20 a0     sb         zero,0x1bf(at)
     9::800a8440 d3 01 20 a0     sb         zero,0x1d3(at)
     9::800a8444 08 00 60 00     jr         v1
     9::800a8448 e7 01 20 a0     _sb        zero,0x1e7(at)
                             LAB_OVR_229__800a844c                           XREF[2]:     FUN_OVR_229__800a8ebc:800a8ed4(*
                                                                                          OVR_229::800a92ac(*)  
     9::800a844c b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8450 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8454 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8458 dc 01 35 24     _addiu     s5,at,0x1dc
     9::800a845c b2 ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8460 30 00 f7 26     _addiu     s7,s7,0x30
                             LAB_OVR_229__800a8464                           XREF[2]:     FUN_OVR_229__800a8ebc:800a8ed4(*
                                                                                          OVR_229::800a92b0(*)  
     9::800a8464 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8468 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a846c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8470 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8474 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8478 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a847c 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8480 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8484 dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8488 04 02 35 24     addiu      s5,at,0x204
     9::800a848c 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8490 18 02 36 24     _addiu     s6,at,0x218
     9::800a8494 a4 ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8498 30 00 f7 26     _addiu     s7,s7,0x30
     9::800a849c dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a84a0 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a84a4 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a84a8 04 02 2f 24     _addiu     t7,at,0x204
     9::800a84ac b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a84b0 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a84b4 18 02 2f 24     _addiu     t7,at,0x218
     9::800a84b8 dc 01 33 24     addiu      s3,at,0x1dc
     9::800a84bc b4 01 34 24     addiu      s4,at,0x1b4
     9::800a84c0 04 02 35 24     addiu      s5,at,0x204
     9::800a84c4 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a84c8 18 02 36 24     _addiu     s6,at,0x218
     9::800a84cc 96 ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a84d0 30 00 f7 26     _addiu     s7,s7,0x30
     9::800a84d4 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a84d8 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a84dc 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a84e0 04 02 2f 24     _addiu     t7,at,0x204
     9::800a84e4 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a84e8 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a84ec 18 02 2f 24     _addiu     t7,at,0x218
     9::800a84f0 dc 01 33 24     addiu      s3,at,0x1dc
     9::800a84f4 18 02 34 24     addiu      s4,at,0x218
     9::800a84f8 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a84fc 04 02 35 24     _addiu     s5,at,0x204
     9::800a8500 89 ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8504 30 00 f7 26     _addiu     s7,s7,0x30
     9::800a8508 b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a850c dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8510 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8514 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8518 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a851c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8520 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8524 b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8528 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a852c 04 02 35 24     addiu      s5,at,0x204
     9::800a8530 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8534 18 02 36 24     _addiu     s6,at,0x218
     9::800a8538 7b ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a853c 30 00 f7 26     _addiu     s7,s7,0x30
     9::800a8540 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8544 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8548 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a854c 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8550 dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8554 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8558 18 02 2f 24     _addiu     t7,at,0x218
     9::800a855c c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8560 18 02 34 24     addiu      s4,at,0x218
     9::800a8564 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8568 04 02 35 24     _addiu     s5,at,0x204
     9::800a856c 6e ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8570 30 00 f7 26     _addiu     s7,s7,0x30
     9::800a8574 b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8578 dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a857c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8580 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8584 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8588 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a858c 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8590 b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8594 18 02 34 24     addiu      s4,at,0x218
     9::800a8598 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a859c 04 02 35 24     _addiu     s5,at,0x204
     9::800a85a0 61 ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a85a4 30 00 f7 26     _addiu     s7,s7,0x30
     9::800a85a8 5f ff 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a85ac 30 00 f7 26     _addiu     s7,s7,0x30
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a85b0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a85b0                           XREF[7]:     FUN_OVR_229__800a8270:800a83fc(c
                                                                                          FUN_OVR_229__800a8270:800a8404(c
                                                                                          FUN_OVR_229__800a8270:800a840c(c
                                                                                          FUN_OVR_229__800a8270:800a89e8(c
                                                                                          FUN_OVR_229__800a8270:800a89f0(c
                                                                                          FUN_OVR_229__800a8270:800a89f8(c
                                                                                          FUN_OVR_229__800a8270:800a8a00(c
     9::800a85b0 04 00 b2 85     lh         s2,0x4(t5)
     9::800a85b4 02 00 b1 85     lh         s1,0x2(t5)
     9::800a85b8 00 00 b0 85     lh         s0,0x0(t5)
     9::800a85bc 23 18 5e 02     subu       v1,s2,s8
     9::800a85c0 40 80 10 00     sll        s0,s0,0x1
     9::800a85c4 40 88 11 00     sll        s1,s1,0x1
     9::800a85c8 40 90 12 00     sll        s2,s2,0x1
     9::800a85cc 0c 00 b0 a5     sh         s0,0xc(t5)
     9::800a85d0 0e 00 b1 a5     sh         s1,0xe(t5)
     9::800a85d4 10 00 b2 a5     sh         s2,0x10(t5)
     9::800a85d8 08 00 e0 03     jr         ra
     9::800a85dc 12 00 a3 a5     _sh        v1,0x12(t5)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a85e0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a85e0                           XREF[52]:    OVR_229::800a846c(c), 
                                                                                          OVR_229::800a8478(c), 
                                                                                          OVR_229::800a84a4(c), 
                                                                                          OVR_229::800a84b0(c), 
                                                                                          OVR_229::800a84dc(c), 
                                                                                          OVR_229::800a84e8(c), 
                                                                                          OVR_229::800a8510(c), 
                                                                                          OVR_229::800a851c(c), 
                                                                                          OVR_229::800a8548(c), 
                                                                                          OVR_229::800a8554(c), 
                                                                                          OVR_229::800a857c(c), 
                                                                                          OVR_229::800a8588(c), 
                                                                                          OVR_229::800a8a74(c), 
                                                                                          OVR_229::800a8a80(c), 
                                                                                          OVR_229::800a8abc(c), 
                                                                                          OVR_229::800a8ac8(c), 
                                                                                          OVR_229::800a8ad4(c), 
                                                                                          OVR_229::800a8b14(c), 
                                                                                          OVR_229::800a8b20(c), 
                                                                                          OVR_229::800a8b2c(c), [more]
     9::800a85e0 10 00 a3 85     lh         v1,0x10(t5)
     9::800a85e4 10 00 c8 85     lh         t0,0x10(t6)
     9::800a85e8 23 48 c3 03     subu       t1,s8,v1
     9::800a85ec 23 50 03 01     subu       t2,t0,v1
     9::800a85f0 00 4c 09 00     sll        t1,t1,0x10
     9::800a85f4 1a 00 2a 01     div        t1,t2
     9::800a85f8 0c 00 a3 85     lh         v1,0xc(t5)
     9::800a85fc 0c 00 c8 85     lh         t0,0xc(t6)
     9::800a8600 12 50 00 00     mflo       t2
     9::800a8604 23 48 03 01     subu       t1,t0,v1
     9::800a8608 0e 00 c8 85     lh         t0,0xe(t6)
     9::800a860c 18 00 2a 01     mult       t1,t2
     9::800a8610 12 48 00 00     mflo       t1
     9::800a8614 03 4c 09 00     sra        t1,t1,0x10
     9::800a8618 21 48 23 01     addu       t1,t1,v1
     9::800a861c 0e 00 a3 85     lh         v1,0xe(t5)
     9::800a8620 00 00 e9 a5     sh         t1,0x0(t7)
     9::800a8624 23 48 03 01     subu       t1,t0,v1
     9::800a8628 18 00 2a 01     mult       t1,t2
     9::800a862c 06 00 c8 91     lbu        t0,0x6(t6)
     9::800a8630 12 48 00 00     mflo       t1
     9::800a8634 03 4c 09 00     sra        t1,t1,0x10
     9::800a8638 21 48 23 01     addu       t1,t1,v1
     9::800a863c 06 00 a3 91     lbu        v1,0x6(t5)
     9::800a8640 02 00 e9 a5     sh         t1,0x2(t7)
     9::800a8644 23 48 03 01     subu       t1,t0,v1
     9::800a8648 18 00 2a 01     mult       t1,t2
     9::800a864c 07 00 c8 91     lbu        t0,0x7(t6)
     9::800a8650 12 48 00 00     mflo       t1
     9::800a8654 03 4c 09 00     sra        t1,t1,0x10
     9::800a8658 21 48 23 01     addu       t1,t1,v1
     9::800a865c 07 00 a3 91     lbu        v1,0x7(t5)
     9::800a8660 06 00 e9 a1     sb         t1,0x6(t7)
     9::800a8664 23 48 03 01     subu       t1,t0,v1
     9::800a8668 18 00 2a 01     mult       t1,t2
     9::800a866c 08 00 c8 91     lbu        t0,0x8(t6)
     9::800a8670 12 48 00 00     mflo       t1
     9::800a8674 03 4c 09 00     sra        t1,t1,0x10
     9::800a8678 21 48 23 01     addu       t1,t1,v1
     9::800a867c 08 00 a3 91     lbu        v1,0x8(t5)
     9::800a8680 07 00 e9 a1     sb         t1,0x7(t7)
     9::800a8684 23 48 03 01     subu       t1,t0,v1
     9::800a8688 18 00 2a 01     mult       t1,t2
     9::800a868c 09 00 c8 91     lbu        t0,0x9(t6)
     9::800a8690 12 48 00 00     mflo       t1
     9::800a8694 03 4c 09 00     sra        t1,t1,0x10
     9::800a8698 21 48 23 01     addu       t1,t1,v1
     9::800a869c 09 00 a3 91     lbu        v1,0x9(t5)
     9::800a86a0 08 00 e9 a1     sb         t1,0x8(t7)
     9::800a86a4 23 48 03 01     subu       t1,t0,v1
     9::800a86a8 18 00 2a 01     mult       t1,t2
     9::800a86ac 0a 00 c8 91     lbu        t0,0xa(t6)
     9::800a86b0 12 48 00 00     mflo       t1
     9::800a86b4 03 4c 09 00     sra        t1,t1,0x10
     9::800a86b8 21 48 23 01     addu       t1,t1,v1
     9::800a86bc 0a 00 a3 91     lbu        v1,0xa(t5)
     9::800a86c0 09 00 e9 a1     sb         t1,0x9(t7)
     9::800a86c4 23 48 03 01     subu       t1,t0,v1
     9::800a86c8 18 00 2a 01     mult       t1,t2
     9::800a86cc 12 48 00 00     mflo       t1
     9::800a86d0 03 4c 09 00     sra        t1,t1,0x10
     9::800a86d4 21 48 23 01     addu       t1,t1,v1
     9::800a86d8 08 00 e0 03     jr         ra
     9::800a86dc 0a 00 e9 a1     _sb        t1,0xa(t7)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a86e0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a86e0                           XREF[15]:    OVR_229::800a8454(c), 
                                                                                          OVR_229::800a84f8(c), 
                                                                                          OVR_229::800a8564(c), 
                                                                                          OVR_229::800a8598(c), 
                                                                                          FUN_OVR_229__800a8824:800a88e4(j
                                                                                          OVR_229::800a8a90(c), 
                                                                                          OVR_229::800a8b50(c), 
                                                                                          OVR_229::800a8be8(c), 
                                                                                          OVR_229::800a8c30(c), 
                                                                                          OVR_229::800a8c5c(c), 
                                                                                          OVR_229::800a8c90(c), 
                                                                                          OVR_229::800a8cc4(c), 
                                                                                          OVR_229::800a8d80(c), 
                                                                                          OVR_229::800a8e2c(c), 
                                                                                          OVR_229::800a8ea4(c)  
     9::800a86e0 12 00 63 86     lh         v1,0x12(s3)
     9::800a86e4 12 00 88 86     lh         t0,0x12(s4)
     9::800a86e8 12 00 a9 86     lh         t1,0x12(s5)
     9::800a86ec 00 00 60 ca     gte_ldVXY0 0x0(s3)
     9::800a86f0 03 00 61 04     bgez       v1,LAB_OVR_229__800a8700
     9::800a86f4 04 00 61 ca     _gte_ldVZ0 0x4(s3)
     9::800a86f8 0c 00 60 ca     gte_ldVXY0 0xc(s3)
     9::800a86fc 10 00 61 ca     gte_ldVZ0  0x10(s3)
                             LAB_OVR_229__800a8700                           XREF[1]:     OVR_229::800a86f0(j)  
     9::800a8700 00 00 82 ca     gte_ldVXY1 0x0(s4)
     9::800a8704 03 00 01 05     bgez       t0,LAB_OVR_229__800a8714
     9::800a8708 04 00 83 ca     _gte_ldVZ1 0x4(s4)
     9::800a870c 0c 00 82 ca     gte_ldVXY1 0xc(s4)
     9::800a8710 10 00 83 ca     gte_ldVZ1  0x10(s4)
                             LAB_OVR_229__800a8714                           XREF[1]:     OVR_229::800a8704(j)  
     9::800a8714 00 00 a4 ca     gte_ldVXY2 0x0(s5)
     9::800a8718 03 00 21 05     bgez       t1,LAB_OVR_229__800a8728
     9::800a871c 04 00 a5 ca     _gte_ldVZ2 0x4(s5)
     9::800a8720 0c 00 a4 ca     gte_ldVXY2 0xc(s5)
     9::800a8724 10 00 a5 ca     gte_ldVZ2  0x10(s5)
                             LAB_OVR_229__800a8728                           XREF[1]:     OVR_229::800a8718(j)  
     9::800a8728 06 00 63 86     lh         v1,0x6(s3)
     9::800a872c 06 00 88 86     lh         t0,0x6(s4)
     9::800a8730 30 00 28 4a     RTPT
     9::800a8734 06 00 a9 86     lh         t1,0x6(s5)
     9::800a8738 a0 01 23 a4     sh         v1,0x1a0(at)
     9::800a873c a4 01 28 a4     sh         t0,0x1a4(at)
     9::800a8740 a8 01 29 a4     sh         t1,0x1a8(at)
     9::800a8744 6c 00 23 8c     lw         v1,0x6c(at)
     9::800a8748 00 60 0b        read_sxs   t3,t4,t5
                 48 00 68 
                 0c 48 00 
     9::800a8754 06 00 40 4b     NCLIP
     9::800a8758 23 78 63 01     subu       t7,t3,v1
     9::800a875c 23 80 83 01     subu       s0,t4,v1
     9::800a8760 23 88 a3 01     subu       s1,t5,v1
     9::800a8764 24 18 6c 01     and        v1,t3,t4
     9::800a8768 24 18 6d 00     and        v1,v1,t5
     9::800a876c 25 78 f0 01     or         t7,t7,s0
     9::800a8770 27 78 f1 01     nor        t7,t7,s1
     9::800a8774 25 78 e3 01     or         t7,t7,v1
     9::800a8778 28 00 e0 05     bltz       t7,LAB_OVR_229__800a881c
     9::800a877c 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a8780 26 00 e0 05     bltz       t7,LAB_OVR_229__800a881c
     9::800a8784 00 c0 0a 48     _gte_stM   t2
     9::800a8788 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a878c 23 00 40 11     beq        t2,zero,LAB_OVR_229__800a881c
     9::800a8790 40 40 09 00     _sll       t0,t1,0x1
     9::800a8794 02 00 20 05     bltz       t1,LAB_OVR_229__800a87a0
     9::800a8798 26 50 48 01     _xor       t2,t2,t0
     9::800a879c 1f 00 40 19     blez       t2,LAB_OVR_229__800a881c
                             LAB_OVR_229__800a87a0                           XREF[1]:     OVR_229::800a8794(j)  
     9::800a87a0 a4 01 28 8c     _lw        t0,0x1a4(at)
     9::800a87a4 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a87a8 08 00 90 8e     lw         s0,0x8(s4)
     9::800a87ac 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a87b0 60 00 03 3c     lui        v1,0x60
     9::800a87b4 24 48 03 01     and        t1,t0,v1
     9::800a87b8 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a87c4
     9::800a87bc 00 36 03 3c     _lui       v1,0x3600
     9::800a87c0 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_229__800a87c4                           XREF[1]:     OVR_229::800a87b8(j)  
     9::800a87c4 25 78 e3 01     or         t7,t7,v1
     9::800a87c8 a0 01 23 8c     lw         v1,0x1a0(at)
     9::800a87cc a8 01 29 8c     lw         t1,0x1a8(at)
     9::800a87d0 04 00 4f ac     sw         t7,0x4(v0)
     9::800a87d4 08 00 4b ac     sw         t3,0x8(v0)
     9::800a87d8 0c 00 43 ac     sw         v1,0xc(v0)
     9::800a87dc 10 00 50 ac     sw         s0,0x10(v0)
     9::800a87e0 14 00 4c ac     sw         t4,0x14(v0)
     9::800a87e4 18 00 48 ac     sw         t0,0x18(v0)
     9::800a87e8 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a87ec 20 00 4d ac     sw         t5,0x20(v0)
     9::800a87f0 24 00 49 ac     sw         t1,0x24(v0)
     9::800a87f4 00 09 0a 3c     lui        t2,0x900
     9::800a87f8 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a87fc 00 42 02 00     sll        t0,v0,0x8
     9::800a8800 02 42 08 00     srl        t0,t0,0x8
     9::800a8804 25 18 6a 00     or         v1,v1,t2
     9::800a8808 00 00 43 ac     sw         v1,0x0(v0)
     9::800a880c 28 00 42 24     addiu      v0,v0,0x28
     9::800a8810 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a8814 08 00 e0 03     jr         ra
     9::800a8818 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_229__800a881c                           XREF[6]:     OVR_229::800a8778(j), 
                                                                                          OVR_229::800a8780(j), 
                                                                                          OVR_229::800a878c(j), 
                                                                                          OVR_229::800a879c(j), 
                                                                                          FUN_OVR_229__800a8824:800a8918(j
                                                                                          FUN_OVR_229__800a8824:800a8920(j
     9::800a881c 08 00 e0 03     jr         ra
     9::800a8820 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a8824()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a8824                           XREF[18]:    OVR_229::800a848c(c), 
                                                                                          OVR_229::800a84c4(c), 
                                                                                          OVR_229::800a8530(c), 
                                                                                          OVR_229::800a8a5c(c), 
                                                                                          OVR_229::800a8aa4(c), 
                                                                                          OVR_229::800a8ae8(c), 
                                                                                          OVR_229::800a8afc(c), 
                                                                                          OVR_229::800a8b40(c), 
                                                                                          OVR_229::800a8b94(c), 
                                                                                          OVR_229::800a8ba8(c), 
                                                                                          OVR_229::800a8bfc(c), 
                                                                                          OVR_229::800a8cd8(c), 
                                                                                          OVR_229::800a8d10(c), 
                                                                                          OVR_229::800a8d40(c), 
                                                                                          OVR_229::800a8d94(c), 
                                                                                          OVR_229::800a8dd8(c), 
                                                                                          OVR_229::800a8e1c(c), 
                                                                                          OVR_229::800a8e70(c)  
     9::800a8824 12 00 63 86     lh         v1,0x12(s3)
     9::800a8828 12 00 88 86     lh         t0,0x12(s4)
     9::800a882c 12 00 a9 86     lh         t1,0x12(s5)
     9::800a8830 00 00 60 ca     gte_ldVXY0 0x0(s3)
     9::800a8834 03 00 61 04     bgez       v1,LAB_OVR_229__800a8844
     9::800a8838 04 00 61 ca     _gte_ldVZ0 0x4(s3)
     9::800a883c 0c 00 60 ca     gte_ldVXY0 0xc(s3)
     9::800a8840 10 00 61 ca     gte_ldVZ0  0x10(s3)
                             LAB_OVR_229__800a8844                           XREF[1]:     OVR_229::800a8834(j)  
     9::800a8844 00 00 82 ca     gte_ldVXY1 0x0(s4)
     9::800a8848 03 00 01 05     bgez       t0,LAB_OVR_229__800a8858
     9::800a884c 04 00 83 ca     _gte_ldVZ1 0x4(s4)
     9::800a8850 0c 00 82 ca     gte_ldVXY1 0xc(s4)
     9::800a8854 10 00 83 ca     gte_ldVZ1  0x10(s4)
                             LAB_OVR_229__800a8858                           XREF[1]:     OVR_229::800a8848(j)  
     9::800a8858 00 00 a4 ca     gte_ldVXY2 0x0(s5)
     9::800a885c 03 00 21 05     bgez       t1,LAB_OVR_229__800a886c
     9::800a8860 04 00 a5 ca     _gte_ldVZ2 0x4(s5)
     9::800a8864 0c 00 a4 ca     gte_ldVXY2 0xc(s5)
     9::800a8868 10 00 a5 ca     gte_ldVZ2  0x10(s5)
                             LAB_OVR_229__800a886c                           XREF[1]:     OVR_229::800a885c(j)  
     9::800a886c 06 00 63 86     lh         v1,0x6(s3)
     9::800a8870 06 00 88 86     lh         t0,0x6(s4)
     9::800a8874 30 00 28 4a     RTPT
     9::800a8878 06 00 a9 86     lh         t1,0x6(s5)
     9::800a887c a0 01 23 a4     sh         v1,0x1a0(at)
     9::800a8880 a4 01 28 a4     sh         t0,0x1a4(at)
     9::800a8884 a8 01 29 a4     sh         t1,0x1a8(at)
     9::800a8888 6c 00 23 8c     lw         v1,0x6c(at)
     9::800a888c 00 60 0b        read_sxs   t3,t4,t5
                 48 00 68 
                 0c 48 00 
     9::800a8898 06 00 40 4b     NCLIP
     9::800a889c 23 78 63 01     subu       t7,t3,v1
     9::800a88a0 23 80 83 01     subu       s0,t4,v1
     9::800a88a4 23 88 a3 01     subu       s1,t5,v1
     9::800a88a8 00 c0 0a 48     gte_stMAC0 t2
     9::800a88ac 7c 00 29 8c     lw         t1,0x7c(at)
     9::800a88b0 12 00 c3 86     lh         v1,0x12(s6)
     9::800a88b4 0a 00 40 11     beq        t2,zero,LAB_OVR_229__800a88e0
     9::800a88b8 00 00 c0 ca     _gte_ldV   0x0(s6)
     9::800a88bc 03 00 61 04     bgez       v1,LAB_OVR_229__800a88cc
     9::800a88c0 04 00 c1 ca     _gte_ldVZ0 0x4(s6)
     9::800a88c4 0c 00 c0 ca     gte_ldVXY0 0xc(s6)
     9::800a88c8 10 00 c1 ca     gte_ldVZ0  0x10(s6)
                             LAB_OVR_229__800a88cc                           XREF[1]:     OVR_229::800a88bc(j)  
     9::800a88cc 07 00 20 05     bltz       t1,LAB_OVR_229__800a88ec
     9::800a88d0 40 48 09 00     _sll       t1,t1,0x1
     9::800a88d4 26 50 49 01     xor        t2,t2,t1
     9::800a88d8 04 00 40 1d     bgtz       t2,LAB_OVR_229__800a88ec
     9::800a88dc 00 00 00 00     _nop
                             LAB_OVR_229__800a88e0                           XREF[1]:     OVR_229::800a88b4(j)  
     9::800a88e0 21 98 80 02     move       s3,s4
     9::800a88e4 7e ff 01 04     bgez       zero,FUN_OVR_229__800a86e0
     9::800a88e8 21 a0 c0 02     _move      s4,s6
                             LAB_OVR_229__800a88ec                           XREF[2]:     OVR_229::800a88cc(j), 
                                                                                          OVR_229::800a88d8(j)  
     9::800a88ec 01 00 18 4a     RTPS
     9::800a88f0 6c 00 23 8c     lw         v1,0x6c(at)
     9::800a88f4 25 78 f0 01     or         t7,t7,s0
     9::800a88f8 00 70 0e 48     gte_stSXY2 t6
     9::800a88fc 25 78 f1 01     or         t7,t7,s1
     9::800a8900 23 90 c3 01     subu       s2,t6,v1
     9::800a8904 27 78 f2 01     nor        t7,t7,s2
     9::800a8908 24 18 6c 01     and        v1,t3,t4
     9::800a890c 24 18 6d 00     and        v1,v1,t5
     9::800a8910 24 18 6e 00     and        v1,v1,t6
     9::800a8914 25 78 e3 01     or         t7,t7,v1
     9::800a8918 c0 ff e0 05     bltz       t7,LAB_OVR_229__800a881c
     9::800a891c 00 7c 0f 00     _sll       t7,t7,0x10
     9::800a8920 be ff e0 05     bltz       t7,LAB_OVR_229__800a881c
     9::800a8924 a4 01 28 8c     _lw        t0,0x1a4(at)
     9::800a8928 06 00 ca 86     lh         t2,0x6(s6)
     9::800a892c 08 00 6f 8e     lw         t7,0x8(s3)
     9::800a8930 08 00 90 8e     lw         s0,0x8(s4)
     9::800a8934 08 00 b1 8e     lw         s1,0x8(s5)
     9::800a8938 08 00 d2 8e     lw         s2,0x8(s6)
     9::800a893c 60 00 03 3c     lui        v1,0x60
     9::800a8940 24 48 03 01     and        t1,t0,v1
     9::800a8944 02 00 23 15     bne        t1,v1,LAB_OVR_229__800a8950
     9::800a8948 00 3e 03 3c     _lui       v1,0x3e00
     9::800a894c 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_229__800a8950                           XREF[1]:     OVR_229::800a8944(j)  
     9::800a8950 25 78 e3 01     or         t7,t7,v1
     9::800a8954 a0 01 23 8c     lw         v1,0x1a0(at)
     9::800a8958 a8 01 29 8c     lw         t1,0x1a8(at)
     9::800a895c 04 00 4f ac     sw         t7,0x4(v0)
     9::800a8960 08 00 4b ac     sw         t3,0x8(v0)
     9::800a8964 0c 00 43 ac     sw         v1,0xc(v0)
     9::800a8968 10 00 50 ac     sw         s0,0x10(v0)
     9::800a896c 14 00 4c ac     sw         t4,0x14(v0)
     9::800a8970 18 00 48 ac     sw         t0,0x18(v0)
     9::800a8974 1c 00 51 ac     sw         s1,0x1c(v0)
     9::800a8978 20 00 4d ac     sw         t5,0x20(v0)
     9::800a897c 24 00 49 ac     sw         t1,0x24(v0)
     9::800a8980 28 00 52 ac     sw         s2,0x28(v0)
     9::800a8984 2c 00 4e ac     sw         t6,0x2c(v0)
     9::800a8988 30 00 4a ac     sw         t2,0x30(v0)
     9::800a898c 00 0c 0a 3c     lui        t2,0xc00
     9::800a8990 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     9::800a8994 00 42 02 00     sll        t0,v0,0x8
     9::800a8998 02 42 08 00     srl        t0,t0,0x8
     9::800a899c 25 18 6a 00     or         v1,v1,t2
     9::800a89a0 00 00 43 ac     sw         v1,0x0(v0)
     9::800a89a4 34 00 42 24     addiu      v0,v0,0x34
     9::800a89a8 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     9::800a89ac 08 00 e0 03     jr         ra
     9::800a89b0 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_229__800a89b4                           XREF[1]:     OVR_229::800a83f4(j)  
     9::800a89b4 30 00 e0 ca     gte_ldVXY0 0x30(s7)
     9::800a89b8 34 00 e1 ca     gte_ldVZ0  0x34(s7)
     9::800a89bc 36 00 e3 86     lh         v1,0x36(s7)
     9::800a89c0 38 00 e8 8e     lw         t0,0x38(s7)
     9::800a89c4 12 20 4a 4a     LLV0BK
     9::800a89c8 f6 01 23 a4     sh         v1,0x1f6(at)
     9::800a89cc f8 01 28 ac     sw         t0,0x1f8(at)
     9::800a89d0 00 48 0b 48     gte_stIR1  t3
     9::800a89d4 00 50 0c 48     gte_stIR2  t4
     9::800a89d8 00 58 0d 48     gte_stIR3  t5
     9::800a89dc f0 01 2b a4     sh         t3,0x1f0(at)
     9::800a89e0 f2 01 2c a4     sh         t4,0x1f2(at)
     9::800a89e4 f4 01 2d a4     sh         t5,0x1f4(at)
     9::800a89e8 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a89ec b4 01 2d 24     _addiu     t5,at,0x1b4
     9::800a89f0 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a89f4 c8 01 2d 24     _addiu     t5,at,0x1c8
     9::800a89f8 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a89fc dc 01 2d 24     _addiu     t5,at,0x1dc
     9::800a8a00 6c a1 02 0c     jal        FUN_OVR_229__800a85b0                            undefined FUN_OVR_229__800a85b0()
     9::800a8a04 f0 01 2d 24     _addiu     t5,at,0x1f0
     9::800a8a08 bf 01 23 80     lb         v1,0x1bf(at)
     9::800a8a0c d3 01 28 80     lb         t0,0x1d3(at)
     9::800a8a10 e7 01 29 80     lb         t1,0x1e7(at)
     9::800a8a14 fb 01 2a 80     lb         t2,0x1fb(at)
     9::800a8a18 80 18 03 00     sll        v1,v1,0x2
     9::800a8a1c c0 40 08 00     sll        t0,t0,0x3
     9::800a8a20 00 49 09 00     sll        t1,t1,0x4
     9::800a8a24 40 51 0a 00     sll        t2,t2,0x5
     9::800a8a28 25 18 68 00     or         v1,v1,t0
     9::800a8a2c 25 18 69 00     or         v1,v1,t1
     9::800a8a30 25 18 6a 00     or         v1,v1,t2
     9::800a8a34 21 18 61 00     addu       v1,v1,at
     9::800a8a38 60 02 63 8c     lw         v1,0x260(v1)
     9::800a8a3c bf 01 20 a0     sb         zero,0x1bf(at)
     9::800a8a40 d3 01 20 a0     sb         zero,0x1d3(at)
     9::800a8a44 e7 01 20 a0     sb         zero,0x1e7(at)
     9::800a8a48 08 00 60 00     jr         v1
     9::800a8a4c fb 01 20 a0     _sb        zero,0x1fb(at)
     9::800a8a50 b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8a54 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8a58 dc 01 35 24     addiu      s5,at,0x1dc
     9::800a8a5c 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8a60 f0 01 36 24     _addiu     s6,at,0x1f0
     9::800a8a64 30 fe 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8a68 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8a6c c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8a70 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8a74 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8a78 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8a7c dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8a80 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8a84 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8a88 f0 01 33 24     addiu      s3,at,0x1f0
     9::800a8a8c dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8a90 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8a94 c8 01 35 24     _addiu     s5,at,0x1c8
     9::800a8a98 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8a9c dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8aa0 04 02 35 24     addiu      s5,at,0x204
     9::800a8aa4 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8aa8 18 02 36 24     _addiu     s6,at,0x218
     9::800a8aac 1e fe 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8ab0 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8ab4 f0 01 2d 24     addiu      t5,at,0x1f0
     9::800a8ab8 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8abc 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8ac0 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8ac4 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8ac8 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8acc 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8ad0 b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8ad4 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8ad8 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8adc f0 01 33 24     addiu      s3,at,0x1f0
     9::800a8ae0 dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8ae4 04 02 35 24     addiu      s5,at,0x204
     9::800a8ae8 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8aec 18 02 36 24     _addiu     s6,at,0x218
     9::800a8af0 dc 01 33 24     addiu      s3,at,0x1dc
     9::800a8af4 b4 01 34 24     addiu      s4,at,0x1b4
     9::800a8af8 18 02 35 24     addiu      s5,at,0x218
     9::800a8afc 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8b00 2c 02 36 24     _addiu     s6,at,0x22c
     9::800a8b04 08 fe 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8b08 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8b0c f0 01 2d 24     addiu      t5,at,0x1f0
     9::800a8b10 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8b14 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8b18 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8b1c dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8b20 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8b24 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8b28 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8b2c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8b30 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8b34 f0 01 33 24     addiu      s3,at,0x1f0
     9::800a8b38 dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8b3c 04 02 35 24     addiu      s5,at,0x204
     9::800a8b40 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8b44 18 02 36 24     _addiu     s6,at,0x218
     9::800a8b48 dc 01 33 24     addiu      s3,at,0x1dc
     9::800a8b4c 2c 02 34 24     addiu      s4,at,0x22c
     9::800a8b50 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8b54 18 02 35 24     _addiu     s5,at,0x218
     9::800a8b58 f3 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8b5c 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8b60 b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8b64 dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8b68 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8b6c 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8b70 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8b74 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8b78 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8b7c f0 01 2d 24     addiu      t5,at,0x1f0
     9::800a8b80 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8b84 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8b88 b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8b8c c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8b90 04 02 35 24     addiu      s5,at,0x204
     9::800a8b94 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8b98 18 02 36 24     _addiu     s6,at,0x218
     9::800a8b9c c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8ba0 f0 01 34 24     addiu      s4,at,0x1f0
     9::800a8ba4 18 02 35 24     addiu      s5,at,0x218
     9::800a8ba8 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8bac 2c 02 36 24     _addiu     s6,at,0x22c
     9::800a8bb0 dd fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8bb4 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8bb8 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8bbc b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8bc0 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8bc4 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8bc8 dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8bcc 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8bd0 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8bd4 f0 01 2d 24     addiu      t5,at,0x1f0
     9::800a8bd8 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8bdc 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8be0 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8be4 18 02 34 24     addiu      s4,at,0x218
     9::800a8be8 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8bec 04 02 35 24     _addiu     s5,at,0x204
     9::800a8bf0 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8bf4 f0 01 34 24     addiu      s4,at,0x1f0
     9::800a8bf8 18 02 35 24     addiu      s5,at,0x218
     9::800a8bfc 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8c00 2c 02 36 24     _addiu     s6,at,0x22c
     9::800a8c04 c8 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8c08 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8c0c b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8c10 dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8c14 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8c18 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8c1c c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8c20 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8c24 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8c28 b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8c2c 18 02 34 24     addiu      s4,at,0x218
     9::800a8c30 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8c34 04 02 35 24     _addiu     s5,at,0x204
     9::800a8c38 f0 01 2d 24     addiu      t5,at,0x1f0
     9::800a8c3c dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8c40 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8c44 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8c48 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8c4c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8c50 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8c54 f0 01 33 24     addiu      s3,at,0x1f0
     9::800a8c58 18 02 34 24     addiu      s4,at,0x218
     9::800a8c5c b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8c60 04 02 35 24     _addiu     s5,at,0x204
     9::800a8c64 b0 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8c68 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8c6c f0 01 2d 24     addiu      t5,at,0x1f0
     9::800a8c70 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8c74 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8c78 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8c7c dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8c80 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8c84 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8c88 f0 01 33 24     addiu      s3,at,0x1f0
     9::800a8c8c 18 02 34 24     addiu      s4,at,0x218
     9::800a8c90 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8c94 04 02 35 24     _addiu     s5,at,0x204
     9::800a8c98 a3 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8c9c 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8ca0 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8ca4 f0 01 2e 24     addiu      t6,at,0x1f0
     9::800a8ca8 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8cac 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8cb0 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8cb4 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8cb8 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8cbc b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8cc0 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8cc4 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8cc8 dc 01 35 24     _addiu     s5,at,0x1dc
     9::800a8ccc dc 01 33 24     addiu      s3,at,0x1dc
     9::800a8cd0 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8cd4 04 02 35 24     addiu      s5,at,0x204
     9::800a8cd8 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8cdc 18 02 36 24     _addiu     s6,at,0x218
     9::800a8ce0 91 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8ce4 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8ce8 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8cec b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8cf0 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8cf4 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8cf8 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8cfc 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8d00 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8d04 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8d08 dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8d0c 04 02 35 24     addiu      s5,at,0x204
     9::800a8d10 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8d14 18 02 36 24     _addiu     s6,at,0x218
     9::800a8d18 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8d1c f0 01 2e 24     addiu      t6,at,0x1f0
     9::800a8d20 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8d24 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8d28 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8d2c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8d30 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8d34 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8d38 dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8d3c 04 02 35 24     addiu      s5,at,0x204
     9::800a8d40 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8d44 18 02 36 24     _addiu     s6,at,0x218
     9::800a8d48 77 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8d4c 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8d50 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8d54 f0 01 2e 24     addiu      t6,at,0x1f0
     9::800a8d58 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8d5c 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8d60 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8d64 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8d68 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8d6c b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8d70 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8d74 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8d78 dc 01 33 24     addiu      s3,at,0x1dc
     9::800a8d7c 18 02 34 24     addiu      s4,at,0x218
     9::800a8d80 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8d84 04 02 35 24     _addiu     s5,at,0x204
     9::800a8d88 dc 01 33 24     addiu      s3,at,0x1dc
     9::800a8d8c b4 01 34 24     addiu      s4,at,0x1b4
     9::800a8d90 18 02 35 24     addiu      s5,at,0x218
     9::800a8d94 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8d98 2c 02 36 24     _addiu     s6,at,0x22c
     9::800a8d9c 62 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8da0 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8da4 dc 01 2d 24     addiu      t5,at,0x1dc
     9::800a8da8 f0 01 2e 24     addiu      t6,at,0x1f0
     9::800a8dac 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8db0 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8db4 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8db8 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8dbc 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8dc0 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8dc4 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8dc8 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8dcc 04 02 33 24     addiu      s3,at,0x204
     9::800a8dd0 dc 01 34 24     addiu      s4,at,0x1dc
     9::800a8dd4 18 02 35 24     addiu      s5,at,0x218
     9::800a8dd8 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8ddc 2c 02 36 24     _addiu     s6,at,0x22c
     9::800a8de0 51 fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8de4 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8de8 b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8dec dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8df0 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8df4 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8df8 c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8dfc 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e00 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8e04 f0 01 2e 24     addiu      t6,at,0x1f0
     9::800a8e08 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e0c 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8e10 b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8e14 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8e18 04 02 35 24     addiu      s5,at,0x204
     9::800a8e1c 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8e20 18 02 36 24     _addiu     s6,at,0x218
     9::800a8e24 c8 01 33 24     addiu      s3,at,0x1c8
     9::800a8e28 2c 02 34 24     addiu      s4,at,0x22c
     9::800a8e2c b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8e30 18 02 35 24     _addiu     s5,at,0x218
     9::800a8e34 3c fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8e38 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8e3c c8 01 2d 24     addiu      t5,at,0x1c8
     9::800a8e40 b4 01 2e 24     addiu      t6,at,0x1b4
     9::800a8e44 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e48 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8e4c dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8e50 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e54 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8e58 f0 01 2e 24     addiu      t6,at,0x1f0
     9::800a8e5c 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e60 2c 02 2f 24     _addiu     t7,at,0x22c
     9::800a8e64 04 02 33 24     addiu      s3,at,0x204
     9::800a8e68 c8 01 34 24     addiu      s4,at,0x1c8
     9::800a8e6c 18 02 35 24     addiu      s5,at,0x218
     9::800a8e70 09 a2 02 0c     jal        FUN_OVR_229__800a8824                            undefined FUN_OVR_229__800a8824()
     9::800a8e74 2c 02 36 24     _addiu     s6,at,0x22c
     9::800a8e78 2b fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8e7c 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8e80 b4 01 2d 24     addiu      t5,at,0x1b4
     9::800a8e84 dc 01 2e 24     addiu      t6,at,0x1dc
     9::800a8e88 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e8c 04 02 2f 24     _addiu     t7,at,0x204
     9::800a8e90 c8 01 2e 24     addiu      t6,at,0x1c8
     9::800a8e94 78 a1 02 0c     jal        FUN_OVR_229__800a85e0                            undefined FUN_OVR_229__800a85e0()
     9::800a8e98 18 02 2f 24     _addiu     t7,at,0x218
     9::800a8e9c b4 01 33 24     addiu      s3,at,0x1b4
     9::800a8ea0 18 02 34 24     addiu      s4,at,0x218
     9::800a8ea4 b8 a1 02 0c     jal        FUN_OVR_229__800a86e0                            undefined FUN_OVR_229__800a86e0()
     9::800a8ea8 04 02 35 24     _addiu     s5,at,0x204
     9::800a8eac 1e fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8eb0 3c 00 f7 26     _addiu     s7,s7,0x3c
     9::800a8eb4 1c fd 01 04     bgez       zero,LAB_OVR_229__800a8328
     9::800a8eb8 3c 00 f7 26     _addiu     s7,s7,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_229__800a8ebc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_229__800a8ebc                           XREF[1]:     OVR_229::800a0fc8(c)  
     9::800a8ebc 0b 80 03 3c     lui        v1,0x800b
     9::800a8ec0 ac 92 63 24     addiu      v1,v1,-0x6d54
     9::800a8ec4 40 02 28 24     addiu      t0,at,0x240
     9::800a8ec8 18 00 09 24     li         t1,0x18
                             LAB_OVR_229__800a8ecc                           XREF[1]:     OVR_229::800a8edc(j)  
     9::800a8ecc 00 00 6a 8c     lw         t2,0x0(v1)=>PTR_LAB_OVR_229__800a844c_OVR_229_   = OVR_229::800a8464
                                                                                             = OVR_229::800a844c
     9::800a8ed0 04 00 63 24     addiu      v1,v1,0x4
     9::800a8ed4 00 00 0a ad     sw         t2=>LAB_OVR_229__800a844c,0x0(t0)
     9::800a8ed8 04 00 08 25     addiu      t0,t0,0x4
     9::800a8edc fb ff 20 15     bne        t1,zero,LAB_OVR_229__800a8ecc
     9::800a8ee0 ff ff 29 25     _addiu     t1,t1,-0x1
     9::800a8ee4 08 00 e0 03     jr         ra
     9::800a8ee8 00 00 00 00     _nop
                             DAT_OVR_229__800a8eec                           XREF[1]:     FUN_OVR_229__800a106c:800a1078(R
     9::800a8eec 80              ??         80h                                              ?  ->  OVR_229::800a9180
     9::800a8eed 91              ??         91h
     9::800a8eee 0a              ??         0Ah
     9::800a8eef 80              ??         80h
     9::800a8ef0 1c              ??         1Ch                                              ?  ->  OVR_229::800a911c
     9::800a8ef1 91              ??         91h
     9::800a8ef2 0a              ??         0Ah
     9::800a8ef3 80              ??         80h
     9::800a8ef4 b8              ??         B8h                                              ?  ->  OVR_229::800a90b8
     9::800a8ef5 90              ??         90h
     9::800a8ef6 0a              ??         0Ah
     9::800a8ef7 80              ??         80h
     9::800a8ef8 54              ??         54h    T                                         ?  ->  OVR_229::800a9054
     9::800a8ef9 90              ??         90h
     9::800a8efa 0a              ??         0Ah
     9::800a8efb 80              ??         80h
     9::800a8efc f0              ??         F0h                                              ?  ->  OVR_229::800a8ff0
     9::800a8efd 8f              ??         8Fh
     9::800a8efe 0a              ??         0Ah
     9::800a8eff 80              ??         80h
     9::800a8f00 8c              ??         8Ch                                              ?  ->  OVR_229::800a8f8c
     9::800a8f01 8f              ??         8Fh
     9::800a8f02 0a              ??         0Ah
     9::800a8f03 80              ??         80h
     9::800a8f04 48              ??         48h    H                                         ?  ->  OVR_229::800a9248
     9::800a8f05 92              ??         92h
     9::800a8f06 0a              ??         0Ah
     9::800a8f07 80              ??         80h
                             PTR_DAT_OVR_229__800a91e4_OVR_229__800a8f08     XREF[1]:     FUN_OVR_229__800a106c:800a1078(R
     9::800a8f08 e4 91 0a 80     addr       DAT_OVR_229__800a91e4                            = 0000000Eh
                             DAT_OVR_229__800a8f0c                           XREF[1]:     FUN_OVR_229__800a106c:800a1088(R
     9::800a8f0c ac              ??         ACh                                              ?  ->  OVR_229::800a56ac
     9::800a8f0d 56              ??         56h    V
     9::800a8f0e 0a              ??         0Ah
     9::800a8f0f 80              ??         80h
     9::800a8f10 1c              ??         1Ch                                              ?  ->  OVR_229::800a481c
     9::800a8f11 48              ??         48h    H
     9::800a8f12 0a              ??         0Ah
     9::800a8f13 80              ??         80h
     9::800a8f14 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a386c
     9::800a8f15 38              ??         38h    8
     9::800a8f16 0a              ??         0Ah
     9::800a8f17 80              ??         80h
     9::800a8f18 dc              ??         DCh                                              ?  ->  OVR_229::800a29dc
     9::800a8f19 29              ??         29h    )
     9::800a8f1a 0a              ??         0Ah
     9::800a8f1b 80              ??         80h
     9::800a8f1c 3c              ??         3Ch    <                                         ?  ->  OVR_229::800a1c3c
     9::800a8f1d 1c              ??         1Ch
     9::800a8f1e 0a              ??         0Ah
     9::800a8f1f 80              ??         80h
     9::800a8f20 78              ??         78h    x                                         ?  ->  OVR_229::800a1178
     9::800a8f21 11              ??         11h
     9::800a8f22 0a              ??         0Ah
     9::800a8f23 80              ??         80h
     9::800a8f24 b0              ??         B0h                                              ?  ->  OVR_229::800a72b0
     9::800a8f25 72              ??         72h    r
     9::800a8f26 0a              ??         0Ah
     9::800a8f27 80              ??         80h
                             PTR_LAB_OVR_229__800a665c_OVR_229__800a8f28     XREF[1]:     FUN_OVR_229__800a106c:800a1088(R
     9::800a8f28 5c 66 0a 80     addr       LAB_OVR_229__800a665c
                             DAT_OVR_229__800a8f2c                           XREF[1]:     OVR_229::800a0db0(R)  
     9::800a8f2c 00 08 10 18     undefined4 18100800h
                             DAT_OVR_229__800a8f30                           XREF[1]:     OVR_229::800a0db0(R)  
     9::800a8f30 18 08 90 80     undefined4 80900818h
     9::800a8f34 18              ??         18h
     9::800a8f35 10              ??         10h
     9::800a8f36 08              ??         08h
     9::800a8f37 00              ??         00h
     9::800a8f38 00              ??         00h
     9::800a8f39 10              ??         10h
     9::800a8f3a 88              ??         88h
     9::800a8f3b 98              ??         98h
     9::800a8f3c 00              ??         00h
     9::800a8f3d 10              ??         10h
     9::800a8f3e 08              ??         08h
     9::800a8f3f 98              ??         98h
     9::800a8f40 18              ??         18h
     9::800a8f41 10              ??         10h
     9::800a8f42 88              ??         88h
     9::800a8f43 00              ??         00h
     9::800a8f44 18              ??         18h                                              ?  ->  80100818
     9::800a8f45 08              ??         08h
     9::800a8f46 10              ??         10h
     9::800a8f47 80              ??         80h
     9::800a8f48 00              ??         00h
     9::800a8f49 08              ??         08h
     9::800a8f4a 90              ??         90h
     9::800a8f4b 18              ??         18h
     9::800a8f4c 98              ??         98h
     9::800a8f4d 18              ??         18h
     9::800a8f4e 08              ??         08h
     9::800a8f4f 10              ??         10h
     9::800a8f50 10              ??         10h
     9::800a8f51 18              ??         18h
     9::800a8f52 88              ??         88h
     9::800a8f53 88              ??         88h
     9::800a8f54 10              ??         10h
     9::800a8f55 08              ??         08h
     9::800a8f56 18              ??         18h
     9::800a8f57 18              ??         18h
     9::800a8f58 88              ??         88h
     9::800a8f59 08              ??         08h
     9::800a8f5a 98              ??         98h
     9::800a8f5b 90              ??         90h
     9::800a8f5c 88              ??         88h
     9::800a8f5d 08              ??         08h
     9::800a8f5e 18              ??         18h
     9::800a8f5f 90              ??         90h
     9::800a8f60 10              ??         10h
     9::800a8f61 08              ??         08h
     9::800a8f62 98              ??         98h
     9::800a8f63 18              ??         18h
     9::800a8f64 10              ??         10h
     9::800a8f65 18              ??         18h
     9::800a8f66 08              ??         08h
     9::800a8f67 88              ??         88h
     9::800a8f68 98              ??         98h
     9::800a8f69 18              ??         18h
     9::800a8f6a 88              ??         88h
     9::800a8f6b 10              ??         10h
     9::800a8f6c 90              ??         90h
     9::800a8f6d 10              ??         10h
     9::800a8f6e 18              ??         18h
     9::800a8f6f 08              ??         08h
     9::800a8f70 08              ??         08h
     9::800a8f71 10              ??         10h
     9::800a8f72 98              ??         98h
     9::800a8f73 98              ??         98h
     9::800a8f74 08              ??         08h
     9::800a8f75 18              ??         18h
     9::800a8f76 10              ??         10h
     9::800a8f77 10              ??         10h
     9::800a8f78 98              ??         98h
     9::800a8f79 18              ??         18h
     9::800a8f7a 90              ??         90h
     9::800a8f7b 88              ??         88h
     9::800a8f7c 98              ??         98h
     9::800a8f7d 18              ??         18h
     9::800a8f7e 10              ??         10h
     9::800a8f7f 88              ??         88h
     9::800a8f80 08              ??         08h
     9::800a8f81 18              ??         18h
     9::800a8f82 90              ??         90h
     9::800a8f83 10              ??         10h
     9::800a8f84 08              ??         08h
     9::800a8f85 10              ??         10h
     9::800a8f86 18              ??         18h
     9::800a8f87 98              ??         98h
     9::800a8f88 90              ??         90h
     9::800a8f89 10              ??         10h
     9::800a8f8a 98              ??         98h
     9::800a8f8b 08              ??         08h
     9::800a8f8c 0e              ??         0Eh
     9::800a8f8d 00              ??         00h
     9::800a8f8e 00              ??         00h
     9::800a8f8f 00              ??         00h
     9::800a8f90 a8              ??         A8h                                              ?  ->  OVR_229::800a8fa8
     9::800a8f91 8f              ??         8Fh
     9::800a8f92 0a              ??         0Ah
     9::800a8f93 80              ??         80h
     9::800a8f94 4c              ??         4Ch    L
     9::800a8f95 01              ??         01h
     9::800a8f96 00              ??         00h
     9::800a8f97 00              ??         00h
     9::800a8f98 02              ??         02h
     9::800a8f99 00              ??         00h
     9::800a8f9a 00              ??         00h
     9::800a8f9b 00              ??         00h
     9::800a8f9c e4              ??         E4h                                              ?  ->  OVR_229::800a8fe4
     9::800a8f9d 8f              ??         8Fh
     9::800a8f9e 0a              ??         0Ah
     9::800a8f9f 80              ??         80h
     9::800a8fa0 88              ??         88h
     9::800a8fa1 01              ??         01h
     9::800a8fa2 00              ??         00h
     9::800a8fa3 00              ??         00h
     9::800a8fa4 00              ??         00h
     9::800a8fa5 00              ??         00h
     9::800a8fa6 00              ??         00h
     9::800a8fa7 00              ??         00h
     9::800a8fa8 80              ??         80h                                              ?  ->  OVR_229::800a1680
     9::800a8fa9 16              ??         16h
     9::800a8faa 0a              ??         0Ah
     9::800a8fab 80              ??         80h
     9::800a8fac c0              ??         C0h                                              ?  ->  OVR_229::800a16c0
     9::800a8fad 16              ??         16h
     9::800a8fae 0a              ??         0Ah
     9::800a8faf 80              ??         80h
     9::800a8fb0 40              ??         40h    @                                         ?  ->  OVR_229::800a1740
     9::800a8fb1 17              ??         17h
     9::800a8fb2 0a              ??         0Ah
     9::800a8fb3 80              ??         80h
     9::800a8fb4 e0              ??         E0h                                              ?  ->  OVR_229::800a16e0
     9::800a8fb5 16              ??         16h
     9::800a8fb6 0a              ??         0Ah
     9::800a8fb7 80              ??         80h
     9::800a8fb8 68              ??         68h    h                                         ?  ->  OVR_229::800a1768
     9::800a8fb9 17              ??         17h
     9::800a8fba 0a              ??         0Ah
     9::800a8fbb 80              ??         80h
     9::800a8fbc e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fbd 17              ??         17h
     9::800a8fbe 0a              ??         0Ah
     9::800a8fbf 80              ??         80h
     9::800a8fc0 e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fc1 17              ??         17h
     9::800a8fc2 0a              ??         0Ah
     9::800a8fc3 80              ??         80h
     9::800a8fc4 00              ??         00h                                              ?  ->  OVR_229::800a1700
     9::800a8fc5 17              ??         17h
     9::800a8fc6 0a              ??         0Ah
     9::800a8fc7 80              ??         80h
     9::800a8fc8 e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fc9 17              ??         17h
     9::800a8fca 0a              ??         0Ah
     9::800a8fcb 80              ??         80h
     9::800a8fcc 90              ??         90h                                              ?  ->  OVR_229::800a1790
     9::800a8fcd 17              ??         17h
     9::800a8fce 0a              ??         0Ah
     9::800a8fcf 80              ??         80h
     9::800a8fd0 e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fd1 17              ??         17h
     9::800a8fd2 0a              ??         0Ah
     9::800a8fd3 80              ??         80h
     9::800a8fd4 b8              ??         B8h                                              ?  ->  OVR_229::800a17b8
     9::800a8fd5 17              ??         17h
     9::800a8fd6 0a              ??         0Ah
     9::800a8fd7 80              ??         80h
     9::800a8fd8 e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fd9 17              ??         17h
     9::800a8fda 0a              ??         0Ah
     9::800a8fdb 80              ??         80h
     9::800a8fdc e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fdd 17              ??         17h
     9::800a8fde 0a              ??         0Ah
     9::800a8fdf 80              ??         80h
     9::800a8fe0 e0              ??         E0h                                              ?  ->  OVR_229::800a17e0
     9::800a8fe1 17              ??         17h
     9::800a8fe2 0a              ??         0Ah
     9::800a8fe3 80              ??         80h
     9::800a8fe4 14              ??         14h                                              ?  ->  OVR_229::800a1b14
     9::800a8fe5 1b              ??         1Bh
     9::800a8fe6 0a              ??         0Ah
     9::800a8fe7 80              ??         80h
     9::800a8fe8 0c              ??         0Ch                                              ?  ->  OVR_229::800a1b0c
     9::800a8fe9 1b              ??         1Bh
     9::800a8fea 0a              ??         0Ah
     9::800a8feb 80              ??         80h
     9::800a8fec 88              ??         88h                                              ?  ->  OVR_229::800a1b88
     9::800a8fed 1b              ??         1Bh
     9::800a8fee 0a              ??         0Ah
     9::800a8fef 80              ??         80h
     9::800a8ff0 0e              ??         0Eh
     9::800a8ff1 00              ??         00h
     9::800a8ff2 00              ??         00h
     9::800a8ff3 00              ??         00h
     9::800a8ff4 0c              ??         0Ch                                              ?  ->  OVR_229::800a900c
     9::800a8ff5 90              ??         90h
     9::800a8ff6 0a              ??         0Ah
     9::800a8ff7 80              ??         80h
     9::800a8ff8 4c              ??         4Ch    L
     9::800a8ff9 01              ??         01h
     9::800a8ffa 00              ??         00h
     9::800a8ffb 00              ??         00h
     9::800a8ffc 02              ??         02h
     9::800a8ffd 00              ??         00h
     9::800a8ffe 00              ??         00h
     9::800a8fff 00              ??         00h
     9::800a9000 48              ??         48h    H                                         ?  ->  OVR_229::800a9048
     9::800a9001 90              ??         90h
     9::800a9002 0a              ??         0Ah
     9::800a9003 80              ??         80h
     9::800a9004 88              ??         88h
     9::800a9005 01              ??         01h
     9::800a9006 00              ??         00h
     9::800a9007 00              ??         00h
     9::800a9008 00              ??         00h
     9::800a9009 00              ??         00h
     9::800a900a 00              ??         00h
     9::800a900b 00              ??         00h
     9::800a900c 78              ??         78h    x                                         ?  ->  OVR_229::800a2178
     9::800a900d 21              ??         21h    !
     9::800a900e 0a              ??         0Ah
     9::800a900f 80              ??         80h
     9::800a9010 b8              ??         B8h                                              ?  ->  OVR_229::800a21b8
     9::800a9011 21              ??         21h    !
     9::800a9012 0a              ??         0Ah
     9::800a9013 80              ??         80h
     9::800a9014 38              ??         38h    8                                         ?  ->  OVR_229::800a2238
     9::800a9015 22              ??         22h    "
     9::800a9016 0a              ??         0Ah
     9::800a9017 80              ??         80h
     9::800a9018 d8              ??         D8h                                              ?  ->  OVR_229::800a21d8
     9::800a9019 21              ??         21h    !
     9::800a901a 0a              ??         0Ah
     9::800a901b 80              ??         80h
     9::800a901c 60              ??         60h    `                                         ?  ->  OVR_229::800a2260
     9::800a901d 22              ??         22h    "
     9::800a901e 0a              ??         0Ah
     9::800a901f 80              ??         80h
     9::800a9020 d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a9021 22              ??         22h    "
     9::800a9022 0a              ??         0Ah
     9::800a9023 80              ??         80h
     9::800a9024 d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a9025 22              ??         22h    "
     9::800a9026 0a              ??         0Ah
     9::800a9027 80              ??         80h
     9::800a9028 f8              ??         F8h                                              ?  ->  OVR_229::800a21f8
     9::800a9029 21              ??         21h    !
     9::800a902a 0a              ??         0Ah
     9::800a902b 80              ??         80h
     9::800a902c d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a902d 22              ??         22h    "
     9::800a902e 0a              ??         0Ah
     9::800a902f 80              ??         80h
     9::800a9030 88              ??         88h                                              ?  ->  OVR_229::800a2288
     9::800a9031 22              ??         22h    "
     9::800a9032 0a              ??         0Ah
     9::800a9033 80              ??         80h
     9::800a9034 d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a9035 22              ??         22h    "
     9::800a9036 0a              ??         0Ah
     9::800a9037 80              ??         80h
     9::800a9038 b0              ??         B0h                                              ?  ->  OVR_229::800a22b0
     9::800a9039 22              ??         22h    "
     9::800a903a 0a              ??         0Ah
     9::800a903b 80              ??         80h
     9::800a903c d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a903d 22              ??         22h    "
     9::800a903e 0a              ??         0Ah
     9::800a903f 80              ??         80h
     9::800a9040 d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a9041 22              ??         22h    "
     9::800a9042 0a              ??         0Ah
     9::800a9043 80              ??         80h
     9::800a9044 d8              ??         D8h                                              ?  ->  OVR_229::800a22d8
     9::800a9045 22              ??         22h    "
     9::800a9046 0a              ??         0Ah
     9::800a9047 80              ??         80h
     9::800a9048 70              ??         70h    p                                         ?  ->  OVR_229::800a2670
     9::800a9049 26              ??         26h    &
     9::800a904a 0a              ??         0Ah
     9::800a904b 80              ??         80h
     9::800a904c 68              ??         68h    h                                         ?  ->  OVR_229::800a2668
     9::800a904d 26              ??         26h    &
     9::800a904e 0a              ??         0Ah
     9::800a904f 80              ??         80h
     9::800a9050 14              ??         14h                                              ?  ->  OVR_229::800a2714
     9::800a9051 27              ??         27h    '
     9::800a9052 0a              ??         0Ah
     9::800a9053 80              ??         80h
     9::800a9054 0e              ??         0Eh
     9::800a9055 00              ??         00h
     9::800a9056 00              ??         00h
     9::800a9057 00              ??         00h
     9::800a9058 70              ??         70h    p                                         ?  ->  OVR_229::800a9070
     9::800a9059 90              ??         90h
     9::800a905a 0a              ??         0Ah
     9::800a905b 80              ??         80h
     9::800a905c 4c              ??         4Ch    L
     9::800a905d 01              ??         01h
     9::800a905e 00              ??         00h
     9::800a905f 00              ??         00h
     9::800a9060 02              ??         02h
     9::800a9061 00              ??         00h
     9::800a9062 00              ??         00h
     9::800a9063 00              ??         00h
     9::800a9064 ac              ??         ACh                                              ?  ->  OVR_229::800a90ac
     9::800a9065 90              ??         90h
     9::800a9066 0a              ??         0Ah
     9::800a9067 80              ??         80h
     9::800a9068 88              ??         88h
     9::800a9069 01              ??         01h
     9::800a906a 00              ??         00h
     9::800a906b 00              ??         00h
     9::800a906c 00              ??         00h
     9::800a906d 00              ??         00h
     9::800a906e 00              ??         00h
     9::800a906f 00              ??         00h
     9::800a9070 68              ??         68h    h                                         ?  ->  OVR_229::800a2f68
     9::800a9071 2f              ??         2Fh    /
     9::800a9072 0a              ??         0Ah
     9::800a9073 80              ??         80h
     9::800a9074 a8              ??         A8h                                              ?  ->  OVR_229::800a2fa8
     9::800a9075 2f              ??         2Fh    /
     9::800a9076 0a              ??         0Ah
     9::800a9077 80              ??         80h
     9::800a9078 28              ??         28h    (                                         ?  ->  OVR_229::800a3028
     9::800a9079 30              ??         30h    0
     9::800a907a 0a              ??         0Ah
     9::800a907b 80              ??         80h
     9::800a907c c8              ??         C8h                                              ?  ->  OVR_229::800a2fc8
     9::800a907d 2f              ??         2Fh    /
     9::800a907e 0a              ??         0Ah
     9::800a907f 80              ??         80h
     9::800a9080 50              ??         50h    P                                         ?  ->  OVR_229::800a3050
     9::800a9081 30              ??         30h    0
     9::800a9082 0a              ??         0Ah
     9::800a9083 80              ??         80h
     9::800a9084 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a9085 30              ??         30h    0
     9::800a9086 0a              ??         0Ah
     9::800a9087 80              ??         80h
     9::800a9088 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a9089 30              ??         30h    0
     9::800a908a 0a              ??         0Ah
     9::800a908b 80              ??         80h
     9::800a908c e8              ??         E8h                                              ?  ->  OVR_229::800a2fe8
     9::800a908d 2f              ??         2Fh    /
     9::800a908e 0a              ??         0Ah
     9::800a908f 80              ??         80h
     9::800a9090 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a9091 30              ??         30h    0
     9::800a9092 0a              ??         0Ah
     9::800a9093 80              ??         80h
     9::800a9094 78              ??         78h    x                                         ?  ->  OVR_229::800a3078
     9::800a9095 30              ??         30h    0
     9::800a9096 0a              ??         0Ah
     9::800a9097 80              ??         80h
     9::800a9098 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a9099 30              ??         30h    0
     9::800a909a 0a              ??         0Ah
     9::800a909b 80              ??         80h
     9::800a909c a0              ??         A0h                                              ?  ->  OVR_229::800a30a0
     9::800a909d 30              ??         30h    0
     9::800a909e 0a              ??         0Ah
     9::800a909f 80              ??         80h
     9::800a90a0 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a90a1 30              ??         30h    0
     9::800a90a2 0a              ??         0Ah
     9::800a90a3 80              ??         80h
     9::800a90a4 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a90a5 30              ??         30h    0
     9::800a90a6 0a              ??         0Ah
     9::800a90a7 80              ??         80h
     9::800a90a8 c8              ??         C8h                                              ?  ->  OVR_229::800a30c8
     9::800a90a9 30              ??         30h    0
     9::800a90aa 0a              ??         0Ah
     9::800a90ab 80              ??         80h
     9::800a90ac 24              ??         24h    $                                         ?  ->  OVR_229::800a3724
     9::800a90ad 37              ??         37h    7
     9::800a90ae 0a              ??         0Ah
     9::800a90af 80              ??         80h
     9::800a90b0 1c              ??         1Ch                                              ?  ->  OVR_229::800a371c
     9::800a90b1 37              ??         37h    7
     9::800a90b2 0a              ??         0Ah
     9::800a90b3 80              ??         80h
     9::800a90b4 a8              ??         A8h                                              ?  ->  OVR_229::800a37a8
     9::800a90b5 37              ??         37h    7
     9::800a90b6 0a              ??         0Ah
     9::800a90b7 80              ??         80h
     9::800a90b8 0e              ??         0Eh
     9::800a90b9 00              ??         00h
     9::800a90ba 00              ??         00h
     9::800a90bb 00              ??         00h
     9::800a90bc d4              ??         D4h                                              ?  ->  OVR_229::800a90d4
     9::800a90bd 90              ??         90h
     9::800a90be 0a              ??         0Ah
     9::800a90bf 80              ??         80h
     9::800a90c0 4c              ??         4Ch    L
     9::800a90c1 01              ??         01h
     9::800a90c2 00              ??         00h
     9::800a90c3 00              ??         00h
     9::800a90c4 02              ??         02h
     9::800a90c5 00              ??         00h
     9::800a90c6 00              ??         00h
     9::800a90c7 00              ??         00h
     9::800a90c8 10              ??         10h                                              ?  ->  OVR_229::800a9110
     9::800a90c9 91              ??         91h
     9::800a90ca 0a              ??         0Ah
     9::800a90cb 80              ??         80h
     9::800a90cc 88              ??         88h
     9::800a90cd 01              ??         01h
     9::800a90ce 00              ??         00h
     9::800a90cf 00              ??         00h
     9::800a90d0 00              ??         00h
     9::800a90d1 00              ??         00h
     9::800a90d2 00              ??         00h
     9::800a90d3 00              ??         00h
     9::800a90d4 70              ??         70h    p                                         ?  ->  OVR_229::800a3c70
     9::800a90d5 3c              ??         3Ch    <
     9::800a90d6 0a              ??         0Ah
     9::800a90d7 80              ??         80h
     9::800a90d8 b0              ??         B0h                                              ?  ->  OVR_229::800a3cb0
     9::800a90d9 3c              ??         3Ch    <
     9::800a90da 0a              ??         0Ah
     9::800a90db 80              ??         80h
     9::800a90dc 30              ??         30h    0                                         ?  ->  OVR_229::800a3d30
     9::800a90dd 3d              ??         3Dh    =
     9::800a90de 0a              ??         0Ah
     9::800a90df 80              ??         80h
     9::800a90e0 d0              ??         D0h                                              ?  ->  OVR_229::800a3cd0
     9::800a90e1 3c              ??         3Ch    <
     9::800a90e2 0a              ??         0Ah
     9::800a90e3 80              ??         80h
     9::800a90e4 58              ??         58h    X                                         ?  ->  OVR_229::800a3d58
     9::800a90e5 3d              ??         3Dh    =
     9::800a90e6 0a              ??         0Ah
     9::800a90e7 80              ??         80h
     9::800a90e8 d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a90e9 3d              ??         3Dh    =
     9::800a90ea 0a              ??         0Ah
     9::800a90eb 80              ??         80h
     9::800a90ec d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a90ed 3d              ??         3Dh    =
     9::800a90ee 0a              ??         0Ah
     9::800a90ef 80              ??         80h
     9::800a90f0 f0              ??         F0h                                              ?  ->  OVR_229::800a3cf0
     9::800a90f1 3c              ??         3Ch    <
     9::800a90f2 0a              ??         0Ah
     9::800a90f3 80              ??         80h
     9::800a90f4 d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a90f5 3d              ??         3Dh    =
     9::800a90f6 0a              ??         0Ah
     9::800a90f7 80              ??         80h
     9::800a90f8 80              ??         80h                                              ?  ->  OVR_229::800a3d80
     9::800a90f9 3d              ??         3Dh    =
     9::800a90fa 0a              ??         0Ah
     9::800a90fb 80              ??         80h
     9::800a90fc d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a90fd 3d              ??         3Dh    =
     9::800a90fe 0a              ??         0Ah
     9::800a90ff 80              ??         80h
     9::800a9100 a8              ??         A8h                                              ?  ->  OVR_229::800a3da8
     9::800a9101 3d              ??         3Dh    =
     9::800a9102 0a              ??         0Ah
     9::800a9103 80              ??         80h
     9::800a9104 d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a9105 3d              ??         3Dh    =
     9::800a9106 0a              ??         0Ah
     9::800a9107 80              ??         80h
     9::800a9108 d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a9109 3d              ??         3Dh    =
     9::800a910a 0a              ??         0Ah
     9::800a910b 80              ??         80h
     9::800a910c d0              ??         D0h                                              ?  ->  OVR_229::800a3dd0
     9::800a910d 3d              ??         3Dh    =
     9::800a910e 0a              ??         0Ah
     9::800a910f 80              ??         80h
     9::800a9110 90              ??         90h                                              ?  ->  OVR_229::800a4490
     9::800a9111 44              ??         44h    D
     9::800a9112 0a              ??         0Ah
     9::800a9113 80              ??         80h
     9::800a9114 88              ??         88h                                              ?  ->  OVR_229::800a4488
     9::800a9115 44              ??         44h    D
     9::800a9116 0a              ??         0Ah
     9::800a9117 80              ??         80h
     9::800a9118 44              ??         44h    D                                         ?  ->  OVR_229::800a4544
     9::800a9119 45              ??         45h    E
     9::800a911a 0a              ??         0Ah
     9::800a911b 80              ??         80h
     9::800a911c 0e              ??         0Eh
     9::800a911d 00              ??         00h
     9::800a911e 00              ??         00h
     9::800a911f 00              ??         00h
     9::800a9120 38              ??         38h    8                                         ?  ->  OVR_229::800a9138
     9::800a9121 91              ??         91h
     9::800a9122 0a              ??         0Ah
     9::800a9123 80              ??         80h
     9::800a9124 4c              ??         4Ch    L
     9::800a9125 01              ??         01h
     9::800a9126 00              ??         00h
     9::800a9127 00              ??         00h
     9::800a9128 02              ??         02h
     9::800a9129 00              ??         00h
     9::800a912a 00              ??         00h
     9::800a912b 00              ??         00h
     9::800a912c 74              ??         74h    t                                         ?  ->  OVR_229::800a9174
     9::800a912d 91              ??         91h
     9::800a912e 0a              ??         0Ah
     9::800a912f 80              ??         80h
     9::800a9130 88              ??         88h
     9::800a9131 01              ??         01h
     9::800a9132 00              ??         00h
     9::800a9133 00              ??         00h
     9::800a9134 00              ??         00h
     9::800a9135 00              ??         00h
     9::800a9136 00              ??         00h
     9::800a9137 00              ??         00h
     9::800a9138 a8              ??         A8h                                              ?  ->  OVR_229::800a4da8
     9::800a9139 4d              ??         4Dh    M
     9::800a913a 0a              ??         0Ah
     9::800a913b 80              ??         80h
     9::800a913c e8              ??         E8h                                              ?  ->  OVR_229::800a4de8
     9::800a913d 4d              ??         4Dh    M
     9::800a913e 0a              ??         0Ah
     9::800a913f 80              ??         80h
     9::800a9140 68              ??         68h    h                                         ?  ->  OVR_229::800a4e68
     9::800a9141 4e              ??         4Eh    N
     9::800a9142 0a              ??         0Ah
     9::800a9143 80              ??         80h
     9::800a9144 08              ??         08h                                              ?  ->  OVR_229::800a4e08
     9::800a9145 4e              ??         4Eh    N
     9::800a9146 0a              ??         0Ah
     9::800a9147 80              ??         80h
     9::800a9148 90              ??         90h                                              ?  ->  OVR_229::800a4e90
     9::800a9149 4e              ??         4Eh    N
     9::800a914a 0a              ??         0Ah
     9::800a914b 80              ??         80h
     9::800a914c 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a914d 4f              ??         4Fh    O
     9::800a914e 0a              ??         0Ah
     9::800a914f 80              ??         80h
     9::800a9150 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a9151 4f              ??         4Fh    O
     9::800a9152 0a              ??         0Ah
     9::800a9153 80              ??         80h
     9::800a9154 28              ??         28h    (                                         ?  ->  OVR_229::800a4e28
     9::800a9155 4e              ??         4Eh    N
     9::800a9156 0a              ??         0Ah
     9::800a9157 80              ??         80h
     9::800a9158 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a9159 4f              ??         4Fh    O
     9::800a915a 0a              ??         0Ah
     9::800a915b 80              ??         80h
     9::800a915c b8              ??         B8h                                              ?  ->  OVR_229::800a4eb8
     9::800a915d 4e              ??         4Eh    N
     9::800a915e 0a              ??         0Ah
     9::800a915f 80              ??         80h
     9::800a9160 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a9161 4f              ??         4Fh    O
     9::800a9162 0a              ??         0Ah
     9::800a9163 80              ??         80h
     9::800a9164 e0              ??         E0h                                              ?  ->  OVR_229::800a4ee0
     9::800a9165 4e              ??         4Eh    N
     9::800a9166 0a              ??         0Ah
     9::800a9167 80              ??         80h
     9::800a9168 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a9169 4f              ??         4Fh    O
     9::800a916a 0a              ??         0Ah
     9::800a916b 80              ??         80h
     9::800a916c 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a916d 4f              ??         4Fh    O
     9::800a916e 0a              ??         0Ah
     9::800a916f 80              ??         80h
     9::800a9170 08              ??         08h                                              ?  ->  OVR_229::800a4f08
     9::800a9171 4f              ??         4Fh    O
     9::800a9172 0a              ??         0Ah
     9::800a9173 80              ??         80h
     9::800a9174 64              ??         64h    d                                         ?  ->  OVR_229::800a5564
     9::800a9175 55              ??         55h    U
     9::800a9176 0a              ??         0Ah
     9::800a9177 80              ??         80h
     9::800a9178 5c              ??         5Ch    \                                         ?  ->  OVR_229::800a555c
     9::800a9179 55              ??         55h    U
     9::800a917a 0a              ??         0Ah
     9::800a917b 80              ??         80h
     9::800a917c e8              ??         E8h                                              ?  ->  OVR_229::800a55e8
     9::800a917d 55              ??         55h    U
     9::800a917e 0a              ??         0Ah
     9::800a917f 80              ??         80h
     9::800a9180 0e              ??         0Eh
     9::800a9181 00              ??         00h
     9::800a9182 00              ??         00h
     9::800a9183 00              ??         00h
     9::800a9184 9c              ??         9Ch                                              ?  ->  OVR_229::800a919c
     9::800a9185 91              ??         91h
     9::800a9186 0a              ??         0Ah
     9::800a9187 80              ??         80h
     9::800a9188 4c              ??         4Ch    L
     9::800a9189 01              ??         01h
     9::800a918a 00              ??         00h
     9::800a918b 00              ??         00h
     9::800a918c 02              ??         02h
     9::800a918d 00              ??         00h
     9::800a918e 00              ??         00h
     9::800a918f 00              ??         00h
     9::800a9190 d8              ??         D8h                                              ?  ->  OVR_229::800a91d8
     9::800a9191 91              ??         91h
     9::800a9192 0a              ??         0Ah
     9::800a9193 80              ??         80h
     9::800a9194 88              ??         88h
     9::800a9195 01              ??         01h
     9::800a9196 00              ??         00h
     9::800a9197 00              ??         00h
     9::800a9198 00              ??         00h
     9::800a9199 00              ??         00h
     9::800a919a 00              ??         00h
     9::800a919b 00              ??         00h
     9::800a919c b0              ??         B0h                                              ?  ->  OVR_229::800a5ab0
     9::800a919d 5a              ??         5Ah    Z
     9::800a919e 0a              ??         0Ah
     9::800a919f 80              ??         80h
     9::800a91a0 f0              ??         F0h                                              ?  ->  OVR_229::800a5af0
     9::800a91a1 5a              ??         5Ah    Z
     9::800a91a2 0a              ??         0Ah
     9::800a91a3 80              ??         80h
     9::800a91a4 70              ??         70h    p                                         ?  ->  OVR_229::800a5b70
     9::800a91a5 5b              ??         5Bh    [
     9::800a91a6 0a              ??         0Ah
     9::800a91a7 80              ??         80h
     9::800a91a8 10              ??         10h                                              ?  ->  OVR_229::800a5b10
     9::800a91a9 5b              ??         5Bh    [
     9::800a91aa 0a              ??         0Ah
     9::800a91ab 80              ??         80h
     9::800a91ac 98              ??         98h                                              ?  ->  OVR_229::800a5b98
     9::800a91ad 5b              ??         5Bh    [
     9::800a91ae 0a              ??         0Ah
     9::800a91af 80              ??         80h
     9::800a91b0 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91b1 5c              ??         5Ch    \
     9::800a91b2 0a              ??         0Ah
     9::800a91b3 80              ??         80h
     9::800a91b4 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91b5 5c              ??         5Ch    \
     9::800a91b6 0a              ??         0Ah
     9::800a91b7 80              ??         80h
     9::800a91b8 30              ??         30h    0                                         ?  ->  OVR_229::800a5b30
     9::800a91b9 5b              ??         5Bh    [
     9::800a91ba 0a              ??         0Ah
     9::800a91bb 80              ??         80h
     9::800a91bc 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91bd 5c              ??         5Ch    \
     9::800a91be 0a              ??         0Ah
     9::800a91bf 80              ??         80h
     9::800a91c0 c0              ??         C0h                                              ?  ->  OVR_229::800a5bc0
     9::800a91c1 5b              ??         5Bh    [
     9::800a91c2 0a              ??         0Ah
     9::800a91c3 80              ??         80h
     9::800a91c4 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91c5 5c              ??         5Ch    \
     9::800a91c6 0a              ??         0Ah
     9::800a91c7 80              ??         80h
     9::800a91c8 e8              ??         E8h                                              ?  ->  OVR_229::800a5be8
     9::800a91c9 5b              ??         5Bh    [
     9::800a91ca 0a              ??         0Ah
     9::800a91cb 80              ??         80h
     9::800a91cc 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91cd 5c              ??         5Ch    \
     9::800a91ce 0a              ??         0Ah
     9::800a91cf 80              ??         80h
     9::800a91d0 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91d1 5c              ??         5Ch    \
     9::800a91d2 0a              ??         0Ah
     9::800a91d3 80              ??         80h
     9::800a91d4 10              ??         10h                                              ?  ->  OVR_229::800a5c10
     9::800a91d5 5c              ??         5Ch    \
     9::800a91d6 0a              ??         0Ah
     9::800a91d7 80              ??         80h
     9::800a91d8 d0              ??         D0h                                              ?  ->  OVR_229::800a62d0
     9::800a91d9 62              ??         62h    b
     9::800a91da 0a              ??         0Ah
     9::800a91db 80              ??         80h
     9::800a91dc c8              ??         C8h                                              ?  ->  OVR_229::800a62c8
     9::800a91dd 62              ??         62h    b
     9::800a91de 0a              ??         0Ah
     9::800a91df 80              ??         80h
     9::800a91e0 84              ??         84h                                              ?  ->  OVR_229::800a6384
     9::800a91e1 63              ??         63h    c
     9::800a91e2 0a              ??         0Ah
     9::800a91e3 80              ??         80h
                             DAT_OVR_229__800a91e4                           XREF[2]:     FUN_OVR_229__800a106c:800a108c(R
                                                                                          OVR_229::800a8f08(*)  
     9::800a91e4 0e 00 00 00     undefined4 0000000Eh
                             PTR_PTR_LAB_OVR_229__800a6a0c_OVR_229__800a920  XREF[1]:     FUN_OVR_229__800a106c:800a1090(R
     9::800a91e8 00 92 0a 80     addr       PTR_LAB_OVR_229__800a6a0c_OVR_229__800a9200      = OVR_229::800a6a0c
                             DAT_OVR_229__800a91ec                           XREF[1]:     FUN_OVR_229__800a106c:800a1094(R
     9::800a91ec 4c 01 00 00     undefined4 0000014Ch
                             DAT_OVR_229__800a91f0                           XREF[1]:     FUN_OVR_229__800a106c:800a108c(R
     9::800a91f0 02 00 00 00     undefined4 00000002h
                             PTR_PTR_LAB_OVR_229__800a7168_OVR_229__800a923  XREF[1]:     FUN_OVR_229__800a106c:800a1090(R
     9::800a91f4 3c 92 0a 80     addr       PTR_LAB_OVR_229__800a7168_OVR_229__800a923c      = OVR_229::800a7168
                             DAT_OVR_229__800a91f8                           XREF[1]:     FUN_OVR_229__800a106c:800a1094(R
     9::800a91f8 88 01 00 00     undefined4 00000188h
     9::800a91fc 00              ??         00h
     9::800a91fd 00              ??         00h
     9::800a91fe 00              ??         00h
     9::800a91ff 00              ??         00h
                             PTR_LAB_OVR_229__800a6a0c_OVR_229__800a9200     XREF[2]:     FUN_OVR_229__800a106c:800a10a0(R
                                                                                          OVR_229::800a91e8(*)  
     9::800a9200 0c 6a 0a 80     addr       LAB_OVR_229__800a6a0c
                             PTR_LAB_OVR_229__800a6a4c_OVR_229__800a9204     XREF[1]:     FUN_OVR_229__800a106c:800a10a0(R
     9::800a9204 4c 6a 0a 80     addr       LAB_OVR_229__800a6a4c
     9::800a9208 cc              ??         CCh                                              ?  ->  OVR_229::800a6acc
     9::800a9209 6a              ??         6Ah    j
     9::800a920a 0a              ??         0Ah
     9::800a920b 80              ??         80h
     9::800a920c 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6a6c
     9::800a920d 6a              ??         6Ah    j
     9::800a920e 0a              ??         0Ah
     9::800a920f 80              ??         80h
     9::800a9210 f4              ??         F4h                                              ?  ->  OVR_229::800a6af4
     9::800a9211 6a              ??         6Ah    j
     9::800a9212 0a              ??         0Ah
     9::800a9213 80              ??         80h
     9::800a9214 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9215 6b              ??         6Bh    k
     9::800a9216 0a              ??         0Ah
     9::800a9217 80              ??         80h
     9::800a9218 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9219 6b              ??         6Bh    k
     9::800a921a 0a              ??         0Ah
     9::800a921b 80              ??         80h
     9::800a921c 8c              ??         8Ch                                              ?  ->  OVR_229::800a6a8c
     9::800a921d 6a              ??         6Ah    j
     9::800a921e 0a              ??         0Ah
     9::800a921f 80              ??         80h
     9::800a9220 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9221 6b              ??         6Bh    k
     9::800a9222 0a              ??         0Ah
     9::800a9223 80              ??         80h
     9::800a9224 1c              ??         1Ch                                              ?  ->  OVR_229::800a6b1c
     9::800a9225 6b              ??         6Bh    k
     9::800a9226 0a              ??         0Ah
     9::800a9227 80              ??         80h
     9::800a9228 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9229 6b              ??         6Bh    k
     9::800a922a 0a              ??         0Ah
     9::800a922b 80              ??         80h
     9::800a922c 44              ??         44h    D                                         ?  ->  OVR_229::800a6b44
     9::800a922d 6b              ??         6Bh    k
     9::800a922e 0a              ??         0Ah
     9::800a922f 80              ??         80h
     9::800a9230 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9231 6b              ??         6Bh    k
     9::800a9232 0a              ??         0Ah
     9::800a9233 80              ??         80h
     9::800a9234 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9235 6b              ??         6Bh    k
     9::800a9236 0a              ??         0Ah
     9::800a9237 80              ??         80h
     9::800a9238 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a6b6c
     9::800a9239 6b              ??         6Bh    k
     9::800a923a 0a              ??         0Ah
     9::800a923b 80              ??         80h
                             PTR_LAB_OVR_229__800a7168_OVR_229__800a923c     XREF[1]:     OVR_229::800a91f4(*)  
     9::800a923c 68 71 0a 80     addr       LAB_OVR_229__800a7168
     9::800a9240 60              ??         60h    `                                         ?  ->  OVR_229::800a7160
     9::800a9241 71              ??         71h    q
     9::800a9242 0a              ??         0Ah
     9::800a9243 80              ??         80h
     9::800a9244 ec              ??         ECh                                              ?  ->  OVR_229::800a71ec
     9::800a9245 71              ??         71h    q
     9::800a9246 0a              ??         0Ah
     9::800a9247 80              ??         80h
     9::800a9248 0e              ??         0Eh
     9::800a9249 00              ??         00h
     9::800a924a 00              ??         00h
     9::800a924b 00              ??         00h
     9::800a924c 64              ??         64h    d                                         ?  ->  OVR_229::800a9264
     9::800a924d 92              ??         92h
     9::800a924e 0a              ??         0Ah
     9::800a924f 80              ??         80h
     9::800a9250 4c              ??         4Ch    L
     9::800a9251 01              ??         01h
     9::800a9252 00              ??         00h
     9::800a9253 00              ??         00h
     9::800a9254 02              ??         02h
     9::800a9255 00              ??         00h
     9::800a9256 00              ??         00h
     9::800a9257 00              ??         00h
     9::800a9258 a0              ??         A0h                                              ?  ->  OVR_229::800a92a0
     9::800a9259 92              ??         92h
     9::800a925a 0a              ??         0Ah
     9::800a925b 80              ??         80h
     9::800a925c 88              ??         88h
     9::800a925d 01              ??         01h
     9::800a925e 00              ??         00h
     9::800a925f 00              ??         00h
     9::800a9260 00              ??         00h
     9::800a9261 00              ??         00h
     9::800a9262 00              ??         00h
     9::800a9263 00              ??         00h
     9::800a9264 b4              ??         B4h                                              ?  ->  OVR_229::800a76b4
     9::800a9265 76              ??         76h    v
     9::800a9266 0a              ??         0Ah
     9::800a9267 80              ??         80h
     9::800a9268 f4              ??         F4h                                              ?  ->  OVR_229::800a76f4
     9::800a9269 76              ??         76h    v
     9::800a926a 0a              ??         0Ah
     9::800a926b 80              ??         80h
     9::800a926c 74              ??         74h    t                                         ?  ->  OVR_229::800a7774
     9::800a926d 77              ??         77h    w
     9::800a926e 0a              ??         0Ah
     9::800a926f 80              ??         80h
     9::800a9270 14              ??         14h                                              ?  ->  OVR_229::800a7714
     9::800a9271 77              ??         77h    w
     9::800a9272 0a              ??         0Ah
     9::800a9273 80              ??         80h
     9::800a9274 9c              ??         9Ch                                              ?  ->  OVR_229::800a779c
     9::800a9275 77              ??         77h    w
     9::800a9276 0a              ??         0Ah
     9::800a9277 80              ??         80h
     9::800a9278 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a9279 78              ??         78h    x
     9::800a927a 0a              ??         0Ah
     9::800a927b 80              ??         80h
     9::800a927c 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a927d 78              ??         78h    x
     9::800a927e 0a              ??         0Ah
     9::800a927f 80              ??         80h
     9::800a9280 34              ??         34h    4                                         ?  ->  OVR_229::800a7734
     9::800a9281 77              ??         77h    w
     9::800a9282 0a              ??         0Ah
     9::800a9283 80              ??         80h
     9::800a9284 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a9285 78              ??         78h    x
     9::800a9286 0a              ??         0Ah
     9::800a9287 80              ??         80h
     9::800a9288 c4              ??         C4h                                              ?  ->  OVR_229::800a77c4
     9::800a9289 77              ??         77h    w
     9::800a928a 0a              ??         0Ah
     9::800a928b 80              ??         80h
     9::800a928c 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a928d 78              ??         78h    x
     9::800a928e 0a              ??         0Ah
     9::800a928f 80              ??         80h
     9::800a9290 ec              ??         ECh                                              ?  ->  OVR_229::800a77ec
     9::800a9291 77              ??         77h    w
     9::800a9292 0a              ??         0Ah
     9::800a9293 80              ??         80h
     9::800a9294 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a9295 78              ??         78h    x
     9::800a9296 0a              ??         0Ah
     9::800a9297 80              ??         80h
     9::800a9298 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a9299 78              ??         78h    x
     9::800a929a 0a              ??         0Ah
     9::800a929b 80              ??         80h
     9::800a929c 14              ??         14h                                              ?  ->  OVR_229::800a7814
     9::800a929d 78              ??         78h    x
     9::800a929e 0a              ??         0Ah
     9::800a929f 80              ??         80h
     9::800a92a0 d4              ??         D4h                                              ?  ->  OVR_229::800a7ed4
     9::800a92a1 7e              ??         7Eh    ~
     9::800a92a2 0a              ??         0Ah
     9::800a92a3 80              ??         80h
     9::800a92a4 cc              ??         CCh                                              ?  ->  OVR_229::800a7ecc
     9::800a92a5 7e              ??         7Eh    ~
     9::800a92a6 0a              ??         0Ah
     9::800a92a7 80              ??         80h
     9::800a92a8 88              ??         88h                                              ?  ->  OVR_229::800a7f88
     9::800a92a9 7f              ??         7Fh    
     9::800a92aa 0a              ??         0Ah
     9::800a92ab 80              ??         80h
                             PTR_LAB_OVR_229__800a844c_OVR_229__800a92ac     XREF[1]:     FUN_OVR_229__800a8ebc:800a8ecc(R
     9::800a92ac 4c 84 0a 80     addr       LAB_OVR_229__800a844c
                             PTR_LAB_OVR_229__800a8464_OVR_229__800a92b0     XREF[1]:     FUN_OVR_229__800a8ebc:800a8ecc(R
     9::800a92b0 64 84 0a 80     addr       LAB_OVR_229__800a8464
     9::800a92b4 9c              ??         9Ch                                              ?  ->  OVR_229::800a849c
     9::800a92b5 84              ??         84h
     9::800a92b6 0a              ??         0Ah
     9::800a92b7 80              ??         80h
     9::800a92b8 d4              ??         D4h                                              ?  ->  OVR_229::800a84d4
     9::800a92b9 84              ??         84h
     9::800a92ba 0a              ??         0Ah
     9::800a92bb 80              ??         80h
     9::800a92bc 08              ??         08h                                              ?  ->  OVR_229::800a8508
     9::800a92bd 85              ??         85h
     9::800a92be 0a              ??         0Ah
     9::800a92bf 80              ??         80h
     9::800a92c0 40              ??         40h    @                                         ?  ->  OVR_229::800a8540
     9::800a92c1 85              ??         85h
     9::800a92c2 0a              ??         0Ah
     9::800a92c3 80              ??         80h
     9::800a92c4 74              ??         74h    t                                         ?  ->  OVR_229::800a8574
     9::800a92c5 85              ??         85h
     9::800a92c6 0a              ??         0Ah
     9::800a92c7 80              ??         80h
     9::800a92c8 a8              ??         A8h                                              ?  ->  OVR_229::800a85a8
     9::800a92c9 85              ??         85h
     9::800a92ca 0a              ??         0Ah
     9::800a92cb 80              ??         80h
     9::800a92cc 50              ??         50h    P                                         ?  ->  OVR_229::800a8a50
     9::800a92cd 8a              ??         8Ah
     9::800a92ce 0a              ??         0Ah
     9::800a92cf 80              ??         80h
     9::800a92d0 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a8a6c
     9::800a92d1 8a              ??         8Ah
     9::800a92d2 0a              ??         0Ah
     9::800a92d3 80              ??         80h
     9::800a92d4 b4              ??         B4h                                              ?  ->  OVR_229::800a8ab4
     9::800a92d5 8a              ??         8Ah
     9::800a92d6 0a              ??         0Ah
     9::800a92d7 80              ??         80h
     9::800a92d8 0c              ??         0Ch                                              ?  ->  OVR_229::800a8b0c
     9::800a92d9 8b              ??         8Bh
     9::800a92da 0a              ??         0Ah
     9::800a92db 80              ??         80h
     9::800a92dc 60              ??         60h    `                                         ?  ->  OVR_229::800a8b60
     9::800a92dd 8b              ??         8Bh
     9::800a92de 0a              ??         0Ah
     9::800a92df 80              ??         80h
     9::800a92e0 b8              ??         B8h                                              ?  ->  OVR_229::800a8bb8
     9::800a92e1 8b              ??         8Bh
     9::800a92e2 0a              ??         0Ah
     9::800a92e3 80              ??         80h
     9::800a92e4 0c              ??         0Ch                                              ?  ->  OVR_229::800a8c0c
     9::800a92e5 8c              ??         8Ch
     9::800a92e6 0a              ??         0Ah
     9::800a92e7 80              ??         80h
     9::800a92e8 6c              ??         6Ch    l                                         ?  ->  OVR_229::800a8c6c
     9::800a92e9 8c              ??         8Ch
     9::800a92ea 0a              ??         0Ah
     9::800a92eb 80              ??         80h
     9::800a92ec a0              ??         A0h                                              ?  ->  OVR_229::800a8ca0
     9::800a92ed 8c              ??         8Ch
     9::800a92ee 0a              ??         0Ah
     9::800a92ef 80              ??         80h
     9::800a92f0 e8              ??         E8h                                              ?  ->  OVR_229::800a8ce8
     9::800a92f1 8c              ??         8Ch
     9::800a92f2 0a              ??         0Ah
     9::800a92f3 80              ??         80h
     9::800a92f4 50              ??         50h    P                                         ?  ->  OVR_229::800a8d50
     9::800a92f5 8d              ??         8Dh
     9::800a92f6 0a              ??         0Ah
     9::800a92f7 80              ??         80h
     9::800a92f8 a4              ??         A4h                                              ?  ->  OVR_229::800a8da4
     9::800a92f9 8d              ??         8Dh
     9::800a92fa 0a              ??         0Ah
     9::800a92fb 80              ??         80h
     9::800a92fc e8              ??         E8h                                              ?  ->  OVR_229::800a8de8
     9::800a92fd 8d              ??         8Dh
     9::800a92fe 0a              ??         0Ah
     9::800a92ff 80              ??         80h
     9::800a9300 3c              ??         3Ch    <                                         ?  ->  OVR_229::800a8e3c
     9::800a9301 8e              ??         8Eh
     9::800a9302 0a              ??         0Ah
     9::800a9303 80              ??         80h
     9::800a9304 80              ??         80h                                              ?  ->  OVR_229::800a8e80
     9::800a9305 8e              ??         8Eh
     9::800a9306 0a              ??         0Ah
     9::800a9307 80              ??         80h
     9::800a9308 b4              ??         B4h                                              ?  ->  OVR_229::800a8eb4
     9::800a9309 8e              ??         8Eh
     9::800a930a 0a              ??         0Ah
     9::800a930b 80              ??         80h
