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
#include "input.hpp"
#include "playlist.hpp"
#include "menu.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <optional>
#include <string>
#include <vector>
#include <optional>
#include <memory>

#define SDL_VIDEO_DRIVER_WAYLAND 1//WaylandとX11の両対応
#define SDL_VIDEO_DRIVER_X11 1

const int WAIT_TIME_FOR_HOLD = 5;
const int HOLD_DELAY = 0;


bool isSDLInitialized(void);//SDLが初期化されているか
int GUIInit(void);//GUIを初期化
int GUIRelease(void);//SDLをリリース
bool ProcessMessage(bool Hold);//ウィンドウのメッセージを処理。
						  //この関数を定期的に呼びだす必要がある。成功の場合0を返します。エラー発生、若しくはウィンドウが閉じられたときには1を返します。
SDL_Surface* GetGUISurface(void);//ウィンドウのサーフェスを取得する。
SDL_Window* GetWindow(void);//ウィンドウを得る
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

int CalcResizedWidth(int W, int H, int MaxSize);//長辺がMaxSizeになるようにリサイズして横幅を返す
int CalcResizedHeight(int W, int H, int MaxSize);//長辺がMaxSizeになるようにリサイズして縦幅を返す


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





class UIRender
{
public:
	
	std::vector<Image> ArtworkList;
	Image UnknownArtwork;
	int DrawMenu(int ChoosingLine, int Scroll, const std::vector<MenuItem>& Object);
	UIRender(std::vector<Music> &MusicList);
	int DrawControler(Playlist &List);
private:
	Color FontColor;
	TTF_Font* Font;
	std::vector<std::string> Texts;//テキスト
};

class UI
{
private:
	std::unique_ptr<Player> P;

	Config C;
	
	Playlist List;
	
	std::vector<Image> Imgs;

	std::vector<int> PrevScroll;//前のスクロール位置の保存
	std::vector<int> PrevChoosingLine;//前のスクロール位置の保存
	
	std::unique_ptr<ScrollState> S;
	Input_Process Inp;

	std::string ChoosingArtist;

	bool ControlMode;
	bool First;
	int ProcessKey(void);//キーを処理する
	int ProcessChoice(bool End = true);//選択したときの処理を行う(最後尾に並ぶか、先頭に挿入するか)
	
	int ListItem(std::vector<Music> M, EVENT E, EVENT SetE);

	std::vector<Music> MList;//音楽の情報を保持
	
	std::vector<MenuItem> Object;//描画する内容
			
	UIRender Rend;	
	
	int ShuffleTitles(std::vector<Music> &ArgMusic);
	
	int Render(void);//描画処理

	std::vector<std::vector<MenuItem>> ObjectBuf;//進んだ場合にObjectをpushして戻る場合にpopしてObjectに代入する
public:
	UI(std::vector<Music> &MusicList);
	int Process(void);

};
