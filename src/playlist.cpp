/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/playlist.hpp"
#include <iostream>

Playlist::Playlist(void)
{
	PlayingMusic = new Music("");
	P = new Player("");
}

Player& Playlist::GetPlayer(void)
{
	return *P;
}

int Playlist::InsertQueue(Music M)
{
	List.insert(List.begin(), M);
	return 0;
}
int Playlist::PushQueue(Music M)
{
	List.push_back(M);
	return 0;
}

int Playlist::PlayNext(void)
{
	if(!List.empty())
	{
		if(PlayingMusic->GetPath() != "")
		{
			History.push_back(*PlayingMusic);
		}
		*PlayingMusic = List[0];
	}
	delete P;
	P = nullptr;
	return 0;
}

int Playlist::PlayPrev(void)
{
	if(!History.empty())
	{
		if(PlayingMusic->GetPath() != "")
		{
			InsertQueue(*PlayingMusic);
			InsertQueue(History[History.size() - 1]);
			*PlayingMusic = History[History.size() - 1];
			History.pop_back();
		}
		delete P;
		P = nullptr;
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
	if(P != nullptr && P->isEnded())
	{
		if(!List.empty())
		{
			History.push_back(List[0]);
		}
	}
	if(P == nullptr || P->isEnded())
	{
		if(P != nullptr)
		{
			delete P;
		}
		P = nullptr;
		if(!List.empty())
		{
			P = new Player(List[0].GetPath().c_str());
			*PlayingMusic = List[0];
			List.erase(List.begin());
			P->Play();
		}
	}
	
	return 0;
}

int Playlist::Pause()
{
	if(P->isPaused())
	{
		std::cout << "bb" << std::endl;
		P->Play();
		return 0;
	}
	if(P->isPlaying())
	{
		std::cout << "aa" << std::endl;
		P->Pause();
		return 0;
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
	if(PlayingMusic != nullptr)
	{
		delete PlayingMusic;
		PlayingMusic = nullptr;
	}
	return;
}
Music Playlist::GetPlayingMusic(void)
{
	return *PlayingMusic;
}
