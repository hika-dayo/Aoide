/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/player.hpp"
#include "../includes/audio_engine.hpp"
#include "../includes/file.hpp"
#include <miniaudio/miniaudio.h>
#include <string>

//プレーヤークラスの関数
Player::Player(const char* Path)
{
	Error = false;
	Error = !FileExists(Path);
	FilePath = Path;

	Engine = GetMiniaudioEngine();
	SoundInitFromFile(FilePath.c_str(), &Sound);
	return;
}
Player::~Player()
{
	ma_sound_uninit(&Sound);
	return;
}

const char* Player::GetFilePath(void)
{
	return FilePath.c_str();
}

//プレーヤーの状態確認する関数
bool Player::isEnded(void)
{
	ma_uint64 Length;
	ma_uint64 Cursor;
	ma_sound_get_length_in_pcm_frames(&Sound, &Length);
	ma_sound_get_cursor_in_pcm_frames(&Sound, &Cursor);
	return (Length == Cursor);
}

bool Player::isPlaying(void)
{
	return ma_sound_is_playing(&Sound);
}

bool Player::isPaused(void)
{
	ma_uint64 Length;
	ma_uint64 Cursor;
	ma_sound_get_length_in_pcm_frames(&Sound, &Length);
	ma_sound_get_cursor_in_pcm_frames(&Sound, &Cursor);
	return (Length != Cursor) && !ma_sound_is_playing(&Sound);
}
bool Player::hasError(void)
{
	return Error;
}
int Player::GetAudioLength(void)
{
	ma_uint64 Length;
	ma_sound_get_length_in_pcm_frames(&Sound, &Length);
	return Length * 1000 / ma_engine_get_sample_rate(Engine);
}

int Player::GetAudioTime(void)
{
	ma_uint64 Cursor;
	ma_sound_get_cursor_in_pcm_frames(&Sound, &Cursor);
	return Cursor * 1000 / ma_engine_get_sample_rate(Engine);
}
double Player::GetAudioPosition(void)
{
	ma_uint64 Length;
	ma_uint64 Cursor;
	ma_sound_get_length_in_pcm_frames(&Sound, &Length);
	ma_sound_get_cursor_in_pcm_frames(&Sound, &Cursor);
	return (Cursor / Length);
}


//プレーヤーの状態変更関数
int Player::Stop(void)
{
	if(ma_sound_is_playing(&Sound) == true)//変更前と変更後が同じだったら変更しない
	{
		ma_sound_seek_to_second(&Sound, 0);
		ma_sound_stop(&Sound);
	}
	return 0;
}
int Player::Pause(void)
{
	if(ma_sound_is_playing(&Sound) == true)//変更前と変更後が同じだったら変更しない
	{
		ma_sound_stop(&Sound);
	}
	return 0;
}
int Player::Play(void)
{
	if(ma_sound_is_playing(&Sound) != true)//変更前と変更後が同じだったら変更しない
	{
		ma_sound_start(&Sound);
	}
	return 0;
}
