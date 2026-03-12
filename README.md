概要  
  
本ソフトウェアは、LibVLCを利用して作成したまだ未完成の音楽再生ソフトウェアです。 
音楽を再生する機能が実装されています。 
VLC上で再生可能な音楽ファイルならばそのほとんどが再生可能です。
音楽の情報を表示する、音楽再生用のファイラなどの機能を追加する予定です。 
使用したライブラリ・言語等
- C++
- make
- VLC-3.0.23
- GCC
- automake
- SDL3-3.2.28
- SDL3_ttf-3.2.2
- SDL3_image-3.4.0
機能
- 楽曲の再生
- 楽曲の停止
- 音楽情報の表示
- 音楽再生用ファイラ

ビルド方法
このソフトウェアはlibVLC(LGPLv2.1+)とSDL3(zlib)を利用しています。
このソフトウェアは以下のライブラリに依存します。
- libvlc-devel
- SDL3-devel

libVLCのセットアップ
パッケージマネージャーからインストールする。
Debianの場合
```bash
$ sudo apt-get install libvlc-dev
```
Archの場合
```bash
$ sudo pacman -S base-devel git pkg-config autoconf automake
```
- 他のディストロについては[UnixCompile](https://wiki.videolan.org/UnixCompile)を参照してください
libVLCのビルド
```bash
$ cd /libraries/sdl3
$ tar xf vlc-3.0.23.tar.xz
$ cd vlc-3.0.23
$ ./bootstrap
$ ./configure
$ make
$ sudo make install
```

SDL3のビルド
```bash
$ cd /libraries/sdl3
$ tar xf SDL3-3.2.28.tar.gz
$ cd SDL3-3.2.28/
$ cmake .
$ make
$ sudo make install
```
本ソフトのビルド
```bash
$ cd /
$ ./configure
$ make
```
- インストールする場合
```bash
$ cd /
$ make install
```

- アンインストール
```bash
$ cd /libraries/vlc/vlc-3.0.23
$ sudo make uninstall
$ cd /libraries/sdl3/SDL3-3.2.28
$ sudo make uninstall
$ cd /
$ sudo make uninstall
```



ライセンス

このソフトウェアはGNU General Public License v3.0 or laterの下でライセンスされています。

使用したライブラリはlibraries/ディレクトリに未改変のアーカイブとして収録されています。各ライブラリのライセンスは、それぞれのアーカイブとlicensesディレクトリ内に存在します。


使用したライブラリのライセンス  
このソフトウェアは以下のサードパーティー製ライブラリを利用しています。

- libVLC -Copyright (C) 1998-2025 VLC authors and VideoLAN 
License: LGPLv2.1 or later  
libVLCのソースコードは、以下のリンクから入手できます：    
[VLC公式のソースダウンロードリンク](https://www.videolan.org/vlc/download-sources.html)  
詳細、全文は/licenses/libVLC-COPYING.LIB又は、/libraries/vlc/vlc-3.0.23.tar.xz 内にあるCOPYING.LIBを参照してください。 

- SDL3 -Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3のソースコードは以下のリンクから入手できます。:  
[SDL3公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL/releases/)  
詳細、全文は/licenses/SDL3-LICENSE又は、/libraries/sdl3/SDL3-3.2.28.tar.gz 内にあるLICENSE.txtを参照してください。 

- SDL3_ttf Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3_ttfのソースコードは以下のリンクから入手できます。:  
[SDL3_ttf公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL_ttf)  
詳細、全文は/licenses/SDL_ttf-LICENSE又は、/libraries/sdl3/SDL3_ttf-3.2.2.tar.gz 内にあるLICENSE.txtを参照してください。 

- SDL3_image Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org> 
License: zlib License  
SDL3_imageのソースコードは以下のリンクから入手できます。:  
[SDL3_image公式のソースダウンロードリンク](https://github.com/libsdl-org/SDL_image)
詳細、全文は/licenses/SDL_image-LICENSE又は、/libraries/sdl3/SDL3_image-3.4.0.tar.gz 内にあるLICENSE.txtを参照してください。 


