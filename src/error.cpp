/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/utility.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../includes/gui.hpp"
#include <SDL3_ttf/SDL_ttf.h>
int ReportError(const char* Context, ERROR_SCALE SCALE, const char* FILE, int LINE, const char* FUNCNAME)
{
	time_t NowTime;
	time(&NowTime);
	struct tm * Tmp = localtime(&NowTime);
	std::cerr << Tmp->tm_hour << "-" << Tmp->tm_min << "-" << Tmp->tm_sec << ":";
	std::cerr << FILE << ":" << LINE << ":" << FUNCNAME << "()"<<":";
	if(SCALE == INFO_ERROR)
	{	
		//情報だけstd::errに流す
	}
	if(SCALE == GENERAL_ERROR)
	{
		std::cerr << "エラーが発生しました！";
		
	}
	if(SCALE == CRITICAL_ERROR)
	{
		std::cerr << "重大なエラーです。";
				
	}
	std::cerr << ":" << Context << std::endl;
	return 0;
}
