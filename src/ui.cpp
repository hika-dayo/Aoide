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

UI::UI(std::vector<Music> &MusicList) : img(C.GetGraphicDir() + "playicon.png"), img2(C.GetGraphicDir() + "stopicon.png")
{
	Object.push_back(MenuItem("Artists", LIST_ARTISTS));
	Object.push_back(MenuItem("Albums", LIST_ALBUMS));
	Object.push_back(MenuItem("Songs", LIST_TITLES));
	Object.push_back(MenuItem("Exit", EXIT));
	S = std::make_unique<ScrollState>(0, 0, Object.size());
	
	P = nullptr;

	Hold = false;
	KeyIntervalCount = 0;
	TmpKey = false;
	TmpEnter = false;
	TmpSpace = false;
	
	PlaylistMode = false;

	MList = MusicList;
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
	
	return;
}

int UI::Process(void)
{
	
	ProcessKey();
		
	List.Process();

	if(PlaylistMode == true)
	{
		img.DrawImage(0, 0, 24, 24);
		img2.DrawImage(50,0, 24, 24);
		
		
	}else
	{
		Rend.DrawMenu(S->GetChoosingLine(), S->GetScroll(), Object);

	}
	
	return 0;
}


int UI::ProcessKey(void)
{
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
			S = std::make_unique<ScrollState>(PrevScroll[PrevScroll.size() - 1], PrevChoosingLine[PrevChoosingLine.size() - 1], Object.size());
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
int UI::ListItem(std::vector<Music> M, EVENT E, EVENT SetE)
{
	ObjectBuf.push_back(Object);
	PrevScroll.push_back(S->GetScroll());
	PrevChoosingLine.push_back(S->GetChoosingLine());
	
	Object.clear();
	std::vector<MenuItem> TmpMenu;
	if(E == LIST_TITLES)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		TmpMenu.push_back(MenuItem("Shuffle", SHUFFLE_PLAY));	
		TmpMenu.push_back(MenuItem("Play All", PLAY_ALL));

		std::string Title;
		for(int i = 0; i < M.size(); i++)
		{
			std::string Title = "  " + M[i].GetTitle();
			TmpMenu.push_back(MenuItem(Title, SetE, M[i]));
		}	
		S = std::make_unique<ScrollState>(0, 2, TmpMenu.size());
	}
	if(E == LIST_ALBUMS)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		for(int i = 0; i < M.size(); i++)
		{
			TmpMenu.push_back(MenuItem(M[i].GetAlbum(), SetE, M[i]));
		}	
		S = std::make_unique<ScrollState>(0, 1, TmpMenu.size());
	}
	if(E == LIST_ARTISTS)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		for(int i = 0; i < M.size(); i++)
		{
			TmpMenu.push_back(MenuItem(M[i].GetArtist(), SetE, M[i]));
		}	
		S = std::make_unique<ScrollState>(0, 1, TmpMenu.size());
	}
	if(E == LIST_TITLES_BY_TRACKNUM)
	{
		TmpMenu.push_back(MenuItem("< Back", BACK));
		TmpMenu.push_back(MenuItem("Shuffle", SHUFFLE_PLAY));
		TmpMenu.push_back(MenuItem("Play All", PLAY_ALL));
	
		std::string Title;
		for(int i = 0; i < M.size(); i++)
		{
			Title = "  " + M[i].GetTitle();
			TmpMenu.push_back(MenuItem(Title, SetE, M[i]));
		}	
		S = std::make_unique<ScrollState>(0, 2, TmpMenu.size());
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
