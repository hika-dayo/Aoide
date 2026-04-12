# 概要  
  
本ソフトウェアは、LibVLCとSDL等を利用して作成した音楽再生ソフトウェアです。現在は開発途中ですが、音楽再生用のUIの実装などを予定しています。 
VLC上で再生可能な音楽ファイルならばそのほとんどが再生可能です。

## 機能
- 音楽の再生停止
- ウィンドウ表示  
- 音楽ファイル検索機能
## 予定している機能 
- ソフトを操作するためのUI

## 使用したライブラリ・言語等
- C++
- make
- GCC
- automake
- VLC-3.0.23
- SDL3-3.2.28
- SDL3_ttf-3.2.2
- SDL3_image-3.2.2
- TagLib-2.2.1
## ビルド方法
このソフトウェアはlibVLC(LGPLv2.1+)とSDL3(zlib)を利用しています。
このソフトウェアは以下のライブラリに依存します。
- libvlc-devel
- SDL3-devel
- taglib
### libVLCのセットアップ
- パッケージマネージャーからインストールする  
ArchLinuxの場合
```bash
$ sudo pacman -S vlc sdl3 sdl3_image sdl3_ttf taglib
```

- 自分でビルドする  
Archの場合
```bash
$ sudo pacman -S base-devel git pkg-config autoconf automake cmake
```
#### libVLCのビルド
```bash
$ cd Aoide/libraries/vlc
$ tar xf vlc-3.0.23.tar.xz
$ cd vlc-3.0.23
$ ./bootstrap
$ ./configure
$ make
$ sudo make install
```
#### SDL3(ttf+image)のビルド
```bash
$ cd Aoide/libraries/sdl3
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
$ cd Aoide/libraries/sdl3
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
$ cd Aoide/libraries/sdl3
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
$ cd Aoide/libraries/Taglib
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
$ cd Aoide
$ ./configure
$ make
$ sudo make install
```

#### アンインストール
```bash
$ cd Aoide/libraries/vlc/vlc-3.0.23
$ sudo make uninstall
$ cd Aoide/libraries/sdl3/SDL3-3.2.28
$ sudo make uninstall
$ cd Aoide/libraries/sdl3/SDL3_image-3.2.2
$ sudo make uninstall
$ cd Aoide/libraries/sdl3/SDL3_ttf-3.2.2
$ sudo make uninstall
$ cd Aoide/libraries/taglib/taglib-2.2.1/
$ sudo make uninstall
$ cd Aoide/
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

- libVLC -Copyright (C) 1998-2025 VLC authors and VideoLAN 
License: LGPLv2.1 or later  
libVLCのソースコードは、以下のリンクから入手できます：    
[VLC公式のソースダウンロードリンク](https://www.videolan.org/vlc/download-sources.html)  
詳細、全文はAoide/licenses/libVLC-COPYING.LIB又は、Aoide/libraries/vlc/vlc-3.0.23.tar.xz 内にあるCOPYING.LIBを参照してください。 

- SDL3 -Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3のソースコードは以下のリンクから入手できます。:  
[SDL3公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL/releases/)  
詳細、全文はAoide/licenses/SDL3-LICENSE又は、Aoide/libraries/sdl3/SDL3-3.2.28.tar.gz 内にあるLICENSE.txtを参照してください。 

- SDL3_ttf Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3_ttfのソースコードは以下のリンクから入手できます。:  
[SDL3_ttf公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL_ttf)  
詳細、全文はAoide/licenses/SDL_ttf-LICENSE又は、Aoide/libraries/sdl3/SDL3_ttf-3.2.2.tar.gz 内にあるLICENSE.txtを参照してください。 

- SDL3_image Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3_imageのソースコードは以下のリンクから入手できます。:  
[SDL3_image公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL_image)
詳細、全文はAoide/licenses/SDL_image-LICENSE又は、Aoide/libraries/sdl3/SDL3_image-3.2.2.tar.gz 内にあるLICENSE.txtを参照してください。 

- TagLib Copyright (C) 2003 Scott Wheeler <wheeler@kde.org> and other contributors
License: LGPLv2.1-only OR MPLv1.1
TagLibのソースコードは以下のリンクから入手できます。:  
[TagLib公式のソースダウンロードリンク](https://github.com/TagLib/TagLib)
詳細、全文はAoide/licenses/TagLib-LGPL、Aoide/licenses/TagLib-MPL又は、Aoide/libraries/taglib/taglib-2.2.1.tar.gz 内にあるCOPYING.LGPL、COPYING.MPLを参照してください。 

### 同梱されたフォントのライセンス
- このソフトウェアのアーカイブにはGNU Unifontが含まれています。GNU UnifontはSIL Open Font License1.1の下で配布されています。  
著作権はRoman Czyborra及びコントリビュータに帰属します。  
詳細、全文はlicense/OFL-1.1.txt又は[OFL本文へのリンク](https://openfontlicense.org/open-font-license-official-text/)を参照してください。
