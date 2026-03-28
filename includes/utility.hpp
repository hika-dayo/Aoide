/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#include <string>
enum ERROR_SCALE
{
	INFO_ERROR,
	GENERAL_ERROR,
	CRITICAL_ERROR
};
enum METADATA
{
	ARTIST,
	TITLE,
	ALBUM,
	TRACKNUM,
	ARTWORK,

};
void Release(void);//プログラムが終了したときにインスタンスを解放する
int ReportError(const char* Context, ERROR_SCALE SCALE, const char* FILE, int LINE, const char* FUNCNAME = "Unknown function");//エラー発生時に呼び出し 引数FILEには__FILE__、引数LINEには__LINE__を指定、引数FuncNameには__func__を指定する。
int RunMainLoop(void);//ループ処理
 
bool FileExists(const char* Path);//そのファイルが存在しているか確認する
int ReadConf(void);
const char* GetSearchDir(void);//コンフィグファイル内で設定された、検索対象のパスを返す
int SearchDir(const char *Path);
std::string GetAudioMetaData(const char* Path, METADATA METAID);
