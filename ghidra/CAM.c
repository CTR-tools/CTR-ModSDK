
// called "CAM" cause of "camera init" string

// CAM_SkyboxGlow
// Draws skybox glowing effect found in Papu's Pyramid
// param1 is "someData" from lev header
// param2 is pushBuffer
// param3 is primMem
// param4 is ptrOT (+ 0xffc)?
void FUN_800175cc(short *param_1,int param_2,int param_3,uint *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;

  // Sine(angle)
  // camera rotZ
  iVar1 = FUN_8003d184((int)*(short *)(param_2 + 10));

  // Cosine(angle)
  // camera rotZ
  iVar2 = FUN_8003d1c0((int)*(short *)(param_2 + 10));

  if (iVar2 == 0) {
    iVar2 = 1;
  }
  if (iVar2 == 0) {
    trap(0x1c00);
  }
  if ((iVar2 == -1) && (iVar1 << 0xc == -0x80000000)) {
    trap(0x1800);
  }

  // camera rotX
  iVar8 = ((int)*(short *)(param_2 + 6) + -0x800) * 0x78;

  iVar1 = -(((iVar1 << 0xc) / iVar2 << 8) >> 0xc) / 2;

  // angle range
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x3ff;
  }

  // rect.h
  iVar2 = (uint)*(ushort *)(param_2 + 0x22) << 0x10;
  DAT_1f800014 = (iVar8 >> 10) + ((iVar2 >> 0x10) - (iVar2 >> 0x1f) >> 1);

  // camera rotX
  iVar2 = ((int)*(short *)(param_2 + 6) + -0x800) * 0x78;

  iVar8 = 0;

  // angle range
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x3ff;
  }

  // rect.h
  iVar3 = (uint)*(ushort *)(param_2 + 0x22) << 0x10;
  DAT_1f800018 = (iVar2 >> 10) + ((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);

  // rect.w
  uVar14 = SEXT24(*(short *)(param_2 + 0x20));
  uVar13 = uVar14 & 0xffff;

  do {
    uVar12 = (DAT_1f800018 - param_1[1]) - iVar1;
    uVar10 = ~uVar12 >> 0x1f;
    iVar2 = (DAT_1f800018 - param_1[1]) + iVar1;
    uVar4 = *(uint *)(param_1 + 2);
    DAT_1f800000 = uVar4 & 0xffffff;
    uVar5 = *(uint *)(param_1 + 4);
    DAT_1f800008 = uVar5 & 0xffffff;
    iVar11 = (DAT_1f800014 - *param_1) - iVar1;
    iVar3 = (DAT_1f800014 - *param_1) + iVar1;
    if (-1 < iVar2) {
      uVar10 = uVar10 | 2;
    }
    if (-1 < iVar11) {
      uVar10 = uVar10 | 4;
    }
    if (-1 < iVar3) {
      uVar10 = uVar10 | 8;
    }
    DAT_1f800008._1_1_ = (byte)(DAT_1f800008 >> 8);
    DAT_1f800008._2_1_ = (byte)(DAT_1f800008 >> 0x10);
    DAT_1f800000._1_1_ = (byte)(DAT_1f800000 >> 8);
    DAT_1f800000._2_1_ = (byte)(DAT_1f800000 >> 0x10);
    DAT_1f800004 = DAT_1f800000;
    DAT_1f80000c = DAT_1f800008;
    switch(uVar10) {
    case 1:
      iVar3 = iVar11 - uVar12;
      iVar6 = (iVar11 * 0x1000) / iVar3;
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (iVar11 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      iVar2 = uVar12 - iVar2;
      iVar3 = (int)(uVar12 * 0x1000) / iVar2;
      if (iVar2 == 0) {
        trap(0x1c00);
      }
      if ((iVar2 == -1) && (uVar12 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_1f800000._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800000._1_1_) * iVar6) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar5 & 0xff) - (uVar4 & 0xff)) * iVar6) >> 0xc));
      DAT_1f800000._0_3_ =
           CONCAT12(DAT_1f800000._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800000._2_1_) * iVar6) >>
                          0xc),(undefined2)DAT_1f800000);
      DAT_1f80000c._0_3_ =
           CONCAT12(DAT_1f800008._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800008._2_1_) * iVar3) >>
                          0xc),
                    CONCAT11(DAT_1f800008._1_1_ +
                             (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800008._1_1_) *
                                         iVar3) >> 0xc),
                             (char)DAT_1f800008 +
                             (char)((int)(((uVar5 & 0xff) - (uVar5 & 0xff)) * iVar3) >> 0xc)));
      DAT_1f80000c = (uint)(uint3)DAT_1f80000c;

	  // primMem->current
      puVar9 = *(uint **)(param_3 + 0xc);

      DAT_1f800000 = (uint)(uint3)DAT_1f800000;
      puVar9[1] = (uint)(uint3)DAT_1f800000 | 0x30000000;
      puVar9[3] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      puVar9[2] = 0;
      puVar9[4] = uVar12 * 0x10000;
      puVar9[5] = uVar4;
      puVar9[6] = (int)(uVar14 * iVar3) >> 0xc & 0xffff;
      *puVar9 = *param_4 | 0x6000000;
      uVar4 = (uint)puVar9 & 0xffffff;

	  // increment pointer
	  puVar9 = puVar9 + 7;

      goto LAB_80017cb4;

	case 2:
      iVar11 = iVar3 - iVar2;
      iVar6 = (iVar3 * 0x1000) / iVar11;
      if (iVar11 == 0) {
        trap(0x1c00);
      }
      if ((iVar11 == -1) && (iVar3 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      iVar3 = uVar12 - iVar2;
      iVar11 = (int)(uVar12 * 0x1000) / iVar3;
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (uVar12 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_1f800004._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800000._1_1_) * iVar6) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar5 & 0xff) - (uVar4 & 0xff)) * iVar6) >> 0xc));
      DAT_1f800004 = (uint)CONCAT12(DAT_1f800000._2_1_ +
                                    (char)((int)(((uint)DAT_1f800008._2_1_ -
                                                 (uint)DAT_1f800000._2_1_) * iVar6) >> 0xc),
                                    (undefined2)DAT_1f800004);
      DAT_1f800008._0_3_ =
           CONCAT12(DAT_1f800008._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800008._2_1_) * iVar11) >>
                          0xc),
                    CONCAT11(DAT_1f800008._1_1_ +
                             (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800008._1_1_) *
                                         iVar11) >> 0xc),
                             (char)DAT_1f800008 +
                             (char)((int)(((uVar5 & 0xff) - (uVar5 & 0xff)) * iVar11) >> 0xc)));

	  // primMem->current
	  puVar9 = *(uint **)(param_3 + 0xc);

	  DAT_1f800008 = (uint)(uint3)DAT_1f800008;
      puVar9[1] = (uint)(uint3)DAT_1f800008 | 0x30000000;
      puVar9[3] = DAT_1f800004;
      uVar4 = DAT_1f80000c;
      puVar9[4] = uVar13;
      puVar9[5] = uVar4;
      puVar9[2] = (int)(uVar14 * iVar11) >> 0xc & 0xffff;
      puVar9[6] = uVar13 | iVar2 * 0x10000;
      *puVar9 = *param_4 | 0x6000000;
      uVar4 = (uint)puVar9 & 0xffffff;

	  // increment pointer
	  puVar9 = puVar9 + 7;

	  goto LAB_80017cb4;

    case 3:
      iVar6 = iVar11 - uVar12;
      iVar7 = (iVar11 * 0x1000) / iVar6;
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (iVar11 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      iVar11 = iVar3 - iVar2;
      iVar6 = (iVar3 * 0x1000) / iVar11;
      if (iVar11 == 0) {
        trap(0x1c00);
      }
      if ((iVar11 == -1) && (iVar3 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_1f800000._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800000._1_1_) * iVar7) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar5 & 0xff) - (uVar4 & 0xff)) * iVar7) >> 0xc));
      DAT_1f800000._0_3_ =
           CONCAT12(DAT_1f800000._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800000._2_1_) * iVar7) >>
                          0xc),(undefined2)DAT_1f800000);
      DAT_1f800000 = (uint)(uint3)DAT_1f800000;
      DAT_1f800004._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800000._1_1_) * iVar6) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar5 & 0xff) - (uVar4 & 0xff)) * iVar6) >> 0xc));
      DAT_1f800004._0_3_ =
           CONCAT12(DAT_1f800000._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800000._2_1_) * iVar6) >>
                          0xc),(undefined2)DAT_1f800004);
      DAT_1f800004 = (uint)(uint3)DAT_1f800004;

	  // primMem->current
      puVar9 = *(uint **)(param_3 + 0xc);

	  puVar9[1] = DAT_1f800000 | 0x38000000;
      puVar9[3] = DAT_1f800004;
      puVar9[5] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      puVar9[6] = uVar12 * 0x10000;
      puVar9[2] = 0;
      puVar9[4] = uVar13;
      puVar9[8] = uVar13 | iVar2 * 0x10000;
      puVar9[7] = uVar4;
      *puVar9 = *param_4 | 0x8000000;
      uVar4 = (uint)puVar9 & 0xffffff;

	  // increment pointer
	  puVar9 = puVar9 + 9;

LAB_80017cb4:
      *param_4 = uVar4;

	  // set new primMem->current
      *(uint **)(param_3 + 0xc) = puVar9;

      break;
    case 5:
      iVar3 = iVar11 - iVar3;
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (iVar11 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      iVar2 = uVar12 - iVar2;
      if (iVar2 == 0) {
        trap(0x1c00);
      }
      if ((iVar2 == -1) && (uVar12 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }

	  // primMem->current
      puVar9 = *(uint **)(param_3 + 0xc);

	  puVar9[1] = DAT_1f800000 | 0x38000000;
      uVar5 = (int)(uVar14 * ((iVar11 * 0x1000) / iVar3)) >> 0xc & 0xffff;
      puVar9[3] = DAT_1f800004;
      puVar9[5] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      puVar9[2] = iVar11 * 0x10000;
      puVar9[6] = uVar12 * 0x10000;
      puVar9[4] = uVar5;
      puVar9[7] = uVar4;
      puVar9[8] = (int)(uVar14 * ((int)(uVar12 * 0x1000) / iVar2)) >> 0xc & 0xffff;
      *puVar9 = *param_4 | 0x8000000;
      *param_4 = (uint)puVar9 & 0xffffff;

	  // update primMem->current
	  *(uint **)(param_3 + 0xc) = puVar9 + 9;

	  if (
			(iVar8 == 0) &&

			// if background gradient exists
			(*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x16b) != '\0')
		  )
	  {
		// gradient color
        uVar4 = *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x168);

        puVar9[0xb] = uVar5;
        puVar9[0xc] = 0;
        puVar9[0xd] = iVar11 * 0x10000;
        puVar9[10] = uVar4 & 0xffffff | 0x20000000;
        puVar9[9] = *param_4 | 0x4000000;
        *param_4 = (uint)(puVar9 + 9) & 0xffffff;
        puVar9 = puVar9 + 0xe;
LAB_800185d8:

		// update primMem->current
        *(uint **)(param_3 + 0xc) = puVar9;
      }
      break;
    case 7:
      iVar6 = iVar11 - iVar3;
      iVar7 = (iVar11 * 0x1000) / iVar6;
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (iVar11 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      iVar6 = iVar3 - iVar2;
      iVar15 = (iVar3 * 0x1000) / iVar6;
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (iVar3 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_1f800010._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800000._1_1_ - (uint)DAT_1f800000._1_1_) * iVar7) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar4 & 0xff) - (uVar4 & 0xff)) * iVar7) >> 0xc));
      uVar10 = iVar11 * 0x10000;
      DAT_1f800010._0_3_ =
           CONCAT12(DAT_1f800000._2_1_ +
                    (char)((int)(((uint)DAT_1f800000._2_1_ - (uint)DAT_1f800000._2_1_) * iVar7) >>
                          0xc),(ushort)DAT_1f800010);
      DAT_1f800010 = DAT_1f800010 & 0xff000000 | (uint)(uint3)DAT_1f800010;
      DAT_1f800004._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800000._1_1_) * iVar15) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar5 & 0xff) - (uVar4 & 0xff)) * iVar15) >> 0xc));
      DAT_1f800004._0_3_ =
           CONCAT12(DAT_1f800000._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800000._2_1_) * iVar15) >>
                          0xc),(undefined2)DAT_1f800004);
      DAT_1f800004 = (uint)(uint3)DAT_1f800004;

	  // get primMem->current
      puVar9 = *(uint **)(param_3 + 0xc);

      puVar9[1] = DAT_1f800000 | 0x30000000;
      puVar9[3] = DAT_1f800010;
      uVar4 = DAT_1f800004;
      uVar5 = (int)(uVar14 * iVar7) >> 0xc & 0xffff;
      puVar9[2] = uVar10;
      puVar9[4] = uVar5;
      puVar9[6] = uVar13;
      puVar9[5] = uVar4;
      *puVar9 = *param_4 | 0x6000000;
      *param_4 = (uint)puVar9 & 0xffffff;
      uVar4 = DAT_1f800000;

	  // update primMem->current
      *(uint **)(param_3 + 0xc) = puVar9 + 7;

      puVar9[8] = uVar4 & 0xffffff | 0x38000000;
      puVar9[10] = DAT_1f800004;
      puVar9[0xc] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      puVar9[0xd] = uVar12 * 0x10000;
      puVar9[9] = uVar10;
      puVar9[0xb] = uVar13;
      puVar9[0xf] = uVar13 | iVar2 * 0x10000;
      puVar9[0xe] = uVar4;
      puVar9[7] = *param_4 | 0x8000000;

      *param_4 = (uint)(puVar9 + 7) & 0xffffff;

	  // update primMem->current
	  *(uint **)(param_3 + 0xc) = puVar9 + 0x10;

	  if (
			(iVar8 == 0) &&

			// if background gradient exists
			(*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x16b) != '\0')
		  )
	  {
		// gradient color
        uVar4 = *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x168);

		puVar9[0x12] = uVar5;
        puVar9[0x13] = 0;
        puVar9[0x14] = uVar10;
        puVar9[0x11] = uVar4 & 0xffffff | 0x20000000;
        puVar9[0x10] = *param_4 | 0x4000000;
        *param_4 = (uint)(puVar9 + 0x10) & 0xffffff;
        puVar9 = puVar9 + 0x15;
        goto LAB_800185d8;
      }
      break;
    case 10:
      iVar6 = iVar11 - iVar3;
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (iVar11 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      iVar7 = uVar12 - iVar2;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (uVar12 * 0x1000 == -0x80000000)) {
        trap(0x1800);
      }
      puVar9 = *(uint **)(param_3 + 0xc);
      puVar9[1] = DAT_1f800000 | 0x38000000;
      uVar5 = (int)(uVar14 * ((iVar11 * 0x1000) / iVar6)) >> 0xc & 0xffff;
      puVar9[3] = DAT_1f800004;
      puVar9[5] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      uVar10 = uVar13 | iVar3 * 0x10000;
      puVar9[4] = uVar10;
      puVar9[8] = uVar13 | iVar2 * 0x10000;
      puVar9[2] = uVar5;
      puVar9[7] = uVar4;
      puVar9[6] = (int)(uVar14 * ((int)(uVar12 * 0x1000) / iVar7)) >> 0xc & 0xffff;
      *puVar9 = *param_4 | 0x8000000;
      *param_4 = (uint)puVar9 & 0xffffff;

	  // update primMem->current
      *(uint **)(param_3 + 0xc) = puVar9 + 9;

	  if (
			(iVar8 == 0) &&

			// if background gradient exists
			(*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x16b) != '\0')
		  )
	  {
		// gradient color
        uVar4 = *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x168);

		puVar9[0xb] = uVar5;
        puVar9[0xc] = uVar13;
        puVar9[0xd] = uVar10;
        puVar9[10] = uVar4 & 0xffffff | 0x20000000;
        puVar9[9] = *param_4 | 0x4000000;
        *param_4 = (uint)(puVar9 + 9) & 0xffffff;
        puVar9 = puVar9 + 0xe;
        goto LAB_800185d8;
      }
      break;
    case 0xb:
      iVar7 = iVar11 * 0x1000;
      iVar6 = iVar11 - iVar3;
      iVar15 = iVar7 / iVar6;
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (iVar7 == -0x80000000)) {
        trap(0x1800);
      }
      iVar11 = iVar11 - uVar12;
      iVar6 = iVar7 / iVar11;
      if (iVar11 == 0) {
        trap(0x1c00);
      }
      if ((iVar11 == -1) && (iVar7 == -0x80000000)) {
        trap(0x1800);
      }
      DAT_1f800010._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800000._1_1_ - (uint)DAT_1f800000._1_1_) * iVar15) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar4 & 0xff) - (uVar4 & 0xff)) * iVar15) >> 0xc));
      DAT_1f800010 = DAT_1f800010 & 0xff000000 |
                     (uint)(byte)(DAT_1f800000._2_1_ +
                                 (char)((int)(((uint)DAT_1f800000._2_1_ - (uint)DAT_1f800000._2_1_)
                                             * iVar15) >> 0xc)) << 0x10 | (uint)(ushort)DAT_1f800010
      ;
      DAT_1f800000._0_2_ =
           CONCAT11(DAT_1f800000._1_1_ +
                    (char)((int)(((uint)DAT_1f800008._1_1_ - (uint)DAT_1f800000._1_1_) * iVar6) >>
                          0xc),
                    (char)DAT_1f800000 +
                    (char)((int)(((uVar5 & 0xff) - (uVar4 & 0xff)) * iVar6) >> 0xc));
      DAT_1f800000._0_3_ =
           CONCAT12(DAT_1f800000._2_1_ +
                    (char)((int)(((uint)DAT_1f800008._2_1_ - (uint)DAT_1f800000._2_1_) * iVar6) >>
                          0xc),(undefined2)DAT_1f800000);

	  // get primMem->current
	  puVar9 = *(uint **)(param_3 + 0xc);

      DAT_1f800000 = (uint)(uint3)DAT_1f800000;
      puVar9[1] = (uint)(uint3)DAT_1f800000 | 0x30000000;
      puVar9[3] = DAT_1f800010;
      uVar4 = DAT_1f800004;
      uVar5 = uVar13 | iVar3 * 0x10000;
      uVar10 = (int)(uVar14 * iVar15) >> 0xc & 0xffff;
      puVar9[2] = 0;
      puVar9[4] = uVar10;
      puVar9[6] = uVar5;
      puVar9[5] = uVar4;
      *puVar9 = *param_4 | 0x6000000;
      *param_4 = (uint)puVar9 & 0xffffff;
      uVar4 = DAT_1f800000;

	  // update primMem->current
      *(uint **)(param_3 + 0xc) = puVar9 + 7;

      puVar9[8] = uVar4 & 0xffffff | 0x38000000;
      puVar9[10] = DAT_1f800004;
      puVar9[0xc] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      puVar9[0xd] = uVar12 * 0x10000;
      puVar9[9] = 0;
      puVar9[0xb] = uVar5;
      puVar9[0xf] = uVar13 | iVar2 * 0x10000;
      puVar9[0xe] = uVar4;
      puVar9[7] = *param_4 | 0x8000000;
      *param_4 = (uint)(puVar9 + 7) & 0xffffff;

	  // update primMem->current
      *(uint **)(param_3 + 0xc) = puVar9 + 0x10;

      if (
			(iVar8 == 0) &&

			// if background gradient exists
			(*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x16b) != '\0')
		  )
	  {
		// gradient color
        uVar4 = *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x168);

		puVar9[0x12] = uVar10;
        puVar9[0x13] = uVar13;
        puVar9[0x14] = uVar5;
        puVar9[0x11] = uVar4 & 0xffffff | 0x20000000;
        puVar9[0x10] = *param_4 | 0x4000000;
        *param_4 = (uint)(puVar9 + 0x10) & 0xffffff;
        puVar9 = puVar9 + 0x15;
        goto LAB_800185d8;
      }
      break;
    case 0xf:

	  // get primMem->current
      puVar9 = *(uint **)(param_3 + 0xc);

      puVar9[1] = DAT_1f800000 | 0x38000000;
      puVar9[3] = DAT_1f800004;
      puVar9[5] = DAT_1f800008;
      uVar4 = DAT_1f80000c;
      uVar5 = uVar13 | iVar3 * 0x10000;
      puVar9[6] = uVar12 * 0x10000;
      puVar9[2] = iVar11 * 0x10000;
      puVar9[4] = uVar5;
      puVar9[8] = uVar13 | iVar2 * 0x10000;
      puVar9[7] = uVar4;
      *puVar9 = *param_4 | 0x8000000;
      *param_4 = (uint)puVar9 & 0xffffff;

	  // update primMem->current
      *(uint **)(param_3 + 0xc) = puVar9 + 9;

      if (
			(iVar8 == 0) &&

			// if background gradient exists
			(*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x16b) != '\0')
		  )
	  {
		// gradient color
        uVar4 = *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x168);

		puVar9[0xb] = 0;
        puVar9[0xc] = uVar13;
        puVar9[0xd] = iVar11 * 0x10000;
        puVar9[0xe] = uVar5;
        puVar9[10] = uVar4 & 0xffffff | 0x28000000;
        puVar9[9] = *param_4 | 0x5000000;
        *param_4 = (uint)(puVar9 + 9) & 0xffffff;
        puVar9 = puVar9 + 0xf;
        goto LAB_800185d8;
      }
    }
    iVar8 = iVar8 + 1;
    param_1 = param_1 + 6;
    if (2 < iVar8) {
      return;
    }
  } while( true );
}

