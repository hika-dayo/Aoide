/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/vlcinstance.hpp"
#include "../includes/utility.hpp"
#include <unistd.h>
#include <vlc/deprecated.h>
#include <vlc/libvlc.h>
#include <string>
#include <vlc/libvlc_events.h>
#include <vlc/libvlc_media.h>
#include <iostream>
#include <stdlib.h>
#include <vlc/libvlc_media_player.h>
#include <taglib/tag.h>
static libvlc_instance_t* VLCInstance;
bool Initialized = false;
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
	libvlc_release(VLCInstance);
	return 0;
}

const char* GetAudioMetaData(const char* Path, METADATA METAID)
{
	if(!FileExists(Path))
	{
		return 0;
	}
	libvlc_media_t* Media;
	Media = libvlc_media_new_path(GetVLCInstance(), Path);
   libvlc_media_parse(Media);
	const char* TmpStr = NULL;
	if(METAID == ARTIST)
	{

	TmpStr = libvlc_media_get_meta(Media, libvlc_meta_Artist);
	}

	if(METAID == TITLE)
	{

	TmpStr = libvlc_media_get_meta(Media, libvlc_meta_Title);
	}

	if(METAID == ALBUM)
	{

	TmpStr = libvlc_media_get_meta(Media, libvlc_meta_Album);
	}

	if(METAID == TRACKNUM)
	{

	TmpStr = libvlc_media_get_meta(Media, libvlc_meta_TrackNumber);
	}
	if(METAID == ARTWORK)
	{

	TmpStr = libvlc_media_get_meta(Media, libvlc_meta_ArtworkURL);
	}
		
	libvlc_media_release(Media);
	if(TmpStr == NULL)
	{
		return "";
	}
	return TmpStr;
}
