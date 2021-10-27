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
    uint8_t getr();
    uint8_t getg();
    uint8_t getb();
    uint8_t geta();
    void setr(uint8_t nr, int x, int y);
    void setr(uint8_t nr, int i);
    void setg(uint8_t ng, int x, int y);
    void setg(uint8_t ng, int i);
    void setb(uint8_t nb, int x, int y);
    void setb(uint8_t nb, int i);
    void seta(uint8_t na, int x, int y);
    void seta(uint8_t na, int i);
    void setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int x, int y);
    void setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int i);
    ~RGBPixel();
    
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    short val;
};

#endif
