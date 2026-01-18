/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "header/gui.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include "header/utity.hpp"

static SDL_Event E;
static SDL_Window *Window;
static SDL_Renderer *Renderer;
bool Initilized = false;
int GUIInit(void)
{
	if(Initilized == true)
	{
		return 1;
	}
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		ReportError("SDLを初期化できませんでした。", CRITICAL_ERROR, __FILE__, __LINE__);
		return 1;
	}
	
	Window = SDL_CreateWindow("Aoide", WINDOW_RES_X, WINDOW_RES_Y, 0);
	if(Window == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		ReportError("SDLのウィンドウを作成できませんでした。", CRITICAL_ERROR, __FILE__, __LINE__);
		return 1;
	}
	Renderer = SDL_CreateRenderer(Window, NULL);
	if(!Renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		ReportError("SDLのレンダラーを作成できませんでした。", CRITICAL_ERROR, __FILE__, __LINE__);
		return 1;
	}
	Initilized = true;
	ProcessMessage();
	return 0;
}
SDL_Renderer* GetGUIRenderer(void)
{
	return Renderer;
}
bool ProcessMessage(void)
{
	bool Quit = false;
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
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	Initilized = false;
	return 0;
}
