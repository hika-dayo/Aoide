/*
	(C)Copyright 2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/input.hpp"
#include "../includes/gui.hpp"

KEY Input_Process::ProcessKey(void)
{
	KEY K = NO_INPUT;
	if(GetKey(PLAY_BACK))
	{
		if(TmpFB == false)
		{
			K = PLAY_BACK;
		}
		TmpFB = true;
	}
	else if(GetKey(PLAY_FORWARD))
	{
		if(TmpFB == false)
		{
			K = PLAY_FORWARD;
		}
		TmpFB = true;
	}
	else
	{
		TmpFB = false;
	}
	
	if(GetKey(PAUSE_PLAY))
	{
		if(TmpPause == false)
		{	
			K = PAUSE_PLAY;
		}
		TmpPause = true;
	}
	else
	{
		TmpPause= false;
	}

	if(GetKey(SPACE))
	{
		if(TmpSpace == false)
		{
			K = PAUSE_PLAY;
		}
//			ProcessChoice(false);
		TmpSpace = true;
	}
	else
	{
		TmpSpace = false;
	}
	if(GetKey(ENTER))
	{
		if(TmpEnter == false)
		{
			K = ENTER;
		}
//			ProcessChoice();
		TmpEnter = true;
	}
	else
	{
		TmpEnter = false;
	}
	
	if(GetKey(RIGHT))
	{
		if(TmpRightKey == false)
		{
			K = RIGHT;
/*			if(PlaylistMode == false)
			{
				PlaylistMode = true;
			}
			else
			{
				PlaylistMode = false;
			}*/
		}
		TmpRightKey = true;
	}
	else
	{
		TmpRightKey = false;
	}
	if(GetKey(LEFT))
	{
		K = LEFT;
//		S->GoBegin(Object.size());
	}
	if(GetKey(UP))
	{
		if(KeyIntervalCount > WAIT_TIME_FOR_HOLD)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > HOLD_DELAY && Hold))
		{
			K = UP;
//			S->ScrollDown(Object.size(), Hold);
			KeyIntervalCount = 0;
		}
		else
		{
			KeyIntervalCount++;
		}
		TmpKey = true;
	}
	else if(GetKey(DOWN))
	{
		if(KeyIntervalCount > WAIT_TIME_FOR_HOLD)
		{
			Hold = true;
		}
		if(TmpKey == false || (KeyIntervalCount > HOLD_DELAY && Hold))
		{
			K = DOWN;
//			S->ScrollUp(Object.size(), Hold);
			KeyIntervalCount = 0;
		}
		else
		{
			KeyIntervalCount++;
		}
		TmpKey = true;
	}
	else
	{
		KeyIntervalCount = 0;
		TmpKey = false;
		Hold = false;
	}
	return K; 
}

Input_Process::Input_Process(void)
{
	Hold = false;
	KeyIntervalCount = 0;
	TmpKey = false;
	TmpEnter = false;
	TmpSpace = false;
	return;
}

bool GetKey(KEY K)
{
	auto Keys = SDL_GetKeyboardState(NULL);
	if(K == UP)
	{
		return Keys[SDL_SCANCODE_UP];
	}
	if(K == DOWN)
	{
		return Keys[SDL_SCANCODE_DOWN];
	}
	if(K == RIGHT)
	{
		return Keys[SDL_SCANCODE_RIGHT];
	}
	if(K == LEFT)
	{
		return Keys[SDL_SCANCODE_LEFT];
	}
	if(K == ENTER)
	{
		return Keys[SDL_SCANCODE_RETURN];
	}
	if(K == ESC)
	{
		return Keys[SDL_SCANCODE_ESCAPE];
	}
	if(K == SPACE)
	{
		return Keys[SDL_SCANCODE_SPACE];
	}
	if(K == PLAY_FORWARD)
	{
		return Keys[SDL_SCANCODE_F];
	}
	if(K == PLAY_BACK)
	{
		return Keys[SDL_SCANCODE_B];
	}
	if(K == PAUSE_PLAY)
	{
		return Keys[SDL_SCANCODE_P];
	}
	return false;
}
