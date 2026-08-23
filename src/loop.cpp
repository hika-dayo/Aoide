/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/audio_engine.hpp"
#include "../includes/gui.hpp"
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_timer.h>



int RunMainLoop(void)
{
	GUIInit();
	Config C;
	std::vector<Music> M = SearchDir(C.GetSearchDir().c_str());
	UI UIobj(M);
	CleanWindow();
	while(1)
	{
//		SDL_Delay(14);
		UIobj.Process();
		if(ProcessMessage())
		{
			break;
		}

	}
	return 0;
}
