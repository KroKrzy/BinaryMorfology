#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "PixelArr.h"
#include "Singleton.h"
#include "RGBPixel.h"

using namespace std;

PixelArr::PixelArr()
{
    this->setall();
};
void PixelArr::setall()
{
    SDL_Surface* &sur = Singleton::getInstance().surface;
    this->sizex=sur->w;
    this->sizey=sur->h;
    this->size=this->sizex*this->sizey;
    this->array=new RGBPixel[this->size];
    for(int x=0;x<this->sizex;x++){
        for(int y = 0; y<this->sizey; y++){
            this->set(x,y);
        }
    }
};
void PixelArr::set(int x, int y)
{
    this->array[this->sizey*y+x].setpixelrgb(x,y);
}
short PixelArr::get(int x, int y)
{
    return this->array[this->sizey*y+x].getValue();
}
void PixelArr::setValue(int x, int y, short value)
{
    this->array[this->sizey*y+x].setvalue(x,y,value);
}

PixelArr::~PixelArr()
{
    delete [] this->array;
}




