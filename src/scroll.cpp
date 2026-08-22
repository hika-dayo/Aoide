/*

	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/gui.hpp"
#include <iostream>
ScrollState::ScrollState(int DefScroll, int DefChoosingLine, int DefLength)
{
	Scroll = DefScroll;
	ChoosingLine = DefChoosingLine;

	ListLength = DefLength;
	if(DefLength <= GetCurrentLine())
	{
		GoEnd(DefLength);
	}
	return;
}

int ScrollState::ScrollUp(int Length, bool Hold)
{
	ListLength = Length;
	ChoosingLine++;
	ProcessScroll(Hold);
	return 0;
}
int ScrollState::ScrollDown(int Length, bool Hold)
{
	ListLength = Length;
	ChoosingLine--;
	ProcessScroll(Hold);
	return 0;
}
int ScrollState::GetChoosingLine(void)
{
	return ChoosingLine;
}
int ScrollState::GetCurrentLine(void)
{
	return Scroll + ChoosingLine;
}
int ScrollState::GetScroll(void)
{
	return Scroll;
}

int ScrollState::GoBegin(int Length)
{
	ChoosingLine = 0;
	Scroll = 0;
	ProcessScroll(false);
	return 0;
}
int ScrollState::GoEnd(int Length)
{
	Scroll = ListLength - (C.GetWindowHeight() / C.GetFontSize() / 3 * 2);

	if(Scroll < 0)
	{
		Scroll = 0;
	}
	ChoosingLine = ListLength - Scroll - 1;
	ProcessScroll(false);
	return 0;
}
int ScrollState::ProcessScroll(bool Hold)
{
	if(0 > ChoosingLine + Scroll)
	{
		if(Hold)//ホールドされてるなら止まる
		{
			Scroll = 0;
			ChoosingLine = 0;
		}
		else
		{
			GoEnd(ListLength);
//			Scroll = ListLength - (C.GetWindowHeight() / C.GetFontSize());
//	
//			if(Scroll < 0)
//			{
//				Scroll = 0;
//			}
//			ChoosingLine = ListLength - Scroll - 1;
	
		}
	}


	if(ListLength <= ChoosingLine + Scroll)//選択したところが範囲外なら
	{
		if(Hold)//ホールドされてるなら止まる
		{
			ChoosingLine--;
		}
		else
		{
			Scroll = 0;
			ChoosingLine = 0;

		}
	}

	if(Scroll == ListLength)
	{
		Scroll = ListLength - 1;

	}
	if(ChoosingLine > C.GetWindowHeight() / C.GetFontSize() / 3 * 2 - 1)
	{
		Scroll++;
		ChoosingLine--;
	}
	if(ChoosingLine < 0)
	{
		Scroll--;
		ChoosingLine++;
	}
	if(Scroll == -1)
	{
		Scroll = 0;
	}
	
	return 0;
}

