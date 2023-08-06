#include <common.h>

void DECOMP_MENUBOX_DrawSelf(struct MenuBox *mb, int param_2, short param_3, u_short width)
{
  struct MenuRow *row;
  struct GameTracker *gGT;

  u_short uVar1;
  u_int uVar2;
  int iVar3;
  u_int uVar4;
  int iVar5;
  u_int *puVar6;
  short sVar7;
  u_short uVar8;
  short sVar9;
  short sVar11;
  short sVar12;
  u_short uVar13;
  u_int local_78;
  short local_70;
  short local_6e;
  u_short local_6c;
  short local_6a;
  short local_68;
  short local_66;
  short local_64;
  short local_62;
  short local_60;
  short local_5e[3];
  short local_58;
  short local_50;
  short local_48;
  short local_40;
  short local_38;
  int local_30;
  int local_2c;

  gGT = sdata->gGT;

  // default text color (orange)
  local_78 = 0;
  local_40 = 0;
  local_38 = 0;

  // if MenuBox should be drawn green
  // for save/load screen
  if ((mb[10] & 0x10U) != 0)
  {
    // make text color green
    local_78 = 0x1d;
  }
  uVar13 = (u_short)local_78;
  local_58 = param_3;

  // setting flag 0x60000 disables input in pause menu,
  // so how does this "if" make sense?
  if ((mb->state & 0x60000) == 0x60000)
  {
    mb[0xf] = 2;

    // if funcPtr exists, execute it
    if (mb->funcPtr != NULL)
    {
      (mb->funcPtr)(mb);
    }
  }
  sVar11 = 2;

  // if large text in rows
  if ((mb->state & USE_SMALL_FONT) == 0)
  {
    sVar11 = 1;
    local_50 = 2;

    local_62 = data.font_charPixHeight[FONT_BIG] + 3;
  }
  // & 80 == 1
  // if tiny text in rows
  else
  {
    local_50 = 0;

    // row height
    local_62 = data.font_charPixHeight[FONT_SMALL];

    // if tiny text in title
    if ((mb->state & BIG_TEXT_IN_TITLE) == 0)
    {

      // row height
      local_48 = data.font_charPixHeight[FONT_SMALL];

      goto LAB_80045e94;
    }
  }

  // if large text in title
  local_48 = data.font_charPixHeight[FONT_BIG] + 3;

LAB_80045e94:
  local_60 = 0;
  mb->posX_prev = mb->posX_curr;
  mb->posY_prev = mb->posY_curr;

  // get height of menubox
  MENUBOX_GetHeight(mb, &local_60, 0);

  // set menuBox width
  mb->width = width;

  mb->state &= 0xfffffff7;

  // set menuBox height
  mb->height = local_60;

  if ((mb->state & CENTER_ON_Y) != 0)
  {
    local_5e[0] = 0;
    MENUBOX_GetHeight(mb, local_5e, 1);
    local_38 = (short)((-(int)local_5e[0] - (-(int)local_5e[0] >> 0x1f)) >> 1);
  }

  if ((mb->state & CENTER_ON_X) != 0)
  {
    local_40 = (short)((-(int)(short)width - (-(int)(short)width >> 0x1f)) >> 1);
  }
  sVar12 = 0;

  // MenuRow array, deref to get string index
  row = mb->rows[0];

  // dereference short, then cast short to int,
  // get string index of the MenuBox title
  iVar3 = mb->stringIndexTitle;

  sVar9 = local_50 + local_38 + local_58 + mb->posY_prev;

  if (
      // if title is not 0xFFFF
      (-1 < iVar3) &&

      ((mb->state & 4) == 0))
  {
    sVar7 = 1;
    if ((mb->state & BIG_TEXT_IN_TITLE) == 0)
    {
      sVar7 = sVar11;
    }
    if ((mb->state & 0x200) == 0)
    {
      iVar5 = param_2 + mb->posX_prev;
      uVar8 = uVar13;
      if ((mb->state & 1) != 0)
      {
        uVar8 = uVar13 | 0x8000;
      }
      local_78 = SEXT24((short)uVar8);

      // get string from LNG
      uVar4 = sdata->lngStrings[iVar3];
    }
    else
    {
      local_78 |= 0xffff8000;

      // get string from LNG
      uVar4 = sdata->lngStrings[iVar3];

      iVar5 = param_2 + mb->posX_prev + (width - (width >> 0xf) >> 1);
    }

    // draw title string
    DecalFont_DrawLine(uVar4, iVar5, sVar9, sVar7, local_78);

    sVar9 = local_48 + sVar9 + 6;
  }

  if (row->stringIndex != -1)
  {
    local_30 = (width - (width >> 0xf) >> 1) + 1;
    local_2c = (int)sVar11;

    // loop through all menu rows
    do
    {
      if (
          // flags are disabled
          ((mb->state & (SHOW_ONLY_HIGHLIT_ROW | ONLY_DRAW_TITLE)) == 0) ||

          // if this row is the highlighted row
          (sVar12 == mb->rowSelected))
      {
        // dereference row to get string
        uVar8 = row->stringIndex;

        // color of "locked" text (gray)
        uVar1 = 0x17;

        // if row is not "locked"
        if ((uVar8 & 0x8000) == 0)
        {
          // change color to unlocked
          uVar1 = uVar13;
        }
        // if string is valid
        if ((uVar8 & 0x7fff) != 0)
        {

          if ((mb->state & 0x200) == 0)
          {
            iVar3 = param_2 + mb->posX_prev + 1;

            if ((mb->state & CENTER_ON_X) != 0)
            {
              // center text
              uVar1 |= 0x8000;
            }

            // get pointer to string, from index
            uVar4 = sdata->lngStrings[uVar8];

            iVar5 = local_2c;
          }
          else
          {
            // center text
            uVar1 |= 0x8000;

            iVar3 = param_2 + mb->posX_prev + local_30;

            // get pointer to string, from index
            uVar4 = sdata->lngStrings[uVar8];

            iVar5 = (int)sVar11;
          }

          // Draw string
          DecalFont_DrawLine(uVar4, iVar3, sVar9, iVar5, uVar1);
        }
        sVar9 = sVar9 + local_62;
      }

      // keep count of row
      sVar12 = sVar12 + 1;

      // as long as another row is valid
    } while (row->stringIndex != -1);
  }

  if ((mb->state & 0x104) == 0)
  {
    local_70 = local_40 + (short)param_2 + mb->posX_prev;
    local_6e = local_58 + mb->posY_prev + local_38;
    if ((mb->state & SHOW_ONLY_HIGHLIT_ROW) == 0)
    {
      local_6e = local_6e + mb->rowSelected * local_62 + local_50 + -1;
    }
    else
    {
      local_6e = local_6e + local_50 + -1;
    }
    if ((mb->state & USE_SMALL_FONT) == 0)
    {
      local_6a = -3;
    }
    else
    {
      local_6a = 1;
    }
    local_6a = local_62 + local_6a;
    if (-1 < mb->stringIndexTitle)
    {
      local_6e = local_48 + local_6e + 6;
    }

    // if normal,
    // draw menu row highlight
    puVar6 = &sdata->menuRowHighlight_Normal;

    // if draw green save/load
    if ((mb[10] & 0x10U) != 0)
    {
      // draw green menu row highlight
      puVar6 = &sdata->menuRowHighlight_Green;
    }

    local_6c = width;
    CTR_Box_DrawClearBox(&local_70, puVar6, 1, gGT->backBuffer->otMem.startPlusFour, &gGT->backBuffer->primMem);
  }

  // if a submenu is being drawn in a hierarchy structure
  if ((mb->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
  {
    // recursively call this function,
    // draw the next menu within this menu
    MENUBOX_DrawSelf(
        // offset 0x24, pointer to next menu
        mb->ptrNextBox_InHierarchy,

        (int)(param_2 + mb->posX_prev),
        (int)(short)(local_38 + local_58 + mb->posY_prev + local_62 + 0xc),

        // same width in parent and child
        (int)(short)width);
  }
  if ((mb->state & ONLY_DRAW_TITLE) == 0)
  {
    sVar11 = mb->posX_prev;
    sVar9 = mb->posY_prev;
    local_62 = (local_60 + 8) - (u_short)(*(byte *)(mb + 4) >> 7);
  }
  else
  {
    sVar11 = mb->posX_prev;
    sVar9 = mb->posY_prev;
    local_62 = local_62 + 8;
  }
  local_64 = width + 0xc;
  local_66 = local_38 + local_58 + sVar9 + -4;
  local_68 = local_40 + (short)param_2 + sVar11 + -6;

  // draw background of menubox
  MENUBOX_DrawFullRect(mb, &local_68);
  return;
}
 