#include <common.h>

short CS_ScriptCmd_ReadOpcode_GetShort(short **Opcodes)
{
  Opcodes[0] += 1;
  return *Opcodes[0];
}

u_int CS_ScriptCmd_ReadOpcode_GetInt(char **Opcodes)
{
  char* bytes = Opcodes[0];
  Opcodes[0] += 4;
  return bytes[3] << 0x18 | bytes[2] << 0x10 | bytes[1] << 8 | bytes[0];
}

// same as above function
u_int CS_ScriptCmd_ReadOpcode_GetInt_dup(char **Opcodes)
{
  char* bytes = Opcodes[0];
  Opcodes[0] += 4;
  return bytes[3] << 0x18 | bytes[2] << 0x10 | bytes[1] << 8 | bytes[0];
}

void CS_ScriptCmd_ReadOpcode_Main(struct CutsceneObj* cs)
{
  char meta;
  char* opcodes;
  short* offsets;
  char *local_18[2];

  opcodes = cs->currOpcode[0];
  local_18[0] = opcodes + 1;

  if (opcodes != cs->currOpcode[0])
  {
    // char offset of meta data
    offsets = (short*)cs->metadata;

    // remember 0x38 (curr opcode) as 0x40 (prev opcode)
    cs->prevOpcode = opcodes;
    offsets[0] = opcodes[0];

    // global hard-coded array of meta data
    meta = ((char*)0x800b14cc)[offsets[0]];

    if ((meta & 1) == 0)
    {
      // if this is always zero,
      // Spinning ND Box never disappears
      offsets[1] = 0;
    }
    // & 1
    else
    {
      offsets[1] = CS_ScriptCmd_ReadOpcode_GetShort(local_18);
    }

    if ((meta & 2) == 0)
    {
      // if this is always zero,
      // no new instances spawn after the initial instances
      // are loaded in a cutscene (no ND sparks, no ND drivers, etc)
      offsets[2] = 0;
    }
    // & 2
    else
    {
      offsets[2] = CS_ScriptCmd_ReadOpcode_GetShort(local_18);
    }

    if ((meta & 4) == 0)
    {
      // if this is always zero,
      // similar to & 2 == 0
      offsets[3] = 0;
    }
    // & 4
    else
    {
      offsets[3] =  CS_ScriptCmd_ReadOpcode_GetShort(local_18);
    }

    if ((meta & 8) == 0)
    {
      // clear XA category
      *(u_int*)(offsets[4]) = 0;
    }
    // & 8
    // CDSYS_XAPlay -- Category (param1)
    else
    {
      // set category
      *(u_int*)(offsets[4]) = CS_ScriptCmd_ReadOpcode_GetInt(local_18);
    }

    if ((meta & 0x10) == 0)
    {
      // clear XA index
      *(int*)offsets[6] = 0;
    }
    // & 0x10
    // CDSYS_XAPlay -- Index (param2)
    else
    {
      // set index
      *(u_int*)(offsets[6]) = CS_ScriptCmd_ReadOpcode_GetInt(local_18);
    }

    // & 0x20,
    // if always zero, ND Box works fine,
    // oxide intro crashes on first frame
    if ((meta & 0x20) != 0)
    {
      while (((u_int)local_18[0] & 3) != 0)
      {
        local_18[0] += 1;
      }

      *(u_int*)(offsets[6]) = CS_ScriptCmd_ReadOpcode_GetInt_dup(local_18);

      local_18[0] += 1;
    }

    // unknown
    if ((meta & 0x40) == 0)
    {
      offsets[8] = 0;
    }
    // & 0x40
    else
    {
      offsets[8] = CS_ScriptCmd_ReadOpcode_GetShort(local_18);
    }

    // unknown
    if ((meta & 0x80) == 0)
    {
      offsets[9] = 0;
    }
    // & 0x80
    else
    {
      offsets[9] = CS_ScriptCmd_ReadOpcode_GetShort(local_18);
    }
    cs->prevOpcode = local_18[0];
  }
  return;
}

void CS_ScriptCmd_OpcodeNext(struct CutsceneObj* cs)
{
  // erase prev opcode, so (38 == 40) will never happen
  cs->prevOpcode = 0xffffffff;

  // curr opcode (starting from the end of previous)
  cs->currOpcode[0] = cs->prevOpcode;

  CS_ScriptCmd_ReadOpcode_Main(cs);
}

void CS_ScriptCmd_OpcodeAt(struct CutsceneObj* cs, char* opCodeAt)
{
  // set curr opcode
  cs->currOpcode[0] = opCodeAt;

  // erase prev opcode, so (38 == 40) will never happen
  cs->prevOpcode = 0xffffffff;

  CS_ScriptCmd_ReadOpcode_Main(cs);
}