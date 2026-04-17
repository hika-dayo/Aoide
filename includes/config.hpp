/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once
#include <string>
#include <vector>

const int DEFAULT_WINDOW_WIDTH = 640;
const int DEFAULT_WINDOW_HEIGHT = 480;
const int DEFAULT_FONT_SIZE = 16;
class Config
{
private:
	static int WINDOW_WIDTH;// = 640;
	static int WINDOW_HEIGHT;// = 480;
	static float FONT_SIZE;// = 16;
	static std::string FONT_PATH;
	static std::vector<std::string> SEARCH_EXTENTION;
	static std::string SEARCH_DIR;//$HOME
	static bool LoadConfig;//false
	static std::string ConfigPath;//$HOME/.config/aoide/aoide.conf
	static std::string CacheDir;//$HOME/.cache/aoide/searched
	int ReadConf(void);//コンフィグファイルを読む
	int MakeConfAndCacheDir(void);
	int InitConf(void);//コンフィグファイルの初期化
	int LoadWindowWidth(std::string Line, int LineNum);//文字列からオプションを分離する
	int LoadWindowHeight(std::string Line, int LineNum);
	int LoadFontSize(std::string Line, int LineNum);
	int LoadFontPath(std::string Line, int LineNum);
	int LoadSearchExtension(std::string Line, int LineNum);
public:
	Config();
	std::string GetCacheDir(void);//キャッシュがあるディレクトリのパス
	std::string GetConfigPath(void);//コンフィグファイルのパス
	std::string GetFontPath(void);//フォントのパス
	std::string GetSearchDir(void);//検索対象のディレクトリ
	std::vector<std::string>GetSearchExtension();//検索対象の拡張子
	int GetWindowWidth(void);//ウィンドウサイズ(横)
	int GetWindowHeight(void);//ウィンドウサイズ(縦)
	float GetFontSize(void);//フォントのサイズ
	bool DidConfigLoad(void);//コンフィグファイルが読み込まれたか(インストラクタで読み込むからほとんど使う用が無い)
};
