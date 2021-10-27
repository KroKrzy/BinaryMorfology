#ifndef PICTURE_H
#define PICTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RGBPixel.h"
#include "PixelArr.h"

using namespace std;

class RGBPixel;
class PixelArr;
class Picture{
public:
    Picture();
    void loadPicture(char* path);
    void monochrome();
    int getw();
    int geth();
    ~Picture();
private:
    SDL_Surface* surf;
    PixelArr array;

    
};


#endif
