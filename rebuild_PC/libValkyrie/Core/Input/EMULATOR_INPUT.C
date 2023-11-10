#include "EMULATOR_INPUT.H"

#include "Core/EMULATOR.H"

int g_initialisedPadSubsystem = FALSE;
unsigned char* padData[MAX_CONTROLLERS];
unsigned char* padDataDebug[MAX_CONTROLLERS];
int padAllowCommunication = 1;

#if defined(SDL2)

#define PAD_FLAG_SUBSYSTEM_INITED 0
#define PAD_FLAG_HAPTIC_INITED 1

unsigned int padFlags[MAX_CONTROLLERS];

SDL_Joystick* padJoyStickHandle[MAX_CONTROLLERS];
SDL_GameController* padHandle[MAX_CONTROLLERS];
unsigned char* padRumbleData[MAX_CONTROLLERS];
const unsigned char* keyboardState;

SDL_GameController* padHandleDebug[MAX_CONTROLLERS];
const unsigned char* keyboardStateDebug;

void Emulator_AddController(unsigned int index)
{
	if (SDL_IsGameController(index) && index < MAX_CONTROLLERS)
	{
		padHandle[index] = SDL_GameControllerOpen(index);
		padJoyStickHandle[index] = SDL_GameControllerGetJoystick(padHandle[index]);

		if (SDL_JoystickIsHaptic(padJoyStickHandle[index]) && !(padFlags[index] & 1 << PAD_FLAG_HAPTIC_INITED))
		{
			SDL_HapticRumbleInit(SDL_HapticOpenFromJoystick(padJoyStickHandle[index]));
			padFlags[index] |= 1 << PAD_FLAG_HAPTIC_INITED;
		}
	}
}

void Emulator_InitialiseSDLInput(const unsigned char** kbState, int isDebugInput)
{
	if (isDebugInput == TRUE && g_initialisedPadSubsystem == TRUE)
	{
		return;
	}

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		eprinterr("Failed to initialise subsystem GAMECONTROLLER\n");
	}

#if defined(__EMSCRIPTEN__) && 0//Bug in emscripten, if called to early, always says 0.
	int attempts = 1000;
	while (attempts--)
	{
		if (SDL_NumJoysticks() > 0)
		{
			break;
		}
	}
#endif

	if (SDL_NumJoysticks() < 1)
	{
		eprinterr("Failed to locate a connected gamepad!\n");
	}
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			Emulator_AddController(i);
		}
	}

	kbState[0] = SDL_GetKeyboardState(NULL);
}
#endif

#if defined(SDL2)
unsigned short UpdateGameControllerInput(SDL_GameController* pad)
{
	unsigned short ret = 0xFFFF;


	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_X))//Square
	{
		ret &= ~0x8000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B))//Circle
	{
		ret &= ~0x2000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_Y))//Triangle
	{
		ret &= ~0x1000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A))//Cross
	{
		ret &= ~0x4000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER))//L1
	{
		ret &= ~0x400;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))//R1
	{
		ret &= ~0x800;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_UP))//UP
	{
		ret &= ~0x10;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))//DOWN
	{
		ret &= ~0x40;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT))//LEFT
	{
		ret &= ~0x80;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))//RIGHT
	{
		ret &= ~0x20;
	}

	if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERLEFT))//L2
	{
		ret &= ~0x100;
	}

	if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT))//R2
	{
		ret &= ~0x200;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_LEFTSTICK))//L3
	{
		ret &= ~0x2;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_RIGHTSTICK))//R3
	{
		ret &= ~0x4;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_BACK))//SELECT
	{
		ret &= ~0x1;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_START))//START
	{
		ret &= ~0x8;
	}
	return ret;
}
#endif

#if defined(SDL2)
void UpdateGameControllerAnalogInput(SDL_GameController* pad, void* analogR, void* analogL)
{

#define PSX_MIN 0
#define PSX_MAX 255

#define SDL_MIN -32768
#define SDL_MAX 32767

	///@FIXME 0 is not exactly 0x80 it's 0x7F!
#define TRANSLATE(x) (unsigned char)((PSX_MAX - PSX_MIN) * (x - SDL_MIN) / (SDL_MAX - SDL_MIN)) + PSX_MIN

	struct Analog
	{
		unsigned char x;
		unsigned char y;
	};

	Analog* ar = (Analog*)analogR;
	Analog* al = (Analog*)analogL;

	if (ar != NULL)
	{
		ar->x = TRANSLATE(SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_RIGHTX));
		ar->y = TRANSLATE(SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_RIGHTY));
	}

	if (al != NULL)
	{
		al->x = TRANSLATE(SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTX));
		al->y = TRANSLATE(SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTY));
	}
}
#endif

