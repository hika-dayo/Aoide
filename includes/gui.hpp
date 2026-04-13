/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once
#include "utility.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#define SDL_VIDEO_DRIVER_WAYLAND 1//WaylandとX11の両対応
#define SDL_VIDEO_DRIVER_X11 1


bool isSDLInitialized(void);//SDLが初期化されているか
int GUIInit(void);//GUIを初期化
int GUIRelease(void);//SDLをリリース
bool ProcessMessage(void);//ウィンドウのメッセージを処理。
						  //この関数を定期的に呼びだす。成功の場合0を返します。エラー発生、若しくはウィンドウが閉じられたときには1を返します。
SDL_Surface* GetGUISurface(void);//ウィンドウのサーフェスを取得する。

enum UI_MODE
{
	MAINMENU,
	OPTION,
	CHOOSE_ARTIST,
	CHOOSE_ALBUM,
	CHOOSE_TITLE,
};
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
float GetFontSize(TTF_Font* Font);//フォントのサイズを取得
TTF_Font* InitFont(float Size, std::string Path);//Pathのフォントと引数のサイズの大きさに
int CleanWindow(void);//黒で画面を塗り潰す
int DrawText(TTF_Font* Font, const char* Str, Color FontColor, int X, int Y); //InitFontの返り値をFontにセットして、Strに文字列、FontColorに色、X、Y、を指定する
int DrawRect(int X, int Y, int W, int H, Color RectColor);//四角形を描画する(X、Y、横の長さ、縦の長さ)


class UI
{
	private:
		Config C;
		std::vector<Music> M;//音楽の情報を保持
		int ChoosingLine;
//		int ProcessKey(void);//キーを処理する(後で実装するつもり)
		Color FontColor;
		int ChoiceLine;
		TTF_Font* Font;
		bool TmpKey;
		std::vector<std::string> Texts;
	public:
		UI(std::vector<Music> &M);
		int Process(void);
};

class Image
{
	private:
		std::string Path;
		int Width;
		int Height;
		SDL_Surface* ImgData;
	public:
		Image(std::string Path);
		~Image(void);
		int GetWidth(void);
		int GetHeight(void);
		int DrawImage(int X, int Y, int Width = 0, int Height = 0);
};


