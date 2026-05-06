#include <common.h>

// NOTE(aalhendi): WorkInProgress only replaces CS_Thread_UseOpcode,
// NOTE(aalhendi): so read the original overlay garage data at 0x800b8598.
#define gGarage (*(struct OVR233_Garage*)0x800b8598)

// TODO(aalhendi): can probably remove when defined in `functions.h`
int CS_Instance_SafeCheckAnimFrame(struct Instance* inst, int unused1, int unused2, int desiredFrame);

static inline void CS_SaveDecodedOpcode(const struct CutsceneObj* cs, int out[5])
{
  const int* src = (const int*)&cs->decodedOpcode;

  out[0] = src[0];
  out[1] = src[1];
  out[2] = src[2];
  out[3] = src[3];
  out[4] = src[4];
}

static inline void CS_RestoreDecodedOpcode(struct CutsceneObj* cs, const int in[5])
{
  int* dst = (int*)&cs->decodedOpcode;

  dst[0] = in[0];
  dst[1] = in[1];
  dst[2] = in[2];
  dst[3] = in[3];
  dst[4] = in[4];
}

// pass instance and object
bool CS_Thread_UseOpcode(struct Instance* instance, struct CutsceneObj* cs)

{
  unsigned char numPlayers;
  bool frameBoundaryHit;
  short numCamPathPoints;
  short gameModeTarget;
  unsigned short clockEffectFlags;
  unsigned short cutsceneFlags;
  unsigned int conditionMet;
  int iVar8;
  char **cutsceneOpcodes;
  int iVar10;
  short levelToLoad;
  int distanceToScreen;
  struct Thread* dancerThread;
  char* opcodeAt;
  int iVar12;
  struct CsOpcodeMeta* opcodeMeta;
  short* opcodeMetaShorts;
  short* frameData;
  int rotInterpNumerator;
  int rotInterpStartFrame;
  int rotInterpFrameRange;
  int nextFrameTime;
  int lodIndex;
  struct ModelHeader* modelHeader;
  // NOTE(aalhendi): Original backs up the inline decoded-opcode buffer at cs+0x4c..0x5f.
  // NOTE(aalhendi): Temporary CS_ScriptCmd_OpcodeAt calls below decode into that same buffer.
  int metadataBackup[5];
  short camRot[3];
  short camPos[3];
  unsigned short camPathFlags[2];
  int animIndex;
  int opcodeDuration;
  int opcodeChanged;
  int elapsedTimeRemaining;

  // param1 is instance, param2 is object

  struct GameTracker* gGT = sdata->gGT;
  CS_SaveDecodedOpcode(cs, metadataBackup);
  if (instance != 0)
  {
	// if instance is using a split-line
    if ((instance->flags & SPLIT_LINE) != 0) {
      instance->vertSplit = OVR_233.VertSplitLine;
    }

	// instance -> model -> modelID == podium_second
    if ((int)instance->model->id == (unsigned int)(u_char)gGT->podium_modelIndex_Second)
	{
      if (OVR_233.PodiumInitUnk2 - 0x65U < 0x87)
	  {
		// make invisible
        instance->flags |= HIDE_MODEL;
      }
      else
	  {
		// if object is not invisible, then skip a few lines
        if ((instance->flags & HIDE_MODEL) == 0) goto afterPodiumSecondModelCheck;

		// if object is invisible...

        instance->unk50 -= 2;
        instance->unk51 -= 2;

		// make visible
        instance->flags &= ~HIDE_MODEL;
      }
    }
afterPodiumSecondModelCheck:

    // instance -> model -> modelID == podium_first
    if ((int)instance->model->id == (unsigned int)(u_char)gGT->podium_modelIndex_First) {
      if (OVR_233.PodiumInitUnk2 - 0x83U < 0x69)
	  {
		// make invisible
        instance->flags |= HIDE_MODEL;
      }
      else
	  {
		// if object is not invisible, then skip a few lines
        if ((instance->flags & HIDE_MODEL) == 0) goto afterPodiumFirstModelCheck;
        instance->unk50 -= 6;
        instance->unk51 -= 6;

		// make visible
        instance->flags &= ~HIDE_MODEL;
      }
    }
afterPodiumFirstModelCheck:
    if ((cs->flags & 0x80) != 0) {

	  // all these are STATIC_xxxSELECT
	  if (((int)instance->model->id + -0xce ==
           (int)gGarage.unusedArr_garageChars[sdata->advCharSelectIndex_curr]) &&
         (gGarage.boolSelected == 1))
	  {

		if ((cs->flags & 0x100) == 0)
		{
		  // pushBuffer fade,
		  // flash white after selecting Adv Character
          gGT->pushBuffer[0].fadeFromBlack_currentValue = 0x1fff;
          gGT->pushBuffer[0].fadeFromBlack_desiredResult = 0x1000;
          gGT->pushBuffer[0].fade_step = 0xfd56;

          cs->flags |= 0x100;

		  // CS_ScriptCmd_OpcodeAt
          CS_ScriptCmd_OpcodeAt
                    (cs,OVR_233.advCharSelectSelectOpcodes

							 // instance -> model -> modelID, - 0xce (STATIC_CRASHSELECT)
                             [(int)instance->model->id - STATIC_CRASHSELECT]);

          CS_SaveDecodedOpcode(cs, metadataBackup);
reloadAdvCharSelectOpcodeState:
          cs->unk18 = ((int*)&cs->decodedOpcode)[2];
          iVar8 = MixRNG_Scramble();
          opcodeMeta = &cs->decodedOpcode;
          opcodeMetaShorts = (short*)opcodeMeta;
          cs->unk14 =
               opcodeMeta->frameStart +
               (short)((int)((iVar8 >> 2 & 0xfffU) *
                            (((int)opcodeMeta->frameEnd - (int)opcodeMeta->frameStart) + 1)) >>
                      0xc);
        }
      }

      else {
        if ((cs->flags & 0x100) != 0) {
          cs->flags &= 0xfeff;

		  // CS_ScriptCmd_OpcodeAt
          CS_ScriptCmd_OpcodeAt
                    (cs,OVR_233.advCharSelectDeselectOpcodes
                             [(int)instance->model->id - STATIC_CRASHSELECT]);

		  CS_SaveDecodedOpcode(cs, metadataBackup);
          goto reloadAdvCharSelectOpcodeState;
        }
      }
    }
  }
  opcodeDuration = (int)cs->unk14;
  iVar12 = cs->unk18;
  iVar8 = (int)cs->unk1e;

  // elapsed time per frame
  elapsedTimeRemaining = gGT->elapsedTimeMS;

  opcodeMeta = &cs->decodedOpcode;
  opcodeMetaShorts = (short*)opcodeMeta;
  animIndex = (int)opcodeMeta->animIndex;

  if (instance == 0)
  {
	// CAM_Path_GetNumPoints
    numCamPathPoints = CAM_Path_GetNumPoints();

    if ((int)numCamPathPoints != 0)
	{
	  // gGT->msInThisLEV
      iVar10 = ((s32)((u32)gGT->msInThisLEV << 11)) >> 16;

      if (iVar10 < (int)numCamPathPoints + -1)
	  {
		// CAM_Path_Move
		CAM_Path_Move(iVar10,camPos,camRot,camPathFlags);

		// Store camera path output in main pushBuffer.
		gGT->pushBuffer[0].pos[0] = camPos[0];
        gGT->pushBuffer[0].pos[1] = camPos[1];
        gGT->pushBuffer[0].pos[2] = camPos[2];
        gGT->pushBuffer[0].rot[0] = camRot[0];
        gGT->pushBuffer[0].rot[1] = camRot[1];
        gGT->pushBuffer[0].rot[2] = camRot[2];
      }
      else {
        if (opcodeMeta->opcode == 0x14)
		{
		  // CS_ScriptCmd_OpcodeNext
          CS_ScriptCmd_OpcodeNext(cs);
        }

		// CAM_Path_Move
		CAM_Path_Move((int)(short)(numCamPathPoints + -1),gGT->pushBuffer[0].pos,gGT->pushBuffer[0].rot,camPathFlags);
      }

	  // gGT->clockEffectEnabled
	  clockEffectFlags = gGT->clockEffectEnabled;
      gGT->clockEffectEnabled = clockEffectFlags & 0xfffe;

      if ((camPathFlags[0] & 1) != 0) {
        gGT->clockEffectEnabled = clockEffectFlags & 0xfffe | 1;
      }
      if ((cs->flags & 0x20) == 0)
	  {
		// gGT->pushBuffer[0].distanceToScreen_PREV

		// Default FOV
        gGT->pushBuffer[0].distanceToScreen_PREV = 0x100;

		// Oxide Intro, Transition between Polar/Dingo
        if ((camPathFlags[0] & 2) != 0)
		{
		  // Wide FOV (zoom out)
          gGT->pushBuffer[0].distanceToScreen_PREV = 0x50;
        }

		// Oxide Intro, oxide flies down to earth
		if ((camPathFlags[0] & 4) != 0)
		{
		  // Narrow FOV (zoom in)
          gGT->pushBuffer[0].distanceToScreen_PREV = 0x278;
        }

		if ((camPathFlags[0] & 0x20) != 0)
		{
          gGT->pushBuffer[0].distanceToScreen_PREV = 0x1eb;
        }

		if ((camPathFlags[0] & 0x40) != 0)
		{
          gGT->pushBuffer[0].distanceToScreen_PREV = 0x14d;
        }
      }
      if (((camPathFlags[0] & 0x10) != 0) && ((MixRNG_Scramble() & 0xf) == 0)) {

		// CTR_Box_DrawClearBox
		CTR_Box_DrawClearBox(&OVR_233.introClearBoxRect,&OVR_233.introClearBoxColor,1,
                     gGT->backBuffer->otMem.startPlusFour,

					 // pointer to PrimMem struct
					 &gGT->backBuffer->primMem);
      }

	  // if level ID is Naughty Dog Box
      if (gGT->levelID == 0x29)
	  {
		// Narrow FOV (zoom in)
		// gGT->pushBuffer[0].distanceToScreen_PREV
        gGT->pushBuffer[0].distanceToScreen_PREV = 0x140;
      }

	  // gGT->pushBuffer[0].distanceToScreen_CURR
      gGT->pushBuffer[0].distanceToScreen_CURR = gGT->pushBuffer[0].distanceToScreen_PREV;
    }

	// If you tap the "Start" button
    if ((sdata->gGamepads->gamepad[0].buttonsTapped & BTN_START) != 0)
	{
      gGT->clockEffectEnabled &= 0xfffe;

	  // if not between 0x2c and 0x2c+0x13,
	  // if not between 44 and 63, if not credits
      if (0x13 < gGT->levelID - 0x2cU)
	  {
		// if level ID is Naughty Dog Box
        if (gGT->levelID == 0x29)
		{
		  // if less than 6 seconds passed, Start button does nothing
          if ((unsigned int)gGT->msInThisLEV >> 5 < 0xb5) goto afterCameraAndSkipChecks;

		  // RaceFlag_SetCanDraw
		  RaceFlag_SetCanDraw(1);

		  // RaceFlag_IsTransitioning
		  iVar8 = RaceFlag_IsTransitioning();
          if (
				// if not
				(iVar8 == 0) &&

				(
					// RaceFlag_IsFullyOnScreen
					iVar8 = RaceFlag_IsFullyOnScreen(),
					iVar8 == 0
				)
			 )
		  {

			// RaceFlag_SetFullyOffScreen
			RaceFlag_SetFullyOffScreen();
          }
        }

		// if level ID is not Naughty Dog Box
        else
		{
		  // RaceFlag_SetCanDraw
          RaceFlag_SetCanDraw(1);

		  // RaceFlag_IsTransitioning
          iVar8 = RaceFlag_IsTransitioning();

          if (
				// if not
				(iVar8 == 0) &&

				(
					// RaceFlag_IsFullyOnScreen
					iVar8 = RaceFlag_IsFullyOnScreen(),
					iVar8 == 0
				)
			 )
		  {
			// RaceFlag_SetFullyOffScreen
            RaceFlag_SetFullyOffScreen();
          }

		  // go to credits
          levelToLoad = CREDITS_CRASH;

          if (gGT->levelID - 0x2aU < 2) goto requestSkipLevelLoad;
        }

		// CseqMusic_StopAll
		CseqMusic_StopAll();

		// CDSYS_XAPauseRequest
        CDSYS_XAPauseRequest();

		// RaceFlag_SetDrawOrder
        RaceFlag_SetDrawOrder(0);

		// main menu
		levelToLoad = MAIN_MENU_LEVEL;
requestSkipLevelLoad:

		// load LEV
        MainRaceTrack_RequestLoad(levelToLoad);

		// end cutscene
        OVR_233.isCutsceneOver = 1;

	    // remove VEH_FREEZE_PODIUM
        gGT->gameMode2 &= ~VEH_FREEZE_PODIUM;

		CS_RestoreDecodedOpcode(cs, metadataBackup);

		// kill cutscene thread
        return 1;
      }

	  // else, if it is credits...

	  // CS_Credits_End
      CS_Credits_End();
    }
  }
afterCameraAndSkipChecks:
  opcodeChanged = 0;
  if (elapsedTimeRemaining == 0) {
updateInstanceAndReturn:
    cs->unk18 = iVar12;
    cs->animIndex = (char)animIndex;
    cs->unk1e = (short)iVar8;
    cs->unk14 = (short)opcodeDuration;
    iVar10 = (int)opcodeMeta->rotStart;
    iVar12 = iVar12 >> 5;

    if (iVar10 != (int)opcodeMeta->rotEnd) {
      rotInterpStartFrame = opcodeMeta->arg0.i;
      if (opcodeMeta->arg1.i != rotInterpStartFrame) {
        rotInterpNumerator = ((((int)opcodeMeta->rotEnd - iVar10) + 0x800U & 0xfff) - 0x800) *
                             (iVar12 - rotInterpStartFrame);
        rotInterpFrameRange = opcodeMeta->arg1.i - rotInterpStartFrame;
        if (rotInterpFrameRange < 0) {
          rotInterpFrameRange = -rotInterpFrameRange;
        }
        iVar10 = iVar10 + rotInterpNumerator / rotInterpFrameRange;
      }
    }
    iVar10 = iVar10 + cs->unk1c;
    if ((iVar10 != (int)cs->unk22) &&
       (cs->unk22 = (short)iVar10, instance != 0))
	{
	   // convert 3 rotation shorts into rotation matrix
      ConvertRotToMatrix(&instance->matrix,&cs->unk20);
    }

	// CS_Instance_SafeCheckAnimFrame
    iVar8 = CS_Instance_SafeCheckAnimFrame(instance,animIndex,iVar8,iVar12);

	if (iVar12 != iVar8) {
      animIndex &= ~0xff;
      iVar12 = 0;
    }
    if (instance != 0)
	{
	  // instance animation
      instance->animFrame = (short)iVar12;
      instance->animIndex = (char)animIndex;
    }
    if (cs->frameOverrideRoot != 0)
	{
      frameData = (short*)((uintptr_t)(*cs->frameOverrideRoot) + iVar12 * 0x20);

      // instance rotation matrix
	  *(int*)((u_char*)&instance->matrix + 0x00) = *(int*)(frameData + 4);
      *(int*)((u_char*)&instance->matrix + 0x04) = *(int*)(frameData + 6);
      *(int*)((u_char*)&instance->matrix + 0x08) = *(int*)(frameData + 8);
      *(int*)((u_char*)&instance->matrix + 0x0c) = *(int*)(frameData + 10);
      *(int*)((u_char*)&instance->matrix + 0x10) = *(int*)(frameData + 0xc);

	  // instance position
      instance->matrix.t[0] = (int)*frameData;
      instance->matrix.t[1] = (int)frameData[1];
      instance->matrix.t[2] = (int)frameData[2];
    }
    return 0;
  }
processOpcode:
  switch(opcodeMeta->opcode) {
  case 0:
  case 0x2a:
  case 0x2b:
    if (instance != 0) {
      cutsceneFlags = cs->flags;
      if ((cutsceneFlags & 0x200) != 0) {
        if (
			((cutsceneFlags & 0x400) == 0) &&

			// if XA is playing
			(sdata->XA_State == 3)
		   )
		{
          cs->flags = cutsceneFlags | 0x400;
        }

		// if XA is seeking, playing, or stopping
        if (sdata->XA_State != 0)
		{
          if ((cs->flags & 0x400) == 0) {
            iVar12 = 0;
          }
          else
		  {
			// CS_Instance_SafeCheckAnimFrame
			// last parameter given is related to XA_CurrOffset
            iVar12 = CS_Instance_SafeCheckAnimFrame(instance,animIndex,iVar8,(sdata->XA_CurrOffset * 0x1e00) / 0xac44);

			iVar12 = iVar12 << 5;
          }
          if (opcodeMeta->arg1.i << 5 < iVar12) break;
          goto updateInstanceAndReturn;
        }
        break;
      }
    }
    if (opcodeChanged != 0) {
      animIndex = (int)opcodeMeta->animIndex;

	  // CS_Instance_SafeCheckAnimFrame
      iVar12 = CS_Instance_SafeCheckAnimFrame(instance,animIndex,iVar8,opcodeMeta->arg0.i);


      iVar12 = iVar12 << 5;
      iVar10 = MixRNG_Scramble();
      opcodeChanged = 0;
      opcodeDuration = ((int)((iVar10 >> 2 & 0xfffU) * (((int)opcodeMeta->frameEnd - (int)opcodeMeta->frameStart) + 1)) >> 0xc)
                 + (int)opcodeMeta->frameStart;
    }
    frameBoundaryHit = false;
    if (opcodeMeta->arg1.i < opcodeMeta->arg0.i) {
      iVar10 = opcodeMeta->arg1.i * 0x20;
      iVar12 = iVar12 - elapsedTimeRemaining;
      if (iVar12 < iVar10) {
        elapsedTimeRemaining = iVar10 - iVar12;
markAnimationBoundary:
        frameBoundaryHit = true;
      }
    }
    else {

	  // CS_Instance_SafeCheckAnimFrame
	  // NOTE(aalhendi): Original MIPS leaves a3 as opcodeMeta->arg1.i here.
	  // NOTE(aalhendi): Ghidra shows a 3-arg call, but the callee still consumes a3.
	  iVar10 = CS_Instance_SafeCheckAnimFrame(instance,animIndex,iVar8,opcodeMeta->arg1.i);

      nextFrameTime = (iVar10 + 1) * 0x20;
      iVar12 = iVar12 + elapsedTimeRemaining;
      if (nextFrameTime <= iVar12) {
        frameBoundaryHit = true;
        elapsedTimeRemaining = 0;
        if (nextFrameTime != 0) {
          elapsedTimeRemaining = iVar12 + (iVar10 + 1) * -0x20;
          goto markAnimationBoundary;
        }
      }
    }
    if ((frameBoundaryHit) || (opcodeDuration < 1)) {
      opcodeDuration = opcodeDuration + -1;
      if (opcodeDuration < 1)
	  {
		// CS_ScriptCmd_OpcodeNext
        CS_ScriptCmd_OpcodeNext(cs);
        opcodeChanged = 1;
      }
      else
	  {
		// CS_Instance_SafeCheckAnimFrame
        iVar12 = CS_Instance_SafeCheckAnimFrame(instance,animIndex,iVar8,opcodeMeta->arg0.i);

		iVar12 = iVar12 << 5;
      }
    }
    else {
      elapsedTimeRemaining = 0;
    }
    goto finishOpcodeStep;

  // ???
  case 1:
    opcodeChanged = 1;

	// CS_ScriptCmd_OpcodeAt
    CS_ScriptCmd_OpcodeAt(cs,opcodeMeta->arg1.ptr);

    goto finishOpcodeStep;

  // ???
  case 2:
    if (instance != 0)
	{
	  // make invisible
      instance->flags |= HIDE_MODEL;
    }
    CS_RestoreDecodedOpcode(cs, metadataBackup);

	// kill cutscene thread
	return 1;

  // ???
  case 3:
    if (instance != 0)
	{
      struct CsThreadInitData* initData = (struct CsThreadInitData*)0x1f800108;
      int spawnModelID = opcodeMeta->arg1.i;

      CS_Instance_GetFrameData(
        instance,
        (int)opcodeMeta->animIndex,
        opcodeMeta->arg0.i,
        (u_short*)initData->podiumPos,
        (u_short*)initData->rot,
        0);

	  // position
      initData->podiumPos[0] += (short)instance->matrix.t[0];
      initData->podiumPos[1] += (short)instance->matrix.t[1];
      initData->podiumPos[2] += (short)instance->matrix.t[2];

	  // relative spawn offset
      initData->characterPos[0] = 0;
      initData->characterPos[1] = 0;
      initData->characterPos[2] = 0;

      if (spawnModelID == NDI_BOX_PARTICLES_01) {
        initData->rot[0] = 0;
        initData->rot[1] = 0;
        initData->rot[2] = 0;
      }

	  // CS_Thread_Init for "spawn"
      CS_Thread_Init(spawnModelID, OVR_233.s_spawn, (short*)initData, 0, instance->thread);
    }
    break;

  // ???
  case 4:
	// random number
    iVar10 = MixRNG_Scramble();

    if (opcodeMeta->arg0.i < (int)(iVar10 >> 2 & 0xffU))
	{
	  // CS_ScriptCmd_OpcodeNext
      CS_ScriptCmd_OpcodeNext(cs);
    }
    else
	{
	  // CS_ScriptCmd_OpcodeAt
      CS_ScriptCmd_OpcodeAt(cs,opcodeMeta->arg1.ptr);
    }
    opcodeChanged = 1;
    goto finishOpcodeStep;

  // PLAY SOUND
  case 5:

	// if you're at the adventure character select screen
    if (gGT->levelID == 0x28) {
      if (instance != 0)
	  {
		// Garage_PlayFX
        Garage_PlayFX(opcodeMeta->arg1.u,
                     (int)instance->model->id + -0xce);
      }
    }

	// if not...
	// if called from Naughty Dog Box Scene
    else
	{
	  // CS_Instance_BoolPlaySound
      iVar10 = CS_Instance_BoolPlaySound(cs,instance);

	  // if need to play sound
      if (iVar10 != 0)
	  {
		// OtherFX_Play, each sound in ND Box Scene
        OtherFX_Play((unsigned int)(unsigned short)opcodeMetaShorts[6],1);
      }
    }
    break;

  // STOP SOUND
  case 6:
	// OtherFX_Stop2
    OtherFX_Stop2((unsigned int)(unsigned short)opcodeMetaShorts[6]);
    break;

  // START MUSIC
  case 7:
	// CseqMusic_Start
    CseqMusic_Start((unsigned int)(unsigned short)opcodeMetaShorts[6],0,0,0,opcodeMeta->arg0.i);
    break;

  // RESTART MUSIC
  case 8:
	// CseqMusic_Restart
    CseqMusic_Restart((unsigned int)(unsigned short)opcodeMetaShorts[6],1);
    break;

  // FORCE LOD
  case 9:

    // if Instance
    if (instance != 0) {

	  // Inst -> model -> numHeaders,
	  iVar10 = (int)instance->model->numHeaders;

      if (
			(iVar10 != 0) &&

			// Inst -> model -> modelHeader,
			(modelHeader = instance->model->headers, modelHeader != 0)
		 )
	  {
        // LOD index from opcode
		lodIndex = opcodeMeta->arg1.i;

        iVar8 = lodIndex;
        if (iVar10 <= lodIndex) {
          lodIndex = iVar10 + -1;
          iVar8 = lodIndex;
        }

		// Disable drawing LODs
        while (lodIndex != 0)
		{
		  // erase maxDistanceLOD
          modelHeader->maxDistanceLOD = 0;

		  // next LOD
          lodIndex = lodIndex + -1;
          modelHeader++;
        }

		// headers[x].maxDistanceLOD
        modelHeader->maxDistanceLOD = 20000;
      }
    }
    break;

  // ???
  case 10:
    if (opcodeMeta->arg1.i == -1) {
      cutsceneFlags = cs->flags | 1;
    }
    else {
      cs->unk28 = 0;
      cutsceneFlags = cs->flags & 0xfffe;
    }
    cs->flags = cutsceneFlags;
    break;

  // ???
  case 0xb:
    cs->desiredScale = opcodeMetaShorts[4];
    cs->scaleSpeed = opcodeMetaShorts[6];

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // FADE WHITE TO NORMAL
  case 0xc:

	// pushBuffer fade values
    gGT->pushBuffer[0].fadeFromBlack_currentValue = 0x1fff;
    gGT->pushBuffer[0].fadeFromBlack_desiredResult = 0x1000;
    gGT->pushBuffer[0].fade_step = 0xfd56;

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // ???
  case 0xd:
    cutsceneFlags = cs->flags | opcodeMetaShorts[6];
    goto setFlagsAndAdvanceOpcode;

  // ???
  case 0xe:
    cs->flags &= ~opcodeMetaShorts[6];

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // SWAP LEVEL
  case 0xf:

	// need to swap LEV files
    gGT->bool_AdvHub_NeedToSwapLEV = 1;

	// if not going to credits
	if ((gGT->gameMode2 & CREDITS) == 0)
	{
      cutsceneOpcodes = OVR_233.introCutsceneOpcodes;

	  // intro cutscenes
	  iVar10 = gGT->levelID + -0x1e;
    }

	// if credits
	else
	{
      cutsceneOpcodes = OVR_233.creditsCutsceneOpcodes;

	  // credits
	  iVar10 = gGT->levelID + -0x2c;
    }

	// CS_ScriptCmd_OpcodeAt
    CS_ScriptCmd_OpcodeAt(cs,cutsceneOpcodes[iVar10]);

    goto updateInstanceAndReturn;

  // LOAD LEVEL
  case 0x10:

	// get level from opcode
	iVar10 = opcodeMeta->arg1.i;

	// set level ID
	gGT->levelID = iVar10;

	// oxide intro
	if (iVar10 == 0x1e)
	{
	  // RaceFlag_SetCanDraw
      RaceFlag_SetCanDraw(0);

requestDirectLevelLoad:

	  // remove VEH_FREEZE_PODIUM
      gGT->gameMode2 &= ~VEH_FREEZE_PODIUM;

	  // load LEV
	  MainRaceTrack_RequestLoad((int)(short)iVar10);
    }
    else {
      if (iVar10 < 0x1f)
	  {
		// gemstone valley
        if (iVar10 == 0x19)
		{
		  // gemstone valley
          levelToLoad = GEM_STONE_VALLEY;
requestMappedLevelLoad:

		  // remove VEH_FREEZE_PODIUM
          gGT->gameMode2 &= ~VEH_FREEZE_PODIUM;

		  // load LEV
		  MainRaceTrack_RequestLoad(levelToLoad);

		  break;
        }
      }
      else
	  {
		// main menu
        if (iVar10 == 0x27)
		{
		  // RaceFlag_SetDrawOrder
          RaceFlag_SetDrawOrder(0);
          levelToLoad = MAIN_MENU_LEVEL;
          goto requestMappedLevelLoad;
        }

		// Credits
        if (iVar10 == 0x2c) goto requestDirectLevelLoad;
      }

	  // Not:
	  //	Oxide Intro,
	  //	Gemstone Valley
	  //	Main Menu
	  //	Credits

	  // loading next swap-level
      OVR_233.boolLoadNextSwap = 1;

	  // LOAD_Hub_ReadFile
      LOAD_Hub_ReadFile(sdata->ptrBigfileCdPos_2,iVar10,3 - (int)gGT->activeMempackIndex);
    }
    break;

  // ???
  // what? loading 'something' that isnt a swap-level?
  case 0x11:
    if (
		// not loading next swap-level
		(OVR_233.boolLoadNextSwap == 0) ||

		// queueReady (queue in use)
		(sdata->queueReady == 0) ||

		// queueLength (queue in use)
		(sdata->queueLength != 0)
	   )
	{
		goto updateInstanceAndReturn;
    }
	break;

  // SET XA
  case 0x12:

	// CDSYS_XAPlay
    CDSYS_XAPlay(opcodeMeta->arg0.i,opcodeMeta->arg1.i);

	// if XA is not seeking, playing, or stopping
	if (sdata->XA_State != 0) {
      cs->flags = cs->flags & 0xfbff | 0x200;
    }
    break;

  case 0x13:

    // if XA is not playing
    if (sdata->XA_State == 0) {
      cutsceneFlags = cs->flags & 0xfdff;
      goto setFlagsAndAdvanceOpcode;
    }

  case 0x14:
    goto updateInstanceAndReturn;

  // SET STARS
  case 0x15:

	// number of players
    numPlayers = gGT->numPlyrCurrGame;

	// number of stars per screen = number of stars in level, divided by number of players
    gGT->stars.numStars =
         (short)((int)gGT->level1->stars.numStars / (int)(unsigned int)numPlayers);

	// other star-related data
    gGT->stars.spread = gGT->level1->stars.spread;
    gGT->stars.seed = gGT->level1->stars.seed;
    gGT->stars.distance = gGT->level1->stars.distance;

	// not loading swap-level
    OVR_233.boolLoadNextSwap = 0;

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // FLAG TRANSITION ON
  case 0x16:

	// RaceFlag_IsFullyOffScreen
    iVar10 = RaceFlag_IsFullyOffScreen();
    if (iVar10 == 1)
	{
	  // RaceFlag_SetCanDraw
      RaceFlag_SetCanDraw(1);

	  // RaceFlag_BeginTransition(GoOnscreen)
      RaceFlag_BeginTransition(1);
    }
    break;

  case 0x17:

	// RaceFlag_IsFullyOnScreen
    conditionMet = RaceFlag_IsFullyOnScreen();
    goto advanceIfConditionMet;

  // FLAG TRANSITION OFF
  case 0x18:

    // RaceFlag_IsFullyOnScreen
    iVar10 = RaceFlag_IsFullyOnScreen();
    if (iVar10 == 1)
	{
	  // RaceFlag_BeginTransition(GoOffscreen)
      RaceFlag_BeginTransition(2);
    }
    break;

  case 0x19:
    cs->particleID = opcodeMetaShorts[6];

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // MAKE INVISIBLE
  case 0x1a:
    if (instance != 0)
	{
	  // make invisible
      instance->flags |= HIDE_MODEL;
    }
    break;

  // MAKE VISIBLE
  case 0x1b:
    if (instance != 0)
	{
	  // make visible
      instance->flags &= ~HIDE_MODEL;
    }
    break;

  // Instance OT sorting offset
  case 0x1c:
    if (instance != 0) {
      instance->unk50 += (char)opcodeMeta->arg1.i;
      instance->unk51 += (char)opcodeMeta->arg1.i;
    }
    break;

  // INSTANCE SET FLAG
  case 0x1d:
    if (instance != 0) {
      instance->flags |= opcodeMeta->arg1.u;
    }
    break;

  // INSTANCE REMOVE FLAG
  case 0x1e:
    if (instance != 0) {
      instance->flags &= ~opcodeMeta->arg1.u;
    }
    break;

  case 0x1f:
    cs->unk4 = 0x1333;
    break;

  // END PODIUM CUTSCENE
  case 0x20:

	// end cutscene
    OVR_233.isCutsceneOver = 1;

	// CS_DestroyPodium_StartDriving
    CS_DestroyPodium_StartDriving();

	// undecided boss cutscene
    OVR_233.bossCutsceneIndex = -1;

	// hold 233 overlay, dont load 232 yet
	gGT->overlayTransition = 3;

	// remove VEH_FREEZE_PODIUM
    gGT->gameMode2 &= ~VEH_FREEZE_PODIUM;

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // PICK BOSS CUTSCENE
  case 0x21:

    // boss cutscene from opcode
    OVR_233.bossCutsceneIndex = opcodeMeta->arg1.i;

    if (
		// if oxide intro (collected all trophies)
		(OVR_233.bossCutsceneIndex == 0) &&

		// all 18 relics
		(0x11 < gGT->currAdvProfile.numRelics)
	  )
	{
	  // oxide intro (all relics) on gemstone valley
      OVR_233.bossCutsceneIndex = 9;
    }

	// go to boss cutscene
    OVR_233.cutsceneState = 1;
    break;

  // SET FOV
  case 0x22:
    distanceToScreen = opcodeMeta->arg1.i;

	// gGT->pushBuffer[0].distanceToScreen_PREV
	gGT->pushBuffer[0].distanceToScreen_PREV = distanceToScreen;

	// gGT->pushBuffer[0].distanceToScreen_CURR
    gGT->pushBuffer[0].distanceToScreen_CURR = distanceToScreen;

    cutsceneFlags = cs->flags | 0x20;
setFlagsAndAdvanceOpcode:
    cs->flags = cutsceneFlags;

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  case 0x23:
	// CS_Credits_IsTextValid
    conditionMet = CS_Credits_IsTextValid();
    goto advanceIfConditionMet;

  // CREDITS NEW DANCER
  case 0x24:
  {
    struct CsThreadInitData* initData = (struct CsThreadInitData*)0x1f800108;
    int dancerModelID = opcodeMeta->arg1.i;

    initData->podiumPos[0] = 0;
    initData->podiumPos[1] = 0;
    initData->podiumPos[2] = 0;
    initData->rot[0] = 0;
    initData->rot[1] = 0;
    initData->rot[2] = 0;
    initData->characterPos[0] = 0;
    initData->characterPos[1] = 0;
    initData->characterPos[2] = 0;

    gGT->podium_modelIndex_First = (u_char)dancerModelID;
    gGT->podium_modelIndex_Second = 0;
    gGT->podium_modelIndex_Third = 0;

	// STATIC_OXIDEDANCE
    if (dancerModelID == STATIC_OXIDEDANCE) {
      gGT->podium_modelIndex_First = 0;
      gGT->podium_modelIndex_Second = STATIC_OXIDEDANCE;
    }

	// STATIC_CRASHDANCE
    if (dancerModelID == STATIC_CRASHDANCE) {
      initData->rot[1] += 0x800;
    }

    initData->rot[0] += OVR_233.creditsDancerRotOffset[0];
    initData->rot[1] += OVR_233.creditsDancerRotOffset[1];
    initData->rot[2] += OVR_233.creditsDancerRotOffset[2];

	// CS_Thread_Init for "dancer"
    dancerThread = (struct Thread*)CS_Thread_Init(dancerModelID, OVR_233.s_g_dancer, (short*)initData, 0, 0);

	// store dancer thread globally,
	// and erase old dancer thread if it exists

	// CS_Credits_NewDancer
    CS_Credits_NewDancer(dancerThread,(int)opcodeMetaShorts[6]);
  }
    break;

  // CREDITS NEW GHOST
  case 0x25:

	// CS_Credits_NewCreditGhosts
    conditionMet = CS_Credits_NewCreditGhosts();

advanceIfConditionMet:
    conditionMet &= 0xffff;
    if (conditionMet == 0) goto updateInstanceAndReturn;
    break;

  // ADV GARAGE
  case 0x26:
    if (opcodeMeta->frameEnd == 0) {
      if ((opcodeMeta->arg0.i != (int)gGarage.unusedArr_garageChars[sdata->advCharSelectIndex_curr])
         || (gGarage.boolSelected == 0)) {
        opcodeAt = opcodeMeta->arg1.ptr;
branchToGarageOpcode:
        opcodeChanged = 1;

		// CS_ScriptCmd_OpcodeAt
        CS_ScriptCmd_OpcodeAt(cs,opcodeAt);
      }
    }
    else {
      if ((opcodeMeta->arg0.i == (int)gGarage.unusedArr_garageChars[sdata->advCharSelectIndex_curr])
         && (gGarage.boolSelected == 1)) {
        opcodeAt = opcodeMeta->arg1.ptr;
        goto branchToGarageOpcode;
      }
    }
    break;

  case 0x27:

	// gGT->msInThisLEV
    if ((unsigned int)gGT->msInThisLEV >> 5 < opcodeMeta->arg1.u)
		goto updateInstanceAndReturn;
    break;

  case 0x28:

	// CS_Instance_SafeCheckAnimFrame
	iVar12 = CS_Instance_SafeCheckAnimFrame(instance,animIndex,iVar8,iVar12 >> 5);

	iVar12 = iVar12 << 5;
    goto updateInstanceAndReturn;

  // CREDITS END
  case 0x29:

    // CS_Credits_End
    CS_Credits_End();

    CS_RestoreDecodedOpcode(cs, metadataBackup);

	// kill cutscene thread
    return 1;

  // SET GAME MODES
  case 0x2c:
    gameModeTarget = opcodeMeta->animIndex;
    if (gameModeTarget == 1)
	{
	  // gGT->gameMode2 |= flags
      gGT->gameMode2 |= opcodeMeta->arg1.u;
    }
    else {
      if (gameModeTarget < 2) {
        if (gameModeTarget == 0)
		{
		  // gGT->gameMode1 |= flags
          gGT->gameMode1 |= opcodeMeta->arg1.u;
        }
      }
      else {
        if (gameModeTarget == 2)
		{
		  // gGT->renderFlags |= flags
          gGT->renderFlags |= opcodeMeta->arg1.u;
        }
        else {
          if (gameModeTarget == 3)
		  {
			// gGT->renderFlags &= ~(flags)
            gGT->renderFlags &= ~opcodeMeta->arg1.u;
          }
        }
      }
    }
    break;

  case 0x2d:
    cs->Subtitles.textPos[0] = opcodeMeta->animIndex;
    cs->Subtitles.textPos[1] = opcodeMeta->frameStart;
    cs->Subtitles.lngIndex = opcodeMeta->frameEnd;
    cs->Subtitles.font = opcodeMeta->rotStart;
    cs->Subtitles.colors = opcodeMeta->rotEnd;

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  // FADE NORMAL TO BLACK
  case 0x2e:

	// pushBuffer_UI fade to black
    gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0;
    gGT->pushBuffer_UI.fade_step = 0xfd56;

	// CS_ScriptCmd_OpcodeNext
    CS_ScriptCmd_OpcodeNext(cs);

    goto finishOpcodeStep;

  case 0x2f:
    // pushBuffer_UI fade is NOT black
    if (0 < gGT->pushBuffer_UI.fadeFromBlack_currentValue) goto updateInstanceAndReturn;
    break;

  // SET VOLUME MODES
  case 0x30:
	// cutscene manipulated audio
    OVR_233.CutsceneManipulatesAudio = 1;

	// howl_VolumeSet
    howl_VolumeSet(0,(unsigned int)*((unsigned char*)opcodeMeta + 2));
    howl_VolumeSet(1,(unsigned int)*((unsigned char*)opcodeMeta + 4));
    howl_VolumeSet(2,(unsigned int)*((unsigned char*)opcodeMeta + 6));
    break;

  default:
    CS_RestoreDecodedOpcode(cs, metadataBackup);
    return 0;
  }

  // CS_ScriptCmd_OpcodeNext
  CS_ScriptCmd_OpcodeNext(cs);

finishOpcodeStep:
  if ((elapsedTimeRemaining != 0) || (opcodeChanged != 0)) goto processOpcode;
  goto updateInstanceAndReturn;
}
