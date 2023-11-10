#include "EMULATOR.H"

#include "EMULATOR_VERSION.H"
#include "EMULATOR_GLOBALS.H"
#include "Public/EMULATOR_PUBLIC.H"
#include "Debug/CRASHHANDLER.H"
#include "Debug/BOUNTY_LIST.H"
#include "Core/Input/EMULATOR_INPUT.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include "Audio/EMULATOR_SPU.H"

#if defined(_WINDOWS)
#if defined(MEM_CHECK)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#include <vld.h>
#endif
#endif

#include "LIBGPU.H"
#include "LIBGTE.H"
#include "LIBETC.H"
#include "LIBPAD.H"
#if !defined(__ANDROID__) && !defined(SN_TARGET_PSP2) && !defined(PLATFORM_NX)  && !defined(PLATFORM_NX_ARM) && !defined(D3D12)  && !defined(PLATFORM_NX_ARM) && !defined(D3D12) && !defined(_XBOX) && !defined(__linux__)
#include <thread>
#endif
#include <assert.h>
#include <stdlib.h>

#define MAX_NUM_FINGER_TOUCHES (2)
int g_useHintedTouchUIFont = FALSE;
int g_touchHeld = FALSE;
int g_numTouchFingers = 0;
int g_touchAxis[MAX_NUM_FINGER_TOUCHES][2] = { 0, 0, 0, 0};

#if defined(SDL2) || (defined(OGLES) && defined(_WINDOWS))
extern SDL_Window* g_window;
#endif

extern int splitAgain;

#if defined(NTSC_VERSION)
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#include <stdio.h>
#include <string.h>

struct TouchButtonVRAM touchButtonsUI[10];

#if defined(D3D11)


#if defined(UWP) && !defined(UWP_SDL2)

using namespace Windows::Gaming::Input;

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

CoreWindow^ g_window;
std::thread g_uiThread;
char* g_windowName;
int g_windowReady = 0;

ref class App sealed : public IFrameworkView
{
	bool WindowClosed;
	unsigned int kbInputs;

public:
	virtual void Initialize(CoreApplicationView^ AppView)
	{
		AppView->Activated += ref new TypedEventHandler
			<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);
		CoreApplication::Suspending +=
			ref new EventHandler<SuspendingEventArgs^>(this, &App::Suspending);
		CoreApplication::Resuming +=
			ref new EventHandler<Object^>(this, &App::Resuming);
		
		WindowClosed = false;    // initialize to false
	}
	virtual void SetWindow(CoreWindow^ Window)
	{
		Window->Closed += ref new TypedEventHandler
			<CoreWindow^, CoreWindowEventArgs^>(this, &App::Closed);

		Window->KeyDown +=
			ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::OnKeyPressed);

		Window->KeyUp +=
			ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::OnKeyReleased);
	
		kbInputs = 0xFFFF;
	}

	void App::OnKeyPressed(CoreWindow^ sender, KeyEventArgs^ args)
	{
		if (args->VirtualKey == Windows::System::VirtualKey::X)//Square
		{
			kbInputs &= ~0x8000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::V)//Circle
		{
			kbInputs &= ~0x2000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Z)//Triangle
		{
			kbInputs &= ~0x1000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::C)//Cross
		{
			kbInputs &= ~0x4000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::LeftShift)//L1
		{
			kbInputs &= ~0x400;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::RightShift)//R1
		{
			kbInputs &= ~0x800;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Up)//UP
		{
			kbInputs &= ~0x10;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Down)//DOWN
		{
			kbInputs &= ~0x40;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Left)//LEFT
		{
			kbInputs &= ~0x80;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Right)//RIGHT
		{
			kbInputs &= ~0x20;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::LeftControl)//L2
		{
			kbInputs &= ~0x100;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::RightControl)//R2
		{
			kbInputs &= ~0x200;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Space)//SELECT
		{
			kbInputs &= ~0x1;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Enter)//START
		{
			kbInputs &= ~0x8;
		}

		padData[0][0] = 0;
		padData[0][1] = 0x41;
		((unsigned short*)padData[0])[1] = kbInputs;
	}

	void App::OnKeyReleased(CoreWindow^ sender, KeyEventArgs^ args)
	{
		if (args->VirtualKey == Windows::System::VirtualKey::X)//Square
		{
			kbInputs |= 0x8000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::V)//Circle
		{
			kbInputs |= 0x2000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Z)//Triangle
		{
			kbInputs |= 0x1000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::C)//Cross
		{
			kbInputs |= 0x4000;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::LeftShift)//L1
		{
			kbInputs |= 0x400;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::RightShift)//R1
		{
			kbInputs |= 0x800;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Up)//UP
		{
			kbInputs |= 0x10;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Down)//DOWN
		{
			kbInputs |= 0x40;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Left)//LEFT
		{
			kbInputs |= 0x80;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Right)//RIGHT
		{
			kbInputs |= 0x20;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::LeftControl)//L2
		{
			kbInputs |= 0x100;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::RightControl)//R2
		{
			kbInputs |= 0x200;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Space)//SELECT
		{
			kbInputs |= 0x1;
		}

		if (args->VirtualKey == Windows::System::VirtualKey::Enter)//START
		{
			kbInputs |= 0x8;
		}

		padData[0][0] = 0;
		padData[0][1] = 0x41;
		((unsigned short*)padData[0])[1] = kbInputs;
	}

	virtual void Load(String^ EntryPoint) {}
	virtual void Run()
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();

		g_window = Window;
		g_windowReady = 1;

		while (!WindowClosed)
		{
			Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
		}
	}
	virtual void Uninitialize() {}

	void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();
		Window->Activate();
	}

	void Closed(CoreWindow^ sender, CoreWindowEventArgs^ args)
	{
		WindowClosed = true;    // time to end the endless loop
	}

	void Suspending(Object^ Sender, SuspendingEventArgs^ Args) {}
	void Resuming(Object^ Sender, Object^ Args) {}
};


// the class definition that creates our core framework
ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView()
	{
		return ref new App();    // create the framework view and return it
	}
};

[MTAThread]    // define main() as a multi-threaded-apartment function

void CreateUWPApplication()
{
	CoreApplication::Run(ref new AppSource());
}

#endif

#endif

int g_otSize = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = { 0 };
#if !defined(__ANDROID__) && !defined(SN_TARGET_PSP2) && !defined(PLATFORM_NX) && !defined(PLATFORM_NX_ARM) && !defined(D3D12) && !defined(_XBOX) && !defined(__linux__)
std::thread counter_thread;
#endif
#if defined(__ANDROID__)
#define malloc SDL_malloc
#define free SDL_free
#endif

int g_texturelessMode = 0;
int g_emulatorPaused = 0;

void Emulator_HintOTSize(int ots)
{
	g_otSize = ots;
}