// CAM_ClearScreen
// param1 is PTR_DAT_8008d2ac - GameTracker
void FUN_8001861c(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;

  // gGT->backBuffer
  iVar4 = *(int *)(param_1 + 0x10);

  // DB->primMem.curr
  puVar10 = *(uint **)(iVar4 + 0x80);

  // loop counter
  iVar12 = 0;

  // if numPlyrCurrGame is not zero
  if (*(char *)(param_1 + 0x1ca8) != '\0')
  {
	// offset of 8008d2ac where each screen holds
	// pushBuffer info, like position, width, height
    iVar4 = 0x168;

    puVar9 = puVar10 + 1;

	// for iVar12 = 0; iVar12 < numPlyrCurrGame; iVar12++
	do
	{
	  // pointer to pushBuffer struct
      iVar8 = param_1 + iVar4;

	  // window sizeX
      sVar1 = *(short *)(iVar8 + 0x20);

	  // window startX
      sVar2 = *(short *)(iVar8 + 0x1c);

	  // window startY
      sVar3 = *(short *)(iVar8 + 0x1e);

	  // window sizeY (casted to short?)
      iVar5 = (uint)*(ushort *)(iVar8 + 0x22) << 0x10;
	  iVar11 = iVar5 >> 0x10;

	  // pushBuffer rotation
	  // view up/down will change where the line splits.
	  // At 0x800, camera looks straight, and line is perfectly midpoint
	  iVar5 = ((int)*(short *)(iVar8 + 6) + -0x800 >> 3) + (iVar11 - (iVar5 >> 0x1f) >> 1);
	  
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      iVar7 = iVar11;
      if (iVar5 < iVar11) {
        iVar7 = iVar5;
      }

	  // pushBuffer->ptrOT
      iVar5 = *(int *)(iVar8 + 0xf4);

	  // if top-half clear color exists
      if ((*(char *)(*(int *)(param_1 + 0x160) + 0x163) != '\0') && (0 < iVar7))
	  {
		// swapchain index
        iVar8 = *(int *)(param_1 + 0xc);

		// draw colored quad?
		puVar9[2] = (int)sVar1 | iVar7 << 0x10;

		// Y-pos in VRAM, position of window + swapIndex*0x128
        puVar9[1] = (int)sVar2 | ((int)sVar3 + iVar8 * 0x128) * 0x10000;

		// top half clear color
		*puVar9 = (uint)*(uint3 *)(*(int *)(param_1 + 0x160) + 0x160) | 0x2000000;

        puVar9 = puVar9 + 4;
        *puVar10 = *(uint *)(iVar5 + 0xffc) | 0x3000000;
        uVar6 = (uint)puVar10 & 0xffffff;
        puVar10 = puVar10 + 4;
        *(uint *)(iVar5 + 0xffc) = uVar6;
      }

	  // if bottom-half clear color exists
      if ((*(char *)(*(int *)(param_1 + 0x160) + 0x167) != '\0') && (iVar7 < iVar11))
	  {
		// swapchain index
        iVar8 = *(int *)(param_1 + 0xc);

		// draw colored quad?
        puVar9[2] = (int)sVar1 | (iVar11 - iVar7) * 0x10000;

		// Y-pos in VRAM, position of window + swapIndex*0x128
        puVar9[1] = (int)sVar2 | ((int)sVar3 + iVar8 * 0x128 + iVar7) * 0x10000;

		// bottom half clear color
		*puVar9 = (uint)*(uint3 *)(*(int *)(param_1 + 0x160) + 0x164) | 0x2000000;

        puVar9 = puVar9 + 4;
        *puVar10 = *(uint *)(iVar5 + 0xffc) | 0x3000000;
        uVar6 = (uint)puVar10 & 0xffffff;
        puVar10 = puVar10 + 4;
        *(uint *)(iVar5 + 0xffc) = uVar6;
      }

	  // increment loop counter
      iVar12 = iVar12 + 1;

	  // increment pointer to next pushBuffer struct
      iVar4 = iVar4 + 0x110;

    } while (iVar12 < (int)(uint)*(byte *)(param_1 + 0x1ca8));

	// gGT->backBuffer
    iVar4 = *(int *)(param_1 + 0x10);
  }

  // set new backBuffer->primMem.curr
  *(uint **)(iVar4 + 0x80) = puVar10;

  return;
}


// CAM_Init
// param1 is CameraDC
// param2 is cameraID
// param3 is driver
// param4 is PushBuffer
void FUN_80018818(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{

  int iVar1;

  // s_camera_8008cf8c
  // "camera"

  // PROC_BirthWithObject
  // 0 = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0xf = camera thread bucket
  iVar1 = FUN_8004205c(0x30f,FUN_8001b334,s_camera_8008cf8c,0);

  // attach to thread, why 0x34 and not 0x30?
  *(undefined4 **)(iVar1 + 0x34) = param_1;

  // clear the full 0xdc struct
  memset(param_1,0,0xdc);

  // camera index
  *param_1 = param_2;

  // driver
  param_1[0x11] = param_3;

  // pushBuffer
  param_1[0x12] = param_4;

  // set camera mode to zoomed in
  *(undefined2 *)((int)param_1 + 0x9a) = 0;

  // just changed direction (for init?)
  param_1[0x1c] = param_1[0x1c] | 8;

  return;
}


// CAM_FindClosestQuadblock
// param1 = 1f800108
// param2 = cameraDC
// param3 = driver object
// param4 = 1f800348
// NOP, and instances wont draw
void FUN_800188a8(short *param_1,int param_2,undefined4 param_3,short *param_4)

{
  short sVar1;
  short sVar2;
  undefined *puVar3;
  int iVar4;
  short sVar5;

  // make short[3] from int[3],
  // posCurr
  sVar5 = *param_4;
  param_1[8] = sVar5;
  param_1[9] = param_4[2];
  param_1[10] = param_4[4];
  
  // posPrev, with Y - 0x800
  *param_1 = *param_4;
  sVar1 = param_4[2];
  param_1[1] = sVar1;
  sVar2 = param_4[4];
  param_1[1] = sVar1 + -0x800;
  param_1[0xe] = *param_1;
  param_1[2] = sVar2;
  param_1[9] = param_1[9] + 0x100;
  param_1[0xf] = param_1[1];
  param_1[0x10] = sVar2;
  
  // boundingbox minX
  if (*param_1 < param_1[8]) {
    sVar5 = *param_1;
  }
  param_1[0x18] = sVar5;
  
  // boundingbox minY
  sVar5 = param_1[9];
  if (param_1[1] < param_1[9]) {
    sVar5 = param_1[1];
  }
  param_1[0x19] = sVar5;
  
  // boundingbox minZ
  sVar5 = param_1[10];
  if (param_1[2] < param_1[10]) {
    sVar5 = param_1[2];
  }
  param_1[0x1a] = sVar5;
  
  // boundingbox maxX
  sVar5 = param_1[8];
  if (param_1[8] < *param_1) {
    sVar5 = *param_1;
  }
  param_1[0x1b] = sVar5;
  
  // boundingbox maxY
  sVar5 = param_1[9];
  if (param_1[9] < param_1[1]) {
    sVar5 = param_1[1];
  }
  param_1[0x1c] = sVar5;
  
  puVar3 = PTR_DAT_8008d2ac;
  
  // boundingbox maxZ
  sVar5 = param_1[10];
  if (param_1[10] < param_1[2]) {
    sVar5 = param_1[2];
  }
  param_1[0x1d] = sVar5;
  
  *(undefined4 *)(param_1 + 0x12) = 0x800;
  *(undefined4 *)(param_1 + 0x14) = 0;
  param_1[0x1f] = 0;
  param_1[0x1e] = 0;
  param_1[0x11] = 0;
  *(undefined4 *)(param_2 + 0x3c) = 0;

  if (
		(
			// get LEV and mesh_info
			(*(int **)(puVar3 + 0x160) == (int *)0x0) ||

			// lev -> mesh_info
			(iVar4 = **(int **)(puVar3 + 0x160), iVar4 == 0)
		) ||

		// if bspRoot is nullptr
		(*(int *)(iVar4 + 0x18) == 0)
	 )
  {
	// short 0x16 -> byte 0x2c
    *(undefined4 *)(param_1 + 0x16) = 0;
  }

  // if bspRoot is valid
  else
  {
	// short 0x16 -> byte 0x2c
    *(int *)(param_1 + 0x16) = iVar4;

	// if camera -> ptrQuadblock
    if (*(int *)(param_2 + 0x1c) != 0)
	{
	  // COLL_PerQuadblock_CheckTriangles_Touching
      FUN_8001f41c(*(int *)(param_2 + 0x1c),param_1);
    }

    if (
			(param_1[0x1f] == 0) &&
			(
				// COLL_SearchTree_FindX, callback
				// COLL_PerBspLeaf_CheckQuadblocks_Touching
				FUN_8001ebec(*(undefined4 *)(*(int *)(param_1 + 0x16) + 0x18),param_1 + 0x18,FUN_8001f5f0,
						param_1), param_1[0x1f] == 0
			)
		)
	{
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cac) = 0xffffffff;
    }

    else {
      *(undefined4 *)(param_2 + 0x3c) = 1;
      puVar3 = PTR_DAT_8008d2ac;

	  // get quadblock from BSP
      iVar4 = *(int *)(param_1 + 0x40);

	  // new quadblock
	  *(int *)(param_2 + 0x1c) = iVar4;

      *(int *)(puVar3 + 0x1cac) =
           (iVar4 - *(int *)(**(int **)(puVar3 + 0x160) + 0xc)) * -0x1642c859 >> 2;
    }
  }
  return;
}


