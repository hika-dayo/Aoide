/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/utility.hpp"
#include "../includes/player.hpp"
#include "../includes/vlcinstance.hpp"
#include "../includes/gui.hpp"
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	atexit(Release);
	ReadConf();
	GUIInit();
	InitVLCInstance();
	SearchDir(getenv("HOME"));
	RunMainLoop();
	exit(0);
}
void Release(void)
{
	ReleaseVLCInstance();
	GUIRelease();
}
