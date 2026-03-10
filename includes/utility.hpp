/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

enum ERROR_SCALE
{
	INFO_ERROR,
	GENERAL_ERROR,
	CRITICAL_ERROR
};

int ReportError(const char* Context, ERROR_SCALE SCALE, const char* FILE, int LINE);//エラー発生時に呼び出し 引数FILEには__FILE__、引数LINEには__LINE__を指定
int RunMainLoop(void);//ループ処理
 
bool isFileExists(const char* Path);//そのファイルが存在しているか確認する
int ReadConf(void);
