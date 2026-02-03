/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../include/player.hpp"
#include "../include/vlcinstance.hpp"
#include <vlc/libvlc.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>
#include <string>

//プレーヤークラスの関数たち
Player::Player(const char* Path)
{
	FilePath = Path;
	Instance = GetVLCInstance();
	Media = libvlc_media_new_path(Instance, FilePath.c_str());//メディアを作成
	MediaPlayer = libvlc_media_player_new_from_media(Media);//プレーヤーの再生環境を作成
	libvlc_media_release(Media);//メディアの参照カウントを減少
	return;
}
Player::~Player()
{
	libvlc_media_player_release(MediaPlayer);
	return;
}

const char* Player::GetFilePath(void)
{
	return FilePath.c_str();
}

libvlc_state_t Player::GetState(void)
{
	return libvlc_media_player_get_state(MediaPlayer);
}



//プレーヤーの状態確認する関数たち
bool Player::isEnded(void)
{
	return (libvlc_state_t::libvlc_Ended == GetState());
}

bool Player::isPlaying(void)
{
	return (libvlc_state_t::libvlc_Playing == GetState());
}

bool Player::isPaused(void)
{
	return (libvlc_state_t::libvlc_Paused == GetState());
}
bool Player::hasError(void)
{
	return (libvlc_state_t::libvlc_Error == GetState());
}




//プレーヤーの状態変更関数たち
int Player::Stop(void)
{
	if(libvlc_state_t::libvlc_Stopped != GetState())//変更前と変更後が同じだったら変更しない
	{
		libvlc_media_player_stop(MediaPlayer);
	}
	return 0;
}
int Player::Pause(void)
{
	if(libvlc_state_t::libvlc_Paused != GetState())
	{
		libvlc_media_player_pause(MediaPlayer);
	}
	return 0;
}
int Player::Play(void)
{
	if(libvlc_state_t::libvlc_Playing != GetState())
	{
		libvlc_media_player_play(MediaPlayer);
	}
	return 0;
}
