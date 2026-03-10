/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#define SDL_VIDEO_DRIVER_WAYLAND 1//WaylandとX11の両対応
#define SDL_VIDEO_DRIVER_X11 1


const std::string FontPath = "/home/hika/Downloads/unifont-17.0.03.otf";//フォントファイルの場所

const int WINDOW_RES_X = 1920;//解像度をここで設定
const int WINDOW_RES_Y = 1080;
int GUIInit(void);//SDL_Windowのポインタのアドレスを引数に設定する
int GUIRelease(void);//
bool ProcessMessage(void);//ウィンドウのメッセージを処理。
						  //この関数を定期的に呼びだす必要があります。目安はフレームの更新の時です。成功の場合0を返します。エラー発生、若しくはウィンドウが閉じられたときには1を返します。
SDL_Renderer* GetGUIRenderer(void);//レンダラーを取得する。
SDL_Surface* GetGUISurface(void);//ウィンドウのサーフェスを取得する。


//色ゾーン
enum COLOR
{
	RED,
	GREEN,
	BLUE,
};

typedef unsigned int Color;//符号無し32bit整数(00000000~FFFFFFFF)の範囲(アルファチャンネル有り)で色を表現する

SDL_Color ToSDLPixel(Color Arg);//符号無し32bit整数で表現された色をSDL用の表現に変換する

//終わり

TTF_Font* InitFont(int Size, std::string Path);//Pathのフォントと引数のサイズの大きさに

int DrawText(TTF_Font* Font, const char* Str, Color FontColor, int X, int Y); //InitFontの返り値をFontにセットして、Strに文字列、FontColorに色、X、Y、を指定する
