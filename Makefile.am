bin_PROGRAMS = aoide
aoide_SOURCES = src/main.cpp src/player.cpp src/audio_engine.cpp src/loop.cpp src/error.cpp src/gui.cpp src/sdl.cpp src/file.cpp src/config.cpp src/image.cpp src/toolkit.cpp src/playlist.cpp src/scroll.cpp src/ui.cpp src/input.cpp\
				includes/audio_engine.hpp includes/config.hpp includes/error.hpp includes/gui.hpp includes/input.hpp includes/loop.hpp includes/player.hpp 
aoide_LDADD = -lminiaudio -lSDL3 -lSDL3_ttf -lSDL3_image -ltag

EXTRA_DIST = libraries licenses
dist_pkgdata_DATA = assets/font/unifont-17.0.03.otf
dist_pkgdata_DATA = assets/graphics/playicon.png
dist_pkgdata_DATA = assets/graphics/stopicon.png
dist_pkgdata_DATA = assets/graphics/unknown.png