unsigned short UpdateTouchInput()
{
#if defined(TOUCH_UI)
	extern unsigned short resultTouchKeysPressed;
	unsigned short ret = 0xFFFF;
	ret &= ~resultTouchKeysPressed;
	return ret;
#else
	return 0xFFFF;
#endif
}

unsigned short UpdateKeyboardInput()
{
	unsigned short ret = UpdateTouchInput();

#if defined(SDL2)
	//Not initialised yet
	if (keyboardState == NULL)
	{
		return ret;
	}

	SDL_PumpEvents();

	if (keyboardState[SDL_SCANCODE_X])//Square
	{
		ret &= ~0x8000;
	}

	if (keyboardState[SDL_SCANCODE_V])//Circle
	{
		ret &= ~0x2000;
	}

	if (keyboardState[SDL_SCANCODE_Z])//Triangle
	{
		ret &= ~0x1000;
	}

	if (keyboardState[SDL_SCANCODE_C])//Cross
	{
		ret &= ~0x4000;
	}

	if (keyboardState[SDL_SCANCODE_LSHIFT])//L1
	{
		ret &= ~0x400;
	}

	if (keyboardState[SDL_SCANCODE_RSHIFT])//R1
	{
		ret &= ~0x800;
	}

	if (keyboardState[SDL_SCANCODE_UP])//UP
	{
		ret &= ~0x10;
	}

	if (keyboardState[SDL_SCANCODE_DOWN])//DOWN
	{
		ret &= ~0x40;
	}

	if (keyboardState[SDL_SCANCODE_LEFT])//LEFT
	{
		ret &= ~0x80;
	}

	if (keyboardState[SDL_SCANCODE_RIGHT])//RIGHT
	{
		ret &= ~0x20;
	}

	if (keyboardState[SDL_SCANCODE_LCTRL])//L2
	{
		ret &= ~0x100;
	}

	if (keyboardState[SDL_SCANCODE_RCTRL])//R2
	{
		ret &= ~0x200;
	}

	if (keyboardState[SDL_SCANCODE_SPACE])//SELECT
	{
		ret &= ~0x1;
	}

	if (keyboardState[SDL_SCANCODE_RETURN])//START
	{
		ret &= ~0x8;
	}
#endif
	return ret;
}

unsigned short UpdateKeyboardInputDebug()
{
	unsigned short ret = 0xFFFF;

#if defined(SDL2)
	//Not initialised yet
	if (keyboardStateDebug == NULL)
	{
		return ret;
	}

	SDL_PumpEvents();

	if (keyboardStateDebug[SDL_SCANCODE_X])//Square
	{
		ret &= ~0x8000;
	}

	if (keyboardStateDebug[SDL_SCANCODE_V])//Circle
	{
		ret &= ~0x2000;
	}

	if (keyboardStateDebug[SDL_SCANCODE_Z])//Triangle
	{
		ret &= ~0x1000;
	}

	if (keyboardStateDebug[SDL_SCANCODE_C])//Cross
	{
		ret &= ~0x4000;
	}

	if (keyboardStateDebug[SDL_SCANCODE_LSHIFT])//L1
	{
		ret &= ~0x400;
	}

	if (keyboardStateDebug[SDL_SCANCODE_RSHIFT])//R1
	{
		ret &= ~0x800;
	}

	if (keyboardStateDebug[SDL_SCANCODE_UP])//UP
	{
		ret &= ~0x10;
	}

	if (keyboardStateDebug[SDL_SCANCODE_DOWN])//DOWN
	{
		ret &= ~0x40;
	}

	if (keyboardStateDebug[SDL_SCANCODE_LEFT])//LEFT
	{
		ret &= ~0x80;
	}

	if (keyboardStateDebug[SDL_SCANCODE_RIGHT])//RIGHT
	{
		ret &= ~0x20;
	}

	if (keyboardStateDebug[SDL_SCANCODE_LCTRL])//L2
	{
		ret &= ~0x100;
	}

	if (keyboardStateDebug[SDL_SCANCODE_RCTRL])//R2
	{
		ret &= ~0x200;
	}

	if (keyboardStateDebug[SDL_SCANCODE_SPACE])//SELECT
	{
		ret &= ~0x1;
	}

	if (keyboardStateDebug[SDL_SCANCODE_RETURN])//START
	{
		ret &= ~0x8;
	}
#endif
	return ret;
}

#if defined(__EMSCRIPTEN__)
void EMSCRIPTEN_KEEPALIVE Emulator_SetFocus(int state)
{
	int enabled = state ? SDL_ENABLE : SDL_DISABLE;
	SDL_EventState(SDL_TEXTINPUT, enabled);
	SDL_EventState(SDL_KEYDOWN, enabled);
	SDL_EventState(SDL_KEYUP, enabled);
	SDL_EventState(SDL_MOUSEMOTION, enabled);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, enabled);
	SDL_EventState(SDL_MOUSEBUTTONUP, enabled);
}
#endif