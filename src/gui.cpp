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
	DrawLines(Texts, ChoosingLine, Font, FontColor, 0, 0);
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

int DrawLines(std::vector<std::string> List, int Index, TTF_Font* Font, Color TextColor, int X, int Y, std::string Title)
{
	Config C;
	if(List.size() < Index + 1)
	{
		return -1;
	}
	if(Title != "")
	{
		Index++;
		List.insert(List.begin(), Title);
	}
	for(int i = 0; i < List.size(); i++)
	{
		if(i == Index)
		{
			DrawRect(X, GetFontSize(Font) * i + Y, C.GetWindowWidth(), GetFontSize(Font) , TextColor);
			DrawText(Font, List[i].c_str(), ~TextColor, 0, GetFontSize(Font) * i);
		}
		else
		{
			DrawText(Font, List[i].c_str(), TextColor, 0, GetFontSize(Font) * i);
		}
	}
	return 0;	
}

int DrawImage(std::string Path, int X, int Y, bool Centered)
{
	if(!FileExists(Path.c_str()))
	{
		return 1;
	}
	SDL_Surface* Image = IMG_Load(Path.c_str());
	SDL_Rect Rect, Scr_Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = Image->w;
	Rect.h = Image->h;
	if(Centered)
	{
		Scr_Rect.x = X - Image->w / 2;
		Scr_Rect.y = Y - Image->h / 2;
	}
	else
	{
		Scr_Rect.x = X;
		Scr_Rect.y = Y;	
	}
	SDL_BlitSurface(Image, &Rect, GetGUISurface(), &Scr_Rect);
	SDL_DestroySurface(Image);
	return 0;
}


/*int DrawUI(std::vector<Music> Musics, int ChoiceLine, TTF_Font* Font, Color TextColor, METADATA Meta, std::string Header)
{
	std::vector<std::string> Tmp;
	if(Header != "")
	{
		Tmp.push_back(Header);
	}
	switch(Meta)
	{
		case ARTIST:
		for(int i = 0; i < Musics.size(); i++)
		{
			Tmp.push_back(Musics[i].GetArtist());
		}
		break;
		case ALBUM:
		for(int i = 0; i < Musics.size(); i++)
		{
			Tmp.push_back(Musics[i].GetAlbum());
		}
		break;
		case TITLE:
		for(int i = 0; i < Musics.size(); i++)
		{
			Tmp.push_back(Musics[i].GetTitle());
		}
		break;
		default:
		return 1;
	}
	DrawLines(Tmp, ChoiceLine, Font, TextColor, ChoiceLine);
	return 0;
}*/
