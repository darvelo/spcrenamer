CC=g++
COMPILED_LIBS=./lib/compiled
LIB_GME=./lib/game-music-emu-0.6.0/gme/*.cpp
LIB_UNRAR=$(COMPILED_LIBS)/libunrar.so
LIB_UV=$(COMPILED_LIBS)/libuv.a
LIBS=$(LIB_GME) $(LIB_UNRAR) $(LIB_UV)
LIBFLAGS=-std=c++11
LDFLAGS=-Wl,-rpath,'$ORIGIN' -pthread
SOURCE_DIR=./src
SOURCE_FILES=$(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/Package.cpp $(SOURCE_DIR)/unrar.cpp $(SOURCE_DIR)/libuvHandlers.cpp
OUTPUT_DIR=./out
OUTPUT=-o $(OUTPUT_DIR)/spcrenamer

all: clean makeoutputdir copylibs
	$(CC) $(OUTPUT) $(SOURCE_FILES) $(LIBS) $(LIBFLAGS) $(LDFLAGS)

.PHONY: mkoutputdir copylibs clean

makeoutputdir:
	mkdir $(OUTPUT_DIR)

copylibs:
	cp $(COMPILED_LIBS)/*.so $(OUTPUT_DIR)

clean:
	rm -rf $(OUTPUT_DIR)
