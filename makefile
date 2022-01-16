cc := g++

CFLAGS := `sdl2-config --libs --cflags` -g -ggdb -ggdb3 -O0 --std=c++14 -Wall -lstdc++ -lstdc++fs -lSDL2_image -lSDL2_ttf -lm

HDRS := PixelArr.h Textures.h Window.h

SRCS := main.cpp PixelArr.cpp Textures.cpp Window.cpp

OBJS := $(SRCS:.cpp=.o)

EXEC := app

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
clean:
	rm -f $(EXEC) $(OBJS)
.PHONY:	all clean
