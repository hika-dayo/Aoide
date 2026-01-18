/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once



#include <vlc/vlc.h>
#include <string>




class Player
{
	private:
		libvlc_instance_t* Instance;
		//VLCの読み込み
		libvlc_media_t* Media;
		libvlc_media_player_t* MediaPlayer;
		std::string FilePath;
		libvlc_state_t GetState(void);
	public:
		~Player();
		Player(const char* Path);	const char* GetFilePath(void);
		bool isEnded(void);	
		bool isPlaying(void);
		bool isPaused(void);
		bool hasError(void);
		int Stop(void);
		int Pause(void);
		int Play(void);
};
