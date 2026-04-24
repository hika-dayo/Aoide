/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */
#pragma once
#include <string>
#include <vector>
#include <miniaudio/miniaudio.h>


int InitMiniaudio(void);//miniaudioを初期化
ma_engine *GetMiniaudioEngine(void);//miniaudioのインスタンスを返す
int ReleaseMiniaudioEngine(void);//VLCの解放
bool isMiniaudioInitialized(void);//miniaudioが初期化されているか



enum METADATA
{
	ARTIST,
	TITLE,
	ALBUM,
	TRACKNUM,
	ARTWORK,
	DISCNUM,
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
	int DiscNum = 1;
public:
	Music(std::string Path, std::string Artist = "", std::string Album = "", std::string Title = "",int TrackNum = 0, std::string ArtworkPath = "", int DiscNum = 1);
	const std::string GetArtist(void);
	const std::string GetTitle(void);
	const std::string GetAlbum(void);
	const std::string GetPath(void);
	const std::string GetArtworkPath(void);
	const int GetTrackNum(void);
	const int GetDiscNum(void);
	bool isThisInitialized(void);
};

Music GetAudioMetaData(const char* Path);//音楽ファイルのメタデータを返す

int SoundInitFromFile(const char* Path, ma_sound* S);//音楽を取得する関数

std::string GetTitlePath(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName, const std::string TitleName);
std::vector<Music> SearchDir(const char *Path);//ディレクトリを検索する

const std::vector<Music> GetSortedArtists(std::vector<Music> &M);
const std::vector<Music> GetSortedAlbums(std::vector<Music> &M, const std::string ArtistName = "");
const std::vector<Music> GetSortedTitles(std::vector<Music> &M, const std::string ArtistName = "", const std::string AlbumName = "");
const std::vector<Music> GetSortedTrackNum(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName);
std::string ExtractFromFlacFile(const char* Path, const char* ArtistName, const char* AlbumName);
//std::vector<std::string> GetSortedTitles(std::vector<Music> M);
