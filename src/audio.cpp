/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/vlcinstance.hpp"
#include "../includes/utility.hpp"
#include <sstream>
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
	if(Initialized == true)
	{
		return 1;
	}
	VLCInstance = libvlc_new(0,NULL);
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

std::string GetAudioMetaData(const char* Path, METADATA METAID)
{
	if(!FileExists(Path))
	{
		return 0;
	}
	TagLib::FileRef F(Path);
	if(F.isNull() && !F.tag())
	{
		return 0;
	}
	TagLib::Tag *T = F.tag();
	std::string TmpStr = "";
	if(METAID == ARTIST)
	{

		TagLib::String Artist = T->artist();
		TmpStr = Artist.to8Bit(true);
	}
	
	if(METAID == TITLE)
	{

	TagLib::String Title = T->title();
	TmpStr = Title.to8Bit(true);
	
	}

	if(METAID == ALBUM)
	{

	TagLib::String Album = T->album();
	TmpStr = Album.to8Bit(true);
	}

	if(METAID == TRACKNUM)
	{
	int t = T->track();
	std::ostringstream I;
	I << t;
	TmpStr = I.str();
	}
	if(METAID == ARTWORK)
	{

	TagLib::String Album = T->artist();
	}
		
	return TmpStr;
}
