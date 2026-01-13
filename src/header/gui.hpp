/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once
#include <SDL3/SDL.h>

const int WINDOW_RES_X = 480;//解像度をここで設定
const int WINDOW_RES_Y = 320;
int GUIInit(void);//SDL_Windowのポインタのアドレスを引数に設定する
int GUIRelease(void);//
bool ProcessMessage(void);//ウィンドウのメッセージを処理。
						  //この関数を定期的に呼びだす必要があります。目安はフレームの更新の時です。成功の場合0を返します。エラー発生、若しくはウィンドウが閉じられたときには1を返します。
SDL_Renderer* GetGUIRenderer(void);//レンダラーを取得する。


//色ゾーン
enum COLOR
{
	RED,
	GREEN,
	BLUE,
};

typedef unsigned int Color;//符号無し32bit整数(000000~FFFFFF)の範囲で色を表現する
int GetPrimaryColors(COLOR Color);
int SetRenderColor(Color AugColor);//レンダラーの色を変更する
Color SetRenderColor(void);//レンダラーの色を変更する
