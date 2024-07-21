#pragma once

#include "ui.h"

#include <SDL.h>
#include <string>

class App
{
public:
	void Init();
	void Run();
	void Main();
	void Close();
#ifdef _DEBUG
	void RunImGuiExample();
#endif

private:
	bool InitSDL();
	void CloseSDL();
	void InitImGui();
	void CloseImGui();
	void InitFonts();

private:
	UI ui;
	const std::string m_version = "v0.2";
	std::string m_glslVer;
	SDL_GLContext m_glContext;
	SDL_Window* m_window;
};