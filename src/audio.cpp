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
#include <taglib/tstring.h>
#include <unistd.h>
#include <stdio.h>
#include <vlc/deprecated.h>
#include <vlc/libvlc.h>
#include <string>
#include <vlc/libvlc_events.h>
#include <vlc/libvlc_media.h>
#include <iostream>
#include <stdlib.h>
#include <vlc/libvlc_media_player.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>

static libvlc_instance_t* VLCInstance;
static bool Initialized = false;
int InitVLCInstance(void)
{
	std::cout << "aa";
	if(Initialized == true)
	{
		return 1;
	}
//	const char* Args[] = {"--no-video"};
	VLCInstance = libvlc_new(0, NULL);
	Initialized = true;
	return 0;
}
bool isLibVLCInitialized(void)
{
	return Initialized;
}
libvlc_instance_t* GetVLCInstance(void)
{
	return VLCInstance;
}
int ReleaseVLCInstance(void)
{
	if(isLibVLCInitialized())
	{
	libvlc_release(VLCInstance);
	return 0;
	}
	return 1;
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
	Music M(T->artist().to8Bit(true), T->album().to8Bit(true), T->title().to8Bit(true), Path, T->track());
	return M;
		
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

Music::Music(std::string Artist, std::string Album, std::string Title, std::string Path, int TrackNum)
{
	this->Artist = Artist;
	this->Title = Title;
	this->Album = Album;
	this->Path = Path;
	this->TrackNum = TrackNum;
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
