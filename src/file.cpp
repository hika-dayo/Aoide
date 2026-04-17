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

/*//デフォルトの値設定
static std::string SEARCH_DIR = getenv("HOME");
//static std::string FONT_PATH = "";
static std::vector<std::string> SEARCH_EXTENTION=
{
	"flac",
	"mp3"
};*/
//static std::vector<std::string> MusicList;

Config::Config()
{
	if(!LoadConfig)
	{
		MakeConfAndCacheDir();
		if(!FileExists(ConfigPath.c_str()))
		{
			InitConf();	
		}
		ReadConf();
	
	}
	return;
}


/*int Config::WINDOW_WIDTH = 640;
int Config::WINDOW_HEIGHT = 480;
float Config::FONT_SIZE = 16;
bool Config::ReadConfig = false;*/

int Config::WINDOW_WIDTH = 640;
int Config::WINDOW_HEIGHT = 480;
float Config::FONT_SIZE = 16;
std::string Config::FONT_PATH = "";
std::string Config::SEARCH_DIR = getenv("HOME");
bool Config::LoadConfig = false;
std::string Config::ConfigPath = "";
std::string Config::CacheDir = "";
std::vector<std::string> Config::SEARCH_EXTENTION=
{
	"flac",
	"mp3"
};
static bool SubstitutedPath = 0;
bool FileExists(const char* Path)
{
	return std::filesystem::exists(Path);
}

int Config::MakeConfAndCacheDir(void)
{
	std::string ConfDir;
	if(getenv("XDG_CACHE_HOME") == NULL)
	{//特に指定が無いなら~/.config以下にaoideディレクトリを生成する
		CacheDir = getenv("HOME");
		if(CacheDir.empty())
		{
			ReportError("HOME環境変数が設定されていません。", CRITICAL_ERROR, __FILE__, __LINE__, __func__);
			exit(1);
		}
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
		ConfigPath = ConfDir + "/aoide.conf";
	}
	else	
	{
		ConfDir = getenv("XDG_CONFIG_HOME");
		ConfDir += "/aoide/";
		ConfigPath = ConfDir + "/aoide.conf";
	}
	std::filesystem::create_directory(ConfDir.c_str());
	std::filesystem::create_directory(CacheDir.c_str());
	SubstitutedPath = true;
	return 0;

}
int Config::InitConf(void)
{
	if(SubstitutedPath)
	{
		std::ofstream DefaultConf(ConfigPath);
		if(!DefaultConf)
		{
			ReportError("コンフィグファイルの新規作成に失敗しました", CRITICAL_ERROR, __FILE__, __LINE__);
			exit(1);
		}
		DefaultConf << "#ハッシュから始まる行はコメントになります\n";
		DefaultConf << "###検索するディレクトリ(デフォルトはホームディレクトリ)\n";
		DefaultConf << "#SearchDirectory=/home/hika/\n";
		DefaultConf << "\n";
		DefaultConf << "###ウィンドウの横幅(デフォルトは640px)\n";
		DefaultConf << "#WindowWidth=640\n";
		DefaultConf << "\n";
		DefaultConf << "#ウィンドウの縦幅(デフォルトは480px)\n";
		DefaultConf << "#WindowHeight=480\n";
		DefaultConf << "\n";
		DefaultConf << "#文字のサイズ(デフォルトは16)\n";
		DefaultConf << "#FontSize=16\n";
		DefaultConf << "\n";
		DefaultConf << "#音楽ファイルの拡張子(デフォルトはflac mp3)ピリオドの有無は影響しません\n";
		DefaultConf << "#SearchExtension=flac mp3\n";
		DefaultConf << "\n";
		DefaultConf << "#フォントファイルのパス(未設定の場合unifontが選択されます)\n";
		DefaultConf << "#FontPath=/usr/local/share/aoide/unifont-17.0.03.otf\n";
		DefaultConf.close();
	}	
	else
	{
		return -1;
	}

	return 0;
}


int Config::LoadWindowWidth(std::string Line, int LineNum)
{
	if(Line.find("WindowWidth") + 2 >= Line.length())
	{
		std::string Error = std::to_string(LineNum) + "行目の設定がされていません。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		return 1;
	}
	try{WINDOW_WIDTH = stoi(Line.substr(Line.find("=") + 1, Line.length()));}
	catch(const std::invalid_argument& e)
	{
		std::string Error = "設定(" + Line.substr(Line.find("=") + 1) + ")が数値以外の文字を含んでいます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
		return 1;
	}
	catch(const std::out_of_range& e)
	{
		std::string Error = "設定(" + Line.substr(Line.find("=") + 1)+ ")の値が大きすぎます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
		return 1;
	}
	if(WINDOW_WIDTH == 0)
	{
		std::string Error = std::to_string(LineNum) + "行目のウィンドウの横幅の設定がされていません。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
	}
	return 0;
}



int Config::LoadFontPath(std::string Line, int LineNum)
{
	FONT_PATH = Line.substr(Line.find("=") + 1, Line.length());
	if(FONT_PATH == "")
	{
		std::string Error = std::to_string(LineNum) + "行目フォントの設定がされていません。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
		return 1;
	}
	return 0;
}


