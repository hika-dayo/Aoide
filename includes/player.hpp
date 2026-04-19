/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once


#include <string>
#include <miniaudio/miniaudio.h>



class Player
{
	private:
		ma_engine *Engine;
		ma_sound Sound;
		//VLCの読み込み
		std::string FilePath;
		bool Error;		
	public:
		~Player();
		Player(const char* Path);
		const char* GetFilePath(void);
		bool isEnded(void);	//状態を取得
		bool isPlaying(void);
		bool isPaused(void);
		bool hasError(void);
		int Stop(void);//状態を変更する
		int Pause(void);
		int Play(void);
		int GetAudioLength(void);//音楽ファイルの長さをミリ秒で返す
		int GetAudioTime(void);//現在の再生位置をミリ秒で返す
		double GetAudioPosition(void);//0.0〜1.0までに正規化された、現在の再生位置
};
