                             //
                             // OVR_226 
                             // OVR_226::800a0cb8-OVR_226::800ab96f
                             //
             assume gp = 0x80000000
     
	 // Overlay Tag
	 6::800a0cb8 0b              ??         0Bh
     6::800a0cb9 00              ??         00h
     6::800a0cba 00              ??         00h
     6::800a0cbb 00              ??         00h
	 
// FUN_800a0cbc, called by exe as entry to this monsterous algorithm, for rendering LEV.
// param1 (a0) - offset 0x1808 of gameTracker, one struct per player
// param2 (a1) - pushBuffer
// param3 (a2) - LEV->ptr_mesh_info, pointer is stored at first four bytes of LEV
// param4 (a3) - primMem
// param5 (sp+0x10) - Vismem 0x10-0x1F
// param6 (sp+0x14) - lev->0x44

	 // allocate stack memory
     6::800a0cbc c4 ff bd 27     addiu      sp,sp,-0x3c
	 
	 // backup registers on stack, including $gp which is edited in the algorithm
     6::800a0cc0 10 00 b0 af     sw         s0,0x10(sp)
     6::800a0cc4 14 00 b1 af     sw         s1,0x14(sp)
     6::800a0cc8 18 00 b2 af     sw         s2,0x18(sp)
     6::800a0ccc 1c 00 b3 af     sw         s3,0x1c(sp)
     6::800a0cd0 20 00 b4 af     sw         s4,0x20(sp)
     6::800a0cd4 24 00 b5 af     sw         s5,0x24(sp)
     6::800a0cd8 28 00 b6 af     sw         s6,0x28(sp)
     6::800a0cdc 2c 00 b7 af     sw         s7,0x2c(sp)
     6::800a0ce0 30 00 bc af     sw         gp,0x30(sp)                        = ??
     6::800a0ce4 34 00 be af     sw         s8,0x34(sp)
     6::800a0ce8 38 00 bf af     sw         ra,0x38(sp)
	 
	 // $at = 1f800000
     6::800a0cec 80 1f 01 3c     lui        at,0x1f80
     
	 // 0x1f800038 = $sp (backup)
	 6::800a0cf0 38 00 3d ac     sw         sp,offset DAT_1f800038(at)                       = ??
     
	 // remember $sp was subtracted by 0x3C,
	 // so this was originally offsets 0x10 and 0x14
	 
	 // param_5, VisMem 0x10-0x1F (visFaceList)
	 6::800a0cf4 4c 00 a8 8f     lw         t0,0x4c(sp)
	 
	 // param_6, lev->0x44 (restart_main?)
     6::800a0cf8 50 00 a9 8f     lw         t1,0x50(sp)
	 
	 // primMem->curr
     6::800a0cfc 0c 00 e2 8c     lw         v0,0xc(a3)
	 
	 // primMem->end
     6::800a0d00 08 00 e3 8c     lw         v1,0x8(a3)
	 
	 // primMem->unk(0x14?)
     6::800a0d04 14 00 fd 8c     lw         sp,0x14(a3)
	 
	 // 1f800030 = primMem->end
     6::800a0d08 30 00 23 ac     sw         v1,offset DAT_1f800030(at)                       = ??
	 
	 // v1 = mesh_info -> ptrQuadBlockArray
     6::800a0d0c 0c 00 c3 8c     lw         v1,0xc(a2)
	 
	 // if the visFaceList is invalid, jump to 800a0eb4,
	 // where the function rsetores the backed-up registers, and returns to the EXE
     // ------------------------------
	 // 1f8000c8 = visFaceList
	 6::800a0d10 68 00 00 11     beq        t0,zero,LAB_OVR_226__800a0eb4
	 6::800a0d14 c8 00 28 ac     _sw        t0,offset DAT_1f8000c8(at)                       = ??
     
	 // if ptrQuadBlockArray == 0 (invalid), then end rendering, return to exe
	 6::800a0d18 66 00 60 10     beq        v1,zero,LAB_OVR_226__800a0eb4
	 
	 // 1f800088 = param_6 lev->0x44 (restart_main)
     6::800a0d1c 88 00 29 ac     _sw        t1,offset DAT_1f800088(at)                       = ??
	 
	 // t2 = 80084228
     // address of ptrClipBuffer array
	 6::800a0d20 08 80 0a 3c     lui        t2,0x8008
     6::800a0d24 28 42 4a 25     addiu      t2,t2,0x4228
	 
	 // v1 = P1 clipBuffer
     6::800a0d28 00 00 43 8d     lw         v1,0x0(t2)=>DAT_80084228
	 
	 // 1f8000dc = pushBuffer
     6::800a0d2c dc 00 25 ac     sw         a1,offset DAT_1f8000dc(at)                       = ??
	 
	 // 1f800010 = P1 ClipBuffer
     6::800a0d30 10 00 23 ac     sw         v1,offset DAT_1f800010(at)                       = ??
	 
	 // load PushBuffer matrix (offset 0x28) into registers
     6::800a0d34 28 00 ab 8c     lw         t3,0x28(a1)
     6::800a0d38 2c 00 ac 8c     lw         t4,0x2c(a1)
     6::800a0d3c 30 00 ad 8c     lw         t5,0x30(a1)
     6::800a0d40 34 00 ae 8c     lw         t6,0x34(a1)
     6::800a0d44 38 00 af 8c     lw         t7,0x38(a1)
     6::800a0d48 3c 00 b0 8c     lw         s0,0x3c(a1)
     6::800a0d4c 40 00 b1 8c     lw         s1,0x40(a1)
     6::800a0d50 44 00 b2 8c     lw         s2,0x44(a1)
	 
	 // store matrix in GTE regsiters
     6::800a0d54 00 00 cb 48     gte_ldR1   t3
     6::800a0d58 00 08 cc 48     gte_ldR1   t4
     6::800a0d5c 00 10 cd 48     gte_ldR2   t5
     6::800a0d60 00 18 ce 48     gte_ldR3   t6
     6::800a0d64 00 20 cf 48     gte_ldR33  t7
     6::800a0d68 00 28 d0        ldtr       s0,s1,s2
                 48 00 30 
                 d1 48 00 
				 
	 // camera frustum data
     6::800a0d74 0c 00 b0 84     lh         s0,0xc(a1)
     6::800a0d78 0e 00 b1 84     lh         s1,0xe(a1)
     6::800a0d7c 10 00 b2 84     lh         s2,0x10(a1)
	 
	 // store frustum data on scratchpad
     6::800a0d80 98 01 30 a4     sh         s0,offset DAT_1f800198(at)                       = ??
     6::800a0d84 9a 01 31 a4     sh         s1,offset DAT_1f80019a(at)                       = ??
     6::800a0d88 9c 01 32 a4     sh         s2,offset DAT_1f80019c(at)                       = ??
	 
	 // pushBuffer sizeX, sizeY, and distanceToScreen
     6::800a0d8c 20 00 a3 84     lh         v1,0x20(a1)
     6::800a0d90 22 00 a8 84     lh         t0,0x22(a1)
     6::800a0d94 18 00 a9 8c     lw         t1,0x18(a1)
     6::800a0d98 c0 1b 03 00     sll        v1,v1,0xf
     6::800a0d9c c0 43 08 00     sll        t0,t0,0xf
     6::800a0da0 00 c0 c3 48     gte_ldOFX  v1
     6::800a0da4 00 c8 c8 48     gte_ldOFY  t0
     6::800a0da8 00 d0 c9 48     gte_ldH    t1
	 
	 // 1f80005c = half-distance
     6::800a0dac 43 48 09 00     sra        t1,t1,0x1
     6::800a0db0 01 00 29 25     addiu      t1,t1,0x1
     6::800a0db4 5c 00 29 ac     sw         t1,offset DAT_1f80005c(at)                       = ??
	 
	 // v1 = pushBuffer window sizeX
     6::800a0db8 20 00 a3 8c     lw         v1,0x20(a1)
     
	 // a1 = pushBuffer ptrOT
	 6::800a0dbc f4 00 a5 8c     lw         a1,0xf4(a1)
	 
	 // 1f80006c = window sizeX
     6::800a0dc0 6c 00 23 ac     sw         v1,offset DAT_1f80006c(at)                       = ??
	 
	 // t5 = 0x224 (loop)
     6::800a0dc4 24 02 0d 24     li         t5,0x224
	 
	 // t3 = 0x1f8001b4 (ptr to start clearing)
     6::800a0dc8 b4 01 2b 24     addiu      t3,at,0x1b4
     
	 // loop, set 0x1f8001b4-0x1F8003D8
                        LAB_OVR_226__800a0dcc                           XREF[1]:     OVR_226::800a0dd4(j)  
     6::800a0dcc 00 00 60 ad     sw         zero,0x0(t3)=>DAT_1f8001b4                       = ??
     6::800a0dd0 04 00 6b 25     addiu      t3,t3,0x4
     6::800a0dd4 fd ff a0 1d     bgtz       t5,LAB_OVR_226__800a0dcc
     6::800a0dd8 fc ff ad 25     _addiu     t5,t5,-0x4
	 
	 // t5 = 0x17 (loop)
     6::800a0ddc 17 00 0d 24     li         t5,0x17
	 
	 // t3 = 0x800ab464
     6::800a0de0 0b 80 0b 3c     lui        t3,0x800b
     6::800a0de4 64 b4 6b 25     addiu      t3,t3,-0x4b9c
	 
	 // t4 = 0x1f8000ec
     6::800a0de8 ec 00 2c 24     addiu      t4,at,0xec
	 
	 // 0x1f8000ec-0x1F800148
	 // some kind of render flags for quadblocks, not sure how they work
	 
	 // copy 0x17*4 bytes from 0x800ab464 to 0x1f8000ec
	 // this is 0x1f8000ec-0x1F800148
                             LAB_OVR_226__800a0dec                           XREF[1]:     OVR_226::800a0dfc(j)  
     6::800a0dec 00 00 6e 8d     lw         t6,0x0(t3)=>DAT_OVR_226__800ab464                = 80900818h
                                                                                             = 18100800h
     6::800a0df0 04 00 6b 25     addiu      t3,t3,0x4
     6::800a0df4 00 00 8e ad     sw         t6,0x0(t4)=>DAT_1f8000ec                         = ??
     6::800a0df8 04 00 8c 25     addiu      t4,t4,0x4
     6::800a0dfc fb ff a0 15     bne        t5,zero,LAB_OVR_226__800a0dec
     6::800a0e00 ff ff ad 25     _addiu     t5,t5,-0x1
	 
	 // s7 = mesh_info -> ptrVertexArray
     6::800a0e04 10 00 d7 8c     lw         s7,0x10(a2)
	 
	 // 1f800060 = gGT + 0x1808 (renderlists)
     6::800a0e08 60 00 24 ac     sw         a0,offset DAT_1f800060(at)                       = ??
	 
	 // v1 = 0x28 (loop)
     6::800a0e0c 28 00 03 24     li         v1,0x28
	 
	 // loop through 0xA functions (0x28/4)
	 
                             LAB_OVR_226__800a0e10                           XREF[1]:     OVR_226::800a0e90(j)  
     
	 // if loop is over, jump to end
	 6::800a0e10 21 00 60 04     bltz       v1,LAB_OVR_226__800a0e98
	 
	 // loop runs
	 
	 // t0 = gGT + 0x1808 + v1
     6::800a0e14 21 40 64 00     _addu      t0,v1,a0
	 
	 // 1f800034 = v1 (backup loop counter)
     6::800a0e18 34 00 23 ac     sw         v1,offset DAT_1f800034(at)                       = ??
	 
	 // a0 = dereference (gGT + 0x1808 + v1),
	 // first bsp (bsp node) in the linked list of this particular render list
     6::800a0e1c 00 00 04 8d     lw         a0,0x0(t0)
	 
	 // t0 = 800AB40C
	 // array of CopyMeta
     6::800a0e20 0b 80 08 3c     lui        t0,0x800b
     6::800a0e24 0c b4 08 25     addiu      t0,t0,-0x4bf4
	 
	 // get address of CopyMeta pointer (t0 += loop index)
     6::800a0e28 21 40 03 01     addu       t0,t0,v1
	 
	 // if a0 == 0, jump to next loop index
     6::800a0e2c 13 00 80 10     beq        a0,zero,LAB_OVR_226__800a0e7c
	 
	 // t2 = dereference, get ptrCopyMeta
	 // This is actually a pointer to CopyMeta "array",
	 // which loops infinitely until a null meta is found with size=0
     6::800a0e30 00 00 0a 8d     _lw        t2,0x0(t0)=>PTR_DAT_OVR_226__800ab4c4_OVR_226_   = OVR_226::800ab4c4
     
	 // t0 = 800AB438
	 6::800a0e34 0b 80 08 3c     lui        t0,0x800b
     6::800a0e38 38 b4 08 25     addiu      t0,t0,-0x4bc8
	 
	 // get address of function pointer (t0 += loop index)
     6::800a0e3c 21 40 03 01     addu       t0,t0,v1
     
	 // t0 = dereference, get function pointer
	 6::800a0e40 00 00 08 8d     lw         t0,0x0(t0)=>PTR_LAB_OVR_226__800a0ef4_OVR_226_   = OVR_226::800ab4c4
                                                                                             = OVR_226::800a0ef4

	 // run a loop, CopyMeta sends stuff from RAM to scratchpad,
	 // depending on which function in this 0x28 (0xA) loop is running
							 LAB_OVR_226__800a0e44                           XREF[1]:     OVR_226::800a0e70(j)  
     
	 // CopyMeta size
	 6::800a0e44 00 00 4d 8d     lw         t5,0x0(t2)=>DAT_OVR_226__800ab4c4                = 0000000Eh
                                                                                             = 00000002h
     
	 // CopyMeta source (RAM addr)
	 6::800a0e48 04 00 4b 8d     lw         t3,0x4(t2)=>PTR_PTR_LAB_OVR_226__800a15d4_OVR_   = OVR_226::800ab51c
                                                                                             = OVR_226::800ab4e0
     
	 // CopyMeta destination (scratchpad offset)
	 6::800a0e4c 08 00 4c 8d     lw         t4,0x8(t2)=>DAT_OVR_226__800ab4cc                = 0000014Ch
                                                                                             = 00000188h
     
	 // if size == 0, skip the copy
	 6::800a0e50 09 00 a0 11     beq        t5,zero,LAB_OVR_226__800a0e78
	 
	 // t4 = scratchpad+t4
     6::800a0e54 21 60 81 01     _addu      t4,t4,at
	 
	 // loop through and copy until size runs out
                             LAB_OVR_226__800a0e58                           XREF[1]:     OVR_226::800a0e68(j)  
     
	 // get int from source
	 6::800a0e58 00 00 6e 8d     lw         t6,0x0(t3)
     6::800a0e5c 04 00 6b 25     addiu      t3,t3,0x4
	 
	 // store int in destination
     6::800a0e60 00 00 8e ad     sw         t6,0x0(t4)
     6::800a0e64 04 00 8c 25     addiu      t4,t4,0x4
	 
	 // end copy when size runs out
     6::800a0e68 fb ff a0 15     bne        t5,zero,LAB_OVR_226__800a0e58
     6::800a0e6c ff ff ad 25     _addiu     t5,t5,-0x1
	 
	 // loop infinitely until an invalid CopyMeta is found with null size
     6::800a0e70 f4 ff 01 04     bgez       zero,LAB_OVR_226__800a0e44
	 
	 // next CopyMeta
     6::800a0e74 0c 00 4a 21     _addi      t2,t2,0xc
                             LAB_OVR_226__800a0e78                           XREF[1]:     OVR_226::800a0e50(j)  
     
	// JRs are the following
	// 800a0ef4 -- full dynamic
	// 800a1e30 -- water
	// 800a2904
	// 800a36a8 -- 4x1
	// 800a417c
	// 800a4fa0 -- 4x2
	// 800a5e5c
	// 800a6f40 -- dynamicSubdiv
	// 800a7ba8
	// 800a97c8 -- 4x4
	 
	 // jr t0, call function pointer,
	 // ignore the lui in delay, it does not touch anything important,
	 // the end of the JR function will JMP back to the start of the loop
	 6::800a0e78 08 00 00 01     jr         t0=>LAB_OVR_226__800a0ef4
     
	 // === Below this line will only happen if a0 was invalid ===
	 
	 // jmp here if a0 in entry is invalid
                        LAB_OVR_226__800a0e7c                           XREF[1]:     OVR_226::800a0e2c(j)  
     
	 // v1 = 80096404
	 6::800a0e7c 09 80 03 3c     _lui       v1,0x8009
     6::800a0e80 04 64 63 24     addiu      v1,v1,0x6404
	 
	 // *(int*)0x80096404 = 0
     6::800a0e84 00 00 60 ac     sw         zero,0x0(v1)=>DAT_80096404                       = ??
                             
	// === Above this line will only happen if a0 was invalid ===
	
	// all ten JRs wil JMP back here when they're done
							 LAB_OVR_226__800a0e88                           XREF[11]:    OVR_226::800a0ef8(j), 
                                                                                          OVR_226::800a2224(j), 
                                                                                          OVR_226::800a291c(j), 
                                                                                          OVR_226::800a39b4(j), 
                                                                                          OVR_226::800a4194(j), 
                                                                                          OVR_226::800a52ac(j), 
                                                                                          OVR_226::800a5e74(j), 
                                                                                          OVR_226::800a724c(j), 
                                                                                          OVR_226::800a7bc0(j), 
                                                                                          OVR_226::800a8e6c(j), 
                                                                                          OVR_226::800a97e0(j)
	 // a0 = 1f800060 (gGT + 0x1808) (renderlists)
     6::800a0e88 60 00 24 8c     lw         a0,offset DAT_1f800060(at)                       = ??
	 
	 // v1 = 1f800034 (loop index, before v1 was overwritten)
     6::800a0e8c 34 00 23 8c     lw         v1,offset DAT_1f800034(at)                       = ??
	 
	 // always true, jump 0x80 bytes back,
	 // v1 -= 4, next loop index
     6::800a0e90 df ff 01 04     bgez       zero,LAB_OVR_226__800a0e10
     6::800a0e94 fc ff 63 24     _addiu     v1,v1,-0x4
	 
	 
                             LAB_OVR_226__800a0e98                           XREF[1]:     OVR_226::800a0e10(j)  
     
	 // a0 = gGT+0x1808 (renderlists)
	 // a1 = pushBuffer (from 1f8000dc)
	 6::800a0e98 f7 ac 02 0c     jal        FUN_OVR_226__800ab3dc                            undefined FUN_OVR_226__800ab3dc()
     6::800a0e9c dc 00 25 8c     _lw        a1,offset DAT_1f8000dc(at)                       = ??
     
	 // t2 = 80084228 (address of ptrClipBuffer)
	 6::800a0ea0 08 80 0a 3c     lui        t2,0x8008
     6::800a0ea4 28 42 4a 25     addiu      t2,t2,0x4228
	 
	 // dereference,
	 // s7 = ptrClipBuffer (altered?)
     6::800a0ea8 00 00 57 8d     lw         s7,0x0(t2)=>DAT_80084228
	 
	 // finalize frame somehow?
     6::800a0eac e4 a9 02 0c     jal        FUN_OVR_226__800aa790                            undefined FUN_OVR_226__800aa790()
     
	 // t8 = backed-up version of P1 ClipBuffer
	 6::800a0eb0 10 00 38 8c     _lw        t8,offset DAT_1f800010(at)                       = ??
                             
	 // at this point, end rendering, return to exe
							 LAB_OVR_226__800a0eb4                           XREF[14]:    OVR_226::800a0d10(j), 
                                                                                          OVR_226::800a0d18(j), 
                                                                                          FUN_OVR_226__800a15c0:800a0f40(j
                                                                                          OVR_226::800a1ea8(j), 
                                                                                          OVR_226::800a2914(j), 
                                                                                          OVR_226::800a3700(j), 
                                                                                          OVR_226::800a418c(j), 
                                                                                          OVR_226::800a4ff8(j), 
                                                                                          OVR_226::800a5e6c(j), 
                                                                                          OVR_226::800a6f98(j), 
                                                                                          OVR_226::800a7bb8(j), 
                                                                                          OVR_226::800a8bb8(j), 
                                                                                          OVR_226::800a97d8(j), 
                                                                                          OVR_226::800aa858(j)  
     // set new primMem + 0x14 (unk??)
	 6::800a0eb4 14 00 fd ac     sw         sp,0x14(a3)
	 
	 // restore $sp
     6::800a0eb8 38 00 3d 8c     lw         sp,offset DAT_1f800038(at)                       = ??
	 
	 // set new primMem curr
     6::800a0ebc 0c 00 e2 ac     sw         v0,0xc(a3)
	 
	 // restore registers from stack memory
     6::800a0ec0 38 00 bf 8f     lw         ra,0x38(sp)
     6::800a0ec4 34 00 be 8f     lw         s8,0x34(sp)
     6::800a0ec8 30 00 bc 8f     lw         gp,0x30(sp)
     6::800a0ecc 2c 00 b7 8f     lw         s7,0x2c(sp)
     6::800a0ed0 28 00 b6 8f     lw         s6,0x28(sp)
     6::800a0ed4 24 00 b5 8f     lw         s5,0x24(sp)
     6::800a0ed8 20 00 b4 8f     lw         s4,0x20(sp)
     6::800a0edc 1c 00 b3 8f     lw         s3,0x1c(sp)
     6::800a0ee0 18 00 b2 8f     lw         s2,0x18(sp)
     6::800a0ee4 14 00 b1 8f     lw         s1,0x14(sp)
     6::800a0ee8 10 00 b0 8f     lw         s0,0x10(sp)
	 
	 // end function
     6::800a0eec 08 00 e0 03     jr         ra
     6::800a0ef0 3c 00 bd 27     _addiu     sp,sp,0x3c
	 
	 
	 // 800a0ef4 -- first JR
                             LAB_OVR_226__800a0ef4                           XREF[2]:     OVR_226::800a0e78(j), 
                                                                                          OVR_226::800ab460(*)  
     
	 // v1 = gGT+0x1808+0x4
	 // v1 = bsp (bsp node)
	 6::800a0ef4 04 00 83 8c     lw         v1,0x4(a0)
	 
                             LAB_OVR_226__800a0ef8                           XREF[1]:     OVR_226::800a13f8(j)  
     
	 // if finished, jump back to entry function, back to the main loop
	 6::800a0ef8 e3 ff 80 10     beq        a0,zero,LAB_OVR_226__800a0e88
     6::800a0efc 00 00 00 00     _nop
	 
	 // t8 = bsp->ptrQuadblocks (v1->0x1c)
     6::800a0f00 1c 00 78 8c     lw         t8,0x1c(v1)
	 
	 // t9 = bsp->numQuadblocks (v1->0x18)
     6::800a0f04 18 00 79 8c     lw         t9,0x18(v1)
	 
	 // t2 = 0x1f8000c8 (visFaceList)
     6::800a0f08 c8 00 2a 8c     lw         t2,0xc8(at)
	 
	 // t0 = quadblockID (quadblock->0x3c)
     6::800a0f0c 3c 00 08 97     lhu        t0,0x3c(t8)
	 
	 // 0x1f800068 = t9 (numQuadblocks)
     6::800a0f10 68 00 39 ac     sw         t9,0x68(at)
	 
	 // quadblockID >> 3
	 // bit index of visFaceList, to byte index
     6::800a0f14 c2 48 08 00     srl        t1,t0,0x3
	 
	 // t1 = t1 & 0x1fc
	 // 4 byte alignment, to read int with the quadblock bit,
	 // instead of a char with the quadblock bit
     6::800a0f18 fc 01 29 31     andi       t1,t1,0x1fc
	 
	 // t1 = visFaceList + (quadblockID>>3)&0x1fc,
	 // this is an int that contains the quadblock bit
     6::800a0f1c 21 48 2a 01     addu       t1,t1,t2
	 
	 // 0x1f8000c0 = t1
     6::800a0f20 c0 00 29 ac     sw         t1,0xc0(at)
	 
	 // t1 = value of quadblock flag int
     6::800a0f24 00 00 29 8d     lw         t1,0x0(t1)
	 
	 // quadblockID = quadblockID & 0x1f,
	 // 32 bits in a byte, get which bit our quadblock is, within this int
     6::800a0f28 1f 00 08 31     andi       t0,t0,0x1f
	 
	 // 0x1f8000bc = visFaceList flag bit (within int)
     6::800a0f2c bc 00 28 ac     sw         t0,0xbc(at)
	 
	 // 0x1f8000c4 = visFaceList flag int
     6::800a0f30 c4 00 29 ac     sw         t1,0xc4(at)
	 
	 // first quadblock in a bsp (bsp node) is the lowest bit index,
	 // all other quadblocks are sequential to this one. If the first index
	 // is quadBlockID #3, then the next are guaranteed 4,5,6,7...
	 // so we manipulate bit index without grabbing ID while looping through blocks
	 
	 // loop back here, for every quadblock in the bsp
                             LAB_OVR_226__800a0f34                           XREF[1]:     OVR_226::800a13ec(j)  
     
	 // v1 = 1f800030 (primMem->end)
	 6::800a0f34 30 00 23 8c     lw         v1,0x30(at)
	 
	 // t0 = primMem->curr + 0x2700
     6::800a0f38 00 27 48 24     addiu      t0,v0,0x2700
	 
	 // v1 = primMem->end - (primMem->curr + 0x2700)
     6::800a0f3c 23 18 68 00     subu       v1,v1,t0
	 
	 // if not enough primMem, end rendering and return to EXE
     6::800a0f40 dc ff 60 04     bltz       v1,LAB_OVR_226__800a0eb4
	 
	 // v1 = 0x1f8000bc, visFaceList flag bit (within int)
     6::800a0f44 bc 00 23 8c     _lw        v1,0xbc(at)
	 
	 // t0 = 0x1f8000c4, visFaceList flag int
     6::800a0f48 c4 00 28 8c     lw         t0,0xc4(at)
	 
	 // if bit index is valid, and not negative, jump 6 instructions
     6::800a0f4c 06 00 61 04     bgez       v1,LAB_OVR_226__800a0f68
	 
	 // if bit index is negative, meaning the next bit is in the next int:
	 // go to next int, and reset bit index to 0x1f, highest bit in next int
	 
	 // t1 = 0x1f8000c0
	 6::800a0f50 c0 00 29 8c     _lw        t1,0xc0(at)
	 
	 // v1 = 0x1f (last bit in flag int)
	 6::800a0f54 1f 00 03 24     li         v1,0x1f
	 
	 // t0 = 0x1f8000c0 -> 0x4 (next set of 32 quadblock bits)
     6::800a0f58 04 00 28 8d     lw         t0,0x4(t1)
	 
	 // 0x1f8000c0 += 4
     6::800a0f5c 04 00 29 25     addiu      t1,t1,0x4
     6::800a0f60 c0 00 29 ac     sw         t1,0xc0(at)
	 
	 // t0 = 0x1f8000c0 -> 0x4 (next set of 32 quadblock bits)
     6::800a0f64 c4 00 28 ac     sw         t0,0xc4(at)
	 
	 // valid quadblock to begin with
                             LAB_OVR_226__800a0f68                           XREF[1]:     OVR_226::800a0f4c(j)  
     
	 // int-flag = int-flag << bit flag index
	 6::800a0f68 04 40 68 00     sllv       t0,t0,v1
	 
	 // quadblock bit flag index -= 1,
	 // check bit of next quadblock (since they're all in order)
     6::800a0f6c ff ff 63 24     addiu      v1,v1,-0x1
	 
	 // if rendering this quad is disabled,
	 // then skip the drawing of this quadblock
     6::800a0f70 1b 01 01 05     bgez       t0,LAB_OVR_226__800a13e0
	 
	 // drawing quadblock
	 
	 // 0x1f8000bc = v1, new quadblock flag bit index within int, 
	 // loops 0x1f to 0x0, then goes to next quadblock flag int index
     6::800a0f74 bc 00 23 ac     _sw        v1,0xbc(at)
	 
	 // s8 = 0x1f8001b4 (the scratchpad region cleared in main func)
     6::800a0f78 b4 01 3e 24     addiu      s8,at,0x1b4
	 
	 // s8->0xb4 = 0
     6::800a0f7c b4 00 c0 af     sw         zero,0xb4(s8)
	 
	 // s4 = quadblock->0x0 (index[0,1])
     6::800a0f80 00 00 14 8f     lw         s4,0x0(t8)
	 
	 // s6 = quadblock->0x4 (index[2,3])
     6::800a0f84 04 00 16 8f     lw         s6,0x4(t8)
	 
	 // s3 = s4 & 0xffff
	 // s3 = vertex index[0]
     6::800a0f88 ff ff 93 32     andi       s3,s4,0xffff
	 
	 // s3 = s3 << 4
	 // s3 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a0f8c 00 99 13 00     sll        s3,s3,0x4
	 
	 // s3 = s3 + s7
	 // s3 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a0f90 21 98 77 02     addu       s3,s3,s7
	 
	 // load pos[4] from LevVertex into GTE, (load vertex0)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
     6::800a0f94 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     
	 // s4 = s4 >> 0x10
	 // s4 = vertex index[1]
	 6::800a0f9c 02 a4 14 00     srl        s4,s4,0x10
	 
	 // s4 = s4 << 4
	 // s4 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a0fa0 00 a1 14 00     sll        s4,s4,0x4
	 
	 // s4 = s4 + s7
	 // s4 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a0fa4 21 a0 97 02     addu       s4,s4,s7
     
	 // load pos[4] from LevVertex into GTE, (load vertex1)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
	 6::800a0fa8 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     
	 // s5 = s6 & 0xffff
	 // s5 = vertex index[2]
	 6::800a0fb0 ff ff d5 32     andi       s5,s6,0xffff
	 
	 // s5 = s5 << 4
	 // s5 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a0fb4 00 a9 15 00     sll        s5,s5,0x4
	 
	 // s5 = s5 + s7
	 // s5 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a0fb8 21 a8 b7 02     addu       s5,s5,s7
     
	 // load pos[4] from LevVertex into GTE, (load vertex2)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
	 6::800a0fbc 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     
	 // s6 = s6 >> 0x10
	 // s6 = vertex index[3]
	 6::800a0fc4 02 b4 16 00     srl        s6,s6,0x10

	 // s6 = s6 << 4
	 // s6 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a0fc8 00 b1 16 00     sll        s6,s6,0x4
	 
	 // perspective projection on triangle in GTE
     6::800a0fcc 30 00 28 4a     RTPT
	 
	 // s6 = s6 + s7
	 // s6 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a0fd0 21 b0 d7 02     addu       s6,s6,s7
	 
	 // get color_hi from each vertex
     6::800a0fd4 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a0fd8 08 00 90 8e     lw         s0,0x8(s4)
     6::800a0fdc 08 00 b1 8e     lw         s1,0x8(s5)
	 
	 // store color_hi from each vertex on scratchpad (0x1f8001b4)
     6::800a0fe0 08 00 cf af     sw         t7,0x8(s8)
     6::800a0fe4 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a0fe8 30 00 d1 af     sw         s1,0x30(s8)
	 
	 /*
	 {
		 0x00 - VXY0
		 0x04 - VZ0
		 0x06 - drawOrder (see SH)
		 0x08 - color0
		 0x0C - SXY0
		 0x10 - SZ1 (ghidra typo?)
		 
		 0x14 - VXY1
		 0x18 - VZ1
		 0x1A - drawOrder (see SH)
		 0x1C - color1
		 0x20 - SXY1
		 0x24 - SZ2 (ghidra typo?)
		 
		 0x28 - VXY2
		 0x2C - VZ2
		 0x2E - drawOrder (see SH)
		 0x30 - color2
		 0x34 - SXY2
		 0x38 - SZ3 (ghidra typo?)
	 }
	 */
	 
	 // dump results from GTE to scratchpad (0x1f8001b4)
     6::800a0fec 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a0ff0 10 00 d1 eb     gte_stSZ1  0x10(s8)
     6::800a0ff4 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a0ff8 24 00 d2 eb     gte_stSZ2  0x24(s8)
     6::800a0ffc 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a1000 38 00 d3 eb     gte_stSZ3  0x38(s8)
     6::800a1004 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a1008 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a100c 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a1010 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a1014 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a1018 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
	 
	 // v1 = draw_order_low (quadblock->0x14)
     6::800a101c 14 00 03 8f     lw         v1,0x14(t8)
	 
	 // color_hi vertex[3]
     6::800a1020 08 00 d2 8e     lw         s2,0x8(s6)
	 
	 // load pos[4] from LevVertex into GTE, (load vertex0)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
     6::800a1024 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     
	 
	 // s3 = scratchpad ptr vertex result [0]
	 // s4 = scratchpad ptr vertex result [1]
	 6::800a102c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a1030 14 00 d4 27     addiu      s4,s8,0x14
     
	 // perspective projection on triangle in GTE
	 6::800a1034 01 00 18 4a     RTPS
     
	 // s5 = scratchpad ptr vertex result [2]
	 // s6 = scratchpad ptr vertex result [3]
	 6::800a1038 28 00 d5 27     addiu      s5,s8,0x28
     6::800a103c 3c 00 d6 27     addiu      s6,s8,0x3c
	 
	 // 1f80007c = draw_order_low
     6::800a1040 7c 00 23 ac     sw         v1,0x7c(at)
	 
	 // 0x3C - 0x50,
	 // store result of fourth vertex on scratchpad,
	 // just like the other three before it
     6::800a1044 44 00 d2 af     sw         s2,0x44(s8)
     6::800a1048 48 00 ce eb     gte_stSXY2 0x48(s8)
     6::800a104c 4c 00 d3 eb     gte_stSZ3  0x4c(s8)
     6::800a1050 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a1054 40 00 c1 eb     gte_stVZ0  0x40(s8)
	 
	 // v1 = quadblock->ptr_tex_low
     6::800a1058 40 00 03 8f     lw         v1,0x40(t8)
	 
	 // 1f800194 = 0
     6::800a105c 94 01 20 ac     sw         zero,0x194(at)
	 
	 // load 3 registers of ptr_tex_low
     6::800a1060 00 00 68 8c     lw         t0,0x0(v1)
     6::800a1064 04 00 69 8c     lw         t1,0x4(v1)
     6::800a1068 08 00 6a 8c     lw         t2,0x8(v1)
	 
	 // store 3 registers of ptr_tex_low, 1f8001a0
     6::800a106c a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a1070 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a1074 a8 01 2a ac     sw         t2,0x1a8(at)
	 
	 // store drawOrder info in each vertex on scratchpad
     6::800a1078 06 00 68 a6     sh         t0,0x6(s3)
     6::800a107c 06 00 89 a6     sh         t1,0x6(s4)
     6::800a1080 06 00 aa a6     sh         t2,0x6(s5)
	 
     6::800a1084 02 54 0a 00     srl        t2,t2,0x10
     6::800a1088 06 00 ca a6     sh         t2,0x6(s6)
	 
     6::800a108c 00 80 0b        read_sz_   t3,t4,t5,t6
                 48 00 88 
                 0c 48 00 
     
	 6::800a109c 23 18 6c 01     subu       v1,t3,t4
     6::800a10a0 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a10ac
     6::800a10a4 21 e0 60 01     _move      gp,t3
     6::800a10a8 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a10ac                           XREF[1]:     OVR_226::800a10a0(j)  
     6::800a10ac 23 18 8d 03     subu       v1,gp,t5
     6::800a10b0 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a10bc
     6::800a10b4 7c 00 29 80     _lb        t1,0x7c(at)
     6::800a10b8 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a10bc                           XREF[1]:     OVR_226::800a10b0(j)  
     6::800a10bc 23 18 8e 03     subu       v1,gp,t6
     6::800a10c0 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a10cc
     6::800a10c4 82 e1 1c 00     _srl       gp,gp,0x6
     6::800a10c8 82 e1 0e 00     srl        gp,t6,0x6
                             LAB_OVR_226__800a10cc                           XREF[1]:     OVR_226::800a10c0(j)  
     6::800a10cc 21 e0 89 03     addu       gp,gp,t1
     6::800a10d0 14 00 29 8c     lw         t1,0x14(at)
     6::800a10d4 80 e0 1c 00     sll        gp,gp,0x2
     6::800a10d8 21 e0 85 03     addu       gp,gp,a1
     6::800a10dc 23 88 69 01     subu       s1,t3,t1
     6::800a10e0 23 90 89 01     subu       s2,t4,t1
     6::800a10e4 23 78 a9 01     subu       t7,t5,t1
     6::800a10e8 23 80 c9 01     subu       s0,t6,t1
     6::800a10ec 42 8f 11 00     srl        s1,s1,0x1d
     6::800a10f0 04 00 31 32     andi       s1,s1,0x4
     6::800a10f4 02 97 12 00     srl        s2,s2,0x1c
     6::800a10f8 08 00 52 32     andi       s2,s2,0x8
     6::800a10fc 25 88 32 02     or         s1,s1,s2
     6::800a1100 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a1104 10 00 ef 31     andi       t7,t7,0x10
     6::800a1108 25 88 2f 02     or         s1,s1,t7
     6::800a110c 82 86 10 00     srl        s0,s0,0x1a
     6::800a1110 20 00 10 32     andi       s0,s0,0x20
     6::800a1114 25 88 30 02     or         s1,s1,s0
     6::800a1118 87 00 20 12     beq        s1,zero,LAB_OVR_226__800a1338
     6::800a111c 21 c8 20 00     _move      t9,at
     6::800a1120 21 58 21 02     addu       t3,s1,at
     6::800a1124 48 01 6b 8d     lw         t3,0x148(t3)
     6::800a1128 08 00 14 8f     lw         s4,0x8(t8)
     6::800a112c 0c 00 16 8f     lw         s6,0xc(t8)
     6::800a1130 ff ff 93 32     andi       s3,s4,0xffff
     6::800a1134 00 99 13 00     sll        s3,s3,0x4
     6::800a1138 21 98 77 02     addu       s3,s3,s7
     6::800a113c 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a1144 02 a4 14 00     srl        s4,s4,0x10
     6::800a1148 00 a1 14 00     sll        s4,s4,0x4
     6::800a114c 21 a0 97 02     addu       s4,s4,s7
     6::800a1150 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a1158 ff ff d5 32     andi       s5,s6,0xffff
     6::800a115c 00 a9 15 00     sll        s5,s5,0x4
     6::800a1160 21 a8 b7 02     addu       s5,s5,s7
     6::800a1164 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a116c 02 b4 16 00     srl        s6,s6,0x10
     6::800a1170 00 b1 16 00     sll        s6,s6,0x4
     6::800a1174 30 00 28 4a     RTPT
     6::800a1178 21 b0 d7 02     addu       s6,s6,s7
     6::800a117c a0 00 33 ac     sw         s3,0xa0(at)
     6::800a1180 a4 00 34 ac     sw         s4,0xa4(at)
     6::800a1184 a8 00 35 ac     sw         s5,0xa8(at)
     6::800a1188 ac 00 36 ac     sw         s6,0xac(at)
     6::800a118c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a1190 08 00 90 8e     lw         s0,0x8(s4)
     6::800a1194 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a1198 58 00 cf af     sw         t7,0x58(s8)
     6::800a119c 6c 00 d0 af     sw         s0,0x6c(s8)
     6::800a11a0 80 00 d1 af     sw         s1,0x80(s8)
     6::800a11a4 10 00 13 87     lh         s3,0x10(t8)
     6::800a11a8 5c 00 cc eb     gte_stSXY0 0x5c(s8)
     6::800a11ac 60 00 d1 eb     gte_stSZ1  0x60(s8)
     6::800a11b0 70 00 cd eb     gte_stSXY1 0x70(s8)
     6::800a11b4 74 00 d2 eb     gte_stSZ2  0x74(s8)
     6::800a11b8 84 00 ce eb     gte_stSXY2 0x84(s8)
     6::800a11bc 88 00 d3 eb     gte_stSZ3  0x88(s8)
     6::800a11c0 50 00 c0 eb     sVXY0      0x50(s8)
     6::800a11c4 54 00 c1 eb     gte_stVZ0  0x54(s8)
     6::800a11c8 64 00 c2 eb     gte_stVXY1 0x64(s8)
     6::800a11cc 68 00 c3 eb     gte_stVZ1  0x68(s8)
     6::800a11d0 78 00 c4 eb     gte_stVXY2 0x78(s8)
     6::800a11d4 7c 00 c5 eb     gte_stVZ2  0x7c(s8)
     6::800a11d8 00 99 13 00     sll        s3,s3,0x4
     6::800a11dc 21 98 77 02     addu       s3,s3,s7
     6::800a11e0 00 00 c0        ldv01      s6,s3                                            void gte_ldv01(SVECTOR * r0, SVE
                 ca 04 00 
                 c1 ca 00 
     
	 // v1 = 800a13e0
	 6::800a11f0 0a 80 03 3c     lui        v1,0x800a
     6::800a11f4 e0 13 63 24     addiu      v1,v1,0x13e0
	 
     6::800a11f8 30 00 28 4a     RTPT
	 
	 // fake return address, to return back to loop
     6::800a11fc 3c 00 23 af     sw         v1=>LAB_OVR_226__800a13e0,0x3c(t9)
	 
     6::800a1200 04 00 39 27     addiu      t9,t9,0x4
     6::800a1204 b0 00 33 ac     sw         s3,0xb0(at)
     6::800a1208 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a120c 08 00 70 8e     lw         s0,0x8(s3)
     6::800a1210 94 00 d2 af     sw         s2,0x94(s8)
     6::800a1214 a8 00 d0 af     sw         s0,0xa8(s8)
     6::800a1218 98 00 cc eb     gte_stSXY0 0x98(s8)
     6::800a121c 9c 00 d1 eb     gte_stSZ1  0x9c(s8)
     6::800a1220 ac 00 cd eb     gte_stSXY1 0xac(s8)
     6::800a1224 b0 00 d2 eb     gte_stSZ2  0xb0(s8)
     6::800a1228 8c 00 c0 eb     sVXY0      0x8c(s8)
     6::800a122c 90 00 c1 eb     gte_stVZ0  0x90(s8)
     6::800a1230 a0 00 c2 eb     gte_stVXY1 0xa0(s8)
     6::800a1234 a4 00 c3 eb     gte_stVZ1  0xa4(s8)
     6::800a1238 a0 00 2d 8c     lw         t5,0xa0(at)
     6::800a123c 50 00 cf 27     addiu      t7,s8,0x50
     6::800a1240 00 00 d0 27     addiu      s0,s8,0x0
     6::800a1244 02 85 02 0c     jal        FUN_OVR_226__800a1408                            undefined FUN_OVR_226__800a1408()
     6::800a1248 14 00 d2 27     _addiu     s2,s8,0x14
     6::800a124c a4 00 2d 8c     lw         t5,0xa4(at)
     6::800a1250 64 00 cf 27     addiu      t7,s8,0x64
     6::800a1254 00 00 d0 27     addiu      s0,s8,0x0
     6::800a1258 02 85 02 0c     jal        FUN_OVR_226__800a1408                            undefined FUN_OVR_226__800a1408()
     6::800a125c 28 00 d2 27     _addiu     s2,s8,0x28
     6::800a1260 a8 00 2d 8c     lw         t5,0xa8(at)
     6::800a1264 78 00 cf 27     addiu      t7,s8,0x78
     6::800a1268 14 00 d0 27     addiu      s0,s8,0x14
     6::800a126c 02 85 02 0c     jal        FUN_OVR_226__800a1408                            undefined FUN_OVR_226__800a1408()
     6::800a1270 28 00 d2 27     _addiu     s2,s8,0x28
     6::800a1274 ac 00 2d 8c     lw         t5,0xac(at)
     6::800a1278 8c 00 cf 27     addiu      t7,s8,0x8c
     6::800a127c 14 00 d0 27     addiu      s0,s8,0x14
     6::800a1280 02 85 02 0c     jal        FUN_OVR_226__800a1408                            undefined FUN_OVR_226__800a1408()
     6::800a1284 3c 00 d2 27     _addiu     s2,s8,0x3c
     6::800a1288 b0 00 2d 8c     lw         t5,0xb0(at)
     6::800a128c a0 00 cf 27     addiu      t7,s8,0xa0
     6::800a1290 28 00 d0 27     addiu      s0,s8,0x28
     6::800a1294 02 85 02 0c     jal        FUN_OVR_226__800a1408                            undefined FUN_OVR_226__800a1408()
     6::800a1298 3c 00 d2 27     _addiu     s2,s8,0x3c
     6::800a129c 06 00 c3 93     lbu        v1,0x6(s8)
     6::800a12a0 1a 00 c8 93     lbu        t0,0x1a(s8)
     6::800a12a4 2e 00 c9 93     lbu        t1,0x2e(s8)
     6::800a12a8 42 00 ca 93     lbu        t2,0x42(s8)
     6::800a12ac 21 78 68 00     addu       t7,v1,t0
     6::800a12b0 21 80 69 00     addu       s0,v1,t1
     6::800a12b4 21 88 09 01     addu       s1,t0,t1
     6::800a12b8 21 90 0a 01     addu       s2,t0,t2
     6::800a12bc 21 18 2a 01     addu       v1,t1,t2
     6::800a12c0 43 78 0f 00     sra        t7,t7,0x1
     6::800a12c4 43 80 10 00     sra        s0,s0,0x1
     6::800a12c8 43 88 11 00     sra        s1,s1,0x1
     6::800a12cc 43 90 12 00     sra        s2,s2,0x1
     6::800a12d0 43 18 03 00     sra        v1,v1,0x1
     6::800a12d4 56 00 cf a3     sb         t7,0x56(s8)
     6::800a12d8 6a 00 d0 a3     sb         s0,0x6a(s8)
     6::800a12dc 7e 00 d1 a3     sb         s1,0x7e(s8)
     6::800a12e0 92 00 d2 a3     sb         s2,0x92(s8)
     6::800a12e4 a6 00 c3 a3     sb         v1,0xa6(s8)
     6::800a12e8 07 00 c3 93     lbu        v1,0x7(s8)
     6::800a12ec 1b 00 c8 93     lbu        t0,0x1b(s8)
     6::800a12f0 2f 00 c9 93     lbu        t1,0x2f(s8)
     6::800a12f4 43 00 ca 93     lbu        t2,0x43(s8)
     6::800a12f8 21 78 68 00     addu       t7,v1,t0
     6::800a12fc 21 80 69 00     addu       s0,v1,t1
     6::800a1300 21 88 09 01     addu       s1,t0,t1
     6::800a1304 21 90 0a 01     addu       s2,t0,t2
     6::800a1308 21 18 2a 01     addu       v1,t1,t2
     6::800a130c 43 78 0f 00     sra        t7,t7,0x1
     6::800a1310 43 80 10 00     sra        s0,s0,0x1
     6::800a1314 43 88 11 00     sra        s1,s1,0x1
     6::800a1318 43 90 12 00     sra        s2,s2,0x1
     6::800a131c 43 18 03 00     sra        v1,v1,0x1
     6::800a1320 57 00 cf a3     sb         t7,0x57(s8)
     6::800a1324 6b 00 d0 a3     sb         s0,0x6b(s8)
     6::800a1328 7f 00 d1 a3     sb         s1,0x7f(s8)
     6::800a132c 93 00 d2 a3     sb         s2,0x93(s8)
     6::800a1330 08 00 60 01     jr         t3
     6::800a1334 a7 00 c3 a3     _sb        v1,0xa7(s8)
                             LAB_OVR_226__800a1338                           XREF[1]:     OVR_226::800a1118(j)  
     6::800a1338 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a133c 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a1340 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a1344 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a1348 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a134c 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a1350 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a1354 06 00 40 4b     NCLIP
     6::800a1358 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a135c 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a1360 23 78 68 01     subu       t7,t3,t0
     6::800a1364 23 80 88 01     subu       s0,t4,t0
     6::800a1368 23 88 a8 01     subu       s1,t5,t0
     6::800a136c 23 90 c8 01     subu       s2,t6,t0
     6::800a1370 00 c0 08 48     gte_stMAC0 t0
     6::800a1374 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a1378 22 40 08 00     sub        t0,zero,t0
     6::800a137c 25 40 09 01     or         t0,t0,t1
     6::800a1380 06 00 40 4b     NCLIP
     6::800a1384 24 18 6c 01     and        v1,t3,t4
     6::800a1388 24 18 6d 00     and        v1,v1,t5
     6::800a138c 24 18 6e 00     and        v1,v1,t6
     6::800a1390 25 78 f0 01     or         t7,t7,s0
     6::800a1394 25 78 f1 01     or         t7,t7,s1
     6::800a1398 27 78 f2 01     nor        t7,t7,s2
     6::800a139c 25 78 e3 01     or         t7,t7,v1
     6::800a13a0 0f 00 e0 05     bltz       t7,LAB_OVR_226__800a13e0
     6::800a13a4 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a13a8 0d 00 e0 05     bltz       t7,LAB_OVR_226__800a13e0
     6::800a13ac 00 c0 03 48     _gte_stM   v1
     6::800a13b0 c2 47 08 00     srl        t0,t0,0x1f
     6::800a13b4 80 40 08 00     sll        t0,t0,0x2
     6::800a13b8 25 18 69 00     or         v1,v1,t1
     6::800a13bc c2 1f 03 00     srl        v1,v1,0x1f
     6::800a13c0 c0 18 03 00     sll        v1,v1,0x3
     6::800a13c4 25 18 68 00     or         v1,v1,t0
     6::800a13c8 05 00 60 10     beq        v1,zero,LAB_OVR_226__800a13e0
     6::800a13cc 21 18 61 00     _addu      v1,v1,at
     6::800a13d0 84 01 63 8c     lw         v1,0x184(v1)
     6::800a13d4 00 00 00 00     nop
     6::800a13d8 09 f8 60 00     jalr       v1
     6::800a13dc 00 00 00 00     _nop
	 
	 
                             LAB_OVR_226__800a13e0                           XREF[6]:     OVR_226::800a0f70(j), 
                               
	 // this happens after a quadblock is drawn,
	 // or after a quadblock is determined as "disabled"
	 
	 
     // t9 = 0x1f800068 (numQuadblocks)                                                                                    OVR_226::800a178c(j)  
     6::800a13e0 68 00 39 8c     lw         t9,0x68(at)
	 
	 // t8 (ptrQuadblocks) += 0x5c (size of quadblock)
     6::800a13e4 5c 00 18 27     addiu      t8,t8,0x5c
     
	 // subtract one from numQuadblocks (loop through all)
	 6::800a13e8 ff ff 39 27     addiu      t9,t9,-0x1
	 
	 // if more quadblocks remain, jump back to 
	 // region in first JR to loop to next block
     6::800a13ec d1 fe 20 1f     bgtz       t9,LAB_OVR_226__800a0f34
	 
	 // save new numQuadblocks, 0x1f800068 = t9
     6::800a13f0 68 00 39 ac     _sw        t9,0x68(at)
	 
	 // if no quadblocks remain
	 
	 // a0 = dereference a0,
	 // bsp = bsp->next
     6::800a13f4 00 00 84 8c     lw         a0,0x0(a0)
	 
	 // if not out of bsp, jmp back to main loop
     6::800a13f8 bf fe 01 04     bgez       zero,LAB_OVR_226__800a0ef8
	 
	 // v1 = gGT+0x1808+0x4
	 // v1 = bsp (bsp node)
     6::800a13fc 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_226__800a1400                           XREF[6]:     FUN_OVR_226__800a18c0:800a1934(j
                                                                                          FUN_OVR_226__800a18c0:800a193c(j
                                                                                          FUN_OVR_226__800a18c0:800a1970(j
                                                                                          OVR_226::800a1a7c(j), 
                                                                                          OVR_226::800a1a84(j), 
     // if out of bsp, rendering is over, return to EXE                                                                                     OVR_226::800a1ab0(j)  
     6::800a1400 08 00 e0 03     jr         ra
     6::800a1404 00 00 00 00     _nop
	 
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a1408()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a1408                           XREF[5]:     FUN_OVR_226__800a15c0:800a1244(c
                                                                                          FUN_OVR_226__800a15c0:800a1258(c
                                                                                          FUN_OVR_226__800a15c0:800a126c(c
                                                                                          FUN_OVR_226__800a15c0:800a1280(c
                                                                                          FUN_OVR_226__800a15c0:800a1294(c
     6::800a1408 2c 00 2a 8c     lw         t2,0x2c(at)
     6::800a140c 10 00 e3 8d     lw         v1,0x10(t7)
     6::800a1410 00 00 08 86     lh         t0,0x0(s0)
     6::800a1414 23 18 6a 00     subu       v1,v1,t2
     6::800a1418 80 18 03 00     sll        v1,v1,0x2
     6::800a141c 43 00 60 04     bltz       v1,LAB_OVR_226__800a152c
     6::800a1420 00 f0 6a 24     _addiu     t2,v1,-0x1000
     6::800a1424 00 00 49 86     lh         t1,0x0(s2)
     6::800a1428 00 40 83 48     gte_ldIR0  v1
     6::800a142c 21 18 09 01     addu       v1,t0,t1
     6::800a1430 43 18 03 00     sra        v1,v1,0x1
     6::800a1434 02 00 08 86     lh         t0,0x2(s0)
     6::800a1438 02 00 49 86     lh         t1,0x2(s2)
     6::800a143c b4 00 23 a4     sh         v1,0xb4(at)
     6::800a1440 21 18 09 01     addu       v1,t0,t1
     6::800a1444 43 18 03 00     sra        v1,v1,0x1
     6::800a1448 04 00 08 86     lh         t0,0x4(s0)
     6::800a144c 04 00 49 86     lh         t1,0x4(s2)
     6::800a1450 b6 00 23 a4     sh         v1,0xb6(at)
     6::800a1454 21 18 09 01     addu       v1,t0,t1
     6::800a1458 43 18 03 00     sra        v1,v1,0x1
     6::800a145c b8 00 23 ac     sw         v1,0xb8(at)
     6::800a1460 27 00 41 05     bgez       t2,LAB_OVR_226__800a1500
     6::800a1464 0c 00 a9 8d     _lw        t1,0xc(t5)
     6::800a1468 08 00 e6 c9     gte_ldRGB  0x8(t7)
     6::800a146c 00 19 09 00     sll        v1,t1,0x4
     6::800a1470 02 44 03 00     srl        t0,v1,0x10
     6::800a1474 02 4a 03 00     srl        t1,v1,0x8
     6::800a1478 f0 0f 08 31     andi       t0,t0,0xff0
     6::800a147c f0 0f 29 31     andi       t1,t1,0xff0
     6::800a1480 f0 0f 63 30     andi       v1,v1,0xff0
     6::800a1484 00 b8 c8 48     gte_ldBFC  t0
     6::800a1488 00 b0 c9 48     gte_ldGFC  t1
     6::800a148c 00 a8 c3 48     gte_ldRFC  v1
     6::800a1490 00 00 00        nDPCS
                 00 00 00 
                 00 00 10 
     6::800a149c 00 b0 09 48     gte_stRGB2 t1
     6::800a14a0 00 00 e3 85     lh         v1,0x0(t7)
     6::800a14a4 b4 00 28 84     lh         t0,0xb4(at)
     6::800a14a8 00 c8 83 48     gte_ldMAC1 v1
     6::800a14ac 23 40 03 01     subu       t0,t0,v1
     6::800a14b0 00 48 88 48     gte_ldIR1  t0
     6::800a14b4 02 00 e3 85     lh         v1,0x2(t7)
     6::800a14b8 b6 00 28 84     lh         t0,0xb6(at)
     6::800a14bc 00 d0 83 48     gte_ldMAC2 v1
     6::800a14c0 23 40 03 01     subu       t0,t0,v1
     6::800a14c4 00 50 88 48     gte_ldIR2  t0
     6::800a14c8 04 00 e3 85     lh         v1,0x4(t7)
     6::800a14cc b8 00 28 84     lh         t0,0xb8(at)
     6::800a14d0 00 d8 83 48     gte_ldMAC3 v1
     6::800a14d4 23 40 03 01     subu       t0,t0,v1
     6::800a14d8 00 58 88 48     gte_ldIR3  t0
     6::800a14dc 00 00 00        nGPL12
                 00 00 00 
                 00 00 3e 
     6::800a14e8 00 c8 03        read_mt    v1,t0,t2
                 48 00 d0 
                 08 48 00 
     6::800a14f4 b4 00 23 a4     sh         v1,0xb4(at)
     6::800a14f8 b6 00 28 a4     sh         t0,0xb6(at)
     6::800a14fc b8 00 2a ac     sw         t2,0xb8(at)
                             LAB_OVR_226__800a1500                           XREF[1]:     OVR_226::800a1460(j)  
     6::800a1500 b4 00 23 8c     lw         v1,0xb4(at)
     6::800a1504 b8 00 28 8c     lw         t0,0xb8(at)
     6::800a1508 00 00 83 48     gte_ldVXY0 v1
     6::800a150c 00 08 88 48     gte_ldVZ0  t0
     6::800a1510 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a1514 04 00 e8 a5     sh         t0,0x4(t7)
     6::800a1518 01 00 18 4a     RTPS
     6::800a151c 08 00 e9 ad     sw         t1,0x8(t7)
     6::800a1520 0c 00 ee e9     gte_stSXY2 0xc(t7)
     6::800a1524 08 00 e0 03     jr         ra
     6::800a1528 10 00 f3 e9     _gte_stSZ3 0x10(t7)
                             LAB_OVR_226__800a152c                           XREF[1]:     OVR_226::800a141c(j)  
     6::800a152c 08 00 e0 03     jr         ra
     6::800a1530 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a1534()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a1534                           XREF[4]:     FUN_OVR_226__800a15c0:800a160c(j
                                                                                          FUN_OVR_226__800a15c0:800a16a4(c
                                                                                          FUN_OVR_226__800a15c0:800a16cc(c
                                                                                          FUN_OVR_226__800a15c0:800a1798(c
     6::800a1534 00 00 d3 27     addiu      s3,s8,0x0
     6::800a1538 50 00 d4 27     addiu      s4,s8,0x50
     6::800a153c 64 00 d5 27     addiu      s5,s8,0x64
     6::800a1540 df 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a1544 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a1548()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a1548                           XREF[6]:     FUN_OVR_226__800a15c0:800a1614(c
                                                                                          FUN_OVR_226__800a15c0:800a16b4(j
                                                                                          FUN_OVR_226__800a15c0:800a16c4(c
                                                                                          FUN_OVR_226__800a15c0:800a16f4(c
                                                                                          FUN_OVR_226__800a15c0:800a1714(c
                                                                                          FUN_OVR_226__800a15c0:800a17a8(c
     6::800a1548 50 00 d3 27     addiu      s3,s8,0x50
     6::800a154c 14 00 d4 27     addiu      s4,s8,0x14
     6::800a1550 78 00 d5 27     addiu      s5,s8,0x78
     6::800a1554 da 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a1558 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a155c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a155c                           XREF[6]:     FUN_OVR_226__800a15c0:800a163c(c
                                                                                          FUN_OVR_226__800a15c0:800a169c(c
                                                                                          FUN_OVR_226__800a15c0:800a16dc(j
                                                                                          FUN_OVR_226__800a15c0:800a16ec(c
                                                                                          FUN_OVR_226__800a15c0:800a171c(c
                                                                                          FUN_OVR_226__800a15c0:800a17b8(c
     6::800a155c 64 00 d3 27     addiu      s3,s8,0x64
     6::800a1560 78 00 d4 27     addiu      s4,s8,0x78
     6::800a1564 28 00 d5 27     addiu      s5,s8,0x28
     6::800a1568 d5 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a156c a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a1570                           XREF[4]:     OVR_226::800a168c(j), 
                                                                                          OVR_226::800a1704(j), 
                                                                                          OVR_226::800a172c(j), 
                                                                                          OVR_226::800a17d0(j)  
     6::800a1570 78 00 d3 27     addiu      s3,s8,0x78
     6::800a1574 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a1578 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a157c d0 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a1580 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a1584()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a1584                           XREF[2]:     FUN_OVR_226__800a15c0:800a1634(c
                                                                                          FUN_OVR_226__800a15c0:800a170c(c
     6::800a1584 64 00 d3 27     addiu      s3,s8,0x64
     6::800a1588 00 00 d4 27     addiu      s4,s8,0x0
     6::800a158c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a1590 cb 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a1594 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a1598()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a1598                           XREF[2]:     FUN_OVR_226__800a15c0:800a164c(j
                                                                                          FUN_OVR_226__800a15c0:800a16bc(c
     6::800a1598 14 00 d3 27     addiu      s3,s8,0x14
     6::800a159c 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a15a0 78 00 d5 27     addiu      s5,s8,0x78
     6::800a15a4 c6 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a15a8 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a15ac()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a15ac                           XREF[2]:     FUN_OVR_226__800a15c0:800a161c(c
                                                                                          FUN_OVR_226__800a15c0:800a16e4(c
     6::800a15ac 28 00 d3 27     addiu      s3,s8,0x28
     6::800a15b0 00 00 d4 27     addiu      s4,s8,0x0
     6::800a15b4 78 00 d5 27     addiu      s5,s8,0x78
     6::800a15b8 c1 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a15bc 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a15c0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a15c0                           XREF[2]:     OVR_226::800a162c(j), 
                                                                                          OVR_226::800a1694(c)  
     6::800a15c0 28 00 d3 27     addiu      s3,s8,0x28
     6::800a15c4 78 00 d4 27     addiu      s4,s8,0x78
     6::800a15c8 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a15cc bc 00 01 04     bgez       zero,FUN_OVR_226__800a18c0
     6::800a15d0 8c 00 d6 27     _addiu     s6,s8,0x8c
                             LAB_OVR_226__800a15d4                           XREF[2]:     OVR_226::800a0e60(*), 
                                                                                          OVR_226::800ab4e0(*)  
     6::800a15d4 50 00 d3 27     addiu      s3,s8,0x50
     6::800a15d8 14 00 d4 27     addiu      s4,s8,0x14
     6::800a15dc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a15e0 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a15e4 30 86 02 0c     jal        FUN_OVR_226__800a18c0                            undefined FUN_OVR_226__800a18c0()
     6::800a15e8 0c 00 0a 24     _li        t2,0xc
     6::800a15ec 64 00 d3 27     addiu      s3,s8,0x64
     6::800a15f0 78 00 d4 27     addiu      s4,s8,0x78
     6::800a15f4 28 00 d5 27     addiu      s5,s8,0x28
     6::800a15f8 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a15fc 30 86 02 0c     jal        FUN_OVR_226__800a18c0                            undefined FUN_OVR_226__800a18c0()
     6::800a1600 0c 00 0a 24     _li        t2,0xc
     6::800a1604 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1608 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a160c c9 ff 01 04     bgez       zero,FUN_OVR_226__800a1534
     6::800a1610 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a1614                           XREF[2]:     OVR_226::800a0e60(*), 
                                                                                          OVR_226::800ab4e4(*)  
     6::800a1614 52 85 02 0c     jal        FUN_OVR_226__800a1548                            undefined FUN_OVR_226__800a1548()
     6::800a1618 0c 00 0a 24     _li        t2,0xc
     6::800a161c 6b 85 02 0c     jal        FUN_OVR_226__800a15ac                            undefined FUN_OVR_226__800a15ac()
     6::800a1620 0c 00 0a 24     _li        t2,0xc
     6::800a1624 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1628 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a162c e4 ff 01 04     bgez       zero,FUN_OVR_226__800a15c0
     6::800a1630 0c 00 0a 24     _li        t2,0xc
     6::800a1634 61 85 02 0c     jal        FUN_OVR_226__800a1584                            undefined FUN_OVR_226__800a1584()
     6::800a1638 0c 00 0a 24     _li        t2,0xc
     6::800a163c 57 85 02 0c     jal        FUN_OVR_226__800a155c                            undefined FUN_OVR_226__800a155c()
     6::800a1640 0c 00 0a 24     _li        t2,0xc
     6::800a1644 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1648 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a164c d2 ff 01 04     bgez       zero,FUN_OVR_226__800a1598
     6::800a1650 0c 00 0a 24     _li        t2,0xc
     6::800a1654 00 00 d3 27     addiu      s3,s8,0x0
     6::800a1658 14 00 d4 27     addiu      s4,s8,0x14
     6::800a165c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a1660 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a1664 30 86 02 0c     jal        FUN_OVR_226__800a18c0                            undefined FUN_OVR_226__800a18c0()
     6::800a1668 0c 00 0a 24     _li        t2,0xc
     6::800a166c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a1670 78 00 d4 27     addiu      s4,s8,0x78
     6::800a1674 28 00 d5 27     addiu      s5,s8,0x28
     6::800a1678 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a167c 30 86 02 0c     jal        FUN_OVR_226__800a18c0                            undefined FUN_OVR_226__800a18c0()
     6::800a1680 0c 00 0a 24     _li        t2,0xc
     6::800a1684 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1688 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a168c b8 ff 01 04     bgez       zero,LAB_OVR_226__800a1570
     6::800a1690 0c 00 0a 24     _li        t2,0xc
     6::800a1694 70 85 02 0c     jal        FUN_OVR_226__800a15c0                            undefined FUN_OVR_226__800a15c0()
     6::800a1698 0c 00 0a 24     _li        t2,0xc
     6::800a169c 57 85 02 0c     jal        FUN_OVR_226__800a155c                            undefined FUN_OVR_226__800a155c()
     6::800a16a0 04 00 0a 24     _li        t2,0x4
     6::800a16a4 4d 85 02 0c     jal        FUN_OVR_226__800a1534                            undefined FUN_OVR_226__800a1534()
     6::800a16a8 0c 00 0a 24     _li        t2,0xc
     6::800a16ac 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a16b0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a16b4 a4 ff 01 04     bgez       zero,FUN_OVR_226__800a1548
     6::800a16b8 0c 00 0a 24     _li        t2,0xc
     6::800a16bc 66 85 02 0c     jal        FUN_OVR_226__800a1598                            undefined FUN_OVR_226__800a1598()
     6::800a16c0 0c 00 0a 24     _li        t2,0xc
     6::800a16c4 52 85 02 0c     jal        FUN_OVR_226__800a1548                            undefined FUN_OVR_226__800a1548()
     6::800a16c8 04 00 0a 24     _li        t2,0x4
     6::800a16cc 4d 85 02 0c     jal        FUN_OVR_226__800a1534                            undefined FUN_OVR_226__800a1534()
     6::800a16d0 0c 00 0a 24     _li        t2,0xc
     6::800a16d4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a16d8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a16dc 9f ff 01 04     bgez       zero,FUN_OVR_226__800a155c
     6::800a16e0 0c 00 0a 24     _li        t2,0xc
     6::800a16e4 6b 85 02 0c     jal        FUN_OVR_226__800a15ac                            undefined FUN_OVR_226__800a15ac()
     6::800a16e8 0c 00 0a 24     _li        t2,0xc
     6::800a16ec 57 85 02 0c     jal        FUN_OVR_226__800a155c                            undefined FUN_OVR_226__800a155c()
     6::800a16f0 08 00 0a 24     _li        t2,0x8
     6::800a16f4 52 85 02 0c     jal        FUN_OVR_226__800a1548                            undefined FUN_OVR_226__800a1548()
     6::800a16f8 0c 00 0a 24     _li        t2,0xc
     6::800a16fc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1700 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a1704 9a ff 01 04     bgez       zero,LAB_OVR_226__800a1570
     6::800a1708 0c 00 0a 24     _li        t2,0xc
     6::800a170c 61 85 02 0c     jal        FUN_OVR_226__800a1584                            undefined FUN_OVR_226__800a1584()
     6::800a1710 0c 00 0a 24     _li        t2,0xc
     6::800a1714 52 85 02 0c     jal        FUN_OVR_226__800a1548                            undefined FUN_OVR_226__800a1548()
     6::800a1718 08 00 0a 24     _li        t2,0x8
     6::800a171c 57 85 02 0c     jal        FUN_OVR_226__800a155c                            undefined FUN_OVR_226__800a155c()
     6::800a1720 0c 00 0a 24     _li        t2,0xc
     6::800a1724 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1728 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a172c 90 ff 01 04     bgez       zero,LAB_OVR_226__800a1570
     6::800a1730 0c 00 0a 24     _li        t2,0xc
     6::800a1734 b4 01 23 24     addiu      v1,at,0x1b4
     6::800a1738 16 00 7e 14     bne        v1,s8,LAB_OVR_226__800a1794
     6::800a173c 50 00 03 3c     _lui       v1,0x50
     6::800a1740 78 64 63 34     ori        v1,v1,0x6478
     6::800a1744 08 00 08 24     li         t0,0x8
     6::800a1748 6a 86 02 0c     jal        FUN_OVR_226__800a19a8                            undefined FUN_OVR_226__800a19a8()
     6::800a174c 00 00 0a 24     _li        t2,0x0
     6::800a1750 14 50 03 3c     lui        v1,0x5014
     6::800a1754 8c 78 63 34     ori        v1,v1,0x788c
     6::800a1758 0d 00 08 24     li         t0,0xd
     6::800a175c 6a 86 02 0c     jal        FUN_OVR_226__800a19a8                            undefined FUN_OVR_226__800a19a8()
     6::800a1760 04 00 0a 24     _li        t2,0x4
     6::800a1764 78 64 03 3c     lui        v1,0x6478
     6::800a1768 a0 28 63 34     ori        v1,v1,0x28a0
     6::800a176c 12 00 08 24     li         t0,0x12
     6::800a1770 6a 86 02 0c     jal        FUN_OVR_226__800a19a8                            undefined FUN_OVR_226__800a19a8()
     6::800a1774 08 00 0a 24     _li        t2,0x8
     6::800a1778 8c 78 03 3c     lui        v1,0x788c
     6::800a177c 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a1780 17 00 08 24     li         t0,0x17
     6::800a1784 6a 86 02 0c     jal        FUN_OVR_226__800a19a8                            undefined FUN_OVR_226__800a19a8()
     6::800a1788 0c 00 0a 24     _li        t2,0xc
     6::800a178c 14 ff 01 04     bgez       zero,LAB_OVR_226__800a13e0
     6::800a1790 00 00 00 00     _nop
                             LAB_OVR_226__800a1794                           XREF[1]:     OVR_226::800a1738(j)  
     6::800a1794 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a1798 4d 85 02 0c     jal        FUN_OVR_226__800a1534                            undefined FUN_OVR_226__800a1534()
     6::800a179c 0c 00 0a 24     _li        t2,0xc
     6::800a17a0 04 00 03 24     li         v1,0x4
     6::800a17a4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a17a8 52 85 02 0c     jal        FUN_OVR_226__800a1548                            undefined FUN_OVR_226__800a1548()
     6::800a17ac 0c 00 0a 24     _li        t2,0xc
     6::800a17b0 08 00 03 24     li         v1,0x8
     6::800a17b4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a17b8 57 85 02 0c     jal        FUN_OVR_226__800a155c                            undefined FUN_OVR_226__800a155c()
     6::800a17bc 0c 00 0a 24     _li        t2,0xc
     6::800a17c0 0c 00 03 24     li         v1,0xc
     6::800a17c4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a17c8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a17cc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a17d0 67 ff 01 04     bgez       zero,LAB_OVR_226__800a1570
     6::800a17d4 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a17d8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a17d8                           XREF[5]:     FUN_OVR_226__800a19a8:800a1c3c(c
                                                                                          FUN_OVR_226__800a19a8:800a1c50(c
                                                                                          FUN_OVR_226__800a19a8:800a1c64(c
                                                                                          FUN_OVR_226__800a19a8:800a1c78(c
                                                                                          FUN_OVR_226__800a19a8:800a1c8c(c
     6::800a17d8 00 00 ab 85     lh         t3,0x0(t5)
     6::800a17dc 00 00 cc 85     lh         t4,0x0(t6)
     6::800a17e0 00 00 eb a5     sh         t3,0x0(t7)
     6::800a17e4 21 18 6c 01     addu       v1,t3,t4
     6::800a17e8 43 18 03 00     sra        v1,v1,0x1
     6::800a17ec 00 00 03 a6     sh         v1,0x0(s0)
     6::800a17f0 02 00 ab 85     lh         t3,0x2(t5)
     6::800a17f4 02 00 cc 85     lh         t4,0x2(t6)
     6::800a17f8 02 00 eb a5     sh         t3,0x2(t7)
     6::800a17fc 21 18 6c 01     addu       v1,t3,t4
     6::800a1800 43 18 03 00     sra        v1,v1,0x1
     6::800a1804 02 00 03 a6     sh         v1,0x2(s0)
     6::800a1808 04 00 ab 85     lh         t3,0x4(t5)
     6::800a180c 04 00 cc 85     lh         t4,0x4(t6)
     6::800a1810 04 00 eb a5     sh         t3,0x4(t7)
     6::800a1814 21 18 6c 01     addu       v1,t3,t4
     6::800a1818 43 18 03 00     sra        v1,v1,0x1
     6::800a181c 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a1820 00 08 83 48     gte_ldVZ0  v1
     6::800a1824 04 00 03 a6     sh         v1,0x4(s0)
     6::800a1828 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a182c 01 00 18 4a     RTPS
     6::800a1830 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a1834 08 00 eb a1     sb         t3,0x8(t7)
     6::800a1838 21 18 6c 01     addu       v1,t3,t4
     6::800a183c 43 18 03 00     sra        v1,v1,0x1
     6::800a1840 08 00 03 a2     sb         v1,0x8(s0)
     6::800a1844 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a1848 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a184c 09 00 eb a1     sb         t3,0x9(t7)
     6::800a1850 21 18 6c 01     addu       v1,t3,t4
     6::800a1854 43 18 03 00     sra        v1,v1,0x1
     6::800a1858 09 00 03 a2     sb         v1,0x9(s0)
     6::800a185c 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a1860 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a1864 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a1868 21 18 6c 01     addu       v1,t3,t4
     6::800a186c 43 18 03 00     sra        v1,v1,0x1
     6::800a1870 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a1874 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a1878 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a187c 06 00 eb a1     sb         t3,0x6(t7)
     6::800a1880 21 18 6c 01     addu       v1,t3,t4
     6::800a1884 43 18 03 00     sra        v1,v1,0x1
     6::800a1888 06 00 03 a2     sb         v1,0x6(s0)
     6::800a188c 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a1890 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a1894 07 00 eb a1     sb         t3,0x7(t7)
     6::800a1898 21 18 6c 01     addu       v1,t3,t4
     6::800a189c 43 18 03 00     sra        v1,v1,0x1
     6::800a18a0 07 00 03 a2     sb         v1,0x7(s0)
     6::800a18a4 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a18a8 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a18ac 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a18b0 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a18b4 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a18b8 08 00 e0 03     jr         ra
     6::800a18bc 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a18c0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a18c0                           XREF[12]:    FUN_OVR_226__800a1534:800a1540(j
                                                                                          FUN_OVR_226__800a1548:800a1554(j
                                                                                          FUN_OVR_226__800a155c:800a1568(j
                                                                                          FUN_OVR_226__800a15c0:800a157c(j
                                                                                          FUN_OVR_226__800a1584:800a1590(j
                                                                                          FUN_OVR_226__800a1598:800a15a4(j
                                                                                          FUN_OVR_226__800a15ac:800a15b8(j
                                                                                          FUN_OVR_226__800a15c0:800a15cc(j
                                                                                          FUN_OVR_226__800a15c0:800a15e4(c
                                                                                          FUN_OVR_226__800a15c0:800a15fc(c
                                                                                          FUN_OVR_226__800a15c0:800a1664(c
                                                                                          FUN_OVR_226__800a15c0:800a167c(c
     6::800a18c0 70 00 2a ac     sw         t2,0x70(at)
     6::800a18c4 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a18c8 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a18cc 94 01 2a 8c     lw         t2,0x194(at)
     6::800a18d0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a18d4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a18d8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a18dc 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a18e0 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a18e4 06 00 40 4b     NCLIP
     6::800a18e8 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a18ec 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a18f0 23 78 68 01     subu       t7,t3,t0
     6::800a18f4 23 80 88 01     subu       s0,t4,t0
     6::800a18f8 23 88 a8 01     subu       s1,t5,t0
     6::800a18fc 23 90 c8 01     subu       s2,t6,t0
     6::800a1900 00 c0 08 48     gte_stMAC0 t0
     6::800a1904 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a1908 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a1914
     6::800a190c 22 40 08 00     _sub       t0,zero,t0
     6::800a1910 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a1914                           XREF[1]:     OVR_226::800a1908(j)  
     6::800a1914 06 00 40 4b     NCLIP
     6::800a1918 24 18 6c 01     and        v1,t3,t4
     6::800a191c 24 18 6d 00     and        v1,v1,t5
     6::800a1920 24 18 6e 00     and        v1,v1,t6
     6::800a1924 25 78 f0 01     or         t7,t7,s0
     6::800a1928 25 78 f1 01     or         t7,t7,s1
     6::800a192c 27 78 f2 01     nor        t7,t7,s2
     6::800a1930 25 78 e3 01     or         t7,t7,v1
     6::800a1934 b2 fe e0 05     bltz       t7,LAB_OVR_226__800a1400
     6::800a1938 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a193c b0 fe e0 05     bltz       t7,LAB_OVR_226__800a1400
     6::800a1940 00 c0 03 48     _gte_stM   v1
     6::800a1944 25 40 09 01     or         t0,t0,t1
     6::800a1948 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a1954
     6::800a194c c2 47 08 00     _srl       t0,t0,0x1f
     6::800a1950 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a1954                           XREF[1]:     OVR_226::800a1948(j)  
     6::800a1954 80 40 08 00     sll        t0,t0,0x2
     6::800a1958 25 18 69 00     or         v1,v1,t1
     6::800a195c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a1960 c0 18 03 00     sll        v1,v1,0x3
     6::800a1964 70 00 2a 8c     lw         t2,0x70(at)
     6::800a1968 25 18 68 00     or         v1,v1,t0
     6::800a196c 24 18 6a 00     and        v1,v1,t2
     6::800a1970 a3 fe 60 10     beq        v1,zero,LAB_OVR_226__800a1400
     6::800a1974 70 00 23 ac     _sw        v1,0x70(at)
     6::800a1978 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a197c b4 01 28 24     addiu      t0,at,0x1b4
     6::800a1980 00 00 1e 15     bne        t0,s8,LAB_OVR_226__800a1984
                             LAB_OVR_226__800a1984                           XREF[1]:     OVR_226::800a1980(j)  
     6::800a1984 24 03 28 24     _addiu     t0,at,0x324
     6::800a1988 ce 00 1e 11     beq        t0,s8,LAB_OVR_226__800a1cc4
     6::800a198c 04 00 39 27     _addiu     t9,t9,0x4
     6::800a1990 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a1994 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a1998 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a199c 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a19a0 91 00 01 04     bgez       zero,LAB_OVR_226__800a1be8
     6::800a19a4 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a19a8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a19a8                           XREF[4]:     FUN_OVR_226__800a15c0:800a1748(c
                                                                                          FUN_OVR_226__800a15c0:800a175c(c
                                                                                          FUN_OVR_226__800a15c0:800a1770(c
                                                                                          FUN_OVR_226__800a15c0:800a1784(c
     6::800a19a8 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a19ac b4 00 ca af     sw         t2,0xb4(s8)
     6::800a19b0 06 50 09 01     srlv       t2,t1,t0
     6::800a19b4 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a19b8 80 50 0a 00     sll        t2,t2,0x2
     6::800a19bc 21 50 41 01     addu       t2,t2,at
     6::800a19c0 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a19c4 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a19c8 94 01 2a ac     sw         t2,0x194(at)
     6::800a19cc 02 9e 0a 00     srl        s3,t2,0x18
     6::800a19d0 1f 00 73 32     andi       s3,s3,0x1f
     6::800a19d4 06 98 63 02     srlv       s3,v1,s3
     6::800a19d8 ff 00 73 32     andi       s3,s3,0xff
     6::800a19dc 21 98 7e 02     addu       s3,s3,s8
     6::800a19e0 02 a4 0a 00     srl        s4,t2,0x10
     6::800a19e4 1f 00 94 32     andi       s4,s4,0x1f
     6::800a19e8 06 a0 83 02     srlv       s4,v1,s4
     6::800a19ec ff 00 94 32     andi       s4,s4,0xff
     6::800a19f0 21 a0 9e 02     addu       s4,s4,s8
     6::800a19f4 02 aa 0a 00     srl        s5,t2,0x8
     6::800a19f8 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a19fc 06 a8 a3 02     srlv       s5,v1,s5
     6::800a1a00 ff 00 b5 32     andi       s5,s5,0xff
     6::800a1a04 21 a8 be 02     addu       s5,s5,s8
     6::800a1a08 1f 00 56 31     andi       s6,t2,0x1f
     6::800a1a0c 06 b0 c3 02     srlv       s6,v1,s6
     6::800a1a10 ff 00 d6 32     andi       s6,s6,0xff
     6::800a1a14 21 b0 de 02     addu       s6,s6,s8
     6::800a1a18 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a1a1c 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a1a20 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a1a24 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a1a28 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a1a2c 06 00 40 4b     NCLIP
     6::800a1a30 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a1a34 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a1a38 23 78 68 01     subu       t7,t3,t0
     6::800a1a3c 23 80 88 01     subu       s0,t4,t0
     6::800a1a40 23 88 a8 01     subu       s1,t5,t0
     6::800a1a44 23 90 c8 01     subu       s2,t6,t0
     6::800a1a48 00 c0 08 48     gte_stMAC0 t0
     6::800a1a4c 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a1a50 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a1a5c
     6::800a1a54 22 40 08 00     _sub       t0,zero,t0
     6::800a1a58 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a1a5c                           XREF[1]:     OVR_226::800a1a50(j)  
     6::800a1a5c 06 00 40 4b     NCLIP
     6::800a1a60 24 18 6c 01     and        v1,t3,t4
     6::800a1a64 24 18 6d 00     and        v1,v1,t5
     6::800a1a68 24 18 6e 00     and        v1,v1,t6
     6::800a1a6c 25 78 f0 01     or         t7,t7,s0
     6::800a1a70 25 78 f1 01     or         t7,t7,s1
     6::800a1a74 27 78 f2 01     nor        t7,t7,s2
     6::800a1a78 25 78 e3 01     or         t7,t7,v1
     6::800a1a7c 60 fe e0 05     bltz       t7,LAB_OVR_226__800a1400
     6::800a1a80 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a1a84 5e fe e0 05     bltz       t7,LAB_OVR_226__800a1400
     6::800a1a88 00 c0 03 48     _gte_stM   v1
     6::800a1a8c 25 40 09 01     or         t0,t0,t1
     6::800a1a90 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a1a9c
     6::800a1a94 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a1a98 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a1a9c                           XREF[1]:     OVR_226::800a1a90(j)  
     6::800a1a9c 80 40 08 00     sll        t0,t0,0x2
     6::800a1aa0 25 18 69 00     or         v1,v1,t1
     6::800a1aa4 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a1aa8 c0 18 03 00     sll        v1,v1,0x3
     6::800a1aac 25 18 68 00     or         v1,v1,t0
     6::800a1ab0 53 fe 60 10     beq        v1,zero,LAB_OVR_226__800a1400
     6::800a1ab4 70 00 23 ac     _sw        v1,0x70(at)
     6::800a1ab8 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a1abc 04 00 39 27     addiu      t9,t9,0x4
     6::800a1ac0 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a1ac4 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a1ac8 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a1acc 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a1ad0 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a1ad4 23 50 6c 01     subu       t2,t3,t4
     6::800a1ad8 82 48 03 00     srl        t1,v1,0x2
     6::800a1adc 21 48 38 01     addu       t1,t1,t8
     6::800a1ae0 18 00 29 81     lb         t1,0x18(t1)
     6::800a1ae4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a1af0
     6::800a1ae8 21 e0 60 01     _move      gp,t3
     6::800a1aec 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a1af0                           XREF[1]:     OVR_226::800a1ae4(j)  
     6::800a1af0 23 50 8d 03     subu       t2,gp,t5
     6::800a1af4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a1b00
     6::800a1af8 21 18 78 00     _addu      v1,v1,t8
     6::800a1afc 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a1b00                           XREF[1]:     OVR_226::800a1af4(j)  
     6::800a1b00 23 50 8e 03     subu       t2,gp,t6
     6::800a1b04 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a1b10
     6::800a1b08 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a1b0c 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a1b10                           XREF[1]:     OVR_226::800a1b04(j)  
     6::800a1b10 21 50 80 03     move       t2,gp
     6::800a1b14 82 e1 1c 00     srl        gp,gp,0x6
     6::800a1b18 21 e0 89 03     addu       gp,gp,t1
     6::800a1b1c 01 00 69 30     andi       t1,v1,0x1
     6::800a1b20 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a1b2c
     6::800a1b24 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a1b28 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a1b2c                           XREF[1]:     OVR_226::800a1b20(j)  
     6::800a1b2c 02 00 81 07     bgez       gp,LAB_OVR_226__800a1b38
     6::800a1b30 21 e0 85 03     _addu      gp,gp,a1
     6::800a1b34 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a1b38                           XREF[1]:     OVR_226::800a1b2c(j)  
     6::800a1b38 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a1b3c 24 00 69 8c     lw         t1,0x24(v1)
     6::800a1b40 23 40 48 01     subu       t0,t2,t0
     6::800a1b44 84 00 29 ac     sw         t1,0x84(at)
     6::800a1b48 0c 00 01 05     bgez       t0,LAB_OVR_226__800a1b7c
     6::800a1b4c 20 00 28 8c     _lw        t0,0x20(at)
     6::800a1b50 0c 00 63 24     addiu      v1,v1,0xc
     6::800a1b54 23 40 48 01     subu       t0,t2,t0
     6::800a1b58 08 00 01 05     bgez       t0,LAB_OVR_226__800a1b7c
     6::800a1b5c 24 00 28 8c     _lw        t0,0x24(at)
     6::800a1b60 0c 00 63 24     addiu      v1,v1,0xc
     6::800a1b64 23 40 48 01     subu       t0,t2,t0
     6::800a1b68 04 00 01 05     bgez       t0,LAB_OVR_226__800a1b7c
     6::800a1b6c 00 00 00 00     _nop
     6::800a1b70 02 00 20 05     bltz       t1,LAB_OVR_226__800a1b7c
     6::800a1b74 00 00 00 00     _nop
     6::800a1b78 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a1b7c                           XREF[4]:     OVR_226::800a1b48(j), 
                                                                                          OVR_226::800a1b58(j), 
                                                                                          OVR_226::800a1b68(j), 
                                                                                          OVR_226::800a1b70(j)  
     6::800a1b7c 94 01 2a 8c     lw         t2,0x194(at)
     6::800a1b80 00 00 68 8c     lw         t0,0x0(v1)
     6::800a1b84 04 00 69 8c     lw         t1,0x4(v1)
     6::800a1b88 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a1b8c ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a1b90 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a1b94 00 52 0a 00     sll        t2,t2,0x8
     6::800a1b98 0a 00 40 05     bltz       t2,LAB_OVR_226__800a1bc4
     6::800a1b9c b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a1ba0 06 00 68 a6     sh         t0,0x6(s3)
     6::800a1ba4 08 00 68 8c     lw         t0,0x8(v1)
     6::800a1ba8 06 00 89 a6     sh         t1,0x6(s4)
     6::800a1bac 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a1bb0 00 54 0a 00     sll        t2,t2,0x10
     6::800a1bb4 0b 00 40 05     bltz       t2,LAB_OVR_226__800a1be4
     6::800a1bb8 02 4c 08 00     _srl       t1,t0,0x10
     6::800a1bbc 09 00 01 04     bgez       zero,LAB_OVR_226__800a1be4
     6::800a1bc0 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a1bc4                           XREF[1]:     OVR_226::800a1b98(j)  
     6::800a1bc4 06 00 69 a6     sh         t1,0x6(s3)
     6::800a1bc8 08 00 69 8c     lw         t1,0x8(v1)
     6::800a1bcc 00 54 0a 00     sll        t2,t2,0x10
     6::800a1bd0 06 00 88 a6     sh         t0,0x6(s4)
     6::800a1bd4 02 44 09 00     srl        t0,t1,0x10
     6::800a1bd8 02 00 40 05     bltz       t2,LAB_OVR_226__800a1be4
     6::800a1bdc 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a1be0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a1be4                           XREF[3]:     OVR_226::800a1bb4(j), 
                                                                                          OVR_226::800a1bbc(j), 
                                                                                          OVR_226::800a1bd8(j)  
     6::800a1be4 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a1be8                           XREF[1]:     FUN_OVR_226__800a18c0:800a19a0(j
     6::800a1be8 00 00 00 00     nop
     6::800a1bec 23 88 63 01     subu       s1,t3,v1
     6::800a1bf0 23 90 83 01     subu       s2,t4,v1
     6::800a1bf4 23 78 a3 01     subu       t7,t5,v1
     6::800a1bf8 23 80 c3 01     subu       s0,t6,v1
     6::800a1bfc 42 8f 11 00     srl        s1,s1,0x1d
     6::800a1c00 04 00 31 32     andi       s1,s1,0x4
     6::800a1c04 02 97 12 00     srl        s2,s2,0x1c
     6::800a1c08 08 00 52 32     andi       s2,s2,0x8
     6::800a1c0c 25 88 32 02     or         s1,s1,s2
     6::800a1c10 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a1c14 10 00 ef 31     andi       t7,t7,0x10
     6::800a1c18 25 88 2f 02     or         s1,s1,t7
     6::800a1c1c 82 86 10 00     srl        s0,s0,0x1a
     6::800a1c20 20 00 10 32     andi       s0,s0,0x20
     6::800a1c24 25 88 30 02     or         s1,s1,s0
     6::800a1c28 26 00 20 12     beq        s1,zero,LAB_OVR_226__800a1cc4
     6::800a1c2c 21 68 60 02     _move      t5,s3
     6::800a1c30 21 70 80 02     move       t6,s4
     6::800a1c34 b8 00 de 27     addiu      s8,s8,0xb8
     6::800a1c38 00 00 cf 27     addiu      t7,s8,0x0
     6::800a1c3c f6 85 02 0c     jal        FUN_OVR_226__800a17d8                            undefined FUN_OVR_226__800a17d8()
     6::800a1c40 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a1c44 21 68 80 02     move       t5,s4
     6::800a1c48 21 70 c0 02     move       t6,s6
     6::800a1c4c 14 00 cf 27     addiu      t7,s8,0x14
     6::800a1c50 f6 85 02 0c     jal        FUN_OVR_226__800a17d8                            undefined FUN_OVR_226__800a17d8()
     6::800a1c54 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a1c58 21 68 a0 02     move       t5,s5
     6::800a1c5c 21 70 60 02     move       t6,s3
     6::800a1c60 28 00 cf 27     addiu      t7,s8,0x28
     6::800a1c64 f6 85 02 0c     jal        FUN_OVR_226__800a17d8                            undefined FUN_OVR_226__800a17d8()
     6::800a1c68 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a1c6c 21 68 c0 02     move       t5,s6
     6::800a1c70 21 70 a0 02     move       t6,s5
     6::800a1c74 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a1c78 f6 85 02 0c     jal        FUN_OVR_226__800a17d8                            undefined FUN_OVR_226__800a17d8()
     6::800a1c7c a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a1c80 21 68 80 02     move       t5,s4
     6::800a1c84 21 70 a0 02     move       t6,s5
     6::800a1c88 14 00 cf 27     addiu      t7,s8,0x14
     6::800a1c8c f6 85 02 0c     jal        FUN_OVR_226__800a17d8                            undefined FUN_OVR_226__800a17d8()
     6::800a1c90 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a1c94 21 18 21 02     addu       v1,s1,at
     6::800a1c98 48 01 63 8c     lw         v1,0x148(v1)
     6::800a1c9c 0a 80 08 3c     lui        t0,0x800a
     6::800a1ca0 b4 1c 08 25     addiu      t0,t0,0x1cb4
     6::800a1ca4 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a1ca8 3c 00 28 af     sw         t0=>LAB_OVR_226__800a1cb4,0x3c(t9)
     6::800a1cac 08 00 60 00     jr         v1
     6::800a1cb0 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a1cb4                           XREF[1]:     FUN_OVR_226__800a19a8:800a1ca8(*
     6::800a1cb4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a1cb8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a1cbc 08 00 e0 03     jr         ra
     6::800a1cc0 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a1cc4                           XREF[2]:     FUN_OVR_226__800a18c0:800a1988(j
                                                                                          OVR_226::800a1c28(j)  
     6::800a1cc4 70 00 23 8c     lw         v1,0x70(at)
     6::800a1cc8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a1ccc 21 18 61 00     addu       v1,v1,at
     6::800a1cd0 84 01 63 8c     lw         v1,0x184(v1)
     6::800a1cd4 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a1cd8 08 00 60 00     jr         v1
     6::800a1cdc 00 00 00 00     _nop

// PrimMem and OTMem for far-away lev quadblocks
     6::800a1ce0 21 98 80 02     move       s3,s4
     6::800a1ce4 21 a0 c0 02     move       s4,s6
                             LAB_OVR_226__800a1ce8                           XREF[1]:     OVR_226::800ab51c(*)  
     6::800a1ce8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a1cec 08 00 90 8e     lw         s0,0x8(s4)
     6::800a1cf0 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a1cf4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a1cf8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a1cfc 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a1d00 06 00 73 86     lh         s3,0x6(s3)
     6::800a1d04 06 00 94 86     lh         s4,0x6(s4)
     6::800a1d08 06 00 b5 86     lh         s5,0x6(s5)
     6::800a1d0c a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a1d10 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a1d14 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a1d18 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a1d1c a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a1d20 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a1d24 60 00 03 3c     lui        v1,0x60
     6::800a1d28 24 48 83 02     and        t1,s4,v1
     6::800a1d2c 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a1d38
     6::800a1d30 00 36 03 3c     _lui       v1,0x3600
     6::800a1d34 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a1d38                           XREF[1]:     OVR_226::800a1d2c(j)  
     6::800a1d38 25 18 6f 00     or         v1,v1,t7
     6::800a1d3c 04 00 43 ac     sw         v1,0x4(v0)
     6::800a1d40 08 00 4b ac     sw         t3,0x8(v0)
     6::800a1d44 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a1d48 10 00 50 ac     sw         s0,0x10(v0)
     6::800a1d4c 14 00 4c ac     sw         t4,0x14(v0)
     6::800a1d50 18 00 54 ac     sw         s4,0x18(v0)
     6::800a1d54 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a1d58 20 00 4d ac     sw         t5,0x20(v0)
     6::800a1d5c 24 00 55 ac     sw         s5,0x24(v0)
     6::800a1d60 28 00 09 24     li         t1,0x28
     6::800a1d64 29 00 01 04     bgez       zero,LAB_OVR_226__800a1e0c
     6::800a1d68 00 09 0a 3c     _lui       t2,0x900
     6::800a1d6c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a1d70 08 00 90 8e     lw         s0,0x8(s4)
     6::800a1d74 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a1d78 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a1d7c 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a1d80 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a1d84 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a1d88 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a1d8c 06 00 73 86     lh         s3,0x6(s3)
     6::800a1d90 06 00 94 86     lh         s4,0x6(s4)
     6::800a1d94 06 00 b5 86     lh         s5,0x6(s5)
     6::800a1d98 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a1d9c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a1da0 06 00 d4 86     lh         s4,0x6(s6)
     6::800a1da4 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a1da8 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a1dac a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a1db0 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a1db4 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a1db8 60 00 03 3c     lui        v1,0x60
     6::800a1dbc 24 48 83 02     and        t1,s4,v1
     6::800a1dc0 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a1dcc
     6::800a1dc4 00 3e 03 3c     _lui       v1,0x3e00
     6::800a1dc8 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a1dcc                           XREF[1]:     OVR_226::800a1dc0(j)  
     6::800a1dcc 25 18 6f 00     or         v1,v1,t7
     6::800a1dd0 04 00 43 ac     sw         v1,0x4(v0)
     6::800a1dd4 08 00 4b ac     sw         t3,0x8(v0)
     6::800a1dd8 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a1ddc 10 00 50 ac     sw         s0,0x10(v0)
     6::800a1de0 14 00 4c ac     sw         t4,0x14(v0)
     6::800a1de4 18 00 54 ac     sw         s4,0x18(v0)
     6::800a1de8 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a1dec 20 00 4d ac     sw         t5,0x20(v0)
     6::800a1df0 24 00 55 ac     sw         s5,0x24(v0)
     6::800a1df4 28 00 52 ac     sw         s2,0x28(v0)
     6::800a1df8 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a1dfc 02 1c 15 00     srl        v1,s5,0x10
     6::800a1e00 30 00 43 ac     sw         v1,0x30(v0)
     6::800a1e04 34 00 09 24     li         t1,0x34
     6::800a1e08 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a1e0c                           XREF[1]:     OVR_226::800a1d64(j)  
     6::800a1e0c 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a1e10 00 42 02 00     sll        t0,v0,0x8
     6::800a1e14 02 42 08 00     srl        t0,t0,0x8
     6::800a1e18 25 18 6a 00     or         v1,v1,t2
     6::800a1e1c 00 00 43 ac     sw         v1,0x0(v0)
     6::800a1e20 21 10 49 00     addu       v0,v0,t1
     6::800a1e24 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a1e28 08 00 e0 03     jr         ra
     6::800a1e2c 01 00 bd 23     _addi      sp,sp,0x1
     
	 // second JR in main loop
                        LAB_OVR_226__800a1e30                           XREF[1]:     OVR_226::800ab45c(*)  
     
	 6::800a1e30 09 80 08 3c     lui        t0,0x8009
     6::800a1e34 04 64 08 25     addiu      t0,t0,0x6404
     6::800a1e38 64 00 28 ac     sw         t0=>DAT_80096404,0x64(at)                        = ??
     
	 // v1 = 1f800088 lev->0x44 (restart_main)
	 6::800a1e3c 88 00 23 8c     lw         v1,0x88(at)
     6::800a1e40 00 a8 c0        ldfcdir    zero,zero,zero
                 48 00 b0 
                 c0 48 00 
	 
	 // something in lev???
     6::800a1e4c 00 00 68 8c     lw         t0,0x0(v1)
	 6::800a1e50 04 00 69 8c     lw         t1,0x4(v1)
     6::800a1e54 a0 01 28 ac     sw         t0,0x1a0(at)
	 6::800a1e58 a4 01 29 ac     sw         t1,0x1a4(at)
     
	 // v1? gGT + 1808 + (mainFunc loopIndex) + 0x4?
	 // v1 is bsp, a BSP node
	 6::800a1e5c 04 00 83 8c     lw         v1,0x4(a0)
     
	 // loop until out of bsp
                        LAB_OVR_226__800a1e60                           XREF[1]:     OVR_226::800a2218(j)  
     
	 // if loop is finished, JMP somewhere
	 6::800a1e60 ef 00 80 10     beq        a0,zero,LAB_OVR_226__800a2220
     6::800a1e64 00 00 00 00     _nop
     
	 // t8 = bsp->ptrQuadblocks, v1->0x1c
	 6::800a1e68 1c 00 78 8c     lw         t8,0x1c(v1)
	 
	 // t9 = bsp->numBlocks v1->0x18
     6::800a1e6c 18 00 79 8c     lw         t9,0x18(v1)
	 
	 // t2 = 0x1f8000c8 (visFaceList)
     6::800a1e70 c8 00 2a 8c     lw         t2,0xc8(at)
	 
	 // t0 = quadblock->ID, t8->0x3c
     6::800a1e74 3c 00 08 97     lhu        t0,0x3c(t8)
	 
	 // t9 = 0x1f800068 (numQuadblocks)
     6::800a1e78 68 00 39 ac     sw         t9,0x68(at)
	 
	 // t1 = quadblockID >> 3
     6::800a1e7c c2 48 08 00     srl        t1,t0,0x3
	 
	 // t1 = t1 & 0x1fc
     6::800a1e80 fc 01 29 31     andi       t1,t1,0x1fc
	 
	 // t1 = visFaceList + (quadblockID>>3)&0x1fc
     6::800a1e84 21 48 2a 01     addu       t1,t1,t2
	 
	 // 0x1f8000c0 = t1
     6::800a1e88 c0 00 29 ac     sw         t1,0xc0(at)
	 
	 // t1 = dereference t1
     6::800a1e8c 00 00 29 8d     lw         t1,0x0(t1)
	 
	 // quadblockID = quadblockID & 0x1f,
	 // can't have more than 32 blocks in bsp
     6::800a1e90 1f 00 08 31     andi       t0,t0,0x1f
	 
     6::800a1e94 bc 00 28 ac     sw         t0,0xbc(at)
     6::800a1e98 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_226__800a1e9c                           XREF[1]:     OVR_226::800a220c(j)  
     6::800a1e9c 30 00 23 8c     lw         v1,0x30(at)
     6::800a1ea0 00 1a 48 24     addiu      t0,v0,0x1a00
     6::800a1ea4 23 18 68 00     subu       v1,v1,t0
     6::800a1ea8 02 fc 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a1eac bc 00 23 8c     _lw        v1,0xbc(at)
     6::800a1eb0 c4 00 28 8c     lw         t0,0xc4(at)
     6::800a1eb4 06 00 61 04     bgez       v1,LAB_OVR_226__800a1ed0
     6::800a1eb8 c0 00 29 8c     _lw        t1,0xc0(at)
     6::800a1ebc 1f 00 03 24     li         v1,0x1f
     6::800a1ec0 04 00 28 8d     lw         t0,0x4(t1)
     6::800a1ec4 04 00 29 25     addiu      t1,t1,0x4
     6::800a1ec8 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a1ecc c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_226__800a1ed0                           XREF[1]:     OVR_226::800a1eb4(j)  
     6::800a1ed0 04 40 68 00     sllv       t0,t0,v1
     6::800a1ed4 ff ff 63 24     addiu      v1,v1,-0x1
     6::800a1ed8 c9 00 01 05     bgez       t0,LAB_OVR_226__800a2200
     6::800a1edc bc 00 23 ac     _sw        v1,0xbc(at)
     6::800a1ee0 b4 01 3e 24     addiu      s8,at,0x1b4
     6::800a1ee4 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a1ee8 00 00 14 8f     lw         s4,0x0(t8)
     6::800a1eec 04 00 16 8f     lw         s6,0x4(t8)
     6::800a1ef0 ff ff 93 32     andi       s3,s4,0xffff
     6::800a1ef4 00 99 13 00     sll        s3,s3,0x4
     6::800a1ef8 21 98 77 02     addu       s3,s3,s7
     6::800a1efc 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a1f04 02 a4 14 00     srl        s4,s4,0x10
     6::800a1f08 00 a1 14 00     sll        s4,s4,0x4
     6::800a1f0c 21 a0 97 02     addu       s4,s4,s7
     6::800a1f10 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a1f18 ff ff d5 32     andi       s5,s6,0xffff
     6::800a1f1c 00 a9 15 00     sll        s5,s5,0x4
     6::800a1f20 21 a8 b7 02     addu       s5,s5,s7
     6::800a1f24 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a1f2c 02 b4 16 00     srl        s6,s6,0x10
     6::800a1f30 00 b1 16 00     sll        s6,s6,0x4
     6::800a1f34 30 00 28 4a     RTPT
     6::800a1f38 21 b0 d7 02     addu       s6,s6,s7
     6::800a1f3c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a1f40 08 00 90 8e     lw         s0,0x8(s4)
     6::800a1f44 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a1f48 08 00 cf af     sw         t7,0x8(s8)
     6::800a1f4c 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a1f50 30 00 d1 af     sw         s1,0x30(s8)
     6::800a1f54 0c 00 6f 86     lh         t7,0xc(s3)
     6::800a1f58 0c 00 90 86     lh         s0,0xc(s4)
     6::800a1f5c 0c 00 b1 86     lh         s1,0xc(s5)
     6::800a1f60 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a1f64 00 f8 43 48     gte_stFLAG v1
     6::800a1f68 10 00 d1 eb     gte_stSZ1  0x10(s8)
     6::800a1f6c 80 1b 03 00     sll        v1,v1,0xe
     6::800a1f70 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a1f74 9d 00 60 14     bne        v1,zero,LAB_OVR_226__800a21ec
     6::800a1f78 08 00 14 8f     _lw        s4,0x8(t8)
     6::800a1f7c 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a1f80 24 00 d2 eb     gte_stSZ2  0x24(s8)
     6::800a1f84 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a1f88 38 00 d3 eb     gte_stSZ3  0x38(s8)
     6::800a1f8c 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a1f90 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a1f94 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a1f98 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a1f9c 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a1fa0 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a1fa4 06 00 cf a7     sh         t7,0x6(s8)
     6::800a1fa8 1a 00 d0 a7     sh         s0,0x1a(s8)
     6::800a1fac 2e 00 d1 a7     sh         s1,0x2e(s8)
     6::800a1fb0 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a1fb8 ff ff 93 32     andi       s3,s4,0xffff
     6::800a1fbc 00 99 13 00     sll        s3,s3,0x4
     6::800a1fc0 21 98 77 02     addu       s3,s3,s7
     6::800a1fc4 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a1fcc 02 a4 14 00     srl        s4,s4,0x10
     6::800a1fd0 00 a1 14 00     sll        s4,s4,0x4
     6::800a1fd4 21 a0 97 02     addu       s4,s4,s7
     6::800a1fd8 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a1fe0 21 c8 20 00     move       t9,at
     6::800a1fe4 00 00 00 00     nop
     6::800a1fe8 30 00 28 4a     RTPT
     6::800a1fec 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a1ff0 08 00 70 8e     lw         s0,0x8(s3)
     6::800a1ff4 08 00 91 8e     lw         s1,0x8(s4)
     6::800a1ff8 44 00 cf af     sw         t7,0x44(s8)
     6::800a1ffc 58 00 d0 af     sw         s0,0x58(s8)
     6::800a2000 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a2004 0c 00 cf 86     lh         t7,0xc(s6)
     6::800a2008 0c 00 70 86     lh         s0,0xc(s3)
     6::800a200c 0c 00 91 86     lh         s1,0xc(s4)
     6::800a2010 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a2014 00 f8 43 48     gte_stFLAG v1
     6::800a2018 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     6::800a201c 80 1b 03 00     sll        v1,v1,0xe
     6::800a2020 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a2024 71 00 60 14     bne        v1,zero,LAB_OVR_226__800a21ec
     6::800a2028 0c 00 14 8f     _lw        s4,0xc(t8)
     6::800a202c 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a2030 60 00 d2 eb     gte_stSZ2  0x60(s8)
     6::800a2034 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a2038 74 00 d3 eb     gte_stSZ3  0x74(s8)
     6::800a203c 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a2040 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a2044 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a2048 10 00 15 97     lhu        s5,0x10(t8)
     6::800a204c 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a2050 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a2054 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a2058 42 00 cf a7     sh         t7,0x42(s8)
     6::800a205c 56 00 d0 a7     sh         s0,0x56(s8)
     6::800a2060 6a 00 d1 a7     sh         s1,0x6a(s8)
     6::800a2064 ff ff 93 32     andi       s3,s4,0xffff
     6::800a2068 00 99 13 00     sll        s3,s3,0x4
     6::800a206c 21 98 77 02     addu       s3,s3,s7
     6::800a2070 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a2078 02 a4 14 00     srl        s4,s4,0x10
     6::800a207c 00 a1 14 00     sll        s4,s4,0x4
     6::800a2080 21 a0 97 02     addu       s4,s4,s7
     6::800a2084 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a208c 14 00 09 8f     lw         t1,0x14(t8)
     6::800a2090 00 a9 15 00     sll        s5,s5,0x4
     6::800a2094 21 a8 b7 02     addu       s5,s5,s7
     6::800a2098 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a20a0 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a20a4 08 00 08 24     li         t0,0x8
     6::800a20a8 30 00 28 4a     RTPT
     6::800a20ac 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a20b0 08 00 90 8e     lw         s0,0x8(s4)
     6::800a20b4 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a20b8 80 00 cf af     sw         t7,0x80(s8)
     6::800a20bc 94 00 d0 af     sw         s0,0x94(s8)
     6::800a20c0 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a20c4 0c 00 6f 86     lh         t7,0xc(s3)
     6::800a20c8 0c 00 90 86     lh         s0,0xc(s4)
     6::800a20cc 0c 00 b1 86     lh         s1,0xc(s5)
     6::800a20d0 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a20d4 00 f8 43 48     gte_stFLAG v1
     6::800a20d8 88 00 d1 eb     gte_stSZ1  0x88(s8)
     6::800a20dc 80 1b 03 00     sll        v1,v1,0xe
     6::800a20e0 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a20e4 41 00 60 14     bne        v1,zero,LAB_OVR_226__800a21ec
     6::800a20e8 98 00 cd eb     _gte_stS   0x98(s8)
     6::800a20ec 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     6::800a20f0 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a20f4 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     6::800a20f8 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a20fc 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a2100 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a2104 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a2108 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a210c a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a2110 7e 00 cf a7     sh         t7,0x7e(s8)
     6::800a2114 92 00 d0 a7     sh         s0,0x92(s8)
     6::800a2118 a6 00 d1 a7     sh         s1,0xa6(s8)
     6::800a211c 98 01 2d 84     lh         t5,0x198(at)
     6::800a2120 9c 01 2e 84     lh         t6,0x19c(at)
     6::800a2124 00 00 cb 87     lh         t3,0x0(s8)
     6::800a2128 04 00 cc 87     lh         t4,0x4(s8)
     6::800a212c 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a2130 08 00 cf 8f     _lw        t7,0x8(s8)
     6::800a2134 14 00 cb 87     lh         t3,0x14(s8)
     6::800a2138 18 00 cc 87     lh         t4,0x18(s8)
     6::800a213c 08 00 cf af     sw         t7,0x8(s8)
     6::800a2140 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a2144 1c 00 cf 8f     _lw        t7,0x1c(s8)
     6::800a2148 28 00 cb 87     lh         t3,0x28(s8)
     6::800a214c 2c 00 cc 87     lh         t4,0x2c(s8)
     6::800a2150 1c 00 cf af     sw         t7,0x1c(s8)
     6::800a2154 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a2158 30 00 cf 8f     _lw        t7,0x30(s8)
     6::800a215c 3c 00 cb 87     lh         t3,0x3c(s8)
     6::800a2160 40 00 cc 87     lh         t4,0x40(s8)
     6::800a2164 30 00 cf af     sw         t7,0x30(s8)
     6::800a2168 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a216c 44 00 cf 8f     _lw        t7,0x44(s8)
     6::800a2170 50 00 cb 87     lh         t3,0x50(s8)
     6::800a2174 54 00 cc 87     lh         t4,0x54(s8)
     6::800a2178 44 00 cf af     sw         t7,0x44(s8)
     6::800a217c 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a2180 58 00 cf 8f     _lw        t7,0x58(s8)
     6::800a2184 64 00 cb 87     lh         t3,0x64(s8)
     6::800a2188 68 00 cc 87     lh         t4,0x68(s8)
     6::800a218c 58 00 cf af     sw         t7,0x58(s8)
     6::800a2190 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a2194 6c 00 cf 8f     _lw        t7,0x6c(s8)
     6::800a2198 78 00 cb 87     lh         t3,0x78(s8)
     6::800a219c 7c 00 cc 87     lh         t4,0x7c(s8)
     6::800a21a0 6c 00 cf af     sw         t7,0x6c(s8)
     6::800a21a4 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a21a8 80 00 cf 8f     _lw        t7,0x80(s8)
     6::800a21ac 8c 00 cb 87     lh         t3,0x8c(s8)
     6::800a21b0 90 00 cc 87     lh         t4,0x90(s8)
     6::800a21b4 80 00 cf af     sw         t7,0x80(s8)
     6::800a21b8 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a21bc 94 00 cf 8f     _lw        t7,0x94(s8)
     6::800a21c0 a0 00 cb 87     lh         t3,0xa0(s8)
     6::800a21c4 a4 00 cc 87     lh         t4,0xa4(s8)
     6::800a21c8 94 00 cf af     sw         t7,0x94(s8)
     6::800a21cc 8d 88 02 0c     jal        FUN_OVR_226__800a2234                            undefined FUN_OVR_226__800a2234()
     6::800a21d0 a8 00 cf 8f     _lw        t7,0xa8(s8)
     6::800a21d4 0a 80 03 3c     lui        v1,0x800a
     6::800a21d8 00 22 63 24     addiu      v1,v1,0x2200
     6::800a21dc a8 00 cf af     sw         t7,0xa8(s8)
     6::800a21e0 3c 00 23 af     sw         v1=>LAB_OVR_226__800a2200,0x3c(t9)
     6::800a21e4 af 00 01 04     bgez       zero,LAB_OVR_226__800a24a4
     6::800a21e8 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a21ec                           XREF[3]:     OVR_226::800a1f74(j), 
                                                                                          OVR_226::800a2024(j), 
                                                                                          OVR_226::800a20e4(j)  
     6::800a21ec 64 00 28 8c     lw         t0,0x64(at)
     6::800a21f0 00 00 00 00     nop
     6::800a21f4 00 00 18 ad     sw         t8,0x0(t0)
     6::800a21f8 04 00 08 25     addiu      t0,t0,0x4
     6::800a21fc 64 00 28 ac     sw         t0,0x64(at)
                             LAB_OVR_226__800a2200                           XREF[2]:     OVR_226::800a1ed8(j), 
                                                                                          OVR_226::800a21e0(*)  
     6::800a2200 68 00 39 8c     lw         t9,0x68(at)
     6::800a2204 5c 00 18 27     addiu      t8,t8,0x5c
     6::800a2208 ff ff 39 27     addiu      t9,t9,-0x1
     6::800a220c 23 ff 20 1f     bgtz       t9,LAB_OVR_226__800a1e9c
     6::800a2210 68 00 39 ac     _sw        t9,0x68(at)
     6::800a2214 00 00 84 8c     lw         a0,0x0(a0)
     6::800a2218 11 ff 01 04     bgez       zero,LAB_OVR_226__800a1e60
     6::800a221c 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_226__800a2220                           XREF[1]:     OVR_226::800a1e60(j)  
     6::800a2220 64 00 28 8c     lw         t0,0x64(at)
     6::800a2224 18 fb 01 04     bgez       zero,LAB_OVR_226__800a0e88
     6::800a2228 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_226__800a222c                           XREF[3]:     OVR_226::800a2610(j), 
                                                                                          OVR_226::800a2618(j), 
                                                                                          OVR_226::800a2658(j)  
     6::800a222c 08 00 e0 03     jr         ra
     6::800a2230 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2234()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2234                           XREF[9]:     OVR_226::800a212c(c), 
                                                                                          OVR_226::800a2140(c), 
                                                                                          OVR_226::800a2154(c), 
                                                                                          OVR_226::800a2168(c), 
                                                                                          OVR_226::800a217c(c), 
                                                                                          OVR_226::800a2190(c), 
                                                                                          OVR_226::800a21a4(c), 
                                                                                          OVR_226::800a21b8(c), 
                                                                                          OVR_226::800a21cc(c)  
     6::800a2234 23 58 6d 01     subu       t3,t3,t5
     6::800a2238 02 00 61 05     bgez       t3,LAB_OVR_226__800a2244
     6::800a223c 23 60 8e 01     _subu      t4,t4,t6
     6::800a2240 22 58 0b 00     sub        t3,zero,t3
                             LAB_OVR_226__800a2244                           XREF[1]:     OVR_226::800a2238(j)  
     6::800a2244 02 00 81 05     bgez       t4,LAB_OVR_226__800a2250
     6::800a2248 00 00 00 00     _nop
     6::800a224c 22 60 0c 00     sub        t4,zero,t4
                             LAB_OVR_226__800a2250                           XREF[1]:     OVR_226::800a2244(j)  
     6::800a2250 23 40 6c 01     subu       t0,t3,t4
     6::800a2254 03 00 01 05     bgez       t0,LAB_OVR_226__800a2264
     6::800a2258 83 40 0c 00     _sra       t0,t4,0x2
     6::800a225c 83 40 0b 00     sra        t0,t3,0x2
     6::800a2260 21 58 80 01     move       t3,t4
                             LAB_OVR_226__800a2264                           XREF[1]:     OVR_226::800a2254(j)  
     6::800a2264 21 58 68 01     addu       t3,t3,t0
     6::800a2268 00 f0 6b 25     addiu      t3,t3,-0x1000
     6::800a226c 0b 00 61 05     bgez       t3,LAB_OVR_226__800a229c
     6::800a2270 80 40 0b 00     _sll       t0,t3,0x2
     6::800a2274 00 10 08 25     addiu      t0,t0,0x1000
     6::800a2278 06 00 00 05     bltz       t0,LAB_OVR_226__800a2294
     6::800a227c 00 30 8f 48     _gte_ldRGB t7
     6::800a2280 00 40 88 48     gte_ldIR0  t0
     6::800a2284 00 00 00        nDPCS
                 00 00 00 
                 00 00 10 
     6::800a2290 00 b0 0f 48     gte_stRGB2 t7
                             LAB_OVR_226__800a2294                           XREF[1]:     OVR_226::800a2278(j)  
     6::800a2294 08 00 e0 03     jr         ra
     6::800a2298 00 00 00 00     _nop
                             LAB_OVR_226__800a229c                           XREF[1]:     OVR_226::800a226c(j)  
     6::800a229c 08 00 e0 03     jr         ra
     6::800a22a0 00 00 0f 24     _li        t7,0x0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a22a4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a22a4                           XREF[4]:     FUN_OVR_226__800a2330:800a237c(j
                                                                                          FUN_OVR_226__800a2330:800a2414(c
                                                                                          FUN_OVR_226__800a2330:800a243c(c
                                                                                          FUN_OVR_226__800a2330:800a24a8(c
     6::800a22a4 00 00 d3 27     addiu      s3,s8,0x0
     6::800a22a8 50 00 d4 27     addiu      s4,s8,0x50
     6::800a22ac 64 00 d5 27     addiu      s5,s8,0x64
     6::800a22b0 c7 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a22b4 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a22b8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a22b8                           XREF[6]:     FUN_OVR_226__800a2330:800a2384(c
                                                                                          FUN_OVR_226__800a2330:800a2424(j
                                                                                          FUN_OVR_226__800a2330:800a2434(c
                                                                                          FUN_OVR_226__800a2330:800a2464(c
                                                                                          FUN_OVR_226__800a2330:800a2484(c
                                                                                          FUN_OVR_226__800a2330:800a24b8(c
     6::800a22b8 50 00 d3 27     addiu      s3,s8,0x50
     6::800a22bc 14 00 d4 27     addiu      s4,s8,0x14
     6::800a22c0 78 00 d5 27     addiu      s5,s8,0x78
     6::800a22c4 c2 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a22c8 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a22cc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a22cc                           XREF[6]:     FUN_OVR_226__800a2330:800a23ac(c
                                                                                          FUN_OVR_226__800a2330:800a240c(c
                                                                                          FUN_OVR_226__800a2330:800a244c(j
                                                                                          FUN_OVR_226__800a2330:800a245c(c
                                                                                          FUN_OVR_226__800a2330:800a248c(c
                                                                                          FUN_OVR_226__800a2330:800a24c8(c
     6::800a22cc 64 00 d3 27     addiu      s3,s8,0x64
     6::800a22d0 78 00 d4 27     addiu      s4,s8,0x78
     6::800a22d4 28 00 d5 27     addiu      s5,s8,0x28
     6::800a22d8 bd 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a22dc a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a22e0                           XREF[4]:     OVR_226::800a23fc(j), 
                                                                                          OVR_226::800a2474(j), 
                                                                                          OVR_226::800a249c(j), 
                                                                                          OVR_226::800a24e0(j)  
     6::800a22e0 78 00 d3 27     addiu      s3,s8,0x78
     6::800a22e4 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a22e8 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a22ec b8 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a22f0 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a22f4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a22f4                           XREF[2]:     FUN_OVR_226__800a2330:800a23a4(c
                                                                                          FUN_OVR_226__800a2330:800a247c(c
     6::800a22f4 64 00 d3 27     addiu      s3,s8,0x64
     6::800a22f8 00 00 d4 27     addiu      s4,s8,0x0
     6::800a22fc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2300 b3 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a2304 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2308()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2308                           XREF[2]:     FUN_OVR_226__800a2330:800a23bc(j
                                                                                          FUN_OVR_226__800a2330:800a242c(c
     6::800a2308 14 00 d3 27     addiu      s3,s8,0x14
     6::800a230c 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a2310 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2314 ae 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a2318 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a231c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a231c                           XREF[2]:     FUN_OVR_226__800a2330:800a238c(c
                                                                                          FUN_OVR_226__800a2330:800a2454(c
     6::800a231c 28 00 d3 27     addiu      s3,s8,0x28
     6::800a2320 00 00 d4 27     addiu      s4,s8,0x0
     6::800a2324 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2328 a9 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a232c 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2330()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2330                           XREF[2]:     OVR_226::800a239c(j), 
                                                                                          OVR_226::800a2404(c)  
     6::800a2330 28 00 d3 27     addiu      s3,s8,0x28
     6::800a2334 78 00 d4 27     addiu      s4,s8,0x78
     6::800a2338 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a233c a4 00 01 04     bgez       zero,FUN_OVR_226__800a25d0
     6::800a2340 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a2344 50 00 d3 27     addiu      s3,s8,0x50
     6::800a2348 14 00 d4 27     addiu      s4,s8,0x14
     6::800a234c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2350 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a2354 74 89 02 0c     jal        FUN_OVR_226__800a25d0                            undefined FUN_OVR_226__800a25d0()
     6::800a2358 0c 00 0a 24     _li        t2,0xc
     6::800a235c 64 00 d3 27     addiu      s3,s8,0x64
     6::800a2360 78 00 d4 27     addiu      s4,s8,0x78
     6::800a2364 28 00 d5 27     addiu      s5,s8,0x28
     6::800a2368 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a236c 74 89 02 0c     jal        FUN_OVR_226__800a25d0                            undefined FUN_OVR_226__800a25d0()
     6::800a2370 0c 00 0a 24     _li        t2,0xc
     6::800a2374 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2378 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a237c c9 ff 01 04     bgez       zero,FUN_OVR_226__800a22a4
     6::800a2380 0c 00 0a 24     _li        t2,0xc
     6::800a2384 ae 88 02 0c     jal        FUN_OVR_226__800a22b8                            undefined FUN_OVR_226__800a22b8()
     6::800a2388 0c 00 0a 24     _li        t2,0xc
     6::800a238c c7 88 02 0c     jal        FUN_OVR_226__800a231c                            undefined FUN_OVR_226__800a231c()
     6::800a2390 0c 00 0a 24     _li        t2,0xc
     6::800a2394 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2398 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a239c e4 ff 01 04     bgez       zero,FUN_OVR_226__800a2330
     6::800a23a0 0c 00 0a 24     _li        t2,0xc
     6::800a23a4 bd 88 02 0c     jal        FUN_OVR_226__800a22f4                            undefined FUN_OVR_226__800a22f4()
     6::800a23a8 0c 00 0a 24     _li        t2,0xc
     6::800a23ac b3 88 02 0c     jal        FUN_OVR_226__800a22cc                            undefined FUN_OVR_226__800a22cc()
     6::800a23b0 0c 00 0a 24     _li        t2,0xc
     6::800a23b4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a23b8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a23bc d2 ff 01 04     bgez       zero,FUN_OVR_226__800a2308
     6::800a23c0 0c 00 0a 24     _li        t2,0xc
     6::800a23c4 00 00 d3 27     addiu      s3,s8,0x0
     6::800a23c8 14 00 d4 27     addiu      s4,s8,0x14
     6::800a23cc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a23d0 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a23d4 74 89 02 0c     jal        FUN_OVR_226__800a25d0                            undefined FUN_OVR_226__800a25d0()
     6::800a23d8 0c 00 0a 24     _li        t2,0xc
     6::800a23dc 00 00 d3 27     addiu      s3,s8,0x0
     6::800a23e0 78 00 d4 27     addiu      s4,s8,0x78
     6::800a23e4 28 00 d5 27     addiu      s5,s8,0x28
     6::800a23e8 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a23ec 74 89 02 0c     jal        FUN_OVR_226__800a25d0                            undefined FUN_OVR_226__800a25d0()
     6::800a23f0 0c 00 0a 24     _li        t2,0xc
     6::800a23f4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a23f8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a23fc b8 ff 01 04     bgez       zero,LAB_OVR_226__800a22e0
     6::800a2400 0c 00 0a 24     _li        t2,0xc
     6::800a2404 cc 88 02 0c     jal        FUN_OVR_226__800a2330                            undefined FUN_OVR_226__800a2330()
     6::800a2408 0c 00 0a 24     _li        t2,0xc
     6::800a240c b3 88 02 0c     jal        FUN_OVR_226__800a22cc                            undefined FUN_OVR_226__800a22cc()
     6::800a2410 04 00 0a 24     _li        t2,0x4
     6::800a2414 a9 88 02 0c     jal        FUN_OVR_226__800a22a4                            undefined FUN_OVR_226__800a22a4()
     6::800a2418 0c 00 0a 24     _li        t2,0xc
     6::800a241c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2420 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2424 a4 ff 01 04     bgez       zero,FUN_OVR_226__800a22b8
     6::800a2428 0c 00 0a 24     _li        t2,0xc
     6::800a242c c2 88 02 0c     jal        FUN_OVR_226__800a2308                            undefined FUN_OVR_226__800a2308()
     6::800a2430 0c 00 0a 24     _li        t2,0xc
     6::800a2434 ae 88 02 0c     jal        FUN_OVR_226__800a22b8                            undefined FUN_OVR_226__800a22b8()
     6::800a2438 04 00 0a 24     _li        t2,0x4
     6::800a243c a9 88 02 0c     jal        FUN_OVR_226__800a22a4                            undefined FUN_OVR_226__800a22a4()
     6::800a2440 0c 00 0a 24     _li        t2,0xc
     6::800a2444 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2448 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a244c 9f ff 01 04     bgez       zero,FUN_OVR_226__800a22cc
     6::800a2450 0c 00 0a 24     _li        t2,0xc
     6::800a2454 c7 88 02 0c     jal        FUN_OVR_226__800a231c                            undefined FUN_OVR_226__800a231c()
     6::800a2458 0c 00 0a 24     _li        t2,0xc
     6::800a245c b3 88 02 0c     jal        FUN_OVR_226__800a22cc                            undefined FUN_OVR_226__800a22cc()
     6::800a2460 08 00 0a 24     _li        t2,0x8
     6::800a2464 ae 88 02 0c     jal        FUN_OVR_226__800a22b8                            undefined FUN_OVR_226__800a22b8()
     6::800a2468 0c 00 0a 24     _li        t2,0xc
     6::800a246c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2470 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2474 9a ff 01 04     bgez       zero,LAB_OVR_226__800a22e0
     6::800a2478 0c 00 0a 24     _li        t2,0xc
     6::800a247c bd 88 02 0c     jal        FUN_OVR_226__800a22f4                            undefined FUN_OVR_226__800a22f4()
     6::800a2480 0c 00 0a 24     _li        t2,0xc
     6::800a2484 ae 88 02 0c     jal        FUN_OVR_226__800a22b8                            undefined FUN_OVR_226__800a22b8()
     6::800a2488 08 00 0a 24     _li        t2,0x8
     6::800a248c b3 88 02 0c     jal        FUN_OVR_226__800a22cc                            undefined FUN_OVR_226__800a22cc()
     6::800a2490 0c 00 0a 24     _li        t2,0xc
     6::800a2494 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2498 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a249c 90 ff 01 04     bgez       zero,LAB_OVR_226__800a22e0
     6::800a24a0 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a24a4                           XREF[1]:     OVR_226::800a21e4(j)  
     6::800a24a4 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a24a8 a9 88 02 0c     jal        FUN_OVR_226__800a22a4                            undefined FUN_OVR_226__800a22a4()
     6::800a24ac 0c 00 0a 24     _li        t2,0xc
     6::800a24b0 04 00 03 24     li         v1,0x4
     6::800a24b4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a24b8 ae 88 02 0c     jal        FUN_OVR_226__800a22b8                            undefined FUN_OVR_226__800a22b8()
     6::800a24bc 0c 00 0a 24     _li        t2,0xc
     6::800a24c0 08 00 03 24     li         v1,0x8
     6::800a24c4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a24c8 b3 88 02 0c     jal        FUN_OVR_226__800a22cc                            undefined FUN_OVR_226__800a22cc()
     6::800a24cc 0c 00 0a 24     _li        t2,0xc
     6::800a24d0 0c 00 03 24     li         v1,0xc
     6::800a24d4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a24d8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a24dc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a24e0 7f ff 01 04     bgez       zero,LAB_OVR_226__800a22e0
     6::800a24e4 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a24e8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a24e8                           XREF[5]:     FUN_OVR_226__800a25d0:800a2734(c
                                                                                          FUN_OVR_226__800a25d0:800a2748(c
                                                                                          FUN_OVR_226__800a25d0:800a275c(c
                                                                                          FUN_OVR_226__800a25d0:800a2770(c
                                                                                          FUN_OVR_226__800a25d0:800a2784(c
     6::800a24e8 00 00 ab 85     lh         t3,0x0(t5)
     6::800a24ec 00 00 cc 85     lh         t4,0x0(t6)
     6::800a24f0 00 00 eb a5     sh         t3,0x0(t7)
     6::800a24f4 21 18 6c 01     addu       v1,t3,t4
     6::800a24f8 43 18 03 00     sra        v1,v1,0x1
     6::800a24fc 00 00 03 a6     sh         v1,0x0(s0)
     6::800a2500 02 00 ab 85     lh         t3,0x2(t5)
     6::800a2504 02 00 cc 85     lh         t4,0x2(t6)
     6::800a2508 02 00 eb a5     sh         t3,0x2(t7)
     6::800a250c 21 18 6c 01     addu       v1,t3,t4
     6::800a2510 43 18 03 00     sra        v1,v1,0x1
     6::800a2514 02 00 03 a6     sh         v1,0x2(s0)
     6::800a2518 04 00 ab 85     lh         t3,0x4(t5)
     6::800a251c 04 00 cc 85     lh         t4,0x4(t6)
     6::800a2520 04 00 eb a5     sh         t3,0x4(t7)
     6::800a2524 21 18 6c 01     addu       v1,t3,t4
     6::800a2528 43 18 03 00     sra        v1,v1,0x1
     6::800a252c 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a2530 00 08 83 48     gte_ldVZ0  v1
     6::800a2534 04 00 03 a6     sh         v1,0x4(s0)
     6::800a2538 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a253c 01 00 18 4a     RTPS
     6::800a2540 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a2544 08 00 eb a1     sb         t3,0x8(t7)
     6::800a2548 21 18 6c 01     addu       v1,t3,t4
     6::800a254c 43 18 03 00     sra        v1,v1,0x1
     6::800a2550 08 00 03 a2     sb         v1,0x8(s0)
     6::800a2554 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a2558 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a255c 09 00 eb a1     sb         t3,0x9(t7)
     6::800a2560 21 18 6c 01     addu       v1,t3,t4
     6::800a2564 43 18 03 00     sra        v1,v1,0x1
     6::800a2568 09 00 03 a2     sb         v1,0x9(s0)
     6::800a256c 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a2570 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a2574 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a2578 21 18 6c 01     addu       v1,t3,t4
     6::800a257c 43 18 03 00     sra        v1,v1,0x1
     6::800a2580 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a2584 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a2588 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a258c 06 00 eb a1     sb         t3,0x6(t7)
     6::800a2590 21 18 6c 01     addu       v1,t3,t4
     6::800a2594 43 18 03 00     sra        v1,v1,0x1
     6::800a2598 06 00 03 a2     sb         v1,0x6(s0)
     6::800a259c 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a25a0 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a25a4 07 00 eb a1     sb         t3,0x7(t7)
     6::800a25a8 21 18 6c 01     addu       v1,t3,t4
     6::800a25ac 43 18 03 00     sra        v1,v1,0x1
     6::800a25b0 07 00 03 a2     sb         v1,0x7(s0)
     6::800a25b4 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a25b8 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a25bc 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a25c0 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a25c4 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a25c8 08 00 e0 03     jr         ra
     6::800a25cc 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a25d0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a25d0                           XREF[12]:    FUN_OVR_226__800a22a4:800a22b0(j
                                                                                          FUN_OVR_226__800a22b8:800a22c4(j
                                                                                          FUN_OVR_226__800a22cc:800a22d8(j
                                                                                          FUN_OVR_226__800a2330:800a22ec(j
                                                                                          FUN_OVR_226__800a22f4:800a2300(j
                                                                                          FUN_OVR_226__800a2308:800a2314(j
                                                                                          FUN_OVR_226__800a231c:800a2328(j
                                                                                          FUN_OVR_226__800a2330:800a233c(j
                                                                                          FUN_OVR_226__800a2330:800a2354(c
                                                                                          FUN_OVR_226__800a2330:800a236c(c
                                                                                          FUN_OVR_226__800a2330:800a23d4(c
                                                                                          FUN_OVR_226__800a2330:800a23ec(c
     6::800a25d0 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a25d4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a25d8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a25dc 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a25e0 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a25e4 23 78 68 01     subu       t7,t3,t0
     6::800a25e8 23 80 88 01     subu       s0,t4,t0
     6::800a25ec 23 88 a8 01     subu       s1,t5,t0
     6::800a25f0 23 90 c8 01     subu       s2,t6,t0
     6::800a25f4 24 40 6c 01     and        t0,t3,t4
     6::800a25f8 24 40 0d 01     and        t0,t0,t5
     6::800a25fc 24 40 0e 01     and        t0,t0,t6
     6::800a2600 25 78 f0 01     or         t7,t7,s0
     6::800a2604 25 78 f1 01     or         t7,t7,s1
     6::800a2608 27 78 f2 01     nor        t7,t7,s2
     6::800a260c 25 78 e8 01     or         t7,t7,t0
     6::800a2610 06 ff e0 05     bltz       t7,LAB_OVR_226__800a222c
     6::800a2614 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a2618 04 ff e0 05     bltz       t7,LAB_OVR_226__800a222c
     6::800a261c 08 00 6f 8e     _lw        t7,0x8(s3)
     6::800a2620 08 00 90 8e     lw         s0,0x8(s4)
     6::800a2624 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a2628 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a262c 25 40 f0 01     or         t0,t7,s0
     6::800a2630 25 40 11 01     or         t0,t0,s1
     6::800a2634 02 00 00 15     bne        t0,zero,LAB_OVR_226__800a2640
     6::800a2638 04 00 03 24     _li        v1,0x4
     6::800a263c 00 00 03 24     li         v1,0x0
                             LAB_OVR_226__800a2640                           XREF[1]:     OVR_226::800a2634(j)  
     6::800a2640 25 40 11 02     or         t0,s0,s1
     6::800a2644 25 40 12 01     or         t0,t0,s2
     6::800a2648 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a2654
     6::800a264c 00 00 00 00     _nop
     6::800a2650 08 00 63 34     ori        v1,v1,0x8
                             LAB_OVR_226__800a2654                           XREF[1]:     OVR_226::800a2648(j)  
     6::800a2654 24 50 43 01     and        t2,t2,v1
     6::800a2658 f4 fe 40 11     beq        t2,zero,LAB_OVR_226__800a222c
     6::800a265c 70 00 2a ac     _sw        t2,0x70(at)
     6::800a2660 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a2664 24 03 28 24     addiu      t0,at,0x324
     6::800a2668 53 00 1e 11     beq        t0,s8,LAB_OVR_226__800a27b8
     6::800a266c 04 00 39 27     _addiu     t9,t9,0x4
     6::800a2670 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a2674 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a2678 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a267c 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a2680 b4 01 28 24     addiu      t0,at,0x1b4
     6::800a2684 16 00 1e 15     bne        t0,s8,LAB_OVR_226__800a26e0
     6::800a2688 28 00 23 8c     _lw        v1,0x28(at)
     6::800a268c b4 00 c9 8f     lw         t1,0xb4(s8)
     6::800a2690 23 18 6c 01     subu       v1,t3,t4
     6::800a2694 82 48 09 00     srl        t1,t1,0x2
     6::800a2698 21 48 38 01     addu       t1,t1,t8
     6::800a269c 18 00 29 81     lb         t1,0x18(t1)
     6::800a26a0 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a26ac
     6::800a26a4 21 e0 60 01     _move      gp,t3
     6::800a26a8 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a26ac                           XREF[1]:     OVR_226::800a26a0(j)  
     6::800a26ac 23 18 8d 03     subu       v1,gp,t5
     6::800a26b0 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a26bc
     6::800a26b4 23 18 8e 03     _subu      v1,gp,t6
     6::800a26b8 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a26bc                           XREF[1]:     OVR_226::800a26b0(j)  
     6::800a26bc 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a26c8
     6::800a26c0 00 00 00 00     _nop
     6::800a26c4 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a26c8                           XREF[1]:     OVR_226::800a26bc(j)  
     6::800a26c8 21 18 80 03     move       v1,gp
     6::800a26cc 82 e1 1c 00     srl        gp,gp,0x6
     6::800a26d0 21 e0 89 03     addu       gp,gp,t1
     6::800a26d4 80 e0 1c 00     sll        gp,gp,0x2
     6::800a26d8 21 e0 85 03     addu       gp,gp,a1
     6::800a26dc 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a26e0                           XREF[1]:     OVR_226::800a2684(j)  
     6::800a26e0 00 00 00 00     nop
     6::800a26e4 23 88 63 01     subu       s1,t3,v1
     6::800a26e8 23 90 83 01     subu       s2,t4,v1
     6::800a26ec 23 78 a3 01     subu       t7,t5,v1
     6::800a26f0 23 80 c3 01     subu       s0,t6,v1
     6::800a26f4 42 8f 11 00     srl        s1,s1,0x1d
     6::800a26f8 04 00 31 32     andi       s1,s1,0x4
     6::800a26fc 02 97 12 00     srl        s2,s2,0x1c
     6::800a2700 08 00 52 32     andi       s2,s2,0x8
     6::800a2704 25 88 32 02     or         s1,s1,s2
     6::800a2708 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a270c 10 00 ef 31     andi       t7,t7,0x10
     6::800a2710 25 88 2f 02     or         s1,s1,t7
     6::800a2714 82 86 10 00     srl        s0,s0,0x1a
     6::800a2718 20 00 10 32     andi       s0,s0,0x20
     6::800a271c 25 88 30 02     or         s1,s1,s0
     6::800a2720 25 00 20 12     beq        s1,zero,LAB_OVR_226__800a27b8
     6::800a2724 21 68 60 02     _move      t5,s3
     6::800a2728 21 70 80 02     move       t6,s4
     6::800a272c b8 00 de 27     addiu      s8,s8,0xb8
     6::800a2730 00 00 cf 27     addiu      t7,s8,0x0
     6::800a2734 3a 89 02 0c     jal        FUN_OVR_226__800a24e8                            undefined FUN_OVR_226__800a24e8()
     6::800a2738 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a273c 21 68 80 02     move       t5,s4
     6::800a2740 21 70 c0 02     move       t6,s6
     6::800a2744 14 00 cf 27     addiu      t7,s8,0x14
     6::800a2748 3a 89 02 0c     jal        FUN_OVR_226__800a24e8                            undefined FUN_OVR_226__800a24e8()
     6::800a274c 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a2750 21 68 a0 02     move       t5,s5
     6::800a2754 21 70 60 02     move       t6,s3
     6::800a2758 28 00 cf 27     addiu      t7,s8,0x28
     6::800a275c 3a 89 02 0c     jal        FUN_OVR_226__800a24e8                            undefined FUN_OVR_226__800a24e8()
     6::800a2760 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a2764 21 68 c0 02     move       t5,s6
     6::800a2768 21 70 a0 02     move       t6,s5
     6::800a276c 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a2770 3a 89 02 0c     jal        FUN_OVR_226__800a24e8                            undefined FUN_OVR_226__800a24e8()
     6::800a2774 a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a2778 21 68 80 02     move       t5,s4
     6::800a277c 21 70 a0 02     move       t6,s5
     6::800a2780 14 00 cf 27     addiu      t7,s8,0x14
     6::800a2784 3a 89 02 0c     jal        FUN_OVR_226__800a24e8                            undefined FUN_OVR_226__800a24e8()
     6::800a2788 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a278c 21 18 21 02     addu       v1,s1,at
     6::800a2790 48 01 63 8c     lw         v1,0x148(v1)
     6::800a2794 0a 80 08 3c     lui        t0,0x800a
     6::800a2798 a8 27 08 25     addiu      t0,t0,0x27a8
     6::800a279c 3c 00 28 af     sw         t0=>LAB_OVR_226__800a27a8,0x3c(t9)
     6::800a27a0 08 00 60 00     jr         v1
     6::800a27a4 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a27a8                           XREF[1]:     FUN_OVR_226__800a25d0:800a279c(*
     6::800a27a8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a27ac fc ff 39 27     addiu      t9,t9,-0x4
     6::800a27b0 08 00 e0 03     jr         ra
     6::800a27b4 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a27b8                           XREF[2]:     OVR_226::800a2668(j), 
                                                                                          OVR_226::800a2720(j)  
     6::800a27b8 70 00 23 8c     lw         v1,0x70(at)
     6::800a27bc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a27c0 21 18 61 00     addu       v1,v1,at
     6::800a27c4 84 01 63 8c     lw         v1,0x184(v1)
     6::800a27c8 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a27cc 08 00 60 00     jr         v1
     6::800a27d0 00 00 00 00     _nop
     6::800a27d4 21 98 80 02     move       s3,s4
     6::800a27d8 21 a0 c0 02     move       s4,s6
     6::800a27dc 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a27e0 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a27e4 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a27e8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a27ec 08 00 90 8e     lw         s0,0x8(s4)
     6::800a27f0 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a27f4 06 00 73 86     lh         s3,0x6(s3)
     6::800a27f8 06 00 94 86     lh         s4,0x6(s4)
     6::800a27fc 06 00 b5 86     lh         s5,0x6(s5)
     6::800a2800 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a2804 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a2808 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a280c a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a2810 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a2814 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a2818 00 36 03 3c     lui        v1,0x3600
     6::800a281c 25 18 6f 00     or         v1,v1,t7
     6::800a2820 04 00 43 ac     sw         v1,0x4(v0)
     6::800a2824 08 00 4b ac     sw         t3,0x8(v0)
     6::800a2828 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a282c 10 00 50 ac     sw         s0,0x10(v0)
     6::800a2830 14 00 4c ac     sw         t4,0x14(v0)
     6::800a2834 18 00 54 ac     sw         s4,0x18(v0)
     6::800a2838 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a283c 20 00 4d ac     sw         t5,0x20(v0)
     6::800a2840 24 00 55 ac     sw         s5,0x24(v0)
     6::800a2844 28 00 09 24     li         t1,0x28
     6::800a2848 25 00 01 04     bgez       zero,LAB_OVR_226__800a28e0
     6::800a284c 00 09 0a 3c     _lui       t2,0x900
     6::800a2850 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a2854 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a2858 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a285c 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a2860 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a2864 08 00 90 8e     lw         s0,0x8(s4)
     6::800a2868 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a286c 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a2870 06 00 73 86     lh         s3,0x6(s3)
     6::800a2874 06 00 94 86     lh         s4,0x6(s4)
     6::800a2878 06 00 b5 86     lh         s5,0x6(s5)
     6::800a287c a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a2880 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a2884 06 00 d4 86     lh         s4,0x6(s6)
     6::800a2888 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a288c aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a2890 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a2894 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a2898 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a289c 00 3e 03 3c     lui        v1,0x3e00
     6::800a28a0 25 18 6f 00     or         v1,v1,t7
     6::800a28a4 04 00 43 ac     sw         v1,0x4(v0)
     6::800a28a8 08 00 4b ac     sw         t3,0x8(v0)
     6::800a28ac 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a28b0 10 00 50 ac     sw         s0,0x10(v0)
     6::800a28b4 14 00 4c ac     sw         t4,0x14(v0)
     6::800a28b8 18 00 54 ac     sw         s4,0x18(v0)
     6::800a28bc 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a28c0 20 00 4d ac     sw         t5,0x20(v0)
     6::800a28c4 24 00 55 ac     sw         s5,0x24(v0)
     6::800a28c8 28 00 52 ac     sw         s2,0x28(v0)
     6::800a28cc 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a28d0 02 1c 15 00     srl        v1,s5,0x10
     6::800a28d4 30 00 43 ac     sw         v1,0x30(v0)
     6::800a28d8 34 00 09 24     li         t1,0x34
     6::800a28dc 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a28e0                           XREF[1]:     OVR_226::800a2848(j)  
     6::800a28e0 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a28e4 00 42 02 00     sll        t0,v0,0x8
     6::800a28e8 02 42 08 00     srl        t0,t0,0x8
     6::800a28ec 25 18 6a 00     or         v1,v1,t2
     6::800a28f0 00 00 43 ac     sw         v1,0x0(v0)
     6::800a28f4 21 10 49 00     addu       v0,v0,t1
     6::800a28f8 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a28fc 08 00 e0 03     jr         ra
     6::800a2900 01 00 bd 23     _addi      sp,sp,0x1

                             
							 LAB_OVR_226__800a2904                           XREF[1]:     OVR_226::800ab458(*)  
     6::800a2904 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_226__800a2908                           XREF[1]:     OVR_226::800a2d20(j)  
     6::800a2908 30 00 23 8c     lw         v1,0x30(at)
     6::800a290c 00 1a 48 24     addiu      t0,v0,0x1a00
     6::800a2910 23 18 68 00     subu       v1,v1,t0
     6::800a2914 67 f9 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a2918 b4 01 3e 24     _addiu     s8,at,0x1b4
     6::800a291c 5a f9 00 13     beq        t8,zero,LAB_OVR_226__800a0e88
     6::800a2920 b4 00 c0 af     _sw        zero,0xb4(s8)
     6::800a2924 00 00 14 8f     lw         s4,0x0(t8)
     6::800a2928 04 00 16 8f     lw         s6,0x4(t8)
     6::800a292c ff ff 93 32     andi       s3,s4,0xffff
     6::800a2930 00 99 13 00     sll        s3,s3,0x4
     6::800a2934 21 98 77 02     addu       s3,s3,s7
     6::800a2938 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a2940 02 a4 14 00     srl        s4,s4,0x10
     6::800a2944 00 a1 14 00     sll        s4,s4,0x4
     6::800a2948 21 a0 97 02     addu       s4,s4,s7
     6::800a294c 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a2954 ff ff d5 32     andi       s5,s6,0xffff
     6::800a2958 00 a9 15 00     sll        s5,s5,0x4
     6::800a295c 21 a8 b7 02     addu       s5,s5,s7
     6::800a2960 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a2968 02 b4 16 00     srl        s6,s6,0x10
     6::800a296c 00 b1 16 00     sll        s6,s6,0x4
     6::800a2970 30 00 28 4a     RTPT
     6::800a2974 21 b0 d7 02     addu       s6,s6,s7
     6::800a2978 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a297c 08 00 90 8e     lw         s0,0x8(s4)
     6::800a2980 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a2984 08 00 cf af     sw         t7,0x8(s8)
     6::800a2988 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a298c 30 00 d1 af     sw         s1,0x30(s8)
     6::800a2990 0c 00 6f 86     lh         t7,0xc(s3)
     6::800a2994 0c 00 90 86     lh         s0,0xc(s4)
     6::800a2998 0c 00 b1 86     lh         s1,0xc(s5)
     6::800a299c 08 00 14 8f     lw         s4,0x8(t8)
     6::800a29a0 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a29a4 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a29a8 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a29ac 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a29b0 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a29b4 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a29b8 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a29bc 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a29c0 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a29c4 06 00 cf a7     sh         t7,0x6(s8)
     6::800a29c8 1a 00 d0 a7     sh         s0,0x1a(s8)
     6::800a29cc 2e 00 d1 a7     sh         s1,0x2e(s8)
     6::800a29d0 5c 00 2a 8c     lw         t2,0x5c(at)
     6::800a29d4 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a29e0 10 00 c3 a7     sh         v1,0x10(s8)
     6::800a29e4 24 00 c8 a7     sh         t0,0x24(s8)
     6::800a29e8 38 00 c9 a7     sh         t1,0x38(s8)
     6::800a29ec 23 58 6a 00     subu       t3,v1,t2
     6::800a29f0 23 60 0a 01     subu       t4,t0,t2
     6::800a29f4 23 68 2a 01     subu       t5,t1,t2
     6::800a29f8 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a29fc c2 67 0c 00     srl        t4,t4,0x1f
     6::800a2a00 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a2a04 12 00 cb a3     sb         t3,0x12(s8)
     6::800a2a08 26 00 cc a3     sb         t4,0x26(s8)
     6::800a2a0c 3a 00 cd a3     sb         t5,0x3a(s8)
     6::800a2a10 40 18 03 00     sll        v1,v1,0x1
     6::800a2a14 40 40 08 00     sll        t0,t0,0x1
     6::800a2a18 40 48 09 00     sll        t1,t1,0x1
     6::800a2a1c 23 58 6a 00     subu       t3,v1,t2
     6::800a2a20 23 60 0a 01     subu       t4,t0,t2
     6::800a2a24 23 68 2a 01     subu       t5,t1,t2
     6::800a2a28 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a2a2c c2 67 0c 00     srl        t4,t4,0x1f
     6::800a2a30 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a2a34 13 00 cb a3     sb         t3,0x13(s8)
     6::800a2a38 27 00 cc a3     sb         t4,0x27(s8)
     6::800a2a3c 3b 00 cd a3     sb         t5,0x3b(s8)
     6::800a2a40 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a2a48 ff ff 93 32     andi       s3,s4,0xffff
     6::800a2a4c 00 99 13 00     sll        s3,s3,0x4
     6::800a2a50 21 98 77 02     addu       s3,s3,s7
     6::800a2a54 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a2a5c 02 a4 14 00     srl        s4,s4,0x10
     6::800a2a60 00 a1 14 00     sll        s4,s4,0x4
     6::800a2a64 21 a0 97 02     addu       s4,s4,s7
     6::800a2a68 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a2a70 21 c8 20 00     move       t9,at
     6::800a2a74 00 00 00 00     nop
     6::800a2a78 30 00 28 4a     RTPT
     6::800a2a7c 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a2a80 08 00 70 8e     lw         s0,0x8(s3)
     6::800a2a84 08 00 91 8e     lw         s1,0x8(s4)
     6::800a2a88 44 00 cf af     sw         t7,0x44(s8)
     6::800a2a8c 58 00 d0 af     sw         s0,0x58(s8)
     6::800a2a90 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a2a94 0c 00 cf 86     lh         t7,0xc(s6)
     6::800a2a98 0c 00 70 86     lh         s0,0xc(s3)
     6::800a2a9c 0c 00 91 86     lh         s1,0xc(s4)
     6::800a2aa0 0c 00 14 8f     lw         s4,0xc(t8)
     6::800a2aa4 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a2aa8 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a2aac 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a2ab0 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a2ab4 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a2ab8 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a2abc 10 00 15 97     lhu        s5,0x10(t8)
     6::800a2ac0 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a2ac4 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a2ac8 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a2acc 42 00 cf a7     sh         t7,0x42(s8)
     6::800a2ad0 56 00 d0 a7     sh         s0,0x56(s8)
     6::800a2ad4 6a 00 d1 a7     sh         s1,0x6a(s8)
     6::800a2ad8 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a2ae4 4c 00 c3 a7     sh         v1,0x4c(s8)
     6::800a2ae8 60 00 c8 a7     sh         t0,0x60(s8)
     6::800a2aec 74 00 c9 a7     sh         t1,0x74(s8)
     6::800a2af0 23 58 6a 00     subu       t3,v1,t2
     6::800a2af4 23 60 0a 01     subu       t4,t0,t2
     6::800a2af8 23 68 2a 01     subu       t5,t1,t2
     6::800a2afc c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a2b00 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a2b04 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a2b08 4e 00 cb a3     sb         t3,0x4e(s8)
     6::800a2b0c 62 00 cc a3     sb         t4,0x62(s8)
     6::800a2b10 76 00 cd a3     sb         t5,0x76(s8)
     6::800a2b14 40 18 03 00     sll        v1,v1,0x1
     6::800a2b18 40 40 08 00     sll        t0,t0,0x1
     6::800a2b1c 40 48 09 00     sll        t1,t1,0x1
     6::800a2b20 23 58 6a 00     subu       t3,v1,t2
     6::800a2b24 23 60 0a 01     subu       t4,t0,t2
     6::800a2b28 23 68 2a 01     subu       t5,t1,t2
     6::800a2b2c c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a2b30 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a2b34 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a2b38 4f 00 cb a3     sb         t3,0x4f(s8)
     6::800a2b3c 63 00 cc a3     sb         t4,0x63(s8)
     6::800a2b40 77 00 cd a3     sb         t5,0x77(s8)
     6::800a2b44 ff ff 93 32     andi       s3,s4,0xffff
     6::800a2b48 00 99 13 00     sll        s3,s3,0x4
     6::800a2b4c 21 98 77 02     addu       s3,s3,s7
     6::800a2b50 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a2b58 02 a4 14 00     srl        s4,s4,0x10
     6::800a2b5c 00 a1 14 00     sll        s4,s4,0x4
     6::800a2b60 21 a0 97 02     addu       s4,s4,s7
     6::800a2b64 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a2b6c 14 00 09 8f     lw         t1,0x14(t8)
     6::800a2b70 00 a9 15 00     sll        s5,s5,0x4
     6::800a2b74 21 a8 b7 02     addu       s5,s5,s7
     6::800a2b78 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a2b80 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a2b84 00 00 00 00     nop
     6::800a2b88 30 00 28 4a     RTPT
     6::800a2b8c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a2b90 08 00 90 8e     lw         s0,0x8(s4)
     6::800a2b94 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a2b98 80 00 cf af     sw         t7,0x80(s8)
     6::800a2b9c 94 00 d0 af     sw         s0,0x94(s8)
     6::800a2ba0 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a2ba4 0c 00 6f 86     lh         t7,0xc(s3)
     6::800a2ba8 0c 00 90 86     lh         s0,0xc(s4)
     6::800a2bac 0c 00 b1 86     lh         s1,0xc(s5)
     6::800a2bb0 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a2bb4 98 00 cd eb     gte_stSXY1 0x98(s8)
     6::800a2bb8 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a2bbc 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a2bc0 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a2bc4 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a2bc8 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a2bcc a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a2bd0 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a2bd4 7e 00 cf a7     sh         t7,0x7e(s8)
     6::800a2bd8 92 00 d0 a7     sh         s0,0x92(s8)
     6::800a2bdc a6 00 d1 a7     sh         s1,0xa6(s8)
     6::800a2be0 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a2bec 88 00 c3 a7     sh         v1,0x88(s8)
     6::800a2bf0 9c 00 c8 a7     sh         t0,0x9c(s8)
     6::800a2bf4 b0 00 c9 a7     sh         t1,0xb0(s8)
     6::800a2bf8 23 58 6a 00     subu       t3,v1,t2
     6::800a2bfc 23 60 0a 01     subu       t4,t0,t2
     6::800a2c00 23 68 2a 01     subu       t5,t1,t2
     6::800a2c04 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a2c08 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a2c0c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a2c10 8a 00 cb a3     sb         t3,0x8a(s8)
     6::800a2c14 9e 00 cc a3     sb         t4,0x9e(s8)
     6::800a2c18 b2 00 cd a3     sb         t5,0xb2(s8)
     6::800a2c1c 40 18 03 00     sll        v1,v1,0x1
     6::800a2c20 40 40 08 00     sll        t0,t0,0x1
     6::800a2c24 40 48 09 00     sll        t1,t1,0x1
     6::800a2c28 23 58 6a 00     subu       t3,v1,t2
     6::800a2c2c 23 60 0a 01     subu       t4,t0,t2
     6::800a2c30 23 68 2a 01     subu       t5,t1,t2
     6::800a2c34 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a2c38 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a2c3c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a2c40 8b 00 cb a3     sb         t3,0x8b(s8)
     6::800a2c44 9f 00 cc a3     sb         t4,0x9f(s8)
     6::800a2c48 b3 00 cd a3     sb         t5,0xb3(s8)
     6::800a2c4c 98 01 2d 84     lh         t5,0x198(at)
     6::800a2c50 9c 01 2e 84     lh         t6,0x19c(at)
     6::800a2c54 00 00 cb 87     lh         t3,0x0(s8)
     6::800a2c58 04 00 cc 87     lh         t4,0x4(s8)
     6::800a2c5c 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2c60 08 00 cf 8f     _lw        t7,0x8(s8)
     6::800a2c64 14 00 cb 87     lh         t3,0x14(s8)
     6::800a2c68 18 00 cc 87     lh         t4,0x18(s8)
     6::800a2c6c 08 00 cf af     sw         t7,0x8(s8)
     6::800a2c70 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2c74 1c 00 cf 8f     _lw        t7,0x1c(s8)
     6::800a2c78 28 00 cb 87     lh         t3,0x28(s8)
     6::800a2c7c 2c 00 cc 87     lh         t4,0x2c(s8)
     6::800a2c80 1c 00 cf af     sw         t7,0x1c(s8)
     6::800a2c84 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2c88 30 00 cf 8f     _lw        t7,0x30(s8)
     6::800a2c8c 3c 00 cb 87     lh         t3,0x3c(s8)
     6::800a2c90 40 00 cc 87     lh         t4,0x40(s8)
     6::800a2c94 30 00 cf af     sw         t7,0x30(s8)
     6::800a2c98 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2c9c 44 00 cf 8f     _lw        t7,0x44(s8)
     6::800a2ca0 50 00 cb 87     lh         t3,0x50(s8)
     6::800a2ca4 54 00 cc 87     lh         t4,0x54(s8)
     6::800a2ca8 44 00 cf af     sw         t7,0x44(s8)
     6::800a2cac 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2cb0 58 00 cf 8f     _lw        t7,0x58(s8)
     6::800a2cb4 64 00 cb 87     lh         t3,0x64(s8)
     6::800a2cb8 68 00 cc 87     lh         t4,0x68(s8)
     6::800a2cbc 58 00 cf af     sw         t7,0x58(s8)
     6::800a2cc0 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2cc4 6c 00 cf 8f     _lw        t7,0x6c(s8)
     6::800a2cc8 78 00 cb 87     lh         t3,0x78(s8)
     6::800a2ccc 7c 00 cc 87     lh         t4,0x7c(s8)
     6::800a2cd0 6c 00 cf af     sw         t7,0x6c(s8)
     6::800a2cd4 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2cd8 80 00 cf 8f     _lw        t7,0x80(s8)
     6::800a2cdc 8c 00 cb 87     lh         t3,0x8c(s8)
     6::800a2ce0 90 00 cc 87     lh         t4,0x90(s8)
     6::800a2ce4 80 00 cf af     sw         t7,0x80(s8)
     6::800a2ce8 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2cec 94 00 cf 8f     _lw        t7,0x94(s8)
     6::800a2cf0 a0 00 cb 87     lh         t3,0xa0(s8)
     6::800a2cf4 a4 00 cc 87     lh         t4,0xa4(s8)
     6::800a2cf8 94 00 cf af     sw         t7,0x94(s8)
     6::800a2cfc 4c 8b 02 0c     jal        FUN_OVR_226__800a2d30                            undefined FUN_OVR_226__800a2d30()
     6::800a2d00 a8 00 cf 8f     _lw        t7,0xa8(s8)
     6::800a2d04 0a 80 03 3c     lui        v1,0x800a
     6::800a2d08 1c 2d 63 24     addiu      v1,v1,0x2d1c
     6::800a2d0c a8 00 cf af     sw         t7,0xa8(s8)
     6::800a2d10 3c 00 23 af     sw         v1=>LAB_OVR_226__800a2d1c,0x3c(t9)
     6::800a2d14 a2 00 01 04     bgez       zero,LAB_OVR_226__800a2fa0
     6::800a2d18 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a2d1c                           XREF[1]:     OVR_226::800a2d10(*)  
     6::800a2d1c 04 00 98 8c     lw         t8,0x4(a0)
     6::800a2d20 f9 fe 01 04     bgez       zero,LAB_OVR_226__800a2908
     6::800a2d24 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_226__800a2d28                           XREF[8]:     OVR_226::800a310c(j), 
                                                                                          OVR_226::800a3170(j), 
                                                                                          OVR_226::800a3178(j), 
                                                                                          OVR_226::800a31b8(j), 
                                                                                          OVR_226::800a3350(j), 
                                                                                          OVR_226::800a33fc(j), 
                                                                                          OVR_226::800a3520(j), 
                                                                                          OVR_226::800a35d8(j)  
     6::800a2d28 08 00 e0 03     jr         ra
     6::800a2d2c 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2d30()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2d30                           XREF[9]:     OVR_226::800a2c5c(c), 
                                                                                          OVR_226::800a2c70(c), 
                                                                                          OVR_226::800a2c84(c), 
                                                                                          OVR_226::800a2c98(c), 
                                                                                          OVR_226::800a2cac(c), 
                                                                                          OVR_226::800a2cc0(c), 
                                                                                          OVR_226::800a2cd4(c), 
                                                                                          OVR_226::800a2ce8(c), 
                                                                                          OVR_226::800a2cfc(c)  
     6::800a2d30 23 58 6d 01     subu       t3,t3,t5
     6::800a2d34 02 00 61 05     bgez       t3,LAB_OVR_226__800a2d40
     6::800a2d38 23 60 8e 01     _subu      t4,t4,t6
     6::800a2d3c 22 58 0b 00     sub        t3,zero,t3
                             LAB_OVR_226__800a2d40                           XREF[1]:     OVR_226::800a2d34(j)  
     6::800a2d40 02 00 81 05     bgez       t4,LAB_OVR_226__800a2d4c
     6::800a2d44 00 00 00 00     _nop
     6::800a2d48 22 60 0c 00     sub        t4,zero,t4
                             LAB_OVR_226__800a2d4c                           XREF[1]:     OVR_226::800a2d40(j)  
     6::800a2d4c 23 40 6c 01     subu       t0,t3,t4
     6::800a2d50 03 00 01 05     bgez       t0,LAB_OVR_226__800a2d60
     6::800a2d54 83 40 0c 00     _sra       t0,t4,0x2
     6::800a2d58 83 40 0b 00     sra        t0,t3,0x2
     6::800a2d5c 21 58 80 01     move       t3,t4
                             LAB_OVR_226__800a2d60                           XREF[1]:     OVR_226::800a2d50(j)  
     6::800a2d60 21 58 68 01     addu       t3,t3,t0
     6::800a2d64 00 f0 6b 25     addiu      t3,t3,-0x1000
     6::800a2d68 0b 00 61 05     bgez       t3,LAB_OVR_226__800a2d98
     6::800a2d6c 80 40 0b 00     _sll       t0,t3,0x2
     6::800a2d70 00 10 08 25     addiu      t0,t0,0x1000
     6::800a2d74 06 00 00 05     bltz       t0,LAB_OVR_226__800a2d90
     6::800a2d78 00 30 8f 48     _gte_ldRGB t7
     6::800a2d7c 00 40 88 48     gte_ldIR0  t0
     6::800a2d80 00 00 00        nDPCS
                 00 00 00 
                 00 00 10 
     6::800a2d8c 00 b0 0f 48     gte_stRGB2 t7
                             LAB_OVR_226__800a2d90                           XREF[1]:     OVR_226::800a2d74(j)  
     6::800a2d90 08 00 e0 03     jr         ra
     6::800a2d94 00 00 00 00     _nop
                             LAB_OVR_226__800a2d98                           XREF[1]:     OVR_226::800a2d68(j)  
     6::800a2d98 08 00 e0 03     jr         ra
     6::800a2d9c 00 00 0f 24     _li        t7,0x0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2da0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2da0                           XREF[4]:     FUN_OVR_226__800a2e2c:800a2e78(j
                                                                                          FUN_OVR_226__800a2e2c:800a2f10(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f38(c
                                                                                          FUN_OVR_226__800a2e2c:800a2fa4(c
     6::800a2da0 00 00 d3 27     addiu      s3,s8,0x0
     6::800a2da4 50 00 d4 27     addiu      s4,s8,0x50
     6::800a2da8 64 00 d5 27     addiu      s5,s8,0x64
     6::800a2dac d0 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2db0 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2db4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2db4                           XREF[6]:     FUN_OVR_226__800a2e2c:800a2e80(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f20(j
                                                                                          FUN_OVR_226__800a2e2c:800a2f30(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f60(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f80(c
                                                                                          FUN_OVR_226__800a2e2c:800a2fb4(c
     6::800a2db4 50 00 d3 27     addiu      s3,s8,0x50
     6::800a2db8 14 00 d4 27     addiu      s4,s8,0x14
     6::800a2dbc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2dc0 cb 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2dc4 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2dc8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2dc8                           XREF[6]:     FUN_OVR_226__800a2e2c:800a2ea8(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f08(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f48(j
                                                                                          FUN_OVR_226__800a2e2c:800a2f58(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f88(c
                                                                                          FUN_OVR_226__800a2e2c:800a2fc4(c
     6::800a2dc8 64 00 d3 27     addiu      s3,s8,0x64
     6::800a2dcc 78 00 d4 27     addiu      s4,s8,0x78
     6::800a2dd0 28 00 d5 27     addiu      s5,s8,0x28
     6::800a2dd4 c6 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2dd8 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a2ddc                           XREF[4]:     OVR_226::800a2ef8(j), 
                                                                                          OVR_226::800a2f70(j), 
                                                                                          OVR_226::800a2f98(j), 
                                                                                          OVR_226::800a2fdc(j)  
     6::800a2ddc 78 00 d3 27     addiu      s3,s8,0x78
     6::800a2de0 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a2de4 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a2de8 c1 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2dec 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2df0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2df0                           XREF[2]:     FUN_OVR_226__800a2e2c:800a2ea0(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f78(c
     6::800a2df0 64 00 d3 27     addiu      s3,s8,0x64
     6::800a2df4 00 00 d4 27     addiu      s4,s8,0x0
     6::800a2df8 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2dfc bc 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2e00 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2e04()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2e04                           XREF[2]:     FUN_OVR_226__800a2e2c:800a2eb8(j
                                                                                          FUN_OVR_226__800a2e2c:800a2f28(c
     6::800a2e04 14 00 d3 27     addiu      s3,s8,0x14
     6::800a2e08 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a2e0c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2e10 b7 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2e14 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2e18()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2e18                           XREF[2]:     FUN_OVR_226__800a2e2c:800a2e88(c
                                                                                          FUN_OVR_226__800a2e2c:800a2f50(c
     6::800a2e18 28 00 d3 27     addiu      s3,s8,0x28
     6::800a2e1c 00 00 d4 27     addiu      s4,s8,0x0
     6::800a2e20 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2e24 b2 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2e28 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2e2c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2e2c                           XREF[2]:     OVR_226::800a2e98(j), 
                                                                                          OVR_226::800a2f00(c)  
     6::800a2e2c 28 00 d3 27     addiu      s3,s8,0x28
     6::800a2e30 78 00 d4 27     addiu      s4,s8,0x78
     6::800a2e34 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a2e38 ad 00 01 04     bgez       zero,FUN_OVR_226__800a30f0
     6::800a2e3c 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a2e40 50 00 d3 27     addiu      s3,s8,0x50
     6::800a2e44 14 00 d4 27     addiu      s4,s8,0x14
     6::800a2e48 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2e4c 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a2e50 3c 8c 02 0c     jal        FUN_OVR_226__800a30f0                            undefined FUN_OVR_226__800a30f0()
     6::800a2e54 0c 00 0a 24     _li        t2,0xc
     6::800a2e58 64 00 d3 27     addiu      s3,s8,0x64
     6::800a2e5c 78 00 d4 27     addiu      s4,s8,0x78
     6::800a2e60 28 00 d5 27     addiu      s5,s8,0x28
     6::800a2e64 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a2e68 3c 8c 02 0c     jal        FUN_OVR_226__800a30f0                            undefined FUN_OVR_226__800a30f0()
     6::800a2e6c 0c 00 0a 24     _li        t2,0xc
     6::800a2e70 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2e74 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2e78 c9 ff 01 04     bgez       zero,FUN_OVR_226__800a2da0
     6::800a2e7c 0c 00 0a 24     _li        t2,0xc
     6::800a2e80 6d 8b 02 0c     jal        FUN_OVR_226__800a2db4                            undefined FUN_OVR_226__800a2db4()
     6::800a2e84 0c 00 0a 24     _li        t2,0xc
     6::800a2e88 86 8b 02 0c     jal        FUN_OVR_226__800a2e18                            undefined FUN_OVR_226__800a2e18()
     6::800a2e8c 0c 00 0a 24     _li        t2,0xc
     6::800a2e90 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2e94 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2e98 e4 ff 01 04     bgez       zero,FUN_OVR_226__800a2e2c
     6::800a2e9c 0c 00 0a 24     _li        t2,0xc
     6::800a2ea0 7c 8b 02 0c     jal        FUN_OVR_226__800a2df0                            undefined FUN_OVR_226__800a2df0()
     6::800a2ea4 0c 00 0a 24     _li        t2,0xc
     6::800a2ea8 72 8b 02 0c     jal        FUN_OVR_226__800a2dc8                            undefined FUN_OVR_226__800a2dc8()
     6::800a2eac 0c 00 0a 24     _li        t2,0xc
     6::800a2eb0 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2eb4 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2eb8 d2 ff 01 04     bgez       zero,FUN_OVR_226__800a2e04
     6::800a2ebc 0c 00 0a 24     _li        t2,0xc
     6::800a2ec0 00 00 d3 27     addiu      s3,s8,0x0
     6::800a2ec4 14 00 d4 27     addiu      s4,s8,0x14
     6::800a2ec8 78 00 d5 27     addiu      s5,s8,0x78
     6::800a2ecc 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a2ed0 3c 8c 02 0c     jal        FUN_OVR_226__800a30f0                            undefined FUN_OVR_226__800a30f0()
     6::800a2ed4 0c 00 0a 24     _li        t2,0xc
     6::800a2ed8 00 00 d3 27     addiu      s3,s8,0x0
     6::800a2edc 78 00 d4 27     addiu      s4,s8,0x78
     6::800a2ee0 28 00 d5 27     addiu      s5,s8,0x28
     6::800a2ee4 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a2ee8 3c 8c 02 0c     jal        FUN_OVR_226__800a30f0                            undefined FUN_OVR_226__800a30f0()
     6::800a2eec 0c 00 0a 24     _li        t2,0xc
     6::800a2ef0 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2ef4 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2ef8 b8 ff 01 04     bgez       zero,LAB_OVR_226__800a2ddc
     6::800a2efc 0c 00 0a 24     _li        t2,0xc
     6::800a2f00 8b 8b 02 0c     jal        FUN_OVR_226__800a2e2c                            undefined FUN_OVR_226__800a2e2c()
     6::800a2f04 0c 00 0a 24     _li        t2,0xc
     6::800a2f08 72 8b 02 0c     jal        FUN_OVR_226__800a2dc8                            undefined FUN_OVR_226__800a2dc8()
     6::800a2f0c 04 00 0a 24     _li        t2,0x4
     6::800a2f10 68 8b 02 0c     jal        FUN_OVR_226__800a2da0                            undefined FUN_OVR_226__800a2da0()
     6::800a2f14 0c 00 0a 24     _li        t2,0xc
     6::800a2f18 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2f1c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2f20 a4 ff 01 04     bgez       zero,FUN_OVR_226__800a2db4
     6::800a2f24 0c 00 0a 24     _li        t2,0xc
     6::800a2f28 81 8b 02 0c     jal        FUN_OVR_226__800a2e04                            undefined FUN_OVR_226__800a2e04()
     6::800a2f2c 0c 00 0a 24     _li        t2,0xc
     6::800a2f30 6d 8b 02 0c     jal        FUN_OVR_226__800a2db4                            undefined FUN_OVR_226__800a2db4()
     6::800a2f34 04 00 0a 24     _li        t2,0x4
     6::800a2f38 68 8b 02 0c     jal        FUN_OVR_226__800a2da0                            undefined FUN_OVR_226__800a2da0()
     6::800a2f3c 0c 00 0a 24     _li        t2,0xc
     6::800a2f40 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2f44 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2f48 9f ff 01 04     bgez       zero,FUN_OVR_226__800a2dc8
     6::800a2f4c 0c 00 0a 24     _li        t2,0xc
     6::800a2f50 86 8b 02 0c     jal        FUN_OVR_226__800a2e18                            undefined FUN_OVR_226__800a2e18()
     6::800a2f54 0c 00 0a 24     _li        t2,0xc
     6::800a2f58 72 8b 02 0c     jal        FUN_OVR_226__800a2dc8                            undefined FUN_OVR_226__800a2dc8()
     6::800a2f5c 08 00 0a 24     _li        t2,0x8
     6::800a2f60 6d 8b 02 0c     jal        FUN_OVR_226__800a2db4                            undefined FUN_OVR_226__800a2db4()
     6::800a2f64 0c 00 0a 24     _li        t2,0xc
     6::800a2f68 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2f6c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2f70 9a ff 01 04     bgez       zero,LAB_OVR_226__800a2ddc
     6::800a2f74 0c 00 0a 24     _li        t2,0xc
     6::800a2f78 7c 8b 02 0c     jal        FUN_OVR_226__800a2df0                            undefined FUN_OVR_226__800a2df0()
     6::800a2f7c 0c 00 0a 24     _li        t2,0xc
     6::800a2f80 6d 8b 02 0c     jal        FUN_OVR_226__800a2db4                            undefined FUN_OVR_226__800a2db4()
     6::800a2f84 08 00 0a 24     _li        t2,0x8
     6::800a2f88 72 8b 02 0c     jal        FUN_OVR_226__800a2dc8                            undefined FUN_OVR_226__800a2dc8()
     6::800a2f8c 0c 00 0a 24     _li        t2,0xc
     6::800a2f90 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2f94 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2f98 90 ff 01 04     bgez       zero,LAB_OVR_226__800a2ddc
     6::800a2f9c 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a2fa0                           XREF[1]:     OVR_226::800a2d14(j)  
     6::800a2fa0 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a2fa4 68 8b 02 0c     jal        FUN_OVR_226__800a2da0                            undefined FUN_OVR_226__800a2da0()
     6::800a2fa8 0c 00 0a 24     _li        t2,0xc
     6::800a2fac 04 00 03 24     li         v1,0x4
     6::800a2fb0 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a2fb4 6d 8b 02 0c     jal        FUN_OVR_226__800a2db4                            undefined FUN_OVR_226__800a2db4()
     6::800a2fb8 0c 00 0a 24     _li        t2,0xc
     6::800a2fbc 08 00 03 24     li         v1,0x8
     6::800a2fc0 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a2fc4 72 8b 02 0c     jal        FUN_OVR_226__800a2dc8                            undefined FUN_OVR_226__800a2dc8()
     6::800a2fc8 0c 00 0a 24     _li        t2,0xc
     6::800a2fcc 0c 00 03 24     li         v1,0xc
     6::800a2fd0 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a2fd4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a2fd8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a2fdc 7f ff 01 04     bgez       zero,LAB_OVR_226__800a2ddc
     6::800a2fe0 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a2fe4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a2fe4                           XREF[5]:     FUN_OVR_226__800a30f0:800a3294(c
                                                                                          FUN_OVR_226__800a30f0:800a32a8(c
                                                                                          FUN_OVR_226__800a30f0:800a32bc(c
                                                                                          FUN_OVR_226__800a30f0:800a32d0(c
                                                                                          FUN_OVR_226__800a30f0:800a32e4(c
     6::800a2fe4 00 00 ab 85     lh         t3,0x0(t5)
     6::800a2fe8 00 00 cc 85     lh         t4,0x0(t6)
     6::800a2fec 00 00 eb a5     sh         t3,0x0(t7)
     6::800a2ff0 21 18 6c 01     addu       v1,t3,t4
     6::800a2ff4 43 18 03 00     sra        v1,v1,0x1
     6::800a2ff8 00 00 03 a6     sh         v1,0x0(s0)
     6::800a2ffc 02 00 ab 85     lh         t3,0x2(t5)
     6::800a3000 02 00 cc 85     lh         t4,0x2(t6)
     6::800a3004 02 00 eb a5     sh         t3,0x2(t7)
     6::800a3008 21 18 6c 01     addu       v1,t3,t4
     6::800a300c 43 18 03 00     sra        v1,v1,0x1
     6::800a3010 02 00 03 a6     sh         v1,0x2(s0)
     6::800a3014 04 00 ab 85     lh         t3,0x4(t5)
     6::800a3018 04 00 cc 85     lh         t4,0x4(t6)
     6::800a301c 04 00 eb a5     sh         t3,0x4(t7)
     6::800a3020 21 18 6c 01     addu       v1,t3,t4
     6::800a3024 43 18 03 00     sra        v1,v1,0x1
     6::800a3028 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a302c 00 08 83 48     gte_ldVZ0  v1
     6::800a3030 04 00 03 a6     sh         v1,0x4(s0)
     6::800a3034 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a3038 01 00 18 4a     RTPS
     6::800a303c 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a3040 08 00 eb a1     sb         t3,0x8(t7)
     6::800a3044 21 18 6c 01     addu       v1,t3,t4
     6::800a3048 43 18 03 00     sra        v1,v1,0x1
     6::800a304c 08 00 03 a2     sb         v1,0x8(s0)
     6::800a3050 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a3054 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a3058 09 00 eb a1     sb         t3,0x9(t7)
     6::800a305c 21 18 6c 01     addu       v1,t3,t4
     6::800a3060 43 18 03 00     sra        v1,v1,0x1
     6::800a3064 09 00 03 a2     sb         v1,0x9(s0)
     6::800a3068 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a306c 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a3070 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a3074 21 18 6c 01     addu       v1,t3,t4
     6::800a3078 43 18 03 00     sra        v1,v1,0x1
     6::800a307c 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a3080 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a3084 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a3088 06 00 eb a1     sb         t3,0x6(t7)
     6::800a308c 21 18 6c 01     addu       v1,t3,t4
     6::800a3090 43 18 03 00     sra        v1,v1,0x1
     6::800a3094 06 00 03 a2     sb         v1,0x6(s0)
     6::800a3098 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a309c 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a30a0 07 00 eb a1     sb         t3,0x7(t7)
     6::800a30a4 21 18 6c 01     addu       v1,t3,t4
     6::800a30a8 43 18 03 00     sra        v1,v1,0x1
     6::800a30ac 07 00 03 a2     sb         v1,0x7(s0)
     6::800a30b0 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a30b4 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a30b8 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a30bc 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a30c0 5c 00 2b 8c     lw         t3,0x5c(at)
     6::800a30c4 00 98 03 48     gte_stSZ3  v1
     6::800a30c8 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a30cc 10 00 03 ae     sw         v1,0x10(s0)
     6::800a30d0 23 40 6b 00     subu       t0,v1,t3
     6::800a30d4 c2 47 08 00     srl        t0,t0,0x1f
     6::800a30d8 12 00 08 a2     sb         t0,0x12(s0)
     6::800a30dc 40 18 03 00     sll        v1,v1,0x1
     6::800a30e0 23 40 6b 00     subu       t0,v1,t3
     6::800a30e4 c2 47 08 00     srl        t0,t0,0x1f
     6::800a30e8 08 00 e0 03     jr         ra
     6::800a30ec 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a30f0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a30f0                           XREF[12]:    FUN_OVR_226__800a2da0:800a2dac(j
                                                                                          FUN_OVR_226__800a2db4:800a2dc0(j
                                                                                          FUN_OVR_226__800a2dc8:800a2dd4(j
                                                                                          FUN_OVR_226__800a2e2c:800a2de8(j
                                                                                          FUN_OVR_226__800a2df0:800a2dfc(j
                                                                                          FUN_OVR_226__800a2e04:800a2e10(j
                                                                                          FUN_OVR_226__800a2e18:800a2e24(j
                                                                                          FUN_OVR_226__800a2e2c:800a2e38(j
                                                                                          FUN_OVR_226__800a2e2c:800a2e50(c
                                                                                          FUN_OVR_226__800a2e2c:800a2e68(c
                                                                                          FUN_OVR_226__800a2e2c:800a2ed0(c
                                                                                          FUN_OVR_226__800a2e2c:800a2ee8(c
     6::800a30f0 13 00 6f 82     lb         t7,0x13(s3)
     6::800a30f4 13 00 90 82     lb         s0,0x13(s4)
     6::800a30f8 13 00 b1 82     lb         s1,0x13(s5)
     6::800a30fc 13 00 d2 82     lb         s2,0x13(s6)
     6::800a3100 24 18 f0 01     and        v1,t7,s0
     6::800a3104 24 18 71 00     and        v1,v1,s1
     6::800a3108 24 18 72 00     and        v1,v1,s2
     6::800a310c 06 ff 60 14     bne        v1,zero,LAB_OVR_226__800a2d28
     6::800a3110 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a3114 12 00 90 82     lb         s0,0x12(s4)
     6::800a3118 12 00 b1 82     lb         s1,0x12(s5)
     6::800a311c 12 00 d2 82     lb         s2,0x12(s6)
     6::800a3120 25 78 f0 01     or         t7,t7,s0
     6::800a3124 25 78 f1 01     or         t7,t7,s1
     6::800a3128 25 78 f2 01     or         t7,t7,s2
     6::800a312c 23 00 e0 15     bne        t7,zero,LAB_OVR_226__800a31bc
     6::800a3130 6c 00 28 8c     _lw        t0,0x6c(at)
     6::800a3134 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a3138 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a313c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a3140 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a3144 23 78 68 01     subu       t7,t3,t0
     6::800a3148 23 80 88 01     subu       s0,t4,t0
     6::800a314c 23 88 a8 01     subu       s1,t5,t0
     6::800a3150 23 90 c8 01     subu       s2,t6,t0
     6::800a3154 24 40 6c 01     and        t0,t3,t4
     6::800a3158 24 40 0d 01     and        t0,t0,t5
     6::800a315c 24 40 0e 01     and        t0,t0,t6
     6::800a3160 25 78 f0 01     or         t7,t7,s0
     6::800a3164 25 78 f1 01     or         t7,t7,s1
     6::800a3168 27 78 f2 01     nor        t7,t7,s2
     6::800a316c 25 78 e8 01     or         t7,t7,t0
     6::800a3170 ed fe e0 05     bltz       t7,LAB_OVR_226__800a2d28
     6::800a3174 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a3178 eb fe e0 05     bltz       t7,LAB_OVR_226__800a2d28
     6::800a317c 08 00 6f 8e     _lw        t7,0x8(s3)
     6::800a3180 08 00 90 8e     lw         s0,0x8(s4)
     6::800a3184 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a3188 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a318c 25 40 f0 01     or         t0,t7,s0
     6::800a3190 25 40 11 01     or         t0,t0,s1
     6::800a3194 02 00 00 15     bne        t0,zero,LAB_OVR_226__800a31a0
     6::800a3198 04 00 03 24     _li        v1,0x4
     6::800a319c 00 00 03 24     li         v1,0x0
                             LAB_OVR_226__800a31a0                           XREF[1]:     OVR_226::800a3194(j)  
     6::800a31a0 25 40 11 02     or         t0,s0,s1
     6::800a31a4 25 40 12 01     or         t0,t0,s2
     6::800a31a8 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a31b4
     6::800a31ac 00 00 00 00     _nop
     6::800a31b0 08 00 63 34     ori        v1,v1,0x8
                             LAB_OVR_226__800a31b4                           XREF[1]:     OVR_226::800a31a8(j)  
     6::800a31b4 24 50 43 01     and        t2,t2,v1
     6::800a31b8 db fe 40 11     beq        t2,zero,LAB_OVR_226__800a2d28
                             LAB_OVR_226__800a31bc                           XREF[1]:     OVR_226::800a312c(j)  
     6::800a31bc 70 00 2a ac     _sw        t2,0x70(at)
     6::800a31c0 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a31c4 24 03 28 24     addiu      t0,at,0x324
     6::800a31c8 53 00 1e 11     beq        t0,s8,LAB_OVR_226__800a3318
     6::800a31cc 04 00 39 27     _addiu     t9,t9,0x4
     6::800a31d0 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a31d4 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a31d8 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a31dc 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a31e0 b4 01 28 24     addiu      t0,at,0x1b4
     6::800a31e4 16 00 1e 15     bne        t0,s8,LAB_OVR_226__800a3240
     6::800a31e8 28 00 23 8c     _lw        v1,0x28(at)
     6::800a31ec b4 00 c9 8f     lw         t1,0xb4(s8)
     6::800a31f0 23 18 6c 01     subu       v1,t3,t4
     6::800a31f4 82 48 09 00     srl        t1,t1,0x2
     6::800a31f8 21 48 38 01     addu       t1,t1,t8
     6::800a31fc 18 00 29 81     lb         t1,0x18(t1)
     6::800a3200 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a320c
     6::800a3204 21 e0 60 01     _move      gp,t3
     6::800a3208 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a320c                           XREF[1]:     OVR_226::800a3200(j)  
     6::800a320c 23 18 8d 03     subu       v1,gp,t5
     6::800a3210 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a321c
     6::800a3214 23 18 8e 03     _subu      v1,gp,t6
     6::800a3218 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a321c                           XREF[1]:     OVR_226::800a3210(j)  
     6::800a321c 02 00 60 1c     bgtz       v1,LAB_OVR_226__800a3228
     6::800a3220 00 00 00 00     _nop
     6::800a3224 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a3228                           XREF[1]:     OVR_226::800a321c(j)  
     6::800a3228 21 18 80 03     move       v1,gp
     6::800a322c 82 e1 1c 00     srl        gp,gp,0x6
     6::800a3230 21 e0 89 03     addu       gp,gp,t1
     6::800a3234 80 e0 1c 00     sll        gp,gp,0x2
     6::800a3238 21 e0 85 03     addu       gp,gp,a1
     6::800a323c 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a3240                           XREF[1]:     OVR_226::800a31e4(j)  
     6::800a3240 00 00 00 00     nop
     6::800a3244 23 88 63 01     subu       s1,t3,v1
     6::800a3248 23 90 83 01     subu       s2,t4,v1
     6::800a324c 23 78 a3 01     subu       t7,t5,v1
     6::800a3250 23 80 c3 01     subu       s0,t6,v1
     6::800a3254 42 8f 11 00     srl        s1,s1,0x1d
     6::800a3258 04 00 31 32     andi       s1,s1,0x4
     6::800a325c 02 97 12 00     srl        s2,s2,0x1c
     6::800a3260 08 00 52 32     andi       s2,s2,0x8
     6::800a3264 25 88 32 02     or         s1,s1,s2
     6::800a3268 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a326c 10 00 ef 31     andi       t7,t7,0x10
     6::800a3270 25 88 2f 02     or         s1,s1,t7
     6::800a3274 82 86 10 00     srl        s0,s0,0x1a
     6::800a3278 20 00 10 32     andi       s0,s0,0x20
     6::800a327c 25 88 30 02     or         s1,s1,s0
     6::800a3280 25 00 20 12     beq        s1,zero,LAB_OVR_226__800a3318
     6::800a3284 21 68 60 02     _move      t5,s3
     6::800a3288 21 70 80 02     move       t6,s4
     6::800a328c b8 00 de 27     addiu      s8,s8,0xb8
     6::800a3290 00 00 cf 27     addiu      t7,s8,0x0
     6::800a3294 f9 8b 02 0c     jal        FUN_OVR_226__800a2fe4                            undefined FUN_OVR_226__800a2fe4()
     6::800a3298 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a329c 21 68 80 02     move       t5,s4
     6::800a32a0 21 70 c0 02     move       t6,s6
     6::800a32a4 14 00 cf 27     addiu      t7,s8,0x14
     6::800a32a8 f9 8b 02 0c     jal        FUN_OVR_226__800a2fe4                            undefined FUN_OVR_226__800a2fe4()
     6::800a32ac 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a32b0 21 68 a0 02     move       t5,s5
     6::800a32b4 21 70 60 02     move       t6,s3
     6::800a32b8 28 00 cf 27     addiu      t7,s8,0x28
     6::800a32bc f9 8b 02 0c     jal        FUN_OVR_226__800a2fe4                            undefined FUN_OVR_226__800a2fe4()
     6::800a32c0 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a32c4 21 68 c0 02     move       t5,s6
     6::800a32c8 21 70 a0 02     move       t6,s5
     6::800a32cc 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a32d0 f9 8b 02 0c     jal        FUN_OVR_226__800a2fe4                            undefined FUN_OVR_226__800a2fe4()
     6::800a32d4 a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a32d8 21 68 80 02     move       t5,s4
     6::800a32dc 21 70 a0 02     move       t6,s5
     6::800a32e0 14 00 cf 27     addiu      t7,s8,0x14
     6::800a32e4 f9 8b 02 0c     jal        FUN_OVR_226__800a2fe4                            undefined FUN_OVR_226__800a2fe4()
     6::800a32e8 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a32ec 21 18 21 02     addu       v1,s1,at
     6::800a32f0 48 01 63 8c     lw         v1,0x148(v1)
     6::800a32f4 0a 80 08 3c     lui        t0,0x800a
     6::800a32f8 08 33 08 25     addiu      t0,t0,0x3308
     6::800a32fc 3c 00 28 af     sw         t0=>LAB_OVR_226__800a3308,0x3c(t9)
     6::800a3300 08 00 60 00     jr         v1
     6::800a3304 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a3308                           XREF[1]:     FUN_OVR_226__800a30f0:800a32fc(*
     6::800a3308 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a330c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a3310 08 00 e0 03     jr         ra
     6::800a3314 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a3318                           XREF[2]:     OVR_226::800a31c8(j), 
                                                                                          OVR_226::800a3280(j)  
     6::800a3318 70 00 23 8c     lw         v1,0x70(at)
     6::800a331c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a3320 21 18 61 00     addu       v1,v1,at
     6::800a3324 84 01 63 8c     lw         v1,0x184(v1)
     6::800a3328 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a332c 08 00 60 00     jr         v1
     6::800a3330 00 00 00 00     _nop
     6::800a3334 21 98 80 02     move       s3,s4
     6::800a3338 21 a0 c0 02     move       s4,s6
     6::800a333c 13 00 6f 82     lb         t7,0x13(s3)
     6::800a3340 13 00 90 82     lb         s0,0x13(s4)
     6::800a3344 13 00 b1 82     lb         s1,0x13(s5)
     6::800a3348 24 18 f0 01     and        v1,t7,s0
     6::800a334c 24 18 71 00     and        v1,v1,s1
     6::800a3350 75 fe 60 04     bltz       v1,LAB_OVR_226__800a2d28
     6::800a3354 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a3358 12 00 90 82     lb         s0,0x12(s4)
     6::800a335c 12 00 b1 82     lb         s1,0x12(s5)
     6::800a3360 25 78 f0 01     or         t7,t7,s0
     6::800a3364 25 78 f1 01     or         t7,t7,s1
     6::800a3368 5a 00 e0 05     bltz       t7,LAB_OVR_226__800a34d4
     6::800a336c 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a3370 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a3374 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a3378 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a337c 08 00 90 8e     lw         s0,0x8(s4)
     6::800a3380 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a3384 06 00 73 86     lh         s3,0x6(s3)
     6::800a3388 06 00 94 86     lh         s4,0x6(s4)
     6::800a338c 06 00 b5 86     lh         s5,0x6(s5)
     6::800a3390 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a3394 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a3398 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a339c a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a33a0 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a33a4 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a33a8 00 36 03 3c     lui        v1,0x3600
     6::800a33ac 25 18 6f 00     or         v1,v1,t7
     6::800a33b0 04 00 43 ac     sw         v1,0x4(v0)
     6::800a33b4 08 00 4b ac     sw         t3,0x8(v0)
     6::800a33b8 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a33bc 10 00 50 ac     sw         s0,0x10(v0)
     6::800a33c0 14 00 4c ac     sw         t4,0x14(v0)
     6::800a33c4 18 00 54 ac     sw         s4,0x18(v0)
     6::800a33c8 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a33cc 20 00 4d ac     sw         t5,0x20(v0)
     6::800a33d0 24 00 55 ac     sw         s5,0x24(v0)
     6::800a33d4 28 00 09 24     li         t1,0x28
     6::800a33d8 35 00 01 04     bgez       zero,LAB_OVR_226__800a34b0
     6::800a33dc 00 09 0a 3c     _lui       t2,0x900
     6::800a33e0 13 00 6f 82     lb         t7,0x13(s3)
     6::800a33e4 13 00 90 82     lb         s0,0x13(s4)
     6::800a33e8 13 00 b1 82     lb         s1,0x13(s5)
     6::800a33ec 13 00 d2 82     lb         s2,0x13(s6)
     6::800a33f0 24 18 f0 01     and        v1,t7,s0
     6::800a33f4 24 18 71 00     and        v1,v1,s1
     6::800a33f8 24 18 72 00     and        v1,v1,s2
     6::800a33fc 4a fe 60 14     bne        v1,zero,LAB_OVR_226__800a2d28
     6::800a3400 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a3404 12 00 90 82     lb         s0,0x12(s4)
     6::800a3408 12 00 b1 82     lb         s1,0x12(s5)
     6::800a340c 12 00 d2 82     lb         s2,0x12(s6)
     6::800a3410 25 78 f0 01     or         t7,t7,s0
     6::800a3414 25 78 f1 01     or         t7,t7,s1
     6::800a3418 25 78 f2 01     or         t7,t7,s2
     6::800a341c 56 00 e0 15     bne        t7,zero,LAB_OVR_226__800a3578
     6::800a3420 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a3424 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a3428 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a342c 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a3430 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a3434 08 00 90 8e     lw         s0,0x8(s4)
     6::800a3438 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a343c 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a3440 06 00 73 86     lh         s3,0x6(s3)
     6::800a3444 06 00 94 86     lh         s4,0x6(s4)
     6::800a3448 06 00 b5 86     lh         s5,0x6(s5)
     6::800a344c a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a3450 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a3454 06 00 d4 86     lh         s4,0x6(s6)
     6::800a3458 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a345c aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a3460 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a3464 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a3468 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a346c 00 3e 03 3c     lui        v1,0x3e00
     6::800a3470 25 18 6f 00     or         v1,v1,t7
     6::800a3474 04 00 43 ac     sw         v1,0x4(v0)
     6::800a3478 08 00 4b ac     sw         t3,0x8(v0)
     6::800a347c 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a3480 10 00 50 ac     sw         s0,0x10(v0)
     6::800a3484 14 00 4c ac     sw         t4,0x14(v0)
     6::800a3488 18 00 54 ac     sw         s4,0x18(v0)
     6::800a348c 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a3490 20 00 4d ac     sw         t5,0x20(v0)
     6::800a3494 24 00 55 ac     sw         s5,0x24(v0)
     6::800a3498 28 00 52 ac     sw         s2,0x28(v0)
     6::800a349c 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a34a0 02 1c 15 00     srl        v1,s5,0x10
     6::800a34a4 30 00 43 ac     sw         v1,0x30(v0)
     6::800a34a8 34 00 09 24     li         t1,0x34
     6::800a34ac 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a34b0                           XREF[1]:     OVR_226::800a33d8(j)  
     6::800a34b0 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a34b4 00 42 02 00     sll        t0,v0,0x8
     6::800a34b8 02 42 08 00     srl        t0,t0,0x8
     6::800a34bc 25 18 6a 00     or         v1,v1,t2
     6::800a34c0 00 00 43 ac     sw         v1,0x0(v0)
     6::800a34c4 21 10 49 00     addu       v0,v0,t1
     6::800a34c8 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a34cc 08 00 e0 03     jr         ra
     6::800a34d0 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800a34d4                           XREF[1]:     OVR_226::800a3368(j)  
     6::800a34d4 58 00 3f ac     sw         ra,0x58(at)
     6::800a34d8 98 01 2f 84     lh         t7,0x198(at)
     6::800a34dc 9a 01 30 84     lh         s0,0x19a(at)
     6::800a34e0 9c 01 31 84     lh         s1,0x19c(at)
     6::800a34e4 00 00 63 86     lh         v1,0x0(s3)
     6::800a34e8 02 00 68 86     lh         t0,0x2(s3)
     6::800a34ec 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a34f0 04 00 69 86     _lh        t1,0x4(s3)
     6::800a34f4 0b 00 40 05     bltz       t2,LAB_OVR_226__800a3524
     6::800a34f8 00 00 83 86     _lh        v1,0x0(s4)
     6::800a34fc 02 00 88 86     lh         t0,0x2(s4)
     6::800a3500 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a3504 04 00 89 86     _lh        t1,0x4(s4)
     6::800a3508 06 00 40 05     bltz       t2,LAB_OVR_226__800a3524
     6::800a350c 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a3510 02 00 a8 86     lh         t0,0x2(s5)
     6::800a3514 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a3518 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a351c 58 00 3f 8c     lw         ra,0x58(at)
     6::800a3520 01 fe 41 05     bgez       t2,LAB_OVR_226__800a2d28
                             LAB_OVR_226__800a3524                           XREF[2]:     OVR_226::800a34f4(j), 
                                                                                          OVR_226::800a3508(j)  
     6::800a3524 10 00 2f 8c     lw         t7,0x10(at)
     6::800a3528 00 80 03 3c     lui        v1,0x8000
     6::800a352c a6 01 28 84     lh         t0,0x1a6(at)
     6::800a3530 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a3534 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a3538 00 00 e3 ad     sw         v1=>DAT_80000000,0x0(t7)                         = ??
     6::800a353c 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a3540 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a3544 21 68 60 02     move       t5,s3
     6::800a3548 a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a354c 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a3550 21 68 80 02     move       t5,s4
     6::800a3554 a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a3558 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a355c 21 68 a0 02     move       t5,s5
     6::800a3560 a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a3564 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a3568 58 00 3f 8c     lw         ra,0x58(at)
     6::800a356c 30 00 ef 25     addiu      t7,t7,0x30
     6::800a3570 08 00 e0 03     jr         ra
     6::800a3574 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_226__800a3578                           XREF[1]:     OVR_226::800a341c(j)  
     6::800a3578 58 00 3f ac     sw         ra,0x58(at)
     6::800a357c 98 01 2f 84     lh         t7,0x198(at)
     6::800a3580 9a 01 30 84     lh         s0,0x19a(at)
     6::800a3584 9c 01 31 84     lh         s1,0x19c(at)
     6::800a3588 00 00 63 86     lh         v1,0x0(s3)
     6::800a358c 02 00 68 86     lh         t0,0x2(s3)
     6::800a3590 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a3594 04 00 69 86     _lh        t1,0x4(s3)
     6::800a3598 10 00 40 05     bltz       t2,LAB_OVR_226__800a35dc
     6::800a359c 00 00 83 86     _lh        v1,0x0(s4)
     6::800a35a0 02 00 88 86     lh         t0,0x2(s4)
     6::800a35a4 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a35a8 04 00 89 86     _lh        t1,0x4(s4)
     6::800a35ac 0b 00 40 05     bltz       t2,LAB_OVR_226__800a35dc
     6::800a35b0 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a35b4 02 00 a8 86     lh         t0,0x2(s5)
     6::800a35b8 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a35bc 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a35c0 06 00 40 05     bltz       t2,LAB_OVR_226__800a35dc
     6::800a35c4 00 00 c3 86     _lh        v1,0x0(s6)
     6::800a35c8 02 00 c8 86     lh         t0,0x2(s6)
     6::800a35cc 90 8d 02 0c     jal        FUN_OVR_226__800a3640                            undefined FUN_OVR_226__800a3640()
     6::800a35d0 04 00 c9 86     _lh        t1,0x4(s6)
     6::800a35d4 58 00 3f 8c     lw         ra,0x58(at)
     6::800a35d8 d3 fd 41 05     bgez       t2,LAB_OVR_226__800a2d28
                             LAB_OVR_226__800a35dc                           XREF[3]:     OVR_226::800a3598(j), 
                                                                                          OVR_226::800a35ac(j), 
                                                                                          OVR_226::800a35c0(j)  
     6::800a35dc 10 00 2f 8c     lw         t7,0x10(at)
     6::800a35e0 00 80 03 3c     lui        v1,0x8000
     6::800a35e4 01 00 63 34     ori        v1,v1,0x1
     6::800a35e8 a6 01 28 84     lh         t0,0x1a6(at)
     6::800a35ec a2 01 29 84     lh         t1,0x1a2(at)
     6::800a35f0 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a35f4 00 00 e3 ad     sw         v1=>DAT_80000000+1,0x0(t7)
     6::800a35f8 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a35fc 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a3600 21 68 60 02     move       t5,s3
     6::800a3604 a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a3608 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a360c 21 68 80 02     move       t5,s4
     6::800a3610 a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a3614 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a3618 21 68 a0 02     move       t5,s5
     6::800a361c a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a3620 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a3624 21 68 c0 02     move       t5,s6
     6::800a3628 a0 8d 02 0c     jal        FUN_OVR_226__800a3680                            undefined FUN_OVR_226__800a3680()
     6::800a362c 30 00 f0 25     _addiu     s0,t7,0x30
     6::800a3630 58 00 3f 8c     lw         ra,0x58(at)
     6::800a3634 3c 00 ef 25     addiu      t7,t7,0x3c
     6::800a3638 08 00 e0 03     jr         ra
     6::800a363c 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a3640()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a3640                           XREF[7]:     OVR_226::800a34ec(c), 
                                                                                          OVR_226::800a3500(c), 
                                                                                          OVR_226::800a3514(c), 
                                                                                          OVR_226::800a3590(c), 
                                                                                          OVR_226::800a35a4(c), 
                                                                                          OVR_226::800a35b8(c), 
                                                                                          OVR_226::800a35cc(c)  
     6::800a3640 23 18 6f 00     subu       v1,v1,t7
     6::800a3644 02 00 61 04     bgez       v1,LAB_OVR_226__800a3650
     6::800a3648 23 40 10 01     _subu      t0,t0,s0
     6::800a364c 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_226__800a3650                           XREF[1]:     OVR_226::800a3644(j)  
     6::800a3650 00 ff 6b 24     addiu      t3,v1,-0x100
     6::800a3654 02 00 01 05     bgez       t0,LAB_OVR_226__800a3660
     6::800a3658 23 48 31 01     _subu      t1,t1,s1
     6::800a365c 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_226__800a3660                           XREF[1]:     OVR_226::800a3654(j)  
     6::800a3660 80 fe 0c 25     addiu      t4,t0,-0x180
     6::800a3664 02 00 21 05     bgez       t1,LAB_OVR_226__800a3670
     6::800a3668 00 00 00 00     _nop
     6::800a366c 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_226__800a3670                           XREF[1]:     OVR_226::800a3664(j)  
     6::800a3670 00 ff 2d 25     addiu      t5,t1,-0x100
     6::800a3674 24 58 6c 01     and        t3,t3,t4
     6::800a3678 08 00 e0 03     jr         ra
     6::800a367c 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a3680()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a3680                           XREF[7]:     OVR_226::800a3548(c), 
                                                                                          OVR_226::800a3554(c), 
                                                                                          OVR_226::800a3560(c), 
                                                                                          OVR_226::800a3604(c), 
                                                                                          OVR_226::800a3610(c), 
                                                                                          OVR_226::800a361c(c), 
                                                                                          OVR_226::800a3628(c)  
     6::800a3680 13 00 a3 81     lb         v1,0x13(t5)
     6::800a3684 00 00 a8 8d     lw         t0,0x0(t5)
     6::800a3688 04 00 a9 8d     lw         t1,0x4(t5)
     6::800a368c 08 00 aa 8d     lw         t2,0x8(t5)
     6::800a3690 00 1e 03 00     sll        v1,v1,0x18
     6::800a3694 25 50 43 01     or         t2,t2,v1
     6::800a3698 00 00 08 ae     sw         t0,0x0(s0)
     6::800a369c 04 00 09 ae     sw         t1,0x4(s0)
     6::800a36a0 08 00 e0 03     jr         ra
     6::800a36a4 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_226__800a36a8                           XREF[1]:     OVR_226::800ab454(*)  
     6::800a36a8 09 80 08 3c     lui        t0,0x8009
     6::800a36ac 04 64 08 25     addiu      t0,t0,0x6404
     6::800a36b0 64 00 28 ac     sw         t0=>DAT_80096404,0x64(at)                        = ??
     6::800a36b4 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_226__800a36b8                           XREF[1]:     OVR_226::800a3990(j)  
     6::800a36b8 bd 00 80 10     beq        a0,zero,LAB_OVR_226__800a39b0
     6::800a36bc 00 00 00 00     _nop
     6::800a36c0 1c 00 78 8c     lw         t8,0x1c(v1)
     6::800a36c4 18 00 79 8c     lw         t9,0x18(v1)
     6::800a36c8 c8 00 2a 8c     lw         t2,0xc8(at)
     6::800a36cc 3c 00 08 97     lhu        t0,0x3c(t8)
     6::800a36d0 68 00 39 ac     sw         t9,0x68(at)
     6::800a36d4 c2 48 08 00     srl        t1,t0,0x3
     6::800a36d8 fc 01 29 31     andi       t1,t1,0x1fc
     6::800a36dc 21 48 2a 01     addu       t1,t1,t2
     6::800a36e0 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a36e4 00 00 29 8d     lw         t1,0x0(t1)
     6::800a36e8 1f 00 08 31     andi       t0,t0,0x1f
     6::800a36ec bc 00 28 ac     sw         t0,0xbc(at)
     6::800a36f0 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_226__800a36f4                           XREF[1]:     OVR_226::800a3984(j)  
     6::800a36f4 30 00 23 8c     lw         v1,0x30(at)
     6::800a36f8 40 10 48 24     addiu      t0,v0,0x1040
     6::800a36fc 23 18 68 00     subu       v1,v1,t0
     6::800a3700 ec f5 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a3704 bc 00 23 8c     _lw        v1,0xbc(at)
     6::800a3708 c4 00 28 8c     lw         t0,0xc4(at)
     6::800a370c 06 00 61 04     bgez       v1,LAB_OVR_226__800a3728
     6::800a3710 c0 00 29 8c     _lw        t1,0xc0(at)
     6::800a3714 1f 00 03 24     li         v1,0x1f
     6::800a3718 04 00 28 8d     lw         t0,0x4(t1)
     6::800a371c 04 00 29 25     addiu      t1,t1,0x4
     6::800a3720 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a3724 c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_226__800a3728                           XREF[1]:     OVR_226::800a370c(j)  
     6::800a3728 04 40 68 00     sllv       t0,t0,v1
     6::800a372c ff ff 63 24     addiu      v1,v1,-0x1
     6::800a3730 91 00 01 05     bgez       t0,LAB_OVR_226__800a3978
     6::800a3734 bc 00 23 ac     _sw        v1,0xbc(at)
     6::800a3738 b4 01 3e 24     addiu      s8,at,0x1b4
     6::800a373c b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a3740 00 00 14 8f     lw         s4,0x0(t8)
     6::800a3744 04 00 16 8f     lw         s6,0x4(t8)
     6::800a3748 ff ff 93 32     andi       s3,s4,0xffff
     6::800a374c 00 99 13 00     sll        s3,s3,0x4
     6::800a3750 21 98 77 02     addu       s3,s3,s7
     6::800a3754 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a375c 02 a4 14 00     srl        s4,s4,0x10
     6::800a3760 00 a1 14 00     sll        s4,s4,0x4
     6::800a3764 21 a0 97 02     addu       s4,s4,s7
     6::800a3768 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a3770 ff ff d5 32     andi       s5,s6,0xffff
     6::800a3774 00 a9 15 00     sll        s5,s5,0x4
     6::800a3778 21 a8 b7 02     addu       s5,s5,s7
     6::800a377c 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a3784 02 b4 16 00     srl        s6,s6,0x10
     6::800a3788 00 b1 16 00     sll        s6,s6,0x4
     6::800a378c 30 00 28 4a     RTPT
     6::800a3790 21 b0 d7 02     addu       s6,s6,s7
     6::800a3794 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a3798 08 00 90 8e     lw         s0,0x8(s4)
     6::800a379c 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a37a0 08 00 cf af     sw         t7,0x8(s8)
     6::800a37a4 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a37a8 30 00 d1 af     sw         s1,0x30(s8)
     6::800a37ac 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a37b0 00 f8 43 48     gte_stFLAG v1
     6::800a37b4 10 00 d1 eb     gte_stSZ1  0x10(s8)
     6::800a37b8 80 1b 03 00     sll        v1,v1,0xe
     6::800a37bc c2 1f 03 00     srl        v1,v1,0x1f
     6::800a37c0 75 00 60 14     bne        v1,zero,LAB_OVR_226__800a3998
     6::800a37c4 08 00 14 8f     _lw        s4,0x8(t8)
     6::800a37c8 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a37cc 24 00 d2 eb     gte_stSZ2  0x24(s8)
     6::800a37d0 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a37d4 38 00 d3 eb     gte_stSZ3  0x38(s8)
     6::800a37d8 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a37dc 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a37e0 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a37e4 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a37e8 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a37ec 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a37f0 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a37f8 ff ff 93 32     andi       s3,s4,0xffff
     6::800a37fc 00 99 13 00     sll        s3,s3,0x4
     6::800a3800 21 98 77 02     addu       s3,s3,s7
     6::800a3804 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a380c 02 a4 14 00     srl        s4,s4,0x10
     6::800a3810 00 a1 14 00     sll        s4,s4,0x4
     6::800a3814 21 a0 97 02     addu       s4,s4,s7
     6::800a3818 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a3820 21 c8 20 00     move       t9,at
     6::800a3824 00 00 00 00     nop
     6::800a3828 30 00 28 4a     RTPT
     6::800a382c 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a3830 08 00 70 8e     lw         s0,0x8(s3)
     6::800a3834 08 00 91 8e     lw         s1,0x8(s4)
     6::800a3838 44 00 cf af     sw         t7,0x44(s8)
     6::800a383c 58 00 d0 af     sw         s0,0x58(s8)
     6::800a3840 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a3844 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a3848 00 f8 43 48     gte_stFLAG v1
     6::800a384c 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     6::800a3850 80 1b 03 00     sll        v1,v1,0xe
     6::800a3854 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a3858 4f 00 60 14     bne        v1,zero,LAB_OVR_226__800a3998
     6::800a385c 0c 00 14 8f     _lw        s4,0xc(t8)
     6::800a3860 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a3864 60 00 d2 eb     gte_stSZ2  0x60(s8)
     6::800a3868 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a386c 74 00 d3 eb     gte_stSZ3  0x74(s8)
     6::800a3870 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a3874 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a3878 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a387c 10 00 15 97     lhu        s5,0x10(t8)
     6::800a3880 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a3884 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a3888 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a388c ff ff 93 32     andi       s3,s4,0xffff
     6::800a3890 00 99 13 00     sll        s3,s3,0x4
     6::800a3894 21 98 77 02     addu       s3,s3,s7
     6::800a3898 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a38a0 02 a4 14 00     srl        s4,s4,0x10
     6::800a38a4 00 a1 14 00     sll        s4,s4,0x4
     6::800a38a8 21 a0 97 02     addu       s4,s4,s7
     6::800a38ac 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a38b4 14 00 09 8f     lw         t1,0x14(t8)
     6::800a38b8 00 a9 15 00     sll        s5,s5,0x4
     6::800a38bc 21 a8 b7 02     addu       s5,s5,s7
     6::800a38c0 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a38c8 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a38cc 08 00 08 24     li         t0,0x8
     6::800a38d0 30 00 28 4a     RTPT
     6::800a38d4 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a38d8 08 00 90 8e     lw         s0,0x8(s4)
     6::800a38dc 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a38e0 80 00 cf af     sw         t7,0x80(s8)
     6::800a38e4 94 00 d0 af     sw         s0,0x94(s8)
     6::800a38e8 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a38ec 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a38f0 00 f8 43 48     gte_stFLAG v1
     6::800a38f4 88 00 d1 eb     gte_stSZ1  0x88(s8)
     6::800a38f8 80 1b 03 00     sll        v1,v1,0xe
     6::800a38fc c2 1f 03 00     srl        v1,v1,0x1f
     6::800a3900 25 00 60 14     bne        v1,zero,LAB_OVR_226__800a3998
     6::800a3904 98 00 cd eb     _gte_stS   0x98(s8)
     6::800a3908 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     6::800a390c ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a3910 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     6::800a3914 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a3918 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a391c 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a3920 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a3924 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a3928 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a392c 50 00 03 3c     lui        v1,0x50
     6::800a3930 78 64 63 34     ori        v1,v1,0x6478
     6::800a3934 1c 8f 02 0c     jal        FUN_OVR_226__800a3c70                            undefined FUN_OVR_226__800a3c70()
     6::800a3938 00 00 0a 24     _li        t2,0x0
     6::800a393c 14 50 03 3c     lui        v1,0x5014
     6::800a3940 8c 78 63 34     ori        v1,v1,0x788c
     6::800a3944 0d 00 08 24     li         t0,0xd
     6::800a3948 1c 8f 02 0c     jal        FUN_OVR_226__800a3c70                            undefined FUN_OVR_226__800a3c70()
     6::800a394c 04 00 0a 24     _li        t2,0x4
     6::800a3950 78 64 03 3c     lui        v1,0x6478
     6::800a3954 a0 28 63 34     ori        v1,v1,0x28a0
     6::800a3958 12 00 08 24     li         t0,0x12
     6::800a395c 1c 8f 02 0c     jal        FUN_OVR_226__800a3c70                            undefined FUN_OVR_226__800a3c70()
     6::800a3960 08 00 0a 24     _li        t2,0x8
     6::800a3964 8c 78 03 3c     lui        v1,0x788c
     6::800a3968 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a396c 17 00 08 24     li         t0,0x17
     6::800a3970 1c 8f 02 0c     jal        FUN_OVR_226__800a3c70                            undefined FUN_OVR_226__800a3c70()
     6::800a3974 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a3978                           XREF[2]:     OVR_226::800a3730(j), 
                                                                                          OVR_226::800a39a8(j)  
     6::800a3978 68 00 39 8c     lw         t9,0x68(at)
     6::800a397c 5c 00 18 27     addiu      t8,t8,0x5c
     6::800a3980 ff ff 39 27     addiu      t9,t9,-0x1
     6::800a3984 5b ff 20 1f     bgtz       t9,LAB_OVR_226__800a36f4
     6::800a3988 68 00 39 ac     _sw        t9,0x68(at)
     6::800a398c 00 00 84 8c     lw         a0,0x0(a0)
     6::800a3990 49 ff 01 04     bgez       zero,LAB_OVR_226__800a36b8
     6::800a3994 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_226__800a3998                           XREF[3]:     OVR_226::800a37c0(j), 
                                                                                          OVR_226::800a3858(j), 
                                                                                          OVR_226::800a3900(j)  
     6::800a3998 64 00 28 8c     lw         t0,0x64(at)
     6::800a399c 00 00 00 00     nop
     6::800a39a0 00 00 18 ad     sw         t8,0x0(t0)
     6::800a39a4 04 00 08 25     addiu      t0,t0,0x4
     6::800a39a8 f3 ff 01 04     bgez       zero,LAB_OVR_226__800a3978
     6::800a39ac 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_226__800a39b0                           XREF[1]:     OVR_226::800a36b8(j)  
     6::800a39b0 64 00 28 8c     lw         t0,0x64(at)
     6::800a39b4 34 f5 01 04     bgez       zero,LAB_OVR_226__800a0e88
     6::800a39b8 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_226__800a39bc                           XREF[6]:     FUN_OVR_226__800a3b90:800a3c04(j
                                                                                          FUN_OVR_226__800a3b90:800a3c0c(j
                                                                                          FUN_OVR_226__800a3b90:800a3c40(j
                                                                                          OVR_226::800a3d44(j), 
                                                                                          OVR_226::800a3d4c(j), 
                                                                                          OVR_226::800a3d78(j)  
     6::800a39bc 08 00 e0 03     jr         ra
     6::800a39c0 00 00 00 00     _nop
                             LAB_OVR_226__800a39c4                           XREF[3]:     OVR_226::800ab60c(*), 
                                                                                          OVR_226::800ab610(*), 
                                                                                          OVR_226::800ab614(*)  
     6::800a39c4 00 00 d3 27     addiu      s3,s8,0x0
     6::800a39c8 50 00 d4 27     addiu      s4,s8,0x50
     6::800a39cc 28 00 d5 27     addiu      s5,s8,0x28
     6::800a39d0 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a39d4 e4 8e 02 0c     jal        FUN_OVR_226__800a3b90                            undefined FUN_OVR_226__800a3b90()
     6::800a39d8 0c 00 0a 24     _li        t2,0xc
     6::800a39dc 14 00 d3 27     addiu      s3,s8,0x14
     6::800a39e0 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a39e4 50 00 d5 27     addiu      s5,s8,0x50
     6::800a39e8 28 00 d6 27     addiu      s6,s8,0x28
     6::800a39ec 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a39f0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a39f4 66 00 01 04     bgez       zero,FUN_OVR_226__800a3b90
     6::800a39f8 04 00 0a 24     _li        t2,0x4
     6::800a39fc 14 00 d3 27     addiu      s3,s8,0x14
     6::800a3a00 a0 00 d4 27     addiu      s4,s8,0xa0
     6::800a3a04 00 00 d5 27     addiu      s5,s8,0x0
     6::800a3a08 28 00 d6 27     addiu      s6,s8,0x28
     6::800a3a0c e4 8e 02 0c     jal        FUN_OVR_226__800a3b90                            undefined FUN_OVR_226__800a3b90()
     6::800a3a10 0c 00 0a 24     _li        t2,0xc
     6::800a3a14 00 00 d3 27     addiu      s3,s8,0x0
     6::800a3a18 14 00 d4 27     addiu      s4,s8,0x14
     6::800a3a1c a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a3a20 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a3a24 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a3a28 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a3a2c 58 00 01 04     bgez       zero,FUN_OVR_226__800a3b90
     6::800a3a30 08 00 0a 24     _li        t2,0x8
     6::800a3a34 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a3a38 00 00 d3 27     addiu      s3,s8,0x0
     6::800a3a3c 50 00 d4 27     addiu      s4,s8,0x50
     6::800a3a40 28 00 d5 27     addiu      s5,s8,0x28
     6::800a3a44 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a3a48 e4 8e 02 0c     jal        FUN_OVR_226__800a3b90                            undefined FUN_OVR_226__800a3b90()
     6::800a3a4c 0c 00 0a 24     _li        t2,0xc
     6::800a3a50 0c 00 03 24     li         v1,0xc
     6::800a3a54 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a3a58 50 00 d3 27     addiu      s3,s8,0x50
     6::800a3a5c 14 00 d4 27     addiu      s4,s8,0x14
     6::800a3a60 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a3a64 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a3a68 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a3a6c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a3a70 47 00 01 04     bgez       zero,FUN_OVR_226__800a3b90
     6::800a3a74 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a3a78()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a3a78                           XREF[2]:     FUN_OVR_226__800a3c70:800a3f08(c
                                                                                          FUN_OVR_226__800a3c70:800a3f20(c
     6::800a3a78 00 00 ab 85     lh         t3,0x0(t5)
     6::800a3a7c 00 00 cc 85     lh         t4,0x0(t6)
     6::800a3a80 00 00 eb a5     sh         t3,0x0(t7)
     6::800a3a84 00 00 0c a6     sh         t4,0x0(s0)
     6::800a3a88 21 18 6c 01     addu       v1,t3,t4
     6::800a3a8c 43 18 03 00     sra        v1,v1,0x1
     6::800a3a90 00 00 43 a6     sh         v1,0x0(s2)
     6::800a3a94 02 00 ab 85     lh         t3,0x2(t5)
     6::800a3a98 02 00 cc 85     lh         t4,0x2(t6)
     6::800a3a9c 02 00 eb a5     sh         t3,0x2(t7)
     6::800a3aa0 02 00 0c a6     sh         t4,0x2(s0)
     6::800a3aa4 21 18 6c 01     addu       v1,t3,t4
     6::800a3aa8 43 18 03 00     sra        v1,v1,0x1
     6::800a3aac 02 00 43 a6     sh         v1,0x2(s2)
     6::800a3ab0 04 00 ab 85     lh         t3,0x4(t5)
     6::800a3ab4 04 00 cc 85     lh         t4,0x4(t6)
     6::800a3ab8 04 00 eb a5     sh         t3,0x4(t7)
     6::800a3abc 04 00 0c a6     sh         t4,0x4(s0)
     6::800a3ac0 21 18 6c 01     addu       v1,t3,t4
     6::800a3ac4 43 18 03 00     sra        v1,v1,0x1
     6::800a3ac8 00 00 40 ca     gte_ldVXY0 0x0(s2)
     6::800a3acc 00 08 83 48     gte_ldVZ0  v1
     6::800a3ad0 04 00 43 a6     sh         v1,0x4(s2)
     6::800a3ad4 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a3ad8 01 00 18 4a     RTPS
     6::800a3adc 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a3ae0 08 00 eb a1     sb         t3,0x8(t7)
     6::800a3ae4 08 00 0c a2     sb         t4,0x8(s0)
     6::800a3ae8 21 18 6c 01     addu       v1,t3,t4
     6::800a3aec 43 18 03 00     sra        v1,v1,0x1
     6::800a3af0 08 00 43 a2     sb         v1,0x8(s2)
     6::800a3af4 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a3af8 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a3afc 09 00 eb a1     sb         t3,0x9(t7)
     6::800a3b00 09 00 0c a2     sb         t4,0x9(s0)
     6::800a3b04 21 18 6c 01     addu       v1,t3,t4
     6::800a3b08 43 18 03 00     sra        v1,v1,0x1
     6::800a3b0c 09 00 43 a2     sb         v1,0x9(s2)
     6::800a3b10 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a3b14 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a3b18 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a3b1c 0a 00 0c a2     sb         t4,0xa(s0)
     6::800a3b20 21 18 6c 01     addu       v1,t3,t4
     6::800a3b24 43 18 03 00     sra        v1,v1,0x1
     6::800a3b28 0a 00 43 a2     sb         v1,0xa(s2)
     6::800a3b2c 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a3b30 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a3b34 06 00 eb a1     sb         t3,0x6(t7)
     6::800a3b38 06 00 0c a2     sb         t4,0x6(s0)
     6::800a3b3c 21 18 6c 01     addu       v1,t3,t4
     6::800a3b40 43 18 03 00     sra        v1,v1,0x1
     6::800a3b44 06 00 43 a2     sb         v1,0x6(s2)
     6::800a3b48 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a3b4c 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a3b50 07 00 eb a1     sb         t3,0x7(t7)
     6::800a3b54 07 00 0c a2     sb         t4,0x7(s0)
     6::800a3b58 21 18 6c 01     addu       v1,t3,t4
     6::800a3b5c 43 18 03 00     sra        v1,v1,0x1
     6::800a3b60 07 00 43 a2     sb         v1,0x7(s2)
     6::800a3b64 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a3b68 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a3b6c 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a3b70 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a3b74 0c 00 c3 8d     lw         v1,0xc(t6)
     6::800a3b78 10 00 c8 8d     lw         t0,0x10(t6)
     6::800a3b7c 0c 00 03 ae     sw         v1,0xc(s0)
     6::800a3b80 10 00 08 ae     sw         t0,0x10(s0)
     6::800a3b84 0c 00 4e ea     gte_stSXY2 0xc(s2)
     6::800a3b88 08 00 e0 03     jr         ra
     6::800a3b8c 10 00 53 ea     _gte_stSZ3 0x10(s2)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a3b90()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a3b90                           XREF[6]:     OVR_226::800a39d4(c), 
                                                                                          OVR_226::800a39f4(j), 
                                                                                          OVR_226::800a3a0c(c), 
                                                                                          OVR_226::800a3a2c(j), 
                                                                                          OVR_226::800a3a48(c), 
                                                                                          OVR_226::800a3a70(j)  
     6::800a3b90 70 00 2a ac     sw         t2,0x70(at)
     6::800a3b94 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a3b98 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a3b9c 94 01 2a 8c     lw         t2,0x194(at)
     6::800a3ba0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a3ba4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a3ba8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a3bac 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a3bb0 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a3bb4 06 00 40 4b     NCLIP
     6::800a3bb8 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a3bbc 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a3bc0 23 78 68 01     subu       t7,t3,t0
     6::800a3bc4 23 80 88 01     subu       s0,t4,t0
     6::800a3bc8 23 88 a8 01     subu       s1,t5,t0
     6::800a3bcc 23 90 c8 01     subu       s2,t6,t0
     6::800a3bd0 00 c0 08 48     gte_stMAC0 t0
     6::800a3bd4 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a3bd8 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a3be4
     6::800a3bdc 22 40 08 00     _sub       t0,zero,t0
     6::800a3be0 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a3be4                           XREF[1]:     OVR_226::800a3bd8(j)  
     6::800a3be4 06 00 40 4b     NCLIP
     6::800a3be8 24 18 6c 01     and        v1,t3,t4
     6::800a3bec 24 18 6d 00     and        v1,v1,t5
     6::800a3bf0 24 18 6e 00     and        v1,v1,t6
     6::800a3bf4 25 78 f0 01     or         t7,t7,s0
     6::800a3bf8 25 78 f1 01     or         t7,t7,s1
     6::800a3bfc 27 78 f2 01     nor        t7,t7,s2
     6::800a3c00 25 78 e3 01     or         t7,t7,v1
     6::800a3c04 6d ff e0 05     bltz       t7,LAB_OVR_226__800a39bc
     6::800a3c08 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a3c0c 6b ff e0 05     bltz       t7,LAB_OVR_226__800a39bc
     6::800a3c10 00 c0 03 48     _gte_stM   v1
     6::800a3c14 25 40 09 01     or         t0,t0,t1
     6::800a3c18 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a3c24
     6::800a3c1c c2 47 08 00     _srl       t0,t0,0x1f
     6::800a3c20 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a3c24                           XREF[1]:     OVR_226::800a3c18(j)  
     6::800a3c24 80 40 08 00     sll        t0,t0,0x2
     6::800a3c28 25 18 69 00     or         v1,v1,t1
     6::800a3c2c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a3c30 c0 18 03 00     sll        v1,v1,0x3
     6::800a3c34 70 00 2a 8c     lw         t2,0x70(at)
     6::800a3c38 25 18 68 00     or         v1,v1,t0
     6::800a3c3c 24 18 6a 00     and        v1,v1,t2
     6::800a3c40 5e ff 60 10     beq        v1,zero,LAB_OVR_226__800a39bc
     6::800a3c44 70 00 23 ac     _sw        v1,0x70(at)
     6::800a3c48 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a3c4c 24 03 28 24     addiu      t0,at,0x324
     6::800a3c50 c8 00 1e 11     beq        t0,s8,LAB_OVR_226__800a3f74
     6::800a3c54 04 00 39 27     _addiu     t9,t9,0x4
     6::800a3c58 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a3c5c 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a3c60 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a3c64 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a3c68 91 00 01 04     bgez       zero,LAB_OVR_226__800a3eb0
     6::800a3c6c 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a3c70()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a3c70                           XREF[4]:     OVR_226::800a3934(c), 
                                                                                          OVR_226::800a3948(c), 
                                                                                          OVR_226::800a395c(c), 
                                                                                          OVR_226::800a3970(c)  
     6::800a3c70 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a3c74 b4 00 ca af     sw         t2,0xb4(s8)
     6::800a3c78 06 50 09 01     srlv       t2,t1,t0
     6::800a3c7c 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a3c80 80 50 0a 00     sll        t2,t2,0x2
     6::800a3c84 21 50 41 01     addu       t2,t2,at
     6::800a3c88 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a3c8c 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a3c90 94 01 2a ac     sw         t2,0x194(at)
     6::800a3c94 02 9e 0a 00     srl        s3,t2,0x18
     6::800a3c98 1f 00 73 32     andi       s3,s3,0x1f
     6::800a3c9c 06 98 63 02     srlv       s3,v1,s3
     6::800a3ca0 ff 00 73 32     andi       s3,s3,0xff
     6::800a3ca4 21 98 7e 02     addu       s3,s3,s8
     6::800a3ca8 02 a4 0a 00     srl        s4,t2,0x10
     6::800a3cac 1f 00 94 32     andi       s4,s4,0x1f
     6::800a3cb0 06 a0 83 02     srlv       s4,v1,s4
     6::800a3cb4 ff 00 94 32     andi       s4,s4,0xff
     6::800a3cb8 21 a0 9e 02     addu       s4,s4,s8
     6::800a3cbc 02 aa 0a 00     srl        s5,t2,0x8
     6::800a3cc0 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a3cc4 06 a8 a3 02     srlv       s5,v1,s5
     6::800a3cc8 ff 00 b5 32     andi       s5,s5,0xff
     6::800a3ccc 21 a8 be 02     addu       s5,s5,s8
     6::800a3cd0 1f 00 56 31     andi       s6,t2,0x1f
     6::800a3cd4 06 b0 c3 02     srlv       s6,v1,s6
     6::800a3cd8 ff 00 d6 32     andi       s6,s6,0xff
     6::800a3cdc 21 b0 de 02     addu       s6,s6,s8
     6::800a3ce0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a3ce4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a3ce8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a3cec 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a3cf0 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a3cf4 06 00 40 4b     NCLIP
     6::800a3cf8 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a3cfc 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a3d00 23 78 68 01     subu       t7,t3,t0
     6::800a3d04 23 80 88 01     subu       s0,t4,t0
     6::800a3d08 23 88 a8 01     subu       s1,t5,t0
     6::800a3d0c 23 90 c8 01     subu       s2,t6,t0
     6::800a3d10 00 c0 08 48     gte_stMAC0 t0
     6::800a3d14 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a3d18 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a3d24
     6::800a3d1c 22 40 08 00     _sub       t0,zero,t0
     6::800a3d20 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a3d24                           XREF[1]:     OVR_226::800a3d18(j)  
     6::800a3d24 06 00 40 4b     NCLIP
     6::800a3d28 24 18 6c 01     and        v1,t3,t4
     6::800a3d2c 24 18 6d 00     and        v1,v1,t5
     6::800a3d30 24 18 6e 00     and        v1,v1,t6
     6::800a3d34 25 78 f0 01     or         t7,t7,s0
     6::800a3d38 25 78 f1 01     or         t7,t7,s1
     6::800a3d3c 27 78 f2 01     nor        t7,t7,s2
     6::800a3d40 25 78 e3 01     or         t7,t7,v1
     6::800a3d44 1d ff e0 05     bltz       t7,LAB_OVR_226__800a39bc
     6::800a3d48 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a3d4c 1b ff e0 05     bltz       t7,LAB_OVR_226__800a39bc
     6::800a3d50 00 c0 03 48     _gte_stM   v1
     6::800a3d54 25 40 09 01     or         t0,t0,t1
     6::800a3d58 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a3d64
     6::800a3d5c c2 47 08 00     _srl       t0,t0,0x1f
     6::800a3d60 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a3d64                           XREF[1]:     OVR_226::800a3d58(j)  
     6::800a3d64 80 40 08 00     sll        t0,t0,0x2
     6::800a3d68 25 18 69 00     or         v1,v1,t1
     6::800a3d6c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a3d70 c0 18 03 00     sll        v1,v1,0x3
     6::800a3d74 25 18 68 00     or         v1,v1,t0
     6::800a3d78 10 ff 60 10     beq        v1,zero,LAB_OVR_226__800a39bc
     6::800a3d7c 70 00 23 ac     _sw        v1,0x70(at)
     6::800a3d80 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a3d84 04 00 39 27     addiu      t9,t9,0x4
     6::800a3d88 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a3d8c 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a3d90 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a3d94 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a3d98 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a3d9c 23 50 6c 01     subu       t2,t3,t4
     6::800a3da0 82 48 03 00     srl        t1,v1,0x2
     6::800a3da4 21 48 38 01     addu       t1,t1,t8
     6::800a3da8 18 00 29 81     lb         t1,0x18(t1)
     6::800a3dac 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a3db8
     6::800a3db0 21 e0 60 01     _move      gp,t3
     6::800a3db4 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a3db8                           XREF[1]:     OVR_226::800a3dac(j)  
     6::800a3db8 23 50 8d 03     subu       t2,gp,t5
     6::800a3dbc 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a3dc8
     6::800a3dc0 21 18 78 00     _addu      v1,v1,t8
     6::800a3dc4 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a3dc8                           XREF[1]:     OVR_226::800a3dbc(j)  
     6::800a3dc8 23 50 8e 03     subu       t2,gp,t6
     6::800a3dcc 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a3dd8
     6::800a3dd0 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a3dd4 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a3dd8                           XREF[1]:     OVR_226::800a3dcc(j)  
     6::800a3dd8 21 50 80 03     move       t2,gp
     6::800a3ddc 82 e1 1c 00     srl        gp,gp,0x6
     6::800a3de0 21 e0 89 03     addu       gp,gp,t1
     6::800a3de4 01 00 69 30     andi       t1,v1,0x1
     6::800a3de8 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a3df4
     6::800a3dec 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a3df0 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a3df4                           XREF[1]:     OVR_226::800a3de8(j)  
     6::800a3df4 02 00 81 07     bgez       gp,LAB_OVR_226__800a3e00
     6::800a3df8 21 e0 85 03     _addu      gp,gp,a1
     6::800a3dfc 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a3e00                           XREF[1]:     OVR_226::800a3df4(j)  
     6::800a3e00 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a3e04 24 00 69 8c     lw         t1,0x24(v1)
     6::800a3e08 23 40 48 01     subu       t0,t2,t0
     6::800a3e0c 84 00 29 ac     sw         t1,0x84(at)
     6::800a3e10 0c 00 01 05     bgez       t0,LAB_OVR_226__800a3e44
     6::800a3e14 20 00 28 8c     _lw        t0,0x20(at)
     6::800a3e18 0c 00 63 24     addiu      v1,v1,0xc
     6::800a3e1c 23 40 48 01     subu       t0,t2,t0
     6::800a3e20 08 00 01 05     bgez       t0,LAB_OVR_226__800a3e44
     6::800a3e24 24 00 28 8c     _lw        t0,0x24(at)
     6::800a3e28 0c 00 63 24     addiu      v1,v1,0xc
     6::800a3e2c 23 40 48 01     subu       t0,t2,t0
     6::800a3e30 04 00 01 05     bgez       t0,LAB_OVR_226__800a3e44
     6::800a3e34 00 00 00 00     _nop
     6::800a3e38 02 00 20 05     bltz       t1,LAB_OVR_226__800a3e44
     6::800a3e3c 00 00 00 00     _nop
     6::800a3e40 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a3e44                           XREF[4]:     OVR_226::800a3e10(j), 
                                                                                          OVR_226::800a3e20(j), 
                                                                                          OVR_226::800a3e30(j), 
                                                                                          OVR_226::800a3e38(j)  
     6::800a3e44 94 01 2a 8c     lw         t2,0x194(at)
     6::800a3e48 00 00 68 8c     lw         t0,0x0(v1)
     6::800a3e4c 04 00 69 8c     lw         t1,0x4(v1)
     6::800a3e50 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a3e54 ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a3e58 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a3e5c 00 52 0a 00     sll        t2,t2,0x8
     6::800a3e60 0a 00 40 05     bltz       t2,LAB_OVR_226__800a3e8c
     6::800a3e64 b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a3e68 06 00 68 a6     sh         t0,0x6(s3)
     6::800a3e6c 08 00 68 8c     lw         t0,0x8(v1)
     6::800a3e70 06 00 89 a6     sh         t1,0x6(s4)
     6::800a3e74 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a3e78 00 54 0a 00     sll        t2,t2,0x10
     6::800a3e7c 0b 00 40 05     bltz       t2,LAB_OVR_226__800a3eac
     6::800a3e80 02 4c 08 00     _srl       t1,t0,0x10
     6::800a3e84 09 00 01 04     bgez       zero,LAB_OVR_226__800a3eac
     6::800a3e88 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a3e8c                           XREF[1]:     OVR_226::800a3e60(j)  
     6::800a3e8c 06 00 69 a6     sh         t1,0x6(s3)
     6::800a3e90 08 00 69 8c     lw         t1,0x8(v1)
     6::800a3e94 00 54 0a 00     sll        t2,t2,0x10
     6::800a3e98 06 00 88 a6     sh         t0,0x6(s4)
     6::800a3e9c 02 44 09 00     srl        t0,t1,0x10
     6::800a3ea0 02 00 40 05     bltz       t2,LAB_OVR_226__800a3eac
     6::800a3ea4 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a3ea8 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a3eac                           XREF[3]:     OVR_226::800a3e7c(j), 
                                                                                          OVR_226::800a3e84(j), 
                                                                                          OVR_226::800a3ea0(j)  
     6::800a3eac 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a3eb0                           XREF[1]:     FUN_OVR_226__800a3b90:800a3c68(j
     6::800a3eb0 00 00 00 00     nop
     6::800a3eb4 23 88 63 01     subu       s1,t3,v1
     6::800a3eb8 23 90 83 01     subu       s2,t4,v1
     6::800a3ebc 23 78 a3 01     subu       t7,t5,v1
     6::800a3ec0 23 80 c3 01     subu       s0,t6,v1
     6::800a3ec4 42 8f 11 00     srl        s1,s1,0x1d
     6::800a3ec8 04 00 31 32     andi       s1,s1,0x4
     6::800a3ecc 02 97 12 00     srl        s2,s2,0x1c
     6::800a3ed0 08 00 52 32     andi       s2,s2,0x8
     6::800a3ed4 25 88 32 02     or         s1,s1,s2
     6::800a3ed8 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a3edc 10 00 ef 31     andi       t7,t7,0x10
     6::800a3ee0 25 88 2f 02     or         s1,s1,t7
     6::800a3ee4 82 86 10 00     srl        s0,s0,0x1a
     6::800a3ee8 20 00 10 32     andi       s0,s0,0x20
     6::800a3eec 25 88 30 02     or         s1,s1,s0
     6::800a3ef0 19 00 20 12     beq        s1,zero,LAB_OVR_226__800a3f58
     6::800a3ef4 21 68 60 02     _move      t5,s3
     6::800a3ef8 21 70 80 02     move       t6,s4
     6::800a3efc b8 00 de 27     addiu      s8,s8,0xb8
     6::800a3f00 00 00 cf 27     addiu      t7,s8,0x0
     6::800a3f04 14 00 d0 27     addiu      s0,s8,0x14
     6::800a3f08 9e 8e 02 0c     jal        FUN_OVR_226__800a3a78                            undefined FUN_OVR_226__800a3a78()
     6::800a3f0c 50 00 d2 27     _addiu     s2,s8,0x50
     6::800a3f10 21 68 a0 02     move       t5,s5
     6::800a3f14 21 70 c0 02     move       t6,s6
     6::800a3f18 28 00 cf 27     addiu      t7,s8,0x28
     6::800a3f1c 3c 00 d0 27     addiu      s0,s8,0x3c
     6::800a3f20 9e 8e 02 0c     jal        FUN_OVR_226__800a3a78                            undefined FUN_OVR_226__800a3a78()
     6::800a3f24 a0 00 d2 27     _addiu     s2,s8,0xa0
     6::800a3f28 21 18 21 02     addu       v1,s1,at
     6::800a3f2c 48 01 63 8c     lw         v1,0x148(v1)
     6::800a3f30 0a 80 08 3c     lui        t0,0x800a
     6::800a3f34 48 3f 08 25     addiu      t0,t0,0x3f48
     6::800a3f38 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a3f3c 3c 00 28 af     sw         t0=>LAB_OVR_226__800a3f48,0x3c(t9)
     6::800a3f40 08 00 60 00     jr         v1
     6::800a3f44 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a3f48                           XREF[1]:     FUN_OVR_226__800a3c70:800a3f3c(*
     6::800a3f48 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a3f4c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a3f50 08 00 e0 03     jr         ra
     6::800a3f54 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a3f58                           XREF[1]:     OVR_226::800a3ef0(j)  
     6::800a3f58 70 00 23 8c     lw         v1,0x70(at)
     6::800a3f5c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a3f60 21 18 61 00     addu       v1,v1,at
     6::800a3f64 84 01 63 8c     lw         v1,0x184(v1)
     6::800a3f68 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a3f6c 08 00 60 00     jr         v1
     6::800a3f70 00 00 00 00     _nop
                             LAB_OVR_226__800a3f74                           XREF[1]:     OVR_226::800a3c50(j)  
     6::800a3f74 84 00 23 8c     lw         v1,0x84(at)
     6::800a3f78 24 03 2a 24     addiu      t2,at,0x324
     6::800a3f7c 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a4018
     6::800a3f80 20 03 28 8c     _lw        t0,0x320(at)
     6::800a3f84 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a3f88 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a3fe4
     6::800a3f8c 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a3f90 0a 80 0a 3c     lui        t2,0x800a
     6::800a3f94 34 3a 4a 25     addiu      t2,t2,0x3a34
     6::800a3f98 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a4018
     6::800a3f9c 94 01 23 8c     _lw        v1,0x194(at)
     6::800a3fa0 40 40 08 00     sll        t0,t0,0x1
     6::800a3fa4 00 1a 03 00     sll        v1,v1,0x8
     6::800a3fa8 02 00 61 04     bgez       v1,LAB_OVR_226__800a3fb4
     6::800a3fac 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a3fb0 30 00 08 25     addiu      t0,t0,0x30
                             LAB_OVR_226__800a3fb4                           XREF[1]:     OVR_226::800a3fa8(j)  
     6::800a3fb4 21 40 09 01     addu       t0,t0,t1
     6::800a3fb8 21 50 48 01     addu       t2,t2,t0
     6::800a3fbc 00 00 48 8d     lw         t0,0x0(t2)
     6::800a3fc0 04 00 49 8d     lw         t1,0x4(t2)
     6::800a3fc4 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a3fc8 06 00 68 a6     sh         t0,0x6(s3)
     6::800a3fcc 08 00 48 85     lh         t0,0x8(t2)
     6::800a3fd0 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a3fd4 06 00 89 a6     sh         t1,0x6(s4)
     6::800a3fd8 0a 00 49 85     lh         t1,0xa(t2)
     6::800a3fdc 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a3fe0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a3fe4                           XREF[2]:     OVR_226::800a3f88(j), 
                                                                                          OVR_226::800a4024(j)  
     6::800a3fe4 70 00 23 8c     lw         v1,0x70(at)
     6::800a3fe8 00 00 00 00     nop
     6::800a3fec 21 18 61 00     addu       v1,v1,at
     6::800a3ff0 84 01 63 8c     lw         v1,0x184(v1)
     6::800a3ff4 00 00 00 00     nop
     6::800a3ff8 09 f8 60 00     jalr       v1
     6::800a3ffc fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a4000 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a4004 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a4008 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a400c a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a4010 08 00 e0 03     jr         ra
     6::800a4014 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a4018                           XREF[2]:     OVR_226::800a3f7c(j), 
                                                                                          OVR_226::800a3f98(j)  
     6::800a4018 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a401c b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a4020 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a4024 ef ff 01 04     bgez       zero,LAB_OVR_226__800a3fe4
     6::800a4028 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a402c 21 98 80 02     move       s3,s4
     6::800a4030 21 a0 c0 02     move       s4,s6
     6::800a4034 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a4038 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a403c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a4040 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a4044 08 00 90 8e     lw         s0,0x8(s4)
     6::800a4048 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a404c 06 00 73 86     lh         s3,0x6(s3)
     6::800a4050 06 00 94 86     lh         s4,0x6(s4)
     6::800a4054 06 00 b5 86     lh         s5,0x6(s5)
     6::800a4058 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a405c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a4060 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a4064 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a4068 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a406c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a4070 60 00 03 3c     lui        v1,0x60
     6::800a4074 24 48 83 02     and        t1,s4,v1
     6::800a4078 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a4084
     6::800a407c 00 36 03 3c     _lui       v1,0x3600
     6::800a4080 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a4084                           XREF[1]:     OVR_226::800a4078(j)  
     6::800a4084 25 18 6f 00     or         v1,v1,t7
     6::800a4088 04 00 43 ac     sw         v1,0x4(v0)
     6::800a408c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a4090 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a4094 10 00 50 ac     sw         s0,0x10(v0)
     6::800a4098 14 00 4c ac     sw         t4,0x14(v0)
     6::800a409c 18 00 54 ac     sw         s4,0x18(v0)
     6::800a40a0 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a40a4 20 00 4d ac     sw         t5,0x20(v0)
     6::800a40a8 24 00 55 ac     sw         s5,0x24(v0)
     6::800a40ac 28 00 09 24     li         t1,0x28
     6::800a40b0 29 00 01 04     bgez       zero,LAB_OVR_226__800a4158
     6::800a40b4 00 09 0a 3c     _lui       t2,0x900
     6::800a40b8 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a40bc 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a40c0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a40c4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a40c8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a40cc 08 00 90 8e     lw         s0,0x8(s4)
     6::800a40d0 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a40d4 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a40d8 06 00 73 86     lh         s3,0x6(s3)
     6::800a40dc 06 00 94 86     lh         s4,0x6(s4)
     6::800a40e0 06 00 b5 86     lh         s5,0x6(s5)
     6::800a40e4 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a40e8 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a40ec 06 00 d4 86     lh         s4,0x6(s6)
     6::800a40f0 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a40f4 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a40f8 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a40fc a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a4100 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a4104 60 00 03 3c     lui        v1,0x60
     6::800a4108 24 48 83 02     and        t1,s4,v1
     6::800a410c 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a4118
     6::800a4110 00 3e 03 3c     _lui       v1,0x3e00
     6::800a4114 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a4118                           XREF[1]:     OVR_226::800a410c(j)  
     6::800a4118 25 18 6f 00     or         v1,v1,t7
     6::800a411c 04 00 43 ac     sw         v1,0x4(v0)
     6::800a4120 08 00 4b ac     sw         t3,0x8(v0)
     6::800a4124 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a4128 10 00 50 ac     sw         s0,0x10(v0)
     6::800a412c 14 00 4c ac     sw         t4,0x14(v0)
     6::800a4130 18 00 54 ac     sw         s4,0x18(v0)
     6::800a4134 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a4138 20 00 4d ac     sw         t5,0x20(v0)
     6::800a413c 24 00 55 ac     sw         s5,0x24(v0)
     6::800a4140 28 00 52 ac     sw         s2,0x28(v0)
     6::800a4144 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a4148 02 1c 15 00     srl        v1,s5,0x10
     6::800a414c 30 00 43 ac     sw         v1,0x30(v0)
     6::800a4150 34 00 09 24     li         t1,0x34
     6::800a4154 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a4158                           XREF[1]:     OVR_226::800a40b0(j)  
     6::800a4158 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a415c 00 42 02 00     sll        t0,v0,0x8
     6::800a4160 02 42 08 00     srl        t0,t0,0x8
     6::800a4164 25 18 6a 00     or         v1,v1,t2
     6::800a4168 00 00 43 ac     sw         v1,0x0(v0)
     6::800a416c 21 10 49 00     addu       v0,v0,t1
     6::800a4170 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a4174 08 00 e0 03     jr         ra
     6::800a4178 01 00 bd 23     _addi      sp,sp,0x1
                             
							 
							 LAB_OVR_226__800a417c                           XREF[1]:     OVR_226::800ab450(*)  
     6::800a417c 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_226__800a4180                           XREF[1]:     OVR_226::800a44d0(j)  
     6::800a4180 30 00 23 8c     lw         v1,0x30(at)
     6::800a4184 40 10 48 24     addiu      t0,v0,0x1040
     6::800a4188 23 18 68 00     subu       v1,v1,t0
     6::800a418c 49 f3 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a4190 b4 01 3e 24     _addiu     s8,at,0x1b4
     6::800a4194 3c f3 00 13     beq        t8,zero,LAB_OVR_226__800a0e88
     6::800a4198 b4 00 c0 af     _sw        zero,0xb4(s8)
     6::800a419c 00 00 14 8f     lw         s4,0x0(t8)
     6::800a41a0 04 00 16 8f     lw         s6,0x4(t8)
     6::800a41a4 ff ff 93 32     andi       s3,s4,0xffff
     6::800a41a8 00 99 13 00     sll        s3,s3,0x4
     6::800a41ac 21 98 77 02     addu       s3,s3,s7
     6::800a41b0 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a41b8 02 a4 14 00     srl        s4,s4,0x10
     6::800a41bc 00 a1 14 00     sll        s4,s4,0x4
     6::800a41c0 21 a0 97 02     addu       s4,s4,s7
     6::800a41c4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a41cc ff ff d5 32     andi       s5,s6,0xffff
     6::800a41d0 00 a9 15 00     sll        s5,s5,0x4
     6::800a41d4 21 a8 b7 02     addu       s5,s5,s7
     6::800a41d8 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a41e0 02 b4 16 00     srl        s6,s6,0x10
     6::800a41e4 00 b1 16 00     sll        s6,s6,0x4
     6::800a41e8 30 00 28 4a     RTPT
     6::800a41ec 21 b0 d7 02     addu       s6,s6,s7
     6::800a41f0 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a41f4 08 00 90 8e     lw         s0,0x8(s4)
     6::800a41f8 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a41fc 08 00 cf af     sw         t7,0x8(s8)
     6::800a4200 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a4204 30 00 d1 af     sw         s1,0x30(s8)
     6::800a4208 08 00 14 8f     lw         s4,0x8(t8)
     6::800a420c 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a4210 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a4214 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a4218 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a421c 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a4220 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a4224 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a4228 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a422c 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a4230 5c 00 2a 8c     lw         t2,0x5c(at)
     6::800a4234 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a4240 10 00 c3 a7     sh         v1,0x10(s8)
     6::800a4244 24 00 c8 a7     sh         t0,0x24(s8)
     6::800a4248 38 00 c9 a7     sh         t1,0x38(s8)
     6::800a424c 23 58 6a 00     subu       t3,v1,t2
     6::800a4250 23 60 0a 01     subu       t4,t0,t2
     6::800a4254 23 68 2a 01     subu       t5,t1,t2
     6::800a4258 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a425c c2 67 0c 00     srl        t4,t4,0x1f
     6::800a4260 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a4264 12 00 cb a3     sb         t3,0x12(s8)
     6::800a4268 26 00 cc a3     sb         t4,0x26(s8)
     6::800a426c 3a 00 cd a3     sb         t5,0x3a(s8)
     6::800a4270 40 18 03 00     sll        v1,v1,0x1
     6::800a4274 40 40 08 00     sll        t0,t0,0x1
     6::800a4278 40 48 09 00     sll        t1,t1,0x1
     6::800a427c 23 58 6a 00     subu       t3,v1,t2
     6::800a4280 23 60 0a 01     subu       t4,t0,t2
     6::800a4284 23 68 2a 01     subu       t5,t1,t2
     6::800a4288 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a428c c2 67 0c 00     srl        t4,t4,0x1f
     6::800a4290 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a4294 13 00 cb a3     sb         t3,0x13(s8)
     6::800a4298 27 00 cc a3     sb         t4,0x27(s8)
     6::800a429c 3b 00 cd a3     sb         t5,0x3b(s8)
     6::800a42a0 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a42a8 ff ff 93 32     andi       s3,s4,0xffff
     6::800a42ac 00 99 13 00     sll        s3,s3,0x4
     6::800a42b0 21 98 77 02     addu       s3,s3,s7
     6::800a42b4 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a42bc 02 a4 14 00     srl        s4,s4,0x10
     6::800a42c0 00 a1 14 00     sll        s4,s4,0x4
     6::800a42c4 21 a0 97 02     addu       s4,s4,s7
     6::800a42c8 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a42d0 21 c8 20 00     move       t9,at
     6::800a42d4 00 00 00 00     nop
     6::800a42d8 30 00 28 4a     RTPT
     6::800a42dc 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a42e0 08 00 70 8e     lw         s0,0x8(s3)
     6::800a42e4 08 00 91 8e     lw         s1,0x8(s4)
     6::800a42e8 44 00 cf af     sw         t7,0x44(s8)
     6::800a42ec 58 00 d0 af     sw         s0,0x58(s8)
     6::800a42f0 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a42f4 0c 00 14 8f     lw         s4,0xc(t8)
     6::800a42f8 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a42fc 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a4300 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a4304 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a4308 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a430c 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a4310 10 00 15 97     lhu        s5,0x10(t8)
     6::800a4314 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a4318 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a431c 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a4320 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a432c 4c 00 c3 a7     sh         v1,0x4c(s8)
     6::800a4330 60 00 c8 a7     sh         t0,0x60(s8)
     6::800a4334 74 00 c9 a7     sh         t1,0x74(s8)
     6::800a4338 23 58 6a 00     subu       t3,v1,t2
     6::800a433c 23 60 0a 01     subu       t4,t0,t2
     6::800a4340 23 68 2a 01     subu       t5,t1,t2
     6::800a4344 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a4348 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a434c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a4350 4e 00 cb a3     sb         t3,0x4e(s8)
     6::800a4354 62 00 cc a3     sb         t4,0x62(s8)
     6::800a4358 76 00 cd a3     sb         t5,0x76(s8)
     6::800a435c 40 18 03 00     sll        v1,v1,0x1
     6::800a4360 40 40 08 00     sll        t0,t0,0x1
     6::800a4364 40 48 09 00     sll        t1,t1,0x1
     6::800a4368 23 58 6a 00     subu       t3,v1,t2
     6::800a436c 23 60 0a 01     subu       t4,t0,t2
     6::800a4370 23 68 2a 01     subu       t5,t1,t2
     6::800a4374 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a4378 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a437c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a4380 4f 00 cb a3     sb         t3,0x4f(s8)
     6::800a4384 63 00 cc a3     sb         t4,0x63(s8)
     6::800a4388 77 00 cd a3     sb         t5,0x77(s8)
     6::800a438c ff ff 93 32     andi       s3,s4,0xffff
     6::800a4390 00 99 13 00     sll        s3,s3,0x4
     6::800a4394 21 98 77 02     addu       s3,s3,s7
     6::800a4398 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a43a0 02 a4 14 00     srl        s4,s4,0x10
     6::800a43a4 00 a1 14 00     sll        s4,s4,0x4
     6::800a43a8 21 a0 97 02     addu       s4,s4,s7
     6::800a43ac 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a43b4 14 00 09 8f     lw         t1,0x14(t8)
     6::800a43b8 00 a9 15 00     sll        s5,s5,0x4
     6::800a43bc 21 a8 b7 02     addu       s5,s5,s7
     6::800a43c0 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a43c8 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a43cc 00 00 00 00     nop
     6::800a43d0 30 00 28 4a     RTPT
     6::800a43d4 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a43d8 08 00 90 8e     lw         s0,0x8(s4)
     6::800a43dc 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a43e0 80 00 cf af     sw         t7,0x80(s8)
     6::800a43e4 94 00 d0 af     sw         s0,0x94(s8)
     6::800a43e8 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a43ec 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a43f0 98 00 cd eb     gte_stSXY1 0x98(s8)
     6::800a43f4 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a43f8 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a43fc 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a4400 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a4404 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a4408 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a440c a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a4410 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a441c 88 00 c3 a7     sh         v1,0x88(s8)
     6::800a4420 9c 00 c8 a7     sh         t0,0x9c(s8)
     6::800a4424 b0 00 c9 a7     sh         t1,0xb0(s8)
     6::800a4428 23 58 6a 00     subu       t3,v1,t2
     6::800a442c 23 60 0a 01     subu       t4,t0,t2
     6::800a4430 23 68 2a 01     subu       t5,t1,t2
     6::800a4434 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a4438 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a443c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a4440 8a 00 cb a3     sb         t3,0x8a(s8)
     6::800a4444 9e 00 cc a3     sb         t4,0x9e(s8)
     6::800a4448 b2 00 cd a3     sb         t5,0xb2(s8)
     6::800a444c 40 18 03 00     sll        v1,v1,0x1
     6::800a4450 40 40 08 00     sll        t0,t0,0x1
     6::800a4454 40 48 09 00     sll        t1,t1,0x1
     6::800a4458 23 58 6a 00     subu       t3,v1,t2
     6::800a445c 23 60 0a 01     subu       t4,t0,t2
     6::800a4460 23 68 2a 01     subu       t5,t1,t2
     6::800a4464 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a4468 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a446c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a4470 8b 00 cb a3     sb         t3,0x8b(s8)
     6::800a4474 9f 00 cc a3     sb         t4,0x9f(s8)
     6::800a4478 b3 00 cd a3     sb         t5,0xb3(s8)
     6::800a447c 50 00 03 3c     lui        v1,0x50
     6::800a4480 78 64 63 34     ori        v1,v1,0x6478
     6::800a4484 08 00 08 24     li         t0,0x8
     6::800a4488 fd 91 02 0c     jal        FUN_OVR_226__800a47f4                            undefined FUN_OVR_226__800a47f4()
     6::800a448c 00 00 0a 24     _li        t2,0x0
     6::800a4490 14 50 03 3c     lui        v1,0x5014
     6::800a4494 8c 78 63 34     ori        v1,v1,0x788c
     6::800a4498 0d 00 08 24     li         t0,0xd
     6::800a449c fd 91 02 0c     jal        FUN_OVR_226__800a47f4                            undefined FUN_OVR_226__800a47f4()
     6::800a44a0 04 00 0a 24     _li        t2,0x4
     6::800a44a4 78 64 03 3c     lui        v1,0x6478
     6::800a44a8 a0 28 63 34     ori        v1,v1,0x28a0
     6::800a44ac 12 00 08 24     li         t0,0x12
     6::800a44b0 fd 91 02 0c     jal        FUN_OVR_226__800a47f4                            undefined FUN_OVR_226__800a47f4()
     6::800a44b4 08 00 0a 24     _li        t2,0x8
     6::800a44b8 8c 78 03 3c     lui        v1,0x788c
     6::800a44bc 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a44c0 17 00 08 24     li         t0,0x17
     6::800a44c4 fd 91 02 0c     jal        FUN_OVR_226__800a47f4                            undefined FUN_OVR_226__800a47f4()
     6::800a44c8 0c 00 0a 24     _li        t2,0xc
     6::800a44cc 04 00 98 8c     lw         t8,0x4(a0)
     6::800a44d0 2b ff 01 04     bgez       zero,LAB_OVR_226__800a4180
     6::800a44d4 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_226__800a44d8                           XREF[12]:    FUN_OVR_226__800a46d0:800a46ec(j
                                                                                          FUN_OVR_226__800a46d0:800a4788(j
                                                                                          FUN_OVR_226__800a46d0:800a4790(j
                                                                                          FUN_OVR_226__800a46d0:800a47c4(j
                                                                                          OVR_226::800a4880(j), 
                                                                                          OVR_226::800a490c(j), 
                                                                                          OVR_226::800a4914(j), 
                                                                                          OVR_226::800a4940(j), 
                                                                                          FUN_OVR_226__800a46d0:800a4c28(j
                                                                                          FUN_OVR_226__800a46d0:800a4ce4(j
                                                                                          FUN_OVR_226__800a46d0:800a4e18(j
                                                                                          FUN_OVR_226__800a46d0:800a4ed0(j
     6::800a44d8 08 00 e0 03     jr         ra
     6::800a44dc 00 00 00 00     _nop
                             LAB_OVR_226__800a44e0                           XREF[3]:     OVR_226::800ab670(*), 
                                                                                          OVR_226::800ab674(*), 
                                                                                          OVR_226::800ab678(*)  
     6::800a44e0 00 00 d3 27     addiu      s3,s8,0x0
     6::800a44e4 50 00 d4 27     addiu      s4,s8,0x50
     6::800a44e8 28 00 d5 27     addiu      s5,s8,0x28
     6::800a44ec 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a44f0 b4 91 02 0c     jal        FUN_OVR_226__800a46d0                            undefined FUN_OVR_226__800a46d0()
     6::800a44f4 0c 00 0a 24     _li        t2,0xc
     6::800a44f8 14 00 d3 27     addiu      s3,s8,0x14
     6::800a44fc 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a4500 50 00 d5 27     addiu      s5,s8,0x50
     6::800a4504 28 00 d6 27     addiu      s6,s8,0x28
     6::800a4508 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a450c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a4510 6f 00 01 04     bgez       zero,FUN_OVR_226__800a46d0
     6::800a4514 04 00 0a 24     _li        t2,0x4
     6::800a4518 14 00 d3 27     addiu      s3,s8,0x14
     6::800a451c a0 00 d4 27     addiu      s4,s8,0xa0
     6::800a4520 00 00 d5 27     addiu      s5,s8,0x0
     6::800a4524 28 00 d6 27     addiu      s6,s8,0x28
     6::800a4528 b4 91 02 0c     jal        FUN_OVR_226__800a46d0                            undefined FUN_OVR_226__800a46d0()
     6::800a452c 0c 00 0a 24     _li        t2,0xc
     6::800a4530 00 00 d3 27     addiu      s3,s8,0x0
     6::800a4534 14 00 d4 27     addiu      s4,s8,0x14
     6::800a4538 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a453c 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a4540 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a4544 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a4548 61 00 01 04     bgez       zero,FUN_OVR_226__800a46d0
     6::800a454c 08 00 0a 24     _li        t2,0x8
     6::800a4550 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a4554 00 00 d3 27     addiu      s3,s8,0x0
     6::800a4558 50 00 d4 27     addiu      s4,s8,0x50
     6::800a455c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a4560 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a4564 b4 91 02 0c     jal        FUN_OVR_226__800a46d0                            undefined FUN_OVR_226__800a46d0()
     6::800a4568 0c 00 0a 24     _li        t2,0xc
     6::800a456c 0c 00 03 24     li         v1,0xc
     6::800a4570 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a4574 50 00 d3 27     addiu      s3,s8,0x50
     6::800a4578 14 00 d4 27     addiu      s4,s8,0x14
     6::800a457c a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a4580 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a4584 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a4588 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a458c 50 00 01 04     bgez       zero,FUN_OVR_226__800a46d0
     6::800a4590 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a4594()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a4594                           XREF[2]:     FUN_OVR_226__800a47f4:800a4ae8(c
                                                                                          FUN_OVR_226__800a47f4:800a4b00(c
     6::800a4594 00 00 ab 85     lh         t3,0x0(t5)
     6::800a4598 00 00 cc 85     lh         t4,0x0(t6)
     6::800a459c 00 00 eb a5     sh         t3,0x0(t7)
     6::800a45a0 00 00 0c a6     sh         t4,0x0(s0)
     6::800a45a4 21 18 6c 01     addu       v1,t3,t4
     6::800a45a8 43 18 03 00     sra        v1,v1,0x1
     6::800a45ac 00 00 43 a6     sh         v1,0x0(s2)
     6::800a45b0 02 00 ab 85     lh         t3,0x2(t5)
     6::800a45b4 02 00 cc 85     lh         t4,0x2(t6)
     6::800a45b8 02 00 eb a5     sh         t3,0x2(t7)
     6::800a45bc 02 00 0c a6     sh         t4,0x2(s0)
     6::800a45c0 21 18 6c 01     addu       v1,t3,t4
     6::800a45c4 43 18 03 00     sra        v1,v1,0x1
     6::800a45c8 02 00 43 a6     sh         v1,0x2(s2)
     6::800a45cc 04 00 ab 85     lh         t3,0x4(t5)
     6::800a45d0 04 00 cc 85     lh         t4,0x4(t6)
     6::800a45d4 04 00 eb a5     sh         t3,0x4(t7)
     6::800a45d8 04 00 0c a6     sh         t4,0x4(s0)
     6::800a45dc 21 18 6c 01     addu       v1,t3,t4
     6::800a45e0 43 18 03 00     sra        v1,v1,0x1
     6::800a45e4 00 00 40 ca     gte_ldVXY0 0x0(s2)
     6::800a45e8 00 08 83 48     gte_ldVZ0  v1
     6::800a45ec 04 00 43 a6     sh         v1,0x4(s2)
     6::800a45f0 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a45f4 01 00 18 4a     RTPS
     6::800a45f8 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a45fc 08 00 eb a1     sb         t3,0x8(t7)
     6::800a4600 08 00 0c a2     sb         t4,0x8(s0)
     6::800a4604 21 18 6c 01     addu       v1,t3,t4
     6::800a4608 43 18 03 00     sra        v1,v1,0x1
     6::800a460c 08 00 43 a2     sb         v1,0x8(s2)
     6::800a4610 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a4614 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a4618 09 00 eb a1     sb         t3,0x9(t7)
     6::800a461c 09 00 0c a2     sb         t4,0x9(s0)
     6::800a4620 21 18 6c 01     addu       v1,t3,t4
     6::800a4624 43 18 03 00     sra        v1,v1,0x1
     6::800a4628 09 00 43 a2     sb         v1,0x9(s2)
     6::800a462c 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a4630 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a4634 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a4638 0a 00 0c a2     sb         t4,0xa(s0)
     6::800a463c 21 18 6c 01     addu       v1,t3,t4
     6::800a4640 43 18 03 00     sra        v1,v1,0x1
     6::800a4644 0a 00 43 a2     sb         v1,0xa(s2)
     6::800a4648 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a464c 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a4650 06 00 eb a1     sb         t3,0x6(t7)
     6::800a4654 06 00 0c a2     sb         t4,0x6(s0)
     6::800a4658 21 18 6c 01     addu       v1,t3,t4
     6::800a465c 43 18 03 00     sra        v1,v1,0x1
     6::800a4660 06 00 43 a2     sb         v1,0x6(s2)
     6::800a4664 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a4668 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a466c 07 00 eb a1     sb         t3,0x7(t7)
     6::800a4670 07 00 0c a2     sb         t4,0x7(s0)
     6::800a4674 21 18 6c 01     addu       v1,t3,t4
     6::800a4678 43 18 03 00     sra        v1,v1,0x1
     6::800a467c 07 00 43 a2     sb         v1,0x7(s2)
     6::800a4680 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a4684 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a4688 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a468c 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a4690 0c 00 c3 8d     lw         v1,0xc(t6)
     6::800a4694 10 00 c8 8d     lw         t0,0x10(t6)
     6::800a4698 0c 00 03 ae     sw         v1,0xc(s0)
     6::800a469c 10 00 08 ae     sw         t0,0x10(s0)
     6::800a46a0 5c 00 2b 8c     lw         t3,0x5c(at)
     6::800a46a4 00 98 03 48     gte_stSZ3  v1
     6::800a46a8 0c 00 4e ea     gte_stSXY2 0xc(s2)
     6::800a46ac 10 00 43 ae     sw         v1,0x10(s2)
     6::800a46b0 23 40 6b 00     subu       t0,v1,t3
     6::800a46b4 c2 47 08 00     srl        t0,t0,0x1f
     6::800a46b8 12 00 48 a2     sb         t0,0x12(s2)
     6::800a46bc 40 18 03 00     sll        v1,v1,0x1
     6::800a46c0 23 40 6b 00     subu       t0,v1,t3
     6::800a46c4 c2 47 08 00     srl        t0,t0,0x1f
     6::800a46c8 08 00 e0 03     jr         ra
     6::800a46cc 13 00 48 a2     _sb        t0,0x13(s2)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a46d0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a46d0                           XREF[6]:     OVR_226::800a44f0(c), 
                                                                                          OVR_226::800a4510(j), 
                                                                                          OVR_226::800a4528(c), 
                                                                                          OVR_226::800a4548(j), 
                                                                                          OVR_226::800a4564(c), 
                                                                                          OVR_226::800a458c(j)  
     6::800a46d0 13 00 6f 82     lb         t7,0x13(s3)
     6::800a46d4 13 00 90 82     lb         s0,0x13(s4)
     6::800a46d8 13 00 b1 82     lb         s1,0x13(s5)
     6::800a46dc 13 00 d2 82     lb         s2,0x13(s6)
     6::800a46e0 24 18 f0 01     and        v1,t7,s0
     6::800a46e4 24 18 71 00     and        v1,v1,s1
     6::800a46e8 24 18 72 00     and        v1,v1,s2
     6::800a46ec 7a ff 60 14     bne        v1,zero,LAB_OVR_226__800a44d8
     6::800a46f0 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a46f4 12 00 90 82     lb         s0,0x12(s4)
     6::800a46f8 12 00 b1 82     lb         s1,0x12(s5)
     6::800a46fc 12 00 d2 82     lb         s2,0x12(s6)
     6::800a4700 25 78 f0 01     or         t7,t7,s0
     6::800a4704 25 78 f1 01     or         t7,t7,s1
     6::800a4708 25 78 f2 01     or         t7,t7,s2
     6::800a470c 2e 00 e0 15     bne        t7,zero,LAB_OVR_226__800a47c8
     6::800a4710 0c 00 03 24     _li        v1,0xc
     6::800a4714 70 00 2a ac     sw         t2,0x70(at)
     6::800a4718 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a471c 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a4720 94 01 2a 8c     lw         t2,0x194(at)
     6::800a4724 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a4728 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a472c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a4730 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a4734 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a4738 06 00 40 4b     NCLIP
     6::800a473c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a4740 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a4744 23 78 68 01     subu       t7,t3,t0
     6::800a4748 23 80 88 01     subu       s0,t4,t0
     6::800a474c 23 88 a8 01     subu       s1,t5,t0
     6::800a4750 23 90 c8 01     subu       s2,t6,t0
     6::800a4754 00 c0 08 48     gte_stMAC0 t0
     6::800a4758 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a475c 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a4768
     6::800a4760 22 40 08 00     _sub       t0,zero,t0
     6::800a4764 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a4768                           XREF[1]:     OVR_226::800a475c(j)  
     6::800a4768 06 00 40 4b     NCLIP
     6::800a476c 24 18 6c 01     and        v1,t3,t4
     6::800a4770 24 18 6d 00     and        v1,v1,t5
     6::800a4774 24 18 6e 00     and        v1,v1,t6
     6::800a4778 25 78 f0 01     or         t7,t7,s0
     6::800a477c 25 78 f1 01     or         t7,t7,s1
     6::800a4780 27 78 f2 01     nor        t7,t7,s2
     6::800a4784 25 78 e3 01     or         t7,t7,v1
     6::800a4788 53 ff e0 05     bltz       t7,LAB_OVR_226__800a44d8
     6::800a478c 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a4790 51 ff e0 05     bltz       t7,LAB_OVR_226__800a44d8
     6::800a4794 00 c0 03 48     _gte_stM   v1
     6::800a4798 25 40 09 01     or         t0,t0,t1
     6::800a479c 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a47a8
     6::800a47a0 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a47a4 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a47a8                           XREF[1]:     OVR_226::800a479c(j)  
     6::800a47a8 80 40 08 00     sll        t0,t0,0x2
     6::800a47ac 25 18 69 00     or         v1,v1,t1
     6::800a47b0 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a47b4 c0 18 03 00     sll        v1,v1,0x3
     6::800a47b8 70 00 2a 8c     lw         t2,0x70(at)
     6::800a47bc 25 18 68 00     or         v1,v1,t0
     6::800a47c0 24 18 6a 00     and        v1,v1,t2
     6::800a47c4 44 ff 60 10     beq        v1,zero,LAB_OVR_226__800a44d8
                             LAB_OVR_226__800a47c8                           XREF[1]:     OVR_226::800a470c(j)  
     6::800a47c8 70 00 23 ac     _sw        v1,0x70(at)
     6::800a47cc 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a47d0 24 03 23 24     addiu      v1,at,0x324
     6::800a47d4 df 00 7e 10     beq        v1,s8,LAB_OVR_226__800a4b54
     6::800a47d8 04 00 39 27     _addiu     t9,t9,0x4
     6::800a47dc 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a47e0 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a47e4 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a47e8 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a47ec a8 00 01 04     bgez       zero,LAB_OVR_226__800a4a90
     6::800a47f0 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a47f4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a47f4                           XREF[4]:     OVR_226::800a4488(c), 
                                                                                          OVR_226::800a449c(c), 
                                                                                          OVR_226::800a44b0(c), 
                                                                                          OVR_226::800a44c4(c)  
     6::800a47f4 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a47f8 b4 00 ca af     sw         t2,0xb4(s8)
     6::800a47fc 06 50 09 01     srlv       t2,t1,t0
     6::800a4800 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a4804 80 50 0a 00     sll        t2,t2,0x2
     6::800a4808 21 50 41 01     addu       t2,t2,at
     6::800a480c ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a4810 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a4814 94 01 2a ac     sw         t2,0x194(at)
     6::800a4818 02 9e 0a 00     srl        s3,t2,0x18
     6::800a481c 1f 00 73 32     andi       s3,s3,0x1f
     6::800a4820 06 98 63 02     srlv       s3,v1,s3
     6::800a4824 ff 00 73 32     andi       s3,s3,0xff
     6::800a4828 21 98 7e 02     addu       s3,s3,s8
     6::800a482c 02 a4 0a 00     srl        s4,t2,0x10
     6::800a4830 1f 00 94 32     andi       s4,s4,0x1f
     6::800a4834 06 a0 83 02     srlv       s4,v1,s4
     6::800a4838 ff 00 94 32     andi       s4,s4,0xff
     6::800a483c 21 a0 9e 02     addu       s4,s4,s8
     6::800a4840 02 aa 0a 00     srl        s5,t2,0x8
     6::800a4844 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a4848 06 a8 a3 02     srlv       s5,v1,s5
     6::800a484c ff 00 b5 32     andi       s5,s5,0xff
     6::800a4850 21 a8 be 02     addu       s5,s5,s8
     6::800a4854 1f 00 56 31     andi       s6,t2,0x1f
     6::800a4858 06 b0 c3 02     srlv       s6,v1,s6
     6::800a485c ff 00 d6 32     andi       s6,s6,0xff
     6::800a4860 21 b0 de 02     addu       s6,s6,s8
     6::800a4864 13 00 6f 82     lb         t7,0x13(s3)
     6::800a4868 13 00 90 82     lb         s0,0x13(s4)
     6::800a486c 13 00 b1 82     lb         s1,0x13(s5)
     6::800a4870 13 00 d2 82     lb         s2,0x13(s6)
     6::800a4874 24 18 f0 01     and        v1,t7,s0
     6::800a4878 24 18 71 00     and        v1,v1,s1
     6::800a487c 24 18 72 00     and        v1,v1,s2
     6::800a4880 15 ff 60 14     bne        v1,zero,LAB_OVR_226__800a44d8
     6::800a4884 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a4888 12 00 90 82     lb         s0,0x12(s4)
     6::800a488c 12 00 b1 82     lb         s1,0x12(s5)
     6::800a4890 12 00 d2 82     lb         s2,0x12(s6)
     6::800a4894 25 78 f0 01     or         t7,t7,s0
     6::800a4898 25 78 f1 01     or         t7,t7,s1
     6::800a489c 25 78 f2 01     or         t7,t7,s2
     6::800a48a0 28 00 e0 15     bne        t7,zero,LAB_OVR_226__800a4944
     6::800a48a4 0c 00 03 24     _li        v1,0xc
     6::800a48a8 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a48ac 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a48b0 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a48b4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a48b8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a48bc 06 00 40 4b     NCLIP
     6::800a48c0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a48c4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a48c8 23 78 68 01     subu       t7,t3,t0
     6::800a48cc 23 80 88 01     subu       s0,t4,t0
     6::800a48d0 23 88 a8 01     subu       s1,t5,t0
     6::800a48d4 23 90 c8 01     subu       s2,t6,t0
     6::800a48d8 00 c0 08 48     gte_stMAC0 t0
     6::800a48dc 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a48e0 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a48ec
     6::800a48e4 22 40 08 00     _sub       t0,zero,t0
     6::800a48e8 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a48ec                           XREF[1]:     OVR_226::800a48e0(j)  
     6::800a48ec 06 00 40 4b     NCLIP
     6::800a48f0 24 18 6c 01     and        v1,t3,t4
     6::800a48f4 24 18 6d 00     and        v1,v1,t5
     6::800a48f8 24 18 6e 00     and        v1,v1,t6
     6::800a48fc 25 78 f0 01     or         t7,t7,s0
     6::800a4900 25 78 f1 01     or         t7,t7,s1
     6::800a4904 27 78 f2 01     nor        t7,t7,s2
     6::800a4908 25 78 e3 01     or         t7,t7,v1
     6::800a490c f2 fe e0 05     bltz       t7,LAB_OVR_226__800a44d8
     6::800a4910 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a4914 f0 fe e0 05     bltz       t7,LAB_OVR_226__800a44d8
     6::800a4918 00 c0 03 48     _gte_stM   v1
     6::800a491c 25 40 09 01     or         t0,t0,t1
     6::800a4920 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a492c
     6::800a4924 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a4928 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a492c                           XREF[1]:     OVR_226::800a4920(j)  
     6::800a492c 80 40 08 00     sll        t0,t0,0x2
     6::800a4930 25 18 69 00     or         v1,v1,t1
     6::800a4934 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a4938 c0 18 03 00     sll        v1,v1,0x3
     6::800a493c 25 18 68 00     or         v1,v1,t0
     6::800a4940 e5 fe 60 10     beq        v1,zero,LAB_OVR_226__800a44d8
                             LAB_OVR_226__800a4944                           XREF[1]:     OVR_226::800a48a0(j)  
     6::800a4944 70 00 23 ac     _sw        v1,0x70(at)
     6::800a4948 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a494c 04 00 39 27     addiu      t9,t9,0x4
     6::800a4950 c2 4f 09 00     srl        t1,t1,0x1f
     6::800a4954 c0 4f 09 00     sll        t1,t1,0x1f
     6::800a4958 c2 57 0a 00     srl        t2,t2,0x1f
     6::800a495c 80 57 0a 00     sll        t2,t2,0x1e
     6::800a4960 25 50 49 01     or         t2,t2,t1
     6::800a4964 80 00 2a ac     sw         t2,0x80(at)
     6::800a4968 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a496c 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a4970 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a4974 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a4978 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a497c 23 50 6c 01     subu       t2,t3,t4
     6::800a4980 82 48 03 00     srl        t1,v1,0x2
     6::800a4984 21 48 38 01     addu       t1,t1,t8
     6::800a4988 18 00 29 81     lb         t1,0x18(t1)
     6::800a498c 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a4998
     6::800a4990 21 e0 60 01     _move      gp,t3
     6::800a4994 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a4998                           XREF[1]:     OVR_226::800a498c(j)  
     6::800a4998 23 50 8d 03     subu       t2,gp,t5
     6::800a499c 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a49a8
     6::800a49a0 21 18 78 00     _addu      v1,v1,t8
     6::800a49a4 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a49a8                           XREF[1]:     OVR_226::800a499c(j)  
     6::800a49a8 23 50 8e 03     subu       t2,gp,t6
     6::800a49ac 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a49b8
     6::800a49b0 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a49b4 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a49b8                           XREF[1]:     OVR_226::800a49ac(j)  
     6::800a49b8 21 50 80 03     move       t2,gp
     6::800a49bc 82 e1 1c 00     srl        gp,gp,0x6
     6::800a49c0 21 e0 89 03     addu       gp,gp,t1
     6::800a49c4 01 00 69 30     andi       t1,v1,0x1
     6::800a49c8 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a49d4
     6::800a49cc 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a49d0 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a49d4                           XREF[1]:     OVR_226::800a49c8(j)  
     6::800a49d4 02 00 81 07     bgez       gp,LAB_OVR_226__800a49e0
     6::800a49d8 21 e0 85 03     _addu      gp,gp,a1
     6::800a49dc 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a49e0                           XREF[1]:     OVR_226::800a49d4(j)  
     6::800a49e0 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a49e4 24 00 69 8c     lw         t1,0x24(v1)
     6::800a49e8 23 40 48 01     subu       t0,t2,t0
     6::800a49ec 84 00 29 ac     sw         t1,0x84(at)
     6::800a49f0 0c 00 01 05     bgez       t0,LAB_OVR_226__800a4a24
     6::800a49f4 20 00 28 8c     _lw        t0,0x20(at)
     6::800a49f8 0c 00 63 24     addiu      v1,v1,0xc
     6::800a49fc 23 40 48 01     subu       t0,t2,t0
     6::800a4a00 08 00 01 05     bgez       t0,LAB_OVR_226__800a4a24
     6::800a4a04 24 00 28 8c     _lw        t0,0x24(at)
     6::800a4a08 0c 00 63 24     addiu      v1,v1,0xc
     6::800a4a0c 23 40 48 01     subu       t0,t2,t0
     6::800a4a10 04 00 01 05     bgez       t0,LAB_OVR_226__800a4a24
     6::800a4a14 00 00 00 00     _nop
     6::800a4a18 02 00 20 05     bltz       t1,LAB_OVR_226__800a4a24
     6::800a4a1c 00 00 00 00     _nop
     6::800a4a20 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a4a24                           XREF[4]:     OVR_226::800a49f0(j), 
                                                                                          OVR_226::800a4a00(j), 
                                                                                          OVR_226::800a4a10(j), 
                                                                                          OVR_226::800a4a18(j)  
     6::800a4a24 94 01 2a 8c     lw         t2,0x194(at)
     6::800a4a28 00 00 68 8c     lw         t0,0x0(v1)
     6::800a4a2c 04 00 69 8c     lw         t1,0x4(v1)
     6::800a4a30 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a4a34 ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a4a38 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a4a3c 00 52 0a 00     sll        t2,t2,0x8
     6::800a4a40 0a 00 40 05     bltz       t2,LAB_OVR_226__800a4a6c
     6::800a4a44 b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a4a48 06 00 68 a6     sh         t0,0x6(s3)
     6::800a4a4c 08 00 68 8c     lw         t0,0x8(v1)
     6::800a4a50 06 00 89 a6     sh         t1,0x6(s4)
     6::800a4a54 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a4a58 00 54 0a 00     sll        t2,t2,0x10
     6::800a4a5c 0b 00 40 05     bltz       t2,LAB_OVR_226__800a4a8c
     6::800a4a60 02 4c 08 00     _srl       t1,t0,0x10
     6::800a4a64 09 00 01 04     bgez       zero,LAB_OVR_226__800a4a8c
     6::800a4a68 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a4a6c                           XREF[1]:     OVR_226::800a4a40(j)  
     6::800a4a6c 06 00 69 a6     sh         t1,0x6(s3)
     6::800a4a70 08 00 69 8c     lw         t1,0x8(v1)
     6::800a4a74 00 54 0a 00     sll        t2,t2,0x10
     6::800a4a78 06 00 88 a6     sh         t0,0x6(s4)
     6::800a4a7c 02 44 09 00     srl        t0,t1,0x10
     6::800a4a80 02 00 40 05     bltz       t2,LAB_OVR_226__800a4a8c
     6::800a4a84 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a4a88 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a4a8c                           XREF[3]:     OVR_226::800a4a5c(j), 
                                                                                          OVR_226::800a4a64(j), 
                                                                                          OVR_226::800a4a80(j)  
     6::800a4a8c 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a4a90                           XREF[1]:     FUN_OVR_226__800a46d0:800a47ec(j
     6::800a4a90 00 00 00 00     nop
     6::800a4a94 23 88 63 01     subu       s1,t3,v1
     6::800a4a98 23 90 83 01     subu       s2,t4,v1
     6::800a4a9c 23 78 a3 01     subu       t7,t5,v1
     6::800a4aa0 23 80 c3 01     subu       s0,t6,v1
     6::800a4aa4 42 8f 11 00     srl        s1,s1,0x1d
     6::800a4aa8 04 00 31 32     andi       s1,s1,0x4
     6::800a4aac 02 97 12 00     srl        s2,s2,0x1c
     6::800a4ab0 08 00 52 32     andi       s2,s2,0x8
     6::800a4ab4 25 88 32 02     or         s1,s1,s2
     6::800a4ab8 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a4abc 10 00 ef 31     andi       t7,t7,0x10
     6::800a4ac0 25 88 2f 02     or         s1,s1,t7
     6::800a4ac4 82 86 10 00     srl        s0,s0,0x1a
     6::800a4ac8 20 00 10 32     andi       s0,s0,0x20
     6::800a4acc 25 88 30 02     or         s1,s1,s0
     6::800a4ad0 19 00 20 12     beq        s1,zero,LAB_OVR_226__800a4b38
     6::800a4ad4 21 68 60 02     _move      t5,s3
     6::800a4ad8 21 70 80 02     move       t6,s4
     6::800a4adc b8 00 de 27     addiu      s8,s8,0xb8
     6::800a4ae0 00 00 cf 27     addiu      t7,s8,0x0
     6::800a4ae4 14 00 d0 27     addiu      s0,s8,0x14
     6::800a4ae8 65 91 02 0c     jal        FUN_OVR_226__800a4594                            undefined FUN_OVR_226__800a4594()
     6::800a4aec 50 00 d2 27     _addiu     s2,s8,0x50
     6::800a4af0 21 68 a0 02     move       t5,s5
     6::800a4af4 21 70 c0 02     move       t6,s6
     6::800a4af8 28 00 cf 27     addiu      t7,s8,0x28
     6::800a4afc 3c 00 d0 27     addiu      s0,s8,0x3c
     6::800a4b00 65 91 02 0c     jal        FUN_OVR_226__800a4594                            undefined FUN_OVR_226__800a4594()
     6::800a4b04 a0 00 d2 27     _addiu     s2,s8,0xa0
     6::800a4b08 21 18 21 02     addu       v1,s1,at
     6::800a4b0c 48 01 63 8c     lw         v1,0x148(v1)
     6::800a4b10 0a 80 08 3c     lui        t0,0x800a
     6::800a4b14 28 4b 08 25     addiu      t0,t0,0x4b28
     6::800a4b18 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a4b1c 3c 00 28 af     sw         t0=>LAB_OVR_226__800a4b28,0x3c(t9)
     6::800a4b20 08 00 60 00     jr         v1
     6::800a4b24 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a4b28                           XREF[1]:     FUN_OVR_226__800a47f4:800a4b1c(*
     6::800a4b28 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a4b2c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a4b30 08 00 e0 03     jr         ra
     6::800a4b34 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a4b38                           XREF[1]:     OVR_226::800a4ad0(j)  
     6::800a4b38 70 00 23 8c     lw         v1,0x70(at)
     6::800a4b3c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a4b40 21 18 61 00     addu       v1,v1,at
     6::800a4b44 84 01 63 8c     lw         v1,0x184(v1)
     6::800a4b48 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a4b4c 08 00 60 00     jr         v1
     6::800a4b50 00 00 00 00     _nop
                             LAB_OVR_226__800a4b54                           XREF[1]:     OVR_226::800a47d4(j)  
     6::800a4b54 84 00 23 8c     lw         v1,0x84(at)
     6::800a4b58 24 03 2a 24     addiu      t2,at,0x324
     6::800a4b5c 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a4bf8
     6::800a4b60 20 03 28 8c     _lw        t0,0x320(at)
     6::800a4b64 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a4b68 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a4bc4
     6::800a4b6c 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a4b70 0a 80 0a 3c     lui        t2,0x800a
     6::800a4b74 50 45 4a 25     addiu      t2,t2,0x4550
     6::800a4b78 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a4bf8
     6::800a4b7c 94 01 23 8c     _lw        v1,0x194(at)
     6::800a4b80 40 40 08 00     sll        t0,t0,0x1
     6::800a4b84 00 1a 03 00     sll        v1,v1,0x8
     6::800a4b88 02 00 61 04     bgez       v1,LAB_OVR_226__800a4b94
     6::800a4b8c 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a4b90 30 00 08 25     addiu      t0,t0,0x30
                             LAB_OVR_226__800a4b94                           XREF[1]:     OVR_226::800a4b88(j)  
     6::800a4b94 21 40 09 01     addu       t0,t0,t1
     6::800a4b98 21 50 48 01     addu       t2,t2,t0
     6::800a4b9c 00 00 48 8d     lw         t0,0x0(t2)
     6::800a4ba0 04 00 49 8d     lw         t1,0x4(t2)
     6::800a4ba4 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a4ba8 06 00 68 a6     sh         t0,0x6(s3)
     6::800a4bac 08 00 48 85     lh         t0,0x8(t2)
     6::800a4bb0 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a4bb4 06 00 89 a6     sh         t1,0x6(s4)
     6::800a4bb8 0a 00 49 85     lh         t1,0xa(t2)
     6::800a4bbc 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a4bc0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a4bc4                           XREF[2]:     OVR_226::800a4b68(j), 
                                                                                          OVR_226::800a4c04(j)  
     6::800a4bc4 70 00 23 8c     lw         v1,0x70(at)
     6::800a4bc8 00 00 00 00     nop
     6::800a4bcc 21 18 61 00     addu       v1,v1,at
     6::800a4bd0 84 01 63 8c     lw         v1,0x184(v1)
     6::800a4bd4 00 00 00 00     nop
     6::800a4bd8 09 f8 60 00     jalr       v1
     6::800a4bdc fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a4be0 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a4be4 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a4be8 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a4bec a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a4bf0 08 00 e0 03     jr         ra
     6::800a4bf4 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a4bf8                           XREF[2]:     OVR_226::800a4b5c(j), 
                                                                                          OVR_226::800a4b78(j)  
     6::800a4bf8 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a4bfc b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a4c00 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a4c04 ef ff 01 04     bgez       zero,LAB_OVR_226__800a4bc4
     6::800a4c08 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a4c0c 21 98 80 02     move       s3,s4
     6::800a4c10 21 a0 c0 02     move       s4,s6
     6::800a4c14 13 00 6f 82     lb         t7,0x13(s3)
     6::800a4c18 13 00 90 82     lb         s0,0x13(s4)
     6::800a4c1c 13 00 b1 82     lb         s1,0x13(s5)
     6::800a4c20 24 18 f0 01     and        v1,t7,s0
     6::800a4c24 24 18 71 00     and        v1,v1,s1
     6::800a4c28 2b fe 60 04     bltz       v1,LAB_OVR_226__800a44d8
     6::800a4c2c 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a4c30 12 00 90 82     lb         s0,0x12(s4)
     6::800a4c34 12 00 b1 82     lb         s1,0x12(s5)
     6::800a4c38 25 78 f0 01     or         t7,t7,s0
     6::800a4c3c 25 78 f1 01     or         t7,t7,s1
     6::800a4c40 62 00 e0 05     bltz       t7,LAB_OVR_226__800a4dcc
     6::800a4c44 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a4c48 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a4c4c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a4c50 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a4c54 08 00 90 8e     lw         s0,0x8(s4)
     6::800a4c58 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a4c5c 06 00 73 86     lh         s3,0x6(s3)
     6::800a4c60 06 00 94 86     lh         s4,0x6(s4)
     6::800a4c64 06 00 b5 86     lh         s5,0x6(s5)
     6::800a4c68 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a4c6c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a4c70 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a4c74 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a4c78 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a4c7c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a4c80 60 00 03 3c     lui        v1,0x60
     6::800a4c84 24 48 83 02     and        t1,s4,v1
     6::800a4c88 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a4c94
     6::800a4c8c 00 36 03 3c     _lui       v1,0x3600
     6::800a4c90 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a4c94                           XREF[1]:     OVR_226::800a4c88(j)  
     6::800a4c94 25 18 6f 00     or         v1,v1,t7
     6::800a4c98 04 00 43 ac     sw         v1,0x4(v0)
     6::800a4c9c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a4ca0 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a4ca4 10 00 50 ac     sw         s0,0x10(v0)
     6::800a4ca8 14 00 4c ac     sw         t4,0x14(v0)
     6::800a4cac 18 00 54 ac     sw         s4,0x18(v0)
     6::800a4cb0 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a4cb4 20 00 4d ac     sw         t5,0x20(v0)
     6::800a4cb8 24 00 55 ac     sw         s5,0x24(v0)
     6::800a4cbc 28 00 09 24     li         t1,0x28
     6::800a4cc0 39 00 01 04     bgez       zero,LAB_OVR_226__800a4da8
     6::800a4cc4 00 09 0a 3c     _lui       t2,0x900
     6::800a4cc8 13 00 6f 82     lb         t7,0x13(s3)
     6::800a4ccc 13 00 90 82     lb         s0,0x13(s4)
     6::800a4cd0 13 00 b1 82     lb         s1,0x13(s5)
     6::800a4cd4 13 00 d2 82     lb         s2,0x13(s6)
     6::800a4cd8 24 18 f0 01     and        v1,t7,s0
     6::800a4cdc 24 18 71 00     and        v1,v1,s1
     6::800a4ce0 24 18 72 00     and        v1,v1,s2
     6::800a4ce4 fc fd 60 14     bne        v1,zero,LAB_OVR_226__800a44d8
     6::800a4ce8 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a4cec 12 00 90 82     lb         s0,0x12(s4)
     6::800a4cf0 12 00 b1 82     lb         s1,0x12(s5)
     6::800a4cf4 12 00 d2 82     lb         s2,0x12(s6)
     6::800a4cf8 25 78 f0 01     or         t7,t7,s0
     6::800a4cfc 25 78 f1 01     or         t7,t7,s1
     6::800a4d00 25 78 f2 01     or         t7,t7,s2
     6::800a4d04 5a 00 e0 15     bne        t7,zero,LAB_OVR_226__800a4e70
     6::800a4d08 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a4d0c 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a4d10 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a4d14 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a4d18 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a4d1c 08 00 90 8e     lw         s0,0x8(s4)
     6::800a4d20 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a4d24 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a4d28 06 00 73 86     lh         s3,0x6(s3)
     6::800a4d2c 06 00 94 86     lh         s4,0x6(s4)
     6::800a4d30 06 00 b5 86     lh         s5,0x6(s5)
     6::800a4d34 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a4d38 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a4d3c 06 00 d4 86     lh         s4,0x6(s6)
     6::800a4d40 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a4d44 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a4d48 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a4d4c a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a4d50 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a4d54 60 00 03 3c     lui        v1,0x60
     6::800a4d58 24 48 83 02     and        t1,s4,v1
     6::800a4d5c 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a4d68
     6::800a4d60 00 3e 03 3c     _lui       v1,0x3e00
     6::800a4d64 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a4d68                           XREF[1]:     OVR_226::800a4d5c(j)  
     6::800a4d68 25 18 6f 00     or         v1,v1,t7
     6::800a4d6c 04 00 43 ac     sw         v1,0x4(v0)
     6::800a4d70 08 00 4b ac     sw         t3,0x8(v0)
     6::800a4d74 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a4d78 10 00 50 ac     sw         s0,0x10(v0)
     6::800a4d7c 14 00 4c ac     sw         t4,0x14(v0)
     6::800a4d80 18 00 54 ac     sw         s4,0x18(v0)
     6::800a4d84 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a4d88 20 00 4d ac     sw         t5,0x20(v0)
     6::800a4d8c 24 00 55 ac     sw         s5,0x24(v0)
     6::800a4d90 28 00 52 ac     sw         s2,0x28(v0)
     6::800a4d94 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a4d98 02 1c 15 00     srl        v1,s5,0x10
     6::800a4d9c 30 00 43 ac     sw         v1,0x30(v0)
     6::800a4da0 34 00 09 24     li         t1,0x34
     6::800a4da4 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a4da8                           XREF[1]:     OVR_226::800a4cc0(j)  
     6::800a4da8 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a4dac 00 42 02 00     sll        t0,v0,0x8
     6::800a4db0 02 42 08 00     srl        t0,t0,0x8
     6::800a4db4 25 18 6a 00     or         v1,v1,t2
     6::800a4db8 00 00 43 ac     sw         v1,0x0(v0)
     6::800a4dbc 21 10 49 00     addu       v0,v0,t1
     6::800a4dc0 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a4dc4 08 00 e0 03     jr         ra
     6::800a4dc8 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800a4dcc                           XREF[1]:     OVR_226::800a4c40(j)  
     6::800a4dcc 58 00 3f ac     sw         ra,0x58(at)
     6::800a4dd0 98 01 2f 84     lh         t7,0x198(at)
     6::800a4dd4 9a 01 30 84     lh         s0,0x19a(at)
     6::800a4dd8 9c 01 31 84     lh         s1,0x19c(at)
     6::800a4ddc 00 00 63 86     lh         v1,0x0(s3)
     6::800a4de0 02 00 68 86     lh         t0,0x2(s3)
     6::800a4de4 ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4de8 04 00 69 86     _lh        t1,0x4(s3)
     6::800a4dec 0b 00 40 05     bltz       t2,LAB_OVR_226__800a4e1c
     6::800a4df0 00 00 83 86     _lh        v1,0x0(s4)
     6::800a4df4 02 00 88 86     lh         t0,0x2(s4)
     6::800a4df8 ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4dfc 04 00 89 86     _lh        t1,0x4(s4)
     6::800a4e00 06 00 40 05     bltz       t2,LAB_OVR_226__800a4e1c
     6::800a4e04 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a4e08 02 00 a8 86     lh         t0,0x2(s5)
     6::800a4e0c ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4e10 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a4e14 58 00 3f 8c     lw         ra,0x58(at)
     6::800a4e18 af fd 41 05     bgez       t2,LAB_OVR_226__800a44d8
                             LAB_OVR_226__800a4e1c                           XREF[2]:     OVR_226::800a4dec(j), 
                                                                                          OVR_226::800a4e00(j)  
     6::800a4e1c 10 00 2f 8c     lw         t7,0x10(at)
     6::800a4e20 80 00 23 8c     lw         v1,0x80(at)
     6::800a4e24 a6 01 28 84     lh         t0,0x1a6(at)
     6::800a4e28 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a4e2c 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a4e30 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a4e34 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a4e38 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a4e3c 21 68 60 02     move       t5,s3
     6::800a4e40 de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4e44 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a4e48 21 68 80 02     move       t5,s4
     6::800a4e4c de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4e50 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a4e54 21 68 a0 02     move       t5,s5
     6::800a4e58 de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4e5c 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a4e60 58 00 3f 8c     lw         ra,0x58(at)
     6::800a4e64 30 00 ef 25     addiu      t7,t7,0x30
     6::800a4e68 08 00 e0 03     jr         ra
     6::800a4e6c 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_226__800a4e70                           XREF[1]:     OVR_226::800a4d04(j)  
     6::800a4e70 58 00 3f ac     sw         ra,0x58(at)
     6::800a4e74 98 01 2f 84     lh         t7,0x198(at)
     6::800a4e78 9a 01 30 84     lh         s0,0x19a(at)
     6::800a4e7c 9c 01 31 84     lh         s1,0x19c(at)
     6::800a4e80 00 00 63 86     lh         v1,0x0(s3)
     6::800a4e84 02 00 68 86     lh         t0,0x2(s3)
     6::800a4e88 ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4e8c 04 00 69 86     _lh        t1,0x4(s3)
     6::800a4e90 10 00 40 05     bltz       t2,LAB_OVR_226__800a4ed4
     6::800a4e94 00 00 83 86     _lh        v1,0x0(s4)
     6::800a4e98 02 00 88 86     lh         t0,0x2(s4)
     6::800a4e9c ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4ea0 04 00 89 86     _lh        t1,0x4(s4)
     6::800a4ea4 0b 00 40 05     bltz       t2,LAB_OVR_226__800a4ed4
     6::800a4ea8 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a4eac 02 00 a8 86     lh         t0,0x2(s5)
     6::800a4eb0 ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4eb4 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a4eb8 06 00 40 05     bltz       t2,LAB_OVR_226__800a4ed4
     6::800a4ebc 00 00 c3 86     _lh        v1,0x0(s6)
     6::800a4ec0 02 00 c8 86     lh         t0,0x2(s6)
     6::800a4ec4 ce 93 02 0c     jal        FUN_OVR_226__800a4f38                            undefined FUN_OVR_226__800a4f38()
     6::800a4ec8 04 00 c9 86     _lh        t1,0x4(s6)
     6::800a4ecc 58 00 3f 8c     lw         ra,0x58(at)
     6::800a4ed0 81 fd 41 05     bgez       t2,LAB_OVR_226__800a44d8
                             LAB_OVR_226__800a4ed4                           XREF[3]:     OVR_226::800a4e90(j), 
                                                                                          OVR_226::800a4ea4(j), 
                                                                                          OVR_226::800a4eb8(j)  
     6::800a4ed4 10 00 2f 8c     lw         t7,0x10(at)
     6::800a4ed8 80 00 23 8c     lw         v1,0x80(at)
     6::800a4edc a6 01 28 84     lh         t0,0x1a6(at)
     6::800a4ee0 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a4ee4 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a4ee8 01 00 63 34     ori        v1,v1,0x1
     6::800a4eec 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a4ef0 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a4ef4 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a4ef8 21 68 60 02     move       t5,s3
     6::800a4efc de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4f00 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a4f04 21 68 80 02     move       t5,s4
     6::800a4f08 de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4f0c 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a4f10 21 68 a0 02     move       t5,s5
     6::800a4f14 de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4f18 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a4f1c 21 68 c0 02     move       t5,s6
     6::800a4f20 de 93 02 0c     jal        FUN_OVR_226__800a4f78                            undefined FUN_OVR_226__800a4f78()
     6::800a4f24 30 00 f0 25     _addiu     s0,t7,0x30
     6::800a4f28 58 00 3f 8c     lw         ra,0x58(at)
     6::800a4f2c 3c 00 ef 25     addiu      t7,t7,0x3c
     6::800a4f30 08 00 e0 03     jr         ra
     6::800a4f34 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a4f38()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a4f38                           XREF[7]:     FUN_OVR_226__800a46d0:800a4de4(c
                                                                                          FUN_OVR_226__800a46d0:800a4df8(c
                                                                                          FUN_OVR_226__800a46d0:800a4e0c(c
                                                                                          FUN_OVR_226__800a46d0:800a4e88(c
                                                                                          FUN_OVR_226__800a46d0:800a4e9c(c
                                                                                          FUN_OVR_226__800a46d0:800a4eb0(c
                                                                                          FUN_OVR_226__800a46d0:800a4ec4(c
     6::800a4f38 23 18 6f 00     subu       v1,v1,t7
     6::800a4f3c 02 00 61 04     bgez       v1,LAB_OVR_226__800a4f48
     6::800a4f40 23 40 10 01     _subu      t0,t0,s0
     6::800a4f44 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_226__800a4f48                           XREF[1]:     OVR_226::800a4f3c(j)  
     6::800a4f48 00 ff 6b 24     addiu      t3,v1,-0x100
     6::800a4f4c 02 00 01 05     bgez       t0,LAB_OVR_226__800a4f58
     6::800a4f50 23 48 31 01     _subu      t1,t1,s1
     6::800a4f54 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_226__800a4f58                           XREF[1]:     OVR_226::800a4f4c(j)  
     6::800a4f58 80 fe 0c 25     addiu      t4,t0,-0x180
     6::800a4f5c 02 00 21 05     bgez       t1,LAB_OVR_226__800a4f68
     6::800a4f60 00 00 00 00     _nop
     6::800a4f64 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_226__800a4f68                           XREF[1]:     OVR_226::800a4f5c(j)  
     6::800a4f68 00 ff 2d 25     addiu      t5,t1,-0x100
     6::800a4f6c 24 58 6c 01     and        t3,t3,t4
     6::800a4f70 08 00 e0 03     jr         ra
     6::800a4f74 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a4f78()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a4f78                           XREF[7]:     FUN_OVR_226__800a46d0:800a4e40(c
                                                                                          FUN_OVR_226__800a46d0:800a4e4c(c
                                                                                          FUN_OVR_226__800a46d0:800a4e58(c
                                                                                          FUN_OVR_226__800a46d0:800a4efc(c
                                                                                          FUN_OVR_226__800a46d0:800a4f08(c
                                                                                          FUN_OVR_226__800a46d0:800a4f14(c
                                                                                          FUN_OVR_226__800a46d0:800a4f20(c
     6::800a4f78 13 00 a3 81     lb         v1,0x13(t5)
     6::800a4f7c 00 00 a8 8d     lw         t0,0x0(t5)
     6::800a4f80 04 00 a9 8d     lw         t1,0x4(t5)
     6::800a4f84 08 00 aa 8d     lw         t2,0x8(t5)
     6::800a4f88 00 1e 03 00     sll        v1,v1,0x18
     6::800a4f8c 25 50 43 01     or         t2,t2,v1
     6::800a4f90 00 00 08 ae     sw         t0,0x0(s0)
     6::800a4f94 04 00 09 ae     sw         t1,0x4(s0)
     6::800a4f98 08 00 e0 03     jr         ra
     6::800a4f9c 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_226__800a4fa0                           XREF[1]:     OVR_226::800ab44c(*)  
     6::800a4fa0 09 80 08 3c     lui        t0,0x8009
     6::800a4fa4 04 64 08 25     addiu      t0,t0,0x6404
     6::800a4fa8 64 00 28 ac     sw         t0=>DAT_80096404,0x64(at)                        = ??
     6::800a4fac 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_226__800a4fb0                           XREF[1]:     OVR_226::800a5288(j)  
     6::800a4fb0 bd 00 80 10     beq        a0,zero,LAB_OVR_226__800a52a8
     6::800a4fb4 00 00 00 00     _nop
     6::800a4fb8 1c 00 78 8c     lw         t8,0x1c(v1)
     6::800a4fbc 18 00 79 8c     lw         t9,0x18(v1)
     6::800a4fc0 c8 00 2a 8c     lw         t2,0xc8(at)
     6::800a4fc4 3c 00 08 97     lhu        t0,0x3c(t8)
     6::800a4fc8 68 00 39 ac     sw         t9,0x68(at)
     6::800a4fcc c2 48 08 00     srl        t1,t0,0x3
     6::800a4fd0 fc 01 29 31     andi       t1,t1,0x1fc
     6::800a4fd4 21 48 2a 01     addu       t1,t1,t2
     6::800a4fd8 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a4fdc 00 00 29 8d     lw         t1,0x0(t1)
     6::800a4fe0 1f 00 08 31     andi       t0,t0,0x1f
     6::800a4fe4 bc 00 28 ac     sw         t0,0xbc(at)
     6::800a4fe8 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_226__800a4fec                           XREF[1]:     OVR_226::800a527c(j)  
     6::800a4fec 30 00 23 8c     lw         v1,0x30(at)
     6::800a4ff0 80 13 48 24     addiu      t0,v0,0x1380
     6::800a4ff4 23 18 68 00     subu       v1,v1,t0
     6::800a4ff8 ae ef 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a4ffc bc 00 23 8c     _lw        v1,0xbc(at)
     6::800a5000 c4 00 28 8c     lw         t0,0xc4(at)
     6::800a5004 06 00 61 04     bgez       v1,LAB_OVR_226__800a5020
     6::800a5008 c0 00 29 8c     _lw        t1,0xc0(at)
     6::800a500c 1f 00 03 24     li         v1,0x1f
     6::800a5010 04 00 28 8d     lw         t0,0x4(t1)
     6::800a5014 04 00 29 25     addiu      t1,t1,0x4
     6::800a5018 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a501c c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_226__800a5020                           XREF[1]:     OVR_226::800a5004(j)  
     6::800a5020 04 40 68 00     sllv       t0,t0,v1
     6::800a5024 ff ff 63 24     addiu      v1,v1,-0x1
     6::800a5028 91 00 01 05     bgez       t0,LAB_OVR_226__800a5270
     6::800a502c bc 00 23 ac     _sw        v1,0xbc(at)
     6::800a5030 b4 01 3e 24     addiu      s8,at,0x1b4
     6::800a5034 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a5038 00 00 14 8f     lw         s4,0x0(t8)
     6::800a503c 04 00 16 8f     lw         s6,0x4(t8)
     6::800a5040 ff ff 93 32     andi       s3,s4,0xffff
     6::800a5044 00 99 13 00     sll        s3,s3,0x4
     6::800a5048 21 98 77 02     addu       s3,s3,s7
     6::800a504c 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a5054 02 a4 14 00     srl        s4,s4,0x10
     6::800a5058 00 a1 14 00     sll        s4,s4,0x4
     6::800a505c 21 a0 97 02     addu       s4,s4,s7
     6::800a5060 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a5068 ff ff d5 32     andi       s5,s6,0xffff
     6::800a506c 00 a9 15 00     sll        s5,s5,0x4
     6::800a5070 21 a8 b7 02     addu       s5,s5,s7
     6::800a5074 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a507c 02 b4 16 00     srl        s6,s6,0x10
     6::800a5080 00 b1 16 00     sll        s6,s6,0x4
     6::800a5084 30 00 28 4a     RTPT
     6::800a5088 21 b0 d7 02     addu       s6,s6,s7
     6::800a508c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a5090 08 00 90 8e     lw         s0,0x8(s4)
     6::800a5094 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a5098 08 00 cf af     sw         t7,0x8(s8)
     6::800a509c 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a50a0 30 00 d1 af     sw         s1,0x30(s8)
     6::800a50a4 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a50a8 00 f8 43 48     gte_stFLAG v1
     6::800a50ac 10 00 d1 eb     gte_stSZ1  0x10(s8)
     6::800a50b0 80 1b 03 00     sll        v1,v1,0xe
     6::800a50b4 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a50b8 75 00 60 14     bne        v1,zero,LAB_OVR_226__800a5290
     6::800a50bc 08 00 14 8f     _lw        s4,0x8(t8)
     6::800a50c0 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a50c4 24 00 d2 eb     gte_stSZ2  0x24(s8)
     6::800a50c8 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a50cc 38 00 d3 eb     gte_stSZ3  0x38(s8)
     6::800a50d0 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a50d4 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a50d8 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a50dc 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a50e0 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a50e4 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a50e8 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a50f0 ff ff 93 32     andi       s3,s4,0xffff
     6::800a50f4 00 99 13 00     sll        s3,s3,0x4
     6::800a50f8 21 98 77 02     addu       s3,s3,s7
     6::800a50fc 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a5104 02 a4 14 00     srl        s4,s4,0x10
     6::800a5108 00 a1 14 00     sll        s4,s4,0x4
     6::800a510c 21 a0 97 02     addu       s4,s4,s7
     6::800a5110 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a5118 21 c8 20 00     move       t9,at
     6::800a511c 00 00 00 00     nop
     6::800a5120 30 00 28 4a     RTPT
     6::800a5124 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a5128 08 00 70 8e     lw         s0,0x8(s3)
     6::800a512c 08 00 91 8e     lw         s1,0x8(s4)
     6::800a5130 44 00 cf af     sw         t7,0x44(s8)
     6::800a5134 58 00 d0 af     sw         s0,0x58(s8)
     6::800a5138 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a513c 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a5140 00 f8 43 48     gte_stFLAG v1
     6::800a5144 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     6::800a5148 80 1b 03 00     sll        v1,v1,0xe
     6::800a514c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a5150 4f 00 60 14     bne        v1,zero,LAB_OVR_226__800a5290
     6::800a5154 0c 00 14 8f     _lw        s4,0xc(t8)
     6::800a5158 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a515c 60 00 d2 eb     gte_stSZ2  0x60(s8)
     6::800a5160 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a5164 74 00 d3 eb     gte_stSZ3  0x74(s8)
     6::800a5168 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a516c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a5170 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a5174 10 00 15 97     lhu        s5,0x10(t8)
     6::800a5178 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a517c 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a5180 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a5184 ff ff 93 32     andi       s3,s4,0xffff
     6::800a5188 00 99 13 00     sll        s3,s3,0x4
     6::800a518c 21 98 77 02     addu       s3,s3,s7
     6::800a5190 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a5198 02 a4 14 00     srl        s4,s4,0x10
     6::800a519c 00 a1 14 00     sll        s4,s4,0x4
     6::800a51a0 21 a0 97 02     addu       s4,s4,s7
     6::800a51a4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a51ac 14 00 09 8f     lw         t1,0x14(t8)
     6::800a51b0 00 a9 15 00     sll        s5,s5,0x4
     6::800a51b4 21 a8 b7 02     addu       s5,s5,s7
     6::800a51b8 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a51c0 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a51c4 08 00 08 24     li         t0,0x8
     6::800a51c8 30 00 28 4a     RTPT
     6::800a51cc 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a51d0 08 00 90 8e     lw         s0,0x8(s4)
     6::800a51d4 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a51d8 80 00 cf af     sw         t7,0x80(s8)
     6::800a51dc 94 00 d0 af     sw         s0,0x94(s8)
     6::800a51e0 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a51e4 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a51e8 00 f8 43 48     gte_stFLAG v1
     6::800a51ec 88 00 d1 eb     gte_stSZ1  0x88(s8)
     6::800a51f0 80 1b 03 00     sll        v1,v1,0xe
     6::800a51f4 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a51f8 25 00 60 14     bne        v1,zero,LAB_OVR_226__800a5290
     6::800a51fc 98 00 cd eb     _gte_stS   0x98(s8)
     6::800a5200 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     6::800a5204 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a5208 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     6::800a520c 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a5210 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a5214 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a5218 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a521c a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a5220 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a5224 50 00 03 3c     lui        v1,0x50
     6::800a5228 78 64 63 34     ori        v1,v1,0x6478
     6::800a522c 3b 96 02 0c     jal        FUN_OVR_226__800a58ec                            undefined FUN_OVR_226__800a58ec()
     6::800a5230 00 00 0a 24     _li        t2,0x0
     6::800a5234 14 50 03 3c     lui        v1,0x5014
     6::800a5238 8c 78 63 34     ori        v1,v1,0x788c
     6::800a523c 0d 00 08 24     li         t0,0xd
     6::800a5240 3b 96 02 0c     jal        FUN_OVR_226__800a58ec                            undefined FUN_OVR_226__800a58ec()
     6::800a5244 04 00 0a 24     _li        t2,0x4
     6::800a5248 78 64 03 3c     lui        v1,0x6478
     6::800a524c a0 28 63 34     ori        v1,v1,0x28a0
     6::800a5250 12 00 08 24     li         t0,0x12
     6::800a5254 3b 96 02 0c     jal        FUN_OVR_226__800a58ec                            undefined FUN_OVR_226__800a58ec()
     6::800a5258 08 00 0a 24     _li        t2,0x8
     6::800a525c 8c 78 03 3c     lui        v1,0x788c
     6::800a5260 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a5264 17 00 08 24     li         t0,0x17
     6::800a5268 3b 96 02 0c     jal        FUN_OVR_226__800a58ec                            undefined FUN_OVR_226__800a58ec()
     6::800a526c 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a5270                           XREF[2]:     OVR_226::800a5028(j), 
                                                                                          OVR_226::800a52a0(j)  
     6::800a5270 68 00 39 8c     lw         t9,0x68(at)
     6::800a5274 5c 00 18 27     addiu      t8,t8,0x5c
     6::800a5278 ff ff 39 27     addiu      t9,t9,-0x1
     6::800a527c 5b ff 20 1f     bgtz       t9,LAB_OVR_226__800a4fec
     6::800a5280 68 00 39 ac     _sw        t9,0x68(at)
     6::800a5284 00 00 84 8c     lw         a0,0x0(a0)
     6::800a5288 49 ff 01 04     bgez       zero,LAB_OVR_226__800a4fb0
     6::800a528c 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_226__800a5290                           XREF[3]:     OVR_226::800a50b8(j), 
                                                                                          OVR_226::800a5150(j), 
                                                                                          OVR_226::800a51f8(j)  
     6::800a5290 64 00 28 8c     lw         t0,0x64(at)
     6::800a5294 00 00 00 00     nop
     6::800a5298 00 00 18 ad     sw         t8,0x0(t0)
     6::800a529c 04 00 08 25     addiu      t0,t0,0x4
     6::800a52a0 f3 ff 01 04     bgez       zero,LAB_OVR_226__800a5270
     6::800a52a4 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_226__800a52a8                           XREF[1]:     OVR_226::800a4fb0(j)  
     6::800a52a8 64 00 28 8c     lw         t0,0x64(at)
     6::800a52ac f6 ee 01 04     bgez       zero,LAB_OVR_226__800a0e88
     6::800a52b0 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_226__800a52b4                           XREF[6]:     FUN_OVR_226__800a580c:800a5880(j
                                                                                          FUN_OVR_226__800a580c:800a5888(j
                                                                                          FUN_OVR_226__800a580c:800a58bc(j
                                                                                          OVR_226::800a59c0(j), 
                                                                                          OVR_226::800a59c8(j), 
                                                                                          OVR_226::800a59f4(j)  
     6::800a52b4 08 00 e0 03     jr         ra
     6::800a52b8 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a52bc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a52bc                           XREF[4]:     FUN_OVR_226__800a5348:800a539c(j
                                                                                          FUN_OVR_226__800a5348:800a54c8(c
                                                                                          FUN_OVR_226__800a5348:800a54fc(c
                                                                                          FUN_OVR_226__800a5348:800a5588(c
     6::800a52bc 00 00 d3 27     addiu      s3,s8,0x0
     6::800a52c0 50 00 d4 27     addiu      s4,s8,0x50
     6::800a52c4 64 00 d5 27     addiu      s5,s8,0x64
     6::800a52c8 50 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a52cc 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a52d0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a52d0                           XREF[6]:     FUN_OVR_226__800a5348:800a53e4(c
                                                                                          FUN_OVR_226__800a5348:800a54d8(j
                                                                                          FUN_OVR_226__800a5348:800a54f4(c
                                                                                          FUN_OVR_226__800a5348:800a5530(c
                                                                                          FUN_OVR_226__800a5348:800a555c(c
                                                                                          FUN_OVR_226__800a5348:800a5598(c
     6::800a52d0 50 00 d3 27     addiu      s3,s8,0x50
     6::800a52d4 14 00 d4 27     addiu      s4,s8,0x14
     6::800a52d8 78 00 d5 27     addiu      s5,s8,0x78
     6::800a52dc 4b 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a52e0 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a52e4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a52e4                           XREF[6]:     FUN_OVR_226__800a5348:800a544c(c
                                                                                          FUN_OVR_226__800a5348:800a54c0(c
                                                                                          FUN_OVR_226__800a5348:800a550c(j
                                                                                          FUN_OVR_226__800a5348:800a5528(c
                                                                                          FUN_OVR_226__800a5348:800a5564(c
                                                                                          FUN_OVR_226__800a5348:800a55a8(c
     6::800a52e4 64 00 d3 27     addiu      s3,s8,0x64
     6::800a52e8 78 00 d4 27     addiu      s4,s8,0x78
     6::800a52ec 28 00 d5 27     addiu      s5,s8,0x28
     6::800a52f0 46 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a52f4 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a52f8                           XREF[4]:     OVR_226::800a54a4(j), 
                                                                                          OVR_226::800a5540(j), 
                                                                                          OVR_226::800a5574(j), 
                                                                                          OVR_226::800a55c0(j)  
     6::800a52f8 78 00 d3 27     addiu      s3,s8,0x78
     6::800a52fc 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a5300 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a5304 41 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a5308 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a530c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a530c                           XREF[2]:     FUN_OVR_226__800a5348:800a5444(c
                                                                                          FUN_OVR_226__800a5348:800a5554(c
     6::800a530c 64 00 d3 27     addiu      s3,s8,0x64
     6::800a5310 00 00 d4 27     addiu      s4,s8,0x0
     6::800a5314 78 00 d5 27     addiu      s5,s8,0x78
     6::800a5318 3c 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a531c 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a5320()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a5320                           XREF[2]:     FUN_OVR_226__800a5348:800a545c(j
                                                                                          FUN_OVR_226__800a5348:800a54ec(c
     6::800a5320 14 00 d3 27     addiu      s3,s8,0x14
     6::800a5324 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a5328 78 00 d5 27     addiu      s5,s8,0x78
     6::800a532c 37 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a5330 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a5334()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a5334                           XREF[2]:     FUN_OVR_226__800a5348:800a53ec(c
                                                                                          FUN_OVR_226__800a5348:800a5520(c
     6::800a5334 28 00 d3 27     addiu      s3,s8,0x28
     6::800a5338 00 00 d4 27     addiu      s4,s8,0x0
     6::800a533c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a5340 32 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a5344 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a5348()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a5348                           XREF[2]:     OVR_226::800a53fc(j), 
                                                                                          OVR_226::800a54b8(c)  
     6::800a5348 28 00 d3 27     addiu      s3,s8,0x28
     6::800a534c 78 00 d4 27     addiu      s4,s8,0x78
     6::800a5350 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a5354 2d 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a5358 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a535c 24 03 23 24     addiu      v1,at,0x324
     6::800a5360 12 00 7e 10     beq        v1,s8,LAB_OVR_226__800a53ac
     6::800a5364 50 00 d3 27     _addiu     s3,s8,0x50
     6::800a5368 14 00 d4 27     addiu      s4,s8,0x14
     6::800a536c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a5370 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a5374 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a5378 0c 00 0a 24     _li        t2,0xc
     6::800a537c 64 00 d3 27     addiu      s3,s8,0x64
     6::800a5380 78 00 d4 27     addiu      s4,s8,0x78
     6::800a5384 28 00 d5 27     addiu      s5,s8,0x28
     6::800a5388 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a538c 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a5390 0c 00 0a 24     _li        t2,0xc
     6::800a5394 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5398 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a539c c7 ff 01 04     bgez       zero,FUN_OVR_226__800a52bc
     6::800a53a0 0c 00 0a 24     _li        t2,0xc
     6::800a53a4 24 03 23 24     addiu      v1,at,0x324
     6::800a53a8 0e 00 7e 14     bne        v1,s8,LAB_OVR_226__800a53e4
                             LAB_OVR_226__800a53ac                           XREF[2]:     OVR_226::800a5360(j), 
                                                                                          OVR_226::800a54b0(j)  
     6::800a53ac 00 00 d3 27     addiu      s3,s8,0x0
     6::800a53b0 50 00 d4 27     addiu      s4,s8,0x50
     6::800a53b4 28 00 d5 27     addiu      s5,s8,0x28
     6::800a53b8 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a53bc 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a53c0 0c 00 0a 24     _li        t2,0xc
     6::800a53c4 14 00 d3 27     addiu      s3,s8,0x14
     6::800a53c8 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a53cc 50 00 d5 27     addiu      s5,s8,0x50
     6::800a53d0 28 00 d6 27     addiu      s6,s8,0x28
     6::800a53d4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a53d8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a53dc 0b 01 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a53e0 04 00 0a 24     _li        t2,0x4
                             LAB_OVR_226__800a53e4                           XREF[1]:     OVR_226::800a53a8(j)  
     6::800a53e4 b4 94 02 0c     jal        FUN_OVR_226__800a52d0                            undefined FUN_OVR_226__800a52d0()
     6::800a53e8 0c 00 0a 24     _li        t2,0xc
     6::800a53ec cd 94 02 0c     jal        FUN_OVR_226__800a5334                            undefined FUN_OVR_226__800a5334()
     6::800a53f0 0c 00 0a 24     _li        t2,0xc
     6::800a53f4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a53f8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a53fc d2 ff 01 04     bgez       zero,FUN_OVR_226__800a5348
     6::800a5400 0c 00 0a 24     _li        t2,0xc
     6::800a5404 24 03 23 24     addiu      v1,at,0x324
     6::800a5408 0e 00 7e 14     bne        v1,s8,LAB_OVR_226__800a5444
                             LAB_OVR_226__800a540c                           XREF[2]:     OVR_226::800a5468(j), 
                                                                                          OVR_226::800a554c(j)  
     6::800a540c 14 00 d3 27     _addiu     s3,s8,0x14
     6::800a5410 a0 00 d4 27     addiu      s4,s8,0xa0
     6::800a5414 00 00 d5 27     addiu      s5,s8,0x0
     6::800a5418 28 00 d6 27     addiu      s6,s8,0x28
     6::800a541c 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a5420 0c 00 0a 24     _li        t2,0xc
     6::800a5424 00 00 d3 27     addiu      s3,s8,0x0
     6::800a5428 14 00 d4 27     addiu      s4,s8,0x14
     6::800a542c a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a5430 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a5434 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5438 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a543c f3 00 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a5440 08 00 0a 24     _li        t2,0x8
                             LAB_OVR_226__800a5444                           XREF[1]:     OVR_226::800a5408(j)  
     6::800a5444 c3 94 02 0c     jal        FUN_OVR_226__800a530c                            undefined FUN_OVR_226__800a530c()
     6::800a5448 0c 00 0a 24     _li        t2,0xc
     6::800a544c b9 94 02 0c     jal        FUN_OVR_226__800a52e4                            undefined FUN_OVR_226__800a52e4()
     6::800a5450 0c 00 0a 24     _li        t2,0xc
     6::800a5454 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5458 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a545c b0 ff 01 04     bgez       zero,FUN_OVR_226__800a5320
     6::800a5460 0c 00 0a 24     _li        t2,0xc
     6::800a5464 24 03 23 24     addiu      v1,at,0x324
     6::800a5468 e8 ff 7e 10     beq        v1,s8,LAB_OVR_226__800a540c
     6::800a546c 00 00 d3 27     _addiu     s3,s8,0x0
     6::800a5470 14 00 d4 27     addiu      s4,s8,0x14
     6::800a5474 78 00 d5 27     addiu      s5,s8,0x78
     6::800a5478 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a547c 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a5480 0c 00 0a 24     _li        t2,0xc
     6::800a5484 00 00 d3 27     addiu      s3,s8,0x0
     6::800a5488 78 00 d4 27     addiu      s4,s8,0x78
     6::800a548c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a5490 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a5494 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a5498 0c 00 0a 24     _li        t2,0xc
     6::800a549c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a54a0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a54a4 94 ff 01 04     bgez       zero,LAB_OVR_226__800a52f8
     6::800a54a8 0c 00 0a 24     _li        t2,0xc
     6::800a54ac 24 03 23 24     addiu      v1,at,0x324
     6::800a54b0 be ff 7e 10     beq        v1,s8,LAB_OVR_226__800a53ac
     6::800a54b4 00 00 00 00     _nop
     6::800a54b8 d2 94 02 0c     jal        FUN_OVR_226__800a5348                            undefined FUN_OVR_226__800a5348()
     6::800a54bc 0c 00 0a 24     _li        t2,0xc
     6::800a54c0 b9 94 02 0c     jal        FUN_OVR_226__800a52e4                            undefined FUN_OVR_226__800a52e4()
     6::800a54c4 04 00 0a 24     _li        t2,0x4
     6::800a54c8 af 94 02 0c     jal        FUN_OVR_226__800a52bc                            undefined FUN_OVR_226__800a52bc()
     6::800a54cc 0c 00 0a 24     _li        t2,0xc
     6::800a54d0 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a54d4 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a54d8 7d ff 01 04     bgez       zero,FUN_OVR_226__800a52d0
     6::800a54dc 0c 00 0a 24     _li        t2,0xc
     6::800a54e0 24 03 23 24     addiu      v1,at,0x324
     6::800a54e4 38 00 7e 10     beq        v1,s8,LAB_OVR_226__800a55c8
     6::800a54e8 00 00 00 00     _nop
     6::800a54ec c8 94 02 0c     jal        FUN_OVR_226__800a5320                            undefined FUN_OVR_226__800a5320()
     6::800a54f0 0c 00 0a 24     _li        t2,0xc
     6::800a54f4 b4 94 02 0c     jal        FUN_OVR_226__800a52d0                            undefined FUN_OVR_226__800a52d0()
     6::800a54f8 04 00 0a 24     _li        t2,0x4
     6::800a54fc af 94 02 0c     jal        FUN_OVR_226__800a52bc                            undefined FUN_OVR_226__800a52bc()
     6::800a5500 0c 00 0a 24     _li        t2,0xc
     6::800a5504 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5508 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a550c 75 ff 01 04     bgez       zero,FUN_OVR_226__800a52e4
     6::800a5510 0c 00 0a 24     _li        t2,0xc
     6::800a5514 24 03 23 24     addiu      v1,at,0x324
     6::800a5518 2b 00 7e 10     beq        v1,s8,LAB_OVR_226__800a55c8
     6::800a551c 00 00 00 00     _nop
     6::800a5520 cd 94 02 0c     jal        FUN_OVR_226__800a5334                            undefined FUN_OVR_226__800a5334()
     6::800a5524 0c 00 0a 24     _li        t2,0xc
     6::800a5528 b9 94 02 0c     jal        FUN_OVR_226__800a52e4                            undefined FUN_OVR_226__800a52e4()
     6::800a552c 08 00 0a 24     _li        t2,0x8
     6::800a5530 b4 94 02 0c     jal        FUN_OVR_226__800a52d0                            undefined FUN_OVR_226__800a52d0()
     6::800a5534 0c 00 0a 24     _li        t2,0xc
     6::800a5538 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a553c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a5540 6d ff 01 04     bgez       zero,LAB_OVR_226__800a52f8
     6::800a5544 0c 00 0a 24     _li        t2,0xc
     6::800a5548 24 03 23 24     addiu      v1,at,0x324
     6::800a554c af ff 7e 10     beq        v1,s8,LAB_OVR_226__800a540c
     6::800a5550 00 00 00 00     _nop
     6::800a5554 c3 94 02 0c     jal        FUN_OVR_226__800a530c                            undefined FUN_OVR_226__800a530c()
     6::800a5558 0c 00 0a 24     _li        t2,0xc
     6::800a555c b4 94 02 0c     jal        FUN_OVR_226__800a52d0                            undefined FUN_OVR_226__800a52d0()
     6::800a5560 08 00 0a 24     _li        t2,0x8
     6::800a5564 b9 94 02 0c     jal        FUN_OVR_226__800a52e4                            undefined FUN_OVR_226__800a52e4()
     6::800a5568 0c 00 0a 24     _li        t2,0xc
     6::800a556c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5570 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a5574 60 ff 01 04     bgez       zero,LAB_OVR_226__800a52f8
     6::800a5578 0c 00 0a 24     _li        t2,0xc
     6::800a557c 24 03 23 24     addiu      v1,at,0x324
     6::800a5580 11 00 7e 10     beq        v1,s8,LAB_OVR_226__800a55c8
     6::800a5584 b4 00 c0 af     _sw        zero,0xb4(s8)
     6::800a5588 af 94 02 0c     jal        FUN_OVR_226__800a52bc                            undefined FUN_OVR_226__800a52bc()
     6::800a558c 0c 00 0a 24     _li        t2,0xc
     6::800a5590 0c 00 03 24     li         v1,0xc
     6::800a5594 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a5598 b4 94 02 0c     jal        FUN_OVR_226__800a52d0                            undefined FUN_OVR_226__800a52d0()
     6::800a559c 0c 00 0a 24     _li        t2,0xc
     6::800a55a0 18 00 03 24     li         v1,0x18
     6::800a55a4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a55a8 b9 94 02 0c     jal        FUN_OVR_226__800a52e4                            undefined FUN_OVR_226__800a52e4()
     6::800a55ac 0c 00 0a 24     _li        t2,0xc
     6::800a55b0 24 00 03 24     li         v1,0x24
     6::800a55b4 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a55b8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a55bc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a55c0 4d ff 01 04     bgez       zero,LAB_OVR_226__800a52f8
     6::800a55c4 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a55c8                           XREF[3]:     OVR_226::800a54e4(j), 
                                                                                          OVR_226::800a5518(j), 
                                                                                          OVR_226::800a5580(j)  
     6::800a55c8 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a55cc 00 00 d3 27     addiu      s3,s8,0x0
     6::800a55d0 50 00 d4 27     addiu      s4,s8,0x50
     6::800a55d4 28 00 d5 27     addiu      s5,s8,0x28
     6::800a55d8 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a55dc 03 96 02 0c     jal        FUN_OVR_226__800a580c                            undefined FUN_OVR_226__800a580c()
     6::800a55e0 0c 00 0a 24     _li        t2,0xc
     6::800a55e4 0c 00 03 24     li         v1,0xc
     6::800a55e8 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a55ec 50 00 d3 27     addiu      s3,s8,0x50
     6::800a55f0 14 00 d4 27     addiu      s4,s8,0x14
     6::800a55f4 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a55f8 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a55fc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5600 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a5604 81 00 01 04     bgez       zero,FUN_OVR_226__800a580c
     6::800a5608 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a560c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a560c                           XREF[3]:     FUN_OVR_226__800a58ec:800a5bb8(c
                                                                                          FUN_OVR_226__800a58ec:800a5bcc(c
                                                                                          FUN_OVR_226__800a58ec:800a5be0(c
     6::800a560c 00 00 ab 85     lh         t3,0x0(t5)
     6::800a5610 00 00 cc 85     lh         t4,0x0(t6)
     6::800a5614 00 00 eb a5     sh         t3,0x0(t7)
     6::800a5618 21 18 6c 01     addu       v1,t3,t4
     6::800a561c 43 18 03 00     sra        v1,v1,0x1
     6::800a5620 00 00 03 a6     sh         v1,0x0(s0)
     6::800a5624 02 00 ab 85     lh         t3,0x2(t5)
     6::800a5628 02 00 cc 85     lh         t4,0x2(t6)
     6::800a562c 02 00 eb a5     sh         t3,0x2(t7)
     6::800a5630 21 18 6c 01     addu       v1,t3,t4
     6::800a5634 43 18 03 00     sra        v1,v1,0x1
     6::800a5638 02 00 03 a6     sh         v1,0x2(s0)
     6::800a563c 04 00 ab 85     lh         t3,0x4(t5)
     6::800a5640 04 00 cc 85     lh         t4,0x4(t6)
     6::800a5644 04 00 eb a5     sh         t3,0x4(t7)
     6::800a5648 21 18 6c 01     addu       v1,t3,t4
     6::800a564c 43 18 03 00     sra        v1,v1,0x1
     6::800a5650 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a5654 00 08 83 48     gte_ldVZ0  v1
     6::800a5658 04 00 03 a6     sh         v1,0x4(s0)
     6::800a565c 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a5660 01 00 18 4a     RTPS
     6::800a5664 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a5668 08 00 eb a1     sb         t3,0x8(t7)
     6::800a566c 21 18 6c 01     addu       v1,t3,t4
     6::800a5670 43 18 03 00     sra        v1,v1,0x1
     6::800a5674 08 00 03 a2     sb         v1,0x8(s0)
     6::800a5678 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a567c 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a5680 09 00 eb a1     sb         t3,0x9(t7)
     6::800a5684 21 18 6c 01     addu       v1,t3,t4
     6::800a5688 43 18 03 00     sra        v1,v1,0x1
     6::800a568c 09 00 03 a2     sb         v1,0x9(s0)
     6::800a5690 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a5694 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a5698 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a569c 21 18 6c 01     addu       v1,t3,t4
     6::800a56a0 43 18 03 00     sra        v1,v1,0x1
     6::800a56a4 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a56a8 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a56ac 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a56b0 06 00 eb a1     sb         t3,0x6(t7)
     6::800a56b4 21 18 6c 01     addu       v1,t3,t4
     6::800a56b8 43 18 03 00     sra        v1,v1,0x1
     6::800a56bc 06 00 03 a2     sb         v1,0x6(s0)
     6::800a56c0 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a56c4 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a56c8 07 00 eb a1     sb         t3,0x7(t7)
     6::800a56cc 21 18 6c 01     addu       v1,t3,t4
     6::800a56d0 43 18 03 00     sra        v1,v1,0x1
     6::800a56d4 07 00 03 a2     sb         v1,0x7(s0)
     6::800a56d8 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a56dc 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a56e0 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a56e4 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a56e8 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a56ec 08 00 e0 03     jr         ra
     6::800a56f0 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a56f4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a56f4                           XREF[2]:     FUN_OVR_226__800a58ec:800a5b84(c
                                                                                          FUN_OVR_226__800a58ec:800a5b9c(c
     6::800a56f4 00 00 ab 85     lh         t3,0x0(t5)
     6::800a56f8 00 00 cc 85     lh         t4,0x0(t6)
     6::800a56fc 00 00 eb a5     sh         t3,0x0(t7)
     6::800a5700 00 00 0c a6     sh         t4,0x0(s0)
     6::800a5704 21 18 6c 01     addu       v1,t3,t4
     6::800a5708 43 18 03 00     sra        v1,v1,0x1
     6::800a570c 00 00 43 a6     sh         v1,0x0(s2)
     6::800a5710 02 00 ab 85     lh         t3,0x2(t5)
     6::800a5714 02 00 cc 85     lh         t4,0x2(t6)
     6::800a5718 02 00 eb a5     sh         t3,0x2(t7)
     6::800a571c 02 00 0c a6     sh         t4,0x2(s0)
     6::800a5720 21 18 6c 01     addu       v1,t3,t4
     6::800a5724 43 18 03 00     sra        v1,v1,0x1
     6::800a5728 02 00 43 a6     sh         v1,0x2(s2)
     6::800a572c 04 00 ab 85     lh         t3,0x4(t5)
     6::800a5730 04 00 cc 85     lh         t4,0x4(t6)
     6::800a5734 04 00 eb a5     sh         t3,0x4(t7)
     6::800a5738 04 00 0c a6     sh         t4,0x4(s0)
     6::800a573c 21 18 6c 01     addu       v1,t3,t4
     6::800a5740 43 18 03 00     sra        v1,v1,0x1
     6::800a5744 00 00 40 ca     gte_ldVXY0 0x0(s2)
     6::800a5748 00 08 83 48     gte_ldVZ0  v1
     6::800a574c 04 00 43 a6     sh         v1,0x4(s2)
     6::800a5750 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a5754 01 00 18 4a     RTPS
     6::800a5758 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a575c 08 00 eb a1     sb         t3,0x8(t7)
     6::800a5760 08 00 0c a2     sb         t4,0x8(s0)
     6::800a5764 21 18 6c 01     addu       v1,t3,t4
     6::800a5768 43 18 03 00     sra        v1,v1,0x1
     6::800a576c 08 00 43 a2     sb         v1,0x8(s2)
     6::800a5770 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a5774 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a5778 09 00 eb a1     sb         t3,0x9(t7)
     6::800a577c 09 00 0c a2     sb         t4,0x9(s0)
     6::800a5780 21 18 6c 01     addu       v1,t3,t4
     6::800a5784 43 18 03 00     sra        v1,v1,0x1
     6::800a5788 09 00 43 a2     sb         v1,0x9(s2)
     6::800a578c 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a5790 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a5794 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a5798 0a 00 0c a2     sb         t4,0xa(s0)
     6::800a579c 21 18 6c 01     addu       v1,t3,t4
     6::800a57a0 43 18 03 00     sra        v1,v1,0x1
     6::800a57a4 0a 00 43 a2     sb         v1,0xa(s2)
     6::800a57a8 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a57ac 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a57b0 06 00 eb a1     sb         t3,0x6(t7)
     6::800a57b4 06 00 0c a2     sb         t4,0x6(s0)
     6::800a57b8 21 18 6c 01     addu       v1,t3,t4
     6::800a57bc 43 18 03 00     sra        v1,v1,0x1
     6::800a57c0 06 00 43 a2     sb         v1,0x6(s2)
     6::800a57c4 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a57c8 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a57cc 07 00 eb a1     sb         t3,0x7(t7)
     6::800a57d0 07 00 0c a2     sb         t4,0x7(s0)
     6::800a57d4 21 18 6c 01     addu       v1,t3,t4
     6::800a57d8 43 18 03 00     sra        v1,v1,0x1
     6::800a57dc 07 00 43 a2     sb         v1,0x7(s2)
     6::800a57e0 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a57e4 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a57e8 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a57ec 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a57f0 0c 00 c3 8d     lw         v1,0xc(t6)
     6::800a57f4 10 00 c8 8d     lw         t0,0x10(t6)
     6::800a57f8 0c 00 03 ae     sw         v1,0xc(s0)
     6::800a57fc 10 00 08 ae     sw         t0,0x10(s0)
     6::800a5800 0c 00 4e ea     gte_stSXY2 0xc(s2)
     6::800a5804 08 00 e0 03     jr         ra
     6::800a5808 10 00 53 ea     _gte_stSZ3 0x10(s2)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a580c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a580c                           XREF[18]:    FUN_OVR_226__800a52bc:800a52c8(j
                                                                                          FUN_OVR_226__800a52d0:800a52dc(j
                                                                                          FUN_OVR_226__800a52e4:800a52f0(j
                                                                                          FUN_OVR_226__800a5348:800a5304(j
                                                                                          FUN_OVR_226__800a530c:800a5318(j
                                                                                          FUN_OVR_226__800a5320:800a532c(j
                                                                                          FUN_OVR_226__800a5334:800a5340(j
                                                                                          FUN_OVR_226__800a5348:800a5354(j
                                                                                          FUN_OVR_226__800a5348:800a5374(c
                                                                                          FUN_OVR_226__800a5348:800a538c(c
                                                                                          FUN_OVR_226__800a5348:800a53bc(c
                                                                                          FUN_OVR_226__800a5348:800a53dc(j
                                                                                          FUN_OVR_226__800a5348:800a541c(c
                                                                                          FUN_OVR_226__800a5348:800a543c(j
                                                                                          FUN_OVR_226__800a5348:800a547c(c
                                                                                          FUN_OVR_226__800a5348:800a5494(c
                                                                                          FUN_OVR_226__800a5348:800a55dc(c
                                                                                          FUN_OVR_226__800a5348:800a5604(j
     6::800a580c 70 00 2a ac     sw         t2,0x70(at)
     6::800a5810 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a5814 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a5818 94 01 2a 8c     lw         t2,0x194(at)
     6::800a581c 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a5820 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a5824 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a5828 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a582c 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a5830 06 00 40 4b     NCLIP
     6::800a5834 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a5838 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a583c 23 78 68 01     subu       t7,t3,t0
     6::800a5840 23 80 88 01     subu       s0,t4,t0
     6::800a5844 23 88 a8 01     subu       s1,t5,t0
     6::800a5848 23 90 c8 01     subu       s2,t6,t0
     6::800a584c 00 c0 08 48     gte_stMAC0 t0
     6::800a5850 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a5854 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a5860
     6::800a5858 22 40 08 00     _sub       t0,zero,t0
     6::800a585c 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a5860                           XREF[1]:     OVR_226::800a5854(j)  
     6::800a5860 06 00 40 4b     NCLIP
     6::800a5864 24 18 6c 01     and        v1,t3,t4
     6::800a5868 24 18 6d 00     and        v1,v1,t5
     6::800a586c 24 18 6e 00     and        v1,v1,t6
     6::800a5870 25 78 f0 01     or         t7,t7,s0
     6::800a5874 25 78 f1 01     or         t7,t7,s1
     6::800a5878 27 78 f2 01     nor        t7,t7,s2
     6::800a587c 25 78 e3 01     or         t7,t7,v1
     6::800a5880 8c fe e0 05     bltz       t7,LAB_OVR_226__800a52b4
     6::800a5884 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a5888 8a fe e0 05     bltz       t7,LAB_OVR_226__800a52b4
     6::800a588c 00 c0 03 48     _gte_stM   v1
     6::800a5890 25 40 09 01     or         t0,t0,t1
     6::800a5894 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a58a0
     6::800a5898 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a589c 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a58a0                           XREF[1]:     OVR_226::800a5894(j)  
     6::800a58a0 80 40 08 00     sll        t0,t0,0x2
     6::800a58a4 25 18 69 00     or         v1,v1,t1
     6::800a58a8 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a58ac c0 18 03 00     sll        v1,v1,0x3
     6::800a58b0 70 00 2a 8c     lw         t2,0x70(at)
     6::800a58b4 25 18 68 00     or         v1,v1,t0
     6::800a58b8 24 18 6a 00     and        v1,v1,t2
     6::800a58bc 7d fe 60 10     beq        v1,zero,LAB_OVR_226__800a52b4
     6::800a58c0 70 00 23 ac     _sw        v1,0x70(at)
     6::800a58c4 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a58c8 24 03 23 24     addiu      v1,at,0x324
     6::800a58cc e1 00 7e 10     beq        v1,s8,LAB_OVR_226__800a5c54
     6::800a58d0 04 00 39 27     _addiu     t9,t9,0x4
     6::800a58d4 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a58d8 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a58dc 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a58e0 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a58e4 91 00 01 04     bgez       zero,LAB_OVR_226__800a5b2c
     6::800a58e8 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a58ec()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a58ec                           XREF[4]:     OVR_226::800a522c(c), 
                                                                                          OVR_226::800a5240(c), 
                                                                                          OVR_226::800a5254(c), 
                                                                                          OVR_226::800a5268(c)  
     6::800a58ec 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a58f0 b4 00 ca af     sw         t2,0xb4(s8)
     6::800a58f4 06 50 09 01     srlv       t2,t1,t0
     6::800a58f8 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a58fc 80 50 0a 00     sll        t2,t2,0x2
     6::800a5900 21 50 41 01     addu       t2,t2,at
     6::800a5904 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a5908 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a590c 94 01 2a ac     sw         t2,0x194(at)
     6::800a5910 02 9e 0a 00     srl        s3,t2,0x18
     6::800a5914 1f 00 73 32     andi       s3,s3,0x1f
     6::800a5918 06 98 63 02     srlv       s3,v1,s3
     6::800a591c ff 00 73 32     andi       s3,s3,0xff
     6::800a5920 21 98 7e 02     addu       s3,s3,s8
     6::800a5924 02 a4 0a 00     srl        s4,t2,0x10
     6::800a5928 1f 00 94 32     andi       s4,s4,0x1f
     6::800a592c 06 a0 83 02     srlv       s4,v1,s4
     6::800a5930 ff 00 94 32     andi       s4,s4,0xff
     6::800a5934 21 a0 9e 02     addu       s4,s4,s8
     6::800a5938 02 aa 0a 00     srl        s5,t2,0x8
     6::800a593c 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a5940 06 a8 a3 02     srlv       s5,v1,s5
     6::800a5944 ff 00 b5 32     andi       s5,s5,0xff
     6::800a5948 21 a8 be 02     addu       s5,s5,s8
     6::800a594c 1f 00 56 31     andi       s6,t2,0x1f
     6::800a5950 06 b0 c3 02     srlv       s6,v1,s6
     6::800a5954 ff 00 d6 32     andi       s6,s6,0xff
     6::800a5958 21 b0 de 02     addu       s6,s6,s8
     6::800a595c 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a5960 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a5964 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a5968 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a596c 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a5970 06 00 40 4b     NCLIP
     6::800a5974 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a5978 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a597c 23 78 68 01     subu       t7,t3,t0
     6::800a5980 23 80 88 01     subu       s0,t4,t0
     6::800a5984 23 88 a8 01     subu       s1,t5,t0
     6::800a5988 23 90 c8 01     subu       s2,t6,t0
     6::800a598c 00 c0 08 48     gte_stMAC0 t0
     6::800a5990 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a5994 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a59a0
     6::800a5998 22 40 08 00     _sub       t0,zero,t0
     6::800a599c 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a59a0                           XREF[1]:     OVR_226::800a5994(j)  
     6::800a59a0 06 00 40 4b     NCLIP
     6::800a59a4 24 18 6c 01     and        v1,t3,t4
     6::800a59a8 24 18 6d 00     and        v1,v1,t5
     6::800a59ac 24 18 6e 00     and        v1,v1,t6
     6::800a59b0 25 78 f0 01     or         t7,t7,s0
     6::800a59b4 25 78 f1 01     or         t7,t7,s1
     6::800a59b8 27 78 f2 01     nor        t7,t7,s2
     6::800a59bc 25 78 e3 01     or         t7,t7,v1
     6::800a59c0 3c fe e0 05     bltz       t7,LAB_OVR_226__800a52b4
     6::800a59c4 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a59c8 3a fe e0 05     bltz       t7,LAB_OVR_226__800a52b4
     6::800a59cc 00 c0 03 48     _gte_stM   v1
     6::800a59d0 25 40 09 01     or         t0,t0,t1
     6::800a59d4 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a59e0
     6::800a59d8 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a59dc 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a59e0                           XREF[1]:     OVR_226::800a59d4(j)  
     6::800a59e0 80 40 08 00     sll        t0,t0,0x2
     6::800a59e4 25 18 69 00     or         v1,v1,t1
     6::800a59e8 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a59ec c0 18 03 00     sll        v1,v1,0x3
     6::800a59f0 25 18 68 00     or         v1,v1,t0
     6::800a59f4 2f fe 60 10     beq        v1,zero,LAB_OVR_226__800a52b4
     6::800a59f8 70 00 23 ac     _sw        v1,0x70(at)
     6::800a59fc 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a5a00 04 00 39 27     addiu      t9,t9,0x4
     6::800a5a04 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a5a08 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a5a0c 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a5a10 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a5a14 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a5a18 23 50 6c 01     subu       t2,t3,t4
     6::800a5a1c 82 48 03 00     srl        t1,v1,0x2
     6::800a5a20 21 48 38 01     addu       t1,t1,t8
     6::800a5a24 18 00 29 81     lb         t1,0x18(t1)
     6::800a5a28 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a5a34
     6::800a5a2c 21 e0 60 01     _move      gp,t3
     6::800a5a30 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a5a34                           XREF[1]:     OVR_226::800a5a28(j)  
     6::800a5a34 23 50 8d 03     subu       t2,gp,t5
     6::800a5a38 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a5a44
     6::800a5a3c 21 18 78 00     _addu      v1,v1,t8
     6::800a5a40 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a5a44                           XREF[1]:     OVR_226::800a5a38(j)  
     6::800a5a44 23 50 8e 03     subu       t2,gp,t6
     6::800a5a48 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a5a54
     6::800a5a4c 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a5a50 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a5a54                           XREF[1]:     OVR_226::800a5a48(j)  
     6::800a5a54 21 50 80 03     move       t2,gp
     6::800a5a58 82 e1 1c 00     srl        gp,gp,0x6
     6::800a5a5c 21 e0 89 03     addu       gp,gp,t1
     6::800a5a60 01 00 69 30     andi       t1,v1,0x1
     6::800a5a64 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a5a70
     6::800a5a68 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a5a6c ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a5a70                           XREF[1]:     OVR_226::800a5a64(j)  
     6::800a5a70 02 00 81 07     bgez       gp,LAB_OVR_226__800a5a7c
     6::800a5a74 21 e0 85 03     _addu      gp,gp,a1
     6::800a5a78 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a5a7c                           XREF[1]:     OVR_226::800a5a70(j)  
     6::800a5a7c 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a5a80 24 00 69 8c     lw         t1,0x24(v1)
     6::800a5a84 23 40 48 01     subu       t0,t2,t0
     6::800a5a88 84 00 29 ac     sw         t1,0x84(at)
     6::800a5a8c 0c 00 01 05     bgez       t0,LAB_OVR_226__800a5ac0
     6::800a5a90 20 00 28 8c     _lw        t0,0x20(at)
     6::800a5a94 0c 00 63 24     addiu      v1,v1,0xc
     6::800a5a98 23 40 48 01     subu       t0,t2,t0
     6::800a5a9c 08 00 01 05     bgez       t0,LAB_OVR_226__800a5ac0
     6::800a5aa0 24 00 28 8c     _lw        t0,0x24(at)
     6::800a5aa4 0c 00 63 24     addiu      v1,v1,0xc
     6::800a5aa8 23 40 48 01     subu       t0,t2,t0
     6::800a5aac 04 00 01 05     bgez       t0,LAB_OVR_226__800a5ac0
     6::800a5ab0 00 00 00 00     _nop
     6::800a5ab4 02 00 20 05     bltz       t1,LAB_OVR_226__800a5ac0
     6::800a5ab8 00 00 00 00     _nop
     6::800a5abc 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a5ac0                           XREF[4]:     OVR_226::800a5a8c(j), 
                                                                                          OVR_226::800a5a9c(j), 
                                                                                          OVR_226::800a5aac(j), 
                                                                                          OVR_226::800a5ab4(j)  
     6::800a5ac0 94 01 2a 8c     lw         t2,0x194(at)
     6::800a5ac4 00 00 68 8c     lw         t0,0x0(v1)
     6::800a5ac8 04 00 69 8c     lw         t1,0x4(v1)
     6::800a5acc a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a5ad0 ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a5ad4 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a5ad8 00 52 0a 00     sll        t2,t2,0x8
     6::800a5adc 0a 00 40 05     bltz       t2,LAB_OVR_226__800a5b08
     6::800a5ae0 b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a5ae4 06 00 68 a6     sh         t0,0x6(s3)
     6::800a5ae8 08 00 68 8c     lw         t0,0x8(v1)
     6::800a5aec 06 00 89 a6     sh         t1,0x6(s4)
     6::800a5af0 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a5af4 00 54 0a 00     sll        t2,t2,0x10
     6::800a5af8 0b 00 40 05     bltz       t2,LAB_OVR_226__800a5b28
     6::800a5afc 02 4c 08 00     _srl       t1,t0,0x10
     6::800a5b00 09 00 01 04     bgez       zero,LAB_OVR_226__800a5b28
     6::800a5b04 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a5b08                           XREF[1]:     OVR_226::800a5adc(j)  
     6::800a5b08 06 00 69 a6     sh         t1,0x6(s3)
     6::800a5b0c 08 00 69 8c     lw         t1,0x8(v1)
     6::800a5b10 00 54 0a 00     sll        t2,t2,0x10
     6::800a5b14 06 00 88 a6     sh         t0,0x6(s4)
     6::800a5b18 02 44 09 00     srl        t0,t1,0x10
     6::800a5b1c 02 00 40 05     bltz       t2,LAB_OVR_226__800a5b28
     6::800a5b20 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a5b24 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a5b28                           XREF[3]:     OVR_226::800a5af8(j), 
                                                                                          OVR_226::800a5b00(j), 
                                                                                          OVR_226::800a5b1c(j)  
     6::800a5b28 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a5b2c                           XREF[1]:     FUN_OVR_226__800a580c:800a58e4(j
     6::800a5b2c 00 00 00 00     nop
     6::800a5b30 23 88 63 01     subu       s1,t3,v1
     6::800a5b34 23 90 83 01     subu       s2,t4,v1
     6::800a5b38 23 78 a3 01     subu       t7,t5,v1
     6::800a5b3c 23 80 c3 01     subu       s0,t6,v1
     6::800a5b40 42 8f 11 00     srl        s1,s1,0x1d
     6::800a5b44 04 00 31 32     andi       s1,s1,0x4
     6::800a5b48 02 97 12 00     srl        s2,s2,0x1c
     6::800a5b4c 08 00 52 32     andi       s2,s2,0x8
     6::800a5b50 25 88 32 02     or         s1,s1,s2
     6::800a5b54 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a5b58 10 00 ef 31     andi       t7,t7,0x10
     6::800a5b5c 25 88 2f 02     or         s1,s1,t7
     6::800a5b60 82 86 10 00     srl        s0,s0,0x1a
     6::800a5b64 20 00 10 32     andi       s0,s0,0x20
     6::800a5b68 25 88 30 02     or         s1,s1,s0
     6::800a5b6c 32 00 20 12     beq        s1,zero,LAB_OVR_226__800a5c38
     6::800a5b70 21 68 60 02     _move      t5,s3
     6::800a5b74 21 70 80 02     move       t6,s4
     6::800a5b78 b8 00 de 27     addiu      s8,s8,0xb8
     6::800a5b7c 00 00 cf 27     addiu      t7,s8,0x0
     6::800a5b80 14 00 d0 27     addiu      s0,s8,0x14
     6::800a5b84 bd 95 02 0c     jal        FUN_OVR_226__800a56f4                            undefined FUN_OVR_226__800a56f4()
     6::800a5b88 50 00 d2 27     _addiu     s2,s8,0x50
     6::800a5b8c 21 68 a0 02     move       t5,s5
     6::800a5b90 21 70 c0 02     move       t6,s6
     6::800a5b94 28 00 cf 27     addiu      t7,s8,0x28
     6::800a5b98 3c 00 d0 27     addiu      s0,s8,0x3c
     6::800a5b9c bd 95 02 0c     jal        FUN_OVR_226__800a56f4                            undefined FUN_OVR_226__800a56f4()
     6::800a5ba0 a0 00 d2 27     _addiu     s2,s8,0xa0
     6::800a5ba4 24 03 23 24     addiu      v1,at,0x324
     6::800a5ba8 17 00 7e 10     beq        v1,s8,LAB_OVR_226__800a5c08
     6::800a5bac 21 68 a0 02     _move      t5,s5
     6::800a5bb0 21 70 60 02     move       t6,s3
     6::800a5bb4 28 00 cf 27     addiu      t7,s8,0x28
     6::800a5bb8 83 95 02 0c     jal        FUN_OVR_226__800a560c                            undefined FUN_OVR_226__800a560c()
     6::800a5bbc 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a5bc0 21 68 80 02     move       t5,s4
     6::800a5bc4 21 70 a0 02     move       t6,s5
     6::800a5bc8 14 00 cf 27     addiu      t7,s8,0x14
     6::800a5bcc 83 95 02 0c     jal        FUN_OVR_226__800a560c                            undefined FUN_OVR_226__800a560c()
     6::800a5bd0 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a5bd4 21 68 c0 02     move       t5,s6
     6::800a5bd8 21 70 80 02     move       t6,s4
     6::800a5bdc 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a5be0 83 95 02 0c     jal        FUN_OVR_226__800a560c                            undefined FUN_OVR_226__800a560c()
     6::800a5be4 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a5be8 21 18 21 02     addu       v1,s1,at
     6::800a5bec 48 01 63 8c     lw         v1,0x148(v1)
     6::800a5bf0 0a 80 08 3c     lui        t0,0x800a
     6::800a5bf4 28 5c 08 25     addiu      t0,t0,0x5c28
     6::800a5bf8 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a5bfc 3c 00 28 af     sw         t0=>LAB_OVR_226__800a5c28,0x3c(t9)
     6::800a5c00 08 00 60 00     jr         v1
     6::800a5c04 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a5c08                           XREF[1]:     OVR_226::800a5ba8(j)  
     6::800a5c08 21 18 21 02     addu       v1,s1,at
     6::800a5c0c 48 01 63 8c     lw         v1,0x148(v1)
     6::800a5c10 0a 80 08 3c     lui        t0,0x800a
     6::800a5c14 28 5c 08 25     addiu      t0,t0,0x5c28
     6::800a5c18 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a5c1c 3c 00 28 af     sw         t0=>LAB_OVR_226__800a5c28,0x3c(t9)
     6::800a5c20 08 00 60 00     jr         v1
     6::800a5c24 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a5c28                           XREF[2]:     FUN_OVR_226__800a58ec:800a5bfc(*
                                                                                          FUN_OVR_226__800a58ec:800a5c1c(*
     6::800a5c28 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a5c2c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a5c30 08 00 e0 03     jr         ra
     6::800a5c34 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a5c38                           XREF[1]:     OVR_226::800a5b6c(j)  
     6::800a5c38 70 00 23 8c     lw         v1,0x70(at)
     6::800a5c3c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a5c40 21 18 61 00     addu       v1,v1,at
     6::800a5c44 84 01 63 8c     lw         v1,0x184(v1)
     6::800a5c48 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a5c4c 08 00 60 00     jr         v1
     6::800a5c50 00 00 00 00     _nop
                             LAB_OVR_226__800a5c54                           XREF[1]:     OVR_226::800a58cc(j)  
     6::800a5c54 84 00 23 8c     lw         v1,0x84(at)
     6::800a5c58 24 03 2a 24     addiu      t2,at,0x324
     6::800a5c5c 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a5cf8
     6::800a5c60 20 03 28 8c     _lw        t0,0x320(at)
     6::800a5c64 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a5c68 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a5cc4
     6::800a5c6c 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a5c70 0a 80 0a 3c     lui        t2,0x800a
     6::800a5c74 7c 55 4a 25     addiu      t2,t2,0x557c
     6::800a5c78 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a5cf8
     6::800a5c7c 94 01 23 8c     _lw        v1,0x194(at)
     6::800a5c80 40 40 08 00     sll        t0,t0,0x1
     6::800a5c84 00 1a 03 00     sll        v1,v1,0x8
     6::800a5c88 02 00 61 04     bgez       v1,LAB_OVR_226__800a5c94
     6::800a5c8c 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a5c90 60 00 08 25     addiu      t0,t0,0x60
                             LAB_OVR_226__800a5c94                           XREF[1]:     OVR_226::800a5c88(j)  
     6::800a5c94 21 40 09 01     addu       t0,t0,t1
     6::800a5c98 21 50 48 01     addu       t2,t2,t0
     6::800a5c9c 00 00 48 8d     lw         t0,0x0(t2)
     6::800a5ca0 04 00 49 8d     lw         t1,0x4(t2)
     6::800a5ca4 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a5ca8 06 00 68 a6     sh         t0,0x6(s3)
     6::800a5cac 08 00 48 85     lh         t0,0x8(t2)
     6::800a5cb0 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a5cb4 06 00 89 a6     sh         t1,0x6(s4)
     6::800a5cb8 0a 00 49 85     lh         t1,0xa(t2)
     6::800a5cbc 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a5cc0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a5cc4                           XREF[2]:     OVR_226::800a5c68(j), 
                                                                                          OVR_226::800a5d04(j)  
     6::800a5cc4 70 00 23 8c     lw         v1,0x70(at)
     6::800a5cc8 00 00 00 00     nop
     6::800a5ccc 21 18 61 00     addu       v1,v1,at
     6::800a5cd0 84 01 63 8c     lw         v1,0x184(v1)
     6::800a5cd4 00 00 00 00     nop
     6::800a5cd8 09 f8 60 00     jalr       v1
     6::800a5cdc fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a5ce0 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a5ce4 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a5ce8 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a5cec a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a5cf0 08 00 e0 03     jr         ra
     6::800a5cf4 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a5cf8                           XREF[2]:     OVR_226::800a5c5c(j), 
                                                                                          OVR_226::800a5c78(j)  
     6::800a5cf8 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a5cfc b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a5d00 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a5d04 ef ff 01 04     bgez       zero,LAB_OVR_226__800a5cc4
     6::800a5d08 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a5d0c 21 98 80 02     move       s3,s4
     6::800a5d10 21 a0 c0 02     move       s4,s6
     6::800a5d14 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a5d18 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a5d1c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a5d20 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a5d24 08 00 90 8e     lw         s0,0x8(s4)
     6::800a5d28 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a5d2c 06 00 73 86     lh         s3,0x6(s3)
     6::800a5d30 06 00 94 86     lh         s4,0x6(s4)
     6::800a5d34 06 00 b5 86     lh         s5,0x6(s5)
     6::800a5d38 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a5d3c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a5d40 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a5d44 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a5d48 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a5d4c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a5d50 60 00 03 3c     lui        v1,0x60
     6::800a5d54 24 48 83 02     and        t1,s4,v1
     6::800a5d58 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a5d64
     6::800a5d5c 00 36 03 3c     _lui       v1,0x3600
     6::800a5d60 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a5d64                           XREF[1]:     OVR_226::800a5d58(j)  
     6::800a5d64 25 18 6f 00     or         v1,v1,t7
     6::800a5d68 04 00 43 ac     sw         v1,0x4(v0)
     6::800a5d6c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a5d70 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a5d74 10 00 50 ac     sw         s0,0x10(v0)
     6::800a5d78 14 00 4c ac     sw         t4,0x14(v0)
     6::800a5d7c 18 00 54 ac     sw         s4,0x18(v0)
     6::800a5d80 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a5d84 20 00 4d ac     sw         t5,0x20(v0)
     6::800a5d88 24 00 55 ac     sw         s5,0x24(v0)
     6::800a5d8c 28 00 09 24     li         t1,0x28
     6::800a5d90 29 00 01 04     bgez       zero,LAB_OVR_226__800a5e38
     6::800a5d94 00 09 0a 3c     _lui       t2,0x900
     6::800a5d98 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a5d9c 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a5da0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a5da4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a5da8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a5dac 08 00 90 8e     lw         s0,0x8(s4)
     6::800a5db0 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a5db4 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a5db8 06 00 73 86     lh         s3,0x6(s3)
     6::800a5dbc 06 00 94 86     lh         s4,0x6(s4)
     6::800a5dc0 06 00 b5 86     lh         s5,0x6(s5)
     6::800a5dc4 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a5dc8 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a5dcc 06 00 d4 86     lh         s4,0x6(s6)
     6::800a5dd0 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a5dd4 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a5dd8 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a5ddc a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a5de0 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a5de4 60 00 03 3c     lui        v1,0x60
     6::800a5de8 24 48 83 02     and        t1,s4,v1
     6::800a5dec 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a5df8
     6::800a5df0 00 3e 03 3c     _lui       v1,0x3e00
     6::800a5df4 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a5df8                           XREF[1]:     OVR_226::800a5dec(j)  
     6::800a5df8 25 18 6f 00     or         v1,v1,t7
     6::800a5dfc 04 00 43 ac     sw         v1,0x4(v0)
     6::800a5e00 08 00 4b ac     sw         t3,0x8(v0)
     6::800a5e04 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a5e08 10 00 50 ac     sw         s0,0x10(v0)
     6::800a5e0c 14 00 4c ac     sw         t4,0x14(v0)
     6::800a5e10 18 00 54 ac     sw         s4,0x18(v0)
     6::800a5e14 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a5e18 20 00 4d ac     sw         t5,0x20(v0)
     6::800a5e1c 24 00 55 ac     sw         s5,0x24(v0)
     6::800a5e20 28 00 52 ac     sw         s2,0x28(v0)
     6::800a5e24 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a5e28 02 1c 15 00     srl        v1,s5,0x10
     6::800a5e2c 30 00 43 ac     sw         v1,0x30(v0)
     6::800a5e30 34 00 09 24     li         t1,0x34
     6::800a5e34 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a5e38                           XREF[1]:     OVR_226::800a5d90(j)  
     6::800a5e38 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a5e3c 00 42 02 00     sll        t0,v0,0x8
     6::800a5e40 02 42 08 00     srl        t0,t0,0x8
     6::800a5e44 25 18 6a 00     or         v1,v1,t2
     6::800a5e48 00 00 43 ac     sw         v1,0x0(v0)
     6::800a5e4c 21 10 49 00     addu       v0,v0,t1
     6::800a5e50 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a5e54 08 00 e0 03     jr         ra
     6::800a5e58 01 00 bd 23     _addi      sp,sp,0x1
     
	 
                        LAB_OVR_226__800a5e5c                           XREF[1]:     OVR_226::800ab448(*)  
     6::800a5e5c 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_226__800a5e60                           XREF[1]:     OVR_226::800a61b0(j)  
     6::800a5e60 30 00 23 8c     lw         v1,0x30(at)
     6::800a5e64 80 13 48 24     addiu      t0,v0,0x1380
     6::800a5e68 23 18 68 00     subu       v1,v1,t0
     6::800a5e6c 11 ec 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a5e70 b4 01 3e 24     _addiu     s8,at,0x1b4
     6::800a5e74 04 ec 00 13     beq        t8,zero,LAB_OVR_226__800a0e88
     6::800a5e78 b4 00 c0 af     _sw        zero,0xb4(s8)
     6::800a5e7c 00 00 14 8f     lw         s4,0x0(t8)
     6::800a5e80 04 00 16 8f     lw         s6,0x4(t8)
     6::800a5e84 ff ff 93 32     andi       s3,s4,0xffff
     6::800a5e88 00 99 13 00     sll        s3,s3,0x4
     6::800a5e8c 21 98 77 02     addu       s3,s3,s7
     6::800a5e90 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a5e98 02 a4 14 00     srl        s4,s4,0x10
     6::800a5e9c 00 a1 14 00     sll        s4,s4,0x4
     6::800a5ea0 21 a0 97 02     addu       s4,s4,s7
     6::800a5ea4 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a5eac ff ff d5 32     andi       s5,s6,0xffff
     6::800a5eb0 00 a9 15 00     sll        s5,s5,0x4
     6::800a5eb4 21 a8 b7 02     addu       s5,s5,s7
     6::800a5eb8 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a5ec0 02 b4 16 00     srl        s6,s6,0x10
     6::800a5ec4 00 b1 16 00     sll        s6,s6,0x4
     6::800a5ec8 30 00 28 4a     RTPT
     6::800a5ecc 21 b0 d7 02     addu       s6,s6,s7
     6::800a5ed0 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a5ed4 08 00 90 8e     lw         s0,0x8(s4)
     6::800a5ed8 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a5edc 08 00 cf af     sw         t7,0x8(s8)
     6::800a5ee0 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a5ee4 30 00 d1 af     sw         s1,0x30(s8)
     6::800a5ee8 08 00 14 8f     lw         s4,0x8(t8)
     6::800a5eec 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a5ef0 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a5ef4 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a5ef8 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a5efc 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a5f00 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a5f04 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a5f08 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a5f0c 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a5f10 5c 00 2a 8c     lw         t2,0x5c(at)
     6::800a5f14 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a5f20 10 00 c3 a7     sh         v1,0x10(s8)
     6::800a5f24 24 00 c8 a7     sh         t0,0x24(s8)
     6::800a5f28 38 00 c9 a7     sh         t1,0x38(s8)
     6::800a5f2c 23 58 6a 00     subu       t3,v1,t2
     6::800a5f30 23 60 0a 01     subu       t4,t0,t2
     6::800a5f34 23 68 2a 01     subu       t5,t1,t2
     6::800a5f38 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a5f3c c2 67 0c 00     srl        t4,t4,0x1f
     6::800a5f40 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a5f44 12 00 cb a3     sb         t3,0x12(s8)
     6::800a5f48 26 00 cc a3     sb         t4,0x26(s8)
     6::800a5f4c 3a 00 cd a3     sb         t5,0x3a(s8)
     6::800a5f50 40 18 03 00     sll        v1,v1,0x1
     6::800a5f54 40 40 08 00     sll        t0,t0,0x1
     6::800a5f58 40 48 09 00     sll        t1,t1,0x1
     6::800a5f5c 23 58 6a 00     subu       t3,v1,t2
     6::800a5f60 23 60 0a 01     subu       t4,t0,t2
     6::800a5f64 23 68 2a 01     subu       t5,t1,t2
     6::800a5f68 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a5f6c c2 67 0c 00     srl        t4,t4,0x1f
     6::800a5f70 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a5f74 13 00 cb a3     sb         t3,0x13(s8)
     6::800a5f78 27 00 cc a3     sb         t4,0x27(s8)
     6::800a5f7c 3b 00 cd a3     sb         t5,0x3b(s8)
     6::800a5f80 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a5f88 ff ff 93 32     andi       s3,s4,0xffff
     6::800a5f8c 00 99 13 00     sll        s3,s3,0x4
     6::800a5f90 21 98 77 02     addu       s3,s3,s7
     6::800a5f94 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a5f9c 02 a4 14 00     srl        s4,s4,0x10
     6::800a5fa0 00 a1 14 00     sll        s4,s4,0x4
     6::800a5fa4 21 a0 97 02     addu       s4,s4,s7
     6::800a5fa8 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a5fb0 21 c8 20 00     move       t9,at
     6::800a5fb4 00 00 00 00     nop
     6::800a5fb8 30 00 28 4a     RTPT
     6::800a5fbc 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a5fc0 08 00 70 8e     lw         s0,0x8(s3)
     6::800a5fc4 08 00 91 8e     lw         s1,0x8(s4)
     6::800a5fc8 44 00 cf af     sw         t7,0x44(s8)
     6::800a5fcc 58 00 d0 af     sw         s0,0x58(s8)
     6::800a5fd0 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a5fd4 0c 00 14 8f     lw         s4,0xc(t8)
     6::800a5fd8 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a5fdc 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a5fe0 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a5fe4 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a5fe8 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a5fec 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a5ff0 10 00 15 97     lhu        s5,0x10(t8)
     6::800a5ff4 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a5ff8 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a5ffc 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a6000 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a600c 4c 00 c3 a7     sh         v1,0x4c(s8)
     6::800a6010 60 00 c8 a7     sh         t0,0x60(s8)
     6::800a6014 74 00 c9 a7     sh         t1,0x74(s8)
     6::800a6018 23 58 6a 00     subu       t3,v1,t2
     6::800a601c 23 60 0a 01     subu       t4,t0,t2
     6::800a6020 23 68 2a 01     subu       t5,t1,t2
     6::800a6024 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a6028 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a602c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a6030 4e 00 cb a3     sb         t3,0x4e(s8)
     6::800a6034 62 00 cc a3     sb         t4,0x62(s8)
     6::800a6038 76 00 cd a3     sb         t5,0x76(s8)
     6::800a603c 40 18 03 00     sll        v1,v1,0x1
     6::800a6040 40 40 08 00     sll        t0,t0,0x1
     6::800a6044 40 48 09 00     sll        t1,t1,0x1
     6::800a6048 23 58 6a 00     subu       t3,v1,t2
     6::800a604c 23 60 0a 01     subu       t4,t0,t2
     6::800a6050 23 68 2a 01     subu       t5,t1,t2
     6::800a6054 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a6058 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a605c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a6060 4f 00 cb a3     sb         t3,0x4f(s8)
     6::800a6064 63 00 cc a3     sb         t4,0x63(s8)
     6::800a6068 77 00 cd a3     sb         t5,0x77(s8)
     6::800a606c ff ff 93 32     andi       s3,s4,0xffff
     6::800a6070 00 99 13 00     sll        s3,s3,0x4
     6::800a6074 21 98 77 02     addu       s3,s3,s7
     6::800a6078 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a6080 02 a4 14 00     srl        s4,s4,0x10
     6::800a6084 00 a1 14 00     sll        s4,s4,0x4
     6::800a6088 21 a0 97 02     addu       s4,s4,s7
     6::800a608c 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a6094 14 00 09 8f     lw         t1,0x14(t8)
     6::800a6098 00 a9 15 00     sll        s5,s5,0x4
     6::800a609c 21 a8 b7 02     addu       s5,s5,s7
     6::800a60a0 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a60a8 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a60ac 00 00 00 00     nop
     6::800a60b0 30 00 28 4a     RTPT
     6::800a60b4 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a60b8 08 00 90 8e     lw         s0,0x8(s4)
     6::800a60bc 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a60c0 80 00 cf af     sw         t7,0x80(s8)
     6::800a60c4 94 00 d0 af     sw         s0,0x94(s8)
     6::800a60c8 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a60cc 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a60d0 98 00 cd eb     gte_stSXY1 0x98(s8)
     6::800a60d4 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a60d8 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a60dc 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a60e0 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a60e4 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a60e8 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a60ec a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a60f0 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a60fc 88 00 c3 a7     sh         v1,0x88(s8)
     6::800a6100 9c 00 c8 a7     sh         t0,0x9c(s8)
     6::800a6104 b0 00 c9 a7     sh         t1,0xb0(s8)
     6::800a6108 23 58 6a 00     subu       t3,v1,t2
     6::800a610c 23 60 0a 01     subu       t4,t0,t2
     6::800a6110 23 68 2a 01     subu       t5,t1,t2
     6::800a6114 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a6118 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a611c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a6120 8a 00 cb a3     sb         t3,0x8a(s8)
     6::800a6124 9e 00 cc a3     sb         t4,0x9e(s8)
     6::800a6128 b2 00 cd a3     sb         t5,0xb2(s8)
     6::800a612c 40 18 03 00     sll        v1,v1,0x1
     6::800a6130 40 40 08 00     sll        t0,t0,0x1
     6::800a6134 40 48 09 00     sll        t1,t1,0x1
     6::800a6138 23 58 6a 00     subu       t3,v1,t2
     6::800a613c 23 60 0a 01     subu       t4,t0,t2
     6::800a6140 23 68 2a 01     subu       t5,t1,t2
     6::800a6144 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a6148 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a614c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a6150 8b 00 cb a3     sb         t3,0x8b(s8)
     6::800a6154 9f 00 cc a3     sb         t4,0x9f(s8)
     6::800a6158 b3 00 cd a3     sb         t5,0xb3(s8)
     6::800a615c 50 00 03 3c     lui        v1,0x50
     6::800a6160 78 64 63 34     ori        v1,v1,0x6478
     6::800a6164 08 00 08 24     li         t0,0x8
     6::800a6168 d0 99 02 0c     jal        FUN_OVR_226__800a6740                            undefined FUN_OVR_226__800a6740()
     6::800a616c 00 00 0a 24     _li        t2,0x0
     6::800a6170 14 50 03 3c     lui        v1,0x5014
     6::800a6174 8c 78 63 34     ori        v1,v1,0x788c
     6::800a6178 0d 00 08 24     li         t0,0xd
     6::800a617c d0 99 02 0c     jal        FUN_OVR_226__800a6740                            undefined FUN_OVR_226__800a6740()
     6::800a6180 04 00 0a 24     _li        t2,0x4
     6::800a6184 78 64 03 3c     lui        v1,0x6478
     6::800a6188 a0 28 63 34     ori        v1,v1,0x28a0
     6::800a618c 12 00 08 24     li         t0,0x12
     6::800a6190 d0 99 02 0c     jal        FUN_OVR_226__800a6740                            undefined FUN_OVR_226__800a6740()
     6::800a6194 08 00 0a 24     _li        t2,0x8
     6::800a6198 8c 78 03 3c     lui        v1,0x788c
     6::800a619c 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a61a0 17 00 08 24     li         t0,0x17
     6::800a61a4 d0 99 02 0c     jal        FUN_OVR_226__800a6740                            undefined FUN_OVR_226__800a6740()
     6::800a61a8 0c 00 0a 24     _li        t2,0xc
     6::800a61ac 04 00 98 8c     lw         t8,0x4(a0)
     6::800a61b0 2b ff 01 04     bgez       zero,LAB_OVR_226__800a5e60
     6::800a61b4 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_226__800a61b8                           XREF[12]:    FUN_OVR_226__800a661c:800a6638(j
                                                                                          FUN_OVR_226__800a661c:800a66d4(j
                                                                                          FUN_OVR_226__800a661c:800a66dc(j
                                                                                          FUN_OVR_226__800a661c:800a6710(j
                                                                                          OVR_226::800a67cc(j), 
                                                                                          OVR_226::800a6858(j), 
                                                                                          OVR_226::800a6860(j), 
                                                                                          OVR_226::800a688c(j), 
                                                                                          FUN_OVR_226__800a661c:800a6bc8(j
                                                                                          FUN_OVR_226__800a661c:800a6c84(j
                                                                                          FUN_OVR_226__800a661c:800a6db8(j
                                                                                          FUN_OVR_226__800a661c:800a6e70(j
     6::800a61b8 08 00 e0 03     jr         ra
     6::800a61bc 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a61c0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a61c0                           XREF[4]:     FUN_OVR_226__800a624c:800a62a0(j
                                                                                          FUN_OVR_226__800a624c:800a63cc(c
                                                                                          FUN_OVR_226__800a624c:800a6400(c
                                                                                          FUN_OVR_226__800a624c:800a648c(c
     6::800a61c0 00 00 d3 27     addiu      s3,s8,0x0
     6::800a61c4 50 00 d4 27     addiu      s4,s8,0x50
     6::800a61c8 64 00 d5 27     addiu      s5,s8,0x64
     6::800a61cc 13 01 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a61d0 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a61d4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a61d4                           XREF[6]:     FUN_OVR_226__800a624c:800a62e8(c
                                                                                          FUN_OVR_226__800a624c:800a63dc(j
                                                                                          FUN_OVR_226__800a624c:800a63f8(c
                                                                                          FUN_OVR_226__800a624c:800a6434(c
                                                                                          FUN_OVR_226__800a624c:800a6460(c
                                                                                          FUN_OVR_226__800a624c:800a649c(c
     6::800a61d4 50 00 d3 27     addiu      s3,s8,0x50
     6::800a61d8 14 00 d4 27     addiu      s4,s8,0x14
     6::800a61dc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a61e0 0e 01 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a61e4 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a61e8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a61e8                           XREF[6]:     FUN_OVR_226__800a624c:800a6350(c
                                                                                          FUN_OVR_226__800a624c:800a63c4(c
                                                                                          FUN_OVR_226__800a624c:800a6410(j
                                                                                          FUN_OVR_226__800a624c:800a642c(c
                                                                                          FUN_OVR_226__800a624c:800a6468(c
                                                                                          FUN_OVR_226__800a624c:800a64ac(c
     6::800a61e8 64 00 d3 27     addiu      s3,s8,0x64
     6::800a61ec 78 00 d4 27     addiu      s4,s8,0x78
     6::800a61f0 28 00 d5 27     addiu      s5,s8,0x28
     6::800a61f4 09 01 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a61f8 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a61fc                           XREF[4]:     OVR_226::800a63a8(j), 
                                                                                          OVR_226::800a6444(j), 
                                                                                          OVR_226::800a6478(j), 
                                                                                          OVR_226::800a64c4(j)  
     6::800a61fc 78 00 d3 27     addiu      s3,s8,0x78
     6::800a6200 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a6204 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a6208 04 01 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a620c 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6210()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6210                           XREF[2]:     FUN_OVR_226__800a624c:800a6348(c
                                                                                          FUN_OVR_226__800a624c:800a6458(c
     6::800a6210 64 00 d3 27     addiu      s3,s8,0x64
     6::800a6214 00 00 d4 27     addiu      s4,s8,0x0
     6::800a6218 78 00 d5 27     addiu      s5,s8,0x78
     6::800a621c ff 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a6220 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6224()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6224                           XREF[2]:     FUN_OVR_226__800a624c:800a6360(j
                                                                                          FUN_OVR_226__800a624c:800a63f0(c
     6::800a6224 14 00 d3 27     addiu      s3,s8,0x14
     6::800a6228 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a622c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a6230 fa 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a6234 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6238()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6238                           XREF[2]:     FUN_OVR_226__800a624c:800a62f0(c
                                                                                          FUN_OVR_226__800a624c:800a6424(c
     6::800a6238 28 00 d3 27     addiu      s3,s8,0x28
     6::800a623c 00 00 d4 27     addiu      s4,s8,0x0
     6::800a6240 78 00 d5 27     addiu      s5,s8,0x78
     6::800a6244 f5 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a6248 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a624c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a624c                           XREF[2]:     OVR_226::800a6300(j), 
                                                                                          OVR_226::800a63bc(c)  
     6::800a624c 28 00 d3 27     addiu      s3,s8,0x28
     6::800a6250 78 00 d4 27     addiu      s4,s8,0x78
     6::800a6254 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a6258 f0 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a625c 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a6260 24 03 23 24     addiu      v1,at,0x324
     6::800a6264 12 00 7e 10     beq        v1,s8,LAB_OVR_226__800a62b0
     6::800a6268 50 00 d3 27     _addiu     s3,s8,0x50
     6::800a626c 14 00 d4 27     addiu      s4,s8,0x14
     6::800a6270 78 00 d5 27     addiu      s5,s8,0x78
     6::800a6274 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a6278 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a627c 0c 00 0a 24     _li        t2,0xc
     6::800a6280 64 00 d3 27     addiu      s3,s8,0x64
     6::800a6284 78 00 d4 27     addiu      s4,s8,0x78
     6::800a6288 28 00 d5 27     addiu      s5,s8,0x28
     6::800a628c 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a6290 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a6294 0c 00 0a 24     _li        t2,0xc
     6::800a6298 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a629c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a62a0 c7 ff 01 04     bgez       zero,FUN_OVR_226__800a61c0
     6::800a62a4 0c 00 0a 24     _li        t2,0xc
     6::800a62a8 24 03 23 24     addiu      v1,at,0x324
     6::800a62ac 0e 00 7e 14     bne        v1,s8,LAB_OVR_226__800a62e8
                             LAB_OVR_226__800a62b0                           XREF[2]:     OVR_226::800a6264(j), 
                                                                                          OVR_226::800a63b4(j)  
     6::800a62b0 00 00 d3 27     addiu      s3,s8,0x0
     6::800a62b4 50 00 d4 27     addiu      s4,s8,0x50
     6::800a62b8 28 00 d5 27     addiu      s5,s8,0x28
     6::800a62bc 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a62c0 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a62c4 0c 00 0a 24     _li        t2,0xc
     6::800a62c8 14 00 d3 27     addiu      s3,s8,0x14
     6::800a62cc 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a62d0 50 00 d5 27     addiu      s5,s8,0x50
     6::800a62d4 28 00 d6 27     addiu      s6,s8,0x28
     6::800a62d8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a62dc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a62e0 ce 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a62e4 04 00 0a 24     _li        t2,0x4
                             LAB_OVR_226__800a62e8                           XREF[1]:     OVR_226::800a62ac(j)  
     6::800a62e8 75 98 02 0c     jal        FUN_OVR_226__800a61d4                            undefined FUN_OVR_226__800a61d4()
     6::800a62ec 0c 00 0a 24     _li        t2,0xc
     6::800a62f0 8e 98 02 0c     jal        FUN_OVR_226__800a6238                            undefined FUN_OVR_226__800a6238()
     6::800a62f4 0c 00 0a 24     _li        t2,0xc
     6::800a62f8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a62fc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6300 d2 ff 01 04     bgez       zero,FUN_OVR_226__800a624c
     6::800a6304 0c 00 0a 24     _li        t2,0xc
     6::800a6308 24 03 23 24     addiu      v1,at,0x324
     6::800a630c 0e 00 7e 14     bne        v1,s8,LAB_OVR_226__800a6348
                             LAB_OVR_226__800a6310                           XREF[2]:     OVR_226::800a636c(j), 
                                                                                          OVR_226::800a6450(j)  
     6::800a6310 14 00 d3 27     _addiu     s3,s8,0x14
     6::800a6314 a0 00 d4 27     addiu      s4,s8,0xa0
     6::800a6318 00 00 d5 27     addiu      s5,s8,0x0
     6::800a631c 28 00 d6 27     addiu      s6,s8,0x28
     6::800a6320 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a6324 0c 00 0a 24     _li        t2,0xc
     6::800a6328 00 00 d3 27     addiu      s3,s8,0x0
     6::800a632c 14 00 d4 27     addiu      s4,s8,0x14
     6::800a6330 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a6334 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a6338 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a633c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6340 b6 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a6344 08 00 0a 24     _li        t2,0x8
                             LAB_OVR_226__800a6348                           XREF[1]:     OVR_226::800a630c(j)  
     6::800a6348 84 98 02 0c     jal        FUN_OVR_226__800a6210                            undefined FUN_OVR_226__800a6210()
     6::800a634c 0c 00 0a 24     _li        t2,0xc
     6::800a6350 7a 98 02 0c     jal        FUN_OVR_226__800a61e8                            undefined FUN_OVR_226__800a61e8()
     6::800a6354 0c 00 0a 24     _li        t2,0xc
     6::800a6358 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a635c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6360 b0 ff 01 04     bgez       zero,FUN_OVR_226__800a6224
     6::800a6364 0c 00 0a 24     _li        t2,0xc
     6::800a6368 24 03 23 24     addiu      v1,at,0x324
     6::800a636c e8 ff 7e 10     beq        v1,s8,LAB_OVR_226__800a6310
     6::800a6370 00 00 d3 27     _addiu     s3,s8,0x0
     6::800a6374 14 00 d4 27     addiu      s4,s8,0x14
     6::800a6378 78 00 d5 27     addiu      s5,s8,0x78
     6::800a637c 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a6380 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a6384 0c 00 0a 24     _li        t2,0xc
     6::800a6388 00 00 d3 27     addiu      s3,s8,0x0
     6::800a638c 78 00 d4 27     addiu      s4,s8,0x78
     6::800a6390 28 00 d5 27     addiu      s5,s8,0x28
     6::800a6394 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a6398 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a639c 0c 00 0a 24     _li        t2,0xc
     6::800a63a0 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a63a4 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a63a8 94 ff 01 04     bgez       zero,LAB_OVR_226__800a61fc
     6::800a63ac 0c 00 0a 24     _li        t2,0xc
     6::800a63b0 24 03 23 24     addiu      v1,at,0x324
     6::800a63b4 be ff 7e 10     beq        v1,s8,LAB_OVR_226__800a62b0
     6::800a63b8 00 00 00 00     _nop
     6::800a63bc 93 98 02 0c     jal        FUN_OVR_226__800a624c                            undefined FUN_OVR_226__800a624c()
     6::800a63c0 0c 00 0a 24     _li        t2,0xc
     6::800a63c4 7a 98 02 0c     jal        FUN_OVR_226__800a61e8                            undefined FUN_OVR_226__800a61e8()
     6::800a63c8 04 00 0a 24     _li        t2,0x4
     6::800a63cc 70 98 02 0c     jal        FUN_OVR_226__800a61c0                            undefined FUN_OVR_226__800a61c0()
     6::800a63d0 0c 00 0a 24     _li        t2,0xc
     6::800a63d4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a63d8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a63dc 7d ff 01 04     bgez       zero,FUN_OVR_226__800a61d4
     6::800a63e0 0c 00 0a 24     _li        t2,0xc
     6::800a63e4 24 03 23 24     addiu      v1,at,0x324
     6::800a63e8 38 00 7e 10     beq        v1,s8,LAB_OVR_226__800a64cc
     6::800a63ec 00 00 00 00     _nop
     6::800a63f0 89 98 02 0c     jal        FUN_OVR_226__800a6224                            undefined FUN_OVR_226__800a6224()
     6::800a63f4 0c 00 0a 24     _li        t2,0xc
     6::800a63f8 75 98 02 0c     jal        FUN_OVR_226__800a61d4                            undefined FUN_OVR_226__800a61d4()
     6::800a63fc 04 00 0a 24     _li        t2,0x4
     6::800a6400 70 98 02 0c     jal        FUN_OVR_226__800a61c0                            undefined FUN_OVR_226__800a61c0()
     6::800a6404 0c 00 0a 24     _li        t2,0xc
     6::800a6408 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a640c fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6410 75 ff 01 04     bgez       zero,FUN_OVR_226__800a61e8
     6::800a6414 0c 00 0a 24     _li        t2,0xc
     6::800a6418 24 03 23 24     addiu      v1,at,0x324
     6::800a641c 2b 00 7e 10     beq        v1,s8,LAB_OVR_226__800a64cc
     6::800a6420 00 00 00 00     _nop
     6::800a6424 8e 98 02 0c     jal        FUN_OVR_226__800a6238                            undefined FUN_OVR_226__800a6238()
     6::800a6428 0c 00 0a 24     _li        t2,0xc
     6::800a642c 7a 98 02 0c     jal        FUN_OVR_226__800a61e8                            undefined FUN_OVR_226__800a61e8()
     6::800a6430 08 00 0a 24     _li        t2,0x8
     6::800a6434 75 98 02 0c     jal        FUN_OVR_226__800a61d4                            undefined FUN_OVR_226__800a61d4()
     6::800a6438 0c 00 0a 24     _li        t2,0xc
     6::800a643c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a6440 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6444 6d ff 01 04     bgez       zero,LAB_OVR_226__800a61fc
     6::800a6448 0c 00 0a 24     _li        t2,0xc
     6::800a644c 24 03 23 24     addiu      v1,at,0x324
     6::800a6450 af ff 7e 10     beq        v1,s8,LAB_OVR_226__800a6310
     6::800a6454 00 00 00 00     _nop
     6::800a6458 84 98 02 0c     jal        FUN_OVR_226__800a6210                            undefined FUN_OVR_226__800a6210()
     6::800a645c 0c 00 0a 24     _li        t2,0xc
     6::800a6460 75 98 02 0c     jal        FUN_OVR_226__800a61d4                            undefined FUN_OVR_226__800a61d4()
     6::800a6464 08 00 0a 24     _li        t2,0x8
     6::800a6468 7a 98 02 0c     jal        FUN_OVR_226__800a61e8                            undefined FUN_OVR_226__800a61e8()
     6::800a646c 0c 00 0a 24     _li        t2,0xc
     6::800a6470 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a6474 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6478 60 ff 01 04     bgez       zero,LAB_OVR_226__800a61fc
     6::800a647c 0c 00 0a 24     _li        t2,0xc
     6::800a6480 24 03 23 24     addiu      v1,at,0x324
     6::800a6484 11 00 7e 10     beq        v1,s8,LAB_OVR_226__800a64cc
     6::800a6488 b4 00 c0 af     _sw        zero,0xb4(s8)
     6::800a648c 70 98 02 0c     jal        FUN_OVR_226__800a61c0                            undefined FUN_OVR_226__800a61c0()
     6::800a6490 0c 00 0a 24     _li        t2,0xc
     6::800a6494 0c 00 03 24     li         v1,0xc
     6::800a6498 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a649c 75 98 02 0c     jal        FUN_OVR_226__800a61d4                            undefined FUN_OVR_226__800a61d4()
     6::800a64a0 0c 00 0a 24     _li        t2,0xc
     6::800a64a4 18 00 03 24     li         v1,0x18
     6::800a64a8 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a64ac 7a 98 02 0c     jal        FUN_OVR_226__800a61e8                            undefined FUN_OVR_226__800a61e8()
     6::800a64b0 0c 00 0a 24     _li        t2,0xc
     6::800a64b4 24 00 03 24     li         v1,0x24
     6::800a64b8 b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a64bc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a64c0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a64c4 4d ff 01 04     bgez       zero,LAB_OVR_226__800a61fc
     6::800a64c8 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a64cc                           XREF[3]:     OVR_226::800a63e8(j), 
                                                                                          OVR_226::800a641c(j), 
                                                                                          OVR_226::800a6484(j)  
     6::800a64cc b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a64d0 00 00 d3 27     addiu      s3,s8,0x0
     6::800a64d4 50 00 d4 27     addiu      s4,s8,0x50
     6::800a64d8 28 00 d5 27     addiu      s5,s8,0x28
     6::800a64dc a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a64e0 87 99 02 0c     jal        FUN_OVR_226__800a661c                            undefined FUN_OVR_226__800a661c()
     6::800a64e4 0c 00 0a 24     _li        t2,0xc
     6::800a64e8 0c 00 03 24     li         v1,0xc
     6::800a64ec b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a64f0 50 00 d3 27     addiu      s3,s8,0x50
     6::800a64f4 14 00 d4 27     addiu      s4,s8,0x14
     6::800a64f8 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a64fc 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a6500 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a6504 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6508 44 00 01 04     bgez       zero,FUN_OVR_226__800a661c
     6::800a650c 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6510()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6510                           XREF[5]:     FUN_OVR_226__800a6740:800a6a30(c
                                                                                          FUN_OVR_226__800a6740:800a6a44(c
                                                                                          FUN_OVR_226__800a6740:800a6a58(c
                                                                                          FUN_OVR_226__800a6740:800a6a6c(c
                                                                                          FUN_OVR_226__800a6740:800a6a80(c
     6::800a6510 00 00 ab 85     lh         t3,0x0(t5)
     6::800a6514 00 00 cc 85     lh         t4,0x0(t6)
     6::800a6518 00 00 eb a5     sh         t3,0x0(t7)
     6::800a651c 21 18 6c 01     addu       v1,t3,t4
     6::800a6520 43 18 03 00     sra        v1,v1,0x1
     6::800a6524 00 00 03 a6     sh         v1,0x0(s0)
     6::800a6528 02 00 ab 85     lh         t3,0x2(t5)
     6::800a652c 02 00 cc 85     lh         t4,0x2(t6)
     6::800a6530 02 00 eb a5     sh         t3,0x2(t7)
     6::800a6534 21 18 6c 01     addu       v1,t3,t4
     6::800a6538 43 18 03 00     sra        v1,v1,0x1
     6::800a653c 02 00 03 a6     sh         v1,0x2(s0)
     6::800a6540 04 00 ab 85     lh         t3,0x4(t5)
     6::800a6544 04 00 cc 85     lh         t4,0x4(t6)
     6::800a6548 04 00 eb a5     sh         t3,0x4(t7)
     6::800a654c 21 18 6c 01     addu       v1,t3,t4
     6::800a6550 43 18 03 00     sra        v1,v1,0x1
     6::800a6554 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a6558 00 08 83 48     gte_ldVZ0  v1
     6::800a655c 04 00 03 a6     sh         v1,0x4(s0)
     6::800a6560 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a6564 01 00 18 4a     RTPS
     6::800a6568 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a656c 08 00 eb a1     sb         t3,0x8(t7)
     6::800a6570 21 18 6c 01     addu       v1,t3,t4
     6::800a6574 43 18 03 00     sra        v1,v1,0x1
     6::800a6578 08 00 03 a2     sb         v1,0x8(s0)
     6::800a657c 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a6580 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a6584 09 00 eb a1     sb         t3,0x9(t7)
     6::800a6588 21 18 6c 01     addu       v1,t3,t4
     6::800a658c 43 18 03 00     sra        v1,v1,0x1
     6::800a6590 09 00 03 a2     sb         v1,0x9(s0)
     6::800a6594 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a6598 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a659c 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a65a0 21 18 6c 01     addu       v1,t3,t4
     6::800a65a4 43 18 03 00     sra        v1,v1,0x1
     6::800a65a8 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a65ac 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a65b0 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a65b4 06 00 eb a1     sb         t3,0x6(t7)
     6::800a65b8 21 18 6c 01     addu       v1,t3,t4
     6::800a65bc 43 18 03 00     sra        v1,v1,0x1
     6::800a65c0 06 00 03 a2     sb         v1,0x6(s0)
     6::800a65c4 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a65c8 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a65cc 07 00 eb a1     sb         t3,0x7(t7)
     6::800a65d0 21 18 6c 01     addu       v1,t3,t4
     6::800a65d4 43 18 03 00     sra        v1,v1,0x1
     6::800a65d8 07 00 03 a2     sb         v1,0x7(s0)
     6::800a65dc 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a65e0 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a65e4 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a65e8 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a65ec 5c 00 2b 8c     lw         t3,0x5c(at)
     6::800a65f0 00 98 03 48     gte_stSZ3  v1
     6::800a65f4 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a65f8 10 00 03 ae     sw         v1,0x10(s0)
     6::800a65fc 23 40 6b 00     subu       t0,v1,t3
     6::800a6600 c2 47 08 00     srl        t0,t0,0x1f
     6::800a6604 12 00 08 a2     sb         t0,0x12(s0)
     6::800a6608 40 18 03 00     sll        v1,v1,0x1
     6::800a660c 23 40 6b 00     subu       t0,v1,t3
     6::800a6610 c2 47 08 00     srl        t0,t0,0x1f
     6::800a6614 08 00 e0 03     jr         ra
     6::800a6618 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a661c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a661c                           XREF[18]:    FUN_OVR_226__800a61c0:800a61cc(j
                                                                                          FUN_OVR_226__800a61d4:800a61e0(j
                                                                                          FUN_OVR_226__800a61e8:800a61f4(j
                                                                                          FUN_OVR_226__800a624c:800a6208(j
                                                                                          FUN_OVR_226__800a6210:800a621c(j
                                                                                          FUN_OVR_226__800a6224:800a6230(j
                                                                                          FUN_OVR_226__800a6238:800a6244(j
                                                                                          FUN_OVR_226__800a624c:800a6258(j
                                                                                          FUN_OVR_226__800a624c:800a6278(c
                                                                                          FUN_OVR_226__800a624c:800a6290(c
                                                                                          FUN_OVR_226__800a624c:800a62c0(c
                                                                                          FUN_OVR_226__800a624c:800a62e0(j
                                                                                          FUN_OVR_226__800a624c:800a6320(c
                                                                                          FUN_OVR_226__800a624c:800a6340(j
                                                                                          FUN_OVR_226__800a624c:800a6380(c
                                                                                          FUN_OVR_226__800a624c:800a6398(c
                                                                                          FUN_OVR_226__800a624c:800a64e0(c
                                                                                          FUN_OVR_226__800a624c:800a6508(j
     6::800a661c 13 00 6f 82     lb         t7,0x13(s3)
     6::800a6620 13 00 90 82     lb         s0,0x13(s4)
     6::800a6624 13 00 b1 82     lb         s1,0x13(s5)
     6::800a6628 13 00 d2 82     lb         s2,0x13(s6)
     6::800a662c 24 18 f0 01     and        v1,t7,s0
     6::800a6630 24 18 71 00     and        v1,v1,s1
     6::800a6634 24 18 72 00     and        v1,v1,s2
     6::800a6638 df fe 60 14     bne        v1,zero,LAB_OVR_226__800a61b8
     6::800a663c 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a6640 12 00 90 82     lb         s0,0x12(s4)
     6::800a6644 12 00 b1 82     lb         s1,0x12(s5)
     6::800a6648 12 00 d2 82     lb         s2,0x12(s6)
     6::800a664c 25 78 f0 01     or         t7,t7,s0
     6::800a6650 25 78 f1 01     or         t7,t7,s1
     6::800a6654 25 78 f2 01     or         t7,t7,s2
     6::800a6658 2e 00 e0 15     bne        t7,zero,LAB_OVR_226__800a6714
     6::800a665c 0c 00 03 24     _li        v1,0xc
     6::800a6660 70 00 2a ac     sw         t2,0x70(at)
     6::800a6664 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a6668 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a666c 94 01 2a 8c     lw         t2,0x194(at)
     6::800a6670 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a6674 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a6678 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a667c 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a6680 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a6684 06 00 40 4b     NCLIP
     6::800a6688 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a668c 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a6690 23 78 68 01     subu       t7,t3,t0
     6::800a6694 23 80 88 01     subu       s0,t4,t0
     6::800a6698 23 88 a8 01     subu       s1,t5,t0
     6::800a669c 23 90 c8 01     subu       s2,t6,t0
     6::800a66a0 00 c0 08 48     gte_stMAC0 t0
     6::800a66a4 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a66a8 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a66b4
     6::800a66ac 22 40 08 00     _sub       t0,zero,t0
     6::800a66b0 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a66b4                           XREF[1]:     OVR_226::800a66a8(j)  
     6::800a66b4 06 00 40 4b     NCLIP
     6::800a66b8 24 18 6c 01     and        v1,t3,t4
     6::800a66bc 24 18 6d 00     and        v1,v1,t5
     6::800a66c0 24 18 6e 00     and        v1,v1,t6
     6::800a66c4 25 78 f0 01     or         t7,t7,s0
     6::800a66c8 25 78 f1 01     or         t7,t7,s1
     6::800a66cc 27 78 f2 01     nor        t7,t7,s2
     6::800a66d0 25 78 e3 01     or         t7,t7,v1
     6::800a66d4 b8 fe e0 05     bltz       t7,LAB_OVR_226__800a61b8
     6::800a66d8 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a66dc b6 fe e0 05     bltz       t7,LAB_OVR_226__800a61b8
     6::800a66e0 00 c0 03 48     _gte_stM   v1
     6::800a66e4 25 40 09 01     or         t0,t0,t1
     6::800a66e8 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a66f4
     6::800a66ec c2 47 08 00     _srl       t0,t0,0x1f
     6::800a66f0 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a66f4                           XREF[1]:     OVR_226::800a66e8(j)  
     6::800a66f4 80 40 08 00     sll        t0,t0,0x2
     6::800a66f8 25 18 69 00     or         v1,v1,t1
     6::800a66fc c2 1f 03 00     srl        v1,v1,0x1f
     6::800a6700 c0 18 03 00     sll        v1,v1,0x3
     6::800a6704 70 00 2a 8c     lw         t2,0x70(at)
     6::800a6708 25 18 68 00     or         v1,v1,t0
     6::800a670c 24 18 6a 00     and        v1,v1,t2
     6::800a6710 a9 fe 60 10     beq        v1,zero,LAB_OVR_226__800a61b8
                             LAB_OVR_226__800a6714                           XREF[1]:     OVR_226::800a6658(j)  
     6::800a6714 70 00 23 ac     _sw        v1,0x70(at)
     6::800a6718 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a671c 24 03 28 24     addiu      t0,at,0x324
     6::800a6720 f4 00 1e 11     beq        t0,s8,LAB_OVR_226__800a6af4
     6::800a6724 04 00 39 27     _addiu     t9,t9,0x4
     6::800a6728 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a672c 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a6730 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a6734 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a6738 a8 00 01 04     bgez       zero,LAB_OVR_226__800a69dc
     6::800a673c 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6740()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6740                           XREF[4]:     OVR_226::800a6168(c), 
                                                                                          OVR_226::800a617c(c), 
                                                                                          OVR_226::800a6190(c), 
                                                                                          OVR_226::800a61a4(c)  
     6::800a6740 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a6744 b4 00 ca af     sw         t2,0xb4(s8)
     6::800a6748 06 50 09 01     srlv       t2,t1,t0
     6::800a674c 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a6750 80 50 0a 00     sll        t2,t2,0x2
     6::800a6754 21 50 41 01     addu       t2,t2,at
     6::800a6758 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a675c 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a6760 94 01 2a ac     sw         t2,0x194(at)
     6::800a6764 02 9e 0a 00     srl        s3,t2,0x18
     6::800a6768 1f 00 73 32     andi       s3,s3,0x1f
     6::800a676c 06 98 63 02     srlv       s3,v1,s3
     6::800a6770 ff 00 73 32     andi       s3,s3,0xff
     6::800a6774 21 98 7e 02     addu       s3,s3,s8
     6::800a6778 02 a4 0a 00     srl        s4,t2,0x10
     6::800a677c 1f 00 94 32     andi       s4,s4,0x1f
     6::800a6780 06 a0 83 02     srlv       s4,v1,s4
     6::800a6784 ff 00 94 32     andi       s4,s4,0xff
     6::800a6788 21 a0 9e 02     addu       s4,s4,s8
     6::800a678c 02 aa 0a 00     srl        s5,t2,0x8
     6::800a6790 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a6794 06 a8 a3 02     srlv       s5,v1,s5
     6::800a6798 ff 00 b5 32     andi       s5,s5,0xff
     6::800a679c 21 a8 be 02     addu       s5,s5,s8
     6::800a67a0 1f 00 56 31     andi       s6,t2,0x1f
     6::800a67a4 06 b0 c3 02     srlv       s6,v1,s6
     6::800a67a8 ff 00 d6 32     andi       s6,s6,0xff
     6::800a67ac 21 b0 de 02     addu       s6,s6,s8
     6::800a67b0 13 00 6f 82     lb         t7,0x13(s3)
     6::800a67b4 13 00 90 82     lb         s0,0x13(s4)
     6::800a67b8 13 00 b1 82     lb         s1,0x13(s5)
     6::800a67bc 13 00 d2 82     lb         s2,0x13(s6)
     6::800a67c0 24 18 f0 01     and        v1,t7,s0
     6::800a67c4 24 18 71 00     and        v1,v1,s1
     6::800a67c8 24 18 72 00     and        v1,v1,s2
     6::800a67cc 7a fe 60 14     bne        v1,zero,LAB_OVR_226__800a61b8
     6::800a67d0 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a67d4 12 00 90 82     lb         s0,0x12(s4)
     6::800a67d8 12 00 b1 82     lb         s1,0x12(s5)
     6::800a67dc 12 00 d2 82     lb         s2,0x12(s6)
     6::800a67e0 25 78 f0 01     or         t7,t7,s0
     6::800a67e4 25 78 f1 01     or         t7,t7,s1
     6::800a67e8 25 78 f2 01     or         t7,t7,s2
     6::800a67ec 28 00 e0 15     bne        t7,zero,LAB_OVR_226__800a6890
     6::800a67f0 0c 00 03 24     _li        v1,0xc
     6::800a67f4 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a67f8 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a67fc 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a6800 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a6804 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a6808 06 00 40 4b     NCLIP
     6::800a680c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a6810 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a6814 23 78 68 01     subu       t7,t3,t0
     6::800a6818 23 80 88 01     subu       s0,t4,t0
     6::800a681c 23 88 a8 01     subu       s1,t5,t0
     6::800a6820 23 90 c8 01     subu       s2,t6,t0
     6::800a6824 00 c0 08 48     gte_stMAC0 t0
     6::800a6828 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a682c 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a6838
     6::800a6830 22 40 08 00     _sub       t0,zero,t0
     6::800a6834 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a6838                           XREF[1]:     OVR_226::800a682c(j)  
     6::800a6838 06 00 40 4b     NCLIP
     6::800a683c 24 18 6c 01     and        v1,t3,t4
     6::800a6840 24 18 6d 00     and        v1,v1,t5
     6::800a6844 24 18 6e 00     and        v1,v1,t6
     6::800a6848 25 78 f0 01     or         t7,t7,s0
     6::800a684c 25 78 f1 01     or         t7,t7,s1
     6::800a6850 27 78 f2 01     nor        t7,t7,s2
     6::800a6854 25 78 e3 01     or         t7,t7,v1
     6::800a6858 57 fe e0 05     bltz       t7,LAB_OVR_226__800a61b8
     6::800a685c 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a6860 55 fe e0 05     bltz       t7,LAB_OVR_226__800a61b8
     6::800a6864 00 c0 03 48     _gte_stM   v1
     6::800a6868 25 40 09 01     or         t0,t0,t1
     6::800a686c 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a6878
     6::800a6870 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a6874 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a6878                           XREF[1]:     OVR_226::800a686c(j)  
     6::800a6878 80 40 08 00     sll        t0,t0,0x2
     6::800a687c 25 18 69 00     or         v1,v1,t1
     6::800a6880 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a6884 c0 18 03 00     sll        v1,v1,0x3
     6::800a6888 25 18 68 00     or         v1,v1,t0
     6::800a688c 4a fe 60 10     beq        v1,zero,LAB_OVR_226__800a61b8
                             LAB_OVR_226__800a6890                           XREF[1]:     OVR_226::800a67ec(j)  
     6::800a6890 70 00 23 ac     _sw        v1,0x70(at)
     6::800a6894 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a6898 04 00 39 27     addiu      t9,t9,0x4
     6::800a689c c2 4f 09 00     srl        t1,t1,0x1f
     6::800a68a0 c0 4f 09 00     sll        t1,t1,0x1f
     6::800a68a4 c2 57 0a 00     srl        t2,t2,0x1f
     6::800a68a8 80 57 0a 00     sll        t2,t2,0x1e
     6::800a68ac 25 50 49 01     or         t2,t2,t1
     6::800a68b0 80 00 2a ac     sw         t2,0x80(at)
     6::800a68b4 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a68b8 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a68bc 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a68c0 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a68c4 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a68c8 23 50 6c 01     subu       t2,t3,t4
     6::800a68cc 82 48 03 00     srl        t1,v1,0x2
     6::800a68d0 21 48 38 01     addu       t1,t1,t8
     6::800a68d4 18 00 29 81     lb         t1,0x18(t1)
     6::800a68d8 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a68e4
     6::800a68dc 21 e0 60 01     _move      gp,t3
     6::800a68e0 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a68e4                           XREF[1]:     OVR_226::800a68d8(j)  
     6::800a68e4 23 50 8d 03     subu       t2,gp,t5
     6::800a68e8 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a68f4
     6::800a68ec 21 18 78 00     _addu      v1,v1,t8
     6::800a68f0 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a68f4                           XREF[1]:     OVR_226::800a68e8(j)  
     6::800a68f4 23 50 8e 03     subu       t2,gp,t6
     6::800a68f8 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a6904
     6::800a68fc 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a6900 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a6904                           XREF[1]:     OVR_226::800a68f8(j)  
     6::800a6904 21 50 80 03     move       t2,gp
     6::800a6908 82 e1 1c 00     srl        gp,gp,0x6
     6::800a690c 21 e0 89 03     addu       gp,gp,t1
     6::800a6910 01 00 69 30     andi       t1,v1,0x1
     6::800a6914 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a6920
     6::800a6918 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a691c ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a6920                           XREF[1]:     OVR_226::800a6914(j)  
     6::800a6920 02 00 81 07     bgez       gp,LAB_OVR_226__800a692c
     6::800a6924 21 e0 85 03     _addu      gp,gp,a1
     6::800a6928 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a692c                           XREF[1]:     OVR_226::800a6920(j)  
     6::800a692c 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a6930 24 00 69 8c     lw         t1,0x24(v1)
     6::800a6934 23 40 48 01     subu       t0,t2,t0
     6::800a6938 84 00 29 ac     sw         t1,0x84(at)
     6::800a693c 0c 00 01 05     bgez       t0,LAB_OVR_226__800a6970
     6::800a6940 20 00 28 8c     _lw        t0,0x20(at)
     6::800a6944 0c 00 63 24     addiu      v1,v1,0xc
     6::800a6948 23 40 48 01     subu       t0,t2,t0
     6::800a694c 08 00 01 05     bgez       t0,LAB_OVR_226__800a6970
     6::800a6950 24 00 28 8c     _lw        t0,0x24(at)
     6::800a6954 0c 00 63 24     addiu      v1,v1,0xc
     6::800a6958 23 40 48 01     subu       t0,t2,t0
     6::800a695c 04 00 01 05     bgez       t0,LAB_OVR_226__800a6970
     6::800a6960 00 00 00 00     _nop
     6::800a6964 02 00 20 05     bltz       t1,LAB_OVR_226__800a6970
     6::800a6968 00 00 00 00     _nop
     6::800a696c 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a6970                           XREF[4]:     OVR_226::800a693c(j), 
                                                                                          OVR_226::800a694c(j), 
                                                                                          OVR_226::800a695c(j), 
                                                                                          OVR_226::800a6964(j)  
     6::800a6970 94 01 2a 8c     lw         t2,0x194(at)
     6::800a6974 00 00 68 8c     lw         t0,0x0(v1)
     6::800a6978 04 00 69 8c     lw         t1,0x4(v1)
     6::800a697c a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a6980 ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a6984 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a6988 00 52 0a 00     sll        t2,t2,0x8
     6::800a698c 0a 00 40 05     bltz       t2,LAB_OVR_226__800a69b8
     6::800a6990 b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a6994 06 00 68 a6     sh         t0,0x6(s3)
     6::800a6998 08 00 68 8c     lw         t0,0x8(v1)
     6::800a699c 06 00 89 a6     sh         t1,0x6(s4)
     6::800a69a0 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a69a4 00 54 0a 00     sll        t2,t2,0x10
     6::800a69a8 0b 00 40 05     bltz       t2,LAB_OVR_226__800a69d8
     6::800a69ac 02 4c 08 00     _srl       t1,t0,0x10
     6::800a69b0 09 00 01 04     bgez       zero,LAB_OVR_226__800a69d8
     6::800a69b4 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a69b8                           XREF[1]:     OVR_226::800a698c(j)  
     6::800a69b8 06 00 69 a6     sh         t1,0x6(s3)
     6::800a69bc 08 00 69 8c     lw         t1,0x8(v1)
     6::800a69c0 00 54 0a 00     sll        t2,t2,0x10
     6::800a69c4 06 00 88 a6     sh         t0,0x6(s4)
     6::800a69c8 02 44 09 00     srl        t0,t1,0x10
     6::800a69cc 02 00 40 05     bltz       t2,LAB_OVR_226__800a69d8
     6::800a69d0 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a69d4 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a69d8                           XREF[3]:     OVR_226::800a69a8(j), 
                                                                                          OVR_226::800a69b0(j), 
                                                                                          OVR_226::800a69cc(j)  
     6::800a69d8 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a69dc                           XREF[1]:     FUN_OVR_226__800a661c:800a6738(j
     6::800a69dc 00 00 00 00     nop
     6::800a69e0 23 88 63 01     subu       s1,t3,v1
     6::800a69e4 23 90 83 01     subu       s2,t4,v1
     6::800a69e8 23 78 a3 01     subu       t7,t5,v1
     6::800a69ec 23 80 c3 01     subu       s0,t6,v1
     6::800a69f0 42 8f 11 00     srl        s1,s1,0x1d
     6::800a69f4 04 00 31 32     andi       s1,s1,0x4
     6::800a69f8 02 97 12 00     srl        s2,s2,0x1c
     6::800a69fc 08 00 52 32     andi       s2,s2,0x8
     6::800a6a00 25 88 32 02     or         s1,s1,s2
     6::800a6a04 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a6a08 10 00 ef 31     andi       t7,t7,0x10
     6::800a6a0c 25 88 2f 02     or         s1,s1,t7
     6::800a6a10 82 86 10 00     srl        s0,s0,0x1a
     6::800a6a14 20 00 10 32     andi       s0,s0,0x20
     6::800a6a18 25 88 30 02     or         s1,s1,s0
     6::800a6a1c 2e 00 20 12     beq        s1,zero,LAB_OVR_226__800a6ad8
     6::800a6a20 21 68 60 02     _move      t5,s3
     6::800a6a24 21 70 80 02     move       t6,s4
     6::800a6a28 b8 00 de 27     addiu      s8,s8,0xb8
     6::800a6a2c 00 00 cf 27     addiu      t7,s8,0x0
     6::800a6a30 44 99 02 0c     jal        FUN_OVR_226__800a6510                            undefined FUN_OVR_226__800a6510()
     6::800a6a34 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a6a38 21 68 a0 02     move       t5,s5
     6::800a6a3c 21 70 c0 02     move       t6,s6
     6::800a6a40 28 00 cf 27     addiu      t7,s8,0x28
     6::800a6a44 44 99 02 0c     jal        FUN_OVR_226__800a6510                            undefined FUN_OVR_226__800a6510()
     6::800a6a48 a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a6a4c 21 68 a0 02     move       t5,s5
     6::800a6a50 21 70 60 02     move       t6,s3
     6::800a6a54 28 00 cf 27     addiu      t7,s8,0x28
     6::800a6a58 44 99 02 0c     jal        FUN_OVR_226__800a6510                            undefined FUN_OVR_226__800a6510()
     6::800a6a5c 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a6a60 21 68 80 02     move       t5,s4
     6::800a6a64 21 70 a0 02     move       t6,s5
     6::800a6a68 14 00 cf 27     addiu      t7,s8,0x14
     6::800a6a6c 44 99 02 0c     jal        FUN_OVR_226__800a6510                            undefined FUN_OVR_226__800a6510()
     6::800a6a70 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a6a74 21 68 c0 02     move       t5,s6
     6::800a6a78 21 70 80 02     move       t6,s4
     6::800a6a7c 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a6a80 44 99 02 0c     jal        FUN_OVR_226__800a6510                            undefined FUN_OVR_226__800a6510()
     6::800a6a84 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a6a88 21 18 21 02     addu       v1,s1,at
     6::800a6a8c 48 01 63 8c     lw         v1,0x148(v1)
     6::800a6a90 0a 80 08 3c     lui        t0,0x800a
     6::800a6a94 c8 6a 08 25     addiu      t0,t0,0x6ac8
     6::800a6a98 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a6a9c 3c 00 28 af     sw         t0=>LAB_OVR_226__800a6ac8,0x3c(t9)
     6::800a6aa0 08 00 60 00     jr         v1
     6::800a6aa4 04 00 39 27     _addiu     t9,t9,0x4
     6::800a6aa8 21 18 21 02     addu       v1,s1,at
     6::800a6aac 48 01 63 8c     lw         v1,0x148(v1)
     6::800a6ab0 0a 80 08 3c     lui        t0,0x800a
     6::800a6ab4 c8 6a 08 25     addiu      t0,t0,0x6ac8
     6::800a6ab8 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a6abc 3c 00 28 af     sw         t0=>LAB_OVR_226__800a6ac8,0x3c(t9)
     6::800a6ac0 08 00 60 00     jr         v1
     6::800a6ac4 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a6ac8                           XREF[2]:     FUN_OVR_226__800a6740:800a6a9c(*
                                                                                          OVR_226::800a6abc(*)  
     6::800a6ac8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a6acc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6ad0 08 00 e0 03     jr         ra
     6::800a6ad4 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a6ad8                           XREF[1]:     OVR_226::800a6a1c(j)  
     6::800a6ad8 70 00 23 8c     lw         v1,0x70(at)
     6::800a6adc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a6ae0 21 18 61 00     addu       v1,v1,at
     6::800a6ae4 84 01 63 8c     lw         v1,0x184(v1)
     6::800a6ae8 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a6aec 08 00 60 00     jr         v1
     6::800a6af0 00 00 00 00     _nop
                             LAB_OVR_226__800a6af4                           XREF[1]:     OVR_226::800a6720(j)  
     6::800a6af4 84 00 23 8c     lw         v1,0x84(at)
     6::800a6af8 24 03 2a 24     addiu      t2,at,0x324
     6::800a6afc 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a6b98
     6::800a6b00 20 03 28 8c     _lw        t0,0x320(at)
     6::800a6b04 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a6b08 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a6b64
     6::800a6b0c 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a6b10 0a 80 0a 3c     lui        t2,0x800a
     6::800a6b14 80 64 4a 25     addiu      t2,t2,0x6480
     6::800a6b18 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a6b98
     6::800a6b1c 94 01 23 8c     _lw        v1,0x194(at)
     6::800a6b20 40 40 08 00     sll        t0,t0,0x1
     6::800a6b24 00 1a 03 00     sll        v1,v1,0x8
     6::800a6b28 02 00 61 04     bgez       v1,LAB_OVR_226__800a6b34
     6::800a6b2c 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a6b30 60 00 08 25     addiu      t0,t0,0x60
                             LAB_OVR_226__800a6b34                           XREF[1]:     OVR_226::800a6b28(j)  
     6::800a6b34 21 40 09 01     addu       t0,t0,t1
     6::800a6b38 21 50 48 01     addu       t2,t2,t0
     6::800a6b3c 00 00 48 8d     lw         t0,0x0(t2)
     6::800a6b40 04 00 49 8d     lw         t1,0x4(t2)
     6::800a6b44 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a6b48 06 00 68 a6     sh         t0,0x6(s3)
     6::800a6b4c 08 00 48 85     lh         t0,0x8(t2)
     6::800a6b50 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a6b54 06 00 89 a6     sh         t1,0x6(s4)
     6::800a6b58 0a 00 49 85     lh         t1,0xa(t2)
     6::800a6b5c 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a6b60 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a6b64                           XREF[2]:     OVR_226::800a6b08(j), 
                                                                                          OVR_226::800a6ba4(j)  
     6::800a6b64 70 00 23 8c     lw         v1,0x70(at)
     6::800a6b68 00 00 00 00     nop
     6::800a6b6c 21 18 61 00     addu       v1,v1,at
     6::800a6b70 84 01 63 8c     lw         v1,0x184(v1)
     6::800a6b74 00 00 00 00     nop
     6::800a6b78 09 f8 60 00     jalr       v1
     6::800a6b7c fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a6b80 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a6b84 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a6b88 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a6b8c a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a6b90 08 00 e0 03     jr         ra
     6::800a6b94 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a6b98                           XREF[2]:     OVR_226::800a6afc(j), 
                                                                                          OVR_226::800a6b18(j)  
     6::800a6b98 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a6b9c b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a6ba0 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a6ba4 ef ff 01 04     bgez       zero,LAB_OVR_226__800a6b64
     6::800a6ba8 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a6bac 21 98 80 02     move       s3,s4
     6::800a6bb0 21 a0 c0 02     move       s4,s6
     6::800a6bb4 13 00 6f 82     lb         t7,0x13(s3)
     6::800a6bb8 13 00 90 82     lb         s0,0x13(s4)
     6::800a6bbc 13 00 b1 82     lb         s1,0x13(s5)
     6::800a6bc0 24 18 f0 01     and        v1,t7,s0
     6::800a6bc4 24 18 71 00     and        v1,v1,s1
     6::800a6bc8 7b fd 60 04     bltz       v1,LAB_OVR_226__800a61b8
     6::800a6bcc 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a6bd0 12 00 90 82     lb         s0,0x12(s4)
     6::800a6bd4 12 00 b1 82     lb         s1,0x12(s5)
     6::800a6bd8 25 78 f0 01     or         t7,t7,s0
     6::800a6bdc 25 78 f1 01     or         t7,t7,s1
     6::800a6be0 62 00 e0 05     bltz       t7,LAB_OVR_226__800a6d6c
     6::800a6be4 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a6be8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a6bec 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a6bf0 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a6bf4 08 00 90 8e     lw         s0,0x8(s4)
     6::800a6bf8 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a6bfc 06 00 73 86     lh         s3,0x6(s3)
     6::800a6c00 06 00 94 86     lh         s4,0x6(s4)
     6::800a6c04 06 00 b5 86     lh         s5,0x6(s5)
     6::800a6c08 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a6c0c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a6c10 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a6c14 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a6c18 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a6c1c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a6c20 60 00 03 3c     lui        v1,0x60
     6::800a6c24 24 48 83 02     and        t1,s4,v1
     6::800a6c28 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a6c34
     6::800a6c2c 00 36 03 3c     _lui       v1,0x3600
     6::800a6c30 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a6c34                           XREF[1]:     OVR_226::800a6c28(j)  
     6::800a6c34 25 18 6f 00     or         v1,v1,t7
     6::800a6c38 04 00 43 ac     sw         v1,0x4(v0)
     6::800a6c3c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a6c40 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a6c44 10 00 50 ac     sw         s0,0x10(v0)
     6::800a6c48 14 00 4c ac     sw         t4,0x14(v0)
     6::800a6c4c 18 00 54 ac     sw         s4,0x18(v0)
     6::800a6c50 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a6c54 20 00 4d ac     sw         t5,0x20(v0)
     6::800a6c58 24 00 55 ac     sw         s5,0x24(v0)
     6::800a6c5c 28 00 09 24     li         t1,0x28
     6::800a6c60 39 00 01 04     bgez       zero,LAB_OVR_226__800a6d48
     6::800a6c64 00 09 0a 3c     _lui       t2,0x900
     6::800a6c68 13 00 6f 82     lb         t7,0x13(s3)
     6::800a6c6c 13 00 90 82     lb         s0,0x13(s4)
     6::800a6c70 13 00 b1 82     lb         s1,0x13(s5)
     6::800a6c74 13 00 d2 82     lb         s2,0x13(s6)
     6::800a6c78 24 18 f0 01     and        v1,t7,s0
     6::800a6c7c 24 18 71 00     and        v1,v1,s1
     6::800a6c80 24 18 72 00     and        v1,v1,s2
     6::800a6c84 4c fd 60 14     bne        v1,zero,LAB_OVR_226__800a61b8
     6::800a6c88 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a6c8c 12 00 90 82     lb         s0,0x12(s4)
     6::800a6c90 12 00 b1 82     lb         s1,0x12(s5)
     6::800a6c94 12 00 d2 82     lb         s2,0x12(s6)
     6::800a6c98 25 78 f0 01     or         t7,t7,s0
     6::800a6c9c 25 78 f1 01     or         t7,t7,s1
     6::800a6ca0 25 78 f2 01     or         t7,t7,s2
     6::800a6ca4 5a 00 e0 15     bne        t7,zero,LAB_OVR_226__800a6e10
     6::800a6ca8 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a6cac 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a6cb0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a6cb4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a6cb8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a6cbc 08 00 90 8e     lw         s0,0x8(s4)
     6::800a6cc0 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a6cc4 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a6cc8 06 00 73 86     lh         s3,0x6(s3)
     6::800a6ccc 06 00 94 86     lh         s4,0x6(s4)
     6::800a6cd0 06 00 b5 86     lh         s5,0x6(s5)
     6::800a6cd4 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a6cd8 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a6cdc 06 00 d4 86     lh         s4,0x6(s6)
     6::800a6ce0 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a6ce4 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a6ce8 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a6cec a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a6cf0 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a6cf4 60 00 03 3c     lui        v1,0x60
     6::800a6cf8 24 48 83 02     and        t1,s4,v1
     6::800a6cfc 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a6d08
     6::800a6d00 00 3e 03 3c     _lui       v1,0x3e00
     6::800a6d04 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a6d08                           XREF[1]:     OVR_226::800a6cfc(j)  
     6::800a6d08 25 18 6f 00     or         v1,v1,t7
     6::800a6d0c 04 00 43 ac     sw         v1,0x4(v0)
     6::800a6d10 08 00 4b ac     sw         t3,0x8(v0)
     6::800a6d14 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a6d18 10 00 50 ac     sw         s0,0x10(v0)
     6::800a6d1c 14 00 4c ac     sw         t4,0x14(v0)
     6::800a6d20 18 00 54 ac     sw         s4,0x18(v0)
     6::800a6d24 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a6d28 20 00 4d ac     sw         t5,0x20(v0)
     6::800a6d2c 24 00 55 ac     sw         s5,0x24(v0)
     6::800a6d30 28 00 52 ac     sw         s2,0x28(v0)
     6::800a6d34 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a6d38 02 1c 15 00     srl        v1,s5,0x10
     6::800a6d3c 30 00 43 ac     sw         v1,0x30(v0)
     6::800a6d40 34 00 09 24     li         t1,0x34
     6::800a6d44 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a6d48                           XREF[1]:     OVR_226::800a6c60(j)  
     6::800a6d48 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a6d4c 00 42 02 00     sll        t0,v0,0x8
     6::800a6d50 02 42 08 00     srl        t0,t0,0x8
     6::800a6d54 25 18 6a 00     or         v1,v1,t2
     6::800a6d58 00 00 43 ac     sw         v1,0x0(v0)
     6::800a6d5c 21 10 49 00     addu       v0,v0,t1
     6::800a6d60 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a6d64 08 00 e0 03     jr         ra
     6::800a6d68 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800a6d6c                           XREF[1]:     OVR_226::800a6be0(j)  
     6::800a6d6c 58 00 3f ac     sw         ra,0x58(at)
     6::800a6d70 98 01 2f 84     lh         t7,0x198(at)
     6::800a6d74 9a 01 30 84     lh         s0,0x19a(at)
     6::800a6d78 9c 01 31 84     lh         s1,0x19c(at)
     6::800a6d7c 00 00 63 86     lh         v1,0x0(s3)
     6::800a6d80 02 00 68 86     lh         t0,0x2(s3)
     6::800a6d84 b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6d88 04 00 69 86     _lh        t1,0x4(s3)
     6::800a6d8c 0b 00 40 05     bltz       t2,LAB_OVR_226__800a6dbc
     6::800a6d90 00 00 83 86     _lh        v1,0x0(s4)
     6::800a6d94 02 00 88 86     lh         t0,0x2(s4)
     6::800a6d98 b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6d9c 04 00 89 86     _lh        t1,0x4(s4)
     6::800a6da0 06 00 40 05     bltz       t2,LAB_OVR_226__800a6dbc
     6::800a6da4 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a6da8 02 00 a8 86     lh         t0,0x2(s5)
     6::800a6dac b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6db0 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a6db4 58 00 3f 8c     lw         ra,0x58(at)
     6::800a6db8 ff fc 41 05     bgez       t2,LAB_OVR_226__800a61b8
                             LAB_OVR_226__800a6dbc                           XREF[2]:     OVR_226::800a6d8c(j), 
                                                                                          OVR_226::800a6da0(j)  
     6::800a6dbc 10 00 2f 8c     lw         t7,0x10(at)
     6::800a6dc0 80 00 23 8c     lw         v1,0x80(at)
     6::800a6dc4 a6 01 28 84     lh         t0,0x1a6(at)
     6::800a6dc8 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a6dcc 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a6dd0 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a6dd4 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a6dd8 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a6ddc 21 68 60 02     move       t5,s3
     6::800a6de0 c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6de4 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a6de8 21 68 80 02     move       t5,s4
     6::800a6dec c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6df0 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a6df4 21 68 a0 02     move       t5,s5
     6::800a6df8 c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6dfc 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a6e00 58 00 3f 8c     lw         ra,0x58(at)
     6::800a6e04 30 00 ef 25     addiu      t7,t7,0x30
     6::800a6e08 08 00 e0 03     jr         ra
     6::800a6e0c 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_226__800a6e10                           XREF[1]:     OVR_226::800a6ca4(j)  
     6::800a6e10 58 00 3f ac     sw         ra,0x58(at)
     6::800a6e14 98 01 2f 84     lh         t7,0x198(at)
     6::800a6e18 9a 01 30 84     lh         s0,0x19a(at)
     6::800a6e1c 9c 01 31 84     lh         s1,0x19c(at)
     6::800a6e20 00 00 63 86     lh         v1,0x0(s3)
     6::800a6e24 02 00 68 86     lh         t0,0x2(s3)
     6::800a6e28 b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6e2c 04 00 69 86     _lh        t1,0x4(s3)
     6::800a6e30 10 00 40 05     bltz       t2,LAB_OVR_226__800a6e74
     6::800a6e34 00 00 83 86     _lh        v1,0x0(s4)
     6::800a6e38 02 00 88 86     lh         t0,0x2(s4)
     6::800a6e3c b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6e40 04 00 89 86     _lh        t1,0x4(s4)
     6::800a6e44 0b 00 40 05     bltz       t2,LAB_OVR_226__800a6e74
     6::800a6e48 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a6e4c 02 00 a8 86     lh         t0,0x2(s5)
     6::800a6e50 b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6e54 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a6e58 06 00 40 05     bltz       t2,LAB_OVR_226__800a6e74
     6::800a6e5c 00 00 c3 86     _lh        v1,0x0(s6)
     6::800a6e60 02 00 c8 86     lh         t0,0x2(s6)
     6::800a6e64 b6 9b 02 0c     jal        FUN_OVR_226__800a6ed8                            undefined FUN_OVR_226__800a6ed8()
     6::800a6e68 04 00 c9 86     _lh        t1,0x4(s6)
     6::800a6e6c 58 00 3f 8c     lw         ra,0x58(at)
     6::800a6e70 d1 fc 41 05     bgez       t2,LAB_OVR_226__800a61b8
                             LAB_OVR_226__800a6e74                           XREF[3]:     OVR_226::800a6e30(j), 
                                                                                          OVR_226::800a6e44(j), 
                                                                                          OVR_226::800a6e58(j)  
     6::800a6e74 10 00 2f 8c     lw         t7,0x10(at)
     6::800a6e78 80 00 23 8c     lw         v1,0x80(at)
     6::800a6e7c a6 01 28 84     lh         t0,0x1a6(at)
     6::800a6e80 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a6e84 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a6e88 01 00 63 34     ori        v1,v1,0x1
     6::800a6e8c 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a6e90 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a6e94 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a6e98 21 68 60 02     move       t5,s3
     6::800a6e9c c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6ea0 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a6ea4 21 68 80 02     move       t5,s4
     6::800a6ea8 c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6eac 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a6eb0 21 68 a0 02     move       t5,s5
     6::800a6eb4 c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6eb8 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a6ebc 21 68 c0 02     move       t5,s6
     6::800a6ec0 c6 9b 02 0c     jal        FUN_OVR_226__800a6f18                            undefined FUN_OVR_226__800a6f18()
     6::800a6ec4 30 00 f0 25     _addiu     s0,t7,0x30
     6::800a6ec8 58 00 3f 8c     lw         ra,0x58(at)
     6::800a6ecc 3c 00 ef 25     addiu      t7,t7,0x3c
     6::800a6ed0 08 00 e0 03     jr         ra
     6::800a6ed4 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6ed8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6ed8                           XREF[7]:     FUN_OVR_226__800a661c:800a6d84(c
                                                                                          FUN_OVR_226__800a661c:800a6d98(c
                                                                                          FUN_OVR_226__800a661c:800a6dac(c
                                                                                          FUN_OVR_226__800a661c:800a6e28(c
                                                                                          FUN_OVR_226__800a661c:800a6e3c(c
                                                                                          FUN_OVR_226__800a661c:800a6e50(c
                                                                                          FUN_OVR_226__800a661c:800a6e64(c
     6::800a6ed8 23 18 6f 00     subu       v1,v1,t7
     6::800a6edc 02 00 61 04     bgez       v1,LAB_OVR_226__800a6ee8
     6::800a6ee0 23 40 10 01     _subu      t0,t0,s0
     6::800a6ee4 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_226__800a6ee8                           XREF[1]:     OVR_226::800a6edc(j)  
     6::800a6ee8 00 ff 6b 24     addiu      t3,v1,-0x100
     6::800a6eec 02 00 01 05     bgez       t0,LAB_OVR_226__800a6ef8
     6::800a6ef0 23 48 31 01     _subu      t1,t1,s1
     6::800a6ef4 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_226__800a6ef8                           XREF[1]:     OVR_226::800a6eec(j)  
     6::800a6ef8 80 fe 0c 25     addiu      t4,t0,-0x180
     6::800a6efc 02 00 21 05     bgez       t1,LAB_OVR_226__800a6f08
     6::800a6f00 00 00 00 00     _nop
     6::800a6f04 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_226__800a6f08                           XREF[1]:     OVR_226::800a6efc(j)  
     6::800a6f08 00 ff 2d 25     addiu      t5,t1,-0x100
     6::800a6f0c 24 58 6c 01     and        t3,t3,t4
     6::800a6f10 08 00 e0 03     jr         ra
     6::800a6f14 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a6f18()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a6f18                           XREF[7]:     FUN_OVR_226__800a661c:800a6de0(c
                                                                                          FUN_OVR_226__800a661c:800a6dec(c
                                                                                          FUN_OVR_226__800a661c:800a6df8(c
                                                                                          FUN_OVR_226__800a661c:800a6e9c(c
                                                                                          FUN_OVR_226__800a661c:800a6ea8(c
                                                                                          FUN_OVR_226__800a661c:800a6eb4(c
                                                                                          FUN_OVR_226__800a661c:800a6ec0(c
     6::800a6f18 13 00 a3 81     lb         v1,0x13(t5)
     6::800a6f1c 00 00 a8 8d     lw         t0,0x0(t5)
     6::800a6f20 04 00 a9 8d     lw         t1,0x4(t5)
     6::800a6f24 08 00 aa 8d     lw         t2,0x8(t5)
     6::800a6f28 00 1e 03 00     sll        v1,v1,0x18
     6::800a6f2c 25 50 43 01     or         t2,t2,v1
     6::800a6f30 00 00 08 ae     sw         t0,0x0(s0)
     6::800a6f34 04 00 09 ae     sw         t1,0x4(s0)
     6::800a6f38 08 00 e0 03     jr         ra
     6::800a6f3c 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_226__800a6f40                           XREF[1]:     OVR_226::800ab444(*)  
     6::800a6f40 09 80 08 3c     lui        t0,0x8009
     6::800a6f44 04 64 08 25     addiu      t0,t0,0x6404
     6::800a6f48 64 00 28 ac     sw         t0=>DAT_80096404,0x64(at)                        = ??
     6::800a6f4c 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_226__800a6f50                           XREF[1]:     OVR_226::800a7228(j)  
     6::800a6f50 bd 00 80 10     beq        a0,zero,LAB_OVR_226__800a7248
     6::800a6f54 00 00 00 00     _nop
     6::800a6f58 1c 00 78 8c     lw         t8,0x1c(v1)
     6::800a6f5c 18 00 79 8c     lw         t9,0x18(v1)
     6::800a6f60 c8 00 2a 8c     lw         t2,0xc8(at)
     6::800a6f64 3c 00 08 97     lhu        t0,0x3c(t8)
     6::800a6f68 68 00 39 ac     sw         t9,0x68(at)
     6::800a6f6c c2 48 08 00     srl        t1,t0,0x3
     6::800a6f70 fc 01 29 31     andi       t1,t1,0x1fc
     6::800a6f74 21 48 2a 01     addu       t1,t1,t2
     6::800a6f78 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a6f7c 00 00 29 8d     lw         t1,0x0(t1)
     6::800a6f80 1f 00 08 31     andi       t0,t0,0x1f
     6::800a6f84 bc 00 28 ac     sw         t0,0xbc(at)
     6::800a6f88 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_226__800a6f8c                           XREF[1]:     OVR_226::800a721c(j)  
     6::800a6f8c 30 00 23 8c     lw         v1,0x30(at)
     6::800a6f90 00 1a 48 24     addiu      t0,v0,0x1a00
     6::800a6f94 23 18 68 00     subu       v1,v1,t0
     6::800a6f98 c6 e7 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a6f9c bc 00 23 8c     _lw        v1,0xbc(at)
     6::800a6fa0 c4 00 28 8c     lw         t0,0xc4(at)
     6::800a6fa4 06 00 61 04     bgez       v1,LAB_OVR_226__800a6fc0
     6::800a6fa8 c0 00 29 8c     _lw        t1,0xc0(at)
     6::800a6fac 1f 00 03 24     li         v1,0x1f
     6::800a6fb0 04 00 28 8d     lw         t0,0x4(t1)
     6::800a6fb4 04 00 29 25     addiu      t1,t1,0x4
     6::800a6fb8 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a6fbc c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_226__800a6fc0                           XREF[1]:     OVR_226::800a6fa4(j)  
     6::800a6fc0 04 40 68 00     sllv       t0,t0,v1
     6::800a6fc4 ff ff 63 24     addiu      v1,v1,-0x1
     6::800a6fc8 91 00 01 05     bgez       t0,LAB_OVR_226__800a7210
     6::800a6fcc bc 00 23 ac     _sw        v1,0xbc(at)
     6::800a6fd0 b4 01 3e 24     addiu      s8,at,0x1b4
     6::800a6fd4 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a6fd8 00 00 14 8f     lw         s4,0x0(t8)
     6::800a6fdc 04 00 16 8f     lw         s6,0x4(t8)
     6::800a6fe0 ff ff 93 32     andi       s3,s4,0xffff
     6::800a6fe4 00 99 13 00     sll        s3,s3,0x4
     6::800a6fe8 21 98 77 02     addu       s3,s3,s7
     6::800a6fec 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a6ff4 02 a4 14 00     srl        s4,s4,0x10
     6::800a6ff8 00 a1 14 00     sll        s4,s4,0x4
     6::800a6ffc 21 a0 97 02     addu       s4,s4,s7
     6::800a7000 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a7008 ff ff d5 32     andi       s5,s6,0xffff
     6::800a700c 00 a9 15 00     sll        s5,s5,0x4
     6::800a7010 21 a8 b7 02     addu       s5,s5,s7
     6::800a7014 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a701c 02 b4 16 00     srl        s6,s6,0x10
     6::800a7020 00 b1 16 00     sll        s6,s6,0x4
     6::800a7024 30 00 28 4a     RTPT
     6::800a7028 21 b0 d7 02     addu       s6,s6,s7
     6::800a702c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a7030 08 00 90 8e     lw         s0,0x8(s4)
     6::800a7034 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a7038 08 00 cf af     sw         t7,0x8(s8)
     6::800a703c 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a7040 30 00 d1 af     sw         s1,0x30(s8)
     6::800a7044 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a7048 00 f8 43 48     gte_stFLAG v1
     6::800a704c 10 00 d1 eb     gte_stSZ1  0x10(s8)
     6::800a7050 80 1b 03 00     sll        v1,v1,0xe
     6::800a7054 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a7058 75 00 60 14     bne        v1,zero,LAB_OVR_226__800a7230
     6::800a705c 08 00 14 8f     _lw        s4,0x8(t8)
     6::800a7060 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a7064 24 00 d2 eb     gte_stSZ2  0x24(s8)
     6::800a7068 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a706c 38 00 d3 eb     gte_stSZ3  0x38(s8)
     6::800a7070 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a7074 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a7078 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a707c 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a7080 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a7084 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a7088 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a7090 ff ff 93 32     andi       s3,s4,0xffff
     6::800a7094 00 99 13 00     sll        s3,s3,0x4
     6::800a7098 21 98 77 02     addu       s3,s3,s7
     6::800a709c 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a70a4 02 a4 14 00     srl        s4,s4,0x10
     6::800a70a8 00 a1 14 00     sll        s4,s4,0x4
     6::800a70ac 21 a0 97 02     addu       s4,s4,s7
     6::800a70b0 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a70b8 21 c8 20 00     move       t9,at
     6::800a70bc 00 00 00 00     nop
     6::800a70c0 30 00 28 4a     RTPT
     6::800a70c4 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a70c8 08 00 70 8e     lw         s0,0x8(s3)
     6::800a70cc 08 00 91 8e     lw         s1,0x8(s4)
     6::800a70d0 44 00 cf af     sw         t7,0x44(s8)
     6::800a70d4 58 00 d0 af     sw         s0,0x58(s8)
     6::800a70d8 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a70dc 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a70e0 00 f8 43 48     gte_stFLAG v1
     6::800a70e4 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     6::800a70e8 80 1b 03 00     sll        v1,v1,0xe
     6::800a70ec c2 1f 03 00     srl        v1,v1,0x1f
     6::800a70f0 4f 00 60 14     bne        v1,zero,LAB_OVR_226__800a7230
     6::800a70f4 0c 00 14 8f     _lw        s4,0xc(t8)
     6::800a70f8 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a70fc 60 00 d2 eb     gte_stSZ2  0x60(s8)
     6::800a7100 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a7104 74 00 d3 eb     gte_stSZ3  0x74(s8)
     6::800a7108 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a710c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a7110 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a7114 10 00 15 97     lhu        s5,0x10(t8)
     6::800a7118 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a711c 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a7120 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a7124 ff ff 93 32     andi       s3,s4,0xffff
     6::800a7128 00 99 13 00     sll        s3,s3,0x4
     6::800a712c 21 98 77 02     addu       s3,s3,s7
     6::800a7130 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a7138 02 a4 14 00     srl        s4,s4,0x10
     6::800a713c 00 a1 14 00     sll        s4,s4,0x4
     6::800a7140 21 a0 97 02     addu       s4,s4,s7
     6::800a7144 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a714c 14 00 09 8f     lw         t1,0x14(t8)
     6::800a7150 00 a9 15 00     sll        s5,s5,0x4
     6::800a7154 21 a8 b7 02     addu       s5,s5,s7
     6::800a7158 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a7160 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a7164 08 00 08 24     li         t0,0x8
     6::800a7168 30 00 28 4a     RTPT
     6::800a716c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a7170 08 00 90 8e     lw         s0,0x8(s4)
     6::800a7174 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a7178 80 00 cf af     sw         t7,0x80(s8)
     6::800a717c 94 00 d0 af     sw         s0,0x94(s8)
     6::800a7180 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a7184 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a7188 00 f8 43 48     gte_stFLAG v1
     6::800a718c 88 00 d1 eb     gte_stSZ1  0x88(s8)
     6::800a7190 80 1b 03 00     sll        v1,v1,0xe
     6::800a7194 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a7198 25 00 60 14     bne        v1,zero,LAB_OVR_226__800a7230
     6::800a719c 98 00 cd eb     _gte_stS   0x98(s8)
     6::800a71a0 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     6::800a71a4 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a71a8 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     6::800a71ac 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a71b0 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a71b4 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a71b8 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a71bc a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a71c0 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a71c4 50 00 03 3c     lui        v1,0x50
     6::800a71c8 78 64 63 34     ori        v1,v1,0x6478
     6::800a71cc 9a 9d 02 0c     jal        FUN_OVR_226__800a7668                            undefined FUN_OVR_226__800a7668()
     6::800a71d0 00 00 0a 24     _li        t2,0x0
     6::800a71d4 14 50 03 3c     lui        v1,0x5014
     6::800a71d8 8c 78 63 34     ori        v1,v1,0x788c
     6::800a71dc 0d 00 08 24     li         t0,0xd
     6::800a71e0 9a 9d 02 0c     jal        FUN_OVR_226__800a7668                            undefined FUN_OVR_226__800a7668()
     6::800a71e4 04 00 0a 24     _li        t2,0x4
     6::800a71e8 78 64 03 3c     lui        v1,0x6478
     6::800a71ec a0 28 63 34     ori        v1,v1,0x28a0
     6::800a71f0 12 00 08 24     li         t0,0x12
     6::800a71f4 9a 9d 02 0c     jal        FUN_OVR_226__800a7668                            undefined FUN_OVR_226__800a7668()
     6::800a71f8 08 00 0a 24     _li        t2,0x8
     6::800a71fc 8c 78 03 3c     lui        v1,0x788c
     6::800a7200 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a7204 17 00 08 24     li         t0,0x17
     6::800a7208 9a 9d 02 0c     jal        FUN_OVR_226__800a7668                            undefined FUN_OVR_226__800a7668()
     6::800a720c 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a7210                           XREF[2]:     OVR_226::800a6fc8(j), 
                                                                                          OVR_226::800a7240(j)  
     6::800a7210 68 00 39 8c     lw         t9,0x68(at)
     6::800a7214 5c 00 18 27     addiu      t8,t8,0x5c
     6::800a7218 ff ff 39 27     addiu      t9,t9,-0x1
     6::800a721c 5b ff 20 1f     bgtz       t9,LAB_OVR_226__800a6f8c
     6::800a7220 68 00 39 ac     _sw        t9,0x68(at)
     6::800a7224 00 00 84 8c     lw         a0,0x0(a0)
     6::800a7228 49 ff 01 04     bgez       zero,LAB_OVR_226__800a6f50
     6::800a722c 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_226__800a7230                           XREF[3]:     OVR_226::800a7058(j), 
                                                                                          OVR_226::800a70f0(j), 
                                                                                          OVR_226::800a7198(j)  
     6::800a7230 64 00 28 8c     lw         t0,0x64(at)
     6::800a7234 00 00 00 00     nop
     6::800a7238 00 00 18 ad     sw         t8,0x0(t0)
     6::800a723c 04 00 08 25     addiu      t0,t0,0x4
     6::800a7240 f3 ff 01 04     bgez       zero,LAB_OVR_226__800a7210
     6::800a7244 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_226__800a7248                           XREF[1]:     OVR_226::800a6f50(j)  
     6::800a7248 64 00 28 8c     lw         t0,0x64(at)
     6::800a724c 0e e7 01 04     bgez       zero,LAB_OVR_226__800a0e88
     6::800a7250 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_226__800a7254                           XREF[6]:     FUN_OVR_226__800a7588:800a75fc(j
                                                                                          FUN_OVR_226__800a7588:800a7604(j
                                                                                          FUN_OVR_226__800a7588:800a7638(j
                                                                                          OVR_226::800a773c(j), 
                                                                                          OVR_226::800a7744(j), 
                                                                                          OVR_226::800a7770(j)  
     6::800a7254 08 00 e0 03     jr         ra
     6::800a7258 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a725c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a725c                           XREF[4]:     FUN_OVR_226__800a72ac:800a7334(j
                                                                                          FUN_OVR_226__800a72ac:800a73cc(c
                                                                                          FUN_OVR_226__800a72ac:800a73f4(c
                                                                                          FUN_OVR_226__800a72ac:800a7460(c
     6::800a725c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a7260 50 00 d4 27     addiu      s4,s8,0x50
     6::800a7264 64 00 d5 27     addiu      s5,s8,0x64
     6::800a7268 c7 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a726c 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7270()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7270                           XREF[6]:     FUN_OVR_226__800a72ac:800a733c(c
                                                                                          FUN_OVR_226__800a72ac:800a73dc(j
                                                                                          FUN_OVR_226__800a72ac:800a73ec(c
                                                                                          FUN_OVR_226__800a72ac:800a741c(c
                                                                                          FUN_OVR_226__800a72ac:800a743c(c
                                                                                          FUN_OVR_226__800a72ac:800a7470(c
     6::800a7270 50 00 d3 27     addiu      s3,s8,0x50
     6::800a7274 14 00 d4 27     addiu      s4,s8,0x14
     6::800a7278 78 00 d5 27     addiu      s5,s8,0x78
     6::800a727c c2 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a7280 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7284()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7284                           XREF[6]:     FUN_OVR_226__800a72ac:800a7364(c
                                                                                          FUN_OVR_226__800a72ac:800a73c4(c
                                                                                          FUN_OVR_226__800a72ac:800a7404(j
                                                                                          FUN_OVR_226__800a72ac:800a7414(c
                                                                                          FUN_OVR_226__800a72ac:800a7444(c
                                                                                          FUN_OVR_226__800a72ac:800a7480(c
     6::800a7284 64 00 d3 27     addiu      s3,s8,0x64
     6::800a7288 78 00 d4 27     addiu      s4,s8,0x78
     6::800a728c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a7290 bd 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a7294 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a7298                           XREF[4]:     OVR_226::800a73b4(j), 
                                                                                          OVR_226::800a742c(j), 
                                                                                          OVR_226::800a7454(j), 
                                                                                          OVR_226::800a7498(j)  
     6::800a7298 78 00 d3 27     addiu      s3,s8,0x78
     6::800a729c 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a72a0 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a72a4 b8 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a72a8 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a72ac()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a72ac                           XREF[2]:     OVR_226::800a735c(c), 
                                                                                          OVR_226::800a7434(c)  
     6::800a72ac 64 00 d3 27     addiu      s3,s8,0x64
     6::800a72b0 00 00 d4 27     addiu      s4,s8,0x0
     6::800a72b4 78 00 d5 27     addiu      s5,s8,0x78
     6::800a72b8 b3 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a72bc 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a72c0                           XREF[2]:     OVR_226::800a7374(j), 
                                                                                          OVR_226::800a73e4(c)  
     6::800a72c0 14 00 d3 27     addiu      s3,s8,0x14
     6::800a72c4 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a72c8 78 00 d5 27     addiu      s5,s8,0x78
     6::800a72cc ae 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a72d0 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a72d4                           XREF[2]:     OVR_226::800a7344(c), 
                                                                                          OVR_226::800a740c(c)  
     6::800a72d4 28 00 d3 27     addiu      s3,s8,0x28
     6::800a72d8 00 00 d4 27     addiu      s4,s8,0x0
     6::800a72dc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a72e0 a9 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a72e4 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a72e8                           XREF[2]:     OVR_226::800a7354(j), 
                                                                                          OVR_226::800a73bc(c)  
     6::800a72e8 28 00 d3 27     addiu      s3,s8,0x28
     6::800a72ec 78 00 d4 27     addiu      s4,s8,0x78
     6::800a72f0 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a72f4 a4 00 01 04     bgez       zero,FUN_OVR_226__800a7588
     6::800a72f8 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a72fc 50 00 d3 27     addiu      s3,s8,0x50
     6::800a7300 14 00 d4 27     addiu      s4,s8,0x14
     6::800a7304 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7308 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a730c 62 9d 02 0c     jal        FUN_OVR_226__800a7588                            undefined FUN_OVR_226__800a7588()
     6::800a7310 0c 00 0a 24     _li        t2,0xc
     6::800a7314 64 00 d3 27     addiu      s3,s8,0x64
     6::800a7318 78 00 d4 27     addiu      s4,s8,0x78
     6::800a731c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a7320 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a7324 62 9d 02 0c     jal        FUN_OVR_226__800a7588                            undefined FUN_OVR_226__800a7588()
     6::800a7328 0c 00 0a 24     _li        t2,0xc
     6::800a732c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7330 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7334 c9 ff 01 04     bgez       zero,FUN_OVR_226__800a725c
     6::800a7338 0c 00 0a 24     _li        t2,0xc
     6::800a733c 9c 9c 02 0c     jal        FUN_OVR_226__800a7270                            undefined FUN_OVR_226__800a7270()
     6::800a7340 0c 00 0a 24     _li        t2,0xc
     6::800a7344 b5 9c 02 0c     jal        SUB_OVR_226__800a72d4
     6::800a7348 0c 00 0a 24     _li        t2,0xc
     6::800a734c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7350 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7354 e4 ff 01 04     bgez       zero,SUB_OVR_226__800a72e8
     6::800a7358 0c 00 0a 24     _li        t2,0xc
     6::800a735c ab 9c 02 0c     jal        FUN_OVR_226__800a72ac                            undefined FUN_OVR_226__800a72ac()
     6::800a7360 0c 00 0a 24     _li        t2,0xc
     6::800a7364 a1 9c 02 0c     jal        FUN_OVR_226__800a7284                            undefined FUN_OVR_226__800a7284()
     6::800a7368 0c 00 0a 24     _li        t2,0xc
     6::800a736c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7370 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7374 d2 ff 01 04     bgez       zero,SUB_OVR_226__800a72c0
     6::800a7378 0c 00 0a 24     _li        t2,0xc
     6::800a737c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a7380 14 00 d4 27     addiu      s4,s8,0x14
     6::800a7384 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7388 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a738c 62 9d 02 0c     jal        FUN_OVR_226__800a7588                            undefined FUN_OVR_226__800a7588()
     6::800a7390 0c 00 0a 24     _li        t2,0xc
     6::800a7394 00 00 d3 27     addiu      s3,s8,0x0
     6::800a7398 78 00 d4 27     addiu      s4,s8,0x78
     6::800a739c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a73a0 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a73a4 62 9d 02 0c     jal        FUN_OVR_226__800a7588                            undefined FUN_OVR_226__800a7588()
     6::800a73a8 0c 00 0a 24     _li        t2,0xc
     6::800a73ac 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a73b0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a73b4 b8 ff 01 04     bgez       zero,LAB_OVR_226__800a7298
     6::800a73b8 0c 00 0a 24     _li        t2,0xc
     6::800a73bc ba 9c 02 0c     jal        SUB_OVR_226__800a72e8
     6::800a73c0 0c 00 0a 24     _li        t2,0xc
     6::800a73c4 a1 9c 02 0c     jal        FUN_OVR_226__800a7284                            undefined FUN_OVR_226__800a7284()
     6::800a73c8 04 00 0a 24     _li        t2,0x4
     6::800a73cc 97 9c 02 0c     jal        FUN_OVR_226__800a725c                            undefined FUN_OVR_226__800a725c()
     6::800a73d0 0c 00 0a 24     _li        t2,0xc
     6::800a73d4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a73d8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a73dc a4 ff 01 04     bgez       zero,FUN_OVR_226__800a7270
     6::800a73e0 0c 00 0a 24     _li        t2,0xc
     6::800a73e4 b0 9c 02 0c     jal        SUB_OVR_226__800a72c0
     6::800a73e8 0c 00 0a 24     _li        t2,0xc
     6::800a73ec 9c 9c 02 0c     jal        FUN_OVR_226__800a7270                            undefined FUN_OVR_226__800a7270()
     6::800a73f0 04 00 0a 24     _li        t2,0x4
     6::800a73f4 97 9c 02 0c     jal        FUN_OVR_226__800a725c                            undefined FUN_OVR_226__800a725c()
     6::800a73f8 0c 00 0a 24     _li        t2,0xc
     6::800a73fc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7400 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7404 9f ff 01 04     bgez       zero,FUN_OVR_226__800a7284
     6::800a7408 0c 00 0a 24     _li        t2,0xc
     6::800a740c b5 9c 02 0c     jal        SUB_OVR_226__800a72d4
     6::800a7410 0c 00 0a 24     _li        t2,0xc
     6::800a7414 a1 9c 02 0c     jal        FUN_OVR_226__800a7284                            undefined FUN_OVR_226__800a7284()
     6::800a7418 08 00 0a 24     _li        t2,0x8
     6::800a741c 9c 9c 02 0c     jal        FUN_OVR_226__800a7270                            undefined FUN_OVR_226__800a7270()
     6::800a7420 0c 00 0a 24     _li        t2,0xc
     6::800a7424 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7428 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a742c 9a ff 01 04     bgez       zero,LAB_OVR_226__800a7298
     6::800a7430 0c 00 0a 24     _li        t2,0xc
     6::800a7434 ab 9c 02 0c     jal        FUN_OVR_226__800a72ac                            undefined FUN_OVR_226__800a72ac()
     6::800a7438 0c 00 0a 24     _li        t2,0xc
     6::800a743c 9c 9c 02 0c     jal        FUN_OVR_226__800a7270                            undefined FUN_OVR_226__800a7270()
     6::800a7440 08 00 0a 24     _li        t2,0x8
     6::800a7444 a1 9c 02 0c     jal        FUN_OVR_226__800a7284                            undefined FUN_OVR_226__800a7284()
     6::800a7448 0c 00 0a 24     _li        t2,0xc
     6::800a744c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7450 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7454 90 ff 01 04     bgez       zero,LAB_OVR_226__800a7298
     6::800a7458 0c 00 0a 24     _li        t2,0xc
     6::800a745c b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a7460 97 9c 02 0c     jal        FUN_OVR_226__800a725c                            undefined FUN_OVR_226__800a725c()
     6::800a7464 0c 00 0a 24     _li        t2,0xc
     6::800a7468 0c 00 03 24     li         v1,0xc
     6::800a746c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a7470 9c 9c 02 0c     jal        FUN_OVR_226__800a7270                            undefined FUN_OVR_226__800a7270()
     6::800a7474 0c 00 0a 24     _li        t2,0xc
     6::800a7478 30 00 03 24     li         v1,0x30
     6::800a747c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a7480 a1 9c 02 0c     jal        FUN_OVR_226__800a7284                            undefined FUN_OVR_226__800a7284()
     6::800a7484 0c 00 0a 24     _li        t2,0xc
     6::800a7488 3c 00 03 24     li         v1,0x3c
     6::800a748c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a7490 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7494 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7498 7f ff 01 04     bgez       zero,LAB_OVR_226__800a7298
     6::800a749c 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a74a0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a74a0                           XREF[5]:     FUN_OVR_226__800a7668:800a78fc(c
                                                                                          FUN_OVR_226__800a7668:800a7910(c
                                                                                          FUN_OVR_226__800a7668:800a7924(c
                                                                                          FUN_OVR_226__800a7668:800a7938(c
                                                                                          FUN_OVR_226__800a7668:800a794c(c
     6::800a74a0 00 00 ab 85     lh         t3,0x0(t5)
     6::800a74a4 00 00 cc 85     lh         t4,0x0(t6)
     6::800a74a8 00 00 eb a5     sh         t3,0x0(t7)
     6::800a74ac 21 18 6c 01     addu       v1,t3,t4
     6::800a74b0 43 18 03 00     sra        v1,v1,0x1
     6::800a74b4 00 00 03 a6     sh         v1,0x0(s0)
     6::800a74b8 02 00 ab 85     lh         t3,0x2(t5)
     6::800a74bc 02 00 cc 85     lh         t4,0x2(t6)
     6::800a74c0 02 00 eb a5     sh         t3,0x2(t7)
     6::800a74c4 21 18 6c 01     addu       v1,t3,t4
     6::800a74c8 43 18 03 00     sra        v1,v1,0x1
     6::800a74cc 02 00 03 a6     sh         v1,0x2(s0)
     6::800a74d0 04 00 ab 85     lh         t3,0x4(t5)
     6::800a74d4 04 00 cc 85     lh         t4,0x4(t6)
     6::800a74d8 04 00 eb a5     sh         t3,0x4(t7)
     6::800a74dc 21 18 6c 01     addu       v1,t3,t4
     6::800a74e0 43 18 03 00     sra        v1,v1,0x1
     6::800a74e4 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a74e8 00 08 83 48     gte_ldVZ0  v1
     6::800a74ec 04 00 03 a6     sh         v1,0x4(s0)
     6::800a74f0 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a74f4 01 00 18 4a     RTPS
     6::800a74f8 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a74fc 08 00 eb a1     sb         t3,0x8(t7)
     6::800a7500 21 18 6c 01     addu       v1,t3,t4
     6::800a7504 43 18 03 00     sra        v1,v1,0x1
     6::800a7508 08 00 03 a2     sb         v1,0x8(s0)
     6::800a750c 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a7510 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a7514 09 00 eb a1     sb         t3,0x9(t7)
     6::800a7518 21 18 6c 01     addu       v1,t3,t4
     6::800a751c 43 18 03 00     sra        v1,v1,0x1
     6::800a7520 09 00 03 a2     sb         v1,0x9(s0)
     6::800a7524 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a7528 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a752c 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a7530 21 18 6c 01     addu       v1,t3,t4
     6::800a7534 43 18 03 00     sra        v1,v1,0x1
     6::800a7538 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a753c 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a7540 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a7544 06 00 eb a1     sb         t3,0x6(t7)
     6::800a7548 21 18 6c 01     addu       v1,t3,t4
     6::800a754c 43 18 03 00     sra        v1,v1,0x1
     6::800a7550 06 00 03 a2     sb         v1,0x6(s0)
     6::800a7554 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a7558 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a755c 07 00 eb a1     sb         t3,0x7(t7)
     6::800a7560 21 18 6c 01     addu       v1,t3,t4
     6::800a7564 43 18 03 00     sra        v1,v1,0x1
     6::800a7568 07 00 03 a2     sb         v1,0x7(s0)
     6::800a756c 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a7570 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a7574 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a7578 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a757c 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a7580 08 00 e0 03     jr         ra
     6::800a7584 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7588()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7588                           XREF[12]:    FUN_OVR_226__800a725c:800a7268(j
                                                                                          FUN_OVR_226__800a7270:800a727c(j
                                                                                          FUN_OVR_226__800a7284:800a7290(j
                                                                                          FUN_OVR_226__800a72ac:800a72a4(j
                                                                                          FUN_OVR_226__800a72ac:800a72b8(j
                                                                                          FUN_OVR_226__800a72ac:800a72cc(j
                                                                                          FUN_OVR_226__800a72ac:800a72e0(j
                                                                                          FUN_OVR_226__800a72ac:800a72f4(j
                                                                                          FUN_OVR_226__800a72ac:800a730c(c
                                                                                          FUN_OVR_226__800a72ac:800a7324(c
                                                                                          FUN_OVR_226__800a72ac:800a738c(c
                                                                                          FUN_OVR_226__800a72ac:800a73a4(c
     6::800a7588 70 00 2a ac     sw         t2,0x70(at)
     6::800a758c 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a7590 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a7594 94 01 2a 8c     lw         t2,0x194(at)
     6::800a7598 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a759c 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a75a0 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a75a4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a75a8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a75ac 06 00 40 4b     NCLIP
     6::800a75b0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a75b4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a75b8 23 78 68 01     subu       t7,t3,t0
     6::800a75bc 23 80 88 01     subu       s0,t4,t0
     6::800a75c0 23 88 a8 01     subu       s1,t5,t0
     6::800a75c4 23 90 c8 01     subu       s2,t6,t0
     6::800a75c8 00 c0 08 48     gte_stMAC0 t0
     6::800a75cc 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a75d0 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a75dc
     6::800a75d4 22 40 08 00     _sub       t0,zero,t0
     6::800a75d8 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a75dc                           XREF[1]:     OVR_226::800a75d0(j)  
     6::800a75dc 06 00 40 4b     NCLIP
     6::800a75e0 24 18 6c 01     and        v1,t3,t4
     6::800a75e4 24 18 6d 00     and        v1,v1,t5
     6::800a75e8 24 18 6e 00     and        v1,v1,t6
     6::800a75ec 25 78 f0 01     or         t7,t7,s0
     6::800a75f0 25 78 f1 01     or         t7,t7,s1
     6::800a75f4 27 78 f2 01     nor        t7,t7,s2
     6::800a75f8 25 78 e3 01     or         t7,t7,v1
     6::800a75fc 15 ff e0 05     bltz       t7,LAB_OVR_226__800a7254
     6::800a7600 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a7604 13 ff e0 05     bltz       t7,LAB_OVR_226__800a7254
     6::800a7608 00 c0 03 48     _gte_stM   v1
     6::800a760c 25 40 09 01     or         t0,t0,t1
     6::800a7610 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a761c
     6::800a7614 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a7618 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a761c                           XREF[1]:     OVR_226::800a7610(j)  
     6::800a761c 80 40 08 00     sll        t0,t0,0x2
     6::800a7620 25 18 69 00     or         v1,v1,t1
     6::800a7624 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a7628 c0 18 03 00     sll        v1,v1,0x3
     6::800a762c 70 00 2a 8c     lw         t2,0x70(at)
     6::800a7630 25 18 68 00     or         v1,v1,t0
     6::800a7634 24 18 6a 00     and        v1,v1,t2
     6::800a7638 06 ff 60 10     beq        v1,zero,LAB_OVR_226__800a7254
     6::800a763c 70 00 23 ac     _sw        v1,0x70(at)
     6::800a7640 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a7644 24 03 28 24     addiu      t0,at,0x324
     6::800a7648 d5 00 1e 11     beq        t0,s8,LAB_OVR_226__800a79a0
     6::800a764c 04 00 39 27     _addiu     t9,t9,0x4
     6::800a7650 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a7654 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a7658 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a765c 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a7660 91 00 01 04     bgez       zero,LAB_OVR_226__800a78a8
     6::800a7664 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7668()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7668                           XREF[4]:     OVR_226::800a71cc(c), 
                                                                                          OVR_226::800a71e0(c), 
                                                                                          OVR_226::800a71f4(c), 
                                                                                          OVR_226::800a7208(c)  
     6::800a7668 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a766c b4 00 ca af     sw         t2,0xb4(s8)
     6::800a7670 06 50 09 01     srlv       t2,t1,t0
     6::800a7674 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a7678 80 50 0a 00     sll        t2,t2,0x2
     6::800a767c 21 50 41 01     addu       t2,t2,at
     6::800a7680 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a7684 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a7688 94 01 2a ac     sw         t2,0x194(at)
     6::800a768c 02 9e 0a 00     srl        s3,t2,0x18
     6::800a7690 1f 00 73 32     andi       s3,s3,0x1f
     6::800a7694 06 98 63 02     srlv       s3,v1,s3
     6::800a7698 ff 00 73 32     andi       s3,s3,0xff
     6::800a769c 21 98 7e 02     addu       s3,s3,s8
     6::800a76a0 02 a4 0a 00     srl        s4,t2,0x10
     6::800a76a4 1f 00 94 32     andi       s4,s4,0x1f
     6::800a76a8 06 a0 83 02     srlv       s4,v1,s4
     6::800a76ac ff 00 94 32     andi       s4,s4,0xff
     6::800a76b0 21 a0 9e 02     addu       s4,s4,s8
     6::800a76b4 02 aa 0a 00     srl        s5,t2,0x8
     6::800a76b8 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a76bc 06 a8 a3 02     srlv       s5,v1,s5
     6::800a76c0 ff 00 b5 32     andi       s5,s5,0xff
     6::800a76c4 21 a8 be 02     addu       s5,s5,s8
     6::800a76c8 1f 00 56 31     andi       s6,t2,0x1f
     6::800a76cc 06 b0 c3 02     srlv       s6,v1,s6
     6::800a76d0 ff 00 d6 32     andi       s6,s6,0xff
     6::800a76d4 21 b0 de 02     addu       s6,s6,s8
     6::800a76d8 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a76dc 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a76e0 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a76e4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a76e8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a76ec 06 00 40 4b     NCLIP
     6::800a76f0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a76f4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a76f8 23 78 68 01     subu       t7,t3,t0
     6::800a76fc 23 80 88 01     subu       s0,t4,t0
     6::800a7700 23 88 a8 01     subu       s1,t5,t0
     6::800a7704 23 90 c8 01     subu       s2,t6,t0
     6::800a7708 00 c0 08 48     gte_stMAC0 t0
     6::800a770c 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a7710 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a771c
     6::800a7714 22 40 08 00     _sub       t0,zero,t0
     6::800a7718 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a771c                           XREF[1]:     OVR_226::800a7710(j)  
     6::800a771c 06 00 40 4b     NCLIP
     6::800a7720 24 18 6c 01     and        v1,t3,t4
     6::800a7724 24 18 6d 00     and        v1,v1,t5
     6::800a7728 24 18 6e 00     and        v1,v1,t6
     6::800a772c 25 78 f0 01     or         t7,t7,s0
     6::800a7730 25 78 f1 01     or         t7,t7,s1
     6::800a7734 27 78 f2 01     nor        t7,t7,s2
     6::800a7738 25 78 e3 01     or         t7,t7,v1
     6::800a773c c5 fe e0 05     bltz       t7,LAB_OVR_226__800a7254
     6::800a7740 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a7744 c3 fe e0 05     bltz       t7,LAB_OVR_226__800a7254
     6::800a7748 00 c0 03 48     _gte_stM   v1
     6::800a774c 25 40 09 01     or         t0,t0,t1
     6::800a7750 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a775c
     6::800a7754 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a7758 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a775c                           XREF[1]:     OVR_226::800a7750(j)  
     6::800a775c 80 40 08 00     sll        t0,t0,0x2
     6::800a7760 25 18 69 00     or         v1,v1,t1
     6::800a7764 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a7768 c0 18 03 00     sll        v1,v1,0x3
     6::800a776c 25 18 68 00     or         v1,v1,t0
     6::800a7770 b8 fe 60 10     beq        v1,zero,LAB_OVR_226__800a7254
     6::800a7774 70 00 23 ac     _sw        v1,0x70(at)
     6::800a7778 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a777c 04 00 39 27     addiu      t9,t9,0x4
     6::800a7780 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a7784 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a7788 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a778c 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a7790 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a7794 23 50 6c 01     subu       t2,t3,t4
     6::800a7798 82 48 03 00     srl        t1,v1,0x2
     6::800a779c 21 48 38 01     addu       t1,t1,t8
     6::800a77a0 18 00 29 81     lb         t1,0x18(t1)
     6::800a77a4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a77b0
     6::800a77a8 21 e0 60 01     _move      gp,t3
     6::800a77ac 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a77b0                           XREF[1]:     OVR_226::800a77a4(j)  
     6::800a77b0 23 50 8d 03     subu       t2,gp,t5
     6::800a77b4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a77c0
     6::800a77b8 21 18 78 00     _addu      v1,v1,t8
     6::800a77bc 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a77c0                           XREF[1]:     OVR_226::800a77b4(j)  
     6::800a77c0 23 50 8e 03     subu       t2,gp,t6
     6::800a77c4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a77d0
     6::800a77c8 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a77cc 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a77d0                           XREF[1]:     OVR_226::800a77c4(j)  
     6::800a77d0 21 50 80 03     move       t2,gp
     6::800a77d4 82 e1 1c 00     srl        gp,gp,0x6
     6::800a77d8 21 e0 89 03     addu       gp,gp,t1
     6::800a77dc 01 00 69 30     andi       t1,v1,0x1
     6::800a77e0 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a77ec
     6::800a77e4 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a77e8 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a77ec                           XREF[1]:     OVR_226::800a77e0(j)  
     6::800a77ec 02 00 81 07     bgez       gp,LAB_OVR_226__800a77f8
     6::800a77f0 21 e0 85 03     _addu      gp,gp,a1
     6::800a77f4 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a77f8                           XREF[1]:     OVR_226::800a77ec(j)  
     6::800a77f8 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a77fc 24 00 69 8c     lw         t1,0x24(v1)
     6::800a7800 23 40 48 01     subu       t0,t2,t0
     6::800a7804 84 00 29 ac     sw         t1,0x84(at)
     6::800a7808 0c 00 01 05     bgez       t0,LAB_OVR_226__800a783c
     6::800a780c 20 00 28 8c     _lw        t0,0x20(at)
     6::800a7810 0c 00 63 24     addiu      v1,v1,0xc
     6::800a7814 23 40 48 01     subu       t0,t2,t0
     6::800a7818 08 00 01 05     bgez       t0,LAB_OVR_226__800a783c
     6::800a781c 24 00 28 8c     _lw        t0,0x24(at)
     6::800a7820 0c 00 63 24     addiu      v1,v1,0xc
     6::800a7824 23 40 48 01     subu       t0,t2,t0
     6::800a7828 04 00 01 05     bgez       t0,LAB_OVR_226__800a783c
     6::800a782c 00 00 00 00     _nop
     6::800a7830 02 00 20 05     bltz       t1,LAB_OVR_226__800a783c
     6::800a7834 00 00 00 00     _nop
     6::800a7838 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a783c                           XREF[4]:     OVR_226::800a7808(j), 
                                                                                          OVR_226::800a7818(j), 
                                                                                          OVR_226::800a7828(j), 
                                                                                          OVR_226::800a7830(j)  
     6::800a783c 94 01 2a 8c     lw         t2,0x194(at)
     6::800a7840 00 00 68 8c     lw         t0,0x0(v1)
     6::800a7844 04 00 69 8c     lw         t1,0x4(v1)
     6::800a7848 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a784c ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a7850 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a7854 00 52 0a 00     sll        t2,t2,0x8
     6::800a7858 0a 00 40 05     bltz       t2,LAB_OVR_226__800a7884
     6::800a785c b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a7860 06 00 68 a6     sh         t0,0x6(s3)
     6::800a7864 08 00 68 8c     lw         t0,0x8(v1)
     6::800a7868 06 00 89 a6     sh         t1,0x6(s4)
     6::800a786c 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a7870 00 54 0a 00     sll        t2,t2,0x10
     6::800a7874 0b 00 40 05     bltz       t2,LAB_OVR_226__800a78a4
     6::800a7878 02 4c 08 00     _srl       t1,t0,0x10
     6::800a787c 09 00 01 04     bgez       zero,LAB_OVR_226__800a78a4
     6::800a7880 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a7884                           XREF[1]:     OVR_226::800a7858(j)  
     6::800a7884 06 00 69 a6     sh         t1,0x6(s3)
     6::800a7888 08 00 69 8c     lw         t1,0x8(v1)
     6::800a788c 00 54 0a 00     sll        t2,t2,0x10
     6::800a7890 06 00 88 a6     sh         t0,0x6(s4)
     6::800a7894 02 44 09 00     srl        t0,t1,0x10
     6::800a7898 02 00 40 05     bltz       t2,LAB_OVR_226__800a78a4
     6::800a789c 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a78a0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a78a4                           XREF[3]:     OVR_226::800a7874(j), 
                                                                                          OVR_226::800a787c(j), 
                                                                                          OVR_226::800a7898(j)  
     6::800a78a4 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a78a8                           XREF[1]:     FUN_OVR_226__800a7588:800a7660(j
     6::800a78a8 00 00 00 00     nop
     6::800a78ac 23 88 63 01     subu       s1,t3,v1
     6::800a78b0 23 90 83 01     subu       s2,t4,v1
     6::800a78b4 23 78 a3 01     subu       t7,t5,v1
     6::800a78b8 23 80 c3 01     subu       s0,t6,v1
     6::800a78bc 42 8f 11 00     srl        s1,s1,0x1d
     6::800a78c0 04 00 31 32     andi       s1,s1,0x4
     6::800a78c4 02 97 12 00     srl        s2,s2,0x1c
     6::800a78c8 08 00 52 32     andi       s2,s2,0x8
     6::800a78cc 25 88 32 02     or         s1,s1,s2
     6::800a78d0 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a78d4 10 00 ef 31     andi       t7,t7,0x10
     6::800a78d8 25 88 2f 02     or         s1,s1,t7
     6::800a78dc 82 86 10 00     srl        s0,s0,0x1a
     6::800a78e0 20 00 10 32     andi       s0,s0,0x20
     6::800a78e4 25 88 30 02     or         s1,s1,s0
     6::800a78e8 26 00 20 12     beq        s1,zero,LAB_OVR_226__800a7984
     6::800a78ec 21 68 60 02     _move      t5,s3
     6::800a78f0 21 70 80 02     move       t6,s4
     6::800a78f4 b8 00 de 27     addiu      s8,s8,0xb8
     6::800a78f8 00 00 cf 27     addiu      t7,s8,0x0
     6::800a78fc 28 9d 02 0c     jal        FUN_OVR_226__800a74a0                            undefined FUN_OVR_226__800a74a0()
     6::800a7900 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a7904 21 68 80 02     move       t5,s4
     6::800a7908 21 70 c0 02     move       t6,s6
     6::800a790c 14 00 cf 27     addiu      t7,s8,0x14
     6::800a7910 28 9d 02 0c     jal        FUN_OVR_226__800a74a0                            undefined FUN_OVR_226__800a74a0()
     6::800a7914 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a7918 21 68 a0 02     move       t5,s5
     6::800a791c 21 70 60 02     move       t6,s3
     6::800a7920 28 00 cf 27     addiu      t7,s8,0x28
     6::800a7924 28 9d 02 0c     jal        FUN_OVR_226__800a74a0                            undefined FUN_OVR_226__800a74a0()
     6::800a7928 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a792c 21 68 c0 02     move       t5,s6
     6::800a7930 21 70 a0 02     move       t6,s5
     6::800a7934 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a7938 28 9d 02 0c     jal        FUN_OVR_226__800a74a0                            undefined FUN_OVR_226__800a74a0()
     6::800a793c a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a7940 21 68 80 02     move       t5,s4
     6::800a7944 21 70 a0 02     move       t6,s5
     6::800a7948 14 00 cf 27     addiu      t7,s8,0x14
     6::800a794c 28 9d 02 0c     jal        FUN_OVR_226__800a74a0                            undefined FUN_OVR_226__800a74a0()
     6::800a7950 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a7954 21 18 21 02     addu       v1,s1,at
     6::800a7958 48 01 63 8c     lw         v1,0x148(v1)
     6::800a795c 0a 80 08 3c     lui        t0,0x800a
     6::800a7960 74 79 08 25     addiu      t0,t0,0x7974
     6::800a7964 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a7968 3c 00 28 af     sw         t0=>LAB_OVR_226__800a7974,0x3c(t9)
     6::800a796c 08 00 60 00     jr         v1
     6::800a7970 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a7974                           XREF[1]:     FUN_OVR_226__800a7668:800a7968(*
     6::800a7974 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7978 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a797c 08 00 e0 03     jr         ra
     6::800a7980 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a7984                           XREF[1]:     OVR_226::800a78e8(j)  
     6::800a7984 70 00 23 8c     lw         v1,0x70(at)
     6::800a7988 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a798c 21 18 61 00     addu       v1,v1,at
     6::800a7990 84 01 63 8c     lw         v1,0x184(v1)
     6::800a7994 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a7998 08 00 60 00     jr         v1
     6::800a799c 00 00 00 00     _nop
                             LAB_OVR_226__800a79a0                           XREF[1]:     OVR_226::800a7648(j)  
     6::800a79a0 84 00 23 8c     lw         v1,0x84(at)
     6::800a79a4 24 03 2a 24     addiu      t2,at,0x324
     6::800a79a8 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a7a44
     6::800a79ac 20 03 28 8c     _lw        t0,0x320(at)
     6::800a79b0 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a79b4 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a7a10
     6::800a79b8 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a79bc 0a 80 0a 3c     lui        t2,0x800a
     6::800a79c0 5c 74 4a 25     addiu      t2,t2,0x745c
     6::800a79c4 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a7a44
     6::800a79c8 94 01 23 8c     _lw        v1,0x194(at)
     6::800a79cc 40 40 08 00     sll        t0,t0,0x1
     6::800a79d0 00 1a 03 00     sll        v1,v1,0x8
     6::800a79d4 02 00 61 04     bgez       v1,LAB_OVR_226__800a79e0
     6::800a79d8 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a79dc c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_226__800a79e0                           XREF[1]:     OVR_226::800a79d4(j)  
     6::800a79e0 21 40 09 01     addu       t0,t0,t1
     6::800a79e4 21 50 48 01     addu       t2,t2,t0
     6::800a79e8 00 00 48 8d     lw         t0,0x0(t2)
     6::800a79ec 04 00 49 8d     lw         t1,0x4(t2)
     6::800a79f0 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a79f4 06 00 68 a6     sh         t0,0x6(s3)
     6::800a79f8 08 00 48 85     lh         t0,0x8(t2)
     6::800a79fc a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a7a00 06 00 89 a6     sh         t1,0x6(s4)
     6::800a7a04 0a 00 49 85     lh         t1,0xa(t2)
     6::800a7a08 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a7a0c 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a7a10                           XREF[2]:     OVR_226::800a79b4(j), 
                                                                                          OVR_226::800a7a50(j)  
     6::800a7a10 70 00 23 8c     lw         v1,0x70(at)
     6::800a7a14 00 00 00 00     nop
     6::800a7a18 21 18 61 00     addu       v1,v1,at
     6::800a7a1c 84 01 63 8c     lw         v1,0x184(v1)
     6::800a7a20 00 00 00 00     nop
     6::800a7a24 09 f8 60 00     jalr       v1
     6::800a7a28 fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a7a2c 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a7a30 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a7a34 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a7a38 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a7a3c 08 00 e0 03     jr         ra
     6::800a7a40 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a7a44                           XREF[2]:     OVR_226::800a79a8(j), 
                                                                                          OVR_226::800a79c4(j)  
     6::800a7a44 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a7a48 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a7a4c a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a7a50 ef ff 01 04     bgez       zero,LAB_OVR_226__800a7a10
     6::800a7a54 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a7a58 21 98 80 02     move       s3,s4
     6::800a7a5c 21 a0 c0 02     move       s4,s6
     6::800a7a60 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a7a64 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a7a68 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a7a6c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a7a70 08 00 90 8e     lw         s0,0x8(s4)
     6::800a7a74 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a7a78 06 00 73 86     lh         s3,0x6(s3)
     6::800a7a7c 06 00 94 86     lh         s4,0x6(s4)
     6::800a7a80 06 00 b5 86     lh         s5,0x6(s5)
     6::800a7a84 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a7a88 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a7a8c a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a7a90 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a7a94 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a7a98 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a7a9c 60 00 03 3c     lui        v1,0x60
     6::800a7aa0 24 48 83 02     and        t1,s4,v1
     6::800a7aa4 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a7ab0
     6::800a7aa8 00 36 03 3c     _lui       v1,0x3600
     6::800a7aac 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a7ab0                           XREF[1]:     OVR_226::800a7aa4(j)  
     6::800a7ab0 25 18 6f 00     or         v1,v1,t7
     6::800a7ab4 04 00 43 ac     sw         v1,0x4(v0)
     6::800a7ab8 08 00 4b ac     sw         t3,0x8(v0)
     6::800a7abc 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a7ac0 10 00 50 ac     sw         s0,0x10(v0)
     6::800a7ac4 14 00 4c ac     sw         t4,0x14(v0)
     6::800a7ac8 18 00 54 ac     sw         s4,0x18(v0)
     6::800a7acc 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a7ad0 20 00 4d ac     sw         t5,0x20(v0)
     6::800a7ad4 24 00 55 ac     sw         s5,0x24(v0)
     6::800a7ad8 28 00 09 24     li         t1,0x28
     6::800a7adc 29 00 01 04     bgez       zero,LAB_OVR_226__800a7b84
     6::800a7ae0 00 09 0a 3c     _lui       t2,0x900
     6::800a7ae4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a7ae8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a7aec 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a7af0 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a7af4 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a7af8 08 00 90 8e     lw         s0,0x8(s4)
     6::800a7afc 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a7b00 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a7b04 06 00 73 86     lh         s3,0x6(s3)
     6::800a7b08 06 00 94 86     lh         s4,0x6(s4)
     6::800a7b0c 06 00 b5 86     lh         s5,0x6(s5)
     6::800a7b10 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a7b14 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a7b18 06 00 d4 86     lh         s4,0x6(s6)
     6::800a7b1c a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a7b20 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a7b24 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a7b28 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a7b2c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a7b30 60 00 03 3c     lui        v1,0x60
     6::800a7b34 24 48 83 02     and        t1,s4,v1
     6::800a7b38 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a7b44
     6::800a7b3c 00 3e 03 3c     _lui       v1,0x3e00
     6::800a7b40 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a7b44                           XREF[1]:     OVR_226::800a7b38(j)  
     6::800a7b44 25 18 6f 00     or         v1,v1,t7
     6::800a7b48 04 00 43 ac     sw         v1,0x4(v0)
     6::800a7b4c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a7b50 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a7b54 10 00 50 ac     sw         s0,0x10(v0)
     6::800a7b58 14 00 4c ac     sw         t4,0x14(v0)
     6::800a7b5c 18 00 54 ac     sw         s4,0x18(v0)
     6::800a7b60 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a7b64 20 00 4d ac     sw         t5,0x20(v0)
     6::800a7b68 24 00 55 ac     sw         s5,0x24(v0)
     6::800a7b6c 28 00 52 ac     sw         s2,0x28(v0)
     6::800a7b70 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a7b74 02 1c 15 00     srl        v1,s5,0x10
     6::800a7b78 30 00 43 ac     sw         v1,0x30(v0)
     6::800a7b7c 34 00 09 24     li         t1,0x34
     6::800a7b80 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a7b84                           XREF[1]:     OVR_226::800a7adc(j)  
     6::800a7b84 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a7b88 00 42 02 00     sll        t0,v0,0x8
     6::800a7b8c 02 42 08 00     srl        t0,t0,0x8
     6::800a7b90 25 18 6a 00     or         v1,v1,t2
     6::800a7b94 00 00 43 ac     sw         v1,0x0(v0)
     6::800a7b98 21 10 49 00     addu       v0,v0,t1
     6::800a7b9c 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a7ba0 08 00 e0 03     jr         ra
     6::800a7ba4 01 00 bd 23     _addi      sp,sp,0x1
                             
	 // almost-last JR
							 LAB_OVR_226__800a7ba8                           XREF[1]:     OVR_226::800ab440(*)  
     6::800a7ba8 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_226__800a7bac                           XREF[1]:     OVR_226::800a7efc(j)  
     
	 // v1 = 1f800030 (primMem->end)
	 6::800a7bac 30 00 23 8c     lw         v1,0x30(at)
     
	 // t0 = primMem->curr + 0x1a00
	 6::800a7bb0 00 1a 48 24     addiu      t0,v0,0x1a00
	 
	 // v1 = primMem->end - (primMem->curr + 0x1a00)
     6::800a7bb4 23 18 68 00     subu       v1,v1,t0
	 
	 // if not enough primMem, end rendering and return to EXE
     6::800a7bb8 be e4 60 04     bltz       v1,LAB_OVR_226__800a0eb4
	 
	 // s8 = 0x1f8001b4 (the scratchpad region cleared in main func)
     6::800a7bbc b4 01 3e 24     _addiu     s8,at,0x1b4
	 
	 // if finished, jump back to entry function, back to the main loop
     6::800a7bc0 b1 e4 00 13     beq        t8,zero,LAB_OVR_226__800a0e88
	 
	 // s8->0xb4 = 0
     6::800a7bc4 b4 00 c0 af     _sw        zero,0xb4(s8)
	 
	 // s4 = quadblock->0x0 (index[0,1])
     6::800a7bc8 00 00 14 8f     lw         s4,0x0(t8)
	 
	 // s6 = quadblock->0x4 (index[2,3])
     6::800a7bcc 04 00 16 8f     lw         s6,0x4(t8)
	 
	 // s3 = s4 & 0xffff
	 // s3 = vertex index[0]
     6::800a7bd0 ff ff 93 32     andi       s3,s4,0xffff
	 
	 // s3 = s3 << 4
	 // s3 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a7bd4 00 99 13 00     sll        s3,s3,0x4
	 
	 // s3 = s3 + s7
	 // s3 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a7bd8 21 98 77 02     addu       s3,s3,s7
	 
	 // load pos[4] from LevVertex into GTE, (load vertex0)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
     6::800a7bdc 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     
	 // s4 = s4 >> 0x10
	 // s4 = vertex index[1]
     6::800a7be4 02 a4 14 00     srl        s4,s4,0x10
	 
	 // s4 = s4 << 4
	 // s4 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a7be8 00 a1 14 00     sll        s4,s4,0x4
	 
	 // s4 = s4 + s7
	 // s4 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a7bec 21 a0 97 02     addu       s4,s4,s7
     
	 // load pos[4] from LevVertex into GTE, (load vertex1)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
     6::800a7bf0 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     
	 // s5 = s6 & 0xffff
	 // s5 = vertex index[2]
     6::800a7bf8 ff ff d5 32     andi       s5,s6,0xffff
	 
	 // s5 = s5 << 4
	 // s5 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a7bfc 00 a9 15 00     sll        s5,s5,0x4
	 
	 // s5 = s5 + s7
	 // s5 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a7c00 21 a8 b7 02     addu       s5,s5,s7
     
	 // load pos[4] from LevVertex into GTE, (load vertex2)
	 // keep in mind the camera matrix is already loaded in GTE
	 // from the beginning of the 226 main function
     6::800a7c04 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     
	 // s6 = s6 >> 0x10
	 // s6 = vertex index[3]
     6::800a7c0c 02 b4 16 00     srl        s6,s6,0x10

	 // s6 = s6 << 4
	 // s6 *= 0x10 (byte offset, LevVertex is 0x10 bytes)
     6::800a7c10 00 b1 16 00     sll        s6,s6,0x4
	 
	 // perspective projection on triangle in GTE
     6::800a7c14 30 00 28 4a     RTPT
	 
	 // s6 = s6 + s7
	 // s6 = lev->ptrVertexArray + byte offset of vertex index[0]
     6::800a7c18 21 b0 d7 02     addu       s6,s6,s7
	 
	 // get color_hi from each vertex
     6::800a7c1c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a7c20 08 00 90 8e     lw         s0,0x8(s4)
     6::800a7c24 08 00 b1 8e     lw         s1,0x8(s5)
	 
	 // store color_hi from each vertex on scratchpad (0x1f8001b4)
     6::800a7c28 08 00 cf af     sw         t7,0x8(s8)
     6::800a7c2c 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a7c30 30 00 d1 af     sw         s1,0x30(s8)
	 
	 /*
	 {
		 0x00 - VXY0
		 0x04 - VZ0
		 0x06 - drawOrder (see SH)
		 0x08 - color0
		 0x0C - SXY0
		 0x10 - SZ1 (ghidra typo?)
		 
		 0x14 - VXY1
		 0x18 - VZ1
		 0x1A - drawOrder (see SH)
		 0x1C - color1
		 0x20 - SXY1
		 0x24 - SZ2 (ghidra typo?)
		 
		 0x28 - VXY2
		 0x2C - VZ2
		 0x2E - drawOrder (see SH)
		 0x30 - color2
		 0x34 - SXY2
		 0x38 - SZ3 (ghidra typo?)
	 }
	 */
	 
     6::800a7c34 08 00 14 8f     lw         s4,0x8(t8)
     6::800a7c38 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a7c3c 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a7c40 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a7c44 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a7c48 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a7c4c 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a7c50 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a7c54 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a7c58 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a7c5c 5c 00 2a 8c     lw         t2,0x5c(at)
     6::800a7c60 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a7c6c 10 00 c3 a7     sh         v1,0x10(s8)
     6::800a7c70 24 00 c8 a7     sh         t0,0x24(s8)
     6::800a7c74 38 00 c9 a7     sh         t1,0x38(s8)
     6::800a7c78 23 58 6a 00     subu       t3,v1,t2
     6::800a7c7c 23 60 0a 01     subu       t4,t0,t2
     6::800a7c80 23 68 2a 01     subu       t5,t1,t2
     6::800a7c84 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a7c88 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a7c8c c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a7c90 12 00 cb a3     sb         t3,0x12(s8)
     6::800a7c94 26 00 cc a3     sb         t4,0x26(s8)
     6::800a7c98 3a 00 cd a3     sb         t5,0x3a(s8)
     6::800a7c9c 40 18 03 00     sll        v1,v1,0x1
     6::800a7ca0 40 40 08 00     sll        t0,t0,0x1
     6::800a7ca4 40 48 09 00     sll        t1,t1,0x1
     6::800a7ca8 23 58 6a 00     subu       t3,v1,t2
     6::800a7cac 23 60 0a 01     subu       t4,t0,t2
     6::800a7cb0 23 68 2a 01     subu       t5,t1,t2
     6::800a7cb4 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a7cb8 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a7cbc c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a7cc0 13 00 cb a3     sb         t3,0x13(s8)
     6::800a7cc4 27 00 cc a3     sb         t4,0x27(s8)
     6::800a7cc8 3b 00 cd a3     sb         t5,0x3b(s8)
     6::800a7ccc 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a7cd4 ff ff 93 32     andi       s3,s4,0xffff
     6::800a7cd8 00 99 13 00     sll        s3,s3,0x4
     6::800a7cdc 21 98 77 02     addu       s3,s3,s7
     6::800a7ce0 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a7ce8 02 a4 14 00     srl        s4,s4,0x10
     6::800a7cec 00 a1 14 00     sll        s4,s4,0x4
     6::800a7cf0 21 a0 97 02     addu       s4,s4,s7
     6::800a7cf4 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a7cfc 21 c8 20 00     move       t9,at
     6::800a7d00 00 00 00 00     nop
     6::800a7d04 30 00 28 4a     RTPT
     6::800a7d08 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a7d0c 08 00 70 8e     lw         s0,0x8(s3)
     6::800a7d10 08 00 91 8e     lw         s1,0x8(s4)
     6::800a7d14 44 00 cf af     sw         t7,0x44(s8)
     6::800a7d18 58 00 d0 af     sw         s0,0x58(s8)
     6::800a7d1c 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a7d20 0c 00 14 8f     lw         s4,0xc(t8)
     6::800a7d24 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a7d28 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a7d2c 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a7d30 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a7d34 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a7d38 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a7d3c 10 00 15 97     lhu        s5,0x10(t8)
     6::800a7d40 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a7d44 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a7d48 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a7d4c 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a7d58 4c 00 c3 a7     sh         v1,0x4c(s8)
     6::800a7d5c 60 00 c8 a7     sh         t0,0x60(s8)
     6::800a7d60 74 00 c9 a7     sh         t1,0x74(s8)
     6::800a7d64 23 58 6a 00     subu       t3,v1,t2
     6::800a7d68 23 60 0a 01     subu       t4,t0,t2
     6::800a7d6c 23 68 2a 01     subu       t5,t1,t2
     6::800a7d70 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a7d74 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a7d78 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a7d7c 4e 00 cb a3     sb         t3,0x4e(s8)
     6::800a7d80 62 00 cc a3     sb         t4,0x62(s8)
     6::800a7d84 76 00 cd a3     sb         t5,0x76(s8)
     6::800a7d88 40 18 03 00     sll        v1,v1,0x1
     6::800a7d8c 40 40 08 00     sll        t0,t0,0x1
     6::800a7d90 40 48 09 00     sll        t1,t1,0x1
     6::800a7d94 23 58 6a 00     subu       t3,v1,t2
     6::800a7d98 23 60 0a 01     subu       t4,t0,t2
     6::800a7d9c 23 68 2a 01     subu       t5,t1,t2
     6::800a7da0 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a7da4 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a7da8 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a7dac 4f 00 cb a3     sb         t3,0x4f(s8)
     6::800a7db0 63 00 cc a3     sb         t4,0x63(s8)
     6::800a7db4 77 00 cd a3     sb         t5,0x77(s8)
     6::800a7db8 ff ff 93 32     andi       s3,s4,0xffff
     6::800a7dbc 00 99 13 00     sll        s3,s3,0x4
     6::800a7dc0 21 98 77 02     addu       s3,s3,s7
     6::800a7dc4 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a7dcc 02 a4 14 00     srl        s4,s4,0x10
     6::800a7dd0 00 a1 14 00     sll        s4,s4,0x4
     6::800a7dd4 21 a0 97 02     addu       s4,s4,s7
     6::800a7dd8 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a7de0 14 00 09 8f     lw         t1,0x14(t8)
     6::800a7de4 00 a9 15 00     sll        s5,s5,0x4
     6::800a7de8 21 a8 b7 02     addu       s5,s5,s7
     6::800a7dec 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a7df4 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a7df8 00 00 00 00     nop
     6::800a7dfc 30 00 28 4a     RTPT
     6::800a7e00 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a7e04 08 00 90 8e     lw         s0,0x8(s4)
     6::800a7e08 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a7e0c 80 00 cf af     sw         t7,0x80(s8)
     6::800a7e10 94 00 d0 af     sw         s0,0x94(s8)
     6::800a7e14 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a7e18 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a7e1c 98 00 cd eb     gte_stSXY1 0x98(s8)
     6::800a7e20 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a7e24 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a7e28 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a7e2c 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a7e30 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a7e34 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a7e38 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a7e3c 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a7e48 88 00 c3 a7     sh         v1,0x88(s8)
     6::800a7e4c 9c 00 c8 a7     sh         t0,0x9c(s8)
     6::800a7e50 b0 00 c9 a7     sh         t1,0xb0(s8)
     6::800a7e54 23 58 6a 00     subu       t3,v1,t2
     6::800a7e58 23 60 0a 01     subu       t4,t0,t2
     6::800a7e5c 23 68 2a 01     subu       t5,t1,t2
     6::800a7e60 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a7e64 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a7e68 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a7e6c 8a 00 cb a3     sb         t3,0x8a(s8)
     6::800a7e70 9e 00 cc a3     sb         t4,0x9e(s8)
     6::800a7e74 b2 00 cd a3     sb         t5,0xb2(s8)
     6::800a7e78 40 18 03 00     sll        v1,v1,0x1
     6::800a7e7c 40 40 08 00     sll        t0,t0,0x1
     6::800a7e80 40 48 09 00     sll        t1,t1,0x1
     6::800a7e84 23 58 6a 00     subu       t3,v1,t2
     6::800a7e88 23 60 0a 01     subu       t4,t0,t2
     6::800a7e8c 23 68 2a 01     subu       t5,t1,t2
     6::800a7e90 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a7e94 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a7e98 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a7e9c 8b 00 cb a3     sb         t3,0x8b(s8)
     6::800a7ea0 9f 00 cc a3     sb         t4,0x9f(s8)
     6::800a7ea4 b3 00 cd a3     sb         t5,0xb3(s8)
     6::800a7ea8 50 00 03 3c     lui        v1,0x50
     6::800a7eac 78 64 63 34     ori        v1,v1,0x6478
     6::800a7eb0 08 00 08 24     li         t0,0x8
     6::800a7eb4 e0 a0 02 0c     jal        FUN_OVR_226__800a8380                            undefined FUN_OVR_226__800a8380()
     6::800a7eb8 00 00 0a 24     _li        t2,0x0
     6::800a7ebc 14 50 03 3c     lui        v1,0x5014
     6::800a7ec0 8c 78 63 34     ori        v1,v1,0x788c
     6::800a7ec4 0d 00 08 24     li         t0,0xd
     6::800a7ec8 e0 a0 02 0c     jal        FUN_OVR_226__800a8380                            undefined FUN_OVR_226__800a8380()
     6::800a7ecc 04 00 0a 24     _li        t2,0x4
     6::800a7ed0 78 64 03 3c     lui        v1,0x6478
     6::800a7ed4 a0 28 63 34     ori        v1,v1,0x28a0
     6::800a7ed8 12 00 08 24     li         t0,0x12
     6::800a7edc e0 a0 02 0c     jal        FUN_OVR_226__800a8380                            undefined FUN_OVR_226__800a8380()
     6::800a7ee0 08 00 0a 24     _li        t2,0x8
     6::800a7ee4 8c 78 03 3c     lui        v1,0x788c
     6::800a7ee8 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a7eec 17 00 08 24     li         t0,0x17
     6::800a7ef0 e0 a0 02 0c     jal        FUN_OVR_226__800a8380                            undefined FUN_OVR_226__800a8380()
     6::800a7ef4 0c 00 0a 24     _li        t2,0xc
     6::800a7ef8 04 00 98 8c     lw         t8,0x4(a0)
     6::800a7efc 2b ff 01 04     bgez       zero,LAB_OVR_226__800a7bac
     6::800a7f00 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_226__800a7f04                           XREF[12]:    FUN_OVR_226__800a825c:800a8278(j
                                                                                          FUN_OVR_226__800a825c:800a8314(j
                                                                                          FUN_OVR_226__800a825c:800a831c(j
                                                                                          FUN_OVR_226__800a825c:800a8350(j
                                                                                          OVR_226::800a840c(j), 
                                                                                          OVR_226::800a8498(j), 
                                                                                          OVR_226::800a84a0(j), 
                                                                                          OVR_226::800a84cc(j), 
                                                                                          FUN_OVR_226__800a825c:800a87e8(j
                                                                                          FUN_OVR_226__800a825c:800a88a4(j
                                                                                          FUN_OVR_226__800a825c:800a89d8(j
                                                                                          FUN_OVR_226__800a825c:800a8a90(j
     6::800a7f04 08 00 e0 03     jr         ra
     6::800a7f08 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7f0c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7f0c                           XREF[4]:     FUN_OVR_226__800a7f5c:800a7fe4(j
                                                                                          FUN_OVR_226__800a7f5c:800a807c(c
                                                                                          FUN_OVR_226__800a7f5c:800a80a4(c
                                                                                          FUN_OVR_226__800a7f5c:800a8110(c
     6::800a7f0c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a7f10 50 00 d4 27     addiu      s4,s8,0x50
     6::800a7f14 64 00 d5 27     addiu      s5,s8,0x64
     6::800a7f18 d0 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f1c 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7f20()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7f20                           XREF[6]:     FUN_OVR_226__800a7f5c:800a7fec(c
                                                                                          FUN_OVR_226__800a7f5c:800a808c(j
                                                                                          FUN_OVR_226__800a7f5c:800a809c(c
                                                                                          FUN_OVR_226__800a7f5c:800a80cc(c
                                                                                          FUN_OVR_226__800a7f5c:800a80ec(c
                                                                                          FUN_OVR_226__800a7f5c:800a8120(c
     6::800a7f20 50 00 d3 27     addiu      s3,s8,0x50
     6::800a7f24 14 00 d4 27     addiu      s4,s8,0x14
     6::800a7f28 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7f2c cb 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f30 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7f34()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7f34                           XREF[6]:     FUN_OVR_226__800a7f5c:800a8014(c
                                                                                          FUN_OVR_226__800a7f5c:800a8074(c
                                                                                          FUN_OVR_226__800a7f5c:800a80b4(j
                                                                                          FUN_OVR_226__800a7f5c:800a80c4(c
                                                                                          FUN_OVR_226__800a7f5c:800a80f4(c
                                                                                          FUN_OVR_226__800a7f5c:800a8130(c
     6::800a7f34 64 00 d3 27     addiu      s3,s8,0x64
     6::800a7f38 78 00 d4 27     addiu      s4,s8,0x78
     6::800a7f3c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a7f40 c6 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f44 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a7f48                           XREF[4]:     OVR_226::800a8064(j), 
                                                                                          OVR_226::800a80dc(j), 
                                                                                          OVR_226::800a8104(j), 
                                                                                          OVR_226::800a8148(j)  
     6::800a7f48 78 00 d3 27     addiu      s3,s8,0x78
     6::800a7f4c 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a7f50 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a7f54 c1 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f58 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a7f5c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a7f5c                           XREF[2]:     OVR_226::800a800c(c), 
                                                                                          OVR_226::800a80e4(c)  
     6::800a7f5c 64 00 d3 27     addiu      s3,s8,0x64
     6::800a7f60 00 00 d4 27     addiu      s4,s8,0x0
     6::800a7f64 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7f68 bc 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f6c 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a7f70                           XREF[2]:     OVR_226::800a8024(j), 
                                                                                          OVR_226::800a8094(c)  
     6::800a7f70 14 00 d3 27     addiu      s3,s8,0x14
     6::800a7f74 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a7f78 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7f7c b7 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f80 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a7f84                           XREF[2]:     OVR_226::800a7ff4(c), 
                                                                                          OVR_226::800a80bc(c)  
     6::800a7f84 28 00 d3 27     addiu      s3,s8,0x28
     6::800a7f88 00 00 d4 27     addiu      s4,s8,0x0
     6::800a7f8c 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7f90 b2 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7f94 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a7f98                           XREF[2]:     OVR_226::800a8004(j), 
                                                                                          OVR_226::800a806c(c)  
     6::800a7f98 28 00 d3 27     addiu      s3,s8,0x28
     6::800a7f9c 78 00 d4 27     addiu      s4,s8,0x78
     6::800a7fa0 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a7fa4 ad 00 01 04     bgez       zero,FUN_OVR_226__800a825c
     6::800a7fa8 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a7fac 50 00 d3 27     addiu      s3,s8,0x50
     6::800a7fb0 14 00 d4 27     addiu      s4,s8,0x14
     6::800a7fb4 78 00 d5 27     addiu      s5,s8,0x78
     6::800a7fb8 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a7fbc 97 a0 02 0c     jal        FUN_OVR_226__800a825c                            undefined FUN_OVR_226__800a825c()
     6::800a7fc0 0c 00 0a 24     _li        t2,0xc
     6::800a7fc4 64 00 d3 27     addiu      s3,s8,0x64
     6::800a7fc8 78 00 d4 27     addiu      s4,s8,0x78
     6::800a7fcc 28 00 d5 27     addiu      s5,s8,0x28
     6::800a7fd0 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a7fd4 97 a0 02 0c     jal        FUN_OVR_226__800a825c                            undefined FUN_OVR_226__800a825c()
     6::800a7fd8 0c 00 0a 24     _li        t2,0xc
     6::800a7fdc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a7fe0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a7fe4 c9 ff 01 04     bgez       zero,FUN_OVR_226__800a7f0c
     6::800a7fe8 0c 00 0a 24     _li        t2,0xc
     6::800a7fec c8 9f 02 0c     jal        FUN_OVR_226__800a7f20                            undefined FUN_OVR_226__800a7f20()
     6::800a7ff0 0c 00 0a 24     _li        t2,0xc
     6::800a7ff4 e1 9f 02 0c     jal        SUB_OVR_226__800a7f84
     6::800a7ff8 0c 00 0a 24     _li        t2,0xc
     6::800a7ffc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8000 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8004 e4 ff 01 04     bgez       zero,SUB_OVR_226__800a7f98
     6::800a8008 0c 00 0a 24     _li        t2,0xc
     6::800a800c d7 9f 02 0c     jal        FUN_OVR_226__800a7f5c                            undefined FUN_OVR_226__800a7f5c()
     6::800a8010 0c 00 0a 24     _li        t2,0xc
     6::800a8014 cd 9f 02 0c     jal        FUN_OVR_226__800a7f34                            undefined FUN_OVR_226__800a7f34()
     6::800a8018 0c 00 0a 24     _li        t2,0xc
     6::800a801c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8020 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8024 d2 ff 01 04     bgez       zero,SUB_OVR_226__800a7f70
     6::800a8028 0c 00 0a 24     _li        t2,0xc
     6::800a802c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a8030 14 00 d4 27     addiu      s4,s8,0x14
     6::800a8034 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8038 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a803c 97 a0 02 0c     jal        FUN_OVR_226__800a825c                            undefined FUN_OVR_226__800a825c()
     6::800a8040 0c 00 0a 24     _li        t2,0xc
     6::800a8044 00 00 d3 27     addiu      s3,s8,0x0
     6::800a8048 78 00 d4 27     addiu      s4,s8,0x78
     6::800a804c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a8050 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a8054 97 a0 02 0c     jal        FUN_OVR_226__800a825c                            undefined FUN_OVR_226__800a825c()
     6::800a8058 0c 00 0a 24     _li        t2,0xc
     6::800a805c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8060 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8064 b8 ff 01 04     bgez       zero,LAB_OVR_226__800a7f48
     6::800a8068 0c 00 0a 24     _li        t2,0xc
     6::800a806c e6 9f 02 0c     jal        SUB_OVR_226__800a7f98
     6::800a8070 0c 00 0a 24     _li        t2,0xc
     6::800a8074 cd 9f 02 0c     jal        FUN_OVR_226__800a7f34                            undefined FUN_OVR_226__800a7f34()
     6::800a8078 04 00 0a 24     _li        t2,0x4
     6::800a807c c3 9f 02 0c     jal        FUN_OVR_226__800a7f0c                            undefined FUN_OVR_226__800a7f0c()
     6::800a8080 0c 00 0a 24     _li        t2,0xc
     6::800a8084 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8088 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a808c a4 ff 01 04     bgez       zero,FUN_OVR_226__800a7f20
     6::800a8090 0c 00 0a 24     _li        t2,0xc
     6::800a8094 dc 9f 02 0c     jal        SUB_OVR_226__800a7f70
     6::800a8098 0c 00 0a 24     _li        t2,0xc
     6::800a809c c8 9f 02 0c     jal        FUN_OVR_226__800a7f20                            undefined FUN_OVR_226__800a7f20()
     6::800a80a0 04 00 0a 24     _li        t2,0x4
     6::800a80a4 c3 9f 02 0c     jal        FUN_OVR_226__800a7f0c                            undefined FUN_OVR_226__800a7f0c()
     6::800a80a8 0c 00 0a 24     _li        t2,0xc
     6::800a80ac 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a80b0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a80b4 9f ff 01 04     bgez       zero,FUN_OVR_226__800a7f34
     6::800a80b8 0c 00 0a 24     _li        t2,0xc
     6::800a80bc e1 9f 02 0c     jal        SUB_OVR_226__800a7f84
     6::800a80c0 0c 00 0a 24     _li        t2,0xc
     6::800a80c4 cd 9f 02 0c     jal        FUN_OVR_226__800a7f34                            undefined FUN_OVR_226__800a7f34()
     6::800a80c8 08 00 0a 24     _li        t2,0x8
     6::800a80cc c8 9f 02 0c     jal        FUN_OVR_226__800a7f20                            undefined FUN_OVR_226__800a7f20()
     6::800a80d0 0c 00 0a 24     _li        t2,0xc
     6::800a80d4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a80d8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a80dc 9a ff 01 04     bgez       zero,LAB_OVR_226__800a7f48
     6::800a80e0 0c 00 0a 24     _li        t2,0xc
     6::800a80e4 d7 9f 02 0c     jal        FUN_OVR_226__800a7f5c                            undefined FUN_OVR_226__800a7f5c()
     6::800a80e8 0c 00 0a 24     _li        t2,0xc
     6::800a80ec c8 9f 02 0c     jal        FUN_OVR_226__800a7f20                            undefined FUN_OVR_226__800a7f20()
     6::800a80f0 08 00 0a 24     _li        t2,0x8
     6::800a80f4 cd 9f 02 0c     jal        FUN_OVR_226__800a7f34                            undefined FUN_OVR_226__800a7f34()
     6::800a80f8 0c 00 0a 24     _li        t2,0xc
     6::800a80fc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8100 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8104 90 ff 01 04     bgez       zero,LAB_OVR_226__800a7f48
     6::800a8108 0c 00 0a 24     _li        t2,0xc
     6::800a810c b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a8110 c3 9f 02 0c     jal        FUN_OVR_226__800a7f0c                            undefined FUN_OVR_226__800a7f0c()
     6::800a8114 0c 00 0a 24     _li        t2,0xc
     6::800a8118 0c 00 03 24     li         v1,0xc
     6::800a811c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a8120 c8 9f 02 0c     jal        FUN_OVR_226__800a7f20                            undefined FUN_OVR_226__800a7f20()
     6::800a8124 0c 00 0a 24     _li        t2,0xc
     6::800a8128 30 00 03 24     li         v1,0x30
     6::800a812c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a8130 cd 9f 02 0c     jal        FUN_OVR_226__800a7f34                            undefined FUN_OVR_226__800a7f34()
     6::800a8134 0c 00 0a 24     _li        t2,0xc
     6::800a8138 3c 00 03 24     li         v1,0x3c
     6::800a813c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a8140 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8144 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8148 7f ff 01 04     bgez       zero,LAB_OVR_226__800a7f48
     6::800a814c 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8150()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8150                           XREF[5]:     FUN_OVR_226__800a8380:800a8670(c
                                                                                          FUN_OVR_226__800a8380:800a8684(c
                                                                                          FUN_OVR_226__800a8380:800a8698(c
                                                                                          FUN_OVR_226__800a8380:800a86ac(c
                                                                                          FUN_OVR_226__800a8380:800a86c0(c
     6::800a8150 00 00 ab 85     lh         t3,0x0(t5)
     6::800a8154 00 00 cc 85     lh         t4,0x0(t6)
     6::800a8158 00 00 eb a5     sh         t3,0x0(t7)
     6::800a815c 21 18 6c 01     addu       v1,t3,t4
     6::800a8160 43 18 03 00     sra        v1,v1,0x1
     6::800a8164 00 00 03 a6     sh         v1,0x0(s0)
     6::800a8168 02 00 ab 85     lh         t3,0x2(t5)
     6::800a816c 02 00 cc 85     lh         t4,0x2(t6)
     6::800a8170 02 00 eb a5     sh         t3,0x2(t7)
     6::800a8174 21 18 6c 01     addu       v1,t3,t4
     6::800a8178 43 18 03 00     sra        v1,v1,0x1
     6::800a817c 02 00 03 a6     sh         v1,0x2(s0)
     6::800a8180 04 00 ab 85     lh         t3,0x4(t5)
     6::800a8184 04 00 cc 85     lh         t4,0x4(t6)
     6::800a8188 04 00 eb a5     sh         t3,0x4(t7)
     6::800a818c 21 18 6c 01     addu       v1,t3,t4
     6::800a8190 43 18 03 00     sra        v1,v1,0x1
     6::800a8194 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a8198 00 08 83 48     gte_ldVZ0  v1
     6::800a819c 04 00 03 a6     sh         v1,0x4(s0)
     6::800a81a0 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a81a4 01 00 18 4a     RTPS
     6::800a81a8 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a81ac 08 00 eb a1     sb         t3,0x8(t7)
     6::800a81b0 21 18 6c 01     addu       v1,t3,t4
     6::800a81b4 43 18 03 00     sra        v1,v1,0x1
     6::800a81b8 08 00 03 a2     sb         v1,0x8(s0)
     6::800a81bc 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a81c0 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a81c4 09 00 eb a1     sb         t3,0x9(t7)
     6::800a81c8 21 18 6c 01     addu       v1,t3,t4
     6::800a81cc 43 18 03 00     sra        v1,v1,0x1
     6::800a81d0 09 00 03 a2     sb         v1,0x9(s0)
     6::800a81d4 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a81d8 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a81dc 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a81e0 21 18 6c 01     addu       v1,t3,t4
     6::800a81e4 43 18 03 00     sra        v1,v1,0x1
     6::800a81e8 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a81ec 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a81f0 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a81f4 06 00 eb a1     sb         t3,0x6(t7)
     6::800a81f8 21 18 6c 01     addu       v1,t3,t4
     6::800a81fc 43 18 03 00     sra        v1,v1,0x1
     6::800a8200 06 00 03 a2     sb         v1,0x6(s0)
     6::800a8204 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a8208 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a820c 07 00 eb a1     sb         t3,0x7(t7)
     6::800a8210 21 18 6c 01     addu       v1,t3,t4
     6::800a8214 43 18 03 00     sra        v1,v1,0x1
     6::800a8218 07 00 03 a2     sb         v1,0x7(s0)
     6::800a821c 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a8220 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a8224 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a8228 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a822c 5c 00 2b 8c     lw         t3,0x5c(at)
     6::800a8230 00 98 03 48     gte_stSZ3  v1
     6::800a8234 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a8238 10 00 03 ae     sw         v1,0x10(s0)
     6::800a823c 23 40 6b 00     subu       t0,v1,t3
     6::800a8240 c2 47 08 00     srl        t0,t0,0x1f
     6::800a8244 12 00 08 a2     sb         t0,0x12(s0)
     6::800a8248 40 18 03 00     sll        v1,v1,0x1
     6::800a824c 23 40 6b 00     subu       t0,v1,t3
     6::800a8250 c2 47 08 00     srl        t0,t0,0x1f
     6::800a8254 08 00 e0 03     jr         ra
     6::800a8258 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a825c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a825c                           XREF[12]:    FUN_OVR_226__800a7f0c:800a7f18(j
                                                                                          FUN_OVR_226__800a7f20:800a7f2c(j
                                                                                          FUN_OVR_226__800a7f34:800a7f40(j
                                                                                          FUN_OVR_226__800a7f5c:800a7f54(j
                                                                                          FUN_OVR_226__800a7f5c:800a7f68(j
                                                                                          FUN_OVR_226__800a7f5c:800a7f7c(j
                                                                                          FUN_OVR_226__800a7f5c:800a7f90(j
                                                                                          FUN_OVR_226__800a7f5c:800a7fa4(j
                                                                                          FUN_OVR_226__800a7f5c:800a7fbc(c
                                                                                          FUN_OVR_226__800a7f5c:800a7fd4(c
                                                                                          FUN_OVR_226__800a7f5c:800a803c(c
                                                                                          FUN_OVR_226__800a7f5c:800a8054(c
     6::800a825c 13 00 6f 82     lb         t7,0x13(s3)
     6::800a8260 13 00 90 82     lb         s0,0x13(s4)
     6::800a8264 13 00 b1 82     lb         s1,0x13(s5)
     6::800a8268 13 00 d2 82     lb         s2,0x13(s6)
     6::800a826c 24 18 f0 01     and        v1,t7,s0
     6::800a8270 24 18 71 00     and        v1,v1,s1
     6::800a8274 24 18 72 00     and        v1,v1,s2
     6::800a8278 22 ff 60 14     bne        v1,zero,LAB_OVR_226__800a7f04
     6::800a827c 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a8280 12 00 90 82     lb         s0,0x12(s4)
     6::800a8284 12 00 b1 82     lb         s1,0x12(s5)
     6::800a8288 12 00 d2 82     lb         s2,0x12(s6)
     6::800a828c 25 78 f0 01     or         t7,t7,s0
     6::800a8290 25 78 f1 01     or         t7,t7,s1
     6::800a8294 25 78 f2 01     or         t7,t7,s2
     6::800a8298 2e 00 e0 15     bne        t7,zero,LAB_OVR_226__800a8354
     6::800a829c 0c 00 03 24     _li        v1,0xc
     6::800a82a0 70 00 2a ac     sw         t2,0x70(at)
     6::800a82a4 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a82a8 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a82ac 94 01 2a 8c     lw         t2,0x194(at)
     6::800a82b0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a82b4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a82b8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a82bc 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a82c0 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a82c4 06 00 40 4b     NCLIP
     6::800a82c8 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a82cc 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a82d0 23 78 68 01     subu       t7,t3,t0
     6::800a82d4 23 80 88 01     subu       s0,t4,t0
     6::800a82d8 23 88 a8 01     subu       s1,t5,t0
     6::800a82dc 23 90 c8 01     subu       s2,t6,t0
     6::800a82e0 00 c0 08 48     gte_stMAC0 t0
     6::800a82e4 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a82e8 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a82f4
     6::800a82ec 22 40 08 00     _sub       t0,zero,t0
     6::800a82f0 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a82f4                           XREF[1]:     OVR_226::800a82e8(j)  
     6::800a82f4 06 00 40 4b     NCLIP
     6::800a82f8 24 18 6c 01     and        v1,t3,t4
     6::800a82fc 24 18 6d 00     and        v1,v1,t5
     6::800a8300 24 18 6e 00     and        v1,v1,t6
     6::800a8304 25 78 f0 01     or         t7,t7,s0
     6::800a8308 25 78 f1 01     or         t7,t7,s1
     6::800a830c 27 78 f2 01     nor        t7,t7,s2
     6::800a8310 25 78 e3 01     or         t7,t7,v1
     6::800a8314 fb fe e0 05     bltz       t7,LAB_OVR_226__800a7f04
     6::800a8318 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a831c f9 fe e0 05     bltz       t7,LAB_OVR_226__800a7f04
     6::800a8320 00 c0 03 48     _gte_stM   v1
     6::800a8324 25 40 09 01     or         t0,t0,t1
     6::800a8328 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a8334
     6::800a832c c2 47 08 00     _srl       t0,t0,0x1f
     6::800a8330 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a8334                           XREF[1]:     OVR_226::800a8328(j)  
     6::800a8334 80 40 08 00     sll        t0,t0,0x2
     6::800a8338 25 18 69 00     or         v1,v1,t1
     6::800a833c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a8340 c0 18 03 00     sll        v1,v1,0x3
     6::800a8344 70 00 2a 8c     lw         t2,0x70(at)
     6::800a8348 25 18 68 00     or         v1,v1,t0
     6::800a834c 24 18 6a 00     and        v1,v1,t2
     6::800a8350 ec fe 60 10     beq        v1,zero,LAB_OVR_226__800a7f04
                             LAB_OVR_226__800a8354                           XREF[1]:     OVR_226::800a8298(j)  
     6::800a8354 70 00 23 ac     _sw        v1,0x70(at)
     6::800a8358 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a835c 24 03 28 24     addiu      t0,at,0x324
     6::800a8360 ec 00 1e 11     beq        t0,s8,LAB_OVR_226__800a8714
     6::800a8364 04 00 39 27     _addiu     t9,t9,0x4
     6::800a8368 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a836c 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a8370 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a8374 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a8378 a8 00 01 04     bgez       zero,LAB_OVR_226__800a861c
     6::800a837c 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8380()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8380                           XREF[4]:     OVR_226::800a7eb4(c), 
                                                                                          OVR_226::800a7ec8(c), 
                                                                                          OVR_226::800a7edc(c), 
                                                                                          OVR_226::800a7ef0(c)  
     6::800a8380 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a8384 b4 00 ca af     sw         t2,0xb4(s8)
     6::800a8388 06 50 09 01     srlv       t2,t1,t0
     6::800a838c 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a8390 80 50 0a 00     sll        t2,t2,0x2
     6::800a8394 21 50 41 01     addu       t2,t2,at
     6::800a8398 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a839c 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a83a0 94 01 2a ac     sw         t2,0x194(at)
     6::800a83a4 02 9e 0a 00     srl        s3,t2,0x18
     6::800a83a8 1f 00 73 32     andi       s3,s3,0x1f
     6::800a83ac 06 98 63 02     srlv       s3,v1,s3
     6::800a83b0 ff 00 73 32     andi       s3,s3,0xff
     6::800a83b4 21 98 7e 02     addu       s3,s3,s8
     6::800a83b8 02 a4 0a 00     srl        s4,t2,0x10
     6::800a83bc 1f 00 94 32     andi       s4,s4,0x1f
     6::800a83c0 06 a0 83 02     srlv       s4,v1,s4
     6::800a83c4 ff 00 94 32     andi       s4,s4,0xff
     6::800a83c8 21 a0 9e 02     addu       s4,s4,s8
     6::800a83cc 02 aa 0a 00     srl        s5,t2,0x8
     6::800a83d0 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a83d4 06 a8 a3 02     srlv       s5,v1,s5
     6::800a83d8 ff 00 b5 32     andi       s5,s5,0xff
     6::800a83dc 21 a8 be 02     addu       s5,s5,s8
     6::800a83e0 1f 00 56 31     andi       s6,t2,0x1f
     6::800a83e4 06 b0 c3 02     srlv       s6,v1,s6
     6::800a83e8 ff 00 d6 32     andi       s6,s6,0xff
     6::800a83ec 21 b0 de 02     addu       s6,s6,s8
     6::800a83f0 13 00 6f 82     lb         t7,0x13(s3)
     6::800a83f4 13 00 90 82     lb         s0,0x13(s4)
     6::800a83f8 13 00 b1 82     lb         s1,0x13(s5)
     6::800a83fc 13 00 d2 82     lb         s2,0x13(s6)
     6::800a8400 24 18 f0 01     and        v1,t7,s0
     6::800a8404 24 18 71 00     and        v1,v1,s1
     6::800a8408 24 18 72 00     and        v1,v1,s2
     6::800a840c bd fe 60 14     bne        v1,zero,LAB_OVR_226__800a7f04
     6::800a8410 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a8414 12 00 90 82     lb         s0,0x12(s4)
     6::800a8418 12 00 b1 82     lb         s1,0x12(s5)
     6::800a841c 12 00 d2 82     lb         s2,0x12(s6)
     6::800a8420 25 78 f0 01     or         t7,t7,s0
     6::800a8424 25 78 f1 01     or         t7,t7,s1
     6::800a8428 25 78 f2 01     or         t7,t7,s2
     6::800a842c 28 00 e0 15     bne        t7,zero,LAB_OVR_226__800a84d0
     6::800a8430 0c 00 03 24     _li        v1,0xc
     6::800a8434 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a8438 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a843c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a8440 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a8444 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a8448 06 00 40 4b     NCLIP
     6::800a844c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a8450 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a8454 23 78 68 01     subu       t7,t3,t0
     6::800a8458 23 80 88 01     subu       s0,t4,t0
     6::800a845c 23 88 a8 01     subu       s1,t5,t0
     6::800a8460 23 90 c8 01     subu       s2,t6,t0
     6::800a8464 00 c0 08 48     gte_stMAC0 t0
     6::800a8468 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a846c 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a8478
     6::800a8470 22 40 08 00     _sub       t0,zero,t0
     6::800a8474 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a8478                           XREF[1]:     OVR_226::800a846c(j)  
     6::800a8478 06 00 40 4b     NCLIP
     6::800a847c 24 18 6c 01     and        v1,t3,t4
     6::800a8480 24 18 6d 00     and        v1,v1,t5
     6::800a8484 24 18 6e 00     and        v1,v1,t6
     6::800a8488 25 78 f0 01     or         t7,t7,s0
     6::800a848c 25 78 f1 01     or         t7,t7,s1
     6::800a8490 27 78 f2 01     nor        t7,t7,s2
     6::800a8494 25 78 e3 01     or         t7,t7,v1
     6::800a8498 9a fe e0 05     bltz       t7,LAB_OVR_226__800a7f04
     6::800a849c 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a84a0 98 fe e0 05     bltz       t7,LAB_OVR_226__800a7f04
     6::800a84a4 00 c0 03 48     _gte_stM   v1
     6::800a84a8 25 40 09 01     or         t0,t0,t1
     6::800a84ac 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a84b8
     6::800a84b0 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a84b4 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a84b8                           XREF[1]:     OVR_226::800a84ac(j)  
     6::800a84b8 80 40 08 00     sll        t0,t0,0x2
     6::800a84bc 25 18 69 00     or         v1,v1,t1
     6::800a84c0 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a84c4 c0 18 03 00     sll        v1,v1,0x3
     6::800a84c8 25 18 68 00     or         v1,v1,t0
     6::800a84cc 8d fe 60 10     beq        v1,zero,LAB_OVR_226__800a7f04
                             LAB_OVR_226__800a84d0                           XREF[1]:     OVR_226::800a842c(j)  
     6::800a84d0 70 00 23 ac     _sw        v1,0x70(at)
     6::800a84d4 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a84d8 04 00 39 27     addiu      t9,t9,0x4
     6::800a84dc c2 4f 09 00     srl        t1,t1,0x1f
     6::800a84e0 c0 4f 09 00     sll        t1,t1,0x1f
     6::800a84e4 c2 57 0a 00     srl        t2,t2,0x1f
     6::800a84e8 80 57 0a 00     sll        t2,t2,0x1e
     6::800a84ec 25 50 49 01     or         t2,t2,t1
     6::800a84f0 80 00 2a ac     sw         t2,0x80(at)
     6::800a84f4 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a84f8 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a84fc 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a8500 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a8504 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a8508 23 50 6c 01     subu       t2,t3,t4
     6::800a850c 82 48 03 00     srl        t1,v1,0x2
     6::800a8510 21 48 38 01     addu       t1,t1,t8
     6::800a8514 18 00 29 81     lb         t1,0x18(t1)
     6::800a8518 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a8524
     6::800a851c 21 e0 60 01     _move      gp,t3
     6::800a8520 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a8524                           XREF[1]:     OVR_226::800a8518(j)  
     6::800a8524 23 50 8d 03     subu       t2,gp,t5
     6::800a8528 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a8534
     6::800a852c 21 18 78 00     _addu      v1,v1,t8
     6::800a8530 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a8534                           XREF[1]:     OVR_226::800a8528(j)  
     6::800a8534 23 50 8e 03     subu       t2,gp,t6
     6::800a8538 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a8544
     6::800a853c 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a8540 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a8544                           XREF[1]:     OVR_226::800a8538(j)  
     6::800a8544 21 50 80 03     move       t2,gp
     6::800a8548 82 e1 1c 00     srl        gp,gp,0x6
     6::800a854c 21 e0 89 03     addu       gp,gp,t1
     6::800a8550 01 00 69 30     andi       t1,v1,0x1
     6::800a8554 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a8560
     6::800a8558 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a855c ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a8560                           XREF[1]:     OVR_226::800a8554(j)  
     6::800a8560 02 00 81 07     bgez       gp,LAB_OVR_226__800a856c
     6::800a8564 21 e0 85 03     _addu      gp,gp,a1
     6::800a8568 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a856c                           XREF[1]:     OVR_226::800a8560(j)  
     6::800a856c 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a8570 24 00 69 8c     lw         t1,0x24(v1)
     6::800a8574 23 40 48 01     subu       t0,t2,t0
     6::800a8578 84 00 29 ac     sw         t1,0x84(at)
     6::800a857c 0c 00 01 05     bgez       t0,LAB_OVR_226__800a85b0
     6::800a8580 20 00 28 8c     _lw        t0,0x20(at)
     6::800a8584 0c 00 63 24     addiu      v1,v1,0xc
     6::800a8588 23 40 48 01     subu       t0,t2,t0
     6::800a858c 08 00 01 05     bgez       t0,LAB_OVR_226__800a85b0
     6::800a8590 24 00 28 8c     _lw        t0,0x24(at)
     6::800a8594 0c 00 63 24     addiu      v1,v1,0xc
     6::800a8598 23 40 48 01     subu       t0,t2,t0
     6::800a859c 04 00 01 05     bgez       t0,LAB_OVR_226__800a85b0
     6::800a85a0 00 00 00 00     _nop
     6::800a85a4 02 00 20 05     bltz       t1,LAB_OVR_226__800a85b0
     6::800a85a8 00 00 00 00     _nop
     6::800a85ac 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a85b0                           XREF[4]:     OVR_226::800a857c(j), 
                                                                                          OVR_226::800a858c(j), 
                                                                                          OVR_226::800a859c(j), 
                                                                                          OVR_226::800a85a4(j)  
     6::800a85b0 94 01 2a 8c     lw         t2,0x194(at)
     6::800a85b4 00 00 68 8c     lw         t0,0x0(v1)
     6::800a85b8 04 00 69 8c     lw         t1,0x4(v1)
     6::800a85bc a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a85c0 ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a85c4 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a85c8 00 52 0a 00     sll        t2,t2,0x8
     6::800a85cc 0a 00 40 05     bltz       t2,LAB_OVR_226__800a85f8
     6::800a85d0 b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a85d4 06 00 68 a6     sh         t0,0x6(s3)
     6::800a85d8 08 00 68 8c     lw         t0,0x8(v1)
     6::800a85dc 06 00 89 a6     sh         t1,0x6(s4)
     6::800a85e0 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a85e4 00 54 0a 00     sll        t2,t2,0x10
     6::800a85e8 0b 00 40 05     bltz       t2,LAB_OVR_226__800a8618
     6::800a85ec 02 4c 08 00     _srl       t1,t0,0x10
     6::800a85f0 09 00 01 04     bgez       zero,LAB_OVR_226__800a8618
     6::800a85f4 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a85f8                           XREF[1]:     OVR_226::800a85cc(j)  
     6::800a85f8 06 00 69 a6     sh         t1,0x6(s3)
     6::800a85fc 08 00 69 8c     lw         t1,0x8(v1)
     6::800a8600 00 54 0a 00     sll        t2,t2,0x10
     6::800a8604 06 00 88 a6     sh         t0,0x6(s4)
     6::800a8608 02 44 09 00     srl        t0,t1,0x10
     6::800a860c 02 00 40 05     bltz       t2,LAB_OVR_226__800a8618
     6::800a8610 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a8614 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a8618                           XREF[3]:     OVR_226::800a85e8(j), 
                                                                                          OVR_226::800a85f0(j), 
                                                                                          OVR_226::800a860c(j)  
     6::800a8618 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a861c                           XREF[1]:     FUN_OVR_226__800a825c:800a8378(j
     6::800a861c 00 00 00 00     nop
     6::800a8620 23 88 63 01     subu       s1,t3,v1
     6::800a8624 23 90 83 01     subu       s2,t4,v1
     6::800a8628 23 78 a3 01     subu       t7,t5,v1
     6::800a862c 23 80 c3 01     subu       s0,t6,v1
     6::800a8630 42 8f 11 00     srl        s1,s1,0x1d
     6::800a8634 04 00 31 32     andi       s1,s1,0x4
     6::800a8638 02 97 12 00     srl        s2,s2,0x1c
     6::800a863c 08 00 52 32     andi       s2,s2,0x8
     6::800a8640 25 88 32 02     or         s1,s1,s2
     6::800a8644 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a8648 10 00 ef 31     andi       t7,t7,0x10
     6::800a864c 25 88 2f 02     or         s1,s1,t7
     6::800a8650 82 86 10 00     srl        s0,s0,0x1a
     6::800a8654 20 00 10 32     andi       s0,s0,0x20
     6::800a8658 25 88 30 02     or         s1,s1,s0
     6::800a865c 26 00 20 12     beq        s1,zero,LAB_OVR_226__800a86f8
     6::800a8660 21 68 60 02     _move      t5,s3
     6::800a8664 21 70 80 02     move       t6,s4
     6::800a8668 b8 00 de 27     addiu      s8,s8,0xb8
     6::800a866c 00 00 cf 27     addiu      t7,s8,0x0
     6::800a8670 54 a0 02 0c     jal        FUN_OVR_226__800a8150                            undefined FUN_OVR_226__800a8150()
     6::800a8674 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a8678 21 68 80 02     move       t5,s4
     6::800a867c 21 70 c0 02     move       t6,s6
     6::800a8680 14 00 cf 27     addiu      t7,s8,0x14
     6::800a8684 54 a0 02 0c     jal        FUN_OVR_226__800a8150                            undefined FUN_OVR_226__800a8150()
     6::800a8688 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a868c 21 68 a0 02     move       t5,s5
     6::800a8690 21 70 60 02     move       t6,s3
     6::800a8694 28 00 cf 27     addiu      t7,s8,0x28
     6::800a8698 54 a0 02 0c     jal        FUN_OVR_226__800a8150                            undefined FUN_OVR_226__800a8150()
     6::800a869c 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a86a0 21 68 c0 02     move       t5,s6
     6::800a86a4 21 70 a0 02     move       t6,s5
     6::800a86a8 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a86ac 54 a0 02 0c     jal        FUN_OVR_226__800a8150                            undefined FUN_OVR_226__800a8150()
     6::800a86b0 a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a86b4 21 68 80 02     move       t5,s4
     6::800a86b8 21 70 a0 02     move       t6,s5
     6::800a86bc 14 00 cf 27     addiu      t7,s8,0x14
     6::800a86c0 54 a0 02 0c     jal        FUN_OVR_226__800a8150                            undefined FUN_OVR_226__800a8150()
     6::800a86c4 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a86c8 21 18 21 02     addu       v1,s1,at
     6::800a86cc 48 01 63 8c     lw         v1,0x148(v1)
     6::800a86d0 0b 80 08 3c     lui        t0,0x800b
     6::800a86d4 e8 86 08 25     addiu      t0,t0,-0x7918
     6::800a86d8 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a86dc 3c 00 28 af     sw         t0=>LAB_OVR_226__800a86e8,0x3c(t9)
     6::800a86e0 08 00 60 00     jr         v1
     6::800a86e4 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a86e8                           XREF[1]:     FUN_OVR_226__800a8380:800a86dc(*
     6::800a86e8 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a86ec fc ff 39 27     addiu      t9,t9,-0x4
     6::800a86f0 08 00 e0 03     jr         ra
     6::800a86f4 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a86f8                           XREF[1]:     OVR_226::800a865c(j)  
     6::800a86f8 70 00 23 8c     lw         v1,0x70(at)
     6::800a86fc fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8700 21 18 61 00     addu       v1,v1,at
     6::800a8704 84 01 63 8c     lw         v1,0x184(v1)
     6::800a8708 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a870c 08 00 60 00     jr         v1
     6::800a8710 00 00 00 00     _nop
                             LAB_OVR_226__800a8714                           XREF[1]:     OVR_226::800a8360(j)  
     6::800a8714 84 00 23 8c     lw         v1,0x84(at)
     6::800a8718 24 03 2a 24     addiu      t2,at,0x324
     6::800a871c 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a87b8
     6::800a8720 20 03 28 8c     _lw        t0,0x320(at)
     6::800a8724 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a8728 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a8784
     6::800a872c 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a8730 0b 80 0a 3c     lui        t2,0x800b
     6::800a8734 0c 81 4a 25     addiu      t2,t2,-0x7ef4
     6::800a8738 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a87b8
     6::800a873c 94 01 23 8c     _lw        v1,0x194(at)
     6::800a8740 40 40 08 00     sll        t0,t0,0x1
     6::800a8744 00 1a 03 00     sll        v1,v1,0x8
     6::800a8748 02 00 61 04     bgez       v1,LAB_OVR_226__800a8754
     6::800a874c 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a8750 c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_226__800a8754                           XREF[1]:     OVR_226::800a8748(j)  
     6::800a8754 21 40 09 01     addu       t0,t0,t1
     6::800a8758 21 50 48 01     addu       t2,t2,t0
     6::800a875c 00 00 48 8d     lw         t0,0x0(t2)
     6::800a8760 04 00 49 8d     lw         t1,0x4(t2)
     6::800a8764 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a8768 06 00 68 a6     sh         t0,0x6(s3)
     6::800a876c 08 00 48 85     lh         t0,0x8(t2)
     6::800a8770 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a8774 06 00 89 a6     sh         t1,0x6(s4)
     6::800a8778 0a 00 49 85     lh         t1,0xa(t2)
     6::800a877c 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a8780 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a8784                           XREF[2]:     OVR_226::800a8728(j), 
                                                                                          OVR_226::800a87c4(j)  
     6::800a8784 70 00 23 8c     lw         v1,0x70(at)
     6::800a8788 00 00 00 00     nop
     6::800a878c 21 18 61 00     addu       v1,v1,at
     6::800a8790 84 01 63 8c     lw         v1,0x184(v1)
     6::800a8794 00 00 00 00     nop
     6::800a8798 09 f8 60 00     jalr       v1
     6::800a879c fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a87a0 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a87a4 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a87a8 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a87ac a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a87b0 08 00 e0 03     jr         ra
     6::800a87b4 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a87b8                           XREF[2]:     OVR_226::800a871c(j), 
                                                                                          OVR_226::800a8738(j)  
     6::800a87b8 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a87bc b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a87c0 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a87c4 ef ff 01 04     bgez       zero,LAB_OVR_226__800a8784
     6::800a87c8 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a87cc 21 98 80 02     move       s3,s4
     6::800a87d0 21 a0 c0 02     move       s4,s6
     6::800a87d4 13 00 6f 82     lb         t7,0x13(s3)
     6::800a87d8 13 00 90 82     lb         s0,0x13(s4)
     6::800a87dc 13 00 b1 82     lb         s1,0x13(s5)
     6::800a87e0 24 18 f0 01     and        v1,t7,s0
     6::800a87e4 24 18 71 00     and        v1,v1,s1
     6::800a87e8 c6 fd 60 04     bltz       v1,LAB_OVR_226__800a7f04
     6::800a87ec 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a87f0 12 00 90 82     lb         s0,0x12(s4)
     6::800a87f4 12 00 b1 82     lb         s1,0x12(s5)
     6::800a87f8 25 78 f0 01     or         t7,t7,s0
     6::800a87fc 25 78 f1 01     or         t7,t7,s1
     6::800a8800 62 00 e0 05     bltz       t7,LAB_OVR_226__800a898c
     6::800a8804 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a8808 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a880c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a8810 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a8814 08 00 90 8e     lw         s0,0x8(s4)
     6::800a8818 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a881c 06 00 73 86     lh         s3,0x6(s3)
     6::800a8820 06 00 94 86     lh         s4,0x6(s4)
     6::800a8824 06 00 b5 86     lh         s5,0x6(s5)
     6::800a8828 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a882c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a8830 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a8834 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a8838 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a883c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a8840 60 00 03 3c     lui        v1,0x60
     6::800a8844 24 48 83 02     and        t1,s4,v1
     6::800a8848 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a8854
     6::800a884c 00 36 03 3c     _lui       v1,0x3600
     6::800a8850 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a8854                           XREF[1]:     OVR_226::800a8848(j)  
     6::800a8854 25 18 6f 00     or         v1,v1,t7
     6::800a8858 04 00 43 ac     sw         v1,0x4(v0)
     6::800a885c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a8860 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a8864 10 00 50 ac     sw         s0,0x10(v0)
     6::800a8868 14 00 4c ac     sw         t4,0x14(v0)
     6::800a886c 18 00 54 ac     sw         s4,0x18(v0)
     6::800a8870 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a8874 20 00 4d ac     sw         t5,0x20(v0)
     6::800a8878 24 00 55 ac     sw         s5,0x24(v0)
     6::800a887c 28 00 09 24     li         t1,0x28
     6::800a8880 39 00 01 04     bgez       zero,LAB_OVR_226__800a8968
     6::800a8884 00 09 0a 3c     _lui       t2,0x900
     6::800a8888 13 00 6f 82     lb         t7,0x13(s3)
     6::800a888c 13 00 90 82     lb         s0,0x13(s4)
     6::800a8890 13 00 b1 82     lb         s1,0x13(s5)
     6::800a8894 13 00 d2 82     lb         s2,0x13(s6)
     6::800a8898 24 18 f0 01     and        v1,t7,s0
     6::800a889c 24 18 71 00     and        v1,v1,s1
     6::800a88a0 24 18 72 00     and        v1,v1,s2
     6::800a88a4 97 fd 60 14     bne        v1,zero,LAB_OVR_226__800a7f04
     6::800a88a8 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a88ac 12 00 90 82     lb         s0,0x12(s4)
     6::800a88b0 12 00 b1 82     lb         s1,0x12(s5)
     6::800a88b4 12 00 d2 82     lb         s2,0x12(s6)
     6::800a88b8 25 78 f0 01     or         t7,t7,s0
     6::800a88bc 25 78 f1 01     or         t7,t7,s1
     6::800a88c0 25 78 f2 01     or         t7,t7,s2
     6::800a88c4 5a 00 e0 15     bne        t7,zero,LAB_OVR_226__800a8a30
     6::800a88c8 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800a88cc 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a88d0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a88d4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a88d8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a88dc 08 00 90 8e     lw         s0,0x8(s4)
     6::800a88e0 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a88e4 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a88e8 06 00 73 86     lh         s3,0x6(s3)
     6::800a88ec 06 00 94 86     lh         s4,0x6(s4)
     6::800a88f0 06 00 b5 86     lh         s5,0x6(s5)
     6::800a88f4 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a88f8 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a88fc 06 00 d4 86     lh         s4,0x6(s6)
     6::800a8900 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a8904 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a8908 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a890c a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a8910 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a8914 60 00 03 3c     lui        v1,0x60
     6::800a8918 24 48 83 02     and        t1,s4,v1
     6::800a891c 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a8928
     6::800a8920 00 3e 03 3c     _lui       v1,0x3e00
     6::800a8924 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a8928                           XREF[1]:     OVR_226::800a891c(j)  
     6::800a8928 25 18 6f 00     or         v1,v1,t7
     6::800a892c 04 00 43 ac     sw         v1,0x4(v0)
     6::800a8930 08 00 4b ac     sw         t3,0x8(v0)
     6::800a8934 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a8938 10 00 50 ac     sw         s0,0x10(v0)
     6::800a893c 14 00 4c ac     sw         t4,0x14(v0)
     6::800a8940 18 00 54 ac     sw         s4,0x18(v0)
     6::800a8944 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a8948 20 00 4d ac     sw         t5,0x20(v0)
     6::800a894c 24 00 55 ac     sw         s5,0x24(v0)
     6::800a8950 28 00 52 ac     sw         s2,0x28(v0)
     6::800a8954 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a8958 02 1c 15 00     srl        v1,s5,0x10
     6::800a895c 30 00 43 ac     sw         v1,0x30(v0)
     6::800a8960 34 00 09 24     li         t1,0x34
     6::800a8964 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a8968                           XREF[1]:     OVR_226::800a8880(j)  
     6::800a8968 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a896c 00 42 02 00     sll        t0,v0,0x8
     6::800a8970 02 42 08 00     srl        t0,t0,0x8
     6::800a8974 25 18 6a 00     or         v1,v1,t2
     6::800a8978 00 00 43 ac     sw         v1,0x0(v0)
     6::800a897c 21 10 49 00     addu       v0,v0,t1
     6::800a8980 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a8984 08 00 e0 03     jr         ra
     6::800a8988 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800a898c                           XREF[1]:     OVR_226::800a8800(j)  
     6::800a898c 58 00 3f ac     sw         ra,0x58(at)
     6::800a8990 98 01 2f 84     lh         t7,0x198(at)
     6::800a8994 9a 01 30 84     lh         s0,0x19a(at)
     6::800a8998 9c 01 31 84     lh         s1,0x19c(at)
     6::800a899c 00 00 63 86     lh         v1,0x0(s3)
     6::800a89a0 02 00 68 86     lh         t0,0x2(s3)
     6::800a89a4 be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a89a8 04 00 69 86     _lh        t1,0x4(s3)
     6::800a89ac 0b 00 40 05     bltz       t2,LAB_OVR_226__800a89dc
     6::800a89b0 00 00 83 86     _lh        v1,0x0(s4)
     6::800a89b4 02 00 88 86     lh         t0,0x2(s4)
     6::800a89b8 be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a89bc 04 00 89 86     _lh        t1,0x4(s4)
     6::800a89c0 06 00 40 05     bltz       t2,LAB_OVR_226__800a89dc
     6::800a89c4 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a89c8 02 00 a8 86     lh         t0,0x2(s5)
     6::800a89cc be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a89d0 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a89d4 58 00 3f 8c     lw         ra,0x58(at)
     6::800a89d8 4a fd 41 05     bgez       t2,LAB_OVR_226__800a7f04
                             LAB_OVR_226__800a89dc                           XREF[2]:     OVR_226::800a89ac(j), 
                                                                                          OVR_226::800a89c0(j)  
     6::800a89dc 10 00 2f 8c     lw         t7,0x10(at)
     6::800a89e0 80 00 23 8c     lw         v1,0x80(at)
     6::800a89e4 a6 01 28 84     lh         t0,0x1a6(at)
     6::800a89e8 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a89ec 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a89f0 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a89f4 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a89f8 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a89fc 21 68 60 02     move       t5,s3
     6::800a8a00 ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8a04 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a8a08 21 68 80 02     move       t5,s4
     6::800a8a0c ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8a10 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a8a14 21 68 a0 02     move       t5,s5
     6::800a8a18 ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8a1c 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a8a20 58 00 3f 8c     lw         ra,0x58(at)
     6::800a8a24 30 00 ef 25     addiu      t7,t7,0x30
     6::800a8a28 08 00 e0 03     jr         ra
     6::800a8a2c 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_226__800a8a30                           XREF[1]:     OVR_226::800a88c4(j)  
     6::800a8a30 58 00 3f ac     sw         ra,0x58(at)
     6::800a8a34 98 01 2f 84     lh         t7,0x198(at)
     6::800a8a38 9a 01 30 84     lh         s0,0x19a(at)
     6::800a8a3c 9c 01 31 84     lh         s1,0x19c(at)
     6::800a8a40 00 00 63 86     lh         v1,0x0(s3)
     6::800a8a44 02 00 68 86     lh         t0,0x2(s3)
     6::800a8a48 be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a8a4c 04 00 69 86     _lh        t1,0x4(s3)
     6::800a8a50 10 00 40 05     bltz       t2,LAB_OVR_226__800a8a94
     6::800a8a54 00 00 83 86     _lh        v1,0x0(s4)
     6::800a8a58 02 00 88 86     lh         t0,0x2(s4)
     6::800a8a5c be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a8a60 04 00 89 86     _lh        t1,0x4(s4)
     6::800a8a64 0b 00 40 05     bltz       t2,LAB_OVR_226__800a8a94
     6::800a8a68 00 00 a3 86     _lh        v1,0x0(s5)
     6::800a8a6c 02 00 a8 86     lh         t0,0x2(s5)
     6::800a8a70 be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a8a74 04 00 a9 86     _lh        t1,0x4(s5)
     6::800a8a78 06 00 40 05     bltz       t2,LAB_OVR_226__800a8a94
     6::800a8a7c 00 00 c3 86     _lh        v1,0x0(s6)
     6::800a8a80 02 00 c8 86     lh         t0,0x2(s6)
     6::800a8a84 be a2 02 0c     jal        FUN_OVR_226__800a8af8                            undefined FUN_OVR_226__800a8af8()
     6::800a8a88 04 00 c9 86     _lh        t1,0x4(s6)
     6::800a8a8c 58 00 3f 8c     lw         ra,0x58(at)
     6::800a8a90 1c fd 41 05     bgez       t2,LAB_OVR_226__800a7f04
                             LAB_OVR_226__800a8a94                           XREF[3]:     OVR_226::800a8a50(j), 
                                                                                          OVR_226::800a8a64(j), 
                                                                                          OVR_226::800a8a78(j)  
     6::800a8a94 10 00 2f 8c     lw         t7,0x10(at)
     6::800a8a98 80 00 23 8c     lw         v1,0x80(at)
     6::800a8a9c a6 01 28 84     lh         t0,0x1a6(at)
     6::800a8aa0 a2 01 29 84     lh         t1,0x1a2(at)
     6::800a8aa4 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800a8aa8 01 00 63 34     ori        v1,v1,0x1
     6::800a8aac 00 00 e3 ad     sw         v1,0x0(t7)
     6::800a8ab0 08 00 e8 a5     sh         t0,0x8(t7)
     6::800a8ab4 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800a8ab8 21 68 60 02     move       t5,s3
     6::800a8abc ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8ac0 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800a8ac4 21 68 80 02     move       t5,s4
     6::800a8ac8 ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8acc 18 00 f0 25     _addiu     s0,t7,0x18
     6::800a8ad0 21 68 a0 02     move       t5,s5
     6::800a8ad4 ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8ad8 24 00 f0 25     _addiu     s0,t7,0x24
     6::800a8adc 21 68 c0 02     move       t5,s6
     6::800a8ae0 ce a2 02 0c     jal        FUN_OVR_226__800a8b38                            undefined FUN_OVR_226__800a8b38()
     6::800a8ae4 30 00 f0 25     _addiu     s0,t7,0x30
     6::800a8ae8 58 00 3f 8c     lw         ra,0x58(at)
     6::800a8aec 3c 00 ef 25     addiu      t7,t7,0x3c
     6::800a8af0 08 00 e0 03     jr         ra
     6::800a8af4 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8af8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8af8                           XREF[7]:     FUN_OVR_226__800a825c:800a89a4(c
                                                                                          FUN_OVR_226__800a825c:800a89b8(c
                                                                                          FUN_OVR_226__800a825c:800a89cc(c
                                                                                          FUN_OVR_226__800a825c:800a8a48(c
                                                                                          FUN_OVR_226__800a825c:800a8a5c(c
                                                                                          FUN_OVR_226__800a825c:800a8a70(c
                                                                                          FUN_OVR_226__800a825c:800a8a84(c
     6::800a8af8 23 18 6f 00     subu       v1,v1,t7
     6::800a8afc 02 00 61 04     bgez       v1,LAB_OVR_226__800a8b08
     6::800a8b00 23 40 10 01     _subu      t0,t0,s0
     6::800a8b04 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_226__800a8b08                           XREF[1]:     OVR_226::800a8afc(j)  
     6::800a8b08 00 ff 6b 24     addiu      t3,v1,-0x100
     6::800a8b0c 02 00 01 05     bgez       t0,LAB_OVR_226__800a8b18
     6::800a8b10 23 48 31 01     _subu      t1,t1,s1
     6::800a8b14 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_226__800a8b18                           XREF[1]:     OVR_226::800a8b0c(j)  
     6::800a8b18 80 fe 0c 25     addiu      t4,t0,-0x180
     6::800a8b1c 02 00 21 05     bgez       t1,LAB_OVR_226__800a8b28
     6::800a8b20 00 00 00 00     _nop
     6::800a8b24 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_226__800a8b28                           XREF[1]:     OVR_226::800a8b1c(j)  
     6::800a8b28 00 ff 2d 25     addiu      t5,t1,-0x100
     6::800a8b2c 24 58 6c 01     and        t3,t3,t4
     6::800a8b30 08 00 e0 03     jr         ra
     6::800a8b34 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8b38()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8b38                           XREF[7]:     FUN_OVR_226__800a825c:800a8a00(c
                                                                                          FUN_OVR_226__800a825c:800a8a0c(c
                                                                                          FUN_OVR_226__800a825c:800a8a18(c
                                                                                          FUN_OVR_226__800a825c:800a8abc(c
                                                                                          FUN_OVR_226__800a825c:800a8ac8(c
                                                                                          FUN_OVR_226__800a825c:800a8ad4(c
                                                                                          FUN_OVR_226__800a825c:800a8ae0(c
     6::800a8b38 13 00 a3 81     lb         v1,0x13(t5)
     6::800a8b3c 00 00 a8 8d     lw         t0,0x0(t5)
     6::800a8b40 04 00 a9 8d     lw         t1,0x4(t5)
     6::800a8b44 08 00 aa 8d     lw         t2,0x8(t5)
     6::800a8b48 00 1e 03 00     sll        v1,v1,0x18
     6::800a8b4c 25 50 43 01     or         t2,t2,v1
     6::800a8b50 00 00 08 ae     sw         t0,0x0(s0)
     6::800a8b54 04 00 09 ae     sw         t1,0x4(s0)
     6::800a8b58 08 00 e0 03     jr         ra
     6::800a8b5c 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_226__800a8b60                           XREF[1]:     OVR_226::800ab43c(*)  
     6::800a8b60 09 80 08 3c     lui        t0,0x8009
     6::800a8b64 04 64 08 25     addiu      t0,t0,0x6404
     6::800a8b68 64 00 28 ac     sw         t0=>DAT_80096404,0x64(at)                        = ??
     6::800a8b6c 04 00 83 8c     lw         v1,0x4(a0)
                             LAB_OVR_226__800a8b70                           XREF[1]:     OVR_226::800a8e48(j)  
     6::800a8b70 bd 00 80 10     beq        a0,zero,LAB_OVR_226__800a8e68
     6::800a8b74 00 00 00 00     _nop
     6::800a8b78 1c 00 78 8c     lw         t8,0x1c(v1)
     6::800a8b7c 18 00 79 8c     lw         t9,0x18(v1)
     6::800a8b80 c8 00 2a 8c     lw         t2,0xc8(at)
     6::800a8b84 3c 00 08 97     lhu        t0,0x3c(t8)
     6::800a8b88 68 00 39 ac     sw         t9,0x68(at)
     6::800a8b8c c2 48 08 00     srl        t1,t0,0x3
     6::800a8b90 fc 01 29 31     andi       t1,t1,0x1fc
     6::800a8b94 21 48 2a 01     addu       t1,t1,t2
     6::800a8b98 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a8b9c 00 00 29 8d     lw         t1,0x0(t1)
     6::800a8ba0 1f 00 08 31     andi       t0,t0,0x1f
     6::800a8ba4 bc 00 28 ac     sw         t0,0xbc(at)
     6::800a8ba8 c4 00 29 ac     sw         t1,0xc4(at)
                             LAB_OVR_226__800a8bac                           XREF[1]:     OVR_226::800a8e3c(j)  
     6::800a8bac 30 00 23 8c     lw         v1,0x30(at)
     6::800a8bb0 00 1a 48 24     addiu      t0,v0,0x1a00
     6::800a8bb4 23 18 68 00     subu       v1,v1,t0
     6::800a8bb8 be e0 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a8bbc bc 00 23 8c     _lw        v1,0xbc(at)
     6::800a8bc0 c4 00 28 8c     lw         t0,0xc4(at)
     6::800a8bc4 06 00 61 04     bgez       v1,LAB_OVR_226__800a8be0
     6::800a8bc8 c0 00 29 8c     _lw        t1,0xc0(at)
     6::800a8bcc 1f 00 03 24     li         v1,0x1f
     6::800a8bd0 04 00 28 8d     lw         t0,0x4(t1)
     6::800a8bd4 04 00 29 25     addiu      t1,t1,0x4
     6::800a8bd8 c0 00 29 ac     sw         t1,0xc0(at)
     6::800a8bdc c4 00 28 ac     sw         t0,0xc4(at)
                             LAB_OVR_226__800a8be0                           XREF[1]:     OVR_226::800a8bc4(j)  
     6::800a8be0 04 40 68 00     sllv       t0,t0,v1
     6::800a8be4 ff ff 63 24     addiu      v1,v1,-0x1
     6::800a8be8 91 00 01 05     bgez       t0,LAB_OVR_226__800a8e30
     6::800a8bec bc 00 23 ac     _sw        v1,0xbc(at)
     6::800a8bf0 b4 01 3e 24     addiu      s8,at,0x1b4
     6::800a8bf4 b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a8bf8 00 00 14 8f     lw         s4,0x0(t8)
     6::800a8bfc 04 00 16 8f     lw         s6,0x4(t8)
     6::800a8c00 ff ff 93 32     andi       s3,s4,0xffff
     6::800a8c04 00 99 13 00     sll        s3,s3,0x4
     6::800a8c08 21 98 77 02     addu       s3,s3,s7
     6::800a8c0c 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a8c14 02 a4 14 00     srl        s4,s4,0x10
     6::800a8c18 00 a1 14 00     sll        s4,s4,0x4
     6::800a8c1c 21 a0 97 02     addu       s4,s4,s7
     6::800a8c20 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a8c28 ff ff d5 32     andi       s5,s6,0xffff
     6::800a8c2c 00 a9 15 00     sll        s5,s5,0x4
     6::800a8c30 21 a8 b7 02     addu       s5,s5,s7
     6::800a8c34 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a8c3c 02 b4 16 00     srl        s6,s6,0x10
     6::800a8c40 00 b1 16 00     sll        s6,s6,0x4
     6::800a8c44 30 00 28 4a     RTPT
     6::800a8c48 21 b0 d7 02     addu       s6,s6,s7
     6::800a8c4c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a8c50 08 00 90 8e     lw         s0,0x8(s4)
     6::800a8c54 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a8c58 08 00 cf af     sw         t7,0x8(s8)
     6::800a8c5c 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a8c60 30 00 d1 af     sw         s1,0x30(s8)
     6::800a8c64 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a8c68 00 f8 43 48     gte_stFLAG v1
     6::800a8c6c 10 00 d1 eb     gte_stSZ1  0x10(s8)
     6::800a8c70 80 1b 03 00     sll        v1,v1,0xe
     6::800a8c74 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a8c78 75 00 60 14     bne        v1,zero,LAB_OVR_226__800a8e50
     6::800a8c7c 08 00 14 8f     _lw        s4,0x8(t8)
     6::800a8c80 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a8c84 24 00 d2 eb     gte_stSZ2  0x24(s8)
     6::800a8c88 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a8c8c 38 00 d3 eb     gte_stSZ3  0x38(s8)
     6::800a8c90 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a8c94 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a8c98 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a8c9c 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a8ca0 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a8ca4 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a8ca8 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a8cb0 ff ff 93 32     andi       s3,s4,0xffff
     6::800a8cb4 00 99 13 00     sll        s3,s3,0x4
     6::800a8cb8 21 98 77 02     addu       s3,s3,s7
     6::800a8cbc 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a8cc4 02 a4 14 00     srl        s4,s4,0x10
     6::800a8cc8 00 a1 14 00     sll        s4,s4,0x4
     6::800a8ccc 21 a0 97 02     addu       s4,s4,s7
     6::800a8cd0 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a8cd8 21 c8 20 00     move       t9,at
     6::800a8cdc 00 00 00 00     nop
     6::800a8ce0 30 00 28 4a     RTPT
     6::800a8ce4 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a8ce8 08 00 70 8e     lw         s0,0x8(s3)
     6::800a8cec 08 00 91 8e     lw         s1,0x8(s4)
     6::800a8cf0 44 00 cf af     sw         t7,0x44(s8)
     6::800a8cf4 58 00 d0 af     sw         s0,0x58(s8)
     6::800a8cf8 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a8cfc 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a8d00 00 f8 43 48     gte_stFLAG v1
     6::800a8d04 4c 00 d1 eb     gte_stSZ1  0x4c(s8)
     6::800a8d08 80 1b 03 00     sll        v1,v1,0xe
     6::800a8d0c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a8d10 4f 00 60 14     bne        v1,zero,LAB_OVR_226__800a8e50
     6::800a8d14 0c 00 14 8f     _lw        s4,0xc(t8)
     6::800a8d18 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a8d1c 60 00 d2 eb     gte_stSZ2  0x60(s8)
     6::800a8d20 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a8d24 74 00 d3 eb     gte_stSZ3  0x74(s8)
     6::800a8d28 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a8d2c 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a8d30 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a8d34 10 00 15 97     lhu        s5,0x10(t8)
     6::800a8d38 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a8d3c 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a8d40 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a8d44 ff ff 93 32     andi       s3,s4,0xffff
     6::800a8d48 00 99 13 00     sll        s3,s3,0x4
     6::800a8d4c 21 98 77 02     addu       s3,s3,s7
     6::800a8d50 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a8d58 02 a4 14 00     srl        s4,s4,0x10
     6::800a8d5c 00 a1 14 00     sll        s4,s4,0x4
     6::800a8d60 21 a0 97 02     addu       s4,s4,s7
     6::800a8d64 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a8d6c 14 00 09 8f     lw         t1,0x14(t8)
     6::800a8d70 00 a9 15 00     sll        s5,s5,0x4
     6::800a8d74 21 a8 b7 02     addu       s5,s5,s7
     6::800a8d78 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a8d80 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a8d84 08 00 08 24     li         t0,0x8
     6::800a8d88 30 00 28 4a     RTPT
     6::800a8d8c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a8d90 08 00 90 8e     lw         s0,0x8(s4)
     6::800a8d94 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a8d98 80 00 cf af     sw         t7,0x80(s8)
     6::800a8d9c 94 00 d0 af     sw         s0,0x94(s8)
     6::800a8da0 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a8da4 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a8da8 00 f8 43 48     gte_stFLAG v1
     6::800a8dac 88 00 d1 eb     gte_stSZ1  0x88(s8)
     6::800a8db0 80 1b 03 00     sll        v1,v1,0xe
     6::800a8db4 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a8db8 25 00 60 14     bne        v1,zero,LAB_OVR_226__800a8e50
     6::800a8dbc 98 00 cd eb     _gte_stS   0x98(s8)
     6::800a8dc0 9c 00 d2 eb     gte_stSZ2  0x9c(s8)
     6::800a8dc4 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a8dc8 b0 00 d3 eb     gte_stSZ3  0xb0(s8)
     6::800a8dcc 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a8dd0 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a8dd4 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a8dd8 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a8ddc a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a8de0 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a8de4 50 00 03 3c     lui        v1,0x50
     6::800a8de8 78 64 63 34     ori        v1,v1,0x6478
     6::800a8dec a2 a4 02 0c     jal        FUN_OVR_226__800a9288                            undefined FUN_OVR_226__800a9288()
     6::800a8df0 00 00 0a 24     _li        t2,0x0
     6::800a8df4 14 50 03 3c     lui        v1,0x5014
     6::800a8df8 8c 78 63 34     ori        v1,v1,0x788c
     6::800a8dfc 0d 00 08 24     li         t0,0xd
     6::800a8e00 a2 a4 02 0c     jal        FUN_OVR_226__800a9288                            undefined FUN_OVR_226__800a9288()
     6::800a8e04 04 00 0a 24     _li        t2,0x4
     6::800a8e08 78 64 03 3c     lui        v1,0x6478
     6::800a8e0c a0 28 63 34     ori        v1,v1,0x28a0
     6::800a8e10 12 00 08 24     li         t0,0x12
     6::800a8e14 a2 a4 02 0c     jal        FUN_OVR_226__800a9288                            undefined FUN_OVR_226__800a9288()
     6::800a8e18 08 00 0a 24     _li        t2,0x8
     6::800a8e1c 8c 78 03 3c     lui        v1,0x788c
     6::800a8e20 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a8e24 17 00 08 24     li         t0,0x17
     6::800a8e28 a2 a4 02 0c     jal        FUN_OVR_226__800a9288                            undefined FUN_OVR_226__800a9288()
     6::800a8e2c 0c 00 0a 24     _li        t2,0xc
                             LAB_OVR_226__800a8e30                           XREF[2]:     OVR_226::800a8be8(j), 
                                                                                          OVR_226::800a8e60(j)  
     6::800a8e30 68 00 39 8c     lw         t9,0x68(at)
     6::800a8e34 5c 00 18 27     addiu      t8,t8,0x5c
     6::800a8e38 ff ff 39 27     addiu      t9,t9,-0x1
     6::800a8e3c 5b ff 20 1f     bgtz       t9,LAB_OVR_226__800a8bac
     6::800a8e40 68 00 39 ac     _sw        t9,0x68(at)
     6::800a8e44 00 00 84 8c     lw         a0,0x0(a0)
     6::800a8e48 49 ff 01 04     bgez       zero,LAB_OVR_226__800a8b70
     6::800a8e4c 04 00 83 8c     _lw        v1,0x4(a0)
                             LAB_OVR_226__800a8e50                           XREF[3]:     OVR_226::800a8c78(j), 
                                                                                          OVR_226::800a8d10(j), 
                                                                                          OVR_226::800a8db8(j)  
     6::800a8e50 64 00 28 8c     lw         t0,0x64(at)
     6::800a8e54 00 00 00 00     nop
     6::800a8e58 00 00 18 ad     sw         t8,0x0(t0)
     6::800a8e5c 04 00 08 25     addiu      t0,t0,0x4
     6::800a8e60 f3 ff 01 04     bgez       zero,LAB_OVR_226__800a8e30
     6::800a8e64 64 00 28 ac     _sw        t0,0x64(at)
                             LAB_OVR_226__800a8e68                           XREF[1]:     OVR_226::800a8b70(j)  
     6::800a8e68 64 00 28 8c     lw         t0,0x64(at)
     6::800a8e6c 06 e0 01 04     bgez       zero,LAB_OVR_226__800a0e88
     6::800a8e70 00 00 00 ad     _sw        zero,0x0(t0)
                             LAB_OVR_226__800a8e74                           XREF[6]:     FUN_OVR_226__800a91a8:800a921c(j
                                                                                          FUN_OVR_226__800a91a8:800a9224(j
                                                                                          FUN_OVR_226__800a91a8:800a9258(j
                                                                                          OVR_226::800a935c(j), 
                                                                                          OVR_226::800a9364(j), 
                                                                                          OVR_226::800a9390(j)  
     6::800a8e74 08 00 e0 03     jr         ra
     6::800a8e78 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8e7c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8e7c                           XREF[4]:     FUN_OVR_226__800a8ecc:800a8f54(j
                                                                                          FUN_OVR_226__800a8ecc:800a8fec(c
                                                                                          FUN_OVR_226__800a8ecc:800a9014(c
                                                                                          FUN_OVR_226__800a8ecc:800a9080(c
     6::800a8e7c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a8e80 50 00 d4 27     addiu      s4,s8,0x50
     6::800a8e84 64 00 d5 27     addiu      s5,s8,0x64
     6::800a8e88 c7 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8e8c 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8e90()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8e90                           XREF[6]:     FUN_OVR_226__800a8ecc:800a8f5c(c
                                                                                          FUN_OVR_226__800a8ecc:800a8ffc(j
                                                                                          FUN_OVR_226__800a8ecc:800a900c(c
                                                                                          FUN_OVR_226__800a8ecc:800a903c(c
                                                                                          FUN_OVR_226__800a8ecc:800a905c(c
                                                                                          FUN_OVR_226__800a8ecc:800a9090(c
     6::800a8e90 50 00 d3 27     addiu      s3,s8,0x50
     6::800a8e94 14 00 d4 27     addiu      s4,s8,0x14
     6::800a8e98 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8e9c c2 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8ea0 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8ea4()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8ea4                           XREF[6]:     FUN_OVR_226__800a8ecc:800a8f84(c
                                                                                          FUN_OVR_226__800a8ecc:800a8fe4(c
                                                                                          FUN_OVR_226__800a8ecc:800a9024(j
                                                                                          FUN_OVR_226__800a8ecc:800a9034(c
                                                                                          FUN_OVR_226__800a8ecc:800a9064(c
                                                                                          FUN_OVR_226__800a8ecc:800a90a0(c
     6::800a8ea4 64 00 d3 27     addiu      s3,s8,0x64
     6::800a8ea8 78 00 d4 27     addiu      s4,s8,0x78
     6::800a8eac 28 00 d5 27     addiu      s5,s8,0x28
     6::800a8eb0 bd 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8eb4 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a8eb8                           XREF[4]:     OVR_226::800a8fd4(j), 
                                                                                          OVR_226::800a904c(j), 
                                                                                          OVR_226::800a9074(j), 
                                                                                          OVR_226::800a90b8(j)  
     6::800a8eb8 78 00 d3 27     addiu      s3,s8,0x78
     6::800a8ebc 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a8ec0 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a8ec4 b8 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8ec8 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a8ecc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a8ecc                           XREF[2]:     OVR_226::800a8f7c(c), 
                                                                                          OVR_226::800a9054(c)  
     6::800a8ecc 64 00 d3 27     addiu      s3,s8,0x64
     6::800a8ed0 00 00 d4 27     addiu      s4,s8,0x0
     6::800a8ed4 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8ed8 b3 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8edc 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a8ee0                           XREF[2]:     OVR_226::800a8f94(j), 
                                                                                          OVR_226::800a9004(c)  
     6::800a8ee0 14 00 d3 27     addiu      s3,s8,0x14
     6::800a8ee4 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a8ee8 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8eec ae 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8ef0 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a8ef4                           XREF[2]:     OVR_226::800a8f64(c), 
                                                                                          OVR_226::800a902c(c)  
     6::800a8ef4 28 00 d3 27     addiu      s3,s8,0x28
     6::800a8ef8 00 00 d4 27     addiu      s4,s8,0x0
     6::800a8efc 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8f00 a9 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8f04 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a8f08                           XREF[2]:     OVR_226::800a8f74(j), 
                                                                                          OVR_226::800a8fdc(c)  
     6::800a8f08 28 00 d3 27     addiu      s3,s8,0x28
     6::800a8f0c 78 00 d4 27     addiu      s4,s8,0x78
     6::800a8f10 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a8f14 a4 00 01 04     bgez       zero,FUN_OVR_226__800a91a8
     6::800a8f18 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a8f1c 50 00 d3 27     addiu      s3,s8,0x50
     6::800a8f20 14 00 d4 27     addiu      s4,s8,0x14
     6::800a8f24 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8f28 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a8f2c 6a a4 02 0c     jal        FUN_OVR_226__800a91a8                            undefined FUN_OVR_226__800a91a8()
     6::800a8f30 0c 00 0a 24     _li        t2,0xc
     6::800a8f34 64 00 d3 27     addiu      s3,s8,0x64
     6::800a8f38 78 00 d4 27     addiu      s4,s8,0x78
     6::800a8f3c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a8f40 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a8f44 6a a4 02 0c     jal        FUN_OVR_226__800a91a8                            undefined FUN_OVR_226__800a91a8()
     6::800a8f48 0c 00 0a 24     _li        t2,0xc
     6::800a8f4c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8f50 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8f54 c9 ff 01 04     bgez       zero,FUN_OVR_226__800a8e7c
     6::800a8f58 0c 00 0a 24     _li        t2,0xc
     6::800a8f5c a4 a3 02 0c     jal        FUN_OVR_226__800a8e90                            undefined FUN_OVR_226__800a8e90()
     6::800a8f60 0c 00 0a 24     _li        t2,0xc
     6::800a8f64 bd a3 02 0c     jal        SUB_OVR_226__800a8ef4
     6::800a8f68 0c 00 0a 24     _li        t2,0xc
     6::800a8f6c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8f70 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8f74 e4 ff 01 04     bgez       zero,SUB_OVR_226__800a8f08
     6::800a8f78 0c 00 0a 24     _li        t2,0xc
     6::800a8f7c b3 a3 02 0c     jal        FUN_OVR_226__800a8ecc                            undefined FUN_OVR_226__800a8ecc()
     6::800a8f80 0c 00 0a 24     _li        t2,0xc
     6::800a8f84 a9 a3 02 0c     jal        FUN_OVR_226__800a8ea4                            undefined FUN_OVR_226__800a8ea4()
     6::800a8f88 0c 00 0a 24     _li        t2,0xc
     6::800a8f8c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8f90 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8f94 d2 ff 01 04     bgez       zero,SUB_OVR_226__800a8ee0
     6::800a8f98 0c 00 0a 24     _li        t2,0xc
     6::800a8f9c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a8fa0 14 00 d4 27     addiu      s4,s8,0x14
     6::800a8fa4 78 00 d5 27     addiu      s5,s8,0x78
     6::800a8fa8 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a8fac 6a a4 02 0c     jal        FUN_OVR_226__800a91a8                            undefined FUN_OVR_226__800a91a8()
     6::800a8fb0 0c 00 0a 24     _li        t2,0xc
     6::800a8fb4 00 00 d3 27     addiu      s3,s8,0x0
     6::800a8fb8 78 00 d4 27     addiu      s4,s8,0x78
     6::800a8fbc 28 00 d5 27     addiu      s5,s8,0x28
     6::800a8fc0 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a8fc4 6a a4 02 0c     jal        FUN_OVR_226__800a91a8                            undefined FUN_OVR_226__800a91a8()
     6::800a8fc8 0c 00 0a 24     _li        t2,0xc
     6::800a8fcc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8fd0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8fd4 b8 ff 01 04     bgez       zero,LAB_OVR_226__800a8eb8
     6::800a8fd8 0c 00 0a 24     _li        t2,0xc
     6::800a8fdc c2 a3 02 0c     jal        SUB_OVR_226__800a8f08
     6::800a8fe0 0c 00 0a 24     _li        t2,0xc
     6::800a8fe4 a9 a3 02 0c     jal        FUN_OVR_226__800a8ea4                            undefined FUN_OVR_226__800a8ea4()
     6::800a8fe8 04 00 0a 24     _li        t2,0x4
     6::800a8fec 9f a3 02 0c     jal        FUN_OVR_226__800a8e7c                            undefined FUN_OVR_226__800a8e7c()
     6::800a8ff0 0c 00 0a 24     _li        t2,0xc
     6::800a8ff4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a8ff8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a8ffc a4 ff 01 04     bgez       zero,FUN_OVR_226__800a8e90
     6::800a9000 0c 00 0a 24     _li        t2,0xc
     6::800a9004 b8 a3 02 0c     jal        SUB_OVR_226__800a8ee0
     6::800a9008 0c 00 0a 24     _li        t2,0xc
     6::800a900c a4 a3 02 0c     jal        FUN_OVR_226__800a8e90                            undefined FUN_OVR_226__800a8e90()
     6::800a9010 04 00 0a 24     _li        t2,0x4
     6::800a9014 9f a3 02 0c     jal        FUN_OVR_226__800a8e7c                            undefined FUN_OVR_226__800a8e7c()
     6::800a9018 0c 00 0a 24     _li        t2,0xc
     6::800a901c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9020 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9024 9f ff 01 04     bgez       zero,FUN_OVR_226__800a8ea4
     6::800a9028 0c 00 0a 24     _li        t2,0xc
     6::800a902c bd a3 02 0c     jal        SUB_OVR_226__800a8ef4
     6::800a9030 0c 00 0a 24     _li        t2,0xc
     6::800a9034 a9 a3 02 0c     jal        FUN_OVR_226__800a8ea4                            undefined FUN_OVR_226__800a8ea4()
     6::800a9038 08 00 0a 24     _li        t2,0x8
     6::800a903c a4 a3 02 0c     jal        FUN_OVR_226__800a8e90                            undefined FUN_OVR_226__800a8e90()
     6::800a9040 0c 00 0a 24     _li        t2,0xc
     6::800a9044 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9048 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a904c 9a ff 01 04     bgez       zero,LAB_OVR_226__800a8eb8
     6::800a9050 0c 00 0a 24     _li        t2,0xc
     6::800a9054 b3 a3 02 0c     jal        FUN_OVR_226__800a8ecc                            undefined FUN_OVR_226__800a8ecc()
     6::800a9058 0c 00 0a 24     _li        t2,0xc
     6::800a905c a4 a3 02 0c     jal        FUN_OVR_226__800a8e90                            undefined FUN_OVR_226__800a8e90()
     6::800a9060 08 00 0a 24     _li        t2,0x8
     6::800a9064 a9 a3 02 0c     jal        FUN_OVR_226__800a8ea4                            undefined FUN_OVR_226__800a8ea4()
     6::800a9068 0c 00 0a 24     _li        t2,0xc
     6::800a906c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9070 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9074 90 ff 01 04     bgez       zero,LAB_OVR_226__800a8eb8
     6::800a9078 0c 00 0a 24     _li        t2,0xc
     6::800a907c b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a9080 9f a3 02 0c     jal        FUN_OVR_226__800a8e7c                            undefined FUN_OVR_226__800a8e7c()
     6::800a9084 0c 00 0a 24     _li        t2,0xc
     6::800a9088 0c 00 03 24     li         v1,0xc
     6::800a908c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a9090 a4 a3 02 0c     jal        FUN_OVR_226__800a8e90                            undefined FUN_OVR_226__800a8e90()
     6::800a9094 0c 00 0a 24     _li        t2,0xc
     6::800a9098 30 00 03 24     li         v1,0x30
     6::800a909c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a90a0 a9 a3 02 0c     jal        FUN_OVR_226__800a8ea4                            undefined FUN_OVR_226__800a8ea4()
     6::800a90a4 0c 00 0a 24     _li        t2,0xc
     6::800a90a8 3c 00 03 24     li         v1,0x3c
     6::800a90ac b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a90b0 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a90b4 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a90b8 7f ff 01 04     bgez       zero,LAB_OVR_226__800a8eb8
     6::800a90bc 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a90c0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a90c0                           XREF[5]:     FUN_OVR_226__800a9288:800a951c(c
                                                                                          FUN_OVR_226__800a9288:800a9530(c
                                                                                          FUN_OVR_226__800a9288:800a9544(c
                                                                                          FUN_OVR_226__800a9288:800a9558(c
                                                                                          FUN_OVR_226__800a9288:800a956c(c
     6::800a90c0 00 00 ab 85     lh         t3,0x0(t5)
     6::800a90c4 00 00 cc 85     lh         t4,0x0(t6)
     6::800a90c8 00 00 eb a5     sh         t3,0x0(t7)
     6::800a90cc 21 18 6c 01     addu       v1,t3,t4
     6::800a90d0 43 18 03 00     sra        v1,v1,0x1
     6::800a90d4 00 00 03 a6     sh         v1,0x0(s0)
     6::800a90d8 02 00 ab 85     lh         t3,0x2(t5)
     6::800a90dc 02 00 cc 85     lh         t4,0x2(t6)
     6::800a90e0 02 00 eb a5     sh         t3,0x2(t7)
     6::800a90e4 21 18 6c 01     addu       v1,t3,t4
     6::800a90e8 43 18 03 00     sra        v1,v1,0x1
     6::800a90ec 02 00 03 a6     sh         v1,0x2(s0)
     6::800a90f0 04 00 ab 85     lh         t3,0x4(t5)
     6::800a90f4 04 00 cc 85     lh         t4,0x4(t6)
     6::800a90f8 04 00 eb a5     sh         t3,0x4(t7)
     6::800a90fc 21 18 6c 01     addu       v1,t3,t4
     6::800a9100 43 18 03 00     sra        v1,v1,0x1
     6::800a9104 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a9108 00 08 83 48     gte_ldVZ0  v1
     6::800a910c 04 00 03 a6     sh         v1,0x4(s0)
     6::800a9110 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a9114 01 00 18 4a     RTPS
     6::800a9118 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a911c 08 00 eb a1     sb         t3,0x8(t7)
     6::800a9120 21 18 6c 01     addu       v1,t3,t4
     6::800a9124 43 18 03 00     sra        v1,v1,0x1
     6::800a9128 08 00 03 a2     sb         v1,0x8(s0)
     6::800a912c 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a9130 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a9134 09 00 eb a1     sb         t3,0x9(t7)
     6::800a9138 21 18 6c 01     addu       v1,t3,t4
     6::800a913c 43 18 03 00     sra        v1,v1,0x1
     6::800a9140 09 00 03 a2     sb         v1,0x9(s0)
     6::800a9144 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a9148 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a914c 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a9150 21 18 6c 01     addu       v1,t3,t4
     6::800a9154 43 18 03 00     sra        v1,v1,0x1
     6::800a9158 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a915c 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a9160 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a9164 06 00 eb a1     sb         t3,0x6(t7)
     6::800a9168 21 18 6c 01     addu       v1,t3,t4
     6::800a916c 43 18 03 00     sra        v1,v1,0x1
     6::800a9170 06 00 03 a2     sb         v1,0x6(s0)
     6::800a9174 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a9178 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a917c 07 00 eb a1     sb         t3,0x7(t7)
     6::800a9180 21 18 6c 01     addu       v1,t3,t4
     6::800a9184 43 18 03 00     sra        v1,v1,0x1
     6::800a9188 07 00 03 a2     sb         v1,0x7(s0)
     6::800a918c 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a9190 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a9194 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a9198 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a919c 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a91a0 08 00 e0 03     jr         ra
     6::800a91a4 10 00 13 ea     _gte_stSZ3 0x10(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a91a8()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a91a8                           XREF[12]:    FUN_OVR_226__800a8e7c:800a8e88(j
                                                                                          FUN_OVR_226__800a8e90:800a8e9c(j
                                                                                          FUN_OVR_226__800a8ea4:800a8eb0(j
                                                                                          FUN_OVR_226__800a8ecc:800a8ec4(j
                                                                                          FUN_OVR_226__800a8ecc:800a8ed8(j
                                                                                          FUN_OVR_226__800a8ecc:800a8eec(j
                                                                                          FUN_OVR_226__800a8ecc:800a8f00(j
                                                                                          FUN_OVR_226__800a8ecc:800a8f14(j
                                                                                          FUN_OVR_226__800a8ecc:800a8f2c(c
                                                                                          FUN_OVR_226__800a8ecc:800a8f44(c
                                                                                          FUN_OVR_226__800a8ecc:800a8fac(c
                                                                                          FUN_OVR_226__800a8ecc:800a8fc4(c
     6::800a91a8 70 00 2a ac     sw         t2,0x70(at)
     6::800a91ac 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a91b0 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a91b4 94 01 2a 8c     lw         t2,0x194(at)
     6::800a91b8 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a91bc 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a91c0 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a91c4 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a91c8 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a91cc 06 00 40 4b     NCLIP
     6::800a91d0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a91d4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a91d8 23 78 68 01     subu       t7,t3,t0
     6::800a91dc 23 80 88 01     subu       s0,t4,t0
     6::800a91e0 23 88 a8 01     subu       s1,t5,t0
     6::800a91e4 23 90 c8 01     subu       s2,t6,t0
     6::800a91e8 00 c0 08 48     gte_stMAC0 t0
     6::800a91ec 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a91f0 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a91fc
     6::800a91f4 22 40 08 00     _sub       t0,zero,t0
     6::800a91f8 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a91fc                           XREF[1]:     OVR_226::800a91f0(j)  
     6::800a91fc 06 00 40 4b     NCLIP
     6::800a9200 24 18 6c 01     and        v1,t3,t4
     6::800a9204 24 18 6d 00     and        v1,v1,t5
     6::800a9208 24 18 6e 00     and        v1,v1,t6
     6::800a920c 25 78 f0 01     or         t7,t7,s0
     6::800a9210 25 78 f1 01     or         t7,t7,s1
     6::800a9214 27 78 f2 01     nor        t7,t7,s2
     6::800a9218 25 78 e3 01     or         t7,t7,v1
     6::800a921c 15 ff e0 05     bltz       t7,LAB_OVR_226__800a8e74
     6::800a9220 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a9224 13 ff e0 05     bltz       t7,LAB_OVR_226__800a8e74
     6::800a9228 00 c0 03 48     _gte_stM   v1
     6::800a922c 25 40 09 01     or         t0,t0,t1
     6::800a9230 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a923c
     6::800a9234 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a9238 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a923c                           XREF[1]:     OVR_226::800a9230(j)  
     6::800a923c 80 40 08 00     sll        t0,t0,0x2
     6::800a9240 25 18 69 00     or         v1,v1,t1
     6::800a9244 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a9248 c0 18 03 00     sll        v1,v1,0x3
     6::800a924c 70 00 2a 8c     lw         t2,0x70(at)
     6::800a9250 25 18 68 00     or         v1,v1,t0
     6::800a9254 24 18 6a 00     and        v1,v1,t2
     6::800a9258 06 ff 60 10     beq        v1,zero,LAB_OVR_226__800a8e74
     6::800a925c 70 00 23 ac     _sw        v1,0x70(at)
     6::800a9260 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a9264 24 03 28 24     addiu      t0,at,0x324
     6::800a9268 d5 00 1e 11     beq        t0,s8,LAB_OVR_226__800a95c0
     6::800a926c 04 00 39 27     _addiu     t9,t9,0x4
     6::800a9270 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a9274 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a9278 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a927c 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a9280 91 00 01 04     bgez       zero,LAB_OVR_226__800a94c8
     6::800a9284 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9288()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9288                           XREF[4]:     OVR_226::800a8dec(c), 
                                                                                          OVR_226::800a8e00(c), 
                                                                                          OVR_226::800a8e14(c), 
                                                                                          OVR_226::800a8e28(c)  
     6::800a9288 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a928c b4 00 ca af     sw         t2,0xb4(s8)
     6::800a9290 06 50 09 01     srlv       t2,t1,t0
     6::800a9294 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a9298 80 50 0a 00     sll        t2,t2,0x2
     6::800a929c 21 50 41 01     addu       t2,t2,at
     6::800a92a0 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a92a4 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a92a8 94 01 2a ac     sw         t2,0x194(at)
     6::800a92ac 02 9e 0a 00     srl        s3,t2,0x18
     6::800a92b0 1f 00 73 32     andi       s3,s3,0x1f
     6::800a92b4 06 98 63 02     srlv       s3,v1,s3
     6::800a92b8 ff 00 73 32     andi       s3,s3,0xff
     6::800a92bc 21 98 7e 02     addu       s3,s3,s8
     6::800a92c0 02 a4 0a 00     srl        s4,t2,0x10
     6::800a92c4 1f 00 94 32     andi       s4,s4,0x1f
     6::800a92c8 06 a0 83 02     srlv       s4,v1,s4
     6::800a92cc ff 00 94 32     andi       s4,s4,0xff
     6::800a92d0 21 a0 9e 02     addu       s4,s4,s8
     6::800a92d4 02 aa 0a 00     srl        s5,t2,0x8
     6::800a92d8 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a92dc 06 a8 a3 02     srlv       s5,v1,s5
     6::800a92e0 ff 00 b5 32     andi       s5,s5,0xff
     6::800a92e4 21 a8 be 02     addu       s5,s5,s8
     6::800a92e8 1f 00 56 31     andi       s6,t2,0x1f
     6::800a92ec 06 b0 c3 02     srlv       s6,v1,s6
     6::800a92f0 ff 00 d6 32     andi       s6,s6,0xff
     6::800a92f4 21 b0 de 02     addu       s6,s6,s8
     6::800a92f8 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a92fc 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a9300 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a9304 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a9308 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a930c 06 00 40 4b     NCLIP
     6::800a9310 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a9314 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a9318 23 78 68 01     subu       t7,t3,t0
     6::800a931c 23 80 88 01     subu       s0,t4,t0
     6::800a9320 23 88 a8 01     subu       s1,t5,t0
     6::800a9324 23 90 c8 01     subu       s2,t6,t0
     6::800a9328 00 c0 08 48     gte_stMAC0 t0
     6::800a932c 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a9330 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a933c
     6::800a9334 22 40 08 00     _sub       t0,zero,t0
     6::800a9338 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a933c                           XREF[1]:     OVR_226::800a9330(j)  
     6::800a933c 06 00 40 4b     NCLIP
     6::800a9340 24 18 6c 01     and        v1,t3,t4
     6::800a9344 24 18 6d 00     and        v1,v1,t5
     6::800a9348 24 18 6e 00     and        v1,v1,t6
     6::800a934c 25 78 f0 01     or         t7,t7,s0
     6::800a9350 25 78 f1 01     or         t7,t7,s1
     6::800a9354 27 78 f2 01     nor        t7,t7,s2
     6::800a9358 25 78 e3 01     or         t7,t7,v1
     6::800a935c c5 fe e0 05     bltz       t7,LAB_OVR_226__800a8e74
     6::800a9360 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a9364 c3 fe e0 05     bltz       t7,LAB_OVR_226__800a8e74
     6::800a9368 00 c0 03 48     _gte_stM   v1
     6::800a936c 25 40 09 01     or         t0,t0,t1
     6::800a9370 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a937c
     6::800a9374 c2 47 08 00     _srl       t0,t0,0x1f
     6::800a9378 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a937c                           XREF[1]:     OVR_226::800a9370(j)  
     6::800a937c 80 40 08 00     sll        t0,t0,0x2
     6::800a9380 25 18 69 00     or         v1,v1,t1
     6::800a9384 c2 1f 03 00     srl        v1,v1,0x1f
     6::800a9388 c0 18 03 00     sll        v1,v1,0x3
     6::800a938c 25 18 68 00     or         v1,v1,t0
     6::800a9390 b8 fe 60 10     beq        v1,zero,LAB_OVR_226__800a8e74
     6::800a9394 70 00 23 ac     _sw        v1,0x70(at)
     6::800a9398 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a939c 04 00 39 27     addiu      t9,t9,0x4
     6::800a93a0 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a93a4 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a93a8 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a93ac 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a93b0 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800a93b4 23 50 6c 01     subu       t2,t3,t4
     6::800a93b8 82 48 03 00     srl        t1,v1,0x2
     6::800a93bc 21 48 38 01     addu       t1,t1,t8
     6::800a93c0 18 00 29 81     lb         t1,0x18(t1)
     6::800a93c4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a93d0
     6::800a93c8 21 e0 60 01     _move      gp,t3
     6::800a93cc 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800a93d0                           XREF[1]:     OVR_226::800a93c4(j)  
     6::800a93d0 23 50 8d 03     subu       t2,gp,t5
     6::800a93d4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a93e0
     6::800a93d8 21 18 78 00     _addu      v1,v1,t8
     6::800a93dc 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800a93e0                           XREF[1]:     OVR_226::800a93d4(j)  
     6::800a93e0 23 50 8e 03     subu       t2,gp,t6
     6::800a93e4 02 00 40 1d     bgtz       t2,LAB_OVR_226__800a93f0
     6::800a93e8 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800a93ec 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800a93f0                           XREF[1]:     OVR_226::800a93e4(j)  
     6::800a93f0 21 50 80 03     move       t2,gp
     6::800a93f4 82 e1 1c 00     srl        gp,gp,0x6
     6::800a93f8 21 e0 89 03     addu       gp,gp,t1
     6::800a93fc 01 00 69 30     andi       t1,v1,0x1
     6::800a9400 02 00 20 11     beq        t1,zero,LAB_OVR_226__800a940c
     6::800a9404 80 e0 1c 00     _sll       gp,gp,0x2
     6::800a9408 ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800a940c                           XREF[1]:     OVR_226::800a9400(j)  
     6::800a940c 02 00 81 07     bgez       gp,LAB_OVR_226__800a9418
     6::800a9410 21 e0 85 03     _addu      gp,gp,a1
     6::800a9414 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800a9418                           XREF[1]:     OVR_226::800a940c(j)  
     6::800a9418 1c 00 28 8c     lw         t0,0x1c(at)
     6::800a941c 24 00 69 8c     lw         t1,0x24(v1)
     6::800a9420 23 40 48 01     subu       t0,t2,t0
     6::800a9424 84 00 29 ac     sw         t1,0x84(at)
     6::800a9428 0c 00 01 05     bgez       t0,LAB_OVR_226__800a945c
     6::800a942c 20 00 28 8c     _lw        t0,0x20(at)
     6::800a9430 0c 00 63 24     addiu      v1,v1,0xc
     6::800a9434 23 40 48 01     subu       t0,t2,t0
     6::800a9438 08 00 01 05     bgez       t0,LAB_OVR_226__800a945c
     6::800a943c 24 00 28 8c     _lw        t0,0x24(at)
     6::800a9440 0c 00 63 24     addiu      v1,v1,0xc
     6::800a9444 23 40 48 01     subu       t0,t2,t0
     6::800a9448 04 00 01 05     bgez       t0,LAB_OVR_226__800a945c
     6::800a944c 00 00 00 00     _nop
     6::800a9450 02 00 20 05     bltz       t1,LAB_OVR_226__800a945c
     6::800a9454 00 00 00 00     _nop
     6::800a9458 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800a945c                           XREF[4]:     OVR_226::800a9428(j), 
                                                                                          OVR_226::800a9438(j), 
                                                                                          OVR_226::800a9448(j), 
                                                                                          OVR_226::800a9450(j)  
     6::800a945c 94 01 2a 8c     lw         t2,0x194(at)
     6::800a9460 00 00 68 8c     lw         t0,0x0(v1)
     6::800a9464 04 00 69 8c     lw         t1,0x4(v1)
     6::800a9468 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a946c ac 01 28 ac     sw         t0,0x1ac(at)
     6::800a9470 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a9474 00 52 0a 00     sll        t2,t2,0x8
     6::800a9478 0a 00 40 05     bltz       t2,LAB_OVR_226__800a94a4
     6::800a947c b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800a9480 06 00 68 a6     sh         t0,0x6(s3)
     6::800a9484 08 00 68 8c     lw         t0,0x8(v1)
     6::800a9488 06 00 89 a6     sh         t1,0x6(s4)
     6::800a948c 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a9490 00 54 0a 00     sll        t2,t2,0x10
     6::800a9494 0b 00 40 05     bltz       t2,LAB_OVR_226__800a94c4
     6::800a9498 02 4c 08 00     _srl       t1,t0,0x10
     6::800a949c 09 00 01 04     bgez       zero,LAB_OVR_226__800a94c4
     6::800a94a0 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800a94a4                           XREF[1]:     OVR_226::800a9478(j)  
     6::800a94a4 06 00 69 a6     sh         t1,0x6(s3)
     6::800a94a8 08 00 69 8c     lw         t1,0x8(v1)
     6::800a94ac 00 54 0a 00     sll        t2,t2,0x10
     6::800a94b0 06 00 88 a6     sh         t0,0x6(s4)
     6::800a94b4 02 44 09 00     srl        t0,t1,0x10
     6::800a94b8 02 00 40 05     bltz       t2,LAB_OVR_226__800a94c4
     6::800a94bc 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800a94c0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a94c4                           XREF[3]:     OVR_226::800a9494(j), 
                                                                                          OVR_226::800a949c(j), 
                                                                                          OVR_226::800a94b8(j)  
     6::800a94c4 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800a94c8                           XREF[1]:     FUN_OVR_226__800a91a8:800a9280(j
     6::800a94c8 00 00 00 00     nop
     6::800a94cc 23 88 63 01     subu       s1,t3,v1
     6::800a94d0 23 90 83 01     subu       s2,t4,v1
     6::800a94d4 23 78 a3 01     subu       t7,t5,v1
     6::800a94d8 23 80 c3 01     subu       s0,t6,v1
     6::800a94dc 42 8f 11 00     srl        s1,s1,0x1d
     6::800a94e0 04 00 31 32     andi       s1,s1,0x4
     6::800a94e4 02 97 12 00     srl        s2,s2,0x1c
     6::800a94e8 08 00 52 32     andi       s2,s2,0x8
     6::800a94ec 25 88 32 02     or         s1,s1,s2
     6::800a94f0 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800a94f4 10 00 ef 31     andi       t7,t7,0x10
     6::800a94f8 25 88 2f 02     or         s1,s1,t7
     6::800a94fc 82 86 10 00     srl        s0,s0,0x1a
     6::800a9500 20 00 10 32     andi       s0,s0,0x20
     6::800a9504 25 88 30 02     or         s1,s1,s0
     6::800a9508 26 00 20 12     beq        s1,zero,LAB_OVR_226__800a95a4
     6::800a950c 21 68 60 02     _move      t5,s3
     6::800a9510 21 70 80 02     move       t6,s4
     6::800a9514 b8 00 de 27     addiu      s8,s8,0xb8
     6::800a9518 00 00 cf 27     addiu      t7,s8,0x0
     6::800a951c 30 a4 02 0c     jal        FUN_OVR_226__800a90c0                            undefined FUN_OVR_226__800a90c0()
     6::800a9520 50 00 d0 27     _addiu     s0,s8,0x50
     6::800a9524 21 68 80 02     move       t5,s4
     6::800a9528 21 70 c0 02     move       t6,s6
     6::800a952c 14 00 cf 27     addiu      t7,s8,0x14
     6::800a9530 30 a4 02 0c     jal        FUN_OVR_226__800a90c0                            undefined FUN_OVR_226__800a90c0()
     6::800a9534 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800a9538 21 68 a0 02     move       t5,s5
     6::800a953c 21 70 60 02     move       t6,s3
     6::800a9540 28 00 cf 27     addiu      t7,s8,0x28
     6::800a9544 30 a4 02 0c     jal        FUN_OVR_226__800a90c0                            undefined FUN_OVR_226__800a90c0()
     6::800a9548 64 00 d0 27     _addiu     s0,s8,0x64
     6::800a954c 21 68 c0 02     move       t5,s6
     6::800a9550 21 70 a0 02     move       t6,s5
     6::800a9554 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800a9558 30 a4 02 0c     jal        FUN_OVR_226__800a90c0                            undefined FUN_OVR_226__800a90c0()
     6::800a955c a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800a9560 50 00 cd 27     addiu      t5,s8,0x50
     6::800a9564 a0 00 ce 27     addiu      t6,s8,0xa0
     6::800a9568 50 00 cf 27     addiu      t7,s8,0x50
     6::800a956c 30 a4 02 0c     jal        FUN_OVR_226__800a90c0                            undefined FUN_OVR_226__800a90c0()
     6::800a9570 78 00 d0 27     _addiu     s0,s8,0x78
     6::800a9574 21 18 21 02     addu       v1,s1,at
     6::800a9578 48 01 63 8c     lw         v1,0x148(v1)
     6::800a957c 0b 80 08 3c     lui        t0,0x800b
     6::800a9580 94 95 08 25     addiu      t0,t0,-0x6a6c
     6::800a9584 9c 00 23 ac     sw         v1,0x9c(at)
     6::800a9588 3c 00 28 af     sw         t0=>LAB_OVR_226__800a9594,0x3c(t9)
     6::800a958c 08 00 60 00     jr         v1
     6::800a9590 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800a9594                           XREF[1]:     FUN_OVR_226__800a9288:800a9588(*
     6::800a9594 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9598 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a959c 08 00 e0 03     jr         ra
     6::800a95a0 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800a95a4                           XREF[1]:     OVR_226::800a9508(j)  
     6::800a95a4 70 00 23 8c     lw         v1,0x70(at)
     6::800a95a8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a95ac 21 18 61 00     addu       v1,v1,at
     6::800a95b0 84 01 63 8c     lw         v1,0x184(v1)
     6::800a95b4 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a95b8 08 00 60 00     jr         v1
     6::800a95bc 00 00 00 00     _nop
                             LAB_OVR_226__800a95c0                           XREF[1]:     OVR_226::800a9268(j)  
     6::800a95c0 84 00 23 8c     lw         v1,0x84(at)
     6::800a95c4 24 03 2a 24     addiu      t2,at,0x324
     6::800a95c8 26 00 60 1c     bgtz       v1,LAB_OVR_226__800a9664
     6::800a95cc 20 03 28 8c     _lw        t0,0x320(at)
     6::800a95d0 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800a95d4 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800a9630
     6::800a95d8 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800a95dc 0b 80 0a 3c     lui        t2,0x800b
     6::800a95e0 7c 90 4a 25     addiu      t2,t2,-0x6f84
     6::800a95e4 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800a9664
     6::800a95e8 94 01 23 8c     _lw        v1,0x194(at)
     6::800a95ec 40 40 08 00     sll        t0,t0,0x1
     6::800a95f0 00 1a 03 00     sll        v1,v1,0x8
     6::800a95f4 02 00 61 04     bgez       v1,LAB_OVR_226__800a9600
     6::800a95f8 84 00 2a 8c     _lw        t2,0x84(at)
     6::800a95fc c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_226__800a9600                           XREF[1]:     OVR_226::800a95f4(j)  
     6::800a9600 21 40 09 01     addu       t0,t0,t1
     6::800a9604 21 50 48 01     addu       t2,t2,t0
     6::800a9608 00 00 48 8d     lw         t0,0x0(t2)
     6::800a960c 04 00 49 8d     lw         t1,0x4(t2)
     6::800a9610 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a9614 06 00 68 a6     sh         t0,0x6(s3)
     6::800a9618 08 00 48 85     lh         t0,0x8(t2)
     6::800a961c a4 01 29 ac     sw         t1,0x1a4(at)
     6::800a9620 06 00 89 a6     sh         t1,0x6(s4)
     6::800a9624 0a 00 49 85     lh         t1,0xa(t2)
     6::800a9628 06 00 a8 a6     sh         t0,0x6(s5)
     6::800a962c 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800a9630                           XREF[2]:     OVR_226::800a95d4(j), 
                                                                                          OVR_226::800a9670(j)  
     6::800a9630 70 00 23 8c     lw         v1,0x70(at)
     6::800a9634 00 00 00 00     nop
     6::800a9638 21 18 61 00     addu       v1,v1,at
     6::800a963c 84 01 63 8c     lw         v1,0x184(v1)
     6::800a9640 00 00 00 00     nop
     6::800a9644 09 f8 60 00     jalr       v1
     6::800a9648 fc ff 39 27     _addiu     t9,t9,-0x4
     6::800a964c 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800a9650 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a9654 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a9658 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a965c 08 00 e0 03     jr         ra
     6::800a9660 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800a9664                           XREF[2]:     OVR_226::800a95c8(j), 
                                                                                          OVR_226::800a95e4(j)  
     6::800a9664 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800a9668 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800a966c a0 01 28 ac     sw         t0,0x1a0(at)
     6::800a9670 ef ff 01 04     bgez       zero,LAB_OVR_226__800a9630
     6::800a9674 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800a9678 21 98 80 02     move       s3,s4
     6::800a967c 21 a0 c0 02     move       s4,s6
     6::800a9680 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a9684 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a9688 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a968c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a9690 08 00 90 8e     lw         s0,0x8(s4)
     6::800a9694 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a9698 06 00 73 86     lh         s3,0x6(s3)
     6::800a969c 06 00 94 86     lh         s4,0x6(s4)
     6::800a96a0 06 00 b5 86     lh         s5,0x6(s5)
     6::800a96a4 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a96a8 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a96ac a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a96b0 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a96b4 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a96b8 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a96bc 60 00 03 3c     lui        v1,0x60
     6::800a96c0 24 48 83 02     and        t1,s4,v1
     6::800a96c4 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a96d0
     6::800a96c8 00 36 03 3c     _lui       v1,0x3600
     6::800a96cc 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800a96d0                           XREF[1]:     OVR_226::800a96c4(j)  
     6::800a96d0 25 18 6f 00     or         v1,v1,t7
     6::800a96d4 04 00 43 ac     sw         v1,0x4(v0)
     6::800a96d8 08 00 4b ac     sw         t3,0x8(v0)
     6::800a96dc 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a96e0 10 00 50 ac     sw         s0,0x10(v0)
     6::800a96e4 14 00 4c ac     sw         t4,0x14(v0)
     6::800a96e8 18 00 54 ac     sw         s4,0x18(v0)
     6::800a96ec 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a96f0 20 00 4d ac     sw         t5,0x20(v0)
     6::800a96f4 24 00 55 ac     sw         s5,0x24(v0)
     6::800a96f8 28 00 09 24     li         t1,0x28
     6::800a96fc 29 00 01 04     bgez       zero,LAB_OVR_226__800a97a4
     6::800a9700 00 09 0a 3c     _lui       t2,0x900
     6::800a9704 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a9708 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a970c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a9710 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a9714 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a9718 08 00 90 8e     lw         s0,0x8(s4)
     6::800a971c 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a9720 08 00 d2 8e     lw         s2,0x8(s6)
     6::800a9724 06 00 73 86     lh         s3,0x6(s3)
     6::800a9728 06 00 94 86     lh         s4,0x6(s4)
     6::800a972c 06 00 b5 86     lh         s5,0x6(s5)
     6::800a9730 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800a9734 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800a9738 06 00 d4 86     lh         s4,0x6(s6)
     6::800a973c a8 01 35 a4     sh         s5,0x1a8(at)
     6::800a9740 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800a9744 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800a9748 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800a974c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800a9750 60 00 03 3c     lui        v1,0x60
     6::800a9754 24 48 83 02     and        t1,s4,v1
     6::800a9758 02 00 23 15     bne        t1,v1,LAB_OVR_226__800a9764
     6::800a975c 00 3e 03 3c     _lui       v1,0x3e00
     6::800a9760 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800a9764                           XREF[1]:     OVR_226::800a9758(j)  
     6::800a9764 25 18 6f 00     or         v1,v1,t7
     6::800a9768 04 00 43 ac     sw         v1,0x4(v0)
     6::800a976c 08 00 4b ac     sw         t3,0x8(v0)
     6::800a9770 0c 00 53 ac     sw         s3,0xc(v0)
     6::800a9774 10 00 50 ac     sw         s0,0x10(v0)
     6::800a9778 14 00 4c ac     sw         t4,0x14(v0)
     6::800a977c 18 00 54 ac     sw         s4,0x18(v0)
     6::800a9780 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800a9784 20 00 4d ac     sw         t5,0x20(v0)
     6::800a9788 24 00 55 ac     sw         s5,0x24(v0)
     6::800a978c 28 00 52 ac     sw         s2,0x28(v0)
     6::800a9790 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800a9794 02 1c 15 00     srl        v1,s5,0x10
     6::800a9798 30 00 43 ac     sw         v1,0x30(v0)
     6::800a979c 34 00 09 24     li         t1,0x34
     6::800a97a0 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800a97a4                           XREF[1]:     OVR_226::800a96fc(j)  
     6::800a97a4 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800a97a8 00 42 02 00     sll        t0,v0,0x8
     6::800a97ac 02 42 08 00     srl        t0,t0,0x8
     6::800a97b0 25 18 6a 00     or         v1,v1,t2
     6::800a97b4 00 00 43 ac     sw         v1,0x0(v0)
     6::800a97b8 21 10 49 00     addu       v0,v0,t1
     6::800a97bc 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800a97c0 08 00 e0 03     jr         ra
     6::800a97c4 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800a97c8                           XREF[1]:     OVR_226::800ab438(*)  
     6::800a97c8 00 00 98 8c     lw         t8,0x0(a0)
                             LAB_OVR_226__800a97cc                           XREF[1]:     OVR_226::800a9b1c(j)  
     6::800a97cc 30 00 23 8c     lw         v1,0x30(at)
     6::800a97d0 00 1a 48 24     addiu      t0,v0,0x1a00
     6::800a97d4 23 18 68 00     subu       v1,v1,t0
     6::800a97d8 b6 dd 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800a97dc b4 01 3e 24     _addiu     s8,at,0x1b4
     6::800a97e0 a9 dd 00 13     beq        t8,zero,LAB_OVR_226__800a0e88
     6::800a97e4 b4 00 c0 af     _sw        zero,0xb4(s8)
     6::800a97e8 00 00 14 8f     lw         s4,0x0(t8)
     6::800a97ec 04 00 16 8f     lw         s6,0x4(t8)
     6::800a97f0 ff ff 93 32     andi       s3,s4,0xffff
     6::800a97f4 00 99 13 00     sll        s3,s3,0x4
     6::800a97f8 21 98 77 02     addu       s3,s3,s7
     6::800a97fc 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a9804 02 a4 14 00     srl        s4,s4,0x10
     6::800a9808 00 a1 14 00     sll        s4,s4,0x4
     6::800a980c 21 a0 97 02     addu       s4,s4,s7
     6::800a9810 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a9818 ff ff d5 32     andi       s5,s6,0xffff
     6::800a981c 00 a9 15 00     sll        s5,s5,0x4
     6::800a9820 21 a8 b7 02     addu       s5,s5,s7
     6::800a9824 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a982c 02 b4 16 00     srl        s6,s6,0x10
     6::800a9830 00 b1 16 00     sll        s6,s6,0x4
     6::800a9834 30 00 28 4a     RTPT
     6::800a9838 21 b0 d7 02     addu       s6,s6,s7
     6::800a983c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a9840 08 00 90 8e     lw         s0,0x8(s4)
     6::800a9844 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a9848 08 00 cf af     sw         t7,0x8(s8)
     6::800a984c 1c 00 d0 af     sw         s0,0x1c(s8)
     6::800a9850 30 00 d1 af     sw         s1,0x30(s8)
     6::800a9854 08 00 14 8f     lw         s4,0x8(t8)
     6::800a9858 0c 00 cc eb     gte_stSXY0 0xc(s8)
     6::800a985c 20 00 cd eb     gte_stSXY1 0x20(s8)
     6::800a9860 34 00 ce eb     gte_stSXY2 0x34(s8)
     6::800a9864 00 00 c0 eb     sVXY0      0x0(s8)
     6::800a9868 04 00 c1 eb     gte_stVZ0  0x4(s8)
     6::800a986c 14 00 c2 eb     gte_stVXY1 0x14(s8)
     6::800a9870 18 00 c3 eb     gte_stVZ1  0x18(s8)
     6::800a9874 28 00 c4 eb     gte_stVXY2 0x28(s8)
     6::800a9878 2c 00 c5 eb     gte_stVZ2  0x2c(s8)
     6::800a987c 5c 00 2a 8c     lw         t2,0x5c(at)
     6::800a9880 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a988c 10 00 c3 a7     sh         v1,0x10(s8)
     6::800a9890 24 00 c8 a7     sh         t0,0x24(s8)
     6::800a9894 38 00 c9 a7     sh         t1,0x38(s8)
     6::800a9898 23 58 6a 00     subu       t3,v1,t2
     6::800a989c 23 60 0a 01     subu       t4,t0,t2
     6::800a98a0 23 68 2a 01     subu       t5,t1,t2
     6::800a98a4 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a98a8 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a98ac c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a98b0 12 00 cb a3     sb         t3,0x12(s8)
     6::800a98b4 26 00 cc a3     sb         t4,0x26(s8)
     6::800a98b8 3a 00 cd a3     sb         t5,0x3a(s8)
     6::800a98bc 40 18 03 00     sll        v1,v1,0x1
     6::800a98c0 40 40 08 00     sll        t0,t0,0x1
     6::800a98c4 40 48 09 00     sll        t1,t1,0x1
     6::800a98c8 23 58 6a 00     subu       t3,v1,t2
     6::800a98cc 23 60 0a 01     subu       t4,t0,t2
     6::800a98d0 23 68 2a 01     subu       t5,t1,t2
     6::800a98d4 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a98d8 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a98dc c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a98e0 13 00 cb a3     sb         t3,0x13(s8)
     6::800a98e4 27 00 cc a3     sb         t4,0x27(s8)
     6::800a98e8 3b 00 cd a3     sb         t5,0x3b(s8)
     6::800a98ec 00 00 c0        ldv0       s6                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 c1 ca
     6::800a98f4 ff ff 93 32     andi       s3,s4,0xffff
     6::800a98f8 00 99 13 00     sll        s3,s3,0x4
     6::800a98fc 21 98 77 02     addu       s3,s3,s7
     6::800a9900 00 00 62        ldv1       s3                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 63 ca
     6::800a9908 02 a4 14 00     srl        s4,s4,0x10
     6::800a990c 00 a1 14 00     sll        s4,s4,0x4
     6::800a9910 21 a0 97 02     addu       s4,s4,s7
     6::800a9914 00 00 84        ldv2       s4                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 85 ca
     6::800a991c 21 c8 20 00     move       t9,at
     6::800a9920 00 00 00 00     nop
     6::800a9924 30 00 28 4a     RTPT
     6::800a9928 08 00 cf 8e     lw         t7,0x8(s6)
     6::800a992c 08 00 70 8e     lw         s0,0x8(s3)
     6::800a9930 08 00 91 8e     lw         s1,0x8(s4)
     6::800a9934 44 00 cf af     sw         t7,0x44(s8)
     6::800a9938 58 00 d0 af     sw         s0,0x58(s8)
     6::800a993c 6c 00 d1 af     sw         s1,0x6c(s8)
     6::800a9940 0c 00 14 8f     lw         s4,0xc(t8)
     6::800a9944 48 00 cc eb     gte_stSXY0 0x48(s8)
     6::800a9948 5c 00 cd eb     gte_stSXY1 0x5c(s8)
     6::800a994c 70 00 ce eb     gte_stSXY2 0x70(s8)
     6::800a9950 3c 00 c0 eb     sVXY0      0x3c(s8)
     6::800a9954 40 00 c1 eb     gte_stVZ0  0x40(s8)
     6::800a9958 50 00 c2 eb     gte_stVXY1 0x50(s8)
     6::800a995c 10 00 15 97     lhu        s5,0x10(t8)
     6::800a9960 54 00 c3 eb     gte_stVZ1  0x54(s8)
     6::800a9964 64 00 c4 eb     gte_stVXY2 0x64(s8)
     6::800a9968 68 00 c5 eb     gte_stVZ2  0x68(s8)
     6::800a996c 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a9978 4c 00 c3 a7     sh         v1,0x4c(s8)
     6::800a997c 60 00 c8 a7     sh         t0,0x60(s8)
     6::800a9980 74 00 c9 a7     sh         t1,0x74(s8)
     6::800a9984 23 58 6a 00     subu       t3,v1,t2
     6::800a9988 23 60 0a 01     subu       t4,t0,t2
     6::800a998c 23 68 2a 01     subu       t5,t1,t2
     6::800a9990 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a9994 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a9998 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a999c 4e 00 cb a3     sb         t3,0x4e(s8)
     6::800a99a0 62 00 cc a3     sb         t4,0x62(s8)
     6::800a99a4 76 00 cd a3     sb         t5,0x76(s8)
     6::800a99a8 40 18 03 00     sll        v1,v1,0x1
     6::800a99ac 40 40 08 00     sll        t0,t0,0x1
     6::800a99b0 40 48 09 00     sll        t1,t1,0x1
     6::800a99b4 23 58 6a 00     subu       t3,v1,t2
     6::800a99b8 23 60 0a 01     subu       t4,t0,t2
     6::800a99bc 23 68 2a 01     subu       t5,t1,t2
     6::800a99c0 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a99c4 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a99c8 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a99cc 4f 00 cb a3     sb         t3,0x4f(s8)
     6::800a99d0 63 00 cc a3     sb         t4,0x63(s8)
     6::800a99d4 77 00 cd a3     sb         t5,0x77(s8)
     6::800a99d8 ff ff 93 32     andi       s3,s4,0xffff
     6::800a99dc 00 99 13 00     sll        s3,s3,0x4
     6::800a99e0 21 98 77 02     addu       s3,s3,s7
     6::800a99e4 00 00 60        ldv0       s3                                               void gte_ldv0(SVECTOR * r0)
                 ca 04 00 
                 61 ca
     6::800a99ec 02 a4 14 00     srl        s4,s4,0x10
     6::800a99f0 00 a1 14 00     sll        s4,s4,0x4
     6::800a99f4 21 a0 97 02     addu       s4,s4,s7
     6::800a99f8 00 00 82        ldv1       s4                                               void gte_ldv1(SVECTOR * r0)
                 ca 04 00 
                 83 ca
     6::800a9a00 14 00 09 8f     lw         t1,0x14(t8)
     6::800a9a04 00 a9 15 00     sll        s5,s5,0x4
     6::800a9a08 21 a8 b7 02     addu       s5,s5,s7
     6::800a9a0c 00 00 a4        ldv2       s5                                               void gte_ldv2(SVECTOR * r0)
                 ca 04 00 
                 a5 ca
     6::800a9a14 7c 00 29 ac     sw         t1,0x7c(at)
     6::800a9a18 00 00 00 00     nop
     6::800a9a1c 30 00 28 4a     RTPT
     6::800a9a20 08 00 6f 8e     lw         t7,0x8(s3)
     6::800a9a24 08 00 90 8e     lw         s0,0x8(s4)
     6::800a9a28 08 00 b1 8e     lw         s1,0x8(s5)
     6::800a9a2c 80 00 cf af     sw         t7,0x80(s8)
     6::800a9a30 94 00 d0 af     sw         s0,0x94(s8)
     6::800a9a34 a8 00 d1 af     sw         s1,0xa8(s8)
     6::800a9a38 84 00 cc eb     gte_stSXY0 0x84(s8)
     6::800a9a3c 98 00 cd eb     gte_stSXY1 0x98(s8)
     6::800a9a40 ac 00 ce eb     gte_stSXY2 0xac(s8)
     6::800a9a44 78 00 c0 eb     sVXY0      0x78(s8)
     6::800a9a48 7c 00 c1 eb     gte_stVZ0  0x7c(s8)
     6::800a9a4c 8c 00 c2 eb     gte_stVXY1 0x8c(s8)
     6::800a9a50 90 00 c3 eb     gte_stVZ1  0x90(s8)
     6::800a9a54 a0 00 c4 eb     gte_stVXY2 0xa0(s8)
     6::800a9a58 a4 00 c5 eb     gte_stVZ2  0xa4(s8)
     6::800a9a5c 00 88 03        read_sz_   v1,t0,t1
                 48 00 90 
                 08 48 00 
     6::800a9a68 88 00 c3 a7     sh         v1,0x88(s8)
     6::800a9a6c 9c 00 c8 a7     sh         t0,0x9c(s8)
     6::800a9a70 b0 00 c9 a7     sh         t1,0xb0(s8)
     6::800a9a74 23 58 6a 00     subu       t3,v1,t2
     6::800a9a78 23 60 0a 01     subu       t4,t0,t2
     6::800a9a7c 23 68 2a 01     subu       t5,t1,t2
     6::800a9a80 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a9a84 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a9a88 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a9a8c 8a 00 cb a3     sb         t3,0x8a(s8)
     6::800a9a90 9e 00 cc a3     sb         t4,0x9e(s8)
     6::800a9a94 b2 00 cd a3     sb         t5,0xb2(s8)
     6::800a9a98 40 18 03 00     sll        v1,v1,0x1
     6::800a9a9c 40 40 08 00     sll        t0,t0,0x1
     6::800a9aa0 40 48 09 00     sll        t1,t1,0x1
     6::800a9aa4 23 58 6a 00     subu       t3,v1,t2
     6::800a9aa8 23 60 0a 01     subu       t4,t0,t2
     6::800a9aac 23 68 2a 01     subu       t5,t1,t2
     6::800a9ab0 c2 5f 0b 00     srl        t3,t3,0x1f
     6::800a9ab4 c2 67 0c 00     srl        t4,t4,0x1f
     6::800a9ab8 c2 6f 0d 00     srl        t5,t5,0x1f
     6::800a9abc 8b 00 cb a3     sb         t3,0x8b(s8)
     6::800a9ac0 9f 00 cc a3     sb         t4,0x9f(s8)
     6::800a9ac4 b3 00 cd a3     sb         t5,0xb3(s8)
     6::800a9ac8 50 00 03 3c     lui        v1,0x50
     6::800a9acc 78 64 63 34     ori        v1,v1,0x6478
     6::800a9ad0 08 00 08 24     li         t0,0x8
     6::800a9ad4 e8 a7 02 0c     jal        FUN_OVR_226__800a9fa0                            undefined FUN_OVR_226__800a9fa0()
     6::800a9ad8 00 00 0a 24     _li        t2,0x0
     6::800a9adc 14 50 03 3c     lui        v1,0x5014
     6::800a9ae0 8c 78 63 34     ori        v1,v1,0x788c
     6::800a9ae4 0d 00 08 24     li         t0,0xd
     6::800a9ae8 e8 a7 02 0c     jal        FUN_OVR_226__800a9fa0                            undefined FUN_OVR_226__800a9fa0()
     6::800a9aec 04 00 0a 24     _li        t2,0x4
     6::800a9af0 78 64 03 3c     lui        v1,0x6478
     6::800a9af4 a0 28 63 34     ori        v1,v1,0x28a0
     6::800a9af8 12 00 08 24     li         t0,0x12
     6::800a9afc e8 a7 02 0c     jal        FUN_OVR_226__800a9fa0                            undefined FUN_OVR_226__800a9fa0()
     6::800a9b00 08 00 0a 24     _li        t2,0x8
     6::800a9b04 8c 78 03 3c     lui        v1,0x788c
     6::800a9b08 3c a0 63 34     ori        v1,v1,0xa03c
     6::800a9b0c 17 00 08 24     li         t0,0x17
     6::800a9b10 e8 a7 02 0c     jal        FUN_OVR_226__800a9fa0                            undefined FUN_OVR_226__800a9fa0()
     6::800a9b14 0c 00 0a 24     _li        t2,0xc
     6::800a9b18 04 00 98 8c     lw         t8,0x4(a0)
     6::800a9b1c 2b ff 01 04     bgez       zero,LAB_OVR_226__800a97cc
     6::800a9b20 04 00 84 24     _addiu     a0,a0,0x4
                             LAB_OVR_226__800a9b24                           XREF[12]:    FUN_OVR_226__800a9e7c:800a9e98(j
                                                                                          FUN_OVR_226__800a9e7c:800a9f34(j
                                                                                          FUN_OVR_226__800a9e7c:800a9f3c(j
                                                                                          FUN_OVR_226__800a9e7c:800a9f70(j
                                                                                          OVR_226::800aa02c(j), 
                                                                                          OVR_226::800aa0b8(j), 
                                                                                          OVR_226::800aa0c0(j), 
                                                                                          OVR_226::800aa0ec(j), 
                                                                                          FUN_OVR_226__800a9e7c:800aa408(j
                                                                                          FUN_OVR_226__800a9e7c:800aa4c4(j
                                                                                          FUN_OVR_226__800a9e7c:800aa5f8(j
                                                                                          FUN_OVR_226__800a9e7c:800aa6b0(j
     6::800a9b24 08 00 e0 03     jr         ra
     6::800a9b28 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9b2c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9b2c                           XREF[4]:     FUN_OVR_226__800a9b7c:800a9c04(j
                                                                                          FUN_OVR_226__800a9b7c:800a9c9c(c
                                                                                          FUN_OVR_226__800a9b7c:800a9cc4(c
                                                                                          FUN_OVR_226__800a9b7c:800a9d30(c
     6::800a9b2c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a9b30 50 00 d4 27     addiu      s4,s8,0x50
     6::800a9b34 64 00 d5 27     addiu      s5,s8,0x64
     6::800a9b38 d0 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9b3c 78 00 d6 27     _addiu     s6,s8,0x78
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9b40()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9b40                           XREF[6]:     FUN_OVR_226__800a9b7c:800a9c0c(c
                                                                                          FUN_OVR_226__800a9b7c:800a9cac(j
                                                                                          FUN_OVR_226__800a9b7c:800a9cbc(c
                                                                                          FUN_OVR_226__800a9b7c:800a9cec(c
                                                                                          FUN_OVR_226__800a9b7c:800a9d0c(c
                                                                                          FUN_OVR_226__800a9b7c:800a9d40(c
     6::800a9b40 50 00 d3 27     addiu      s3,s8,0x50
     6::800a9b44 14 00 d4 27     addiu      s4,s8,0x14
     6::800a9b48 78 00 d5 27     addiu      s5,s8,0x78
     6::800a9b4c cb 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9b50 8c 00 d6 27     _addiu     s6,s8,0x8c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9b54()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9b54                           XREF[6]:     FUN_OVR_226__800a9b7c:800a9c34(c
                                                                                          FUN_OVR_226__800a9b7c:800a9c94(c
                                                                                          FUN_OVR_226__800a9b7c:800a9cd4(j
                                                                                          FUN_OVR_226__800a9b7c:800a9ce4(c
                                                                                          FUN_OVR_226__800a9b7c:800a9d14(c
                                                                                          FUN_OVR_226__800a9b7c:800a9d50(c
     6::800a9b54 64 00 d3 27     addiu      s3,s8,0x64
     6::800a9b58 78 00 d4 27     addiu      s4,s8,0x78
     6::800a9b5c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a9b60 c6 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9b64 a0 00 d6 27     _addiu     s6,s8,0xa0
                             LAB_OVR_226__800a9b68                           XREF[4]:     OVR_226::800a9c84(j), 
                                                                                          OVR_226::800a9cfc(j), 
                                                                                          OVR_226::800a9d24(j), 
                                                                                          OVR_226::800a9d68(j)  
     6::800a9b68 78 00 d3 27     addiu      s3,s8,0x78
     6::800a9b6c 8c 00 d4 27     addiu      s4,s8,0x8c
     6::800a9b70 a0 00 d5 27     addiu      s5,s8,0xa0
     6::800a9b74 c1 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9b78 3c 00 d6 27     _addiu     s6,s8,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9b7c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9b7c                           XREF[2]:     OVR_226::800a9c2c(c), 
                                                                                          OVR_226::800a9d04(c)  
     6::800a9b7c 64 00 d3 27     addiu      s3,s8,0x64
     6::800a9b80 00 00 d4 27     addiu      s4,s8,0x0
     6::800a9b84 78 00 d5 27     addiu      s5,s8,0x78
     6::800a9b88 bc 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9b8c 14 00 d6 27     _addiu     s6,s8,0x14
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a9b90                           XREF[2]:     OVR_226::800a9c44(j), 
                                                                                          OVR_226::800a9cb4(c)  
     6::800a9b90 14 00 d3 27     addiu      s3,s8,0x14
     6::800a9b94 3c 00 d4 27     addiu      s4,s8,0x3c
     6::800a9b98 78 00 d5 27     addiu      s5,s8,0x78
     6::800a9b9c b7 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9ba0 a0 00 d6 27     _addiu     s6,s8,0xa0
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a9ba4                           XREF[2]:     OVR_226::800a9c14(c), 
                                                                                          OVR_226::800a9cdc(c)  
     6::800a9ba4 28 00 d3 27     addiu      s3,s8,0x28
     6::800a9ba8 00 00 d4 27     addiu      s4,s8,0x0
     6::800a9bac 78 00 d5 27     addiu      s5,s8,0x78
     6::800a9bb0 b2 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9bb4 50 00 d6 27     _addiu     s6,s8,0x50
                             **************************************************************
                             *                                                            *
                             *  SUBROUTINE                                                *
                             **************************************************************
                             SUB_OVR_226__800a9bb8                           XREF[2]:     OVR_226::800a9c24(j), 
                                                                                          OVR_226::800a9c8c(c)  
     6::800a9bb8 28 00 d3 27     addiu      s3,s8,0x28
     6::800a9bbc 78 00 d4 27     addiu      s4,s8,0x78
     6::800a9bc0 3c 00 d5 27     addiu      s5,s8,0x3c
     6::800a9bc4 ad 00 01 04     bgez       zero,FUN_OVR_226__800a9e7c
     6::800a9bc8 8c 00 d6 27     _addiu     s6,s8,0x8c
     6::800a9bcc 50 00 d3 27     addiu      s3,s8,0x50
     6::800a9bd0 14 00 d4 27     addiu      s4,s8,0x14
     6::800a9bd4 78 00 d5 27     addiu      s5,s8,0x78
     6::800a9bd8 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a9bdc 9f a7 02 0c     jal        FUN_OVR_226__800a9e7c                            undefined FUN_OVR_226__800a9e7c()
     6::800a9be0 0c 00 0a 24     _li        t2,0xc
     6::800a9be4 64 00 d3 27     addiu      s3,s8,0x64
     6::800a9be8 78 00 d4 27     addiu      s4,s8,0x78
     6::800a9bec 28 00 d5 27     addiu      s5,s8,0x28
     6::800a9bf0 3c 00 d6 27     addiu      s6,s8,0x3c
     6::800a9bf4 9f a7 02 0c     jal        FUN_OVR_226__800a9e7c                            undefined FUN_OVR_226__800a9e7c()
     6::800a9bf8 0c 00 0a 24     _li        t2,0xc
     6::800a9bfc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9c00 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9c04 c9 ff 01 04     bgez       zero,FUN_OVR_226__800a9b2c
     6::800a9c08 0c 00 0a 24     _li        t2,0xc
     6::800a9c0c d0 a6 02 0c     jal        FUN_OVR_226__800a9b40                            undefined FUN_OVR_226__800a9b40()
     6::800a9c10 0c 00 0a 24     _li        t2,0xc
     6::800a9c14 e9 a6 02 0c     jal        SUB_OVR_226__800a9ba4
     6::800a9c18 0c 00 0a 24     _li        t2,0xc
     6::800a9c1c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9c20 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9c24 e4 ff 01 04     bgez       zero,SUB_OVR_226__800a9bb8
     6::800a9c28 0c 00 0a 24     _li        t2,0xc
     6::800a9c2c df a6 02 0c     jal        FUN_OVR_226__800a9b7c                            undefined FUN_OVR_226__800a9b7c()
     6::800a9c30 0c 00 0a 24     _li        t2,0xc
     6::800a9c34 d5 a6 02 0c     jal        FUN_OVR_226__800a9b54                            undefined FUN_OVR_226__800a9b54()
     6::800a9c38 0c 00 0a 24     _li        t2,0xc
     6::800a9c3c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9c40 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9c44 d2 ff 01 04     bgez       zero,SUB_OVR_226__800a9b90
     6::800a9c48 0c 00 0a 24     _li        t2,0xc
     6::800a9c4c 00 00 d3 27     addiu      s3,s8,0x0
     6::800a9c50 14 00 d4 27     addiu      s4,s8,0x14
     6::800a9c54 78 00 d5 27     addiu      s5,s8,0x78
     6::800a9c58 8c 00 d6 27     addiu      s6,s8,0x8c
     6::800a9c5c 9f a7 02 0c     jal        FUN_OVR_226__800a9e7c                            undefined FUN_OVR_226__800a9e7c()
     6::800a9c60 0c 00 0a 24     _li        t2,0xc
     6::800a9c64 00 00 d3 27     addiu      s3,s8,0x0
     6::800a9c68 78 00 d4 27     addiu      s4,s8,0x78
     6::800a9c6c 28 00 d5 27     addiu      s5,s8,0x28
     6::800a9c70 a0 00 d6 27     addiu      s6,s8,0xa0
     6::800a9c74 9f a7 02 0c     jal        FUN_OVR_226__800a9e7c                            undefined FUN_OVR_226__800a9e7c()
     6::800a9c78 0c 00 0a 24     _li        t2,0xc
     6::800a9c7c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9c80 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9c84 b8 ff 01 04     bgez       zero,LAB_OVR_226__800a9b68
     6::800a9c88 0c 00 0a 24     _li        t2,0xc
     6::800a9c8c ee a6 02 0c     jal        SUB_OVR_226__800a9bb8
     6::800a9c90 0c 00 0a 24     _li        t2,0xc
     6::800a9c94 d5 a6 02 0c     jal        FUN_OVR_226__800a9b54                            undefined FUN_OVR_226__800a9b54()
     6::800a9c98 04 00 0a 24     _li        t2,0x4
     6::800a9c9c cb a6 02 0c     jal        FUN_OVR_226__800a9b2c                            undefined FUN_OVR_226__800a9b2c()
     6::800a9ca0 0c 00 0a 24     _li        t2,0xc
     6::800a9ca4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9ca8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9cac a4 ff 01 04     bgez       zero,FUN_OVR_226__800a9b40
     6::800a9cb0 0c 00 0a 24     _li        t2,0xc
     6::800a9cb4 e4 a6 02 0c     jal        SUB_OVR_226__800a9b90
     6::800a9cb8 0c 00 0a 24     _li        t2,0xc
     6::800a9cbc d0 a6 02 0c     jal        FUN_OVR_226__800a9b40                            undefined FUN_OVR_226__800a9b40()
     6::800a9cc0 04 00 0a 24     _li        t2,0x4
     6::800a9cc4 cb a6 02 0c     jal        FUN_OVR_226__800a9b2c                            undefined FUN_OVR_226__800a9b2c()
     6::800a9cc8 0c 00 0a 24     _li        t2,0xc
     6::800a9ccc 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9cd0 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9cd4 9f ff 01 04     bgez       zero,FUN_OVR_226__800a9b54
     6::800a9cd8 0c 00 0a 24     _li        t2,0xc
     6::800a9cdc e9 a6 02 0c     jal        SUB_OVR_226__800a9ba4
     6::800a9ce0 0c 00 0a 24     _li        t2,0xc
     6::800a9ce4 d5 a6 02 0c     jal        FUN_OVR_226__800a9b54                            undefined FUN_OVR_226__800a9b54()
     6::800a9ce8 08 00 0a 24     _li        t2,0x8
     6::800a9cec d0 a6 02 0c     jal        FUN_OVR_226__800a9b40                            undefined FUN_OVR_226__800a9b40()
     6::800a9cf0 0c 00 0a 24     _li        t2,0xc
     6::800a9cf4 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9cf8 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9cfc 9a ff 01 04     bgez       zero,LAB_OVR_226__800a9b68
     6::800a9d00 0c 00 0a 24     _li        t2,0xc
     6::800a9d04 df a6 02 0c     jal        FUN_OVR_226__800a9b7c                            undefined FUN_OVR_226__800a9b7c()
     6::800a9d08 0c 00 0a 24     _li        t2,0xc
     6::800a9d0c d0 a6 02 0c     jal        FUN_OVR_226__800a9b40                            undefined FUN_OVR_226__800a9b40()
     6::800a9d10 08 00 0a 24     _li        t2,0x8
     6::800a9d14 d5 a6 02 0c     jal        FUN_OVR_226__800a9b54                            undefined FUN_OVR_226__800a9b54()
     6::800a9d18 0c 00 0a 24     _li        t2,0xc
     6::800a9d1c 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9d20 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9d24 90 ff 01 04     bgez       zero,LAB_OVR_226__800a9b68
     6::800a9d28 0c 00 0a 24     _li        t2,0xc
     6::800a9d2c b4 00 c0 af     sw         zero,0xb4(s8)
     6::800a9d30 cb a6 02 0c     jal        FUN_OVR_226__800a9b2c                            undefined FUN_OVR_226__800a9b2c()
     6::800a9d34 0c 00 0a 24     _li        t2,0xc
     6::800a9d38 0c 00 03 24     li         v1,0xc
     6::800a9d3c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a9d40 d0 a6 02 0c     jal        FUN_OVR_226__800a9b40                            undefined FUN_OVR_226__800a9b40()
     6::800a9d44 0c 00 0a 24     _li        t2,0xc
     6::800a9d48 30 00 03 24     li         v1,0x30
     6::800a9d4c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a9d50 d5 a6 02 0c     jal        FUN_OVR_226__800a9b54                            undefined FUN_OVR_226__800a9b54()
     6::800a9d54 0c 00 0a 24     _li        t2,0xc
     6::800a9d58 3c 00 03 24     li         v1,0x3c
     6::800a9d5c b4 00 c3 af     sw         v1,0xb4(s8)
     6::800a9d60 38 00 3f 8f     lw         ra,0x38(t9)
     6::800a9d64 fc ff 39 27     addiu      t9,t9,-0x4
     6::800a9d68 7f ff 01 04     bgez       zero,LAB_OVR_226__800a9b68
     6::800a9d6c 0c 00 0a 24     _li        t2,0xc
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9d70()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9d70                           XREF[5]:     FUN_OVR_226__800a9fa0:800aa290(c
                                                                                          FUN_OVR_226__800a9fa0:800aa2a4(c
                                                                                          FUN_OVR_226__800a9fa0:800aa2b8(c
                                                                                          FUN_OVR_226__800a9fa0:800aa2cc(c
                                                                                          FUN_OVR_226__800a9fa0:800aa2e0(c
     6::800a9d70 00 00 ab 85     lh         t3,0x0(t5)
     6::800a9d74 00 00 cc 85     lh         t4,0x0(t6)
     6::800a9d78 00 00 eb a5     sh         t3,0x0(t7)
     6::800a9d7c 21 18 6c 01     addu       v1,t3,t4
     6::800a9d80 43 18 03 00     sra        v1,v1,0x1
     6::800a9d84 00 00 03 a6     sh         v1,0x0(s0)
     6::800a9d88 02 00 ab 85     lh         t3,0x2(t5)
     6::800a9d8c 02 00 cc 85     lh         t4,0x2(t6)
     6::800a9d90 02 00 eb a5     sh         t3,0x2(t7)
     6::800a9d94 21 18 6c 01     addu       v1,t3,t4
     6::800a9d98 43 18 03 00     sra        v1,v1,0x1
     6::800a9d9c 02 00 03 a6     sh         v1,0x2(s0)
     6::800a9da0 04 00 ab 85     lh         t3,0x4(t5)
     6::800a9da4 04 00 cc 85     lh         t4,0x4(t6)
     6::800a9da8 04 00 eb a5     sh         t3,0x4(t7)
     6::800a9dac 21 18 6c 01     addu       v1,t3,t4
     6::800a9db0 43 18 03 00     sra        v1,v1,0x1
     6::800a9db4 00 00 00 ca     gte_ldVXY0 0x0(s0)
     6::800a9db8 00 08 83 48     gte_ldVZ0  v1
     6::800a9dbc 04 00 03 a6     sh         v1,0x4(s0)
     6::800a9dc0 08 00 ab 91     lbu        t3,0x8(t5)
     6::800a9dc4 01 00 18 4a     RTPS
     6::800a9dc8 08 00 cc 91     lbu        t4,0x8(t6)
     6::800a9dcc 08 00 eb a1     sb         t3,0x8(t7)
     6::800a9dd0 21 18 6c 01     addu       v1,t3,t4
     6::800a9dd4 43 18 03 00     sra        v1,v1,0x1
     6::800a9dd8 08 00 03 a2     sb         v1,0x8(s0)
     6::800a9ddc 09 00 ab 91     lbu        t3,0x9(t5)
     6::800a9de0 09 00 cc 91     lbu        t4,0x9(t6)
     6::800a9de4 09 00 eb a1     sb         t3,0x9(t7)
     6::800a9de8 21 18 6c 01     addu       v1,t3,t4
     6::800a9dec 43 18 03 00     sra        v1,v1,0x1
     6::800a9df0 09 00 03 a2     sb         v1,0x9(s0)
     6::800a9df4 0a 00 ab 91     lbu        t3,0xa(t5)
     6::800a9df8 0a 00 cc 91     lbu        t4,0xa(t6)
     6::800a9dfc 0a 00 eb a1     sb         t3,0xa(t7)
     6::800a9e00 21 18 6c 01     addu       v1,t3,t4
     6::800a9e04 43 18 03 00     sra        v1,v1,0x1
     6::800a9e08 0a 00 03 a2     sb         v1,0xa(s0)
     6::800a9e0c 06 00 ab 91     lbu        t3,0x6(t5)
     6::800a9e10 06 00 cc 91     lbu        t4,0x6(t6)
     6::800a9e14 06 00 eb a1     sb         t3,0x6(t7)
     6::800a9e18 21 18 6c 01     addu       v1,t3,t4
     6::800a9e1c 43 18 03 00     sra        v1,v1,0x1
     6::800a9e20 06 00 03 a2     sb         v1,0x6(s0)
     6::800a9e24 07 00 ab 91     lbu        t3,0x7(t5)
     6::800a9e28 07 00 cc 91     lbu        t4,0x7(t6)
     6::800a9e2c 07 00 eb a1     sb         t3,0x7(t7)
     6::800a9e30 21 18 6c 01     addu       v1,t3,t4
     6::800a9e34 43 18 03 00     sra        v1,v1,0x1
     6::800a9e38 07 00 03 a2     sb         v1,0x7(s0)
     6::800a9e3c 0c 00 a3 8d     lw         v1,0xc(t5)
     6::800a9e40 10 00 a8 8d     lw         t0,0x10(t5)
     6::800a9e44 0c 00 e3 ad     sw         v1,0xc(t7)
     6::800a9e48 10 00 e8 ad     sw         t0,0x10(t7)
     6::800a9e4c 5c 00 2b 8c     lw         t3,0x5c(at)
     6::800a9e50 00 98 03 48     gte_stSZ3  v1
     6::800a9e54 0c 00 0e ea     gte_stSXY2 0xc(s0)
     6::800a9e58 10 00 03 ae     sw         v1,0x10(s0)
     6::800a9e5c 23 40 6b 00     subu       t0,v1,t3
     6::800a9e60 c2 47 08 00     srl        t0,t0,0x1f
     6::800a9e64 12 00 08 a2     sb         t0,0x12(s0)
     6::800a9e68 40 18 03 00     sll        v1,v1,0x1
     6::800a9e6c 23 40 6b 00     subu       t0,v1,t3
     6::800a9e70 c2 47 08 00     srl        t0,t0,0x1f
     6::800a9e74 08 00 e0 03     jr         ra
     6::800a9e78 13 00 08 a2     _sb        t0,0x13(s0)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9e7c()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9e7c                           XREF[12]:    FUN_OVR_226__800a9b2c:800a9b38(j
                                                                                          FUN_OVR_226__800a9b40:800a9b4c(j
                                                                                          FUN_OVR_226__800a9b54:800a9b60(j
                                                                                          FUN_OVR_226__800a9b7c:800a9b74(j
                                                                                          FUN_OVR_226__800a9b7c:800a9b88(j
                                                                                          FUN_OVR_226__800a9b7c:800a9b9c(j
                                                                                          FUN_OVR_226__800a9b7c:800a9bb0(j
                                                                                          FUN_OVR_226__800a9b7c:800a9bc4(j
                                                                                          FUN_OVR_226__800a9b7c:800a9bdc(c
                                                                                          FUN_OVR_226__800a9b7c:800a9bf4(c
                                                                                          FUN_OVR_226__800a9b7c:800a9c5c(c
                                                                                          FUN_OVR_226__800a9b7c:800a9c74(c
     6::800a9e7c 13 00 6f 82     lb         t7,0x13(s3)
     6::800a9e80 13 00 90 82     lb         s0,0x13(s4)
     6::800a9e84 13 00 b1 82     lb         s1,0x13(s5)
     6::800a9e88 13 00 d2 82     lb         s2,0x13(s6)
     6::800a9e8c 24 18 f0 01     and        v1,t7,s0
     6::800a9e90 24 18 71 00     and        v1,v1,s1
     6::800a9e94 24 18 72 00     and        v1,v1,s2
     6::800a9e98 22 ff 60 14     bne        v1,zero,LAB_OVR_226__800a9b24
     6::800a9e9c 12 00 6f 82     _lb        t7,0x12(s3)
     6::800a9ea0 12 00 90 82     lb         s0,0x12(s4)
     6::800a9ea4 12 00 b1 82     lb         s1,0x12(s5)
     6::800a9ea8 12 00 d2 82     lb         s2,0x12(s6)
     6::800a9eac 25 78 f0 01     or         t7,t7,s0
     6::800a9eb0 25 78 f1 01     or         t7,t7,s1
     6::800a9eb4 25 78 f2 01     or         t7,t7,s2
     6::800a9eb8 2e 00 e0 15     bne        t7,zero,LAB_OVR_226__800a9f74
     6::800a9ebc 0c 00 03 24     _li        v1,0xc
     6::800a9ec0 70 00 2a ac     sw         t2,0x70(at)
     6::800a9ec4 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a9ec8 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a9ecc 94 01 2a 8c     lw         t2,0x194(at)
     6::800a9ed0 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800a9ed4 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800a9ed8 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800a9edc 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800a9ee0 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800a9ee4 06 00 40 4b     NCLIP
     6::800a9ee8 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800a9eec 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800a9ef0 23 78 68 01     subu       t7,t3,t0
     6::800a9ef4 23 80 88 01     subu       s0,t4,t0
     6::800a9ef8 23 88 a8 01     subu       s1,t5,t0
     6::800a9efc 23 90 c8 01     subu       s2,t6,t0
     6::800a9f00 00 c0 08 48     gte_stMAC0 t0
     6::800a9f04 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800a9f08 02 00 00 11     beq        t0,zero,LAB_OVR_226__800a9f14
     6::800a9f0c 22 40 08 00     _sub       t0,zero,t0
     6::800a9f10 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800a9f14                           XREF[1]:     OVR_226::800a9f08(j)  
     6::800a9f14 06 00 40 4b     NCLIP
     6::800a9f18 24 18 6c 01     and        v1,t3,t4
     6::800a9f1c 24 18 6d 00     and        v1,v1,t5
     6::800a9f20 24 18 6e 00     and        v1,v1,t6
     6::800a9f24 25 78 f0 01     or         t7,t7,s0
     6::800a9f28 25 78 f1 01     or         t7,t7,s1
     6::800a9f2c 27 78 f2 01     nor        t7,t7,s2
     6::800a9f30 25 78 e3 01     or         t7,t7,v1
     6::800a9f34 fb fe e0 05     bltz       t7,LAB_OVR_226__800a9b24
     6::800a9f38 00 7c 0f 00     _sll       t7,t7,0x10
     6::800a9f3c f9 fe e0 05     bltz       t7,LAB_OVR_226__800a9b24
     6::800a9f40 00 c0 03 48     _gte_stM   v1
     6::800a9f44 25 40 09 01     or         t0,t0,t1
     6::800a9f48 02 00 60 10     beq        v1,zero,LAB_OVR_226__800a9f54
     6::800a9f4c c2 47 08 00     _srl       t0,t0,0x1f
     6::800a9f50 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800a9f54                           XREF[1]:     OVR_226::800a9f48(j)  
     6::800a9f54 80 40 08 00     sll        t0,t0,0x2
     6::800a9f58 25 18 69 00     or         v1,v1,t1
     6::800a9f5c c2 1f 03 00     srl        v1,v1,0x1f
     6::800a9f60 c0 18 03 00     sll        v1,v1,0x3
     6::800a9f64 70 00 2a 8c     lw         t2,0x70(at)
     6::800a9f68 25 18 68 00     or         v1,v1,t0
     6::800a9f6c 24 18 6a 00     and        v1,v1,t2
     6::800a9f70 ec fe 60 10     beq        v1,zero,LAB_OVR_226__800a9b24
                             LAB_OVR_226__800a9f74                           XREF[1]:     OVR_226::800a9eb8(j)  
     6::800a9f74 70 00 23 ac     _sw        v1,0x70(at)
     6::800a9f78 3c 00 3f af     sw         ra,0x3c(t9)
     6::800a9f7c 24 03 28 24     addiu      t0,at,0x324
     6::800a9f80 ec 00 1e 11     beq        t0,s8,LAB_OVR_226__800aa334
     6::800a9f84 04 00 39 27     _addiu     t9,t9,0x4
     6::800a9f88 10 00 6b 96     lhu        t3,0x10(s3)
     6::800a9f8c 10 00 8c 96     lhu        t4,0x10(s4)
     6::800a9f90 10 00 ad 96     lhu        t5,0x10(s5)
     6::800a9f94 10 00 ce 96     lhu        t6,0x10(s6)
     6::800a9f98 a8 00 01 04     bgez       zero,LAB_OVR_226__800aa23c
     6::800a9f9c 28 00 23 8c     _lw        v1,0x28(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800a9fa0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800a9fa0                           XREF[4]:     OVR_226::800a9ad4(c), 
                                                                                          OVR_226::800a9ae8(c), 
                                                                                          OVR_226::800a9afc(c), 
                                                                                          OVR_226::800a9b10(c)  
     6::800a9fa0 7c 00 29 8c     lw         t1,0x7c(at)
     6::800a9fa4 b4 00 ca af     sw         t2,0xb4(s8)
     6::800a9fa8 06 50 09 01     srlv       t2,t1,t0
     6::800a9fac 1f 00 4a 31     andi       t2,t2,0x1f
     6::800a9fb0 80 50 0a 00     sll        t2,t2,0x2
     6::800a9fb4 21 50 41 01     addu       t2,t2,at
     6::800a9fb8 ec 00 4a 8d     lw         t2,0xec(t2)
     6::800a9fbc 6c 00 28 8c     lw         t0,0x6c(at)
     6::800a9fc0 94 01 2a ac     sw         t2,0x194(at)
     6::800a9fc4 02 9e 0a 00     srl        s3,t2,0x18
     6::800a9fc8 1f 00 73 32     andi       s3,s3,0x1f
     6::800a9fcc 06 98 63 02     srlv       s3,v1,s3
     6::800a9fd0 ff 00 73 32     andi       s3,s3,0xff
     6::800a9fd4 21 98 7e 02     addu       s3,s3,s8
     6::800a9fd8 02 a4 0a 00     srl        s4,t2,0x10
     6::800a9fdc 1f 00 94 32     andi       s4,s4,0x1f
     6::800a9fe0 06 a0 83 02     srlv       s4,v1,s4
     6::800a9fe4 ff 00 94 32     andi       s4,s4,0xff
     6::800a9fe8 21 a0 9e 02     addu       s4,s4,s8
     6::800a9fec 02 aa 0a 00     srl        s5,t2,0x8
     6::800a9ff0 1f 00 b5 32     andi       s5,s5,0x1f
     6::800a9ff4 06 a8 a3 02     srlv       s5,v1,s5
     6::800a9ff8 ff 00 b5 32     andi       s5,s5,0xff
     6::800a9ffc 21 a8 be 02     addu       s5,s5,s8
     6::800aa000 1f 00 56 31     andi       s6,t2,0x1f
     6::800aa004 06 b0 c3 02     srlv       s6,v1,s6
     6::800aa008 ff 00 d6 32     andi       s6,s6,0xff
     6::800aa00c 21 b0 de 02     addu       s6,s6,s8
     6::800aa010 13 00 6f 82     lb         t7,0x13(s3)
     6::800aa014 13 00 90 82     lb         s0,0x13(s4)
     6::800aa018 13 00 b1 82     lb         s1,0x13(s5)
     6::800aa01c 13 00 d2 82     lb         s2,0x13(s6)
     6::800aa020 24 18 f0 01     and        v1,t7,s0
     6::800aa024 24 18 71 00     and        v1,v1,s1
     6::800aa028 24 18 72 00     and        v1,v1,s2
     6::800aa02c bd fe 60 14     bne        v1,zero,LAB_OVR_226__800a9b24
     6::800aa030 12 00 6f 82     _lb        t7,0x12(s3)
     6::800aa034 12 00 90 82     lb         s0,0x12(s4)
     6::800aa038 12 00 b1 82     lb         s1,0x12(s5)
     6::800aa03c 12 00 d2 82     lb         s2,0x12(s6)
     6::800aa040 25 78 f0 01     or         t7,t7,s0
     6::800aa044 25 78 f1 01     or         t7,t7,s1
     6::800aa048 25 78 f2 01     or         t7,t7,s2
     6::800aa04c 28 00 e0 15     bne        t7,zero,LAB_OVR_226__800aa0f0
     6::800aa050 0c 00 03 24     _li        v1,0xc
     6::800aa054 0c 00 6c ca     gte_ldSXY0 0xc(s3)
     6::800aa058 0c 00 8d ca     gte_ldSXY1 0xc(s4)
     6::800aa05c 0c 00 ae ca     gte_ldSXY2 0xc(s5)
     6::800aa060 0c 00 6b 8e     lw         t3,0xc(s3)
     6::800aa064 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800aa068 06 00 40 4b     NCLIP
     6::800aa06c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800aa070 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800aa074 23 78 68 01     subu       t7,t3,t0
     6::800aa078 23 80 88 01     subu       s0,t4,t0
     6::800aa07c 23 88 a8 01     subu       s1,t5,t0
     6::800aa080 23 90 c8 01     subu       s2,t6,t0
     6::800aa084 00 c0 08 48     gte_stMAC0 t0
     6::800aa088 0c 00 cc ca     gte_ldSXY0 0xc(s6)
     6::800aa08c 02 00 00 11     beq        t0,zero,LAB_OVR_226__800aa098
     6::800aa090 22 40 08 00     _sub       t0,zero,t0
     6::800aa094 26 40 0a 01     xor        t0,t0,t2
                             LAB_OVR_226__800aa098                           XREF[1]:     OVR_226::800aa08c(j)  
     6::800aa098 06 00 40 4b     NCLIP
     6::800aa09c 24 18 6c 01     and        v1,t3,t4
     6::800aa0a0 24 18 6d 00     and        v1,v1,t5
     6::800aa0a4 24 18 6e 00     and        v1,v1,t6
     6::800aa0a8 25 78 f0 01     or         t7,t7,s0
     6::800aa0ac 25 78 f1 01     or         t7,t7,s1
     6::800aa0b0 27 78 f2 01     nor        t7,t7,s2
     6::800aa0b4 25 78 e3 01     or         t7,t7,v1
     6::800aa0b8 9a fe e0 05     bltz       t7,LAB_OVR_226__800a9b24
     6::800aa0bc 00 7c 0f 00     _sll       t7,t7,0x10
     6::800aa0c0 98 fe e0 05     bltz       t7,LAB_OVR_226__800a9b24
     6::800aa0c4 00 c0 03 48     _gte_stM   v1
     6::800aa0c8 25 40 09 01     or         t0,t0,t1
     6::800aa0cc 02 00 60 10     beq        v1,zero,LAB_OVR_226__800aa0d8
     6::800aa0d0 c2 47 08 00     _srl       t0,t0,0x1f
     6::800aa0d4 26 18 6a 00     xor        v1,v1,t2
                             LAB_OVR_226__800aa0d8                           XREF[1]:     OVR_226::800aa0cc(j)  
     6::800aa0d8 80 40 08 00     sll        t0,t0,0x2
     6::800aa0dc 25 18 69 00     or         v1,v1,t1
     6::800aa0e0 c2 1f 03 00     srl        v1,v1,0x1f
     6::800aa0e4 c0 18 03 00     sll        v1,v1,0x3
     6::800aa0e8 25 18 68 00     or         v1,v1,t0
     6::800aa0ec 8d fe 60 10     beq        v1,zero,LAB_OVR_226__800a9b24
                             LAB_OVR_226__800aa0f0                           XREF[1]:     OVR_226::800aa04c(j)  
     6::800aa0f0 70 00 23 ac     _sw        v1,0x70(at)
     6::800aa0f4 3c 00 3f af     sw         ra,0x3c(t9)
     6::800aa0f8 04 00 39 27     addiu      t9,t9,0x4
     6::800aa0fc c2 4f 09 00     srl        t1,t1,0x1f
     6::800aa100 c0 4f 09 00     sll        t1,t1,0x1f
     6::800aa104 c2 57 0a 00     srl        t2,t2,0x1f
     6::800aa108 80 57 0a 00     sll        t2,t2,0x1e
     6::800aa10c 25 50 49 01     or         t2,t2,t1
     6::800aa110 80 00 2a ac     sw         t2,0x80(at)
     6::800aa114 10 00 6b 96     lhu        t3,0x10(s3)
     6::800aa118 10 00 8c 96     lhu        t4,0x10(s4)
     6::800aa11c 10 00 ad 96     lhu        t5,0x10(s5)
     6::800aa120 10 00 ce 96     lhu        t6,0x10(s6)
     6::800aa124 b4 00 c3 8f     lw         v1,0xb4(s8)
     6::800aa128 23 50 6c 01     subu       t2,t3,t4
     6::800aa12c 82 48 03 00     srl        t1,v1,0x2
     6::800aa130 21 48 38 01     addu       t1,t1,t8
     6::800aa134 18 00 29 81     lb         t1,0x18(t1)
     6::800aa138 02 00 40 1d     bgtz       t2,LAB_OVR_226__800aa144
     6::800aa13c 21 e0 60 01     _move      gp,t3
     6::800aa140 21 e0 80 01     move       gp,t4
                             LAB_OVR_226__800aa144                           XREF[1]:     OVR_226::800aa138(j)  
     6::800aa144 23 50 8d 03     subu       t2,gp,t5
     6::800aa148 02 00 40 1d     bgtz       t2,LAB_OVR_226__800aa154
     6::800aa14c 21 18 78 00     _addu      v1,v1,t8
     6::800aa150 21 e0 a0 01     move       gp,t5
                             LAB_OVR_226__800aa154                           XREF[1]:     OVR_226::800aa148(j)  
     6::800aa154 23 50 8e 03     subu       t2,gp,t6
     6::800aa158 02 00 40 1d     bgtz       t2,LAB_OVR_226__800aa164
     6::800aa15c 1c 00 63 8c     _lw        v1,0x1c(v1)
     6::800aa160 21 e0 c0 01     move       gp,t6
                             LAB_OVR_226__800aa164                           XREF[1]:     OVR_226::800aa158(j)  
     6::800aa164 21 50 80 03     move       t2,gp
     6::800aa168 82 e1 1c 00     srl        gp,gp,0x6
     6::800aa16c 21 e0 89 03     addu       gp,gp,t1
     6::800aa170 01 00 69 30     andi       t1,v1,0x1
     6::800aa174 02 00 20 11     beq        t1,zero,LAB_OVR_226__800aa180
     6::800aa178 80 e0 1c 00     _sll       gp,gp,0x2
     6::800aa17c ff ff 63 8c     lw         v1,-0x1(v1)
                             LAB_OVR_226__800aa180                           XREF[1]:     OVR_226::800aa174(j)  
     6::800aa180 02 00 81 07     bgez       gp,LAB_OVR_226__800aa18c
     6::800aa184 21 e0 85 03     _addu      gp,gp,a1
     6::800aa188 21 e0 a0 00     move       gp,a1
                             LAB_OVR_226__800aa18c                           XREF[1]:     OVR_226::800aa180(j)  
     6::800aa18c 1c 00 28 8c     lw         t0,0x1c(at)
     6::800aa190 24 00 69 8c     lw         t1,0x24(v1)
     6::800aa194 23 40 48 01     subu       t0,t2,t0
     6::800aa198 84 00 29 ac     sw         t1,0x84(at)
     6::800aa19c 0c 00 01 05     bgez       t0,LAB_OVR_226__800aa1d0
     6::800aa1a0 20 00 28 8c     _lw        t0,0x20(at)
     6::800aa1a4 0c 00 63 24     addiu      v1,v1,0xc
     6::800aa1a8 23 40 48 01     subu       t0,t2,t0
     6::800aa1ac 08 00 01 05     bgez       t0,LAB_OVR_226__800aa1d0
     6::800aa1b0 24 00 28 8c     _lw        t0,0x24(at)
     6::800aa1b4 0c 00 63 24     addiu      v1,v1,0xc
     6::800aa1b8 23 40 48 01     subu       t0,t2,t0
     6::800aa1bc 04 00 01 05     bgez       t0,LAB_OVR_226__800aa1d0
     6::800aa1c0 00 00 00 00     _nop
     6::800aa1c4 02 00 20 05     bltz       t1,LAB_OVR_226__800aa1d0
     6::800aa1c8 00 00 00 00     _nop
     6::800aa1cc 0c 00 63 24     addiu      v1,v1,0xc
                             LAB_OVR_226__800aa1d0                           XREF[4]:     OVR_226::800aa19c(j), 
                                                                                          OVR_226::800aa1ac(j), 
                                                                                          OVR_226::800aa1bc(j), 
                                                                                          OVR_226::800aa1c4(j)  
     6::800aa1d0 94 01 2a 8c     lw         t2,0x194(at)
     6::800aa1d4 00 00 68 8c     lw         t0,0x0(v1)
     6::800aa1d8 04 00 69 8c     lw         t1,0x4(v1)
     6::800aa1dc a0 01 28 ac     sw         t0,0x1a0(at)
     6::800aa1e0 ac 01 28 ac     sw         t0,0x1ac(at)
     6::800aa1e4 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800aa1e8 00 52 0a 00     sll        t2,t2,0x8
     6::800aa1ec 0a 00 40 05     bltz       t2,LAB_OVR_226__800aa218
     6::800aa1f0 b0 01 29 ac     _sw        t1,0x1b0(at)
     6::800aa1f4 06 00 68 a6     sh         t0,0x6(s3)
     6::800aa1f8 08 00 68 8c     lw         t0,0x8(v1)
     6::800aa1fc 06 00 89 a6     sh         t1,0x6(s4)
     6::800aa200 06 00 a8 a6     sh         t0,0x6(s5)
     6::800aa204 00 54 0a 00     sll        t2,t2,0x10
     6::800aa208 0b 00 40 05     bltz       t2,LAB_OVR_226__800aa238
     6::800aa20c 02 4c 08 00     _srl       t1,t0,0x10
     6::800aa210 09 00 01 04     bgez       zero,LAB_OVR_226__800aa238
     6::800aa214 06 00 c9 a6     _sh        t1,0x6(s6)
                             LAB_OVR_226__800aa218                           XREF[1]:     OVR_226::800aa1ec(j)  
     6::800aa218 06 00 69 a6     sh         t1,0x6(s3)
     6::800aa21c 08 00 69 8c     lw         t1,0x8(v1)
     6::800aa220 00 54 0a 00     sll        t2,t2,0x10
     6::800aa224 06 00 88 a6     sh         t0,0x6(s4)
     6::800aa228 02 44 09 00     srl        t0,t1,0x10
     6::800aa22c 02 00 40 05     bltz       t2,LAB_OVR_226__800aa238
     6::800aa230 06 00 a8 a6     _sh        t0,0x6(s5)
     6::800aa234 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800aa238                           XREF[3]:     OVR_226::800aa208(j), 
                                                                                          OVR_226::800aa210(j), 
                                                                                          OVR_226::800aa22c(j)  
     6::800aa238 24 00 23 8c     lw         v1,0x24(at)
                             LAB_OVR_226__800aa23c                           XREF[1]:     FUN_OVR_226__800a9e7c:800a9f98(j
     6::800aa23c 00 00 00 00     nop
     6::800aa240 23 88 63 01     subu       s1,t3,v1
     6::800aa244 23 90 83 01     subu       s2,t4,v1
     6::800aa248 23 78 a3 01     subu       t7,t5,v1
     6::800aa24c 23 80 c3 01     subu       s0,t6,v1
     6::800aa250 42 8f 11 00     srl        s1,s1,0x1d
     6::800aa254 04 00 31 32     andi       s1,s1,0x4
     6::800aa258 02 97 12 00     srl        s2,s2,0x1c
     6::800aa25c 08 00 52 32     andi       s2,s2,0x8
     6::800aa260 25 88 32 02     or         s1,s1,s2
     6::800aa264 c2 7e 0f 00     srl        t7,t7,0x1b
     6::800aa268 10 00 ef 31     andi       t7,t7,0x10
     6::800aa26c 25 88 2f 02     or         s1,s1,t7
     6::800aa270 82 86 10 00     srl        s0,s0,0x1a
     6::800aa274 20 00 10 32     andi       s0,s0,0x20
     6::800aa278 25 88 30 02     or         s1,s1,s0
     6::800aa27c 26 00 20 12     beq        s1,zero,LAB_OVR_226__800aa318
     6::800aa280 21 68 60 02     _move      t5,s3
     6::800aa284 21 70 80 02     move       t6,s4
     6::800aa288 b8 00 de 27     addiu      s8,s8,0xb8
     6::800aa28c 00 00 cf 27     addiu      t7,s8,0x0
     6::800aa290 5c a7 02 0c     jal        FUN_OVR_226__800a9d70                            undefined FUN_OVR_226__800a9d70()
     6::800aa294 50 00 d0 27     _addiu     s0,s8,0x50
     6::800aa298 21 68 80 02     move       t5,s4
     6::800aa29c 21 70 c0 02     move       t6,s6
     6::800aa2a0 14 00 cf 27     addiu      t7,s8,0x14
     6::800aa2a4 5c a7 02 0c     jal        FUN_OVR_226__800a9d70                            undefined FUN_OVR_226__800a9d70()
     6::800aa2a8 8c 00 d0 27     _addiu     s0,s8,0x8c
     6::800aa2ac 21 68 a0 02     move       t5,s5
     6::800aa2b0 21 70 60 02     move       t6,s3
     6::800aa2b4 28 00 cf 27     addiu      t7,s8,0x28
     6::800aa2b8 5c a7 02 0c     jal        FUN_OVR_226__800a9d70                            undefined FUN_OVR_226__800a9d70()
     6::800aa2bc 64 00 d0 27     _addiu     s0,s8,0x64
     6::800aa2c0 21 68 c0 02     move       t5,s6
     6::800aa2c4 21 70 a0 02     move       t6,s5
     6::800aa2c8 3c 00 cf 27     addiu      t7,s8,0x3c
     6::800aa2cc 5c a7 02 0c     jal        FUN_OVR_226__800a9d70                            undefined FUN_OVR_226__800a9d70()
     6::800aa2d0 a0 00 d0 27     _addiu     s0,s8,0xa0
     6::800aa2d4 50 00 cd 27     addiu      t5,s8,0x50
     6::800aa2d8 a0 00 ce 27     addiu      t6,s8,0xa0
     6::800aa2dc 50 00 cf 27     addiu      t7,s8,0x50
     6::800aa2e0 5c a7 02 0c     jal        FUN_OVR_226__800a9d70                            undefined FUN_OVR_226__800a9d70()
     6::800aa2e4 78 00 d0 27     _addiu     s0,s8,0x78
     6::800aa2e8 21 18 21 02     addu       v1,s1,at
     6::800aa2ec 48 01 63 8c     lw         v1,0x148(v1)
     6::800aa2f0 0b 80 08 3c     lui        t0,0x800b
     6::800aa2f4 08 a3 08 25     addiu      t0,t0,-0x5cf8
     6::800aa2f8 9c 00 23 ac     sw         v1,0x9c(at)
     6::800aa2fc 3c 00 28 af     sw         t0=>LAB_OVR_226__800aa308,0x3c(t9)
     6::800aa300 08 00 60 00     jr         v1
     6::800aa304 04 00 39 27     _addiu     t9,t9,0x4
                             LAB_OVR_226__800aa308                           XREF[1]:     FUN_OVR_226__800a9fa0:800aa2fc(*
     6::800aa308 38 00 3f 8f     lw         ra,0x38(t9)
     6::800aa30c fc ff 39 27     addiu      t9,t9,-0x4
     6::800aa310 08 00 e0 03     jr         ra
     6::800aa314 48 ff de 27     _addiu     s8,s8,-0xb8
                             LAB_OVR_226__800aa318                           XREF[1]:     OVR_226::800aa27c(j)  
     6::800aa318 70 00 23 8c     lw         v1,0x70(at)
     6::800aa31c fc ff 39 27     addiu      t9,t9,-0x4
     6::800aa320 21 18 61 00     addu       v1,v1,at
     6::800aa324 84 01 63 8c     lw         v1,0x184(v1)
     6::800aa328 3c 00 3f 8f     lw         ra,0x3c(t9)
     6::800aa32c 08 00 60 00     jr         v1
     6::800aa330 00 00 00 00     _nop
                             LAB_OVR_226__800aa334                           XREF[1]:     OVR_226::800a9f80(j)  
     6::800aa334 84 00 23 8c     lw         v1,0x84(at)
     6::800aa338 24 03 2a 24     addiu      t2,at,0x324
     6::800aa33c 26 00 60 1c     bgtz       v1,LAB_OVR_226__800aa3d8
     6::800aa340 20 03 28 8c     _lw        t0,0x320(at)
     6::800aa344 d8 03 29 8c     lw         t1,0x3d8(at)
     6::800aa348 16 00 5e 15     bne        t2,s8,LAB_OVR_226__800aa3a4
     6::800aa34c 9c 00 23 8c     _lw        v1,0x9c(at)
     6::800aa350 0b 80 0a 3c     lui        t2,0x800b
     6::800aa354 2c 9d 4a 25     addiu      t2,t2,-0x62d4
     6::800aa358 1f 00 6a 14     bne        v1,t2,LAB_OVR_226__800aa3d8
     6::800aa35c 94 01 23 8c     _lw        v1,0x194(at)
     6::800aa360 40 40 08 00     sll        t0,t0,0x1
     6::800aa364 00 1a 03 00     sll        v1,v1,0x8
     6::800aa368 02 00 61 04     bgez       v1,LAB_OVR_226__800aa374
     6::800aa36c 84 00 2a 8c     _lw        t2,0x84(at)
     6::800aa370 c0 00 08 25     addiu      t0,t0,0xc0
                             LAB_OVR_226__800aa374                           XREF[1]:     OVR_226::800aa368(j)  
     6::800aa374 21 40 09 01     addu       t0,t0,t1
     6::800aa378 21 50 48 01     addu       t2,t2,t0
     6::800aa37c 00 00 48 8d     lw         t0,0x0(t2)
     6::800aa380 04 00 49 8d     lw         t1,0x4(t2)
     6::800aa384 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800aa388 06 00 68 a6     sh         t0,0x6(s3)
     6::800aa38c 08 00 48 85     lh         t0,0x8(t2)
     6::800aa390 a4 01 29 ac     sw         t1,0x1a4(at)
     6::800aa394 06 00 89 a6     sh         t1,0x6(s4)
     6::800aa398 0a 00 49 85     lh         t1,0xa(t2)
     6::800aa39c 06 00 a8 a6     sh         t0,0x6(s5)
     6::800aa3a0 06 00 c9 a6     sh         t1,0x6(s6)
                             LAB_OVR_226__800aa3a4                           XREF[2]:     OVR_226::800aa348(j), 
                                                                                          OVR_226::800aa3e4(j)  
     6::800aa3a4 70 00 23 8c     lw         v1,0x70(at)
     6::800aa3a8 00 00 00 00     nop
     6::800aa3ac 21 18 61 00     addu       v1,v1,at
     6::800aa3b0 84 01 63 8c     lw         v1,0x184(v1)
     6::800aa3b4 00 00 00 00     nop
     6::800aa3b8 09 f8 60 00     jalr       v1
     6::800aa3bc fc ff 39 27     _addiu     t9,t9,-0x4
	 
	 // return address could return to main loop (800a13e0), 
	 // or could return to exe, depends on when it is executed
     6::800aa3c0 3c 00 3f 8f     lw         ra,0x3c(t9)
	 
     6::800aa3c4 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800aa3c8 b0 01 29 8c     lw         t1,0x1b0(at)
     6::800aa3cc a0 01 28 ac     sw         t0,0x1a0(at)
     6::800aa3d0 08 00 e0 03     jr         ra
     6::800aa3d4 a4 01 29 ac     _sw        t1,0x1a4(at)
                             LAB_OVR_226__800aa3d8                           XREF[2]:     OVR_226::800aa33c(j), 
                                                                                          OVR_226::800aa358(j)  
     6::800aa3d8 ac 01 28 8c     lw         t0,0x1ac(at)
     6::800aa3dc b0 01 29 8c     lw         t1,0x1b0(at)
     6::800aa3e0 a0 01 28 ac     sw         t0,0x1a0(at)
     6::800aa3e4 ef ff 01 04     bgez       zero,LAB_OVR_226__800aa3a4
     6::800aa3e8 a4 01 29 ac     _sw        t1,0x1a4(at)
     6::800aa3ec 21 98 80 02     move       s3,s4
     6::800aa3f0 21 a0 c0 02     move       s4,s6
     6::800aa3f4 13 00 6f 82     lb         t7,0x13(s3)
     6::800aa3f8 13 00 90 82     lb         s0,0x13(s4)
     6::800aa3fc 13 00 b1 82     lb         s1,0x13(s5)
     6::800aa400 24 18 f0 01     and        v1,t7,s0
     6::800aa404 24 18 71 00     and        v1,v1,s1
     6::800aa408 c6 fd 60 04     bltz       v1,LAB_OVR_226__800a9b24
     6::800aa40c 12 00 6f 82     _lb        t7,0x12(s3)
     6::800aa410 12 00 90 82     lb         s0,0x12(s4)
     6::800aa414 12 00 b1 82     lb         s1,0x12(s5)
     6::800aa418 25 78 f0 01     or         t7,t7,s0
     6::800aa41c 25 78 f1 01     or         t7,t7,s1
     6::800aa420 62 00 e0 05     bltz       t7,LAB_OVR_226__800aa5ac
     6::800aa424 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800aa428 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800aa42c 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800aa430 08 00 6f 8e     lw         t7,0x8(s3)
     6::800aa434 08 00 90 8e     lw         s0,0x8(s4)
     6::800aa438 08 00 b1 8e     lw         s1,0x8(s5)
     6::800aa43c 06 00 73 86     lh         s3,0x6(s3)
     6::800aa440 06 00 94 86     lh         s4,0x6(s4)
     6::800aa444 06 00 b5 86     lh         s5,0x6(s5)
     6::800aa448 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800aa44c a4 01 34 a4     sh         s4,0x1a4(at)
     6::800aa450 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800aa454 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800aa458 a4 01 34 8c     lw         s4,0x1a4(at)
     6::800aa45c a8 01 35 8c     lw         s5,0x1a8(at)
     6::800aa460 60 00 03 3c     lui        v1,0x60
     6::800aa464 24 48 83 02     and        t1,s4,v1
     6::800aa468 02 00 23 15     bne        t1,v1,LAB_OVR_226__800aa474
     6::800aa46c 00 36 03 3c     _lui       v1,0x3600
     6::800aa470 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800aa474                           XREF[1]:     OVR_226::800aa468(j)  
     6::800aa474 25 18 6f 00     or         v1,v1,t7
     6::800aa478 04 00 43 ac     sw         v1,0x4(v0)
     6::800aa47c 08 00 4b ac     sw         t3,0x8(v0)
     6::800aa480 0c 00 53 ac     sw         s3,0xc(v0)
     6::800aa484 10 00 50 ac     sw         s0,0x10(v0)
     6::800aa488 14 00 4c ac     sw         t4,0x14(v0)
     6::800aa48c 18 00 54 ac     sw         s4,0x18(v0)
     6::800aa490 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800aa494 20 00 4d ac     sw         t5,0x20(v0)
     6::800aa498 24 00 55 ac     sw         s5,0x24(v0)
     6::800aa49c 28 00 09 24     li         t1,0x28
     6::800aa4a0 39 00 01 04     bgez       zero,LAB_OVR_226__800aa588
     6::800aa4a4 00 09 0a 3c     _lui       t2,0x900
     6::800aa4a8 13 00 6f 82     lb         t7,0x13(s3)
     6::800aa4ac 13 00 90 82     lb         s0,0x13(s4)
     6::800aa4b0 13 00 b1 82     lb         s1,0x13(s5)
     6::800aa4b4 13 00 d2 82     lb         s2,0x13(s6)
     6::800aa4b8 24 18 f0 01     and        v1,t7,s0
     6::800aa4bc 24 18 71 00     and        v1,v1,s1
     6::800aa4c0 24 18 72 00     and        v1,v1,s2
     6::800aa4c4 97 fd 60 14     bne        v1,zero,LAB_OVR_226__800a9b24
     6::800aa4c8 12 00 6f 82     _lb        t7,0x12(s3)
     6::800aa4cc 12 00 90 82     lb         s0,0x12(s4)
     6::800aa4d0 12 00 b1 82     lb         s1,0x12(s5)
     6::800aa4d4 12 00 d2 82     lb         s2,0x12(s6)
     6::800aa4d8 25 78 f0 01     or         t7,t7,s0
     6::800aa4dc 25 78 f1 01     or         t7,t7,s1
     6::800aa4e0 25 78 f2 01     or         t7,t7,s2
     6::800aa4e4 5a 00 e0 15     bne        t7,zero,LAB_OVR_226__800aa650
     6::800aa4e8 0c 00 6b 8e     _lw        t3,0xc(s3)
     6::800aa4ec 0c 00 8c 8e     lw         t4,0xc(s4)
     6::800aa4f0 0c 00 ad 8e     lw         t5,0xc(s5)
     6::800aa4f4 0c 00 ce 8e     lw         t6,0xc(s6)
     6::800aa4f8 08 00 6f 8e     lw         t7,0x8(s3)
     6::800aa4fc 08 00 90 8e     lw         s0,0x8(s4)
     6::800aa500 08 00 b1 8e     lw         s1,0x8(s5)
     6::800aa504 08 00 d2 8e     lw         s2,0x8(s6)
     6::800aa508 06 00 73 86     lh         s3,0x6(s3)
     6::800aa50c 06 00 94 86     lh         s4,0x6(s4)
     6::800aa510 06 00 b5 86     lh         s5,0x6(s5)
     6::800aa514 a0 01 33 a4     sh         s3,0x1a0(at)
     6::800aa518 a4 01 34 a4     sh         s4,0x1a4(at)
     6::800aa51c 06 00 d4 86     lh         s4,0x6(s6)
     6::800aa520 a8 01 35 a4     sh         s5,0x1a8(at)
     6::800aa524 aa 01 34 a4     sh         s4,0x1aa(at)
     6::800aa528 a0 01 33 8c     lw         s3,0x1a0(at)
     6::800aa52c a4 01 34 8c     lw         s4,0x1a4(at)
     6::800aa530 a8 01 35 8c     lw         s5,0x1a8(at)
     6::800aa534 60 00 03 3c     lui        v1,0x60
     6::800aa538 24 48 83 02     and        t1,s4,v1
     6::800aa53c 02 00 23 15     bne        t1,v1,LAB_OVR_226__800aa548
     6::800aa540 00 3e 03 3c     _lui       v1,0x3e00
     6::800aa544 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800aa548                           XREF[1]:     OVR_226::800aa53c(j)  
     6::800aa548 25 18 6f 00     or         v1,v1,t7
     6::800aa54c 04 00 43 ac     sw         v1,0x4(v0)
     6::800aa550 08 00 4b ac     sw         t3,0x8(v0)
     6::800aa554 0c 00 53 ac     sw         s3,0xc(v0)
     6::800aa558 10 00 50 ac     sw         s0,0x10(v0)
     6::800aa55c 14 00 4c ac     sw         t4,0x14(v0)
     6::800aa560 18 00 54 ac     sw         s4,0x18(v0)
     6::800aa564 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800aa568 20 00 4d ac     sw         t5,0x20(v0)
     6::800aa56c 24 00 55 ac     sw         s5,0x24(v0)
     6::800aa570 28 00 52 ac     sw         s2,0x28(v0)
     6::800aa574 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800aa578 02 1c 15 00     srl        v1,s5,0x10
     6::800aa57c 30 00 43 ac     sw         v1,0x30(v0)
     6::800aa580 34 00 09 24     li         t1,0x34
     6::800aa584 00 0c 0a 3c     lui        t2,0xc00
                             LAB_OVR_226__800aa588                           XREF[1]:     OVR_226::800aa4a0(j)  
     6::800aa588 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800aa58c 00 42 02 00     sll        t0,v0,0x8
     6::800aa590 02 42 08 00     srl        t0,t0,0x8
     6::800aa594 25 18 6a 00     or         v1,v1,t2
     6::800aa598 00 00 43 ac     sw         v1,0x0(v0)
     6::800aa59c 21 10 49 00     addu       v0,v0,t1
     6::800aa5a0 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800aa5a4 08 00 e0 03     jr         ra
     6::800aa5a8 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800aa5ac                           XREF[1]:     OVR_226::800aa420(j)  
     6::800aa5ac 58 00 3f ac     sw         ra,0x58(at)
     6::800aa5b0 98 01 2f 84     lh         t7,0x198(at)
     6::800aa5b4 9a 01 30 84     lh         s0,0x19a(at)
     6::800aa5b8 9c 01 31 84     lh         s1,0x19c(at)
     6::800aa5bc 00 00 63 86     lh         v1,0x0(s3)
     6::800aa5c0 02 00 68 86     lh         t0,0x2(s3)
     6::800aa5c4 c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa5c8 04 00 69 86     _lh        t1,0x4(s3)
     6::800aa5cc 0b 00 40 05     bltz       t2,LAB_OVR_226__800aa5fc
     6::800aa5d0 00 00 83 86     _lh        v1,0x0(s4)
     6::800aa5d4 02 00 88 86     lh         t0,0x2(s4)
     6::800aa5d8 c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa5dc 04 00 89 86     _lh        t1,0x4(s4)
     6::800aa5e0 06 00 40 05     bltz       t2,LAB_OVR_226__800aa5fc
     6::800aa5e4 00 00 a3 86     _lh        v1,0x0(s5)
     6::800aa5e8 02 00 a8 86     lh         t0,0x2(s5)
     6::800aa5ec c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa5f0 04 00 a9 86     _lh        t1,0x4(s5)
     6::800aa5f4 58 00 3f 8c     lw         ra,0x58(at)
     6::800aa5f8 4a fd 41 05     bgez       t2,LAB_OVR_226__800a9b24
                             LAB_OVR_226__800aa5fc                           XREF[2]:     OVR_226::800aa5cc(j), 
                                                                                          OVR_226::800aa5e0(j)  
     6::800aa5fc 10 00 2f 8c     lw         t7,0x10(at)
     6::800aa600 80 00 23 8c     lw         v1,0x80(at)
     6::800aa604 a6 01 28 84     lh         t0,0x1a6(at)
     6::800aa608 a2 01 29 84     lh         t1,0x1a2(at)
     6::800aa60c 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800aa610 00 00 e3 ad     sw         v1,0x0(t7)
     6::800aa614 08 00 e8 a5     sh         t0,0x8(t7)
     6::800aa618 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800aa61c 21 68 60 02     move       t5,s3
     6::800aa620 d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa624 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800aa628 21 68 80 02     move       t5,s4
     6::800aa62c d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa630 18 00 f0 25     _addiu     s0,t7,0x18
     6::800aa634 21 68 a0 02     move       t5,s5
     6::800aa638 d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa63c 24 00 f0 25     _addiu     s0,t7,0x24
     6::800aa640 58 00 3f 8c     lw         ra,0x58(at)
     6::800aa644 30 00 ef 25     addiu      t7,t7,0x30
     6::800aa648 08 00 e0 03     jr         ra
     6::800aa64c 10 00 2f ac     _sw        t7,0x10(at)
                             LAB_OVR_226__800aa650                           XREF[1]:     OVR_226::800aa4e4(j)  
     6::800aa650 58 00 3f ac     sw         ra,0x58(at)
     6::800aa654 98 01 2f 84     lh         t7,0x198(at)
     6::800aa658 9a 01 30 84     lh         s0,0x19a(at)
     6::800aa65c 9c 01 31 84     lh         s1,0x19c(at)
     6::800aa660 00 00 63 86     lh         v1,0x0(s3)
     6::800aa664 02 00 68 86     lh         t0,0x2(s3)
     6::800aa668 c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa66c 04 00 69 86     _lh        t1,0x4(s3)
     6::800aa670 10 00 40 05     bltz       t2,LAB_OVR_226__800aa6b4
     6::800aa674 00 00 83 86     _lh        v1,0x0(s4)
     6::800aa678 02 00 88 86     lh         t0,0x2(s4)
     6::800aa67c c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa680 04 00 89 86     _lh        t1,0x4(s4)
     6::800aa684 0b 00 40 05     bltz       t2,LAB_OVR_226__800aa6b4
     6::800aa688 00 00 a3 86     _lh        v1,0x0(s5)
     6::800aa68c 02 00 a8 86     lh         t0,0x2(s5)
     6::800aa690 c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa694 04 00 a9 86     _lh        t1,0x4(s5)
     6::800aa698 06 00 40 05     bltz       t2,LAB_OVR_226__800aa6b4
     6::800aa69c 00 00 c3 86     _lh        v1,0x0(s6)
     6::800aa6a0 02 00 c8 86     lh         t0,0x2(s6)
     6::800aa6a4 c6 a9 02 0c     jal        FUN_OVR_226__800aa718                            undefined FUN_OVR_226__800aa718()
     6::800aa6a8 04 00 c9 86     _lh        t1,0x4(s6)
     6::800aa6ac 58 00 3f 8c     lw         ra,0x58(at)
     6::800aa6b0 1c fd 41 05     bgez       t2,LAB_OVR_226__800a9b24
                             LAB_OVR_226__800aa6b4                           XREF[3]:     OVR_226::800aa670(j), 
                                                                                          OVR_226::800aa684(j), 
                                                                                          OVR_226::800aa698(j)  
     6::800aa6b4 10 00 2f 8c     lw         t7,0x10(at)
     6::800aa6b8 80 00 23 8c     lw         v1,0x80(at)
     6::800aa6bc a6 01 28 84     lh         t0,0x1a6(at)
     6::800aa6c0 a2 01 29 84     lh         t1,0x1a2(at)
     6::800aa6c4 04 00 fc ad     sw         gp=>DAT_80000000,0x4(t7)                         = ??
     6::800aa6c8 01 00 63 34     ori        v1,v1,0x1
     6::800aa6cc 00 00 e3 ad     sw         v1,0x0(t7)
     6::800aa6d0 08 00 e8 a5     sh         t0,0x8(t7)
     6::800aa6d4 0a 00 e9 a5     sh         t1,0xa(t7)
     6::800aa6d8 21 68 60 02     move       t5,s3
     6::800aa6dc d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa6e0 0c 00 f0 25     _addiu     s0,t7,0xc
     6::800aa6e4 21 68 80 02     move       t5,s4
     6::800aa6e8 d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa6ec 18 00 f0 25     _addiu     s0,t7,0x18
     6::800aa6f0 21 68 a0 02     move       t5,s5
     6::800aa6f4 d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa6f8 24 00 f0 25     _addiu     s0,t7,0x24
     6::800aa6fc 21 68 c0 02     move       t5,s6
     6::800aa700 d6 a9 02 0c     jal        FUN_OVR_226__800aa758                            undefined FUN_OVR_226__800aa758()
     6::800aa704 30 00 f0 25     _addiu     s0,t7,0x30
     6::800aa708 58 00 3f 8c     lw         ra,0x58(at)
     6::800aa70c 3c 00 ef 25     addiu      t7,t7,0x3c
     6::800aa710 08 00 e0 03     jr         ra
     6::800aa714 10 00 2f ac     _sw        t7,0x10(at)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aa718()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aa718                           XREF[7]:     FUN_OVR_226__800a9e7c:800aa5c4(c
                                                                                          FUN_OVR_226__800a9e7c:800aa5d8(c
                                                                                          FUN_OVR_226__800a9e7c:800aa5ec(c
                                                                                          FUN_OVR_226__800a9e7c:800aa668(c
                                                                                          FUN_OVR_226__800a9e7c:800aa67c(c
                                                                                          FUN_OVR_226__800a9e7c:800aa690(c
                                                                                          FUN_OVR_226__800a9e7c:800aa6a4(c
     6::800aa718 23 18 6f 00     subu       v1,v1,t7
     6::800aa71c 02 00 61 04     bgez       v1,LAB_OVR_226__800aa728
     6::800aa720 23 40 10 01     _subu      t0,t0,s0
     6::800aa724 22 18 03 00     sub        v1,zero,v1
                             LAB_OVR_226__800aa728                           XREF[1]:     OVR_226::800aa71c(j)  
     6::800aa728 00 ff 6b 24     addiu      t3,v1,-0x100
     6::800aa72c 02 00 01 05     bgez       t0,LAB_OVR_226__800aa738
     6::800aa730 23 48 31 01     _subu      t1,t1,s1
     6::800aa734 22 40 08 00     sub        t0,zero,t0
                             LAB_OVR_226__800aa738                           XREF[1]:     OVR_226::800aa72c(j)  
     6::800aa738 80 fe 0c 25     addiu      t4,t0,-0x180
     6::800aa73c 02 00 21 05     bgez       t1,LAB_OVR_226__800aa748
     6::800aa740 00 00 00 00     _nop
     6::800aa744 22 48 09 00     sub        t1,zero,t1
                             LAB_OVR_226__800aa748                           XREF[1]:     OVR_226::800aa73c(j)  
     6::800aa748 00 ff 2d 25     addiu      t5,t1,-0x100
     6::800aa74c 24 58 6c 01     and        t3,t3,t4
     6::800aa750 08 00 e0 03     jr         ra
     6::800aa754 24 50 6d 01     _and       t2,t3,t5
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aa758()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aa758                           XREF[7]:     FUN_OVR_226__800a9e7c:800aa620(c
                                                                                          FUN_OVR_226__800a9e7c:800aa62c(c
                                                                                          FUN_OVR_226__800a9e7c:800aa638(c
                                                                                          FUN_OVR_226__800a9e7c:800aa6dc(c
                                                                                          FUN_OVR_226__800a9e7c:800aa6e8(c
                                                                                          FUN_OVR_226__800a9e7c:800aa6f4(c
                                                                                          FUN_OVR_226__800a9e7c:800aa700(c
     6::800aa758 13 00 a3 81     lb         v1,0x13(t5)
     6::800aa75c 00 00 a8 8d     lw         t0,0x0(t5)
     6::800aa760 04 00 a9 8d     lw         t1,0x4(t5)
     6::800aa764 08 00 aa 8d     lw         t2,0x8(t5)
     6::800aa768 00 1e 03 00     sll        v1,v1,0x18
     6::800aa76c 25 50 43 01     or         t2,t2,v1
     6::800aa770 00 00 08 ae     sw         t0,0x0(s0)
     6::800aa774 04 00 09 ae     sw         t1,0x4(s0)
     6::800aa778 08 00 e0 03     jr         ra
     6::800aa77c 08 00 0a ae     _sw        t2,0x8(s0)
                             LAB_OVR_226__800aa780                           XREF[1]:     OVR_226::800aa848(j)  
     6::800aa780 a0 02 3f 8c     lw         ra,0x2a0(at)
     6::800aa784 00 00 00 00     nop
                             LAB_OVR_226__800aa788                           XREF[1]:     OVR_226::800aa794(j)  
     6::800aa788 08 00 e0 03     jr         ra
     6::800aa78c 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aa790()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aa790                           XREF[1]:     FUN_OVR_226__800a15c0:800a0eac(c
     6::800aa790 a0 02 3f ac     sw         ra,0x2a0(at)
     6::800aa794 fc ff f8 12     beq        s7,t8,LAB_OVR_226__800aa788
     6::800aa798 28 00 ab 8c     _lw        t3,0x28(a1)
     6::800aa79c 2c 00 ac 8c     lw         t4,0x2c(a1)
     6::800aa7a0 30 00 ad 8c     lw         t5,0x30(a1)
     6::800aa7a4 34 00 ae 8c     lw         t6,0x34(a1)
     6::800aa7a8 38 00 af 8c     lw         t7,0x38(a1)
     6::800aa7ac 3c 00 b0 8c     lw         s0,0x3c(a1)
     6::800aa7b0 40 00 b1 8c     lw         s1,0x40(a1)
     6::800aa7b4 44 00 b2 8c     lw         s2,0x44(a1)
     6::800aa7b8 00 40 cb 48     gte_ldL1   t3
     6::800aa7bc 00 48 cc 48     gte_ldL1   t4
     6::800aa7c0 00 50 cd 48     gte_ldL2   t5
     6::800aa7c4 00 58 ce 48     gte_ldL3   t6
     6::800aa7c8 00 60 cf 48     gte_ldL33  t7
     6::800aa7cc 00 68 d0        ldbkdir    s0,s1,s2
                 48 00 70 
                 d1 48 00 
     6::800aa7d8 20 00 a3 84     lh         v1,0x20(a1)
     6::800aa7dc 22 00 a8 84     lh         t0,0x22(a1)
     6::800aa7e0 18 00 be 8c     lw         s8,0x18(a1)
     6::800aa7e4 c0 1b 03 00     sll        v1,v1,0xf
     6::800aa7e8 c0 43 08 00     sll        t0,t0,0xf
     6::800aa7ec 00 c0 c3 48     gte_ldOFX  v1
     6::800aa7f0 00 c8 c8 48     gte_ldOFY  t0
     6::800aa7f4 00 d0 de 48     gte_ldH    s8
     6::800aa7f8 42 f0 1e 00     srl        s8,s8,0x1
     6::800aa7fc 01 00 de 27     addiu      s8,s8,0x1
     6::800aa800 08 02 3e a4     sh         s8,0x208(at)
     6::800aa804 1c 02 3e a4     sh         s8,0x21c(at)
     6::800aa808 30 02 3e a4     sh         s8,0x230(at)
     6::800aa80c 16 02 20 a4     sh         zero,0x216(at)
     6::800aa810 2a 02 20 a4     sh         zero,0x22a(at)
     6::800aa814 3e 02 20 a4     sh         zero,0x23e(at)
     6::800aa818 20 00 a3 8c     lw         v1,0x20(a1)
     6::800aa81c f4 00 a5 8c     lw         a1,0xf4(a1)
     6::800aa820 6c 00 23 ac     sw         v1,0x6c(at)
     6::800aa824 00 10 0b 24     li         t3,0x1000
     6::800aa828 00 00 cb 48     gte_ldR1   t3
     6::800aa82c 00 08 c0 48     gte_ldR1   zero
     6::800aa830 00 10 cb 48     gte_ldR2   t3
     6::800aa834 00 18 c0 48     gte_ldR3   zero
     6::800aa838 00 20 cb 48     gte_ldR33  t3
     6::800aa83c 00 28 c0        ldtr       zero,zero,zero
                 48 00 30 
                 c0 48 00 
                             LAB_OVR_226__800aa848                           XREF[24]:    OVR_226::800aa97c(j), 
                                                                                          OVR_226::800aa9b4(j), 
                                                                                          OVR_226::800aa9ec(j), 
                                                                                          OVR_226::800aaa20(j), 
                                                                                          OVR_226::800aaa58(j), 
                                                                                          OVR_226::800aaa8c(j), 
                                                                                          OVR_226::800aaac0(j), 
                                                                                          OVR_226::800aaac8(j), 
                                                                                          OVR_226::800aaf84(j), 
                                                                                          OVR_226::800aafcc(j), 
                                                                                          OVR_226::800ab024(j), 
                                                                                          OVR_226::800ab078(j), 
                                                                                          OVR_226::800ab0d0(j), 
                                                                                          OVR_226::800ab124(j), 
                                                                                          OVR_226::800ab184(j), 
                                                                                          OVR_226::800ab1b8(j), 
                                                                                          OVR_226::800ab200(j), 
                                                                                          OVR_226::800ab268(j), 
                                                                                          OVR_226::800ab2bc(j), 
                                                                                          OVR_226::800ab300(j), [more]
     6::800aa848 cd ff f8 12     beq        s7,t8,LAB_OVR_226__800aa780
     6::800aa84c 30 00 23 8c     _lw        v1,0x30(at)
     6::800aa850 68 0d 48 24     addiu      t0,v0,0xd68
     6::800aa854 23 18 68 00     subu       v1,v1,t0
     6::800aa858 96 d9 60 04     bltz       v1,LAB_OVR_226__800a0eb4
     6::800aa85c 0c 00 e0 ca     _gte_ldV   0xc(s7)
     6::800aa860 10 00 e1 ca     gte_ldVZ0  0x10(s7)
     6::800aa864 08 00 e8 86     lh         t0,0x8(s7)
     6::800aa868 0a 00 e9 86     lh         t1,0xa(s7)
     6::800aa86c 12 20 4a 4a     LLV0BK
     6::800aa870 a6 01 28 a4     sh         t0,0x1a6(at)
     6::800aa874 a2 01 29 a4     sh         t1,0x1a2(at)
     6::800aa878 12 00 e3 86     lh         v1,0x12(s7)
     6::800aa87c 14 00 e8 8e     lw         t0,0x14(s7)
     6::800aa880 ba 01 23 a4     sh         v1,0x1ba(at)
     6::800aa884 bc 01 28 ac     sw         t0,0x1bc(at)
     6::800aa888 00 48 0b 48     gte_stIR1  t3
     6::800aa88c 00 50 0c 48     gte_stIR2  t4
     6::800aa890 00 58 0d 48     gte_stIR3  t5
     6::800aa894 b4 01 2b a4     sh         t3,0x1b4(at)
     6::800aa898 b6 01 2c a4     sh         t4,0x1b6(at)
     6::800aa89c b8 01 2d a4     sh         t5,0x1b8(at)
     6::800aa8a0 18 00 e0 ca     gte_ldVXY0 0x18(s7)
     6::800aa8a4 1c 00 e1 ca     gte_ldVZ0  0x1c(s7)
     6::800aa8a8 1e 00 e3 86     lh         v1,0x1e(s7)
     6::800aa8ac 20 00 e8 8e     lw         t0,0x20(s7)
     6::800aa8b0 12 20 4a 4a     LLV0BK
     6::800aa8b4 ce 01 23 a4     sh         v1,0x1ce(at)
     6::800aa8b8 d0 01 28 ac     sw         t0,0x1d0(at)
     6::800aa8bc 04 00 fc 8e     lw         gp,0x4(s7)
     6::800aa8c0 00 48 0b 48     gte_stIR1  t3
     6::800aa8c4 00 50 0c 48     gte_stIR2  t4
     6::800aa8c8 00 58 0d 48     gte_stIR3  t5
     6::800aa8cc c8 01 2b a4     sh         t3,0x1c8(at)
     6::800aa8d0 ca 01 2c a4     sh         t4,0x1ca(at)
     6::800aa8d4 cc 01 2d a4     sh         t5,0x1cc(at)
     6::800aa8d8 24 00 e0 ca     gte_ldVXY0 0x24(s7)
     6::800aa8dc 28 00 e1 ca     gte_ldVZ0  0x28(s7)
     6::800aa8e0 00 00 e9 8e     lw         t1,0x0(s7)
     6::800aa8e4 2a 00 e3 86     lh         v1,0x2a(s7)
     6::800aa8e8 12 20 4a 4a     LLV0BK
     6::800aa8ec 2c 00 e8 8e     lw         t0,0x2c(s7)
     6::800aa8f0 e2 01 23 a4     sh         v1,0x1e2(at)
     6::800aa8f4 e4 01 28 ac     sw         t0,0x1e4(at)
     6::800aa8f8 00 48 0b 48     gte_stIR1  t3
     6::800aa8fc 00 50 0c 48     gte_stIR2  t4
     6::800aa900 00 58 0d 48     gte_stIR3  t5
     6::800aa904 dc 01 2b a4     sh         t3,0x1dc(at)
     6::800aa908 de 01 2c a4     sh         t4,0x1de(at)
     6::800aa90c e0 01 2d a4     sh         t5,0x1e0(at)
     6::800aa910 01 00 23 31     andi       v1,t1,0x1
     6::800aa914 6f 01 60 14     bne        v1,zero,LAB_OVR_226__800aaed4
     6::800aa918 7c 00 29 ac     _sw        t1,0x7c(at)
     6::800aa91c b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aa920 b4 01 2d 24     _addiu     t5,at,0x1b4
     6::800aa924 b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aa928 c8 01 2d 24     _addiu     t5,at,0x1c8
     6::800aa92c b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aa930 dc 01 2d 24     _addiu     t5,at,0x1dc
     6::800aa934 bf 01 23 80     lb         v1,0x1bf(at)
     6::800aa938 d3 01 28 80     lb         t0,0x1d3(at)
     6::800aa93c e7 01 29 80     lb         t1,0x1e7(at)
     6::800aa940 80 18 03 00     sll        v1,v1,0x2
     6::800aa944 c0 40 08 00     sll        t0,t0,0x3
     6::800aa948 00 49 09 00     sll        t1,t1,0x4
     6::800aa94c 25 18 68 00     or         v1,v1,t0
     6::800aa950 25 18 69 00     or         v1,v1,t1
     6::800aa954 21 18 61 00     addu       v1,v1,at
     6::800aa958 40 02 63 8c     lw         v1,0x240(v1)
     6::800aa95c bf 01 20 a0     sb         zero,0x1bf(at)
     6::800aa960 d3 01 20 a0     sb         zero,0x1d3(at)
     6::800aa964 08 00 60 00     jr         v1
     6::800aa968 e7 01 20 a0     _sb        zero,0x1e7(at)
                             LAB_OVR_226__800aa96c                           XREF[2]:     FUN_OVR_226__800ab3dc:800ab3f4(*
                                                                                          OVR_226::800ab910(*)  
     6::800aa96c b4 01 33 24     addiu      s3,at,0x1b4
     6::800aa970 c8 01 34 24     addiu      s4,at,0x1c8
     6::800aa974 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800aa978 dc 01 35 24     _addiu     s5,at,0x1dc
     6::800aa97c b2 ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aa980 30 00 f7 26     _addiu     s7,s7,0x30
                             LAB_OVR_226__800aa984                           XREF[2]:     FUN_OVR_226__800ab3dc:800ab3f4(*
                                                                                          OVR_226::800ab914(*)  
     6::800aa984 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800aa988 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800aa98c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aa990 04 02 2f 24     _addiu     t7,at,0x204
     6::800aa994 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800aa998 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aa99c 18 02 2f 24     _addiu     t7,at,0x218
     6::800aa9a0 c8 01 33 24     addiu      s3,at,0x1c8
     6::800aa9a4 dc 01 34 24     addiu      s4,at,0x1dc
     6::800aa9a8 04 02 35 24     addiu      s5,at,0x204
     6::800aa9ac 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800aa9b0 18 02 36 24     _addiu     s6,at,0x218
     6::800aa9b4 a4 ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aa9b8 30 00 f7 26     _addiu     s7,s7,0x30
     6::800aa9bc dc 01 2d 24     addiu      t5,at,0x1dc
     6::800aa9c0 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800aa9c4 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aa9c8 04 02 2f 24     _addiu     t7,at,0x204
     6::800aa9cc b4 01 2d 24     addiu      t5,at,0x1b4
     6::800aa9d0 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aa9d4 18 02 2f 24     _addiu     t7,at,0x218
     6::800aa9d8 dc 01 33 24     addiu      s3,at,0x1dc
     6::800aa9dc b4 01 34 24     addiu      s4,at,0x1b4
     6::800aa9e0 04 02 35 24     addiu      s5,at,0x204
     6::800aa9e4 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800aa9e8 18 02 36 24     _addiu     s6,at,0x218
     6::800aa9ec 96 ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aa9f0 30 00 f7 26     _addiu     s7,s7,0x30
     6::800aa9f4 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800aa9f8 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800aa9fc c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaa00 04 02 2f 24     _addiu     t7,at,0x204
     6::800aaa04 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800aaa08 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaa0c 18 02 2f 24     _addiu     t7,at,0x218
     6::800aaa10 dc 01 33 24     addiu      s3,at,0x1dc
     6::800aaa14 18 02 34 24     addiu      s4,at,0x218
     6::800aaa18 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800aaa1c 04 02 35 24     _addiu     s5,at,0x204
     6::800aaa20 89 ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aaa24 30 00 f7 26     _addiu     s7,s7,0x30
     6::800aaa28 b4 01 2d 24     addiu      t5,at,0x1b4
     6::800aaa2c dc 01 2e 24     addiu      t6,at,0x1dc
     6::800aaa30 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaa34 04 02 2f 24     _addiu     t7,at,0x204
     6::800aaa38 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800aaa3c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaa40 18 02 2f 24     _addiu     t7,at,0x218
     6::800aaa44 b4 01 33 24     addiu      s3,at,0x1b4
     6::800aaa48 c8 01 34 24     addiu      s4,at,0x1c8
     6::800aaa4c 04 02 35 24     addiu      s5,at,0x204
     6::800aaa50 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800aaa54 18 02 36 24     _addiu     s6,at,0x218
     6::800aaa58 7b ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aaa5c 30 00 f7 26     _addiu     s7,s7,0x30
     6::800aaa60 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800aaa64 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800aaa68 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaa6c 04 02 2f 24     _addiu     t7,at,0x204
     6::800aaa70 dc 01 2e 24     addiu      t6,at,0x1dc
     6::800aaa74 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaa78 18 02 2f 24     _addiu     t7,at,0x218
     6::800aaa7c c8 01 33 24     addiu      s3,at,0x1c8
     6::800aaa80 18 02 34 24     addiu      s4,at,0x218
     6::800aaa84 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800aaa88 04 02 35 24     _addiu     s5,at,0x204
     6::800aaa8c 6e ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aaa90 30 00 f7 26     _addiu     s7,s7,0x30
     6::800aaa94 b4 01 2d 24     addiu      t5,at,0x1b4
     6::800aaa98 dc 01 2e 24     addiu      t6,at,0x1dc
     6::800aaa9c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaaa0 04 02 2f 24     _addiu     t7,at,0x204
     6::800aaaa4 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800aaaa8 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaaac 18 02 2f 24     _addiu     t7,at,0x218
     6::800aaab0 b4 01 33 24     addiu      s3,at,0x1b4
     6::800aaab4 18 02 34 24     addiu      s4,at,0x218
     6::800aaab8 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800aaabc 04 02 35 24     _addiu     s5,at,0x204
     6::800aaac0 61 ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aaac4 30 00 f7 26     _addiu     s7,s7,0x30
     6::800aaac8 5f ff 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aaacc 30 00 f7 26     _addiu     s7,s7,0x30
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aaad0()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aaad0                           XREF[7]:     FUN_OVR_226__800aa790:800aa91c(c
                                                                                          FUN_OVR_226__800aa790:800aa924(c
                                                                                          FUN_OVR_226__800aa790:800aa92c(c
                                                                                          FUN_OVR_226__800aa790:800aaf08(c
                                                                                          FUN_OVR_226__800aa790:800aaf10(c
                                                                                          FUN_OVR_226__800aa790:800aaf18(c
                                                                                          FUN_OVR_226__800aa790:800aaf20(c
     6::800aaad0 04 00 b2 85     lh         s2,0x4(t5)
     6::800aaad4 02 00 b1 85     lh         s1,0x2(t5)
     6::800aaad8 00 00 b0 85     lh         s0,0x0(t5)
     6::800aaadc 23 18 5e 02     subu       v1,s2,s8
     6::800aaae0 40 80 10 00     sll        s0,s0,0x1
     6::800aaae4 40 88 11 00     sll        s1,s1,0x1
     6::800aaae8 40 90 12 00     sll        s2,s2,0x1
     6::800aaaec 0c 00 b0 a5     sh         s0,0xc(t5)
     6::800aaaf0 0e 00 b1 a5     sh         s1,0xe(t5)
     6::800aaaf4 10 00 b2 a5     sh         s2,0x10(t5)
     6::800aaaf8 08 00 e0 03     jr         ra
     6::800aaafc 12 00 a3 a5     _sh        v1,0x12(t5)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aab00()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aab00                           XREF[52]:    OVR_226::800aa98c(c), 
                                                                                          OVR_226::800aa998(c), 
                                                                                          OVR_226::800aa9c4(c), 
                                                                                          OVR_226::800aa9d0(c), 
                                                                                          OVR_226::800aa9fc(c), 
                                                                                          OVR_226::800aaa08(c), 
                                                                                          OVR_226::800aaa30(c), 
                                                                                          OVR_226::800aaa3c(c), 
                                                                                          OVR_226::800aaa68(c), 
                                                                                          OVR_226::800aaa74(c), 
                                                                                          OVR_226::800aaa9c(c), 
                                                                                          OVR_226::800aaaa8(c), 
                                                                                          OVR_226::800aaf94(c), 
                                                                                          OVR_226::800aafa0(c), 
                                                                                          OVR_226::800aafdc(c), 
                                                                                          OVR_226::800aafe8(c), 
                                                                                          OVR_226::800aaff4(c), 
                                                                                          OVR_226::800ab034(c), 
                                                                                          OVR_226::800ab040(c), 
                                                                                          OVR_226::800ab04c(c), [more]
     6::800aab00 10 00 a3 85     lh         v1,0x10(t5)
     6::800aab04 10 00 c8 85     lh         t0,0x10(t6)
     6::800aab08 23 48 c3 03     subu       t1,s8,v1
     6::800aab0c 23 50 03 01     subu       t2,t0,v1
     6::800aab10 00 4c 09 00     sll        t1,t1,0x10
     6::800aab14 1a 00 2a 01     div        t1,t2
     6::800aab18 0c 00 a3 85     lh         v1,0xc(t5)
     6::800aab1c 0c 00 c8 85     lh         t0,0xc(t6)
     6::800aab20 12 50 00 00     mflo       t2
     6::800aab24 23 48 03 01     subu       t1,t0,v1
     6::800aab28 0e 00 c8 85     lh         t0,0xe(t6)
     6::800aab2c 18 00 2a 01     mult       t1,t2
     6::800aab30 12 48 00 00     mflo       t1
     6::800aab34 03 4c 09 00     sra        t1,t1,0x10
     6::800aab38 21 48 23 01     addu       t1,t1,v1
     6::800aab3c 0e 00 a3 85     lh         v1,0xe(t5)
     6::800aab40 00 00 e9 a5     sh         t1,0x0(t7)
     6::800aab44 23 48 03 01     subu       t1,t0,v1
     6::800aab48 18 00 2a 01     mult       t1,t2
     6::800aab4c 06 00 c8 91     lbu        t0,0x6(t6)
     6::800aab50 12 48 00 00     mflo       t1
     6::800aab54 03 4c 09 00     sra        t1,t1,0x10
     6::800aab58 21 48 23 01     addu       t1,t1,v1
     6::800aab5c 06 00 a3 91     lbu        v1,0x6(t5)
     6::800aab60 02 00 e9 a5     sh         t1,0x2(t7)
     6::800aab64 23 48 03 01     subu       t1,t0,v1
     6::800aab68 18 00 2a 01     mult       t1,t2
     6::800aab6c 07 00 c8 91     lbu        t0,0x7(t6)
     6::800aab70 12 48 00 00     mflo       t1
     6::800aab74 03 4c 09 00     sra        t1,t1,0x10
     6::800aab78 21 48 23 01     addu       t1,t1,v1
     6::800aab7c 07 00 a3 91     lbu        v1,0x7(t5)
     6::800aab80 06 00 e9 a1     sb         t1,0x6(t7)
     6::800aab84 23 48 03 01     subu       t1,t0,v1
     6::800aab88 18 00 2a 01     mult       t1,t2
     6::800aab8c 08 00 c8 91     lbu        t0,0x8(t6)
     6::800aab90 12 48 00 00     mflo       t1
     6::800aab94 03 4c 09 00     sra        t1,t1,0x10
     6::800aab98 21 48 23 01     addu       t1,t1,v1
     6::800aab9c 08 00 a3 91     lbu        v1,0x8(t5)
     6::800aaba0 07 00 e9 a1     sb         t1,0x7(t7)
     6::800aaba4 23 48 03 01     subu       t1,t0,v1
     6::800aaba8 18 00 2a 01     mult       t1,t2
     6::800aabac 09 00 c8 91     lbu        t0,0x9(t6)
     6::800aabb0 12 48 00 00     mflo       t1
     6::800aabb4 03 4c 09 00     sra        t1,t1,0x10
     6::800aabb8 21 48 23 01     addu       t1,t1,v1
     6::800aabbc 09 00 a3 91     lbu        v1,0x9(t5)
     6::800aabc0 08 00 e9 a1     sb         t1,0x8(t7)
     6::800aabc4 23 48 03 01     subu       t1,t0,v1
     6::800aabc8 18 00 2a 01     mult       t1,t2
     6::800aabcc 0a 00 c8 91     lbu        t0,0xa(t6)
     6::800aabd0 12 48 00 00     mflo       t1
     6::800aabd4 03 4c 09 00     sra        t1,t1,0x10
     6::800aabd8 21 48 23 01     addu       t1,t1,v1
     6::800aabdc 0a 00 a3 91     lbu        v1,0xa(t5)
     6::800aabe0 09 00 e9 a1     sb         t1,0x9(t7)
     6::800aabe4 23 48 03 01     subu       t1,t0,v1
     6::800aabe8 18 00 2a 01     mult       t1,t2
     6::800aabec 12 48 00 00     mflo       t1
     6::800aabf0 03 4c 09 00     sra        t1,t1,0x10
     6::800aabf4 21 48 23 01     addu       t1,t1,v1
     6::800aabf8 08 00 e0 03     jr         ra
     6::800aabfc 0a 00 e9 a1     _sb        t1,0xa(t7)
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aac00()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aac00                           XREF[15]:    OVR_226::800aa974(c), 
                                                                                          OVR_226::800aaa18(c), 
                                                                                          OVR_226::800aaa84(c), 
                                                                                          OVR_226::800aaab8(c), 
                                                                                          FUN_OVR_226__800aad44:800aae04(j
                                                                                          OVR_226::800aafb0(c), 
                                                                                          OVR_226::800ab070(c), 
                                                                                          OVR_226::800ab108(c), 
                                                                                          OVR_226::800ab150(c), 
                                                                                          OVR_226::800ab17c(c), 
                                                                                          OVR_226::800ab1b0(c), 
                                                                                          OVR_226::800ab1e4(c), 
                                                                                          OVR_226::800ab2a0(c), 
                                                                                          OVR_226::800ab34c(c), 
                                                                                          OVR_226::800ab3c4(c)  

// PrimMem and OTMem for triangles (not quads) right under camera,
// setting this to jr ra makes the game not draw some triangles VERY close to the camera

     6::800aac00 12 00 63 86     lh         v1,0x12(s3)
     6::800aac04 12 00 88 86     lh         t0,0x12(s4)
     6::800aac08 12 00 a9 86     lh         t1,0x12(s5)
     6::800aac0c 00 00 60 ca     gte_ldVXY0 0x0(s3)
     6::800aac10 03 00 61 04     bgez       v1,LAB_OVR_226__800aac20
     6::800aac14 04 00 61 ca     _gte_ldVZ0 0x4(s3)
     6::800aac18 0c 00 60 ca     gte_ldVXY0 0xc(s3)
     6::800aac1c 10 00 61 ca     gte_ldVZ0  0x10(s3)
                             LAB_OVR_226__800aac20                           XREF[1]:     OVR_226::800aac10(j)  
     6::800aac20 00 00 82 ca     gte_ldVXY1 0x0(s4)
     6::800aac24 03 00 01 05     bgez       t0,LAB_OVR_226__800aac34
     6::800aac28 04 00 83 ca     _gte_ldVZ1 0x4(s4)
     6::800aac2c 0c 00 82 ca     gte_ldVXY1 0xc(s4)
     6::800aac30 10 00 83 ca     gte_ldVZ1  0x10(s4)
                             LAB_OVR_226__800aac34                           XREF[1]:     OVR_226::800aac24(j)  
     6::800aac34 00 00 a4 ca     gte_ldVXY2 0x0(s5)
     6::800aac38 03 00 21 05     bgez       t1,LAB_OVR_226__800aac48
     6::800aac3c 04 00 a5 ca     _gte_ldVZ2 0x4(s5)
     6::800aac40 0c 00 a4 ca     gte_ldVXY2 0xc(s5)
     6::800aac44 10 00 a5 ca     gte_ldVZ2  0x10(s5)
                             LAB_OVR_226__800aac48                           XREF[1]:     OVR_226::800aac38(j)  
     6::800aac48 06 00 63 86     lh         v1,0x6(s3)
     6::800aac4c 06 00 88 86     lh         t0,0x6(s4)
     6::800aac50 30 00 28 4a     RTPT
     6::800aac54 06 00 a9 86     lh         t1,0x6(s5)
     6::800aac58 a0 01 23 a4     sh         v1,0x1a0(at)
     6::800aac5c a4 01 28 a4     sh         t0,0x1a4(at)
     6::800aac60 a8 01 29 a4     sh         t1,0x1a8(at)
     6::800aac64 6c 00 23 8c     lw         v1,0x6c(at)
     6::800aac68 00 60 0b        read_sxs   t3,t4,t5
                 48 00 68 
                 0c 48 00 
     6::800aac74 06 00 40 4b     NCLIP
     6::800aac78 23 78 63 01     subu       t7,t3,v1
     6::800aac7c 23 80 83 01     subu       s0,t4,v1
     6::800aac80 23 88 a3 01     subu       s1,t5,v1
     6::800aac84 24 18 6c 01     and        v1,t3,t4
     6::800aac88 24 18 6d 00     and        v1,v1,t5
     6::800aac8c 25 78 f0 01     or         t7,t7,s0
     6::800aac90 27 78 f1 01     nor        t7,t7,s1
     6::800aac94 25 78 e3 01     or         t7,t7,v1
     6::800aac98 28 00 e0 05     bltz       t7,LAB_OVR_226__800aad3c
     6::800aac9c 00 7c 0f 00     _sll       t7,t7,0x10
     6::800aaca0 26 00 e0 05     bltz       t7,LAB_OVR_226__800aad3c
     6::800aaca4 00 c0 0a 48     _gte_stM   t2
     6::800aaca8 7c 00 29 8c     lw         t1,0x7c(at)
     6::800aacac 23 00 40 11     beq        t2,zero,LAB_OVR_226__800aad3c
     6::800aacb0 40 40 09 00     _sll       t0,t1,0x1
     6::800aacb4 02 00 20 05     bltz       t1,LAB_OVR_226__800aacc0
     6::800aacb8 26 50 48 01     _xor       t2,t2,t0
     6::800aacbc 1f 00 40 19     blez       t2,LAB_OVR_226__800aad3c
                             LAB_OVR_226__800aacc0                           XREF[1]:     OVR_226::800aacb4(j)  
     6::800aacc0 a4 01 28 8c     _lw        t0,0x1a4(at)
     6::800aacc4 08 00 6f 8e     lw         t7,0x8(s3)
     6::800aacc8 08 00 90 8e     lw         s0,0x8(s4)
     6::800aaccc 08 00 b1 8e     lw         s1,0x8(s5)
     6::800aacd0 60 00 03 3c     lui        v1,0x60
     6::800aacd4 24 48 03 01     and        t1,t0,v1
     6::800aacd8 02 00 23 15     bne        t1,v1,LAB_OVR_226__800aace4
     6::800aacdc 00 36 03 3c     _lui       v1,0x3600
     6::800aace0 00 34 03 3c     lui        v1,0x3400
                             LAB_OVR_226__800aace4                           XREF[1]:     OVR_226::800aacd8(j)  
     6::800aace4 25 78 e3 01     or         t7,t7,v1
     6::800aace8 a0 01 23 8c     lw         v1,0x1a0(at)
     6::800aacec a8 01 29 8c     lw         t1,0x1a8(at)
     6::800aacf0 04 00 4f ac     sw         t7,0x4(v0)
     6::800aacf4 08 00 4b ac     sw         t3,0x8(v0)
     6::800aacf8 0c 00 43 ac     sw         v1,0xc(v0)
     6::800aacfc 10 00 50 ac     sw         s0,0x10(v0)
     6::800aad00 14 00 4c ac     sw         t4,0x14(v0)
     6::800aad04 18 00 48 ac     sw         t0,0x18(v0)
     6::800aad08 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800aad0c 20 00 4d ac     sw         t5,0x20(v0)
     6::800aad10 24 00 49 ac     sw         t1,0x24(v0)
     6::800aad14 00 09 0a 3c     lui        t2,0x900
     6::800aad18 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800aad1c 00 42 02 00     sll        t0,v0,0x8
     6::800aad20 02 42 08 00     srl        t0,t0,0x8
     6::800aad24 25 18 6a 00     or         v1,v1,t2
     6::800aad28 00 00 43 ac     sw         v1,0x0(v0)
     6::800aad2c 28 00 42 24     addiu      v0,v0,0x28
     6::800aad30 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800aad34 08 00 e0 03     jr         ra
     6::800aad38 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800aad3c                           XREF[6]:     OVR_226::800aac98(j), 
                                                                                          OVR_226::800aaca0(j), 
                                                                                          OVR_226::800aacac(j), 
                                                                                          OVR_226::800aacbc(j), 
                                                                                          FUN_OVR_226__800aad44:800aae38(j
                                                                                          FUN_OVR_226__800aad44:800aae40(j
     6::800aad3c 08 00 e0 03     jr         ra
     6::800aad40 00 00 00 00     _nop
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800aad44()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800aad44                           XREF[18]:    OVR_226::800aa9ac(c), 
                                                                                          OVR_226::800aa9e4(c), 
                                                                                          OVR_226::800aaa50(c), 
                                                                                          OVR_226::800aaf7c(c), 
                                                                                          OVR_226::800aafc4(c), 
                                                                                          OVR_226::800ab008(c), 
                                                                                          OVR_226::800ab01c(c), 
                                                                                          OVR_226::800ab060(c), 
                                                                                          OVR_226::800ab0b4(c), 
                                                                                          OVR_226::800ab0c8(c), 
                                                                                          OVR_226::800ab11c(c), 
                                                                                          OVR_226::800ab1f8(c), 
                                                                                          OVR_226::800ab230(c), 
                                                                                          OVR_226::800ab260(c), 
                                                                                          OVR_226::800ab2b4(c), 
                                                                                          OVR_226::800ab2f8(c), 
                                                                                          OVR_226::800ab33c(c), 
                                                                                          OVR_226::800ab390(c)  

// PrimMem and OTMem for quads (not triangles) under camera,
// settings this to jr ra makes the game not draw a lot of polygons VERY close to the camera
     6::800aad44 12 00 63 86     lh         v1,0x12(s3)
     6::800aad48 12 00 88 86     lh         t0,0x12(s4)
     6::800aad4c 12 00 a9 86     lh         t1,0x12(s5)
     6::800aad50 00 00 60 ca     gte_ldVXY0 0x0(s3)
     6::800aad54 03 00 61 04     bgez       v1,LAB_OVR_226__800aad64
     6::800aad58 04 00 61 ca     _gte_ldVZ0 0x4(s3)
     6::800aad5c 0c 00 60 ca     gte_ldVXY0 0xc(s3)
     6::800aad60 10 00 61 ca     gte_ldVZ0  0x10(s3)
                             LAB_OVR_226__800aad64                           XREF[1]:     OVR_226::800aad54(j)  
     6::800aad64 00 00 82 ca     gte_ldVXY1 0x0(s4)
     6::800aad68 03 00 01 05     bgez       t0,LAB_OVR_226__800aad78
     6::800aad6c 04 00 83 ca     _gte_ldVZ1 0x4(s4)
     6::800aad70 0c 00 82 ca     gte_ldVXY1 0xc(s4)
     6::800aad74 10 00 83 ca     gte_ldVZ1  0x10(s4)
                             LAB_OVR_226__800aad78                           XREF[1]:     OVR_226::800aad68(j)  
     6::800aad78 00 00 a4 ca     gte_ldVXY2 0x0(s5)
     6::800aad7c 03 00 21 05     bgez       t1,LAB_OVR_226__800aad8c
     6::800aad80 04 00 a5 ca     _gte_ldVZ2 0x4(s5)
     6::800aad84 0c 00 a4 ca     gte_ldVXY2 0xc(s5)
     6::800aad88 10 00 a5 ca     gte_ldVZ2  0x10(s5)
                             LAB_OVR_226__800aad8c                           XREF[1]:     OVR_226::800aad7c(j)  
     6::800aad8c 06 00 63 86     lh         v1,0x6(s3)
     6::800aad90 06 00 88 86     lh         t0,0x6(s4)
     6::800aad94 30 00 28 4a     RTPT
     6::800aad98 06 00 a9 86     lh         t1,0x6(s5)
     6::800aad9c a0 01 23 a4     sh         v1,0x1a0(at)
     6::800aada0 a4 01 28 a4     sh         t0,0x1a4(at)
     6::800aada4 a8 01 29 a4     sh         t1,0x1a8(at)
     6::800aada8 6c 00 23 8c     lw         v1,0x6c(at)
     6::800aadac 00 60 0b        read_sxs   t3,t4,t5
                 48 00 68 
                 0c 48 00 
     6::800aadb8 06 00 40 4b     NCLIP
     6::800aadbc 23 78 63 01     subu       t7,t3,v1
     6::800aadc0 23 80 83 01     subu       s0,t4,v1
     6::800aadc4 23 88 a3 01     subu       s1,t5,v1
     6::800aadc8 00 c0 0a 48     gte_stMAC0 t2
     6::800aadcc 7c 00 29 8c     lw         t1,0x7c(at)
     6::800aadd0 12 00 c3 86     lh         v1,0x12(s6)
     6::800aadd4 0a 00 40 11     beq        t2,zero,LAB_OVR_226__800aae00
     6::800aadd8 00 00 c0 ca     _gte_ldV   0x0(s6)
     6::800aaddc 03 00 61 04     bgez       v1,LAB_OVR_226__800aadec
     6::800aade0 04 00 c1 ca     _gte_ldVZ0 0x4(s6)
     6::800aade4 0c 00 c0 ca     gte_ldVXY0 0xc(s6)
     6::800aade8 10 00 c1 ca     gte_ldVZ0  0x10(s6)
                             LAB_OVR_226__800aadec                           XREF[1]:     OVR_226::800aaddc(j)  
     6::800aadec 07 00 20 05     bltz       t1,LAB_OVR_226__800aae0c
     6::800aadf0 40 48 09 00     _sll       t1,t1,0x1
     6::800aadf4 26 50 49 01     xor        t2,t2,t1
     6::800aadf8 04 00 40 1d     bgtz       t2,LAB_OVR_226__800aae0c
     6::800aadfc 00 00 00 00     _nop
                             LAB_OVR_226__800aae00                           XREF[1]:     OVR_226::800aadd4(j)  
     6::800aae00 21 98 80 02     move       s3,s4
     6::800aae04 7e ff 01 04     bgez       zero,FUN_OVR_226__800aac00
     6::800aae08 21 a0 c0 02     _move      s4,s6
                             LAB_OVR_226__800aae0c                           XREF[2]:     OVR_226::800aadec(j), 
                                                                                          OVR_226::800aadf8(j)  
     6::800aae0c 01 00 18 4a     RTPS
     6::800aae10 6c 00 23 8c     lw         v1,0x6c(at)
     6::800aae14 25 78 f0 01     or         t7,t7,s0
     6::800aae18 00 70 0e 48     gte_stSXY2 t6
     6::800aae1c 25 78 f1 01     or         t7,t7,s1
     6::800aae20 23 90 c3 01     subu       s2,t6,v1
     6::800aae24 27 78 f2 01     nor        t7,t7,s2
     6::800aae28 24 18 6c 01     and        v1,t3,t4
     6::800aae2c 24 18 6d 00     and        v1,v1,t5
     6::800aae30 24 18 6e 00     and        v1,v1,t6
     6::800aae34 25 78 e3 01     or         t7,t7,v1
     6::800aae38 c0 ff e0 05     bltz       t7,LAB_OVR_226__800aad3c
     6::800aae3c 00 7c 0f 00     _sll       t7,t7,0x10
     6::800aae40 be ff e0 05     bltz       t7,LAB_OVR_226__800aad3c
     6::800aae44 a4 01 28 8c     _lw        t0,0x1a4(at)
     6::800aae48 06 00 ca 86     lh         t2,0x6(s6)
     6::800aae4c 08 00 6f 8e     lw         t7,0x8(s3)
     6::800aae50 08 00 90 8e     lw         s0,0x8(s4)
     6::800aae54 08 00 b1 8e     lw         s1,0x8(s5)
     6::800aae58 08 00 d2 8e     lw         s2,0x8(s6)
     6::800aae5c 60 00 03 3c     lui        v1,0x60
     6::800aae60 24 48 03 01     and        t1,t0,v1
     6::800aae64 02 00 23 15     bne        t1,v1,LAB_OVR_226__800aae70
     6::800aae68 00 3e 03 3c     _lui       v1,0x3e00
     6::800aae6c 00 3c 03 3c     lui        v1,0x3c00
                             LAB_OVR_226__800aae70                           XREF[1]:     OVR_226::800aae64(j)  
     6::800aae70 25 78 e3 01     or         t7,t7,v1
     6::800aae74 a0 01 23 8c     lw         v1,0x1a0(at)
     6::800aae78 a8 01 29 8c     lw         t1,0x1a8(at)
     6::800aae7c 04 00 4f ac     sw         t7,0x4(v0)
     6::800aae80 08 00 4b ac     sw         t3,0x8(v0)
     6::800aae84 0c 00 43 ac     sw         v1,0xc(v0)
     6::800aae88 10 00 50 ac     sw         s0,0x10(v0)
     6::800aae8c 14 00 4c ac     sw         t4,0x14(v0)
     6::800aae90 18 00 48 ac     sw         t0,0x18(v0)
     6::800aae94 1c 00 51 ac     sw         s1,0x1c(v0)
     6::800aae98 20 00 4d ac     sw         t5,0x20(v0)
     6::800aae9c 24 00 49 ac     sw         t1,0x24(v0)
     6::800aaea0 28 00 52 ac     sw         s2,0x28(v0)
     6::800aaea4 2c 00 4e ac     sw         t6,0x2c(v0)
     6::800aaea8 30 00 4a ac     sw         t2,0x30(v0)
     6::800aaeac 00 0c 0a 3c     lui        t2,0xc00
     6::800aaeb0 00 00 83 8f     lw         v1,0x0(gp)=>DAT_80000000                         = ??
     6::800aaeb4 00 42 02 00     sll        t0,v0,0x8
     6::800aaeb8 02 42 08 00     srl        t0,t0,0x8
     6::800aaebc 25 18 6a 00     or         v1,v1,t2
     6::800aaec0 00 00 43 ac     sw         v1,0x0(v0)
     6::800aaec4 34 00 42 24     addiu      v0,v0,0x34
     6::800aaec8 00 00 88 af     sw         t0,0x0(gp)=>DAT_80000000                         = ??
     6::800aaecc 08 00 e0 03     jr         ra
     6::800aaed0 01 00 bd 23     _addi      sp,sp,0x1
                             LAB_OVR_226__800aaed4                           XREF[1]:     OVR_226::800aa914(j)  
     6::800aaed4 30 00 e0 ca     gte_ldVXY0 0x30(s7)
     6::800aaed8 34 00 e1 ca     gte_ldVZ0  0x34(s7)
     6::800aaedc 36 00 e3 86     lh         v1,0x36(s7)
     6::800aaee0 38 00 e8 8e     lw         t0,0x38(s7)
     6::800aaee4 12 20 4a 4a     LLV0BK
     6::800aaee8 f6 01 23 a4     sh         v1,0x1f6(at)
     6::800aaeec f8 01 28 ac     sw         t0,0x1f8(at)
     6::800aaef0 00 48 0b 48     gte_stIR1  t3
     6::800aaef4 00 50 0c 48     gte_stIR2  t4
     6::800aaef8 00 58 0d 48     gte_stIR3  t5
     6::800aaefc f0 01 2b a4     sh         t3,0x1f0(at)
     6::800aaf00 f2 01 2c a4     sh         t4,0x1f2(at)
     6::800aaf04 f4 01 2d a4     sh         t5,0x1f4(at)
     6::800aaf08 b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aaf0c b4 01 2d 24     _addiu     t5,at,0x1b4
     6::800aaf10 b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aaf14 c8 01 2d 24     _addiu     t5,at,0x1c8
     6::800aaf18 b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aaf1c dc 01 2d 24     _addiu     t5,at,0x1dc
     6::800aaf20 b4 aa 02 0c     jal        FUN_OVR_226__800aaad0                            undefined FUN_OVR_226__800aaad0()
     6::800aaf24 f0 01 2d 24     _addiu     t5,at,0x1f0
     6::800aaf28 bf 01 23 80     lb         v1,0x1bf(at)
     6::800aaf2c d3 01 28 80     lb         t0,0x1d3(at)
     6::800aaf30 e7 01 29 80     lb         t1,0x1e7(at)
     6::800aaf34 fb 01 2a 80     lb         t2,0x1fb(at)
     6::800aaf38 80 18 03 00     sll        v1,v1,0x2
     6::800aaf3c c0 40 08 00     sll        t0,t0,0x3
     6::800aaf40 00 49 09 00     sll        t1,t1,0x4
     6::800aaf44 40 51 0a 00     sll        t2,t2,0x5
     6::800aaf48 25 18 68 00     or         v1,v1,t0
     6::800aaf4c 25 18 69 00     or         v1,v1,t1
     6::800aaf50 25 18 6a 00     or         v1,v1,t2
     6::800aaf54 21 18 61 00     addu       v1,v1,at
     6::800aaf58 60 02 63 8c     lw         v1,0x260(v1)
     6::800aaf5c bf 01 20 a0     sb         zero,0x1bf(at)
     6::800aaf60 d3 01 20 a0     sb         zero,0x1d3(at)
     6::800aaf64 e7 01 20 a0     sb         zero,0x1e7(at)
     6::800aaf68 08 00 60 00     jr         v1
     6::800aaf6c fb 01 20 a0     _sb        zero,0x1fb(at)
     6::800aaf70 b4 01 33 24     addiu      s3,at,0x1b4
     6::800aaf74 c8 01 34 24     addiu      s4,at,0x1c8
     6::800aaf78 dc 01 35 24     addiu      s5,at,0x1dc
     6::800aaf7c 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800aaf80 f0 01 36 24     _addiu     s6,at,0x1f0
     6::800aaf84 30 fe 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aaf88 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800aaf8c c8 01 2d 24     addiu      t5,at,0x1c8
     6::800aaf90 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800aaf94 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaf98 04 02 2f 24     _addiu     t7,at,0x204
     6::800aaf9c dc 01 2d 24     addiu      t5,at,0x1dc
     6::800aafa0 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aafa4 18 02 2f 24     _addiu     t7,at,0x218
     6::800aafa8 f0 01 33 24     addiu      s3,at,0x1f0
     6::800aafac dc 01 34 24     addiu      s4,at,0x1dc
     6::800aafb0 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800aafb4 c8 01 35 24     _addiu     s5,at,0x1c8
     6::800aafb8 c8 01 33 24     addiu      s3,at,0x1c8
     6::800aafbc dc 01 34 24     addiu      s4,at,0x1dc
     6::800aafc0 04 02 35 24     addiu      s5,at,0x204
     6::800aafc4 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800aafc8 18 02 36 24     _addiu     s6,at,0x218
     6::800aafcc 1e fe 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800aafd0 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800aafd4 f0 01 2d 24     addiu      t5,at,0x1f0
     6::800aafd8 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800aafdc c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aafe0 04 02 2f 24     _addiu     t7,at,0x204
     6::800aafe4 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800aafe8 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aafec 18 02 2f 24     _addiu     t7,at,0x218
     6::800aaff0 b4 01 2d 24     addiu      t5,at,0x1b4
     6::800aaff4 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800aaff8 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800aaffc f0 01 33 24     addiu      s3,at,0x1f0
     6::800ab000 dc 01 34 24     addiu      s4,at,0x1dc
     6::800ab004 04 02 35 24     addiu      s5,at,0x204
     6::800ab008 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab00c 18 02 36 24     _addiu     s6,at,0x218
     6::800ab010 dc 01 33 24     addiu      s3,at,0x1dc
     6::800ab014 b4 01 34 24     addiu      s4,at,0x1b4
     6::800ab018 18 02 35 24     addiu      s5,at,0x218
     6::800ab01c 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab020 2c 02 36 24     _addiu     s6,at,0x22c
     6::800ab024 08 fe 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab028 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab02c f0 01 2d 24     addiu      t5,at,0x1f0
     6::800ab030 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab034 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab038 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab03c dc 01 2d 24     addiu      t5,at,0x1dc
     6::800ab040 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab044 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab048 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800ab04c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab050 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab054 f0 01 33 24     addiu      s3,at,0x1f0
     6::800ab058 dc 01 34 24     addiu      s4,at,0x1dc
     6::800ab05c 04 02 35 24     addiu      s5,at,0x204
     6::800ab060 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab064 18 02 36 24     _addiu     s6,at,0x218
     6::800ab068 dc 01 33 24     addiu      s3,at,0x1dc
     6::800ab06c 2c 02 34 24     addiu      s4,at,0x22c
     6::800ab070 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab074 18 02 35 24     _addiu     s5,at,0x218
     6::800ab078 f3 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab07c 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab080 b4 01 2d 24     addiu      t5,at,0x1b4
     6::800ab084 dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab088 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab08c 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab090 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab094 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab098 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab09c f0 01 2d 24     addiu      t5,at,0x1f0
     6::800ab0a0 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab0a4 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab0a8 b4 01 33 24     addiu      s3,at,0x1b4
     6::800ab0ac c8 01 34 24     addiu      s4,at,0x1c8
     6::800ab0b0 04 02 35 24     addiu      s5,at,0x204
     6::800ab0b4 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab0b8 18 02 36 24     _addiu     s6,at,0x218
     6::800ab0bc c8 01 33 24     addiu      s3,at,0x1c8
     6::800ab0c0 f0 01 34 24     addiu      s4,at,0x1f0
     6::800ab0c4 18 02 35 24     addiu      s5,at,0x218
     6::800ab0c8 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab0cc 2c 02 36 24     _addiu     s6,at,0x22c
     6::800ab0d0 dd fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab0d4 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab0d8 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab0dc b4 01 2e 24     addiu      t6,at,0x1b4
     6::800ab0e0 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab0e4 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab0e8 dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab0ec c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab0f0 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab0f4 f0 01 2d 24     addiu      t5,at,0x1f0
     6::800ab0f8 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab0fc 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab100 c8 01 33 24     addiu      s3,at,0x1c8
     6::800ab104 18 02 34 24     addiu      s4,at,0x218
     6::800ab108 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab10c 04 02 35 24     _addiu     s5,at,0x204
     6::800ab110 c8 01 33 24     addiu      s3,at,0x1c8
     6::800ab114 f0 01 34 24     addiu      s4,at,0x1f0
     6::800ab118 18 02 35 24     addiu      s5,at,0x218
     6::800ab11c 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab120 2c 02 36 24     _addiu     s6,at,0x22c
     6::800ab124 c8 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab128 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab12c b4 01 2d 24     addiu      t5,at,0x1b4
     6::800ab130 dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab134 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab138 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab13c c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab140 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab144 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab148 b4 01 33 24     addiu      s3,at,0x1b4
     6::800ab14c 18 02 34 24     addiu      s4,at,0x218
     6::800ab150 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab154 04 02 35 24     _addiu     s5,at,0x204
     6::800ab158 f0 01 2d 24     addiu      t5,at,0x1f0
     6::800ab15c dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab160 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab164 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab168 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab16c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab170 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab174 f0 01 33 24     addiu      s3,at,0x1f0
     6::800ab178 18 02 34 24     addiu      s4,at,0x218
     6::800ab17c 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab180 04 02 35 24     _addiu     s5,at,0x204
     6::800ab184 b0 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab188 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab18c f0 01 2d 24     addiu      t5,at,0x1f0
     6::800ab190 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab194 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab198 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab19c dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab1a0 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab1a4 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab1a8 f0 01 33 24     addiu      s3,at,0x1f0
     6::800ab1ac 18 02 34 24     addiu      s4,at,0x218
     6::800ab1b0 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab1b4 04 02 35 24     _addiu     s5,at,0x204
     6::800ab1b8 a3 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab1bc 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab1c0 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800ab1c4 f0 01 2e 24     addiu      t6,at,0x1f0
     6::800ab1c8 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab1cc 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab1d0 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab1d4 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab1d8 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab1dc b4 01 33 24     addiu      s3,at,0x1b4
     6::800ab1e0 c8 01 34 24     addiu      s4,at,0x1c8
     6::800ab1e4 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab1e8 dc 01 35 24     _addiu     s5,at,0x1dc
     6::800ab1ec dc 01 33 24     addiu      s3,at,0x1dc
     6::800ab1f0 c8 01 34 24     addiu      s4,at,0x1c8
     6::800ab1f4 04 02 35 24     addiu      s5,at,0x204
     6::800ab1f8 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab1fc 18 02 36 24     _addiu     s6,at,0x218
     6::800ab200 91 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab204 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab208 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab20c b4 01 2e 24     addiu      t6,at,0x1b4
     6::800ab210 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab214 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab218 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800ab21c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab220 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab224 c8 01 33 24     addiu      s3,at,0x1c8
     6::800ab228 dc 01 34 24     addiu      s4,at,0x1dc
     6::800ab22c 04 02 35 24     addiu      s5,at,0x204
     6::800ab230 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab234 18 02 36 24     _addiu     s6,at,0x218
     6::800ab238 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab23c f0 01 2e 24     addiu      t6,at,0x1f0
     6::800ab240 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab244 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab248 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800ab24c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab250 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab254 c8 01 33 24     addiu      s3,at,0x1c8
     6::800ab258 dc 01 34 24     addiu      s4,at,0x1dc
     6::800ab25c 04 02 35 24     addiu      s5,at,0x204
     6::800ab260 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab264 18 02 36 24     _addiu     s6,at,0x218
     6::800ab268 77 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab26c 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab270 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800ab274 f0 01 2e 24     addiu      t6,at,0x1f0
     6::800ab278 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab27c 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab280 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab284 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab288 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab28c b4 01 2d 24     addiu      t5,at,0x1b4
     6::800ab290 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab294 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab298 dc 01 33 24     addiu      s3,at,0x1dc
     6::800ab29c 18 02 34 24     addiu      s4,at,0x218
     6::800ab2a0 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab2a4 04 02 35 24     _addiu     s5,at,0x204
     6::800ab2a8 dc 01 33 24     addiu      s3,at,0x1dc
     6::800ab2ac b4 01 34 24     addiu      s4,at,0x1b4
     6::800ab2b0 18 02 35 24     addiu      s5,at,0x218
     6::800ab2b4 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab2b8 2c 02 36 24     _addiu     s6,at,0x22c
     6::800ab2bc 62 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab2c0 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab2c4 dc 01 2d 24     addiu      t5,at,0x1dc
     6::800ab2c8 f0 01 2e 24     addiu      t6,at,0x1f0
     6::800ab2cc c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab2d0 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab2d4 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab2d8 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab2dc 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab2e0 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800ab2e4 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab2e8 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab2ec 04 02 33 24     addiu      s3,at,0x204
     6::800ab2f0 dc 01 34 24     addiu      s4,at,0x1dc
     6::800ab2f4 18 02 35 24     addiu      s5,at,0x218
     6::800ab2f8 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab2fc 2c 02 36 24     _addiu     s6,at,0x22c
     6::800ab300 51 fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab304 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab308 b4 01 2d 24     addiu      t5,at,0x1b4
     6::800ab30c dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab310 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab314 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab318 c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab31c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab320 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab324 f0 01 2e 24     addiu      t6,at,0x1f0
     6::800ab328 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab32c 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab330 b4 01 33 24     addiu      s3,at,0x1b4
     6::800ab334 c8 01 34 24     addiu      s4,at,0x1c8
     6::800ab338 04 02 35 24     addiu      s5,at,0x204
     6::800ab33c 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab340 18 02 36 24     _addiu     s6,at,0x218
     6::800ab344 c8 01 33 24     addiu      s3,at,0x1c8
     6::800ab348 2c 02 34 24     addiu      s4,at,0x22c
     6::800ab34c 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab350 18 02 35 24     _addiu     s5,at,0x218
     6::800ab354 3c fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab358 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab35c c8 01 2d 24     addiu      t5,at,0x1c8
     6::800ab360 b4 01 2e 24     addiu      t6,at,0x1b4
     6::800ab364 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab368 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab36c dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab370 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab374 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab378 f0 01 2e 24     addiu      t6,at,0x1f0
     6::800ab37c c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab380 2c 02 2f 24     _addiu     t7,at,0x22c
     6::800ab384 04 02 33 24     addiu      s3,at,0x204
     6::800ab388 c8 01 34 24     addiu      s4,at,0x1c8
     6::800ab38c 18 02 35 24     addiu      s5,at,0x218
     6::800ab390 51 ab 02 0c     jal        FUN_OVR_226__800aad44                            undefined FUN_OVR_226__800aad44()
     6::800ab394 2c 02 36 24     _addiu     s6,at,0x22c
     6::800ab398 2b fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab39c 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab3a0 b4 01 2d 24     addiu      t5,at,0x1b4
     6::800ab3a4 dc 01 2e 24     addiu      t6,at,0x1dc
     6::800ab3a8 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab3ac 04 02 2f 24     _addiu     t7,at,0x204
     6::800ab3b0 c8 01 2e 24     addiu      t6,at,0x1c8
     6::800ab3b4 c0 aa 02 0c     jal        FUN_OVR_226__800aab00                            undefined FUN_OVR_226__800aab00()
     6::800ab3b8 18 02 2f 24     _addiu     t7,at,0x218
     6::800ab3bc b4 01 33 24     addiu      s3,at,0x1b4
     6::800ab3c0 18 02 34 24     addiu      s4,at,0x218
     6::800ab3c4 00 ab 02 0c     jal        FUN_OVR_226__800aac00                            undefined FUN_OVR_226__800aac00()
     6::800ab3c8 04 02 35 24     _addiu     s5,at,0x204
     6::800ab3cc 1e fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab3d0 3c 00 f7 26     _addiu     s7,s7,0x3c
     6::800ab3d4 1c fd 01 04     bgez       zero,LAB_OVR_226__800aa848
     6::800ab3d8 3c 00 f7 26     _addiu     s7,s7,0x3c
                             **************************************************************
                             *                                                            *
                             *  FUNCTION                                                  *
                             **************************************************************
                             undefined FUN_OVR_226__800ab3dc()
                               assume gp = 0x80000000
             undefined         v0:1           <RETURN>
                             FUN_OVR_226__800ab3dc                           XREF[1]:     FUN_OVR_226__800a15c0:800a0e98(c
     6::800ab3dc 0b 80 03 3c     lui        v1,0x800b
     6::800ab3e0 10 b9 63 24     addiu      v1,v1,-0x46f0
     6::800ab3e4 40 02 28 24     addiu      t0,at,0x240
     6::800ab3e8 18 00 09 24     li         t1,0x18
                             LAB_OVR_226__800ab3ec                           XREF[1]:     OVR_226::800ab3fc(j)  
     6::800ab3ec 00 00 6a 8c     lw         t2,0x0(v1)=>PTR_LAB_OVR_226__800aa96c_OVR_226_   = OVR_226::800aa984
                                                                                             = OVR_226::800aa96c
     6::800ab3f0 04 00 63 24     addiu      v1,v1,0x4
     6::800ab3f4 00 00 0a ad     sw         t2=>LAB_OVR_226__800aa96c,0x0(t0)
     6::800ab3f8 04 00 08 25     addiu      t0,t0,0x4
     6::800ab3fc fb ff 20 15     bne        t1,zero,LAB_OVR_226__800ab3ec
     6::800ab400 ff ff 29 25     _addiu     t1,t1,-0x1
     6::800ab404 08 00 e0 03     jr         ra
                             LAB_OVR_226__800ab408                           XREF[1]:     FUN_OVR_226__800a15c0:800a0e30(R
     6::800ab408 00 00 00 00     _nop
     6::800ab40c ac b8 0a 80     lb         t2,-0x4754(zero)
     6::800ab410 48 b8 0a 80     lb         t2,-0x47b8(zero)
     6::800ab414 e4 b7 0a 80     lb         t2,-0x481c(zero)
     6::800ab418 80 b7 0a 80     lb         t2,-0x4880(zero)
     6::800ab41c 1c b7 0a 80     lb         t2,-0x48e4(zero)
     6::800ab420 b8 b6 0a 80     lb         t2,-0x4948(zero)
     6::800ab424 54 b6 0a 80     lb         t2,-0x49ac(zero)
     6::800ab428 f0 b5 0a 80     lb         t2,-0x4a10(zero)
     6::800ab42c 8c b5 0a 80     lb         t2,-0x4a74(zero)
     6::800ab430 28 b5 0a 80     lb         t2,-0x4ad8(zero)
                             PTR_DAT_OVR_226__800ab4c4_OVR_226__800ab434     XREF[2]:     FUN_OVR_226__800a15c0:800a0e30(R
                                                                                          FUN_OVR_226__800a15c0:800a0e40(R
     6::800ab434 c4 b4 0a 80     addr       DAT_OVR_226__800ab4c4                            = 0000000Eh
     6::800ab438 c8 97 0a 80     addr       LAB_OVR_226__800a97c8
     6::800ab43c 60 8b 0a 80     addr       LAB_OVR_226__800a8b60
     6::800ab440 a8 7b 0a 80     addr       LAB_OVR_226__800a7ba8
     6::800ab444 40 6f 0a 80     addr       LAB_OVR_226__800a6f40
     6::800ab448 5c 5e 0a 80     addr       LAB_OVR_226__800a5e5c
     6::800ab44c a0 4f 0a 80     addr       LAB_OVR_226__800a4fa0
     6::800ab450 7c 41 0a 80     addr       LAB_OVR_226__800a417c
     6::800ab454 a8 36 0a 80     addr       LAB_OVR_226__800a36a8
     6::800ab458 04 29 0a 80     addr       LAB_OVR_226__800a2904
     6::800ab45c 30 1e 0a 80     addr       LAB_OVR_226__800a1e30
                             PTR_LAB_OVR_226__800a0ef4_OVR_226__800ab460     XREF[1]:     FUN_OVR_226__800a15c0:800a0e40(R
     6::800ab460 f4 0e 0a 80     addr       LAB_OVR_226__800a0ef4
                             DAT_OVR_226__800ab464                           XREF[1]:     OVR_226::800a0dec(R)  
     6::800ab464 00 08 10 18     undefined4 18100800h
                             DAT_OVR_226__800ab468                           XREF[1]:     OVR_226::800a0dec(R)  
     6::800ab468 18 08 90 80     undefined4 80900818h
     6::800ab46c 18              ??         18h
     6::800ab46d 10              ??         10h
     6::800ab46e 08              ??         08h
     6::800ab46f 00              ??         00h
     6::800ab470 00              ??         00h
     6::800ab471 10              ??         10h
     6::800ab472 88              ??         88h
     6::800ab473 98              ??         98h
     6::800ab474 00              ??         00h
     6::800ab475 10              ??         10h
     6::800ab476 08              ??         08h
     6::800ab477 98              ??         98h
     6::800ab478 18              ??         18h
     6::800ab479 10              ??         10h
     6::800ab47a 88              ??         88h
     6::800ab47b 00              ??         00h
     6::800ab47c 18              ??         18h                                              ?  ->  80100818
     6::800ab47d 08              ??         08h
     6::800ab47e 10              ??         10h
     6::800ab47f 80              ??         80h
     6::800ab480 00              ??         00h
     6::800ab481 08              ??         08h
     6::800ab482 90              ??         90h
     6::800ab483 18              ??         18h
     6::800ab484 98              ??         98h
     6::800ab485 18              ??         18h
     6::800ab486 08              ??         08h
     6::800ab487 10              ??         10h
     6::800ab488 10              ??         10h
     6::800ab489 18              ??         18h
     6::800ab48a 88              ??         88h
     6::800ab48b 88              ??         88h
     6::800ab48c 10              ??         10h
     6::800ab48d 08              ??         08h
     6::800ab48e 18              ??         18h
     6::800ab48f 18              ??         18h
     6::800ab490 88              ??         88h
     6::800ab491 08              ??         08h
     6::800ab492 98              ??         98h
     6::800ab493 90              ??         90h
     6::800ab494 88              ??         88h
     6::800ab495 08              ??         08h
     6::800ab496 18              ??         18h
     6::800ab497 90              ??         90h
     6::800ab498 10              ??         10h
     6::800ab499 08              ??         08h
     6::800ab49a 98              ??         98h
     6::800ab49b 18              ??         18h
     6::800ab49c 10              ??         10h
     6::800ab49d 18              ??         18h
     6::800ab49e 08              ??         08h
     6::800ab49f 88              ??         88h
     6::800ab4a0 98              ??         98h
     6::800ab4a1 18              ??         18h
     6::800ab4a2 88              ??         88h
     6::800ab4a3 10              ??         10h
     6::800ab4a4 90              ??         90h
     6::800ab4a5 10              ??         10h
     6::800ab4a6 18              ??         18h
     6::800ab4a7 08              ??         08h
     6::800ab4a8 08              ??         08h
     6::800ab4a9 10              ??         10h
     6::800ab4aa 98              ??         98h
     6::800ab4ab 98              ??         98h
     6::800ab4ac 08              ??         08h
     6::800ab4ad 18              ??         18h
     6::800ab4ae 10              ??         10h
     6::800ab4af 10              ??         10h
     6::800ab4b0 98              ??         98h
     6::800ab4b1 18              ??         18h
     6::800ab4b2 90              ??         90h
     6::800ab4b3 88              ??         88h
     6::800ab4b4 98              ??         98h
     6::800ab4b5 18              ??         18h
     6::800ab4b6 10              ??         10h
     6::800ab4b7 88              ??         88h
     6::800ab4b8 08              ??         08h
     6::800ab4b9 18              ??         18h
     6::800ab4ba 90              ??         90h
     6::800ab4bb 10              ??         10h
     6::800ab4bc 08              ??         08h
     6::800ab4bd 10              ??         10h
     6::800ab4be 18              ??         18h
     6::800ab4bf 98              ??         98h
     6::800ab4c0 90              ??         90h
     6::800ab4c1 10              ??         10h
     6::800ab4c2 98              ??         98h
     6::800ab4c3 08              ??         08h
                             DAT_OVR_226__800ab4c4                           XREF[2]:     FUN_OVR_226__800a15c0:800a0e44(R
                                                                                          OVR_226::800ab434(*)  
     6::800ab4c4 0e 00 00 00     undefined4 0000000Eh
                             PTR_PTR_LAB_OVR_226__800a15d4_OVR_226__800ab4e  XREF[1]:     FUN_OVR_226__800a15c0:800a0e48(R
     6::800ab4c8 e0 b4 0a 80     addr       PTR_LAB_OVR_226__800a15d4_OVR_226__800ab4e0      = OVR_226::800a15d4
                             DAT_OVR_226__800ab4cc                           XREF[1]:     FUN_OVR_226__800a15c0:800a0e4c(R
     6::800ab4cc 4c 01 00 00     undefined4 0000014Ch
                             DAT_OVR_226__800ab4d0                           XREF[1]:     FUN_OVR_226__800a15c0:800a0e44(R
     6::800ab4d0 02 00 00 00     undefined4 00000002h
                             PTR_PTR_LAB_OVR_226__800a1ce8_OVR_226__800ab51  XREF[1]:     FUN_OVR_226__800a15c0:800a0e48(R
     6::800ab4d4 1c b5 0a 80     addr       PTR_LAB_OVR_226__800a1ce8_OVR_226__800ab51c      = OVR_226::800a1ce8
                             DAT_OVR_226__800ab4d8                           XREF[1]:     FUN_OVR_226__800a15c0:800a0e4c(R
     6::800ab4d8 88 01 00 00     undefined4 00000188h
     6::800ab4dc 00              ??         00h
     6::800ab4dd 00              ??         00h
     6::800ab4de 00              ??         00h
     6::800ab4df 00              ??         00h
                             PTR_LAB_OVR_226__800a15d4_OVR_226__800ab4e0     XREF[2]:     FUN_OVR_226__800a15c0:800a0e58(R
                                                                                          OVR_226::800ab4c8(*)  
     6::800ab4e0 d4 15 0a 80     addr       LAB_OVR_226__800a15d4
                             PTR_LAB_OVR_226__800a1614_OVR_226__800ab4e4     XREF[1]:     FUN_OVR_226__800a15c0:800a0e58(R
     6::800ab4e4 14 16 0a 80     addr       LAB_OVR_226__800a1614
     6::800ab4e8 94              ??         94h                                              ?  ->  OVR_226::800a1694
     6::800ab4e9 16              ??         16h
     6::800ab4ea 0a              ??         0Ah
     6::800ab4eb 80              ??         80h
     6::800ab4ec 34              ??         34h    4                                         ?  ->  OVR_226::800a1634
     6::800ab4ed 16              ??         16h
     6::800ab4ee 0a              ??         0Ah
     6::800ab4ef 80              ??         80h
     6::800ab4f0 bc              ??         BCh                                              ?  ->  OVR_226::800a16bc
     6::800ab4f1 16              ??         16h
     6::800ab4f2 0a              ??         0Ah
     6::800ab4f3 80              ??         80h
     6::800ab4f4 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab4f5 17              ??         17h
     6::800ab4f6 0a              ??         0Ah
     6::800ab4f7 80              ??         80h
     6::800ab4f8 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab4f9 17              ??         17h
     6::800ab4fa 0a              ??         0Ah
     6::800ab4fb 80              ??         80h
     6::800ab4fc 54              ??         54h    T                                         ?  ->  OVR_226::800a1654
     6::800ab4fd 16              ??         16h
     6::800ab4fe 0a              ??         0Ah
     6::800ab4ff 80              ??         80h
     6::800ab500 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab501 17              ??         17h
     6::800ab502 0a              ??         0Ah
     6::800ab503 80              ??         80h
     6::800ab504 e4              ??         E4h                                              ?  ->  OVR_226::800a16e4
     6::800ab505 16              ??         16h
     6::800ab506 0a              ??         0Ah
     6::800ab507 80              ??         80h
     6::800ab508 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab509 17              ??         17h
     6::800ab50a 0a              ??         0Ah
     6::800ab50b 80              ??         80h
     6::800ab50c 0c              ??         0Ch                                              ?  ->  OVR_226::800a170c
     6::800ab50d 17              ??         17h
     6::800ab50e 0a              ??         0Ah
     6::800ab50f 80              ??         80h
     6::800ab510 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab511 17              ??         17h
     6::800ab512 0a              ??         0Ah
     6::800ab513 80              ??         80h
     6::800ab514 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab515 17              ??         17h
     6::800ab516 0a              ??         0Ah
     6::800ab517 80              ??         80h
     6::800ab518 34              ??         34h    4                                         ?  ->  OVR_226::800a1734
     6::800ab519 17              ??         17h
     6::800ab51a 0a              ??         0Ah
     6::800ab51b 80              ??         80h
                             PTR_LAB_OVR_226__800a1ce8_OVR_226__800ab51c     XREF[1]:     OVR_226::800ab4d4(*)  
     6::800ab51c e8 1c 0a 80     addr       LAB_OVR_226__800a1ce8
     6::800ab520 e0              ??         E0h                                              ?  ->  OVR_226::800a1ce0
     6::800ab521 1c              ??         1Ch
     6::800ab522 0a              ??         0Ah
     6::800ab523 80              ??         80h
     6::800ab524 6c              ??         6Ch    l                                         ?  ->  OVR_226::800a1d6c
     6::800ab525 1d              ??         1Dh
     6::800ab526 0a              ??         0Ah
     6::800ab527 80              ??         80h
     6::800ab528 0e              ??         0Eh
     6::800ab529 00              ??         00h
     6::800ab52a 00              ??         00h
     6::800ab52b 00              ??         00h
     6::800ab52c 44              ??         44h    D                                         ?  ->  OVR_226::800ab544
     6::800ab52d b5              ??         B5h
     6::800ab52e 0a              ??         0Ah
     6::800ab52f 80              ??         80h
     6::800ab530 4c              ??         4Ch    L
     6::800ab531 01              ??         01h
     6::800ab532 00              ??         00h
     6::800ab533 00              ??         00h
     6::800ab534 02              ??         02h
     6::800ab535 00              ??         00h
     6::800ab536 00              ??         00h
     6::800ab537 00              ??         00h
     6::800ab538 80              ??         80h                                              ?  ->  OVR_226::800ab580
     6::800ab539 b5              ??         B5h
     6::800ab53a 0a              ??         0Ah
     6::800ab53b 80              ??         80h
     6::800ab53c 88              ??         88h
     6::800ab53d 01              ??         01h
     6::800ab53e 00              ??         00h
     6::800ab53f 00              ??         00h
     6::800ab540 00              ??         00h
     6::800ab541 00              ??         00h
     6::800ab542 00              ??         00h
     6::800ab543 00              ??         00h
     6::800ab544 44              ??         44h    D                                         ?  ->  OVR_226::800a2344
     6::800ab545 23              ??         23h    #
     6::800ab546 0a              ??         0Ah
     6::800ab547 80              ??         80h
     6::800ab548 84              ??         84h                                              ?  ->  OVR_226::800a2384
     6::800ab549 23              ??         23h    #
     6::800ab54a 0a              ??         0Ah
     6::800ab54b 80              ??         80h
     6::800ab54c 04              ??         04h                                              ?  ->  OVR_226::800a2404
     6::800ab54d 24              ??         24h    $
     6::800ab54e 0a              ??         0Ah
     6::800ab54f 80              ??         80h
     6::800ab550 a4              ??         A4h                                              ?  ->  OVR_226::800a23a4
     6::800ab551 23              ??         23h    #
     6::800ab552 0a              ??         0Ah
     6::800ab553 80              ??         80h
     6::800ab554 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a242c
     6::800ab555 24              ??         24h    $
     6::800ab556 0a              ??         0Ah
     6::800ab557 80              ??         80h
     6::800ab558 a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab559 24              ??         24h    $
     6::800ab55a 0a              ??         0Ah
     6::800ab55b 80              ??         80h
     6::800ab55c a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab55d 24              ??         24h    $
     6::800ab55e 0a              ??         0Ah
     6::800ab55f 80              ??         80h
     6::800ab560 c4              ??         C4h                                              ?  ->  OVR_226::800a23c4
     6::800ab561 23              ??         23h    #
     6::800ab562 0a              ??         0Ah
     6::800ab563 80              ??         80h
     6::800ab564 a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab565 24              ??         24h    $
     6::800ab566 0a              ??         0Ah
     6::800ab567 80              ??         80h
     6::800ab568 54              ??         54h    T                                         ?  ->  OVR_226::800a2454
     6::800ab569 24              ??         24h    $
     6::800ab56a 0a              ??         0Ah
     6::800ab56b 80              ??         80h
     6::800ab56c a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab56d 24              ??         24h    $
     6::800ab56e 0a              ??         0Ah
     6::800ab56f 80              ??         80h
     6::800ab570 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a247c
     6::800ab571 24              ??         24h    $
     6::800ab572 0a              ??         0Ah
     6::800ab573 80              ??         80h
     6::800ab574 a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab575 24              ??         24h    $
     6::800ab576 0a              ??         0Ah
     6::800ab577 80              ??         80h
     6::800ab578 a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab579 24              ??         24h    $
     6::800ab57a 0a              ??         0Ah
     6::800ab57b 80              ??         80h
     6::800ab57c a4              ??         A4h                                              ?  ->  OVR_226::800a24a4
     6::800ab57d 24              ??         24h    $
     6::800ab57e 0a              ??         0Ah
     6::800ab57f 80              ??         80h
     6::800ab580 dc              ??         DCh                                              ?  ->  OVR_226::800a27dc
     6::800ab581 27              ??         27h    '
     6::800ab582 0a              ??         0Ah
     6::800ab583 80              ??         80h
     6::800ab584 d4              ??         D4h                                              ?  ->  OVR_226::800a27d4
     6::800ab585 27              ??         27h    '
     6::800ab586 0a              ??         0Ah
     6::800ab587 80              ??         80h
     6::800ab588 50              ??         50h    P                                         ?  ->  OVR_226::800a2850
     6::800ab589 28              ??         28h    (
     6::800ab58a 0a              ??         0Ah
     6::800ab58b 80              ??         80h
     6::800ab58c 0e              ??         0Eh
     6::800ab58d 00              ??         00h
     6::800ab58e 00              ??         00h
     6::800ab58f 00              ??         00h
     6::800ab590 a8              ??         A8h                                              ?  ->  OVR_226::800ab5a8
     6::800ab591 b5              ??         B5h
     6::800ab592 0a              ??         0Ah
     6::800ab593 80              ??         80h
     6::800ab594 4c              ??         4Ch    L
     6::800ab595 01              ??         01h
     6::800ab596 00              ??         00h
     6::800ab597 00              ??         00h
     6::800ab598 02              ??         02h
     6::800ab599 00              ??         00h
     6::800ab59a 00              ??         00h
     6::800ab59b 00              ??         00h
     6::800ab59c e4              ??         E4h                                              ?  ->  OVR_226::800ab5e4
     6::800ab59d b5              ??         B5h
     6::800ab59e 0a              ??         0Ah
     6::800ab59f 80              ??         80h
     6::800ab5a0 88              ??         88h
     6::800ab5a1 01              ??         01h
     6::800ab5a2 00              ??         00h
     6::800ab5a3 00              ??         00h
     6::800ab5a4 00              ??         00h
     6::800ab5a5 00              ??         00h
     6::800ab5a6 00              ??         00h
     6::800ab5a7 00              ??         00h
     6::800ab5a8 40              ??         40h    @                                         ?  ->  OVR_226::800a2e40
     6::800ab5a9 2e              ??         2Eh    .
     6::800ab5aa 0a              ??         0Ah
     6::800ab5ab 80              ??         80h
     6::800ab5ac 80              ??         80h                                              ?  ->  OVR_226::800a2e80
     6::800ab5ad 2e              ??         2Eh    .
     6::800ab5ae 0a              ??         0Ah
     6::800ab5af 80              ??         80h
     6::800ab5b0 00              ??         00h                                              ?  ->  OVR_226::800a2f00
     6::800ab5b1 2f              ??         2Fh    /
     6::800ab5b2 0a              ??         0Ah
     6::800ab5b3 80              ??         80h
     6::800ab5b4 a0              ??         A0h                                              ?  ->  OVR_226::800a2ea0
     6::800ab5b5 2e              ??         2Eh    .
     6::800ab5b6 0a              ??         0Ah
     6::800ab5b7 80              ??         80h
     6::800ab5b8 28              ??         28h    (                                         ?  ->  OVR_226::800a2f28
     6::800ab5b9 2f              ??         2Fh    /
     6::800ab5ba 0a              ??         0Ah
     6::800ab5bb 80              ??         80h
     6::800ab5bc a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5bd 2f              ??         2Fh    /
     6::800ab5be 0a              ??         0Ah
     6::800ab5bf 80              ??         80h
     6::800ab5c0 a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5c1 2f              ??         2Fh    /
     6::800ab5c2 0a              ??         0Ah
     6::800ab5c3 80              ??         80h
     6::800ab5c4 c0              ??         C0h                                              ?  ->  OVR_226::800a2ec0
     6::800ab5c5 2e              ??         2Eh    .
     6::800ab5c6 0a              ??         0Ah
     6::800ab5c7 80              ??         80h
     6::800ab5c8 a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5c9 2f              ??         2Fh    /
     6::800ab5ca 0a              ??         0Ah
     6::800ab5cb 80              ??         80h
     6::800ab5cc 50              ??         50h    P                                         ?  ->  OVR_226::800a2f50
     6::800ab5cd 2f              ??         2Fh    /
     6::800ab5ce 0a              ??         0Ah
     6::800ab5cf 80              ??         80h
     6::800ab5d0 a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5d1 2f              ??         2Fh    /
     6::800ab5d2 0a              ??         0Ah
     6::800ab5d3 80              ??         80h
     6::800ab5d4 78              ??         78h    x                                         ?  ->  OVR_226::800a2f78
     6::800ab5d5 2f              ??         2Fh    /
     6::800ab5d6 0a              ??         0Ah
     6::800ab5d7 80              ??         80h
     6::800ab5d8 a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5d9 2f              ??         2Fh    /
     6::800ab5da 0a              ??         0Ah
     6::800ab5db 80              ??         80h
     6::800ab5dc a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5dd 2f              ??         2Fh    /
     6::800ab5de 0a              ??         0Ah
     6::800ab5df 80              ??         80h
     6::800ab5e0 a0              ??         A0h                                              ?  ->  OVR_226::800a2fa0
     6::800ab5e1 2f              ??         2Fh    /
     6::800ab5e2 0a              ??         0Ah
     6::800ab5e3 80              ??         80h
     6::800ab5e4 3c              ??         3Ch    <                                         ?  ->  OVR_226::800a333c
     6::800ab5e5 33              ??         33h    3
     6::800ab5e6 0a              ??         0Ah
     6::800ab5e7 80              ??         80h
     6::800ab5e8 34              ??         34h    4                                         ?  ->  OVR_226::800a3334
     6::800ab5e9 33              ??         33h    3
     6::800ab5ea 0a              ??         0Ah
     6::800ab5eb 80              ??         80h
     6::800ab5ec e0              ??         E0h                                              ?  ->  OVR_226::800a33e0
     6::800ab5ed 33              ??         33h    3
     6::800ab5ee 0a              ??         0Ah
     6::800ab5ef 80              ??         80h
     6::800ab5f0 0e              ??         0Eh
     6::800ab5f1 00              ??         00h
     6::800ab5f2 00              ??         00h
     6::800ab5f3 00              ??         00h
     6::800ab5f4 0c              ??         0Ch                                              ?  ->  OVR_226::800ab60c
     6::800ab5f5 b6              ??         B6h
     6::800ab5f6 0a              ??         0Ah
     6::800ab5f7 80              ??         80h
     6::800ab5f8 4c              ??         4Ch    L
     6::800ab5f9 01              ??         01h
     6::800ab5fa 00              ??         00h
     6::800ab5fb 00              ??         00h
     6::800ab5fc 02              ??         02h
     6::800ab5fd 00              ??         00h
     6::800ab5fe 00              ??         00h
     6::800ab5ff 00              ??         00h
     6::800ab600 48              ??         48h    H                                         ?  ->  OVR_226::800ab648
     6::800ab601 b6              ??         B6h
     6::800ab602 0a              ??         0Ah
     6::800ab603 80              ??         80h
     6::800ab604 88              ??         88h
     6::800ab605 01              ??         01h
     6::800ab606 00              ??         00h
     6::800ab607 00              ??         00h
     6::800ab608 00              ??         00h
     6::800ab609 00              ??         00h
     6::800ab60a 00              ??         00h
     6::800ab60b 00              ??         00h
     6::800ab60c c4 39 0a 80     addr       LAB_OVR_226__800a39c4
     6::800ab610 c4 39 0a 80     addr       LAB_OVR_226__800a39c4
     6::800ab614 c4 39 0a 80     addr       LAB_OVR_226__800a39c4
     6::800ab618 fc              ??         FCh                                              ?  ->  OVR_226::800a39fc
     6::800ab619 39              ??         39h    9
     6::800ab61a 0a              ??         0Ah
     6::800ab61b 80              ??         80h
     6::800ab61c 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab61d 3a              ??         3Ah    :
     6::800ab61e 0a              ??         0Ah
     6::800ab61f 80              ??         80h
     6::800ab620 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab621 3a              ??         3Ah    :
     6::800ab622 0a              ??         0Ah
     6::800ab623 80              ??         80h
     6::800ab624 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab625 3a              ??         3Ah    :
     6::800ab626 0a              ??         0Ah
     6::800ab627 80              ??         80h
     6::800ab628 fc              ??         FCh                                              ?  ->  OVR_226::800a39fc
     6::800ab629 39              ??         39h    9
     6::800ab62a 0a              ??         0Ah
     6::800ab62b 80              ??         80h
     6::800ab62c 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab62d 3a              ??         3Ah    :
     6::800ab62e 0a              ??         0Ah
     6::800ab62f 80              ??         80h
     6::800ab630 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab631 3a              ??         3Ah    :
     6::800ab632 0a              ??         0Ah
     6::800ab633 80              ??         80h
     6::800ab634 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab635 3a              ??         3Ah    :
     6::800ab636 0a              ??         0Ah
     6::800ab637 80              ??         80h
     6::800ab638 fc              ??         FCh                                              ?  ->  OVR_226::800a39fc
     6::800ab639 39              ??         39h    9
     6::800ab63a 0a              ??         0Ah
     6::800ab63b 80              ??         80h
     6::800ab63c 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab63d 3a              ??         3Ah    :
     6::800ab63e 0a              ??         0Ah
     6::800ab63f 80              ??         80h
     6::800ab640 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab641 3a              ??         3Ah    :
     6::800ab642 0a              ??         0Ah
     6::800ab643 80              ??         80h
     6::800ab644 34              ??         34h    4                                         ?  ->  OVR_226::800a3a34
     6::800ab645 3a              ??         3Ah    :
     6::800ab646 0a              ??         0Ah
     6::800ab647 80              ??         80h
     6::800ab648 34              ??         34h    4                                         ?  ->  OVR_226::800a4034
     6::800ab649 40              ??         40h    @
     6::800ab64a 0a              ??         0Ah
     6::800ab64b 80              ??         80h
     6::800ab64c 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a402c
     6::800ab64d 40              ??         40h    @
     6::800ab64e 0a              ??         0Ah
     6::800ab64f 80              ??         80h
     6::800ab650 b8              ??         B8h                                              ?  ->  OVR_226::800a40b8
     6::800ab651 40              ??         40h    @
     6::800ab652 0a              ??         0Ah
     6::800ab653 80              ??         80h
     6::800ab654 0e              ??         0Eh
     6::800ab655 00              ??         00h
     6::800ab656 00              ??         00h
     6::800ab657 00              ??         00h
     6::800ab658 70              ??         70h    p                                         ?  ->  OVR_226::800ab670
     6::800ab659 b6              ??         B6h
     6::800ab65a 0a              ??         0Ah
     6::800ab65b 80              ??         80h
     6::800ab65c 4c              ??         4Ch    L
     6::800ab65d 01              ??         01h
     6::800ab65e 00              ??         00h
     6::800ab65f 00              ??         00h
     6::800ab660 02              ??         02h
     6::800ab661 00              ??         00h
     6::800ab662 00              ??         00h
     6::800ab663 00              ??         00h
     6::800ab664 ac              ??         ACh                                              ?  ->  OVR_226::800ab6ac
     6::800ab665 b6              ??         B6h
     6::800ab666 0a              ??         0Ah
     6::800ab667 80              ??         80h
     6::800ab668 88              ??         88h
     6::800ab669 01              ??         01h
     6::800ab66a 00              ??         00h
     6::800ab66b 00              ??         00h
     6::800ab66c 00              ??         00h
     6::800ab66d 00              ??         00h
     6::800ab66e 00              ??         00h
     6::800ab66f 00              ??         00h
     6::800ab670 e0 44 0a 80     addr       LAB_OVR_226__800a44e0
     6::800ab674 e0 44 0a 80     addr       LAB_OVR_226__800a44e0
     6::800ab678 e0 44 0a 80     addr       LAB_OVR_226__800a44e0
     6::800ab67c 18              ??         18h                                              ?  ->  OVR_226::800a4518
     6::800ab67d 45              ??         45h    E
     6::800ab67e 0a              ??         0Ah
     6::800ab67f 80              ??         80h
     6::800ab680 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab681 45              ??         45h    E
     6::800ab682 0a              ??         0Ah
     6::800ab683 80              ??         80h
     6::800ab684 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab685 45              ??         45h    E
     6::800ab686 0a              ??         0Ah
     6::800ab687 80              ??         80h
     6::800ab688 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab689 45              ??         45h    E
     6::800ab68a 0a              ??         0Ah
     6::800ab68b 80              ??         80h
     6::800ab68c 18              ??         18h                                              ?  ->  OVR_226::800a4518
     6::800ab68d 45              ??         45h    E
     6::800ab68e 0a              ??         0Ah
     6::800ab68f 80              ??         80h
     6::800ab690 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab691 45              ??         45h    E
     6::800ab692 0a              ??         0Ah
     6::800ab693 80              ??         80h
     6::800ab694 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab695 45              ??         45h    E
     6::800ab696 0a              ??         0Ah
     6::800ab697 80              ??         80h
     6::800ab698 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab699 45              ??         45h    E
     6::800ab69a 0a              ??         0Ah
     6::800ab69b 80              ??         80h
     6::800ab69c 18              ??         18h                                              ?  ->  OVR_226::800a4518
     6::800ab69d 45              ??         45h    E
     6::800ab69e 0a              ??         0Ah
     6::800ab69f 80              ??         80h
     6::800ab6a0 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab6a1 45              ??         45h    E
     6::800ab6a2 0a              ??         0Ah
     6::800ab6a3 80              ??         80h
     6::800ab6a4 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab6a5 45              ??         45h    E
     6::800ab6a6 0a              ??         0Ah
     6::800ab6a7 80              ??         80h
     6::800ab6a8 50              ??         50h    P                                         ?  ->  OVR_226::800a4550
     6::800ab6a9 45              ??         45h    E
     6::800ab6aa 0a              ??         0Ah
     6::800ab6ab 80              ??         80h
     6::800ab6ac 14              ??         14h                                              ?  ->  OVR_226::800a4c14
     6::800ab6ad 4c              ??         4Ch    L
     6::800ab6ae 0a              ??         0Ah
     6::800ab6af 80              ??         80h
     6::800ab6b0 0c              ??         0Ch                                              ?  ->  OVR_226::800a4c0c
     6::800ab6b1 4c              ??         4Ch    L
     6::800ab6b2 0a              ??         0Ah
     6::800ab6b3 80              ??         80h
     6::800ab6b4 c8              ??         C8h                                              ?  ->  OVR_226::800a4cc8
     6::800ab6b5 4c              ??         4Ch    L
     6::800ab6b6 0a              ??         0Ah
     6::800ab6b7 80              ??         80h
     6::800ab6b8 0e              ??         0Eh
     6::800ab6b9 00              ??         00h
     6::800ab6ba 00              ??         00h
     6::800ab6bb 00              ??         00h
     6::800ab6bc d4              ??         D4h                                              ?  ->  OVR_226::800ab6d4
     6::800ab6bd b6              ??         B6h
     6::800ab6be 0a              ??         0Ah
     6::800ab6bf 80              ??         80h
     6::800ab6c0 4c              ??         4Ch    L
     6::800ab6c1 01              ??         01h
     6::800ab6c2 00              ??         00h
     6::800ab6c3 00              ??         00h
     6::800ab6c4 02              ??         02h
     6::800ab6c5 00              ??         00h
     6::800ab6c6 00              ??         00h
     6::800ab6c7 00              ??         00h
     6::800ab6c8 10              ??         10h                                              ?  ->  OVR_226::800ab710
     6::800ab6c9 b7              ??         B7h
     6::800ab6ca 0a              ??         0Ah
     6::800ab6cb 80              ??         80h
     6::800ab6cc 88              ??         88h
     6::800ab6cd 01              ??         01h
     6::800ab6ce 00              ??         00h
     6::800ab6cf 00              ??         00h
     6::800ab6d0 00              ??         00h
     6::800ab6d1 00              ??         00h
     6::800ab6d2 00              ??         00h
     6::800ab6d3 00              ??         00h
     6::800ab6d4 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a535c
     6::800ab6d5 53              ??         53h    S
     6::800ab6d6 0a              ??         0Ah
     6::800ab6d7 80              ??         80h
     6::800ab6d8 a4              ??         A4h                                              ?  ->  OVR_226::800a53a4
     6::800ab6d9 53              ??         53h    S
     6::800ab6da 0a              ??         0Ah
     6::800ab6db 80              ??         80h
     6::800ab6dc ac              ??         ACh                                              ?  ->  OVR_226::800a54ac
     6::800ab6dd 54              ??         54h    T
     6::800ab6de 0a              ??         0Ah
     6::800ab6df 80              ??         80h
     6::800ab6e0 04              ??         04h                                              ?  ->  OVR_226::800a5404
     6::800ab6e1 54              ??         54h    T
     6::800ab6e2 0a              ??         0Ah
     6::800ab6e3 80              ??         80h
     6::800ab6e4 e0              ??         E0h                                              ?  ->  OVR_226::800a54e0
     6::800ab6e5 54              ??         54h    T
     6::800ab6e6 0a              ??         0Ah
     6::800ab6e7 80              ??         80h
     6::800ab6e8 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab6e9 55              ??         55h    U
     6::800ab6ea 0a              ??         0Ah
     6::800ab6eb 80              ??         80h
     6::800ab6ec 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab6ed 55              ??         55h    U
     6::800ab6ee 0a              ??         0Ah
     6::800ab6ef 80              ??         80h
     6::800ab6f0 64              ??         64h    d                                         ?  ->  OVR_226::800a5464
     6::800ab6f1 54              ??         54h    T
     6::800ab6f2 0a              ??         0Ah
     6::800ab6f3 80              ??         80h
     6::800ab6f4 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab6f5 55              ??         55h    U
     6::800ab6f6 0a              ??         0Ah
     6::800ab6f7 80              ??         80h
     6::800ab6f8 14              ??         14h                                              ?  ->  OVR_226::800a5514
     6::800ab6f9 55              ??         55h    U
     6::800ab6fa 0a              ??         0Ah
     6::800ab6fb 80              ??         80h
     6::800ab6fc 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab6fd 55              ??         55h    U
     6::800ab6fe 0a              ??         0Ah
     6::800ab6ff 80              ??         80h
     6::800ab700 48              ??         48h    H                                         ?  ->  OVR_226::800a5548
     6::800ab701 55              ??         55h    U
     6::800ab702 0a              ??         0Ah
     6::800ab703 80              ??         80h
     6::800ab704 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab705 55              ??         55h    U
     6::800ab706 0a              ??         0Ah
     6::800ab707 80              ??         80h
     6::800ab708 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab709 55              ??         55h    U
     6::800ab70a 0a              ??         0Ah
     6::800ab70b 80              ??         80h
     6::800ab70c 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a557c
     6::800ab70d 55              ??         55h    U
     6::800ab70e 0a              ??         0Ah
     6::800ab70f 80              ??         80h
     6::800ab710 14              ??         14h                                              ?  ->  OVR_226::800a5d14
     6::800ab711 5d              ??         5Dh    ]
     6::800ab712 0a              ??         0Ah
     6::800ab713 80              ??         80h
     6::800ab714 0c              ??         0Ch                                              ?  ->  OVR_226::800a5d0c
     6::800ab715 5d              ??         5Dh    ]
     6::800ab716 0a              ??         0Ah
     6::800ab717 80              ??         80h
     6::800ab718 98              ??         98h                                              ?  ->  OVR_226::800a5d98
     6::800ab719 5d              ??         5Dh    ]
     6::800ab71a 0a              ??         0Ah
     6::800ab71b 80              ??         80h
     6::800ab71c 0e              ??         0Eh
     6::800ab71d 00              ??         00h
     6::800ab71e 00              ??         00h
     6::800ab71f 00              ??         00h
     6::800ab720 38              ??         38h    8                                         ?  ->  OVR_226::800ab738
     6::800ab721 b7              ??         B7h
     6::800ab722 0a              ??         0Ah
     6::800ab723 80              ??         80h
     6::800ab724 4c              ??         4Ch    L
     6::800ab725 01              ??         01h
     6::800ab726 00              ??         00h
     6::800ab727 00              ??         00h
     6::800ab728 02              ??         02h
     6::800ab729 00              ??         00h
     6::800ab72a 00              ??         00h
     6::800ab72b 00              ??         00h
     6::800ab72c 74              ??         74h    t                                         ?  ->  OVR_226::800ab774
     6::800ab72d b7              ??         B7h
     6::800ab72e 0a              ??         0Ah
     6::800ab72f 80              ??         80h
     6::800ab730 88              ??         88h
     6::800ab731 01              ??         01h
     6::800ab732 00              ??         00h
     6::800ab733 00              ??         00h
     6::800ab734 00              ??         00h
     6::800ab735 00              ??         00h
     6::800ab736 00              ??         00h
     6::800ab737 00              ??         00h
     6::800ab738 60              ??         60h    `                                         ?  ->  OVR_226::800a6260
     6::800ab739 62              ??         62h    b
     6::800ab73a 0a              ??         0Ah
     6::800ab73b 80              ??         80h
     6::800ab73c a8              ??         A8h                                              ?  ->  OVR_226::800a62a8
     6::800ab73d 62              ??         62h    b
     6::800ab73e 0a              ??         0Ah
     6::800ab73f 80              ??         80h
     6::800ab740 b0              ??         B0h                                              ?  ->  OVR_226::800a63b0
     6::800ab741 63              ??         63h    c
     6::800ab742 0a              ??         0Ah
     6::800ab743 80              ??         80h
     6::800ab744 08              ??         08h                                              ?  ->  OVR_226::800a6308
     6::800ab745 63              ??         63h    c
     6::800ab746 0a              ??         0Ah
     6::800ab747 80              ??         80h
     6::800ab748 e4              ??         E4h                                              ?  ->  OVR_226::800a63e4
     6::800ab749 63              ??         63h    c
     6::800ab74a 0a              ??         0Ah
     6::800ab74b 80              ??         80h
     6::800ab74c 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab74d 64              ??         64h    d
     6::800ab74e 0a              ??         0Ah
     6::800ab74f 80              ??         80h
     6::800ab750 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab751 64              ??         64h    d
     6::800ab752 0a              ??         0Ah
     6::800ab753 80              ??         80h
     6::800ab754 68              ??         68h    h                                         ?  ->  OVR_226::800a6368
     6::800ab755 63              ??         63h    c
     6::800ab756 0a              ??         0Ah
     6::800ab757 80              ??         80h
     6::800ab758 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab759 64              ??         64h    d
     6::800ab75a 0a              ??         0Ah
     6::800ab75b 80              ??         80h
     6::800ab75c 18              ??         18h                                              ?  ->  OVR_226::800a6418
     6::800ab75d 64              ??         64h    d
     6::800ab75e 0a              ??         0Ah
     6::800ab75f 80              ??         80h
     6::800ab760 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab761 64              ??         64h    d
     6::800ab762 0a              ??         0Ah
     6::800ab763 80              ??         80h
     6::800ab764 4c              ??         4Ch    L                                         ?  ->  OVR_226::800a644c
     6::800ab765 64              ??         64h    d
     6::800ab766 0a              ??         0Ah
     6::800ab767 80              ??         80h
     6::800ab768 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab769 64              ??         64h    d
     6::800ab76a 0a              ??         0Ah
     6::800ab76b 80              ??         80h
     6::800ab76c 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab76d 64              ??         64h    d
     6::800ab76e 0a              ??         0Ah
     6::800ab76f 80              ??         80h
     6::800ab770 80              ??         80h                                              ?  ->  OVR_226::800a6480
     6::800ab771 64              ??         64h    d
     6::800ab772 0a              ??         0Ah
     6::800ab773 80              ??         80h
     6::800ab774 b4              ??         B4h                                              ?  ->  OVR_226::800a6bb4
     6::800ab775 6b              ??         6Bh    k
     6::800ab776 0a              ??         0Ah
     6::800ab777 80              ??         80h
     6::800ab778 ac              ??         ACh                                              ?  ->  OVR_226::800a6bac
     6::800ab779 6b              ??         6Bh    k
     6::800ab77a 0a              ??         0Ah
     6::800ab77b 80              ??         80h
     6::800ab77c 68              ??         68h    h                                         ?  ->  OVR_226::800a6c68
     6::800ab77d 6c              ??         6Ch    l
     6::800ab77e 0a              ??         0Ah
     6::800ab77f 80              ??         80h
     6::800ab780 0e              ??         0Eh
     6::800ab781 00              ??         00h
     6::800ab782 00              ??         00h
     6::800ab783 00              ??         00h
     6::800ab784 9c              ??         9Ch                                              ?  ->  OVR_226::800ab79c
     6::800ab785 b7              ??         B7h
     6::800ab786 0a              ??         0Ah
     6::800ab787 80              ??         80h
     6::800ab788 4c              ??         4Ch    L
     6::800ab789 01              ??         01h
     6::800ab78a 00              ??         00h
     6::800ab78b 00              ??         00h
     6::800ab78c 02              ??         02h
     6::800ab78d 00              ??         00h
     6::800ab78e 00              ??         00h
     6::800ab78f 00              ??         00h
     6::800ab790 d8              ??         D8h                                              ?  ->  OVR_226::800ab7d8
     6::800ab791 b7              ??         B7h
     6::800ab792 0a              ??         0Ah
     6::800ab793 80              ??         80h
     6::800ab794 88              ??         88h
     6::800ab795 01              ??         01h
     6::800ab796 00              ??         00h
     6::800ab797 00              ??         00h
     6::800ab798 00              ??         00h
     6::800ab799 00              ??         00h
     6::800ab79a 00              ??         00h
     6::800ab79b 00              ??         00h
     6::800ab79c fc              ??         FCh                                              ?  ->  OVR_226::800a72fc
     6::800ab79d 72              ??         72h    r
     6::800ab79e 0a              ??         0Ah
     6::800ab79f 80              ??         80h
     6::800ab7a0 3c              ??         3Ch    <                                         ?  ->  OVR_226::800a733c
     6::800ab7a1 73              ??         73h    s
     6::800ab7a2 0a              ??         0Ah
     6::800ab7a3 80              ??         80h
     6::800ab7a4 bc              ??         BCh                                              ?  ->  OVR_226::800a73bc
     6::800ab7a5 73              ??         73h    s
     6::800ab7a6 0a              ??         0Ah
     6::800ab7a7 80              ??         80h
     6::800ab7a8 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a735c
     6::800ab7a9 73              ??         73h    s
     6::800ab7aa 0a              ??         0Ah
     6::800ab7ab 80              ??         80h
     6::800ab7ac e4              ??         E4h                                              ?  ->  OVR_226::800a73e4
     6::800ab7ad 73              ??         73h    s
     6::800ab7ae 0a              ??         0Ah
     6::800ab7af 80              ??         80h
     6::800ab7b0 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7b1 74              ??         74h    t
     6::800ab7b2 0a              ??         0Ah
     6::800ab7b3 80              ??         80h
     6::800ab7b4 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7b5 74              ??         74h    t
     6::800ab7b6 0a              ??         0Ah
     6::800ab7b7 80              ??         80h
     6::800ab7b8 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a737c
     6::800ab7b9 73              ??         73h    s
     6::800ab7ba 0a              ??         0Ah
     6::800ab7bb 80              ??         80h
     6::800ab7bc 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7bd 74              ??         74h    t
     6::800ab7be 0a              ??         0Ah
     6::800ab7bf 80              ??         80h
     6::800ab7c0 0c              ??         0Ch                                              ?  ->  OVR_226::800a740c
     6::800ab7c1 74              ??         74h    t
     6::800ab7c2 0a              ??         0Ah
     6::800ab7c3 80              ??         80h
     6::800ab7c4 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7c5 74              ??         74h    t
     6::800ab7c6 0a              ??         0Ah
     6::800ab7c7 80              ??         80h
     6::800ab7c8 34              ??         34h    4                                         ?  ->  OVR_226::800a7434
     6::800ab7c9 74              ??         74h    t
     6::800ab7ca 0a              ??         0Ah
     6::800ab7cb 80              ??         80h
     6::800ab7cc 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7cd 74              ??         74h    t
     6::800ab7ce 0a              ??         0Ah
     6::800ab7cf 80              ??         80h
     6::800ab7d0 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7d1 74              ??         74h    t
     6::800ab7d2 0a              ??         0Ah
     6::800ab7d3 80              ??         80h
     6::800ab7d4 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a745c
     6::800ab7d5 74              ??         74h    t
     6::800ab7d6 0a              ??         0Ah
     6::800ab7d7 80              ??         80h
     6::800ab7d8 60              ??         60h    `                                         ?  ->  OVR_226::800a7a60
     6::800ab7d9 7a              ??         7Ah    z
     6::800ab7da 0a              ??         0Ah
     6::800ab7db 80              ??         80h
     6::800ab7dc 58              ??         58h    X                                         ?  ->  OVR_226::800a7a58
     6::800ab7dd 7a              ??         7Ah    z
     6::800ab7de 0a              ??         0Ah
     6::800ab7df 80              ??         80h
     6::800ab7e0 e4              ??         E4h                                              ?  ->  OVR_226::800a7ae4
     6::800ab7e1 7a              ??         7Ah    z
     6::800ab7e2 0a              ??         0Ah
     6::800ab7e3 80              ??         80h
     6::800ab7e4 0e              ??         0Eh
     6::800ab7e5 00              ??         00h
     6::800ab7e6 00              ??         00h
     6::800ab7e7 00              ??         00h
     6::800ab7e8 00              ??         00h                                              ?  ->  OVR_226::800ab800
     6::800ab7e9 b8              ??         B8h
     6::800ab7ea 0a              ??         0Ah
     6::800ab7eb 80              ??         80h
     6::800ab7ec 4c              ??         4Ch    L
     6::800ab7ed 01              ??         01h
     6::800ab7ee 00              ??         00h
     6::800ab7ef 00              ??         00h
     6::800ab7f0 02              ??         02h
     6::800ab7f1 00              ??         00h
     6::800ab7f2 00              ??         00h
     6::800ab7f3 00              ??         00h
     6::800ab7f4 3c              ??         3Ch    <                                         ?  ->  OVR_226::800ab83c
     6::800ab7f5 b8              ??         B8h
     6::800ab7f6 0a              ??         0Ah
     6::800ab7f7 80              ??         80h
     6::800ab7f8 88              ??         88h
     6::800ab7f9 01              ??         01h
     6::800ab7fa 00              ??         00h
     6::800ab7fb 00              ??         00h
     6::800ab7fc 00              ??         00h
     6::800ab7fd 00              ??         00h
     6::800ab7fe 00              ??         00h
     6::800ab7ff 00              ??         00h
     6::800ab800 ac              ??         ACh                                              ?  ->  OVR_226::800a7fac
     6::800ab801 7f              ??         7Fh    
     6::800ab802 0a              ??         0Ah
     6::800ab803 80              ??         80h
     6::800ab804 ec              ??         ECh                                              ?  ->  OVR_226::800a7fec
     6::800ab805 7f              ??         7Fh    
     6::800ab806 0a              ??         0Ah
     6::800ab807 80              ??         80h
     6::800ab808 6c              ??         6Ch    l                                         ?  ->  OVR_226::800a806c
     6::800ab809 80              ??         80h
     6::800ab80a 0a              ??         0Ah                                              ?  ->  800c800a
     6::800ab80b 80              ??         80h
     6::800ab80c 0c              ??         0Ch                                              ?  ->  OVR_226::800a800c
     6::800ab80d 80              ??         80h
     6::800ab80e 0a              ??         0Ah
     6::800ab80f 80              ??         80h
     6::800ab810 94              ??         94h                                              ?  ->  OVR_226::800a8094
     6::800ab811 80              ??         80h
     6::800ab812 0a              ??         0Ah
     6::800ab813 80              ??         80h
     6::800ab814 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab815 81              ??         81h
     6::800ab816 0a              ??         0Ah
     6::800ab817 80              ??         80h
     6::800ab818 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab819 81              ??         81h
     6::800ab81a 0a              ??         0Ah
     6::800ab81b 80              ??         80h
     6::800ab81c 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a802c
     6::800ab81d 80              ??         80h
     6::800ab81e 0a              ??         0Ah
     6::800ab81f 80              ??         80h
     6::800ab820 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab821 81              ??         81h
     6::800ab822 0a              ??         0Ah
     6::800ab823 80              ??         80h
     6::800ab824 bc              ??         BCh                                              ?  ->  OVR_226::800a80bc
     6::800ab825 80              ??         80h
     6::800ab826 0a              ??         0Ah
     6::800ab827 80              ??         80h
     6::800ab828 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab829 81              ??         81h
     6::800ab82a 0a              ??         0Ah
     6::800ab82b 80              ??         80h
     6::800ab82c e4              ??         E4h                                              ?  ->  OVR_226::800a80e4
     6::800ab82d 80              ??         80h
     6::800ab82e 0a              ??         0Ah
     6::800ab82f 80              ??         80h
     6::800ab830 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab831 81              ??         81h
     6::800ab832 0a              ??         0Ah
     6::800ab833 80              ??         80h
     6::800ab834 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab835 81              ??         81h
     6::800ab836 0a              ??         0Ah
     6::800ab837 80              ??         80h
     6::800ab838 0c              ??         0Ch                                              ?  ->  OVR_226::800a810c
     6::800ab839 81              ??         81h
     6::800ab83a 0a              ??         0Ah
     6::800ab83b 80              ??         80h
     6::800ab83c d4              ??         D4h                                              ?  ->  OVR_226::800a87d4
     6::800ab83d 87              ??         87h
     6::800ab83e 0a              ??         0Ah
     6::800ab83f 80              ??         80h
     6::800ab840 cc              ??         CCh                                              ?  ->  OVR_226::800a87cc
     6::800ab841 87              ??         87h
     6::800ab842 0a              ??         0Ah
     6::800ab843 80              ??         80h
     6::800ab844 88              ??         88h                                              ?  ->  OVR_226::800a8888
     6::800ab845 88              ??         88h
     6::800ab846 0a              ??         0Ah
     6::800ab847 80              ??         80h
     6::800ab848 0e              ??         0Eh
     6::800ab849 00              ??         00h
     6::800ab84a 00              ??         00h
     6::800ab84b 00              ??         00h
     6::800ab84c 64              ??         64h    d                                         ?  ->  OVR_226::800ab864
     6::800ab84d b8              ??         B8h
     6::800ab84e 0a              ??         0Ah
     6::800ab84f 80              ??         80h
     6::800ab850 4c              ??         4Ch    L
     6::800ab851 01              ??         01h
     6::800ab852 00              ??         00h
     6::800ab853 00              ??         00h
     6::800ab854 02              ??         02h
     6::800ab855 00              ??         00h
     6::800ab856 00              ??         00h
     6::800ab857 00              ??         00h
     6::800ab858 a0              ??         A0h                                              ?  ->  OVR_226::800ab8a0
     6::800ab859 b8              ??         B8h
     6::800ab85a 0a              ??         0Ah
     6::800ab85b 80              ??         80h
     6::800ab85c 88              ??         88h
     6::800ab85d 01              ??         01h
     6::800ab85e 00              ??         00h
     6::800ab85f 00              ??         00h
     6::800ab860 00              ??         00h
     6::800ab861 00              ??         00h
     6::800ab862 00              ??         00h
     6::800ab863 00              ??         00h
     6::800ab864 1c              ??         1Ch                                              ?  ->  OVR_226::800a8f1c
     6::800ab865 8f              ??         8Fh
     6::800ab866 0a              ??         0Ah
     6::800ab867 80              ??         80h
     6::800ab868 5c              ??         5Ch    \                                         ?  ->  OVR_226::800a8f5c
     6::800ab869 8f              ??         8Fh
     6::800ab86a 0a              ??         0Ah
     6::800ab86b 80              ??         80h
     6::800ab86c dc              ??         DCh                                              ?  ->  OVR_226::800a8fdc
     6::800ab86d 8f              ??         8Fh
     6::800ab86e 0a              ??         0Ah
     6::800ab86f 80              ??         80h
     6::800ab870 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a8f7c
     6::800ab871 8f              ??         8Fh
     6::800ab872 0a              ??         0Ah
     6::800ab873 80              ??         80h
     6::800ab874 04              ??         04h                                              ?  ->  OVR_226::800a9004
     6::800ab875 90              ??         90h
     6::800ab876 0a              ??         0Ah
     6::800ab877 80              ??         80h
     6::800ab878 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab879 90              ??         90h
     6::800ab87a 0a              ??         0Ah
     6::800ab87b 80              ??         80h
     6::800ab87c 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab87d 90              ??         90h
     6::800ab87e 0a              ??         0Ah
     6::800ab87f 80              ??         80h
     6::800ab880 9c              ??         9Ch                                              ?  ->  OVR_226::800a8f9c
     6::800ab881 8f              ??         8Fh
     6::800ab882 0a              ??         0Ah
     6::800ab883 80              ??         80h
     6::800ab884 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab885 90              ??         90h
     6::800ab886 0a              ??         0Ah
     6::800ab887 80              ??         80h
     6::800ab888 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a902c
     6::800ab889 90              ??         90h
     6::800ab88a 0a              ??         0Ah
     6::800ab88b 80              ??         80h
     6::800ab88c 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab88d 90              ??         90h
     6::800ab88e 0a              ??         0Ah
     6::800ab88f 80              ??         80h
     6::800ab890 54              ??         54h    T                                         ?  ->  OVR_226::800a9054
     6::800ab891 90              ??         90h
     6::800ab892 0a              ??         0Ah
     6::800ab893 80              ??         80h
     6::800ab894 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab895 90              ??         90h
     6::800ab896 0a              ??         0Ah
     6::800ab897 80              ??         80h
     6::800ab898 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab899 90              ??         90h
     6::800ab89a 0a              ??         0Ah
     6::800ab89b 80              ??         80h
     6::800ab89c 7c              ??         7Ch    |                                         ?  ->  OVR_226::800a907c
     6::800ab89d 90              ??         90h
     6::800ab89e 0a              ??         0Ah
     6::800ab89f 80              ??         80h
     6::800ab8a0 80              ??         80h                                              ?  ->  OVR_226::800a9680
     6::800ab8a1 96              ??         96h
     6::800ab8a2 0a              ??         0Ah
     6::800ab8a3 80              ??         80h
     6::800ab8a4 78              ??         78h    x                                         ?  ->  OVR_226::800a9678
     6::800ab8a5 96              ??         96h
     6::800ab8a6 0a              ??         0Ah
     6::800ab8a7 80              ??         80h
     6::800ab8a8 04              ??         04h                                              ?  ->  OVR_226::800a9704
     6::800ab8a9 97              ??         97h
     6::800ab8aa 0a              ??         0Ah
     6::800ab8ab 80              ??         80h
     6::800ab8ac 0e              ??         0Eh
     6::800ab8ad 00              ??         00h
     6::800ab8ae 00              ??         00h
     6::800ab8af 00              ??         00h
     6::800ab8b0 c8              ??         C8h                                              ?  ->  OVR_226::800ab8c8
     6::800ab8b1 b8              ??         B8h
     6::800ab8b2 0a              ??         0Ah
     6::800ab8b3 80              ??         80h
     6::800ab8b4 4c              ??         4Ch    L
     6::800ab8b5 01              ??         01h
     6::800ab8b6 00              ??         00h
     6::800ab8b7 00              ??         00h
     6::800ab8b8 02              ??         02h
     6::800ab8b9 00              ??         00h
     6::800ab8ba 00              ??         00h
     6::800ab8bb 00              ??         00h
     6::800ab8bc 04              ??         04h                                              ?  ->  OVR_226::800ab904
     6::800ab8bd b9              ??         B9h
     6::800ab8be 0a              ??         0Ah
     6::800ab8bf 80              ??         80h
     6::800ab8c0 88              ??         88h
     6::800ab8c1 01              ??         01h
     6::800ab8c2 00              ??         00h
     6::800ab8c3 00              ??         00h
     6::800ab8c4 00              ??         00h
     6::800ab8c5 00              ??         00h
     6::800ab8c6 00              ??         00h
     6::800ab8c7 00              ??         00h
     6::800ab8c8 cc              ??         CCh                                              ?  ->  OVR_226::800a9bcc
     6::800ab8c9 9b              ??         9Bh
     6::800ab8ca 0a              ??         0Ah
     6::800ab8cb 80              ??         80h
     6::800ab8cc 0c              ??         0Ch                                              ?  ->  OVR_226::800a9c0c
     6::800ab8cd 9c              ??         9Ch
     6::800ab8ce 0a              ??         0Ah
     6::800ab8cf 80              ??         80h
     6::800ab8d0 8c              ??         8Ch                                              ?  ->  OVR_226::800a9c8c
     6::800ab8d1 9c              ??         9Ch
     6::800ab8d2 0a              ??         0Ah
     6::800ab8d3 80              ??         80h
     6::800ab8d4 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9c2c
     6::800ab8d5 9c              ??         9Ch
     6::800ab8d6 0a              ??         0Ah
     6::800ab8d7 80              ??         80h
     6::800ab8d8 b4              ??         B4h                                              ?  ->  OVR_226::800a9cb4
     6::800ab8d9 9c              ??         9Ch
     6::800ab8da 0a              ??         0Ah
     6::800ab8db 80              ??         80h
     6::800ab8dc 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab8dd 9d              ??         9Dh
     6::800ab8de 0a              ??         0Ah
     6::800ab8df 80              ??         80h
     6::800ab8e0 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab8e1 9d              ??         9Dh
     6::800ab8e2 0a              ??         0Ah
     6::800ab8e3 80              ??         80h
     6::800ab8e4 4c              ??         4Ch    L                                         ?  ->  OVR_226::800a9c4c
     6::800ab8e5 9c              ??         9Ch
     6::800ab8e6 0a              ??         0Ah
     6::800ab8e7 80              ??         80h
     6::800ab8e8 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab8e9 9d              ??         9Dh
     6::800ab8ea 0a              ??         0Ah
     6::800ab8eb 80              ??         80h
     6::800ab8ec dc              ??         DCh                                              ?  ->  OVR_226::800a9cdc
     6::800ab8ed 9c              ??         9Ch
     6::800ab8ee 0a              ??         0Ah
     6::800ab8ef 80              ??         80h
     6::800ab8f0 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab8f1 9d              ??         9Dh
     6::800ab8f2 0a              ??         0Ah
     6::800ab8f3 80              ??         80h
     6::800ab8f4 04              ??         04h                                              ?  ->  OVR_226::800a9d04
     6::800ab8f5 9d              ??         9Dh
     6::800ab8f6 0a              ??         0Ah
     6::800ab8f7 80              ??         80h
     6::800ab8f8 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab8f9 9d              ??         9Dh
     6::800ab8fa 0a              ??         0Ah
     6::800ab8fb 80              ??         80h
     6::800ab8fc 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab8fd 9d              ??         9Dh
     6::800ab8fe 0a              ??         0Ah
     6::800ab8ff 80              ??         80h
     6::800ab900 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800a9d2c
     6::800ab901 9d              ??         9Dh
     6::800ab902 0a              ??         0Ah
     6::800ab903 80              ??         80h
     6::800ab904 f4              ??         F4h                                              ?  ->  OVR_226::800aa3f4
     6::800ab905 a3              ??         A3h
     6::800ab906 0a              ??         0Ah
     6::800ab907 80              ??         80h
     6::800ab908 ec              ??         ECh                                              ?  ->  OVR_226::800aa3ec
     6::800ab909 a3              ??         A3h
     6::800ab90a 0a              ??         0Ah
     6::800ab90b 80              ??         80h
     6::800ab90c a8              ??         A8h                                              ?  ->  OVR_226::800aa4a8
     6::800ab90d a4              ??         A4h
     6::800ab90e 0a              ??         0Ah
     6::800ab90f 80              ??         80h
                             PTR_LAB_OVR_226__800aa96c_OVR_226__800ab910     XREF[1]:     FUN_OVR_226__800ab3dc:800ab3ec(R
     6::800ab910 6c a9 0a 80     addr       LAB_OVR_226__800aa96c
                             PTR_LAB_OVR_226__800aa984_OVR_226__800ab914     XREF[1]:     FUN_OVR_226__800ab3dc:800ab3ec(R
     6::800ab914 84 a9 0a 80     addr       LAB_OVR_226__800aa984
     6::800ab918 bc              ??         BCh                                              ?  ->  OVR_226::800aa9bc
     6::800ab919 a9              ??         A9h
     6::800ab91a 0a              ??         0Ah
     6::800ab91b 80              ??         80h
     6::800ab91c f4              ??         F4h                                              ?  ->  OVR_226::800aa9f4
     6::800ab91d a9              ??         A9h
     6::800ab91e 0a              ??         0Ah
     6::800ab91f 80              ??         80h
     6::800ab920 28              ??         28h    (                                         ?  ->  OVR_226::800aaa28
     6::800ab921 aa              ??         AAh
     6::800ab922 0a              ??         0Ah
     6::800ab923 80              ??         80h
     6::800ab924 60              ??         60h    `                                         ?  ->  OVR_226::800aaa60
     6::800ab925 aa              ??         AAh
     6::800ab926 0a              ??         0Ah
     6::800ab927 80              ??         80h
     6::800ab928 94              ??         94h                                              ?  ->  OVR_226::800aaa94
     6::800ab929 aa              ??         AAh
     6::800ab92a 0a              ??         0Ah
     6::800ab92b 80              ??         80h
     6::800ab92c c8              ??         C8h                                              ?  ->  OVR_226::800aaac8
     6::800ab92d aa              ??         AAh
     6::800ab92e 0a              ??         0Ah
     6::800ab92f 80              ??         80h
     6::800ab930 70              ??         70h    p                                         ?  ->  OVR_226::800aaf70
     6::800ab931 af              ??         AFh
     6::800ab932 0a              ??         0Ah
     6::800ab933 80              ??         80h
     6::800ab934 8c              ??         8Ch                                              ?  ->  OVR_226::800aaf8c
     6::800ab935 af              ??         AFh
     6::800ab936 0a              ??         0Ah
     6::800ab937 80              ??         80h
     6::800ab938 d4              ??         D4h                                              ?  ->  OVR_226::800aafd4
     6::800ab939 af              ??         AFh
     6::800ab93a 0a              ??         0Ah
     6::800ab93b 80              ??         80h
     6::800ab93c 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800ab02c
     6::800ab93d b0              ??         B0h
     6::800ab93e 0a              ??         0Ah
     6::800ab93f 80              ??         80h
     6::800ab940 80              ??         80h                                              ?  ->  OVR_226::800ab080
     6::800ab941 b0              ??         B0h
     6::800ab942 0a              ??         0Ah
     6::800ab943 80              ??         80h
     6::800ab944 d8              ??         D8h                                              ?  ->  OVR_226::800ab0d8
     6::800ab945 b0              ??         B0h
     6::800ab946 0a              ??         0Ah
     6::800ab947 80              ??         80h
     6::800ab948 2c              ??         2Ch    ,                                         ?  ->  OVR_226::800ab12c
     6::800ab949 b1              ??         B1h
     6::800ab94a 0a              ??         0Ah
     6::800ab94b 80              ??         80h
     6::800ab94c 8c              ??         8Ch                                              ?  ->  OVR_226::800ab18c
     6::800ab94d b1              ??         B1h
     6::800ab94e 0a              ??         0Ah
     6::800ab94f 80              ??         80h
     6::800ab950 c0              ??         C0h                                              ?  ->  OVR_226::800ab1c0
     6::800ab951 b1              ??         B1h
     6::800ab952 0a              ??         0Ah
     6::800ab953 80              ??         80h
     6::800ab954 08              ??         08h                                              ?  ->  OVR_226::800ab208
     6::800ab955 b2              ??         B2h
     6::800ab956 0a              ??         0Ah
     6::800ab957 80              ??         80h
     6::800ab958 70              ??         70h    p                                         ?  ->  OVR_226::800ab270
     6::800ab959 b2              ??         B2h
     6::800ab95a 0a              ??         0Ah
     6::800ab95b 80              ??         80h
     6::800ab95c c4              ??         C4h                                              ?  ->  OVR_226::800ab2c4
     6::800ab95d b2              ??         B2h
     6::800ab95e 0a              ??         0Ah
     6::800ab95f 80              ??         80h
     6::800ab960 08              ??         08h                                              ?  ->  OVR_226::800ab308
     6::800ab961 b3              ??         B3h
     6::800ab962 0a              ??         0Ah
     6::800ab963 80              ??         80h
     6::800ab964 5c              ??         5Ch    \                                         ?  ->  OVR_226::800ab35c
     6::800ab965 b3              ??         B3h
     6::800ab966 0a              ??         0Ah
     6::800ab967 80              ??         80h
     6::800ab968 a0              ??         A0h                                              ?  ->  OVR_226::800ab3a0
     6::800ab969 b3              ??         B3h
     6::800ab96a 0a              ??         0Ah
     6::800ab96b 80              ??         80h
     6::800ab96c d4              ??         D4h                                              ?  ->  OVR_226::800ab3d4
     6::800ab96d b3              ??         B3h
     6::800ab96e 0a              ??         0Ah
     6::800ab96f 80              ??         80h
