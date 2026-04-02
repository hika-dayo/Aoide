/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/audio.hpp"
#include "../includes/player.hpp"
#include "../includes/utility.hpp"
#include "../includes/gui.hpp"

#include <SDL3/SDL_pixels.h>
#include <iostream>
#include <stdio.h>

int RunMainLoop(void)
{
	
	Config C;
	std::vector<Music> M = SearchDir(C.GetSearchDir().c_str());
	GUIInit();
	TTF_Font* Font = InitFont(C.GetFontSize(), C.GetFontPath());
	if(Font == 0)
	{
		ReportError("フォントの初期化に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
		exit(1);
	}
	Color FontColor = 0x00ffffff;
	std::vector<std::string> ArtistsList = GetSortedArtists(M);
	std::vector<std::string> Menu;
	Menu.push_back("Artists");
	Menu.push_back("Albums");
	Menu.push_back("Songs");
	Menu.push_back("Options");
	Menu.push_back("Exit");
	UI_MODE UI = MAINMENU;
	int Index = 2;	
	int i = DrawLines(GetSortedTitles(M), 0, Font, FontColor, 0);
	bool KeyDown = false;
	while(1)
	{


		if(KeyDown == false)
		{
			if(GetKey(UP))
			{
				Index--;
				KeyDown = true;
			}
			if(GetKey(DOWN))
			{
				Index++;
				KeyDown = true;
			}
			if(GetKey(ENTER))
			{
				if(Menu[Index] == "Artists")
				{
					UI = CHOOSE_ARTIST;

				}
				KeyDown = true;
			}
		}
		else
		{
			if(GetKeyCount() == 0)
			{
				KeyDown = false;
			}
		}
		if(GetKey(ESC))
		{
			break;
		}



		CleanWindow();
		if(UI == MAINMENU)
		{
			i = DrawLines(Menu, Index, Font, FontColor, i);
		}
		if(UI == CHOOSE_ARTIST)
		{
			i = DrawLines(ArtistsList, Index, Font, FontColor, i);
		}
		if(ProcessMessage())
		{
			break;
		}
	//ここに処理を書く
	}
	return 0;
}
