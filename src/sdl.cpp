/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/gui.hpp"
#include "../includes/utility.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

static SDL_Event E;
static SDL_Window *Window = NULL;
static SDL_Renderer *Renderer = NULL;
static SDL_Surface *Surface = NULL;
static bool Initialized = false;
bool isSDLInitialized(void)
{
	return Initialized;
}
int GUIInit(void)
{
	Config C;
	if(Initialized == true)
	{
		return 1;
	}
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		ReportError("SDLを初期化できませんでした。", CRITICAL_ERROR, __FILE__, __LINE__);
		return 1;
	}	
	Window = SDL_CreateWindow("Aoide", C.GetWindowWidth(), C.GetWindowHeight(), 0);
	if(Window == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		ReportError("SDLのウィンドウを作成できませんでした。", CRITICAL_ERROR, __FILE__, __LINE__);
		return 1;
	}
	Surface = SDL_GetWindowSurface(Window);
	if(!Surface)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		ReportError("ウィンドウのサーフェスを作成できませんでした。", CRITICAL_ERROR, __FILE__, __LINE__);
		return 1;
	}
	SDL_SetWindowSurfaceVSync(Window, 2);
	Initialized = true;
//	ProcessMessage();
	return 0;
}
SDL_Surface* GetGUISurface(void)
{
	return Surface;
}
bool ProcessMessage(void)
{
	if(!Initialized)
	{
		return 0;
	}
	bool Quit = false;
	SDL_UpdateWindowSurface(Window);
	while(SDL_PollEvent(&E))
	{
		if(E.type == SDL_EVENT_QUIT)
		{
			Quit = true;

		}
	}

	return Quit;
}



int GUIRelease(void)
{
	if(isSDLInitialized())
	{
		SDL_DestroyRenderer(Renderer);
		SDL_DestroySurface(Surface);
		SDL_DestroyWindow(Window);
		SDL_Quit();
		Initialized = false;
		return 0;
	}
	return 1;
}

SDL_Color ToSDLPixel(Color Arg)
{
	SDL_Color Color;
	Color.a = 0;
	Color.r = 0xff;
	Color.g = 0xff;
	Color.b = 0xff;
	
	Color.a = 0;
	Color.r = (Arg / 0x00010000) % 0x100;
	Color.g = (Arg / 0x00000100) % 0x100;
	Color.b = Arg % 0x100;
	return Color;
}
bool GetKey(KEY K)
{
	auto Keys = SDL_GetKeyboardState(NULL);
	if(K == UP)
	{
		return Keys[SDL_SCANCODE_UP];
	}
	if(K == DOWN)
	{
		return Keys[SDL_SCANCODE_DOWN];
	}
	if(K == RIGHT)
	{
		return Keys[SDL_SCANCODE_RIGHT];
	}
	if(K == LEFT)
	{
		return Keys[SDL_SCANCODE_LEFT];
	}
	if(K == ENTER)
	{
		return Keys[SDL_SCANCODE_RETURN];
	}
	if(K == ESC)
	{
		return Keys[SDL_SCANCODE_ESCAPE];
	}
	return false;
}
int GetKeyCount(void)
{
	KEY K;
	auto Keys = SDL_GetKeyboardState(NULL);
	int KeyCount = 0;
	if(Keys[SDL_SCANCODE_UP])
	{
		KeyCount++;
	}
	if(Keys[SDL_SCANCODE_DOWN])
	{
		KeyCount++;
	}
	if(Keys[SDL_SCANCODE_RIGHT])
	{
		KeyCount++;
	}
	if(Keys[SDL_SCANCODE_LEFT])
	{
		KeyCount++;
	}
	if(Keys[SDL_SCANCODE_RETURN])
	{
		KeyCount++;
	}
	if(Keys[SDL_SCANCODE_ESCAPE])
	{
		KeyCount++;
	}
	return KeyCount;
}