// CAM_Path_GetNumPoints
int FUN_80018b18(void)

{
  int iVar1;
  int *piVar2;
  short *psVar3;
  ushort uVar4;

  uVar4 = 0;

  // If LEV exists
  if (*(int *)(PTR_DAT_8008d2ac + 0x160) != 0)
  {
	// LEV -> SpawnType1
    piVar2 = *(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134);

    iVar1 = 0;

    if (
			// numPointers
			(*piVar2 < 3) ||

			(
				// get ptr_intro_cam
				psVar3 = (short *)piVar2[4],

				// ptr_intro_cam is nullptr
				psVar3 == (short *)0x0
			)
		) goto LAB_80018b98;

	while( true ) {
      if (*psVar3 == 0) break;
      uVar4 = uVar4 + *psVar3;
      psVar3 = psVar3 + 2 + (int)*psVar3 * 6;
    }
  }
  iVar1 = (uint)uVar4 << 0x10;
LAB_80018b98:
  return iVar1 >> 0x10;
}


// CAM_Path_Move
undefined4 FUN_80018ba0(int param_1,ushort *param_2,ushort *param_3,ushort *param_4)

{
  short sVar1;
  undefined4 uVar2;
  uint uVar3;
  short sVar4;
  ushort *puVar5;
  ushort *puVar6;
  ushort uVar7;

  // frame index
  sVar4 = (short)param_1;

  // get number of position on track
  sVar1 = FUN_80018b18();

  if (sVar4 < 0)
  {
	// return zero, function failed
    uVar2 = 0;
  }

  else
  {
	// ret value zero
    uVar2 = 0;

    if (sVar4 < sVar1)
	{
	  // LEV -> ptrSpawnType1 -> pointers[3] -- ST1_CAMERA_PATH
      puVar5 = *(ushort **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 0x10);

	  uVar3 = (uint)*puVar5;
      uVar7 = puVar5[1];
      puVar6 = puVar5 + 2;
      if ((short)*puVar5 <= sVar4) {
        do {
          param_1 = param_1 - uVar3;
          sVar4 = (short)param_1;
          puVar6 = puVar6 + (int)(short)uVar3 * 6;
          uVar3 = (uint)*puVar6;
          uVar7 = puVar6[1];
          puVar6 = puVar6 + 2;
        } while ((int)(uVar3 << 0x10) <= param_1 * 0x10000);
      }

	  // advance pointer to pos+rot
	  puVar6 = puVar6 + (int)sVar4 * 6;

      *param_4 = uVar7;

	  // position of frame
      *param_2 = *puVar6;
      param_2[1] = puVar6[1];
      param_2[2] = puVar6[2];

	  // rotation of frame
      *param_3 = ((short)puVar6[3] >> 4) + 0x800U & 0xfff;
      param_3[1] = puVar6[4] >> 4;
      uVar2 = 1;	// ret value 1
      param_3[2] = puVar6[5] >> 4;
    }
  }
  return uVar2;
}

// CAM_StartOfRace
void FUN_80018d20(int param_1)
// param1 is a pointer to a camera buffer
// param1 = 8008d2ac + 0x1498 + 0xdc*playerID
{
  undefined *puVar1;
  undefined2 uVar2;
  int iVar3;

  puVar1 = PTR_DAT_8008d2ac;

  // if fly-in camera data exists
  if (2 < *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x148)) {
    iVar3 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);
    *(undefined4 *)(param_1 + 0x94) = 0;
    *(undefined2 *)(param_1 + 0x8c) = 0;

	// make transition to driver last one second
    *(undefined2 *)(param_1 + 0x9e) = 0x1e;

	*(undefined2 *)(param_1 + 10) = 0;

	// when camera reaches player, be zoomed in
	*(undefined2 *)(param_1 + 0x9a) = 0;

	*(int *)(param_1 + 0x88) = iVar3 + 0x18;

	// if 1 or less screens
	// set fly-in to last 165 frames, (5.25 seconds)
    uVar2 = 0xa5;

	// if more than 1 screen
    if (1 < (byte)puVar1[0x1ca8])
	{
	  // set animation to last one frame
      uVar2 = 1;
    }

	// set cameraDC -> camera fly-in intro
    *(undefined2 *)(param_1 + 0x8e) = uVar2;
  }
  *(undefined2 *)(param_1 + 0x9a) = 0;

  // remove bit & 0x4 (battle end of race) and 0x1000 (idk)
  *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xffffeffb;
  return;
}


// CAM_EndOfRace_Battle
void FUN_80018d9c(int param_1,int param_2)

{
  undefined2 uVar1;
  long lVar2;

  // This is NOT TransitionTo,
  // spin360's spinSpeed (missing union)
  *(undefined2 *)(param_1 + 0xa4) = 0xffe5;

  // Activate end-of-race Battle flag
  *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 4;

  // Spin360_heightOffset_cameraPos[numPlyrCurrGame]
  uVar1 = *(undefined2 *)(&DAT_80080fd4 + (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] * 4);

  *(undefined2 *)(param_1 + 0xa8) = 0xc0;
  
  // for Spin360, this is an offset of height to player,
  // not an absolute height, like other functions
  *(undefined2 *)(param_1 + 0xa6) = uVar1;

  // Get direction from camera to driver
  lVar2 = ratan2((int)**(short **)(param_1 + 0x48) - (*(int *)(param_2 + 0x2d4) >> 8),
                 (int)(*(short **)(param_1 + 0x48))[2] - (*(int *)(param_2 + 0x2dc) >> 8));

  // Set camera to face the direction towards the driver
  *(undefined2 *)(param_1 + 0x90) = (short)lVar2;

  *(undefined2 *)(param_1 + 0x8c) = 0;

  // two timers each last two seconds
  *(undefined2 *)(param_1 + 0x8e) = 0x3c;
  *(undefined2 *)(param_1 + 0x9e) = 0x3c;
  return;
}


// initialize end-of-race camera
// param_1 cameraDC
// param_2 driver

// CAM_EndOfRace
void FUN_80018e38(int param_1, int param_2)

{
  // If you're not in Battle Mode
  if ((((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) &&

	  // LEV -> ptrSpawn1 -> numPointers
      (1 < **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))) &&

	  // if numPlyrCurrGame is less than 3
     ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3))
  {
	// This flag bit is for racing end-of-race,
	// a different flag bit is used for Battle

	// Activate end-of-race camera flag, inside CameraDC struct
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 0x20;
  }

  // if you're in Battle Mode
  else
  {
	// CAM_EndOfRace_Battle
    FUN_80018d9c(param_1, param_2);
  }
  return;
}


// CAM_StartLine_FlyIn_FixY
void FUN_80018ec0(undefined2 *param_1)

{
  int iVar1;
  int iVar2;
  short local_26;
  short sVar3;
  undefined2 local_20;
  short local_1e;
  undefined2 local_1c;
  undefined2 local_18;
  short local_16;
  undefined2 local_14;

  // lev -> mesh_info
  DAT_8008db48 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);

  // ground and wall
  DAT_8008db40 = 0x3000;

  DAT_8008db44 = 0;
  DAT_8008db3e = 2;
  local_20 = *param_1;
  local_26 = param_1[1];
  iVar2 = 0;
  local_1c = param_1[2];
  iVar1 = 0;
  do {
    sVar3 = (short)(iVar1 >> 6);
    local_1e = local_26 - (sVar3 + 0x400);
    local_16 = local_26 - (sVar3 + -0x100);
    local_18 = local_20;
    local_14 = local_1c;

	// COLL_SearchTree_FindQuadblock_Touching
    FUN_8001eb0c(&local_20,&local_18,&DAT_8008db1c,0,local_20,local_1c);

	iVar2 = iVar2 + 1;
    sVar3 = DAT_8008db3a;
    if (DAT_8008db5a != 0) break;
    iVar1 = iVar2 * 0x10000;
    sVar3 = local_26;
  } while (iVar2 * 0x10000 >> 0x10 < 8);
  param_1[1] = sVar3;
  return;
}


// CAM_ProcessTransition
// param1 camera pos return value
// param2 camera rot return value
// param3 camera pos start
// param4 camera rot start
// param5 camera pos end
// param6 camera rot end
// param7 frame counter
void FUN_80018fec(short *param_1,ushort *param_2,short *param_3,short *param_4,short *param_5,
                 short *param_6,int param_7)
{
  uint uVar1;

  *param_1 = *param_3 + (short)(((int)*param_5 - (int)*param_3) * param_7 >> 0xc);
  param_1[1] = param_3[1] + (short)(((int)param_5[1] - (int)param_3[1]) * param_7 >> 0xc);
  param_1[2] = param_3[2] + (short)(((int)param_5[2] - (int)param_3[2]) * param_7 >> 0xc);
  uVar1 = (int)*param_6 - (int)*param_4 & 0xfff;
  if (0x7ff < uVar1) {
    uVar1 = uVar1 - 0x1000;
  }
  *param_2 = *param_4 + (short)((int)(uVar1 * param_7) >> 0xc) & 0xfff;
  uVar1 = (int)param_6[1] - (int)param_4[1] & 0xfff;
  if (0x7ff < uVar1) {
    uVar1 = uVar1 - 0x1000;
  }
  param_2[1] = param_4[1] + (short)((int)(uVar1 * param_7) >> 0xc) & 0xfff;
  uVar1 = (int)param_6[2] - (int)param_4[2] & 0xfff;
  if (0x7ff < uVar1) {
    uVar1 = uVar1 - 0x1000;
  }
  param_2[2] = param_4[2] + (short)((int)(uVar1 * param_7) >> 0xc) & 0xfff;
  return;
}

// CAM_FollowDriver_AngleAxis (camera->0x9a is 0x8 or 0xe)
// param_1 is cameraDC
// param_2 is driver object
// param_4 is pushBuffer pos
// param_5 is pushBuffer rot
// only called from ThTick (camera->0x9a is 0x8 or 0xe)
void FUN_80019128(int param_1,int param_2,int param_3,short *param_4,short *param_5)
{
  long lVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined auStack64 [32];

  puVar6 = auStack64;
  puVar5 = auStack64;

  // debug feature:
  // if camera is at the center of the driver (where driver collides with ground)
  if (*(short *)(param_1 + 0x9a) == 0xe)
  {
	// VehPhysForce_RotAxisAngle
    FUN_8005f89c((MATRIX *)(param_3 + 0x220),param_2 + 0x368,(int)*(short *)(param_2 + 0x39a));
    gte_SetRotMatrix((MATRIX *)(param_3 + 0x220));
    puVar6 = puVar5;
  }

  // if you have any other "normal" camera feature
  else
  {
	// VehPhysForce_RotAxisAngle
    FUN_8005f89c((MATRIX *)(param_3 + 0x220),param_2 + 0x368,(int)*(short *)(param_2 + 0x2ee));
    gte_SetRotMatrix((MATRIX *)(param_3 + 0x220));
  }

  // driver -> selfInstance -> matrix
  gte_SetTransMatrix((MATRIX *)(*(int *)(param_2 + 0x1c) + 0x30));

  // driverOffset_CamEyePos
  gte_ldVXY0(*(undefined4 *)(param_1 + 0x74));
  gte_ldVZ0((uint)*(ushort *)(param_1 + 0x78));
  gte_rt();

  uVar3 = gte_stMAC1();
  *(undefined4 *)(param_3 + 0x240) = uVar3;
  uVar3 = gte_stMAC2();
  *(undefined4 *)(param_3 + 0x244) = uVar3;
  uVar3 = gte_stMAC3();
  *(undefined4 *)(param_3 + 0x248) = uVar3;

  // driverOffset_CamLookAtPos
  gte_ldVXY0(*(undefined4 *)(param_1 + 0x7c));
  gte_ldVZ0((uint)*(ushort *)(param_1 + 0x80));
  gte_rt();

  uVar3 = gte_stMAC1();
  *(undefined4 *)(puVar6 + 0x10) = uVar3;
  uVar4 = gte_stMAC2();
  *(undefined4 *)(puVar6 + 0x14) = uVar4;
  uVar4 = gte_stMAC3();
  *(undefined4 *)(puVar6 + 0x18) = uVar4;

  if ((*(uint *)(param_1 + 0x70) & 8) == 0)
  {
    *(int *)(param_3 + 0x240) =
         (0x100 - *(short *)(param_1 + 0x7a)) * *(int *)(param_3 + 0x240) +
         (int)*(short *)(param_1 + 0x7a) * (int)*param_4 >> 8;
    *(int *)(param_3 + 0x244) =
         (0x100 - *(short *)(param_1 + 0x7a)) * *(int *)(param_3 + 0x244) +
         (int)*(short *)(param_1 + 0x7a) * (int)param_4[1] >> 8;
    *(int *)(param_3 + 0x248) =
         (0x100 - *(short *)(param_1 + 0x7a)) * *(int *)(param_3 + 0x248) +
         (int)*(short *)(param_1 + 0x7a) * (int)param_4[2] >> 8;
    iVar2 = (int)*(short *)(param_1 + 0x7a);
	
	// 0x64 - 0x6c (triplet[3])
	// interpolate from stack->10 (CamLookAtPos) GTE
    *(int *)(param_1 + 100) =
         (0x100 - iVar2) * *(int *)(puVar6 + 0x10) + iVar2 * *(int *)(param_1 + 100) >> 8;
    *(int *)(param_1 + 0x68) =
         (0x100 - iVar2) * *(int *)(puVar6 + 0x14) + iVar2 * *(int *)(param_1 + 0x68) >> 8;
    *(int *)(param_1 + 0x6c) =
         (0x100 - iVar2) * *(int *)(puVar6 + 0x18) + iVar2 * *(int *)(param_1 + 0x6c) >> 8;
  }

  else
  {
	// copy directly from stack->10 (CamLookAtPos) GTE
    *(undefined4 *)(param_1 + 100) = uVar3;
    *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(puVar6 + 0x14);
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(puVar6 + 0x18);
  }

  *(int *)(param_3 + 0x24c) = *(int *)(param_3 + 0x240) - *(int *)(param_1 + 100);
  *(int *)(param_3 + 0x250) = *(int *)(param_3 + 0x244) - *(int *)(param_1 + 0x68);
  iVar2 = *(int *)(param_3 + 0x248) - *(int *)(param_1 + 0x6c);
  *(int *)(param_3 + 0x254) = iVar2;

  lVar1 = ratan2(*(long *)(param_3 + 0x24c),iVar2);
  param_5[1] = (short)lVar1;

  // SquareRoot0_stub
  lVar1 = FUN_8006c618(*(int *)(param_3 + 0x24c) * *(int *)(param_3 + 0x24c) +
                       *(int *)(param_3 + 0x254) * *(int *)(param_3 + 0x254));
  
  lVar1 = ratan2(*(long *)(param_3 + 0x250),lVar1);

  *param_5 = 0x800 - (short)lVar1;
  param_5[2] = 0;

  *param_4 = *(short *)(param_3 + 0x240);
  param_4[1] = *(short *)(param_3 + 0x244);
  param_4[2] = *(short *)(param_3 + 0x248);
  return;
}

// CAM_StartLine_FlyIn
// param2 - const 0x96
// param3 - frame index
// param4 - camera TransitionTo pos
// param5 - camera TransitionTo rot
void FUN_800194c8(int *param_1,short param_2,int param_3,ushort *param_4,short *param_5)

