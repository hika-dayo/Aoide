/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/vlcinstance.hpp"
#include "../includes/player.hpp"
#include "../includes/utility.hpp"
#include "../includes/gui.hpp"

#include <SDL3/SDL_pixels.h>
#include <iostream>
#include <stdio.h>

int RunMainLoop(void)
{
	TTF_Font* Font = InitFont(16, GetFontPath());
	if(Font == 0)
	{
		ReportError("フォントの初期化に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
		exit(1);
	}
	Color FontColor = 0x00ffffff;
	while(1)
	{
		CleanWindow();
		if(ProcessMessage())
		{
			break;
		}
		
	//ここに処理を書く
	}
	return 0;
}