int Config::LoadWindowHeight(std::string Line, int LineNum)
{
	if(Line.find("WindowHeight") + 2 >= Line.length())
	{
		std::string Error = std::to_string(LineNum) + "行目の設定がされていません。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		return 1;

	}
	try{WINDOW_HEIGHT = stoi(Line.substr(Line.find("=") + 1, Line.length()));}
	catch(const std::invalid_argument& e)
	{
		std::string Error = std::to_string(LineNum) + "行目の設定(" + Line.substr(Line.find("=") + 1) + ")が数値以外の文字を含んでいます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		WINDOW_HEIGHT= DEFAULT_WINDOW_HEIGHT;
		return 1;
	}
	catch(const std::out_of_range& e)
	{
		std::string Error = std::to_string(LineNum) + "行目の設定(" + Line.substr(Line.find("=") + 1) + ")の値が大きすぎます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
		return 1;
	}
	if(WINDOW_HEIGHT <= 0)
	{
		std::string Error = std::to_string(LineNum) + "行目の設定(" + Line.substr(Line.find("=") + 1) + ")の値が小さすぎます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
		WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
	}
	return 0;
}
int Config::LoadFontSize(std::string Line, int LineNum)
{
	if(Line.find("FontSize") + 2 >= Line.length())
	{
		std::string Error = std::to_string(LineNum) + "行目の設定がされていません。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		return 1;

	}
	try{FONT_SIZE = stof(Line.substr(Line.find("=") + 1, Line.length()));}
	catch(const std::invalid_argument& e)
	{
		std::string Error = std::to_string(LineNum) + "行目の設定(" + Line.substr(Line.find("=") + 1) + ")が数値以外の文字を含んでいます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		FONT_SIZE = DEFAULT_FONT_SIZE;
		return 1;
	}
	catch(const std::out_of_range& e)
	{
		std::string Error = std::to_string(LineNum) + "行目の設定(" + Line.substr(Line.find("=") + 1) + ")の値が大きすぎます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
		FONT_SIZE = DEFAULT_FONT_SIZE;
		return 1;
	}
		if(FONT_SIZE <= 0)
	{
		std::string Error = std::to_string(LineNum) + "行目の設定(" + Line.substr(Line.find("=") + 1) + ")の値が小さすぎます。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
		FONT_SIZE = DEFAULT_FONT_SIZE;
		return 1;
	}
	return 0;
}
int Config::LoadSearchExtension(std::string Line, int LineNum)
{
	if(Line.find("SearchExtension") + 1 == std::string::npos)
	{
		std::string Error = std::to_string(LineNum) + "行目の検索対象の拡張子の設定がされていません。";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);	
		return 1;
	}
	SEARCH_EXTENTION.clear();

	std::istringstream Option(Line.substr(Line.find("=") + 1, Line.length()));//istringstreamは空白改行で区切られたデータを一つずつ取り出せる
	std::string Tmp;
	while(Option >> Tmp)
	{
		SEARCH_EXTENTION.push_back(Tmp);
	}
	return 0;
}





std::vector<std::string> Config::GetSearchExtension(void)
{
	return SEARCH_EXTENTION;
}
std::string Config::GetCacheDir(void)
{
	return CacheDir;
}
std::string Config::GetFontPath(void)
{
	if(FONT_PATH != "")
	{
		return FONT_PATH;
	}
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
	return "";
}
int Config::GetWindowWidth(void)
{
	return WINDOW_WIDTH;
}
int Config::GetWindowHeight(void)
{
	return WINDOW_HEIGHT;
}
float Config::GetFontSize(void)
{
	return FONT_SIZE;
}


bool Config::DidConfigLoad(void)
{
	return LoadConfig;
}




int Config::ReadConf(void)
{	
		std::ifstream ConfFile(ConfigPath);
		if(!ConfFile)
		{
			ReportError("コンフィグファイルの読み込みに失敗しました。", CRITICAL_ERROR, __FILE__, __LINE__, __func__);
			exit(1);
		}
		std::string Line = "";
		int LineNum = 1;
		while(getline(ConfFile, Line))
		{
			if(Line[0] != '#' && Line[0] != '\n' && Line[0] != '\0')
			{
				if(Line.find("SearchDirectory=") != std::string::npos)
				{
					SEARCH_DIR = Line.substr(Line.find("=") + 1, Line.length());
					if(SEARCH_DIR == "")
					{
						std::string Error = std::to_string(LineNum) + "行目の検索対象のディレクトリの設定がされていません。";
						ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
						SEARCH_DIR = getenv("HOME");
					}						
				}
				else if(Line.find("WindowWidth") != std::string::npos)
					{
						LoadWindowWidth(Line, LineNum);

					}
					else if(Line.find("WindowHeight") != std::string::npos)
						{
							LoadWindowHeight(Line, LineNum);	

						}
						else if(Line.find("FontSize") != std::string::npos)
							{
								LoadFontSize(Line, LineNum);
							}
							else if(Line.find("FontPath") != std::string::npos)
								{
									LoadFontPath(Line, LineNum);
								}
								else if(Line.find("SearchExtension") != std::string::npos)
									{
										LoadSearchExtension(Line, LineNum);
									}
									else
									{
										std::string Error = std::to_string(LineNum) + "行目に不明な設定(" + Line + ")があります。";
										ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
	
									}
			}
			LineNum++;
		}
	LoadConfig = true;
	return 0;
}



bool DirExsists(const char* Dir)
{
	struct stat D;
	if(stat(Dir, &D) == 0 && S_ISDIR(D.st_mode))
	{
		return 1;
	}
	return 0;
}
std::string Config::GetSearchDir(void)
{	
	return SEARCH_DIR;
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
//	int FileMtime;
	Config C;
	while((Ent = fts_read(Fts))!= nullptr)
	{
		if(S_ISREG(Ent->fts_statp->st_mode))
		{
			CmpStr = Ent->fts_path;
			
	//		if(Ent->fts_statp->st_mtime)
	//		{
	//			std::cout << CmpStr << "\n" << Ent->fts_statp->st_mtime;
	//		}
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
