cc := g++

CFLAGS := `sdl2-config --libs --cflags` -g -ggdb -ggdb3 -O0 --std=c++11 -Wall -lstdc++ -lSDL2_image -lm

HDRS := RGBPixel.h PixelArr.h

SRCS := main.cpp RGBPixel.cpp PixelArr.cpp

OBJS := $(SRCS:.cpp=.o)

EXEC := test

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
clean:
	rm -f $(EXEC) $(OBJS)
.PHONY:	all clean
