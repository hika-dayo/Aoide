/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "header/utity.hpp"
#include <iostream>
#include <time.h>
int ReportError(const char* Context, ERROR_SCALE SCALE, const char* FILE, int LINE)
{
	time_t NowTime;
	time(&NowTime);
	std::cerr << NowTime << ":";
	std::cerr << FILE << ":" << LINE << ":";
	if(SCALE == INFO_ERROR)
	{
		//情報エラーの場合Contextだけを出力する
	}
	if(SCALE == GENERAL_ERROR)
	{
		std::cerr << "エラーが発生しました！";
	}
	if(SCALE == CRITICAL_ERROR)
	{
		std::cerr << "重大なエラーです。プログラムを終了します。";
		
	}
	std::cerr << ":" << Context;

	return 0;
}
