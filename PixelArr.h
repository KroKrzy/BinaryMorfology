#ifndef PIXELARR_H
#define PIXELARR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Singleton.h"
#include "RGBPixel.h"

using namespace std;

class Singleton;
class RGBPixel;
class PixelArr{
public:
    PixelArr();
    void setall();
    void set(int x,int y);
    short get(int x,int y);
    int getsize();
    void setValue(int x, int y,short value);
    uint8_t getr(int x, int y);
    uint8_t getr(int i);
    uint8_t getg(int x, int y);
    uint8_t getg(int i);
    uint8_t getb(int x, int y);
    uint8_t getb(int i);
    void setrgb(int x, int y, uint8_t nr, uint8_t ng, uint8_t nb);
    void setrgb(int i, uint8_t nr, uint8_t ng, uint8_t nb);
    ~PixelArr();
private:
    
    int size,sizex,sizey;
    RGBPixel *array;
    
    
    
};


#endif