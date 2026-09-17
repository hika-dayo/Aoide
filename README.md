# 概要  
  
本ソフトウェアは、MiniaudioとSDL等を利用して作成した音楽再生ソフトウェアです。現在は開発途中ですが、音楽再生用のUIの実装などを予定しています。 

## 機能
- 音楽の再生停止
- ウィンドウ表示  
- 音楽ファイル検索機能
- アーティスト/アルバム/曲のブラウズ
- プレイリスト&履歴

## 基本操作
- 上下矢印キー
項目を選択
- 左矢印キー
一番上まで戻る
- 右矢印キー
コントローラーを開く、又はメニューを開く
- エンターキー
項目を決定。音楽を選択した場合プレイリストに追加する。
- pキー/スペースキー
一時停止/再生
- fキー
曲送り
- bキー
曲戻し

## 使用したライブラリ・言語等
- C++
- make
- GCC
- automake
- miniaudio-0.11.25
- SDL3-3.2.28
- SDL3_ttf-3.2.2
- SDL3_image-3.2.2
- TagLib-2.2.1
## ビルド方法
このソフトウェアは以下のライブラリに依存します。
- miniaudio
- SDL3-devel
- SDL3_ttf
- SDL_image
- taglib
### ライブラリのセットアップ
- パッケージマネージャーからインストールする  
ArchLinuxの場合
```bash
$ sudo pacman -S sdl3 sdl3_image sdl3_ttf taglib miniaudio
```

- 自分でビルドする  
Archの場合
```bash
$ sudo pacman -S base-devel git pkg-config autoconf automake cmake
```
#### Miniaudioのビルド
```bash
$ cd aoide/libraries/miniaudio
$ tar xf miniaudio-0.11.25.tar.gz
$ cd miniaudio-0.11.25
$ ./bootstrap
$ ./configure
$ make
$ sudo make install
```
#### SDL3(ttf+image)のビルド
```bash
$ cd aoide/libraries/sdl3
$ tar xf SDL3-3.2.28.tar.gz
$ cd SDL3-3.2.28/
$ mkdir build
$ cd build/
$ cmake ..
$ make
$ sudo make install
```
#### SDL_imageのインストール
```bash
$ cd aoide/libraries/sdl3
$ tar xf SDL3_image-3.2.2.tar.gz
$ cd SDL3_image-3.2.2/
$ mkdir build
$ cd build/
$ cmake ..
$ make
$ sudo make install
```
#### SDL_ttfのインストール
```bash
$ cd aoide/libraries/sdl3
$ tar xf SDL3_ttf-3.2.2.tar.gz
$ cd SDL3_ttf-3.2.2/
$ mkdir build
$ cd build/
$ cmake ..
$ make
$ sudo make install
```
#### TagLibのインストール
```bash
$ cd aoide/libraries/Taglib
$ tar xf taglib-2.2.1.tar.gz
$ cd taglib-2.2.1/
$ mkdir build
$ cd build/
$ cmake ..
$ make
$ sudo make install
```

#### 本ソフトのインストール
```bash
$ cd aoide
$ ./configure
$ make
$ sudo make install
```

#### アンインストール
```bash
$ cd aoide/
$ sudo make uninstall
```

## 設定ファイル
設定ファイルは~/.config/aoide/aoide.confに生成されます。
($XDG_CONFIG_HOMEが設定されている場合はXDGが優先されます)  
## ライセンス

このソフトウェアはGNU General Public License v3.0 or laterの下でライセンスされています。

使用したライブラリはlibraries/ディレクトリに未改変のアーカイブとして収録されています。各ライブラリのライセンスは、それぞれのアーカイブとlicensesディレクトリ内に存在します。


### 使用したライブラリのライセンス  
このソフトウェアは以下のサードパーティー製ライブラリを利用しています。

- miniaudio -Copyright (C) David Reid
License: Public Domain or MIT No Attribution
miniaudioのソースコードは、以下のリンクから入手できます：    
[miniaudio公式のソースダウンロードリンク](https://github.com/mackron/miniaudio) 
詳細、全文はaoide/licenses/miniaudio-LICENSE又は、aoide/libraries/miniaudio/miniaudio-0.11.25.tar.gz 内にあるLICENSEを参照してください。 

- SDL3 -Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3のソースコードは以下のリンクから入手できます。:  
[SDL3公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL/releases/)  
詳細、全文はaoide/licenses/SDL3-LICENSE又は、aoide/libraries/sdl3/SDL3-3.2.28.tar.gz 内にあるLICENSE.txtを参照してください。 

- SDL3_ttf Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3_ttfのソースコードは以下のリンクから入手できます。:  
[SDL3_ttf公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL_ttf)  
詳細、全文はaoide/licenses/SDL_ttf-LICENSE又は、aoide/libraries/sdl3/SDL3_ttf-3.2.2.tar.gz 内にあるLICENSE.txtを参照してください。 

- SDL3_image Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3_imageのソースコードは以下のリンクから入手できます。:  
[SDL3_image公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL_image)
詳細、全文はaoide/licenses/SDL_image-LICENSE又は、aoide/libraries/sdl3/SDL3_image-3.2.2.tar.gz 内にあるLICENSE.txtを参照してください。 

- TagLib Copyright (C) 2003 Scott Wheeler <wheeler@kde.org> and other contributors
License: LGPLv2.1-only OR MPLv1.1
TagLibのソースコードは以下のリンクから入手できます。:  
[TagLib公式のソースダウンロードリンク](https://github.com/TagLib/TagLib)
詳細、全文はaoide/licenses/TagLib-LGPL、aoide/licenses/TagLib-MPL又は、aoide/libraries/taglib/taglib-2.2.1.tar.gz 内にあるCOPYING.LGPL、COPYING.MPLを参照してください。 

### 同梱されたフォントのライセンス
- このソフトウェアのアーカイブにはGNU Unifontが含まれています。GNU UnifontはSIL Open Font License1.1の下で配布されています。  
著作権はRoman Czyborra及びコントリビュータに帰属します。  
詳細、全文はlicense/OFL-1.1.txt又は[OFL本文へのリンク](https://openfontlicense.org/open-font-license-official-text/)を参照してください。