static int Emulator_InitialiseSDL2(char* windowName, int width, int height)
{
#if defined(XED3D)
	windowWidth = 1280;
	windowHeight = 720;
#else
	windowWidth  = width;
	windowHeight = height;
#endif

#if defined(SDL2)

	unsigned int flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO;

#if defined(SDL2_MIXER)
	flags |= SDL_INIT_AUDIO;
#endif

	//Initialise SDL2
	if (SDL_Init(flags) == 0)
	{
		SDL_version ver;
		SDL_GetVersion(&ver);
		eprintf("Initialised SDL2 Version: %d.%d.%d\n", ver.major, ver.minor, ver.patch);

#if !defined(RO_DOUBLE_BUFFERED)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
#endif

#if defined(OGLES)

#if defined(__ANDROID__)
        //Override to full screen.
        SDL_DisplayMode displayMode;
        if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
        {
            windowWidth = displayMode.w;
            windowHeight = displayMode.h;
        }
#endif

#if defined(__ANDROID__)
		SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
#endif
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OGLES_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#elif defined(OGL)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#if defined(_DEBUG)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
#endif
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
		return FALSE;
	}
#endif

#if defined(OGL)
	if (Emulator_InitialiseGLContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GL Context!\n");
		return FALSE;
	}
#elif defined(OGLES)
	if (Emulator_InitialiseGLESContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GLES Context!\n");
		return FALSE;
	}
#elif defined(D3D9) || defined(XED3D)
	if (Emulator_InitialiseD3D9Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D9 Context!\n");
		return FALSE;
	}
#elif defined(D3D11)
	if (Emulator_InitialiseD3D11Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D11 Context!\n");
		return FALSE;
	}
#elif defined(D3D12)
	if (Emulator_InitialiseD3D12Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D12 Context!\n");
		return FALSE;
	}
#elif defined(VULKAN)
	if (Emulator_InitialiseVulkanContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise Vulkan Context!\n");
		return FALSE;
	}
#elif defined(SN_TARGET_PSP2)
	if(Emulator_InitialiseGXMContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GXM Context!\n");
	}
#elif defined(PLATFORM_NX)
	if (Emulator_InitialiseNNContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise NX Context!\n");
	}
#endif

	return TRUE;
}

static int Emulator_InitialiseCore()
{
	return TRUE;
}

#if defined(EDITOR)
void Emulator_Initialise(char* windowName, int width, int height, int instance_index)
#else
void Emulator_Initialise(char* windowName, int width, int height)
#endif
{
#if defined(_WINDOWS)
#if defined(MEM_CHECK)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_crtBreakAlloc = 171;
#endif
#endif

	eprintf("Initialising %s.\n", EMULATOR_NAME);
	eprintf("VERSION: %d.%d\n", EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION);
	eprintf("Compile Date: %s Time: %s\n", EMULATOR_COMPILE_DATE, EMULATOR_COMPILE_TIME);
	
#if defined(UWP) && !defined(UWP_SDL2)
	g_windowName = windowName;
	//Thread required because UI will block game execution
	g_uiThread = std::thread(CreateUWPApplication);

	while (!g_windowReady)
	{
	}
#endif

	char finalWindowName[128];
	sprintf(finalWindowName, "%s - %s - v%d.%d - %s", windowName, renderBackendName, GAME_MAJOR_VERSION, GAME_MINOR_VERSION, GAME_ARCH_NAME);

	if (Emulator_InitialiseSDL2(finalWindowName, width, height) == FALSE)
	{
		eprinterr("Failed to Intialise SDL2\n");
		Emulator_ShutDown();
	}

	if (Emulator_InitialiseCore() == FALSE)
	{
		eprinterr("Failed to Intialise Emulator Core.\n");
		Emulator_ShutDown();
	}

	if (Emulator_CreateCommonResources() == FALSE)
	{
		eprinterr("Failed to Intialise GL.\n");
		Emulator_ShutDown();
	}

	g_swapTime = Emulator_GetTicks() - FIXED_TIME_STEP;

#if !defined(__ANDROID__)
	//counter_thread = std::thread(Emulator_CounterLoop);
#endif
}

void Emulator_CounterLoop()
{
	int64_t current_time;
	int64_t last_time = 0;
	int64_t start = Emulator_GetTicks();

	while (TRUE)
	{
		current_time = Emulator_GetTicks();

		if (current_time > last_time + 1000)
		{
			for (int i = 0; i < 3; i++)
			{
				//if (!counters[i].IsStopped)
				{
					
					//counters[i].cycle = SDL_GetTicks() - start;
					if (counters[i].target > 0)
					{
						counters[i].cycle += counters[i].value;

						if (counters[i].cycle >= counters[i].target)
						{
							counters[i].cycle %= counters[i].target;

							if (counters[i].padding00 != NULL)
							{
								counters[i].padding00();
							}
						}
					}
				}
			}
			last_time = current_time;
		}
	}
}

#if defined(USE_THREADS)
void Emulator_CounterWrapper(int timerID)
#else
unsigned int Emulator_CounterWrapper(unsigned int interval, void* pTimerID)
#endif
{
#if !defined(USE_THREADS)
	unsigned int timerID = ((unsigned int*)pTimerID)[0];
#endif

	{
#if defined(USE_THREADS)
#define CW_FPS 61

		int now = SDL_GetTicks();
		int lastFrame = SDL_GetTicks();

		while (TRUE)
		{
			now = SDL_GetTicks();
			int delta = now - lastFrame;
			lastFrame = now;

			if (delta < (1000 / CW_FPS))
			{
				Sleep((1000 / CW_FPS) - delta);
			}

			counters[timerID].padding00();
		}
		
#else
		if (counters[timerID].padding00 != NULL)
		{
			counters[timerID].padding00();
		}

		counters[timerID].cycle = Emulator_GetTicks() - counters[timerID].startTick;
#endif
			
	}

#if !defined(USE_THREADS)
	return interval;
#endif
}

void Emulator_GenerateLineArray(struct Vertex* vertex, short* p0, short* p1)
{
	// swap line coordinates for left-to-right and up-to-bottom direction
	if (p0[0] > p1[0]) {
		short *tmp = p0;
		p0 = p1;
		p1 = tmp;
	} else if (p0[0] == p1[0]) {
		 if (p0[1] > p1[1]) {
			short *tmp = p0;
			p0 = p1;
			p1 = tmp;
		 }
	}

	int dx = p1[0] - p0[0];
	int dy = p1[1] - p0[1];

	if (dx > abs(dy)) { // horizontal
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];

		vertex[1].x = p1[0] + 1;
		vertex[1].y = p1[1];

		vertex[2].x = vertex[1].x;
		vertex[2].y = vertex[1].y + 1;

		vertex[3].x = vertex[0].x;
		vertex[3].y = vertex[0].y + 1;
	} else { // vertical
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];

		vertex[1].x = p1[0];
		vertex[1].y = p1[1] + 1;

		vertex[2].x = vertex[1].x + 1;
		vertex[2].y = vertex[1].y;

		vertex[3].x = vertex[0].x + 1;
		vertex[3].y = vertex[0].y;
	} // TODO diagonal line alignment
}

#if defined(PGXP)
void Emulator_ResetPGXPCache()
{
	// Reset the ztable.
	memset(&pgxp_vertex_buffer[0], 0, pgxp_vertex_count * sizeof(PGXPVertex));

	pgxp_vertex_count = 0;
}
#endif

