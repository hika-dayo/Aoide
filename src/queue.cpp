/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/queue.hpp"
#include "../includes/config.hpp"
#include "../includes/gui.hpp"
#include <iostream>

PlaybackQueue::PlaybackQueue(void) : PlayingMusic("")
{
	Config C;
//	PlayingMusic = &EmptyMusic;
	UnknownArtwork = new Image(C.GetUnknownArtworkPath());
	P = nullptr;
	Artwork = nullptr;
}
Player& PlaybackQueue::GetPlayer(void)
{
	return *P;
}

int PlaybackQueue::InsertQueue(Music M)
{
	if(M.GetPath() != "")
	{
		List.insert(List.begin(), M);
	}
	return 0;
}
int PlaybackQueue::PushQueue(Music M)
{
	if(M.GetPath() != "")
	{
		List.push_back(M);
	}
	return 0;
}

int PlaybackQueue::PlayNext(void)
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

int PlaybackQueue::PlayPrev(void)
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

std::vector<Music> &PlaybackQueue::GetPlaybackQueue(void)
{
	return List;
}
std::vector<Music> &PlaybackQueue::GetHistory(void)
{
	return History;
}


int PlaybackQueue::Process(void)
{
	PlayQueue();
	if(Artwork == nullptr)
	{
		if(PlayingMusic.GetArtworkPath() != "")
		{
			Artwork = new Image(PlayingMusic.GetArtworkPath());
		}
	}
	if(Artwork != nullptr)
	{
		if(PlayingMusic.GetArtworkPath() == "")
		{
			delete Artwork;
			Artwork = nullptr;
		}else
		{
			if(Artwork->GetPath() != PlayingMusic.GetArtworkPath())
			{
				delete Artwork;
				Artwork = new Image(PlayingMusic.GetArtworkPath());
			}

		}
	}
	return 0;
}
int PlaybackQueue::PlayQueue(void)
{
	if(P == nullptr)
	{
		if(PlayingMusic.GetPath() != "")
		{
			P = new Player(PlayingMusic.GetPath().c_str());
			P->Play();
		}else
	{
			PlayNext();
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
int PlaybackQueue::Play()
{
	if(P != nullptr)
	{
		if(P->isPaused())
		{
			P->Play();
		}
		else
		{
			Pause();
		}
	}
	return 0;
}
int PlaybackQueue::Pause()
{
	if(P != nullptr)
	{
			P->Pause();
	}
	return 0;
}
PlaybackQueue::~PlaybackQueue(void)
{
	if(P != nullptr)
	{
		delete P;
		P = nullptr;
	}
	return;
}
Music PlaybackQueue::GetPlayingMusic(void)
{
	return PlayingMusic;
}

int PlaybackQueue::GetTrackLength(void)
{
	if(P != nullptr)
	{
		return P->GetAudioLength();
	}
		return 0;

}
int PlaybackQueue::GetPlaybackTime(void)
{
	if(P != nullptr)
	{
		return P->GetAudioTime();
	}
	return 0;

}
int PlaybackQueue::GetPlaybackPosition(void)
{
	if(P != nullptr)
	{
		if(P->GetAudioLength() != 0)
		{
			return 1000 * P->GetAudioTime() / P->GetAudioLength();

		}
	}
	return 0;

}
int PlaybackQueue::GetPlayerStatus(void)
{
	if(P != nullptr)
	{
		return P->isPlaying();
	}
	return 0;
}
Image &PlaybackQueue::GetArtwork(void)
{
	if(Artwork == nullptr)
	{
		return *UnknownArtwork;
	}
	return *Artwork;
}
