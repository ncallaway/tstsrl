OBJS = main.o
CC = g++
DEBUG = -g

SRC_PATH = ../../src/linux

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CFLAGS = -Wall -c $(DEBUG) $(SDL_CFLAGS)
LFLAGS = -Wall $(DEBUG) $(SDL_LDFLAGS)

OUTPUT_DIR = ../../bin/linux
TARGET = tstsrl

tstsrl: main.o
	cd $(OUTPUT_DIR); $(CC) -o $(TARGET) $(OBJS) $(LFLAGS)	

main.o: mkdir $(SRC_PATH)/main.cpp
	$(CC) -o $(OUTPUT_DIR)/main.o $(SRC_PATH)/main.cpp $(CFLAGS)

clean: mkdir
	cd $(OUTPUT_DIR); rm -f *

mkdir:
	mkdir -p $(OUTPUT_DIR)
