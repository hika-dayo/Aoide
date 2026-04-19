/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "../includes/config.hpp"
#include "../includes/file.hpp"
#include "../includes/error.hpp"
#include "../includes/audio_engine.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fts.h>
#include <vector>




bool DirExsists(const char* Dir)
{
	struct stat D;
	if(stat(Dir, &D) == 0 && S_ISDIR(D.st_mode))
	{
		return 1;
	}
	return 0;
}

int CheckExtension(const std::string Str, const std::string Extention)
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


std::vector<Music>SearchDir(const char *Path)
{
	std::vector<Music> MList;
	char* const Paths[] = {const_cast<char*>(Path), nullptr};
	FTS* Fts = fts_open(Paths, FTS_PHYSICAL| FTS_NOCHDIR, nullptr);
	if(Fts == nullptr)
	{
		return MList;
	}
	std::string CmpStr;
	FTSENT* Ent = nullptr;
	Config C;
	while((Ent = fts_read(Fts))!= nullptr)
	{
		if(S_ISREG(Ent->fts_statp->st_mode))
		{
			CmpStr = Ent->fts_path;
			
			for(int i = 0; i < C.GetSearchExtension().size(); i++)
			{
				if(CheckExtension(CmpStr, C.GetSearchExtension()[i]))
				{
					Music Data = GetAudioMetaData(CmpStr.c_str());
					MList.push_back(Data);
				}
			}			
		}
	}
	fts_close(Fts);
	return MList;
}
