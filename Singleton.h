#ifndef SINGLETON_H
#define SINGLETON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>

#include "RGBPixel.h"
#include "PixelArr.h"
#include "Singleton.h"

class RGBPixel;
class Singleton{
private:
    static Singleton* instance_;
    Singleton();
    ~Singleton();
public:
    static Singleton* getInstance();
    RGBPixel *array;
    SDL_Surface * sur;
};
#endif
