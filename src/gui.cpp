/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/utility.hpp"
#include "../includes/gui.hpp"
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <vector>

UI::UI(std::vector<Music> &Music)
{
	M = Music;
	Config C;
	FontColor =  0x00ffffff;
	Font = InitFont(C.GetFontSize(), C.GetFontPath());
	if(Font == 0)
	{
		ReportError("フォントの初期化に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
		exit(1);
	}
	ChoosingLine = 0;
	Texts.push_back("Artists");
	Texts.push_back("Albums");
	Texts.push_back("Songs");
	Texts.push_back("Options");
	Texts.push_back("Exit");
}
int UI::Process(void)
{	
	for(int i = 0; i < Texts.size(); i++)
	{
		DrawText(Font, Texts[i].c_str(), FontColor, 0, i * GetFontSize(Font));
	}
	return 0;

}




TTF_Font* InitFont(float Size, std::string Path)
{	
	TTF_Font* Font;
	TTF_Init();
	if(FileExists(Path.c_str()))
	{
		Font = TTF_OpenFont(Path.c_str(),Size);
		return Font;	
	}
	else
	{
		ReportError("フォントファイルが存在していません!", CRITICAL_ERROR, __FILE__, __LINE__, __func__);
		exit(1);
	}
	return 0;
}
float GetFontSize(TTF_Font* Font)
{
	return TTF_GetFontSize(Font);
}
int DrawText(TTF_Font* Font, const char* Str, Color FontColor, int X, int Y)
{
	SDL_Surface* Image;
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
	SDL_DestroySurface(Image);
	return 0;
}
int QuitFont(TTF_Font* Font)
{
	TTF_CloseFont(Font);
	TTF_Quit();
	return 0;
}
int CleanWindow(void)
{
	SDL_ClearSurface(GetGUISurface(), 0,0,0,0);
	return 0;
}

int DrawRect(int X, int Y, int W, int H, Color RectColor)
{
    SDL_Rect Rect = {X, Y, W, H};

    const SDL_PixelFormatDetails* formatDetails =
        SDL_GetPixelFormatDetails(GetGUISurface()->format);
    Uint8 R = (Uint8)((RectColor / 0x10000) % 0x100);
    Uint8 G = (Uint8)((RectColor / 0x100) % 0x100);
    Uint8 B = (Uint8)(RectColor % 0x100);

    Uint32 ColorUint32 = SDL_MapRGB(formatDetails, nullptr, R, G, B);

    SDL_FillSurfaceRect(GetGUISurface(), &Rect, ColorUint32);

    return 0;  // 成功時とか

}


Image::Image(std::string Path)
{
	if(!FileExists(Path.c_str()))
	{
		return;
	}
	ImgData = IMG_Load(Path.c_str());
	Width = ImgData->w;
	Height = ImgData->h;
	return;
}
Image::~Image(void)
{
	SDL_DestroySurface(ImgData);
	return;
}

int Image::GetWidth(void)
{
	return Width;
}
int Image::GetHeight(void)
{
	return Height;
}

int Image::DrawImage(int X, int Y, int Width, int Height)
{
	SDL_Rect Rect, Scr_Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = ImgData->w;
	Rect.h = ImgData->h;
	Scr_Rect.x = X;
	Scr_Rect.y = Y;	
	Scr_Rect.w = Width;
	Scr_Rect.h = Height;	
	if(Width == 0)
	{
		Scr_Rect.w = GetWidth();
	}
	if(Height == 0)
	{
		Scr_Rect.h = GetHeight();	
	}
	SDL_BlitSurfaceScaled(ImgData, &Rect, GetGUISurface(), &Scr_Rect, SDL_SCALEMODE_NEAREST);
	return 0;
}