void Emulator_GenerateVertexArrayTriangle(struct Vertex* vertex, short* p0, short* p1, short* p2)
{
	assert(p0);
	assert(p1);
	assert(p2);

#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;
	PGXPVertex* pgxp_vertex_1 = NULL;
	PGXPVertex* pgxp_vertex_2 = NULL;

	for (int i = 0; i < pgxp_vertex_count; i++)
	{
		if (pgxp_vertex_0 != NULL && pgxp_vertex_1 != NULL && pgxp_vertex_2 != NULL)
		{
			break;
		}

		if(pgxp_vertex_buffer[i].used == TRUE)
		{
			//continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p0)[0] && pgxp_vertex_0 == NULL /*&& pgxp_vertex_buffer[i].originalSZ3 <= z + 4096*/)
		{
			pgxp_vertex_0 = &pgxp_vertex_buffer[i];
			pgxp_vertex_0->used = TRUE;
			continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p1)[0] && pgxp_vertex_1 == NULL /*&& pgxp_vertex_buffer[i].originalSZ3 <= z + 4096*/ )
		{
			pgxp_vertex_1 = &pgxp_vertex_buffer[i];
			pgxp_vertex_1->used = TRUE;
			continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p2)[0] && pgxp_vertex_2 == NULL /* && pgxp_vertex_buffer[i].originalSZ3 <= z + 4096*/)
		{
			pgxp_vertex_2 = &pgxp_vertex_buffer[i];
			pgxp_vertex_2->used = TRUE;
			continue;
		}
	}

	//Copy over position
	if (pgxp_vertex_0 != NULL)
	{
		vertex[0].x = pgxp_vertex_0->x;
		vertex[0].y = pgxp_vertex_0->y;
		vertex[0].z = 0.95f;
		vertex[0].w = pgxp_vertex_0->z;
	}
	else
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
	}

	if (pgxp_vertex_1 != NULL)
	{
		vertex[1].x = pgxp_vertex_1->x;
		vertex[1].y = pgxp_vertex_1->y;
		vertex[1].z = 0.95f;
		vertex[1].w = pgxp_vertex_1->z;
	}
	else
	{
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
	}

	if (pgxp_vertex_2 != NULL)
	{
		vertex[2].x = pgxp_vertex_2->x;
		vertex[2].y = pgxp_vertex_2->y;
		vertex[2].z = 0.95f;
		vertex[2].w = pgxp_vertex_2->z;
	}
	else
	{
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
	}
#else
	vertex[0].x = p0[0];
	vertex[0].y = p0[1];

	vertex[1].x = p1[0];
	vertex[1].y = p1[1];

	vertex[2].x = p2[0];
	vertex[2].y = p2[1];
#endif
}


void Emulator_DoSplitHackQuad(short* p0, short* p1, short* p2, short* p3)
{
	if (p0[0] == p1[0] && p0[0] == p2[0] && p0[0] == p3[0])
	{
		splitAgain = TRUE;
	}
	else
	{
		splitAgain = FALSE;
	}
}

void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3)
{
	assert(p0);
	assert(p1);
	assert(p2);
	assert(p3);

#if defined(PGXP)

	PGXPVertex* pgxp_vertex_0 = NULL;
	PGXPVertex* pgxp_vertex_1 = NULL;
	PGXPVertex* pgxp_vertex_2 = NULL;
	PGXPVertex* pgxp_vertex_3 = NULL;

	for (int i = 0; i < pgxp_vertex_count; i++)
	{
		if (pgxp_vertex_0 != NULL && pgxp_vertex_1 != NULL && pgxp_vertex_2 != NULL && pgxp_vertex_3 != NULL)
		{
			break;
		}

		if (pgxp_vertex_buffer[i].used == TRUE)
		{
			//continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p0)[0] && pgxp_vertex_0 == NULL)
		{
			pgxp_vertex_0 = &pgxp_vertex_buffer[i];
			pgxp_vertex_0->used = TRUE;
			continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p1)[0] && pgxp_vertex_1 == NULL)
		{
			pgxp_vertex_1 = &pgxp_vertex_buffer[i];
			pgxp_vertex_1->used = TRUE;
			continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p2)[0] && pgxp_vertex_2 == NULL)
		{
			pgxp_vertex_2 = &pgxp_vertex_buffer[i];
			pgxp_vertex_2->used = TRUE;
			continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p3)[0] && pgxp_vertex_3 == NULL)
		{
			pgxp_vertex_3 = &pgxp_vertex_buffer[i];
			pgxp_vertex_3->used = TRUE;
			continue;
		}
	}

	//Copy over position
	if (pgxp_vertex_0 != NULL)
	{
		vertex[0].x = pgxp_vertex_0->x;
		vertex[0].y = pgxp_vertex_0->y;
		vertex[0].z = 0.95f;
		vertex[0].w = pgxp_vertex_0->z;
	}
	else
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
#if defined(PGXP)
		vertex[0].z = 0.95f;
		vertex[0].w = 1.0f;
#endif
	}

	if (pgxp_vertex_1 != NULL)
	{
		vertex[1].x = pgxp_vertex_1->x;
		vertex[1].y = pgxp_vertex_1->y;
		vertex[1].z = 0.95f;
		vertex[1].w = pgxp_vertex_1->z;
	}
	else
	{
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
#if defined(PGXP)
		vertex[1].z = 0.95f;
		vertex[1].w = 1.0f;
#endif
	}

	if (pgxp_vertex_2 != NULL)
	{
		vertex[2].x = pgxp_vertex_2->x;
		vertex[2].y = pgxp_vertex_2->y;
		vertex[2].z = 0.95f;
		vertex[2].w = pgxp_vertex_2->z;
	}
	else
	{
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
#if defined(PGXP)
		vertex[2].z = 0.95f;
		vertex[2].w = 1.0f;
#endif
	}

	if (pgxp_vertex_3 != NULL)
	{
		vertex[3].x = pgxp_vertex_3->x;
		vertex[3].y = pgxp_vertex_3->y;
		vertex[3].z = 0.95f;
		vertex[3].w = pgxp_vertex_3->z;
	}
	else
	{
		vertex[3].x = (float)p3[0];
		vertex[3].y = (float)p3[1];
#if defined(PGXP)
		vertex[3].z = 0.95f;
		vertex[3].w = 1.0f;
#endif
	}
#else
	vertex[0].x = p0[0];
	vertex[0].y = p0[1];

	vertex[1].x = p1[0];
	vertex[1].y = p1[1];

	vertex[2].x = p2[0];
	vertex[2].y = p2[1];

	vertex[3].x = p3[0];
	vertex[3].y = p3[1];
#endif
}

void Emulator_GenerateVertexArrayRect(struct Vertex* vertex, short* p0, short w, short h)
{
	assert(p0);

#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;

	for (int i = 0; i < pgxp_vertex_count; i++)
	{
		if (pgxp_vertex_0 != NULL)
		{
			break;
		}

		if (pgxp_vertex_buffer[i].used == TRUE)
		{
			//continue;
		}

		if (pgxp_vertex_buffer[i].originalSXY2 == ((unsigned int*)p0)[0] && pgxp_vertex_0 == NULL)
		{
			pgxp_vertex_0 = &pgxp_vertex_buffer[i];
			pgxp_vertex_0->used = TRUE;
			continue;
		}
	}


	if (pgxp_vertex_0 != NULL)
	{
		vertex[0].x = pgxp_vertex_0->x;
		vertex[0].y = pgxp_vertex_0->y;
	}
	else
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
	}

	vertex[1].x = vertex[0].x;
	vertex[1].y = vertex[0].y + h;

	vertex[2].x = vertex[0].x + w;
	vertex[2].y = vertex[0].y + h;

	vertex[3].x = vertex[0].x + w;
	vertex[3].y = vertex[0].y;

#else
	vertex[0].x = p0[0];
	vertex[0].y = p0[1];

	vertex[1].x = vertex[0].x;
	vertex[1].y = vertex[0].y + h;

	vertex[2].x = vertex[0].x + w;
	vertex[2].y = vertex[0].y + h;

	vertex[3].x = vertex[0].x + w;
	vertex[3].y = vertex[0].y;
#endif
}

void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);
	assert(uv3);

