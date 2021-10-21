#ifndef RGBPIXEL_H
#define RGBPIXEL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Singleton.h"

using namespace std;

class Singleton;
class RGBPixel
{
public:
    RGBPixel();
    RGBPixel(int x, int y);
    void setpixelrgb(int x,int y);
    void setvalue(int x, int y, short value);
    short getValue();
    ~RGBPixel();
    
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    short val;
};

#endif
