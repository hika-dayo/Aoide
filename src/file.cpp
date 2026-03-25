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
static std::string CacheDir;
static bool SubstitutedPath = 0;
bool FileExists(const char* Path)
{
	return std::filesystem::exists(Path);
}
int MakeConfAndCacheDir(void)
{
	std::string ConfDir;
	if(getenv("XDG_CACHE_HOME") == NULL)
	{//特に指定が無いなら~/.config以下にaoideディレクトリを生成する
		CacheDir = getenv("HOME");
		if(ConfDir.c_str() == NULL)
		{
			ReportError("HOMEが設定されていません", CRITICAL_ERROR, __FILE__,__LINE__);
			exit(1);
		}
		CacheDir += "/.cache/aoide/";
	}
	else	
	{
		CacheDir = getenv("XDG_CACHE_HOME");
		CacheDir += "/aoide/";
	}
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
	std::filesystem::create_directory(CacheDir.c_str());
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
	
	MakeConfAndCacheDir();
	if(FileExists(ConfigPath.c_str()))
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
	if(FileExists("/usr/local/share/aoide/unifont-17.0.03.otf"))
	{
		return "/usr/local/share/aoide/unifont-17.0.03.otf";
	}
	else
	{
		if(FileExists("assets/font/unifont-17.0.03.otf"))
		{
			return "assets/font/unifont-17.0.03.otf";
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



int GetMtime(const char* Path)
{
	struct stat FileStatus;
	if(stat(Path, &FileStatus) < 0)
	{
		return 0;
	}
	return FileStatus.st_mtime;
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
//	int FileMtime;
	int CacheMtime;
	std::ofstream Cache(CacheDir + "searched", std::ios::app);
	if(!Cache)
	{
		exit(1);
	}
	while((Ent = fts_read(Fts))!= nullptr)
	{
		CmpStr = Ent->fts_path;
		
//		if(Ent->fts_statp->st_mtime)
//		{
//			std::cout << CmpStr << "\n" << Ent->fts_statp->st_mtime;
//		}
		if(CheckExtention(CmpStr, ".flac") || CheckExtention(CmpStr, ".mp3"))
		{
//			std::cout << "aa";
			std::string Title = GetAudioMetaData(CmpStr.c_str(), TITLE);
			std::string Album = GetAudioMetaData(CmpStr.c_str(), ALBUM);
			std::string Artist = GetAudioMetaData(CmpStr.c_str(), ARTIST);
			std::string TrackNum = GetAudioMetaData(CmpStr.c_str(), TRACKNUM);
			Cache << Title << '\n'<< Album << '\n' << Artist << '\n' << TrackNum << std::endl;
		}
	}
	Cache.close();
	fts_close(Fts);
	return 0;
}