{
  short sVar1;
  long x;
  int iVar2;
  short *psVar3;
  int iVar4;
  uint uVar5;
  short *psVar6;
  short sVar7;
  int iVar8;
  SVECTOR local_78;
  SVECTOR local_70;
  MATRIX MStack104;
  undefined2 local_48;
  short local_46;
  undefined2 local_44;
  ushort local_40 [2];
  ushort local_3c;
  ushort local_38;
  short local_30;
  short local_2e;
  short local_2c;
  long alStack40 [2];

  // frame index
  iVar4 = (param_3 << 0x10) >> 4;

  // max number of frames
  iVar2 = (int)param_2;

  // divide?
  iVar8 = iVar4 / iVar2;

  if (iVar2 == 0) {
    trap(0x1c00);
  }
  if ((iVar2 == -1) && (iVar4 == -0x80000000)) {
    trap(0x1800);
  }
  iVar2 = (int)*(short *)(param_1 + 2);
  sVar7 = *(short *)((int)param_1 + 10);
  if (*(short *)((int)param_1 + 10) < iVar2) {
    sVar7 = *(short *)(param_1 + 2);
  }
  sVar1 = (short)(sVar7 * iVar8 >> 0xc);
  if ((int)sVar1 < iVar2 + -1) {
    psVar6 = (short *)(*param_1 + (int)sVar1 * 6);
    iVar4 = iVar8;
  }
  else {
    iVar4 = 0;
    psVar6 = (short *)(*param_1 + iVar2 * 6 + -0xc);
  }
  if ((int)sVar1 < (int)*(short *)((int)param_1 + 10) + -1) {
    psVar3 = (short *)(param_1[1] + (int)sVar1 * 6);
  }
  else {
    iVar8 = 0;
    psVar3 = (short *)(param_1[1] + (int)*(short *)((int)param_1 + 10) * 6 + -0xc);
  }
  uVar5 = sVar7 * iVar4 & 0xfff;
  local_78.vx = *psVar6 + (short)((int)(((int)psVar6[3] - (int)*psVar6) * uVar5) >> 0xc);
  local_78.vy = psVar6[1] + (short)((int)(((int)psVar6[4] - (int)psVar6[1]) * uVar5) >> 0xc);
  local_78.vz = psVar6[2] + (short)((int)(((int)psVar6[5] - (int)psVar6[2]) * uVar5) >> 0xc);
  uVar5 = sVar7 * iVar8 & 0xfff;
  local_70.vx = *psVar3 + (short)((int)(((int)psVar3[3] - (int)*psVar3) * uVar5) >> 0xc);
  local_70.vy = psVar3[1] + (short)((int)(((int)psVar3[4] - (int)psVar3[1]) * uVar5) >> 0xc) + -0x60
  ;
  local_70.vz = psVar3[2] + (short)((int)(((int)psVar3[5] - (int)psVar3[2]) * uVar5) >> 0xc);

  // rotation data
  local_48 = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x72);
  local_44 = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x76);
  local_46 = *(short *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x74) + 0x400;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(&MStack104,&local_48);

  iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x160);

  // overwrites Y variables that are
  // used later in MStack104.t[1]

  // CAM_StartLine_FlyIn_FixY
  FUN_80018ec0(iVar8 + 0x78); // &lev->DriverSpawn[1]
  FUN_80018ec0(iVar8 + 0x84); // &lev->DriverSpawn[2]
  FUN_80018ec0(iVar8 + 0xa8); // &lev->DriverSpawn[5]

  // get midpoint between driver[1] and driver[2],
  // make matrix from that for camera
  MStack104.t[0] =
       (int)*(short *)(iVar8 + 0x78) +
       ((int)*(short *)(iVar8 + 0x84) - (int)*(short *)(iVar8 + 0x78)) / 2;
  MStack104.t[1] =
       (int)*(short *)(iVar8 + 0x7a) +
       ((int)*(short *)(iVar8 + 0x86) - (int)*(short *)(iVar8 + 0x7a)) / 2 + 0x40;
  MStack104.t[2] =
       (int)*(short *)(iVar8 + 0x7c) +
       ((int)*(short *)(iVar8 + 0x88) - (int)*(short *)(iVar8 + 0x7c)) / 2;

  SetRotMatrix(&MStack104);
  SetTransMatrix(&MStack104);
  RotTrans(&local_78,(VECTOR *)local_40,alStack40);

  // camera TransitionTo pos
  *param_4 = local_40[0];
  param_4[1] = local_3c;
  param_4[2] = local_38;

  RotTrans(&local_70,(VECTOR *)local_40,alStack40);

  local_30 = (short)((uint)*param_4 - (uint)local_40[0]);
  local_2e = param_4[1] - local_3c;
  local_2c = (short)((uint)param_4[2] - (uint)local_38);

  // Camera Y rotation
  x = ratan2((int)(((uint)*param_4 - (uint)local_40[0]) * 0x10000) >> 0x10,
             (int)(((uint)param_4[2] - (uint)local_38) * 0x10000) >> 0x10);
  param_5[1] = (short)x;

  x = SquareRoot0((int)local_30 * (int)local_30 + (int)local_2c * (int)local_2c);

  // Camera X rotation
  x = ratan2((int)local_2e,x);
  *param_5 = 0x800 - (short)x;

  // Camera Z rotation
  param_5[2] = 0;
  return;
}

// CAM_FollowDriver_TrackPath
// param_1 CameraDC
// param_3 CameraDC + 0xB0 (speed)
uint FUN_800198f8(int param_1,short *param_2,int param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  short *psVar7;
  short *psVar8;
  short *psVar9;
  int iVar10;
  int iVar11;
  int local_30;
  int local_2c;
  int local_28;

  // if camera has negative speed
  if (param_3 < 1) {
    psVar9 = *(short **)(param_1 + 0x88);

	// lev -> restartPts (warpball path)
    psVar8 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                      (uint)*(byte *)(psVar9 + 4) * 0xc);

	if (((*(uint *)(param_1 + 0x70) & 0x100) != 0) && (*(byte *)((int)psVar9 + 9) != 0xff))
	{
	  // lev -> restartPts (warpball path)
      psVar8 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                        (uint)*(byte *)((int)psVar9 + 9) * 0xc);
    }

    local_30 = (int)*psVar8 - (int)*psVar9;
    local_2c = (int)psVar8[1] - (int)psVar9[1];
    local_28 = (int)psVar8[2] - (int)psVar9[2];
    iVar3 = SquareRoot0(local_30 * local_30 + local_2c * local_2c + local_28 * local_28);

	// If game is not paused
    if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) {
      iVar10 = *(int *)(param_1 + 0x94) - param_3;
    }
    else {
      iVar10 = 0;
    }
    while (psVar7 = psVar8, bVar2 = iVar3 <= iVar10, iVar10 = iVar10 - iVar3, bVar2)
	{
	  // lev -> restartPts (warpball path)
      psVar8 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                        (uint)*(byte *)(psVar7 + 4) * 0xc);

      if (((*(uint *)(param_1 + 0x70) & 0x100) != 0) && (*(byte *)((int)psVar7 + 9) != 0xff))
	  {
		// lev -> restartPts (warpball path)
        psVar8 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                          (uint)*(byte *)((int)psVar7 + 9) * 0xc);
      }

      local_30 = (int)*psVar8 - (int)*psVar7;
      local_2c = (int)psVar8[1] - (int)psVar7[1];
      local_28 = (int)psVar8[2] - (int)psVar7[2];
      iVar3 = SquareRoot0(local_30 * local_30 + local_2c * local_2c + local_28 * local_28);
      psVar9 = psVar7;
    }
    iVar10 = iVar10 + iVar3;
  }

  // if camera has positive speed
  else {
    psVar9 = *(short **)(param_1 + 0x88);

	// lev -> restartPts (warpball path)
    psVar7 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                      (uint)*(byte *)(psVar9 + 5) * 0xc);

    if (((*(uint *)(param_1 + 0x70) & 0x100) != 0) && (*(byte *)((int)psVar9 + 0xb) != 0xff))
	{
	  // lev -> restartPts (warpball path)
      psVar7 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                        (uint)*(byte *)((int)psVar9 + 0xb) * 0xc);
    }

    local_30 = (int)*psVar7 - (int)*psVar9;
    local_2c = (int)psVar7[1] - (int)psVar9[1];
    local_28 = (int)psVar7[2] - (int)psVar9[2];
    iVar3 = SquareRoot0(local_30 * local_30 + local_2c * local_2c + local_28 * local_28);

	// If game is not paused
    if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) {
      iVar10 = *(int *)(param_1 + 0x94) + param_3;
    }
    else {
      iVar10 = 0;
    }
    if (iVar3 <= iVar10) {
      iVar10 = iVar10 - iVar3;
      do {
        psVar9 = psVar7;

		// lev -> restartPts (warpball path)
        psVar7 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                          (uint)*(byte *)(psVar9 + 5) * 0xc);

        if (((*(uint *)(param_1 + 0x70) & 0x100) != 0) && (*(byte *)((int)psVar9 + 0xb) != 0xff))
		{
		  // lev -> restartPts (warpball path)
          psVar7 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                            (uint)*(byte *)((int)psVar9 + 0xb) * 0xc);
        }

        local_30 = (int)*psVar7 - (int)*psVar9;
        local_2c = (int)psVar7[1] - (int)psVar9[1];
        local_28 = (int)psVar7[2] - (int)psVar9[2];
        iVar3 = SquareRoot0(local_30 * local_30 + local_2c * local_2c + local_28 * local_28);
        bVar2 = iVar3 <= iVar10;
        iVar10 = iVar10 - iVar3;
      } while (bVar2);
      iVar10 = iVar10 + iVar3;
    }
  }
  if (param_4 != 0) {
    *(int *)(param_1 + 0x94) = iVar10;
    *(short **)(param_1 + 0x88) = psVar9;
  }
  if (iVar3 == 0) {
    iVar11 = 0;
  }
  else {
    iVar11 = (iVar10 << 0xc) / iVar3;
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (iVar10 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
  }

  // save results
  *param_2 = *psVar9 + (short)(local_30 * iVar11 >> 0xc);
  param_2[1] = psVar9[1] + (short)(local_2c * iVar11 >> 0xc) + 0x80;
  param_2[2] = psVar9[2] + (short)(local_28 * iVar11 >> 0xc);
  lVar4 = ratan2(local_30,local_28);

  // negative speed
  if (param_3 < 1)
  {
	// lev -> restartPts (warpball path)
    iVar3 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);
    psVar8 = (short *)(iVar3 + (uint)*(byte *)(psVar7 + 4) * 0xc);
    if ((*(uint *)(param_1 + 0x70) & 0x100) == 0) goto LAB_80019e08;
    bVar1 = *(byte *)((int)psVar7 + 9);
  }

  // positive speed
  else
  {
	// lev -> restartPts (warpball path)
    iVar3 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);
    psVar8 = (short *)(iVar3 + (uint)*(byte *)(psVar7 + 5) * 0xc);
    if ((*(uint *)(param_1 + 0x70) & 0x100) == 0) goto LAB_80019e08;
    bVar1 = *(byte *)((int)psVar7 + 0xb);
  }

  if (bVar1 != 0xff) {
    psVar8 = (short *)(iVar3 + (uint)bVar1 * 0xc);
  }
LAB_80019e08:
  lVar5 = ratan2((int)*psVar8 - (int)*psVar7,(int)psVar8[2] - (int)psVar7[2]);
  uVar6 = (lVar5 + 0x800) - (lVar4 + 0x800) & 0xfff;
  if (0x7ff < uVar6) {
    uVar6 = uVar6 - 0x1000;
  }
  return lVar4 + 0x800 + ((int)(uVar6 * iVar11) >> 0xc) & 0xfff;
}

// CAM_LookAtPosition
// param2 driver position
// param3 camera transitionTo pos
// param4 camera transitionTo rot
void FUN_80019e7c(int param_1,int *param_2,short *param_3,short *param_4)

{
  long x;
  int y;
  int x_00;

  // camera dirX
  y = (int)*param_3 - (*param_2 >> 8);

  // dirX
  *(int *)(param_1 + 0x24c) = y;

  // dirY
  *(int *)(param_1 + 0x250) =

		// camera dirY, plus zoom,
		// plus Spin360_heightOffset_driverPos
       (int)param_3[1] - ((param_2[1] >> 8) + *(int *)(&DAT_80080fe8 + (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] * 4));

  // camera dirZ
  x_00 = (int)param_3[2] - (param_2[2] >> 8);

  // dirZ
  *(int *)(param_1 + 0x254) = x_00;

  // angle with dirX and dirZ
  x = ratan2(y,x_00);

  // rotY (left, right)
  param_4[1] = (short)x;

  // distance to driver
  x = SquareRoot0(*(int *)(param_1 + 0x24c) * *(int *)(param_1 + 0x24c) +
                   *(int *)(param_1 + 0x254) * *(int *)(param_1 + 0x254));

  // dirY / distance
  x = ratan2(*(long *)(param_1 + 0x250),x);

  // rotX (up, down)
  *param_4 = 0x800 - (short)x;

  // rotZ
  param_4[2] = 0;

  return;
}

// CAM_FollowDriver_Spin360
// param1 CameraDC
// param3 driver
// param4 camera transitionTo pos
// param5 camera transitionTo rot
void FUN_80019f58(int param_1,undefined4 param_2,int param_3,short *param_4,undefined4 param_5)

{
  short sVar1;
  int iVar2;

  // even number driver
  if ((*(byte *)(param_3 + 0x4a) & 1) == 0)
  {
	// rotate one way
	// posX
    sVar1 = *(short *)(param_1 + 0xa4);
  }

  // odd number driver
  else
  {
	// rotate other way
	// -posX
    sVar1 = -*(short *)(param_1 + 0xa4);
  }

  // spin angle
  *(short *)(param_1 + 0x90) = *(short *)(param_1 + 0x90) + sVar1;

  // posY
  param_4[1] = *(short *)(param_1 + 0xa6) + (short)((uint)*(undefined4 *)(param_3 + 0x2d8) >> 8);

  // Sine(angle)
  iVar2 = FUN_8003d184((int)*(short *)(param_1 + 0x90));

  // posX
  *param_4 = (short)((uint)*(undefined4 *)(param_3 + 0x2d4) >> 8) +
             (short)(iVar2 * *(short *)(param_1 + 0xa8) >> 0xc);

  // Cosine(angle)
  iVar2 = FUN_8003d1c0((int)*(short *)(param_1 + 0x90));

  // posZ
  param_4[2] = (short)((uint)*(undefined4 *)(param_3 + 0x2dc) >> 8) +
               (short)(iVar2 * *(short *)(param_1 + 0xa8) >> 0xc);

  // CAM_LookAtPosition
  FUN_80019e7c(param_2,param_3 + 0x2d4,param_4,param_5);
  return;
}

// CAM_SetDesiredPosRot
void FUN_8001a054(int param_1,undefined2 *param_2,undefined2 *param_3)

