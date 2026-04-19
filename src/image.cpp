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
