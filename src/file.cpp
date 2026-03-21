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
#include <fts.h>
#include <regex>

static std::string ConfigPath;
static bool SubstitutedPath = 0;
bool isFileExists(const char* Path)
{
	return std::filesystem::exists(Path);
}
int MakeConfDir(void)
{
	std::string ConfDir;
	if(getenv("XDG_CONFIG_HOME") == NULL)
	{//特に指定が無いなら~/.config以下にaoideディレクトリを生成する
		ConfDir = getenv("HOME");
		if(ConfDir.c_str() == NULL)
		{
			ReportError("HOMEが設定されていません", CRITICAL_ERROR, __FILE__,__LINE__);
			exit(1);
		}
		ConfDir += "/.config/aoide/";
		ConfigPath = ConfDir + "aoide.conf";
	}
	else	
	{
		ConfDir = getenv("XDG_CONFIG_HOME");
		ConfDir += "/aoide/";
		ConfigPath = ConfDir + "aoide.conf";
	}
	std::filesystem::create_directory(ConfDir.c_str());
	SubstitutedPath = true;
	return 0;

}
int InitConf(void)
{
	if(SubstitutedPath)
	{
		std::ofstream DefaultConf(ConfigPath);
		DefaultConf << "SearchDirectory=" << getenv("HOME") << "/music" << std::endl;
		DefaultConf << "WindowWidth=640" << std::endl;
		DefaultConf << "WindowHeight=480" << std::endl;
		DefaultConf << "SearchExtension=flac mp3" << std::endl;
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
		
	}
	else
	{
		InitConf();
		
	}
	return 0;
}

const char* GetFontPath()
{
	if(isFileExists("/usr/local/share/aoide/unifont-17.0.03.otf"))
	{
		return "/usr/local/share/aoide/unifont-17.0.03.otf";
	}
	else
	{
		if(isFileExists("../assets/font/unifont-17.0.03.otf"))
		{
			return "../assets/font/unifont-17.0.03.otf";
		}
		else
		{
			ReportError("Fontファイルが存在しません。", CRITICAL_ERROR, __FILE__, __LINE__);
			exit(1);
		}

	}
}
int GetWindow_Width(void)
{
	return 480;
}
int GetWindow_Height(void)
{
	return 320;
}


int CheckExtention(const std::string Str, const std::string Extention)
{
	if(Str.size() < Extention.size())
	{
		return 0;
	}
	if(Str.compare(Str.size() - Extention.size(),Extention.size(), Extention) != 0)//ファイルの最後拡張子分を比較
	{
		return 0;
	}
	return 1;
}
int SearchDir(const char *Path)
{
	char* const Paths[] = {const_cast<char*>(Path), nullptr};
	FTS* Fts = fts_open(Paths, FTS_PHYSICAL| FTS_NOCHDIR, nullptr);
	if(Fts == nullptr)
	{
		return -1;
	}
	std::string CmpStr;
	FTSENT* Ent = nullptr;
	while((Ent = fts_read(Fts))!= nullptr)
	{
		CmpStr = Ent->fts_path;
		if(CheckExtention(CmpStr, ".flac") || CheckExtention(CmpStr, ".mp3"))
		{
			std::cout << CmpStr << std::endl;
		}
	}
	return 0;
}
