/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/audio_engine.hpp"
#include "../includes/file.hpp"
#include "../includes/config.hpp"
#include <fstream>
#include <taglib/tstring.h>
#include <taglib/flacfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <miniaudio/miniaudio.h>
#include <algorithm>
#include <ranges>
#include <vector>

static ma_engine Engine;
static bool Initialized = false;
int InitMiniaudio(void)
{
	if(Initialized == true)
	{
		return 1;
	}
	ma_result Result = ma_engine_init(NULL, &Engine);
	Initialized = true;
	return 0;
}
bool isMiniaudioInitialized(void)
{
	return Initialized;
}
ma_engine *GetMiniaudioEngine(void)
{
	return &Engine;
}
int SoundInitFromFile(const char* Path, ma_sound* S)
{
	ma_engine *E = GetMiniaudioEngine();
	return -(ma_sound_init_from_file(E, Path, 0, NULL, NULL, S) != MA_SUCCESS);
}
int ReleaseSound(ma_sound* S)
{
	ma_sound_uninit(S);
	return 0;
}
int ReleaseMiniaudioEngine(void)
{
	if(isMiniaudioInitialized())
	{
		ma_engine_uninit(&Engine);
		Initialized = false;
	}
	return 0;
}

Music GetAudioMetaData(const char* Path)
{
	if(!FileExists(Path))
	{
		Music M("", "", "", "", 0);
		return M;
	}
	if(DirExsists(Path))
	{
		Music M("", "", "", "", 0);
		return M;
	}
	TagLib::FileRef F(Path);
	if(F.isNull() || !F.tag())
	{
		Music M("", "", "", "", 0);
		return M;
	}
	TagLib::Tag *T = F.tag();
	if(NULL == T)
	{
		Music M("", "", "", "", 0);
		return M;
	}
	TagLib::PropertyMap Props = T->properties();
	TagLib::StringList DiscNumtmp = Props["DISCNUMBER"];
	std::string Artist = T->artist().to8Bit(true);
	std::string Album = T->album().to8Bit(true);
	std::string Title = T->title().to8Bit(true);
	int TrackNum = T->track();	
	int IntDiscNum = 1;

	if(DiscNumtmp.isEmpty())
	{
		IntDiscNum = 1;	
	}
	else
	{
		IntDiscNum = std::stoi(DiscNumtmp[0].to8Bit(true));
	}
	Music M(Path, Artist, Album, Title, TrackNum, ExtractFromFlacFile(Path, Artist.c_str(), Album.c_str()), IntDiscNum);
	return M;
		
}


std::string ExtractFromFlacFile(const char* Path, const char* ArtistName, const char* AlbumName)
{
	TagLib::FileRef F(Path);
	TagLib::Tag* Tag = F.tag();	
	std::string ArtworkPath = "";
	if(Tag != NULL)
	{
		TagLib::File* CoverFile = F.file();
		TagLib::FLAC::File* FileFlac = dynamic_cast<TagLib::FLAC::File*>(CoverFile);
		if(FileFlac != NULL)
		{
			auto Pic = FileFlac->pictureList();
			if(!Pic.isEmpty())
			{
				Config C;
				ArtworkPath = C.GetCacheDir() + "/" + ArtistName + " - " + AlbumName + ".jpg";
				if(!FileExists(ArtworkPath.c_str()))
				{
					
					std::ofstream Out(ArtworkPath, std::ios::binary);
					TagLib::ByteVector Data = Pic.front()->data();
					Out.write(Data.data(), Data.size());
					Out.close();
				}
			}
		}
	}
	return ArtworkPath;
}


std::string GetTitlePath(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName, const std::string TitleName)
{
	for(int i = 0; i < M.size(); i++)
	{
		if(M[i].GetArtist() == ArtistName)
		{
			if(M[i].GetAlbum() == AlbumName)
			{
				if(M[i].GetTitle() == TitleName)
				{
					return M[i].GetPath();
				}
			}
		}
	}
	return "";
}
const std::vector<Music> GetSortedArtists(std::vector<Music> &M)
{
	std::vector<Music> Artists;
	for(int i = 0; i < M.size(); i++)//Musicのリスト文検索
	{
		int n = 0;
		bool Repeat = false;
		for(n = 0; n < Artists.size(); n++)//重複を防ぐ
		{
			if(Artists[n].GetArtist() == M[i].GetArtist())//重複してるならRepeat
			{
				Repeat = true;
			}
		}
		if(!Repeat)//重複してないなら
		{
			Music Tmp("", M[i].GetArtist());
			Artists.push_back(Tmp);
		}
	}
	std::ranges::sort(Artists, {}, &Music::GetArtist);
	
	return Artists;
}

