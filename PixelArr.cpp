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
int PixelArr::getsize()
{
    return this->size;
}
void PixelArr::setValue(int x, int y, short value)
{
    this->array[this->sizey*y+x].setvalue(x,y,value);
}
uint8_t PixelArr::getr(int x, int y)
{
    return this->array[this->sizey*y+x].getr();
}
uint8_t PixelArr::getr(int i)
{
    return this->array[i].getr();
}
uint8_t PixelArr::getg(int x, int y)
{
    return this->array[this->sizey*y+x].getg();
}
uint8_t PixelArr::getg(int i)
{
    return this->array[i].getg();
}
uint8_t PixelArr::getb(int x, int y)
{
    return this->array[this->sizey*y+x].getb();
}
uint8_t PixelArr::getb(int i)
{
    return this->array[i].getb();
}
void PixelArr::setrgb(int x,int y, uint8_t nr, uint8_t ng, uint8_t nb)
{
    this->array[this->sizey*y+x].setrgb(x,y,nr,ng,nb);
}
void PixelArr::setrgb(int i, uint8_t nr, uint8_t ng, uint8_t nb)
{
    this->array[i].setrgb(i,nr,ng,nb);
}




PixelArr::~PixelArr()
{
    delete [] this->array;
}




