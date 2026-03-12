/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/utility.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/stat.h>

static std::string ConfigPath;
static bool SubstitutedPath = 0;
bool isFileExists(const char* Path)
{
	return std::filesystem::is_regular_file(Path);
}
int MakeConfDir(void)
{
	std::string ConfDir;
	if(getenv("XDG_CONFIG_HOME") == NULL)
	{//特に指定が無いなら~/.config以下にaoideディレクトリを生成する
		ConfDir = getenv("HOME");
		ConfDir += "/.config/aoide";
		ConfigPath = ConfDir + "aoide.conf";
	}
	else	
	{
		ConfDir = getenv("XDG_CONFIG_HOME");
		ConfDir += "/aoide";
		ConfigPath = ConfDir + "aoide.conf";
	}
	mkdir(ConfDir.c_str(), 0755);
	SubstitutedPath = true;
	return 0;

}
int InitConf(void)
{
	if(SubstitutedPath)
	{
		std::ofstream DefaultConf(ConfigPath);
		DefaultConf << "SearchDirectory=~/" << std::endl;
		DefaultConf << "WindowWidth=640" << std::endl;
		DefaultConf << "WindowHeight=480" << std::endl;
		DefaultConf.close();
	}	
	else
	{
		return -1;
	}

	return 0;
}

int ReadConf(void)
{
	MakeConfDir();
	if(isFileExists(ConfigPath.c_str()))
	{
		//こっから読む処理
	}
	else
	{
		InitConf();
		//無いからコンフィグファイルを新規で作る
		
	}
	return 0;
}