{
  undefined2 uVar1;

  // set desired position
  *(undefined2 *)(param_1 + 0xa4) = *param_2;
  *(undefined2 *)(param_1 + 0xa6) = param_2[1];
  *(undefined2 *)(param_1 + 0xa8) = param_2[2];

  // set desired rotation
  *(undefined2 *)(param_1 + 0xaa) = *param_3;
  *(undefined2 *)(param_1 + 0xac) = param_3[1];
  uVar1 = param_3[2];

  // make transition last one second
  *(undefined2 *)(param_1 + 0x9e) = 0x1e;

  *(undefined2 *)(param_1 + 0x8e) = 0;
  *(undefined2 *)(param_1 + 0x8c) = 0x1000;

  // begin transition by activating flag
  *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 0x200;

  *(undefined2 *)(param_1 + 0xae) = uVar1;
  return;
}

// CAM_FollowDriver_Normal
// param1 is CameraDC,
// param2 is driver object
// param3 is PushBuffer
// param4 is scratchpad (BSP stuff)
// param5 is ZoomData (becomes $s3)
// NOP mid-race to stop following driver,
// also handles fly-in and adv hub transitions
void FUN_8001a0bc(int param_1,int param_2,short *param_3,int param_4,short *param_5)

{
  char cVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  bool bVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined4 in_zero;
  undefined4 in_at;
  undefined2 uVar8;
  ushort uVar9;
  short sVar10;
  int x;
  long x_00;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  int local_30;
  int local_2c;
  undefined2 local_28;
  undefined2 local_26;

  // get camera flags
  uVar13 = *(uint *)(param_1 + 0x70);

  // disable Reverse Cam,
  // assuming you dont hold R2
  uVar11 = uVar13 & 0xfffeffff;

  // set new flags
  *(uint *)(param_1 + 0x70) = uVar11;

  if (
		(
			// If this is human and not AI
			((*(uint *)(param_2 + 0x2c8) & 0x100000) == 0) &&

			// If not drawing intro-race cutscene
			((*(uint *)PTR_DAT_8008d2ac & 0x40) == 0)
		)

		// If you are holding R2
     && ((*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_2 + 0x4a) * 0x50 + 0x10) & 0x200) != 0)
     )
  {
	// Reverse the camera
    *(uint *)(param_1 + 0x70) = uVar11 | 0x10000;
  }

  // if camera just changed direction
  // (either forward to reverse, or reverse to forward)
  if (uVar13 != *(uint *)(param_1 + 0x70))
  {
	// set flag that view just changed this frame
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 8;
  }

  // 0 = forwards
  // 0x800 = backwards
  sVar10 = (ushort)((*(uint *)(param_1 + 0x70) & 0x10000) != 0) * 0x800;

  // if camera angle was not just changed
  if ((*(uint *)(param_1 + 0x70) & 8) == 0) 
  {
	// absolute value driver speed
    x = (int)*(short *)(param_2 + 0x38e);
    if (x < 0) {
      x = -x;
    }

	// driver speed slower than camera speed
    if (x < *(int *)(param_1 + 0x40)) 
	{
	  // transition inward
      uVar13 = (uint)*(byte *)((int)param_5 + 9);
      uVar11 = (uint)*(byte *)((int)param_5 + 8);
    }
	
	// driver speed faster than camera
    else 
	{
	  // transition outward
      uVar13 = (uint)*(byte *)((int)param_5 + 8);
      uVar11 = uVar13;
    }

	// cameraSpeed = iVar11% of cameraSpeed + (flip%)*driverSpeed
    *(int *)(param_1 + 0x40) = (int)(uVar11 * *(int *)(param_1 + 0x40) + (0x100 - uVar13) * x) >> 8;
  }

  // if camera angle changed
  else 
  {
	// absolute value driver speed
    x = (int)*(short *)(param_2 + 0x38e);
    if (x < 0) {
      x = -x;
    }

	// cameraSpeed = driverSpeed
	*(int *)(param_1 + 0x40) = x;
  }
  
  uVar8 = 0;
  
  // if numPlyrCurrGame != 2
  if (PTR_DAT_8008d2ac[0x1ca8] != '\x02') {
    uVar8 = 0xff9c;
  }
  
  *(undefined2 *)(param_4 + 0x20c) = uVar8;

  // 0x20e
  // camera RotY
  *(ushort *)(param_4 + 0x20e) =
	*(short *)(param_2 + 0x2f2) + // camera rotation
	*(short *)(param_2 + 0x39a) + // player rotation
	0x800 + 					  // constant value
	sVar10 & 0xfff;				  // 0x800 only if reverse cam is active

  *(short *)(param_4 + 0x210) = *(short *)(param_1 + 0x10) * -2;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(param_4 + 0x220,param_4 + 0x20c);

  // CameraDC flag 0x80
  if (((*(uint *)(param_1 + 0x70) & 0x80) != 0) &&
     (x = (int)((uint)*(ushort *)(param_2 + 0x3e4) << 0x10) >> 0x14, *(int *)(param_1 + 0xbc) < x))
  {
    *(int *)(param_1 + 0xbc) = x;
  }
  *(undefined2 *)(param_4 + 0x20c) = 0;
  *(undefined2 *)(param_4 + 0x20e) = 0;

  // Map cameraSpeed from:
  //	[ZoomData 0x4, ZoomData 0x6]
  //	[ZoomData 0x0, ZoomData 0x2]
  uVar8 = FUN_80058f9c(*(undefined4 *)(param_1 + 0x40),
						(int)param_5[2],
						(int)param_5[3],
						(int)*param_5,
						(int)param_5[1]);
						
  *(undefined2 *)(param_4 + 0x210) = uVar8;

  if (*(int *)(param_1 + 0xbc) == 0)
  {
    if (
			// compare &&
			(*(int *)(param_1 + 0xb8) != 0) &&

			(
				// assignment						// elapsed milliseconds per frame, ~32
				x = *(int *)(param_1 + 0xb8) + *(int *)(PTR_DAT_8008d2ac + 0x1d04) * -0x10,

				// assignment
				*(int *)(param_1 + 0xb8) = x,

				// compare <
				x < 0
			)
	    )
	{
      *(undefined4 *)(param_1 + 0xb8) = 0;
    }
  }
  else
  {
	// 0xb8 is a countdown timer in MS
	// that has a maximum value of 0x6000

									// elapsed milliseconds per frame, ~32
    x = *(int *)(param_1 + 0xb8) + *(int *)(PTR_DAT_8008d2ac + 0x1d04) * 0x40;
    *(int *)(param_1 + 0xb8) = x;
    if (0x6000 < x) {
      *(undefined4 *)(param_1 + 0xb8) = 0x6000;
    }

	// 0xbc is a countdown timer in MS
	// that has a maximum value of 0

									// elapsed milliseconds per frame, ~32
    x = *(int *)(param_1 + 0xbc) - *(int *)(PTR_DAT_8008d2ac + 0x1d04);
    *(int *)(param_1 + 0xbc) = x;
    if (x < 0) {
      *(undefined4 *)(param_1 + 0xbc) = 0;
    }
  }
  *(short *)(param_4 + 0x210) =
       *(short *)(param_4 + 0x210) + (short)((uint)*(undefined4 *)(param_1 + 0xb8) >> 8);

  gte_SetRotMatrix((MATRIX *)(param_4 + 0x220));
  pSVar12 = (SVECTOR *)(param_4 + 0x20c);
  gte_ldv0(pSVar12);
  gte_rtv0();
  gte_stlvnl((VECTOR *)(param_4 + 0x240));
  *(undefined2 *)(param_4 + 0x20c) = 0;
  *(undefined2 *)(param_4 + 0x20e) = 0x40;
  *(undefined2 *)(param_4 + 0x210) = 0;
  gte_ldv0(pSVar12);
  gte_rtv0();
  gte_stlvnl((VECTOR *)(param_4 + 0x27c));

  *(int *)(param_4 + 600) = *(int *)(param_2 + 0x2d4) >> 8;
  *(int *)(param_4 + 0x25c) = *(int *)(param_2 + 0x2d8) >> 8;
  x = *(int *)(param_2 + 0x2dc);
  *(int *)(param_4 + 600) = *(int *)(param_4 + 600) + *(int *)(param_4 + 0x27c);
  x = x >> 8;
  *(int *)(param_4 + 0x260) = x;
  *(int *)(param_4 + 0x260) = x + *(int *)(param_4 + 0x284);
  *(int *)(param_4 + 0x240) = *(int *)(param_4 + 0x240) + *(int *)(param_4 + 600);

  // CameraDC flag 0x10
  if ((*(uint *)(param_1 + 0x70) & 0x10) == 0) {
    *(int *)(param_4 + 0x244) =
         *(int *)(param_4 + 0x244) + *(int *)(param_4 + 0x25c) + (int)param_5[8];
  }
  else {
    *(int *)(param_4 + 0x244) =
         (*(int *)(param_2 + 0x2d0) >> 8) + (int)*(short *)(param_1 + 0x98) + (int)param_5[8];
  }
  puVar6 = PTR_DAT_8008d2ac;
  *(int *)(param_4 + 0x248) = *(int *)(param_4 + 0x248) + *(int *)(param_4 + 0x260);

  // rotX
  uVar8 = 0;

  // if numPlyrCurrGame is not 2
  if (puVar6[0x1ca8] != '\x02') {
    uVar8 = 0xff9c;
  }

  // rotX
  *(undefined2 *)(param_4 + 0x20c) = uVar8;

  // camera rotation
  sVar2 = *(short *)(param_2 + 0x2f2);

  // player rotation
  sVar3 = *(short *)(param_2 + 0x39a);

  sVar4 = *(short *)(param_2 + 0x3c6);

  // rotZ
  *(undefined2 *)(param_4 + 0x210) = 0;

  // rotY
  *(ushort *)(param_4 + 0x20e) = sVar4 + sVar3 + sVar2 + 0x800 + sVar10 & 0xfff;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(param_4 + 0x220,param_4 + 0x20c);

  *(undefined2 *)(param_4 + 0x20c) = 0;
  *(undefined2 *)(param_4 + 0x20e) = 0;

  //if racer is not damaged
  if ((*(uint *)(param_2 + 0x2c8) & 0x4000) == 0) {
    sVar10 = *(short *)(param_1 + 0x1a) + -8;
    *(short *)(param_1 + 0x1a) = sVar10;
    if (sVar10 < -0x20) {
      *(undefined2 *)(param_1 + 0x1a) = 0xffe0;
    }
  }
  //if racer is damaged
  else {
    uVar9 = *(short *)(param_1 + 0x1a) + 8;
    *(ushort *)(param_1 + 0x1a) = uVar9;
    if (0 < (int)((uint)uVar9 << 0x10)) {
      *(undefined2 *)(param_1 + 0x1a) = 0;
    }
  }
  *(undefined2 *)(param_4 + 0x210) = *(undefined2 *)(param_1 + 0x1a);

  gte_SetRotMatrix((MATRIX *)(param_4 + 0x220));
  pSVar12 = (SVECTOR *)(param_4 + 0x20c);
  gte_ldv0(pSVar12);
  gte_rtv0();
  gte_stsv(pSVar12);

  *(int *)(param_4 + 600) = *(int *)(param_4 + 600) + (int)*(short *)(param_4 + 0x20c);
  sVar10 = param_5[7];
  *(int *)(param_4 + 0x260) = *(int *)(param_4 + 0x260) + (int)*(short *)(param_4 + 0x210);
  *(int *)(param_4 + 0x25c) =
       *(int *)(param_4 + 0x25c) + (int)*(short *)(param_4 + 0x20e) + (int)sVar10;
  *(undefined2 *)(param_1 + 0x10) =
       (short)((uint)((int)param_5[6] * (int)*(short *)(param_1 + 0x10) +
                     (0x100 - (int)param_5[6]) * (int)*(short *)(param_2 + 0x2f0)) >> 8);
  //cVar1 = kart state
  cVar1 = *(char *)(param_2 + 0x376);

  //if kart is being mask grabbed
  if (cVar1 == '\x05')
  {
	// pushBuffer position
    *(int *)(param_4 + 0x240) = (int)*param_3;
    *(int *)(param_4 + 0x244) = (int)param_3[1];
    *(int *)(param_4 + 0x248) = (int)param_3[2];

	// reset camera interpolation
    *(undefined2 *)(param_1 + 0xc4) = 0;
    *(undefined2 *)(param_1 + 0xc0) = 0;
    *(undefined2 *)(param_1 + 0xc2) = 0;

	// kart state
    cVar1 = *(char *)(param_2 + 0x376);
  }

  //if kart is in forced stillness
  if (cVar1 == '\x04')
  {
	// reset camera interpolation
    *(undefined2 *)(param_1 + 0xc4) = 0;
    *(undefined2 *)(param_1 + 0xc0) = 0;
    *(undefined2 *)(param_1 + 0xc2) = 0;
  }
  //if kart is not being blasted, racer is on the ground and (?)
  if (((*(char *)(param_2 + 0x376) != '\x06') && ((*(uint *)(param_2 + 0x2c8) & 1) != 0)) &&
     (*(short *)(param_1 + 0xc6) != 0))
  {
	// camera distance = camera speed, minus camera position
    *(short *)(param_1 + 0xd4) = *(short *)(param_1 + 0x58) - *(short *)(param_4 + 0x240);
    *(short *)(param_1 + 0xd6) = *(short *)(param_1 + 0x5c) - *(short *)(param_4 + 0x244);
    *(short *)(param_1 + 0xd8) = *(short *)(param_1 + 0x60) - *(short *)(param_4 + 0x248);

    *(short *)(param_1 + 0xcc) = *(short *)(param_1 + 100) - *(short *)(param_4 + 600);
    *(short *)(param_1 + 0xce) = *(short *)(param_1 + 0x68) - *(short *)(param_4 + 0x25c);
    sVar10 = *(short *)(param_4 + 0x260);
    *(undefined2 *)(param_1 + 0xda) = 8;
    *(undefined2 *)(param_1 + 0xc6) = 0;
    *(short *)(param_1 + 0xd0) = *(short *)(param_1 + 0x6c) - sVar10;
  }

  // if not arcade end-of-race
  if (((*(uint *)(param_1 + 0x70) & 0x20) == 0) && (*(short *)(param_1 + 0x9a) == 0)) {
    if ((*(char *)(param_2 + 0x376) != '\x06') && (*(short *)(param_1 + 0xc6) == 0))
    goto LAB_8001a8c0;
    if (*(short *)(param_1 + 0xc6) == 0) {
      *(short *)(param_1 + 200) = *(short *)(param_1 + 0x68) - *(short *)(param_1 + 0x5c);
      *(short *)(param_1 + 0xca) =
           *(short *)(param_1 + 0x5c) - (short)((uint)*(undefined4 *)(param_2 + 0x2d0) >> 8);
    }
    *(undefined2 *)(param_1 + 0xc6) = 1;
    if ((*(int *)(param_1 + 0x5c) < *(int *)(param_4 + 0x244)) &&
       (x = (int)*(short *)(param_1 + 0xca) + (*(int *)(param_2 + 0x2d0) >> 8),
       x < *(int *)(param_4 + 0x244))) {
      *(int *)(param_4 + 0x244) = x;
    }
LAB_8001a8b0:
    if (*(short *)(param_1 + 0xc6) == 0) goto LAB_8001a8c0;
  }

  // if this is arcade end-of-race
  else
  {
	// something to do with camera position interpolation
    if (*(short *)(param_1 + 0xc6) != 0)
	{
	  // camera distance = camera speed, minus camera position
      *(short *)(param_1 + 0xd4) = *(short *)(param_1 + 0x58) - *(short *)(param_4 + 0x240);
      *(short *)(param_1 + 0xd6) = *(short *)(param_1 + 0x5c) - *(short *)(param_4 + 0x244);
      *(short *)(param_1 + 0xd8) = *(short *)(param_1 + 0x60) - *(short *)(param_4 + 0x248);

	  *(short *)(param_1 + 0xcc) = *(short *)(param_1 + 100) - *(short *)(param_4 + 600);
      *(short *)(param_1 + 0xce) = *(short *)(param_1 + 0x68) - *(short *)(param_4 + 0x25c);
      sVar10 = *(short *)(param_4 + 0x260);
      *(undefined2 *)(param_1 + 0xda) = 8;
      *(undefined2 *)(param_1 + 0xc6) = 0;
      *(short *)(param_1 + 0xd0) = *(short *)(param_1 + 0x6c) - sVar10;
      goto LAB_8001a8b0;
    }
LAB_8001a8c0:

	// if frame countdown is not finished
    if ((int)*(short *)(param_1 + 0xda) != 0)
	{
      *(int *)(param_4 + 0x240) =
           *(int *)(param_4 + 0x240) +
           ((int)*(short *)(param_1 + 0xd4) * (int)*(short *)(param_1 + 0xda) >> 3);
      *(int *)(param_4 + 0x244) =
           *(int *)(param_4 + 0x244) +
           ((int)*(short *)(param_1 + 0xd6) * (int)*(short *)(param_1 + 0xda) >> 3);
      *(int *)(param_4 + 0x248) =
           *(int *)(param_4 + 0x248) +
           ((int)*(short *)(param_1 + 0xd8) * (int)*(short *)(param_1 + 0xda) >> 3);
      *(int *)(param_4 + 600) =
           *(int *)(param_4 + 600) +
           ((int)*(short *)(param_1 + 0xcc) * (int)*(short *)(param_1 + 0xda) >> 3);
      *(int *)(param_4 + 0x25c) =
           *(int *)(param_4 + 0x25c) +
           ((int)*(short *)(param_1 + 0xce) * (int)*(short *)(param_1 + 0xda) >> 3);
      *(int *)(param_4 + 0x260) =
           *(int *)(param_4 + 0x260) +
           ((int)*(short *)(param_1 + 0xd0) * (int)*(short *)(param_1 + 0xda) >> 3);

	  // decrease frame countdown
      *(short *)(param_1 + 0xda) = *(short *)(param_1 + 0xda) + -1;
    }
  }

  // CAM_FindClosestQuadblock
  FUN_800188a8(param_4,param_1,param_2,param_4 + 0x240);

  if (
		(*(short *)(param_4 + 0x3e) == 0) ||
		
		// quadblock->quadFlags & 0x4100
		((*(ushort *)(*(int *)(param_4 + 0x80) + 0x12) & 0x4100) != 0)
	 ) 
  {
    if (*(int *)(param_4 + 0x244) <
        (int)*(short *)(param_1 + 0xc4) + (*(int *)(param_2 + 0x2d8) >> 8)) {
      *(undefined2 *)(param_1 + 0xc2) = 8;
      *(short *)(param_1 + 0xc0) = *(short *)(param_1 + 0xc4);
      *(int *)(param_4 + 0x244) = (int)*(short *)(param_1 + 0xc4) + (*(int *)(param_2 + 0x2d8) >> 8)
      ;
      goto LAB_8001ab04;
    }
    *(undefined2 *)(param_1 + 0xc2) = 8;
    *(short *)(param_1 + 0xc0) =
         *(short *)(param_4 + 0x244) - (short)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8);
  }
  
  else 
  {
	// quadblock->terrainFlags
    cVar1 = *(char *)(*(int *)(param_4 + 0x80) + 0x38);
    
	// 14, 4, or 13
	// Mud, Water, or FastWater
	if (((cVar1 == '\x0e') || (cVar1 == '\x04')) || (cVar1 == '\r')) {
      *(undefined2 *)(param_4 + 0x1e) = 0;
    }
    
	x = (int)*(short *)(param_4 + 0x1e) + (int)param_5[8];
    if (*(int *)(param_4 + 0x244) < x) {
      *(int *)(param_4 + 0x244) = x;
    }
	
    x = (int)*(short *)(param_1 + 0xc2);
    if (x != 0) {
      *(int *)(param_4 + 0x244) =
           (8 - x) * *(int *)(param_4 + 0x244) +
           x * ((int)*(short *)(param_1 + 0xc0) + (*(int *)(param_2 + 0x2d8) >> 8)) >> 3;
      *(short *)(param_1 + 0xc2) = *(short *)(param_1 + 0xc2) + -1;
    }
  }
  *(short *)(param_1 + 0xc4) =
       *(short *)(param_4 + 0x244) - (short)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8);
