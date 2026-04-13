/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */
#pragma once
#include <SDL3/SDL_keycode.h>
#include <string>
#include <vector>
#include "audio.hpp"
const int DEFAULT_WINDOW_WIDTH = 640;
const int DEFAULT_WINDOW_HEIGHT = 480;
const int DEFAULT_FONT_SIZE = 16;

enum KEY
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ENTER,
	ESC,
	SPACE,
};

enum ERROR_SCALE
{
	INFO_ERROR,
	GENERAL_ERROR,
	CRITICAL_ERROR
};
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




void Release(void);//プログラムが終了したときにインスタンスを解放する
int ReportError(const char* Context, ERROR_SCALE SCALE, const char* FILE, int LINE, const char* FUNCNAME = "Unknown function");//エラー発生時に呼び出し 引数FILEには__FILE__、引数LINEには__LINE__を指定、引数FuncNameには__func__を指定する。
int RunMainLoop(void);//ループ処理
 
bool FileExists(const char* Path);//そのファイルが存在しているか確認する
bool DirExsists(const char* Dir);

bool GetKey(KEY K);
int GetKeyCount(void);
