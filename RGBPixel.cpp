#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "RGBPixel.h"
#include "Singleton.h"


using namespace std;

RGBPixel::RGBPixel::RGBPixel(){};
RGBPixel::RGBPixel(int x, int y)
{
    this->setpixelrgb(x,y);
}

void RGBPixel::setpixelrgb(int x, int y)
{
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t pixel = *((uint32_t *) sur->pixels + y * sur->w + x );
    SDL_GetRGBA(pixel,sur->format,&r,&g,&b,&a);
}

short RGBPixel::getValue()
{
    return val;
}

void RGBPixel::setvalue(int x, int y, short value)
{
    SDL_Surface* sur=Singleton::getInstance()->sur;
    unsigned char *pixels = (unsigned char*)sur->pixels;
    unsigned char newVal;
    if ( value == 0 ){
        newVal = 0;
    }
    else if ( value == 1){
        newVal = 255;
    }
    else{
        cout << "Wrong pixel value x="<<x<<"y="<<y<<endl;
        exit(1);
    }
    uint32_t amask = sur->format->Amask;
    short ignore;
    switch(amask){
        case 0xFF000000:
            ignore=0;
            break;
        case 0x00FF0000:
            ignore=1;
            break;
        case 0x0000FF00:
            ignore=2;
            break;
        case 0x000000FF:
            ignore=3;
            break;
        default:
            cout<<"Error: Wrong format"<<endl;
            exit(1);
    }
    for (short c = 0;c<4;c++){
        if (c!=ignore){
            pixels[4*(y*sur->w+x)+c]*=newVal;
        }
    }
}
uint8_t RGBPixel::getr()
{
    return this->r;
    
}
uint8_t RGBPixel::getg()
{
    return this->g;
}
uint8_t RGBPixel::getb()
{
    return this->b;
}

void RGBPixel::setr(uint8_t nr,int x, int y)
{
    this->r=nr;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t rmask = sur->format->Rmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (rmask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]*=nr;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]*=nr;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]*=nr;
            break;
        case 0x000000FF:
            pixels[4*(y*sur->w+x)+3]*=nr;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setr(uint8_t nr,int i)
{
    this->r=nr;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t rmask = sur->format->Rmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (rmask){
        case 0xFF000000:
            pixels[4*(i)]*=nr;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]*=nr;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]*=nr;
            break;
        case 0x000000FF:
            pixels[4*(i)+3]*=nr;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setg(uint8_t ng, int x, int y)
{
    this->g=ng;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t gmask = sur->format->Gmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (gmask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]*=ng;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]*=ng;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]*=ng;
            break;
        case 0x000000FF:
            pixels[r*(y*sur->w+x)+3]*=ng;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setg(uint8_t ng, int i)
{
    this->g=ng;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t gmask = sur->format->Gmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (gmask){
        case 0xFF000000:
            pixels[4*(i)]*=ng;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]*=ng;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]*=ng;
            break;
        case 0x000000FF:
            pixels[4*(i)+3]*=ng;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setb(uint8_t nb, int x, int y)
{
    this->b=nb;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t bmask = sur->format->Bmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (bmask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]*=nb;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]*=nb;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]*=nb;
            break;
        case 0x000000FF:
            pixels[4*(y*sur->w+x)+3]*=nb;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setb(uint8_t nb, int i)
{
    this->b=nb;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t bmask = sur->format->Bmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (bmask){
        case 0xFF000000:
            pixels[4*(i)]*=nb;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]*=nb;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]*=nb;
            break;
        case 0x000000FF:
            pixels[4*(i)+3]*=nb;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::seta(uint8_t na, int x, int y)
{
    this->a=na;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t amask = sur->format->Amask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (amask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]*=na;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]*=na;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]*=na;
            break;
        case 0x000000FF:
            pixels[4*(y*sur->w+x)+3]*=na;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::seta(uint8_t na, int i)
{
    this->a=na;
    SDL_Surface* sur=Singleton::getInstance()->sur;
    uint32_t amask = sur->format->Amask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (amask){
        case 0xFF000000:
            pixels[4*(i)]*=na;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]*=na;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]*=na;
            break;
        case 0x000000FF:
            pixels[r*(i)+3]*=na;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}

void RGBPixel::setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int x, int y)
{
    this->setr(nr,x,y);
    this->setg(ng,x,y);
    this->setb(nb,x,y);
}
void RGBPixel::setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int i)
{
    this->setr(nr,i);
    this->setg(ng,i);
    this->setb(nb,i);
}
RGBPixel::~RGBPixel(){;}




