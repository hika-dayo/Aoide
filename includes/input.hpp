/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once
#include <SDL3/SDL_keycode.h>


enum KEY
{
	NO_INPUT,
	UP,
	DOWN,
	RIGHT,
	CHOOSEBEGIN,
	LEFT,
	ENTER,
	ESC,
	SPACE,
	PAUSE_PLAY,
	PLAY_FORWARD,
	PLAY_BACK
};

bool GetKey(KEY K);
int GetKeyCount(void);


class Input_Process
{
private:
	bool TmpRightKey;//右矢印キーが押されている間はtrue
	bool TmpKey;//方向キーが押されている間はtrue
	bool TmpEnter;//エンターキーが押されている間はtrue	
	bool TmpSpace;//スペースキーが押されている間はtrue	

	bool TmpFB;//曲を送る/戻すキーが押されている間はtrue	
	bool TmpPause;//一時停止キーが押されている間はtrue	
	
	bool Hold;//キーが長押しされているか
	int KeyIntervalCount;//長押しされるまでの時間のカウンタ
public:
	KEY ProcessKey(void);
	Input_Process(void);
	bool GetHoldStatus(void);
};