#if defined(PGXP) && 0
	/*
	Locate polygon in ztable
	*/

	PGXPPolygon* z0 = NULL;
	PGXPPolygon* z1 = NULL;
	PGXPPolygon* z2 = NULL;
	PGXPPolygon* z3 = NULL;

	//Can speed this up by storing last index found and using as start iter
	for (int i = pgxp_polgon_table_index; i > -1; i--)
	{
		if (uv0 != NULL)
		{
			if (((unsigned int*)uv0)[0] == pgxp_polygons[i].originalSXY)
			{
				z0 = &pgxp_polygons[i];
				//z0->bUsed = TRUE;
			}
		}

		if (uv1 != NULL)
		{
			if (((unsigned int*)uv1)[0] == pgxp_polygons[i].originalSXY)
			{
				z1 = &pgxp_polygons[i];
				//z1->bUsed = TRUE;
			}
		}

		if (uv2 != NULL)
		{
			if (((unsigned int*)uv2)[0] == pgxp_polygons[i].originalSXY)
			{
				z2 = &pgxp_polygons[i];
				//z2->bUsed = TRUE;
			}
		}

		if (uv3 != NULL)
		{
			if (((unsigned int*)uv3)[0] == pgxp_polygons[i].originalSXY)
			{
				z3 = &pgxp_polygons[i];
				//z3->bUsed = TRUE;
			}
		}

		if ((z0 != NULL || uv0 == NULL) && (z1 != NULL || uv1 == NULL) && (z2 != NULL || uv2 == NULL) && (z3 != NULL || uv3 == NULL))
			break;
	}

	//Copy over uvs
	if (uv0 != NULL)
	{
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];
	}

	if (uv1 != NULL)
	{
		vertex[1].x = p1[0];
		vertex[1].y = p1[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].x = p0[0];
			vertex[1].y = p0[1] + h;
		}
	}

	if (uv2 != NULL)
	{
		vertex[2].x = p2[0];
		vertex[2].y = p2[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].x = p0[0] + w;
			vertex[2].y = p0[1] + h;
		}
	}

	if (uv3 != NULL)
	{
		vertex[3].x = p3[0];
		vertex[3].y = p3[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].x = p0[0] + w;
			vertex[3].y = p0[1];
		}
	}
#else
	const unsigned char bright = 2;

	vertex[0].u      = uv0[0];
	vertex[0].v      = uv0[1];

	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv1[0];
	vertex[1].v      = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv2[0];
	vertex[2].v      = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;

	vertex[3].u      = uv3[0];
	vertex[3].v      = uv3[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = page;
	vertex[3].clut   = clut;
#endif
}

void Emulator_GenerateTexcoordArrayTriangle(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);

#if defined(PGXP) && 0
	#error COPY IMPLEMENTATION FROM Emulator_GenerateTexcoordArrayQuad
#else
	const unsigned char bright = 2;

	vertex[0].u      = uv0[0];
	vertex[0].v      = uv0[1];

	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv1[0];
	vertex[1].v      = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv2[0];
	vertex[2].v      = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;
#endif
}

void Emulator_GenerateTexcoordArrayRect(struct Vertex* vertex, unsigned char* uv, short page, short clut, short w, short h)
{
	assert(uv);
	//assert(int(uv[0]) + w <= 255);
	//assert(int(uv[1]) + h <= 255);
	// TODO
	if ((int)uv[0] + w > 255) w = 255 - uv[0];
	if ((int)uv[1] + h > 255) h = 255 - uv[1];

	const unsigned char bright = 2;
	const unsigned char dither = 0;

	vertex[0].u      = uv[0];
	vertex[0].v      = uv[1];

	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv[0];
	vertex[1].v      = uv[1] + h;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv[0] + w;
	vertex[2].v      = uv[1] + h;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;

	vertex[3].u      = uv[0] + w;
	vertex[3].v      = uv[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = page;
	vertex[3].clut   = clut;
}

void Emulator_GenerateTexcoordArrayLineZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

	vertex[3].u      = 0;
	vertex[3].v      = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = 0;
	vertex[3].clut   = 0;
}

void Emulator_GenerateTexcoordArrayTriangleZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;
}

void Emulator_GenerateTexcoordArrayQuadZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

	vertex[3].u      = 0;
	vertex[3].v      = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = 0;
	vertex[3].clut   = 0;
}

void Emulator_GenerateColourArrayLine(struct Vertex* vertex, unsigned char* col0, unsigned char* col1)
{
	assert(col0);
	assert(col1);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col1[0];
	vertex[2].g = col1[1];
	vertex[2].b = col1[2];
	vertex[2].a = 255;

	vertex[3].r = col0[0];
	vertex[3].g = col0[1];
	vertex[3].b = col0[2];
	vertex[3].a = 255;
}

void Emulator_GenerateColourArrayTriangle(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2)
{
	assert(col0);
	assert(col1);
	assert(col2);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col2[0];
	vertex[2].g = col2[1];
	vertex[2].b = col2[2];
	vertex[2].a = 255;
}

void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, int bMaxCol)
{
	assert(col0);
	assert(col1);
	assert(col2);
	assert(col3);

	if (bMaxCol)
	{
		vertex[0].r = 128;
		vertex[0].g = 128;
		vertex[0].b = 128;
		vertex[0].a = 128;
	}
	else
	{
		vertex[0].r = col0[0];
		vertex[0].g = col0[1];
		vertex[0].b = col0[2];
		vertex[0].a = 255;
	}

	if (bMaxCol)
	{
		vertex[1].r = 128;
		vertex[1].g = 128;
		vertex[1].b = 128;
		vertex[1].a = 255;
	}
	else
	{
		vertex[1].r = col1[0];
		vertex[1].g = col1[1];
		vertex[1].b = col1[2];
		vertex[1].a = 255;
	}

	if (bMaxCol)
	{
		vertex[2].r = 128;
		vertex[2].g = 128;
		vertex[2].b = 128;
		vertex[2].a = 255;
	}
	else
	{
		vertex[2].r = col2[0];
		vertex[2].g = col2[1];
		vertex[2].b = col2[2];
		vertex[2].a = 255;
	}

	if (bMaxCol)
	{
		vertex[3].r = 128;
		vertex[3].g = 128;
		vertex[3].b = 128;
		vertex[3].a = 255;
	}
	else
	{
		vertex[3].r = col3[0];
		vertex[3].g = col3[1];
		vertex[3].b = col3[2];
		vertex[3].a = 255;
	}
}

void Emulator_CopyVRAM(unsigned short *src, int x, int y, int w, int h, int dst_x, int dst_y)
{
	vram_need_update = TRUE;

    int stride = w;

    if (!src) {
        src    = vram;
        stride = VRAM_WIDTH;
    }

    src += x + y * stride;

    unsigned short *dst = vram + dst_x + dst_y * VRAM_WIDTH;

    for (int i = 0; i < h; i++) {
        memcpy(dst, src, w * sizeof(short));
        dst += VRAM_WIDTH;
        src += stride;
    }
}

void Emulator_ReadVRAM(unsigned short *dst, int x, int y, int dst_w, int dst_h)
{
	unsigned short *src = vram + x + VRAM_WIDTH * y;

	for (int i = 0; i < dst_h; i++) {
		memcpy(dst, src, dst_w * sizeof(short));
		dst += dst_w;
		src += VRAM_WIDTH;
	}
}

void Emulator_DoDebugKeys(int nKey, int down); // forward decl

#if defined(TOUCH_UI)

unsigned short resultTouchKeysPressed = 0;

struct Quad
{
	DVECTOR p[4];
};

