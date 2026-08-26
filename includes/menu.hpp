/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "audio_engine.hpp"
#include "config.hpp"
#include <string>
#include <optional>

enum EVENT
{
	NONE,
	PLAY_MUSIC,
	PLAY_ALL,
	SHUFFLE_PLAY,
	EXIT,
	LIST_ARTISTS,
	LIST_ALBUMS,
	LIST_TITLES,
	LIST_TITLES_BY_TRACKNUM,
	BACK,
};

class MenuItem
{
	std::string Text;
	std::string Artist;
	std::string Album;
	std::string Title;
	std::string Path;
	std::string ArtworkPath;
	EVENT Event;
public:
	MenuItem(std::string Text,EVENT Event, std::optional<Music> M = std::nullopt);
	MenuItem(const MenuItem &Copy);//コピーコンストラクタ
	std::string GetText(void) const;
	EVENT GetEvent(void);
	std::string GetArtist(void);
	std::string GetAlbum(void);
	std::string GetTitle(void);
	std::string GetPath(void);
	std::string GetArtworkPath(void);
};

class ScrollState
{
private:
	Config C;
	int Scroll;//スクロール位置の保存
	int ListLength;//リストの長さ
	int ChoosingLine;//画面の何行目を選択しているか(0〜一画面に何行入るかまでの範囲しかならない)
	int ProcessScroll(bool Hold);
public:
	ScrollState(int DefScroll, int DefChoosingLine, int DefLength);
	int ScrollUp(int Length, bool Hold = false);
	int ScrollDown(int Length, bool Hold = false);
	int GoBegin(int Length);
	int GoEnd(int Length);
	int GetCurrentLine(void);
	int GetChoosingLine(void);
	int GetScroll(void);
};