const std::vector<Music> GetSortedAlbums(std::vector<Music> &M, const std::string ArtistName)
{
	std::vector<Music> Albums;
	for(int i = 0; i < M.size(); i++)//Musicのリスト文検索
	{
		int n = 0;
		bool Repeat = false;
		bool ArtistMatch = (ArtistName == "" || ArtistName == M[i].GetArtist());//ArtistNameが空なら、全てのアーティスト
		if(ArtistMatch)
		{
		for(n = 0; n < Albums.size(); n++)//重複を防ぐ
		{
			if(Albums[n].GetAlbum() == M[i].GetAlbum())//重複してるならRepeat
			{
				Repeat = true;
			}
		}
		if(!Repeat)//重複してないなら
		{
			Music Tmp("", M[i].GetArtist(), M[i].GetAlbum());
			Albums.push_back(Tmp);
		}

		}
	}
	std::ranges::sort(Albums, {}, &Music::GetAlbum);
	
	return Albums;
}
const std::vector<Music> GetSortedTitles(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName)
{
	std::vector<Music> Titles;
	for(int i = 0; i < M.size(); i++)
	{

		int n = 0;
		bool Repeat = false;
		bool ArtistMatch = (ArtistName == "" || ArtistName == M[i].GetArtist());
		bool AlbumMatch = (AlbumName == "" || AlbumName == M[i].GetAlbum());
		if(ArtistMatch && AlbumMatch)
		{
			for(n = 0; n < Titles.size(); n++)
			{
				if(Titles[n].GetTitle() == M[i].GetTitle())
				{
					Repeat = true;
				}
			}
			if(!Repeat)
			{
				Music Tmp("", M[i].GetAlbum(), M[i].GetArtist(), M[i].GetTitle());
				Titles.push_back(Tmp);
			}
		}
	}
	std::ranges::sort(Titles, {}, &Music::GetTitle);
	
	return Titles;
}

const std::vector<Music> GetSortedTrackNum(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName)
{
	std::vector<std::vector<Music>> Titles;
	for(int i = 0; i < M.size(); i++)
	{
		int n = 0;
		bool Repeat = false;
		bool ArtistMatch = (ArtistName == "" || ArtistName == M[i].GetArtist());
		bool AlbumMatch = (AlbumName == "" || AlbumName == M[i].GetAlbum());
		if(ArtistMatch && AlbumMatch)
		{
			for(n = 0; n < Titles.size(); n++)
			{
				if(Titles[n][M[i].GetDiscNum() - 1].GetTitle() == M[i].GetTitle())
				{
					Repeat = true;
				}
			}
			if(!Repeat)
			{
				Titles[M[i].GetDiscNum() - 1].push_back(M[i]);
			}
		}

	}
	std::vector<Music> Tmp;
	for(int i = 0; i < Titles.size(); i++)
	{
		std::ranges::sort(Titles[i], {}, &Music::GetTrackNum);
	}
	return Titles[0];//後でディスク番号順にソートする
}

Music::Music(std::string Path, std::string Artist, std::string Album, std::string Title, int TrackNum, std::string ArtworkPath, int DiscNum)
{
	this->Artist = Artist;
	this->Title = Title;
	this->Album = Album;
	this->Path = Path;
	this->TrackNum = TrackNum;
	this->ArtworkPath = ArtworkPath;
	this->DiscNum = DiscNum;
	return;
}
const std::string Music::GetAlbum(void)
{
	return Album;
}
const std::string Music::GetArtist()
{
	return Artist;
}
const std::string Music::GetTitle()
{
	return Title;
}
const int Music::GetTrackNum()
{
	return TrackNum;
}
const std::string Music::GetPath()
{
	return Path;
}
const std::string Music::GetArtworkPath()
{
	return ArtworkPath;
}
const int Music::GetDiscNum()
{
	return DiscNum;
}
