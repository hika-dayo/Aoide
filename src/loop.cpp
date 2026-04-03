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
#include <SDL3/SDL_gpu.h>
#include <thread>
#include <SDL3/SDL_pixels.h>
#include <iostream>
#include <stdio.h>




int RunMainLoop(void)
{	
	Config C;
	GUIInit();
	TTF_Font* Font = InitFont(C.GetFontSize(), C.GetFontPath());
	if(Font == 0)
	{
		ReportError("フォントの初期化に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
		exit(1);
	}
	Color FontColor = 0x00ffffff;
	std::vector<Music> M = SearchDir(C.GetSearchDir().c_str());
	std::vector<std::string> ArtistsList = GetSortedArtists(M);
	std::vector<std::string> AlbumsList = GetSortedAlbums(M);
	std::vector<std::string> TitlesList = GetSortedTitles(M);
	std::string ArtistName = "";
	std::string AlbumsName = "";
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
	Player *P = nullptr;
	bool PAllocate = false;
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
				if(Menu[Index] == "Artists" && UI == MAINMENU)
				{
					UI = CHOOSE_ARTIST;
				}
				else
				{
					if(UI == CHOOSE_ARTIST) {
						AlbumsList = GetSortedAlbums(M, ArtistsList[Index]);
						ArtistName = ArtistsList[Index];
						UI = CHOOSE_ALBUM;	
					}
					else
						{
						if(UI == CHOOSE_ALBUM)
						{
							AlbumsName = AlbumsList[Index];
							TitlesList = GetSortedTrackNum(M, ArtistName, AlbumsName);
							
							UI = CHOOSE_TITLE;
						}
						else
						{
							if(UI == CHOOSE_TITLE)
							{
								if(PAllocate == true)
								{
									P->Stop();
									delete P;
								}
//								std::cout << GetTitlePath(M, ArtistName, AlbumsName, TitlesList[Index]) << std::endl;
								P = new Player(GetTitlePath(M, ArtistName, AlbumsName, TitlesList[Index]).c_str());
								PAllocate = true;
								P->Play();
							}
						}
						}
					}

							}
							
				KeyDown = true;
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
		if(PAllocate == true)
		{
			if(P->isEnded())
			{
				delete P;
				PAllocate = false;
			}

		}

		CleanWindow();
		if(UI == MAINMENU)
		{
			i = DrawLines(Menu, Index, Font, FontColor, i);
		}
		if(UI == CHOOSE_ARTIST)
		{
			i = DrawLines(ArtistsList, Index, Font, FontColor, i ,"<");
		}
		if(UI == CHOOSE_ALBUM)
		{
			i = DrawLines(AlbumsList, Index, Font, FontColor, i, "<");
		}
		if(UI == CHOOSE_TITLE)
		{
			i = DrawLines(TitlesList, Index, Font, FontColor, i, "<");
		}
		if(ProcessMessage())
		{
			break;
		}
	//ここに処理を書く
	}
		if(PAllocate == true)
		{
			delete P;
			PAllocate = false;
		}
	return 0;
}
