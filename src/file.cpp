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
#include <vector>

//デフォルトの値設定
static std::string SEARCH_DIR = getenv("HOME");
static std::string FONT_PATH = "";
static std::vector<std::string> SEARCH_EXTENTION=
{
	"flac",
	"mp3"
};
static int WINDOW_WIDTH = 640;
static int WINDOW_HEIGHT = 480;
static float FONT_SIZE = 16;



static bool ReadConfig = false;
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

int ReadConf(void)
{	
	MakeConfAndCacheDir();
	if(FileExists(ConfigPath.c_str()))
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
					}						
				}
				else
				{
					if(Line.find("WindowWidth") != std::string::npos)
					{
						try{WINDOW_WIDTH = stoi(Line.substr(Line.find("=") + 1, Line.length()));}
						catch(const std::invalid_argument& e)
						{
							std::string Error = "stoiに失敗しました。設定(" + Line.substr(Line.find("=") + 1) + ")が数値以外の文字を含んでいます。";
							ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
							WINDOW_WIDTH = 640;
						}
						catch(const std::out_of_range& e)
						{
							std::string Error = "stoiに失敗しました。設定(" + Line.substr(Line.find("=") + 1)+ ")の値が大きすぎます。";
							ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
							WINDOW_WIDTH = 640;
						}
						if(WINDOW_WIDTH == 0)
						{
							std::string Error = std::to_string(LineNum) + "行目のウィンドウの横幅の設定がされていません。";
							ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
						}

					}
					else
					{

						if(Line.find("WindowHeight") != std::string::npos)
						{
							try{WINDOW_HEIGHT = stoi(Line.substr(Line.find("=") + 1, Line.length()));}
							catch(const std::invalid_argument& e)
							{
									std::string Error = "stoiに失敗しました。設定(" + Line.substr(Line.find("=") + 1) + ")が数値以外の文字を含んでいます。";
									ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
								WINDOW_HEIGHT = 480;
							}
							catch(const std::out_of_range& e)
							{
								std::string Error = "stoiに失敗しました。設定(" + Line.substr(Line.find("=") + 1)+ ")の値が大きすぎます。";
								ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
								WINDOW_HEIGHT = 480;
							}
							if(WINDOW_HEIGHT == 0)
							{
								std::string Error = std::to_string(LineNum) + "行目のウィンドウの高さの設定がされていません。";
								ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
							}
	
						}
						else
						{
							if(Line.find("FontSize") != std::string::npos)
							{
								try{FONT_SIZE = stof(Line.substr(Line.find("=") + 1, Line.length()));}
								catch(const std::invalid_argument& e)
								{
									std::string Error = "stoiに失敗しました。設定(" + Line.substr(Line.find("=") + 1) + ")が数値以外の文字を含んでいます。";
									ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
									FONT_SIZE = 16;
								}
								catch(const std::out_of_range& e)
								{
									std::string Error = "stoiに失敗しました。設定(" + Line.substr(Line.find("=") + 1) + ")の値が大きすぎます。";
									ReportError(Error.c_str(), GENERAL_ERROR, __FILE__,__LINE__,__func__);
									WINDOW_HEIGHT = 16;
								}
									if(WINDOW_WIDTH == 0)
								{
									std::string Error = std::to_string(LineNum) + "行目のウィンドウの横幅の設定がされていません。";
									ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
								}
							}

							else
							{
								if(Line.find("FontPath") != std::string::npos)
								{
										FONT_PATH = Line.substr(Line.find("=") + 1, Line.length());
										if(FONT_PATH == "")
										{
											std::string Error = std::to_string(LineNum) + "行目フォントの設定がされていません。";
											ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);
										}
								}
								else
								{
								if(Line.find("SearchExtension") != std::string::npos)
								{
										if(Line.find("SearchExtension") + 1 == std::string::npos)
										{
											std::string Error = std::to_string(LineNum) + "行目の検索対象の拡張子の設定がされていません。";
											ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);	
										}
//										std::string Op = Line.substr(Line.find("=") + 1, Line.length());
										for(int i = 0; i <= SEARCH_EXTENTION.size(); i++)//初期化されていたデータを全部popして捨てる
										{
											SEARCH_EXTENTION.pop_back();
										}

										std::istringstream Option(Line.substr(Line.find("=") + 1, Line.length()));//istringstreamは空白改行で区切られたデータを一つずつ取り出せる
										std::string Tmp;
										while(Option >> Tmp)
										{
											SEARCH_EXTENTION.push_back(Tmp);
										}
								}
								else
								{
									std::string Error = std::to_string(LineNum) + "行目に不明な設定(" + Line + ")があります。";
									ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);

								}

								}
							}

						}
					}
				}
			}
			LineNum++;
		}

	}
	else
	{
		InitConf();	
	}
	ReadConfig = true;
	return 0;
}


std::vector<std::string> GetSearchExtension(void)
{
	if(!ReadConfig)
	{
		ReadConf();
	}
	return SEARCH_EXTENTION;
}

const char* GetFontPath()
{
	if(!ReadConfig)
	{
		ReadConf();
	}
	if(FONT_PATH != "")
	{
		return FONT_PATH.c_str();
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
const char* GetSearchDir(void)
{	
	if(!ReadConfig)
	{
		ReadConf();
	}
	if(!DirExsists(SEARCH_DIR.c_str()))
	{
		std::string Error = SEARCH_DIR + "は存在しないディレクトリです";
		ReportError(Error.c_str(), GENERAL_ERROR, __FILE__, __LINE__, __func__);

	}

	return SEARCH_DIR.c_str();
}

int GetWindow_Width(void)
{
	if(!ReadConfig)
	{
		ReadConf();
	}
	return WINDOW_WIDTH;
}
float GetSetFontSize(void)
{
	if(!ReadConfig)
	{
		ReadConf();
	}
	return FONT_SIZE;
}
int GetWindow_Height(void)
{
	if(!ReadConfig)
	{
		ReadConf();
	}
	return WINDOW_HEIGHT;
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
	std::ofstream Cache(CacheDir + "searched");
	if(!Cache)
	{
		exit(1);
	}
	while((Ent = fts_read(Fts))!= nullptr)
	{
		if(S_ISREG(Ent->fts_statp->st_mode))
		{
			CmpStr = Ent->fts_path;
			
	//		if(Ent->fts_statp->st_mtime)
	//		{
	//			std::cout << CmpStr << "\n" << Ent->fts_statp->st_mtime;
	//		}
			for(int i = 0; i < GetSearchExtension().size(); i++)
			{
				if(CheckExtension(CmpStr, GetSearchExtension()[i]))
				{
						std::string Title = GetAudioMetaData(CmpStr.c_str(), TITLE);
						std::string Album = GetAudioMetaData(CmpStr.c_str(), ALBUM);
						std::string Artist = GetAudioMetaData(CmpStr.c_str(), ARTIST);
						std::string TrackNum = GetAudioMetaData(CmpStr.c_str(), TRACKNUM);
						Cache << CmpStr << '\n' << Title << '\n'<< Album << '\n' << Artist << '\n' << TrackNum << std::endl;
				}
			}			
		}
	}
	Cache.close();
	fts_close(Fts);
	return 0;
}
