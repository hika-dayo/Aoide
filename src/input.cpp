/*
	(C)Copyright 2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/input.hpp"
#include "../includes/gui.hpp"

INPUT_CODE Input::ProcessKey(void)
{
	INPUT_CODE In = NO_INPUT;
	if(GetKey(PLAY_BACK))
	{
		if(TmpFB == false)
		{
//			Event = PLAY_PREV;
//			List.PlayPrev();
		}
		TmpFB = true;
	}
	else if(GetKey(PLAY_FORWARD))
	{
		if(TmpFB == false)
		{
//			Event = PLAY_NEXT;
//			List.PlayNext();
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
//			Event = PLAY_PAUSE;
//			List.Pause();
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
//			Event = ADD_HEAD;
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
//			Event = ADD_LAST;
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
	return In;
}

Input::Input(void)
{
	Hold = false;
	KeyIntervalCount = 0;
	TmpKey = false;
	TmpEnter = false;
	TmpSpace = false;
	return;
}