LAB_8001ab04:

  // if mask grabs you when you're underwater
  if (((*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xdc) & 2) != 0) &&
     (*(int *)(param_4 + 0x244) < (int)param_5[8])) {
    *(int *)(param_4 + 0x244) = (int)param_5[8];
  }
  
  if (*(short *)(param_1 + 0xc6) != 0) {
    *(int *)(param_4 + 0x25c) = *(int *)(param_4 + 0x244) + (int)*(short *)(param_1 + 200);
  }

  // if mask grab
  if (*(char *)(param_2 + 0x376) == '\x05') {
    param_3[5] = param_3[5] - (param_3[5] >> 3);

	// camera dirX, cameraPosX minus driverPosX
    *(int *)(param_4 + 0x24c) = (int)*param_3 - (*(int *)(param_2 + 0x2d4) >> 8);

	// camera dirY, cameraPosY minus driverPosY, plus something else
	*(int *)(param_4 + 0x250) =
         (int)param_3[1] - ((*(int *)(param_2 + 0x2d8) >> 8) + (int)param_5[7]);

	// camera dirZ, cameraPosZ minus driverPosZ
	*(int *)(param_4 + 0x254) = (int)param_3[2] - (*(int *)(param_2 + 0x2dc) >> 8);

	sVar10 = param_3[3];
    if ((param_3[3] < 0x800) && (param_3[3] = sVar10 + 0x10, 0x800 < (short)(sVar10 + 0x10))) {
      param_3[3] = 0x800;
    }
  }

  // if not mask grab
  else {
    x = *(int *)(param_4 + 0x248) - *(int *)(param_4 + 0x260);

	// camera direction
    *(int *)(param_4 + 0x254) = x;
    *(int *)(param_4 + 0x24c) = *(int *)(param_4 + 0x240) - *(int *)(param_4 + 600);
    *(int *)(param_4 + 0x250) = *(int *)(param_4 + 0x244) - *(int *)(param_4 + 0x25c);

	// camera rotation
	x_00 = ratan2(*(long *)(param_4 + 0x24c),x);
    param_3[4] = (short)x_00;
    x_00 = SquareRoot0(*(int *)(param_4 + 0x24c) * *(int *)(param_4 + 0x24c) +
                        *(int *)(param_4 + 0x254) * *(int *)(param_4 + 0x254));
    x_00 = ratan2(*(long *)(param_4 + 0x250),x_00);
    param_3[3] = 0x800 - (short)x_00;
    param_3[5] = (short)((uint)((int)param_5[5] * (int)*(short *)(param_1 + 0x10)) >> 8);
  }

  // something with pushBuffer position
  *(int *)(param_4 + 0x214) = *(int *)(param_4 + 0x240) - (int)*param_3;
  *(int *)(param_4 + 0x218) = *(int *)(param_4 + 0x244) - (int)param_3[1];
  *(int *)(param_4 + 0x21c) = *(int *)(param_4 + 0x248) - (int)param_3[2];

  // CameraDC offset 0x4C to 0x54
  *(int *)(param_1 + 0x4c) =
       *(int *)(param_1 + 0x4c) - (*(int *)(param_4 + 0x240) - *(int *)(param_1 + 0x58));
  *(int *)(param_1 + 0x50) =
       *(int *)(param_1 + 0x50) - (*(int *)(param_4 + 0x244) - *(int *)(param_1 + 0x5c));
  *(int *)(param_1 + 0x54) =
       *(int *)(param_1 + 0x54) - (*(int *)(param_4 + 0x248) - *(int *)(param_1 + 0x60));

  if (2 < *(int *)(param_1 + 0x4c)) {
    *(undefined4 *)(param_1 + 0x4c) = 2;
  }
  if (*(int *)(param_1 + 0x4c) < -2) {
    *(undefined4 *)(param_1 + 0x4c) = 0xfffffffe;
  }
  if (2 < *(int *)(param_1 + 0x50)) {
    *(undefined4 *)(param_1 + 0x50) = 2;
  }
  if (*(int *)(param_1 + 0x50) < -2) {
    *(undefined4 *)(param_1 + 0x50) = 0xfffffffe;
  }
  if (2 < *(int *)(param_1 + 0x54)) {
    *(undefined4 *)(param_1 + 0x54) = 2;
  }
  if (*(int *)(param_1 + 0x54) < -2) {
    *(undefined4 *)(param_1 + 0x54) = 0xfffffffe;
  }

  // If not mask grabbed
  if (*(char *)(param_2 + 0x376) != '\x05')
  {
	// pushBuffer position
    *param_3 = *param_3 + *(short *)(param_4 + 0x214) + *(short *)(param_1 + 0x4c);
    param_3[1] = param_3[1] + *(short *)(param_4 + 0x218) + *(short *)(param_1 + 0x50);
    param_3[2] = param_3[2] + *(short *)(param_4 + 0x21c) + *(short *)(param_1 + 0x54);
  }
  uVar11 = *(uint *)(param_1 + 0x70);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_4 + 0x240);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_4 + 0x244);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_4 + 0x248);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_4 + 600);
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_4 + 0x25c);
  uVar15 = *(undefined4 *)(param_4 + 0x260);
  *(uint *)(param_1 + 0x70) = uVar11 & 0xffffffef;
  *(undefined4 *)(param_1 + 0x6c) = uVar15;

  if (
		// if transitioning, or end-of-race battle
		((uVar11 & 0x204) != 0) ||

		// If drawing intro-race cutscene
		((*(uint *)PTR_DAT_8008d2ac & 0x40) != 0)
	)
  {
	// if not end-of-race battle
	if ((uVar11 & 4) == 0)
	{
	  // if not transitioning
      if ((uVar11 & 0x200) == 0) {
        bVar5 = false;

		// LEV -> ptrSpawn1 -> numPointers,
		// if fly-in data is not in LEV
        if (**(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) < 4)
		{
		  // startline fly-in is done
		  bVar5 = true;
          x = 0x1000;
        }

		// if fly-in data exists in LEV
        else
		{
		  // LEV -> ptrSpawn1 -> ptr_intro_cam
          local_2c = (*(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))[4];
          local_26 = 0x8e;
          local_28 = 0x96;
          local_30 = local_2c + 0x354;

		  // which frame of fly-in you are in
          x = 0xa5 - (uint)*(ushort *)(param_1 + 0x8e);

		  // cast to short
          sVar10 = (short)x;

		  // set max value
          if (0x96 < x * 0x10000 >> 0x10) {
            sVar10 = 0x96;
          }

		  // CAM_StartLine_FlyIn
          FUN_800194c8(&local_30,0x96,(int)sVar10,&local_40,&local_38);

		  // get interpolation of fly-in [0 - 0x1000]
          x = (int)*(short *)(param_1 + 0x8c);
        }

		// if timer for fly-in camera is finished
        if (*(short *)(param_1 + 0x8e) < 1)
		{
		  // startline fly-in is done
          bVar5 = true;
        }

		// If you press Triangle
        if ((*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_2 + 0x4a) * 0x50 + 0x14) & 0x40000)
            != 0)
		{
		  // Skip Intro-Race cutscene, jump to traffic lights

          *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 9;

		  // startline fly-in is done
		  bVar5 = true;
        }
        puVar6 = PTR_DAT_8008d2ac;

		// if startline fly-in is done
        if (bVar5)
		{
		  // enable drawing HUD
          PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 1;

          puVar7 = PTR_DAT_8008d2ac;
          *(uint *)puVar6 = *(uint *)puVar6 & 0xffffffbf;
          puVar7[0x1d31] = puVar7[0x1d31] | 0x20;
        }
      }

	  // if transitioning
	  else
	  {
		// cameraDC TransitionTo pos and rot
        local_40 = *(undefined2 *)(param_1 + 0xa4);
        local_3e = *(undefined2 *)(param_1 + 0xa6);
        local_3c = *(undefined2 *)(param_1 + 0xa8);
        local_38 = *(undefined2 *)(param_1 + 0xaa);
        local_36 = *(undefined2 *)(param_1 + 0xac);
        local_34 = *(undefined2 *)(param_1 + 0xae);

		// interpolate fly-in [0 to 0x1000]
        x = (int)*(short *)(param_1 + 0x8c);
      }
    }

	// if end-of-race battle
    else
	{
	  // CAM_FollowDriver_Spin360
      FUN_80019f58(param_1,param_4,param_2,&local_40,&local_38);

	  // reverse interpolation of fly-in [0x1000 to 0]
      x = 0x1000 - (int)*(short *)(param_1 + 0x8c);
    }

	// CAM_ProcessTransition
	// use camera pos+rot, TransitionTo pos+rot, camera pos+rot, and interpolation
	FUN_80018fec(param_3,param_3 + 3,&local_40,&local_38,param_3,param_3 + 3,x);

    *(int *)(param_4 + 0x240) = (int)*param_3;
    *(int *)(param_4 + 0x244) = (int)param_3[1];
    *(int *)(param_4 + 0x248) = (int)param_3[2];

	// CAM_FindClosestQuadblock
	FUN_800188a8(param_4,param_1,param_2,param_4 + 0x240);

	x = (uint)*(ushort *)(param_1 + 0x9e) << 0x10;
    iVar14 = x >> 0x10;

	if (iVar14 != 0) {
      iVar12 = (int)*(short *)(param_1 + 0x8e);
      if (iVar12 <= iVar14) {
        x = iVar14 - (x >> 0x1f) >> 1;
        if (iVar12 < x) {
          if (x == 0) {
            trap(0x1c00);
          }
          if ((x == -1) && (iVar12 << 10 == -0x80000000)) {
            trap(0x1800);
          }

		  // Sine(angle)
		  x = FUN_8003d184(0x400 - (iVar12 << 10) / x);

		  *(short *)(param_1 + 0x8c) = (short)(x / 2) + 0x800;
        }
        else {
          iVar14 = (iVar12 - iVar14) * 0x400;
          if (x == 0) {
            trap(0x1c00);
          }
          if ((x == -1) && (iVar14 == -0x80000000)) {
            trap(0x1800);
          }

		  // Cosine(angle)
		  x = FUN_8003d1c0(iVar14 / x);

		  *(short *)(param_1 + 0x8c) = 0x800 - (short)(x / 2);
        }
      }
    }

	// flags
    uVar11 = *(uint *)(param_1 + 0x70);

	// if not transitioning away from player
	if ((uVar11 & 0x200) == 0)
	{
	  // If game is paused
      if ((*(uint *)PTR_DAT_8008d2ac & 0xf) != 0) {
        return;
      }

	  // decrement counter for fly-in camera
      sVar10 = *(short *)(param_1 + 0x8e) + -1;
      if (*(short *)(param_1 + 0x8e) < 1) {
        return;
      }
    }

	// if transitioning from player
    else
	{
	  // if not transitioning back to player
      if ((uVar11 & 0x400) == 0)
	  {
		// increment counter until limit is hit
        sVar10 = *(short *)(param_1 + 0x8e) + 1;

		// compare two transition timers
        if (*(short *)(param_1 + 0x9e) <= *(short *)(param_1 + 0x8e))
		{
		  // stop transitioning away from player,
		  // sit stationary away from player
          *(uint *)(param_1 + 0x70) = uVar11 | 0x800;
          return;
        }
      }

	  // if transitioning back to player
      else
	  {
		// decrement counter to zero
        sVar10 = *(short *)(param_1 + 0x8e) + -1;

		// if timer is over
        if (*(short *)(param_1 + 0x8e) < 1)
		{
		  // remove all transition flags
          *(uint *)(param_1 + 0x70) = uVar11 & 0xfffff1ff;
          return;
        }
      }
    }
    *(short *)(param_1 + 0x8e) = sVar10;
  }
  return;
}

