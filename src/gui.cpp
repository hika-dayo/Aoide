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
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>
#include <optional>
#include <random>
#include <algorithm>
#include <iostream>

UI::UI(std::vector<Music> &MusicList)
{
	P = nullptr;
	Mode = MAINMENU;
	PrevMode = MAINMENU;
	CurrentMusic = new Music("");

	Hold = false;
	KeyIntervalCount = 0;
	TmpKey = false;
	TmpEnter = false;
	TmpSpace = false;


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
	Object.push_back(MenuItem("Exit", EXIT));
	ObjectBuf.push_back(Object);//バッファとして
	return;
}

int UI::Process(void)
{
	ProcessKey();
	CurrentLine = Scroll + ChoosingLine;
	ProcessScroll();	

	if(Playlist.size() != 0)
	{

		if(P == nullptr || (P != nullptr && P->isEnded()))
		{
			if(P != nullptr)
			{
				delete P;
			}
			P = new Player(Playlist[0].GetPath().c_str());
			if(CurrentMusic != nullptr)
			{
				delete CurrentMusic;
			}
			CurrentMusic = new Music("");
			*CurrentMusic = Playlist[0];

			Playlist.erase(Playlist.begin());
			P->Play();
		}
	}

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
	if(0 > ChoosingLine + Scroll)
	{
		if(Hold)//ホールドされてるなら止まる
		{
			Scroll = 0;
			ChoosingLine = 0;
		}
		else
		{
			Scroll = Object.size() - (C.GetWindowHeight() / C.GetFontSize());
	
			if(Scroll < 0)
			{
				Scroll = 0;
			}
			ChoosingLine = Object.size() - Scroll - 1;
	
		}
	}


	if(Object.size() <= ChoosingLine + Scroll)//選択したところが範囲外なら
	{
		if(Hold)//ホールドされてるなら止まる
		{
			ChoosingLine--;
		}
		else
		{
			Scroll = 0;
			ChoosingLine = 0;

		}
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
	if(GetKey(SPACE))
	{
		if(TmpSpace == false)
			ProcessChoice(false);
		TmpSpace = true;
	}
	else
	{
		TmpSpace = false;
	}
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
		if(KeyIntervalCount > WAIT_TIME_FOR_HOLD)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > HOLD_DELAY && Hold))
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
		if(KeyIntervalCount > WAIT_TIME_FOR_HOLD)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > HOLD_DELAY && Hold))
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

int UI::ProcessChoice(bool End)
{
	if(Object[CurrentLine].GetEvent() == BACK)
	{
		if(ObjectBuf.size() != 0)
		{
			Scroll = PrevScroll[PrevScroll.size() - 1];
			PrevScroll.pop_back();

			ChoosingLine = PrevChoosingLine[PrevChoosingLine.size() - 1];
			PrevChoosingLine.pop_back();
			
			Object = ObjectBuf[ObjectBuf.size() - 1];
			ObjectBuf.pop_back();
		}
		return 0;
	}
	if(Object[CurrentLine].GetEvent() == LIST_ARTISTS)
	{
		ListItem(GetSortedArtists(MList), LIST_ARTISTS, LIST_ALBUMS, CHOOSE_ARTIST);
		return 0;
	}
	if(Object[CurrentLine].GetEvent() == LIST_ALBUMS)
	{
		ListItem(GetSortedAlbums(MList, Object[CurrentLine].GetArtist()), LIST_ALBUMS, LIST_TITLES_BY_TRACKNUM, CHOOSE_TITLE);
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == LIST_TITLES_BY_TRACKNUM)
	{
		ListItem(GetSortedTrackNum(MList, Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum()), LIST_TITLES_BY_TRACKNUM, PLAY_MUSIC, CHOOSE_TITLE);
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == LIST_TITLES)
	{
		ListItem(GetSortedTitles(MList, Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum()), LIST_TITLES, PLAY_MUSIC, CHOOSE_TITLE);
		return 0;
	}
	if(Object[CurrentLine].GetEvent() == PLAY_ALL)
	{
		int n = 0;
		for(int i = 0; i < Object.size();i++)
		{
			if(End)
			{
				if(!Object[i].GetPath().empty())
				{
						Playlist.push_back(Music(Object[i].GetPath(), Object[i].GetArtist(), Object[i].GetAlbum(), Object[i].GetTitle(), 0));
				}

			}
			else
			{
				if(!Object[i].GetPath().empty())
				{
						Playlist.insert(Playlist.begin() + n, Music(Object[i].GetPath(), Object[i].GetArtist(), Object[i].GetAlbum(), Object[i].GetTitle(), 0));
						n++;
				}
			}
		}
		if(!End)
		{
			if(P != nullptr)
			{
				P->Stop();
				delete P;
			}
					
			P = nullptr;
		}
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == PLAY_MUSIC)
	{
		if(End)
		{
			Playlist.push_back(Music(Object[CurrentLine].GetPath(), Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum(), Object[CurrentLine].GetTitle(), 0));
		}
		else
		{
			if(P != nullptr)
			{
				P->Stop();
				delete P;
			}
					
			P = nullptr;
			Playlist.insert(Playlist.begin(), Music(Object[CurrentLine].GetPath(), Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum(), Object[CurrentLine].GetTitle(), 0));
		}
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == EXIT)
	{
		exit(0);
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
MenuItem::MenuItem(const MenuItem &Copy)
{
	Text = Copy.Text;
	Artist = Copy.Artist;
	Album = Copy.Album;
	Title = Copy.Title;
	Path = Copy.Path;
	Event = Copy.Event;
	return;
}

int UI::ListItem(std::vector<Music> M, EVENT E, EVENT SetE, UI_MODE MODE)
{
	ObjectBuf.push_back(Object);
	PrevScroll.push_back(Scroll);
	PrevChoosingLine.push_back(ChoosingLine);

	Scroll = 0;
	ChoosingLine = 1;
	PrevMode = Mode;
	Mode = MODE;
	Object.clear();
	std::vector<MenuItem> TmpMenu;
	if(E == LIST_TITLES)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		TmpMenu.push_back(MenuItem("Play All", PLAY_ALL));
		std::string Title;
		for(int i = 0; i < M.size(); i++)
		{
			std::string Title = "  " + M[i].GetTitle();
			TmpMenu.push_back(MenuItem(Title, SetE, M[i]));
		}	
	}
	if(E == LIST_ALBUMS)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		for(int i = 0; i < M.size(); i++)
		{
			TmpMenu.push_back(MenuItem(M[i].GetAlbum(), SetE, M[i]));
		}	
	}
	if(E == LIST_ARTISTS)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		for(int i = 0; i < M.size(); i++)
		{
			TmpMenu.push_back(MenuItem(M[i].GetArtist(), SetE, M[i]));
		}	
	}
	if(E == LIST_TITLES_BY_TRACKNUM)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		TmpMenu.push_back(MenuItem("Play All", PLAY_ALL));
		std::string Title;
		for(int i = 0; i < M.size(); i++)
		{
			Title = "  " + M[i].GetTitle();
			TmpMenu.push_back(MenuItem(Title, SetE, M[i]));
		}	
	}
	Object = TmpMenu;

	

	return 0;
}

int UI::ShufflePlaylist(void)
{
	std::random_device Rd;
	std::default_random_engine Engine(Rd());
	std::shuffle(Playlist.begin(), Playlist.end(), Engine);
	return 0;
}
