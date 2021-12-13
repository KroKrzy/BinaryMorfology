#ifndef PIXELARR_H
#define PIXELARR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <sstream>


#include "RGBPixel.h"

using namespace std;

class Singleton;
class RGBPixel;
class PixelArr{
public:
    SDL_Surface * sur;
    PixelArr();
    short get(int x,int y);
    int getsize();
    void setValue(int x, int y, short value);
    void getrgb(int x, int y);
    int getW();
    int getH();
    void loadPicture(char* path);
    void setpixelrgb(int x,int y);
    void setvalue(int x, int y, short value);
    short getValue(int x, int y);
    void setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int x, int y);
    void monochrome();
    void loadPicturetxt(string path);
    void dilation(string path);
    void erosion(string path);
    void open(string path);
    void close(string path);
    ~PixelArr();
private:
    Uint32 getpixel(int x, int y);
    Uint8 r,g,b;
    
    
};


#endif
