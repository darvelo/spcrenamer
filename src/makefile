CC=g++
LIB_GME=../extlib/game-music-emu-0.6.0/gme/*.cpp 
LIB_UNRAR=./libunrar.so
LIBS=$(LIB_GME) $(LIB_UNRAR)
LIBFLAGS=-std=c++11
LDFLAGS=-Wl,-rpath,'$ORIGIN' 

all:
	$(CC) main.cpp $(LIBS) $(LIBFLAGS) $(LDFLAGS)
