/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/error.hpp"
#include "../includes/input.hpp"
#include "../includes/gui.hpp"
#include "../includes/file.hpp"
#include "../includes/player.hpp"
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>

UI::UI(std::vector<Music> &MusicList)
{
	Scroll = 0;
	MList = MusicList;
	TmpKey = false;
	FontColor =  0x00ffffff;
	Font = InitFont(C.GetFontSize(), C.GetFontPath());
	if(Font == 0)
	{
		ReportError("フォントの初期化に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
		exit(1);
	}
		for(int i = 0; i < MList.size(); i++)
		{
			bool tmp = false;
			for(int j = 0; j < ArtworkList.size(); j++)
			{
				if(ArtworkList[j].GetPath() == MList[i].GetArtworkPath())
				{
					tmp = true;
				}
			}
			if(!tmp)
			{
				Image I(MList[i].GetArtworkPath());
				ArtworkList.push_back(I);
			}

		}
	ChoosingLine = 0;
	Texts.push_back("Artists");
	Texts.push_back("Albums");
	Texts.push_back("Songs");
	Texts.push_back("Options");
	Texts.push_back("Exit");
	return;
}

int UI::Process(void)
{
	Config C;
	ProcessKey();
	ProcessScroll();
	for(int i = 0; i + Scroll < Texts.size(); i++)
	{
		if(i == ChoosingLine)
		{
			DrawRect(0, C.GetFontSize() * i , C.GetWindowWidth(), C.GetFontSize(), FontColor);
			DrawText(Font, Texts[Scroll + i].c_str(), 0x00ffffff - FontColor, 0, i * C.GetFontSize());
		}
		else
		{
			DrawText(Font, Texts[i].c_str(), FontColor, 0, i * C.GetFontSize());			
		}
	}
	return 0;
}
int UI::ProcessScroll(void)
{
	if(Scroll == Texts.size())
	{
		Scroll = Texts.size() - 1;
	}
	if(Scroll == -1)
	{
		Scroll = 0;
	}
	if(ChoosingLine > C.GetWindowHeight() / C.GetFontSize() - 1)
	{
		Scroll++;
		ChoosingLine--;
	}
	if(ChoosingLine == -1)
	{
		Scroll--;
		ChoosingLine++;
	}
	if(0 > ChoosingLine + Scroll)
	{
		Scroll = Texts.size() - C.GetWindowHeight() / C.GetFontSize() / 2;
		if(Scroll < 0)
		{
			Scroll = 0;
		}
		ChoosingLine = Texts.size() - Scroll - 1;
	}
	if(Texts.size() <= ChoosingLine + Scroll)
	{
		Scroll = 0;
		ChoosingLine = 0;
	}
	return 0;
}
int UI::ProcessKey(void)
{
	if(GetKey(ENTER))
	{
//		if(P != nullptr)
//		{
//			delete P;
//		}
//		P = new Player(MList[Scroll + ChoosingLine].GetPath().c_str());
//		P->Play();
	}
	if(GetKey(LEFT))
	{
		ChoosingLine = 0;
	}
	if(GetKey(UP))
	{
		if(TmpKey == false)
			ChoosingLine--;
		TmpKey = true;
	}
	else if(GetKey(DOWN))
	{
		if(TmpKey == false)
			ChoosingLine++;
		TmpKey = true;
	}
	else
	{
		TmpKey = false;
	}
	if(0 > ChoosingLine + Scroll)
	{
		Scroll = MList.size() - C.GetWindowHeight() / C.GetFontSize() / 2;
		ChoosingLine = MList.size() - Scroll - 1;
	}
	if(MList.size() <= ChoosingLine + Scroll)
	{
		Scroll = 0;
		ChoosingLine = 0;
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


Image::Image(std::string ImagePath)
{
	this->Path = "";
	if(!FileExists(ImagePath.c_str()))
	{
		return;
	}
	Path = ImagePath;
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
Image::Image(const Image &Copy)
{
	if(!FileExists(Copy.Path.c_str()))
	{
		Path = "";
		ImgData = nullptr;
		return;
	}
	Path = Copy.Path;
	ImgData = IMG_Load(Path.c_str());
	Height = ImgData->h;
	Width = ImgData->w;
	return;
}
std::string Image::GetPath(void)
{
	return this->Path;
}
int Image::GetWidth(void)
{
	return Width;
}
int Image::GetHeight(void)
{
	return Height;
}
int Image::ChangeImage(std::string ImagePath)
{
	SDL_DestroySurface(ImgData);
	if(!FileExists(ImagePath.c_str()))
	{
		return 1;
	}
	Path = ImagePath;
	ImgData = IMG_Load(Path.c_str());
	Width = ImgData->w;
	Height = ImgData->h;
	return 0;
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
