/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../include/utity.hpp"
#include "../include/gui.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
SDL_Surface* Image;
TTF_Font* InitFont(int Size, std::string Path)
{	
	TTF_Font* Font;
	TTF_Init();
	if(isFileExists(Path.c_str()))
	{
		Font = TTF_OpenFont(Path.c_str(),Size);
		return Font;	
	}
	else
	{
		ReportError("フォントファイルが存在していません!", CRITICAL_ERROR, __FILE__, __LINE__);
		std::cerr << Path << std::endl;
	}
	return 0;
}
int DrawText(TTF_Font* Font, const char* Str, Color FontColor, int X, int Y)
{
	SDL_Rect Rect, Scr_Rect;
	SDL_Color SDLColor = ToSDLPixel(FontColor);
	Image = TTF_RenderText_Shaded(Font, Str, strlen(Str), SDLColor, SDLColor);
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = Image->w;
	Rect.h = Image->h;
	Scr_Rect.x = X;
	Scr_Rect.y = Y;	
	SDL_BlitSurface(Image, &Rect, GetGUISurface(), &Scr_Rect);
	
	return 0;
}
int QuitFont(TTF_Font* Font)
{
	TTF_CloseFont(Font);
	TTF_Quit();
	return 0;
}
bool isFileExists(const char* Path)
{	
	struct stat Buffer;
	int Exist = stat(Path, &Buffer);
	if(Exist == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