// CAM_MapRange_PosPoints
// param1 is vec3s pos1,
// param2 is vec3s pos2,
// param3 is vec3i pos, (driver position)
// get percentage [0 to 0x1000] of Driver between pos1 and pos2
int FUN_8001b254(short *param_1,short *param_2,short *param_3)

{
  int iVar1;
  undefined4 local_20;
  short local_1c;
  undefined4 local_18;

  local_20 = CONCAT22(param_1[1] - param_2[1],*param_1 - *param_2);
  local_1c = param_1[2] - param_2[2];

  // MATH_VectorNormalize
  FUN_8003d378(&local_20);

  local_18 = CONCAT22(param_3[1] - param_1[1],*param_3 - *param_1);

  gte_ldR11R12(local_20);
  gte_ldR13R21((int)local_1c);
  gte_ldVXY0(local_18);
  gte_ldVZ0((int)(short)(param_3[2] - param_1[2]));

  gte_mvmva(0,0,0,3,0);
  iVar1 = gte_stMAC1();

  return iVar1 >> 0xc;
}

// CAM_ThTick
void FUN_8001b334(int param_1)

{
  short sVar1;
  bool bVar2;
  undefined *puVar3;
  undefined4 in_zero;
  undefined4 in_at;
  ushort uVar4;
  short sVar5;
  undefined2 uVar6;
  short sVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  short *psVar12;
  short *psVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  short *psVar16;
  uint uVar17;
  int *piVar18;
  short *psVar19;
  int iVar20;
  undefined4 uVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  short local_28;
  short local_26;
  short local_24;

  // CameraDC ???
  // stored in Instance pointer?
  piVar18 = *(int **)(param_1 + 0x34);

  // p1 from cameraDC, offset 0x44
  iVar22 = piVar18[0x11];

  // pushBuffer from cameraDC, offset 0x48
  psVar19 = (short *)piVar18[0x12];

  // if cameraDC->0x70 & 0x8000 (freecam)
  if ((piVar18[0x1c] & 0x8000U) != 0) 
    return;

  if (
		(
			(
				// if you're not in cutscene, and not in menu, and not paused,
				// and if not drawing intro-race cutscene
				((*(uint *)PTR_DAT_8008d2ac & 0x2000204f) == 0) &&

				// driver -> instance -> thread -> funcThTick == 0
				(*(int *)(*(int *)(*(int *)(iVar22 + 0x1c) + 0x6c) + 0x2c) == 0)
			) &&
			
			// If this is human and not AI
			((*(uint *)(iVar22 + 0x2c8) & 0x100000) == 0)
		) &&
		(
			(
				//if kart state is not warpPad(10), and not Freeze(11)
				(*(char *)(iVar22 + 0x376) != 10 && (*(char *)(iVar22 + 0x376) != 11)) &&
				(
					(
						// if not in a state where you're seeing the boss key open an adv door,
						// or some other kind of cutscene where you can't move
						(*(uint *)(PTR_DAT_8008d2ac + 8) & 4) == 0 &&

						// If you press L2
						// gGamepads->gamepad[cameraDC->cameraID]->buttonsHeld
						((*(uint *)(PTR_DAT_8008d2b0 + *piVar18 * 0x50 + 0x14) & 0x80) != 0)
					)
				)
			)
		)
	 )
  {
	// Zoom camera in and out

	// Add to this variable
    uVar4 = *(short *)((int)piVar18 + 0x92) + 1;

	// Store the incremented variable
    *(ushort *)((int)piVar18 + 0x92) = uVar4;

	// If the variable is 0, then it becomes 1

	// If the variale is 1, and adds to become 2
    if (1 < uVar4)
	{
		// reset the variable back to 0
      *(undefined2 *)((int)piVar18 + 0x92) = 0;
    }

	// unused way to toggle first-person by pressing L2 twice
    if (*(short *)((int)piVar18 + 0x92) == 2)
	{
		// first person mode
      *(undefined2 *)((int)piVar18 + 0x9a) = 0xf;
    }

	// If you are in process of changing 0 to 1
    else {
      *(undefined2 *)((int)piVar18 + 10) = *(undefined2 *)((int)piVar18 + 0x92);
      *(undefined2 *)((int)piVar18 + 0x9a) = 0;
    }
  }
  iVar9 = (int)*(short *)((int)piVar18 + 10) * 0x24;

  // if number of screeens is not 2
  // if you have 4:3 aspect ratio
  iVar20 = iVar9 + -0x7ff7f098; // 80080F68

  // if numPlyrCurrGame is 2
  // if you have 8:3 aspect ratio
  if (PTR_DAT_8008d2ac[0x1ca8] == '\x02') {
    iVar20 = iVar9 + -0x7ff7f086; // 80080F7A
  }

  // Camera zoom variables,
  // with and without L2
  // at motion and at rest

  // if not end-of-race camera, skip block
  if ((piVar18[0x1c] & 0x20U) == 0) goto switchD_8001b678_caseD_1;
  
  // === Assume End-Of-Race camera ===
  
  psVar16 = (short *)0x0;

  // LEV -> ptrSpawnType1 -> numPointers
  if (**(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) < 3) goto switchD_8001b678_caseD_1;

  // LEV -> ptrSpawnType1 -> pointers[2] -- ST1_CAMERA_EOR
  psVar12 = (short *)(*(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))[3];

  // number of nodes for end-of-race camera,
  // these are not "position" nodes, they 
  // are nodes that change camera mode as you move
  sVar7 = *psVar12;

  // something with driver position
  local_28 = (short)((uint)*(undefined4 *)(iVar22 + 0x2d4) >> 8);
  local_26 = (short)((uint)*(undefined4 *)(iVar22 + 0x2d8) >> 8);
  local_24 = (short)((uint)*(undefined4 *)(iVar22 + 0x2dc) >> 8);


  // psVar13 and psVar12 are both short*

  // respawn index
  psVar13 = psVar12 + 1;
  
  // number of camera modes
  if (sVar7 != 0) 
  {
    uVar17 = (uint)*(byte *)(iVar22 + 0x495);
    
	// camera mode
	psVar12 = psVar12 + 2;
	
	// loop through all of them till one is found
	// with the same value is driver->0x495 (sorta like 
	// track progress percentage, but not really)
    do 
	{
	  // camera mode
      iVar9 = (int)*psVar12;
	  
	  // respawn point index
      sVar5 = *psVar13;
	  
      if (iVar9 < 0) {
        iVar9 = -iVar9;
      }
	  
	  // next node =
      psVar13 = 
		
		// current node +
		(short *)((int)psVar12 +
        
		// EndOfRace_Camera_Size[cameraMode]
		(int)*(short *)(&DAT_80080fb0 + ((iVar9 << 0x10) >> 0xf)) 
		
		// plus another 2 bytes (iVar9 and iVar5)
		+ 2);

	  if (
			(
				(uVar17 == (int)sVar5) ||

				// gGT->level1->ptr_restart_points[sVar5]
				(iVar9 = (int)sVar5 * 0xc + *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c),
				
				uVar17 == (uint)*(byte *)(iVar9 + 8))
			) ||
			(
				(uVar17 == (uint)*(byte *)(iVar9 + 9) ||
				((uVar17 == (uint)*(byte *)(iVar9 + 10) || 
				(uVar17 == (uint)*(byte *)(iVar9 + 0xb)))))
			)
		  ) 
	  {
        psVar16 = psVar12;
      }
	  
	  // loop count
      sVar7 = sVar7 + -1;
	  
	  // start of next buffer
      psVar12 = psVar13 + 1;
    
	} while (sVar7 != 0);
  }
  
  // if no valid End-Of-Race camera init data found,
  // or if it has not changed since previous frame
  if ((psVar16 == (short *)0x0) || (psVar16 == (short *)piVar18[0x28]))
  {
	  // skip initialization of new End-Of-Race camera mode
	  goto switchD_8001b678_caseD_1;
  }
  
  // === Initialize new End-Of-Race camera mode ===
  
  // save new pointer to camera init data
  *(short **)(piVar18 + 0x28) = psVar16;
  
  sVar7 = *psVar16;
  psVar12 = psVar16 + 1;
  uVar17 = piVar18[0x1c];
  
  sVar5 = sVar7;
  if (sVar7 < 0) {
    sVar5 = -sVar7;
  }
  
  // new camera mode
  *(short *)((int)piVar18 + 0x9a) = sVar5;
  
  piVar18[0x1c] = uVar17 & 0xffffefff | 9;
  if (sVar7 < 0) {
    piVar18[0x1c] = uVar17 & 0xffffefff | 0x1009;
  }
  piVar18[0x1c] = piVar18[0x1c] | 0x1000;
  
  switch(*(undefined2 *)((int)piVar18 + 0x9a)) 
  {
  
  // CAM_FollowDriver_Normal
  case 0:

	// PushBuffer position
    // Get driver -> instance -> position (x, y, z)
    *psVar19 = *(short *)(*(int *)(iVar22 + 0x1c) + 0x44);
    psVar19[1] = *(short *)(*(int *)(iVar22 + 0x1c) + 0x48);
    psVar19[2] = *(short *)(*(int *)(iVar22 + 0x1c) + 0x4c);

	// PushBuffer rotation
	// compressed 2-byte position?
    psVar19[3] = *(short *)(iVar22 + 0x2ec);
    psVar19[4] = *(short *)(iVar22 + 0x2ee);
    psVar19[5] = *(short *)(iVar22 + 0x2f0);

    *(undefined2 *)(piVar18 + 0x30) = 0;
    break;
	
  // freecam (any time you see (dc + 0x1532) = 3 )
  case 3:

	// PushBuffer position
    *psVar19 = *psVar12;
    psVar19[1] = psVar16[2];
    psVar19[2] = psVar16[3];

	// PushBuffer rotation
    psVar19[3] = psVar16[4];
    psVar19[4] = psVar16[5];
    psVar19[5] = psVar16[6];

    *(short *)(piVar18 + 1) = *psVar12;
    *(short *)((int)piVar18 + 6) = psVar16[2];
    *(short *)(piVar18 + 2) = psVar16[3];
    *(short *)(piVar18 + 3) = psVar16[4];
    *(short *)((int)piVar18 + 0xe) = psVar16[5];
    *(short *)(piVar18 + 4) = psVar16[6];
    break;

  case 4:

    // PushBuffer position
    *psVar19 = *psVar12;
    psVar19[1] = psVar16[2];
    psVar19[2] = psVar16[3];
    break;

  case 7:
    *(short *)(piVar18 + 0x29) = *psVar12;
    uVar17 = piVar18[0x1c];
    sVar7 = psVar16[2];
    piVar18[0x1c] = uVar17 & 0xffffffbf;
    *(short *)((int)piVar18 + 0xa6) = sVar7;
    if (psVar16[3] != 0) {
      piVar18[0x1c] = uVar17 & 0xffffffbf | 0x40;
    }
    break;
  case 8:
  case 0xe:
    *(short *)(piVar18 + 0x1d) = *psVar12;
    *(short *)((int)piVar18 + 0x76) = psVar16[2];
    *(short *)(piVar18 + 0x1e) = psVar16[3];
    *(short *)(piVar18 + 0x1f) = psVar16[4];
    *(short *)((int)piVar18 + 0x7e) = psVar16[5];
    *(short *)(piVar18 + 0x20) = psVar16[6];

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar6 = FUN_80058f9c((int)*(short *)(piVar18 + 0x1d) * (int)*(short *)(piVar18 + 0x1d) +
                         (int)*(short *)((int)piVar18 + 0x76) * (int)*(short *)((int)piVar18 + 0x76)
                         + (int)*(short *)(piVar18 + 0x1e) * (int)*(short *)(piVar18 + 0x1e),0x10000
                         ,0x190000,0x80,0xf0);
    *(undefined2 *)((int)piVar18 + 0x7a) = uVar6;
    break;

  // if camera position is following warpball path
  case 9:
  case 0xd:
    sVar7 = *psVar12;

	// lev -> respawn points (warpball path)
    iVar9 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);

	piVar18[0x25] = 0;
    piVar18[0x22] = iVar9 + (int)sVar7 * 0xc;

	*(short *)(piVar18 + 0x29) = psVar16[2];
    *(short *)((int)piVar18 + 0xa6) = psVar16[3];
    *(short *)(piVar18 + 0x2a) = psVar16[4];
    *(short *)((int)piVar18 + 0xaa) = psVar16[5];
    *(short *)(piVar18 + 0x2b) = psVar16[6];
    *(short *)((int)piVar18 + 0xae) = psVar16[7];
    *(short *)(piVar18 + 0x2c) = psVar16[8];
    break;

  // CAM_FollowDriver_Spin360
  case 10:
    sVar7 = *psVar12;
    psVar12 = psVar16 + 2;
    goto LAB_8001b928;

  case 0xb:

	// PushBuffer position
    *psVar19 = *psVar12;
    psVar19[1] = psVar16[2];
    psVar19[2] = psVar16[3];

    psVar12 = psVar16 + 5;
    sVar7 = psVar16[4] - psVar19[0x86];
LAB_8001b928:
    *(short *)(piVar18 + 0x29) = sVar7;
    *(short *)((int)piVar18 + 0xa6) = *psVar12;
    *(short *)(piVar18 + 0x2a) = psVar12[1];
    break;
	
  // TransitionTo
  case 0xc:
    
	// set TransitionTo
	*(short *)(piVar18 + 0x29) = *psVar12;
    *(short *)((int)piVar18 + 0xa6) = psVar16[2];
    *(short *)(piVar18 + 0x2a) = psVar16[3];
    *(short *)((int)piVar18 + 0xaa) = psVar16[4];
    *(short *)(piVar18 + 0x2b) = psVar16[5];
    *(short *)((int)piVar18 + 0xae) = psVar16[6];
    *(short *)(piVar18 + 0x2c) = psVar16[7];
    *(short *)((int)piVar18 + 0xb2) = psVar16[8];
    *(short *)(piVar18 + 0x2d) = psVar16[9];
    *(short *)((int)piVar18 + 0xb6) = psVar16[10];
  }
  
