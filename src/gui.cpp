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
	S = new ScrollState(0, 0, 0);
	P = nullptr;

	Hold = false;
	KeyIntervalCount = 0;
	TmpKey = false;
	TmpEnter = false;
	TmpSpace = false;
	
	PlaylistMode = false;

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
		
	List.Process();

	if(PlaylistMode != true)
	{
		for(int i = 0; i + S->GetScroll() < Object.size(); i++)
		{
			if(i == S->GetChoosingLine())
			{
				DrawRect(0, C.GetFontSize() * i , C.GetWindowWidth(), C.GetFontSize(), FontColor);
				DrawText(Font, Object[S->GetScroll() + i].GetText().c_str(), 0x00ffffff - FontColor, 0, i * C.GetFontSize());
	
			}
			else
			{
				DrawText(Font, Object[S->GetScroll() + i].GetText().c_str(), FontColor, 0, i * C.GetFontSize());			
			}
		}

		float BarY = S->GetScroll() / (float)Object.size() * (float)C.GetWindowHeight();
		float BarHeight;
		if(Object.size() == 0)
		{	
			BarHeight = C.GetWindowHeight();
		}
		else
		{
			BarHeight = (C.GetWindowHeight() / C.GetFontSize()) / ((float)Object.size()) * (float)C.GetWindowHeight();
		}
			DrawRect(C.GetWindowWidth() - C.GetFontSize() / 2, BarY, C.GetFontSize(), BarHeight, 0x00999999);	
	}
	return 0;
}


int UI::ProcessKey(void)
{
	if(GetKey(PLAY_BACK))
	{
		if(TmpFB == false)
		{
			List.PlayPrev();
		}
		TmpFB = true;
	}
	else if(GetKey(PLAY_FORWARD))
	{
		if(TmpFB == false)
		{
			List.PlayNext();
		}
		TmpFB = true;
	}
	else
	{
		TmpFB = false;
	}
	if(GetKey(PAUSE_PLAY))
	{
		if(TmpPause == false)
		{	
			List.Pause();
		}
		TmpPause = true;
	}
	else
	{
		TmpPause= false;
	}

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
	
	if(GetKey(RIGHT))
	{
		if(TmpRightKey == false)
		{
			if(PlaylistMode == false)
			{
				PlaylistMode = true;
			}
			else
			{
				PlaylistMode = false;
			}
		}
		TmpRightKey = true;
	}
	else
	{
		TmpRightKey = false;
	}
	if(GetKey(LEFT))
	{
		S->GoBegin(Object.size());
	}
	if(GetKey(UP))
	{
		if(KeyIntervalCount > WAIT_TIME_FOR_HOLD)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > HOLD_DELAY && Hold))
		{
			S->ScrollDown(Object.size(), Hold);
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
			S->ScrollUp(Object.size(), Hold);
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
	int CurrentLine = S->GetCurrentLine();
	if(Object[CurrentLine].GetEvent() == BACK)
	{
		if(ObjectBuf.size() != 0)
		{
			Object = ObjectBuf[ObjectBuf.size() - 1];
			delete S;
			S = new ScrollState(PrevScroll[PrevScroll.size() - 1], PrevChoosingLine[PrevChoosingLine.size() - 1], Object.size());
			PrevScroll.pop_back();
			PrevChoosingLine.pop_back();	
			ObjectBuf.pop_back();
		}
		return 0;
	}
	if(Object[CurrentLine].GetEvent() == LIST_ARTISTS)
	{
		ListItem(GetSortedArtists(MList), LIST_ARTISTS, LIST_ALBUMS);
		return 0;
	}
	if(Object[CurrentLine].GetEvent() == LIST_ALBUMS)
	{
		ListItem(GetSortedAlbums(MList, Object[CurrentLine].GetArtist()), LIST_ALBUMS, LIST_TITLES_BY_TRACKNUM);
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == LIST_TITLES_BY_TRACKNUM)
	{
		ListItem(GetSortedTrackNum(MList, Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum()), LIST_TITLES_BY_TRACKNUM, PLAY_MUSIC);
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == LIST_TITLES)
	{
		ListItem(GetSortedTitles(MList, Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum()), LIST_TITLES, PLAY_MUSIC);
		return 0;
	}
	if(Object[CurrentLine].GetEvent() == PLAY_ALL)
	{

		int n = 0;
		for(int i = 0; i < Object.size();i++)
		{
			n = Object.size() - i - 1;
			if(End)
			{
				if(!Object[i].GetPath().empty())
				{
						List.PushQueue(Music(Object[i].GetPath(), Object[i].GetArtist(), Object[i].GetAlbum(), Object[i].GetTitle(), 0));
				}

			}
			else
			{
				if(!Object[n].GetPath().empty())
				{
						List.InsertQueue(Music(Object[n].GetPath(), Object[n].GetArtist(), Object[n].GetAlbum(), Object[n].GetTitle(), 0));
				}
			}
		}
		if(!End)
		{
			List.PlayNext();
		}
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == SHUFFLE_PLAY)
	{
		std::vector<Music> Tmp;
		int n = 0;
		for(int i = 0; i < Object.size();i++)
		{
			if(!Object[i].GetPath().empty())
			{
				Tmp.push_back(Music(Object[i].GetPath(), Object[i].GetArtist(), Object[i].GetAlbum(), Object[i].GetTitle(), 0));
			}
		}
		ShuffleTitles(Tmp);
		
		for(int i = 0; i < Tmp.size();i++)
		{
			n = Tmp.size() - i - 1;
			if(End)
			{
				if(!Tmp[i].GetPath().empty())
				{
						List.PushQueue(Tmp[i]);
				}

			}
			else
			{
				if(!Tmp[n].GetPath().empty())
				{
						List.InsertQueue(Tmp[n]);
				}
			}
		}
		if(!End)
		{
			List.PlayNext();
		}
		return 0;
	}

	if(Object[CurrentLine].GetEvent() == PLAY_MUSIC)
	{
		if(End)
		{
			List.PushQueue(Music(Object[CurrentLine].GetPath(), Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum(), Object[CurrentLine].GetTitle(), 0));
		}
		else
		{
			List.InsertQueue(Music(Object[CurrentLine].GetPath(), Object[CurrentLine].GetArtist(), Object[CurrentLine].GetAlbum(), Object[CurrentLine].GetTitle(), 0));
			List.PlayNext();
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

int UI::ListItem(std::vector<Music> M, EVENT E, EVENT SetE)
{
	ObjectBuf.push_back(Object);
	PrevScroll.push_back(S->GetScroll());
	PrevChoosingLine.push_back(S->GetChoosingLine());
	
	delete S;
	S = new ScrollState(0, 1, 1);
	Object.clear();
	std::vector<MenuItem> TmpMenu;
	if(E == LIST_TITLES)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		TmpMenu.push_back(MenuItem("Shuffle", SHUFFLE_PLAY));	
		TmpMenu.push_back(MenuItem("Play All", PLAY_ALL));
		delete S;
		S = new ScrollState(0, 2, 1);

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
		TmpMenu.push_back(MenuItem("Shuffle", SHUFFLE_PLAY));
		TmpMenu.push_back(MenuItem("Play All", PLAY_ALL));
		delete S;
		S = new ScrollState(0, 2, 1);
	
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

int UI::ShuffleTitles(std::vector<Music> &ArgMusic)
{
	std::random_device Rd;
	std::default_random_engine Engine(Rd());
	std::shuffle(ArgMusic.begin(), ArgMusic.end(), Engine);
	return 0;
}



