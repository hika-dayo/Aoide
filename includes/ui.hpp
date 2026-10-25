/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once

#include "config.hpp"
#include "audio_engine.hpp"
#include "queue.hpp"
#include "gui.hpp"
#include "input.hpp"
#include <vector>
#include <memory>

class UI
{
private:
	std::unique_ptr<Player> P;

	Config C;
	
	PlaybackQueue List;
	
	std::vector<Image> Imgs;

	std::vector<int> PrevScroll;//前のスクロール位置の保存
	std::vector<int> PrevChoosingLine;//前のスクロール位置の保存
	
	std::unique_ptr<ScrollState> S;
	std::unique_ptr<ScrollState> HOQS;//HistoryOrQueueScrollStateの略
	Input_Process Inp;

	std::string ChoosingArtist;

	bool ControlMode;
	int HistoryOrQueueMode;
	bool First;
	int ProcessKey(void);//キーを処理する
	int ProcessChoice(bool End = true);//選択したときの処理を行う(最後尾に並ぶか、先頭に挿入するか)
	
	int ListItem(std::vector<Music> M, EVENT E, EVENT SetE);

	std::vector<Music> MList;//音楽の情報を保持
	
	std::vector<MenuItem> Object;//描画する内容
			
	UIRender Rend;	
	
	int ShuffleTitles(std::vector<Music> &ArgMusic);
	
	int Render(void);//描画処理

	std::vector<std::vector<MenuItem>> ObjectBuf;//進んだ場合にObjectをpushして戻る場合にpopしてObjectに代入する
public:
	UI(std::vector<Music> &MusicList);
	int Process(void);
	PlaybackQueue& GetQueue(void);

};