// Not changing camera mode,
// continue with code that runs each frame
switchD_8001b678_caseD_1:
  
  *(undefined4 *)(psVar19 + 0xc) = *(undefined4 *)(psVar19 + 0x86);

  // get camera mode
  sVar7 = *(short *)((int)piVar18 + 0x9a);

  // not CAM_FollowDriver_Normal
  if (sVar7 != 0) {
    
	*(undefined2 *)((int)piVar18 + 0xda) = 0;
    
	// not CAM_FollowDriver_Normal
	if (sVar7 != 0) 
	{
	  // LookAt and Frozen
      if (sVar7 == 4) {
LAB_8001c11c:
		// CAM_LookAtPosition
        FUN_80019e7c(&DAT_1f800108,iVar22 + 0x2d4,psVar19,psVar19 + 3);
LAB_8001c128:
        sVar7 = *psVar19;
        sVar5 = psVar19[1];
        sVar1 = psVar19[2];
      }
      else 
	  {
		// CAM_FollowDriver_Spin360
        if (sVar7 == 10)
		{
		  // CAM_FollowDriver_Spin360
          FUN_80019f58(piVar18,&DAT_1f800108,iVar22,psVar19,psVar19 + 3);
          goto LAB_8001c128;
        }
        if (sVar7 != 0xb) 
		{
		  // TransitionTo
          if (sVar7 == 0xc) 
		  {
			// first frame of mode 0xc
            if (*(short *)((int)piVar18 + 0x9c) != 0xc) {
              *(undefined2 *)((int)piVar18 + 0x8e) = 0;
            }

			// position of driver
            local_28 = (short)((uint)*(undefined4 *)(iVar22 + 0x2d4) >> 8);
            local_26 = (short)((uint)*(undefined4 *)(iVar22 + 0x2d8) >> 8);
            local_24 = (short)((uint)*(undefined4 *)(iVar22 + 0x2dc) >> 8);

			// camera TransitionTo pos
			// camera TransitionTo rot
			// driver position
            iVar20 = FUN_8001b254(piVar18 + 0x29,(int)piVar18 + 0xaa,&local_28);

			iVar10 = (int)*(short *)((int)piVar18 + 0xb6);
            local_28 = *(short *)((int)piVar18 + 0xb0) - *(short *)((int)piVar18 + 0xaa);
            local_26 = *(short *)((int)piVar18 + 0xb2) - *(short *)((int)piVar18 + 0xac);
            iVar9 = iVar10;
            if (iVar10 < 0) {
              iVar9 = -iVar10;
            }
            local_24 = *(short *)((int)piVar18 + 0xb4) - *(short *)((int)piVar18 + 0xae);
            if (iVar10 < 0) {
              local_28 = -local_28;
              local_26 = -local_26;
              local_24 = -local_24;
            }
            iVar23 = SquareRoot0((int)local_28 * (int)local_28 + (int)local_26 * (int)local_26 +
                                  (int)local_24 * (int)local_24);
            iVar11 = piVar18[0x25] << 0xc;
            iVar24 = iVar11 / iVar23;
            if (iVar23 == 0) {
              trap(0x1c00);
            }
            if ((iVar23 == -1) && (iVar11 == -0x80000000)) {
              trap(0x1800);
            }
            piVar18[0x25] =
                 piVar18[0x25] +
                 ((((int)*(short *)((int)piVar18 + 0x8e) * 0x1000) / 0x1e) * iVar9 >> 0xc);
            
			if (iVar20 < 1) 
			{
              if (iVar24 < 0x1001) {
                
				// camera flyin timer
				if (*(short *)((int)piVar18 + 0x8e) < 0x1e) 
				{
                  *(short *)((int)piVar18 + 0x8e) = *(short *)((int)piVar18 + 0x8e) + 1;
                }
              }
              else 
			  {
				// camera flyin timer
                if (*(short *)((int)piVar18 + 0x8e) != 0) {
                  *(short *)((int)piVar18 + 0x8e) = *(short *)((int)piVar18 + 0x8e) + -1;
                }
              }
            }
            else {
              piVar18[0x25] = 0;
              *(undefined2 *)((int)piVar18 + 0x8e) = 0;
            }
            piVar8 = (int *)((int)piVar18 + 0xaa);
            if (iVar10 < 0) {
              piVar8 = piVar18 + 0x2c;
            }
            *psVar19 = *(short *)piVar8 + (short)(local_28 * iVar24 >> 0xc);
            psVar19[1] = *(short *)((int)piVar8 + 2) + (short)(local_26 * iVar24 >> 0xc);
            psVar19[2] = *(short *)(piVar8 + 1) + (short)(local_24 * iVar24 >> 0xc);
            goto LAB_8001c11c;
          }
          if (sVar7 == 7) {
            *psVar19 = (short)((uint)*(undefined4 *)(iVar22 + 0x2d4) >> 8);
            psVar19[1] = *(short *)((int)piVar18 + 0xa4) +
                         (short)((uint)*(undefined4 *)(iVar22 + 0x2d8) >> 8);
            psVar19[2] = (short)((uint)*(undefined4 *)(iVar22 + 0x2dc) >> 8);
            sVar7 = *(short *)((int)piVar18 + 0xa6);
            psVar19[4] = 0;
            psVar19[5] = 0;
            psVar19[3] = sVar7 + 0x400;
            if ((piVar18[0x1c] & 0x40U) != 0) {
              psVar19[4] = *(short *)(iVar22 + 0x39a) + 0x800;
            }
          }
          else {

			// if 0xF or 0x10
			// if first-person of any type
			if ((ushort)(*(short *)((int)piVar18 + 0x9a) - 0xfU) < 2)
			{
			  // camera pos = driver pos
              *psVar19 = DAT_8008cf94 + (short)((uint)*(undefined4 *)(iVar22 + 0x2d4) >> 8);
              psVar19[1] = DAT_8008cf96 + (short)((uint)*(undefined4 *)(iVar22 + 0x2d8) >> 8);
              psVar19[2] = DAT_8008cf98 + (short)((uint)*(undefined4 *)(iVar22 + 0x2dc) >> 8);

			  // first person without head rotation (during steers)
              if (*(short *)((int)piVar18 + 0x9a) == 0x10) {
                psVar19[3] = DAT_8008cf9c + *(short *)(iVar22 + 0x2ec);
                sVar7 = DAT_8008cf9e + *(short *)(iVar22 + 0x39a);
              }

			  // first person with head rotation (during steers)
              else {
                psVar19[3] = DAT_8008cf9c + *(short *)(iVar22 + 0x2ec);
                sVar7 = DAT_8008cf9e + *(short *)(iVar22 + 0x2ee);
              }
              psVar19[4] = sVar7;
              psVar19[5] = DAT_8008cfa0 + *(short *)(iVar22 + 0x2f0);
            }
            else
			{
			  // if camera mode is close to ground,
			  // or right above player
              if ((sVar7 == 8) || (sVar7 == 0xe))
			  {
				// if player is not blasted or spinning out (currFrame)
                if ((*(uint *)(iVar22 + 0x5b0) & 2) == 0)
				{
				  // if player is blasted or spinning out (prevFrame)
                  if ((piVar18[0x21] & 2U) != 0) 
				  {
					// reset position and change view
                    piVar18[0x1c] = piVar18[0x1c] | 9;
                  }

				  // follow with AngleAxis,
				  // rotate with respect to terrain

				  // piVar18 = cameraDC
				  // iVar22 = driver object

				  // CAM_FollowDriver_AngleAxis
                  FUN_80019128(piVar18,iVar22,&DAT_1f800108,psVar19,psVar19 + 3);
                }

				// if player is blasted or spinning out
                else
				{
				  // not blasted or spinning on prevFrame
                  if ((piVar18[0x21] & 2U) == 0) 
				  {
					// reset position and change view
                    piVar18[0x1c] = piVar18[0x1c] | 9;
                  }

				  // follow driver normally

				  // piVar18 = cameraDC
				  // iVar22 = driver object

				  // CAM_FollowDriver_Normal
                  FUN_8001a0bc(piVar18,iVar22,psVar19,&DAT_1f800108,iVar20);
                }

				// CameraDC 0x84 (prevFrame)
				piVar18[0x21] = *(int *)(iVar22 + 0x5b0);

                goto LAB_8001c150;
              }

			  // if camera is on a path
			  if ((*(short *)((int)piVar18 + 0x9a) == 9) || (*(short *)((int)piVar18 + 0x9a) == 0xd)
                 )
			  {
                if (
						// if path data exists throughout the track
						// (blue path in DCxDemo's lev viewer)
						(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x148) != 0) &&

						// If game is not paused
						((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
					)
				{
                  // CAM_FollowDriver_TrackPath
				  // + 0x2c (0xB0) is speed on path
				  iVar9 = FUN_800198f8(piVar18,&DAT_1f800390,(int)*(short *)(piVar18 + 0x2c),1);

				  // Use 0xC0 or -0xC0 depending on direction
				  uVar14 = 0xffffff40;
                  if (-1 < *(short *)(piVar18 + 0x2c)) {
                    uVar14 = 0xc0;
                  }

				  // CAM_FollowDriver_TrackPath
				  // Get another point on path, then interpolate
                  iVar20 = FUN_800198f8(piVar18,&DAT_1f800398,uVar14,0);

				  // interpolate two rotations
				  DAT_1f800314 = 0x800;
                  DAT_1f800316 = (short)iVar9 +
                                 (short)((int)(((iVar20 - iVar9) + 0x800U & 0xfff) - 0x800) >> 1);
                  DAT_1f800318 = 0;
				  
				  // interpolate two positions
                  DAT_1f800390 = (short)((int)DAT_1f800390 + (int)DAT_1f800398 >> 1);
                  DAT_1f800392 = (short)((int)DAT_1f800392 + (int)DAT_1f80039a >> 1);
                  DAT_1f800394 = (short)((int)DAT_1f800394 + (int)DAT_1f80039c >> 1);

				   // convert 3 rotation shorts into rotation matrix
                  FUN_8006c2a4(&DAT_1f800328,&DAT_1f800314);

                  gte_SetRotMatrix((MATRIX*)&DAT_1f800328);
				  gte_ldv0(piVar18[0x29]);
				  gte_rtv0();
				  read_mt(uVar21,uVar14,uVar15);

				  // camera LookAt data
                  *psVar19 = DAT_1f800390 + (short)uVar21;
                  psVar19[1] = DAT_1f800392 + (short)uVar14;
                  psVar19[2] = DAT_1f800394 + (short)uVar15;
                  psVar19[3] = DAT_1f800314 + *(short *)((int)piVar18 + 0xaa);
                  psVar19[4] = DAT_1f800316 + *(short *)(piVar18 + 0x2b);
                  psVar19[5] = DAT_1f800318 + *(short *)((int)piVar18 + 0xae);
                }

				// if camera should look at driver, run LookAt for driver
                if (*(short *)((int)piVar18 + 0x9a) == 0xd) goto LAB_8001c11c;
              }
            }
          }

		  // if camera should look ahead (or behind) use existing LookAt variable
          goto LAB_8001c128;
        }

		// CAM_LookAtPosition
		FUN_80019e7c(&DAT_1f800108,iVar22 + 0x2d4,psVar19,psVar19 + 3);

		iVar9 = SquareRoot0(DAT_1f800354 * DAT_1f800354 + DAT_1f80035c * DAT_1f80035c);
        iVar10 = (int)*(short *)(piVar18 + 0x29);
        iVar23 = (iVar9 - *(short *)((int)piVar18 + 0xa6)) * iVar10;
        iVar20 = (int)*(short *)(piVar18 + 0x2a);
        iVar9 = iVar23 / iVar20;
        if (iVar20 == 0) {
          trap(0x1c00);
        }
        if ((iVar20 == -1) && (iVar23 == -0x80000000)) {
          trap(0x1800);
        }
        bVar2 = iVar10 < iVar9;
        if (iVar9 < 0) {
          iVar9 = 0;
          bVar2 = iVar10 < 0;
        }
        if (bVar2) {
          iVar9 = iVar10;
        }
        sVar7 = *psVar19;
        *(int *)(psVar19 + 0xc) = *(int *)(psVar19 + 0x86) + iVar9;
        sVar5 = psVar19[1];
        sVar1 = psVar19[2];
      }
      DAT_1f80034c = (int)sVar5;
      DAT_1f800348 = (int)sVar7;
      DAT_1f800350 = (int)sVar1;

	  // CAM_FindClosestQuadblock
	  // piVar18 = cameraDC
	  // iVar22 = driver object
      FUN_800188a8(&DAT_1f800108,piVar18,iVar22,&DAT_1f800348);

	  // jump over CAM_FollowDriver_Normal
	  goto LAB_8001c150;
    }
  }

  // piVar18 = cameraDC
  // iVar22 = driver object
  // psVar19 - pushBuffer
  // CAM_FollowDriver_Normal
  FUN_8001a0bc(piVar18,iVar22,psVar19,&DAT_1f800108,iVar20);

LAB_8001c150:

  // 0x9C = 0x9A
  *(undefined2 *)(piVar18 + 0x27) = *(undefined2 *)((int)piVar18 + 0x9a);
  
  puVar3 = PTR_DAT_8008d2ac;

  // camera quadblock exists
  if (piVar18[7] != 0)
  {
	// quadblock -> ptr_add_tex
    piVar8 = *(int **)(piVar18[7] + 0x44);

	// ptr_add_tex -> 0x0
	if ((piVar8 != (int *)0x0) && (iVar22 = *piVar8, iVar22 != 0))
	{
	  // CameraDC 0x20
      piVar18[8] = iVar22;

      *(int *)(puVar3 + 0x1cb0) =
           (piVar18[7] - *(int *)(**(int **)(puVar3 + 0x160) + 0xc)) * -0x1642c859 >> 2;
    }

    // camera quadblock exists
    if (piVar18[7] != 0)
	{
	  // quadblock -> ptr_add_tex
      iVar22 = *(int *)(piVar18[7] + 0x44);

	  // ptr_add_tex -> 0x4
      if ((iVar22 != 0) && (iVar22 = *(int *)(iVar22 + 4), iVar22 != 0))
	  {
	    // CameraDC 0x24
        piVar18[9] = iVar22;
      }

	  // camera quadblock exists
      if (piVar18[7] != 0)
	  {
		// quadblock -> ptr_add_tex
        iVar22 = *(int *)(piVar18[7] + 0x44);

		// ptr_add_tex -> 0x8
		if ((iVar22 != 0) && (iVar22 = *(int *)(iVar22 + 8), iVar22 != 0))
		{
		  // CameraDC 0x28
          piVar18[10] = iVar22;
        }

		// camera quadblock exists 		quadblock -> ptr_add_tex
        if (((piVar18[7] != 0) && (iVar22 = *(int *)(piVar18[7] + 0x44), iVar22 != 0)) &&

			// ptr_add_tex -> 0xC
		   (iVar22 = *(int *)(iVar22 + 0xc), iVar22 != 0))
		{
		  // if no lev animated vertices
		  if ((*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xdc) & 4) == 0)
		  {
			// CameraDC 0x2C
            piVar18[0xb] = iVar22;
          }
		  
		  // if lev animated vertices
          else
		  {
			// CameraDC 0x30
            piVar18[0xc] = iVar22;
          }
        }
      }
    }
  }
  
  if (piVar18[0xf] == 0) 
  {
	// visLeafSrc
    piVar18[8] = 0;
	
	// visFaceSrc
    piVar18[9] = 0;
  }
  
  puVar3 = PTR_DAT_8008d2ac;

  // if need to reset rainbuffer camPos
  if ((piVar18[0x1c] & 1U) != 0)
  {
	// store PushBuffer position in gGT->RainBuffer[x].cameraPos
    *(short *)(PTR_DAT_8008d2ac + *piVar18 * 0x30 + 0x1a58) = *psVar19;
    *(short *)(puVar3 + *piVar18 * 0x30 + 0x1a5a) = psVar19[1];
    *(short *)(puVar3 + *piVar18 * 0x30 + 0x1a5c) = psVar19[2];

	// dont need to reset anymore
    piVar18[0x1c] = piVar18[0x1c] & 0xfffffffe;
  }
  
  piVar18[0x1c] = piVar18[0x1c] & 0xffffff77;
  
  return;
}
