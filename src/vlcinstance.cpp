/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/vlcinstance.hpp"
#include "../includes/utility.hpp"
#include <vlc/libvlc.h>
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