int Emulator_IsPointInSquare(int x, int y, struct Quad* q)
{
	short maxX = q->p[0].vx;
	short minX = q->p[0].vx;
	short maxY = q->p[0].vy;
	short minY = q->p[0].vy;

	for (int i = 0; i < 4; i++)
	{
		if (maxX < q->p[i].vx)
		{
			maxX = q->p[i].vx;
		}

		if (q->p[i].vx < minX)
		{
			minX = q->p[i].vx;
		}

		if (maxY < q->p[i].vy)
		{
			maxY = q->p[i].vy;
		}

		if (q->p[i].vy < minY)
		{
			minY = q->p[i].vy;
		}
	}

	if (x < minX || x > maxX || y < minY || y > maxY) 
	{
		return FALSE;
	}

	return TRUE;
}

void Emulator_HandleTouchEvent(int x, int y)
{
    if (g_DisableTouchUI)
    {
        return;
    }

	int rx = (x * 512) / windowWidth;
	int ry  = (y * 240) / windowHeight;

	int dist = 16;
	int cx = 32;
	int cy = 172;

	unsigned short mapper[4] = {
		0x8,
		0x1,
		0x2,
		0x4,
	};

	unsigned short mapperShoulder[4] = {
		0x1,
		0x4,
		0x2,
		0x8,
	};
	
	//printf("X: %d, Y: %d, RX: %d, RY: %d\n", x, y, rx, ry);

	for (int i = 0; i < 4; i++)
	{
		int dx = (i % 2) ? 0 : 1;
		int dy = dx ? 0 : 1;
		int ndist = (i >= 2) ? dist : -dist;

		int mx = dx ? ndist * 2 : 0;
		int my = dy ? ndist * 2 : 0;

		struct Quad q;

		q.p[0].vx = cx + mx;
		q.p[0].vy = cy + my;

		q.p[1].vx = cx + mx + 32;
		q.p[1].vy = cy + my;

		q.p[2].vx = cx + mx;
		q.p[2].vy = cy + my + 32;

		q.p[3].vx = cx + mx + 32;
		q.p[3].vy = cy + my + 32;

		if (Emulator_IsPointInSquare(rx, ry, &q))
		{
			resultTouchKeysPressed |= mapper[i] << 4;
		}
	}

	cx = 512 - 64;
	cy = 172;
	
	for (int i = 0; i < 4; i++)
	{
		int dx = (i % 2) ? 0 : 1;
		int dy = dx ? 0 : 1;
		int ndist = (i >= 2) ? dist : -dist;

		int mx = dx ? ndist * 2 : 0;
		int my = dy ? ndist * 2 : 0;

		struct Quad q;

		q.p[0].vx = cx + mx;
		q.p[0].vy = cy + my;

		q.p[1].vx = cx + mx + 32;
		q.p[1].vy = cy + my;

		q.p[2].vx = cx + mx;
		q.p[2].vy = cy + my + 32;

		q.p[3].vx = cx + mx + 32;
		q.p[3].vy = cy + my + 32;

		if (Emulator_IsPointInSquare(rx, ry, &q))
		{
			resultTouchKeysPressed |= mapper[i] << 12;
		}
	}

	cx = 512 / 2;
	cy = 240 - 32;
	dist = 32;

	for (int i = 0; i < 2; i++)
	{
		int dx = (i % 2) ? 0 : 1;
		int ndist = (i != 0) ? dist : -dist;
		int mx = dx ? ndist * 2 : 0;

		struct Quad q;

		q.p[0].vx = cx + mx;
		q.p[0].vy = cy;

		q.p[1].vx = cx + mx + 32;
		q.p[1].vy = cy;

		q.p[2].vx = cx + mx;
		q.p[2].vy = cy + 16;

		q.p[3].vx = cx + mx + 32;
		q.p[3].vy = cy + 16;

		if (Emulator_IsPointInSquare(rx, ry, &q))
		{
			resultTouchKeysPressed |= mapper[!i];
		}
	}

	cx = 32;
	cy = 32;

	for (int i = 0; i < 2; i++)
	{
		int dy = (i % 2) ? 0 : 1;

		int my = dy ? dist : 0;

		struct Quad q;

		q.p[0].vx = cx;
		q.p[0].vy = cy + my;

		q.p[1].vx = cx + 32;
		q.p[1].vy = cy + my;

		q.p[2].vx = cx;
		q.p[2].vy = cy + my + 16;

		q.p[3].vx = cx + 32;
		q.p[3].vy = cy + my + 16;

		if (Emulator_IsPointInSquare(rx, ry, &q))
		{
			resultTouchKeysPressed |= mapperShoulder[i] << 8;
		}
	}

	cx = 512 - 64;
	cy = 32;

	for (int i = 0; i < 2; i++)
	{
		int dy = (i % 2) ? 0 : 1;

		int my = dy ? dist : 0;

		struct Quad q;

		q.p[0].vx = cx;
		q.p[0].vy = cy + my;

		q.p[1].vx = cx + 32;
		q.p[1].vy = cy + my;

		q.p[2].vx = cx;
		q.p[2].vy = cy + my + 16;

		q.p[3].vx = cx + 32;
		q.p[3].vy = cy + my + 16;

		if (Emulator_IsPointInSquare(rx, ry, &q))
		{
			resultTouchKeysPressed |= mapperShoulder[i + 2] << 8;
		}
	}
}
#endif

#if defined(__EMSCRIPTEN__)
EM_JS(int, Emulator_GetCanvasWidth, (), { return canvas.width; });
EM_JS(int, Emulator_GetCanvasHeight, (), { return canvas.height; });
int nextCanvasUpdate = 0;
int currentCanvasTick = 0;
#endif

void Emulator_DoPollEvent()
{
#if defined(__EMSCRIPTEN__)
	currentCanvasTick = SDL_GetTicks();

	nextCanvasUpdate = currentCanvasTick + 1000;

	if (currentCanvasTick >= nextCanvasUpdate)
	{
		windowWidth = Emulator_GetCanvasWidth();
		windowHeight = Emulator_GetCanvasHeight();

		nextCanvasUpdate = currentCanvasTick + 1000;
	}
#endif

#if defined(SDL2)
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
#if defined(TOUCH_UI)
			case SDL_MULTIGESTURE:
			{
				g_numTouchFingers = event.mgesture.numFingers > MAX_NUM_FINGER_TOUCHES ? MAX_NUM_FINGER_TOUCHES : event.mgesture.numFingers;

				break;
			}
			case SDL_MOUSEMOTION:
			{
				if (g_touchHeld)
				{
					g_numTouchFingers = 1;

					g_touchAxis[0][0] = (int)event.button.x;
					g_touchAxis[0][1] = (int)event.button.y;
				}
				break;
			}
			case SDL_FINGERMOTION:
			{
				if (g_numTouchFingers > 0)
				{
					if (g_touchHeld)
					{
						for (int i = 0; i < g_numTouchFingers; i++)
						{
							SDL_Finger* f = SDL_GetTouchFinger(event.mgesture.touchId, i);

							if (f != NULL)
							{
								g_touchAxis[i][0] = (int)(f->x * (float)windowWidth);
								g_touchAxis[i][1] = (int)(f->y * (float)windowHeight);
							}
						}
					}
				}
				else
				{
					g_touchAxis[0][0] = (int)(event.tfinger.x * (float)windowWidth);
					g_touchAxis[0][1] = (int)(event.tfinger.y * (float)windowHeight);
				}

				break;
			}
			case SDL_FINGERDOWN:
			{
				if (g_numTouchFingers > 0)
				{
					for (int i = 0; i < g_numTouchFingers; i++)
					{
						SDL_Finger* f = SDL_GetTouchFinger(event.mgesture.touchId, i);

						if (f != NULL)
						{
							g_touchHeld = TRUE;

							g_touchAxis[i][0] = (int)(f->x * (float)windowWidth);
							g_touchAxis[i][1] = (int)(f->y * (float)windowHeight);
						}
					}
				}
				else
				{
					g_numTouchFingers = 1;

					g_touchHeld = TRUE;

					g_touchAxis[0][0] = (int)(event.tfinger.x * (float)windowWidth);
					g_touchAxis[0][1] = (int)(event.tfinger.y * (float)windowHeight);
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				g_touchHeld = TRUE;

				g_numTouchFingers = 1;

				g_touchAxis[0][0] = (int)event.button.x;
				g_touchAxis[0][1] = (int)event.button.y;

				break;
			}
			case SDL_FINGERUP:
			{
				for (int i = 0; i < g_numTouchFingers; i++)
				{
					SDL_Finger* f = SDL_GetTouchFinger(event.mgesture.touchId, i);

					if (f == NULL)
					{
						g_touchAxis[i][0] = 0;
						g_touchAxis[i][1] = 0;

						g_numTouchFingers--;
					}
				}

				g_touchHeld = g_numTouchFingers > 0 ? TRUE : FALSE;

				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				g_touchHeld = FALSE;

				g_numTouchFingers = 0;
				
				break;
			}
#endif
			case SDL_CONTROLLERDEVICEADDED:
				Emulator_AddController(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				SDL_GameControllerClose(padHandle[event.cdevice.which]);
				break;
			case SDL_QUIT:
				g_closeOnNextFrame = TRUE;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_RESIZED:
					windowWidth = event.window.data1;
					windowHeight = event.window.data2;

					g_resetDeviceOnNextFrame = TRUE;
					break;
				case SDL_WINDOWEVENT_CLOSE:
					g_closeOnNextFrame = TRUE;
					break;
				}
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				int nKey = event.key.keysym.scancode;

				// lshift/right shift
				if (nKey == SDL_SCANCODE_RSHIFT)
					nKey = SDL_SCANCODE_LSHIFT;
				else if (nKey == SDL_SCANCODE_RCTRL)
					nKey = SDL_SCANCODE_LCTRL;
				else if (nKey == SDL_SCANCODE_RALT)
					nKey = SDL_SCANCODE_LALT;
#if defined(_DEBUG)
				Emulator_DoDebugKeys(nKey, (event.type == SDL_KEYUP) ? FALSE : TRUE);
#endif
				break;
			}
		}
	}
