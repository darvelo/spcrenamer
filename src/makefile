CC=g++
LIB_GME=../lib/game-music-emu-0.6.0/gme/*.cpp
LIB_UNRAR=./libunrar.so
LIB_UV=./libuv.a
LIBS=$(LIB_GME) $(LIB_UNRAR) $(LIB_UV)
LIBFLAGS=-std=c++11
LDFLAGS=-Wl,-rpath,'$ORIGIN' -pthread
SOURCE=main.cpp Package.cpp unrar.cpp

all:
	$(CC) $(SOURCE) $(LIBS) $(LIBFLAGS) $(LDFLAGS)
