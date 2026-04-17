/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/audio.hpp"
#include "../includes/utility.hpp"
#include <sstream>
#include <fstream>
#include <taglib/tstring.h>
#include <taglib/flacfile.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <miniaudio/miniaudio.h>

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
	std::string Artist = T->artist().to8Bit(true);
	std::string Album = T->album().to8Bit(true);
	std::string Title = T->title().to8Bit(true);
	int TrackNum = T->track();
	Music M(Path, Artist, Album, Title, TrackNum, ExtractFromFlacFile(Path, Artist.c_str(), Album.c_str()));
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
std::vector<std::string> GetSortedArtists(std::vector<Music> &M)
{
	std::vector<std::string> Artists;
	Artists.push_back((M[0].GetArtist()));
	for(int i = 0; i < M.size(); i++)
	{
		int n = 0;
		bool Repeat = false;
		for(n = 0; n < Artists.size(); n++)
		{
			if(Artists[n] == M[i].GetArtist())
			{
				Repeat = true;
			}
		}
		if(!Repeat)
		{
			Artists.push_back(M[i].GetArtist());
		}
	}
	std::sort(Artists.begin(),Artists.end());
	
	return Artists;
}
std::vector<std::string> GetSortedAlbums(std::vector<Music> &M, const std::string ArtistName)
{
	std::vector<std::string> Albums;
//	Albums.push_back((M[0].GetAlbum()));
	for(int i = 0; i < M.size(); i++)
	{
		int n = 0;
		bool Repeat = false;
		bool ArtistMatch = (ArtistName == "" || ArtistName == M[i].GetArtist());
		if(ArtistMatch)
		{
			for(n = 0; n < Albums.size(); n++)//重複していないかチェック
			{
				if(Albums[n] == M[i].GetAlbum())
				{
					Repeat = true;
				}
			}
			if(!Repeat)
			{
				Albums.push_back(M[i].GetAlbum());
			}
		}
	}
	std::sort(Albums.begin(),Albums.end());
	
	return Albums;
}
std::vector<std::string> GetSortedTitles(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName)
{
	std::vector<std::string> Titles;
//	Titles.push_back((M[0].GetTitle()));
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
				if(Titles[n] == M[i].GetTitle())
				{
					Repeat = true;
				}
			}
			if(!Repeat)
			{
				Titles.push_back(M[i].GetTitle());
			}
		}
	}
	std::sort(Titles.begin(),Titles.end());
	
	return Titles;
}

std::vector<std::string> GetSortedTrackNum(std::vector<Music> &M, const std::string ArtistName, const std::string AlbumName)
{
	std::vector<std::pair<int, std::string>> TitlesWithTrackNum;
	for(int i = 0; i < M.size(); i++)
	{
		int n = 0;
		bool Repeat = false;
		bool ArtistMatch = (ArtistName == "" || ArtistName == M[i].GetArtist());
		bool AlbumMatch = (AlbumName == "" || AlbumName == M[i].GetAlbum());
		if(ArtistMatch && AlbumMatch)
		{
			for(n = 0; n < TitlesWithTrackNum.size(); n++)
			{
				if(TitlesWithTrackNum[n].second == M[i].GetTitle())
				{
					Repeat = true;
				}
			}
			if(!Repeat)
			{
				TitlesWithTrackNum.push_back(std::make_pair(M[i].GetTrackNum(), M[i].GetTitle()));
			}
		}
	}
	std::sort(TitlesWithTrackNum.begin(), TitlesWithTrackNum.end());
	std::vector<std::string> Titles;
	for(int i = 0; i < TitlesWithTrackNum.size(); i++)
	{
		Titles.push_back(TitlesWithTrackNum[i].second);
	}
	return Titles;
}

Music::Music(std::string Path, std::string Artist, std::string Album, std::string Title, int TrackNum, std::string ArtworkPath)
{
	this->Artist = Artist;
	this->Title = Title;
	this->Album = Album;
	this->Path = Path;
	this->TrackNum = TrackNum;
	this->ArtworkPath = ArtworkPath;
	return;
}
std::string Music::GetAlbum(void)
{
	return Album;
}
std::string Music::GetArtist()
{
	return Artist;
}
std::string Music::GetTitle()
{
	return Title;
}
int Music::GetTrackNum()
{
	return TrackNum;
}
std::string Music::GetPath()
{
	return Path;
}
std::string Music::GetArtworkPath()
{
	return ArtworkPath;
}
