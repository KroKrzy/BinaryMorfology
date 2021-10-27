cc := g++

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c++11 -Wall -lstdc++ -lSDL2_image -lm

HDRS := RGBPixel.h Picture.h PixelArr.h Singleton.h

SRCS := main.cpp RGBPixel.cpp Picture.cpp PixelArr.cpp Singleton.cpp

OBJS := $(SRCS:.cpp=.o)

EXEC := test

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
claen:
	rm -f $(EXEC) $(OBJS)
.PHONY: all clean