#endif
}

int Emulator_BeginScene()
{
	Emulator_DoPollEvent();

	if (begin_scene_flag)
		return FALSE;

	assert(!begin_scene_flag);

#if defined(VULKAN)
	g_lastBoundTexture[0].textureImage = NULL;
	g_lastBoundTexture[1].textureImage = NULL;
#elif defined(D3D12)
	g_lastBoundTexture[0].m_textureResource = NULL;
	g_lastBoundTexture[1].m_textureResource = NULL;
#elif defined(PLATFORM_NX)
	//g_lastBoundTexture[0] = NULL;
	//g_lastBoundTexture[1] = NULL;
#elif defined(GXM)
	//g_lastBoundTexture[0] = NULL;
	//g_lastBoundTexture[1] = NULL;
#else
	g_lastBoundTexture[0] = NULL;
	g_lastBoundTexture[1] = NULL;
#endif

#if defined(OGLES)
	glBindVertexArray(dynamic_vertex_array);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->BeginScene();
	d3ddev->SetVertexDeclaration(vertexDecl);
	d3ddev->SetStreamSource(0, dynamic_vertex_buffer, 0, sizeof(Vertex));
#elif defined(D3D11)
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3dcontext->IASetVertexBuffers(0, 1, &dynamic_vertex_buffer, &stride, &offset);
#elif defined(D3D12)
	dynamic_vertex_buffer_index = 0;
	Emulator_UpdateVRAM();
	Emulator_BeginPass();

	dynamic_vertex_buffer_view.BufferLocation = dynamic_vertex_buffer[frameIndex]->GetGPUVirtualAddress();
	dynamic_vertex_buffer_view.StrideInBytes = sizeof(Vertex);
	dynamic_vertex_buffer_view.SizeInBytes = MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex);

	commandList->IASetVertexBuffers(0, 1, &dynamic_vertex_buffer_view);

#elif defined(VULKAN)
	Emulator_UpdateVRAM();
	Emulator_BeginPass();

	if (g_vertexBufferMemoryBound == FALSE)
	{
		//vkBindBufferMemory(device, dynamic_vertex_buffer, dynamic_vertex_buffer_memory, 0);
		g_vertexBufferMemoryBound = TRUE;
	}

	
#elif defined(PLATFORM_NX)
	Emulator_UpdateVRAM();
	Emulator_BeginPass();
	Emulator_SetVertexBuffer();

#elif defined(GXM)
	Emulator_BeginRenderScene();
#endif

#if !defined(VULKAN) && !defined(D3D12) && !defined(PLATFORM_NX)  && !defined(PLATFORM_NX_ARM) && !defined(D3D12) 
	Emulator_UpdateVRAM();
#endif

	Emulator_SetViewPort(0, 0, Emulator_GetWindowWidth(), Emulator_GetWindowHeight());

	begin_scene_flag = TRUE;

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(TRUE);
	}

	return TRUE;
}

int Emulator_GetWindowWidth()
{
	return g_overrideWidth != -1 ? g_overrideWidth : windowWidth;
}

