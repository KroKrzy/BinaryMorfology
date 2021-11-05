#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "PixelArr.h"
#include "Singleton.h"
#include "RGBPixel.h"

using namespace std;

PixelArr::PixelArr(){}

void PixelArr::setall()
{
    Singleton* sin = Singleton::getInstance();
    sizex=sin->sur->w;
    sizey=sin->sur->h;
    size=sizex*sizey;
    array=new RGBPixel[size];
    for(int x=0;x<sizex;x++){
        for(int y = 0; y<sizey; y++){
            set(x,y);
        }
    }
};
void PixelArr::set(int x, int y)
{
    array[sizey*y+x].setpixelrgb(x,y);
}
short PixelArr::get(int x, int y)
{
    return array[sizey*y+x].getValue();
}
int PixelArr::getsize()
{
    return size;
}
void PixelArr::setValue(int x, int y, short value)
{
    array[sizey*y+x].setvalue(x,y,value);
}
uint8_t PixelArr::getr(int x, int y)
{
    return array[this->sizey*y+x].getr();
}
uint8_t PixelArr::getr(int i)
{
    return array[i].getr();
}
uint8_t PixelArr::getg(int x, int y)
{
    return array[sizey*y+x].getg();
}
uint8_t PixelArr::getg(int i)
{
    return array[i].getg();
}
uint8_t PixelArr::getb(int x, int y)
{
    return array[sizey*y+x].getb();
}
uint8_t PixelArr::getb(int i)
{
    return array[i].getb();
}
void PixelArr::setrgb(int x,int y, uint8_t nr, uint8_t ng, uint8_t nb)
{
    array[sizey*y+x].setrgb(x,y,nr,ng,nb);
}
void PixelArr::setrgb(int i, uint8_t nr, uint8_t ng, uint8_t nb)
{
    array[i].setrgb(i,nr,ng,nb);
}
int PixelArr::getW()
{
    return sizex;
}
int PixelArr::getH()
{
    return sizey;
}
void PixelArr::loadPicture(char* path)
{
    SDL_Surface* surf = Singleton::getInstance()->sur;
    surf=IMG_Load(path);
    if (!surf){
        cout<<"Error creating surface"<<endl;
        SDL_Quit();
        exit(1);
    }
}
void PixelArr::monochrome()
{
    for(int i = 0;i<getsize();i++)
    {
        uint8_t newval=0.299*getr(i)+0.587*getg(i)+0.114*getb(i);
        setrgb(i,newval,newval,newval);
    }
}

PixelArr::~PixelArr()
{
    delete [] array;
}








