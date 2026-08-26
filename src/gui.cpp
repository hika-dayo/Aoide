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
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>
#include <optional>
#include <random>
#include <algorithm>
#include <iostream>


MenuItem::MenuItem(std::string Text,EVENT Event, std::optional<Music> M)
{
	Artist = "";
	Album = "";
	Title = "";
	Path = "";
	ArtworkPath = "";
	if(M.has_value())
	{
		Artist = M.value().GetArtist();
		Album = M.value().GetAlbum();
		Title = M.value().GetTitle();
		Path = M.value().GetPath();
		ArtworkPath = M.value().GetArtworkPath();
	}
	this->Text = Text;
	this->Event = Event;
	return;
}

std::string MenuItem::GetArtist(void)
{
	return Artist;
}
std::string MenuItem::GetAlbum(void)
{
	return Album;
}
std::string MenuItem::GetTitle(void)
{
	return Title;
}
std::string MenuItem::GetPath(void)
{
	return Path;
}
std::string MenuItem::GetText(void) const
{
	return Text;
}
std::string MenuItem::GetArtworkPath(void)
{
	return ArtworkPath;
}
EVENT MenuItem::GetEvent(void)
{
	return Event;
}
MenuItem::MenuItem(const MenuItem &Copy)
{
	Text = Copy.Text;
	Artist = Copy.Artist;
	Album = Copy.Album;
	Title = Copy.Title;
	Path = Copy.Path;
	Event = Copy.Event;
	ArtworkPath = Copy.ArtworkPath;
	return;
}

int UIRender::DrawMenu(int ChoosingLine, int Scroll, const std::vector<MenuItem>& Object)
{
	Config C;
		for(int i = 0; i < C.GetWindowHeight() / C.GetFontSize() && Scroll + i < Object.size(); i++)
		{
			if(i == ChoosingLine)
			{
				DrawRect(0, C.GetFontSize() * i , C.GetWindowWidth(), C.GetFontSize(), FontColor);
				DrawText(Font, Object[Scroll + i].GetText().c_str(), 0x00ffffff - FontColor, 0, i * C.GetFontSize());
	
			}
			else
			{
				DrawText(Font, Object[Scroll + i].GetText().c_str(), FontColor, 0, i * C.GetFontSize());			
			}
		}

		float BarY = Scroll / (float)Object.size() * (float)C.GetWindowHeight();
		float BarHeight;
		//if(Object.size() < C.GetWindowHeight() / C.GetFontSize() / 3 * 2)
		if(Object.size() == 0)		
		{	
			BarHeight = C.GetWindowHeight();
		}
		else
		{
			BarHeight =  C.GetWindowHeight() * (C.GetWindowHeight() / C.GetFontSize()) / ((float)Object.size());
			if(BarHeight > C.GetWindowHeight())
			{
				BarHeight = C.GetWindowHeight();
			}
		}		
		DrawRect(C.GetWindowWidth() - C.GetFontSize() / 2, BarY, C.GetFontSize(), BarHeight, 0x00999999);	
	return 0;
}
UIRender::UIRender(void)
{
	Config C;
	FontColor =  0x00ffffff;
	Font = InitFont(C.GetFontSize(), C.GetFontPath());
	if(Font == 0)
	{
		ReportError("フォントの初期化に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
		exit(1);
	}
}