int Emulator_GetWindowHeight()
{
	return g_overrideHeight != -1 ? g_overrideHeight : windowHeight;
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
int Emulator_DoesFileExist(const char* fileName)
{
	FILE* f = fopen(fileName, "rb");
	
	if (f != NULL)
	{
		fclose(f);
		return 1;
	}

	return 0;
}

char* screenshotExtensions[] = { "TGA", "BMP" };

int Emulator_GetScreenshotNumber(int mode)
{
	int fileNumber = 0;
	char buff[64];
	do
	{
		sprintf(buff, "SCREENSHOT_%d.%s", fileNumber++, screenshotExtensions[mode]);

	} while (Emulator_DoesFileExist(buff) == 1);

	return fileNumber - 1;
}

void Emulator_TakeScreenshot(int mode)
{
#if defined(SDL2)
	int width = Emulator_GetWindowWidth();
	int height = Emulator_GetWindowHeight();

	unsigned char* pixels = new unsigned char[width * height * sizeof(unsigned int)];
	
#if defined(_WINDOWS) && (defined(D3D11) || defined(OGL)) && !defined(UWP)
	if (g_overrideHWND != NULL)
	{
		HDC hdcScreen;
		HDC hdcWindow;
		HDC hdcMemDC = NULL;
		HBITMAP hbmScreen = NULL;
		BITMAP bmpScreen;
		DWORD dwBytesWritten = 0;
		DWORD dwSizeofDIB = 0;
		HANDLE hFile = NULL;
		char* lpbitmap = NULL;
		HANDLE hDIB = NULL;
		DWORD dwBmpSize = 0;

		hdcScreen = GetDC(g_overrideHWND);
		hdcWindow = GetDC(g_overrideHWND);

		hdcMemDC = CreateCompatibleDC(hdcWindow);

		if (!hdcMemDC)
		{
			return;
		}

		RECT rcClient;
		GetClientRect(g_overrideHWND, &rcClient);

		SetStretchBltMode(hdcWindow, HALFTONE);

		if (!StretchBlt(hdcWindow,
			0, 0,
			rcClient.right, rcClient.bottom,
			hdcScreen,
			0, 0,
			rcClient.right,
			rcClient.bottom,
			SRCCOPY | CAPTUREBLT))
		{
			return;
		}

		hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

		if (!hbmScreen)
		{
			return;
		}

		SelectObject(hdcMemDC, hbmScreen);

		if (!BitBlt(hdcMemDC,
			0, 0,
			rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
			hdcWindow,
			0, 0,
			SRCCOPY | CAPTUREBLT))
		{
			return;
		}

		GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

		BITMAPFILEHEADER   bmfHeader;
		BITMAPINFOHEADER   bi;

		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bmpScreen.bmWidth;
		bi.biHeight = bmpScreen.bmHeight;
		bi.biPlanes = 1;
		bi.biBitCount = 32;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

		hDIB = GlobalAlloc(GHND, dwBmpSize);
		lpbitmap = (char*)GlobalLock(hDIB);

		GetDIBits(hdcWindow, hbmScreen, 0, (UINT)bmpScreen.bmHeight, lpbitmap, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

		char buff[64];
		sprintf(buff, "SCREENSHOT_%d.%s", Emulator_GetScreenshotNumber(SCREENSHOT_MODE_BMP), screenshotExtensions[SCREENSHOT_MODE_BMP]);

		hFile = CreateFile(buff, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

		bmfHeader.bfSize = dwSizeofDIB;

		bmfHeader.bfType = 0x4D42;

		WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
		WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
		WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

		GlobalUnlock(hDIB);
		GlobalFree(hDIB);

		CloseHandle(hFile);

		DeleteObject(hbmScreen);
		DeleteObject(hdcMemDC);
		ReleaseDC(NULL, hdcScreen);
		ReleaseDC(g_overrideHWND, hdcWindow);

		return;
	}
#endif

#if defined(OGL) || defined(OGLES)
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
#endif

	if (mode == SCREENSHOT_MODE_TGA)
	{
		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 8 * 4, width * 4, 0, 0, 0, 0);

		char buff[64];
		sprintf(buff, "SCREENSHOT_%d.%s", Emulator_GetScreenshotNumber(mode), screenshotExtensions[mode]);

		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6];
		header[0] = (width % 256);
		header[1] = (width / 256);
		header[2] = (height % 256);
		header[3] = (height / 256);
		header[4] = 32;
		header[5] = 0;

		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);

		struct pixel
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned char a;
		};

		pixel* p = (pixel*)surface->pixels;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				unsigned char temp = p->b;
				p->b = p->r;
				p->r = temp;
				p++;
			}
		}

		fwrite(surface->pixels, width * height * sizeof(unsigned int), 1, f);
		fclose(f);

		SDL_FreeSurface(surface);
	}
	else if (mode == SCREENSHOT_MODE_BMP)
	{
		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 8 * 4, width * 4, 0, 0, 0, 0);
		char buff[64];
		sprintf(buff, "SCREENSHOT_%d.%s", Emulator_GetScreenshotNumber(mode), screenshotExtensions[mode]);
		SDL_SaveBMP(surface, buff);
		SDL_FreeSurface(surface);
	}
	
	delete[] pixels;
#endif
}
#endif

void Emulator_CreateMemoryCard(int channel)
{
	char buf[128];

#if defined(__ANDROID__)
	sprintf(&buf[0], "/storage/self/primary/%s/%ld.MCD", GAME_SHORT_NAME, channel);
#elif defined(_XBOX)
	sprintf(&buf[0], "game:/%ld.MCD", channel);
#else
	sprintf(&buf[0], "%ld.MCD", channel);
#endif

	FILE* f = fopen(buf, "wb+");
#define MEMCARD_LENGTH 0x1C000
	unsigned short magic = 0x434D;
	fwrite(&magic, sizeof(unsigned short), 1, f);

	fseek(f, 125, SEEK_CUR);

	unsigned char unk4 = 0xE;
	fwrite(&unk4, sizeof(unsigned char), 1, f);

	for (int i = 0; i < 15; i++)
	{
		unsigned char unk1 = 0xA0;

		fwrite(&unk1, sizeof(unsigned char), 1, f);
		fseek(f, 7, SEEK_CUR);

		unsigned short unk2 = 0xFFFF;
		fwrite(&unk2, sizeof(unsigned short), 1, f);
		fseek(f, 117, SEEK_CUR);

		fwrite(&unk1, sizeof(unsigned char), 1, f);
	}

	for (int i = 0; i < 20; i++)
	{
		unsigned int unk3 = 0xFFFFFFFF;
		fwrite(&unk3, sizeof(unsigned int), 1, f);
		fseek(f, 124, SEEK_CUR);
	}

	for (int i = 0; i < 864; i++)
	{
		unsigned int unk5 = 0xFFFFFFFF;
		fwrite(&unk5, sizeof(unsigned int), 1, f);
	}

	fwrite(&magic, sizeof(unsigned short), 1, f);

	fseek(f, 125, SEEK_CUR);

	unk4 = 0xE;
	fwrite(&unk4, sizeof(unsigned char), 1, f);

	for (int i = 0; i < 30720; i++)
	{
		unsigned int unk6 = 0xFFFFFFFF;
		fwrite(&unk6, sizeof(unsigned int), 1, f);
	}

	fclose(f);
}

void Emulator_DoDebugKeys(int nKey, int down)
{
#if defined(SDL2)

	if (nKey == SDL_SCANCODE_BACKSPACE)
	{
		if(down)
		{
			if (g_swapInterval != 0)
			{
				g_swapInterval = 0;

				g_resetDeviceOnNextFrame = TRUE;
			}
		}
		else
		{
			if (g_swapInterval != SWAP_INTERVAL)
			{
				g_swapInterval = SWAP_INTERVAL;

				g_resetDeviceOnNextFrame = TRUE;
			}
		}
	}

	if (!down)
	{
		switch (nKey)
		{
			case SDL_SCANCODE_1:
				g_wireframeMode ^= 1;
				break;

			case SDL_SCANCODE_2:
				g_texturelessMode ^= 1;
				break;

			case SDL_SCANCODE_3:
				g_emulatorPaused ^= 1;
				break;
			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_DOWN:
				if (g_emulatorPaused)
					g_polygonSelected += (nKey == SDL_SCANCODE_UP) ? 3 : -3;
				break;

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
			case SDL_SCANCODE_4:
				Emulator_TakeScreenshot(SCREENSHOT_MODE_TGA);
				break;
			case SDL_SCANCODE_5:
				Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
				break;
			case SDL_SCANCODE_6:
#if !defined(NO_BOUNTY_LIST_EXPORT)
				Emulator_SaveBountyList();
#endif
				break;
			case SDL_SCANCODE_7:
				extern int32_t disableReverb;
				disableReverb ^= 1;
				break;
			case SDL_SCANCODE_8:
				extern int32_t disableADSR;
				disableADSR ^= 1;
				break;	
			case SDL_SCANCODE_9:
				extern int32_t disableChannelVol;
				disableChannelVol ^= 1;
				break;
#endif
		}
	}
#endif
}

unsigned short kbInputs = 0xFFFF;

#if defined(SDL2)
void Emulator_RumbleGameController(SDL_GameController* pad, unsigned char* padRumbleData)
{
#define PSX_MIN 0
#define PSX_MAX 255

#define SDL_MIN 0
#define SDL_MAX 65535

#define TRANSLATE(x) ((SDL_MAX - SDL_MIN) * (x - PSX_MIN) / (PSX_MAX - PSX_MIN)) + SDL_MIN

	if (padRumbleData != NULL)
	{
		SDL_GameControllerRumble(pad, TRANSLATE(padRumbleData[1]), TRANSLATE(padRumbleData[1]), 100);

		if (SDL_JoystickHasRumbleTriggers(SDL_GameControllerGetJoystick(pad)))
		{
			SDL_GameControllerRumbleTriggers(pad, TRANSLATE(padRumbleData[1]), TRANSLATE(padRumbleData[1]), 100);
		}
	}
}

