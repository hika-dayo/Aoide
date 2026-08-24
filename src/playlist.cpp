/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/playlist.hpp"
#include <iostream>

Playlist::Playlist(void) : PlayingMusic("")
{
//	PlayingMusic = &EmptyMusic;
	P = new Player("");
}
Player& Playlist::GetPlayer(void)
{
	return *P;
}

int Playlist::InsertQueue(Music M)
{
	if(M.GetPath() != "")
	{
		List.insert(List.begin(), M);
	}
	return 0;
}
int Playlist::PushQueue(Music M)
{
	if(M.GetPath() != "")
	{
		List.push_back(M);
	}
	return 0;
}

int Playlist::PlayNext(void)
{
	if(PlayingMusic.GetPath() != "")
	{
		History.push_back(PlayingMusic);

	}
	PlayingMusic = Music("");
	if(!List.empty())
	{
		if(!List.empty())
		{
			PlayingMusic = List[0];
			List.erase(List.begin());
		}
	}
	return 0;
}

int Playlist::PlayPrev(void)
{
	if(History.size() > 0)
	{
		
		InsertQueue(PlayingMusic);
		PlayingMusic = History.back();
		History.pop_back();
		delete P;
		P = nullptr;
		
	}
	else
	{
		InsertQueue(PlayingMusic);
		PlayingMusic = Music("");
	}
	return 0;
}

std::vector<Music> Playlist::GetPlaylist(void)
{
	return List;
}
std::vector<Music> Playlist::GetHistory(void)
{
	return History;
}


int Playlist::Process(void)
{
//	if(P == nullptr)
//	{
//		PlayQueue();
//	}
//	else
//	{
//		if(P->isEnded())
//		{
//			PlayQueue();
//		}
//	}
	PlayQueue();

//	std::cout << std::endl;
//	for(int i = 0; i < History.size(); i++)
//	{
//	  std::cout << History[i].GetTitle() << std::endl;
//	}
//  	std::cout << std::endl;
//	std::cout << PlayingMusic.GetTitle() << std::endl;
//  	std::cout << std::endl;
//	for(int i = 0; i < List.size(); i++)
//	{
//	  std::cout << List[i].GetTitle() << std::endl;
//	}
//  	std::cout << std::endl;
	return 0;
}
int Playlist::PlayQueue(void)
{
	if(P == nullptr)
	{
		if(PlayingMusic.GetPath() != "")
		{
			P = new Player(PlayingMusic.GetPath().c_str());
			P->Play();
		}
		
	}else
	{
		if(P->GetFilePath() != PlayingMusic.GetPath())
		{
			delete P;
			P = new Player(PlayingMusic.GetPath().c_str());
			P->Play();
		}else
	{
			if(P->isEnded())
			{
				PlayNext();
				delete P;
				P = new Player(PlayingMusic.GetPath().c_str());
				P->Play();
			}
		}
	}
	return 0;
}
int Playlist::Play()
{
	if(P != nullptr)
	{
			P->Play();
	}
	return 0;
}
int Playlist::Pause()
{
	if(P != nullptr)
	{
			P->Pause();
	}
	return 0;
}
Playlist::~Playlist(void)
{
	if(P != nullptr)
	{
		delete P;
		P = nullptr;
	}
	return;
}
Music Playlist::GetPlayingMusic(void)
{
	return PlayingMusic;
}
