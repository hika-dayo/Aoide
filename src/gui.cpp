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
	Mode = MAINMENU;
	Hold = false;
	KeyIntervalCount = 0;
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
			DrawText(Font, Texts[Scroll + i].c_str(), FontColor, 0, i * C.GetFontSize());			
		}
	}
		float BarY = Scroll / (float)Texts.size() * (float)C.GetWindowHeight();
		float BarHeight = (C.GetWindowHeight() / C.GetFontSize()) / ((float)Texts.size() + 1) * (float)C.GetWindowHeight();
		DrawRect(C.GetWindowWidth() - C.GetFontSize() / 2, BarY, C.GetFontSize() / 2, BarHeight, 0x00999999);
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
		ProcessChoice();
	}
	if(GetKey(LEFT))
	{
		ChoosingLine = 0;
	}
	if(GetKey(UP))
	{
		if(KeyIntervalCount > 90)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > 2 && Hold))
		{
			ChoosingLine--;
			KeyIntervalCount = 0;
		}
		else
		{
			KeyIntervalCount++;
		}
		TmpKey = true;
	}
	else if(GetKey(DOWN))
	{
		if(KeyIntervalCount > 120)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > 2 && Hold))
		{
			ChoosingLine++;
			KeyIntervalCount = 0;
		}
		else
		{
			KeyIntervalCount++;
		}
		TmpKey = true;
	}
	else
	{
		KeyIntervalCount = 0;
		TmpKey = false;
		Hold = false;
	}
	return 0;
}

int UI::ProcessChoice(void)
{
		if(Mode == MAINMENU)
		{
			if(Texts[Scroll + ChoosingLine] == "Artists")
			{
				Scroll = 0;
				ChoosingLine = 1;
				Mode = CHOOSE_ARTIST;
				Texts = GetSortedArtists(MList);
				Texts.insert(Texts.begin(), "< Back");
			}
			if(Texts[Scroll + ChoosingLine] == "Albums")
			{
				Scroll = 0;
				ChoosingLine = 1;
				Mode = CHOOSE_ALBUM;
				Texts = GetSortedAlbums(MList);
				Texts.insert(Texts.begin(), "< Back");
			}
			if(Texts[Scroll + ChoosingLine] == "Songs")
			{
				Scroll = 0;
				ChoosingLine = 1;
				Mode = CHOOSE_TITLE;
				Texts = GetSortedTitles(MList);
				Texts.insert(Texts.begin(), "< Back");
			}
		}
	return 0;
}