void Emulator_TranslateControllerType(void* padData, SDL_GameController* padHandle)
{
	struct PadData
	{
		unsigned char status;
		unsigned char size : 4;
		unsigned char type : 4;
	};

	PadData* pd = (PadData*)padData;

	bool hasLeftAnalog = SDL_GameControllerHasAxis(padHandle, SDL_CONTROLLER_AXIS_LEFTX) & SDL_GameControllerHasAxis(padHandle, SDL_CONTROLLER_AXIS_LEFTY);
	bool hasRightAnalog = SDL_GameControllerHasAxis(padHandle, SDL_CONTROLLER_AXIS_RIGHTX) & SDL_GameControllerHasAxis(padHandle, SDL_CONTROLLER_AXIS_RIGHTY);

	if (hasLeftAnalog && hasRightAnalog)
	{
		//Analog controller
		pd->type = 7;
		pd->size = 3;
	}
	else
	{
		//Non-analog controller.
		pd->type = 4;
		pd->size = 1;
	}

	pd->status = 0;
}
#endif

void Emulator_UpdateInput(int poll)
{
	// also poll events here
	if (poll)
	{
		Emulator_DoPollEvent();
	}

#if defined(SDL2)

	if (padAllowCommunication)
	{
		for (int i = 0; i < g_numTouchFingers; i++)
		{
			Emulator_HandleTouchEvent(g_touchAxis[i][0], g_touchAxis[i][1]);
		}

		kbInputs = UpdateKeyboardInput();
	}
	else
	{
		kbInputs = 0xFFFFu;
	}

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL && padAllowCommunication)
			{
				unsigned short controllerInputs = UpdateGameControllerInput(padHandle[i]);

				Emulator_TranslateControllerType(padData[i], padHandle[i]);
				((unsigned short*)padData[i])[1] = kbInputs & controllerInputs;

				unsigned short analogData[2];
				UpdateGameControllerAnalogInput(padHandle[i], &analogData[0], &analogData[1]);

				((unsigned short*)padData[i])[2] = analogData[0];
				((unsigned short*)padData[i])[3] = analogData[1];

				if (SDL_GameControllerHasRumble(padHandle[i]))
				{
					Emulator_RumbleGameController(padHandle[i], padRumbleData[i]);
				}
			}
			else
			{
				unsigned short controllerInputs = 0xFFFFu;
				((unsigned short*)padData[i])[1] = kbInputs & controllerInputs;
			}
		}
	}
	else
	{
		//Update keyboard
		if (padData[0] != NULL)
		{
			Emulator_TranslateControllerType(padData[0], padHandle[0]);
			((unsigned short*)padData[0])[1] = kbInputs;
			((unsigned short*)padData[0])[2] = 128;//Maybe not required.
			((unsigned short*)padData[0])[3] = 128;
		}
	}
#elif defined(PLATFORM_NX)
	extern void Emulator_UpdateInputNVN();
	Emulator_UpdateInputNVN();

	if (padAllowCommunication && padData[0] != NULL)
	{
		extern unsigned short UpdateTouchInput();
		kbInputs = UpdateTouchInput();

		((unsigned short*)padData[0])[1] = kbInputs;
		((unsigned short*)padData[0])[2] = 128;//Maybe not required.
		((unsigned short*)padData[0])[3] = 128;
	}
	else
	{
		kbInputs = 0xFFFFu;
	}
#endif

#if !defined(__ANDROID__)
    ///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
    //((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif
}

void Emulator_UpdateInputDebug()
{
	// also poll events here
	Emulator_DoPollEvent();

#if defined(SDL2)
	kbInputs = UpdateKeyboardInputDebug();

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				unsigned short controllerInputs = UpdateGameControllerInput(padHandle[i]);

				padData[i][0] = 0;
				padData[i][1] = 0x41;//?
				((unsigned short*)padData[i])[1] = kbInputs & controllerInputs;
			}
		}
	}

#endif

#if defined(__ANDROID__) || defined(__EMSCRIPTEN__)
	///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
	((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif
}

unsigned int Emulator_GetFPS()
{
#if defined(SDL2)
#define FPS_INTERVAL 1.0

	static int64_t lastTime = Emulator_GetTicks();
	static int64_t currentFps = 0;
	static int64_t passedFrames = 0;

	passedFrames++;
	if (lastTime < Emulator_GetTicks() - FPS_INTERVAL * 1000)
	{
		lastTime = Emulator_GetTicks();
		currentFps = passedFrames;
		passedFrames = 0;
	}

	return (unsigned int)currentFps;
#else
	return 0;
#endif
	
}

void Emulator_EndScene()
{
#if defined(VULKAN) || defined(D3D12) || defined(PLATFORM_NX)
	Emulator_EndPass();
#endif

	if (!begin_scene_flag)
		return;

	if (!vbo_was_dirty_flag)
		return;

	assert(begin_scene_flag);

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(FALSE);
	}

#if defined(OGL) || defined(OGLES)
	//glBindVertexArray(0);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->EndScene();
#elif defined(D3D12)

#elif defined(VULKAN)

#endif

	begin_scene_flag = FALSE;
	vbo_was_dirty_flag = FALSE;

#if defined(GXM)
	Emulator_EndRenderScene();
#endif

	Emulator_SwapWindow();

	if (g_resetDeviceOnNextFrame == TRUE)
	{
		Emulator_ResetDevice(TRUE);
		g_resetDeviceOnNextFrame = FALSE;
	}

	if (g_closeOnNextFrame == TRUE)
	{
		Emulator_ShutDown();
	}

#if defined(TOUCH_UI)
	Emulator_ResetTouchInput();
#endif
}

void Emulator_ResetTouchInput()
{
	resultTouchKeysPressed = 0;
}

void Emulator_ShutDown()
{
	//Stop counters
#if defined(UWP_SDL2) || defined(SDL2) && !defined(USE_THREADS)
	for (int i = 0; i < 3; i++)
	{
		SDL_RemoveTimer(counters[i].timerId);
		counters[i].timerId = 0;
	}
#else
	eassert(FALSE);//TODO join and leave thread
	//counters[spec].timerId = std::thread(Emulator_CounterWrapper, spec);
#endif

#if defined(SDL2)
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
#endif

	Emulator_DestroyRender();

	SPU_Destroy();

#if defined(SDL2)
	if (g_window != NULL)
	{
		SDL_DestroyWindow(g_window);
	}

	SDL_Quit();
#endif

#if defined(_WINDOWS)
#if defined(MEM_CHECK)
	_CrtDumpMemoryLeaks();
#endif
#endif

#if !defined(SN_TARGET_PSP2) && !defined(EDITOR)
	//Disabled as editor needs to run still.
	exit(EXIT_SUCCESS);
#endif
}

void Emulator_SetPGXPVertexCount(int vertexCount)
{
#if defined(PGXP)
	pgxp_vertex_count = vertexCount;
#endif
}

void Emulator_HintTouchFontUIButton(short tpage, short clut, short* x, short* y, int buttonIndex)
{
	g_useHintedTouchUIFont = TRUE;
	
	struct TouchButtonVRAM* touchButton = &touchButtonsUI[buttonIndex];

	touchButton->tpage = tpage;
	touchButton->clut = clut;

	for (int i = 0; i < 4; i++)
	{
		touchButton->u[i] = x[i];
		touchButton->v[i] = y[i];
		touchButton->w = 11;
		touchButton->h = 11;
	}
}