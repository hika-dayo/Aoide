/*
	(C)Copyright 2025-2026 Hika h1ka.net 
	   This file is part of Aoide.

    Aoide is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    Aoide is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Aoide. If not, see <https://www.gnu.org/licenses/>. 
  */

#pragma once

#include "config.hpp"
#include "audio_engine.hpp"
#include "player.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <optional>
#include <string>
#include <vector>
#include <optional>
#include <utility>
#define SDL_VIDEO_DRIVER_WAYLAND 1//WaylandとX11の両対応
#define SDL_VIDEO_DRIVER_X11 1


bool isSDLInitialized(void);//SDLが初期化されているか
int GUIInit(void);//GUIを初期化
int GUIRelease(void);//SDLをリリース
bool ProcessMessage(void);//ウィンドウのメッセージを処理。
						  //この関数を定期的に呼びだす必要がある。成功の場合0を返します。エラー発生、若しくはウィンドウが閉じられたときには1を返します。
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

enum EVENT
{
	NOTHING,
	PLAY_MUSIC,
	EXIT,
	LIST_ARTISTS,
	LIST_ALBUMS,
	LIST_TITLES,
	BACK,
};
typedef unsigned int Color;//符号無し32bit整数(00000000~FFFFFFFF)の範囲(アルファチャンネル有り)で色を表現する

SDL_Color ToSDLPixel(Color Arg);//符号無し32bit整数で表現された色をSDL用の表現に変換する

//終わり
float GetFontSize(TTF_Font* Font);//フォントのサイズを取得
TTF_Font* InitFont(float Size, std::string Path);//Pathのフォントと引数のサイズの大きさに
int CleanWindow(void);//黒で画面を塗り潰す
int DrawText(TTF_Font* Font, const char* Str, Color FontColor, int X, int Y); //InitFontの返り値をFontにセットして、Strに文字列、FontColorに色、X、Y、を指定する
int DrawRect(int X, int Y, int W, int H, Color RectColor);//四角形を描画する(X、Y、横の長さ、縦の長さ)

class Image
{
	private:
		std::string Path;
		int Width;
		int Height;
		SDL_Surface* ImgData;
	public:
		Image(std::string ImagePath);
		Image(const Image &Copy);//コピーコンストラクタ
		~Image(void);
		int ChangeImage(std::string ImagePath);//コンストラクタ
		int GetWidth(void);
		int GetHeight(void);
		int DrawImage(int X, int Y, int Width = 0, int Height = 0);
		std::string GetPath(void);
};

class MenuItem
{
	std::string Text;
	std::string Artist;
	std::string Album;
	std::string Title;
	std::string Path;
	EVENT Event;
public:
	MenuItem(std::string Text,EVENT Event, std::optional<Music> M = std::nullopt);
	std::string GetText(void);
	EVENT GetEvent(void);
	std::string GetArtist(void);
	std::string GetAlbum(void);
	std::string GetTitle(void);
	std::string GetPath(void);
};

class UI
{
	private:
		Config C;
		Player *P;
		UI_MODE Mode;
		UI_MODE PrevMode;//前のモード
		int Scroll;//スクロール位置の保存
		int PrevScroll;//前のスクロール位置の保存
		int PrevChoosingLine;//前のスクロール位置の保存
		int ChoosingLine;//画面の何行目を選択しているか(0〜一画面に何行入るかまでの範囲しかならない)
		
		bool Hold;//キーが長押しされているか
		int KeyIntervalCount;//長押しされるまでの時間のカウンタ
		bool TmpKey;//方向キーが押されている間はtrue
		bool TmpEnter;//エンターキーが押されている間はtrue	

		int ProcessKey(void);//キーを処理する
		int ProcessScroll(void);
		int ProcessChoice(void);//選択したときの処理を行う

		std::vector<Music> MList;//音楽の情報を保持
		std::vector<Image> ArtworkList;
		Color FontColor;
		TTF_Font* Font;
		std::vector<std::string> Texts;//テキスト
		std::vector<MenuItem> Object;//描画する内容
	public:
		UI(std::vector<Music> &MusicLists);
		int Process(void);
};

