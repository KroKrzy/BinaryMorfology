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
    void setValue(int x, int y,short value);
    ~PixelArr();
private:
    
    int size,sizex,sizey;
    RGBPixel *array;
    
    
    
};


#endif
