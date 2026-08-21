/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once
#include <vector>
#include "player.hpp"
#include "audio_engine.hpp"
class Playlist
{
private:
	std::vector<Music> List;
	std::vector<Music> History;
	Music PlayingMusic;
	Player *P;
	bool HasQueue;
	int PlayQueue(void);	
//	Music EmptyMusic;
public:
	Music GetPlayingMusic(void);
	std::vector<Music> GetPlaylist(void);
	std::vector<Music> GetHistory(void);
	Player &GetPlayer(void);
	Playlist(void);
	~Playlist(void);
	int Pause(void);
	int Play(void);
	int InsertQueue(Music M);//先頭に挿入するか
	int PushQueue(Music M);//最後尾に挿入するか
	int PlayNext(void);//次へ進む
	int PlayPrev(void);//前へ進む
	int Process(void);//自動的にプレイリストを再生する
};
