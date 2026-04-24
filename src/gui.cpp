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
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>
#include <optional>
#include <iostream>

UI::UI(std::vector<Music> &MusicList)
{
	Mode = MAINMENU;
	PrevMode = MAINMENU;

	Hold = false;
	KeyIntervalCount = 0;
	TmpKey = false;
	TmpEnter = false;


	Scroll = 0;
	MList = MusicList;
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
	Object.push_back(MenuItem("Artists", LIST_ARTISTS));
	Object.push_back(MenuItem("Albums", LIST_ALBUMS));
	Object.push_back(MenuItem("Songs", LIST_TITLES));
//	Object.push_back(MenuItem("Options", NOTHING));
	Object.push_back(MenuItem("Exit", EXIT));
	return;
}

int UI::Process(void)
{
	Config C;
	ProcessKey();
	ProcessScroll();	

	for(int i = 0; i + Scroll < Object.size(); i++)
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
		float BarHeight = (C.GetWindowHeight() / C.GetFontSize()) / ((float)Object.size() + 1) * (float)C.GetWindowHeight();
		DrawRect(C.GetWindowWidth() - C.GetFontSize() / 2, BarY, C.GetFontSize() / 2, BarHeight, 0x00999999);
	return 0;
}


int UI::ProcessScroll(void)
{
	if(0 > ChoosingLine + Scroll && !Hold)
	{
		Scroll = Object.size() - C.GetWindowHeight() / C.GetFontSize() / 2;

		if(Scroll < 0)
		{
			Scroll = 0;
		}
		ChoosingLine = Object.size() - Scroll - 1;
	}
	if(Object.size() <= ChoosingLine + Scroll && !Hold)
	{
		Scroll = 0;
		ChoosingLine = 0;
	}


	if(Scroll == Object.size())
	{
		Scroll = Object.size() - 1;

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
	return 0;
}
int UI::ProcessKey(void)
{
	if(GetKey(ENTER))
	{
		if(TmpEnter == false)
			ProcessChoice();
		TmpEnter = true;
	}
	else
	{
		TmpEnter = false;
	}
	if(GetKey(LEFT))
	{
		Scroll = 0;
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
	if(Object[Scroll + ChoosingLine].GetEvent() == BACK)
	{
		int Tmp = Scroll;
		Scroll = PrevScroll;
		PrevScroll = Tmp;
		Tmp = ChoosingLine;
		ChoosingLine = PrevChoosingLine;
		PrevChoosingLine = Tmp;


		if(PrevMode == MAINMENU)
		{
			Mode = MAINMENU;
			PrevMode = MAINMENU;
			Object.clear();
			Object.push_back(MenuItem("Artists", LIST_ARTISTS));
			Object.push_back(MenuItem("Albums", LIST_ALBUMS));
			Object.push_back(MenuItem("Songs", LIST_TITLES));
//			Object.push_back(MenuItem("Options", NOTHING));
			Object.push_back(MenuItem("Exit", EXIT));
		}
		return 0;
	}
	if(Mode == MAINMENU)
	{
		if(Object[Scroll + ChoosingLine].GetEvent() == LIST_ARTISTS)
		{
			PrevScroll = Scroll;
			PrevChoosingLine = ChoosingLine;
			Scroll = 0;
			ChoosingLine = 1;
			PrevMode = Mode;
			Mode = CHOOSE_ARTIST;
			Object.clear();
			std::vector<Music> Tmp = GetSortedArtists(MList);
			std::vector<MenuItem> TmpMenu;
			for(int i = 0; i < Tmp.size(); i++)
			{
				TmpMenu.push_back(MenuItem(Tmp[i].GetArtist(), LIST_ALBUMS, Tmp[i]));
			}
			Object = TmpMenu;
			Object.insert(Object.begin(), MenuItem("< Back", BACK));
			
			return 0;
		}
		if(Object[Scroll + ChoosingLine].GetEvent() == LIST_ALBUMS)
		{
			PrevScroll = Scroll;
			PrevChoosingLine = ChoosingLine;
			Scroll = 0;
			ChoosingLine = 1;
			PrevMode = Mode;
			Mode = CHOOSE_ALBUM;
			Object.clear();
			std::vector<Music> Tmp = GetSortedAlbums(MList);
			std::vector<MenuItem> TmpMenu;
			for(int i = 0; i < Tmp.size(); i++)
			{
				TmpMenu.push_back(MenuItem(Tmp[i].GetArtist(), LIST_ALBUMS, Tmp[i]));
			}
			Object = TmpMenu;
			Object.insert(Object.begin(), MenuItem("< Back", BACK));
			return 0;
		}
		if(Object[Scroll + ChoosingLine].GetEvent() == LIST_TITLES)
		{
			PrevScroll = Scroll;
			PrevChoosingLine = ChoosingLine;
			Scroll = 0;
			ChoosingLine = 1;
			PrevMode = Mode;
			Mode = CHOOSE_TITLE;
			Object.clear();
			std::vector<Music> Tmp = GetSortedTitles(MList);
			std::vector<MenuItem> TmpMenu;
			for(int i = 0; i < Tmp.size(); i++)
			{
				TmpMenu.push_back(MenuItem(Tmp[i].GetTitle(), PLAY_MUSIC, Tmp[i]));
			}
			Object = TmpMenu;
			Object.insert(Object.begin(), MenuItem("< Back", BACK));
			return 0;
		}
		if(Object[Scroll + ChoosingLine].GetEvent() == EXIT)
		{
			exit(0);
		}
	}
	return 0;
}

MenuItem::MenuItem(std::string Text,EVENT Event, std::optional<Music> M)
{
	Artist = "";
	Album = "";
	Title = "";
	Path = "";
	if(M.has_value())
	{
		Artist = M.value().GetArtist();
		Album = M.value().GetAlbum();
		Title = M.value().GetTitle();
		Path = M.value().GetPath();
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
std::string MenuItem::GetText(void)
{
	return Text;
}
EVENT MenuItem::GetEvent(void)
{
	return Event;
}
