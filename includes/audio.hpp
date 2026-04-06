/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */
#pragma once
#include "utility.hpp"
#include <vlc/vlc.h>
int InitVLCInstance(void);//VLCの初期化
libvlc_instance_t* GetVLCInstance(void);//VLCインスタンスを返す
int ReleaseVLCInstance(void);//VLCの解放
bool isLibVLCInitialized(void);//VLCが初期化されているか
enum METADATA
{
	ARTIST,
	TITLE,
	ALBUM,
	TRACKNUM,
	ARTWORK,

};

class Music
{
private:
	bool Initialized = false;
	std::string Artist = "";
	std::string Title = "";
	std::string Path = "";
	std::string Album = "";
	std::string ArtworkPath = "";
	int TrackNum = 0;
public:
	Music(std::string Path, std::string Artist = "", std::string Album = "", std::string Title = "",int TrackNum = 0, std::string ArtworkPath = "");
	std::string GetArtist(void);
	std::string GetTitle(void);
	std::string GetAlbum(void);
	std::string GetPath(void);
	std::string GetArtworkPath(void);
	int GetTrackNum(void);
	bool isThisInitialized(void);
};

Music GetAudioMetaData(const char* Path);//音楽ファイルのメタデータを返す


std::string GetTitlePath(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName, const std::string TitleName);
std::vector<Music> SearchDir(const char *Path);//ディレクトリを検索する

std::vector<std::string> GetSortedArtists(std::vector<Music> &M);
std::vector<std::string> GetSortedAlbums(std::vector<Music> &M, const std::string ArtistName = "");
std::vector<std::string> GetSortedTitles(std::vector<Music> &M, const std::string ArtistName = "", const std::string AlbumName = "");
std::vector<std::string> GetSortedTrackNum(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName);
//std::vector<std::string> GetSortedTitles(std::vector<Music> M);
